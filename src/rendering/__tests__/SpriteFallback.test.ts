/**
 * SpriteFallback.test.ts — Verify sprite rendering paths are used (not debug fallbacks)
 *
 * These tests ensure that when sprite textures are loaded, the rendering code
 * uses proper sprite/texture-based rendering (drawQuad + bindTexture) and does
 * NOT fall back to primitive debug rendering (drawCircleFilled, drawLine).
 *
 * Each test sets up a mock GrimInterface that records all draw calls, then
 * invokes the render function with sprites marked as loaded, and asserts that
 * no drawCircleFilled calls were made (the universal fallback indicator).
 */

import { describe, it, expect, beforeEach } from 'vitest';
import { SpriteRenderer } from '../SpriteRenderer';
import { GrimInterface } from '../../engine/GrimInterface';
import { renderPlayer, type PlayerRenderContext } from '../../entities/PlayerRenderer';
import { Enemy, EnemyType } from '../../entities/Enemy';
import { Projectile } from '../../entities/Projectile';
import { Bonus, BonusType } from '../../entities/Bonus';
import { BonusSystem } from '../../systems/bonus/BonusSystem';
import { ProjectileType } from '../../data/WeaponData';
import { drawProjectile, type ProjectileTextureContext } from '../ProjectileRenderer';

// ============================================================
// Mock GrimInterface that records all draw calls
// ============================================================

interface DrawCall {
    method: string;
    args: any[];
}

function createMockGrim(): GrimInterface & { drawCalls: DrawCall[] } {
    const drawCalls: DrawCall[] = [];

    const record =
        (method: string) =>
            (...args: any[]) => {
                drawCalls.push({ method, args });
            };

    const noop = () => { };
    const noopReturn = (val: any) => () => val;

    const mock: any = {
        drawCalls,

        // Drawing methods we track
        drawCircleFilled: record('drawCircleFilled'),
        drawCircleOutline: record('drawCircleOutline'),
        drawRectFilled: record('drawRectFilled'),
        drawLine: record('drawLine'),
        drawQuad: record('drawQuad'),
        drawQuadPoints: record('drawQuadPoints'),
        drawText: record('drawText'),

        // State methods (no-ops that we track)
        setColor: record('setColor'),
        setRotation: record('setRotation'),
        setUV: record('setUV'),
        setAtlasFrame: record('setAtlasFrame'),
        bindTexture: record('bindTexture'),
        setBlendMode: record('setBlendMode'),
        setSubRect: record('setSubRect'),
        setCameraOffset: noop,
        setGraphicsLayer: noop,

        // Getters
        getWidth: noopReturn(800),
        getHeight: noopReturn(600),
        getTime: noopReturn(1000),
        getDeltaTime: noopReturn(16),
        getMouseX: noopReturn(400),
        getMouseY: noopReturn(300),
        getFPS: noopReturn(60),
        getRenderer: noopReturn(null),

        // Texture management
        registerTexture: (_name: string, _tex: any) => 1,
        createTexture: () => 1,
        loadTexture: async () => 1,

        // Input (not needed for rendering tests)
        isMouseButtonDown: noopReturn(false),
        isMouseButtonPressed: noopReturn(false),
        isKeyDown: noopReturn(false),
        isKeyPressed: noopReturn(false),
        getKeyChars: noopReturn([]),
        getMouseDeltaX: noopReturn(0),
        getMouseDeltaY: noopReturn(0),
        setMousePosition: noop,
        flushInput: noop,

        // Lifecycle
        init: async () => true,
        destroy: noop,
        shutdown: noop,
        beginFrame: noop,
        endFrame: noop,
    };

    return mock;
}

// ============================================================
// Helper: check that no drawCircleFilled calls were made
// ============================================================

function getCircleCalls(grim: { drawCalls: DrawCall[] }): DrawCall[] {
    return grim.drawCalls.filter((c) => c.method === 'drawCircleFilled');
}

