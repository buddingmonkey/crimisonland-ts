/**
 * SaveSystem.test.ts - Unit tests for save/load system
 */

import { describe, it, expect, beforeEach } from 'vitest';
import {
    GameStatusData,
    SAVE_VERSION,
    STORAGE_KEYS,
    MAX_HIGH_SCORES,
    createDefaultGameStatus,
    createHighScoreRecord,
    computeChecksum,
    validateChecksum,
} from '../SaveData';
import { MemoryStorageProvider } from '../StorageProvider';
import { SaveSystem } from '../../systems/SaveSystem';

describe('SaveData', () => {
    describe('createDefaultGameStatus', () => {
        it('should create status with correct version', () => {
            const status = createDefaultGameStatus();
            expect(status.version).toBe(SAVE_VERSION);
        });

        it('should initialize all arrays with zeros', () => {
            const status = createDefaultGameStatus();
            expect(status.weaponUsageCounts).toHaveLength(40);
            expect(status.weaponUsageCounts.every((v) => v === 0)).toBe(true);
            expect(status.questPlayCounts).toHaveLength(60);
            expect(status.questPlayCounts.every((v) => v === 0)).toBe(true);
        });

        it('should initialize all counters to zero', () => {
            const status = createDefaultGameStatus();
            expect(status.questUnlockIndex).toBe(0);
            expect(status.questUnlockIndexFull).toBe(0);
            expect(status.modePlaySurvival).toBe(0);
            expect(status.modePlayRush).toBe(0);
            expect(status.modePlayTypo).toBe(0);
            expect(status.modePlayOther).toBe(0);
        });
    });

    describe('createHighScoreRecord', () => {
        it('should create record with correct values', () => {
            const record = createHighScoreRecord('Player1', 5000, 120000, 1);
            expect(record.playerName).toBe('Player1');
            expect(record.scoreXp).toBe(5000);
            expect(record.survivalElapsedMs).toBe(120000);
            expect(record.gameModeId).toBe(1);
        });

        it('should set current date', () => {
            const now = new Date();
            const record = createHighScoreRecord('Player', 100, 1000, 1);
            expect(record.date.year).toBe(now.getFullYear());
            expect(record.date.month).toBe(now.getMonth() + 1);
            expect(record.date.day).toBe(now.getDate());
        });
    });

    describe('checksum', () => {
        it('should compute consistent checksum', () => {
            const status = createDefaultGameStatus();
            const checksum1 = computeChecksum(status);
            const checksum2 = computeChecksum(status);
            expect(checksum1).toBe(checksum2);
        });

        it('should change with data changes', () => {
            const status1 = createDefaultGameStatus();
            const status2 = { ...createDefaultGameStatus(), questUnlockIndex: 5 };

            const checksum1 = computeChecksum(status1);
            const checksum2 = computeChecksum(status2);

            expect(checksum1).not.toBe(checksum2);
        });

        it('should validate correct checksum', () => {
            const status = createDefaultGameStatus();
            status.checksum = computeChecksum(status);
            expect(validateChecksum(status)).toBe(true);
        });

        it('should reject incorrect checksum', () => {
            const status = createDefaultGameStatus();
            status.checksum = 12345; // Wrong checksum
            expect(validateChecksum(status)).toBe(false);
        });
    });
});

describe('StorageProvider', () => {
    let storage: MemoryStorageProvider;

    beforeEach(() => {
        storage = new MemoryStorageProvider();
    });

    it('should return null for missing keys', () => {
        expect(storage.get('missing')).toBeNull();
    });

    it('should store and retrieve values', () => {
        storage.set('test', { foo: 'bar' });
        expect(storage.get('test')).toEqual({ foo: 'bar' });
    });

    it('should handle arrays', () => {
        const arr = [1, 2, 3];
        storage.set('array', arr);
        expect(storage.get<number[]>('array')).toEqual([1, 2, 3]);
    });

    it('should remove values', () => {
        storage.set('key', 'value');
        storage.remove('key');
        expect(storage.get('key')).toBeNull();
    });

    it('should clear all values', () => {
        storage.set('key1', 'value1');
        storage.set('key2', 'value2');
        storage.clear();
        expect(storage.get('key1')).toBeNull();
        expect(storage.get('key2')).toBeNull();
    });
});

