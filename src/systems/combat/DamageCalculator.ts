/**
 * DamageCalculator - Utility for calculating damage with perk modifiers
 *
 * Port of damage calculation from C code (lines 18910-18970)
 */

import { ProjectileType } from '../../data/WeaponData';
import { PerkId } from '../PerkSystem';
import type { PerkSystem } from '../PerkSystem';

/**
 * Damage type enum (from C code)
 */
export enum DamageType {
    BULLET = 1, // Standard bullet damage (C line 18917)
    PLASMA = 2, // Plasma damage
    ROCKET = 3, // Rocket/explosive damage
    FLAME = 4, // Fire damage (C line 18960)
    ION = 7, // Ion beam damage (C line 18952)
}

/**
 * Map ProjectileType to DamageType
 */
export function projectileToDamageType(projectileType: ProjectileType): DamageType {
    switch (projectileType) {
        case ProjectileType.BULLET:
            return DamageType.BULLET;
        case ProjectileType.PLASMA:
            return DamageType.PLASMA;
        case ProjectileType.ROCKET:
            return DamageType.ROCKET;
        case ProjectileType.FLAME:
            return DamageType.FLAME;
        case ProjectileType.ION:
            return DamageType.ION;
        default:
            return DamageType.BULLET;
    }
}

/**
 * Calculate final damage with all perk modifiers applied
 *
 * Port of C code lines 18917-18962
 */
export function calculateDamageWithPerks(
    baseDamage: number,
    damageType: DamageType,
    perkSystem: PerkSystem | null,
): number {
    if (!perkSystem) {
        return baseDamage;
    }

    let damage = baseDamage;

    // C line 18917-18941: Bullet damage modifiers
    if (damageType === DamageType.BULLET) {
        // C line 18918-18921: Uranium Filled Bullets (+100% damage)
        if (perkSystem.hasPerk(PerkId.URANIUM_FILLED_BULLETS)) {
            damage = damage + damage; // Double damage
        }

        // C line 18934-18937: Barrel Greaser (+40% damage)
        if (perkSystem.hasPerk(PerkId.BARREL_GREASER)) {
            damage = damage * 1.4;
        }

        // C line 18938-18941: Doctor (+20% damage)
        if (perkSystem.hasPerk(PerkId.DOCTOR)) {
            damage = damage * 1.2;
        }
    }
    // C line 18952-18954: Ion Gun Master (+20% ion damage)
    else if (damageType === DamageType.ION) {
        if (perkSystem.hasPerk(PerkId.ION_GUN_MASTER)) {
            damage = damage * 1.2;
        }
    }

    // C line 18960-18962: Pyromaniac (+50% fire damage)
    if (damageType === DamageType.FLAME) {
        if (perkSystem.hasPerk(PerkId.PYROMANIAC)) {
            damage = damage * 1.5;
        }
    }

    return damage;
}

/**
 * Calculate incoming damage reduction from defensive perks
 *
 * Port of C code lines 21115-21145
 */
export function calculateIncomingDamage(
    baseDamage: number,
    isReloading: boolean,
    perkSystem: PerkSystem | null,
): number {
    if (!perkSystem) {
        return baseDamage;
    }

    let damage = baseDamage;

    // C line 21122-21125: Thick Skinned (33% damage reduction)
    if (perkSystem.hasPerk(PerkId.THICK_SKINNED)) {
        damage = damage * 0.67; // 33% reduction = multiply by 0.67
    }

    // C line 21141-21145: Tough Reloader (50% damage reduction while reloading)
    if (isReloading && perkSystem.hasPerk(PerkId.TOUGH_RELOADER)) {
        damage = damage * 0.5; // 50% reduction
    }

    return damage;
}

/**
 * Check if attack is dodged by defensive perks
 *
 * Port of C code lines 21127-21138
 * Returns true if attack should be dodged (no damage taken)
 */
export function checkDodge(perkSystem: PerkSystem | null): boolean {
    if (!perkSystem) {
        return false;
    }

    // C line 21127-21138: Ninja (33% dodge chance)
    if (perkSystem.hasPerk(PerkId.NINJA)) {
        const rand = Math.random();
        if (rand < 0.33) {
            return true; // Dodged!
        }
    }
    // C line 21129-21132: Dodger (20% dodge chance)
    // Note: Ninja is checked first, so if you have both, Ninja takes precedence
    else if (perkSystem.hasPerk(PerkId.DODGER)) {
        const rand = Math.random();
        if (rand < 0.2) {
            return true; // Dodged!
        }
    }

    return false;
}
