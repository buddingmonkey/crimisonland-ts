/**
 * SpriteRenderer.test.ts - Unit tests for sprite rotation behavior
 *
 * Verifies that player and enemy sprites use grim.setRotation() for
 * continuous rotation (matching C code player.c lines 2232-2400),
 * NOT 8-direction sprite column selection.
 */

import { describe, it, expect, beforeEach } from 'vitest';
import { SpriteRenderer } from '../SpriteRenderer';
import { GrimInterface } from '../../engine/GrimInterface';
import { TROOPER_CONFIG, getFrameUV } from '../SpriteSheetConfig';

/**
 * Creates a mock GrimInterface that records all calls for assertion.
 * Only stubs the methods used by drawPlayer/drawEnemy.
 */
function createMockGrim(): GrimInterface & {
    calls: {
        setRotation: number[];
        setUV: { u0: number; v0: number; u1: number; v1: number }[];
        setAtlasFrame: { atlasSize: number; frame: number }[];
        drawQuad: { x: number; y: number; w: number; h: number }[];
        bindTexture: number[];
        setColor: { r: number; g: number; b: number; a: number }[];
    };
} {
    const calls = {
        setRotation: [] as number[],
        setUV: [] as { u0: number; v0: number; u1: number; v1: number }[],
        setAtlasFrame: [] as { atlasSize: number; frame: number }[],
        drawQuad: [] as { x: number; y: number; w: number; h: number }[],
        bindTexture: [] as number[],
        setColor: [] as { r: number; g: number; b: number; a: number }[],
    };

    const mock = {
        calls,
        setRotation: (angle: number) => {
            calls.setRotation.push(angle);
        },
        setUV: (u0: number, v0: number, u1: number, v1: number) => {
            calls.setUV.push({ u0, v0, u1, v1 });
        },
        setAtlasFrame: (atlasSize: number, frame: number) => {
            calls.setAtlasFrame.push({ atlasSize, frame });
        },
        drawQuad: (x: number, y: number, w: number, h: number) => {
            calls.drawQuad.push({ x, y, w, h });
        },
        bindTexture: (handle: number) => {
            calls.bindTexture.push(handle);
        },
        setColor: (r: number, g: number, b: number, a: number) => {
            calls.setColor.push({ r, g, b, a });
        },
        setBlendMode: (_mode: string) => {
            /* no-op for test */
        },
    } as unknown as GrimInterface & typeof calls;

    // Re-attach calls for assertion access
    (mock as any).calls = calls;

    return mock as any;
}

/**
 * Utility to make the SpriteRenderer think it has loaded sprites.
 * Bypasses async asset loading by directly setting internal state.
 */
function makeRendererReady(renderer: SpriteRenderer): void {
    // Use Object.assign to set private fields for testing
    (renderer as any).hasPlayerSprite = true;
    (renderer as any).hasEnemySprite = true;
    (renderer as any).playerHandle = 1;
    (renderer as any).enemyHandle = 2;
    (renderer as any).loaded = true;
    // drawEnemy now uses per-type texture handles Map (keyed by textureKey from CREATURE_TYPE_TABLE)
    // Default enemyType=Spider (type 2) uses 'game/spider_sp1.jaz'
    const enemyTextureHandles = new Map<string, number>();
    enemyTextureHandles.set('game/zombie.jaz', 2);
    enemyTextureHandles.set('game/lizard.jaz', 2);
    enemyTextureHandles.set('game/spider_sp1.jaz', 2);
    enemyTextureHandles.set('game/spider_sp2.jaz', 2);
    enemyTextureHandles.set('game/alien.jaz', 2);
    enemyTextureHandles.set('game/trooper.jaz', 2);
    (renderer as any).enemyTextureHandles = enemyTextureHandles;
}

