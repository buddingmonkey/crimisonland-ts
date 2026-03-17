/**
 * PaqReader.test.ts - Unit tests for PAQ format reader/writer
 */

import { describe, it, expect } from 'vitest';
import { readPaq, writePaq, iterPaq, listPaq, readPaqEntry, PAQ_MAGIC } from '../PaqReader';
import * as fs from 'fs';
import * as path from 'path';

describe('PaqReader', () => {
    describe('readPaq', () => {
        it('should reject files that are too small', () => {
            const data = new ArrayBuffer(2);
            expect(() => readPaq(data)).toThrow('PAQ file too small');
        });

        it('should reject files with invalid magic bytes', () => {
            const data = new ArrayBuffer(4);
            const view = new Uint8Array(data);
            view.set([0x00, 0x00, 0x00, 0x00]);
            expect(() => readPaq(data)).toThrow('Invalid PAQ file: bad magic bytes');
        });

        it('should parse empty PAQ (only magic header)', () => {
            const data = new ArrayBuffer(4);
            new Uint8Array(data).set(PAQ_MAGIC);
            const entries = readPaq(data);
            expect(entries).toEqual([]);
        });

        it('should parse PAQ with single entry', () => {
            // Build: magic + "test.txt\0" + u32(5) + "hello"
            const name = new TextEncoder().encode('test.txt');
            const payload = new TextEncoder().encode('hello');
            const buffer = new ArrayBuffer(4 + name.length + 1 + 4 + payload.length);
            const view = new DataView(buffer);
            const bytes = new Uint8Array(buffer);

            bytes.set(PAQ_MAGIC, 0);
            bytes.set(name, 4);
            bytes[4 + name.length] = 0; // NUL terminator
            view.setUint32(4 + name.length + 1, payload.length, true);
            bytes.set(payload, 4 + name.length + 1 + 4);

            const entries = readPaq(buffer);
            expect(entries).toHaveLength(1);
            expect(entries[0].name).toBe('test.txt');
            expect(new TextDecoder().decode(entries[0].data)).toBe('hello');
        });

        it('should parse PAQ with multiple entries', () => {
            // Build manually: magic + entry1 + entry2
            const entries = [
                { name: 'file1.txt', content: 'First file' },
                { name: 'dir/file2.bin', content: '\x00\x01\x02\x03' },
            ];

            let totalSize = 4; // magic
            const encodedEntries: { name: Uint8Array; payload: Uint8Array }[] = [];
            for (const e of entries) {
                const name = new TextEncoder().encode(e.name);
                const payload = new TextEncoder().encode(e.content);
                encodedEntries.push({ name, payload });
                totalSize += name.length + 1 + 4 + payload.length;
            }

            const buffer = new ArrayBuffer(totalSize);
            const view = new DataView(buffer);
            const bytes = new Uint8Array(buffer);
            bytes.set(PAQ_MAGIC, 0);

            let offset = 4;
            for (const e of encodedEntries) {
                bytes.set(e.name, offset);
                offset += e.name.length;
                bytes[offset] = 0;
                offset += 1;
                view.setUint32(offset, e.payload.length, true);
                offset += 4;
                bytes.set(e.payload, offset);
                offset += e.payload.length;
            }

            const result = readPaq(buffer);
            expect(result).toHaveLength(2);
            expect(result[0].name).toBe('file1.txt');
            expect(result[1].name).toBe('dir/file2.bin');
        });
    });

    describe('writePaq', () => {
        it('should create valid PAQ with magic header', () => {
            const buffer = writePaq([]);
            const bytes = new Uint8Array(buffer);
            expect(bytes.slice(0, 4)).toEqual(PAQ_MAGIC);
        });

        it('should round-trip entries correctly', () => {
            const original = [
                { name: 'test.txt', data: new TextEncoder().encode('Hello World') },
                { name: 'binary.bin', data: new Uint8Array([0, 1, 2, 255]) },
            ];

            const packed = writePaq(original);
            const unpacked = readPaq(packed);

            expect(unpacked).toHaveLength(2);
            expect(unpacked[0].name).toBe('test.txt');
            expect(new TextDecoder().decode(unpacked[0].data)).toBe('Hello World');
            expect(unpacked[1].name).toBe('binary.bin');
            expect(Array.from(unpacked[1].data)).toEqual([0, 1, 2, 255]);
        });
    });

    describe('iterPaq', () => {
        it('should iterate over entries lazily', () => {
            const original = [
                { name: 'a.txt', data: new Uint8Array([1]) },
                { name: 'b.txt', data: new Uint8Array([2]) },
            ];
            const packed = writePaq(original);

            const names: string[] = [];
            for (const entry of iterPaq(packed)) {
                names.push(entry.name);
            }
            expect(names).toEqual(['a.txt', 'b.txt']);
        });
    });

    describe('listPaq', () => {
        it('should return entry names', () => {
            const original = [
                { name: 'file1.txt', data: new Uint8Array([]) },
                { name: 'dir/file2.txt', data: new Uint8Array([]) },
            ];
            const packed = writePaq(original);
            expect(listPaq(packed)).toEqual(['file1.txt', 'dir/file2.txt']);
        });
    });

    describe('readPaqEntry', () => {
        it('should return specific entry', () => {
            const original = [
                { name: 'a.txt', data: new TextEncoder().encode('A') },
                { name: 'b.txt', data: new TextEncoder().encode('B') },
            ];
            const packed = writePaq(original);

            const entry = readPaqEntry(packed, 'b.txt');
            expect(entry).not.toBeNull();
            expect(new TextDecoder().decode(entry!)).toBe('B');
        });

        it('should return null for missing entry', () => {
            const packed = writePaq([]);
            expect(readPaqEntry(packed, 'missing.txt')).toBeNull();
        });
    });

    describe('Real PAQ files', () => {
        const contentDir = path.resolve(__dirname, '../../../../content');
        const crimsonPaq = path.join(contentDir, 'crimson.paq');

        it('should parse crimson.paq if available', async () => {
            if (!fs.existsSync(crimsonPaq)) {
                console.log('Skipping: crimson.paq not found');
                return;
            }

            const data = fs.readFileSync(crimsonPaq);
            const buffer = data.buffer.slice(data.byteOffset, data.byteOffset + data.byteLength);
            const entries = readPaq(buffer);

            expect(entries.length).toBeGreaterThan(0);
            console.log(`crimson.paq contains ${entries.length} entries`);

            // Log first few entry names for verification
            const sampleNames = entries.slice(0, 10).map((e) => e.name);
            console.log('Sample entries:', sampleNames);
        });

        it('should list sfx.paq entries if available', () => {
            const sfxPaq = path.join(contentDir, 'sfx.paq');
            if (!fs.existsSync(sfxPaq)) {
                console.log('Skipping: sfx.paq not found');
                return;
            }

            const data = fs.readFileSync(sfxPaq);
            const buffer = data.buffer.slice(data.byteOffset, data.byteOffset + data.byteLength);
            const names = listPaq(buffer);

            expect(names.length).toBeGreaterThan(0);
            console.log(`sfx.paq contains ${names.length} entries`);
        });
    });
});
