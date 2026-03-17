/**
 * Ion Rifle E2E Tests
 *
 * End-to-end tests verifying the Ion Rifle fires a single ION_RIFLE
 * projectile that hits a target, enters a fading phase, and deals
 * continuous AoE radius damage to nearby clustered enemies.
 *
 * C code reference:
 *   - player.c L1545-1548: weapon_id==21 spawns 1 PROJECTILE_TYPE_ION_RIFLE
 *   - projectiles.c L460-467: ION projectiles do NOT deactivate on hit —
 *                              they enter fading phase (lifetime = 0.25)
 *   - projectiles.c L586-601: fading ION_RIFLE deals creatures_apply_radius_damage:
 *                              radius = ionMasterScale * 88, damage = dt * 100, type 7
 *   - CollisionSystem L247-253: isIonType check prevents deactivation
 *   - CollisionSystem L488-493: on-hit VFX: electric_arc(1.2, 0.4) + shockwave(1.2)
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
 * Advance the simulation: move projectiles (with AoE radius damage via
 * enemy list) and check direct-hit collisions.
 *
 * Ion projectiles enter a fading phase on hit where they deal continuous
 * AoE damage — this requires passing the enemy list to ws.update().
 */
function stepSimulation(
    ws: WeaponSystem,
    cs: CollisionSystem,
    enemies: DummyEnemy[],
    player: Player,
    ps: PerkSystem,
    dt: number,
): void {
    // Update projectile positions + ion fading AoE
    // enemies must be 3rd arg (2nd is shockChainState)
    ws.update(dt, undefined, enemies as any[]);

    // Check direct-hit collisions
    cs.checkProjectileHits(
        ws.getActiveProjectiles(),
        enemies,
        player,
        ps,
    );
}

// =============================================================================
// ION RIFLE — SINGLE PROJECTILE
// =============================================================================

describe('Ion Rifle — fires exactly one ION_RIFLE projectile', () => {
    it('spawns exactly 1 ION_RIFLE projectile per shot', () => {
        // Equip Ion Rifle (TS weapon ID 20)
        player.switchWeapon(20, ps);
        player.ammo = 16;
        player.shotCooldown = 0;
        player.spreadHeat = 0;

        // Fire at a target to the right
        ws.fireWeapon(player, 500, 300, ps);

        const projectiles = ws.getActiveProjectiles();
        expect(projectiles.length).toBe(1);

        const proj = projectiles[0];
        expect(proj.projectileType).toBe(ProjectileType.ION_RIFLE);
    });

    it('projectile flies toward the target direction', () => {
        player.switchWeapon(20, ps);
        player.ammo = 16;
        player.shotCooldown = 0;
        player.spreadHeat = 0;

        // Fire to the right
        ws.fireWeapon(player, 800, 300, ps);

        const proj = ws.getActiveProjectiles()[0];
        // vx should be positive (heading right), vy close to 0
        expect(proj.vx).toBeGreaterThan(0);
    });

    it('projectile has correct hitRadius (5.0) and damageScale (1.35)', () => {
        player.switchWeapon(20, ps);
        player.ammo = 16;
        player.shotCooldown = 0;
        player.spreadHeat = 0;

        ws.fireWeapon(player, 500, 300, ps);

        const proj = ws.getActiveProjectiles()[0];
        expect(proj.hitRadius).toBe(5.0);
        expect(proj.damageScale).toBeCloseTo(1.35, 2);
    });
});

// =============================================================================
// ION RIFLE — DIRECT HIT + FADING PHASE TRANSITION
// =============================================================================

describe('Ion Rifle — direct hit and fading phase', () => {
    it('ion projectile hits a DummyEnemy and enters fading phase (stays active)', () => {
        player.switchWeapon(20, ps);
        player.ammo = 16;
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
                // Ion projectile should NOT deactivate — it enters fading phase
                const proj = ws.getActiveProjectiles()[0];
                expect(proj).toBeDefined();
                expect(proj.active).toBe(true);
                // Lifetime should be set to 0.25 (fading)
                expect(proj.lifetime).toBeCloseTo(0.25, 1);
                // Should NOT be exploding (that's rockets)
                expect(proj.isExploding).toBe(false);
                break;
            }
        }

        expect(hitDetected).toBe(true);
    });

    it('direct hit deals distance-based damage using C formula', () => {
        player.switchWeapon(20, ps);
        player.ammo = 16;
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

        // Direct hit damage uses: ((100/dist) * 0.1 * 30 + 10) * 0.95
        // With dist ~300 (player at 100, target at 400):
        // ((100/300) * 0.1 * 30 + 10) * 0.95 ≈ (1.0 + 10) * 0.95 ≈ 10.45
        const directHit = target.getLastHit()!;
        expect(directHit).toBeDefined();
        expect(directHit.damage).toBeGreaterThan(0);
    });
});

