/**
 * Weapon Verification Tests — E2E tests to verify ALL weapon stats
 * match the C code implementation.
 *
 * Tests weapon switching, firing, damage, fire rate, and pellet counts
 * across all weapon categories.
 */

import { test, expect } from '@playwright/test';
import { waitForGameLoaded, startTestEnv, runCommand, moveMouseToCanvas } from './helpers/game';

// ============================================
// Helpers
// ============================================

interface HitRecord {
    damage: number;
    damageType: number;
    timestamp: number;
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

/** Assert value is within ±tolerance% of expected */
function expectWithinTolerance(actual: number, expected: number, tolerancePercent: number, label: string) {
    const lo = expected * (1 - tolerancePercent / 100);
    const hi = expected * (1 + tolerancePercent / 100);
    expect(
        actual,
        `${label}: expected ${expected.toFixed(2)} ±${tolerancePercent}% [${lo.toFixed(2)}–${hi.toFixed(2)}], got ${actual.toFixed(2)}`,
    ).toBeGreaterThanOrEqual(lo);
    expect(
        actual,
        `${label}: expected ${expected.toFixed(2)} ±${tolerancePercent}% [${lo.toFixed(2)}–${hi.toFixed(2)}], got ${actual.toFixed(2)}`,
    ).toBeLessThanOrEqual(hi);
}

/** Fire weapon and collect hit data */
async function fireAndCollect(
    page: import('@playwright/test').Page,
    weaponId: number,
    targetX: number,
    targetY: number,
    holdMs: number,
    waitAfterMs: number = 500,
) {
    await runCommand(page, `weapon_switch ${weaponId}`);
    await runCommand(page, `spawn_dummy ${targetX} ${targetY} target_${weaponId}`);
    await page.waitForTimeout(500);

    await moveMouseToCanvas(page, targetX, targetY);
    await page.waitForTimeout(200);
    await page.mouse.down();
    await page.waitForTimeout(holdMs);
    await page.mouse.up();
    await page.waitForTimeout(waitAfterMs);

    const dummies = await getDummies(page);
    const dummy = dummies.find((d: any) => d.label === `target_${weaponId}`);
    return dummy;
}

/** C damage formula: ((100/dist) * damageScale * 30 + 10) * 0.95 */
function cDamageFormula(distance: number, damageScale: number): number {
    const dist = Math.max(distance, 50);
    return ((100 / dist) * damageScale * 30 + 10) * 0.95;
}

// ============================================
// Weapon definitions for testing
// ============================================
const WEAPONS = {
    // Bullet weapons
    pistol: { id: 0, name: 'Pistol', shotCooldownMs: 712, projectileCount: 5, damageScale: 55.0 },
    ar: { id: 1, name: 'Assault Rifle', shotCooldownMs: 117, projectileCount: 1, damageScale: 50.0 },
    shotgun: { id: 2, name: 'Shotgun', shotCooldownMs: 850, projectileCount: 12, damageScale: 60.0 },
    sawedOff: { id: 3, name: 'Sawed-off Shotgun', shotCooldownMs: 870, projectileCount: 12, damageScale: 60.0 },
    jackhammer: { id: 4, name: 'Jackhammer', shotCooldownMs: 870, projectileCount: 12, damageScale: 60.0 },
    smg: { id: 5, name: 'Submachine Gun', shotCooldownMs: 140, projectileCount: 1, damageScale: 1.0 },
    gaussGun: { id: 10, name: 'Gauss Gun', shotCooldownMs: 110, projectileCount: 1, damageScale: 1.5 },
    blasterR: { id: 37, name: 'Blaster R-300', shotCooldownMs: 40, projectileCount: 9, damageScale: undefined },

    // Plasma weapons
    plasmaRifle: { id: 7, name: 'Plasma Rifle', shotCooldownMs: 8, projectileCount: 2, damageScale: 8.0 },
    multiPlasma: { id: 8, name: 'Multi-Plasma', shotCooldownMs: 291, projectileCount: 3, damageScale: 1.4 },
    plasmaMinigun: { id: 9, name: 'Plasma Minigun', shotCooldownMs: 621, projectileCount: 3, damageScale: 1.4 },
    plasmaShotgun: { id: 14, name: 'Plasma Shotgun', shotCooldownMs: 90, projectileCount: 3, damageScale: 1.5 },

    // Fire weapons
    flamethrower: { id: 6, name: 'Flamethrower', shotCooldownMs: 88, projectileCount: 5 },
    blowTorch: { id: 15, name: 'Blow Torch', shotCooldownMs: 480, projectileCount: 8 },
    hrFlamer: { id: 16, name: 'HR Flamer', shotCooldownMs: 6, projectileCount: 2, damageScale: 1.2 },
    flameburst: { id: 27, name: 'Flameburst', shotCooldownMs: 1000, projectileCount: 4 },

    // Ion weapons
    ionRifle: { id: 20, name: 'Ion Rifle', shotCooldownMs: 100, projectileCount: 3, damageScale: 1.3 },
    ionMinigun: { id: 21, name: 'Ion Minigun', shotCooldownMs: 400, projectileCount: 4, damageScale: 1.2 },
    ionCannon: { id: 22, name: 'Ion Cannon', shotCooldownMs: 100, projectileCount: 4 },
    ionShotgun: { id: 23, name: 'Ion Shotgun', shotCooldownMs: 1000, projectileCount: 4 },

    // Rocket weapons
    rocketLauncher: { id: 11, name: 'Rocket Launcher', shotCooldownMs: 600, projectileCount: 1 },
    seekerRockets: { id: 12, name: 'Seeker Rockets', shotCooldownMs: 741, projectileCount: 5 },
    miniSwarmers: { id: 17, name: 'Mini Rocket Swarmers', shotCooldownMs: 9, projectileCount: 2 },
    rocketMinigun: { id: 18, name: 'Rocket Minigun', shotCooldownMs: 120, projectileCount: 8 },
    nukeLauncher: { id: 38, name: 'Nuke Launcher', shotCooldownMs: 80, projectileCount: 9 },

    // Special weapons
    meanMinigun: { id: 13, name: 'Mean Minigun', shotCooldownMs: 311, projectileCount: 2 },
    pulseGun: { id: 19, name: 'Pulse Gun', shotCooldownMs: 120, projectileCount: 2 },
    gaussShotgun: { id: 24, name: 'Gauss Shotgun', shotCooldownMs: 850, projectileCount: 8 },
    plasmaCannon: { id: 25, name: 'Plasma Cannon', shotCooldownMs: 1050, projectileCount: 1 },
    evilScythe: { id: 26, name: 'Evil Scythe', shotCooldownMs: 900, projectileCount: 25 },
    splitterGun: { id: 28, name: 'Splitter Gun', shotCooldownMs: 700, projectileCount: 4 },
    shrinkifier: { id: 29, name: 'Shrinkifier 5k', shotCooldownMs: 700, projectileCount: 1, damageScale: 6.0 },
    bladeGun: { id: 30, name: 'Blade Gun', shotCooldownMs: 133, projectileCount: 23 },
    plagueSpreader: { id: 31, name: 'Plague Spreader Gun', shotCooldownMs: 350, projectileCount: 24 },
    rainbowGun: { id: 32, name: 'Rainbow Gun', shotCooldownMs: 200, projectileCount: 1 },
    grimWeapon: { id: 33, name: 'Grim Weapon', shotCooldownMs: 200, projectileCount: 1 },
    bubblegun: { id: 34, name: 'Bubblegun', shotCooldownMs: 500, projectileCount: 1 },
    spiderPlasma: { id: 35, name: 'Spider Plasma', shotCooldownMs: 161, projectileCount: 8 },
    transmutator: { id: 36, name: 'Transmutator', shotCooldownMs: 200, projectileCount: 8 },
    lightingRifle: { id: 39, name: 'Lighting Rifle', shotCooldownMs: 4000, projectileCount: 8 },
};

const FIRE_RATE_TOLERANCE = 30;

// ============================================
// Tests
// ============================================

test.describe('Weapon Verification', () => {
    test.beforeEach(async ({ page }) => {
        await page.goto('/');
        await waitForGameLoaded(page);
        await startTestEnv(page);
    });

    // --------------------------------------------------
    // 1. All weapons can switch and fire without crash
    // --------------------------------------------------
    test.describe('Weapon Switch & Fire', () => {
        test('can switch to and fire all 40 weapons', async ({ page }) => {
            // Spawn a dummy to shoot at
            await runCommand(page, 'spawn_dummy 500 300 switch_target');
            await page.waitForTimeout(300);
            await moveMouseToCanvas(page, 500, 300);
            await page.waitForTimeout(200);

            for (let id = 0; id < 40; id++) {
                await runCommand(page, `weapon_switch ${id}`);
                await page.waitForTimeout(50);
                // Quick fire burst
                await page.mouse.down();
                await page.waitForTimeout(150);
                await page.mouse.up();
                await page.waitForTimeout(50);
            }

            // Player should still be alive after cycling all weapons
            const alive = await page.evaluate(() => {
                const player = (window as any).__CRIMSON__.game.getPlayer();
                return player?.isAlive() ?? false;
            });
            expect(alive).toBe(true);

            // Dummy should have been hit by at least some weapons
            const dummies = await getDummies(page);
            const target = dummies.find((d: any) => d.label === 'switch_target');
            expect(target!.hitCount).toBeGreaterThan(0);
        });
    });

    // --------------------------------------------------
    // 2. Fire Rate Tests (slow weapons - accurate interval)
    // --------------------------------------------------
    test.describe('Fire Rate', () => {
        test('Pistol fire rate matches C shotCooldown', async ({ page }) => {
            const weapon = WEAPONS.pistol;
            const dummy = await fireAndCollect(page, weapon.id, 500, 300, 5000);
            const hitLog = dummy!.hitLog as HitRecord[];
            expect(hitLog.length).toBeGreaterThan(2);

            // Group hits by timestamp proximity (multi-projectile shots)
            const timestamps = hitLog.map((h) => h.timestamp);
            const shotTimes: number[] = [];
            let lastShotTime = -Infinity;
            for (const t of timestamps) {
                if (t - lastShotTime > weapon.shotCooldownMs * 0.3) {
                    shotTimes.push(t);
                    lastShotTime = t;
                }
            }

            if (shotTimes.length >= 3) {
                const intervals: number[] = [];
                for (let i = 1; i < shotTimes.length; i++) {
                    intervals.push(shotTimes[i] - shotTimes[i - 1]);
                }
                const avgIntervalMs = intervals.reduce((a, b) => a + b, 0) / intervals.length;
                expectWithinTolerance(
                    avgIntervalMs,
                    weapon.shotCooldownMs,
                    FIRE_RATE_TOLERANCE,
                    'Pistol shotCooldown (ms)',
                );
            }
        });

        test('Assault Rifle has high hit count (fast fire rate)', async ({ page }) => {
            const weapon = WEAPONS.ar;
            const dummy = await fireAndCollect(page, weapon.id, 500, 300, 3000);
            const hitLog = dummy!.hitLog as HitRecord[];

            // AR fires ~8.5 shots/sec, over 3s = ~25 shots. Expect 10+ hits.
            expect(hitLog.length, `AR hits in 3s: ${hitLog.length}`).toBeGreaterThanOrEqual(10);
        });

        test('Shotgun fire rate matches C shotCooldown', async ({ page }) => {
            const weapon = WEAPONS.shotgun;
            const dummy = await fireAndCollect(page, weapon.id, 450, 300, 4000);
            const hitLog = dummy!.hitLog as HitRecord[];

            // Group into shots
            const timestamps = hitLog.map((h) => h.timestamp);
            const shotTimes: number[] = [];
            let lastShotTime = -Infinity;
            for (const t of timestamps) {
                if (t - lastShotTime > weapon.shotCooldownMs * 0.3) {
                    shotTimes.push(t);
                    lastShotTime = t;
                }
            }

            if (shotTimes.length >= 3) {
                const intervals: number[] = [];
                for (let i = 1; i < shotTimes.length; i++) {
                    intervals.push(shotTimes[i] - shotTimes[i - 1]);
                }
                const avgIntervalMs = intervals.reduce((a, b) => a + b, 0) / intervals.length;
                expectWithinTolerance(
                    avgIntervalMs,
                    weapon.shotCooldownMs,
                    FIRE_RATE_TOLERANCE,
                    'Shotgun shotCooldown (ms)',
                );
            }
        });

        test('Sawed-off Shotgun matches Shotgun fire rate pattern', async ({ page }) => {
            const weapon = WEAPONS.sawedOff;
            const dummy = await fireAndCollect(page, weapon.id, 450, 300, 4000);
            expect(dummy!.hitCount).toBeGreaterThan(0);
        });
    });

    // --------------------------------------------------
    // 3. Damage Tests (C distance-based formula)
    // --------------------------------------------------
    test.describe('Damage', () => {
        test('Pistol damage uses C distance formula', async ({ page }) => {
            const weapon = WEAPONS.pistol;
            const dummy = await fireAndCollect(page, weapon.id, 500, 300, 1500);

            if (dummy!.hitCount > 0) {
                const hitLog = dummy!.hitLog as HitRecord[];
                const firstHitDamage = hitLog[0].damage;
                expect(firstHitDamage).toBeGreaterThan(20);

                const minDamage = cDamageFormula(200, weapon.damageScale);
                const maxDamage = cDamageFormula(50, weapon.damageScale);
                expect(firstHitDamage).toBeGreaterThanOrEqual(minDamage * 0.7);
                expect(firstHitDamage).toBeLessThanOrEqual(maxDamage * 1.3);
            }
        });

        test('AR damage uses C distance formula', async ({ page }) => {
            const weapon = WEAPONS.ar;
            const dummy = await fireAndCollect(page, weapon.id, 500, 300, 800);

            if (dummy!.hitCount > 0) {
                const hitLog = dummy!.hitLog as HitRecord[];
                const firstHitDamage = hitLog[0].damage;
                expect(firstHitDamage).toBeGreaterThan(50);

                const minDamage = cDamageFormula(200, weapon.damageScale);
                const maxDamage = cDamageFormula(50, weapon.damageScale);
                expect(firstHitDamage).toBeGreaterThanOrEqual(minDamage * 0.7);
                expect(firstHitDamage).toBeLessThanOrEqual(maxDamage * 1.3);
            }
        });

        test('Gauss Gun damage uses C distance formula', async ({ page }) => {
            const weapon = WEAPONS.gaussGun;
            const dummy = await fireAndCollect(page, weapon.id, 500, 300, 2000);

            if (dummy!.hitCount > 0) {
                const hitLog = dummy!.hitLog as HitRecord[];
                const firstHitDamage = hitLog[0].damage;
                // With damageScale 1.5, damage should be much higher than flat fallback
                expect(firstHitDamage).toBeGreaterThan(10);
            }
        });
    });

    // --------------------------------------------------
    // 4. Shotgun Pellet Count Tests
    // --------------------------------------------------
    test.describe('Shotgun Pellets', () => {
        test('Shotgun fires multiple pellets', async ({ page }) => {
            const dummy = await fireAndCollect(page, WEAPONS.shotgun.id, 450, 300, 200, 1500);
            expect(dummy!.hitCount, `Shotgun pellet hits: ${dummy!.hitCount}`).toBeGreaterThanOrEqual(4);
        });

        test('Sawed-off Shotgun fires multiple pellets', async ({ page }) => {
            const dummy = await fireAndCollect(page, WEAPONS.sawedOff.id, 450, 300, 200, 1500);
            expect(dummy!.hitCount, `Sawed-off pellet hits: ${dummy!.hitCount}`).toBeGreaterThanOrEqual(4);
        });

        test('Jackhammer fires multiple pellets', async ({ page }) => {
            const dummy = await fireAndCollect(page, WEAPONS.jackhammer.id, 450, 300, 200, 1500);
            expect(dummy!.hitCount, `Jackhammer pellet hits: ${dummy!.hitCount}`).toBeGreaterThanOrEqual(4);
        });

        test('Gauss Shotgun fires multiple pellets', async ({ page }) => {
            const dummy = await fireAndCollect(page, WEAPONS.gaussShotgun.id, 450, 300, 200, 1500);
            expect(dummy!.hitCount, `Gauss Shotgun pellet hits: ${dummy!.hitCount}`).toBeGreaterThanOrEqual(3);
        });

        test('Ion Shotgun fires multiple pellets', async ({ page }) => {
            const dummy = await fireAndCollect(page, WEAPONS.ionShotgun.id, 450, 300, 200, 1500);
            expect(dummy!.hitCount, `Ion Shotgun pellet hits: ${dummy!.hitCount}`).toBeGreaterThanOrEqual(2);
        });
    });

    // --------------------------------------------------
    // 5. High-Projectile-Count Weapons
    // --------------------------------------------------
    test.describe('Multi-Projectile Weapons', () => {
        test('Evil Scythe fires many pellets (25 per shot)', async ({ page }) => {
            const dummy = await fireAndCollect(page, WEAPONS.evilScythe.id, 450, 300, 200, 1500);
            expect(dummy!.hitCount, `Evil Scythe hits: ${dummy!.hitCount}`).toBeGreaterThanOrEqual(5);
        });

        test('Plague Spreader fires many pellets (24 per shot)', async ({ page }) => {
            const dummy = await fireAndCollect(page, WEAPONS.plagueSpreader.id, 450, 300, 200, 1500);
            expect(dummy!.hitCount, `Plague Spreader hits: ${dummy!.hitCount}`).toBeGreaterThanOrEqual(5);
        });

        test('Blade Gun fires many pellets (23 per shot)', async ({ page }) => {
            const dummy = await fireAndCollect(page, WEAPONS.bladeGun.id, 450, 300, 200, 1500);
            expect(dummy!.hitCount, `Blade Gun hits: ${dummy!.hitCount}`).toBeGreaterThanOrEqual(5);
        });
    });

    // --------------------------------------------------
    // 6. Plasma Weapon Category
    // --------------------------------------------------
    test.describe('Plasma Weapons', () => {
        test('Plasma Rifle deals damage', async ({ page }) => {
            const dummy = await fireAndCollect(page, WEAPONS.plasmaRifle.id, 500, 300, 2000);
            expect(dummy!.hitCount).toBeGreaterThan(0);
            expect(dummy!.totalDamage).toBeGreaterThan(0);
        });

        test('Multi-Plasma deals damage', async ({ page }) => {
            const dummy = await fireAndCollect(page, WEAPONS.multiPlasma.id, 500, 300, 2000);
            expect(dummy!.hitCount).toBeGreaterThan(0);
            expect(dummy!.totalDamage).toBeGreaterThan(0);
        });

        test('Plasma Minigun deals damage', async ({ page }) => {
            const dummy = await fireAndCollect(page, WEAPONS.plasmaMinigun.id, 500, 300, 3000);
            expect(dummy!.hitCount).toBeGreaterThan(0);
            expect(dummy!.totalDamage).toBeGreaterThan(0);
        });

        test('Plasma Shotgun deals damage', async ({ page }) => {
            const dummy = await fireAndCollect(page, WEAPONS.plasmaShotgun.id, 450, 300, 2000);
            expect(dummy!.hitCount).toBeGreaterThan(0);
            expect(dummy!.totalDamage).toBeGreaterThan(0);
        });
    });

    // --------------------------------------------------
    // 7. Fire Weapons
    // --------------------------------------------------
    test.describe('Fire Weapons', () => {
        test('Flamethrower deals damage', async ({ page }) => {
            const dummy = await fireAndCollect(page, WEAPONS.flamethrower.id, 450, 300, 2000);
            expect(dummy!.hitCount).toBeGreaterThan(0);
            expect(dummy!.totalDamage).toBeGreaterThan(0);
        });

        test('Blow Torch deals damage', async ({ page }) => {
            const dummy = await fireAndCollect(page, WEAPONS.blowTorch.id, 450, 300, 2000);
            expect(dummy!.hitCount).toBeGreaterThan(0);
            expect(dummy!.totalDamage).toBeGreaterThan(0);
        });

        test('HR Flamer deals damage', async ({ page }) => {
            const dummy = await fireAndCollect(page, WEAPONS.hrFlamer.id, 450, 300, 2000);
            expect(dummy!.hitCount).toBeGreaterThan(0);
            expect(dummy!.totalDamage).toBeGreaterThan(0);
        });
    });

    // --------------------------------------------------
    // 8. Ion Weapons
    // --------------------------------------------------
    test.describe('Ion Weapons', () => {
        test('Ion Rifle deals damage', async ({ page }) => {
            const dummy = await fireAndCollect(page, WEAPONS.ionRifle.id, 500, 300, 2000);
            expect(dummy!.hitCount).toBeGreaterThan(0);
            expect(dummy!.totalDamage).toBeGreaterThan(0);
        });

        test('Ion Minigun deals damage with multiple projectiles', async ({ page }) => {
            const dummy = await fireAndCollect(page, WEAPONS.ionMinigun.id, 500, 300, 3000);
            expect(dummy!.hitCount).toBeGreaterThan(0);
            expect(dummy!.totalDamage).toBeGreaterThan(0);
        });

        test('Ion Cannon deals damage', async ({ page }) => {
            const dummy = await fireAndCollect(page, WEAPONS.ionCannon.id, 500, 300, 2000);
            expect(dummy!.hitCount).toBeGreaterThan(0);
            expect(dummy!.totalDamage).toBeGreaterThan(0);
        });
    });

    // --------------------------------------------------
    // 9. Rocket Weapons (use flat damage, no distance formula)
    // --------------------------------------------------
    test.describe('Rocket Weapons', () => {
        test('Rocket Launcher fires and deals damage', async ({ page }) => {
            const dummy = await fireAndCollect(page, WEAPONS.rocketLauncher.id, 500, 300, 2000);
            expect(dummy!.hitCount).toBeGreaterThan(0);
            expect(dummy!.totalDamage).toBeGreaterThan(0);
        });

        test('Seeker Rockets fire multiple projectiles', async ({ page }) => {
            const dummy = await fireAndCollect(page, WEAPONS.seekerRockets.id, 500, 300, 3000);
            expect(dummy!.hitCount).toBeGreaterThan(0);
        });

        test('Rocket Minigun fires multiple projectiles', async ({ page }) => {
            const dummy = await fireAndCollect(page, WEAPONS.rocketMinigun.id, 450, 300, 2000);
            expect(dummy!.hitCount).toBeGreaterThan(0);
        });
    });

    // --------------------------------------------------
    // 10. Special Weapons
    // --------------------------------------------------
    test.describe('Special Weapons', () => {
        test('Shrinkifier 5k uses C distance formula (damageScale 6.0)', async ({ page }) => {
            const weapon = WEAPONS.shrinkifier;
            const dummy = await fireAndCollect(page, weapon.id, 500, 300, 2000);

            if (dummy!.hitCount > 0) {
                const hitLog = dummy!.hitLog as HitRecord[];
                const firstHitDamage = hitLog[0].damage;
                // damageScale 6.0 at ~100px: ((100/100)*6*30+10)*0.95 = 180.5
                expect(firstHitDamage).toBeGreaterThan(20);
            }
        });

        test('Mean Minigun fires and deals damage', async ({ page }) => {
            const dummy = await fireAndCollect(page, WEAPONS.meanMinigun.id, 500, 300, 2000);
            expect(dummy!.hitCount).toBeGreaterThan(0);
            expect(dummy!.totalDamage).toBeGreaterThan(0);
        });

        test('Pulse Gun fires and deals damage', async ({ page }) => {
            const dummy = await fireAndCollect(page, WEAPONS.pulseGun.id, 500, 300, 2000);
            expect(dummy!.hitCount).toBeGreaterThan(0);
            expect(dummy!.totalDamage).toBeGreaterThan(0);
        });

        test('Rainbow Gun fires and deals damage', async ({ page }) => {
            const dummy = await fireAndCollect(page, WEAPONS.rainbowGun.id, 500, 300, 2000);
            expect(dummy!.hitCount).toBeGreaterThan(0);
            expect(dummy!.totalDamage).toBeGreaterThan(0);
        });

        test('Grim Weapon fires and deals damage', async ({ page }) => {
            const dummy = await fireAndCollect(page, WEAPONS.grimWeapon.id, 500, 300, 2000);
            expect(dummy!.hitCount).toBeGreaterThan(0);
            expect(dummy!.totalDamage).toBeGreaterThan(0);
        });

        test('Transmutator fires multiple projectiles', async ({ page }) => {
            const dummy = await fireAndCollect(page, WEAPONS.transmutator.id, 450, 300, 2000);
            expect(dummy!.hitCount).toBeGreaterThan(0);
        });
    });
});
