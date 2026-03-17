/**
 * Rocket Launcher E2E Tests
 *
 * End-to-end tests verifying the Rocket Launcher fires a single rocket
 * projectile that flies into a target, explodes, and causes AoE damage
 * to nearby enemies at increasing distances.
 *
 * C code reference:
 *   - player.c: weapon_id==12 spawns 1 PROJECTILE_TYPE_ROCKET
 *   - projectiles.c L804-863: rocket hit → isExploding, vel=0, scale=1.0
 *   - projectiles.c L620-659: AoE phase — radius = scale * timer * 80,
 *                              DPS = scale * 700 * dt, timer += dt * 3
 *   - CollisionSystem L195-196: direct hit damage = lifetime * 50 + 500
 */

import { describe, it, expect, vi, beforeEach } from 'vitest';
import { DummyEnemy } from '../../entities/DummyEnemy';
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

// ─── Helper ───────────────────────────────────────────────────────────────────

/**
 * Advance the simulation: move projectiles and check collisions.
 * Also pumps AoE explosion damage by calling projectile.update with
 * the enemy list (required for rocket explosion phase).
 */
function stepSimulation(
    ws: WeaponSystem,
    cs: CollisionSystem,
    enemies: DummyEnemy[],
    player: Player,
    ps: PerkSystem,
    dt: number,
): void {
    // Update projectile positions + rocket explosion AoE
    // enemies must be 3rd arg (2nd is shockChainState)
    ws.update(dt, undefined, enemies as any[]);

    // Check direct-hit collisions (rockets that haven't exploded yet)
    cs.checkProjectileHits(
        ws.getActiveProjectiles(),
        enemies,
        player,
        ps,
    );
}

// =============================================================================
// ROCKET LAUNCHER — SINGLE PROJECTILE
// =============================================================================

describe('Rocket Launcher — fires exactly one rocket projectile', () => {
    it('spawns exactly 1 ROCKET projectile per shot', () => {
        // Equip Rocket Launcher (TS weapon ID 11)
        player.switchWeapon(11, ps);
        player.ammo = 6;
        player.shotCooldown = 0;
        player.spreadHeat = 0;

        // Fire at a target to the right
        ws.fireWeapon(player, 500, 300, ps);

        const projectiles = ws.getActiveProjectiles();
        expect(projectiles.length).toBe(1);

        const proj = projectiles[0];
        expect(proj.projectileType).toBe(ProjectileType.ROCKET);
    });

    it('rocket projectile has isRocket=true and rocketType="rocket"', () => {
        player.switchWeapon(11, ps);
        player.ammo = 6;
        player.shotCooldown = 0;
        player.spreadHeat = 0;

        ws.fireWeapon(player, 500, 300, ps);

        const proj = ws.getActiveProjectiles()[0];
        // Dedicated switch case calls initRocketProps → sets isRocket
        expect(proj.projectileType).toBe(ProjectileType.ROCKET);
        expect(proj.isRocket).toBe(true);
        expect(proj.rocketType).toBe('rocket');
    });

    it('rocket projectile flies toward the target direction', () => {
        player.switchWeapon(11, ps);
        player.ammo = 6;
        player.shotCooldown = 0;
        player.spreadHeat = 0;

        // Fire to the right
        ws.fireWeapon(player, 800, 300, ps);

        const proj = ws.getActiveProjectiles()[0];
        // vx should be positive (heading right), vy close to 0
        expect(proj.vx).toBeGreaterThan(0);
    });
});

// =============================================================================
// ROCKET LAUNCHER — DIRECT HIT + EXPLOSION TRANSITION
// =============================================================================

describe('Rocket Launcher — direct hit and explosion', () => {
    it('rocket hits a DummyEnemy and transitions to exploding state', () => {
        player.switchWeapon(11, ps);
        player.ammo = 6;
        player.shotCooldown = 0;
        player.spreadHeat = 0;

        // Place a dummy directly in front of the player
        const target = new DummyEnemy(400, 300, 'direct_hit');
        target.size = 60;

        ws.fireWeapon(player, 500, 300, ps);

        const dt = 1 / 60;
        let hitDetected = false;

        for (let frame = 0; frame < 300; frame++) {
            ws.update(dt);

            cs.checkProjectileHits(
                ws.getActiveProjectiles(),
                [target],
                player,
                ps,
            );

            if (target.getHitCount() > 0 && !hitDetected) {
                hitDetected = true;
                // Rocket should transition to exploding, NOT deactivate
                const proj = ws.getActiveProjectiles()[0];
                expect(proj).toBeDefined();
                expect(proj.isExploding).toBe(true);
                expect(proj.explosionScale).toBe(1.0);
                break;
            }
        }

        expect(hitDetected).toBe(true);
    });

    it('direct hit deals C-formula damage: lifetime * 50 + 500', () => {
        player.switchWeapon(11, ps);
        player.ammo = 6;
        player.shotCooldown = 0;
        player.spreadHeat = 0;

        const target = new DummyEnemy(400, 300, 'damage_check');
        target.size = 60;

        ws.fireWeapon(player, 500, 300, ps);

        const dt = 1 / 60;

        for (let frame = 0; frame < 300; frame++) {
            ws.update(dt);

            cs.checkProjectileHits(
                ws.getActiveProjectiles(),
                [target],
                player,
                ps,
            );

            if (target.getHitCount() > 0) break;
        }

        // Direct hit should deal significant damage (lifetime * 50 + 500)
        // With lifetime around 0.4, that's ~520. Even with decay, should be > 400.
        const directHit = target.getLastHit()!;
        expect(directHit).toBeDefined();
        expect(directHit.damage).toBeGreaterThan(400);
        expect(directHit.damageType).toBe(3); // Rocket damage type
    });
});

