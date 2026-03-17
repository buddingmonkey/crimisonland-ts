/**
 * AssetManager.test.ts - Unit tests for AssetManager
 */

import { describe, it, expect, beforeEach, afterEach, vi } from 'vitest';
import { AssetManager } from '../AssetManager';
import { writePaq } from '../PaqReader';

describe('AssetManager', () => {
    let assetManager: AssetManager;

    beforeEach(() => {
        assetManager = new AssetManager();
    });

    afterEach(() => {
        assetManager.dispose();
    });

    describe('loadPaqFromBuffer', () => {
        it('should load entries from PAQ buffer', () => {
            const entries = [
                { name: 'test.txt', data: new TextEncoder().encode('Hello World') },
                { name: 'dir/file.bin', data: new Uint8Array([1, 2, 3]) },
            ];
            const paqBuffer = writePaq(entries);

            assetManager.loadPaqFromBuffer(paqBuffer, 'test.paq');

            expect(assetManager.fileCount).toBe(2);
            expect(assetManager.hasFile('test.txt')).toBe(true);
            expect(assetManager.hasFile('dir/file.bin')).toBe(true);
        });

        it('should not reload already loaded PAQ', () => {
            const entries = [{ name: 'a.txt', data: new Uint8Array([1]) }];
            const paqBuffer = writePaq(entries);

            assetManager.loadPaqFromBuffer(paqBuffer, 'test.paq');
            assetManager.loadPaqFromBuffer(paqBuffer, 'test.paq'); // Duplicate

            expect(assetManager.fileCount).toBe(1);
        });
    });

    describe('getFile', () => {
        beforeEach(() => {
            const entries = [{ name: 'test.txt', data: new TextEncoder().encode('content') }];
            assetManager.loadPaqFromBuffer(writePaq(entries), 'test');
        });

        it('should return file data for existing file', () => {
            const data = assetManager.getFile('test.txt');
            expect(data).not.toBeNull();
            expect(new TextDecoder().decode(data!)).toBe('content');
        });

        it('should return null for missing file', () => {
            expect(assetManager.getFile('missing.txt')).toBeNull();
        });

        it('should normalize path case', () => {
            expect(assetManager.getFile('TEST.TXT')).not.toBeNull();
        });

        it('should normalize backslashes', () => {
            const entries = [{ name: 'dir/subdir/file.txt', data: new Uint8Array([1]) }];
            assetManager.loadPaqFromBuffer(writePaq(entries), 'test2');

            expect(assetManager.getFile('dir\\subdir\\file.txt')).not.toBeNull();
        });
    });

    describe('hasFile', () => {
        beforeEach(() => {
            const entries = [{ name: 'exists.txt', data: new Uint8Array([1]) }];
            assetManager.loadPaqFromBuffer(writePaq(entries), 'test');
        });

        it('should return true for existing file', () => {
            expect(assetManager.hasFile('exists.txt')).toBe(true);
        });

        it('should return false for missing file', () => {
            expect(assetManager.hasFile('missing.txt')).toBe(false);
        });
    });

    describe('listFiles', () => {
        beforeEach(() => {
            const entries = [
                { name: 'gfx/player.jaz', data: new Uint8Array([1]) },
                { name: 'gfx/enemy.jaz', data: new Uint8Array([2]) },
                { name: 'sfx/shoot.wav', data: new Uint8Array([3]) },
            ];
            assetManager.loadPaqFromBuffer(writePaq(entries), 'test');
        });

        it('should list all files without prefix', () => {
            const files = assetManager.listFiles();
            expect(files).toHaveLength(3);
        });

        it('should filter files by prefix', () => {
            const gfxFiles = assetManager.listFiles('gfx/');
            expect(gfxFiles).toHaveLength(2);
            expect(gfxFiles.every((f) => f.startsWith('gfx/'))).toBe(true);
        });

        it('should return empty array for non-matching prefix', () => {
            expect(assetManager.listFiles('nonexistent/')).toHaveLength(0);
        });
    });

    describe('dispose', () => {
        it('should clear all data', () => {
            const entries = [{ name: 'test.txt', data: new Uint8Array([1]) }];
            assetManager.loadPaqFromBuffer(writePaq(entries), 'test');

            assetManager.dispose();

            expect(assetManager.fileCount).toBe(0);
            expect(assetManager.textureCount).toBe(0);
        });
    });

    describe('getTexture', () => {
        it('should return null and warn for missing file', async () => {
            const warnSpy = vi.spyOn(console, 'warn').mockImplementation(() => {});

            const texture = await assetManager.getTexture('missing.jaz');

            expect(texture).toBeNull();
            expect(warnSpy).toHaveBeenCalledWith(expect.stringContaining('file not found'));

            warnSpy.mockRestore();
        });

        // Note: Full texture loading tests require browser environment
        // Real integration tests would use actual JAZ files from content/
    });

    describe('options', () => {
        it('should use basePath in URL construction', async () => {
            const manager = new AssetManager({ basePath: '/assets/' });

            // Mock fetch to verify URL
            const fetchSpy = vi.spyOn(globalThis, 'fetch').mockRejectedValue(new Error('expected fetch'));

            try {
                await manager.loadPaq('test.paq');
            } catch {
                // Expected to fail
            }

            expect(fetchSpy).toHaveBeenCalledWith('/assets/test.paq');

            fetchSpy.mockRestore();
            manager.dispose();
        });
    });
});
