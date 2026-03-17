/**
 * TgaDecoder.ts - Decodes TGA (Targa) image format to ImageData
 *
 * Supports both uncompressed (type 2) and RLE-compressed (type 10) TGA
 * with 24-bit (RGB) and 32-bit (RGBA) color.
 * Implements the subset of TGA features used by Crimsonland game assets.
 */

export interface TgaImage {
    width: number;
    height: number;
    data: ImageData;
}

/**
 * Decode a TGA file from raw bytes to ImageData
 * Supports both uncompressed (type 2) and RLE (type 10) true-color images.
 *
 * @param buffer - Raw TGA file data
 * @returns ImageData that can be used to create textures
 */
export function decodeTga(buffer: ArrayBuffer): TgaImage {
    const data = new Uint8Array(buffer);
    const view = new DataView(buffer);

    // TGA Header (18 bytes)
    const idLength = data[0];
    const colorMapType = data[1];
    const imageType = data[2];
    // Color map specification bytes 3-7 (ignored), x/y origin bytes 8-11 (ignored)
    const width = view.getUint16(12, true);
    const height = view.getUint16(14, true);
    const bitsPerPixel = data[16];
    const imageDescriptor = data[17];

    // Support uncompressed (2) and RLE-compressed (10) true-color images
    const isRLE = imageType === 10;
    if (imageType !== 2 && imageType !== 10) {
        throw new Error(`TGA: Unsupported image type ${imageType} (only 2=uncompressed and 10=RLE supported)`);
    }

    if (colorMapType !== 0) {
        throw new Error('TGA: Color-mapped images not supported');
    }

    if (bitsPerPixel !== 24 && bitsPerPixel !== 32) {
        throw new Error(`TGA: Unsupported bits per pixel ${bitsPerPixel} (only 24 and 32 supported)`);
    }

    const bytesPerPixel = bitsPerPixel / 8;
    const pixelDataOffset = 18 + idLength; // Header + image ID

    // Check if image is top-to-bottom or bottom-to-top
    const isTopToBottom = (imageDescriptor & 0x20) !== 0;

    // Create output ImageData
    const imageData = new ImageData(width, height);
    const output = imageData.data;
    const totalPixels = width * height;

    // Decode pixels into a temporary buffer (then reorder for orientation)
    const pixels = new Uint8Array(totalPixels * 4);

    if (isRLE) {
        // RLE-compressed decoding
        let srcOffset = pixelDataOffset;
        let pixelIndex = 0;

        while (pixelIndex < totalPixels && srcOffset < data.length) {
            const packet = data[srcOffset++];
            const count = (packet & 0x7f) + 1; // Number of pixels (1-128)
            const isRunLength = (packet & 0x80) !== 0;

            if (isRunLength) {
                // Run-length packet: repeat same color
                const b = data[srcOffset++];
                const g = data[srcOffset++];
                const r = data[srcOffset++];
                const a = bytesPerPixel === 4 ? data[srcOffset++] : 255;

                for (let i = 0; i < count && pixelIndex < totalPixels; i++) {
                    const dstOff = pixelIndex * 4;
                    pixels[dstOff + 0] = r;
                    pixels[dstOff + 1] = g;
                    pixels[dstOff + 2] = b;
                    pixels[dstOff + 3] = a;
                    pixelIndex++;
                }
            } else {
                // Raw packet: read 'count' distinct pixels
                for (let i = 0; i < count && pixelIndex < totalPixels; i++) {
                    const b = data[srcOffset++];
                    const g = data[srcOffset++];
                    const r = data[srcOffset++];
                    const a = bytesPerPixel === 4 ? data[srcOffset++] : 255;

                    const dstOff = pixelIndex * 4;
                    pixels[dstOff + 0] = r;
                    pixels[dstOff + 1] = g;
                    pixels[dstOff + 2] = b;
                    pixels[dstOff + 3] = a;
                    pixelIndex++;
                }
            }
        }
    } else {
        // Uncompressed decoding
        for (let i = 0; i < totalPixels; i++) {
            const srcOffset = pixelDataOffset + i * bytesPerPixel;
            const dstOff = i * 4;
            pixels[dstOff + 0] = data[srcOffset + 2]; // R
            pixels[dstOff + 1] = data[srcOffset + 1]; // G
            pixels[dstOff + 2] = data[srcOffset + 0]; // B
            pixels[dstOff + 3] = bytesPerPixel === 4 ? data[srcOffset + 3] : 255; // A
        }
    }

    // Copy to output with correct orientation
    for (let y = 0; y < height; y++) {
        const srcY = isTopToBottom ? y : height - 1 - y;
        for (let x = 0; x < width; x++) {
            const srcOff = (srcY * width + x) * 4;
            const dstOff = (y * width + x) * 4;
            output[dstOff + 0] = pixels[srcOff + 0];
            output[dstOff + 1] = pixels[srcOff + 1];
            output[dstOff + 2] = pixels[srcOff + 2];
            output[dstOff + 3] = pixels[srcOff + 3];
        }
    }

    return { width, height, data: imageData };
}