describe('SaveSystem', () => {
    let storage: MemoryStorageProvider;
    let saveSystem: SaveSystem;

    beforeEach(() => {
        storage = new MemoryStorageProvider();
        saveSystem = new SaveSystem(storage);
    });

    describe('saveGameStatus', () => {
        it('should save status successfully', () => {
            const status = createDefaultGameStatus();
            const result = saveSystem.saveGameStatus(status);
            expect(result).toBe(true);
        });

        it('should add checksum to saved data', () => {
            const status = createDefaultGameStatus();
            saveSystem.saveGameStatus(status);

            const saved = storage.get<GameStatusData>(STORAGE_KEYS.GAME_STATUS);
            expect(saved).not.toBeNull();
            expect(saved!.checksum).toBeDefined();
            expect(typeof saved!.checksum).toBe('number');
        });
    });

    describe('loadGameStatus', () => {
        it('should return default status when no save exists', () => {
            const status = saveSystem.loadGameStatus();
            expect(status.questUnlockIndex).toBe(0);
            expect(status.version).toBe(SAVE_VERSION);
        });

        it('should load saved status', () => {
            const original = createDefaultGameStatus();
            original.questUnlockIndex = 15;
            original.modePlaySurvival = 5;
            saveSystem.saveGameStatus(original);

            const loaded = saveSystem.loadGameStatus();
            expect(loaded.questUnlockIndex).toBe(15);
            expect(loaded.modePlaySurvival).toBe(5);
        });

        it('should reset on checksum mismatch', () => {
            // Save valid data
            const original = createDefaultGameStatus();
            original.questUnlockIndex = 20;
            saveSystem.saveGameStatus(original);

            // Corrupt the checksum
            const saved = storage.get<GameStatusData>(STORAGE_KEYS.GAME_STATUS)!;
            saved.checksum = 99999;
            storage.set(STORAGE_KEYS.GAME_STATUS, saved);

            // Load should reset to default
            const loaded = saveSystem.loadGameStatus();
            expect(loaded.questUnlockIndex).toBe(0);
        });
    });

    describe('setQuestUnlockIndex', () => {
        it('should update quest index', () => {
            saveSystem.setQuestUnlockIndex(10);
            expect(saveSystem.getQuestUnlockIndex()).toBe(10);
        });

        it('should not decrease quest index', () => {
            saveSystem.setQuestUnlockIndex(10);
            saveSystem.setQuestUnlockIndex(5);
            expect(saveSystem.getQuestUnlockIndex()).toBe(10);
        });
    });

    describe('incrementModePlayCount', () => {
        it('should increment survival count', () => {
            saveSystem.incrementModePlayCount(1);
            const status = saveSystem.loadGameStatus();
            expect(status.modePlaySurvival).toBe(1);
        });

        it('should increment rush count', () => {
            saveSystem.incrementModePlayCount(2);
            const status = saveSystem.loadGameStatus();
            expect(status.modePlayRush).toBe(1);
        });
    });

    describe('high scores', () => {
        it('should save and load high scores', () => {
            const record = createHighScoreRecord('Player1', 5000, 120000, 1);
            saveSystem.saveHighScore(record);

            const loaded = saveSystem.loadHighScores();
            expect(loaded).toHaveLength(1);
            expect(loaded[0].playerName).toBe('Player1');
        });

        it('should sort by score for non-Rush modes', () => {
            saveSystem.saveHighScore(createHighScoreRecord('Low', 1000, 0, 1));
            saveSystem.saveHighScore(createHighScoreRecord('High', 5000, 0, 1));
            saveSystem.saveHighScore(createHighScoreRecord('Mid', 3000, 0, 1));

            const loaded = saveSystem.loadHighScores();
            expect(loaded[0].playerName).toBe('High');
            expect(loaded[1].playerName).toBe('Mid');
            expect(loaded[2].playerName).toBe('Low');
        });

        it('should sort by survival time for Rush mode', () => {
            saveSystem.saveHighScore(createHighScoreRecord('Short', 0, 60000, 2));
            saveSystem.saveHighScore(createHighScoreRecord('Long', 0, 180000, 2));
            saveSystem.saveHighScore(createHighScoreRecord('Medium', 0, 120000, 2));

            const loaded = saveSystem.loadHighScores(2);
            expect(loaded[0].playerName).toBe('Long');
            expect(loaded[1].playerName).toBe('Medium');
            expect(loaded[2].playerName).toBe('Short');
        });

        it('should limit to MAX_HIGH_SCORES', () => {
            // Add more than max
            for (let i = 0; i < MAX_HIGH_SCORES + 10; i++) {
                saveSystem.saveHighScore(createHighScoreRecord(`Player${i}`, i * 100, 0, 1));
            }

            const loaded = saveSystem.loadHighScores();
            expect(loaded.length).toBeLessThanOrEqual(MAX_HIGH_SCORES);
        });

        it('should filter by game mode', () => {
            saveSystem.saveHighScore(createHighScoreRecord('Survival', 1000, 0, 1));
            saveSystem.saveHighScore(createHighScoreRecord('Rush', 0, 60000, 2));

            const survivalRecords = saveSystem.loadHighScores(1);
            expect(survivalRecords).toHaveLength(1);
            expect(survivalRecords[0].playerName).toBe('Survival');
        });
    });

    describe('resetProgress', () => {
        it('should clear all saved data', () => {
            const status = createDefaultGameStatus();
            status.questUnlockIndex = 10;
            saveSystem.saveGameStatus(status);
            saveSystem.saveHighScore(createHighScoreRecord('Player', 5000, 0, 1));

            saveSystem.resetProgress();

            expect(saveSystem.getQuestUnlockIndex()).toBe(0);
            expect(saveSystem.loadHighScores()).toHaveLength(0);
        });
    });
});
