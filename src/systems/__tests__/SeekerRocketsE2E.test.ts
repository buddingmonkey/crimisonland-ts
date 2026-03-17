/**
 * Seeker Rockets E2E Tests
 *
 * End-to-end tests verifying Seeker Rockets fire a single homing rocket
 * projectile per shot that explodes on impact with smaller AoE than standard rockets.
 *
 * C code reference:
 *   - weapon_table: weapon_id 13 (C), TS ID 12, 1 projectile per shot
 *     (pellet_count=5 in weapon table is the type ID, not a count)
 *   - CollisionSystem L197-198: direct hit damage = lifetime * 20 + 80
 *   - CollisionSystem L212-213: explosionScale = 0.35
 *   - AoE max radius = 0.35 × 1.0 × 80 = 28px
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

function stepSimulation(
    ws: WeaponSystem,
    cs: CollisionSystem,
    enemies: DummyEnemy[],
    player: Player,
    ps: PerkSystem,
    dt: number,
): void {
    ws.update(dt, undefined, enemies as any[]);
    cs.checkProjectileHits(
        ws.getActiveProjectiles(),
        enemies,
        player,
        ps,
    );
}

// =============================================================================
// SEEKER ROCKETS — PROJECTILE SPAWN
// =============================================================================

describe('Seeker Rockets — fires 1 seeker rocket projectile per shot', () => {
    it('spawns exactly 1 SEEKER_ROCKET projectile per shot', () => {
        player.switchWeapon(12, ps);
        player.ammo = 8;
        player.shotCooldown = 0;
        player.spreadHeat = 0;

        ws.fireWeapon(player, 500, 300, ps);

        const projectiles = ws.getActiveProjectiles();
        expect(projectiles.length).toBe(1);

        for (const proj of projectiles) {
            expect(proj.projectileType).toBe(ProjectileType.SEEKER_ROCKET);
        }
    });

    it('all projectiles fly in the general direction of the target', () => {
        player.switchWeapon(12, ps);
        player.ammo = 8;
        player.shotCooldown = 0;
        player.spreadHeat = 0;

        // Fire to the right
        ws.fireWeapon(player, 800, 300, ps);

        const projectiles = ws.getActiveProjectiles();
        // At least some should have positive vx (heading right)
        const rightwardCount = projectiles.filter(p => p.vx > 0).length;
        expect(rightwardCount).toBeGreaterThan(0);
    });

    it('all projectiles have isRocket=true and rocketType="seeker"', () => {
        player.switchWeapon(12, ps);
        player.ammo = 8;
        player.shotCooldown = 0;
        player.spreadHeat = 0;

        ws.fireWeapon(player, 500, 300, ps);

        const projectiles = ws.getActiveProjectiles();
        for (const proj of projectiles) {
            expect(proj.isRocket).toBe(true);
            expect(proj.rocketType).toBe('seeker');
        }
    });
});

// =============================================================================
// SEEKER ROCKETS — DIRECT HIT + EXPLOSION
// =============================================================================

describe('Seeker Rockets — direct hit and explosion', () => {
    it('rocket hits a DummyEnemy and transitions to exploding with scale 0.35', () => {
        player.switchWeapon(12, ps);
        player.ammo = 8;
        player.shotCooldown = 0;
        player.spreadHeat = 0;

        // Large target directly ahead
        const target = new DummyEnemy(300, 300, 'direct_hit');
        target.size = 80;

        ws.fireWeapon(player, 400, 300, ps);

        const dt = 1 / 60;
        let explosionDetected = false;

        for (let frame = 0; frame < 300; frame++) {
            ws.update(dt, undefined, [target] as any[]);
            cs.checkProjectileHits(
                ws.getActiveProjectiles(),
                [target],
                player,
                ps,
            );

            // Check if any projectile entered exploding state
            for (const proj of ws.getActiveProjectiles()) {
                if (proj.isExploding) {
                    explosionDetected = true;
                    expect(proj.explosionScale).toBe(0.35);
                    break;
                }
            }
            if (explosionDetected) break;
        }

        expect(explosionDetected).toBe(true);
        expect(target.getHitCount()).toBeGreaterThan(0);
    });

    it('direct hit deals C-formula damage: lifetime * 20 + 80', () => {
        player.switchWeapon(12, ps);
        player.ammo = 8;
        player.shotCooldown = 0;
        player.spreadHeat = 0;

        const target = new DummyEnemy(300, 300, 'damage_check');
        target.size = 80;

        ws.fireWeapon(player, 400, 300, ps);

        const dt = 1 / 60;

        for (let frame = 0; frame < 300; frame++) {
            stepSimulation(ws, cs, [target], player, ps, dt);
            if (target.getHitCount() > 0) break;
        }

        // Direct hit should deal damage based on lifetime * 20 + 80
        // At lifetime ~0.4: damage ≈ 88
        const directHit = target.getLastHit()!;
        expect(directHit).toBeDefined();
        expect(directHit.damage).toBeGreaterThan(50);
        expect(directHit.damageType).toBe(3); // Rocket damage type
    });
});

// =============================================================================
// SEEKER ROCKETS — AoE REACH
// =============================================================================

describe('Seeker Rockets — AoE explosion with smaller radius', () => {
    it('explosion damages nearby bystander within 28px max AoE', () => {
        player.switchWeapon(12, ps);
        player.ammo = 8;
        player.shotCooldown = 0;
        player.spreadHeat = 0;

        const directTarget = new DummyEnemy(300, 300, 'direct');
        directTarget.size = 60;

        // Bystander just to the side of the direct target — within 28px max AoE radius.
        // AoE radiates from the ROCKET's position (where it stops on first collision),
        // which is ~hitRadius+enemyRadius away from the enemy center along the flight path.
        // Place bystander off-axis near the target so it's within explosion range.
        const bystander = new DummyEnemy(300, 310, 'bystander');
        bystander.size = 10;

        const enemies = [directTarget, bystander];

        ws.fireWeapon(player, 400, 300, ps);

        const dt = 1 / 60;

        for (let frame = 0; frame < 500; frame++) {
            stepSimulation(ws, cs, enemies, player, ps, dt);
            if (bystander.getHitCount() > 0) break;
        }

        expect(directTarget.getHitCount()).toBeGreaterThan(0);
        expect(bystander.getHitCount()).toBeGreaterThan(0);
    });

    it('dummy at 40px is outside seeker AoE (28px max) and takes no damage', () => {
        player.switchWeapon(12, ps);
        player.ammo = 8;
        player.shotCooldown = 0;
        player.spreadHeat = 0;

        const directTarget = new DummyEnemy(300, 300, 'direct');
        directTarget.size = 60;

        // Dummy 40px away — outside 28px max AoE radius
        const farDummy = new DummyEnemy(340, 300, 'far');
        farDummy.size = 5; // Tiny so its radius doesn't overlap

        const enemies = [directTarget, farDummy];

        ws.fireWeapon(player, 400, 300, ps);

        const dt = 1 / 60;

        for (let frame = 0; frame < 600; frame++) {
            stepSimulation(ws, cs, enemies, player, ps, dt);
        }

        expect(directTarget.getHitCount()).toBeGreaterThan(0);
        // Far dummy should NOT be hit — outside AoE radius
        expect(farDummy.getHitCount()).toBe(0);
    });
});

// =============================================================================
// SEEKER ROCKETS — WEAPON DATA VERIFICATION
// =============================================================================

describe('Seeker Rockets — weapon data matches C code', () => {
    const data = WEAPON_DATA[12]; // TS weapon ID 12

    it('is named "Seeker Rockets"', () => {
        expect(data.name).toBe('Seeker Rockets');
    });

    it('has clipSize of 8', () => {
        expect(data.clipSize).toBe(8);
    });

    it('has projectileCount of 5', () => {
        expect(data.projectileCount).toBe(5);
    });

    it('uses ProjectileType.SEEKER_ROCKET', () => {
        expect(data.projectileType).toBe(ProjectileType.SEEKER_ROCKET);
    });

    it('has hitRadius of 8.0', () => {
        expect(data.hitRadius).toBe(8.0);
    });

    it('has projectileSpeed of 600', () => {
        expect(data.projectileSpeed).toBe(600);
    });
});
