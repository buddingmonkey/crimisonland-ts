/**
 * Smoke Test — Verify the game loads, starts, and renders
 */

import { test, expect } from '@playwright/test';
import { waitForGameLoaded, getGameState, startGame, isPlayerAlive, screenshotCanvas } from './helpers/game';

test.describe('Smoke Tests', () => {
    test.beforeEach(async ({ page }) => {
        await page.goto('/');
        await waitForGameLoaded(page);
    });

    test('game loads and reaches menu', async ({ page }) => {
        const state = await getGameState(page);
        expect(state).toBe('Menu');

        await screenshotCanvas(page, 'menu');
    });

    test('game starts and player spawns', async ({ page }) => {
        await startGame(page);

        const state = await getGameState(page);
        expect(state).toBe('Playing');

        const alive = await isPlayerAlive(page);
        expect(alive).toBe(true);

        await screenshotCanvas(page, 'game_started');
    });
});
