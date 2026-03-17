/**
 * QuestSystem - Core quest management system
 *
 * Ported from crimsonland.exe_decompiled.c:
 * - quest_mode_update: lines 4866-4931
 * - quest_spawn_timeline_update: lines 27875-27952
 * - quest_start_selected: lines 31936-32012
 */

import { QuestMeta, QuestSpawnEntry, EnemyTemplate, getQuest } from '../../data/QuestData';
import { gameConsole } from '../../console/Console';
import type { SoundSystem } from '../../audio/SoundSystem';
import { SoundId } from '../../audio/SoundId';
import type { MusicSystem } from '../../audio/MusicSystem';

/**
 * Callback for spawning enemies
 */
export type SpawnCallback = (entry: QuestSpawnEntry) => void;

/**
 * Quest state enum
 */
export enum QuestState {
    INACTIVE = 0, // No quest active
    PLAYING = 1, // Quest in progress
    TRANSITIONING = 2, // Quest completed, showing transition
    COMPLETE = 3, // Quest fully complete
}

/**
 * QuestSystem - manages quest gameplay, spawn timeline, and completion
 *
 * C code references:
 * - quest_mode_update (lines 4866-4931): Main update loop
 * - quest_spawn_timeline_update (lines 27875-27952): Spawn processing
 * - quest_start_selected (lines 31936-32012): Quest initialization
 */
export class QuestSystem {
    // Current quest
    private currentQuest: QuestMeta | null = null;

    // Quest timeline (C: quest_spawn_timeline)
    private timelineMs: number = 0;

    // Transition timer (C: quest_transition_timer_ms)
    // -1 = not transitioning, 0+ = transitioning
    private transitionTimerMs: number = -1;

    // Spawn tracking
    private spawnCounts: number[] = []; // Remaining count for each spawn entry

    // Quest state
    private state: QuestState = QuestState.INACTIVE;

    // Stage tracking (C: _quest_stage_major, _quest_stage_minor)
    private stageMajor: number = 1;
    private stageMinor: number = 1;

    // Unlock progress (C: quest_unlock_index)
    private unlockIndex: number = 0;

    // Enemy tracking
    private activeEnemyCount: number = 0;

    // Spawn callback
    private spawnCallback: SpawnCallback | null = null;

    // Total enemies spawned/killed for stats
    private totalSpawned: number = 0;
    private totalKilled: number = 0;

    // Stall timer (C: crt_locale_lc_handle)
    // Tracks how long enemies have been alive without a new spawn batch.
    // If enemies are still alive after 3000ms AND the timeline is past 1700ms,
    // force-trigger the next spawn entry regardless of its trigger time.
    private stallTimerMs: number = 0;

    // Elapsed timer (C: quest_elapsed_timer_ms)
    // Increments unconditionally every frame (unlike timelineMs which pauses).
    // Used for the quest name fade animation in the HUD.
    private elapsedTimerMs: number = 0;

    // Audio systems for transition SFX/music (Fix 6)
    private soundSystem: SoundSystem | null = null;
    private musicSystem: MusicSystem | null = null;
    private hasPlayedHitSfx: boolean = false;
    private hasPlayedVictoryMusic: boolean = false;

    // Hardcore mode (Fix 4: C quest.c lines ~6080-6100)
    private hardcoreMode: boolean = false;

    // Retry difficulty scaling (C: quest_fail_retry_count)
    // Increments each time the player retries the SAME quest after failing.
    // Resets to 0 when starting a different quest.
    private failRetryCount: number = 0;
    private lastQuestTier: number = -1;
    private lastQuestIndex: number = -1;

