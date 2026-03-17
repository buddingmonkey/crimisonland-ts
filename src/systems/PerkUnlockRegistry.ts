/**
 * PerkUnlockRegistry - Manages which perks are unlocked via quest completion.
 *
 * Port of C code's perk entry table from quest.c lines 5931-6030.
 *
 * In the C code, each perk entry has:
 *   - type_id: starts as perk_id_antiperk (locked), replaced with actual PerkId on unlock
 *   - cost: survival level threshold required to be offered the perk
 *   - prereq: always 0 (unused)
 *
 * Perks 0x01–0x1b are "always available" — they don't appear in the entry table
 * and are offered regardless of quest progress. Only perks 0x1c–0x34 (and some
 * repeats) are gated behind quest completion.
 */

import { PerkId } from './PerkSystem';
import { PERK_ANTIPERK } from '../data/quests/QuestTypes';

/**
 * A single perk entry in the unlock table.
 * Mirrors C's perk_entry_t structure.
 */
export interface PerkEntry {
    /** PerkId when unlocked, or PERK_ANTIPERK (locked). */
    perkId: number;
    /** Survival level threshold to be offered this perk. */
    cost: number;
    /** Prerequisite (always 0 in C data). */
    prereq: number;
}

/**
 * Cost values from C code (quest.c lines 5931-6030).
 * These are the survival level thresholds for each perk entry slot.
 * Order matches the C initialization order.
 */
const PERK_ENTRY_COSTS: number[] = [
    3,   // entry 0
    8,   // entry 1
    5,   // entry 2
    6,   // entry 3
    12,  // entry 4
    9,   // entry 5
    21,  // entry 6
    7,   // entry 7
    4,   // entry 8
    11,  // entry 9
    10,  // entry 10
    13,  // entry 11
    15,  // entry 12
    18,  // entry 13
    20,  // entry 14
    19,  // entry 15
    14,  // entry 16
    17,  // entry 17
    22,  // entry 18
    23,  // entry 19
    6,   // entry 20 - THICK_SKINNED
    10,  // entry 21 - VEINS_OF_POISON
];

/**
 * Perk IDs that correspond to each entry slot when unlocked.
 * Maps entry index → PerkId value.
 *
 * Derived from QuestDatabase.ts unlockPerkId values.
 * Entry order matches the C code's perk entry table initialization.
 */
const ENTRY_SLOT_PERK_IDS: number[] = [
    PerkId.URANIUM_FILLED_BULLETS,  // 0x1c - entry 0, cost 3
    PerkId.HOT_TEMPERED,            // 0x1f - entry 1, cost 8
    PerkId.DOCTOR,                  // 0x1d - entry 2, cost 5
    PerkId.MONSTER_VISION,          // 0x1e - entry 3, cost 6
    PerkId.AMMUNITION_WITHIN,       // 0x23 - entry 4, cost 12
    PerkId.PYROMANIAC,              // 0x27 - entry 5, cost 9
    PerkId.PERK_MASTER,             // 0x2b - entry 6, cost 21
    PerkId.BARREL_GREASER,          // 0x22 - entry 7, cost 7
    PerkId.BONUS_ECONOMIST,         // 0x20 - entry 8, cost 4
    PerkId.REGENERATION,            // 0x26 - entry 9, cost 11
    PerkId.TOXIC_AVENGER,           // 0x25 - entry 10, cost 10
    PerkId.NINJA,                   // 0x28 - entry 11, cost 13
    PerkId.JINXED,                  // 0x2a - entry 12, cost 15
    PerkId.GREATER_REGENERATION,    // 0x2d - entry 13, cost 18
    PerkId.BREATHING_ROOM,          // 0x2e - entry 14, cost 20
    PerkId.DEATH_CLOCK,             // 0x2f - entry 15, cost 19
    PerkId.HIGHLANDER,              // 0x29 - entry 16, cost 14
    PerkId.REFLEX_BOOSTED,          // 0x2c - entry 17, cost 17
    PerkId.MY_FAVOURITE_WEAPON,     // 0x30 - entry 18, cost 22
    PerkId.BANDAGE,                 // 0x31 - entry 19, cost 23
    PerkId.THICK_SKINNED,           // 0x21 - entry 20, cost 6
    PerkId.VEINS_OF_POISON,         // 0x24 - entry 21, cost 10
];

/**
 * Set of perk IDs that require quest unlock.
 * Built from the entry table — any perkId in this set must be unlocked
 * before it can be offered. Perks NOT in this set are always available.
 */
const GATED_PERK_IDS: Set<number> = new Set(ENTRY_SLOT_PERK_IDS);

// Also gate these higher-tier perks that appear in later quests
// (0x32–0x34 from QuestDatabase)
GATED_PERK_IDS.add(PerkId.ANGRY_RELOADER);      // 0x32
GATED_PERK_IDS.add(PerkId.ION_GUN_MASTER);      // 0x33
GATED_PERK_IDS.add(PerkId.STATIONARY_RELOADER);  // 0x34

/**
 * Additional gated perks and their costs.
 * These don't have entry table slots in the original 20 entries
 * but ARE unlocked by quests (tier 4-5).
 */
const EXTRA_GATED_ENTRIES: { perkId: number; cost: number }[] = [
    { perkId: PerkId.ANGRY_RELOADER, cost: 24 },       // 0x32
    { perkId: PerkId.ION_GUN_MASTER, cost: 25 },       // 0x33
    { perkId: PerkId.STATIONARY_RELOADER, cost: 26 },   // 0x34
];

