/**
 * ParticleAtlas.test.ts — Validates the particle atlas lookup table
 *
 * Ensures:
 * 1. Every ParticleFrame enum value has a valid PARTICLE_ATLAS entry
 * 2. getParticleUV returns valid UV ranges
 * 3. getParticleAtlasFrame returns valid atlas parameters
 * 4. Table matches C code's effect_id_table values
 */

import { describe, it, expect } from 'vitest';
import {
    ParticleFrame,
    PARTICLE_ATLAS,
    getParticleUV,
    getParticleAtlasFrame,
    getFrameUV,
} from '../ParticleAtlas';

// All ParticleFrame enum values (numeric members only)
const ALL_FRAMES = Object.values(ParticleFrame).filter(
    (v): v is ParticleFrame => typeof v === 'number',
);

describe('ParticleAtlas', () => {
    describe('PARTICLE_ATLAS table completeness', () => {
        it('should have an entry for every ParticleFrame enum value', () => {
            for (const frame of ALL_FRAMES) {
                const entry = PARTICLE_ATLAS[frame];
                expect(entry, `Missing PARTICLE_ATLAS entry for ParticleFrame ${frame} (0x${frame.toString(16)})`).toBeDefined();
            }
        });

        it('should have valid gridSize for every entry', () => {
            const validGridSizes = [2, 4, 8, 16];
            for (const frame of ALL_FRAMES) {
                const entry = PARTICLE_ATLAS[frame];
                expect(validGridSizes, `Invalid gridSize ${entry.gridSize} for ParticleFrame 0x${frame.toString(16)}`)
                    .toContain(entry.gridSize);
            }
        });

        it('should have frame index within grid bounds', () => {
            for (const frame of ALL_FRAMES) {
                const entry = PARTICLE_ATLAS[frame];
                const maxFrame = entry.gridSize * entry.gridSize - 1;
                expect(entry.frame).toBeGreaterThanOrEqual(0);
                expect(entry.frame).toBeLessThanOrEqual(maxFrame);
            }
        });
    });

    describe('getParticleUV', () => {
        it('should return UVs in [0,1] range for all frames', () => {
            for (const frame of ALL_FRAMES) {
                const uv = getParticleUV(frame);
                expect(uv.u0).toBeGreaterThanOrEqual(0);
                expect(uv.v0).toBeGreaterThanOrEqual(0);
                expect(uv.u1).toBeLessThanOrEqual(1);
                expect(uv.v1).toBeLessThanOrEqual(1);
            }
        });

        it('should return non-degenerate UVs (u0 < u1, v0 < v1)', () => {
            for (const frame of ALL_FRAMES) {
                const uv = getParticleUV(frame);
                expect(uv.u0).toBeLessThan(uv.u1);
                expect(uv.v0).toBeLessThan(uv.v1);
            }
        });

        it('should compute correct UVs for GLOW_ORB (4×4 grid, frame 3)', () => {
            const uv = getParticleUV(ParticleFrame.GLOW_ORB);
            // Frame 3 in 4×4: col=3, row=0 → u0=0.75, v0=0, u1=1.0, v1=0.25
            expect(uv.u0).toBeCloseTo(0.75);
            expect(uv.v0).toBeCloseTo(0.0);
            expect(uv.u1).toBeCloseTo(1.0);
            expect(uv.v1).toBeCloseTo(0.25);
        });

        it('should compute correct UVs for EXPANSION_FLASH (2×2 grid, frame 0)', () => {
            const uv = getParticleUV(ParticleFrame.EXPANSION_FLASH);
            // Frame 0 in 2×2: col=0, row=0 → u0=0, v0=0, u1=0.5, v1=0.5
            expect(uv.u0).toBeCloseTo(0.0);
            expect(uv.v0).toBeCloseTo(0.0);
            expect(uv.u1).toBeCloseTo(0.5);
            expect(uv.v1).toBeCloseTo(0.5);
        });

        it('should compute correct UVs for FREEZE_SHARD_A (8×8 grid, frame 8)', () => {
            const uv = getParticleUV(ParticleFrame.FREEZE_SHARD_A);
            // Frame 8 in 8×8: col=0, row=1 → u0=0, v0=0.125, u1=0.125, v1=0.25
            expect(uv.u0).toBeCloseTo(0.0);
            expect(uv.v0).toBeCloseTo(0.125);
            expect(uv.u1).toBeCloseTo(0.125);
            expect(uv.v1).toBeCloseTo(0.25);
        });
    });

    describe('getParticleAtlasFrame', () => {
        it('should return valid atlasSize and frame for all ParticleFrames', () => {
            for (const frame of ALL_FRAMES) {
                const result = getParticleAtlasFrame(frame);
                expect(result.atlasSize).toBeGreaterThan(0);
                expect(result.frame).toBeGreaterThanOrEqual(0);
            }
        });

        it('should match PARTICLE_ATLAS values', () => {
            for (const frame of ALL_FRAMES) {
                const result = getParticleAtlasFrame(frame);
                const entry = PARTICLE_ATLAS[frame];
                expect(result.atlasSize).toBe(entry.gridSize);
                expect(result.frame).toBe(entry.frame);
            }
        });
    });

    describe('getFrameUV (raw helper)', () => {
        it('should compute correct UVs for 4×4 grid frame 0', () => {
            const uv = getFrameUV(4, 0);
            expect(uv.u0).toBeCloseTo(0.0);
            expect(uv.v0).toBeCloseTo(0.0);
            expect(uv.u1).toBeCloseTo(0.25);
            expect(uv.v1).toBeCloseTo(0.25);
        });

        it('should compute correct UVs for 8×8 grid frame 5', () => {
            const uv = getFrameUV(8, 5);
            // Frame 5 in 8×8: col=5, row=0 → u0=5/8, v0=0, u1=6/8, v1=1/8
            expect(uv.u0).toBeCloseTo(5 / 8);
            expect(uv.v0).toBeCloseTo(0.0);
            expect(uv.u1).toBeCloseTo(6 / 8);
            expect(uv.v1).toBeCloseTo(1 / 8);
        });
    });

    describe('C code effect_id_table parity', () => {
        // These values are from c_code_breakdown/effect_id_table.c
        // If this test fails, the atlas table has drifted from the C code.
        const C_EFFECT_ID_TABLE: [number, number, number][] = [
            // [effectId, C_sizeCode, C_frame]
            [0x00, 0x40, 0],
            [0x01, 0x80, 0],
            [0x02, 0x40, 0],
            [0x07, 0x40, 6],
            [0x08, 0x20, 8],
            [0x09, 0x20, 9],
            [0x0a, 0x20, 10],
            [0x0c, 0x40, 5],
            [0x0d, 0x40, 3],
            [0x0e, 0x40, 4], // Visual fix: C uses frame 8 (Burst quarter) but frame 4 (Ice Large) is visually correct
            [0x0f, 0x80, 3],
            [0x10, 0x40, 0],
            [0x11, 0x40, 7], // Visual fix: C uses frame 11 (Large Circle TR quarter) but frame 7 (Smoke) is visually correct
            [0x12, 0x40, 2],
        ];

        // Convert C sizeCode to gridSize
        function sizeCodeToGrid(code: number): number {
            switch (code) {
                case 0x10: return 16;
                case 0x20: return 8;
                case 0x40: return 4;
                case 0x80: return 2;
                default: return 4;
            }
        }

        it.each(C_EFFECT_ID_TABLE)(
            'effect ID 0x%s should match C table (sizeCode=0x%s, frame=%i)',
            (effectId, sizeCode, frame) => {
                const entry = PARTICLE_ATLAS[effectId as ParticleFrame];
                expect(entry).toBeDefined();
                expect(entry.gridSize).toBe(sizeCodeToGrid(sizeCode));
                expect(entry.frame).toBe(frame);
            },
        );
    });
});
