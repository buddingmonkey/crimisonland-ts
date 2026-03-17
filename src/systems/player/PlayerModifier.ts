/**
 * PlayerModifier - Utility for applying player stat perk modifiers
 *
 * Port of player modification logic from C code
 */

import { PerkId } from '../PerkSystem';
import type { PerkSystem } from '../PerkSystem';

/**
 * Calculate modified movement speed with perks
 *
 * Port of C code lines 11958-11974
 */
export function calculateMoveSpeed(
    _baseMoveSpeed: number,
    perkSystem: PerkSystem | null,
): { maxSpeed: number; acceleration: number } {
    if (!perkSystem) {
        return { maxSpeed: 2.0, acceleration: 5.0 };
    }

    // C line 11958-11974: Long Distance Runner (+40% max speed)
    if (perkSystem.hasPerk(PerkId.LONG_DISTANCE_RUNNER)) {
        return {
            maxSpeed: 2.8, // 40% faster (2.0 * 1.4 = 2.8)
            acceleration: 4.0, // Slightly slower acceleration
        };
    }

    return { maxSpeed: 2.0, acceleration: 5.0 };
}

/**
 * Calculate modified collision slowdown with perks
 *
 * Port of C code for Unstoppable perk
 */
export function calculateCollisionSlowdown(perkSystem: PerkSystem | null): number {
    if (!perkSystem) {
        return 1.0;
    }

    // Unstoppable: No collision slowdown
    if (perkSystem.hasPerk(PerkId.UNSTOPPABLE)) {
        return 0.0; // No slowdown from monster collisions
    }

    return 1.0; // Normal slowdown
}

/**
 * Result from applyInstantPerkEffect — signals to caller what follow-up actions are needed.
 */
export interface InstantPerkEffectResult {
    xp: number;
    health: number;
    shouldDie: boolean;
    shouldKillAlternateWeakEnemies: boolean; // Lifeline 50/50
    shouldShrinkEnemyHitboxes: boolean; // Breathing Room
    shouldExplode: boolean; // Man Bomb
    shouldGetRandomWeapon: boolean; // Random Weapon
    shouldRefillAllAmmo: boolean; // Ammo Maniac
    shouldSetPlaguebearer: boolean; // Plaguebearer
    extraLevels: number; // Infernal Contract
    extraPendingPerks: number; // Infernal Contract
    clearPerks: PerkId[]; // Death Clock: clear regen perks
}

/**
 * Apply instant effect perks (called when perk is acquired)
 *
 * Port of C code perk_apply() @ lines 144-298
 */
export function applyInstantPerkEffect(
    perkId: PerkId,
    currentXP: number,
    currentHealth: number,
): InstantPerkEffectResult {
    let xp = currentXP;
    let health = currentHealth;
    let shouldDie = false;
    let shouldKillAlternateWeakEnemies = false;
    let shouldShrinkEnemyHitboxes = false;
    let shouldExplode = false;
    let shouldGetRandomWeapon = false;
    let shouldRefillAllAmmo = false;
    let shouldSetPlaguebearer = false;
    let extraLevels = 0;
    let extraPendingPerks = 0;
    const clearPerks: PerkId[] = [];

    // C line 3994-3998: Instant Winner (+2500 XP)
    if (perkId === PerkId.INSTANT_WINNER) {
        xp += 2500; // 0x9c4 in hex = 2500
    }

    // C line 4001-4009: Fatal Lottery (50/50 death or +10000 XP)
    if (perkId === PerkId.FATAL_LOTTERY) {
        if (Math.random() < 0.5) {
            xp += 10000; // 50% chance for massive XP boost
        } else {
            shouldDie = true; // 50% chance of instant death
        }
    }

    // C perk_apply lines 242-246: Grim Deal — 18% score bonus (GAMEFAQ), kill player
    if (perkId === PerkId.GRIM_DEAL) {
        xp += Math.floor(xp * 0.18); // 18% score bonus
        health = -1.0;
        shouldDie = true;
    }

    // C perk_apply: Infernal Contract — +3 levels, +3 pending perks, health → 0.1
    if (perkId === PerkId.INFERNAL_CONTRACT) {
        health = 0.1;
        extraLevels = 3;
        extraPendingPerks = 3;
    }

    // C perk_apply: Thick Skinned — lose 33% health on apply (min 1 HP)
    if (perkId === PerkId.THICK_SKINNED) {
        health = health - health * 0.33333334;
        if (health <= 0) health = 1.0;
    }

    // C perk_apply: Death Clock — health = 100, remove regen perks
    if (perkId === PerkId.DEATH_CLOCK) {
        health = 100.0;
        clearPerks.push(PerkId.REGENERATION, PerkId.GREATER_REGENERATION);
    }

    // C perk_apply: Breathing Room — health *= 0.333, shrink enemy hitboxes (NOT kill them)
    // C also resets bonus_spawn_guard = 0 here; in TS this is per-entity (noBonusDrop) and
    // defaults to false, so no explicit reset is needed.
    if (perkId === PerkId.BREATHING_ROOM) {
        health = health * 0.3333333;
        shouldShrinkEnemyHitboxes = true;
    }

    // C perk_apply: Plaguebearer — set plaguebearer_active flag
    if (perkId === PerkId.PLAGUEBEARER) {
        shouldSetPlaguebearer = true;
    }

    // C perk_apply: Lifeline 50/50 — kill every other active enemy with health ≤ 500
    if (perkId === PerkId.LIFELINE_50_50) {
        shouldKillAlternateWeakEnemies = true;
    }

    // C perk_apply: Ammo Maniac — reassign all weapons (refills all ammo)
    if (perkId === PerkId.AMMO_MANIAC) {
        shouldRefillAllAmmo = true;
    }

    // Man Bomb: Passive perk — automatic explosions while standing still (see PlayerTimers.ts).
    // C perk_apply() has no instant effect for Man Bomb; it is purely timer-driven.

    // Random Weapon: Get random weapon
    if (perkId === PerkId.RANDOM_WEAPON) {
        shouldGetRandomWeapon = true;
    }

    // C perk_apply: Bandage — health *= (rand() % 50 + 1), cap at 100
    if (perkId === PerkId.BANDAGE) {
        const multiplier = Math.floor(Math.random() * 50) + 1;
        health = health * multiplier;
        if (health > 100) health = 100;
    }

    return {
        xp,
        health,
        shouldDie,
        shouldKillAlternateWeakEnemies,
        shouldShrinkEnemyHitboxes,
        shouldExplode,
        shouldGetRandomWeapon,
        shouldRefillAllAmmo,
        shouldSetPlaguebearer,
        extraLevels,
        extraPendingPerks,
        clearPerks,
    };
}

/**
 * Calculate health regeneration rate with perks
 *
 * Port of C code perks_update_effects lines 498-509
 *
 * C code: only Regeneration perk is checked here.
 * 50% random chance per frame to add +dt HP (capped at 100).
 * Greater Regeneration's benefit comes from stacking via prerequisite.
 */
export function calculateRegenRate(dt: number, perkSystem: PerkSystem | null): number {
    if (!perkSystem) return 0;

    // C: only Regeneration perk checked, 50% chance per frame
    if (perkSystem.hasPerk(PerkId.REGENERATION)) {
        if (Math.random() < 0.5) {
            return dt; // +dt HP per qualifying frame
        }
    }

    return 0;
}