function getQuadCalls(grim: { drawCalls: DrawCall[] }): DrawCall[] {
    return grim.drawCalls.filter((c) => c.method === 'drawQuad' || c.method === 'drawQuadPoints');
}

function getBindTextureCalls(grim: { drawCalls: DrawCall[] }): DrawCall[] {
    return grim.drawCalls.filter((c) => c.method === 'bindTexture');
}

function getLineCalls(grim: { drawCalls: DrawCall[] }): DrawCall[] {
    return grim.drawCalls.filter((c) => c.method === 'drawLine');
}

// ============================================================
// Helper: create a SpriteRenderer with all sprites "loaded"
// ============================================================

function createLoadedSpriteRenderer(): SpriteRenderer {
    const renderer = new SpriteRenderer();

    // Force all sprite flags to true (bypassing async asset loading)
    (renderer as any).hasPlayerSprite = true;
    (renderer as any).hasEnemySprite = true;
    (renderer as any).hasBodysetSprite = true;
    (renderer as any).hasProjectileSprite = true;
    (renderer as any).hasParticlesSprite = true;
    (renderer as any).hasMuzzleFlashSprite = true;
    (renderer as any).hasBulletTrailSprite = true;
    (renderer as any).hasBulletHeadSprite = true;
    (renderer as any).hasBonusSprite = true;
    (renderer as any).hasWeaponIconSprite = true;
    (renderer as any).loaded = true;

    // Set texture handles to valid values
    (renderer as any).playerHandle = 1;
    (renderer as any).bodysetHandle = 2;
    (renderer as any).projectileHandle = 3;
    (renderer as any).particlesHandle = 4;
    (renderer as any).muzzleFlashHandle = 9;
    (renderer as any).bulletTrailHandle = 5;
    (renderer as any).bulletHeadHandle = 6;
    (renderer as any).bonusHandle = 7;
    (renderer as any).weaponIconHandle = 8;

    // Set per-type enemy texture handles
    const enemyTextureHandles = new Map<string, number>();
    enemyTextureHandles.set('game/zombie.jaz', 10);
    enemyTextureHandles.set('game/lizard.jaz', 11);
    enemyTextureHandles.set('game/spider_sp1.jaz', 12);
    enemyTextureHandles.set('game/spider_sp2.jaz', 13);
    enemyTextureHandles.set('game/alien.jaz', 14);
    enemyTextureHandles.set('game/trooper.jaz', 15);
    (renderer as any).enemyTextureHandles = enemyTextureHandles;

    return renderer;
}

// ============================================================
// Helper: create a PlayerRenderContext
// ============================================================

function createPlayerContext(overrides: Partial<PlayerRenderContext> = {}): PlayerRenderContext {
    return {
        x: 400,
        y: 300,
        angle: 0,
        heading: 0,
        radius: 15,
        size: 48,
        dx: 0,
        dy: 0,
        health: 100,
        maxHealth: 100,
        shieldTimer: 0,
        muzzleFlashAlpha: 0,
        animTimer: 0,
        deathTimer: 0,
        weaponId: 0,
        isAlive: () => true,
        ...overrides,
    };
}

// ============================================================
// Tests
// ============================================================

