/**
 * PerkSystem - Player perk management
 *
 * Port of perk system from crimsonland.exe_decompiled.c
 */

/**
 * Perk IDs from C code (perk_meta_table)
 * Maps exactly to C's perk_id enum values 0x00–0x39
 */
export enum PerkId {
    // Internal (never offered to player)
    ANTIPERK = 0x00,

    // Basic perks
    BLOODY_MESS = 0x01, // More blood / Quick Learner (+XP) depending on fx_toggle
    SHARPSHOOTER = 0x02, // Better accuracy, 2x spread recovery
    FASTLOADER = 0x03, // Faster reload (25%)
    LEAN_MEAN_EXP_MACHINE = 0x04, // +10 XP per 0.25s (stacks with count)
    LONG_DISTANCE_RUNNER = 0x05, // +40% speed (max 2.8 vs 2.0)
    PYROKINETIC = 0x06, // Burn enemies in crosshair
    INSTANT_WINNER = 0x07, // +2500 XP instantly (stackable flag 4)
    GRIM_DEAL = 0x08, // Kill self, convert health to XP (prereq: ANTIPERK i.e. none)
    ALTERNATE_WEAPON = 0x09, // Second weapon slot (flag 1 = quest only)
    PLAGUEBEARER = 0x0a, // Sets plaguebearer_active flag, poisons on contact
    EVIL_EYES = 0x0b, // Damage enemy in crosshair
    AMMO_MANIAC = 0x0c, // Refill all weapon ammo (reassigns all weapons)
    RADIOACTIVE = 0x0d, // Proximity damage to enemies
    FASTSHOT = 0x0e, // 12% faster fire rate
    FATAL_LOTTERY = 0x0f, // 50/50: +10000 XP or health = -1 (stackable flag 4)
    RANDOM_WEAPON = 0x10, // Get random available weapon (stackable flag 5)
    MR_MELEE = 0x11, // Counter-damage on touch
    ANXIOUS_LOADER = 0x12, // Fire button speeds reload (-0.05/press)
    FINAL_REVENGE = 0x13, // Explosion on death (prereq: ANTIPERK i.e. none)
    TELEKINETIC = 0x14, // Pickup bonuses from distance
    PERK_EXPERT = 0x15, // +1 perk choice (6 total)
    UNSTOPPABLE = 0x16, // Monsters can't slow you
    REGRESSION_BULLETS = 0x17, // Shoot when empty clip
    INFERNAL_CONTRACT = 0x18, // +3 levels, +3 pending perks, health → 0.1
    POISON_BULLETS = 0x19, // Poison on hit
    DODGER = 0x1a, // 20% dodge chance
    BONUS_MAGNET = 0x1b, // Attract bonuses
    URANIUM_FILLED_BULLETS = 0x1c, // +100% bullet damage
    DOCTOR = 0x1d, // +20% bullet damage + targeting cursor
    MONSTER_VISION = 0x1e, // See enemy health bars
    HOT_TEMPERED = 0x1f, // Periodic 8-projectile plasma burst (2-9s interval)
    BONUS_ECONOMIST = 0x20, // Bonuses last 50% longer
    THICK_SKINNED = 0x21, // On apply: -33% health. Passive: 33% damage reduction
    BARREL_GREASER = 0x22, // +40% bullet damage
    AMMUNITION_WITHIN = 0x23, // Shoot with empty clip (like regression bullets)
    VEINS_OF_POISON = 0x24, // Weak poison on touch
    TOXIC_AVENGER = 0x25, // Strong poison on touch
    REGENERATION = 0x26, // Slow health regen (+dt HP, 50% chance/frame, cap 100)
    PYROMANIAC = 0x27, // +50% fire damage (only offered if weapon == 8 flamethrower)
    NINJA = 0x28, // 33% dodge chance (prereq: DODGER)
    HIGHLANDER = 0x29, // 10% instant death replaces normal damage (prereq: none/0)
    JINXED = 0x2a, // Random -5 HP, random enemy kills, cooldown 2-4s
    PERK_MASTER = 0x2b, // +2 perk choices (7 total) (prereq: PERK_EXPERT)
    REFLEX_BOOSTED = 0x2c, // Slow-mo effect
    GREATER_REGENERATION = 0x2d, // Faster health regen (prereq: REGENERATION)
    BREATHING_ROOM = 0x2e, // Health ×= 0.333, shrink enemy hitboxes, reset bonus guard (prereq: REGENERATION, flag 2)
    DEATH_CLOCK = 0x2f, // On apply: remove regen perks, set health=100. Passive: -3.33 HP/s, invulnerable
    MY_FAVOURITE_WEAPON = 0x30, // +2 clip size to all weapons
    BANDAGE = 0x31, // health *= (rand()%50 + 1), cap 100, spawn burst effect
    ANGRY_RELOADER = 0x32, // Fire burst at 50% reload
    ION_GUN_MASTER = 0x33, // +20% ion damage
    STATIONARY_RELOADER = 0x34, // 3x reload speed when standing still
    MAN_BOMB = 0x35, // Explode on command
    FIRE_COUGH = 0x36, // Periodic fire projectiles (2-5s interval)
    LIVING_FORTRESS = 0x37, // Defense scales with stationary time (up to 30s)
    TOUGH_RELOADER = 0x38, // 50% damage reduction while reloading
    LIFELINE_50_50 = 0x39, // Kill every other active enemy with health ≤ 500
}

