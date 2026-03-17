/**
 * Perk Unlock System E2E Tests
 *
 * End-to-end tests verifying the full perk unlock flow:
 * 1. Quest completion → perk unlock via PerkUnlockRegistry
 * 2. Perk selection filtering by unlock status + player level
 * 3. Save/load roundtrip preserves unlock state across sessions
 * 4. Quest database → registry consistency
 */

import { describe, it, expect, beforeEach, vi } from 'vitest';
import { PerkUnlockRegistry, getPerkUnlockRegistry, resetPerkUnlockRegistry } from '../PerkUnlockRegistry';
import { PerkSystem, PerkId, getSelectablePerkIds } from '../PerkSystem';
import { QUEST_DATABASE } from '../../data/quests/QuestDatabase';
import { PERK_ANTIPERK } from '../../data/quests/QuestTypes';

// Mock the console to prevent log spam
vi.mock('../../console/Console', () => ({
    gameConsole: {
        log: vi.fn(),
        print: vi.fn(),
    },
}));

// ─── Helpers ──────────────────────────────────────────────────────────────────

/** Get all quests that unlock a perk (non-ANTIPERK unlockPerkId) */
function getQuestsWithPerkUnlocks() {
    return QUEST_DATABASE.filter(
        (q) => q.unlockPerkId !== PERK_ANTIPERK && q.unlockPerkId !== PerkId.ANTIPERK,
    );
}

/** Get unique perk IDs unlocked by quests */
function getUniqueQuestPerkIds(): number[] {
    return [...new Set(getQuestsWithPerkUnlocks().map((q) => q.unlockPerkId))];
}

// =============================================================================
// SECTION 1: Quest Database ↔ PerkUnlockRegistry Consistency
// =============================================================================

describe('Quest Database ↔ PerkUnlockRegistry consistency', () => {
    let registry: PerkUnlockRegistry;

    beforeEach(() => {
        registry = new PerkUnlockRegistry();
    });

    it('every quest unlockPerkId is either ANTIPERK or a valid gated perk', () => {
        for (const quest of QUEST_DATABASE) {
            if (quest.unlockPerkId === PERK_ANTIPERK || quest.unlockPerkId === PerkId.ANTIPERK) {
                continue;
            }
            // Unlocking should succeed (no-op for unknown IDs = bad)
            registry.unlockPerk(quest.unlockPerkId);
            expect(registry.isPerkUnlocked(quest.unlockPerkId)).toBe(true);
        }
    });

    it('all unique quest-unlocked perks can be unlocked via registry', () => {
        const perkIds = getUniqueQuestPerkIds();
        expect(perkIds.length).toBeGreaterThan(0);

        for (const id of perkIds) {
            registry.unlockPerk(id);
        }

        expect(registry.getUnlockedPerkIds().length).toBe(perkIds.length);
    });

    it('quests that have PERK_ANTIPERK do NOT unlock anything', () => {
        const noUnlockQuests = QUEST_DATABASE.filter(
            (q) => q.unlockPerkId === PERK_ANTIPERK || q.unlockPerkId === PerkId.ANTIPERK,
        );
        expect(noUnlockQuests.length).toBeGreaterThan(0); // Verify some quests don't unlock perks

        for (const quest of noUnlockQuests) {
            registry.unlockPerk(quest.unlockPerkId); // Should be a no-op
        }
        expect(registry.getUnlockedPerkIds()).toHaveLength(0);
    });
});

// =============================================================================
// SECTION 2: Full Quest Completion → Perk Unlock → Selection Flow
// =============================================================================

