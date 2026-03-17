/**
 * Gauss Gun E2E Tests
 *
 * End-to-end tests verifying the Gauss Gun fires a single piercing blue
 * projectile that passes through multiple enemies.
 *
 * C code reference:
 *   - player.c L1622-1645: weapon_id==6 spawns 1 PROJECTILE_TYPE_GAUSS_GUN
 *   - projectiles.c L77-79: damagePool = 300 for GAUSS_GUN
 *   - projectiles.c L366-368: GAUSS_GUN does NOT deactivate on hit (pierces)
 *   - projectiles.c L605-607: life_timer decays at 0.1x rate (long trail)
 */

import { describe, it, expect, vi, beforeEach } from 'vitest';
import { Enemy, EnemyType } from '../../entities/Enemy';
import { WeaponSystem } from '../combat/WeaponSystem';
import { CollisionSystem } from '../combat/CollisionSystem';
import { Player } from '../../entities/Player';
import { PerkSystem } from '../PerkSystem';
import { ProjectileType, WEAPON_DATA } from '../../data/WeaponData';

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

/**
 * Create a low-health stationary enemy for piercing tests.
 * 
 * Uses a real Enemy (not DummyEnemy) because DummyEnemy resets health to
 * 999999 on death, which breaks the C damagePool math:
 *   C: damagePool -= creature.health  (creature.health is negative after overkill)
 * This means piercing projectiles GAIN pool from overkill, allowing them to
 * pierce through many weak enemies. DummyEnemy's reset defeats this.
 */
