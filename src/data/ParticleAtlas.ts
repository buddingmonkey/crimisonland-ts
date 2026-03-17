/**
 * ParticleAtlas.ts — Single source of truth for the particles.jaz texture atlas
 *
 * The particles texture (256×256 px) is packed inside crimson.paq as "game/particles.jaz".
 * It is subdivided into grids of varying cell size:
 *
 *   gridSize 2  → 2×2 grid  → 128×128 px cells
 *   gridSize 4  → 4×4 grid  →  64× 64 px cells
 *   gridSize 8  → 8×8 grid  →  32× 32 px cells
 *   gridSize 16 → 16×16 grid → 16× 16 px cells
 *
 * C code equivalence:
 *   gridSize 2  = sizeCode 0x80
 *   gridSize 4  = sizeCode 0x40
 *   gridSize 8  = sizeCode 0x20
 *   gridSize 16 = sizeCode 0x10
 *
 * Frame index is row-major: frame = col + row × gridSize
 *
 * ═══════════════════════════════════════════════════════════
 *  HUMAN-VERIFIED 8×8 GRID (32×32 px per cell)
 * ═══════════════════════════════════════════════════════════
 *
 *         Col 0           Col 1         Col 2         Col 3         Col 4            Col 5           Col 6           Col 7
 *  Row 0: Bubble(Shield)  Blood Lg 1    Blood Lg 2    Blood Lg 3    Blood Med        Blood Small     Yellow Glow 0,0 Yellow Glow 1,0
 *  Row 1: Ice Small 1     Ice Small 2   Ice Small 3   Bullet Casing Empty            Empty           Yellow Glow 0,1 Yellow Glow 1,1
 *  Row 2: Ice Large 0,0   Ice Large 1,0 Explosion 0,0 Explosion 1,0 White Glow 0,0   White Glow 1,0  Smoke 0,0       Smoke 1,0
 *  Row 3: Ice Large 0,1   Ice Large 1,1 Explosion 0,1 Explosion 1,1 White Glow 0,1   White Glow 1,1  Smoke 0,1       Smoke 1,1
 *  Row 4: Burst 0,0       Burst 1,0     Burst 2,0     Burst 3,0     Large Circle 0,0 Lg Circle 1,0   Lg Circle 2,0   Lg Circle 3,0
 *  Row 5: Burst 0,1       Burst 1,1     Burst 2,1     Burst 3,1     Large Circle 0,1 Lg Circle 1,1   Lg Circle 2,1   Lg Circle 3,1
 *  Row 6: Burst 0,2       Burst 1,2     Burst 2,2     Burst 3,2     Large Circle 0,2 Lg Circle 2,2   Lg Circle 2,2   Lg Circle 3,2
 *  Row 7: Burst 0,3       Burst 1,3     Burst 2,3     Burst 3,3     Large Circle 0,3 Lg Circle 1,3   Lg Circle 2,3   Lg Circle 3,3
 *
 * Multi-cell sprites:
 *   Yellow Glow : 2×2 cells (cols 6-7, rows 0-1) = 64×64 px
 *   Ice Large   : 2×2 cells (cols 0-1, rows 2-3) = 64×64 px
 *   Explosion   : 2×2 cells (cols 2-3, rows 2-3) = 64×64 px
 *   White Glow  : 2×2 cells (cols 4-5, rows 2-3) = 64×64 px
 *   Smoke       : 2×2 cells (cols 6-7, rows 2-3) = 64×64 px
 *   Burst       : 4×4 cells (cols 0-3, rows 4-7) = 128×128 px
 *   Large Circle: 4×4 cells (cols 4-7, rows 4-7) = 128×128 px
 *
 * ═══════════════════════════════════════════════════════════
 *  4×4 GRID VISUAL MAP (64×64 px per cell)
 *  See: docs/particle-atlas-reference.md for full details
 * ═══════════════════════════════════════════════════════════
 *
 *  Frame  0 (  0,  0): Bubble (Shield) disc + blood/ice fragments
 *  Frame  1 ( 64,  0): Blood/ice fragments + bullet casing
 *  Frame  2 (128,  0): Blood Med + Blood Small + empty
 *  Frame  3 (192,  0): Yellow Glow (complete 64×64)
 *  Frame  4 (  0, 64): Ice Large (complete 64×64)
 *  Frame  5 ( 64, 64): Explosion (complete 64×64)
 *  Frame  6 (128, 64): White Glow (complete 64×64)
 *  Frame  7 (192, 64): Smoke (complete 64×64)
 *  Frame  8 (  0,128): Burst top-left quarter
 *  Frame  9 ( 64,128): Burst top-right quarter
 *  Frame 10 (128,128): Large Circle top-left quarter
 *  Frame 11 (192,128): Large Circle top-right quarter
 *  Frame 12 (  0,192): Burst bottom-left quarter
 *  Frame 13 ( 64,192): Burst bottom-right quarter
 *  Frame 14 (128,192): Large Circle bottom-left quarter
 *  Frame 15 (192,192): Large Circle bottom-right quarter
 *
 * ═══════════════════════════════════════════════════════════
 *  8×8 GRID — used for blood splats and small sprites
 * ═══════════════════════════════════════════════════════════
 *
 *  See docs/particle-atlas-reference.md for 8×8 layout
 *
 * C code: c_code_breakdown/effect_id_table.c
 */

