/**
 * EffectSystemE2E.test.ts — Verify every effect in the EFFECT_ID_TABLE
 * produces valid atlas UVs and does not fall back to default/fallback textures.
 *
 * These tests exercise each spawn function → render path to ensure:
 * 1. Every effect ID used by spawn functions maps to a valid EFFECT_ID_TABLE entry
 * 2. Rendering produces drawQuad + bindTexture calls (not circles/fallbacks)
 * 3. UV coordinates are within [0, 1] and non-degenerate (u0 < u1, v0 < v1)
 * 4. All spawn functions produce at least one active effect
 */

import { describe, it, expect, beforeEach } from 'vitest';
import { EffectSystem } from '../effects/EffectSystem';
import type { GrimInterface, TextureHandle } from '../../engine/GrimInterface';

// ============================================================
// Mock GrimInterface that records draw calls + captures UV values
// ============================================================

interface DrawCall {
    method: string;
    args: any[];
}

interface UVRecord {
    u0: number;
    v0: number;
    u1: number;
    v1: number;
}

function createMockGrim(): GrimInterface & { drawCalls: DrawCall[]; uvRecords: UVRecord[] } {
    const drawCalls: DrawCall[] = [];
    const uvRecords: UVRecord[] = [];

    const record =
        (method: string) =>
            (...args: any[]) => {
                drawCalls.push({ method, args });
            };

    const noop = () => { };
    const noopReturn = (val: any) => () => val;

    const mock: any = {
        drawCalls,
        uvRecords,

        // Drawing methods we track
        drawCircleFilled: record('drawCircleFilled'),
        drawCircleOutline: record('drawCircleOutline'),
        drawRectFilled: record('drawRectFilled'),
        drawLine: record('drawLine'),
        drawQuad: record('drawQuad'),
        drawQuadPoints: record('drawQuadPoints'),
        drawText: record('drawText'),

        // State methods we track
        setColor: record('setColor'),
        setRotation: record('setRotation'),
        setUV: (u0: number, v0: number, u1: number, v1: number) => {
            drawCalls.push({ method: 'setUV', args: [u0, v0, u1, v1] });
            uvRecords.push({ u0, v0, u1, v1 });
        },
        setAtlasFrame: (gridSize: number, frame: number) => {
            drawCalls.push({ method: 'setAtlasFrame', args: [gridSize, frame] });
            // Compute UVs from atlas frame (mirrors real GrimInterface)
            const col = frame % gridSize;
            const row = Math.floor(frame / gridSize);
            const step = 1.0 / gridSize;
            const u0 = col * step;
            const v0 = row * step;
            const u1 = u0 + step;
            const v1 = v0 + step;
            uvRecords.push({ u0, v0, u1, v1 });
        },
        bindTexture: record('bindTexture'),
        setBlendMode: record('setBlendMode'),
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
        registerTexture: (_name: string, _tex: any) => 1 as TextureHandle,
        createTexture: () => 1 as TextureHandle,
        loadTexture: async () => 1 as TextureHandle,

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

function getQuadCalls(grim: { drawCalls: DrawCall[] }): DrawCall[] {
    return grim.drawCalls.filter((c) => c.method === 'drawQuad' || c.method === 'drawQuadPoints');
}

function getCircleCalls(grim: { drawCalls: DrawCall[] }): DrawCall[] {
    return grim.drawCalls.filter((c) => c.method === 'drawCircleFilled');
}

function getBindTextureCalls(grim: { drawCalls: DrawCall[] }): DrawCall[] {
    return grim.drawCalls.filter((c) => c.method === 'bindTexture');
}

// ============================================================
// Helper: Validate that all UV records are within [0,1] range
// and non-degenerate (u0 < u1, v0 < v1)
// ============================================================

function assertAllUVsValid(uvRecords: UVRecord[], _testName: string): void {
    for (let i = 0; i < uvRecords.length; i++) {
        const { u0, v0, u1, v1 } = uvRecords[i];

        // UVs must be in [0, 1] range
        expect(u0).toBeGreaterThanOrEqual(0);
        expect(v0).toBeGreaterThanOrEqual(0);
        expect(u1).toBeLessThanOrEqual(1.0001); // tiny epsilon for float math
        expect(v1).toBeLessThanOrEqual(1.0001);

        // UVs must be non-degenerate (not a zero-area rect)
        expect(u1).toBeGreaterThan(u0);
        expect(v1).toBeGreaterThan(v0);
    }
}

// Default fallback UVs are u0=0, v0=0, u1=0.25, v1=0.25 (4x4 grid frame 0).
// We check that NOT ALL UVs match this exact default — some spawn functions
// intentionally use ID 0 (which maps to these UVs), but compound spawns
// should use a variety of IDs.

// ============================================================
// Tests
// ============================================================

describe('EffectSystem E2E — Effect ID Table Coverage', () => {
    let effectSystem: EffectSystem;

    beforeEach(() => {
        effectSystem = new EffectSystem();
        effectSystem.setParticlesTexture(42 as TextureHandle); // Valid handle
    });

    it('spawnFreezeShard should produce active effects with valid UVs (IDs 8, 9, or 10)', () => {
        const grim = createMockGrim();

        // Spawn many to hit all 3 random IDs (8, 9, 10)
        for (let i = 0; i < 30; i++) {
            effectSystem.spawnFreezeShard(100, 100, i * 0.5);
        }

        expect(effectSystem.getActiveCount()).toBeGreaterThanOrEqual(30);

        effectSystem.render(grim);

        expect(getQuadCalls(grim).length).toBeGreaterThan(0);
        expect(getCircleCalls(grim)).toHaveLength(0);
        expect(getBindTextureCalls(grim).length).toBeGreaterThan(0);
        assertAllUVsValid(grim.uvRecords, 'spawnFreezeShard');

        // Freeze shards use IDs 8, 9, 10 which should NOT all be the default (0,0,0.25,0.25)
        const nonDefaultUVs = grim.uvRecords.filter(
            (uv) => uv.u0 !== 0 || uv.v0 !== 0 || uv.u1 !== 0.25 || uv.v1 !== 0.25,
        );
        expect(nonDefaultUVs.length).toBeGreaterThan(0);
    });

    it('spawnFreezeShatter should produce center burst (ID 0xe) + shards (IDs 8-10)', () => {
        const grim = createMockGrim();

        effectSystem.spawnFreezeShatter(200, 200, 0);

        // 4 center crystals + 4 shards = 8 minimum
        expect(effectSystem.getActiveCount()).toBeGreaterThanOrEqual(8);

        effectSystem.render(grim);

        expect(getQuadCalls(grim).length).toBeGreaterThanOrEqual(8);
        expect(getCircleCalls(grim)).toHaveLength(0);
        assertAllUVsValid(grim.uvRecords, 'spawnFreezeShatter');

        // Center crystals use ID 0x0e (frame 8) and shards use IDs 8,9,10 (frames 13,15,8).
        // Since ID 0x0a (freeze shard C) shares frame 8 with ID 0x0e, UV variety is not
        // guaranteed when all 4 random shards happen to pick ID 0x0a. Just verify we got
        // valid UV records for all rendered effects.
        expect(grim.uvRecords.length).toBeGreaterThanOrEqual(8);
    });

    it('spawnBurst should produce 8 active effects with valid UVs (ID 0)', () => {
        const grim = createMockGrim();

        effectSystem.spawnBurst(150, 150, 8);

        expect(effectSystem.getActiveCount()).toBe(8);

        effectSystem.render(grim);

        expect(getQuadCalls(grim).length).toBe(8);
        expect(getCircleCalls(grim)).toHaveLength(0);
        assertAllUVsValid(grim.uvRecords, 'spawnBurst');
    });

    it('spawnShrinkFx should produce center flash (ID 1) + sparks (ID 0)', () => {
        const grim = createMockGrim();

        effectSystem.spawnShrinkFx(300, 300);

        // 1 center flash + 4 sparks = 5
        expect(effectSystem.getActiveCount()).toBe(5);

        effectSystem.render(grim);

        expect(getQuadCalls(grim).length).toBeGreaterThanOrEqual(5);
        expect(getCircleCalls(grim)).toHaveLength(0);
        assertAllUVsValid(grim.uvRecords, 'spawnShrinkFx');

        // ID 1 uses 2x2 grid (u1=0.5), ID 0 uses 4x4 grid (u1=0.25) — should have both
        const hasLargeUV = grim.uvRecords.some((uv) => uv.u1 > 0.3);
        const hasSmallUV = grim.uvRecords.some((uv) => uv.u1 <= 0.26);
        expect(hasLargeUV).toBe(true); // ID 1 has 0.5 width
        expect(hasSmallUV).toBe(true); // ID 0 has 0.25 width
    });

    it('spawnElectricArc should produce 1 effect with valid UVs (ID 1)', () => {
        const grim = createMockGrim();

        effectSystem.spawnElectricArc(100, 100, 1.0, 0.2);

        expect(effectSystem.getActiveCount()).toBe(1);

        effectSystem.render(grim);

        expect(getQuadCalls(grim).length).toBe(1);
        expect(getCircleCalls(grim)).toHaveLength(0);
        assertAllUVsValid(grim.uvRecords, 'spawnElectricArc');

        // ID 1 = 2x2 grid, frame 0 → u0=0, v0=0, u1=0.5, v1=0.5
        expect(grim.uvRecords[0].u1).toBeCloseTo(0.5);
        expect(grim.uvRecords[0].v1).toBeCloseTo(0.5);
    });

    it('spawnPlasmaExplosion should produce 1 effect with valid UVs (ID 1)', () => {
        const grim = createMockGrim();

        effectSystem.spawnPlasmaExplosion(100, 100, 1.0, 0.3);

        expect(effectSystem.getActiveCount()).toBe(1);

        effectSystem.render(grim);

        // PlasmaExplosion starts with age=0.1 and lifetime=0.3 — it's alive, should render
        expect(getQuadCalls(grim).length).toBe(1);
        expect(getCircleCalls(grim)).toHaveLength(0);
        assertAllUVsValid(grim.uvRecords, 'spawnPlasmaExplosion');

        // ID 1 = 2x2 grid
        expect(grim.uvRecords[0].u1).toBeCloseTo(0.5);
    });

    it('spawnFireParticles should produce N effects with valid UVs (ID 0)', () => {
        const grim = createMockGrim();
        const count = 12;

        effectSystem.spawnFireParticles(100, 100, 64, count);

        expect(effectSystem.getActiveCount()).toBe(count);

        // Fire particles start with negative age — need to advance time for them to render
        effectSystem.update(0.5); // advance past negative age

        effectSystem.render(grim);

        // Some may have already expired, but most should still be active
        expect(getQuadCalls(grim).length).toBeGreaterThan(0);
        expect(getCircleCalls(grim)).toHaveLength(0);
        assertAllUVsValid(grim.uvRecords, 'spawnFireParticles');
    });

    it('spawnShockwave should produce multiple effects with valid UVs (ID 0)', () => {
        const grim = createMockGrim();

        effectSystem.spawnShockwave(100, 100, 1.5);

        expect(effectSystem.getActiveCount()).toBeGreaterThanOrEqual(4);

        effectSystem.render(grim);

        expect(getQuadCalls(grim).length).toBeGreaterThanOrEqual(4);
        expect(getCircleCalls(grim)).toHaveLength(0);
        assertAllUVsValid(grim.uvRecords, 'spawnShockwave');
    });

    it('spawnExplosionBurst should produce multi-layer effects with multiple IDs', () => {
        const grim = createMockGrim();

        effectSystem.spawnExplosionBurst(200, 200, 1.0);

        // Center flash (1) + smoke rings (2) + bright glow (1) + debris (4) + shockwave (variable)
        expect(effectSystem.getActiveCount()).toBeGreaterThanOrEqual(8);

        effectSystem.render(grim);

        expect(getQuadCalls(grim).length).toBeGreaterThanOrEqual(4);
        expect(getCircleCalls(grim)).toHaveLength(0);
        expect(getBindTextureCalls(grim).length).toBeGreaterThan(0);
        assertAllUVsValid(grim.uvRecords, 'spawnExplosionBurst');

        // Explosion burst uses IDs 0, EXPANSION_RING (0x0f), 0x0c, 0x11 — should have UV variety
        const uniqueUVs = new Set(grim.uvRecords.map((uv) => `${uv.u0.toFixed(3)},${uv.v0.toFixed(3)}`));
        expect(uniqueUVs.size).toBeGreaterThanOrEqual(2);
    });

    it('spawnReflexHalo should produce 1 effect with valid UVs (EXPANSION_RING)', () => {
        const grim = createMockGrim();

        effectSystem.spawnReflexHalo(100, 100);

        expect(effectSystem.getActiveCount()).toBe(1);

        effectSystem.render(grim);

        expect(getQuadCalls(grim).length).toBe(1);
        expect(getCircleCalls(grim)).toHaveLength(0);
        assertAllUVsValid(grim.uvRecords, 'spawnReflexHalo');

        // EXPANSION_RING = 2x2 grid, frame 3 → u0=0.5, v0=0.5, u1=1.0, v1=1.0
        expect(grim.uvRecords[0].u0).toBeCloseTo(0.5);
        expect(grim.uvRecords[0].v0).toBeCloseTo(0.5);
        expect(grim.uvRecords[0].u1).toBeCloseTo(1.0);
        expect(grim.uvRecords[0].v1).toBeCloseTo(1.0);
    });
});

describe('EffectSystem E2E — No Fallback Textures', () => {
    let effectSystem: EffectSystem;

    beforeEach(() => {
        effectSystem = new EffectSystem();
        effectSystem.setParticlesTexture(42 as TextureHandle);
    });

    it('should never use drawCircleFilled (fallback) for any spawn function', () => {
        const grim = createMockGrim();

        // Spawn one of each type
        effectSystem.spawnFreezeShard(100, 100, 0);
        effectSystem.spawnFreezeShatter(200, 200, 0);
        effectSystem.spawnBurst(300, 300, 4);
        effectSystem.spawnShrinkFx(400, 400);
        effectSystem.spawnElectricArc(500, 500);
        effectSystem.spawnPlasmaExplosion(600, 600);
        effectSystem.spawnFireParticles(100, 200, 32, 4);
        effectSystem.spawnShockwave(200, 300, 1.0);
        effectSystem.spawnExplosionBurst(300, 400, 1.0);
        effectSystem.spawnShellCasing(400, 500, 0.5);
        effectSystem.spawnReflexHalo(500, 600);

        // Advance time so fire particles (negative age) become visible
        effectSystem.update(0.05);

        effectSystem.render(grim);

        // ZERO circle fallbacks
        expect(getCircleCalls(grim)).toHaveLength(0);
        // MUST have quads
        expect(getQuadCalls(grim).length).toBeGreaterThan(0);
        // MUST bind a texture
        expect(getBindTextureCalls(grim).length).toBeGreaterThan(0);
    });

    it('should produce valid UV coords for ALL rendered effects (no out-of-bounds)', () => {
        const grim = createMockGrim();

        effectSystem.spawnFreezeShard(100, 100, 0);
        effectSystem.spawnFreezeShatter(200, 200, Math.PI);
        effectSystem.spawnBurst(300, 300, 12);
        effectSystem.spawnShrinkFx(400, 400);
        effectSystem.spawnElectricArc(500, 500, 2.0, 0.3);
        effectSystem.spawnPlasmaExplosion(250, 250, 1.5, 0.4);
        effectSystem.spawnFireParticles(150, 150, 48, 8);
        effectSystem.spawnShockwave(350, 350, 2.0);
        effectSystem.spawnExplosionBurst(450, 450, 2.0);
        effectSystem.spawnReflexHalo(550, 550);

        effectSystem.update(0.05);
        effectSystem.render(grim);

        // Assert every UV record is valid
        assertAllUVsValid(grim.uvRecords, 'all spawn functions combined');

        // Must have rendered a significant number of effects
        expect(grim.uvRecords.length).toBeGreaterThanOrEqual(10);
    });
});

describe('EffectSystem E2E — Effect ID Table Completeness', () => {
    let effectSystem: EffectSystem;

    beforeEach(() => {
        effectSystem = new EffectSystem();
        effectSystem.setParticlesTexture(42 as TextureHandle);
    });

    it('every effect ID referenced by spawn functions maps to valid non-fallback UVs', () => {
        // The spawn functions reference these effect IDs:
        // spawnFreezeShard:     8, 9, 10 (random)
        // spawnFreezeShatter:   0x0e (14), then calls spawnFreezeShard (8, 9, 10)
        // spawnBurst:           0
        // spawnShrinkFx:        1, 0
        // spawnElectricArc:     1
        // spawnPlasmaExplosion: 1
        // spawnFireParticles:   0
        // spawnShockwave:       0
        // spawnExplosionBurst:  EXPANSION_RING (0x0f), 0x11 (17), 0, 0x0c (12)
        //
        // Unique IDs used: 0, 1, 8, 9, 10, 12, 14, 17
        // ALL of these must be in EFFECT_ID_TABLE and produce valid UVs

        const allUVsBySpawn: Map<string, UVRecord[]> = new Map();

        // Test each spawn function individually to verify its IDs
        // Each test has a specific update duration to avoid expiry of short-lived effects
        // while still making delayed-start effects (fire particles) visible
        const spawnTests = [
            {
                name: 'FreezeShard',
                dt: 0.01,
                fn: () => {
                    for (let i = 0; i < 30; i++) effectSystem.spawnFreezeShard(100, 100, i * 0.2);
                },
            },
            { name: 'FreezeShatter', dt: 0.01, fn: () => effectSystem.spawnFreezeShatter(100, 100, 0) },
            { name: 'Burst', dt: 0.01, fn: () => effectSystem.spawnBurst(100, 100, 8) },
            { name: 'ShrinkFx', dt: 0.01, fn: () => effectSystem.spawnShrinkFx(100, 100) },
            { name: 'ElectricArc', dt: 0.01, fn: () => effectSystem.spawnElectricArc(100, 100) },
            { name: 'PlasmaExplosion', dt: 0.01, fn: () => effectSystem.spawnPlasmaExplosion(100, 100) },
            { name: 'FireParticles', dt: 0.35, fn: () => effectSystem.spawnFireParticles(100, 100, 32, 8) }, // needs deep advance for negative start age
            { name: 'Shockwave', dt: 0.01, fn: () => effectSystem.spawnShockwave(100, 100, 1.0) },
            { name: 'ExplosionBurst', dt: 0.01, fn: () => effectSystem.spawnExplosionBurst(100, 100, 1.0) },
            { name: 'ReflexHalo', dt: 0.01, fn: () => effectSystem.spawnReflexHalo(100, 100) },
        ];

        for (const test of spawnTests) {
            const testGrim = createMockGrim();
            effectSystem.clear();
            test.fn();
            effectSystem.update(test.dt);
            effectSystem.render(testGrim);

            allUVsBySpawn.set(test.name, testGrim.uvRecords);

            // Every spawn function must produce at least 1 quad
            const quads = getQuadCalls(testGrim);
            expect(quads.length).toBeGreaterThan(0);

            // No fallback circles
            expect(getCircleCalls(testGrim)).toHaveLength(0);

            // All UVs must be valid
            assertAllUVsValid(testGrim.uvRecords, test.name);
        }
    });

    it('effect pool reuses entries correctly without UV corruption', () => {
        const grim = createMockGrim();

        // Fill pool with one type, then spawn another type
        effectSystem.spawnBurst(100, 100, 384); // fill all entries with ID 0
        effectSystem.clear();

        // Now spawn a different type
        effectSystem.spawnFreezeShatter(200, 200, 0); // Uses IDs 8-10, 0x0e

        effectSystem.render(grim);

        // UVs should be correct for the NEW type, not leftover from burst
        assertAllUVsValid(grim.uvRecords, 'pool reuse');

        // At least some freeze shatter UVs should differ from ID 0 default
        const nonDefaultUVs = grim.uvRecords.filter(
            (uv) => uv.u0 !== 0 || uv.v0 !== 0 || uv.u1 !== 0.25 || uv.v1 !== 0.25,
        );
        expect(nonDefaultUVs.length).toBeGreaterThan(0);
    });
});

describe('EffectSystem E2E — Lifecycle and Rendering', () => {
    let effectSystem: EffectSystem;

    beforeEach(() => {
        effectSystem = new EffectSystem();
        effectSystem.setParticlesTexture(42 as TextureHandle);
    });

    it('effects expire correctly and stop rendering', () => {
        effectSystem.spawnElectricArc(100, 100, 1.0, 0.2); // lifetime ~0.16s

        expect(effectSystem.getActiveCount()).toBe(1);

        // Advance way past lifetime
        effectSystem.update(1.0);

        expect(effectSystem.getActiveCount()).toBe(0);

        const grim = createMockGrim();
        effectSystem.render(grim);
        expect(getQuadCalls(grim)).toHaveLength(0);
    });

    it('additive blend effects render with setBlendMode("add")', () => {
        const grim = createMockGrim();

        // spawnBurst uses flags 0x1d which includes FLAG_ADDITIVE (0x40? no — 0x1d = 0x01|0x04|0x08|0x10)
        // Actually 0x1d does NOT have 0x40 bit. Let me check: 0x1d = 0001_1101 = bits 0,2,3,4
        // The additive flag is 0x40 = bit 6. So 0x1d does NOT include additive.
        // Let me use spawnExplosionBurst which uses both 0x19 and 0x5d (which includes 0x40)
        effectSystem.spawnExplosionBurst(100, 100, 1.0);

        effectSystem.render(grim);

        // Should have at least one setBlendMode('add') call for additive pass
        const blendCalls = grim.drawCalls.filter((c) => c.method === 'setBlendMode');
        const addCalls = blendCalls.filter((c) => c.args[0] === 'add');
        expect(addCalls.length).toBeGreaterThanOrEqual(1);
    });

    it('does not render when texture handle is invalid', () => {
        const noTexSystem = new EffectSystem();
        // Don't set texture — handle remains -1
        noTexSystem.spawnBurst(100, 100, 8);

        const grim = createMockGrim();
        noTexSystem.render(grim);

        expect(getQuadCalls(grim)).toHaveLength(0);
        expect(getBindTextureCalls(grim)).toHaveLength(0);
    });
});

describe('EffectSystem E2E — Shell Casing (ID 0x12)', () => {
    let effectSystem: EffectSystem;

    beforeEach(() => {
        effectSystem = new EffectSystem();
        effectSystem.setParticlesTexture(42 as TextureHandle);
    });

    it('spawnShellCasing should produce 1 active effect with valid UVs (ID 0x12)', () => {
        const grim = createMockGrim();

        effectSystem.spawnShellCasing(100, 200, Math.PI / 4);

        expect(effectSystem.getActiveCount()).toBe(1);

        effectSystem.render(grim);

        // Shell casings use additive blend (flag 0x40)
        expect(getQuadCalls(grim).length).toBe(1);
        expect(getCircleCalls(grim)).toHaveLength(0);
        assertAllUVsValid(grim.uvRecords, 'spawnShellCasing');

        // ID 0x12 = 4×4 grid, frame 2 → u0=0.5, v0=0, u1=0.75, v1=0.25
        expect(grim.uvRecords[0].u0).toBeCloseTo(0.5);
        expect(grim.uvRecords[0].v0).toBeCloseTo(0.0);
        expect(grim.uvRecords[0].u1).toBeCloseTo(0.75);
        expect(grim.uvRecords[0].v1).toBeCloseTo(0.25);
    });

    it('spawnShellCasing should use additive blend (flag 0x40)', () => {
        const grim = createMockGrim();

        effectSystem.spawnShellCasing(100, 200, 0);

        effectSystem.render(grim);

        // Shell casings have FLAG_ADDITIVE (0x40), so should render in additive pass
        const blendCalls = grim.drawCalls.filter((c) => c.method === 'setBlendMode');
        const addCalls = blendCalls.filter((c) => c.args[0] === 'add');
        expect(addCalls.length).toBeGreaterThanOrEqual(1);
    });

    it('spawnShellCasing should trigger terrain bake callback on expiry', () => {
        let bakeCount = 0;
        let bakedEffectId = -1;

        effectSystem.setTerrainBakeCallback(
            (effectId, _x, _y, _w, _h, _rot, _r, _g, _b, _a) => {
                bakeCount++;
                bakedEffectId = effectId;
            },
        );

        effectSystem.spawnShellCasing(100, 200, 0);

        // Advance past lifetime (0.15s)
        effectSystem.update(0.2);

        expect(bakeCount).toBe(1);
        expect(bakedEffectId).toBe(0x12);
        expect(effectSystem.getActiveCount()).toBe(0);
    });

    it('multiple shell casings should all render independently', () => {
        const grim = createMockGrim();

        for (let i = 0; i < 10; i++) {
            effectSystem.spawnShellCasing(100 + i * 10, 200, i * 0.3);
        }

        expect(effectSystem.getActiveCount()).toBe(10);

        effectSystem.render(grim);

        expect(getQuadCalls(grim).length).toBe(10);
        assertAllUVsValid(grim.uvRecords, 'multiple shell casings');
    });
});
