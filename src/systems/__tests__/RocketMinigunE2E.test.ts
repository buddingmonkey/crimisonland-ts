/**
 * Rocket Minigun E2E Tests
 *
 * End-to-end tests verifying the Rocket Minigun fires a single rocket
 * per shot with a smaller explosion than standard rockets.
 *
 * C code reference:
 *   - player.c lines 1709-1724: weapon_id 18 (C), TS ID 18
 *   - Dedicated handler fires 1 rocket (overrides pellet_count=8)
 *   - Uses spawnProjectileTyped → initRocketProps → isRocket=true
 *   - CollisionSystem L199-200: direct hit = lifetime * 20 + 40
 *   - CollisionSystem L214-215: explosionScale = 0.25
 *   - AoE max radius = 0.25 × 1.0 × 80 = 20px
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
// ROCKET MINIGUN — SINGLE PROJECTILE
// =============================================================================

describe('Rocket Minigun — fires exactly one rocket per shot', () => {
    it('spawns exactly 1 ROCKET_MINIGUN projectile per shot', () => {
        player.switchWeapon(18, ps);
        player.ammo = 5;
        player.shotCooldown = 0;
        player.spreadHeat = 0;

        ws.fireWeapon(player, 500, 300, ps);

        const projectiles = ws.getActiveProjectiles();
        expect(projectiles.length).toBe(1);

        const proj = projectiles[0];
        expect(proj.projectileType).toBe(ProjectileType.ROCKET_MINIGUN);
    });

    it('has isRocket=true and rocketType="minigun" (dedicated handler)', () => {
        player.switchWeapon(18, ps);
        player.ammo = 5;
        player.shotCooldown = 0;
        player.spreadHeat = 0;

        ws.fireWeapon(player, 500, 300, ps);

        const proj = ws.getActiveProjectiles()[0];
        expect(proj.isRocket).toBe(true);
        expect(proj.rocketType).toBe('minigun');
    });

    it('rocket projectile flies toward the target', () => {
        player.switchWeapon(18, ps);
        player.ammo = 5;
        player.shotCooldown = 0;
        player.spreadHeat = 0;

        ws.fireWeapon(player, 800, 300, ps);

        const proj = ws.getActiveProjectiles()[0];
        expect(proj.vx).toBeGreaterThan(0);
    });
});

// =============================================================================
// ROCKET MINIGUN — DIRECT HIT + EXPLOSION
// =============================================================================

describe('Rocket Minigun — direct hit and explosion', () => {
    it('rocket hits a DummyEnemy and transitions to exploding with scale 0.25', () => {
        player.switchWeapon(18, ps);
        player.ammo = 5;
        player.shotCooldown = 0;
        player.spreadHeat = 0;

        const target = new DummyEnemy(400, 300, 'direct_hit');
        target.size = 60;

        ws.fireWeapon(player, 500, 300, ps);

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

            for (const proj of ws.getActiveProjectiles()) {
                if (proj.isExploding) {
                    explosionDetected = true;
                    expect(proj.explosionScale).toBe(0.25);
                    break;
                }
            }
            if (explosionDetected) break;
        }

        expect(explosionDetected).toBe(true);
        expect(target.getHitCount()).toBeGreaterThan(0);
    });

    it('direct hit deals C-formula damage: lifetime * 20 + 40', () => {
        player.switchWeapon(18, ps);
        player.ammo = 5;
        player.shotCooldown = 0;
        player.spreadHeat = 0;

        const target = new DummyEnemy(400, 300, 'damage_check');
        target.size = 60;

        ws.fireWeapon(player, 500, 300, ps);

        const dt = 1 / 60;

        for (let frame = 0; frame < 300; frame++) {
            stepSimulation(ws, cs, [target], player, ps, dt);
            if (target.getHitCount() > 0) break;
        }

        // Direct hit at lifetime ~0.4: damage ≈ 0.4*20+40 = 48
        const directHit = target.getLastHit()!;
        expect(directHit).toBeDefined();
        expect(directHit.damage).toBeGreaterThan(30);
        expect(directHit.damageType).toBe(3); // Rocket damage type
    });
});

// =============================================================================
// ROCKET MINIGUN — AoE REACH (SMALL RADIUS)
// =============================================================================

describe('Rocket Minigun — AoE explosion with smallest radius', () => {
    it('explosion damages bystander within 20px max AoE', () => {
        player.switchWeapon(18, ps);
        player.ammo = 5;
        player.shotCooldown = 0;
        player.spreadHeat = 0;

        // Small target so rocket hits close to its center
        const directTarget = new DummyEnemy(400, 300, 'direct');
        directTarget.size = 20;

        // Bystander overlapping the target position — well within 20px AoE
        const bystander = new DummyEnemy(400, 310, 'bystander');
        bystander.size = 10;

        const enemies = [directTarget, bystander];

        ws.fireWeapon(player, 500, 300, ps);

        const dt = 1 / 60;

        for (let frame = 0; frame < 500; frame++) {
            stepSimulation(ws, cs, enemies, player, ps, dt);
            if (bystander.getHitCount() > 0) break;
        }

        expect(directTarget.getHitCount()).toBeGreaterThan(0);
        expect(bystander.getHitCount()).toBeGreaterThan(0);
    });

    it('dummy at 30px is outside minigun AoE (20px max) and takes no damage', () => {
        player.switchWeapon(18, ps);
        player.ammo = 5;
        player.shotCooldown = 0;
        player.spreadHeat = 0;

        const directTarget = new DummyEnemy(400, 300, 'direct');
        directTarget.size = 60;

        // Dummy 30px away — outside 20px max AoE radius
        const farDummy = new DummyEnemy(430, 300, 'far');
        farDummy.size = 5; // Tiny so its radius doesn't overlap

        const enemies = [directTarget, farDummy];

        ws.fireWeapon(player, 500, 300, ps);

        const dt = 1 / 60;

        for (let frame = 0; frame < 600; frame++) {
            stepSimulation(ws, cs, enemies, player, ps, dt);
        }

        expect(directTarget.getHitCount()).toBeGreaterThan(0);
        expect(farDummy.getHitCount()).toBe(0);
    });

    it('minigun AoE is smaller than standard rocket AoE', () => {
        // Standard rocket: explosionScale=1.0, max radius=80px
        // Rocket minigun: explosionScale=0.25, max radius=20px
        // Verify by placing dummy at 25px — should NOT be hit by minigun

        player.switchWeapon(18, ps);
        player.ammo = 5;
        player.shotCooldown = 0;
        player.spreadHeat = 0;

        const directTarget = new DummyEnemy(400, 300, 'direct');
        directTarget.size = 60;

        const at25px = new DummyEnemy(425, 300, 'at_25px');
        at25px.size = 5;

        const enemies = [directTarget, at25px];

        ws.fireWeapon(player, 500, 300, ps);

        const dt = 1 / 60;

        for (let frame = 0; frame < 600; frame++) {
            stepSimulation(ws, cs, enemies, player, ps, dt);
        }

        expect(directTarget.getHitCount()).toBeGreaterThan(0);
        // 25px > 20px max AoE — should NOT be damaged
        expect(at25px.getHitCount()).toBe(0);
    });
});

// =============================================================================
// ROCKET MINIGUN — WEAPON DATA VERIFICATION
// =============================================================================

describe('Rocket Minigun — weapon data matches C code', () => {
    const data = WEAPON_DATA[18]; // TS weapon ID 18

    it('is named "Rocket Minigun"', () => {
        expect(data.name).toBe('Rocket Minigun');
    });

    it('has clipSize of 16', () => {
        expect(data.clipSize).toBe(16);
    });

    it('has projectileCount of 1 (dedicated handler fires 1)', () => {
        expect(data.projectileCount).toBe(1);
    });

    it('uses ProjectileType.ROCKET_MINIGUN', () => {
        expect(data.projectileType).toBe(ProjectileType.ROCKET_MINIGUN);
    });

    it('has shotCooldown ~0.12 (C: 0x3df5c28f at struct offset 0x4C)', () => {
        expect(data.shotCooldown).toBeCloseTo(0.12, 2);
    });

    it('has hitRadius of 8.0', () => {
        expect(data.hitRadius).toBe(8.0);
    });

    it('has damageScale of 1.8', () => {
        expect(data.damageScale).toBeCloseTo(1.8, 2);
    });

    it('has projectileSpeed of 660', () => {
        expect(data.projectileSpeed).toBe(660);
    });
});