// ========================================================================
// ParticleFrame — named constants for every atlas sprite
//
// The numeric value is the "effect ID" used throughout the C code.
// Use these instead of raw hex/decimal IDs in spawn calls.
// ========================================================================

export enum ParticleFrame {
    /** Bubble (Shield) glow disc at (0,0). Used for bursts, shockwaves, fire ring particles, bonus sparkles. */
    GLOW_SOFT = 0x00,

    /** Top-left 128px quadrant (2×2 grid). Used for expansion flashes, electric arcs, plasma explosions. */
    EXPANSION_FLASH = 0x01,

    /** Bubble (Shield) disc at (0,0). Used for shield overlay around player, projectile glow rendering. */
    PROJECTILE_TRAIL = 0x02,

    /** Blood Large 2 (8×8 grid, row 0 col 2). */
    BLOOD_SPLAT_A = 0x03,

    /** Blood Large 3 (8×8 grid, row 0 col 3). */
    BLOOD_SPLAT_B = 0x04,

    /** Blood Medium (8×8 grid, row 0 col 4). */
    BLOOD_SPLAT_C = 0x05,

    /** Blood Small (8×8 grid, row 0 col 5). */
    BLOOD_SPLAT_D = 0x06,

    /** White Glow at (128,64), tinted red for flying blood particles. */
    BLOOD_SPLATTER = 0x07,

    /** Ice Small 1 at (0,32) — 8×8 grid row 1, col 0. Freeze shard variant A. */
    FREEZE_SHARD_A = 0x08,

    /** Ice Small 2 at (32,32) — 8×8 grid row 1, col 1. Freeze shard variant B. */
    FREEZE_SHARD_B = 0x09,

    /** Ice Small 3 at (64,32) — 8×8 grid row 1, col 2. Freeze shard variant C. */
    FREEZE_SHARD_C = 0x0a,

    /** Explosion sprite at (64,64). Complete 64×64 fire/explosion shape. Used for flame particles. */
    FLAME_SPRITE = 0x0b,

    /** Explosion sprite at (64,64). Used for fire particle render pass 2 (effect 0x0c). */
    EXPLOSION_SPARKLE = 0x0c,

    /** Yellow Glow at (192,0). Used for cursor, aim enhancement, flame glow halos. */
    GLOW_ORB = 0x0d,

    /** Ice Large chunk at (0,64). Drawn over frozen creatures as ice overlay, and used for shatter crystals. */
    FREEZE_OVERLAY = 0x0e,

    /** Large Circle ring (2×2 grid, frame 3 = bottom-right 128×128 quadrant, cols 4-7 rows 4-7).
     *  Used for nuke explosion expansion ring and reflex boost halo — scales up with alpha fade. */
    EXPANSION_RING = 0x0f,

    /** Bubble (Shield) disc at (0,0). Drawn as black disc for shadows, bonus bases. */
    SHADOW_DISC = 0x10,

    /** Smoke sprite at (192,64). Complete 64×64 smoke puff. Used as smoke ring in explosion bursts. */
    SMOKE_RING = 0x11,

    /** Blood Med/Small area at (128,0). Contains tiny brass bullet casing sprite. */
    SHELL_CASING = 0x12,
}

// ========================================================================
// Atlas entry: gridSize + frame index for each ParticleFrame
// ========================================================================

export interface ParticleAtlasEntry {
    /** Grid subdivision: 2, 4, 8, or 16. Determines cell pixel size (256/gridSize). */
    gridSize: number;
    /** Row-major cell index: frame = col + row × gridSize */
    frame: number;
}

