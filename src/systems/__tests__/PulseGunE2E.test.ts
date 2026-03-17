/**
 * Pulse Gun E2E Tests
 *
 * End-to-end tests verifying the Pulse Gun fires a wave projectile that:
 *   1. Uses ProjectileType.PULSE_GUN
 *   2. Has damagePool = 1 (C-accurate single-hit, then dies)
 *   3. Has hitRadius that grows with distance from origin (wave expansion)
 *   4. Pushes enemies on hit (C projectiles.c L445-448)
 *   5. Dies after hitting one enemy (C: lifetime=0.25, active=false)
 *
 * C code reference:
 *   - player.c L1530-1533: weapon_id==19 spawns PROJECTILE_TYPE_PULSE_GUN
 *   - projectiles.c L90: damagePool = 1.0 (default — single hit)
 *   - projectiles.c L370: lifetime = 0.25 on hit (enters dying phase)
 *   - projectiles.c L445-448: push effect on hit (movement_delta * 3.0)
 *   - projectiles.c L1653-1668: rendering — distance-scaled atlas(2,0)
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

function createTarget(x: number, y: number, health: number = 20): Enemy {
    const enemy = new Enemy(x, y, EnemyType.Zombie);
    enemy.health = health;
    enemy.maxHealth = health;
    enemy.size = 60; // Large hitbox for easy targeting
    enemy.speed = 0;
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
// PULSE GUN — PROJECTILE TYPE & PROPERTIES
// =============================================================================

describe('Pulse Gun — fires correct projectile type', () => {
    it('spawns exactly 1 PULSE_GUN projectile per shot', () => {
        player.switchWeapon(19, ps);
        player.ammo = 30;
        player.shotCooldown = 0;
        player.spreadHeat = 0;

        ws.fireWeapon(player, 500, 300, ps);

        const projectiles = ws.getActiveProjectiles();
        expect(projectiles.length).toBe(1);
        expect(projectiles[0].projectileType).toBe(ProjectileType.PULSE_GUN);
    });

    it('has damagePool of 1 (C-accurate single-hit)', () => {
        player.switchWeapon(19, ps);
        player.ammo = 30;
        player.shotCooldown = 0;
        player.spreadHeat = 0;

        ws.fireWeapon(player, 500, 300, ps);

        const proj = ws.getActiveProjectiles()[0];
        expect(proj.damagePool).toBe(1);
    });

    it('has originX/originY set to player position for distance scaling', () => {
        player.switchWeapon(19, ps);
        player.ammo = 30;
        player.shotCooldown = 0;
        player.spreadHeat = 0;

        ws.fireWeapon(player, 500, 300, ps);

        const proj = ws.getActiveProjectiles()[0];
        expect(proj.originX).toBeCloseTo(player.x, 0);
        expect(proj.originY).toBeCloseTo(player.y, 0);
    });
});

// =============================================================================
// PULSE GUN — WAVE EXPANSION (hitRadius grows with distance)
// =============================================================================

describe('Pulse Gun — wave expands with distance', () => {
    it('hitRadius grows as projectile travels away from origin', () => {
        player.switchWeapon(19, ps);
        player.ammo = 30;
        player.shotCooldown = 0;
        player.spreadHeat = 0;

        ws.fireWeapon(player, 800, 300, ps);

        const proj = ws.getActiveProjectiles()[0];
        const dt = 1 / 60;

        // Record hitRadius at different distances
        const radii: number[] = [];
        const distances: number[] = [];

        for (let frame = 0; frame < 60; frame++) {
            ws.update(dt);
            const dx = proj.x - proj.originX;
            const dy = proj.y - proj.originY;
            const dist = Math.sqrt(dx * dx + dy * dy);
            distances.push(dist);
            radii.push(proj.hitRadius);
        }

        // After traveling, the hitRadius should be larger than at start
        const earlyRadius = radii[5]; // frame 5
        const lateRadius = radii[radii.length - 1]; // last frame

        expect(lateRadius).toBeGreaterThan(earlyRadius);

        // Verify the formula: hitRadius = max(4, dist * 0.01 * 8)
        const lastDist = distances[distances.length - 1];
        const expectedRadius = Math.max(4, lastDist * 0.01 * 8);
        expect(lateRadius).toBeCloseTo(expectedRadius, 1);
    });

    it('hitRadius starts at minimum 4 when near origin', () => {
        player.switchWeapon(19, ps);
        player.ammo = 30;
        player.shotCooldown = 0;
        player.spreadHeat = 0;

        ws.fireWeapon(player, 800, 300, ps);

        const proj = ws.getActiveProjectiles()[0];
        ws.update(1 / 60);
        expect(proj.hitRadius).toBeGreaterThanOrEqual(4);
    });
});

// =============================================================================
// PULSE GUN — SINGLE HIT THEN DIES (C-accurate)
// =============================================================================

describe('Pulse Gun — dies after hitting one enemy', () => {
    it('projectile deactivates after hitting an enemy', () => {
        player.switchWeapon(19, ps);
        player.ammo = 30;
        player.shotCooldown = 0;
        player.spreadHeat = 0;

        // Place close enough that the slow wave (250px/s) reaches it in time
        // Low health (5) so distance-based damage formula kills it
        // At dist=100: damage = ((100/100)*0.1*30+10)*0.95 ≈ 12.35
        const target = createTarget(200, 300, 5);

        ws.fireWeapon(player, 800, 300, ps);

        const dt = 1 / 60;
        let hitDetected = false;

        // 250px/s → ~600 frames to cross screen, allow plenty of time
        for (let frame = 0; frame < 600; frame++) {
            ws.update(dt);
            const killed = cs.checkProjectileHits(
                ws.getActiveProjectiles(),
                [target],
                player,
                ps,
            );

            if (killed.length > 0 && !hitDetected) {
                hitDetected = true;
                // C: damagePool = 1 → after subtracting 1 → 0 → projectile dies
                // Projectile should be deactivated (active = false)
                const activeProj = ws.getActiveProjectiles().filter(p => p.isActive());
                expect(activeProj.length).toBe(0);
                break;
            }
        }

        expect(hitDetected).toBe(true);
    });

    it('does NOT pierce through to second enemy (damagePool = 1)', () => {
        player.switchWeapon(19, ps);
        player.ammo = 30;
        player.shotCooldown = 0;
        player.spreadHeat = 0;

        // Two enemies in a line — only the first should be hit
        // Place close for the slow 250 px/s wave to reach
        // Low health (5) so distance-based damage formula kills them
        const enemy1 = createTarget(200, 300, 5);
        const enemy2 = createTarget(400, 300, 5);
        const enemies = [enemy1, enemy2];

        ws.fireWeapon(player, 800, 300, ps);

        const dt = 1 / 60;

        // Run long enough for wave to pass through both positions
        for (let frame = 0; frame < 900; frame++) {
            ws.update(dt);
            cs.checkProjectileHits(
                ws.getActiveProjectiles(),
                enemies,
                player,
                ps,
            );
        }

        // First enemy should be dead, second should survive
        expect(enemy1.isAlive()).toBe(false);
        expect(enemy2.isAlive()).toBe(true);
    });
});

// =============================================================================
// PULSE GUN — PUSH ON HIT
// =============================================================================

describe('Pulse Gun — push effect on hit', () => {
    it('pushes enemy position on hit (C L445-448: movement_delta * 3.0)', () => {
        player.switchWeapon(19, ps);
        player.ammo = 30;
        player.shotCooldown = 0;
        player.spreadHeat = 0;

        // Place close for the slow 250 px/s wave
        const enemy = createTarget(200, 300, 500); // High health so it survives
        const initialX = enemy.x;

        // Fire to the right
        ws.fireWeapon(player, 800, 300, ps);

        const dt = 1 / 60;

        for (let frame = 0; frame < 600; frame++) {
            ws.update(dt);
            cs.checkProjectileHits(
                ws.getActiveProjectiles(),
                [enemy],
                player,
                ps,
            );

            if (enemy.x !== initialX) break;
        }

        // Enemy should have been pushed in the firing direction (rightward)
        expect(enemy.x).toBeGreaterThan(initialX);
    });
});

// =============================================================================
// PULSE GUN — WEAPON DATA VERIFICATION
// =============================================================================

describe('Pulse Gun — weapon data matches C code', () => {
    const pulseData = WEAPON_DATA[19];

    it('is named "Pulse Gun"', () => {
        expect(pulseData.name).toBe('Pulse Gun');
    });

    it('uses ProjectileType.PULSE_GUN', () => {
        expect(pulseData.projectileType).toBe(ProjectileType.PULSE_GUN);
    });

    it('has damageScale of 0.1 (distance-based damage)', () => {
        expect(pulseData.damageScale).toBeCloseTo(0.1, 2);
    });

    it('has clipSize of 16', () => {
        expect(pulseData.clipSize).toBe(16);
    });

    it('has shotCooldown of 0.1 (rapid fire)', () => {
        expect(pulseData.shotCooldown).toBeCloseTo(0.1, 2);
    });

    it('has slow projectile speed (~250 px/s) for visible wave expansion', () => {
        expect(pulseData.projectileSpeed).toBe(250);
    });
});
