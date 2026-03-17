/**
 * QuestSystem unit tests
 */

import { describe, it, expect, beforeEach, vi } from 'vitest';
import { QuestSystem, QuestState } from '../quest/QuestSystem';
import { QUEST_DATABASE, getQuest, getQuestById, getQuestsInTier, EnemyTemplate } from '../../data/QuestData';

// Mock the console to prevent log spam during tests
vi.mock('../../console/Console', () => ({
    gameConsole: {
        log: vi.fn(),
        print: vi.fn(),
    },
}));

describe('QuestSystem', () => {
    let questSystem: QuestSystem;

    beforeEach(() => {
        vi.clearAllMocks();
        questSystem = new QuestSystem();
    });

    describe('QuestData', () => {
        it('should have 50 quests defined', () => {
            expect(QUEST_DATABASE.length).toBe(50);
        });

        it('should have 10 quests per tier', () => {
            for (let tier = 1; tier <= 5; tier++) {
                const tierQuests = getQuestsInTier(tier);
                expect(tierQuests.length).toBe(10);
            }
        });

        it('should have unique quest IDs', () => {
            const ids = QUEST_DATABASE.map((q) => q.id);
            const uniqueIds = new Set(ids);
            expect(uniqueIds.size).toBe(50);
        });

        it('should retrieve quest by tier and index', () => {
            const quest = getQuest(1, 1);
            expect(quest).toBeDefined();
            expect(quest?.name).toBe('Land Hostile');
            expect(quest?.tier).toBe(1);
            expect(quest?.index).toBe(1);
        });

        it('should retrieve quest by ID', () => {
            const quest = getQuestById(0);
            expect(quest).toBeDefined();
            expect(quest?.name).toBe('Land Hostile');
        });

        it('should have valid spawn entries for Land Hostile', () => {
            const quest = getQuest(1, 1);
            expect(quest?.spawns).toBeDefined();
            expect(quest?.spawns.length).toBeGreaterThan(0);

            // First spawn should trigger at 500ms with 1 zombie
            expect(quest?.spawns[0].triggerTimeMs).toBe(500);
            expect(quest?.spawns[0].templateId).toBe(EnemyTemplate.SPIDER_STANDARD);
            expect(quest?.spawns[0].count).toBe(1);
        });

        it('should have all quests with startWeaponId defined', () => {
            for (const quest of QUEST_DATABASE) {
                expect(quest.startWeaponId).toBeDefined();
                expect(typeof quest.startWeaponId).toBe('number');
            }
        });

        it('should have all quests with timeLimitMs defined', () => {
            for (const quest of QUEST_DATABASE) {
                expect(quest.timeLimitMs).toBeDefined();
                expect(quest.timeLimitMs).toBeGreaterThan(0);
            }
        });
    });

    describe('Quest Start', () => {
        it('should start a quest successfully', () => {
            const result = questSystem.startQuest(1, 1);
            expect(result).toBe(true);
            expect(questSystem.getState()).toBe(QuestState.PLAYING);
        });

        it('should initialize timeline to 0', () => {
            questSystem.startQuest(1, 1);
            expect(questSystem.getTimelineMs()).toBe(0);
        });

        it('should set current quest', () => {
            questSystem.startQuest(1, 1);
            const quest = questSystem.getCurrentQuest();
            expect(quest).toBeDefined();
            expect(quest?.name).toBe('Land Hostile');
        });

        it('should start tier 5 quest successfully', () => {
            const result = questSystem.startQuest(5, 1);
            expect(result).toBe(true);
            expect(questSystem.getState()).toBe(QuestState.PLAYING);
        });

        it('should return false for invalid quest', () => {
            const result = questSystem.startQuest(6, 1); // Invalid tier
            expect(result).toBe(false);
            expect(questSystem.getState()).toBe(QuestState.INACTIVE);
        });

        it('should set stage major and minor', () => {
            questSystem.startQuest(2, 5); // Tier 2, Quest 5
            expect(questSystem.getStageMajor()).toBe(2);
            expect(questSystem.getStageMinor()).toBe(5);
        });
    });

    describe('Timeline Update', () => {
        it('should advance timeline with update', () => {
            questSystem.startQuest(1, 1);
            questSystem.update(100); // 100ms
            expect(questSystem.getTimelineMs()).toBe(100);
        });

        it('should accumulate timeline over multiple updates', () => {
            questSystem.startQuest(1, 1);
            questSystem.update(100);
            questSystem.update(150);
            questSystem.update(50);
            expect(questSystem.getTimelineMs()).toBe(300);
        });

        it('should not update when inactive', () => {
            questSystem.update(100);
            expect(questSystem.getTimelineMs()).toBe(0);
        });
    });

    describe('Spawn Triggering', () => {
        it('should call spawn callback when timeline reaches trigger time', () => {
            const spawnCallback = vi.fn();
            questSystem.setSpawnCallback(spawnCallback);
            questSystem.startQuest(1, 1);

            // First spawn at 500ms
            questSystem.update(600); // Past first trigger

            expect(spawnCallback).toHaveBeenCalled();
        });

        it('should pass spawn entry with count to callback', () => {
            const spawnCallback = vi.fn();
            questSystem.setSpawnCallback(spawnCallback);
            questSystem.startQuest(1, 1);

            questSystem.update(600);

            expect(spawnCallback).toHaveBeenCalledWith(
                expect.objectContaining({
                    count: 1,
                    templateId: EnemyTemplate.SPIDER_STANDARD,
                }),
            );
        });

        it('should trigger multiple spawns at correct times', () => {
            // Callback must report spawns so entries are consumed
            const spawnCallback = vi.fn(() => questSystem.reportEnemySpawned(1));
            questSystem.setSpawnCallback(spawnCallback);
            questSystem.startQuest(1, 1);

            // Land Hostile spawns:
            // 500ms: 1 zombie
            // 2500ms: 2 zombies
            // 6500ms: 3 zombies
            // 11500ms: 4 zombies
            // Note: new system spawns per-enemy (count=1 each) with position offsets
            // and returns after each batch, so we need update() calls between batches

            questSystem.update(600); // First spawn (1 enemy)
            expect(spawnCallback).toHaveBeenCalledTimes(1);

            questSystem.update(2000); // Second spawn (2 enemies = 2 calls)
            expect(spawnCallback).toHaveBeenCalledTimes(3); // 1 + 2

            questSystem.update(4000); // Third spawn (3 enemies = 3 calls)
            expect(spawnCallback).toHaveBeenCalledTimes(6); // 1 + 2 + 3

            questSystem.update(5000); // Fourth spawn (4 enemies = 4 calls)
            expect(spawnCallback).toHaveBeenCalledTimes(10); // 1 + 2 + 3 + 4
        });

        it('should mark spawn table as empty after all spawns triggered', () => {
            // Callback must report spawns so entries are consumed
            questSystem.setSpawnCallback(() => questSystem.reportEnemySpawned(1));
            questSystem.startQuest(1, 1);
            expect(questSystem.isSpawnTableEmpty()).toBe(false);

            // New system returns after each batch, so we need multiple update calls
            // to drain all 4 spawn entries at different trigger times
            questSystem.update(600); // Triggers entry at 500ms
            questSystem.update(2000); // Triggers entry at 2500ms (total 2600)
            questSystem.update(4000); // Triggers entry at 6500ms (total 6600)
            questSystem.update(5000); // Triggers entry at 11500ms (total 11600)

            expect(questSystem.isSpawnTableEmpty()).toBe(true);
        });
    });

    describe('Completion Detection', () => {
        it('should not complete while enemies alive', () => {
            questSystem.startQuest(1, 1);
            questSystem.update(11000); // Most spawned, but not all yet
            questSystem.reportEnemySpawned(5); // Report enemies alive
            questSystem.update(1100); // Complete all spawns

            expect(questSystem.getState()).toBe(QuestState.PLAYING);
        });

        it('should transition when spawn table empty and no enemies', () => {
            // Callback reports spawns so entries are consumed
            questSystem.setSpawnCallback(() => questSystem.reportEnemySpawned(1));
            questSystem.startQuest(1, 1);
            // Drain all spawn entries (each update triggers one batch then returns)
            questSystem.update(600); // 500ms batch
            questSystem.update(2000); // 2500ms batch
            questSystem.update(4000); // 6500ms batch
            questSystem.update(5000); // 11500ms batch

            // All spawned, check no more pending
            expect(questSystem.isSpawnTableEmpty()).toBe(true);

            // Simulate all enemies killed
            while (questSystem.getActiveEnemyCount() > 0) {
                questSystem.reportEnemyKilled();
            }
            // checkCompletion runs externally (deferred check in GamePlayingUpdate)
            questSystem.checkCompletion();

            expect(questSystem.getState()).toBe(QuestState.TRANSITIONING);
        });

        it('should complete after transition timer', () => {
            // Callback reports spawns so entries are consumed
            questSystem.setSpawnCallback(() => questSystem.reportEnemySpawned(1));
            questSystem.startQuest(1, 1);
            questSystem.update(600); // 500ms batch
            questSystem.update(2000); // 2500ms batch
            questSystem.update(4000); // 6500ms batch
            questSystem.update(5000); // 11500ms batch

            // Simulate all enemies killed + external completion check
            while (questSystem.getActiveEnemyCount() > 0) {
                questSystem.reportEnemyKilled();
            }
            questSystem.checkCompletion();

            expect(questSystem.getState()).toBe(QuestState.TRANSITIONING);

            questSystem.update(3000); // Past transition timer (2500ms)

            expect(questSystem.getState()).toBe(QuestState.COMPLETE);
        });
    });

    describe('Force Complete', () => {
        it('should force complete skipping timeline', () => {
            questSystem.startQuest(1, 1);
            questSystem.forceComplete();

            expect(questSystem.getState()).toBe(QuestState.COMPLETE);
        });

        it('should set spawn table to empty', () => {
            questSystem.startQuest(1, 1);
            questSystem.forceComplete();

            expect(questSystem.isSpawnTableEmpty()).toBe(true);
        });
    });

    describe('Enemy Tracking', () => {
        it('should track spawned enemies', () => {
            questSystem.startQuest(1, 1);
            questSystem.reportEnemySpawned(3);

            expect(questSystem.getActiveEnemyCount()).toBe(3);
        });

        it('should decrement on kill', () => {
            questSystem.startQuest(1, 1);
            questSystem.reportEnemySpawned(3);
            questSystem.reportEnemyKilled();

            expect(questSystem.getActiveEnemyCount()).toBe(2);
        });

        it('should not go below zero', () => {
            questSystem.startQuest(1, 1);
            questSystem.reportEnemyKilled(); // No enemies yet

            expect(questSystem.getActiveEnemyCount()).toBe(0);
        });

        it('should track total spawned and killed', () => {
            questSystem.startQuest(1, 1);
            questSystem.reportEnemySpawned(5);
            questSystem.reportEnemyKilled();
            questSystem.reportEnemyKilled();

            expect(questSystem.getTotalSpawned()).toBe(5);
            expect(questSystem.getTotalKilled()).toBe(2);
        });
    });

    describe('Unlock Progress', () => {
        it('should update unlock index on completion', () => {
            questSystem.startQuest(1, 3); // Third quest
            questSystem.forceComplete();

            // Quest 1-3 has ID 2, so unlock index should be 2
            expect(questSystem.getUnlockIndex()).toBe(2);
        });

        it('should not decrease unlock index', () => {
            questSystem.setUnlockIndex(5);
            questSystem.startQuest(1, 1); // First quest
            questSystem.forceComplete();

            // Should stay at 5, not decrease to 0
            expect(questSystem.getUnlockIndex()).toBe(5);
        });
    });

    describe('Reset', () => {
        it('should reset all state', () => {
            questSystem.startQuest(1, 1);
            questSystem.update(1000);
            questSystem.reportEnemySpawned(5);

            questSystem.reset();

            expect(questSystem.getState()).toBe(QuestState.INACTIVE);
            expect(questSystem.getCurrentQuest()).toBeNull();
            expect(questSystem.getTimelineMs()).toBe(0);
            expect(questSystem.getActiveEnemyCount()).toBe(0);
        });
    });

    describe('Pending Spawn Count', () => {
        it('should return total pending enemies', () => {
            questSystem.startQuest(1, 1);
            // Land Hostile has 1+2+3+4 = 10 total enemies
            expect(questSystem.getPendingSpawnCount()).toBe(10);
        });

        it('should decrease as spawns trigger', () => {
            // Callback must report spawns so entries are consumed
            questSystem.setSpawnCallback(() => questSystem.reportEnemySpawned(1));
            questSystem.startQuest(1, 1);
            questSystem.update(600); // First spawn (1 enemy)

            expect(questSystem.getPendingSpawnCount()).toBe(9);
        });
    });

    describe('isActive', () => {
        it('should return false when inactive', () => {
            expect(questSystem.isActive()).toBe(false);
        });

        it('should return true when playing', () => {
            questSystem.startQuest(1, 1);
            expect(questSystem.isActive()).toBe(true);
        });

        it('should return true when transitioning', () => {
            // Callback reports spawns so entries are consumed
            questSystem.setSpawnCallback(() => questSystem.reportEnemySpawned(1));
            questSystem.startQuest(1, 1);
            questSystem.update(600); // 500ms batch
            questSystem.update(2000); // 2500ms batch
            questSystem.update(4000); // 6500ms batch
            questSystem.update(5000); // 11500ms batch
            // Simulate all enemies killed + external completion check
            while (questSystem.getActiveEnemyCount() > 0) {
                questSystem.reportEnemyKilled();
            }
            questSystem.checkCompletion();
            expect(questSystem.getState()).toBe(QuestState.TRANSITIONING);
            expect(questSystem.isActive()).toBe(true);
        });

        it('should return false when complete', () => {
            questSystem.startQuest(1, 1);
            questSystem.forceComplete();
            expect(questSystem.isActive()).toBe(false);
        });
    });
});