describe('Sprite Fallback Verification — Player', () => {
    let grim: ReturnType<typeof createMockGrim>;
    let spriteRenderer: SpriteRenderer;

    beforeEach(() => {
        grim = createMockGrim();
        spriteRenderer = createLoadedSpriteRenderer();
    });

    it('should use sprite rendering for live player (no drawCircleFilled)', () => {
        const ctx = createPlayerContext();
        renderPlayer(ctx, grim, spriteRenderer, false); // debugMode = false

        expect(getCircleCalls(grim)).toHaveLength(0);
        expect(getQuadCalls(grim).length).toBeGreaterThan(0);
        expect(getBindTextureCalls(grim).length).toBeGreaterThan(0);
    });

    it('should use sprite rendering for dead player (no drawCircleFilled)', () => {
        const ctx = createPlayerContext({
            isAlive: () => false,
            deathTimer: 5.0,
        });
        renderPlayer(ctx, grim, spriteRenderer, false);

        expect(getCircleCalls(grim)).toHaveLength(0);
    });

    it('should use sprite rendering for shielded player (no drawCircleFilled)', () => {
        const ctx = createPlayerContext({ shieldTimer: 2.0 });
        renderPlayer(ctx, grim, spriteRenderer, false);

        expect(getCircleCalls(grim)).toHaveLength(0);
        expect(getQuadCalls(grim).length).toBeGreaterThan(0);
    });

    it('should use sprite rendering with muzzle flash (no drawCircleFilled)', () => {
        const ctx = createPlayerContext({ muzzleFlashAlpha: 0.8 });
        renderPlayer(ctx, grim, spriteRenderer, false);

        expect(getCircleCalls(grim)).toHaveLength(0);
    });

    it('should render muzzle flash with texture quad (additive blend)', () => {
        const ctx = createPlayerContext({ muzzleFlashAlpha: 0.6 });
        renderPlayer(ctx, grim, spriteRenderer, false);

        // Should bind the muzzle flash texture (handle 9)
        const bindCalls = getBindTextureCalls(grim);
        const muzzleFlashBinds = bindCalls.filter((c) => c.args[0] === 9);
        expect(muzzleFlashBinds.length).toBeGreaterThanOrEqual(1);

        // Should use additive blending
        const blendCalls = grim.drawCalls.filter((c) => c.method === 'setBlendMode' && c.args[0] === 'add');
        expect(blendCalls.length).toBeGreaterThanOrEqual(1);

        // Should draw quad(s) for the flash
        expect(getQuadCalls(grim).length).toBeGreaterThan(0);
        expect(getCircleCalls(grim)).toHaveLength(0);
    });

    it('should NOT render muzzle flash quad when alpha is 0', () => {
        const ctx = createPlayerContext({ muzzleFlashAlpha: 0 });
        renderPlayer(ctx, grim, spriteRenderer, false);

        // Should NOT bind the muzzle flash texture (handle 9)
        const bindCalls = getBindTextureCalls(grim);
        const muzzleFlashBinds = bindCalls.filter((c) => c.args[0] === 9);
        expect(muzzleFlashBinds).toHaveLength(0);
    });
});

describe('Sprite Fallback Verification — Enemy', () => {
    let grim: ReturnType<typeof createMockGrim>;
    let spriteRenderer: SpriteRenderer;

    beforeEach(() => {
        grim = createMockGrim();
        spriteRenderer = createLoadedSpriteRenderer();
    });

    it('should use sprite rendering for alive enemy (no drawCircleFilled)', () => {
        const enemy = new Enemy(200, 200, EnemyType.Spider);
        enemy.render(grim, undefined, spriteRenderer, false); // debugMode = false

        expect(getCircleCalls(grim)).toHaveLength(0);
        expect(getQuadCalls(grim).length).toBeGreaterThan(0);
    });

    it('should use sprite rendering for each enemy type (no drawCircleFilled)', () => {
        const types = [
            EnemyType.Zombie,
            EnemyType.Lizard,
            EnemyType.Spider,
            EnemyType.Spider2,
            EnemyType.Alien,
            EnemyType.Trooper,
        ];

        for (const type of types) {
            grim = createMockGrim();
            const enemy = new Enemy(200, 200, type);
            enemy.render(grim, undefined, spriteRenderer, false);

            expect(getCircleCalls(grim)).toHaveLength(0);
            // Should render at least one quad
            expect(getQuadCalls(grim).length).toBeGreaterThan(0);
        }
    });

    it('should use sprite rendering for hit-flashing enemy (no drawCircleFilled)', () => {
        const enemy = new Enemy(200, 200, EnemyType.Zombie);
        enemy.hitFlashTimer = 0.15;
        enemy.render(grim, undefined, spriteRenderer, false);

        expect(getCircleCalls(grim)).toHaveLength(0);
    });

    it('should use sprite rendering for dying enemy (no drawCircleFilled)', () => {
        const enemy = new Enemy(200, 200, EnemyType.Spider);
        enemy.isDying = true;
        enemy.hitboxSize = 8.0;
        enemy.deathTimer = 0.5;
        enemy.render(grim, undefined, spriteRenderer, false);

        expect(getCircleCalls(grim)).toHaveLength(0);
    });
});

