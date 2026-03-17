/**
 * Mini Rocket Swarmers E2E Tests
 *
 * End-to-end tests verifying Mini Rocket Swarmers fire a fan of seeker
 * rockets equal to the current ammo count, consuming all ammo.
 *
 * C code reference:
 *   - player.c lines 1672-1708: weapon_id 17 (C), TS ID 17
 *   - Fan of seeker rockets across 60° arc (1.0471976 rad)
 *   - All ammo consumed on fire
 *   - Uses initRocketProps → isRocket=true, rocketType='seeker'
 *   - Explosion scale 0.35, direct hit = lifetime * 20 + 80
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
// MINI ROCKET SWARMERS — PROJECTILE SPAWN
// =============================================================================

describe('Mini Rocket Swarmers — fires a fan of seeker rockets', () => {
    it('spawns rockets equal to current ammo count', () => {
        player.switchWeapon(17, ps);
        player.ammo = 10;
        player.shotCooldown = 0;
        player.spreadHeat = 0;

        ws.fireWeapon(player, 500, 300, ps);

        const projectiles = ws.getActiveProjectiles();
        expect(projectiles.length).toBe(10);

        for (const proj of projectiles) {
            expect(proj.projectileType).toBe(ProjectileType.SEEKER_ROCKET);
        }
    });

    it('consumes ALL ammo on fire', () => {
        player.switchWeapon(17, ps);
        player.ammo = 15;
        player.shotCooldown = 0;
        player.spreadHeat = 0;

        ws.fireWeapon(player, 500, 300, ps);

        expect(player.ammo).toBe(0);
    });

    it('all rockets have isRocket=true and rocketType="seeker" (dedicated handler)', () => {
        player.switchWeapon(17, ps);
        player.ammo = 5;
        player.shotCooldown = 0;
        player.spreadHeat = 0;

        ws.fireWeapon(player, 500, 300, ps);

        const projectiles = ws.getActiveProjectiles();
        for (const proj of projectiles) {
            expect(proj.isRocket).toBe(true);
            expect(proj.rocketType).toBe('seeker');
        }
    });

    it('rockets fan out across an arc (not all heading the same direction)', () => {
        player.switchWeapon(17, ps);
        player.ammo = 8;
        player.shotCooldown = 0;
        player.spreadHeat = 0;

        ws.fireWeapon(player, 500, 300, ps);

        const projectiles = ws.getActiveProjectiles();
        const angles = projectiles.map(p => Math.atan2(p.vy, p.vx));

        // With 8 rockets across a 60° arc, there should be angular diversity
        const minAngle = Math.min(...angles);
        const maxAngle = Math.max(...angles);
        const spread = maxAngle - minAngle;

        // Should span at least some arc (> 10° = 0.17 rad)
        expect(spread).toBeGreaterThan(0.17);
    });
});

// =============================================================================
// MINI ROCKET SWARMERS — DIRECT HIT + EXPLOSION
// =============================================================================

describe('Mini Rocket Swarmers — direct hit and explosion', () => {
    it('rockets hit a DummyEnemy and explode with scale 0.35', () => {
        player.switchWeapon(17, ps);
        player.ammo = 5;
        player.shotCooldown = 0;
        player.spreadHeat = 0;

        // Swarmers fire BACKWARD (baseAngle - PI) then home in.
        // Place a very large target close to the player so rockets
        // collide before lifetime expires (which would give scale 0.5).
        const target = new DummyEnemy(150, 300, 'target');
        target.size = 200;

        ws.fireWeapon(player, 500, 300, ps);

        const dt = 1 / 60;
        let explosionDetected = false;

        for (let frame = 0; frame < 600; frame++) {
            ws.update(dt, undefined, [target] as any[]);
            cs.checkProjectileHits(
                ws.getActiveProjectiles(),
                [target],
                player,
                ps,
            );

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

    it('multiple rockets can hit the same target for stacking damage', () => {
        player.switchWeapon(17, ps);
        player.ammo = 8;
        player.shotCooldown = 0;
        player.spreadHeat = 0;

        // Very large target close to player to catch backward-firing rockets
        const target = new DummyEnemy(150, 300, 'target');
        target.size = 300;

        ws.fireWeapon(player, 500, 300, ps);

        const dt = 1 / 60;

        for (let frame = 0; frame < 600; frame++) {
            stepSimulation(ws, cs, [target], player, ps, dt);
        }

        // Multiple rockets should have hit, dealing significant stacked damage
        expect(target.getHitCount()).toBeGreaterThan(1);
        expect(target.getTotalDamage()).toBeGreaterThan(100);
    });
});

// =============================================================================
// MINI ROCKET SWARMERS — AoE
// =============================================================================

describe('Mini Rocket Swarmers — AoE explosion', () => {
    it('rocket explosion damages a nearby bystander via AoE', () => {
        player.switchWeapon(17, ps);
        player.ammo = 5;
        player.shotCooldown = 0;
        player.spreadHeat = 0;

        // Place target close to player with moderate size so rockets collide
        const directTarget = new DummyEnemy(130, 300, 'direct');
        directTarget.size = 80;

        // Bystander near explosion center but outside direct collision zone
        // Direct target collision zone: center(130,300) + hitRadius(8) + enemyRadius(40) = 48px
        // Bystander at (130, 320) is 20px from center — within 28px seeker AoE
        const bystander = new DummyEnemy(130, 320, 'bystander');
        bystander.size = 5;

        const enemies = [directTarget, bystander];

        ws.fireWeapon(player, 500, 300, ps);

        const dt = 1 / 60;

        for (let frame = 0; frame < 600; frame++) {
            stepSimulation(ws, cs, enemies, player, ps, dt);
        }

        expect(directTarget.getHitCount()).toBeGreaterThan(0);
        // Bystander should receive AoE damage from explosion
        expect(bystander.getHitCount()).toBeGreaterThan(0);
    });
});

// =============================================================================
// MINI ROCKET SWARMERS — WEAPON DATA VERIFICATION
// =============================================================================

describe('Mini Rocket Swarmers — weapon data matches C code', () => {
    const data = WEAPON_DATA[17]; // TS weapon ID 17

    it('is named "Mini Rocket Swarmers"', () => {
        expect(data.name).toBe('Mini Rocket Swarmers');
    });

    it('has clipSize of 5', () => {
        expect(data.clipSize).toBe(5);
    });

    it('uses ProjectileType.SEEKER_ROCKET', () => {
        expect(data.projectileType).toBe(ProjectileType.SEEKER_ROCKET);
    });

    it('has projectileSpeed of 540', () => {
        expect(data.projectileSpeed).toBe(540);
    });

    it('has ammoClass 2 (rocket)', () => {
        expect(data.ammoClass).toBe(2);
    });
});
