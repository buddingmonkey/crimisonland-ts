/**
 * WeaponUnlockRegistry - Manages which weapons are available as bonus drops.
 *
 * Port of C code's weapon unlock system:
 * - weapon_refresh_available @ 00452e40: rebuilds availability from quest progress
 * - weapon_pick_random_available @ 00452cd0: selects a random unlocked weapon
 *
 * In the C code, completing quests unlocks weapons via unlock_weapon_id in
 * quest_meta_t. The weapon_table[].unlocked flag gates which weapons can
 * appear as bonus drops. Pistol (ID 0 in TS, ID 1 in C) is always available.
 * Survival mode additionally unlocks shotgun, SMG, and assault rifle.
 */

import { QUEST_DATABASE } from '../data/quests/QuestDatabase';
import { SELECTABLE_WEAPON_COUNT } from '../data/WeaponData';

/** Total number of weapons in the weapon table (IDs 0-39) */
const TOTAL_WEAPONS = 40;

/**
 * WeaponUnlockRegistry - tracks which weapons are unlocked and available
 * for bonus drops.
 *
 * C reference: weapon_table[].unlocked + weapon_pick_random_available
 */
export class WeaponUnlockRegistry {
    /** Set of unlocked weapon IDs */
    private unlocked: Set<number> = new Set();

    /** Weapon usage counts for anti-repetition (C: game_status_blob.weapon_usage_counts) */
    private usageCounts: number[] = new Array(TOTAL_WEAPONS).fill(0);

    constructor() {
        // Pistol (TS ID 0) is always unlocked (C: weapon_pistol_unlocked = 1)
        this.unlocked.add(0);
    }

    /**
     * Rebuild weapon availability from quest completion progress.
     * Port of weapon_refresh_available @ 00452e40
     *
     * Iterates through completed quests (0..unlockIndex-1) and unlocks
     * each quest's unlockWeaponId.
     *
     * @param questUnlockIndex Number of quests completed (0-based count)
     * @param isSurvivalMode If true, also unlock shotgun/SMG/assault rifle
     *                       (C lines 1460-1464)
     */
    refreshAvailable(questUnlockIndex: number, isSurvivalMode: boolean = false): void {
        // Reset all unlocks
        this.unlocked.clear();

        // Pistol always available (C: weapon_pistol_unlocked = 1)
        this.unlocked.add(0);

        // Iterate completed quests and unlock their weapons
        for (let i = 0; i < questUnlockIndex && i < QUEST_DATABASE.length; i++) {
            const weaponId = QUEST_DATABASE[i].unlockWeaponId;
            if (weaponId > 0 && weaponId < TOTAL_WEAPONS) {
                this.unlocked.add(weaponId);
            }
        }

        // Survival mode: also unlock shotgun, SMG, assault rifle
        // C code lines 1460-1464:
        //   if (game_mode == SURVIVAL) {
        //     weapon_shotgun_unlocked = 1;
        //     weapon_smg_unlocked = 1;
        //     weapon_assault_rifle_unlocked = 1;
        //   }
        if (isSurvivalMode) {
            this.unlocked.add(1);  // Assault Rifle (TS ID 1)
            this.unlocked.add(2);  // Shotgun (TS ID 2)
            this.unlocked.add(5);  // SMG (TS ID 5)
        }
    }

    /**
     * Unlock a specific weapon by ID.
     * Called on quest completion when quest.unlockWeaponId > 0.
     */
    unlockWeapon(weaponId: number): void {
        if (weaponId > 0 && weaponId < TOTAL_WEAPONS) {
            this.unlocked.add(weaponId);
        }
    }

    /**
     * Check if a weapon is unlocked.
     */
    isUnlocked(weaponId: number): boolean {
        return this.unlocked.has(weaponId);
    }

