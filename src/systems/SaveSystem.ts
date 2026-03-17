/**
 * SaveSystem.ts - C-accurate save/load system
 *
 * Ports save/load logic from C code with browser storage backend.
 *
 * C code references:
 * - game_save_status: lines 11160-11217
 * - game_load_status: lines 11225-11291
 * - game_sequence_load: lines 11131-11152
 */

import {
    GameStatusData,
    HighScoreRecord,
    STORAGE_KEYS,
    MAX_HIGH_SCORES,
    SAVE_VERSION,
    createDefaultGameStatus,
    computeChecksum,
    validateChecksum,
} from '../data/SaveData';
import { StorageProvider, getStorageProvider } from '../data/StorageProvider';

/**
 * SaveSystem - manages game persistence
 *
 * Mirrors C code behavior:
 * - Saves/loads game status with checksum validation
 * - Generates new save on first run or corruption
 * - Manages high score records (max 100, C line 32729)
 */
export class SaveSystem {
    private storage: StorageProvider;

    constructor(storage?: StorageProvider) {
        this.storage = storage ?? getStorageProvider();
    }

    // =========================================================================
    // Game Status Methods
    // =========================================================================

    /**
     * Save game status to storage
     * Port of game_save_status (C lines 11160-11217)
     *
     * @param status Game status data to save
     * @returns true if save succeeded
     */
    saveGameStatus(status: Omit<GameStatusData, 'checksum' | 'version'>): boolean {
        try {
            // Add version first, then compute checksum (C lines 11193-11202)
            const statusWithVersion = {
                ...status,
                version: SAVE_VERSION,
            };
            const fullStatus: GameStatusData = {
                ...statusWithVersion,
                checksum: computeChecksum(statusWithVersion),
            };

            this.storage.set(STORAGE_KEYS.GAME_STATUS, fullStatus);

            return true;
        } catch (error) {
            // C line 11214: console_printf("GAME_SaveStatus_FAILED")
            console.error('GAME_SaveStatus_FAILED', error);
            return false;
        }
    }

    /**
     * Load game status from storage
     * Port of game_load_status (C lines 11225-11291)
     *
     * @returns Loaded status, or new default if not found/corrupt
     */
    loadGameStatus(): GameStatusData {
        const stored = this.storage.get<GameStatusData>(STORAGE_KEYS.GAME_STATUS);

        if (stored === null) {
            const newStatus = createDefaultGameStatus();
            this.saveGameStatus(newStatus);
            return newStatus;
        }

        // Validate checksum (C lines 11276-11280)
        if (!validateChecksum(stored)) {
            console.warn('GAME_LoadStatus_FAILED: check_sum mismatch');

            // Generate new on checksum failure
            const newStatus = createDefaultGameStatus();
            this.saveGameStatus(newStatus);
            return newStatus;
        }

        return stored;
    }

    /**
     * Get current quest unlock index
     * C lines 11282-11283
     */
    getQuestUnlockIndex(): number {
        const status = this.loadGameStatus();
        return status.questUnlockIndex;
    }

    /**
     * Update quest unlock progress
     * Called when completing quests
     */
    setQuestUnlockIndex(index: number): void {
        const status = this.loadGameStatus();
        if (index > status.questUnlockIndex) {
            status.questUnlockIndex = index;
            this.saveGameStatus(status);
        }
    }

    /**
     * Increment mode play count
     * Port of C lines 38001-38016
     */
    incrementModePlayCount(gameModeId: number): void {
        const status = this.loadGameStatus();

        switch (gameModeId) {
            case 1: // Survival
                status.modePlaySurvival++;
                break;
            case 2: // Rush
                status.modePlayRush++;
                break;
            case 3: // Quest
                // Quest play counts handled separately
                break;
            case 4: // Typo
                status.modePlayTypo++;
                break;
            default:
                status.modePlayOther++;
                break;
        }

        this.saveGameStatus(status);
    }

    /**
     * Increment quest play count
     * Port of C lines 37993-37994
     */
    incrementQuestPlayCount(stageMajor: number, stageMinor: number): void {
        const status = this.loadGameStatus();
        const index = stageMinor + stageMajor * 10;

        if (index >= 0 && index < status.questPlayCounts.length) {
            status.questPlayCounts[index]++;
            this.saveGameStatus(status);
        }
    }

    /**
     * Get unlocked perk IDs from save data
     */
    getUnlockedPerkIds(): number[] {
        const status = this.loadGameStatus();
        return status.unlockedPerkIds ?? [];
    }

    /**
     * Save unlocked perk IDs
     */
    setUnlockedPerkIds(ids: number[]): void {
        const status = this.loadGameStatus();
        status.unlockedPerkIds = ids;
        this.saveGameStatus(status);
    }