describe('Sprite Fallback Verification — Projectile (entity-level)', () => {
    let grim: ReturnType<typeof createMockGrim>;
    let spriteRenderer: SpriteRenderer;

    beforeEach(() => {
        grim = createMockGrim();
        spriteRenderer = createLoadedSpriteRenderer();
    });

    it('should use sprite rendering for bullet projectile (no drawCircleFilled)', () => {
        const proj = new Projectile(100, 100, 300, 0, 10, 0.4, -1, ProjectileType.PISTOL);
        proj.render(grim, spriteRenderer, false); // debugMode = false

        expect(getCircleCalls(grim)).toHaveLength(0);
    });

    it('should use sprite rendering for all projectile types (no drawCircleFilled)', () => {
        const types = [
            ProjectileType.PISTOL,
            ProjectileType.ASSAULT_RIFLE,
            ProjectileType.SHOTGUN,
            ProjectileType.SMG,
            ProjectileType.MINIGUN,
            ProjectileType.GAUSS_GUN,
            ProjectileType.PLASMA_RIFLE,
            ProjectileType.PLASMA_MINIGUN,
            ProjectileType.PLASMA_CANNON,
            ProjectileType.SPIDER_PLASMA,
            ProjectileType.SHRINKIFIER,
            ProjectileType.PULSE_GUN,
            ProjectileType.SPLITTER_GUN,
            ProjectileType.BLADE_GUN,
            ProjectileType.PLAGUE_SPREADER,
            ProjectileType.ION_RIFLE,
            ProjectileType.ION_MINIGUN,
            ProjectileType.ION_CANNON,
            ProjectileType.ROCKET,
            ProjectileType.SEEKER_ROCKET,
            ProjectileType.ROCKET_MINIGUN,
            ProjectileType.FIRE_BULLETS,
        ];

        for (const pType of types) {
            grim = createMockGrim();
            const proj = new Projectile(100, 100, 300, 0, 10, 0.4, -1, pType);
            proj.render(grim, spriteRenderer, false);

            const circles = getCircleCalls(grim);
            expect(circles).toHaveLength(0);
        }
    });
});

