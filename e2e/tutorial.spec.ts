/**
 * Tutorial E2E Test — Verify tutorial matches C code behavior
 *
 * Key checks:
 * - Tutorial launches without showing "PICK A PERK" screen
 * - Player health stays at 100 during tutorial
 * - XP stays at 0 (except stage 6)
 * - Tutorial text box renders
 * - Stages advance correctly
 */

import { test, expect } from '@playwright/test';
import {
    waitForGameLoaded,
    getGameState,
    getPlayerHealth,
    getScore,
    runCommand,
    screenshotCanvas,
} from './helpers/game';

// Helper: get tutorial-specific state via bridge
async function getTutorialState(page: import('@playwright/test').Page) {
    return page.evaluate(() => {
        const g = (window as any).__CRIMSON__.game;
        return {
            gameMode: g.getGameMode(),
            tutorialActive: g.isTutorialActive(),
            tutorialStage: g.getTutorialStage(),
        };
    });
}

test.describe('Tutorial System', () => {
    test.beforeEach(async ({ page }) => {
        await page.goto('/');
        await waitForGameLoaded(page);
    });

    test('tutorial launches without perk screen', async ({ page }) => {
        // Start tutorial via console command
        await runCommand(page, 'start_tutorial');
        await page.waitForTimeout(500);

        // Should be in Playing state, NOT PerkSelection
        const state = await getGameState(page);
        expect(state).toBe('Playing');

        // Game mode should be Tutorial
        const tut = await getTutorialState(page);
        expect(tut.gameMode).toBe('Tutorial');
        expect(tut.tutorialActive).toBe(true);

        await screenshotCanvas(page, 'tutorial_launched');
    });

    test('player health stays at 100 during tutorial', async ({ page }) => {
        await runCommand(page, 'start_tutorial');
        await page.waitForTimeout(500);

        // Wait a few frames to let the health reset logic run
        await page.waitForTimeout(1000);

        const health = await getPlayerHealth(page);
        expect(health).toBe(100);
    });

    test('XP stays at 0 during tutorial (not stage 6)', async ({ page }) => {
        await runCommand(page, 'start_tutorial');
        await page.waitForTimeout(500);

        // Manually add some XP — it should be reset to 0 next frame
        await runCommand(page, 'sv_score_addexp 500');
        await page.waitForTimeout(300);

        const xp = await getScore(page);
        expect(xp).toBe(0);
    });

    test('tutorial stage advances after intro timer', async ({ page }) => {
        await runCommand(page, 'start_tutorial');
        await page.waitForTimeout(500);

        // Initial stage should be Intro (0) after the fade-in from Inactive (-1)
        // The fade-in takes ~1 second (transitionTimer from -1000 to -1)
        await page.waitForTimeout(1500);

        const tut1 = await getTutorialState(page);
        expect(tut1.tutorialStage).toBe(0); // Intro

        // Intro auto-advances after 6 seconds
        await page.waitForTimeout(7000);

        const tut2 = await getTutorialState(page);
        expect(tut2.tutorialStage).toBeGreaterThan(0); // Should have advanced
    });

    test('no perk screen appears after waiting', async ({ page }) => {
        await runCommand(page, 'start_tutorial');

        // Wait 10 seconds — in the old code, perk screen appeared almost immediately
        await page.waitForTimeout(10000);

        // Should still be Playing, not PerkSelection
        const state = await getGameState(page);
        expect(state).toBe('Playing');

        // Should still be in tutorial mode
        const tut = await getTutorialState(page);
        expect(tut.gameMode).toBe('Tutorial');

        await screenshotCanvas(page, 'tutorial_no_perk_after_wait');
    });
});