    /**
     * Start a quest by tier and index
     * C: quest_start_selected (lines 31936-32012)
     */
    startQuest(tier: number, index: number): boolean {
        const quest = getQuest(tier, index);
        if (!quest) {
            gameConsole.print(`Quest not found: tier ${tier}, index ${index}`);
            return false;
        }

        // C: quest_fail_retry_count tracking (creatures.c lines 3584-3628)
        // Increment retry count when replaying the same quest
        // Reset when starting a different quest
        if (tier === this.lastQuestTier && index === this.lastQuestIndex) {
            this.failRetryCount++;
        } else {
            this.failRetryCount = 0;
        }
        this.lastQuestTier = tier;
        this.lastQuestIndex = index;

        // C line 3628: hardcore mode resets retry count
        if (this.hardcoreMode) {
            this.failRetryCount = 0;
        }

        // Reset state (C lines 31946-31969)
        this.currentQuest = quest;
        this.timelineMs = 0;
        this.transitionTimerMs = -1;
        this.elapsedTimerMs = 0;
        this.state = QuestState.PLAYING;
        this.stageMajor = tier;
        this.stageMinor = index;
        this.activeEnemyCount = 0;
        this.totalSpawned = 0;
        this.totalKilled = 0;
        this.stallTimerMs = 0;

        // Initialize spawn counts
        this.spawnCounts = quest.spawns.map((s) => s.count);

        // Reset transition SFX flags
        this.hasPlayedHitSfx = false;
        this.hasPlayedVictoryMusic = false;

        // Apply hardcore mode count modifiers (C quest.c lines ~6080-6100)
        if (this.hardcoreMode) {
            for (let i = 0; i < this.spawnCounts.length; i++) {
                if (this.spawnCounts[i] > 1) {
                    const templateId = quest.spawns[i].templateId;
                    if (templateId === EnemyTemplate.SPIDER_FAST_RED) {
                        this.spawnCounts[i] += 2;
                    } else if (templateId !== EnemyTemplate.BOSS_ZOMBIE) {
                        this.spawnCounts[i] += 8;
                    }
                }
            }
        }

        gameConsole.print(`Started quest: ${quest.name} (Tier ${tier}, Quest ${index})`);
        gameConsole.print(`Time limit: ${quest.timeLimitMs / 1000}s, Spawns: ${quest.spawns.length}`);

        return true;
    }

    /**
     * Set callback for when enemies need to be spawned
     */
    setSpawnCallback(callback: SpawnCallback): void {
        this.spawnCallback = callback;
    }

    /**
     * Report an enemy was spawned (for tracking)
     */
    reportEnemySpawned(count: number = 1): void {
        this.activeEnemyCount += count;
        this.totalSpawned += count;
    }

    /**
     * Report an enemy was killed
     */
    reportEnemyKilled(): void {
        if (this.activeEnemyCount <= 0) {
            gameConsole.print(`[QUEST WARN] reportEnemyKilled called but activeEnemyCount is already ${this.activeEnemyCount} (totalSpawned=${this.totalSpawned}, totalKilled=${this.totalKilled})`);
        }
        this.activeEnemyCount = Math.max(0, this.activeEnemyCount - 1);
        this.totalKilled++;
    }

    /**
     * Update the quest system
     * C: quest_mode_update (lines 4866-4931)
     */
    update(dtMs: number): void {
        if (this.state === QuestState.INACTIVE || !this.currentQuest) {
            return;
        }

        if (this.state === QuestState.PLAYING) {
            // Advance timeline only when enemies alive or spawns remaining (C lines 12-22)
            // C: if (quest_spawn_count > 0 || creatures_active_count > 0)
            if (!this.isSpawnTableEmpty() || this.activeEnemyCount > 0) {
                this.timelineMs += dtMs;
            }

            // C quest.c:22: quest_elapsed_timer_ms += frame_dt_ms (unconditional)
            this.elapsedTimerMs += dtMs;

            // Update stall timer (C: crt_locale_lc_handle)
            // Only increments when enemies are active
            if (this.activeEnemyCount > 0) {
                this.stallTimerMs += dtMs;
            } else {
                this.stallTimerMs = 0;
            }

            // Process spawn timeline
            this.updateSpawnTimeline();

            // NOTE: checkCompletion() is NOT called here — it runs as a deferred
            // check in GamePlayingUpdate.ts AFTER all kill-reporting phases
            // (enemySpawner.update nest children, burning/poison, collisions).
            // Calling it here caused a race condition: if all enemies died on
            // frame N, frame N+1's update() would see activeEnemyCount===0 and
            // transition to COMPLETE before enemySpawner.update() could spawn
            // nest spawner children.
        } else if (this.state === QuestState.TRANSITIONING) {
            // Handle transition timer (C lines 4899-4926)
            this.updateTransition(dtMs);
        }
    }

