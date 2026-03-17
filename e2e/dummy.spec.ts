/**
 * Dummy Enemy Tests — Verify the stationary test target system
 *
 * Uses test_env_start (no enemy spawning) so the player is safe
 * and we can reliably spawn dummies and test hits.
 */

import { test, expect } from '@playwright/test';
import {
    waitForGameLoaded,
    startTestEnv,
    runCommand,
    moveMouseToCanvas,
    screenshotCanvas,
    getConsoleLogs,
} from './helpers/game';

// ============================================
// Dummy-specific helpers
// ============================================

interface HitRecord {
    damage: number;
    damageType: number;
    impulseX: number;
    impulseY: number;
    positionX: number;
    positionY: number;
    collisionAngle: number;
    impulseMagnitude: number;
    timestamp: number;
    statusEffects: string[];
    healthAfter: number;
}

/** Get all dummy enemies via bridge */
async function getDummies(page: import('@playwright/test').Page) {
    return page.evaluate(() => {
        const spawner = (window as any).__CRIMSON__.game.getEnemySpawner();
        const dummies = spawner.getDummies();
        return dummies.map((d: any) => ({
            label: d.label,
            x: d.x,
            y: d.y,
            health: d.health,
            hitCount: d.getHitCount(),
            totalDamage: d.getTotalDamage(),
            lastHit: d.getLastHit(),
            hitLog: d.getHitLog(),
        }));
    });
}

// ============================================
// Tests
// ============================================

test.describe('Dummy Enemy', () => {
    test.beforeEach(async ({ page }) => {
        await page.goto('/');
        await waitForGameLoaded(page);
        await startTestEnv(page); // No enemies spawn
    });

    test('spawn_dummy creates a dummy at position', async ({ page }) => {
        await runCommand(page, 'spawn_dummy 400 300 center');

        const dummies = await getDummies(page);
        expect(dummies).toHaveLength(1);
        expect(dummies[0].label).toBe('center');
        expect(dummies[0].x).toBe(400);
        expect(dummies[0].y).toBe(300);
        expect(dummies[0].hitCount).toBe(0);

        await screenshotCanvas(page, 'dummy_spawned');
    });

    test('dummy records hits when shot', async ({ page }) => {
        // Spawn dummy close to player (player starts at 400,300)
        await runCommand(page, 'spawn_dummy 500 300 target');
        await page.waitForTimeout(300);

        // Move mouse towards the dummy and hold fire
        await moveMouseToCanvas(page, 500, 300);
        await page.waitForTimeout(200);
        await page.mouse.down();
        await page.waitForTimeout(3000);
        await page.mouse.up();
        await page.waitForTimeout(500);

        const dummies = await getDummies(page);
        expect(dummies).toHaveLength(1);
        expect(dummies[0].hitCount).toBeGreaterThan(0);
        expect(dummies[0].totalDamage).toBeGreaterThan(0);

        // Check last hit has valid data
        const lastHit = dummies[0].lastHit as HitRecord;
        expect(lastHit).not.toBeNull();
        expect(lastHit.damage).toBeGreaterThan(0);
        expect(lastHit.damageType).toBe(1); // bullet

        await screenshotCanvas(page, 'dummy_after_hits');
    });

    test('dummy survives multiple hits', async ({ page }) => {
        await runCommand(page, 'spawn_dummy 500 300');
        await page.waitForTimeout(300);

        // Aim and hold fire
        await moveMouseToCanvas(page, 500, 300);
        await page.waitForTimeout(200);
        await page.mouse.down();
        await page.waitForTimeout(3000);
        await page.mouse.up();
        await page.waitForTimeout(500);

        // Dummy should still be alive with recorded hits
        const dummies = await getDummies(page);
        expect(dummies).toHaveLength(1);
        expect(dummies[0].hitCount).toBeGreaterThan(0);

        await screenshotCanvas(page, 'dummy_survived');
    });

    test('dummy_reset clears hit log', async ({ page }) => {
        await runCommand(page, 'spawn_dummy 500 300');

        // Fire at dummy
        await moveMouseToCanvas(page, 500, 300);
        await page.waitForTimeout(200);
        await page.mouse.down();
        await page.waitForTimeout(2000);
        await page.mouse.up();
        await page.waitForTimeout(500);

        // Reset
        await runCommand(page, 'dummy_reset');

        const dummies = await getDummies(page);
        expect(dummies).toHaveLength(1);
        expect(dummies[0].hitCount).toBe(0);
        expect(dummies[0].totalDamage).toBe(0);
    });

    test('dummy_clear removes dummies', async ({ page }) => {
        await runCommand(page, 'spawn_dummy 200 200');
        await runCommand(page, 'spawn_dummy 600 400');

        let dummies = await getDummies(page);
        expect(dummies).toHaveLength(2);

        await runCommand(page, 'dummy_clear');

        dummies = await getDummies(page);
        expect(dummies).toHaveLength(0);
    });

    test('dummy_report outputs hit data to console', async ({ page }) => {
        await runCommand(page, 'spawn_dummy 500 300 test_target');

        // Fire at it
        await moveMouseToCanvas(page, 500, 300);
        await page.waitForTimeout(200);
        await page.mouse.down();
        await page.waitForTimeout(2000);
        await page.mouse.up();
        await page.waitForTimeout(500);

        await runCommand(page, 'dummy_report');

        const logs = await getConsoleLogs(page, 10);
        const hasReport = logs.some((line) => line.includes('test_target'));
        expect(hasReport).toBe(true);
    });
});