/**
 * PerkUnlockRegistry - tracks which perks have been unlocked via quests.
 *
 * C reference: quest.c perk_entry_table + quest_database_init
 */
export class PerkUnlockRegistry {
    /** The perk entry table (mirrors C's global perk_entry_table). */
    private entries: PerkEntry[];

    /** Set of unlocked perk IDs for fast lookup. */
    private unlockedSet: Set<number> = new Set();

    constructor() {
        // Initialize all entries as locked (type_id = PERK_ANTIPERK)
        this.entries = PERK_ENTRY_COSTS.map((cost) => ({
            perkId: PERK_ANTIPERK,
            cost,
            prereq: 0,
        }));

        // Add extra gated entries
        for (const extra of EXTRA_GATED_ENTRIES) {
            this.entries.push({
                perkId: PERK_ANTIPERK,
                cost: extra.cost,
                prereq: 0,
            });
        }
    }

    /**
     * Unlock a perk by its PerkId.
     * Finds the entry table slot for this perk and sets it from PERK_ANTIPERK
     * to the actual perk ID.
     *
     * C reference: quest_results_screen_update (quest.c lines 678-688)
     */
    unlockPerk(perkId: number): void {
        if (perkId === PERK_ANTIPERK || perkId === PerkId.ANTIPERK) return;

        // Find the entry slot for this perk
        const slotIndex = this.findSlotForPerk(perkId);
        if (slotIndex >= 0) {
            this.entries[slotIndex].perkId = perkId;
        }

        this.unlockedSet.add(perkId);
    }

    /**
     * Check if a specific perk is unlocked.
     */
    isPerkUnlocked(perkId: number): boolean {
        // Perks not in the gated set are always available
        if (!GATED_PERK_IDS.has(perkId)) return true;
        return this.unlockedSet.has(perkId);
    }

    /**
     * Get all perks available at the given player level.
     *
     * A perk is available if:
     * 1. It's not gated (always-available perks 0x01–0x1b, and others not in entry table), OR
     * 2. It's unlocked (quest completed) AND playerLevel >= entry cost
     *
     * Excludes ANTIPERK (0x00).
     *
     * C reference: perk selection logic, gameplay.c lines 466-478
     */
    getAvailablePerks(playerLevel: number): PerkId[] {
        const available: PerkId[] = [];

        // Add all non-gated, non-ANTIPERK perks
        const allPerkValues = Object.values(PerkId).filter(
            (v) => typeof v === 'number' && v !== PerkId.ANTIPERK,
        ) as PerkId[];

        for (const perkId of allPerkValues) {
            if (!GATED_PERK_IDS.has(perkId)) {
                // Always-available perk
                available.push(perkId);
            } else {
                // Gated perk — check unlock + level
                const entry = this.getEntryForPerk(perkId);
                if (entry && entry.perkId !== PERK_ANTIPERK && playerLevel >= entry.cost) {
                    available.push(perkId);
                }
            }
        }

        return available;
    }

    /**
     * Get all currently unlocked perk IDs (for save serialization).
     */
    getUnlockedPerkIds(): number[] {
        return Array.from(this.unlockedSet);
    }

    /**
     * Load unlocked perks from saved state.
     * Restores the entry table to match the saved unlock state.
     */
    loadUnlockedPerks(ids: number[]): void {
        // Reset everything to locked
        for (const entry of this.entries) {
            entry.perkId = PERK_ANTIPERK;
        }
        this.unlockedSet.clear();

        // Re-unlock each saved perk
        for (const id of ids) {
            this.unlockPerk(id);
        }
    }

    /**
     * Reset all unlocks (for testing or new game).
     */
    reset(): void {
        for (const entry of this.entries) {
            entry.perkId = PERK_ANTIPERK;
        }
        this.unlockedSet.clear();
    }

    /**
     * Get the entry table (for debugging/testing).
     */
    getEntries(): readonly PerkEntry[] {
        return this.entries;
    }

    // ── Private helpers ──────────────────────────────────────────────────

    /**
     * Find the entry table slot index for a given perk ID.
     */
    private findSlotForPerk(perkId: number): number {
        // Check main entries first
        const mainIndex = ENTRY_SLOT_PERK_IDS.indexOf(perkId);
        if (mainIndex >= 0) return mainIndex;

        // Check extra gated entries
        for (let i = 0; i < EXTRA_GATED_ENTRIES.length; i++) {
            if (EXTRA_GATED_ENTRIES[i].perkId === perkId) {
                return PERK_ENTRY_COSTS.length + i;
            }
        }

        return -1;
    }

    /**
     * Get the entry for a given perk ID (by its slot).
     */
    private getEntryForPerk(perkId: number): PerkEntry | null {
        const slotIndex = this.findSlotForPerk(perkId);
        if (slotIndex >= 0 && slotIndex < this.entries.length) {
            return this.entries[slotIndex];
        }
        return null;
    }
}

// ── Singleton ────────────────────────────────────────────────────────────────

let registryInstance: PerkUnlockRegistry | null = null;

/**
 * Get the global PerkUnlockRegistry instance.
 */
export function getPerkUnlockRegistry(): PerkUnlockRegistry {
    if (registryInstance === null) {
        registryInstance = new PerkUnlockRegistry();
    }
    return registryInstance;
}

/**
 * Reset the global instance (for testing).
 */
export function resetPerkUnlockRegistry(): void {
    registryInstance = null;
}
