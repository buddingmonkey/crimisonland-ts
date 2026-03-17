/**
 * AssetManager.ts - Manages PAQ archives and JAZ texture loading for Crimsonland
 *
 * Provides a virtual filesystem abstraction over PAQ archives and automatic
 * conversion of JAZ textures to PIXI Textures.
 */

import { Texture } from 'pixi.js';
import { readPaq } from './PaqReader';
import { decodeJaz, jazToImageData } from './JazReader';
import { decodeTga } from './TgaDecoder';

export interface AssetManagerOptions {
    /** URL prefix for loading PAQ files (default: '') */
    basePath?: string;
    /** Whether to auto-decode .jaz files when calling getTexture (default: true) */
    autoDecodeJaz?: boolean;
}

/**
 * AssetManager provides a virtual filesystem over PAQ archives
 * and handles automatic conversion of JAZ textures to PIXI Textures.
 */
export class AssetManager {
    private options: Required<AssetManagerOptions>;

    /** Map of normalized path -> raw file data */
    private files: Map<string, Uint8Array> = new Map();

    /** Map of path -> loaded PIXI Texture (cache) */
    private textureCache: Map<string, Texture> = new Map();

    /** Track which PAQ archives have been loaded */
    private loadedPaqs: Set<string> = new Set();

    constructor(options: AssetManagerOptions = {}) {
        this.options = {
            basePath: options.basePath ?? '',
            autoDecodeJaz: options.autoDecodeJaz ?? true,
        };
    }

    /**
     * Load a PAQ archive from a URL and add its entries to the virtual filesystem.
     * @param url - URL of the PAQ file to load
     * @throws Error if fetch fails or PAQ is invalid
     */
    async loadPaq(url: string): Promise<void> {
        const fullUrl = this.options.basePath + url;

        if (this.loadedPaqs.has(fullUrl)) {
            return; // Already loaded
        }

        const response = await fetch(fullUrl);
        if (!response.ok) {
            throw new Error(`Failed to fetch PAQ: ${fullUrl} (${response.status})`);
        }

        const buffer = await response.arrayBuffer();
        const entries = readPaq(buffer);

        for (const entry of entries) {
            const normalizedPath = this.normalizePath(entry.name);
            this.files.set(normalizedPath, entry.data);
        }

        this.loadedPaqs.add(fullUrl);
    }

    /**
     * Load a PAQ archive from an ArrayBuffer directly.
     * Useful for testing or when the data is already available.
     * @param data - The PAQ file data
     * @param name - Identifier for this archive (prevents duplicate loading)
     */
    loadPaqFromBuffer(data: ArrayBuffer, name: string): void {
        if (this.loadedPaqs.has(name)) {
            return;
        }

        const entries = readPaq(data);
        for (const entry of entries) {
            const normalizedPath = this.normalizePath(entry.name);
            this.files.set(normalizedPath, entry.data);
        }

        this.loadedPaqs.add(name);
    }

    /**
     * Unload a PAQ archive and remove its entries from the virtual filesystem.
     * Note: This does not unload cached textures.
     * @param url - URL of the PAQ file to unload
     */
    unloadPaq(url: string): void {
        const fullUrl = this.options.basePath + url;
        this.loadedPaqs.delete(fullUrl);
        // Note: We don't track which files came from which PAQ,
        // so we can't selectively remove them. This is a limitation.
    }

    /**
     * Get raw file data from the virtual filesystem.
     * @param path - Path to the file (e.g., "gfx/player.jaz")
     * @returns File data or null if not found
     */
    getFile(path: string): Uint8Array | null {
        const normalizedPath = this.normalizePath(path);
        return this.files.get(normalizedPath) ?? null;
    }

    /**
     * Check if a file exists in the virtual filesystem.
     * @param path - Path to check
     */
    hasFile(path: string): boolean {
        const normalizedPath = this.normalizePath(path);
        return this.files.has(normalizedPath);
    }

    /**
     * List all files in the virtual filesystem, optionally filtered by prefix.
     * @param prefix - Optional prefix to filter by (e.g., "gfx/")
     */
    listFiles(prefix?: string): string[] {
        const normalizedPrefix = prefix ? this.normalizePath(prefix) : undefined;
        const allPaths = Array.from(this.files.keys());

        if (!normalizedPrefix) {
            return allPaths;
        }

        return allPaths.filter((p) => p.startsWith(normalizedPrefix));
    }

