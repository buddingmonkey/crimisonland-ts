/**
 * SpriteSheetConfig.ts - Configuration for sprite sheet animations
 *
 * Defines the layout and animation data for sprite sheets in the game.
 * Used by SpriteRenderer to select the correct frame based on entity
 * facing direction and animation state.
 *
 * C code reference: creature_type_table in gameplay.c L1375-1440
 * Rendering: creature_render_type in creatures.c L260-546
 * Animation: creature_update_all in creatures.c L1475-1500
 */

export interface AnimationDef {
    startRow: number; // Starting row in the sprite sheet
    frameCount: number; // Number of animation frames
    frameRate: number; // Frames per second
}

export interface SpriteSheetConfig {
    // Sprite sheet dimensions
    sheetWidth: number; // Total width in pixels
    sheetHeight: number; // Total height in pixels
    frameWidth: number; // Width of each frame
    frameHeight: number; // Height of each frame
    columns: number; // Number of columns (usually = directions)
    rows: number; // Number of rows

    // Animation definitions
    animations: {
        idle: AnimationDef;
        walk: AnimationDef;
        death?: AnimationDef;
    };
}

/**
 * Creature type configuration matching C code's creature_type_table.
 * Each entry corresponds to a C type_id (0-5).
 *
 * C code fields:
 * - texture_handle: which .jaz texture to bind
 * - base_frame: starting atlas frame for non-standard walk/death
 * - anim_flags: &1 = bounce animation (0→15→0), &0 = linear (0→31)
 * - anim_rate: animation speed multiplier
 * - corpse_frame: index into bodyset.jaz 4×4 atlas for corpse sprite
 */
export interface CreatureTypeConfig {
    textureKey: string; // Asset path in PAQ (e.g. 'game/zombie.jaz')
    baseFrame: number; // C: base_frame (frame offset for walk/death)
    animFlags: number; // C: anim_flags (1 = bounce walk)
    animRate: number; // C: anim_rate (animation speed multiplier)
    corpseFrame: number; // C: corpse_frame (index into bodyset 4×4)
}

/**
 * Creature type table — indexed by EnemyType enum (matches C type_id).
 *
 * From gameplay.c gameplay_reset_state() L1375-1440:
 * Type 0: zombie.jaz,      base=0x20, flags=0, rate=1.2,  corpse=0
 * Type 1: lizard.jaz,      base=0x10, flags=1, rate=1.6,  corpse=3
 * Type 2: alien.jaz,       base=0x20, flags=0, rate=1.35, corpse=4  (the main "alien/bug" enemy)
 * Type 3: spider_sp1.jaz,  base=0x10, flags=1, rate=1.5,  corpse=1
 * Type 4: spider_sp2.jaz,  base=0x10, flags=1, rate=1.5,  corpse=2
 * Type 5: trooper.jaz,     base=0x10, flags=1, rate=1.0,  corpse=2 (reuses spider2 corpse)
 *
 * NOTE: Ghidra's creature_type_table variable naming was misleading.
 * Cross-referenced with Python port to confirm correct sprite mapping.
 */
export const CREATURE_TYPE_TABLE: CreatureTypeConfig[] = [
    // Type 0 - Zombie (slow, tough)
    {
        textureKey: 'game/zombie.jaz',
        baseFrame: 0x20, // 32
        animFlags: 0, // Linear walk: 0→31
        animRate: 1.2,
        corpseFrame: 0,
    },
    // Type 1 - Lizard
    {
        textureKey: 'game/lizard.jaz',
        baseFrame: 0x10, // 16
        animFlags: 1, // Bounce walk: 0→7→0
        animRate: 1.6, // 0x3fcccccd
        corpseFrame: 3,
    },
    // Type 2 - Alien (the common "alien/bug" enemy seen in most quests, uses alien.jaz)
    {
        textureKey: 'game/alien.jaz',
        baseFrame: 0x20, // 32
        animFlags: 0, // Linear walk: 0→31
        animRate: 1.35, // 0x3faccccd
        corpseFrame: 4,
    },
    // Type 3 - Spider SP1 (uses spider_sp1.jaz)
    {
        textureKey: 'game/spider_sp1.jaz',
        baseFrame: 0x10, // 16
        animFlags: 1, // Bounce walk: 0→7→0
        animRate: 1.5, // 0x3fc00000
        corpseFrame: 1,
    },
    // Type 4 - Spider SP2 (fast variant, uses spider_sp2.jaz)
    {
        textureKey: 'game/spider_sp2.jaz',
        baseFrame: 0x10, // 16
        animFlags: 1, // Bounce walk: 0→7→0
        animRate: 1.5, // 0x3fc00000
        corpseFrame: 2,
    },
    // Type 5 - Trooper (enemy trooper)
    {
        textureKey: 'game/trooper.jaz',
        baseFrame: 0x10, // 16
        animFlags: 1, // Bounce walk
        animRate: 1.0,
        corpseFrame: 2, // Reuses spider2 corpse
    },
];

