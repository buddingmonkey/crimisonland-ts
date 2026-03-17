/**
 * TerrainRenderer - Procedural terrain generation matching C code
 *
 * Based on terrain_generate_random() @ line 13811 in decompiled C code.
 * Generates natural-looking ground by drawing thousands of randomly
 * positioned/rotated terrain texture copies onto a render target.
 */

import * as PIXI from 'pixi.js';
import type { AssetManager } from '../data/AssetManager';

// C code constants for terrain quad stamping
const TERRAIN_PATCH_SIZE = 128; // Quad draw size in pixels (not necessarily same as texture size)
const TERRAIN_PATCH_OVERSCAN = 64; // C: 0x80/2 = 64px overscan beyond terrain edges
const TERRAIN_ROTATION_MAX = 0x13a; // 314 — rand() % 314 * 0.01 = 0..3.14 radians

/**
 * Buffer zone (in pixels) added to each side of the playable area.
 * The terrain render texture is enlarged by 2×TERRAIN_BUFFER on each axis
 * so that blood/corpse stamps near playable edges don't wrap around.
 * 512px handles viewports up to ~1024px overscroll in each direction.
 */
export const TERRAIN_BUFFER = 512;

export class TerrainRenderer {
    private baseTexture: PIXI.Texture | null = null;
    private overlayTexture: PIXI.Texture | null = null;
    private thirdTexture: PIXI.Texture | null = null;
    private renderTexture: PIXI.RenderTexture | null = null;
    private renderer: PIXI.Renderer;

    // Full terrain texture dimensions (playable + 2×buffer on each axis)
    private width: number;
    private height: number;

    // Inner playable area dimensions (C: terrain_texture_width/height)
    private playableWidth: number;
    private playableHeight: number;

    // Default earth color from C code: grim_clear_color(0.247, 0.22, 0.098, 1.0)
    // Dynamically updated to match loaded terrain texture
    private clearColor: number = 0x3f381a; // RGB(63, 56, 26)

    constructor(renderer: PIXI.Renderer, playableWidth: number = 1024, playableHeight: number = 1024) {
        this.renderer = renderer;
        this.playableWidth = playableWidth;
        this.playableHeight = playableHeight;
        // Full texture = playable area + buffer on each side
        this.width = playableWidth + TERRAIN_BUFFER * 2;
        this.height = playableHeight + TERRAIN_BUFFER * 2;
    }

    /**
     * Load terrain textures for a specific quest tier
     * @param assetManager - Asset manager for loading textures
     * @param tier - Quest tier (1-4), defaults to 1
     */
    async load(assetManager: AssetManager, tier: number = 1): Promise<void> {
        // Clamp tier to valid range (1-4)
        const validTier = Math.max(1, Math.min(4, tier));

        // Load tier-specific base and overlay textures
        const baseJaz = await assetManager.getTexture(`ter/ter_q${validTier}_base.jaz`);
        const overlayJaz = await assetManager.getTexture(`ter/ter_q${validTier}_tex1.jaz`);

        if (baseJaz) {
            this.baseTexture = baseJaz;
            // Sample the texture to derive a matching clear color
            // This prevents the dark brown default base from showing through
            // on lighter terrains (e.g., snow/Q4 is white, not brown)
            this.clearColor = this.sampleTextureClearColor(baseJaz);
        } else {
            console.warn(`TerrainRenderer: Failed to load ter_q${validTier}_base.jaz, terrain may not render`);
        }

        if (overlayJaz) {
            this.overlayTexture = overlayJaz;
        } else {
            console.warn(`TerrainRenderer: Failed to load ter_q${validTier}_tex1.jaz, using base only`);
        }
    }