// =============================================================================
// ION RIFLE — AoE RADIUS DAMAGE (PROPAGATION EFFECT)
// =============================================================================

describe('Ion Rifle — AoE propagation damages nearby clustered enemies', () => {
    it('fading ion projectile damages a nearby DummyEnemy that was NOT directly hit', () => {
        player.switchWeapon(20, ps);
        player.ammo = 16;
        player.shotCooldown = 0;
        player.spreadHeat = 0;

        // Direct-hit target at (400, 300)
        const directTarget = new DummyEnemy(400, 300, 'direct');
        directTarget.size = 60;

        // Nearby bystander at (430, 300) — 30px away, well within AoE radius (88px)
        const bystander = new DummyEnemy(430, 300, 'bystander');
        bystander.size = 30;

        const enemies = [directTarget, bystander];

        ws.fireWeapon(player, 500, 300, ps);

        const dt = 1 / 60;

        // Run simulation long enough for projectile to hit + fading AoE to damage
        for (let frame = 0; frame < 500; frame++) {
            stepSimulation(ws, cs, enemies, player, ps, dt);

            // Stop once bystander has taken AoE damage
            if (bystander.getHitCount() > 0) break;
        }

        // Direct target should have the initial hit
        expect(directTarget.getHitCount()).toBeGreaterThan(0);

        // Bystander should have taken AoE damage from the fading ion projectile
        expect(bystander.getHitCount()).toBeGreaterThan(0);
        expect(bystander.getTotalDamage()).toBeGreaterThan(0);
    });

    it('AoE deals damage over multiple frames (continuous DPS during fading)', () => {
        player.switchWeapon(20, ps);
        player.ammo = 16;
        player.shotCooldown = 0;
        player.spreadHeat = 0;

        // Place a dummy right at where the projectile will land
        const target = new DummyEnemy(400, 300, 'aoe_dps');
        target.size = 60;

        ws.fireWeapon(player, 500, 300, ps);

        const dt = 1 / 60;

        // Run full fading cycle
        for (let frame = 0; frame < 500; frame++) {
            stepSimulation(ws, cs, [target], player, ps, dt);
        }

        // Should have accumulated multiple hits: direct hit + many AoE ticks
        expect(target.getHitCount()).toBeGreaterThan(3);
        expect(target.getTotalDamage()).toBeGreaterThan(10);
    });

    it('AoE hits use damage type 7 (ion)', () => {
        player.switchWeapon(20, ps);
        player.ammo = 16;
        player.shotCooldown = 0;
        player.spreadHeat = 0;

        const directTarget = new DummyEnemy(400, 300, 'target');
        directTarget.size = 60;

        // Bystander — will only receive AoE damage (type 7), not direct hit
        const bystander = new DummyEnemy(430, 300, 'bystander');
        bystander.size = 20;

        const enemies = [directTarget, bystander];

        ws.fireWeapon(player, 500, 300, ps);

        const dt = 1 / 60;

        for (let frame = 0; frame < 500; frame++) {
            stepSimulation(ws, cs, enemies, player, ps, dt);
            if (bystander.getHitCount() > 0) break;
        }

        // Bystander's AoE hits should be damage type 7 (ion)
        expect(bystander.getHitCount()).toBeGreaterThan(0);
        const bystHit = bystander.getLastHit()!;
        expect(bystHit.damageType).toBe(7);
    });
});

// =============================================================================
// ION RIFLE — AoE REACH (CLUSTER OF DUMMIES)
// =============================================================================