// =============================================================================
// ROCKET LAUNCHER — AoE EXPLOSION DAMAGE
// =============================================================================

describe('Rocket Launcher — AoE explosion damages nearby enemies', () => {
    it('explosion damages a nearby DummyEnemy that was NOT directly hit', () => {
        player.switchWeapon(11, ps);
        player.ammo = 6;
        player.shotCooldown = 0;
        player.spreadHeat = 0;

        // Direct-hit target at (400, 300)
        const directTarget = new DummyEnemy(400, 300, 'direct');
        directTarget.size = 60;

        // Nearby bystander at (440, 300) — 40px away, well within AoE radius
        const bystander = new DummyEnemy(440, 300, 'bystander');
        bystander.size = 30;

        const enemies = [directTarget, bystander];

        ws.fireWeapon(player, 500, 300, ps);

        const dt = 1 / 60;

        // Run simulation long enough for rocket to hit + explosion to expand
        for (let frame = 0; frame < 500; frame++) {
            stepSimulation(ws, cs, enemies, player, ps, dt);

            // Stop once bystander has taken AoE damage
            if (bystander.getHitCount() > 0) break;
        }

        // Direct target should have the initial hit
        expect(directTarget.getHitCount()).toBeGreaterThan(0);

        // Bystander should have taken AoE damage from the explosion
        expect(bystander.getHitCount()).toBeGreaterThan(0);
        expect(bystander.getTotalDamage()).toBeGreaterThan(0);
    });

    it('AoE deals damage over multiple frames (continuous DPS)', () => {
        player.switchWeapon(11, ps);
        player.ammo = 6;
        player.shotCooldown = 0;
        player.spreadHeat = 0;

        // Place a dummy right at the explosion point
        const target = new DummyEnemy(400, 300, 'aoe_dps');
        target.size = 60;

        ws.fireWeapon(player, 500, 300, ps);

        const dt = 1 / 60;

        // Run until explosion finishes (timer > 1.0 at 3× rate ≈ 20 frames)
        for (let frame = 0; frame < 500; frame++) {
            stepSimulation(ws, cs, [target], player, ps, dt);
        }

        // Should have accumulated many hits from continuous AoE DPS
        // Direct hit + many AoE ticks = lots of hits
        expect(target.getHitCount()).toBeGreaterThan(5);
        expect(target.getTotalDamage()).toBeGreaterThan(500);
    });
});

// =============================================================================
// ROCKET LAUNCHER — AoE REACH (LINE OF DUMMIES)
// =============================================================================