/**
 * Master lookup table: ParticleFrame → atlas grid + frame.
 *
 * This is the single source of truth for all particle/effect texture UVs.
 * Matches C code: c_code_breakdown/effect_id_table.c
 */
export const PARTICLE_ATLAS: Record<ParticleFrame, ParticleAtlasEntry> = {
    [ParticleFrame.GLOW_SOFT]: { gridSize: 4, frame: 0 },
    [ParticleFrame.EXPANSION_FLASH]: { gridSize: 2, frame: 0 },
    [ParticleFrame.PROJECTILE_TRAIL]: { gridSize: 4, frame: 0 },
    [ParticleFrame.BLOOD_SPLAT_A]: { gridSize: 8, frame: 2 },
    [ParticleFrame.BLOOD_SPLAT_B]: { gridSize: 8, frame: 3 },
    [ParticleFrame.BLOOD_SPLAT_C]: { gridSize: 8, frame: 4 },
    [ParticleFrame.BLOOD_SPLAT_D]: { gridSize: 8, frame: 5 },
    [ParticleFrame.BLOOD_SPLATTER]: { gridSize: 4, frame: 6 },
    [ParticleFrame.FREEZE_SHARD_A]: { gridSize: 8, frame: 8 },
    [ParticleFrame.FREEZE_SHARD_B]: { gridSize: 8, frame: 9 },
    [ParticleFrame.FREEZE_SHARD_C]: { gridSize: 8, frame: 10 },
    [ParticleFrame.FLAME_SPRITE]: { gridSize: 4, frame: 5 },
    [ParticleFrame.EXPLOSION_SPARKLE]: { gridSize: 4, frame: 5 },
    [ParticleFrame.GLOW_ORB]: { gridSize: 4, frame: 3 },
    [ParticleFrame.FREEZE_OVERLAY]: { gridSize: 4, frame: 4 },
    [ParticleFrame.EXPANSION_RING]: { gridSize: 2, frame: 3 },
    [ParticleFrame.SHADOW_DISC]: { gridSize: 4, frame: 0 },
    [ParticleFrame.SMOKE_RING]: { gridSize: 4, frame: 7 },
    [ParticleFrame.SHELL_CASING]: { gridSize: 4, frame: 2 },
};

// ========================================================================
// UV computation helpers
// ========================================================================

export interface AtlasUV {
    u0: number;
    v0: number;
    u1: number;
    v1: number;
}

/**
 * Compute UV rect for a ParticleFrame.
 *
 * @example
 * ```ts
 * const uv = getParticleUV(ParticleFrame.FREEZE_SHARD_A);
 * // → { u0: 0.25, v0: 0.75, u1: 0.5, v1: 1.0 }
 * ```
 */
export function getParticleUV(id: ParticleFrame): AtlasUV {
    const entry = PARTICLE_ATLAS[id];
    if (!entry) {
        // Fallback: full texture
        return { u0: 0, v0: 0, u1: 1, v1: 1 };
    }
    const cellSize = 1.0 / entry.gridSize;
    const col = entry.frame % entry.gridSize;
    const row = Math.floor(entry.frame / entry.gridSize);
    return {
        u0: col * cellSize,
        v0: row * cellSize,
        u1: (col + 1) * cellSize,
        v1: (row + 1) * cellSize,
    };
}

/**
 * Get the (atlasSize, frame) pair for grim.setAtlasFrame().
 *
 * @example
 * ```ts
 * const { atlasSize, frame } = getParticleAtlasFrame(ParticleFrame.GLOW_ORB);
 * grim.setAtlasFrame(atlasSize, frame);
 * ```
 */
export function getParticleAtlasFrame(id: ParticleFrame): { atlasSize: number; frame: number } {
    const entry = PARTICLE_ATLAS[id];
    if (!entry) {
        return { atlasSize: 4, frame: 0 }; // fallback
    }
    return { atlasSize: entry.gridSize, frame: entry.frame };
}

/**
 * Compute UV rect from raw gridSize + frame (for use outside the enum).
 * Prefer getParticleUV(ParticleFrame.X) when possible.
 */
export function getFrameUV(gridSize: number, frame: number): AtlasUV {
    const cellSize = 1.0 / gridSize;
    const col = frame % gridSize;
    const row = Math.floor(frame / gridSize);
    return {
        u0: col * cellSize,
        v0: row * cellSize,
        u1: (col + 1) * cellSize,
        v1: (row + 1) * cellSize,
    };
}