describe('Sprite Fallback Verification — ProjectileRenderer (inline fallbacks)', () => {
    let grim: ReturnType<typeof createMockGrim>;

    beforeEach(() => {
        grim = createMockGrim();
    });

    /**
     * Creates a ProjectileTextureContext with all textures available.
     */
    function createLoadedProjectileContext(): ProjectileTextureContext {
        return {
            particlesHandle: 4,
            projectileHandle: 3,
            bulletTrailHandle: 5,
            bulletHeadHandle: 6,
            hasParticlesSprite: true,
            hasProjectileSprite: true,
            hasBulletTrailSprite: true,
            hasBulletHeadSprite: true,
        };
    }

    function makeProjectileData(type: ProjectileType) {
        return {
            x: 100,
            y: 100,
            angle: 0,
            projectileType: type,
            lifetime: 0.4,
            maxLifetime: 0.4,
            headX: 110,
            headY: 100,
            tailX: 90,
            tailY: 100,
            perpX: 0,
            perpY: 1,
        };
    }

    it('should not use drawCircleFilled for plasma projectile when textures loaded', () => {
        const ctx = createLoadedProjectileContext();
        drawProjectile(ctx, grim, makeProjectileData(ProjectileType.PLASMA_RIFLE));

        expect(getCircleCalls(grim)).toHaveLength(0);
        expect(getQuadCalls(grim).length).toBeGreaterThan(0);
    });

    it('should not use drawCircleFilled for special projectiles when textures loaded', () => {
        const specialTypes = [
            ProjectileType.PULSE_GUN,
            ProjectileType.SPLITTER_GUN,
            ProjectileType.BLADE_GUN,
            ProjectileType.PLAGUE_SPREADER,
        ];

        for (const pType of specialTypes) {
            grim = createMockGrim();
            const ctx = createLoadedProjectileContext();
            drawProjectile(ctx, grim, makeProjectileData(pType));

            expect(getCircleCalls(grim)).toHaveLength(0);
            expect(getQuadCalls(grim).length).toBeGreaterThan(0);
        }
    });

    it('should not use drawCircleFilled for rocket projectiles when textures loaded', () => {
        const rocketTypes = [ProjectileType.ROCKET, ProjectileType.SEEKER_ROCKET, ProjectileType.ROCKET_MINIGUN];

        for (const pType of rocketTypes) {
            grim = createMockGrim();
            const ctx = createLoadedProjectileContext();
            drawProjectile(ctx, grim, makeProjectileData(pType));

            expect(getCircleCalls(grim)).toHaveLength(0);
            expect(getQuadCalls(grim).length).toBeGreaterThan(0);
        }
    });

    it('should not use drawCircleFilled for fire bullet particles when textures loaded', () => {
        const ctx = createLoadedProjectileContext();
        drawProjectile(ctx, grim, makeProjectileData(ProjectileType.FIRE_BULLETS));

        expect(getCircleCalls(grim)).toHaveLength(0);
    });

    it('should not use drawCircleFilled for ion projectiles when textures loaded', () => {
        const ionTypes = [ProjectileType.ION_RIFLE, ProjectileType.ION_MINIGUN, ProjectileType.ION_CANNON];

        for (const pType of ionTypes) {
            grim = createMockGrim();
            const ctx = createLoadedProjectileContext();
            drawProjectile(ctx, grim, makeProjectileData(pType));

            // Ion projectiles should ideally use sprite-based rendering when
            // textures are loaded. Currently they always use drawCircleFilled
            // for the beam endpoint glow — this test will FAIL to surface that gap.
            const circles = getCircleCalls(grim);
            expect(circles.length).toBe(0);
        }
    });
});

describe('Sprite Fallback Verification — Bonus', () => {
    let grim: ReturnType<typeof createMockGrim>;
    let spriteRenderer: SpriteRenderer;

    beforeEach(() => {
        grim = createMockGrim();
        spriteRenderer = createLoadedSpriteRenderer();
    });

    it('should use sprite rendering for bonuses (no drawCircleFilled)', () => {
        const bonusSystem = new BonusSystem();

        // Manually create a bonus and add it to the system
        const bonus = new Bonus(200, 200, BonusType.HEALTH, 25);
        (bonusSystem as any).bonuses = [bonus];

        // Render with sprite renderer
        bonusSystem.render(grim, spriteRenderer, 0, 0);

        // With spriteRenderer available, should use drawBonus (quads) not Bonus.render (circles)
        expect(getCircleCalls(grim)).toHaveLength(0);
    });

    it('should use sprite rendering for all bonus types (no drawCircleFilled)', () => {
        const bonusTypes = [
            BonusType.WEAPON,
            BonusType.POINTS,
            BonusType.HEALTH,
            BonusType.SHIELD,
            BonusType.FIRE_BULLETS,
            BonusType.ENERGIZER,
            BonusType.DOUBLE_EXPERIENCE,
            BonusType.NUKE,
            BonusType.FIREBLAST,
            BonusType.SHOCK_CHAIN,
            BonusType.REFLEX_BOOST,
            BonusType.WEAPON_POWER_UP,
            BonusType.SPEED,
            BonusType.FREEZE,
        ];

        for (const type of bonusTypes) {
            grim = createMockGrim();
            const bonusSystem = new BonusSystem();
            const bonus = new Bonus(200, 200, type, 5);
            (bonusSystem as any).bonuses = [bonus];

            bonusSystem.render(grim, spriteRenderer, 0, 0);

            expect(getCircleCalls(grim)).toHaveLength(0);
        }
    });
});

