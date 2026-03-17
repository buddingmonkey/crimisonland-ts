/**
 * AchievementSystem.ts - Achievement tracking and persistence
 *
 * TypeScript-native achievement system for tracking player milestones.
 * No C code equivalent - designed for browser localStorage persistence.
 */

import { STORAGE_KEYS } from '../data/SaveData';
import {
    AchievementId,
    AchievementProgress,
    ACHIEVEMENT_META,
    createDefaultAchievementProgress,
} from '../data/AchievementData';

/**
 * Achievement system for tracking and persisting player achievements
 */
export class AchievementSystem {
    private progress: AchievementProgress;
    private pendingNotifications: AchievementId[] = [];

    constructor() {
        this.progress = this.load();
    }

    /**
     * Check kill-based achievements
     */
    checkKillMilestones(sessionKills: number): void {
        // Update cumulative total
        this.progress.stats.totalKills += sessionKills;
        const total = this.progress.stats.totalKills;

        // Check milestones
        if (total >= 1) this.tryUnlock(AchievementId.FIRST_BLOOD);
        if (total >= 100) this.tryUnlock(AchievementId.HUNDRED_KILLS);
        if (total >= 1000) this.tryUnlock(AchievementId.THOUSAND_KILLS);
        if (total >= 10000) this.tryUnlock(AchievementId.TEN_THOUSAND_KILLS);

        this.save();
    }

    /**
     * Check survival time achievements
     */
    checkSurvivalMilestones(survivalTimeMs: number): void {
        // Update longest survival
        if (survivalTimeMs > this.progress.stats.longestSurvivalMs) {
            this.progress.stats.longestSurvivalMs = survivalTimeMs;
        }

        // Check milestones (1, 5, 10 minutes)
        if (survivalTimeMs >= 60000) this.tryUnlock(AchievementId.SURVIVOR_1MIN);
        if (survivalTimeMs >= 300000) this.tryUnlock(AchievementId.SURVIVOR_5MIN);
        if (survivalTimeMs >= 600000) this.tryUnlock(AchievementId.SURVIVOR_10MIN);

        this.save();
    }

    /**
     * Check quest-based achievements
     */
    checkQuestMilestones(
        questsComplete: number,
        isChapterComplete: boolean = false,
        allQuestsComplete: boolean = false,
    ): void {
        this.progress.stats.questsCompleted = questsComplete;

        if (questsComplete >= 1) this.tryUnlock(AchievementId.FIRST_QUEST);
        if (isChapterComplete) this.tryUnlock(AchievementId.CHAPTER_COMPLETE);
        if (allQuestsComplete) this.tryUnlock(AchievementId.ALL_QUESTS);

        this.save();
    }

    /**
     * Track weapon usage for weapon mastery achievements
     */
    trackWeaponUsage(weaponId: number): void {
        if (!this.progress.stats.weaponsUsed.includes(weaponId)) {
            this.progress.stats.weaponsUsed.push(weaponId);

            const count = this.progress.stats.weaponsUsed.length;
            if (count >= 5) this.tryUnlock(AchievementId.WEAPON_COLLECTOR);
            if (count >= 10) this.tryUnlock(AchievementId.WEAPON_MASTER);

            this.save();
        }
    }

    /**
     * Check score achievements
     */
    checkScoreMilestones(score: number): void {
        if (score > this.progress.stats.highestScore) {
            this.progress.stats.highestScore = score;
        }

        if (score >= 10000) this.tryUnlock(AchievementId.SCORE_10K);
        if (score >= 100000) this.tryUnlock(AchievementId.SCORE_100K);

        this.save();
    }

    /**
     * Attempt to unlock an achievement
     * Returns true if newly unlocked
     */
    private tryUnlock(id: AchievementId): boolean {
        if (this.isUnlocked(id)) return false;

        this.progress.unlockedIds.push(id);
        this.progress.unlockDates[id] = Date.now();
        this.pendingNotifications.push(id);

        console.log(`[Achievement] Unlocked: ${ACHIEVEMENT_META[id].name}`);
        return true;
    }

    /**
     * Check if achievement is unlocked
     */
    isUnlocked(id: AchievementId): boolean {
        return this.progress.unlockedIds.includes(id);
    }

    /**
     * Get all unlocked achievement IDs
     */
    getUnlockedIds(): AchievementId[] {
        return this.progress.unlockedIds as AchievementId[];
    }

    /**
     * Get unlock count
     */
    getUnlockCount(): number {
        return this.progress.unlockedIds.length;
    }

    /**
     * Get total achievement count
     */
    getTotalCount(): number {
        return Object.keys(ACHIEVEMENT_META).length;
    }

    /**
     * Get pending notifications and clear them
     */
    popNotifications(): AchievementId[] {
        const notifications = [...this.pendingNotifications];
        this.pendingNotifications = [];
        return notifications;
    }

    /**
     * Get current progress stats
     */
    getStats(): AchievementProgress['stats'] {
        return { ...this.progress.stats };
    }

    /**
     * Save progress to localStorage
     */
    save(): void {
        try {
            const json = JSON.stringify(this.progress);
            localStorage.setItem(STORAGE_KEYS.ACHIEVEMENTS, json);
        } catch (e) {
            console.error('[Achievement] Save failed:', e);
        }
    }

    /**
     * Load progress from localStorage
     */
    private load(): AchievementProgress {
        try {
            const json = localStorage.getItem(STORAGE_KEYS.ACHIEVEMENTS);
            if (json) {
                const parsed = JSON.parse(json) as AchievementProgress;
                // Ensure stats object exists with defaults
                if (!parsed.stats) {
                    parsed.stats = createDefaultAchievementProgress().stats;
                }
                return parsed;
            }
        } catch (e) {
            console.error('[Achievement] Load failed:', e);
        }
        return createDefaultAchievementProgress();
    }

    /**
     * Reset all achievement progress (for testing)
     */
    reset(): void {
        this.progress = createDefaultAchievementProgress();
        this.save();
    }
}

// Singleton instance
let achievementSystemInstance: AchievementSystem | null = null;

/**
 * Get the global achievement system instance
 */
export function getAchievementSystem(): AchievementSystem {
    if (!achievementSystemInstance) {
        achievementSystemInstance = new AchievementSystem();
    }
    return achievementSystemInstance;
}
