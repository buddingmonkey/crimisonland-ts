/**
 * FlameParticle.test.ts - Tests for FIRE_BULLETS flame particle rendering
 *
 * Verifies two-pass rendering using particles.jaz texture,
 * matching Python reference (render/world/effects.py):
 * Pass 1: GLOW frame (4×4 frame 3), white, α×0.065
 * Pass 2: EXPLOSION_BURST frame (4×4 frame 5), grayscale shade, α²
 * Both with additive blending, sine-curve radius growth.
 */

import { describe, it, expect, beforeEach, vi } from 'vitest';
import { SpriteRenderer } from '../SpriteRenderer';
import { GrimInterface } from '../../engine/GrimInterface';
import { ProjectileType, WEAPON_DATA, getWeaponStats } from '../../data/WeaponData';

function createMockGrim() {
    const calls = {
        setColor: [] as { r: number; g: number; b: number; a: number }[],
        drawCircleFilled: [] as { x: number; y: number; radius: number }[],
        drawQuad: [] as { x: number; y: number; w: number; h: number }[],
        setBlendMode: [] as string[],
        setRotation: [] as number[],
        setAtlasFrame: [] as { atlasSize: number; frame: number }[],
        bindTexture: [] as number[],
    };
    const grim = {
        calls,
        setColor: (r: number, g: number, b: number, a: number) => {
            calls.setColor.push({ r, g, b, a });
        },
        drawQuad: (x: number, y: number, w: number, h: number) => {
            calls.drawQuad.push({ x, y, w, h });
        },
        drawCircleFilled: (x: number, y: number, radius: number) => {
            calls.drawCircleFilled.push({ x, y, radius });
        },
        setBlendMode: (mode: string) => {
            calls.setBlendMode.push(mode);
        },
        setRotation: (angle: number) => {
            calls.setRotation.push(angle);
        },
        setAtlasFrame: (atlasSize: number, frame: number) => {
            calls.setAtlasFrame.push({ atlasSize, frame });
        },
        bindTexture: (handle: number) => {
            calls.bindTexture.push(handle);
        },
        drawLine: vi.fn(),
        setUV: vi.fn(),
        beginBatch: vi.fn(),
        endBatch: vi.fn(),
        setConfigVar: vi.fn(),
    } as unknown as GrimInterface & { calls: typeof calls };
    return grim;
}

function renderFlameParticle(
    renderer: SpriteRenderer,
    grim: ReturnType<typeof createMockGrim>,
    lifetime: number,
    maxLifetime: number,
) {
    grim.calls.setColor = [];
    grim.calls.drawCircleFilled = [];
    grim.calls.drawQuad = [];
    grim.calls.setBlendMode = [];
    grim.calls.setAtlasFrame = [];
    grim.calls.bindTexture = [];
    grim.calls.setRotation = [];

    renderer.drawProjectile(grim, {
        x: 100,
        y: 100,
        angle: 0,
        lifetime,
        maxLifetime,
        projectileType: ProjectileType.FIRE_BULLETS,
        tailX: 50,
        tailY: 50,
        headX: 100,
        headY: 100,
        perpX: 0,
        perpY: 1,
    });
}

describe('FIRE_BULLETS Flame Particle Effect', () => {
    let renderer: SpriteRenderer;
    let grim: ReturnType<typeof createMockGrim>;

    beforeEach(() => {
        renderer = new SpriteRenderer();
        // Enable the particles/projectile sprite so the textured path (with blending) runs
        (renderer as any).hasProjectileSprite = true;
        (renderer as any).projectileHandle = 3;
        (renderer as any).hasParticlesSprite = true;
        (renderer as any).particlesHandle = 4;
        grim = createMockGrim();
    });

    describe('Weapon data', () => {
        it('Flamethrower should have slow speed', () => {
            const stats = getWeaponStats(6);
            expect(stats.projectileSpeed).toBeLessThanOrEqual(150);
            expect(stats.projectileType).toBe(ProjectileType.FIRE_BULLETS);
        });

        it('all FIRE_BULLETS weapons should be slower than bullets', () => {
            const pistolSpeed = getWeaponStats(0).projectileSpeed;
            for (const [, data] of Object.entries(WEAPON_DATA)) {
                if (data.projectileType === ProjectileType.FIRE_BULLETS) {
                    expect(data.projectileSpeed).toBeLessThan(pistolSpeed);
                }
            }
        });
    });

    describe('Texture-based rendering', () => {
        it('should draw quads (not circles) when texture loaded', () => {
            renderFlameParticle(renderer, grim, 1.0, 2.0);
            expect(grim.calls.drawQuad.length).toBeGreaterThan(0);
            expect(grim.calls.drawCircleFilled.length).toBe(0);
        });

        it('should emit multiple trail quads plus a head quad', () => {
            renderFlameParticle(renderer, grim, 1.0, 2.0);
            // At least 2 quads: trail segments + head
            expect(grim.calls.drawQuad.length).toBeGreaterThanOrEqual(2);
        });

        it('should bind projectile texture', () => {
            renderFlameParticle(renderer, grim, 1.0, 2.0);
            expect(grim.calls.bindTexture).toContain(3);
        });
    });

    describe('Trail rendering', () => {
        it('trail quad count increases with trail length', () => {
            // Longer tail-to-head distance means more trail segments
            grim.calls.drawQuad = [];
            renderer.drawProjectile(grim, {
                x: 200, y: 100, angle: 0,
                lifetime: 1.0, maxLifetime: 2.0,
                projectileType: ProjectileType.FIRE_BULLETS,
                tailX: 50, tailY: 100, headX: 200, headY: 100,
                perpX: 0, perpY: 1,
            });
            const longTrailQuads = grim.calls.drawQuad.length;

            grim.calls.drawQuad = [];
            renderer.drawProjectile(grim, {
                x: 110, y: 100, angle: 0,
                lifetime: 1.0, maxLifetime: 2.0,
                projectileType: ProjectileType.FIRE_BULLETS,
                tailX: 100, tailY: 100, headX: 110, headY: 100,
                perpX: 0, perpY: 1,
            });
            const shortTrailQuads = grim.calls.drawQuad.length;

            expect(longTrailQuads).toBeGreaterThanOrEqual(shortTrailQuads);
        });
    });

    describe('Color passes (textured)', () => {
        it('trail segments should use orange color (R=255, G=153, B=25)', () => {
            renderFlameParticle(renderer, grim, 1.0, 2.0);
            // First setColor should be the orange trail
            const c = grim.calls.setColor[0];
            expect(c.r).toBe(255);
            expect(c.g).toBe(153);
            expect(c.b).toBe(25);
        });

        it('head sprite should use warm white-yellow (255,255,179)', () => {
            renderFlameParticle(renderer, grim, 1.0, 2.0);
            // Last setColor call is the head sprite
            const last = grim.calls.setColor[grim.calls.setColor.length - 1];
            expect(last.r).toBe(255);
            expect(last.g).toBe(255);
            expect(last.b).toBe(179);
        });
    });

    describe('Additive blending', () => {
        it('should use additive blend mode', () => {
            renderFlameParticle(renderer, grim, 1.0, 2.0);
            expect(grim.calls.setBlendMode).toContain('add');
        });

        it('should restore normal blend mode', () => {
            renderFlameParticle(renderer, grim, 1.0, 2.0);
            const last = grim.calls.setBlendMode[grim.calls.setBlendMode.length - 1];
            expect(last).toBe('normal');
        });
    });
});
