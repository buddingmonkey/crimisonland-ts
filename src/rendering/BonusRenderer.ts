/**
 * BonusRenderer - Bonus/pickup rendering extracted from SpriteRenderer.ts.
 *
 * C code reference: bonus_render() in bonuses.c (lines 1156-1300)
 */

import type { GrimInterface, TextureHandle } from '../engine/GrimInterface';
import { BonusType } from '../entities/Bonus';
import { getWeaponStats } from '../data/WeaponData';

/**
 * Texture context for bonus rendering.
 * Duck-typed subset of SpriteRenderer fields.
 */
export interface BonusTextureContext {
    readonly bonusHandle: TextureHandle;
    readonly weaponIconHandle: TextureHandle;
    readonly hasBonusSprite: boolean;
    readonly hasWeaponIconSprite: boolean;
}

/**
 * Icon ID mapping from BonusType to bonuses.jaz atlas frame index.
 * From C code bonus_metadata_init() in bonuses.c (lines 527-613).
 */
const BONUS_ICON_ID: Record<BonusType, number> = {
    [BonusType.NONE]: -1,
    [BonusType.WEAPON]: -1,
    [BonusType.POINTS]: 12,
    [BonusType.HEALTH]: 14,
    [BonusType.SHIELD]: 6,
    [BonusType.FIRE_BULLETS]: 11,
    [BonusType.ENERGIZER]: 10,
    [BonusType.DOUBLE_EXPERIENCE]: 4,
    [BonusType.NUKE]: 1,
    [BonusType.FIREBLAST]: 2,
    [BonusType.SHOCK_CHAIN]: 3,
    [BonusType.REFLEX_BOOST]: 5,
    [BonusType.WEAPON_POWER_UP]: 7,
    [BonusType.SPEED]: 9,
    [BonusType.FREEZE]: 8,
};

/**
 * Draw a bonus/pickup sprite.
 */
export function drawBonus(
    ctx: BonusTextureContext,
    grim: GrimInterface,
    x: number,
    y: number,
    bonusType: BonusType,
    amount: number,
    timeLeft: number,
    timeMax: number,
    bonusIndex: number,
    animTimer: number,
    elapsedMs: number,
): void {
    if (!ctx.hasBonusSprite) return;

    const iconId = BONUS_ICON_ID[bonusType] ?? -1;

    // Blinking alpha when time is running out (C lines 1204-1206)
    let alpha = 1.0;
    if (timeLeft < 2.0) {
        alpha = Math.sin(timeLeft * 18.849556) * 0.5 + 0.5;
    }
    alpha = Math.max(0, Math.min(1, alpha));

    // --- Background glow: atlas frame 0, 32x32 ---
    grim.bindTexture(ctx.bonusHandle);
    grim.setColor(255, 255, 255, Math.floor(alpha * 255));
    grim.setRotation(0);
    grim.setAtlasFrame(4, 0);
    grim.drawQuad(x - 16, y - 16, 32, 32);

    // C: bonus_meta_table[bonus_id].icon_id — weapon has icon_id = -1 (0xffffffff),
    // so the generic icon is skipped; only the weapon overlay from ui_wicons.jaz renders.
    if (iconId >= 0) {
        let fadeScale: number;
        if (timeLeft >= 0.5) {
            const elapsed = timeMax - timeLeft;
            fadeScale = elapsed >= 0.5 ? 1.0 : elapsed * 2.0;
        } else {
            fadeScale = timeLeft * 2.0;
        }

        const pulseRaw = Math.sin(bonusIndex + animTimer);
        const pulse = Math.pow(Math.abs(pulseRaw), 2) * Math.sign(pulseRaw);
        const scale = (pulse * 0.25 + 0.75) * fadeScale;

        const wobble = Math.sin(bonusIndex - elapsedMs * 0.003) * 0.2;

        grim.setColor(255, 255, 255, Math.floor(alpha * 255));
        grim.setRotation(wobble);

        let frameId = iconId;
        if (bonusType === BonusType.POINTS && amount === 1000) {
            frameId = iconId + 1;
        }
        grim.setAtlasFrame(4, frameId);

        const half = scale * 16;
        grim.drawQuad(x - half, y - half, scale * 32, scale * 32);

        grim.setRotation(0);
    }

    // Weapon bonus: draw weapon icon on top (C bonus_render lines 1302-1339)
    if (bonusType === BonusType.WEAPON && ctx.hasWeaponIconSprite) {
        let wFadeScale = 1.0;
        if (timeLeft >= 0.5) {
            const wElapsed = timeMax - timeLeft;
            wFadeScale = wElapsed >= 0.5 ? 1.0 : wElapsed * 2.0;
        } else {
            wFadeScale = timeLeft * 2.0;
        }
        // C: sin(bonus_animation_timer) — weapon pulse uses global timer only, no per-bonus offset
        const wPulseRaw = Math.sin(animTimer);
        const wPulse = Math.pow(Math.abs(wPulseRaw), 2) * Math.sign(wPulseRaw);
        const weaponScale = (wPulse * 0.25 + 0.75) * wFadeScale;

        grim.bindTexture(ctx.weaponIconHandle);
        grim.setRotation(0);
        // C: grim_set_sub_rect(8, 2, 1, weapon_table[amount].hud_icon_id << 1)
        // Each weapon icon occupies 2 columns × 1 row in the 8-column atlas
        const hudIconId = getWeaponStats(amount).hudIconId;
        grim.setSubRect(8, 2, 1, hudIconId << 1);
        const weaponHalf = weaponScale * 30;
        grim.setColor(255, 255, 255, Math.floor(alpha * 255));
        grim.drawQuad(x - weaponHalf, y - weaponHalf * 0.5, weaponScale * 60, weaponScale * 30);
        // Rebind bonus texture for any subsequent draws
        grim.bindTexture(ctx.bonusHandle);
    }
}
