/**
 * HighScoreSystem.ts - High score management
 *
 * Dedicated high score system with ranking and filtering.
 * Delegates storage to SaveSystem.
 *
 * C code references:
 * - highscore_save_record: lines 32824-32864
 * - highscore_save_active: lines 32869-32878
 * - highscore_rank_index: lines 32882-32920
 * - highscore_table_count max: 100 (line 32729)
 */

import { HighScoreRecord, MAX_HIGH_SCORES, createHighScoreRecord } from '../data/SaveData';
import { SaveSystem, getSaveSystem } from './SaveSystem';

/**
 * Game mode identifiers
 * C code: game_mode_id values
 */
export enum GameMode {
    Survival = 1,
    Rush = 2,
    Quest = 3,
    Typo = 4,
}

/**
 * HighScoreSystem - manages high score table
 *
 * Features:
 * - Add/retrieve high scores
 * - Filter by game mode
 * - Get current rank for a score
 * - Max 100 entries (C line 32729)
 */
export class HighScoreSystem {
    private saveSystem: SaveSystem;

    /** Currently active record being built during gameplay */
    private activeRecord: HighScoreRecord | null = null;

    constructor(saveSystem?: SaveSystem) {
        this.saveSystem = saveSystem ?? getSaveSystem();
    }

    // =========================================================================
    // Active Record Management
    // =========================================================================

    /**
     * Start tracking a new game session for high score
     * Call this when starting a new game
     */
    startSession(playerName: string, gameModeId: GameMode): void {
        this.activeRecord = createHighScoreRecord(playerName, 0, 0, gameModeId);
    }

    /**
     * Update the active record during gameplay
     */
    updateSession(updates: Partial<Omit<HighScoreRecord, 'playerName' | 'gameModeId' | 'date'>>): void {
        if (this.activeRecord) {
            Object.assign(this.activeRecord, updates);
        }
    }

    /**
     * End the session and save the high score
     * Port of highscore_save_active (C lines 32869-32878)
     *
     * @returns The rank achieved (0-based), or -1 if no active session
     */
    endSession(): number {
        if (!this.activeRecord) {
            console.warn('HighScoreSystem: No active session to end');
            return -1;
        }

        const record = this.activeRecord;
        this.activeRecord = null;

        return this.addRecord(record);
    }

    /**
     * Get the active record (for display during gameplay)
     */
    getActiveRecord(): HighScoreRecord | null {
        return this.activeRecord;
    }

    // =========================================================================
    // High Score Table Management
    // =========================================================================

    /**
     * Add a high score record
     * Port of highscore_save_record (C lines 32824-32864)
     *
     * @param record The record to add
     * @returns The rank achieved (0-based index)
     */
    addRecord(record: HighScoreRecord): number {
        return this.saveSystem.saveHighScore(record);
    }

    /**
     * Get high score records
     *
     * @param gameMode Optional filter by game mode
     * @param limit Optional limit (default: 10)
     */
    getRecords(gameMode?: GameMode, limit: number = 10): HighScoreRecord[] {
        return this.saveSystem.loadHighScores(gameMode, limit);
    }

    /**
     * Get all records (up to max)
     */
    getAllRecords(): HighScoreRecord[] {
        return this.saveSystem.loadHighScores(undefined, MAX_HIGH_SCORES);
    }

    /**
     * Get the current rank for a potential score
     * Port of highscore_rank_index (C lines 32886-32920)
     *
     * @param record Record to check
     * @returns Rank (0-based), or -1 if wouldn't make the table
     */
    getCurrentRank(record: HighScoreRecord): number {
        const rank = this.saveSystem.getRank(record);
        return rank >= MAX_HIGH_SCORES ? -1 : rank;
    }

    /**
     * Would this score make the high score table?
     */
    wouldMakeTable(scoreXp: number, survivalElapsedMs: number, gameModeId: GameMode): boolean {
        const testRecord = createHighScoreRecord('', scoreXp, survivalElapsedMs, gameModeId);
        return this.getCurrentRank(testRecord) !== -1;
    }

    /**
     * Get top score for a game mode
     */
    getTopScore(gameMode: GameMode): HighScoreRecord | null {
        const records = this.getRecords(gameMode, 1);
        return records.length > 0 ? records[0] : null;
    }

    /**
     * Clear all high scores
     */
    clearRecords(): void {
        this.saveSystem.clearHighScores();
    }
}

/** Singleton instance */
let highScoreSystemInstance: HighScoreSystem | null = null;

/**
 * Get the global HighScoreSystem instance
 */
export function getHighScoreSystem(): HighScoreSystem {
    if (highScoreSystemInstance === null) {
        highScoreSystemInstance = new HighScoreSystem();
    }
    return highScoreSystemInstance;
}

/**
 * Reset the global instance (for testing)
 */
export function resetHighScoreSystem(): void {
    highScoreSystemInstance = null;
}
