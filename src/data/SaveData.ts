/**
 * SaveData.ts - Data types for save/load system
 *
 * TypeScript interfaces matching C save data structures.
 *
 * C code references:
 * - game_status_blob: structure definition (0x268 bytes)
 * - highscore_record_t: structure definition
 * - game_save_status: lines 11160-11217
 * - game_load_status: lines 11225-11291
 */

/** Current save format version for migration support */
export const SAVE_VERSION = 1;

/** Storage keys */
export const STORAGE_KEYS = {
    GAME_STATUS: 'crimsonland.gameStatus',
    HIGH_SCORES: 'crimsonland.highScores',
    ACHIEVEMENTS: 'crimsonland.achievements',
} as const;

/** Max high score entries (C line 32729-32730) */
export const MAX_HIGH_SCORES = 100;

/**
 * Game status data matching game_status_blob (0x268 = 616 bytes)
 * C code reference: lines 11188-11203
 */
export interface GameStatusData {
    /** Save version for migration */
    version: number;

    /** Current quest unlock progress */
    questUnlockIndex: number;

    /** Full game quest unlock progress */
    questUnlockIndexFull: number;

    /** Anti-cheat sequence ID (C line 11177) */
    gameSequenceId: number;

    /** Per-weapon usage tracking (40 entries, C line 11194) */
    weaponUsageCounts: number[];

    /** Per-quest play counts (60 entries for 6 chapters × 10 quests) */
    questPlayCounts: number[];

    /** Mode play counts (C lines 38001-38016) */
    modePlaySurvival: number;
    modePlayRush: number;
    modePlayTypo: number;
    modePlayOther: number;

    /** Unlocked perk IDs (quest completion rewards) */
    unlockedPerkIds: number[];

    /** Unlocked weapon IDs (quest completion rewards) */
    unlockedWeaponIds: number[];

    /** XOR checksum for validation (C lines 11193-11202) */
    checksum: number;
}

/**
 * High score record matching highscore_record_t (0x48 = 72 bytes)
 * C code reference: lines 11435-11449 (field initialization)
 */
export interface HighScoreRecord {
    /** Player name (C: player_name, max ~40 chars) */
    playerName: string;

    /** Score/experience points (C: score_xp) */
    scoreXp: number;

    /** Survival time in milliseconds (C: survival_elapsed_ms) */
    survivalElapsedMs: number;

    /** Total kills (C: creature_kill_count) */
    creatureKillCount: number;

    /** Accuracy stats */
    shotsFired: number;
    shotsHit: number;

    /** Game mode (C: game_mode_id - 1=Survival, 2=Rush, 3=Quest, 4=Typo) */
    gameModeId: number;

    /** Quest progress (C: quest_stage_major/minor) */
    questStageMajor: number;
    questStageMinor: number;

    /** Most used weapon during run */
    mostUsedWeaponId: number;

    /** Date of record */
    date: {
        year: number;
        month: number;
        day: number;
    };

    /** Full version marker (C: full_version_marker) */
    fullVersionMarker: boolean;
}

/**
 * Creates default game status for first-time load
 * C code reference: lines 11245-11248 (fallback on failed load)
 */
export function createDefaultGameStatus(): GameStatusData {
    return {
        version: SAVE_VERSION,
        questUnlockIndex: 0,
        questUnlockIndexFull: 0,
        gameSequenceId: 0,
        weaponUsageCounts: new Array(40).fill(0),
        questPlayCounts: new Array(60).fill(0),
        modePlaySurvival: 0,
        modePlayRush: 0,
        modePlayTypo: 0,
        modePlayOther: 0,
        unlockedPerkIds: [],
        unlockedWeaponIds: [],
        checksum: 0,
    };
}

/**
 * Creates a new high score record with current date
 */
export function createHighScoreRecord(
    playerName: string,
    scoreXp: number,
    survivalElapsedMs: number,
    gameModeId: number,
): HighScoreRecord {
    const now = new Date();
    return {
        playerName,
        scoreXp,
        survivalElapsedMs,
        creatureKillCount: 0,
        shotsFired: 0,
        shotsHit: 0,
        gameModeId,
        questStageMajor: 0,
        questStageMinor: 0,
        mostUsedWeaponId: 0,
        date: {
            year: now.getFullYear(),
            month: now.getMonth() + 1,
            day: now.getDate(),
        },
        fullVersionMarker: true,
    };
}

/**
 * Compute XOR checksum for game status data
 * Port of C checksum logic (lines 11193-11202)
 *
 * The C algorithm iterates through weapon_usage_counts with an XOR pattern:
 * - Uses polynomial: ((i * 7 + 15) * i + 3) * i
 * - Accumulates with: local_4 = local_4 + 0xd + iVar6
 * - Where iVar6 = (value * 7 + i) * value + accumulator
 */
export function computeChecksum(status: Omit<GameStatusData, 'checksum'>): number {
    let checksum = 0;
    let accumulator = 0;

    // Iterate through all data bytes (similar to C's 0x10b18 iterations = 68376)
    // We iterate through weaponUsageCounts and questPlayCounts
    const dataValues = [
        ...status.weaponUsageCounts,
        ...status.questPlayCounts,
        status.questUnlockIndex,
        status.questUnlockIndexFull,
        status.modePlaySurvival,
        status.modePlayRush,
        status.modePlayTypo,
        status.modePlayOther,
    ];

    for (let i = 0; i < dataValues.length; i++) {
        const value = dataValues[i] & 0xff; // Byte value
        const term = (value * 7 + i) * value + accumulator;
        accumulator += 0x6f;
        checksum = (checksum + 0xd + term) & 0xffffffff; // Keep as 32-bit
    }

    return checksum;
}

/**
 * Validate checksum matches stored value
 */
export function validateChecksum(status: GameStatusData): boolean {
    const { checksum: storedChecksum, ...statusWithoutChecksum } = status;
    const computedChecksum = computeChecksum(statusWithoutChecksum);
    return storedChecksum === computedChecksum;
}
