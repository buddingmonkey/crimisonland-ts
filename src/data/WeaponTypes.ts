/**
 * WeaponTypes - Weapon type definitions
 *
 * Extracted from WeaponData.ts
 */

import { SoundId } from '../audio/SoundId';

/**
 * Projectile type enum - matches C projectile_type_id_t values
 * from projectile_render() at line 20366 in crimsonland.exe_decompiled_renamed.c
 *
 * Each type has distinct rendering: color, size, trail, glow, atlas frame
 */
export enum ProjectileType {
    // === Primary projectile types (bullet trail texture) ===
    NONE = 0, // Inactive / deactivates on render
    PISTOL = 1, // 1.2x quad, 6px bullet sprite
    ASSAULT_RIFLE = 2, // 1.0x quad, 8px bullet sprite (type 4 in C)
    SHOTGUN = 3, // 0.7x quad, 4px bullet (default)
    GAUSS_GUN = 4, // 1.1x quad, blue (0.2,0.5,1.0), 4px bullet
    SMG = 5, // 0.7x quad, 4px bullet (default)
    MINIGUN = 6, // 0.7x quad, 4px bullet (default)

    // === Plasma projectile types (particles texture, additive glow) ===
    PLASMA_RIFLE = 10, // 56px glow, 8-seg trail, 256px bloom, white
    PLASMA_MINIGUN = 11, // 16px glow, 3-seg trail, white
    PLASMA_CANNON = 12, // 84px glow, 18-seg trail, 256px bloom, white
    SPIDER_PLASMA = 13, // 16px glow, 3-seg trail, GREEN (0.3,1.0,0.3)
    SHRINKIFIER = 14, // 16px glow, 3-seg trail, BLUE (0.3,0.3,1.0)

    // === Special projectile types (projectile texture atlas) ===
    PULSE_GUN = 20, // Green (0.1,0.6,0.2), distance-scaled, atlas(2,0)
    SPLITTER_GUN = 21, // White, atlas(4,3), max 20px
    BLADE_GUN = 22, // Gray (0.8), rotating, atlas(4,6), max 20px
    PLAGUE_SPREADER = 23, // White, 60px multi-sprite cluster, animated rotation

    // === Ion/beam types (projectile texture, beam segments) ===
    ION_RIFLE = 30, // Blue-white (0.5,0.6,1.0), 2.2x beam, chain lightning
    ION_MINIGUN = 31, // Blue-white (0.5,0.6,1.0), 1.05x beam, chain lightning
    ION_CANNON = 32, // Blue-white (0.5,0.6,1.0), 3.5x beam, chain lightning
    FIRE_BULLETS = 33, // Orange (1.0,0.6,0.1), 0.8x beam

    // === Secondary projectile types (rockets, seekers) ===
    ROCKET = 100, // 14px sprite, 60px glow trail, atlas(4,3)
    SEEKER_ROCKET = 101, // 10px sprite, 40px glow trail, atlas(4,3)
    ROCKET_MINIGUN = 102, // 8px sprite, 30px glow trail, atlas(4,3)

    // === Legacy aliases for backward compatibility ===
    BULLET = 1, // Alias for PISTOL
    PLASMA = 10, // Alias for PLASMA_RIFLE
    ION = 30, // Alias for ION_RIFLE
    FLAME = 33, // Alias for FIRE_BULLETS
}

/**
 * Weapon flags (C weapon flags)
 */
export enum WeaponFlags {
    NONE = 0x00,
    AUTOMATIC = 0x01, // Full auto fire
    BURST = 0x02, // Burst fire mode
    CHARGE = 0x04, // Charge-up weapon
    ENERGY = 0x08, // Energy weapon
}

/**
 * Weapon statistics
 */
export interface WeaponStats {
    name: string; // Weapon name
    clipSize: number; // Magazine capacity
    damage: number; // Flat damage fallback (used when damageScale is absent)
    fireRate: number; // Shots per second (derived: 1/shotCooldown)
    shotCooldown: number; // Fire rate cooldown in seconds (C field 0x4c)
    spread: number; // Spread angle in radians (C field 0x54)
    spreadHeat: number; // Spread heat added per shot (C field 0x50)
    projectileSpeed: number; // Projectile velocity (pixels/sec)
    projectileCount: number; // Number of projectiles per shot (C field 0x6c: pellet_count)
    reloadTime: number; // Reload duration in seconds
    muzzleFlashAlpha: number; // Muzzle flash brightness
    projectileType: ProjectileType; // Projectile behavior type
    flags: WeaponFlags; // Special weapon flags
    hudIconId: number; // Index into 8×2 weapon icon atlas (ui_wicons.jaz)
    //   Used as: grim_set_sub_rect(8, 2, 1, hudIconId << 1)
    ammoClass: number; // Ammo indicator texture: 0=bullet, 1=fire, 2=rocket, 3=electric
    //   C field: weapon_ammo_class at offset 0x1f*weapon_id
    damageScale?: number; // C distance-based damage scale (C field 0x70)
    //   damage = ((100/dist) * damageScale * 30 + 10) * 0.95
    hitRadius?: number; // Projectile hit radius (C projectile_spawn, default 1.0)
    pelletSpreadMultiplier?: number; // Per-pellet angular spread coefficient (C player.c)
    //   pellet_angle = base + (rand%200-100) * multiplier
    ammoCost?: number; // Ammo consumed per shot (default 1.0). Fire weapons use fractional
    //   C: flamethrower=0.1, blow_torch=0.05, hr_flamer=0.1
    shotSfxId?: SoundId; // Sound effect for firing (C field 0x5c)
    reloadSfxId?: SoundId; // Sound effect for reloading (C field 0x64)
    shotSfxVariantCount?: number; // Number of sequential SFX variants for fire sound randomization
    //   C player.c:1284-1285: sfx = rand()%variant_count + base_id
}
