/**
 * StatisticsSystem.ts - Aggregated game statistics
 *
 * Provides computed statistics from SaveSystem data for UI display.
 *
 * C code references:
 * - Statistics display: game menu statistics screen
 * - Mode play counts: lines 38001-38016
 * - Quest progress: questUnlockIndex tracking
 */

import { SaveSystem, getSaveSystem } from './SaveSystem';
import type { GameStatusData } from '../data/SaveData';
import { getWeaponStats } from '../data/WeaponData';

/**
 * Aggregated statistics for display
 */
export interface AggregatedStats {
    // Game counts
    totalGamesPlayed: number;
    survivalGamesPlayed: number;
    rushGamesPlayed: number;
    questGamesPlayed: number;
    otherGamesPlayed: number;

    // Quest progress
    questsUnlocked: number;
    totalQuests: number;
    questProgress: number; // 0-100%

    // Weapon usage (top 5)
    topWeapons: Array<{ weaponId: number; usageCount: number }>;

    // Most played quest
    mostPlayedQuest: { tier: number; index: number; playCount: number } | null;
}

/**
 * StatisticsSystem - aggregates game statistics
 */
export class StatisticsSystem {
    private saveSystem: SaveSystem;

    constructor(saveSystem?: SaveSystem) {
        this.saveSystem = saveSystem ?? getSaveSystem();
    }

    /**
     * Get all aggregated statistics
     */
    getStats(): AggregatedStats {
        const status = this.saveSystem.loadGameStatus();
        return this.aggregateStats(status);
    }

    /**
     * Aggregate stats from game status data
     */
    private aggregateStats(status: GameStatusData): AggregatedStats {
        // Total games played
        const totalGamesPlayed =
            status.modePlaySurvival +
            status.modePlayRush +
            status.modePlayTypo +
            status.modePlayOther +
            status.questPlayCounts.reduce((sum, count) => sum + count, 0);

        // Top weapons by usage
        const weaponUsage = status.weaponUsageCounts
            .map((count, id) => ({ weaponId: id, usageCount: count }))
            .filter((w) => w.usageCount > 0)
            .sort((a, b) => b.usageCount - a.usageCount)
            .slice(0, 5);

        // Most played quest
        let mostPlayedQuest: AggregatedStats['mostPlayedQuest'] = null;
        let maxPlayCount = 0;
        for (let i = 0; i < status.questPlayCounts.length; i++) {
            if (status.questPlayCounts[i] > maxPlayCount) {
                maxPlayCount = status.questPlayCounts[i];
                const tier = Math.floor(i / 10) + 1;
                const index = (i % 10) + 1;
                mostPlayedQuest = { tier, index, playCount: maxPlayCount };
            }
        }

        // Quest games total
        const questGamesPlayed = status.questPlayCounts.reduce((sum, count) => sum + count, 0);

        return {
            totalGamesPlayed,
            survivalGamesPlayed: status.modePlaySurvival,
            rushGamesPlayed: status.modePlayRush,
            questGamesPlayed,
            otherGamesPlayed: status.modePlayTypo + status.modePlayOther,

            questsUnlocked: status.questUnlockIndex,
            totalQuests: 40,
            questProgress: Math.round((status.questUnlockIndex / 40) * 100),

            topWeapons: weaponUsage,
            mostPlayedQuest,
        };
    }

    /**
     * Get formatted time string
     */
    static formatTime(ms: number): string {
        const totalSeconds = Math.floor(ms / 1000);
        const hours = Math.floor(totalSeconds / 3600);
        const minutes = Math.floor((totalSeconds % 3600) / 60);
        const seconds = totalSeconds % 60;

        if (hours > 0) {
            return `${hours}:${minutes.toString().padStart(2, '0')}:${seconds.toString().padStart(2, '0')}`;
        }
        return `${minutes}:${seconds.toString().padStart(2, '0')}`;
    }

    /**
     * Get weapon name by ID
     */
    static getWeaponName(weaponId: number): string {
        return getWeaponStats(weaponId).name;
    }
}

/** Singleton instance */
let statisticsSystemInstance: StatisticsSystem | null = null;

/**
 * Get the global StatisticsSystem instance
 */
export function getStatisticsSystem(): StatisticsSystem {
    if (statisticsSystemInstance === null) {
        statisticsSystemInstance = new StatisticsSystem();
    }
    return statisticsSystemInstance;
}

/**
 * Reset the global instance (for testing)
 */
export function resetStatisticsSystem(): void {
    statisticsSystemInstance = null;
}