    /**
     * Get unlocked weapon IDs from save data
     */
    getUnlockedWeaponIds(): number[] {
        const status = this.loadGameStatus();
        return status.unlockedWeaponIds ?? [];
    }

    /**
     * Save unlocked weapon IDs
     */
    setUnlockedWeaponIds(ids: number[]): void {
        const status = this.loadGameStatus();
        status.unlockedWeaponIds = ids;
        this.saveGameStatus(status);
    }

    /**
     * Reset all progress (for debug/testing)
     */
    resetProgress(): void {
        const defaultStatus = createDefaultGameStatus();
        this.saveGameStatus(defaultStatus);
        this.storage.remove(STORAGE_KEYS.HIGH_SCORES);
    }

    // =========================================================================
    // High Score Methods
    // =========================================================================

    /**
     * Save a high score record
     * Port of highscore_save_record (C lines 32824-32864)
     *
     * @param record High score record to save
     * @returns Rank of the new record (0-based index)
     */
    saveHighScore(record: HighScoreRecord): number {
        const records = this.loadHighScores();

        // Add new record
        records.push(record);

        // Sort by appropriate field based on game mode
        // C highscores.c comparators:
        //   Survival (1): score_xp descending (higher XP = better)
        //   Rush (2): survival_elapsed_ms descending (longer survival = better)
        //   Quest (3): survival_elapsed_ms ascending, 0 sorted last (lower time = better)
        if (record.gameModeId === 3) {
            // Quest: ascending by survivalElapsedMs, 0 treated as "missing" (sorted last)
            records.sort((a, b) => {
                if (a.survivalElapsedMs === 0) return 1;
                if (b.survivalElapsedMs === 0) return -1;
                return a.survivalElapsedMs - b.survivalElapsedMs;
            });
        } else if (record.gameModeId === 2) {
            // Rush: descending by survivalElapsedMs
            records.sort((a, b) => b.survivalElapsedMs - a.survivalElapsedMs);
        } else {
            // Survival/other: descending by scoreXp
            records.sort((a, b) => b.scoreXp - a.scoreXp);
        }

        // Cap at MAX_HIGH_SCORES (C line 32729-32730)
        const trimmedRecords = records.slice(0, MAX_HIGH_SCORES);

        this.storage.set(STORAGE_KEYS.HIGH_SCORES, trimmedRecords);

        // Return rank of the new record
        return trimmedRecords.findIndex(
            (r) =>
                r.playerName === record.playerName &&
                r.scoreXp === record.scoreXp &&
                r.survivalElapsedMs === record.survivalElapsedMs,
        );
    }

    /**
     * Load high score records
     *
     * @param gameMode Optional filter by game mode
     * @param limit Optional limit on number of records
     */
    loadHighScores(gameMode?: number, limit?: number): HighScoreRecord[] {
        const records = this.storage.get<HighScoreRecord[]>(STORAGE_KEYS.HIGH_SCORES) ?? [];

        let filtered = gameMode !== undefined ? records.filter((r) => r.gameModeId === gameMode) : records;

        if (limit !== undefined) {
            filtered = filtered.slice(0, limit);
        }

        return filtered;
    }

    /**
     * Get rank of a score in the high score table
     * Port of highscore_rank_index (C lines 32886-32920)
     */
    getRank(record: HighScoreRecord): number {
        const records = this.loadHighScores(record.gameModeId);

        if (record.gameModeId === 3) {
            // Quest mode: lower time is better (ascending), 0 = missing
            // C: highscore_compare_quest_field32_asc_nonzero_first
            if (record.survivalElapsedMs === 0) return records.length;
            for (let i = 0; i < records.length; i++) {
                if (records[i].survivalElapsedMs === 0 ||
                    record.survivalElapsedMs < records[i].survivalElapsedMs) {
                    return i;
                }
            }
        } else if (record.gameModeId === 2) {
            // Rush mode: longer survival is better (descending)
            for (let i = 0; i < records.length; i++) {
                if (record.survivalElapsedMs > records[i].survivalElapsedMs) {
                    return i;
                }
            }
        } else {
            // Survival/other: higher XP is better (descending)
            for (let i = 0; i < records.length; i++) {
                if (record.scoreXp > records[i].scoreXp) {
                    return i;
                }
            }
        }

        return records.length; // Not ranked higher than any existing
    }

    /**
     * Clear all high scores
     */
    clearHighScores(): void {
        this.storage.remove(STORAGE_KEYS.HIGH_SCORES);
    }
}

/** Singleton instance for easy access */
let saveSystemInstance: SaveSystem | null = null;

/**
 * Get the global SaveSystem instance
 */
export function getSaveSystem(): SaveSystem {
    if (saveSystemInstance === null) {
        saveSystemInstance = new SaveSystem();
    }
    return saveSystemInstance;
}

/**
 * Reset the global instance (for testing)
 */
export function resetSaveSystem(): void {
    saveSystemInstance = null;
}
