/**
 * PlayerTimers - Per-frame perk timer and bonus timer update logic.
 *
 * Extracted from Player.ts to reduce file size.
 * C code reference: player_update @ 004136b0, lines 11703-11884
 */

import { PerkId } from '../systems/PerkSystem';
import { SoundId } from '../audio/SoundId';
import type { BloodEffectSystem } from '../systems/effects/BloodEffectSystem';

/**
 * Subset of Player fields needed by updatePlayerTimers().
 * Matches all properties read or written in the original updateTimers() body.
 */
export interface PlayerTimerContext {
    readonly soundSystem: { playAtPosition(id: SoundId, x: number, y: number, range: number): void } | null;
    readonly bloodEffectSystem: BloodEffectSystem | null;
    readonly _hasMoved: boolean;
    readonly aimHeading: number;
    readonly aimX: number;
    readonly aimY: number;
    readonly x: number;
    readonly y: number;
    readonly spreadHeat: number;

    shieldTimer: number;
    shotCooldown: number;
    weaponPowerUpTimer: number;
    muzzleFlashAlpha: number;
    manBombTimer: number;
    manBombCooldownThreshold: number;
    pendingManBombBurst: boolean;
    livingFortressTimer: number;
    fireCoughTimer: number;
    pendingFireCoughSpawn: { x: number; y: number; angle: number; damage: number; speed: number } | null;
    hotTemperedTimer: number;
    pendingHotTemperedBurst: boolean;
    fireBulletsTimer: number;
    speedBonusTimer: number;
    lowHealthTimer: number;
    energizerTimer: number;
    doubleXPTimer: number;
    reflexBoostTimer: number;
    leanMeanExpTimer: number;
    experience: number;
    freezeTimer: number;
    health: number;
    jinxedCooldown: number;
    pendingJinxedKill: boolean;
}

/**
 * Update all per-frame timers that were formerly in Player.updateTimers().
 *
 * @param ctx  - Player (cast to PlayerTimerContext)
 * @param dt   - Delta time in seconds
 * @param perkSystem - Active perk system (or undefined)
 */