describe('Sprite Fallback Verification — GameplayCursor', () => {
    let grim: ReturnType<typeof createMockGrim>;

    beforeEach(() => {
        grim = createMockGrim();
    });

    it('should use aim texture for crosshair (no line fallback)', async () => {
        // Import GameplayCursor
        const { GameplayCursor } = await import('../GameplayCursor');
        const cursor = new GameplayCursor();

        // Force the aim texture handle to be loaded
        (cursor as any).aimHandle = 10;
        (cursor as any).particlesHandle = 11;

        // Create a mock player
        const mockPlayer = {
            isAlive: () => true,
            x: 400,
            y: 300,
            spreadHeat: 0.1,
            reloadTimer: 0,
            reloadTimerMax: 1,
        };

        cursor.render(grim, mockPlayer as any, 0, 0);

        // When aim texture is loaded, should NOT see the line-based crosshair fallback
        // The fallback draws 4 short lines + 1 center dot (drawCircleFilled)
        // With texture: should use drawQuad for the aim crosshair
        const quads = getQuadCalls(grim);
        const lines = getLineCalls(grim);

        // Should have quads for the glow + crosshair
        expect(quads.length).toBeGreaterThan(0);

        // The only lines should be from the spread circle, not the crosshair fallback
        // Crosshair fallback draws exactly 4 lines (H left, H right, V up, V down)
        // If aim texture is loaded, there should be NO crosshair lines
        // (though spread circle outline uses drawCircleOutline, not drawLine)
        const crosshairLines = lines.filter((l) => {
            // Crosshair lines are exactly 1px wide and 5px long
            const args = l.args;
            return args[4] === 1; // lineWidth = 1 is the crosshair indicator
        });
        expect(crosshairLines).toHaveLength(0);
    });
});

describe('Sprite Fallback Verification — ParticleSystem', () => {
    it('ParticleSystem.render with spriteRenderer uses drawQuad, not drawCircleFilled', async () => {
        const grim = createMockGrim();
        const spriteRenderer = createLoadedSpriteRenderer();
        const { ParticleSystem } = await import('../../systems/effects/ParticleSystem');
        const particleSystem = new ParticleSystem();

        // Spawn some particles
        particleSystem.spawnFastParticle(100, 100, 0, 1.0);
        particleSystem.spawnSlowParticle(200, 200, Math.PI);

        // Render with sprite renderer
        particleSystem.render(grim, spriteRenderer as any);

        // With sprite context: should use quads/texture, NOT circles
        expect(getCircleCalls(grim)).toHaveLength(0);
        expect(getQuadCalls(grim).length).toBeGreaterThan(0);
        expect(getBindTextureCalls(grim).length).toBeGreaterThan(0);
    });

    it('ParticleSystem.render without spriteRenderer falls back to drawCircleFilled', async () => {
        const grim = createMockGrim();
        const { ParticleSystem } = await import('../../systems/effects/ParticleSystem');
        const particleSystem = new ParticleSystem();

        // Spawn some particles
        particleSystem.spawnFastParticle(100, 100, 0, 1.0);
        particleSystem.spawnSlowParticle(200, 200, Math.PI);

        // Render without sprite renderer (fallback path)
        particleSystem.render(grim);

        // Without sprite context: should fall back to circles
        expect(getCircleCalls(grim).length).toBeGreaterThan(0);
        expect(getQuadCalls(grim)).toHaveLength(0);
        expect(getBindTextureCalls(grim)).toHaveLength(0);
    });
});