/**
 * Damage types (from C)
 */
export enum DamageType {
    BULLET = 1, // Standard bullet damage
    EXPLOSIVE = 2, // Explosive damage
    PLASMA = 3, // Plasma damage
    FIRE = 4, // Fire damage
    ION = 7, // Ion damage
}

/**
 * Perk metadata interface
 */
export interface PerkMeta {
    id: PerkId;
    name: string;
    description: string;
}

/**
 * Perk metadata table (from C perk_meta_table)
 * Contains names and descriptions for all perks
 */
export const PERK_META: Record<PerkId, PerkMeta> = {
    [PerkId.ANTIPERK]: {
        id: PerkId.ANTIPERK,
        name: 'Anti-Perk',
        description: 'Internal placeholder — never offered to player',
    },
    [PerkId.BLOODY_MESS]: {
        id: PerkId.BLOODY_MESS,
        name: 'Bloody Mess',
        description: 'Blood everywhere! Also grants +XP on kills (Quick Learner mode)',
    },
    [PerkId.SHARPSHOOTER]: {
        id: PerkId.SHARPSHOOTER,
        name: 'Sharpshooter',
        description: 'Better accuracy, 2x spread recovery',
    },
    [PerkId.FASTLOADER]: {
        id: PerkId.FASTLOADER,
        name: 'Fastloader',
        description: 'Reload weapons 25% faster',
    },
    [PerkId.LEAN_MEAN_EXP_MACHINE]: {
        id: PerkId.LEAN_MEAN_EXP_MACHINE,
        name: 'Lean Mean Exp Machine',
        description: 'Gain +10 XP every 0.25 seconds (stackable)',
    },
    [PerkId.LONG_DISTANCE_RUNNER]: {
        id: PerkId.LONG_DISTANCE_RUNNER,
        name: 'Long Distance Runner',
        description: 'Move 40% faster (max speed 2.8 vs 2.0)',
    },
    [PerkId.PYROKINETIC]: {
        id: PerkId.PYROKINETIC,
        name: 'Pyrokinetic',
        description: 'Burn enemies in your crosshair',
    },
    [PerkId.INSTANT_WINNER]: {
        id: PerkId.INSTANT_WINNER,
        name: 'Instant Winner',
        description: 'Gain 2500 experience points instantly (stackable)',
    },
    [PerkId.GRIM_DEAL]: {
        id: PerkId.GRIM_DEAL,
        name: 'Grim Deal',
        description: 'Die instantly. Gain 18% of your current XP as a bonus.',
    },
    [PerkId.ALTERNATE_WEAPON]: {
        id: PerkId.ALTERNATE_WEAPON,
        name: 'Alternate Weapon',
        description: 'Get a second weapon slot',
    },
    [PerkId.PLAGUEBEARER]: {
        id: PerkId.PLAGUEBEARER,
        name: 'Plaguebearer',
        description: 'Spread a horrible plague to enemies on contact',
    },
    [PerkId.EVIL_EYES]: {
        id: PerkId.EVIL_EYES,
        name: 'Evil Eyes',
        description: 'Freeze the enemy in your crosshair',
    },
    [PerkId.AMMO_MANIAC]: {
        id: PerkId.AMMO_MANIAC,
        name: 'Ammo Maniac',
        description: 'Immediately refill ammo for all weapons',
    },
    [PerkId.RADIOACTIVE]: {
        id: PerkId.RADIOACTIVE,
        name: 'Radioactive',
        description: 'Damage all enemies within 75 units',
    },
    [PerkId.FASTSHOT]: {
        id: PerkId.FASTSHOT,
        name: 'Fast Shot',
        description: 'Fire 12% faster',
    },
    [PerkId.FATAL_LOTTERY]: {
        id: PerkId.FATAL_LOTTERY,
        name: 'Fatal Lottery',
        description: '50/50 chance: gain 10000 XP or instantly die (stackable)',
    },
    [PerkId.RANDOM_WEAPON]: {
        id: PerkId.RANDOM_WEAPON,
        name: 'Random Weapon',
        description: 'Get a random available weapon (stackable)',
    },
    [PerkId.MR_MELEE]: {
        id: PerkId.MR_MELEE,
        name: 'Mr. Melee',
        description: 'Deal counter-damage to enemies that touch you',
    },
    [PerkId.ANXIOUS_LOADER]: {
        id: PerkId.ANXIOUS_LOADER,
        name: 'Anxious Loader',
        description: 'Mash fire during reload to speed it up (-0.05s per press)',
    },
    [PerkId.FINAL_REVENGE]: {
        id: PerkId.FINAL_REVENGE,
        name: 'Final Revenge',
        description: 'Explode on death, damaging nearby enemies',
    },
    [PerkId.TELEKINETIC]: {
        id: PerkId.TELEKINETIC,
        name: 'Telekinetic',
        description: 'Pick up bonuses from a distance',
    },
    [PerkId.PERK_EXPERT]: {
        id: PerkId.PERK_EXPERT,
        name: 'Perk Expert',
        description: 'Get 1 extra perk choice on level up (6 total)',
    },
    [PerkId.UNSTOPPABLE]: {
        id: PerkId.UNSTOPPABLE,
        name: 'Unstoppable',
        description: "Monsters can't slow you down with collisions",
    },
    [PerkId.REGRESSION_BULLETS]: {
        id: PerkId.REGRESSION_BULLETS,
        name: 'Regression Bullets',
        description: 'Shoot projectiles even with an empty clip',
    },
    [PerkId.INFERNAL_CONTRACT]: {
        id: PerkId.INFERNAL_CONTRACT,
        name: 'Infernal Contract',
        description: 'Exchange your soul for 3 extra levels. Health drops to near-death.',
    },
    [PerkId.POISON_BULLETS]: {
        id: PerkId.POISON_BULLETS,
        name: 'Poison Bullets',
        description: 'Your bullets poison enemies',
    },
    [PerkId.DODGER]: {
        id: PerkId.DODGER,
        name: 'Dodger',
        description: '20% chance to dodge enemy attacks',
    },
    [PerkId.BONUS_MAGNET]: {
        id: PerkId.BONUS_MAGNET,
        name: 'Bonus Magnet',
        description: 'Attract bonuses and increase drop rate',
    },
    [PerkId.URANIUM_FILLED_BULLETS]: {
        id: PerkId.URANIUM_FILLED_BULLETS,
        name: 'Uranium Bullets',
        description: 'Bullets deal 100% more damage',
    },
    [PerkId.DOCTOR]: {
        id: PerkId.DOCTOR,
        name: 'Doctor',
        description: 'Diagnose enemies for +20% bullet damage. Targeting cursor enabled.',
    },
    [PerkId.MONSTER_VISION]: {
        id: PerkId.MONSTER_VISION,
        name: 'Monster Vision',
        description: 'See enemy health bars',
    },
    [PerkId.HOT_TEMPERED]: {
        id: PerkId.HOT_TEMPERED,
        name: 'Hot Tempered',
        description: 'Periodically emit 8-projectile plasma bursts (every 2-9s)',
    },
    [PerkId.BONUS_ECONOMIST]: {
        id: PerkId.BONUS_ECONOMIST,
        name: 'Bonus Economist',
        description: 'Bonus power-ups last 50% longer',
    },
    [PerkId.THICK_SKINNED]: {
        id: PerkId.THICK_SKINNED,
        name: 'Thick Skinned',
        description: 'Trade 1/3 of your health for 33% damage reduction',
    },
    [PerkId.BARREL_GREASER]: {
        id: PerkId.BARREL_GREASER,
        name: 'Barrel Greaser',
        description: 'Bullets deal 40% more damage',
    },
    [PerkId.AMMUNITION_WITHIN]: {
        id: PerkId.AMMUNITION_WITHIN,
        name: 'Ammunition Within',
        description: 'Fire with empty clip — never run dry',
    },
    [PerkId.VEINS_OF_POISON]: {
        id: PerkId.VEINS_OF_POISON,
        name: 'Veins of Poison',
        description: 'Poison enemies that touch you (weak)',
    },
    [PerkId.TOXIC_AVENGER]: {
        id: PerkId.TOXIC_AVENGER,
        name: 'Toxic Avenger',
        description: 'Poison enemies that touch you (strong)',
    },
    [PerkId.REGENERATION]: {
        id: PerkId.REGENERATION,
        name: 'Regeneration',
        description: 'Slowly regenerate health over time (50% chance per frame)',
    },
    [PerkId.PYROMANIAC]: {
        id: PerkId.PYROMANIAC,
        name: 'Pyromaniac',
        description: 'Fire weapons deal 50% more damage',
    },
    [PerkId.NINJA]: {
        id: PerkId.NINJA,
        name: 'Ninja',
        description: '33% chance to dodge enemy attacks (requires Dodger)',
    },
    [PerkId.HIGHLANDER]: {
        id: PerkId.HIGHLANDER,
        name: 'Highlander',
        description: '90% of hits deal no damage, but 10% instantly kill you',
    },
    [PerkId.JINXED]: {
        id: PerkId.JINXED,
        name: 'Jinxed',
        description: 'Random -5 HP and random enemy kills every 2-4 seconds',
    },
    [PerkId.PERK_MASTER]: {
        id: PerkId.PERK_MASTER,
        name: 'Perk Master',
        description: 'Get 2 extra perk choices on level up (7 total) (requires Perk Expert)',
    },
    [PerkId.REFLEX_BOOSTED]: {
        id: PerkId.REFLEX_BOOSTED,
        name: 'Reflex Boosted',
        description: 'The world seems to slow down around you',
    },
    [PerkId.GREATER_REGENERATION]: {
        id: PerkId.GREATER_REGENERATION,
        name: 'Greater Regeneration',
        description: 'Prerequisite for advanced perks. No additional regen beyond Regeneration.',
    },
    [PerkId.BREATHING_ROOM]: {
        id: PerkId.BREATHING_ROOM,
        name: 'Breathing Room',
        description: 'Trade 2/3 of your health. Enemies shrink temporarily.',
    },
    [PerkId.DEATH_CLOCK]: {
        id: PerkId.DEATH_CLOCK,
        name: 'Death Clock',
        description: 'Die in exactly 30 seconds. Complete invulnerability until then. Removes regeneration.',
    },
    [PerkId.MY_FAVOURITE_WEAPON]: {
        id: PerkId.MY_FAVOURITE_WEAPON,
        name: 'My Favourite Weapon',
        description: 'All weapons gain +2 clip size',
    },
    [PerkId.BANDAGE]: {
        id: PerkId.BANDAGE,
        name: 'Bandage',
        description: 'Multiply your health by a random amount (1–50×), capped at 100',
    },
    [PerkId.ANGRY_RELOADER]: {
        id: PerkId.ANGRY_RELOADER,
        name: 'Angry Reloader',
        description: 'Fire a burst when reload reaches halfway',
    },
    [PerkId.ION_GUN_MASTER]: {
        id: PerkId.ION_GUN_MASTER,
        name: 'Ion Gun Master',
        description: 'Ion weapons deal 20% more damage',
    },
    [PerkId.STATIONARY_RELOADER]: {
        id: PerkId.STATIONARY_RELOADER,
        name: 'Stationary Reloader',
        description: '3x reload speed when standing still',
    },
    [PerkId.MAN_BOMB]: {
        id: PerkId.MAN_BOMB,
        name: 'Man Bomb',
        description: 'Automatically explode for massive damage while standing still',
    },
    [PerkId.FIRE_COUGH]: {
        id: PerkId.FIRE_COUGH,
        name: 'Fire Cough',
        description: 'Periodically cough fire projectiles (every 2-5s)',
    },
    [PerkId.LIVING_FORTRESS]: {
        id: PerkId.LIVING_FORTRESS,
        name: 'Living Fortress',
        description: 'Defense scales with time spent stationary (up to 30s)',
    },
    [PerkId.TOUGH_RELOADER]: {
        id: PerkId.TOUGH_RELOADER,
        name: 'Tough Reloader',
        description: 'Take 50% less damage while reloading',
    },
    [PerkId.LIFELINE_50_50]: {
        id: PerkId.LIFELINE_50_50,
        name: 'Lifeline 50/50',
        description: 'Kill every other active enemy with health ≤ 500',
    },
};