    /**
     * Update spawn timeline
     * C: quest_spawn_timeline_update (lines 27875-27952)
     *
     * Key behaviors from C code:
     * 1. If enemies are alive for > 3000ms AND timeline > 1700ms (0x6a4),
     *    force-trigger the next pending spawn entry regardless of its trigger time.
     * 2. When spawning multiple enemies (count > 1), offset each enemy's position
     *    by 40px (0x28) alternating positive/negative from the spawn point.
     * 3. Process all entries with the same trigger time together in one batch.
     */
    private updateSpawnTimeline(): void {
        if (!this.currentQuest) return;

        const spawns = this.currentQuest.spawns;

        for (let i = 0; i < spawns.length; i++) {
            if (this.spawnCounts[i] <= 0) continue;

            const entry = spawns[i];

            // C lines 2004-2007: Check if trigger time reached OR stall timer exceeded
            const timeReached = this.timelineMs >= entry.triggerTimeMs;
            const stallForced = this.activeEnemyCount > 0 && this.stallTimerMs > 3000 && this.timelineMs > 1700;

            if (timeReached || stallForced) {
                // Track how many enemies were actually spawned so we only consume
                // the entry if spawning succeeded. If spawnQuestEnemy returns null
                // (maxEnemies cap hit due to dying enemies), we retain the entry
                // for retry next frame instead of permanently losing it.
                const countBefore = this.activeEnemyCount;

                if (this.spawnCallback) {
                    const count = this.spawnCounts[i];

                    // C lines 2014-2038: Multi-spawn position offsetting
                    // Each enemy is offset by 40px (0x28), alternating direction
                    // Direction depends on whether spawn point is off-map horizontally or vertically
                    const isOffMapX = entry.posX < 0 || entry.posX > 1024;

                    for (let j = 0; j < count; j++) {
                        const offsetAmount = j * 40; // 0x28 = 40
                        const sign = (j & 1) !== 0 ? -1 : 1;

                        let posX = entry.posX;
                        let posY = entry.posY;

                        if (isOffMapX) {
                            // Off-map horizontally: offset Y position
                            posY += offsetAmount * sign;
                        } else {
                            // On-map or off-map vertically: offset X position
                            posX += offsetAmount * sign;
                        }

                        const spawnEntry: QuestSpawnEntry = {
                            ...entry,
                            posX,
                            posY,
                            count: 1,
                        };
                        this.spawnCallback(spawnEntry);
                    }
                }

                const spawned = this.activeEnemyCount - countBefore;
                if (spawned > 0) {
                    // Enemies were successfully spawned — consume the entry
                    this.spawnCounts[i] = 0;
                } else {
                    // Spawn failed (maxEnemies cap hit) — retain entry for retry
                    // Don't return; let the loop continue to check other entries
                    continue;
                }
                // Reset stall timer after spawning (C line 2040)
                this.stallTimerMs = 0;

                // C lines 2042-2048: Process all entries with the same trigger time
                // Continue to check if next entry has the same trigger time
                while (
                    i + 1 < spawns.length &&
                    this.spawnCounts[i + 1] > 0 &&
                    spawns[i + 1].triggerTimeMs === entry.triggerTimeMs
                ) {
                    i++;
                    const nextEntry = spawns[i];
                    const nextCount = this.spawnCounts[i];
                    const countBeforeNext = this.activeEnemyCount;

                    if (this.spawnCallback) {
                        const isNextOffMapX = nextEntry.posX < 0 || nextEntry.posX > 1024;

                        for (let j = 0; j < nextCount; j++) {
                            const offsetAmount = j * 40;
                            const sign = (j & 1) !== 0 ? -1 : 1;

                            let posX = nextEntry.posX;
                            let posY = nextEntry.posY;

                            if (isNextOffMapX) {
                                posY += offsetAmount * sign;
                            } else {
                                posX += offsetAmount * sign;
                            }

                            const spawnEntry: QuestSpawnEntry = {
                                ...nextEntry,
                                posX,
                                posY,
                                count: 1,
                            };
                            this.spawnCallback(spawnEntry);
                        }
                    }
                    const nextSpawned = this.activeEnemyCount - countBeforeNext;
                    if (nextSpawned > 0) {
                        this.spawnCounts[i] = 0;
                    }
                }

                // After spawning a batch, return (C line 2050-2051)
                return;
            }
        }
    }

    /**
     * Check if quest is complete.
     * C: quest_mode_update completion check (lines 4885-4891)
     *
     * Public so the game loop can call it as a deferred check *after*
     * all kill-reporting phases (burning, collisions, AoE) have run,
     * ensuring activeEnemyCount reflects all kills from the current frame.
     */
    checkCompletion(): void {
        if (this.state !== QuestState.PLAYING) return;
        // Quest complete when spawn table empty AND no active enemies
        if (this.isSpawnTableEmpty() && this.activeEnemyCount === 0) {
            if (this.transitionTimerMs < 0) {
                // Start transition (C lines 4891-4896)
                gameConsole.print('Quest complete! Starting transition...');
                // C line 32: sfx_mute_all(music_track_extra_0) — mute gameplay music immediately
                this.musicSystem?.stop();
                // C: starts at frame_dt_ms; TS starts at 0 — equivalent within one frame
                this.transitionTimerMs = 0;
                this.state = QuestState.TRANSITIONING;
            }
        }
    }