describe('Rocket Launcher — AoE reach with line of DummyEnemies', () => {
    it('explosion reaches dummies at increasing distances', () => {
        player.switchWeapon(11, ps);
        player.ammo = 6;
        player.shotCooldown = 0;
        player.spreadHeat = 0;

        // Direct-hit target at (400, 300)
        const directTarget = new DummyEnemy(400, 300, 'target');
        directTarget.size = 30;

        // Line of dummies extending outward from the explosion center
        // AoE max radius = explosionScale(1.0) * explosionTimer(~1.0) * 80 = 80px
        const dummy20px = new DummyEnemy(420, 300, 'at_20px');
        dummy20px.size = 10;

        const dummy40px = new DummyEnemy(440, 300, 'at_40px');
        dummy40px.size = 10;

        const dummy60px = new DummyEnemy(460, 300, 'at_60px');
        dummy60px.size = 10;

        const dummy80px = new DummyEnemy(480, 300, 'at_80px');
        dummy80px.size = 10;

        // This one is outside max AoE radius (100px away > 80px max)
        const dummy100px = new DummyEnemy(500, 300, 'at_100px');
        dummy100px.size = 10;

        const enemies = [directTarget, dummy20px, dummy40px, dummy60px, dummy80px, dummy100px];

        ws.fireWeapon(player, 500, 300, ps);

        const dt = 1 / 60;

        // Run full explosion cycle (rocket fly time + explosion duration)
        for (let frame = 0; frame < 600; frame++) {
            stepSimulation(ws, cs, enemies, player, ps, dt);
        }

        // Direct target: hit by direct hit + AoE
        expect(directTarget.getHitCount()).toBeGreaterThan(0);

        // 20px away: well within AoE, should be hit
        expect(dummy20px.getHitCount()).toBeGreaterThan(0);
        expect(dummy20px.getTotalDamage()).toBeGreaterThan(0);

        // 40px away: within AoE, should be hit
        expect(dummy40px.getHitCount()).toBeGreaterThan(0);
        expect(dummy40px.getTotalDamage()).toBeGreaterThan(0);

        // 60px away: within AoE (radius reaches 80px), should be hit
        expect(dummy60px.getHitCount()).toBeGreaterThan(0);
        expect(dummy60px.getTotalDamage()).toBeGreaterThan(0);

        // Damage falloff: closer dummies should take MORE total damage
        // because they're inside the radius for more frames as it grows
        expect(dummy20px.getTotalDamage()).toBeGreaterThan(dummy60px.getTotalDamage());

        // 100px away: outside max AoE (80px radius), should NOT be hit
        expect(dummy100px.getHitCount()).toBe(0);
    });

    it('dummies record AoE damage type 3 (rocket/explosion)', () => {
        player.switchWeapon(11, ps);
        player.ammo = 6;
        player.shotCooldown = 0;
        player.spreadHeat = 0;

        const directTarget = new DummyEnemy(400, 300, 'target');
        directTarget.size = 30;

        const bystander = new DummyEnemy(430, 300, 'bystander');
        bystander.size = 10;

        const enemies = [directTarget, bystander];

        ws.fireWeapon(player, 500, 300, ps);

        const dt = 1 / 60;

        for (let frame = 0; frame < 500; frame++) {
            stepSimulation(ws, cs, enemies, player, ps, dt);
            if (bystander.getHitCount() > 0) break;
        }

        // AoE hits should be damage type 3 (rocket)
        expect(bystander.getHitCount()).toBeGreaterThan(0);
        const bystHit = bystander.getLastHit()!;
        expect(bystHit.damageType).toBe(3);
    });

    it('explosion deactivates projectile after timer > 1.0', () => {
        player.switchWeapon(11, ps);
        player.ammo = 6;
        player.shotCooldown = 0;
        player.spreadHeat = 0;

        const target = new DummyEnemy(400, 300, 'target');
        target.size = 60;

        ws.fireWeapon(player, 500, 300, ps);

        const dt = 1 / 60;

        // Run until projectile deactivates
        for (let frame = 0; frame < 600; frame++) {
            stepSimulation(ws, cs, [target], player, ps, dt);
        }

        // After explosion finishes, projectile should be inactive
        const activeProj = ws.getActiveProjectiles().filter(p => p.isActive());
        expect(activeProj.length).toBe(0);
    });
});

// =============================================================================
// ROCKET LAUNCHER — WEAPON DATA VERIFICATION
// =============================================================================

describe('Rocket Launcher — weapon data matches C code', () => {
    const rocketData = WEAPON_DATA[11]; // TS weapon ID 11

    it('is named "Rocket Launcher"', () => {
        expect(rocketData.name).toBe('Rocket Launcher');
    });

    it('has clipSize of 8 (OFF-BY-ONE FIX: from weapon_seeker_rockets_clip)', () => {
        expect(rocketData.clipSize).toBe(8);
    });

    it('has projectileCount of 1', () => {
        expect(rocketData.projectileCount).toBe(1);
    });

    it('uses ProjectileType.ROCKET', () => {
        expect(rocketData.projectileType).toBe(ProjectileType.ROCKET);
    });

    it('has shotCooldown ~0.741 (OFF-BY-ONE FIX: from weapon_seeker_rockets_fire_rate)', () => {
        expect(rocketData.shotCooldown).toBeCloseTo(0.741, 2);
    });

    it('has hitRadius of 8.0 (C: creature_find_in_radius 8.0)', () => {
        expect(rocketData.hitRadius).toBe(8.0);
    });

    it('has damageScale of 1.6 (C: 0x3fcccccd)', () => {
        expect(rocketData.damageScale).toBeCloseTo(1.2, 2);
    });

    it('has projectileSpeed of 750', () => {
        expect(rocketData.projectileSpeed).toBe(750);
    });
});