/**
 * Get list of all selectable perk IDs (excludes ANTIPERK)
 */
export function getSelectablePerkIds(): PerkId[] {
    return Object.keys(PERK_META)
        .map((k) => parseInt(k) as PerkId)
        .filter((id) => id !== PerkId.ANTIPERK);
}

/**
 * Perk system for managing player perks
 * Uses integer count array matching C's perk_counts[] — supports stacking perks
 */
export class PerkSystem {
    /** Integer count array matching C's perk_counts[] */
    private perkCounts: Map<PerkId, number> = new Map();

    /**
     * Returns count (0 if not held) — matches C perk_count_get()
     */
    getPerkCount(perkId: PerkId): number {
        return this.perkCounts.get(perkId) ?? 0;
    }

    /**
     * Returns true if count >= 1 — convenience wrapper
     */
    hasPerk(perkId: PerkId): boolean {
        return this.getPerkCount(perkId) > 0;
    }

    /**
     * Increment count by 1 — matches C: perk_counts[perk_id]++
     */
    addPerk(perkId: PerkId): void {
        this.perkCounts.set(perkId, this.getPerkCount(perkId) + 1);
    }

    /**
     * Set count to specific value (for Death Clock clearing regen)
     */
    setPerkCount(perkId: PerkId, count: number): void {
        if (count <= 0) {
            this.perkCounts.delete(perkId);
        } else {
            this.perkCounts.set(perkId, count);
        }
    }

    /**
     * Remove a perk from the player (set count to 0)
     */
    removePerk(perkId: PerkId): void {
        this.perkCounts.delete(perkId);
    }

    /**
     * Get all active perks (those with count >= 1)
     */
    getActivePerks(): PerkId[] {
        return Array.from(this.perkCounts.keys());
    }

    /**
     * Clear all perks
     */
    clear(): void {
        this.perkCounts.clear();
    }
}
