/**
 * JazReader.ts - JAZ texture format reader for Crimsonland
 *
 * File layout:
 *   - u8  method: compression method (1 = zlib)
 *   - u32 comp_size: compressed payload size (bytes)
 *   - u32 raw_size: uncompressed payload size (bytes)
 *   - zlib stream (length = comp_size)
 *
 * Decompressed payload:
 *   - u32 jpeg_len
 *   - jpeg bytes (length = jpeg_len)
 *   - alpha_rle: (count, value) byte pairs for alpha channel
 *
 * Notes:
 *   - Alpha runs expand to width*height for most files
 *   - Some files may be short by 1 pixel; we pad with 0 (transparent)
 */

import pako from 'pako';

export interface JazImage {
    width: number;
    height: number;
    jpegData: Uint8Array;
    alphaData: Uint8Array;
}

/**
 * Decode RLE-encoded alpha channel data.
 * Format: pairs of (count, value) bytes.
 * @param data - The RLE encoded alpha data
 * @param expectedSize - Expected number of alpha pixels (width * height)
 * @returns Decoded alpha channel as Uint8Array
 */
export function decodeAlphaRLE(data: Uint8Array, expectedSize: number): Uint8Array {
    const out = new Uint8Array(expectedSize);
    let filled = 0;

    for (let i = 0; i < data.length - 1; i += 2) {
        const count = data[i];
        const value = data[i + 1];

        if (count === 0) continue;
        if (filled >= expectedSize) break;

        const end = Math.min(filled + count, expectedSize);
        out.fill(value, filled, end);
        filled = end;
    }

    // Remaining pixels are already 0 (transparent) due to Uint8Array initialization
    return out;
}

/**
 * Decode a JAZ texture from raw bytes.
 * This version uses an OffscreenCanvas or Image element to decode JPEG dimensions.
 *
 * @param data - The raw JAZ file data
 * @returns Promise resolving to JazImage with JPEG data and decoded alpha
 * @throws Error if compression method is unsupported or decompression fails
 */
export async function decodeJaz(data: ArrayBuffer): Promise<JazImage> {
    const view = new DataView(data);

    // Read header
    const method = view.getUint8(0);
    const compSize = view.getUint32(1, true);
    const rawSize = view.getUint32(5, true);

    if (method !== 1) {
        throw new Error(`Unsupported JAZ compression method: ${method}`);
    }

    // Extract compressed data
    const compressed = new Uint8Array(data, 9, compSize);

    // Decompress with pako
    let raw: Uint8Array;
    try {
        raw = pako.inflate(compressed);
    } catch (e) {
        throw new Error(`JAZ decompression failed: ${e}`);
    }

    if (raw.length !== rawSize) {
        throw new Error(`JAZ raw size mismatch: got ${raw.length}, expected ${rawSize}`);
    }

    // Parse decompressed payload
    const rawView = new DataView(raw.buffer, raw.byteOffset, raw.byteLength);
    const jpegLen = rawView.getUint32(0, true);
    const jpegData = raw.slice(4, 4 + jpegLen);
    const alphaRLE = raw.slice(4 + jpegLen);

    // Decode JPEG to get dimensions
    const { width, height } = await getJpegDimensions(jpegData);

    // Decode alpha channel
    const alphaData = decodeAlphaRLE(alphaRLE, width * height);

    return {
        width,
        height,
        jpegData,
        alphaData,
    };
}

/**
 * Decode JAZ synchronously when dimensions are already known.
 * Useful for batch processing or when JPEG parsing is handled externally.
 *
 * @param data - The raw JAZ file data
 * @param width - Known image width
 * @param height - Known image height
 * @returns JazImage with JPEG data and decoded alpha
 */
export function decodeJazSync(data: ArrayBuffer, width: number, height: number): JazImage {
    const view = new DataView(data);

    const method = view.getUint8(0);
    const compSize = view.getUint32(1, true);
    const rawSize = view.getUint32(5, true);

    if (method !== 1) {
        throw new Error(`Unsupported JAZ compression method: ${method}`);
    }

    const compressed = new Uint8Array(data, 9, compSize);
    const raw = pako.inflate(compressed);

    if (raw.length !== rawSize) {
        throw new Error(`JAZ raw size mismatch: got ${raw.length}, expected ${rawSize}`);
    }

    const rawView = new DataView(raw.buffer, raw.byteOffset, raw.byteLength);
    const jpegLen = rawView.getUint32(0, true);
    const jpegData = raw.slice(4, 4 + jpegLen);
    const alphaRLE = raw.slice(4 + jpegLen);

    const alphaData = decodeAlphaRLE(alphaRLE, width * height);

    return {
        width,
        height,
        jpegData,
        alphaData,
    };
}

/**
 * Get JPEG dimensions by decoding the image.
 * Works in both browser (Image element) and Node.js (requires canvas or similar).
 */
