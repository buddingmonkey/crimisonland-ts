/**
 * PerkUnlockRegistry Unit Tests
 *
 * Tests the perk unlock system: entry table initialization, unlock mechanics,
 * level-based filtering, and save/load roundtrip.
 */

import { describe, it, expect, beforeEach } from 'vitest';
import { PerkUnlockRegistry, getPerkUnlockRegistry, resetPerkUnlockRegistry } from '../PerkUnlockRegistry';
import { PerkId } from '../PerkSystem';
import { PERK_ANTIPERK } from '../../data/quests/QuestTypes';

describe('PerkUnlockRegistry', () => {
    let registry: PerkUnlockRegistry;

    beforeEach(() => {
        registry = new PerkUnlockRegistry();
    });

    // ─── Initial State ────────────────────────────────────────────────────────

    describe('initial state', () => {
        it('all entry table entries start locked (PERK_ANTIPERK)', () => {
            const entries = registry.getEntries();
            for (const entry of entries) {
                expect(entry.perkId).toBe(PERK_ANTIPERK);
            }
        });

        it('has 25 entries (22 main + 3 extra gated)', () => {
            expect(registry.getEntries()).toHaveLength(25);
        });

        it('no perks are unlocked initially', () => {
            expect(registry.getUnlockedPerkIds()).toHaveLength(0);
        });

        it('always-available perks (0x01-0x1b) are available at any level', () => {
            // These perks are not gated — always available
            expect(registry.isPerkUnlocked(PerkId.BLOODY_MESS)).toBe(true);      // 0x01
            expect(registry.isPerkUnlocked(PerkId.SHARPSHOOTER)).toBe(true);     // 0x02
            expect(registry.isPerkUnlocked(PerkId.FASTLOADER)).toBe(true);       // 0x03
            expect(registry.isPerkUnlocked(PerkId.LONG_DISTANCE_RUNNER)).toBe(true); // 0x05
            expect(registry.isPerkUnlocked(PerkId.BONUS_MAGNET)).toBe(true);     // 0x1b
        });

        it('gated perks are NOT unlocked initially', () => {
            expect(registry.isPerkUnlocked(PerkId.URANIUM_FILLED_BULLETS)).toBe(false); // 0x1c
            expect(registry.isPerkUnlocked(PerkId.DOCTOR)).toBe(false);                 // 0x1d
            expect(registry.isPerkUnlocked(PerkId.HOT_TEMPERED)).toBe(false);           // 0x1f
            expect(registry.isPerkUnlocked(PerkId.PERK_MASTER)).toBe(false);            // 0x2b
        });
    });

    // ─── Unlock Mechanics ─────────────────────────────────────────────────────

    describe('unlockPerk', () => {
        it('unlocking a gated perk makes it available', () => {
            registry.unlockPerk(PerkId.URANIUM_FILLED_BULLETS); // 0x1c
            expect(registry.isPerkUnlocked(PerkId.URANIUM_FILLED_BULLETS)).toBe(true);
        });

        it('unlocking sets the entry table slot perkId', () => {
            registry.unlockPerk(PerkId.URANIUM_FILLED_BULLETS);
            const entries = registry.getEntries();
            // Entry 0 corresponds to Uranium Filled Bullets
            expect(entries[0].perkId).toBe(PerkId.URANIUM_FILLED_BULLETS);
        });

        it('unlocking PERK_ANTIPERK is a no-op', () => {
            registry.unlockPerk(PERK_ANTIPERK);
            expect(registry.getUnlockedPerkIds()).toHaveLength(0);
        });

        it('unlocking PerkId.ANTIPERK is a no-op', () => {
            registry.unlockPerk(PerkId.ANTIPERK);
            expect(registry.getUnlockedPerkIds()).toHaveLength(0);
        });

        it('unlocking multiple perks tracks all of them', () => {
            registry.unlockPerk(PerkId.URANIUM_FILLED_BULLETS); // 0x1c
            registry.unlockPerk(PerkId.DOCTOR);                 // 0x1d
            registry.unlockPerk(PerkId.BARREL_GREASER);         // 0x22
            expect(registry.getUnlockedPerkIds()).toHaveLength(3);
            expect(registry.isPerkUnlocked(PerkId.URANIUM_FILLED_BULLETS)).toBe(true);
            expect(registry.isPerkUnlocked(PerkId.DOCTOR)).toBe(true);
            expect(registry.isPerkUnlocked(PerkId.BARREL_GREASER)).toBe(true);
        });

        it('unlocking the same perk twice is idempotent', () => {
            registry.unlockPerk(PerkId.DOCTOR);
            registry.unlockPerk(PerkId.DOCTOR);
            expect(registry.getUnlockedPerkIds()).toHaveLength(1);
        });
    });

    // ─── Level-Based Filtering ────────────────────────────────────────────────

    describe('getAvailablePerks', () => {
        it('always-available perks are included at level 1', () => {
            const available = registry.getAvailablePerks(1);
            expect(available).toContain(PerkId.BLOODY_MESS);       // 0x01
            expect(available).toContain(PerkId.SHARPSHOOTER);      // 0x02
            expect(available).toContain(PerkId.BONUS_MAGNET);      // 0x1b
        });

        it('gated perks are NOT included even at high level if not unlocked', () => {
            const available = registry.getAvailablePerks(100);
            expect(available).not.toContain(PerkId.URANIUM_FILLED_BULLETS); // 0x1c, not unlocked
            expect(available).not.toContain(PerkId.PERK_MASTER);            // 0x2b, not unlocked
        });

        it('excludes ANTIPERK', () => {
            const available = registry.getAvailablePerks(1);
            expect(available).not.toContain(PerkId.ANTIPERK);
        });

        it('unlocked perk appears when level meets cost threshold', () => {
            registry.unlockPerk(PerkId.URANIUM_FILLED_BULLETS); // cost = 3
            // Level 3 meets threshold
            const atLevel3 = registry.getAvailablePerks(3);
            expect(atLevel3).toContain(PerkId.URANIUM_FILLED_BULLETS);
        });

        it('unlocked perk does NOT appear when level is below cost', () => {
            registry.unlockPerk(PerkId.URANIUM_FILLED_BULLETS); // cost = 3
            // Level 2 is below threshold
            const atLevel2 = registry.getAvailablePerks(2);
            expect(atLevel2).not.toContain(PerkId.URANIUM_FILLED_BULLETS);
        });

        it('high-cost perk requires high level', () => {
            registry.unlockPerk(PerkId.BANDAGE); // cost = 23
            expect(registry.getAvailablePerks(22)).not.toContain(PerkId.BANDAGE);
            expect(registry.getAvailablePerks(23)).toContain(PerkId.BANDAGE);
        });

        it('multiple unlocked perks filter by their individual costs', () => {
            registry.unlockPerk(PerkId.URANIUM_FILLED_BULLETS); // cost = 3
            registry.unlockPerk(PerkId.PERK_MASTER);            // cost = 21

            const atLevel5 = registry.getAvailablePerks(5);
            expect(atLevel5).toContain(PerkId.URANIUM_FILLED_BULLETS); // cost 3 <= 5
            expect(atLevel5).not.toContain(PerkId.PERK_MASTER);        // cost 21 > 5

            const atLevel25 = registry.getAvailablePerks(25);
            expect(atLevel25).toContain(PerkId.URANIUM_FILLED_BULLETS);
            expect(atLevel25).toContain(PerkId.PERK_MASTER);
        });
    });

    // ─── Save/Load Roundtrip ──────────────────────────────────────────────────

    describe('save/load roundtrip', () => {
        it('getUnlockedPerkIds returns unlocked IDs', () => {
            registry.unlockPerk(PerkId.DOCTOR);
            registry.unlockPerk(PerkId.BARREL_GREASER);
            const ids = registry.getUnlockedPerkIds();
            expect(ids).toContain(PerkId.DOCTOR);
            expect(ids).toContain(PerkId.BARREL_GREASER);
            expect(ids).toHaveLength(2);
        });

        it('loadUnlockedPerks restores state from saved IDs', () => {
            // Unlock some perks
            registry.unlockPerk(PerkId.URANIUM_FILLED_BULLETS);
            registry.unlockPerk(PerkId.NINJA);
            const savedIds = registry.getUnlockedPerkIds();

            // Create fresh registry and load
            const newRegistry = new PerkUnlockRegistry();
            expect(newRegistry.isPerkUnlocked(PerkId.URANIUM_FILLED_BULLETS)).toBe(false);

            newRegistry.loadUnlockedPerks(savedIds);
            expect(newRegistry.isPerkUnlocked(PerkId.URANIUM_FILLED_BULLETS)).toBe(true);
            expect(newRegistry.isPerkUnlocked(PerkId.NINJA)).toBe(true);
        });

        it('loadUnlockedPerks clears previous state', () => {
            registry.unlockPerk(PerkId.DOCTOR);
            registry.loadUnlockedPerks([PerkId.BARREL_GREASER]);

            expect(registry.isPerkUnlocked(PerkId.DOCTOR)).toBe(false);
            expect(registry.isPerkUnlocked(PerkId.BARREL_GREASER)).toBe(true);
        });

        it('roundtrip preserves getAvailablePerks behavior', () => {
            registry.unlockPerk(PerkId.HOT_TEMPERED);      // cost = 8
            registry.unlockPerk(PerkId.BONUS_ECONOMIST);    // cost = 4
            const ids = registry.getUnlockedPerkIds();

            const newRegistry = new PerkUnlockRegistry();
            newRegistry.loadUnlockedPerks(ids);

            const atLevel5 = newRegistry.getAvailablePerks(5);
            expect(atLevel5).toContain(PerkId.BONUS_ECONOMIST);     // cost 4 <= 5
            expect(atLevel5).not.toContain(PerkId.HOT_TEMPERED);    // cost 8 > 5
        });
    });

    // ─── Reset ────────────────────────────────────────────────────────────────

    describe('reset', () => {
        it('reset clears all unlocks', () => {
            registry.unlockPerk(PerkId.DOCTOR);
            registry.unlockPerk(PerkId.BARREL_GREASER);
            registry.reset();

            expect(registry.getUnlockedPerkIds()).toHaveLength(0);
            expect(registry.isPerkUnlocked(PerkId.DOCTOR)).toBe(false);

            // Entries should all be PERK_ANTIPERK again
            for (const entry of registry.getEntries()) {
                expect(entry.perkId).toBe(PERK_ANTIPERK);
            }
        });
    });

    // ─── Singleton ────────────────────────────────────────────────────────────

    describe('singleton', () => {
        beforeEach(() => {
            resetPerkUnlockRegistry();
        });

        it('getPerkUnlockRegistry returns same instance', () => {
            const a = getPerkUnlockRegistry();
            const b = getPerkUnlockRegistry();
            expect(a).toBe(b);
        });

        it('resetPerkUnlockRegistry creates new instance', () => {
            const a = getPerkUnlockRegistry();
            a.unlockPerk(PerkId.DOCTOR);
            resetPerkUnlockRegistry();
            const b = getPerkUnlockRegistry();
            expect(b.isPerkUnlocked(PerkId.DOCTOR)).toBe(false);
        });
    });
});