function createPiercingTarget(x: number, y: number, health: number = 20): Enemy {
    const enemy = new Enemy(x, y, EnemyType.Zombie);
    enemy.health = health;
    enemy.maxHealth = health;
    enemy.size = 60; // Large hitbox for easy targeting
    enemy.speed = 0; // Stationary
    enemy.maxSpeed = 0;
    return enemy;
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
// GAUSS GUN — SINGLE PROJECTILE
// =============================================================================

describe('Gauss Gun — fires exactly one projectile', () => {
    it('spawns exactly 1 GAUSS_GUN projectile per shot', () => {
        // Equip Gauss Gun (TS weapon ID 10)
        player.switchWeapon(10, ps);
        player.ammo = 30;
        player.shotCooldown = 0;
        player.spreadHeat = 0;

        // Fire at a target to the right
        ws.fireWeapon(player, 500, 300, ps);

        const projectiles = ws.getActiveProjectiles();
        expect(projectiles.length).toBe(1);

        const proj = projectiles[0];
        expect(proj.projectileType).toBe(ProjectileType.GAUSS_GUN);
    });

    it('projectile has damagePool of 300 (allows piercing ~300 enemies)', () => {
        player.switchWeapon(10, ps);
        player.ammo = 30;
        player.shotCooldown = 0;
        player.spreadHeat = 0;

        ws.fireWeapon(player, 500, 300, ps);

        const proj = ws.getActiveProjectiles()[0];
        expect(proj.damagePool).toBe(300);
    });

    it('does NOT fire the Multi-Plasma pattern (5 shots)', () => {
        player.switchWeapon(10, ps);
        player.ammo = 30;
        player.shotCooldown = 0;
        player.spreadHeat = 0;

        ws.fireWeapon(player, 500, 300, ps);

        const projectiles = ws.getActiveProjectiles();
        // Must be exactly 1, not 5 (which would indicate Multi-Plasma)
        expect(projectiles.length).toBe(1);
        // Must NOT be plasma types
        expect(projectiles[0].projectileType).not.toBe(ProjectileType.PLASMA_RIFLE);
        expect(projectiles[0].projectileType).not.toBe(ProjectileType.PLASMA_MINIGUN);
    });
});

// =============================================================================
// GAUSS GUN — PIERCING THROUGH MULTIPLE ENEMIES
// =============================================================================

describe('Gauss Gun — pierces through multiple enemies', () => {
    it('projectile survives after hitting the first enemy', () => {
        player.switchWeapon(10, ps);
        player.ammo = 30;
        player.shotCooldown = 0;
        player.spreadHeat = 0;

        // Low-health target: C damagePool math subtracts creature.health (goes
        // negative on kill → pool GAINS from overkill, enabling piercing)
        const target = createPiercingTarget(300, 300, 20);

        // Fire toward the target
        ws.fireWeapon(player, 500, 300, ps);

        const dt = 1 / 60;
        let hitDetected = false;

        for (let frame = 0; frame < 120; frame++) {
            ws.update(dt);

            const killed = cs.checkProjectileHits(
                ws.getActiveProjectiles(),
                [target],
                player,
                ps,
            );

            if (killed.length > 0 && !hitDetected) {
                hitDetected = true;
                // After killing the enemy, the projectile should still be active
                // because damagePool was 300 and only decremented by ~1 per hit
                // (overkill health is subtracted as negative, increasing pool)
                const activeProj = ws.getActiveProjectiles();
                expect(activeProj.length).toBe(1);
                expect(activeProj[0].damagePool).toBeGreaterThan(0);
                break;
            }
        }

        expect(hitDetected).toBe(true);
    });

    it('pierces through 3 enemies in a line and kills all of them', () => {
        player.switchWeapon(10, ps);
        player.ammo = 30;
        player.shotCooldown = 0;
        player.spreadHeat = 0;

        // Place 3 low-health enemies in a straight line
        const enemy1 = createPiercingTarget(250, 300, 20);
        const enemy2 = createPiercingTarget(400, 300, 20);
        const enemy3 = createPiercingTarget(550, 300, 20);
        const enemies = [enemy1, enemy2, enemy3];

        // Fire toward the right
        ws.fireWeapon(player, 800, 300, ps);

        const dt = 1 / 60;
        const allKilled: Enemy[] = [];

        // Run simulation until all 3 are killed or timeout
        for (let frame = 0; frame < 300; frame++) {
            ws.update(dt);

            const killed = cs.checkProjectileHits(
                ws.getActiveProjectiles(),
                enemies,
                player,
                ps,
            );

            for (const k of killed) {
                if (!allKilled.includes(k)) allKilled.push(k);
            }

            // Stop early if all 3 are dead
            if (!enemy1.isAlive() && !enemy2.isAlive() && !enemy3.isAlive()) {
                break;
            }
        }

        // All 3 enemies should have been killed by the single piercing projectile
        expect(enemy1.isAlive()).toBe(false);
        expect(enemy2.isAlive()).toBe(false);
        expect(enemy3.isAlive()).toBe(false);
        expect(allKilled.length).toBe(3);
    });

    it('only spawns 1 projectile even when piercing multiple enemies', () => {
        player.switchWeapon(10, ps);
        player.ammo = 30;
        player.shotCooldown = 0;
        player.spreadHeat = 0;

        const enemy1 = createPiercingTarget(250, 300, 20);
        const enemy2 = createPiercingTarget(400, 300, 20);

        ws.fireWeapon(player, 800, 300, ps);

        // Verify only 1 projectile was ever spawned
        expect(ws.getActiveProjectiles().length).toBe(1);

        const dt = 1 / 60;
        for (let frame = 0; frame < 200; frame++) {
            ws.update(dt);
            cs.checkProjectileHits(
                ws.getActiveProjectiles(),
                [enemy1, enemy2],
                player,
                ps,
            );
        }

        // Both should be dead (piercing), and Gauss Gun doesn't spawn
        // child projectiles (unlike Splitter Gun or Plasma Cannon)
        expect(enemy1.isAlive()).toBe(false);
        expect(enemy2.isAlive()).toBe(false);
    });
});

// =============================================================================
// GAUSS GUN — WEAPON DATA VERIFICATION
// =============================================================================

describe('Gauss Gun — weapon data matches C code', () => {
    const gaussData = WEAPON_DATA[10]; // TS weapon ID 10

    it('is named "Gauss Gun"', () => {
        expect(gaussData.name).toBe('Gauss Gun');
    });

    it('has clipSize of 6 (OFF-BY-ONE FIX: from weapon_rocket_launcher_clip)', () => {
        expect(gaussData.clipSize).toBe(6);
    });

    it('has projectileCount of 1 (single shot, NOT shotgun)', () => {
        expect(gaussData.projectileCount).toBe(1);
    });

    it('uses ProjectileType.GAUSS_GUN', () => {
        expect(gaussData.projectileType).toBe(ProjectileType.GAUSS_GUN);
    });

    it('has shotCooldown ~0.6 (OFF-BY-ONE FIX: from weapon_rocket_launcher_fire_rate)', () => {
        expect(gaussData.shotCooldown).toBeCloseTo(0.6, 2);
    });
});
