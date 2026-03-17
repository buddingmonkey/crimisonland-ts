/**
 * PixiGrimAdapter.test.ts - Unit tests for PixiGrimAdapter
 *
 * Verifies that the Pixi.js implementation matches the expected behavior
 * of the original grim.dll vtable interface.
 */

import { describe, it, expect, beforeEach, afterEach, vi } from 'vitest';
import { PixiGrimAdapter } from '../PixiGrimAdapter';
import { Application } from 'pixi.js';

describe('PixiGrimAdapter', () => {
    let adapter: PixiGrimAdapter;

    beforeEach(() => {
        adapter = new PixiGrimAdapter(800, 600);
    });

    afterEach(() => {
        if (adapter) {
            adapter.shutdown();
        }
    });

    describe('Lifecycle', () => {
        // These tests require DOM/WebGL which isn't available in Node test environment
        it.skip('should initialize successfully (requires DOM)', async () => {
            const result = await adapter.init();
            expect(result).toBe(true);
            expect(adapter.getApp()).toBeInstanceOf(Application);
        });

        it.skip('should shutdown cleanly (requires DOM)', async () => {
            await adapter.init();
            adapter.shutdown();
            expect(adapter.getApp()).toBeNull();
        });

        it.skip('should handle destroy (requires DOM)', async () => {
            await adapter.init();
            adapter.destroy();
            expect(adapter.getApp()).toBeNull();
        });
    });

    describe('Timing - vtable timing functions', () => {
        // Skip beforeEach that requires init

        it.skip('should track accumulated time (requires DOM)', () => {
            const initialTime = adapter.getTime();
            expect(initialTime).toBeGreaterThanOrEqual(0);
        });

        it.skip('should allow setting time (requires DOM)', () => {
            adapter.setTime(1000);
            expect(adapter.getTime()).toBe(1000);
        });

        it.skip('should calculate delta time on beginFrame (requires DOM)', () => {
            adapter.beginFrame();

            // Simulate time passing
            vi.useFakeTimers();
            vi.advanceTimersByTime(16); // ~60fps

            adapter.beginFrame();
            const dt2 = adapter.getDeltaTime();

            expect(dt2).toBeGreaterThanOrEqual(0);
            vi.useRealTimers();
        });

        it.skip('should calculate FPS (requires DOM)', () => {
            const fps = adapter.getFPS();
            expect(fps).toBeGreaterThanOrEqual(0);
        });
    });

    describe('Input - Mouse (vtable mouse functions)', () => {
        // Skip - requires init

        it.skip('should track mouse position (requires DOM)', () => {
            adapter.setMousePosition(100, 200);
            expect(adapter.getMouseX()).toBe(100);
            expect(adapter.getMouseY()).toBe(200);
        });

        it.skip('should track mouse button state (requires DOM)', () => {
            expect(adapter.isMouseButtonDown(0)).toBe(false);
            expect(adapter.isMouseButtonPressed(0)).toBe(false);
        });

        it.skip('should track mouse delta (requires DOM)', () => {
            const deltaX = adapter.getMouseDeltaX();
            const deltaY = adapter.getMouseDeltaY();
            expect(typeof deltaX).toBe('number');
            expect(typeof deltaY).toBe('number');
        });
    });

    describe('Input - Keyboard (vtable keyboard functions)', () => {
        // Skip - requires init

        it.skip('should track key state (requires DOM)', () => {
            expect(adapter.isKeyDown(65)).toBe(false); // 'A' key
            expect(adapter.isKeyPressed(65)).toBe(false);
        });

        it.skip('should get key chars (requires DOM)', () => {
            const chars = adapter.getKeyChars();
            expect(Array.isArray(chars)).toBe(true);
        });

        it.skip('should flush input (requires DOM)', () => {
            expect(() => adapter.flushInput()).not.toThrow();
        });
    });

    describe('Textures - vtable texture functions', () => {
        // Skip - requires init

        it.skip('should create texture and return handle (requires DOM)', () => {
            const handle = adapter.createTexture('test_texture', 256, 256);
            expect(handle).toBeGreaterThan(0);
        });

        it.skip('should validate texture handle (requires DOM)', () => {
            const handle = adapter.createTexture('test_texture', 256, 256);
            expect(adapter.validateTexture(handle)).toBe(true);
            expect(adapter.validateTexture(-1)).toBe(false);
        });

        it.skip('should get texture handle by name (requires DOM)', () => {
            const handle = adapter.createTexture('test_texture', 256, 256);
            const retrievedHandle = adapter.getTextureHandle('test_texture');
            expect(retrievedHandle).toBe(handle);
        });

        it.skip('should return -1 for non-existent texture (requires DOM)', () => {
            const handle = adapter.getTextureHandle('nonexistent');
            expect(handle).toBe(-1);
        });

        it.skip('should destroy texture (requires DOM)', () => {
            const handle = adapter.createTexture('test_texture', 256, 256);
            adapter.destroyTexture(handle);
            expect(adapter.validateTexture(handle)).toBe(false);
        });

        it.skip('should bind texture (requires DOM)', () => {
            const handle = adapter.createTexture('test_texture', 256, 256);
            expect(() => adapter.bindTexture(handle)).not.toThrow();
        });
    });

    describe('Rendering State - vtable 0xfc, 0x100, 0x104, 0x108, 0x110, 0x114', () => {
        // Skip - requires init

        it.skip('should set rotation (vtable 0xfc) (requires DOM)', () => {
            // C: grim_set_rotation adds +45° for matrix math
            // TypeScript: stores directly for sprite.rotation
            expect(() => adapter.setRotation(Math.PI / 4)).not.toThrow();
        });

        it.skip('should set UV coordinates (vtable 0x100) (requires DOM)', () => {
            expect(() => adapter.setUV(0, 0, 1, 1)).not.toThrow();
        });

        it.skip('should set atlas frame (vtable 0x104) (requires DOM)', () => {
            expect(() => adapter.setAtlasFrame(8, 5)).not.toThrow();
        });

        it.skip('should set sub rect (vtable 0x108) (requires DOM)', () => {
            expect(() => adapter.setSubRect(8, 2, 2, 5)).not.toThrow();
        });

        it.skip('should set color from array (vtable 0x110) (requires DOM)', () => {
            expect(() => adapter.setColorArray([255, 128, 64, 255])).not.toThrow();
        });

        it.skip('should set color (vtable 0x114) (requires DOM)', () => {
            expect(() => adapter.setColor(255, 128, 64, 255)).not.toThrow();
        });

        it.skip('should set clear color (requires DOM)', () => {
            expect(() => adapter.setClearColor(0, 0, 0, 255)).not.toThrow();
        });
    });

    describe('Rendering - Batch (vtable 0xe8, 0xec, 0xf0)', () => {
        // Skip - requires init

        it.skip('should begin batch (vtable 0xe8) (requires DOM)', () => {
            // Pixi auto-batches, this is a no-op but should not throw
            expect(() => adapter.beginBatch()).not.toThrow();
        });

        it.skip('should flush batch (vtable 0xec) (requires DOM)', () => {
            expect(() => adapter.flushBatch()).not.toThrow();
        });

        it.skip('should end batch (vtable 0xf0) (requires DOM)', () => {
            // Pixi auto-batches, this is a no-op but should not throw
            expect(() => adapter.endBatch()).not.toThrow();
        });
    });

    describe('Rendering - Draw Commands (vtable 0xc8-0xdc, 0x11c)', () => {
        // Skip - requires init and beginFrame

        it.skip('should draw fullscreen quad (vtable 0xc8) (requires DOM)', () => {
            expect(() => adapter.drawFullscreenQuad()).not.toThrow();
        });

        it.skip('should draw fullscreen color (vtable 0xcc) (requires DOM)', () => {
            expect(() => adapter.drawFullscreenColor(255, 0, 0, 128)).not.toThrow();
        });

        it.skip('should draw filled rect (vtable 0xd0) (requires DOM)', () => {
            adapter.setColor(255, 0, 0, 255);
            expect(() => adapter.drawRectFilled(100, 100, 50, 50)).not.toThrow();
        });

        it.skip('should draw filled circle (vtable 0xd8) (requires DOM)', () => {
            adapter.setColor(0, 255, 0, 255);
            expect(() => adapter.drawCircleFilled(200, 200, 25)).not.toThrow();
        });

        it.skip('should draw circle outline (vtable 0xdc) (requires DOM)', () => {
            adapter.setColor(0, 0, 255, 255);
            expect(() => adapter.drawCircleOutline(300, 300, 30)).not.toThrow();
        });

        it.skip('should draw line (vtable 0xe0) (requires DOM)', () => {
            adapter.setColor(255, 255, 0, 255);
            expect(() => adapter.drawLine(0, 0, 100, 100, 2)).not.toThrow();
        });

        it.skip('should draw quad (vtable 0x11c) (requires DOM)', () => {
            adapter.setColor(255, 255, 255, 255);
            expect(() => adapter.drawQuad(50, 50, 100, 100)).not.toThrow();
        });
    });

    describe('Frame Management', () => {
        // Skip - requires init

        it.skip('should begin frame and clear (requires DOM)', () => {
            expect(() => adapter.beginFrame()).not.toThrow();
        });

        it.skip('should handle frame lifecycle (requires DOM)', () => {
            // beginFrame should work without errors
            expect(() => adapter.beginFrame()).not.toThrow();
            // Note: endFrame calls renderer.render which may not be fully initialized in test env
        });

        it.skip('should clear graphics and sprites (requires DOM)', () => {
            adapter.beginFrame();
            adapter.setColor(255, 0, 0, 255);
            adapter.drawCircleFilled(100, 100, 50);

            expect(() => adapter.clear()).not.toThrow();
        });
    });

    describe('Screen Info', () => {
        it('should return correct width', () => {
            expect(adapter.getWidth()).toBe(800);
        });

        it('should return correct height', () => {
            expect(adapter.getHeight()).toBe(600);
        });
    });

    describe('Rotation Matrix Behavior', () => {
        // Skip - requires init

        it.skip('should handle zero rotation (requires DOM)', () => {
            adapter.setRotation(0);
            adapter.beginFrame();
            adapter.setColor(255, 255, 255, 255);
            expect(() => adapter.drawQuad(100, 100, 50, 50)).not.toThrow();
            // Note: C code uses rotation=0 to skip matrix math (line 5308)
        });

        it.skip('should handle 90 degree rotation (requires DOM)', () => {
            adapter.setRotation(Math.PI / 2);
            adapter.beginFrame();
            adapter.setColor(255, 255, 255, 255);
            expect(() => adapter.drawQuad(100, 100, 50, 50)).not.toThrow();
            // Pixi handles rotation via sprite.rotation property
        });

        it.skip('should handle 45 degree rotation (requires DOM)', () => {
            // C code (line 4717): adds +45° for rotation matrix (cos/sin precompute)
            // C code (line 5318-5334): uses fast inverse sqrt for vertex transform
            // TypeScript: Pixi.js handles this internally via sprite.rotation
            adapter.setRotation(Math.PI / 4);
            adapter.beginFrame();
            adapter.setColor(255, 255, 255, 255);
            expect(() => adapter.drawQuad(100, 100, 50, 50)).not.toThrow();
        });
    });
});