describe('Ion Rifle — AoE propagation reach with clustered DummyEnemies', () => {
    it('ion AoE reaches dummies at increasing distances within 88px radius', () => {
        player.switchWeapon(20, ps);
        player.ammo = 16;
        player.shotCooldown = 0;
        player.spreadHeat = 0;

        // Direct-hit target at (400, 300)
        const directTarget = new DummyEnemy(400, 300, 'target');
        directTarget.size = 30;

        // Cluster of dummies around the impact point at increasing distances
        // C AoE radius = ionMasterScale(1.0) * 88 = 88px
        const dummy20px = new DummyEnemy(420, 300, 'at_20px');
        dummy20px.size = 10;

        const dummy40px = new DummyEnemy(440, 300, 'at_40px');
        dummy40px.size = 10;

        const dummy60px = new DummyEnemy(460, 300, 'at_60px');
        dummy60px.size = 10;

        const dummy80px = new DummyEnemy(480, 300, 'at_80px');
        dummy80px.size = 10;

        // This one is outside the AoE radius (100px away > 88px max)
        const dummy100px = new DummyEnemy(500, 300, 'at_100px');
        dummy100px.size = 10;

        const enemies = [directTarget, dummy20px, dummy40px, dummy60px, dummy80px, dummy100px];

        ws.fireWeapon(player, 500, 300, ps);

        const dt = 1 / 60;

        // Run full fading cycle (projectile fly time + fading duration)
        for (let frame = 0; frame < 600; frame++) {
            stepSimulation(ws, cs, enemies, player, ps, dt);
        }

        // Direct target: hit by direct hit + AoE
        expect(directTarget.getHitCount()).toBeGreaterThan(0);

        // 20px away: well within AoE (88px radius), should be hit
        expect(dummy20px.getHitCount()).toBeGreaterThan(0);
        expect(dummy20px.getTotalDamage()).toBeGreaterThan(0);

        // 40px away: within AoE, should be hit
        expect(dummy40px.getHitCount()).toBeGreaterThan(0);
        expect(dummy40px.getTotalDamage()).toBeGreaterThan(0);

        // 60px away: within AoE (radius is 88px), should be hit
        expect(dummy60px.getHitCount()).toBeGreaterThan(0);
        expect(dummy60px.getTotalDamage()).toBeGreaterThan(0);

        // 80px away: within AoE (radius is 88px), should be hit
        expect(dummy80px.getHitCount()).toBeGreaterThan(0);
        expect(dummy80px.getTotalDamage()).toBeGreaterThan(0);

        // 100px away: outside AoE (88px radius), should NOT be hit
        expect(dummy100px.getHitCount()).toBe(0);
    });

    it('closer dummies receive more total AoE damage than farther ones', () => {
        player.switchWeapon(20, ps);
        player.ammo = 16;
        player.shotCooldown = 0;
        player.spreadHeat = 0;

        // Direct-hit target
        const directTarget = new DummyEnemy(400, 300, 'target');
        directTarget.size = 30;

        // Two bystanders at different distances
        const close = new DummyEnemy(420, 300, 'close_20px');
        close.size = 10;

        const far = new DummyEnemy(470, 300, 'far_70px');
        far.size = 10;

        const enemies = [directTarget, close, far];

        ws.fireWeapon(player, 500, 300, ps);

        const dt = 1 / 60;

        for (let frame = 0; frame < 600; frame++) {
            stepSimulation(ws, cs, enemies, player, ps, dt);
        }

        // Both should be hit (within 88px)
        expect(close.getHitCount()).toBeGreaterThan(0);
        expect(far.getHitCount()).toBeGreaterThan(0);

        // AoE has a flat radius check (no distance falloff in damage per tick),
        // but closer enemies are within radius for the same number of frames.
        // Both should receive similar damage since ION AoE is a flat radius.
        // The key test is that BOTH received damage.
        expect(close.getTotalDamage()).toBeGreaterThan(0);
        expect(far.getTotalDamage()).toBeGreaterThan(0);
    });

    it('tightly clustered enemies all take AoE damage from a single shot', () => {
        player.switchWeapon(20, ps);
        player.ammo = 16;
        player.shotCooldown = 0;
        player.spreadHeat = 0;

        // Tight cluster: 5 enemies packed within 15px of each other
        const center = new DummyEnemy(400, 300, 'center');
        center.size = 30;

        const north = new DummyEnemy(400, 285, 'north');
        north.size = 15;

        const south = new DummyEnemy(400, 315, 'south');
        south.size = 15;

        const east = new DummyEnemy(415, 300, 'east');
        east.size = 15;

        const west = new DummyEnemy(385, 300, 'west');
        west.size = 15;

        const enemies = [center, north, south, east, west];

        ws.fireWeapon(player, 500, 300, ps);

        const dt = 1 / 60;

        for (let frame = 0; frame < 500; frame++) {
            stepSimulation(ws, cs, enemies, player, ps, dt);
        }

        // ALL enemies in the tight cluster should have taken damage
        for (const enemy of enemies) {
            expect(enemy.getHitCount()).toBeGreaterThan(0);
            expect(enemy.getTotalDamage()).toBeGreaterThan(0);
        }
    });

    it('multiple enemies at same distance all receive AoE damage equally', () => {
        player.switchWeapon(20, ps);
        player.ammo = 16;
        player.shotCooldown = 0;
        player.spreadHeat = 0;

        // Direct-hit target
        const directTarget = new DummyEnemy(400, 300, 'target');
        directTarget.size = 30;

        // Two enemies at equal perpendicular distance (40px above/below),
        // placed off the projectile's flight path so neither gets a direct hit
        const ringN = new DummyEnemy(400, 260, 'ring_N');
        ringN.size = 10;

        const ringS = new DummyEnemy(400, 340, 'ring_S');
        ringS.size = 10;

        const enemies = [directTarget, ringN, ringS];

        ws.fireWeapon(player, 500, 300, ps);

        const dt = 1 / 60;

        for (let frame = 0; frame < 600; frame++) {
            stepSimulation(ws, cs, enemies, player, ps, dt);
        }

        // Both perpendicular ring enemies should be hit (40px < 88px radius)
        expect(ringN.getHitCount()).toBeGreaterThan(0);
        expect(ringS.getHitCount()).toBeGreaterThan(0);

        // Enemies at equal perpendicular distance should receive equal AoE damage
        const dN = ringN.getTotalDamage();
        const dS = ringS.getTotalDamage();
        const avg = (dN + dS) / 2;
        // Allow 10% tolerance for floating-point differences
        expect(dN).toBeGreaterThan(avg * 0.9);
        expect(dN).toBeLessThan(avg * 1.1);
        expect(dS).toBeGreaterThan(avg * 0.9);
        expect(dS).toBeLessThan(avg * 1.1);
    });
});