    /**
     * Pick a random available (unlocked) weapon.
     * Port of weapon_pick_random_available @ 00452cd0
     *
     * C code logic:
     * 1. Roll rand() % 0x21 + 1 (1-33 in C, maps to 0-32 in TS)
     * 2. If weapon has been used before (usage_count > 0), 50% chance to re-roll
     * 3. Loop until an unlocked weapon is found
     * 4. Special: blocks weapon 0x17 (TS ~23) on quest 5-10
     *
     * The C code uses weapon IDs 1-33 (0x21). In TS we use 0-based IDs.
     * We pick from all unlocked non-pistol weapons if possible.
     */
    pickRandomAvailable(): number {
        const unlockedArray = Array.from(this.unlocked);

        // If only pistol is unlocked, return pistol
        if (unlockedArray.length <= 1) {
            return 0;
        }

        // Try up to 100 times (C code loops indefinitely but we add a safety limit)
        for (let attempt = 0; attempt < 100; attempt++) {
            // Pick random weapon ID from the selectable range, excluding 0 (pistol)
            // C: rand() % 0x21 + 1 → weapon IDs 1-33 (maps to TS IDs within 0-32)
            const weaponId = Math.floor(Math.random() * SELECTABLE_WEAPON_COUNT) + 1;

            // Anti-repetition: if weapon was used before, 50% chance to re-roll
            // C lines 1367-1373
            if (this.usageCounts[weaponId] > 0) {
                if (Math.random() < 0.5) {
                    // Re-roll
                    const rerollId = Math.floor(Math.random() * SELECTABLE_WEAPON_COUNT) + 1;
                    if (this.unlocked.has(rerollId)) {
                        this.usageCounts[rerollId]++;
                        return rerollId;
                    }
                    // Re-roll wasn't unlocked, fall through to check original
                }
            }

            // Check if this weapon is unlocked
            if (this.unlocked.has(weaponId)) {
                this.usageCounts[weaponId]++;
                return weaponId;
            }
        }

        // Fallback: pick a random unlocked weapon that isn't pistol
        const nonPistol = unlockedArray.filter(id => id !== 0);
        if (nonPistol.length > 0) {
            return nonPistol[Math.floor(Math.random() * nonPistol.length)];
        }

        return 0; // Last resort: pistol
    }

    /**
     * Set weapon usage counts (loaded from save data).
     */
    setUsageCounts(counts: number[]): void {
        this.usageCounts = [...counts];
        while (this.usageCounts.length < TOTAL_WEAPONS) {
            this.usageCounts.push(0);
        }
    }

    /**
     * Get all unlocked weapon IDs (for save serialization).
     */
    getUnlockedWeaponIds(): number[] {
        return Array.from(this.unlocked).sort((a, b) => a - b);
    }

    /**
     * Load unlocked weapons from saved state.
     */
    loadUnlockedWeapons(ids: number[]): void {
        this.unlocked.clear();
        this.unlocked.add(0); // Pistol always unlocked
        for (const id of ids) {
            if (id >= 0 && id < TOTAL_WEAPONS) {
                this.unlocked.add(id);
            }
        }
    }

    /**
     * Get the number of unlocked weapons.
     */
    getUnlockedCount(): number {
        return this.unlocked.size;
    }

    /**
     * Reset all unlocks (for testing or new game).
     */
    reset(): void {
        this.unlocked.clear();
        this.unlocked.add(0); // Pistol always unlocked
        this.usageCounts = new Array(TOTAL_WEAPONS).fill(0);
    }
}

// ── Singleton ────────────────────────────────────────────────────────────────

let registryInstance: WeaponUnlockRegistry | null = null;

/**
 * Get the global WeaponUnlockRegistry instance.
 */
export function getWeaponUnlockRegistry(): WeaponUnlockRegistry {
    if (registryInstance === null) {
        registryInstance = new WeaponUnlockRegistry();
    }
    return registryInstance;
}

/**
 * Reset the global instance (for testing).
 */
export function resetWeaponUnlockRegistry(): void {
    registryInstance = null;
}