describe('Quest completion → perk unlock → selection filtering E2E', () => {
    let registry: PerkUnlockRegistry;
    let perkSystem: PerkSystem;

    beforeEach(() => {
        registry = new PerkUnlockRegistry();
        perkSystem = new PerkSystem();
    });

    it('completing quest 1-2 unlocks Uranium Filled Bullets and makes it available at level 3+', () => {
        const quest = QUEST_DATABASE.find((q) => q.tier === 1 && q.index === 2)!;
        expect(quest.unlockPerkId).toBe(PerkId.URANIUM_FILLED_BULLETS);

        // Before unlock: not available
        expect(registry.getAvailablePerks(10)).not.toContain(PerkId.URANIUM_FILLED_BULLETS);

        // Simulate quest completion
        registry.unlockPerk(quest.unlockPerkId);

        // After unlock: available at level 3 (cost = 3)
        expect(registry.getAvailablePerks(3)).toContain(PerkId.URANIUM_FILLED_BULLETS);
        // But not at level 2
        expect(registry.getAvailablePerks(2)).not.toContain(PerkId.URANIUM_FILLED_BULLETS);
    });

    it('completing multiple quests progressively expands available perks', () => {
        const tier1Quests = QUEST_DATABASE.filter(
            (q) => q.tier === 1 && q.unlockPerkId !== PERK_ANTIPERK && q.unlockPerkId !== PerkId.ANTIPERK,
        );

        let unlockedCount = 0;
        const baseAvailable = registry.getAvailablePerks(1).length;

        for (const quest of tier1Quests) {
            registry.unlockPerk(quest.unlockPerkId);
            unlockedCount++;
        }

        // At high level, all tier-1 unlocked perks should be available
        const afterAvailable = registry.getAvailablePerks(30);
        expect(afterAvailable.length).toBeGreaterThan(baseAvailable);
    });

    it('perk selection pool only contains unlocked perks + always-available perks', () => {
        // Initially only always-available perks
        const initialPool = registry.getAvailablePerks(30);

        // None of the gated perks should be in the initial pool
        const gatedPerks = getUniqueQuestPerkIds();
        for (const gatedId of gatedPerks) {
            expect(initialPool).not.toContain(gatedId);
        }

        // Unlock one perk
        registry.unlockPerk(PerkId.DOCTOR); // cost = 5
        const afterPool = registry.getAvailablePerks(30);
        expect(afterPool).toContain(PerkId.DOCTOR);
        // Other gated perks still excluded
        expect(afterPool).not.toContain(PerkId.PERK_MASTER);
    });

    it('perks already owned by player are excluded from selection pool via PerkSystem', () => {
        registry.unlockPerk(PerkId.DOCTOR);
        registry.unlockPerk(PerkId.BARREL_GREASER);

        const available = registry.getAvailablePerks(30);
        expect(available).toContain(PerkId.DOCTOR);
        expect(available).toContain(PerkId.BARREL_GREASER);

        // Simulate player owning Doctor
        perkSystem.addPerk(PerkId.DOCTOR);

        // Filter like PerkSelectionScreen does
        const filtered = available.filter((p) => !perkSystem.hasPerk(p));
        expect(filtered).not.toContain(PerkId.DOCTOR);
        expect(filtered).toContain(PerkId.BARREL_GREASER);
    });
});

// =============================================================================
// SECTION 3: Save/Load Roundtrip E2E
// =============================================================================

describe('Save/load roundtrip E2E', () => {
    it('simulates full session: unlock perks → save → new session → load → verify availability', () => {
        // Session 1: complete quests and unlock perks
        const session1Registry = new PerkUnlockRegistry();
        const questsToComplete = QUEST_DATABASE.filter(
            (q) => q.tier <= 2 && q.unlockPerkId !== PERK_ANTIPERK && q.unlockPerkId !== PerkId.ANTIPERK,
        );
        for (const quest of questsToComplete) {
            session1Registry.unlockPerk(quest.unlockPerkId);
        }

        // "Save" — serialize to array (as SaveSystem would)
        const savedIds = session1Registry.getUnlockedPerkIds();
        expect(savedIds.length).toBeGreaterThan(0);

        // Session 2: fresh registry, load from saved data
        const session2Registry = new PerkUnlockRegistry();
        session2Registry.loadUnlockedPerks(savedIds);

        // All perks from session 1 should be available
        for (const id of savedIds) {
            expect(session2Registry.isPerkUnlocked(id)).toBe(true);
        }

        // Available perks at high level should match between sessions
        const session1Perks = session1Registry.getAvailablePerks(30).sort();
        const session2Perks = session2Registry.getAvailablePerks(30).sort();
        expect(session2Perks).toEqual(session1Perks);
    });

    it('load with empty array resets all unlocks', () => {
        const registry = new PerkUnlockRegistry();
        registry.unlockPerk(PerkId.DOCTOR);
        registry.unlockPerk(PerkId.NINJA);

        registry.loadUnlockedPerks([]);
        expect(registry.getUnlockedPerkIds()).toHaveLength(0);
        expect(registry.isPerkUnlocked(PerkId.DOCTOR)).toBe(false);
    });
});