async function getJpegDimensions(jpegData: Uint8Array): Promise<{ width: number; height: number }> {
    // Browser environment: use Image element
    if (typeof window !== 'undefined' && typeof Image !== 'undefined') {
        const blob = new Blob([jpegData.buffer as ArrayBuffer], { type: 'image/jpeg' });
        const url = URL.createObjectURL(blob);

        try {
            const img = new Image();
            await new Promise<void>((resolve, reject) => {
                img.onload = () => resolve();
                img.onerror = () => reject(new Error('Failed to load JPEG'));
                img.src = url;
            });
            return { width: img.width, height: img.height };
        } finally {
            URL.revokeObjectURL(url);
        }
    }

    // OffscreenCanvas for workers
    if (typeof OffscreenCanvas !== 'undefined') {
        const blob = new Blob([jpegData.buffer as ArrayBuffer], { type: 'image/jpeg' });
        const bitmap = await createImageBitmap(blob);
        return { width: bitmap.width, height: bitmap.height };
    }

    // Fallback: parse JPEG header manually for dimensions
    return parseJpegDimensions(jpegData);
}

/**
 * Parse JPEG dimensions from header markers (SOF0/SOF2).
 * This works without any DOM/Canvas dependencies.
 */
function parseJpegDimensions(data: Uint8Array): { width: number; height: number } {
    let i = 0;

    // Check JPEG SOI marker
    if (data[0] !== 0xff || data[1] !== 0xd8) {
        throw new Error('Invalid JPEG: missing SOI marker');
    }
    i = 2;

    while (i < data.length - 1) {
        if (data[i] !== 0xff) {
            i++;
            continue;
        }

        const marker = data[i + 1];

        // Skip padding FF bytes
        if (marker === 0xff) {
            i++;
            continue;
        }

        // SOF markers (Start of Frame) contain dimensions
        // SOF0 (0xC0), SOF1 (0xC1), SOF2 (0xC2), SOF3 (0xC3)
        if (marker >= 0xc0 && marker <= 0xc3) {
            // SOF segment: length(2) + precision(1) + height(2) + width(2)
            if (i + 9 >= data.length) break;
            const height = (data[i + 5] << 8) | data[i + 6];
            const width = (data[i + 7] << 8) | data[i + 8];
            return { width, height };
        }

        // Skip to next marker
        if (i + 3 >= data.length) break;
        const len = (data[i + 2] << 8) | data[i + 3];
        i += 2 + len;
    }

    throw new Error('Could not find JPEG dimensions in header');
}

/**
 * Compose a JazImage into an RGBA ImageData object.
 * Requires browser environment (Canvas API).
 *
 * @param image - The decoded JazImage
 * @returns Promise resolving to ImageData with RGBA pixels
 */
export async function jazToImageData(image: JazImage): Promise<ImageData> {
    const { width, height, jpegData, alphaData } = image;

    // Decode JPEG to get RGB pixels
    let canvas: HTMLCanvasElement | OffscreenCanvas;
    let ctx: CanvasRenderingContext2D | OffscreenCanvasRenderingContext2D | null;

    if (typeof OffscreenCanvas !== 'undefined') {
        canvas = new OffscreenCanvas(width, height);
        ctx = canvas.getContext('2d');
    } else if (typeof document !== 'undefined') {
        canvas = document.createElement('canvas');
        canvas.width = width;
        canvas.height = height;
        ctx = canvas.getContext('2d');
    } else {
        throw new Error('jazToImageData requires browser environment');
    }

    if (!ctx) {
        throw new Error('Failed to get 2D context');
    }

    // Draw JPEG to canvas
    const blob = new Blob([jpegData.buffer as ArrayBuffer], { type: 'image/jpeg' });
    const bitmap = await createImageBitmap(blob);
    ctx.drawImage(bitmap, 0, 0);

    // Get pixel data and apply alpha
    const imageData = ctx.getImageData(0, 0, width, height);
    const pixels = imageData.data;

    // Apply JAZ alpha channel with alpha test.
    // C code: Grim2D uses ALPHATESTENABLE=1, ALPHAFUNC=GREATER, ALPHAREF=4
    // This discards any pixel with alpha ≤ 4. Without this, JPEG compression
    // artifacts at transparent pixels (arbitrary RGB colors) bleed through
    // during rendering, causing wrong-colored smudges (e.g. green/brown
    // on white snow terrain where ~16% of texture pixels have alpha ≤ 4).
    for (let i = 0; i < alphaData.length; i++) {
        const a = alphaData[i];
        const idx = i * 4;
        if (a <= 4) {
            // Alpha test: discard near-transparent pixels entirely
            // Zero out RGB to prevent JPEG color artifacts from bleeding
            pixels[idx] = 0; // R
            pixels[idx + 1] = 0; // G
            pixels[idx + 2] = 0; // B
            pixels[idx + 3] = 0; // A
        } else {
            pixels[idx + 3] = a;
        }
    }

    return imageData;
}