describe('SpriteRenderer - Rotation', () => {
    let renderer: SpriteRenderer;
    let mockGrim: ReturnType<typeof createMockGrim>;

    beforeEach(() => {
        renderer = new SpriteRenderer();
        mockGrim = createMockGrim();
        makeRendererReady(renderer);
    });

    describe('drawPlayer rotation', () => {
        it('should call setRotation with angle + PI/2 offset', () => {
            const angle = 0; // facing right (East)
            renderer.drawPlayer(mockGrim, 100, 100, angle, 15);

            // Should call setRotation with angle + PI/2 (C code: aim_heading = atan2(pY-aY, pX-aX) - PI/2)
            expect(mockGrim.calls.setRotation.length).toBe(2); // set + reset
            expect(mockGrim.calls.setRotation[0]).toBeCloseTo(angle + Math.PI / 2);
        });

        it('should reset rotation to 0 after drawing', () => {
            renderer.drawPlayer(mockGrim, 100, 100, 0, 15);

            // Last setRotation call should reset to 0
            const lastRotation = mockGrim.calls.setRotation[mockGrim.calls.setRotation.length - 1];
            expect(lastRotation).toBe(0);
        });

        it('should rotate correctly for all cardinal directions', () => {
            const testCases = [
                { name: 'East', angle: 0, expected: Math.PI / 2 },
                { name: 'South', angle: Math.PI / 2, expected: Math.PI },
                { name: 'West', angle: Math.PI, expected: (Math.PI * 3) / 2 },
                { name: 'North', angle: -Math.PI / 2, expected: 0 },
            ];

            for (const tc of testCases) {
                mockGrim.calls.setRotation = []; // reset
                renderer.drawPlayer(mockGrim, 100, 100, tc.angle, 15);
                expect(mockGrim.calls.setRotation[0]).toBeCloseTo(tc.expected, 5);
            }
        });

        it('should rotate correctly for diagonal directions', () => {
            const testCases = [
                { name: 'NE', angle: -Math.PI / 4, expected: Math.PI / 4 },
                { name: 'SE', angle: Math.PI / 4, expected: (Math.PI * 3) / 4 },
                { name: 'SW', angle: (Math.PI * 3) / 4, expected: (Math.PI * 5) / 4 },
                { name: 'NW', angle: (-Math.PI * 3) / 4, expected: -Math.PI / 4 },
            ];

            for (const tc of testCases) {
                mockGrim.calls.setRotation = [];
                renderer.drawPlayer(mockGrim, 100, 100, tc.angle, 15);
                expect(mockGrim.calls.setRotation[0]).toBeCloseTo(tc.expected, 5);
            }
        });

        it('should use column 0 for UV (rotation handles direction)', () => {
            renderer.drawPlayer(mockGrim, 100, 100, Math.PI / 4, 15);

            // Verify setAtlasFrame is called with 8×8 atlas, frame = idleRow * 8 (column 0)
            const expectedFrame = TROOPER_CONFIG.animations.idle.startRow * 8;
            expect(mockGrim.calls.setAtlasFrame[0]).toEqual({ atlasSize: 8, frame: expectedFrame });
        });

        it('should not call setRotation without a sprite loaded', () => {
            (renderer as any).hasPlayerSprite = false;
            renderer.drawPlayer(mockGrim, 100, 100, 0, 15);

            expect(mockGrim.calls.setRotation.length).toBe(0);
            expect(mockGrim.calls.drawQuad.length).toBe(0);
        });

        it('should center the sprite on the player position', () => {
            const px = 200,
                py = 300,
                radius = 15;
            renderer.drawPlayer(mockGrim, px, py, 0, radius);

            const size = radius * 2.5;
            expect(mockGrim.calls.drawQuad[0]).toEqual({
                x: px - size / 2,
                y: py - size / 2,
                w: size,
                h: size,
            });
        });

        it('should apply shield flash effect', () => {
            renderer.drawPlayer(mockGrim, 100, 100, 0, 15, { shieldTimer: 1.0 });

            // When shield is active, blue channel should be 255
            const color = mockGrim.calls.setColor[0];
            expect(color.b).toBe(255);
            expect(color.a).toBe(255);
        });
    });

    describe('drawEnemy rotation', () => {
        // drawEnemy now does two-pass rendering (glow + main), so:
        // - 3 setRotation calls: glow pass, main pass, reset to 0
        // - 2 setColor calls: glow pass (alpha*0.4), main pass (full alpha)
        // - 1 setAtlasFrame call (shared by both passes)

        it('should call setRotation with angle directly (enemy sprites face right in texture)', () => {
            const angle = Math.PI / 3; // some angle
            renderer.drawEnemy(mockGrim, 200, 200, angle, 50);

            // 3 calls: glow pass, main pass, reset
            expect(mockGrim.calls.setRotation.length).toBe(3);
            expect(mockGrim.calls.setRotation[0]).toBeCloseTo(angle);
            expect(mockGrim.calls.setRotation[1]).toBeCloseTo(angle);
        });

        it('should reset rotation to 0 after drawing', () => {
            renderer.drawEnemy(mockGrim, 200, 200, 0, 50);

            const lastRotation = mockGrim.calls.setRotation[mockGrim.calls.setRotation.length - 1];
            expect(lastRotation).toBe(0);
        });

        it('should use setAtlasFrame for enemy sprite frame (rotation handles direction)', () => {
            renderer.drawEnemy(mockGrim, 200, 200, Math.PI, 50);

            // Verify setAtlasFrame is called with 8×8 atlas
            const atlasCall = mockGrim.calls.setAtlasFrame[0];
            expect(atlasCall.atlasSize).toBe(8);
            expect(atlasCall.frame).toBeGreaterThanOrEqual(0);
        });

        it('should apply tint color', () => {
            const tint = { r: 0.5, g: 0.8, b: 0.3 };
            renderer.drawEnemy(mockGrim, 200, 200, 0, 50, tint);

            // Main pass color (second setColor call) has full alpha
            const color = mockGrim.calls.setColor[1];
            expect(color.r).toBe(Math.floor(0.5 * 255));
            expect(color.g).toBe(Math.floor(0.8 * 255));
            expect(color.b).toBe(Math.floor(0.3 * 255));
            expect(color.a).toBe(255);
        });

        it('should use additive overlay for hit flash (not tint interpolation)', () => {
            const tint = { r: 0.5, g: 0.5, b: 0.5 };
            const hitFlash = 0.2; // max flash
            renderer.drawEnemy(mockGrim, 200, 200, 0, 50, tint, hitFlash);

            // With Fix 4: main-pass color should retain the original tint (NOT lerped to white)
            // The flash is an additive overlay, so main setColor stays at tint values
            const mainColor = mockGrim.calls.setColor[1]; // second setColor = main pass
            expect(mainColor.r).toBe(Math.floor(0.5 * 255));
            expect(mainColor.g).toBe(Math.floor(0.5 * 255));
            expect(mainColor.b).toBe(Math.floor(0.5 * 255));

            // Additive blend should be set for the flash overlay
            // setBlendMode is not tracked in this mock, but we can verify extra drawQuad calls
            // Normal: 2 draws (glow + main). With flash: +2 more draws = 4 total
            expect(mockGrim.calls.drawQuad.length).toBeGreaterThanOrEqual(4);
        });
    });

    describe('Rotation formula correctness (C code match)', () => {
        // C code: aim_heading = atan2(playerY - aimY, playerX - aimX) - PI/2
        // TS code: angle = atan2(dy, dx) where dy = aimY - playerY, dx = aimX - playerX
        // Therefore: C_aim_heading = atan2(-dy, -dx) - PI/2 = (angle + PI) - PI/2 = angle + PI/2
        // Net result: setRotation(angle + PI/2)

        it('should match C code rotation for mouse directly right of player', () => {
            // Mouse right of player: dx > 0, dy = 0 → angle = 0
            const angle = Math.atan2(0, 1); // = 0
            mockGrim.calls.setRotation = [];
            renderer.drawPlayer(mockGrim, 100, 100, angle, 15);

            // C code would compute: atan2(0, -1) - PI/2 = PI - PI/2 = PI/2
            // Our code: 0 + PI/2 = PI/2 — matches the C code
            expect(mockGrim.calls.setRotation[0]).toBeCloseTo(Math.PI / 2);
        });

        it('should match C code rotation for mouse directly below player', () => {
            // Mouse below player: dx = 0, dy > 0 → angle = PI/2
            const angle = Math.atan2(1, 0); // = PI/2
            mockGrim.calls.setRotation = [];
            renderer.drawPlayer(mockGrim, 100, 100, angle, 15);

            expect(mockGrim.calls.setRotation[0]).toBeCloseTo(Math.PI);
        });

        it('should produce distinct rotation values for 8 directions', () => {
            const rotationValues: number[] = [];
            const directions = 8;

            for (let i = 0; i < directions; i++) {
                const angle = (i * 2 * Math.PI) / directions;
                mockGrim.calls.setRotation = [];
                renderer.drawPlayer(mockGrim, 100, 100, angle, 15);
                rotationValues.push(mockGrim.calls.setRotation[0]);
            }

            // All 8 rotation values should be unique
            const uniqueValues = new Set(rotationValues.map((v) => v.toFixed(4)));
            expect(uniqueValues.size).toBe(8);
        });

        it('should produce continuous rotation (not snapped to 8 directions)', () => {
            // Test that a non-cardinal angle produces a non-snapped rotation
            const angle = 0.123; // arbitrary non-cardinal angle
            mockGrim.calls.setRotation = [];
            renderer.drawPlayer(mockGrim, 100, 100, angle, 15);

            const rotation = mockGrim.calls.setRotation[0];
            // Verify it's the exact expected value, not snapped
            expect(rotation).toBeCloseTo(0.123 + Math.PI / 2);
        });
    });
});

