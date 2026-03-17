/**
 * Gameplay Tests — Verify player movement, aiming, and firing
 *
 * These tests use real keyboard and mouse events on the canvas
 * to simulate actual gameplay.
 */

import { test, expect } from '@playwright/test';
import {
    waitForGameLoaded,
    startGame,
    isPlayerAlive,
    moveMouseToCanvas,
    clickCanvas,
    screenshotCanvas,
} from './helpers/game';

test.describe('Gameplay', () => {
    test.beforeEach(async ({ page }) => {
        await page.goto('/');
        await waitForGameLoaded(page);
        await startGame(page);
    });

    test('player moves with WASD', async ({ page }) => {
        const canvas = page.locator('canvas');

        // Move right (D key) for a bit
        await canvas.dispatchEvent('focus');
        await page.keyboard.down('d');
        await page.waitForTimeout(500);
        await page.keyboard.up('d');

        // Move down (S key)
        await page.keyboard.down('s');
        await page.waitForTimeout(500);
        await page.keyboard.up('s');

        // Player should still be alive after moving
        const alive = await isPlayerAlive(page);
        expect(alive).toBe(true);

        await screenshotCanvas(page, 'after_movement');
    });

    test('player can aim and fire', async ({ page }) => {
        // Move mouse to the right side of the screen
        await moveMouseToCanvas(page, 600, 300);
        await page.waitForTimeout(200);

        // Fire by clicking
        await clickCanvas(page, 600, 300);
        await page.waitForTimeout(100);
        await clickCanvas(page, 600, 300);
        await page.waitForTimeout(100);

        const alive = await isPlayerAlive(page);
        expect(alive).toBe(true);

        await screenshotCanvas(page, 'after_firing');
    });

    test('game survives 3 seconds of play', async ({ page }) => {
        const canvas = page.locator('canvas');

        // Simulate 3 seconds of active gameplay:
        // Move around and shoot at the same time
        await moveMouseToCanvas(page, 600, 200);

        // Hold W + D (move up-right) while clicking to fire
        await page.keyboard.down('w');
        await page.keyboard.down('d');
        await page.mouse.down();

        await page.waitForTimeout(3000);

        await page.mouse.up();
        await page.keyboard.up('w');
        await page.keyboard.up('d');

        // Take a screenshot of the action
        await screenshotCanvas(page, 'after_3s_gameplay');

        // Player may or may not be alive depending on enemy spawns,
        // but the game should not have crashed
        const state = await page.evaluate(() => {
            const crimson = (window as any).__CRIMSON__;
            const s = crimson.game.getState();
            return crimson.GameState[s];
        });

        // Game should be in a valid state (Playing, GameOver, or PerkSelection)
        expect(['Playing', 'GameOver', 'PerkSelection']).toContain(state);
    });
});
