/**
 * PlayerWeapon - Weapon management extracted from Player.ts.
 *
 * Contains updateReload, switchWeapon, swapWeapon, canFire, startCooldown.
 */

import { getWeaponStats } from '../data/WeaponData';
import { PerkId } from '../systems/PerkSystem';
import { calculateReloadTime, calculateShotCooldown } from '../systems/combat/WeaponModifier';

/**
 * Clear reload state — always pair reloadTimer = 0 with reloadActive = false
 * to avoid leaving the player stuck in a "reloading" state that blocks firing.
 */
export function clearReload(ctx: { reloadTimer: number; reloadActive: boolean }): void {
    ctx.reloadTimer = 0;
    ctx.reloadActive = false;
}


/**
 * Duck-typed subset of Player fields needed by weapon functions.
 */
export interface PlayerWeaponContext {
    // Weapon state
    weaponId: number;
    clipSize: number;
    ammo: number;
    shotCooldown: number;
    reloadTimer: number;
    reloadTimerMax: number;
    reloadActive: boolean;
    muzzleFlashAlpha: number;
    angryReloaderTriggered: boolean;
    pendingAngryReloaderBurst: boolean;
    // Alternate weapon state
    altWeaponId: number;
    altClipSize: number;
    altAmmo: number;
    altShotCooldown: number;
    altReloadTimer: number;
    altReloadTimerMax: number;
    altReloadActive: boolean;
    weaponSwapCooldown: number;
    // Player state
    health: number;
    spreadHeat: number;
    // Bonus timers (for reload modifier)
    weaponPowerUpTimer: number;
}

/**
 * Update reload timer (C: player_update @ 004136b0, line 12505-12564).
 */
export function updateReload(
    ctx: PlayerWeaponContext,
    dt: number,
    fireKeyPressed: boolean,
    isMoving: boolean,
    perkSystem?: any,
): void {
    if (ctx.reloadTimer <= 0) return;

    // Anxious Loader: press fire during reload for -0.05/press
    if (perkSystem?.hasPerk(PerkId.ANXIOUS_LOADER) && fireKeyPressed && ctx.reloadTimer > 0) {
        ctx.reloadTimer -= 0.05;
        if (ctx.reloadTimer <= 0.0) {
            ctx.reloadTimer = dt * 0.8;
        }
    }

    const wasReloading = ctx.reloadTimer > 0;
    if (ctx.reloadTimer - dt < 0.0 && ctx.reloadTimer >= 0.0) {
        ctx.ammo = ctx.clipSize;
    }

    let reloadSpeed = 1.0;

    if (perkSystem) {
        const baseReloadTime = ctx.reloadTimerMax;
        const modifiedReloadTime = calculateReloadTime(baseReloadTime, perkSystem);
        if (baseReloadTime > 0) {
            reloadSpeed = baseReloadTime / modifiedReloadTime;
        }
    }

    if (!isMoving && perkSystem?.hasPerk(PerkId.STATIONARY_RELOADER)) {
        reloadSpeed = 3.0;
    }

    if (perkSystem?.hasPerk(PerkId.ANGRY_RELOADER) && ctx.reloadTimer > 0) {
        const reloadProgress = 1.0 - ctx.reloadTimer / ctx.reloadTimerMax;
        if (reloadProgress >= 0.5 && !ctx.angryReloaderTriggered) {
            ctx.pendingAngryReloaderBurst = true;
            ctx.angryReloaderTriggered = true;
        }
    }

    ctx.reloadTimer -= reloadSpeed * dt;

    if (ctx.reloadTimer < 0.0) {
        clearReload(ctx);
    }

    if (wasReloading && ctx.reloadTimer <= 0.0) {
        clearReload(ctx);
        ctx.angryReloaderTriggered = false;
    }
}

/**
 * Switch to a different weapon (port of weapon_assign_player from C line 41117).
 */
export function switchWeapon(ctx: PlayerWeaponContext, weaponId: number, perkSystem?: any): void {
    ctx.weaponId = weaponId;

    const weaponStats = getWeaponStats(weaponId);
    ctx.clipSize = weaponStats.clipSize;

    if (perkSystem) {
        if (perkSystem.hasPerk?.(PerkId.AMMO_MANIAC)) {
            ctx.clipSize = Math.ceil(ctx.clipSize * 1.2); // C perk_apply lines 247-255: 20% clip bonus
        }
        if (perkSystem.hasPerk?.(PerkId.MY_FAVOURITE_WEAPON)) {
            ctx.clipSize += 2;
        }
    }

    ctx.ammo = ctx.clipSize;
    ctx.shotCooldown = 0;
    clearReload(ctx);
}

/**
 * Swap to alternate weapon (C lines 1129-1166).
 */
