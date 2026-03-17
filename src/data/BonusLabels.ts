/**
 * BonusLabels - Label/name metadata for bonus pickups.
 *
 * Port of C code bonus_metadata_init() which populates bonus_meta_table
 * with display labels for each bonus type.
 *
 * Used for:
 *  1. Proximity tooltip text (C: bonus_label_for_entry + grim_draw_text_small)
 *  2. HUD slide panel labels (C: bonus_hud_add_slot)
 */

import { BonusType } from '../entities/Bonus';
import { getWeaponStats } from './WeaponData';

/**
 * Display labels from C bonus_metadata_init() (lines 11244-11327).
 * These match the strings allocated via strdup_malloc in the C code.
 */
export const BONUS_LABELS: Record<BonusType, string> = {
    [BonusType.NONE]: '',
    [BonusType.WEAPON]: 'New Weapon', // C: bonus_new_weapon_name (overridden per-weapon)
    [BonusType.POINTS]: 'Score', // C: bonus_points_format_prefix (formatted with amount)
    [BonusType.HEALTH]: 'MediKit', // C: bonus_medikit_name
    [BonusType.SHIELD]: 'Shield', // C: bonus_shield_name
    [BonusType.FIRE_BULLETS]: 'Fire Bullets', // C: bonus_fire_bullets_name
    [BonusType.ENERGIZER]: 'Energizer', // C: bonus_energizer_name
    [BonusType.DOUBLE_EXPERIENCE]: 'Double Experience', // C: bonus_double_xp_name
    [BonusType.NUKE]: 'Nuke', // C: bonus_nuke_name
    [BonusType.FIREBLAST]: 'Fireblast', // C: bonus_fireblast_name
    [BonusType.SHOCK_CHAIN]: 'Shock Chain', // C: bonus_shock_chain_name
    [BonusType.REFLEX_BOOST]: 'Reflex Boost', // C: bonus_reflex_boost_name
    [BonusType.WEAPON_POWER_UP]: 'Weapon Power-Up', // C: bonus_weapon_power_up_name
    [BonusType.SPEED]: 'Speed', // C: bonus_speed_name
    [BonusType.FREEZE]: 'Freeze', // C: bonus_freeze_name
};

/**
 * Icon IDs from C bonus_metadata_init() — used for HUD slide panels.
 * Maps to bonuses.jaz atlas frame IDs.
 */
export const BONUS_ICON_IDS: Record<BonusType, number> = {
    [BonusType.NONE]: -1,
    [BonusType.WEAPON]: -1, // C: bonus_new_weapon_icon_id = 0xffffffff (-1)
    [BonusType.POINTS]: 12, // C: bonus_xp_icon_id = 0xc
    [BonusType.HEALTH]: 14, // C: bonus_medikit_icon_id = 0xe
    [BonusType.SHIELD]: 6, // C: bonus_shield_icon_id = 6
    [BonusType.FIRE_BULLETS]: 11, // C: bonus_fire_bullets_icon_id = 0xb
    [BonusType.ENERGIZER]: 10, // C: bonus_energizer_icon_id = 10
    [BonusType.DOUBLE_EXPERIENCE]: 4, // C: bonus_double_xp_icon_id = 4
    [BonusType.NUKE]: 1, // C: bonus_nuke_icon_id = 1 (second sprite in bonuses.jaz)
    [BonusType.FIREBLAST]: 2, // C: bonus_fireblast_icon_id = 2
    [BonusType.SHOCK_CHAIN]: 3, // C: bonus_shock_chain_icon_id = 3
    [BonusType.REFLEX_BOOST]: 5, // C: bonus_reflex_boost_icon_id = 5
    [BonusType.WEAPON_POWER_UP]: 7, // C: bonus_weapon_power_up_icon_id = 7
    [BonusType.SPEED]: 9, // C: bonus_speed_icon_id = 9
    [BonusType.FREEZE]: 8, // C: bonus_freeze_icon_id = 8
};

/**
 * Get the display label for a bonus entry.
 *
 * Port of C bonus_label_for_entry() @ 00429580:
 * - WEAPON → weapon name (e.g. "Assault Rifle")
 * - POINTS → "Score +500"
 * - All others → static label from bonus_meta_table
 */
export function getBonusLabel(type: BonusType, amount: number): string {
    if (type === BonusType.WEAPON) {
        const stats = getWeaponStats(amount);
        return stats.name;
    }
    if (type === BonusType.POINTS) {
        return `Score +${amount}`;
    }
    return BONUS_LABELS[type] || '';
}

/**
 * Check if a bonus type has an active timer (i.e. shows a HUD slide panel).
 * These are the types that call bonus_hud_add_slot() in bonus_apply().
 */
export function isTimedBonus(type: BonusType): boolean {
    switch (type) {
        case BonusType.REFLEX_BOOST:
        case BonusType.WEAPON_POWER_UP:
        case BonusType.SPEED:
        case BonusType.FREEZE:
        case BonusType.SHIELD:
        case BonusType.FIRE_BULLETS:
        case BonusType.ENERGIZER:
        case BonusType.DOUBLE_EXPERIENCE:
            return true;
        default:
            return false;
    }
}