    /**
     * Generate procedural terrain matching C code algorithm
     *
     * C code draws 3 passes:
     * - Pass 1: base texture, count = area * 800 / 524288, alpha 0.9
     * - Pass 2: overlay (tex1), count = area * 0x23 / 524288, alpha 0.9
     * - Pass 3: third texture (reuses base), count = area * 0xF / 524288, alpha 0.6
     */
    generate(seed: number = Date.now()): PIXI.RenderTexture | null {
        if (!this.baseTexture) {
            console.warn('TerrainRenderer: base texture not loaded');
            return null;
        }

        // Create render texture if needed
        if (!this.renderTexture) {
            this.renderTexture = PIXI.RenderTexture.create({
                width: this.width,
                height: this.height,
            });
        }

        // Seed random number generator
        let rngState = seed | 0;
        const random = () => {
            // LCG matching C's rand() behavior — must use Math.imul for
            // proper 32-bit wraparound; plain JS multiply can exceed
            // Number.MAX_SAFE_INTEGER and lose precision, producing
            // degenerate patterns that leave visible gaps in coverage.
            rngState = (Math.imul(rngState, 1103515245) + 12345) & 0x7fffffff;
            return rngState;
        };

        // C code: grim_set_config_var(0x15, 1) — enable point/nearest filtering during stamp
        // Set point filtering on source textures before generating
        const texturesToFilter: PIXI.Texture[] = [];
        for (const tex of [this.baseTexture, this.overlayTexture, this.thirdTexture]) {
            if (tex && tex.source) {
                tex.source.scaleMode = 'nearest';
                texturesToFilter.push(tex);
            }
        }

        const container = new PIXI.Container();

        // Clear with terrain-matched color (samples from loaded texture)
        // C code uses fixed dark brown, but covers fully; PIXI may leave gaps
        const background = new PIXI.Graphics();
        background.rect(0, 0, this.width, this.height);
        background.fill(this.clearColor);
        container.addChild(background);

        // Calculate number of quads to draw (from C code formula)
        // C: terrain_texture_height * terrain_texture_width * multiplier / 524288
        const area = this.width * this.height;
        const baseQuadCount = Math.floor((area * 800) / 524288);
        const overlayQuadCount = Math.floor((area * 0x23) / 524288);
        const thirdQuadCount = Math.floor((area * 0xf) / 524288);

        // Pass 1: base texture quads (C: terrain_texture_handles, alpha 0.9)
        if (this.baseTexture) {
            this.drawRandomQuads(container, this.baseTexture, baseQuadCount, random, 0.7, 0.7, 0.7, 0.9);
        }

        // Pass 2: overlay texture quads (C: terrain_texture_q1_tex1, alpha 0.9 NOT 0.6)
        if (this.overlayTexture) {
            this.drawRandomQuads(container, this.overlayTexture, overlayQuadCount, random, 0.7, 0.7, 0.7, 0.9);
        }

        // Pass 3: third texture quads (C: iStack_54[2], reuses base, alpha 0.6)
        const thirdTex = this.thirdTexture ?? this.baseTexture;
        if (thirdTex) {
            this.drawRandomQuads(container, thirdTex, thirdQuadCount, random, 0.7, 0.7, 0.7, 0.6);
        }

        // Render to texture
        this.renderer.render({
            container,
            target: this.renderTexture,
        });

        // Cleanup
        container.destroy({ children: true });

        // C code: grim_set_config_var(0x15, 2) — restore bilinear filtering after stamp
        for (const tex of texturesToFilter) {
            if (tex.source) {
                tex.source.scaleMode = 'linear';
            }
        }

        return this.renderTexture;
    }

    /**
     * Regenerate terrain with a new tier
     * Useful when switching between quests with different terrains
     * @param assetManager - Asset manager for loading textures
     * @param tier - Quest tier (1-4)
     * @param seed - Random seed for terrain generation
     */
    async regenerate(
        assetManager: AssetManager,
        tier: number,
        seed: number = Date.now(),
    ): Promise<PIXI.RenderTexture | null> {
        await this.load(assetManager, tier);
        return this.generate(seed);
    }

    /**
     * Select terrain tier for survival mode based on quest unlock progress.
     * Mirrors C code terrain_generate_random() tier-variant logic:
     *   quest_unlock_index > 39 → 1/8 chance → Q4 textures
     *   quest_unlock_index > 29 → 1/8 chance → Q3 textures
     *   quest_unlock_index > 19 → 1/8 chance → Q2 textures
     *   otherwise              → Q1 textures (always)
     * @param questUnlockIndex - Current quest unlock progress (0-40)
     * @returns Chosen tier (1-4)
     */
    static selectSurvivalTier(questUnlockIndex: number): number {
        if (questUnlockIndex > 39 && Math.floor(Math.random() * 8) === 3) {
            return 4;
        }
        if (questUnlockIndex > 29 && Math.floor(Math.random() * 8) === 3) {
            return 3;
        }
        if (questUnlockIndex > 19 && Math.floor(Math.random() * 8) === 3) {
            return 2;
        }
        return 1;
    }

    /**
     * Draw randomly positioned and rotated texture quads
     * Matches C code loop at lines 13867-13879
     */
    private drawRandomQuads(
        container: PIXI.Container,
        texture: PIXI.Texture,
        count: number,
        random: () => number,
        r: number,
        g: number,
        b: number,
        a: number,
    ): void {
        // C code position span: rand() % (terrain_texture_width + 0x80) - 64
        // Uses terrain_texture_width for BOTH X and Y axes (terrain is square)
        const span = this.width + TERRAIN_PATCH_OVERSCAN * 2; // 1024 + 128 = 1152

        const tintColor = (Math.floor(r * 255) << 16) | (Math.floor(g * 255) << 8) | Math.floor(b * 255);

        for (let i = 0; i < count; i++) {
            const sprite = new PIXI.Sprite(texture);

            // Random rotation (C: rand() % 0x13a * 0.01 = 0..3.14 radians)
            const rotationRand = random() % TERRAIN_ROTATION_MAX;
            sprite.rotation = rotationRand * 0.01;

            // RNG order from C decompilation: rotation, then Y, then X
            // (C stack layout: fVar4 = first rand [stored as X], second rand = Y;
            //  struct passed as {fStack_58=Y, fStack_54=X})
            const yRand = random() % span;
            const xRand = random() % span;
            const patchX = xRand - TERRAIN_PATCH_OVERSCAN;
            const patchY = yRand - TERRAIN_PATCH_OVERSCAN;

            // Draw at fixed TERRAIN_PATCH_SIZE (128×128), not native texture size
            // The texture is sampled in full and scaled to the patch size
            sprite.width = TERRAIN_PATCH_SIZE;
            sprite.height = TERRAIN_PATCH_SIZE;

            // Position at patch center (anchor is 0.5, 0.5 for rotation)
            sprite.anchor.set(0.5, 0.5);
            sprite.x = patchX + TERRAIN_PATCH_SIZE * 0.5;
            sprite.y = patchY + TERRAIN_PATCH_SIZE * 0.5;

            // Apply color tint and alpha
            sprite.tint = tintColor;
            sprite.alpha = a;

            container.addChild(sprite);
        }
    }

