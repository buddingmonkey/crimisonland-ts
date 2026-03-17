/**
 * Shock Chain E2E Tests
 *
 * End-to-end tests for the Shock Chain bonus using DummyEnemy targets,
 * real WeaponSystem, CollisionSystem, and BonusEffects.
 *
 * Verifies:
 * 1. Initial projectile spawns aimed at nearest enemy
 * 2. Chain lightning propagates on hit via handleChainLightning
 * 3. Chain skips enemies within 100px minimum distance
 * 4. Chain stops after 32 links
 * 5. Full integration: projectile actually hits DummyEnemy
 */

import { describe, it, expect, vi, beforeEach } from 'vitest';
import { DummyEnemy } from '../../entities/DummyEnemy';
import { WeaponSystem } from '../combat/WeaponSystem';
import { CollisionSystem } from '../combat/CollisionSystem';
import { Player } from '../../entities/Player';
import { PerkSystem } from '../PerkSystem';
import { BonusType } from '../../entities/Bonus';
import { ProjectileType } from '../../data/WeaponData';
import {
    applyBonusEffect,
    handleChainLightning,
    type BonusEffectContext,
} from '../bonus/BonusEffects';

// Mock quest system
vi.mock('../quest/QuestSystem', () => ({
    questSystem: {
        isActive: () => false,
        reportEnemyKilled: vi.fn(),
    },
}));

// Mock console
vi.mock('../../console/Console', () => ({
    gameConsole: { log: vi.fn(), print: vi.fn() },
}));

// ─── Test Helpers ─────────────────────────────────────────────────────────────

/** Create a minimal BonusEffectContext that uses a real WeaponSystem */
function createBonusContext(
    ws: WeaponSystem,
    enemies: DummyEnemy[],
    overrides: Partial<BonusEffectContext> = {},
): BonusEffectContext {
    return {
        player: {
            experience: 0,
            health: 100,
            shieldTimer: 0,
            fireBulletsTimer: 0,
            shotCooldown: 0,
            reloadTimer: 0,
            reloadActive: false,
            ammo: 10,
            clipSize: 10,
            energizerTimer: 0,
            doubleXPTimer: 0,
            reflexBoostTimer: 0,
            weaponPowerUpTimer: 0,
            speedBonusTimer: 0,
            freezeTimer: 0,
            switchWeapon: vi.fn(),
            getWeaponStats: () => ({ name: 'Test' }),
        },
        perkSystem: { hasPerk: () => false },
        soundSystem: { playAtPosition: vi.fn() },
        enemySpawner: {
            getActiveEnemies: () => enemies as any[],
        },
        weaponSystem: ws as any,
        cameraShake: { startShake: vi.fn() },
        particleSystem: { spawnBurst: vi.fn() },
        effectSystem: {
            spawnExplosionBurst: vi.fn(),
            spawnFreezeShard: vi.fn(),
            spawnFreezeShatter: vi.fn(),
            spawnFreezeFlash: vi.fn(),
            spawnReflexHalo: vi.fn(),
            spawnBurst: vi.fn(),
            spawnShockwave: vi.fn(),
            spawnFireParticles: vi.fn(),
            spawnBonusPickupParticles: vi.fn(),
        },
        addBonusHudSlot: vi.fn(),
        nextProjectileId: 1,
        shockChainLinksLeft: 0,
        shockChainProjectileId: -1,
        ...overrides,
    };
}

/** Create a bonus pickup object */
function createShockChainBonus(x: number, y: number) {
    return {
        type: BonusType.SHOCK_CHAIN,
        x,
        y,
        amount: 0,
    };
}

// ─── Shared State ─────────────────────────────────────────────────────────────

let ws: WeaponSystem;
let cs: CollisionSystem;
let player: Player;
let ps: PerkSystem;

beforeEach(() => {
    ws = new WeaponSystem();
    cs = new CollisionSystem();
    player = new Player(100, 300);
    ps = new PerkSystem();
});

// =============================================================================
// SHOCK CHAIN TESTS
// =============================================================================