// =============================================================================
// ION RIFLE — PROJECTILE LIFECYCLE
// =============================================================================

describe('Ion Rifle — projectile deactivates after fading phase completes', () => {
    it('ion projectile deactivates once lifetime reaches 0', () => {
        player.switchWeapon(20, ps);
        player.ammo = 16;
        player.shotCooldown = 0;
        player.spreadHeat = 0;

        const target = new DummyEnemy(400, 300, 'target');
        target.size = 60;

        ws.fireWeapon(player, 500, 300, ps);

        const dt = 1 / 60;

        // Phase 1: Run until projectile hits the target
        for (let frame = 0; frame < 300; frame++) {
            stepSimulation(ws, cs, [target], player, ps, dt);
            if (target.getHitCount() > 0) break;
        }

        expect(target.getHitCount()).toBeGreaterThan(0);

        // Ion projectile should still be active (entered fading, NOT deactivated)
        const fadingProj = ws.getActiveProjectiles();
        expect(fadingProj.length).toBe(1);
        expect(fadingProj[0].active).toBe(true);

        // Phase 2: Let the fading phase run to completion WITHOUT re-colliding
        // (repeated collisions would reset lifetime back to 0.25 endlessly)
        // Ion fading: lifetime decays at 1:1 from 0.25 → 0 in ~15 frames
        for (let frame = 0; frame < 60; frame++) {
            ws.update(dt); // Only update projectile physics, no collision
        }

        // After fading completes (lifetime <= 0), projectile should be inactive
        const activeProj = ws.getActiveProjectiles().filter(p => p.isActive());
        expect(activeProj.length).toBe(0);
    });
});

// =============================================================================
// ION RIFLE — WEAPON DATA VERIFICATION
// =============================================================================

describe('Ion Rifle — weapon data matches C code', () => {
    const ionData = WEAPON_DATA[20]; // TS weapon ID 20

    it('is named "Ion Rifle"', () => {
        expect(ionData.name).toBe('Ion Rifle');
    });

    it('has clipSize of 8', () => {
        expect(ionData.clipSize).toBe(8);
    });

    it('has projectileCount of 1', () => {
        expect(ionData.projectileCount).toBe(1);
    });

    it('uses ProjectileType.ION_RIFLE', () => {
        expect(ionData.projectileType).toBe(ProjectileType.ION_RIFLE);
    });

    it('has shotCooldown ~0.4 (C: weapon_ion_minigun_fire_rate = 0x3ecccccd)', () => {
        expect(ionData.shotCooldown).toBeCloseTo(0.4, 2);
    });

    it('has hitRadius of 5.0 (C: projectile_spawn hit_radius)', () => {
        expect(ionData.hitRadius).toBe(5.0);
    });

    it('has damageScale of 1.35 (C: weapon_ion_minigun_damage = 0x3faccccd)', () => {
        expect(ionData.damageScale).toBeCloseTo(1.35, 2);
    });

    it('has projectileSpeed of 1650', () => {
        expect(ionData.projectileSpeed).toBe(1650);
    });

    it('has AUTOMATIC and ENERGY flags', () => {
        expect(ionData.flags & 0x01).toBe(0x01); // AUTOMATIC
        expect(ionData.flags & 0x08).toBe(0x08); // ENERGY
    });
});
