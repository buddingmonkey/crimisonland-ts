/**
 * E2E Test Helpers — Reusable Playwright utilities for game interaction
 *
 * Two interaction modes:
 *   1. Bridge (fast):  page.evaluate() → window.__CRIMSON__
 *   2. Keyboard (visual): press keys on the page like a real player
 *
 * Use the bridge for state setup and assertions.
 * Use keyboard/mouse for gameplay simulation.
 */

import { type Page, expect } from '@playwright/test';

// ============================================
// Waiting & Loading
// ============================================

/**
 * Wait until the game has loaded and a canvas is present.
 */
export async function waitForGameLoaded(page: Page): Promise<void> {
    // Wait for the canvas element that Pixi.js creates
    await page.waitForSelector('canvas', { timeout: 15_000 });

    // Wait for the game bridge to be available
    await page.waitForFunction(() => (window as any).__CRIMSON__?.game !== undefined, { timeout: 15_000 });

    // Give the game a moment to finish init (asset loading, etc.)
    await page.waitForTimeout(1000);
}

/**
 * Wait until the game reaches a specific state.
 */
export async function waitForState(page: Page, stateName: string, timeout = 10_000): Promise<void> {
    await page.waitForFunction(
        (expected) => {
            const crimson = (window as any).__CRIMSON__;
            if (!crimson?.game) return false;
            const stateEnum = crimson.GameState;
            const currentState = crimson.game.getState();
            return stateEnum?.[currentState] === expected;
        },
        stateName,
        { timeout },
    );
}

// ============================================
// Console Interaction
// ============================================

/**
 * Execute a console command via the bridge (fast, no keyboard).
 */
export async function runCommand(page: Page, command: string): Promise<void> {
    await page.evaluate((cmd) => {
        (window as any).__CRIMSON__.console.execute(cmd);
    }, command);
}

/**
 * Execute a console command by typing it visually (tests the console UI).
 * Opens console → types → presses Enter → closes console.
 */
export async function typeConsoleCommand(page: Page, command: string): Promise<void> {
    const canvas = page.locator('canvas');

    // Open console with backtick
    await canvas.press('Backquote');
    await page.waitForTimeout(100);

    // Type the command character by character
    for (const char of command) {
        await canvas.press(char);
        await page.waitForTimeout(20);
    }

    // Submit
    await canvas.press('Enter');
    await page.waitForTimeout(100);

    // Close console
    await canvas.press('Backquote');
    await page.waitForTimeout(100);
}

// ============================================
// Game State Queries (via bridge)
// ============================================

/**
 * Get the current GameState name (e.g. "Menu", "Playing", "Loading").
 */
export async function getGameState(page: Page): Promise<string> {
    return page.evaluate(() => {
        const crimson = (window as any).__CRIMSON__;
        const state = crimson.game.getState();
        return crimson.GameState[state] ?? 'Unknown';
    });
}

/**
 * Get the player's current health, or null if no player.
 */
export async function getPlayerHealth(page: Page): Promise<number | null> {
    return page.evaluate(() => {
        const player = (window as any).__CRIMSON__.game.getPlayer();
        return player ? player.health : null;
    });
}

/**
 * Check if the player is alive.
 */
export async function isPlayerAlive(page: Page): Promise<boolean> {
    return page.evaluate(() => {
        const player = (window as any).__CRIMSON__.game.getPlayer();
        return player ? player.isAlive() : false;
    });
}

/**
 * Get the number of active enemies.
 */
export async function getEnemyCount(page: Page): Promise<number> {
    return page.evaluate(() => {
        return (window as any).__CRIMSON__.game.getEnemySpawner().getActiveEnemies().length;
    });
}

/**
 * Get the current score/XP.
 */
export async function getScore(page: Page): Promise<number> {
    return page.evaluate(() => {
        return (window as any).__CRIMSON__.game.getScoreSystem().getExperience();
    });
}

/**
 * Read the last N console log entries.
 */
export async function getConsoleLogs(page: Page, count = 10): Promise<string[]> {
    return page.evaluate((n) => {
        const log = (window as any).__CRIMSON__.console.getRecentLog(n);
        return log.map((entry: any) => entry.text);
    }, count);
}

// ============================================
// Game Actions
// ============================================

/**
 * Start the game and ensure we land in Playing state.
 *
 * The game's `start` command triggers an immediate level-up (level 0→1),
 * which shows PerkSelection. We dismiss it with Escape to reach Playing.
 */
export async function startGame(page: Page): Promise<void> {
    await runCommand(page, 'start');

    // Wait a moment for the game loop to process
    await page.waitForTimeout(300);

    // Check if we're in PerkSelection and dismiss it
    const maxAttempts = 5;
    for (let i = 0; i < maxAttempts; i++) {
        const state = await getGameState(page);
        if (state === 'Playing') break;

        if (state === 'PerkSelection') {
            // Press Escape to cancel perk selection and return to Playing
            await page.keyboard.press('Escape');
            await page.waitForTimeout(200);
        }
    }

    // Final verification
    const finalState = await getGameState(page);
    if (finalState !== 'Playing') {
        throw new Error(`Expected Playing state after start, got ${finalState}`);
    }
}

/**
 * Start the game in test environment mode (no enemy spawning).
 *
 * Uses the `test_env_start` command which starts the game, disables
 * enemy spawning, and clears any enemies — creating a clean sandbox
 * for dummy targets and controlled testing.
 */
export async function startTestEnv(page: Page): Promise<void> {
    await runCommand(page, 'test_env_start');

    // Wait a moment for the game loop to process
    await page.waitForTimeout(300);

    // Handle PerkSelection (same as startGame)
    const maxAttempts = 5;
    for (let i = 0; i < maxAttempts; i++) {
        const state = await getGameState(page);
        if (state === 'Playing') break;

        if (state === 'PerkSelection') {
            await page.keyboard.press('Escape');
            await page.waitForTimeout(200);
        }
    }

    // Final verification
    const finalState = await getGameState(page);
    if (finalState !== 'Playing') {
        throw new Error(`Expected Playing state after test_env_start, got ${finalState}`);
    }
}

// ============================================
// Input Simulation
// ============================================

/**
 * Hold a key down for a specified duration.
 */
export async function holdKey(page: Page, key: string, durationMs: number): Promise<void> {
    const canvas = page.locator('canvas');
    await canvas.press(key, { delay: durationMs });
}

/**
 * Move the mouse to a position on the canvas.
 */
export async function moveMouseToCanvas(page: Page, x: number, y: number): Promise<void> {
    const canvas = page.locator('canvas');
    const box = await canvas.boundingBox();
    if (!box) throw new Error('Canvas not found');
    await page.mouse.move(box.x + x, box.y + y);
}

/**
 * Click at a position on the canvas.
 */
export async function clickCanvas(page: Page, x: number, y: number): Promise<void> {
    const canvas = page.locator('canvas');
    const box = await canvas.boundingBox();
    if (!box) throw new Error('Canvas not found');
    await page.mouse.click(box.x + x, box.y + y);
}

// ============================================
// Screenshots
// ============================================

/**
 * Take a screenshot of just the canvas element.
 */
export async function screenshotCanvas(page: Page, name: string): Promise<Buffer> {
    const canvas = page.locator('canvas');
    const buffer = await canvas.screenshot({ path: `e2e/screenshots/${name}.png` });
    return buffer;
}