describe('SpriteSheetConfig - UV for rotation-based rendering', () => {
    it('getFrameUV column 0 should start at u=0', () => {
        const uv = getFrameUV(TROOPER_CONFIG, 0, 0);
        expect(uv.u0).toBe(0);
    });

    it('getFrameUV should produce correct UV for idle frame', () => {
        const idleRow = TROOPER_CONFIG.animations.idle.startRow;
        const uv = getFrameUV(TROOPER_CONFIG, 0, idleRow);

        const expectedCellWidth = TROOPER_CONFIG.frameWidth / TROOPER_CONFIG.sheetWidth;
        const expectedCellHeight = TROOPER_CONFIG.frameHeight / TROOPER_CONFIG.sheetHeight;

        expect(uv.u0).toBe(0);
        expect(uv.v0).toBeCloseTo(idleRow * expectedCellHeight);
        expect(uv.u1).toBeCloseTo(expectedCellWidth);
        expect(uv.v1).toBeCloseTo((idleRow + 1) * expectedCellHeight);
    });

    it('TROOPER_CONFIG UV cell size should be 0.125 (1/8 of sheet)', () => {
        // C code: UV step is 0.125 for the 8x8 trooper sheet
        const cellWidth = TROOPER_CONFIG.frameWidth / TROOPER_CONFIG.sheetWidth;
        const cellHeight = TROOPER_CONFIG.frameHeight / TROOPER_CONFIG.sheetHeight;
        expect(cellWidth).toBeCloseTo(0.125);
        expect(cellHeight).toBeCloseTo(0.125);
    });
});
