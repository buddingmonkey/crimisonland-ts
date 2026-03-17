/**
 * JazReader.test.ts - Unit tests for JAZ format reader
 */

import { describe, it, expect } from 'vitest';
import { decodeAlphaRLE, decodeJazSync } from '../JazReader';
import { readPaq } from '../PaqReader';
import pako from 'pako';
import * as fs from 'fs';
import * as path from 'path';

describe('JazReader', () => {
    describe('decodeAlphaRLE', () => {
        it('should decode simple RLE sequence', () => {
            // 3 pixels of value 255, 2 pixels of value 128
            const rle = new Uint8Array([3, 255, 2, 128]);
            const result = decodeAlphaRLE(rle, 5);

            expect(Array.from(result)).toEqual([255, 255, 255, 128, 128]);
        });

        it('should handle zero count (no-op)', () => {
            const rle = new Uint8Array([0, 255, 3, 128]);
            const result = decodeAlphaRLE(rle, 3);

            expect(Array.from(result)).toEqual([128, 128, 128]);
        });

        it('should pad short sequences with zeros', () => {
            // Only 2 pixels defined but expecting 5
            const rle = new Uint8Array([2, 200]);
            const result = decodeAlphaRLE(rle, 5);

            expect(Array.from(result)).toEqual([200, 200, 0, 0, 0]);
        });

        it('should not overflow past expected size', () => {
            // Trying to write 10 pixels but only expecting 3
            const rle = new Uint8Array([10, 100]);
            const result = decodeAlphaRLE(rle, 3);

            expect(result.length).toBe(3);
            expect(Array.from(result)).toEqual([100, 100, 100]);
        });

        it('should handle empty RLE', () => {
            const rle = new Uint8Array([]);
            const result = decodeAlphaRLE(rle, 4);

            expect(Array.from(result)).toEqual([0, 0, 0, 0]);
        });

        it('should handle alternating runs', () => {
            // Checkerboard-ish: 1 opaque, 1 transparent, 1 opaque, 1 transparent
            const rle = new Uint8Array([1, 255, 1, 0, 1, 255, 1, 0]);
            const result = decodeAlphaRLE(rle, 4);

            expect(Array.from(result)).toEqual([255, 0, 255, 0]);
        });
    });

    describe('decodeJazSync', () => {
        it('should reject unsupported compression method', () => {
            // Method 0 instead of 1
            const badData = new ArrayBuffer(9);
            const view = new DataView(badData);
            view.setUint8(0, 0); // method = 0 (unsupported)
            view.setUint32(1, 1, true); // comp_size
            view.setUint32(5, 1, true); // raw_size

            expect(() => decodeJazSync(badData, 1, 1)).toThrow('Unsupported JAZ compression method: 0');
        });

        it('should decode valid JAZ data with known dimensions', () => {
            // Create a minimal valid JAZ file
            // Payload: u32 jpeg_len + jpeg_bytes + alpha_rle
            // We'll use a minimal valid JPEG (just enough to not crash)
            // For this test, we'll create synthetic data

            // Minimal "JPEG" (just FFD8 FFD9 - SOI and EOI markers)
            const fakeJpeg = new Uint8Array([0xff, 0xd8, 0xff, 0xd9]);

            // Alpha RLE: 4 fully opaque pixels (2x2 image)
            const alphaRle = new Uint8Array([4, 255]);

            // Build payload
            const payloadSize = 4 + fakeJpeg.length + alphaRle.length;
            const payload = new Uint8Array(payloadSize);
            const payloadView = new DataView(payload.buffer);
            payloadView.setUint32(0, fakeJpeg.length, true);
            payload.set(fakeJpeg, 4);
            payload.set(alphaRle, 4 + fakeJpeg.length);

            // Compress payload
            const compressed = pako.deflate(payload);

            // Build JAZ file
            const jazData = new ArrayBuffer(9 + compressed.length);
            const jazView = new DataView(jazData);
            jazView.setUint8(0, 1); // method = zlib
            jazView.setUint32(1, compressed.length, true);
            jazView.setUint32(5, payloadSize, true);
            new Uint8Array(jazData, 9).set(compressed);

            // Decode with known dimensions (2x2)
            const result = decodeJazSync(jazData, 2, 2);

            expect(result.width).toBe(2);
            expect(result.height).toBe(2);
            expect(result.jpegData.length).toBe(fakeJpeg.length);
            expect(result.alphaData.length).toBe(4);
            expect(Array.from(result.alphaData)).toEqual([255, 255, 255, 255]);
        });
    });

    describe('Real JAZ files from crimson.paq', () => {
        const contentDir = path.resolve(__dirname, '../../../../content');
        const crimsonPaq = path.join(contentDir, 'crimson.paq');

        it('should find and decode .jaz files from crimson.paq', async () => {
            if (!fs.existsSync(crimsonPaq)) {
                console.log('Skipping: crimson.paq not found');
                return;
            }

            const data = fs.readFileSync(crimsonPaq);
            const buffer = data.buffer.slice(data.byteOffset, data.byteOffset + data.byteLength);
            const entries = readPaq(buffer);

            // Find .jaz files
            const jazEntries = entries.filter((e) => e.name.endsWith('.jaz'));
            console.log(`Found ${jazEntries.length} .jaz files in crimson.paq`);

            if (jazEntries.length === 0) {
                console.log('No .jaz files found');
                return;
            }

            // Try to decode the first .jaz file
            const firstJaz = jazEntries[0];
            console.log(`Testing decode of: ${firstJaz.name}`);

            // We need dimensions to use decodeJazSync, so we'll verify the format is correct
            const view = new DataView(firstJaz.data.buffer, firstJaz.data.byteOffset, firstJaz.data.byteLength);
            const method = view.getUint8(0);
            const compSize = view.getUint32(1, true);
            const rawSize = view.getUint32(5, true);

            console.log(`  method: ${method}, comp_size: ${compSize}, raw_size: ${rawSize}`);
            expect(method).toBe(1); // zlib compression

            // Decompress to verify
            const compressed = firstJaz.data.slice(9, 9 + compSize);
            const raw = pako.inflate(compressed);
            expect(raw.length).toBe(rawSize);

            // Parse payload header
            const rawView = new DataView(raw.buffer, raw.byteOffset, raw.byteLength);
            const jpegLen = rawView.getUint32(0, true);
            console.log(`  jpeg_len: ${jpegLen}, alpha_rle_len: ${rawSize - 4 - jpegLen}`);

            expect(jpegLen).toBeGreaterThan(0);
            expect(jpegLen).toBeLessThan(rawSize);
        });
    });
});