/**
 * Trooper (player) sprite sheet configuration
 * Based on visual analysis of trooper.jaz (512x512, 8x8 grid = 64x64 frames):
 * - 8 columns = 8 facing directions
 * - Rows 0-1: Small icons/particles (very tiny)
 * - Rows 2-3: Standing trooper poses (idle and walk animation)
 * - Rows 4-7: Death/falling sequence (large diving/prone sprites)
 *
 * Note: Rows 2-3 are the primary gameplay sprites. Rows 4-7 are death sequence.
 */
export const TROOPER_CONFIG: SpriteSheetConfig = {
    sheetWidth: 512,
    sheetHeight: 512,
    frameWidth: 64,
    frameHeight: 64,
    columns: 8,
    rows: 8,
    animations: {
        idle: { startRow: 2, frameCount: 1, frameRate: 1 },
        walk: { startRow: 2, frameCount: 2, frameRate: 8 }, // Rows 2-3: standing walk cycle
        death: { startRow: 4, frameCount: 4, frameRate: 4 }, // Rows 4-7: falling to prone
    },
};

/**
 * Generic enemy sprite sheet configuration (legacy, kept for compatibility)
 * All enemies use 512×512 / 8×8 grid = 64×64 cells
 */
export const ENEMY_CONFIG: SpriteSheetConfig = {
    sheetWidth: 512,
    sheetHeight: 512,
    frameWidth: 64,
    frameHeight: 64,
    columns: 8,
    rows: 8,
    animations: {
        idle: { startRow: 0, frameCount: 1, frameRate: 1 },
        walk: { startRow: 0, frameCount: 4, frameRate: 8 },
        death: { startRow: 4, frameCount: 2, frameRate: 3 },
    },
};

/**
 * Convert an angle (radians) to a direction index (0-7)
 *
 * Sprite sheet column layout (trooper.jaz) - COUNTER-CLOCKWISE order:
 *   Col 0 = SW (135°)    Col 4 = NE (-45° / 315°)
 *   Col 1 = S  (90°)     Col 5 = N  (-90° / 270°)
 *   Col 2 = SE (45°)     Col 6 = NW (-135° / 225°)
 *   Col 3 = E  (0°)      Col 7 = W  (180° / -180°)
 *
 * The columns go from 135° down to -135° (counter-clockwise decreasing).
 * Angle 0 = facing right (E) = Column 3
 */
export function angleToDirectionIndex(angle: number, directions: number = 8): number {
    // Normalize angle to 0..2π
    const twoPi = Math.PI * 2;
    const normalized = ((angle % twoPi) + twoPi) % twoPi;

    // Calculate sector size and offset for centering
    const sectorSize = twoPi / directions;
    const halfSector = sectorSize / 2;

    // Calculate base index (0 = East, counting clockwise in radians)
    const baseIndex = Math.floor((normalized + halfSector) / sectorSize) % directions;

    // The sprite sheet is COUNTER-CLOCKWISE, so we SUBTRACT the baseIndex
    // E (angle 0, baseIndex 0) maps to Column 3
    // S (angle π/2, baseIndex 2) maps to Column 1 (3 - 2 = 1)
    // W (angle π, baseIndex 4) maps to Column 7 (3 - 4 + 8 = 7)
    const offsetIndex = (directions + 3 - baseIndex) % directions;

    return offsetIndex;
}

/**
 * Calculate UV coordinates for a specific frame in a sprite sheet
 */
export function getFrameUV(
    config: SpriteSheetConfig,
    column: number,
    row: number,
): { u0: number; v0: number; u1: number; v1: number } {
    const cellWidth = config.frameWidth / config.sheetWidth;
    const cellHeight = config.frameHeight / config.sheetHeight;

    return {
        u0: column * cellWidth,
        v0: row * cellHeight,
        u1: (column + 1) * cellWidth,
        v1: (row + 1) * cellHeight,
    };
}

/**
 * Get the current animation frame based on timer
 */
export function getAnimationFrame(animation: AnimationDef, timer: number): number {
    const frameIndex = Math.floor(timer * animation.frameRate) % animation.frameCount;
    return animation.startRow + frameIndex;
}