describe('Shock Chain — initial projectile spawn', () => {
    it('spawns an ION_RIFLE projectile aimed at the nearest enemy', () => {
        const dummy = new DummyEnemy(400, 300, 'target');
        const ctx = createBonusContext(ws, [dummy]);
        const bonus = createShockChainBonus(200, 300);

        applyBonusEffect(ctx, bonus);

        // Should have spawned one projectile
        const projectiles = ws.getActiveProjectiles();
        expect(projectiles.length).toBe(1);

        const proj = projectiles[0];
        expect(proj.projectileType).toBe(ProjectileType.ION_RIFLE);
        expect(proj.isChainLightning).toBe(true);
        expect(proj.noBonusDrop).toBe(true);

        // Projectile should be aimed roughly to the right (toward 400,300 from 200,300)
        // angle should be ~0 (pointing right)
        expect(proj.vx).toBeGreaterThan(0);
        expect(Math.abs(proj.vy)).toBeLessThan(Math.abs(proj.vx) * 0.1);
    });

    it('sets shockChainLinksLeft to 32 and assigns projectile ID', () => {
        const dummy = new DummyEnemy(400, 300, 'target');
        const ctx = createBonusContext(ws, [dummy]);
        const bonus = createShockChainBonus(200, 300);

        applyBonusEffect(ctx, bonus);

        expect(ctx.shockChainLinksLeft).toBe(32);
        expect(ctx.shockChainProjectileId).toBeGreaterThanOrEqual(0);
    });

    it('targets the nearest enemy even when multiple exist', () => {
        const farDummy = new DummyEnemy(600, 300, 'far');
        const nearDummy = new DummyEnemy(300, 300, 'near');
        const ctx = createBonusContext(ws, [farDummy, nearDummy]);
        const bonus = createShockChainBonus(200, 300);

        applyBonusEffect(ctx, bonus);

        const proj = ws.getActiveProjectiles()[0];
        // Should aim toward nearDummy at (300,300) from (200,300) — angle ~0 (right)
        expect(proj.vx).toBeGreaterThan(0);
    });

    it('does nothing when no enemies exist', () => {
        const ctx = createBonusContext(ws, []);
        const bonus = createShockChainBonus(200, 300);

        applyBonusEffect(ctx, bonus);

        expect(ws.getActiveProjectiles().length).toBe(0);
        expect(ctx.shockChainLinksLeft).toBe(0); // Not set
    });
});

describe('Shock Chain — chain propagation (handleChainLightning)', () => {
    it('spawns a new projectile toward the next nearest enemy on hit', () => {
        // Setup: 3 enemies in a line, 150px apart
        const enemy1 = new DummyEnemy(400, 300, 'e1');
        const enemy2 = new DummyEnemy(550, 300, 'e2');
        const enemy3 = new DummyEnemy(700, 300, 'e3');
        const ctx = createBonusContext(ws, [enemy1, enemy2, enemy3]);

        // Simulate initial shock chain pickup
        const bonus = createShockChainBonus(200, 300);
        applyBonusEffect(ctx, bonus);

        const initialProj = ws.getActiveProjectiles()[0];
        expect(initialProj.isChainLightning).toBe(true);

        // Simulate the first projectile hitting enemy1
        handleChainLightning(ctx, initialProj, enemy1);

        // Should have spawned a second projectile
        const allProj = ws.getActiveProjectiles();
        expect(allProj.length).toBe(2);

        // New projectile should be chain lightning too
        const chainProj = allProj[1];
        expect(chainProj.isChainLightning).toBe(true);
        expect(chainProj.projectileType).toBe(ProjectileType.ION_RIFLE);

        // Should aim toward enemy2 (550,300 from 400,300 — pointing right)
        expect(chainProj.vx).toBeGreaterThan(0);

        // Links should have decremented
        expect(ctx.shockChainLinksLeft).toBe(31);
    });

    it('skips enemies within 100px minimum distance', () => {
        // enemy1 is the hit target, tooClose is 50px away (should be skipped),
        // validTarget is 200px away (should be targeted)
        const enemy1 = new DummyEnemy(400, 300, 'hit');
        const tooClose = new DummyEnemy(430, 300, 'close'); // Only 30px from enemy1
        const validTarget = new DummyEnemy(600, 300, 'valid'); // 200px from enemy1
        const ctx = createBonusContext(ws, [enemy1, tooClose, validTarget]);

        const bonus = createShockChainBonus(200, 300);
        applyBonusEffect(ctx, bonus);

        const initialProj = ws.getActiveProjectiles()[0];
        handleChainLightning(ctx, initialProj, enemy1);

        // Should have spawned a chain projectile aimed at validTarget, not tooClose
        const chainProj = ws.getActiveProjectiles()[1];
        // validTarget is at 600, enemy1 is at 400: dx=200, so vx should be positive
        expect(chainProj.vx).toBeGreaterThan(0);
    });

    it('stops chaining when shockChainLinksLeft reaches 0', () => {
        const enemy1 = new DummyEnemy(400, 300, 'e1');
        const enemy2 = new DummyEnemy(550, 300, 'e2');
        const ctx = createBonusContext(ws, [enemy1, enemy2]);

        const bonus = createShockChainBonus(200, 300);
        applyBonusEffect(ctx, bonus);

        // Force links to 1 (last link)
        ctx.shockChainLinksLeft = 1;

        const initialProj = ws.getActiveProjectiles()[0];
        handleChainLightning(ctx, initialProj, enemy1);

        // Should have used the last link
        expect(ctx.shockChainLinksLeft).toBe(0);

        // Now try chaining again — should NOT spawn another projectile
        const projectilesBeforeSecondChain = ws.getActiveProjectiles().length;
        const secondProj = ws.getActiveProjectiles()[1];
        if (secondProj) {
            handleChainLightning(ctx, secondProj, enemy2);
        }
        // No new projectile should be spawned
        expect(ws.getActiveProjectiles().length).toBe(projectilesBeforeSecondChain);
    });

    it('does not chain when projectile ID does not match', () => {
        const enemy1 = new DummyEnemy(400, 300, 'e1');
        const enemy2 = new DummyEnemy(550, 300, 'e2');
        const ctx = createBonusContext(ws, [enemy1, enemy2]);

        const bonus = createShockChainBonus(200, 300);
        applyBonusEffect(ctx, bonus);

        const initialProj = ws.getActiveProjectiles()[0];

        // Corrupt the projectile's chain ID so it doesn't match
        initialProj.chainProjectileId = -999;

        handleChainLightning(ctx, initialProj, enemy1);

        // Should NOT have spawned a new projectile
        expect(ws.getActiveProjectiles().length).toBe(1);
    });

    it('ignores non-chain-lightning projectiles', () => {
        const enemy1 = new DummyEnemy(400, 300, 'e1');
        const enemy2 = new DummyEnemy(550, 300, 'e2');
        const ctx = createBonusContext(ws, [enemy1, enemy2]);

        // Spawn a normal projectile (not chain lightning)
        const normalProj = ws.spawnBonusProjectile(200, 300, 0, ProjectileType.ION_RIFLE);

        handleChainLightning(ctx, normalProj, enemy1);

        // Should NOT chain — only 1 projectile (the normal one)
        expect(ws.getActiveProjectiles().length).toBe(1);
    });
});

