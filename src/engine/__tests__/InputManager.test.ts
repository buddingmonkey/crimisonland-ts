/**
 * InputManager unit tests
 */

import { describe, it, expect, beforeEach } from 'vitest';
import { InputManager } from '../InputManager';

describe('InputManager', () => {
    let input: InputManager;

    beforeEach(() => {
        input = new InputManager();
    });

    describe('keyboard state', () => {
        it('should initially have no keys down', () => {
            expect(input.isKeyDown(65)).toBe(false);
        });

        it('should track key state after flush', () => {
            // After flush, all keys should be up
            input.flush();
            expect(input.isKeyDown(65)).toBe(false);
            expect(input.isKeyPressed(65)).toBe(false);
        });
    });

    describe('mouse state', () => {
        it('should initially have zero position', () => {
            expect(input.getMouseX()).toBe(0);
            expect(input.getMouseY()).toBe(0);
        });

        it('should allow setting mouse position', () => {
            input.setMousePosition(100, 200);
            expect(input.getMouseX()).toBe(100);
            expect(input.getMouseY()).toBe(200);
        });

        it('should initially have no buttons down', () => {
            expect(input.isMouseButtonDown(0)).toBe(false);
            expect(input.isMouseButtonDown(1)).toBe(false);
            expect(input.isMouseButtonDown(2)).toBe(false);
        });

        it('should have zero delta initially', () => {
            expect(input.getMouseDeltaX()).toBe(0);
            expect(input.getMouseDeltaY()).toBe(0);
        });
    });

    describe('flush', () => {
        it('should clear all state', () => {
            input.setMousePosition(100, 200);
            input.flush();

            // Position is not cleared by flush, only button/key states
            expect(input.isMouseButtonDown(0)).toBe(false);
            expect(input.isKeyDown(65)).toBe(false);
        });
    });

    describe('update', () => {
        it('should clear per-frame state', () => {
            input.update();

            // After update, delta should reflect movement
            expect(input.getMouseDeltaX()).toBe(0);
            expect(input.getMouseDeltaY()).toBe(0);
        });

        it('should calculate delta between updates', () => {
            input.setMousePosition(0, 0);
            input.update(); // First update establishes baseline

            input.setMousePosition(50, 30);
            input.update(); // Second update calculates delta

            expect(input.getMouseDeltaX()).toBe(50);
            expect(input.getMouseDeltaY()).toBe(30);
        });
    });

    describe('getKeyChars', () => {
        it('should return empty array when no key pressed', () => {
            expect(input.getKeyChars()).toEqual([]);
        });
    });
});
