/**
 * QuestTypes - Quest type definitions, constants, and enemy templates
 *
 * Extracted from QuestData.ts
 */

/**
 * Quest spawn entry - defines when and where to spawn enemies
 * C: quest_spawn_entry_t
 */
export interface QuestSpawnEntry {
    triggerTimeMs: number; // When to spawn (ms from quest start)
    posX: number; // X position (-64 for left edge, terrain_width+64 for right)
    posY: number; // Y position (-64 for top edge, terrain_height+64 for bottom)
    templateId: number; // Enemy template ID (C line refs in spawn functions)
    count: number; // Number of enemies to spawn
    heading?: number; // Initial heading angle (optional)
}

/**
 * Quest metadata
 * C: quest_meta_t structure (lines 31477-31927)
 */
export interface QuestMeta {
    id: number; // Quest ID (tier * 10 + index - 11)
    tier: number; // 1-4 (C: _quest_stage_major)
    index: number; // 1-10 within tier (C: _quest_stage_minor)
    name: string; // Quest display name
    startWeaponId: number; // Starting weapon (C: start_weapon_id)
    timeLimitMs: number; // Time limit in ms (C: time_limit_ms)
    unlockWeaponId: number; // Weapon unlocked on completion
    unlockPerkId: number; // Perk unlocked on completion
    spawns: QuestSpawnEntry[]; // Enemy spawn timeline
}

/**
 * Enemy template IDs from C code
 * Used in quest spawn entries
 */
export const EnemyTemplate = {
    // Standard enemies — all type_id=2 (Spider) unless noted
    SPIDER_STANDARD: 0x26, // C type_id=2 (spider_sp1.jaz), size=45, hp=50
    SPIDER_FAST_FLAGGED: 0x27, // C type_id=2, flags=0x400
    SPIDER_SMALL: 0x25, // C type_id=2, size=30, hp=25
    SPIDER_MID: 0x28, // C type_id=2, size=55, hp=50
    SPIDER_TANK: 0x29, // C type_id=2, size=70, hp=800
    SPIDER_FAST_DARK: 0x2a, // C type_id=2, size=60, speed=3.1
    SPIDER_FAST_RED: 0x2b, // C type_id=2, size=35, speed=3.6
    SPIDER: 0x2c, // Spider (44)
    SPIDER_LARGE: 0x2d, // Large spider (45)
    // Patrol/specialized enemies (Tier 1-4 quest builders)
    GENERIC_HOSTILE: 0x01, // Generic hostile (1) - Spideroids
    HOSTILE_07: 0x07, // Multi-purpose hostile (7) - Two Fronts, End of All, etc.
    ALIEN_DEN: 0x08, // Alien den spawner (8) - Alien Dens, Nesting Grounds
    SENTINEL: 0x09, // Sentinel (9) - The Fortress, Nesting Grounds
    MINE: 0x0a, // Mine (10) - Fortress, Arachnoid Farm, etc.
    MINE_LARGE: 0x0b, // Large mine (11) - Nagolipoli, End of All
    TURRET_SMALL: 0x0c, // Small turret (12) - Lizard Raze, Lizard Zombie Pact
    LIZARD_VARIANT: 0x0d, // Lizard variant (13) - Surrounded, Deja Vu, Annihilation
    TURRET: 0x0e, // Turret (14) - The Fortress, Land Of Lizards
    SPIDER_MELEE: 0x0f, // C type_id=2 (Spider), melee — was "ZOMBIE_MELEE"
    NEST_SPAWNER: 0x10, // Nest/spawner (16) - Spider Spawns, Arachnoid Farm, Survival
    LIZARD_KING: 0x11, // Lizard king (17) - C type_id=1 (Lizard)
    SPIDER_PATROL: 0x12, // C type_id=2 (Spider) — was "LIZARD_PATROL"
    SPIDER_ORBIT_BOSS: 0x13, // C type_id=2, ai_mode=6 — was "LIZARD_BOSS"
    SPIDER_FORMATION_A: 0x15, // C type_id=2 (Spider) — was "ALIEN_BOSS"
    LIZARD_FORMATION_A: 0x16, // C type_id=1 (Lizard) — was "ALIEN_MECH"
    SPIDER2_FORMATION_A: 0x17, // C type_id=3 (Spider2) — was "ALIEN_DRONE"
    SPIDER_GHOST_LEADER: 0x18, // C type_id=2 (Spider) — was "GHOST_PATROL_END"
    SPIDER_GHOST_PATROL: 0x19, // C type_id=2 (Spider) — was "GHOST_PATROL"
    SPIDER_WAVE: 0x1a, // C type_id=2 (Spider) — was "ZOMBIE_WAVE"
    SPIDER2_WAVE: 0x1b, // C type_id=3 (Spider2) — was "ALIEN_WAVE"
    LIZARD_CIRCLE: 0x1c, // C type_id=1 (Lizard) — was "GHOST"
    NEST_SWARM: 0x1d, // Nest/swarm spawner (29) - Random Factor, Nesting Grounds
    SPIDER_VARIANT: 0x1e, // Spider variant (30) - Nesting Grounds
    BOSS_VARIANT: 0x1f, // Boss variant (31) - Nesting Grounds
    SPIDER_GREEN_WAVE: 0x20, // C type_id=2, green tint — was "ALIEN_BREACH"
    SPIDER_NESTED: 0x21, // Nested spider (33) - Hidden Evil
    SPIDER_QUEEN: 0x22, // Spider queen (34) - Hidden Evil
    SPIDER_BROOD: 0x23, // Spider brood (35) - Hidden Evil
    LIZARD_WAVE: 0x2e, // Lizard wave (46) - Lizquidation, Lizard Raze
    LIZARD_KING_CIRCLE: 0x31, // Lizard king circle (49) - Lizard Kings
    DIR_EAST: 0x32, // Directional enemy east (50) - Everred Pastures
    DIR_WEST: 0x33, // Directional enemy west (51) - Everred Pastures
    DIR_SOUTH: 0x34, // Directional enemy south (52) - Everred Pastures
    DIR_NORTH: 0x35, // Directional enemy north (53) - Everred Pastures
    SPIDER_BURROW: 0x36, // C type_id=2, ai_mode=7 — was "TARGET"
    SPIDER_BOSS_VAR: 0x38, // Spider boss variant (56) - Spider Spawns, Spiders Inc.
    TOUGHGUY: 0x00, // Tough guy (0) - The Gathering
    // Boss enemies
    BOSS_ZOMBIE: 0x3c, // Boss zombie (60)
    BOSS_ALIEN: 0x3d, // Boss alien (61)
    BOSS_LIZARD: 0x3e, // Boss lizard (62)
    BOSS_SPIDER: 0x3f, // Boss spider (63)
    BOSS_ZOMBIE_V2: 0x3a, // Boss zombie v2 (58) - The Gathering
    // Swarm enemies
    SWARM: 0x40, // Swarm (64)
    SWARM_SMALL: 0x41, // Small swarm (65) - Knee Deep, Spanking, Evil Zombies, etc.
    SWARM_MEDIUM: 0x42, // Medium swarm (66) - Knee Deep, Spanking
    SWARM_LEADER: 0x43, // Swarm leader (67) - Knee Deep
} as const;

/**
 * Perk ID for "no perk unlock" (antiperk)
 * C: perk_id_antiperk
 */
export const PERK_ANTIPERK = 0x37; // 55

/**
 * Default terrain dimensions (used for spawn positioning)
 */
export const DEFAULT_TERRAIN_WIDTH = 1024;
export const DEFAULT_TERRAIN_HEIGHT = 1024;