    /**
     * Update transition animation
     * C: transition handling (lines 4899-4926)
     */
    private updateTransition(dtMs: number): void {
        this.transitionTimerMs += dtMs;

        // Transition phases from C code:
        // 800ms: play sfx_questhit
        // 2000ms: play victory music
        // 2500ms (0x9c4): update unlock index, transition to next screen

        // Fix 6: Play quest hit SFX at 800ms (C: sfx_play(sfx_questhit))
        if (this.transitionTimerMs >= 800 && !this.hasPlayedHitSfx) {
            this.soundSystem?.play(SoundId.QUEST_HIT);
            this.hasPlayedHitSfx = true;
        }

        // Fix 6: Play victory music at 2000ms (C: music_play(music_crimsonquest))
        if (this.transitionTimerMs >= 2000 && !this.hasPlayedVictoryMusic) {
            this.musicSystem?.play('crimsonquest.ogg');
            this.hasPlayedVictoryMusic = true;
        }

        if (this.transitionTimerMs > 2500) {
            // Update unlock progress (C lines 4912-4917)
            const questSeqId = (this.stageMajor - 1) * 10 + this.stageMinor - 1;
            if (this.unlockIndex < questSeqId) {
                this.unlockIndex = questSeqId;
                gameConsole.print(`Unlock progress: ${this.unlockIndex}`);
            }

            this.state = QuestState.COMPLETE;
            gameConsole.print('Quest transition complete!');
        }
    }

    /**
     * Check if spawn table is empty
     * C: quest_spawn_table_empty (lines 27848-27865)
     */
    isSpawnTableEmpty(): boolean {
        return this.spawnCounts.every((count) => count === 0);
    }

    /**
     * Skip to quest completion (for testing)
     */
    skipToComplete(): void {
        if (this.state !== QuestState.PLAYING) return;

        // Clear all spawn counts
        this.spawnCounts = this.spawnCounts.map(() => 0);
        this.activeEnemyCount = 0;

        // Trigger completion check
        this.checkCompletion();
    }

    /**
     * Force complete (for testing)
     */
    forceComplete(): void {
        this.skipToComplete();
        this.transitionTimerMs = 3000;
        this.updateTransition(0);
    }

    // ========== Getters ==========

    getCurrentQuest(): QuestMeta | null {
        return this.currentQuest;
    }

    getTimelineMs(): number {
        return this.timelineMs;
    }

    getElapsedTimerMs(): number {
        return this.elapsedTimerMs;
    }

    /**
     * Get transition timer in ms (C: quest_transition_timer_ms)
     * -1 = not transitioning, 0+ = transitioning
     * Used by HUD to render the "Level Complete" overlay.
     */
    getTransitionTimerMs(): number {
        return this.transitionTimerMs;
    }

    getState(): QuestState {
        return this.state;
    }

    getStageMajor(): number {
        return this.stageMajor;
    }

    getStageMinor(): number {
        return this.stageMinor;
    }

    getUnlockIndex(): number {
        return this.unlockIndex;
    }

    getActiveEnemyCount(): number {
        return this.activeEnemyCount;
    }

    getTotalSpawned(): number {
        return this.totalSpawned;
    }

    getTotalKilled(): number {
        return this.totalKilled;
    }

    getPendingSpawnCount(): number {
        return this.spawnCounts.reduce((sum, count) => sum + count, 0);
    }

    isActive(): boolean {
        return this.state === QuestState.PLAYING || this.state === QuestState.TRANSITIONING;
    }

    /**
     * Set unlock index (for testing/loading save)
     */
    setUnlockIndex(index: number): void {
        this.unlockIndex = index;
    }

    /**
     * Reset to initial state
     */
    reset(): void {
        this.currentQuest = null;
        this.timelineMs = 0;
        this.transitionTimerMs = -1;
        this.elapsedTimerMs = 0;
        this.spawnCounts = [];
        this.state = QuestState.INACTIVE;
        this.activeEnemyCount = 0;
        this.totalSpawned = 0;
        this.totalKilled = 0;
        this.stallTimerMs = 0;
        this.hasPlayedHitSfx = false;
        this.hasPlayedVictoryMusic = false;
        this.failRetryCount = 0;
        this.lastQuestTier = -1;
        this.lastQuestIndex = -1;
    }

    /**
     * Set sound system for transition SFX
     */
    setSoundSystem(soundSystem: SoundSystem): void {
        this.soundSystem = soundSystem;
    }

    /**
     * Set music system for victory music
     */
    setMusicSystem(musicSystem: MusicSystem): void {
        this.musicSystem = musicSystem;
    }

    /**
     * Set hardcore mode (C: config_blob.hardcore)
     */
    setHardcoreMode(enabled: boolean): void {
        this.hardcoreMode = enabled;
    }

    /**
     * Get hardcore mode state
     */
    isHardcoreMode(): boolean {
        return this.hardcoreMode;
    }

    /**
     * Get fail retry count (C: quest_fail_retry_count)
     * Used by QuestEnemySpawner to scale enemy difficulty down on retries.
     */
    getFailRetryCount(): number {
        return this.failRetryCount;
    }
}

// Singleton instance
export const questSystem = new QuestSystem();