export function updatePlayerTimers(ctx: PlayerTimerContext, dt: number, perkSystem?: any): void {
    // Shield timer (invulnerability frames)
    if (ctx.shieldTimer > 0) {
        ctx.shieldTimer -= dt;
        if (ctx.shieldTimer < 0) ctx.shieldTimer = 0;
    }

    // Shot cooldown (C line 11727-11736)
    if (ctx.shotCooldown > 0) {
        if (ctx.weaponPowerUpTimer > 0) {
            ctx.shotCooldown -= dt * 1.5; // 1.5x speed with power-up (C line 11731)
        } else {
            ctx.shotCooldown -= dt;
        }
        if (ctx.shotCooldown < 0) ctx.shotCooldown = 0;
    }

    // Muzzle flash fade (C lines 128-133)
    if (ctx.muzzleFlashAlpha > 0) {
        ctx.muzzleFlashAlpha -= dt * 2.0;
        if (ctx.muzzleFlashAlpha < 0) ctx.muzzleFlashAlpha = 0;
    }
    // C L2761-L2762: final clamp — muzzle flash alpha never exceeds 0.8
    if (ctx.muzzleFlashAlpha > 0.8) ctx.muzzleFlashAlpha = 0.8;

    // Man Bomb perk (C lines 144-178)
    if (perkSystem) {
        if (!perkSystem.hasPerk(PerkId.MAN_BOMB)) {
            ctx.manBombTimer = 0.0;
        } else if (!ctx._hasMoved) {
            ctx.manBombTimer += dt;
            if (ctx.manBombTimer > ctx.manBombCooldownThreshold) {
                ctx.pendingManBombBurst = true;
                ctx.soundSystem?.playAtPosition(SoundId.EXPLOSION_SMALL, ctx.x, ctx.y, 800);
                ctx.manBombTimer -= ctx.manBombCooldownThreshold;
                ctx.manBombCooldownThreshold = 4.0;
            }
        }
    }

    // Spread heat recovery (C line 12490-12506)
    const hasSharpshooter = perkSystem?.hasPerk(PerkId.SHARPSHOOTER);
    if (!hasSharpshooter) {
        (ctx as { spreadHeat: number }).spreadHeat -= dt * 0.4;
        if (ctx.spreadHeat < 0.01) (ctx as { spreadHeat: number }).spreadHeat = 0.01;
    } else {
        (ctx as { spreadHeat: number }).spreadHeat -= dt * 2.0;
        if (ctx.spreadHeat < 0.02) (ctx as { spreadHeat: number }).spreadHeat = 0.02;
    }

    // Living Fortress timer (C lines 11772-11781)
    if (perkSystem) {
        if (!perkSystem.hasPerk(PerkId.LIVING_FORTRESS)) {
            ctx.livingFortressTimer = 0.0;
        } else if (!ctx._hasMoved) {
            ctx.livingFortressTimer += dt;
            if (ctx.livingFortressTimer > 30.0) ctx.livingFortressTimer = 30.0;
        }
    }

    // Fire Cough timer — managed by ProjectileSpawner.updateFireCough()
    // (no timer logic here; only reset when perk is absent)

    // Hot Tempered timer (C lines 11850-11884)
    if (perkSystem) {
        if (!perkSystem.hasPerk(PerkId.HOT_TEMPERED)) {
            ctx.hotTemperedTimer = 0.0;
        } else {
            ctx.hotTemperedTimer += dt;
            const burstInterval = 4.5;
            if (ctx.hotTemperedTimer > burstInterval) {
                const randomOffset = Math.floor(Math.random() * 8);
                ctx.hotTemperedTimer -= 2.0 + randomOffset;
                ctx.pendingHotTemperedBurst = true;
                ctx.soundSystem?.playAtPosition(SoundId.EXPLOSION_SMALL, ctx.x, ctx.y, 800);
            }
        }
    }

    // Speed bonus timer
    if (ctx.speedBonusTimer > 0) {
        ctx.speedBonusTimer -= dt;
        if (ctx.speedBonusTimer < 0) ctx.speedBonusTimer = 0;
    }

    // Low health visual effects (C player_update L12027-12043)
    if (ctx.lowHealthTimer !== 100.0 && ctx.health < 20.0 && ctx.lowHealthTimer - dt < 0.0) {
        // Calculate bleed position: offset -6 pixels along aim direction (C: cos/sin(aim_heading + PI/2 - 0.5) * -6)
        const bleedAngle = ctx.aimHeading + Math.PI / 2 - 0.5;
        const bleedX = Math.cos(bleedAngle) * -6.0 + ctx.x;
        const bleedY = Math.sin(bleedAngle) * -6.0 + ctx.y;
        // Spawn 3 blood splatters from bleed position (C L12033-12038)
        if (ctx.bloodEffectSystem) {
            ctx.bloodEffectSystem.spawnBloodSplatter(bleedX, bleedY, ctx.aimHeading, 0.0);
            ctx.bloodEffectSystem.spawnBloodSplatter(bleedX, bleedY, ctx.aimHeading, 0.0);
            ctx.bloodEffectSystem.spawnBloodSplatter(bleedX, bleedY, ctx.aimHeading, 0.0);
        }
        ctx.soundSystem?.playAtPosition(
            Math.random() < 0.5 ? SoundId.BLOOD_SPILL_01 : SoundId.BLOOD_SPILL_02,
            ctx.x,
            ctx.y,
            800,
        );
        ctx.lowHealthTimer = 1.0;
    }
    if (ctx.lowHealthTimer !== 100.0 && ctx.lowHealthTimer > 0) {
        ctx.lowHealthTimer -= dt;
    }

    // Weapon power-up timer (C line 6873-6874)
    if (ctx.weaponPowerUpTimer > 0) {
        ctx.weaponPowerUpTimer -= dt;
        if (ctx.weaponPowerUpTimer < 0) ctx.weaponPowerUpTimer = 0;
    }

    // Fire bullets timer (C: perks.c lines 539-544)
    if (ctx.fireBulletsTimer > 0) {
        ctx.fireBulletsTimer -= dt;
        if (ctx.fireBulletsTimer < 0) ctx.fireBulletsTimer = 0;
    }

    // Energizer timer (C line 6876-6877)
    if (ctx.energizerTimer > 0) {
        ctx.energizerTimer -= dt;
        if (ctx.energizerTimer < 0) ctx.energizerTimer = 0;
    }

    // Double XP timer (C line 6878)
    if (ctx.doubleXPTimer > 0) {
        ctx.doubleXPTimer -= dt;
        if (ctx.doubleXPTimer < 0) ctx.doubleXPTimer = 0;
    }

    // Reflex boost timer (C line 6879-6882)
    if (ctx.reflexBoostTimer > 0) {
        ctx.reflexBoostTimer -= dt;
        if (ctx.reflexBoostTimer < 0) ctx.reflexBoostTimer = 0;
    }

    // Lean Mean Exp Machine timer (C lines 4718-4726)
    ctx.leanMeanExpTimer -= dt;
    if (ctx.leanMeanExpTimer < 0.0) {
        ctx.leanMeanExpTimer = 0.25;
        const leanMeanCount = perkSystem?.getPerkCount(PerkId.LEAN_MEAN_EXP_MACHINE) ?? 0;
        if (leanMeanCount > 0) ctx.experience += leanMeanCount * 10;
    }

    // Living Fortress — second pass (duplicate in original; kept for fidelity)
    if (perkSystem?.hasPerk(PerkId.LIVING_FORTRESS)) {
        if (!ctx._hasMoved) {
            ctx.livingFortressTimer += dt;
            if (ctx.livingFortressTimer > 30.0) ctx.livingFortressTimer = 30.0;
        }
    } else {
        ctx.livingFortressTimer = 0.0;
    }

    // Death Clock timer (C lines 4730-4738) — drains health 3.33 HP/s
    if (perkSystem?.hasPerk(PerkId.DEATH_CLOCK)) {
        if (ctx.health > 0.0) {
            ctx.health -= dt * 3.3333333;
            if (ctx.health < 0.0) ctx.health = 0.0;
        }
    }

    // Freeze timer (C line 6577-6581)
    if (ctx.freezeTimer > 0) {
        ctx.freezeTimer -= dt;
        if (ctx.freezeTimer < 0) ctx.freezeTimer = 0;
    }

    // Jinxed perk (C: perks_update_effects lines 617-647)
    ctx.jinxedCooldown -= dt;
    if (ctx.jinxedCooldown < 0.0 && perkSystem?.hasPerk(PerkId.JINXED)) {
        // 10% chance to damage player
        if (Math.floor(Math.random() * 10) === 3) {
            ctx.health -= 5.0;
        }
        // Reset cooldown: 2-4 seconds (C: (rand%20)*0.1 + cooldown + 2.0)
        ctx.jinxedCooldown += 2.0 + Math.floor(Math.random() * 20) * 0.1;
        // Kill random enemy (handled in EnemySystemsUpdate.ts via flag)
        if (ctx.freezeTimer <= 0) {
            ctx.pendingJinxedKill = true;
        }
    }
}
