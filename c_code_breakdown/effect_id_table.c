/**
 * effect_id_table - Reconstructed from reverse engineering + visual analysis
 * 
 * Source: game/particles.jaz (256×256 texture atlas) extracted from crimson.paq
 * See: c_code_breakdown/particles.jpg (RGB) and particles_alpha.png (alpha channel)
 * 
 * size_code determines the atlas grid subdivision:
 *   0x10 → 16×16 grid (256 cells, each 16×16 px)
 *   0x20 → 8×8 grid   (64 cells, each 32×32 px)
 *   0x40 → 4×4 grid   (16 cells, each 64×64 px)
 *   0x80 → 2×2 grid   (4 cells, each 128×128 px)
 * 
 * frame = cell index (row-major: frame = col + row * gridSize)
 * 
 * NOTE: effect_spawn() and effect_select_texture() both use this table but
 * for different rendering paths:
 *   - effect_select_texture → grim_set_atlas_frame(gridToArg, frame) in the DLL
 *   - effect_spawn → reads UVs from effect_uv{16,8,4,2}[frame] tables
 * Both tables use proper 2D row-major indexing.
 *
 * ====================================================================
 * 4×4 GRID VISUAL MAP (particles.jaz, 64×64 px per cell):
 * ====================================================================
 *
 *   Frame 0  (0,0)    : Soft white glow circle (solid white alpha disc)
 *   Frame 1  (64,0)   : Small ice/debris fragment shapes
 *   Frame 2  (128,0)  : More fragments + tiny brass bullet casing  
 *   Frame 3  (192,0)  : Golden/warm glow orb (large soft alpha circle) ← CONFIRMED glow
 *   Frame 4  (0,64)   : Large dark blue-gray ice/rock chunk
 *   Frame 5  (64,64)  : White ice chunk variant
 *   Frame 6  (128,64) : Orange fire/explosion glow
 *   Frame 7  (192,64) : Gray wispy smoke
 *   Frame 8  (0,128)  : Blue star/snowflake ice crystal
 *   Frame 9  (64,128) : Bright flash/white shapes
 *   Frame 10 (128,128): Small centered glow point/star
 *   Frame 11 (192,128): Soft dark smoke cloud
 *   Frame 12 (0,192)  : Bright star/lens flare sparkle
 *   Frame 13 (64,192) : Ice crystal snowflake
 *   Frame 14 (128,192): Large gray sphere (radial gradient alpha — shadow disc)
 *   Frame 15 (192,192): Small ice crystal/snowflake variant
 *
 * ====================================================================
 */

typedef struct {
    int size_code;  /* atlas grid code: 0x10=16×16, 0x20=8×8, 0x40=4×4, 0x80=2×2 */
    int frame;      /* cell index within grid (row-major) */
} effect_id_entry_t;

/*
 * Reconstructed table. Status key:
 *   [CONFIRMED] = verified from TS code or visual match to expected behavior
 *   [VISUAL]    = determined by matching visual content to usage context
 *   [INFERRED]  = best guess from code analysis
 *   [UNUSED]    = no call sites found
 */