// =============================================================================
// SECTION 4: Level Progression E2E — perks gate as player levels up
// =============================================================================

describe('Level progression gating E2E', () => {
    let registry: PerkUnlockRegistry;

    beforeEach(() => {
        registry = new PerkUnlockRegistry();
        // Unlock ALL quest perks (simulate completing all quests)
        for (const quest of QUEST_DATABASE) {
            if (quest.unlockPerkId !== PERK_ANTIPERK && quest.unlockPerkId !== PerkId.ANTIPERK) {
                registry.unlockPerk(quest.unlockPerkId);
            }
        }
    });

    it('at level 1, only always-available perks are offered', () => {
        const available = registry.getAvailablePerks(1);
        // All should be always-available (not gated)
        const gatedPerks = getUniqueQuestPerkIds();
        for (const perkId of available) {
            expect(gatedPerks).not.toContain(perkId);
        }
    });

    it('at level 3, first gated perk (Uranium Bullets, cost=3) becomes available', () => {
        const available = registry.getAvailablePerks(3);
        expect(available).toContain(PerkId.URANIUM_FILLED_BULLETS); // cost = 3
    });

    it('at level 10, multiple gated perks are available', () => {
        const available = registry.getAvailablePerks(10);
        expect(available).toContain(PerkId.URANIUM_FILLED_BULLETS); // cost = 3
        expect(available).toContain(PerkId.BONUS_ECONOMIST);        // cost = 4
        expect(available).toContain(PerkId.DOCTOR);                 // cost = 5
        expect(available).toContain(PerkId.MONSTER_VISION);         // cost = 6
        expect(available).toContain(PerkId.BARREL_GREASER);         // cost = 7
        expect(available).toContain(PerkId.HOT_TEMPERED);           // cost = 8
        expect(available).toContain(PerkId.PYROMANIAC);             // cost = 9
        expect(available).toContain(PerkId.TOXIC_AVENGER);          // cost = 10

        // These should NOT yet be available (cost > 10)
        expect(available).not.toContain(PerkId.PERK_MASTER);        // cost = 21
        expect(available).not.toContain(PerkId.BANDAGE);            // cost = 23
    });

    it('at level 30, all unlocked perks are available', () => {
        const available = registry.getAvailablePerks(30);
        const gatedPerks = getUniqueQuestPerkIds();
        for (const perkId of gatedPerks) {
            expect(available).toContain(perkId);
        }
    });
});

// =============================================================================
// SECTION 5: Singleton Registry E2E (global state consistency)
// =============================================================================

describe('Singleton PerkUnlockRegistry E2E', () => {
    beforeEach(() => {
        resetPerkUnlockRegistry();
    });

    it('global registry maintains state across multiple access points', () => {
        // Simulate quest completion system accessing registry
        const fromQuestSystem = getPerkUnlockRegistry();
        fromQuestSystem.unlockPerk(PerkId.DOCTOR);

        // Simulate perk selection screen accessing registry
        const fromPerkScreen = getPerkUnlockRegistry();
        expect(fromPerkScreen.isPerkUnlocked(PerkId.DOCTOR)).toBe(true);
        expect(fromPerkScreen.getAvailablePerks(10)).toContain(PerkId.DOCTOR);
    });

    it('resetPerkUnlockRegistry simulates fresh game state', () => {
        getPerkUnlockRegistry().unlockPerk(PerkId.DOCTOR);
        expect(getPerkUnlockRegistry().isPerkUnlocked(PerkId.DOCTOR)).toBe(true);

        resetPerkUnlockRegistry();
        expect(getPerkUnlockRegistry().isPerkUnlocked(PerkId.DOCTOR)).toBe(false);
    });
});

// =============================================================================
// SECTION 6: Always-available perks never gated
// =============================================================================

describe('Always-available perks are never gated', () => {
    it('all perks from getSelectablePerkIds() that are NOT quest-unlocked are always available', () => {
        const registry = new PerkUnlockRegistry();
        const allSelectable = getSelectablePerkIds();
        const questPerks = new Set(getUniqueQuestPerkIds());

        const alwaysAvailable = allSelectable.filter((p) => !questPerks.has(p));
        const available = registry.getAvailablePerks(1); // Level 1, no unlocks

        for (const perkId of alwaysAvailable) {
            expect(available).toContain(perkId);
        }
    });
});