    /**
     * Get the generated terrain texture
     */
    getTexture(): PIXI.RenderTexture | null {
        return this.renderTexture;
    }

    /**
     * Bake blood sprites into the terrain render texture.
     *
     * C code: fx_queue_render @ 00427920
     * Sets render target to terrain_render_target, draws stamped blood effects,
     * then clears the queue. Results are permanent — blood accumulates through
     * alpha blending on each frame's bake.
     *
     * @param container A PIXI.Container holding sprites to bake into terrain
     */
    bakeBlood(container: PIXI.Container): void {
        if (!this.renderTexture) return;
        if (container.children.length === 0) return;

        // Render the container into the existing terrain texture (additive bake)
        // clear=false means we preserve existing terrain pixels
        this.renderer.render({
            container,
            target: this.renderTexture,
            clear: false,
        });
    }

    /**
     * Get terrain texture dimensions for coordinate transformation.
     * Blood stamp positions must be scaled from screen space to texture space.
     */
    getTextureDimensions(): { width: number; height: number } {
        return { width: this.width, height: this.height };
    }

    /**
     * Get the renderer's screen dimensions (the game's viewport size).
     * Used to compute world-to-texture coordinate scaling.
     */
    getScreenDimensions(): { width: number; height: number } {
        return { width: this.renderer.width, height: this.renderer.height };
    }

    /**
     * Get the PIXI renderer for external systems that need to create containers
     */
    getPixiRenderer(): PIXI.Renderer {
        return this.renderer;
    }

    /**
     * Get full terrain texture dimensions (including buffer zones)
     */
    getWidth(): number {
        return this.width;
    }

    getHeight(): number {
        return this.height;
    }

    /**
     * Get the inner playable area dimensions (excluding buffer zones).
     * Used for player boundary clamping and camera clamping.
     */
    getPlayableWidth(): number {
        return this.playableWidth;
    }

    getPlayableHeight(): number {
        return this.playableHeight;
    }

    /**
     * Cleanup resources
     */
    destroy(): void {
        if (this.renderTexture) {
            this.renderTexture.destroy(true);
            this.renderTexture = null;
        }
    }

    /**
     * Sample the center of a terrain texture to derive a matching clear color.
     * This ensures the background fill matches the terrain palette, so any
     * gaps in coverage are invisible (e.g., white for snow instead of brown).
     */
    private sampleTextureClearColor(texture: PIXI.Texture): number {
        try {
            // Render texture to a small temporary canvas to sample its colors
            const canvas = document.createElement('canvas');
            canvas.width = texture.width;
            canvas.height = texture.height;
            const ctx = canvas.getContext('2d');
            if (!ctx) return 0x3f381a;

            // Extract the source image from PIXI texture.
            // Handle all drawable source types — ImageBitmap (most common from
            // JAZ decode), HTMLImageElement, HTMLCanvasElement, OffscreenCanvas,
            // and HTMLVideoElement are all valid CanvasImageSource types.
            const source = texture.source?.resource;
            if (
                source instanceof ImageBitmap ||
                source instanceof HTMLImageElement ||
                source instanceof HTMLCanvasElement ||
                (typeof OffscreenCanvas !== 'undefined' && source instanceof OffscreenCanvas) ||
                source instanceof HTMLVideoElement
            ) {
                ctx.drawImage(source as CanvasImageSource, 0, 0);
            } else {
                // Last resort: try drawImage anyway — PIXI textures from
                // RenderTexture or compressed formats may not match known types
                // but could still be drawable.
                try {
                    ctx.drawImage(source as CanvasImageSource, 0, 0);
                } catch {
                    return 0x3f381a; // Fallback
                }
            }

            // Sample center pixel
            const cx = Math.floor(texture.width / 2);
            const cy = Math.floor(texture.height / 2);
            const pixel = ctx.getImageData(cx, cy, 1, 1).data;

            // Apply the same tint factor used in terrain passes (0.7)
            const tintFactor = 0.7;
            const r = Math.floor(pixel[0] * tintFactor);
            const g = Math.floor(pixel[1] * tintFactor);
            const b = Math.floor(pixel[2] * tintFactor);

            return (r << 16) | (g << 8) | b;
        } catch {
            return 0x3f381a; // Default fallback
        }
    }
}
