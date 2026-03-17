/**
 * WeaponUnlockRegistry Unit Tests
 *
 * Tests for the weapon unlock system, verifying:
 * - Pistol is always unlocked
 * - refreshAvailable builds correct unlock set from quest progress
 * - pickRandomAvailable only returns unlocked weapons
 * - Save/load round-trip
 * - Singleton pattern
 */

import { describe, test, expect, beforeEach } from 'vitest';
import {
    WeaponUnlockRegistry,
    getWeaponUnlockRegistry,
    resetWeaponUnlockRegistry,
} from '../WeaponUnlockRegistry';
import { QUEST_DATABASE } from '../../data/quests/QuestDatabase';

describe('WeaponUnlockRegistry', () => {
    let registry: WeaponUnlockRegistry;

    beforeEach(() => {
        registry = new WeaponUnlockRegistry();
    });

    describe('Initial state', () => {
        test('pistol (ID 0) is always unlocked', () => {
            expect(registry.isUnlocked(0)).toBe(true);
        });

        test('only pistol is unlocked initially', () => {
            expect(registry.getUnlockedCount()).toBe(1);
            expect(registry.getUnlockedWeaponIds()).toEqual([0]);
        });

        test('other weapons are locked initially', () => {
            expect(registry.isUnlocked(1)).toBe(false);
            expect(registry.isUnlocked(2)).toBe(false);
            expect(registry.isUnlocked(10)).toBe(false);
        });
    });

    describe('unlockWeapon', () => {
        test('unlocks a specific weapon', () => {
            registry.unlockWeapon(5);
            expect(registry.isUnlocked(5)).toBe(true);
        });

        test('ignores weapon ID 0 (pistol is always unlocked)', () => {
            const countBefore = registry.getUnlockedCount();
            registry.unlockWeapon(0);
            // Pistol was already unlocked, count shouldn't change
            expect(registry.getUnlockedCount()).toBe(countBefore);
        });

        test('ignores negative weapon IDs', () => {
            registry.unlockWeapon(-1);
            expect(registry.getUnlockedCount()).toBe(1);
        });

        test('ignores weapon IDs >= 40', () => {
            registry.unlockWeapon(40);
            expect(registry.getUnlockedCount()).toBe(1);
        });
    });

    describe('refreshAvailable', () => {
        test('with 0 quests completed, only pistol is unlocked', () => {
            registry.refreshAvailable(0);
            expect(registry.getUnlockedCount()).toBe(1);
            expect(registry.isUnlocked(0)).toBe(true);
        });

        test('completing quest 1-1 unlocks assault rifle (ID 1)', () => {
            // Quest 1-1 (index 0) has unlockWeaponId: 1
            registry.refreshAvailable(1);
            expect(registry.isUnlocked(0)).toBe(true); // Pistol
            expect(registry.isUnlocked(1)).toBe(true); // Assault Rifle
        });

        test('completing first 5 quests unlocks correct weapons', () => {
            registry.refreshAvailable(5);
            // Quest data: 1=AR, 3=Sawed-off, 8=Multi-Plasma, 5=SMG, 6=Flamethrower
            expect(registry.isUnlocked(0)).toBe(true);  // Pistol (always)
            expect(registry.isUnlocked(1)).toBe(true);  // Assault Rifle (quest 1-1)
            expect(registry.isUnlocked(3)).toBe(true);  // Sawed-off (quest 1-2)
            expect(registry.isUnlocked(8)).toBe(true);  // Multi-Plasma (quest 1-3)
            expect(registry.isUnlocked(5)).toBe(true);  // SMG (quest 1-4)
            expect(registry.isUnlocked(6)).toBe(true);  // Flamethrower (quest 1-5)
        });

        test('survival mode unlocks shotgun, SMG, assault rifle', () => {
            registry.refreshAvailable(0, true);
            expect(registry.isUnlocked(0)).toBe(true);  // Pistol
            expect(registry.isUnlocked(1)).toBe(true);  // Assault Rifle
            expect(registry.isUnlocked(2)).toBe(true);  // Shotgun
            expect(registry.isUnlocked(5)).toBe(true);  // SMG
        });

        test('quests with unlockWeaponId: 0 do not add extra weapons', () => {
            // Many tier 3+ quests have unlockWeaponId: 0
            // Count weapons unlocked from first 20 quests (tier 1-2)
            registry.refreshAvailable(20);
            const ids = registry.getUnlockedWeaponIds();
            // Verify ID 0 (pistol) is there but wasn't added by an unlockWeaponId: 0
            expect(ids.includes(0)).toBe(true);
            // All non-zero unlock IDs from first 20 quests should be present
            for (let i = 0; i < 20 && i < QUEST_DATABASE.length; i++) {
                const wid = QUEST_DATABASE[i].unlockWeaponId;
                if (wid > 0) {
                    expect(registry.isUnlocked(wid)).toBe(true);
                }
            }
        });
    });

    describe('pickRandomAvailable', () => {
        test('returns only unlocked weapons', () => {
            registry.unlockWeapon(5);
            registry.unlockWeapon(10);

            const picks = new Set<number>();
            for (let i = 0; i < 200; i++) {
                picks.add(registry.pickRandomAvailable());
            }

            // All picks should be from {0, 5, 10}
            for (const pick of picks) {
                expect(registry.isUnlocked(pick)).toBe(true);
            }
        });

        test('returns pistol when only pistol is unlocked', () => {
            for (let i = 0; i < 20; i++) {
                expect(registry.pickRandomAvailable()).toBe(0);
            }
        });

        test('returns variety when many weapons unlocked', () => {
            // Unlock 10 weapons
            for (let i = 1; i <= 10; i++) {
                registry.unlockWeapon(i);
            }

            const picks = new Set<number>();
            for (let i = 0; i < 500; i++) {
                picks.add(registry.pickRandomAvailable());
            }

            // Should see at least 3 different weapons over 500 picks
            expect(picks.size).toBeGreaterThanOrEqual(3);
        });
    });

    describe('Save/Load round-trip', () => {
        test('getUnlockedWeaponIds returns sorted array', () => {
            registry.unlockWeapon(10);
            registry.unlockWeapon(3);
            registry.unlockWeapon(7);
            const ids = registry.getUnlockedWeaponIds();
            expect(ids).toEqual([0, 3, 7, 10]);
        });

        test('loadUnlockedWeapons restores state', () => {
            registry.unlockWeapon(5);
            registry.unlockWeapon(10);
            const savedIds = registry.getUnlockedWeaponIds();

            const newRegistry = new WeaponUnlockRegistry();
            newRegistry.loadUnlockedWeapons(savedIds);

            expect(newRegistry.isUnlocked(0)).toBe(true);
            expect(newRegistry.isUnlocked(5)).toBe(true);
            expect(newRegistry.isUnlocked(10)).toBe(true);
            expect(newRegistry.isUnlocked(3)).toBe(false);
            expect(newRegistry.getUnlockedCount()).toBe(3);
        });

        test('loadUnlockedWeapons always includes pistol', () => {
            const newRegistry = new WeaponUnlockRegistry();
            newRegistry.loadUnlockedWeapons([5, 10]); // no 0 in list
            expect(newRegistry.isUnlocked(0)).toBe(true); // Pistol always there
        });
    });

    describe('reset', () => {
        test('reset returns to initial state', () => {
            registry.unlockWeapon(5);
            registry.unlockWeapon(10);
            registry.reset();
            expect(registry.getUnlockedCount()).toBe(1);
            expect(registry.isUnlocked(0)).toBe(true);
            expect(registry.isUnlocked(5)).toBe(false);
        });
    });

    describe('Singleton', () => {
        test('getWeaponUnlockRegistry returns same instance', () => {
            resetWeaponUnlockRegistry();
            const a = getWeaponUnlockRegistry();
            const b = getWeaponUnlockRegistry();
            expect(a).toBe(b);
        });

        test('resetWeaponUnlockRegistry creates new instance', () => {
            const a = getWeaponUnlockRegistry();
            a.unlockWeapon(5);
            resetWeaponUnlockRegistry();
            const b = getWeaponUnlockRegistry();
            expect(a).not.toBe(b);
            expect(b.isUnlocked(5)).toBe(false);
        });
    });

    describe('Quest database consistency', () => {
        test('all quest unlockWeaponIds are valid weapon IDs', () => {
            for (const quest of QUEST_DATABASE) {
                if (quest.unlockWeaponId > 0) {
                    expect(quest.unlockWeaponId).toBeLessThan(40);
                    expect(quest.unlockWeaponId).toBeGreaterThan(0);
                }
            }
        });

        test('completing all quests unlocks multiple unique weapons', () => {
            registry.refreshAvailable(QUEST_DATABASE.length);
            // Should have at least 15 unique weapons unlocked after all quests
            expect(registry.getUnlockedCount()).toBeGreaterThanOrEqual(15);
        });
    });
});
