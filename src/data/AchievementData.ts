/**
 * AchievementData.ts - Achievement type definitions and metadata
 *
 * TypeScript-native achievement system (no C equivalent).
 * Tracks player milestones across kills, survival time, and quest progress.
 */

/**
 * Achievement IDs
 */
export enum AchievementId {
    // Kill milestones
    FIRST_BLOOD = 'first_blood', // 1 kill
    HUNDRED_KILLS = 'hundred_kills', // 100 kills
    THOUSAND_KILLS = 'thousand_kills', // 1,000 kills
    TEN_THOUSAND_KILLS = 'ten_thousand_kills', // 10,000 kills

    // Survival time milestones
    SURVIVOR_1MIN = 'survivor_1min', // Survive 1 minute
    SURVIVOR_5MIN = 'survivor_5min', // Survive 5 minutes
    SURVIVOR_10MIN = 'survivor_10min', // Survive 10 minutes

    // Quest milestones
    FIRST_QUEST = 'first_quest', // Complete 1 quest
    CHAPTER_COMPLETE = 'chapter_complete', // Complete a full chapter
    ALL_QUESTS = 'all_quests', // Complete all quests

    // Weapon mastery
    WEAPON_COLLECTOR = 'weapon_collector', // Use 5 different weapons
    WEAPON_MASTER = 'weapon_master', // Use 10 different weapons

    // Score milestones
    SCORE_10K = 'score_10k', // 10,000 points
    SCORE_100K = 'score_100k', // 100,000 points
}

/**
 * Achievement metadata for display
 */
export interface AchievementMeta {
    id: AchievementId;
    name: string;
    description: string;
    category: 'kills' | 'survival' | 'quests' | 'weapons' | 'score';
}

/**
 * Achievement progress data for persistence
 */
export interface AchievementProgress {
    /** List of unlocked achievement IDs */
    unlockedIds: string[];
    /** Timestamp when each achievement was unlocked */
    unlockDates: Record<string, number>;
    /** Cumulative stats for milestone tracking */
    stats: {
        totalKills: number;
        longestSurvivalMs: number;
        questsCompleted: number;
        weaponsUsed: number[];
        highestScore: number;
    };
}

/**
 * Achievement definitions with unlock criteria
 */
export const ACHIEVEMENT_META: Record<AchievementId, AchievementMeta> = {
    // Kill achievements
    [AchievementId.FIRST_BLOOD]: {
        id: AchievementId.FIRST_BLOOD,
        name: 'First Blood',
        description: 'Kill your first enemy',
        category: 'kills',
    },
    [AchievementId.HUNDRED_KILLS]: {
        id: AchievementId.HUNDRED_KILLS,
        name: 'Century',
        description: 'Kill 100 enemies',
        category: 'kills',
    },
    [AchievementId.THOUSAND_KILLS]: {
        id: AchievementId.THOUSAND_KILLS,
        name: 'Slayer',
        description: 'Kill 1,000 enemies',
        category: 'kills',
    },
    [AchievementId.TEN_THOUSAND_KILLS]: {
        id: AchievementId.TEN_THOUSAND_KILLS,
        name: 'Exterminator',
        description: 'Kill 10,000 enemies',
        category: 'kills',
    },

    // Survival achievements
    [AchievementId.SURVIVOR_1MIN]: {
        id: AchievementId.SURVIVOR_1MIN,
        name: 'Survivor',
        description: 'Survive for 1 minute',
        category: 'survival',
    },
    [AchievementId.SURVIVOR_5MIN]: {
        id: AchievementId.SURVIVOR_5MIN,
        name: 'Hardened',
        description: 'Survive for 5 minutes',
        category: 'survival',
    },
    [AchievementId.SURVIVOR_10MIN]: {
        id: AchievementId.SURVIVOR_10MIN,
        name: 'Immortal',
        description: 'Survive for 10 minutes',
        category: 'survival',
    },

    // Quest achievements
    [AchievementId.FIRST_QUEST]: {
        id: AchievementId.FIRST_QUEST,
        name: 'Quest Complete',
        description: 'Complete your first quest',
        category: 'quests',
    },
    [AchievementId.CHAPTER_COMPLETE]: {
        id: AchievementId.CHAPTER_COMPLETE,
        name: 'Chapter Master',
        description: 'Complete an entire chapter',
        category: 'quests',
    },
    [AchievementId.ALL_QUESTS]: {
        id: AchievementId.ALL_QUESTS,
        name: 'Completionist',
        description: 'Complete all quests',
        category: 'quests',
    },

    // Weapon achievements
    [AchievementId.WEAPON_COLLECTOR]: {
        id: AchievementId.WEAPON_COLLECTOR,
        name: 'Collector',
        description: 'Use 5 different weapons',
        category: 'weapons',
    },
    [AchievementId.WEAPON_MASTER]: {
        id: AchievementId.WEAPON_MASTER,
        name: 'Arsenal Master',
        description: 'Use 10 different weapons',
        category: 'weapons',
    },

    // Score achievements
    [AchievementId.SCORE_10K]: {
        id: AchievementId.SCORE_10K,
        name: 'Rising Star',
        description: 'Earn 10,000 points in a single run',
        category: 'score',
    },
    [AchievementId.SCORE_100K]: {
        id: AchievementId.SCORE_100K,
        name: 'Legend',
        description: 'Earn 100,000 points in a single run',
        category: 'score',
    },
};

/**
 * Create default achievement progress
 */
export function createDefaultAchievementProgress(): AchievementProgress {
    return {
        unlockedIds: [],
        unlockDates: {},
        stats: {
            totalKills: 0,
            longestSurvivalMs: 0,
            questsCompleted: 0,
            weaponsUsed: [],
            highestScore: 0,
        },
    };
}
