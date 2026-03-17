/**
 * Console Tests — Verify console commands work through the game bridge
 */

import { test, expect } from '@playwright/test';
import {
    waitForGameLoaded,
    startGame,
    runCommand,
    getPlayerHealth,
    isPlayerAlive,
    getScore,
    getConsoleLogs,
    screenshotCanvas,
} from './helpers/game';

test.describe('Console Commands', () => {
    test.beforeEach(async ({ page }) => {
        await page.goto('/');
        await waitForGameLoaded(page);
    });

    test('help command prints output', async ({ page }) => {
        await runCommand(page, 'help');
        const logs = await getConsoleLogs(page, 10);
        const hasHelp = logs.some((line) => line.includes('Available commands'));
        expect(hasHelp).toBe(true);
    });

    test('set and read cvars', async ({ page }) => {
        await runCommand(page, 'set test_var 42');
        const logs = await getConsoleLogs(page, 5);
        const hasSet = logs.some((line) => line.includes('"test_var" set to "42"'));
        expect(hasSet).toBe(true);
    });

    test('start command transitions to Playing', async ({ page }) => {
        await startGame(page);
        const logs = await getConsoleLogs(page, 10);
        // startGame() runs 'start' which prints "Player spawned", then may
        // dismiss PerkSelection which prints "Perk selection cancelled."
        const hasStarted = logs.some((line) => line.includes('Player spawned') || line.includes('Game started'));
        expect(hasStarted).toBe(true);
    });

    test('player_damage reduces health', async ({ page }) => {
        await startGame(page);

        const healthBefore = await getPlayerHealth(page);
        expect(healthBefore).not.toBeNull();

        await runCommand(page, 'player_damage 50');

        const healthAfter = await getPlayerHealth(page);
        expect(healthAfter).not.toBeNull();
        expect(healthAfter!).toBeLessThan(healthBefore!);
    });

    test('player_heal restores health', async ({ page }) => {
        await startGame(page);
        await runCommand(page, 'player_damage 50');

        const healthDamaged = await getPlayerHealth(page);
        await runCommand(page, 'player_heal 50');

        const healthHealed = await getPlayerHealth(page);
        expect(healthHealed!).toBeGreaterThan(healthDamaged!);
    });

    test('sv_score_addexp increases score', async ({ page }) => {
        await startGame(page);

        const scoreBefore = await getScore(page);
        await runCommand(page, 'sv_score_addexp 1000');

        const scoreAfter = await getScore(page);
        expect(scoreAfter).toBeGreaterThan(scoreBefore);
    });
});