    /**
     * Get a PIXI Texture from a file path.
     * For JAZ files, automatically decodes and creates a texture.
     * For other image formats, attempts to load via blob URL.
     *
     * @param path - Path to the texture file
     * @returns PIXI Texture or null if not found/failed
     */
    async getTexture(path: string): Promise<Texture | null> {
        const normalizedPath = this.normalizePath(path);

        // Check cache first
        const cached = this.textureCache.get(normalizedPath);
        if (cached) {
            return cached;
        }

        const data = this.files.get(normalizedPath);
        if (!data) {
            console.warn(`AssetManager: file not found: ${path}`);
            return null;
        }

        try {
            let texture: Texture;

            if (this.isJazFile(normalizedPath) && this.options.autoDecodeJaz) {
                // Decode JAZ to PIXI Texture
                texture = await this.decodeJazToTexture(data);
            } else if (this.isTgaFile(normalizedPath)) {
                // Decode TGA to PIXI Texture
                texture = await this.decodeTgaToTexture(data);
            } else {
                // Try to load as regular image
                texture = await this.loadImageAsTexture(data, normalizedPath);
            }

            this.textureCache.set(normalizedPath, texture);
            return texture;
        } catch (error) {
            console.error(`AssetManager: failed to load texture ${path}:`, error);
            return null;
        }
    }

    /**
     * Preload multiple textures in parallel.
     * @param paths - Array of file paths to preload
     */
    async preloadTextures(paths: string[]): Promise<void> {
        await Promise.all(paths.map((p) => this.getTexture(p)));
    }

    /**
     * Get the number of loaded files.
     */
    get fileCount(): number {
        return this.files.size;
    }

    /**
     * Get the number of cached textures.
     */
    get textureCount(): number {
        return this.textureCache.size;
    }

    /**
     * Get audio data from the virtual filesystem as an ArrayBuffer for Web Audio API.
     * @param path - Path to the audio file (e.g., "pistol_fire.ogg")
     * @returns ArrayBuffer suitable for AudioContext.decodeAudioData, or null if not found
     */
    getAudioData(path: string): ArrayBuffer | null {
        const normalizedPath = this.normalizePath(path);
        const data = this.files.get(normalizedPath);
        if (!data) {
            return null;
        }
        // Convert Uint8Array to ArrayBuffer
        return data.buffer.slice(data.byteOffset, data.byteOffset + data.byteLength) as ArrayBuffer;
    }

    /**
     * Dispose of all resources.
     */
    dispose(): void {
        // Destroy all cached textures
        for (const texture of this.textureCache.values()) {
            texture.destroy(true);
        }
        this.textureCache.clear();
        this.files.clear();
        this.loadedPaqs.clear();
    }

    // ============================================
    // Private helpers
    // ============================================

    /**
     * Normalize a file path to use forward slashes and lowercase.
     */
    private normalizePath(path: string): string {
        return path.replace(/\\/g, '/').toLowerCase();
    }

    /**
     * Check if a file is a JAZ texture by extension.
     */
    private isJazFile(path: string): boolean {
        return path.endsWith('.jaz');
    }

    /**
     * Check if a file is a TGA texture by extension.
     */
    private isTgaFile(path: string): boolean {
        return path.endsWith('.tga');
    }

    /**
     * Decode TGA data to a PIXI Texture.
     */
    private async decodeTgaToTexture(data: Uint8Array): Promise<Texture> {
        // Convert to ArrayBuffer for decodeTga
        const buffer = data.buffer.slice(data.byteOffset, data.byteOffset + data.byteLength) as ArrayBuffer;

        // Decode TGA to ImageData
        const tgaImage = decodeTga(buffer);

        // Create ImageBitmap from ImageData
        const bitmap = await createImageBitmap(tgaImage.data);

        // Create PIXI Texture from ImageBitmap
        return Texture.from(bitmap);
    }

    /**
     * Decode JAZ data to a PIXI Texture.
     */
    private async decodeJazToTexture(data: Uint8Array): Promise<Texture> {
        // Convert to ArrayBuffer for decodeJaz
        const buffer = data.buffer.slice(data.byteOffset, data.byteOffset + data.byteLength) as ArrayBuffer;

        // Decode JAZ to get JPEG + alpha
        const jazImage = await decodeJaz(buffer);

        // Convert to RGBA ImageData
        const imageData = await jazToImageData(jazImage);

        // Create ImageBitmap from ImageData
        const bitmap = await createImageBitmap(imageData);

        // Create PIXI Texture from ImageBitmap
        const texture = Texture.from(bitmap);

        return texture;
    }

    /**
     * Load raw image data as a PIXI Texture (for PNG, BMP, etc.)
     */
    private async loadImageAsTexture(data: Uint8Array, path: string): Promise<Texture> {
        // Determine MIME type from extension
        const mimeType = this.getMimeType(path);

        // Create blob and load as image
        const blob = new Blob([data as BlobPart], { type: mimeType });
        const bitmap = await createImageBitmap(blob);

        return Texture.from(bitmap);
    }

    /**
     * Get MIME type from file extension.
     */
    private getMimeType(path: string): string {
        const ext = path.split('.').pop()?.toLowerCase();
        switch (ext) {
            case 'png':
                return 'image/png';
            case 'jpg':
            case 'jpeg':
                return 'image/jpeg';
            case 'gif':
                return 'image/gif';
            case 'bmp':
                return 'image/bmp';
            case 'webp':
                return 'image/webp';
            default:
                return 'application/octet-stream';
        }
    }
}