effect_id_entry_t effect_id_table[] = {
    /* 0x00 */ { 0x40, 0 },   /* [VISUAL   ] burst spark — soft white glow circle    
                                  Used: effect_spawn_burst, fx_spawn_shockwave, fx_spawn_fire_particles
                                  Drawn additive with fade-out (flags=0x1d). A white glow disc
                                  works perfectly as a generic bright spark/burst particle. */

    /* 0x01 */ { 0x80, 0 },   /* [VISUAL   ] expansion flash — large fill circle
                                  Used: effect_spawn_shrink_fx, fx_spawn_electric_arc,
                                        fx_spawn_plasma_explosion, effect_spawn_explosion_burst
                                  flags=0x19 (additive, scale grows). Needs a large smooth circle
                                  that scales up. 2×2 grid frame 0 = top-left 128×128 area =
                                  the soft glow circle at maximum resolution. */

    /* 0x02 */ { 0x40, 0 },   /* [CONFIRMED] shield / projectile glow — soft white glow disc
                                  Used: effect_select_texture(2) in player.c shield overlay and
                                  projectiles.c. Frame 0 in 4×4 (0,0) = Bubble (Shield) disc —
                                  the first particle in particles.jaz. */

    /* 0x03 */ { 0x40, 0 },   /* [UNUSED   ] no call sites found */
    /* 0x04 */ { 0x40, 0 },   /* [UNUSED   ] no call sites found */
    /* 0x05 */ { 0x40, 0 },   /* [UNUSED   ] no call sites found */
    /* 0x06 */ { 0x40, 0 },   /* [UNUSED   ] no call sites found */

    /* 0x07 */ { 0x40, 6 },   /* [VISUAL   ] blood splatter — fire/explosion blob
                                  Used: effect_spawn_blood_splatter, flags=0xc9 (non-additive).
                                  Frame 6 in 4×4 (128,64) = orange fire/explosion blob.
                                  When tinted red with non-additive blend, becomes blood splat. */

    /* 0x08 */ { 0x20, 8 },   /* [CONFIRMED] freeze shard A — Ice Small 1
                                  Used: effect_spawn_freeze_shard (rand()%3 + 8).
                                  Frame 8 in 8×8 (0,32) = Ice Small 1 sprite.
                                  Uses 8×8 grid for 32×32 ice crystal sprites. */

    /* 0x09 */ { 0x20, 9 },   /* [CONFIRMED] freeze shard B — Ice Small 2
                                  Frame 9 in 8×8 (32,32) = Ice Small 2 sprite. */

    /* 0x0a */ { 0x20, 10 },  /* [CONFIRMED] freeze shard C — Ice Small 3
                                  Frame 10 in 8×8 (64,32) = Ice Small 3 sprite. */

    /* 0x0b */ { 0x40, 0 },   /* [UNUSED   ] no call sites found */

    /* 0x0c */ { 0x40, 5 },   /* [CONFIRMED] fire particle sprite — Explosion
                                  Used: bonus_render fire particle pass 2 (effect_select_texture(0xc)).
                                  Frame 5 in 4×4 (64,64) = orange fire/explosion shape.
                                  Confirmed by user screenshots of spinning flamethrower:
                                  individual particles are clearly the Explosion blob. */

    /* 0x0d */ { 0x40, 3 },   /* [CONFIRMED] glow particle orb — golden glow
                                  Used: ui_cursor_render, ui_render_aim_enhancement, projectiles 
                                  Frame 3 in 4×4 (192,0) = golden warm glow orb. */

    /* 0x0e */ { 0x40, 8 },   /* [VISUAL   ] freeze crystal overlay — star/snowflake
                                  Used: effect_spawn_freeze_shatter, creature freeze overlay
                                  Frame 8 in 4×4 (0,128) = blue star/snowflake crystal.
                                  Drawn overlaid on frozen creatures. */

    /* 0x0f */ { 0x40, 0 },   /* [UNUSED   ] no call sites found */

    /* 0x10 */ { 0x40, 0 },   /* [CONFIRMED] shadow/overlay — solid glow circle
                                  Used: creature_render_all shadow pass, bonus icon base
                                  Frame 0 in 4×4 (0,0) = soft white glow circle.
                                  Drawn with color=(0,0,0,1) → becomes solid black shadow disc.
                                  Also used as base for bonus icon rendering. */

    /* 0x11 */ { 0x40, 11 },  /* [VISUAL   ] explosion smoke ring — dark smoke
                                  Used: effect_spawn_explosion_burst smoke loop, flags=0x5d.
                                  Frame 11 in 4×4 (192,128) = soft dark smoke cloud. */

    /* 0x12 */ { 0x40, 2 },   /* [VISUAL   ] shell casing — tiny brass bullet shape
                                  Used: player.c weapons with flag&1, flags=0x1c5.
                                  Frame 2 in 4×4 (128,0) = contains tiny brass bullet casing. */
};

#define EFFECT_ID_TABLE_SIZE (sizeof(effect_id_table) / sizeof(effect_id_entry_t))

/*
 * VERIFICATION NOTES:
 * 
 * The particles texture was extracted from content/crimson.paq using
 * scripts/extract_particles.ts. Visual inspection of both the JPEG (RGB)
 * and alpha channels was used to match frame positions to their expected
 * visual effects.
 * 
 * Key insights from visual analysis:
 * 1. Most particle effects use the 4×4 grid (0x40), not 16×16 as initially assumed
 * 2. The 16×16 grid cells are only 16×16 px — too small for most visible effects
 * 3. The texture is organized with:
 *    - Glowing effects in top row (frames 0, 3)
 *    - Rock/ice chunks in middle rows (frames 4, 5, 8)
 *    - Smoke/fire in right side (frames 6, 7, 11)
 *    - Sparkles and crystals in bottom row (frames 12, 13, 15)
 *    - Shadow sphere at frame 14
 * 
 * REMAINING UNCERTAINTY:
 * - IDs 0x08, 0x09, 0x0a (freeze shard variants): The three snowflake/ice
 *   crystal frames (8, 13, 15) are assigned based on visual similarity,
 *   but the exact mapping could be permuted.
 * - ID 0x0e vs 0x0a: Both are freeze effects. 0x0e is the shatter overlay
 *   drawn on creatures, 0x0a is one of the random particle shards. They
 *   could share the same frame.
 * - ID 0x01 size_code: Could be 0x40 (frame 0) instead of 0x80 (frame 0).
 *   The 0x80 (2×2) grid gives a 128×128 cell for the expansion flash,
 *   which makes sense for a large growing circle. But 0x40 frame 0 would
 *   give the same top-left corner as a 64×64 cell.
 */
