/**
 * WeaponModifier - Utility for applying weapon perk modifiers
 *
 * Port of weapon modification logic from C code
 */

import { PerkId } from '../PerkSystem';
import type { PerkSystem } from '../PerkSystem';

/**
 * Calculate modified clip size with perks
 *
 * Port of C code lines 41135-41150
 */
export function calculateClipSize(baseClipSize: number, perkSystem: PerkSystem | null): number {
    if (!perkSystem) {
        return baseClipSize;
    }

    let clipSize = baseClipSize;

    // C line 41147-41150: My Favourite Weapon (+2 clip size)
    if (perkSystem.hasPerk(PerkId.MY_FAVOURITE_WEAPON)) {
        clipSize += 2;
    }

    return Math.floor(clipSize);
}

/**
 * Calculate modified shot cooldown (fire rate) with perks
 *
 * Port of C code lines 13437-13442
 */
export function calculateShotCooldown(baseCooldown: number, perkSystem: PerkSystem | null): number {
    if (!perkSystem) {
        return baseCooldown;
    }

    let cooldown = baseCooldown;

    // C line 13437-13438: Fastshot (12% faster = multiply by 0.88)
    if (perkSystem.hasPerk(PerkId.FASTSHOT)) {
        cooldown = cooldown * 0.88;
    }

    // C line 13440-13441: Sharpshooter (5% slower for accuracy = multiply by 1.05)
    if (perkSystem.hasPerk(PerkId.SHARPSHOOTER)) {
        cooldown = cooldown * 1.05;
    }

    return cooldown;
}

/**
 * Calculate modified reload time with perks
 *
 * Port of C code line 11562 and related reload logic
 */
export function calculateReloadTime(baseReloadTime: number, perkSystem: PerkSystem | null): number {
    if (!perkSystem) {
        return baseReloadTime;
    }

    let reloadTime = baseReloadTime;

    // C line 11562: Fastloader (faster reload, estimated 25% faster)
    if (perkSystem.hasPerk(PerkId.FASTLOADER)) {
        reloadTime = reloadTime * 0.75; // 25% faster
    }

    return reloadTime;
}

/**
 * Calculate modified weapon spread with perks
 *
 * Port of C code lines 12491, 13381, 20162
 * Note: Sharpshooter does NOT reduce instantaneous spread.
 * It only speeds up spread recovery (see calculateSpreadRecoveryMultiplier).
 */
export function calculateSpreadModifier(_perkSystem: PerkSystem | null): number {
    // C: Sharpshooter affects recovery speed, not base spread
    return 1.0;
}

/**
 * Calculate spread recovery speed multiplier with perks
 *
 * C behavior: Sharpshooter gives 2× faster spread recovery.
 * Spread heat returns to baseline twice as fast.
 */
export function calculateSpreadRecoveryMultiplier(perkSystem: PerkSystem | null): number {
    if (!perkSystem) {
        return 1.0;
    }

    // C: Sharpshooter gives 2× spread recovery speed
    if (perkSystem.hasPerk(PerkId.SHARPSHOOTER)) {
        return 2.0;
    }

    return 1.0;
}