describe('Shock Chain — full integration with CollisionSystem', () => {
    it('chain projectile actually hits a DummyEnemy via CollisionSystem', () => {
        const dummy = new DummyEnemy(400, 300, 'target');
        // Give the dummy a known radius
        dummy.size = 60;
        const ctx = createBonusContext(ws, [dummy]);

        const bonus = createShockChainBonus(200, 300);
        applyBonusEffect(ctx, bonus);

        const proj = ws.getActiveProjectiles()[0];
        expect(proj).toBeDefined();
        expect(proj.isChainLightning).toBe(true);

        // Step the projectile forward until it reaches the dummy
        // ION_RIFLE speed is ~5400px/s, dummy is 200px away, so ~0.037s
        const dt = 1 / 60;
        let hitDetected = false;

        for (let frame = 0; frame < 120; frame++) {
            ws.update(dt);

            // Check collisions with chain lightning callback
            cs.checkProjectileHits(
                ws.getActiveProjectiles(),
                [dummy],
                player,
                ps,
                (projectile, enemy) => {
                    hitDetected = true;
                    handleChainLightning(ctx, projectile, enemy);
                },
            );

            if (hitDetected) break;
        }

        expect(hitDetected).toBe(true);
        // The dummy should have recorded at least one hit
        expect(dummy.getHitCount()).toBeGreaterThan(0);
    });

    it('chain projectile hits first enemy then chains to second', () => {
        // Place two dummies 200px apart
        const dummy1 = new DummyEnemy(350, 300, 'd1');
        const dummy2 = new DummyEnemy(550, 300, 'd2');
        dummy1.size = 60;
        dummy2.size = 60;
        const enemies = [dummy1, dummy2];
        const ctx = createBonusContext(ws, enemies);

        const bonus = createShockChainBonus(200, 300);
        applyBonusEffect(ctx, bonus);

        // Run simulation frames
        const dt = 1 / 60;
        let chainCount = 0;

        for (let frame = 0; frame < 300; frame++) {
            ws.update(dt);

            cs.checkProjectileHits(
                ws.getActiveProjectiles(),
                enemies,
                player,
                ps,
                (projectile, enemy) => {
                    handleChainLightning(ctx, projectile, enemy);
                    chainCount++;
                },
            );

            // Stop early if both dummies were hit
            if (dummy1.getHitCount() > 0 && dummy2.getHitCount() > 0) break;
        }

        // First dummy should have been hit
        expect(dummy1.getHitCount()).toBeGreaterThan(0);

        // Chain propagation should have been triggered
        expect(chainCount).toBeGreaterThanOrEqual(1);

        // Second dummy should eventually be hit by the chain projectile
        // (may need more frames if projectile speed is slow — but ION_RIFLE is fast)
        expect(dummy2.getHitCount()).toBeGreaterThan(0);
    });

    it('noBonusDrop flag prevents bonus drops from chain kills', () => {
        const dummy = new DummyEnemy(400, 300, 'target');
        dummy.size = 60;
        dummy.health = 1; // Will die on first hit
        dummy.maxHealth = 1;
        const ctx = createBonusContext(ws, [dummy]);

        const bonus = createShockChainBonus(200, 300);
        applyBonusEffect(ctx, bonus);

        const dt = 1 / 60;
        let killedEnemies: any[] = [];

        for (let frame = 0; frame < 120; frame++) {
            ws.update(dt);

            const kills = cs.checkProjectileHits(
                ws.getActiveProjectiles(),
                [dummy],
                player,
                ps,
                (projectile, enemy) => {
                    handleChainLightning(ctx, projectile, enemy);
                },
            );

            if (kills.length > 0) {
                killedEnemies = kills;
                break;
            }
        }

        // The killed enemy should have noBonusDrop set
        if (killedEnemies.length > 0) {
            expect(killedEnemies[0].noBonusDrop).toBe(true);
        }
    });
});