export function swapWeapon(ctx: PlayerWeaponContext, perkSystem?: any): boolean {
    if (!perkSystem?.hasPerk?.(PerkId.ALTERNATE_WEAPON)) return false;
    if (ctx.weaponSwapCooldown > 0) return false;

    let tmp: number;

    tmp = ctx.altWeaponId;
    ctx.altWeaponId = ctx.weaponId;
    ctx.weaponId = tmp;

    tmp = ctx.altClipSize;
    ctx.altClipSize = ctx.clipSize;
    ctx.clipSize = tmp;

    const tmpBool = ctx.altReloadActive;
    ctx.altReloadActive = ctx.reloadActive;
    ctx.reloadActive = tmpBool;

    tmp = ctx.altAmmo;
    ctx.altAmmo = ctx.ammo;
    ctx.ammo = tmp;

    tmp = ctx.altReloadTimer;
    ctx.altReloadTimer = ctx.reloadTimer;
    ctx.reloadTimer = tmp;

    tmp = ctx.altShotCooldown;
    ctx.altShotCooldown = ctx.shotCooldown;
    ctx.shotCooldown = tmp;

    tmp = ctx.altReloadTimerMax;
    ctx.altReloadTimerMax = ctx.reloadTimerMax;
    ctx.reloadTimerMax = tmp;

    ctx.shotCooldown += 0.1;
    ctx.weaponSwapCooldown = 0.2;

    return true;
}

/**
 * Check if weapon can fire.
 * C code reference: player_update lines 1120-1128
 *   bVar8 = (shotCooldown <= 0 && reloadTimer == 0) — normal fire
 *   bVar5 = (shotCooldown <= 0 && experience > 0 && hasRegressionOrAmmoWithin) — perk fire
 * Either flag allows firing. bVar5 bypasses reload_active entirely.
 */
export function canFire(ctx: PlayerWeaponContext, perkSystem?: any): boolean {
    if (ctx.health <= 0) return false;
    if (ctx.shotCooldown > 0) return false;

    // Normal fire: not reloading
    if (!ctx.reloadActive) return true;

    // Perk fire: Regression Bullets / Ammunition Within bypass reload (C: bVar5)
    if (perkSystem?.hasPerk?.(PerkId.REGRESSION_BULLETS) || perkSystem?.hasPerk?.(PerkId.AMMUNITION_WITHIN)) {
        return true;
    }

    return false;
}

/**
 * Start a manual reload (C: player_start_reload @ 00413430, lines 6-36).
 * Returns true if reload was started.
 *
 * In C code, this is triggered by the reload key (Mouse3 by default).
 * Skip if already reloading (unless has Regression Bullets or Ammunition Within).
 */
export function startManualReload(
    ctx: PlayerWeaponContext,
    perkSystem?: any,
    playSoundCb?: () => void,
): boolean {
    // C lines 13-15: skip if already reloading, unless has infinite-ammo perks
    if (ctx.reloadActive) {
        if (
            !perkSystem?.hasPerk?.(PerkId.AMMUNITION_WITHIN) &&
            !perkSystem?.hasPerk?.(PerkId.REGRESSION_BULLETS)
        ) {
            return false;
        }
    }

    // Don't reload if reload timer is already running
    if (ctx.reloadTimer > 0) return false;

    // C line 17-23: play reload sfx and set reload_active
    if (!ctx.reloadActive) {
        playSoundCb?.();
        ctx.reloadActive = true;
    }

    // C lines 25-26: set reload timer from weapon table
    const weaponStats = getWeaponStats(ctx.weaponId);
    let reloadTime = weaponStats.reloadTime;

    // C line 27-29: Fastloader perk — 30% faster reload
    if (perkSystem?.hasPerk?.(PerkId.FASTLOADER)) {
        reloadTime *= 0.7;
    }

    // C lines 30-32: Weapon power-up bonus — 40% faster reload
    if (ctx.weaponPowerUpTimer > 0) {
        reloadTime *= 0.6;
    }

    ctx.reloadTimer = reloadTime;
    ctx.reloadTimerMax = reloadTime; // C line 33

    return true;
}

/**
 * Start weapon cooldown after firing.
 */
export function startCooldown(ctx: PlayerWeaponContext, duration: number, perkSystem?: any): void {
    let modifiedDuration = duration;
    if (perkSystem) {
        modifiedDuration = calculateShotCooldown(duration, perkSystem);
    }
    ctx.shotCooldown = modifiedDuration;
    // C L2676-L2678: muzzle_flash_alpha += weapon_table[weapon_id].spread_heat
    const weaponStats = getWeaponStats(ctx.weaponId);
    ctx.muzzleFlashAlpha += weaponStats.spreadHeat;
    // C L2673-L2674: clamp to 1.0
    if (ctx.muzzleFlashAlpha > 1.0) ctx.muzzleFlashAlpha = 1.0;
}
