/**
 * WeaponData - Comprehensive weapon statistics and configuration
 *
 * Accurate port of weapon_table_init from crimsonland.exe_decompiled_renamed.c
 * (lines 40042-41372)
 *
 * Types are defined in WeaponTypes.ts and re-exported here for backward compatibility.
 */

export { ProjectileType, WeaponFlags, type WeaponStats } from './WeaponTypes';
import { ProjectileType, WeaponFlags, type WeaponStats } from './WeaponTypes';

import { SoundId } from '../audio/SoundId';

/**
 * Comprehensive weapon data table (from C weapon_table_init @ 004519b0)
 *
 * Hex-to-float conversions verified with IEEE 754:
 *   0x3f800000 = 1.0    0x40000000 = 2.0    0x40400000 = 3.0
 *   0x3f000000 = 0.5    0x3e800000 = 0.25   0x3dcccccd = 0.1
 *   0x3f99999a = 1.2    0x3fb33333 = 1.4    0x3fcccccd = 1.6
 *
 * NOTE: The C code field labeled "damage" in the struct is actually a float
 * multiplier (values like 1.2, 1.4, 3.0), NOT absolute damage. The integer
 * damage values used in gameplay are set via the global constants at the top
 * of weapon_table_init (e.g., 0x41f00000 = 30.0, 0x41a00000 = 20.0).
 * We keep 'damage' as the absolute gameplay value for our TS implementation.
 */
export const WEAPON_DATA: Record<number, WeaponStats> = {
    // ========================================================================
    // ID 0: Pistol (C slot 1, name at 0x004d7aa8)
    // C code: lines 40118-40152
    // ========================================================================
    0: {
        name: 'Pistol',
        clipSize: 12, // weapon_default_clip_size = 0xc = 12
        damage: 55, // 0x425c0000 = 55.0 (C flat damage at struct offset 0x6C)
        fireRate: 1.41, // 1 / 0.712
        shotCooldown: 0.712, // 0x3f3631f9 = 0.712
        spread: 0.22, // 0x3e6147ae = 0.220
        spreadHeat: 1.2, // 0x3f99999a = 1.200
        projectileSpeed: 1200,
        projectileCount: 1, // C weapon_id=1 fires 1 projectile (hardcoded in switch case)
        reloadTime: 1.2, // weapon_default_reload_time = 0x3f99999a = 1.2
        muzzleFlashAlpha: 0.8,
        projectileType: ProjectileType.PISTOL,
        flags: WeaponFlags.NONE,
        hudIconId: 0, // C: weapon_table.hud_icon_id = 0
        ammoClass: 0, // bullet
        hitRadius: 1.0, // C projectile_spawn default hit_radius
        shotSfxId: SoundId.PISTOL_FIRE, // sfx_pistol_fire
        reloadSfxId: SoundId.PISTOL_RELOAD, // sfx_pistol_reload
    },

    // ========================================================================
    // ID 1: Assault Rifle (C slot 2, name at 0x004d7b24)
    // C code: lines 40154-40175
    // ========================================================================
    1: {
        name: 'Assault Rifle',
        clipSize: 25, // _DAT_004d7b68 = 0x19 = 25
        damage: 50, // 0x42480000 = 50.0 (C flat damage at struct offset 0x6C)
        fireRate: 8.55, // 1 / 0.117
        shotCooldown: 0.117, // 0x3def9db2 = 0.117
        spread: 0.09, // 0x3db851ec = 0.090
        spreadHeat: 1.2, // 0x3f99999a = 1.200
        projectileSpeed: 1350,
        projectileCount: 1, // _DAT_004d7b8c = 1
        reloadTime: 1.2, // weapon_default_reload_time = 0x3f99999a = 1.2
        muzzleFlashAlpha: 0.6,
        projectileType: ProjectileType.ASSAULT_RIFLE,
        flags: WeaponFlags.AUTOMATIC,
        hudIconId: 1,
        ammoClass: 0, // bullet
        hitRadius: 1.0, // C projectile_spawn default hit_radius
        shotSfxId: SoundId.AUTORIFLE_FIRE, // sfx_autorifle_fire (_DAT_004d7b7c)
        reloadSfxId: SoundId.AUTORIFLE_RELOAD, // sfx_autorifle_reload (_DAT_004d7b84)
    },

    // ========================================================================
    // ID 2: Shotgun (C slot 3, name at 0x004d7ba0 from DAT_0047956c)
    // C code: lines 40177-40204
    // ========================================================================
    2: {
        name: 'Shotgun',
        clipSize: 12, // _DAT_004d7be4 = 0xc = 12
        damage: 60, // 0x42700000 = 60.0 (C flat damage at struct offset 0x6C)
        fireRate: 1.18, // 1 / 0.85
        shotCooldown: 0.85, // 0x3f59999a = 0.85 (shared shotgun cooldown pattern)
        spread: 0.27, // 0x3e8a3d71 = 0.270
        spreadHeat: 1.9, // 0x3ff33333 = 1.900 (C slot 3 struct offset 0x50 at addr 0x4d7bec)
        projectileSpeed: 1050,
        projectileCount: 12, // _DAT_004d7c14 = 0xc = 12
        reloadTime: 1.2, // weapon_default_reload_time = 0x3f99999a = 1.2
        muzzleFlashAlpha: 1.0,
        projectileType: ProjectileType.SHOTGUN,
        flags: WeaponFlags.NONE,
        hudIconId: 2,
        ammoClass: 0, // bullet
        hitRadius: 1.0, // C projectile_spawn default hit_radius
        pelletSpreadMultiplier: 0.0013, // C player.c line 1389: rand()%200-100 * 0.0013
        shotSfxId: SoundId.SHOTGUN_FIRE, // _DAT_004d8434 = sfx_shotgun_fire
        reloadSfxId: SoundId.SHOTGUN_RELOAD, // sfx_reload_default = sfx_shotgun_reload
    },

    // ========================================================================
    // ID 3: Sawed-off Shotgun (C slot 4, name at 0x004d7c1c)
    // C code: lines 40209-40235
    // ========================================================================
    3: {
        name: 'Sawed-off Shotgun',
        clipSize: 12, // _DAT_004d7c60 = 0xc = 12
        damage: 60, // Same pattern as regular Shotgun (C flat damage)
        fireRate: 1.15, // 1 / 0.87
        shotCooldown: 0.87, // 0x3f5eb852 = 0.870
        spread: 0.13, // 0x3e051eb8 = 0.130 (C slot 4 struct offset 0x54 at addr 0x4d7c6c)
        spreadHeat: 1.9, // 0x3ff33333 = 1.900 (C slot 4 struct offset 0x50 at addr 0x4d7c68)
        projectileSpeed: 900,
        projectileCount: 12, // _DAT_004d7c90 = 0xc = 12
        reloadTime: 1.2, // weapon_default_reload_time = 0x3f99999a = 1.2
        muzzleFlashAlpha: 1.0,
        projectileType: ProjectileType.SHOTGUN,
        flags: WeaponFlags.NONE,
        hudIconId: 3,
        ammoClass: 0, // bullet
        hitRadius: 1.0,
        pelletSpreadMultiplier: 0.004,  // C player.c line 1452: rand()%200-100 * 0.004 (wider than regular shotgun)
        shotSfxId: SoundId.SHOTGUN_FIRE, // _DAT_004d7c74 = sfx_shotgun_fire
        reloadSfxId: SoundId.SHOTGUN_RELOAD, // sfx_reload_default
    },

    // ========================================================================
    // ID 4: Jackhammer (C ID 20, name copies to 0x004d83dc)
    // C code: lines 40236-40265
    // Interleaved with Submachine Gun data in decompiled output
    // ========================================================================
    4: {
        name: 'Jackhammer',
        clipSize: 16, // C slot 20 addr 0x4d8420 = 0x10 = 16
        damage: 60, // Shotgun variant pattern (C flat damage)
        fireRate: 7.14, // 1 / 0.14
        shotCooldown: 0.14, // 0x3e0f5c29 = 0.140 (C slot 20 struct offset 0x4C at addr 0x4d8424)
        spread: 0.16, // 0x3e23d70a = 0.160 (C slot 20 struct offset 0x54 at addr 0x4d842c)
        spreadHeat: 3.0, // 0x40400000 = 3.000 (C slot 20 struct offset 0x50 at addr 0x4d8428)
        projectileSpeed: 1050,
        projectileCount: 12, // _DAT_004d7c90 = 0xc = 12
        reloadTime: 1.2, // weapon_default_reload_time = 0x3f99999a = 1.2
        muzzleFlashAlpha: 0.9,
        projectileType: ProjectileType.SHOTGUN,
        flags: WeaponFlags.AUTOMATIC,
        hudIconId: 19, // C slot 20 → hud_icon_id = 19
        ammoClass: 0, // bullet
        hitRadius: 1.0,
        pelletSpreadMultiplier: 0.0013, // C player.c shotgun pattern
        shotSfxId: SoundId.SHOTGUN_FIRE,
        reloadSfxId: SoundId.SHOTGUN_RELOAD,
    },

    // ========================================================================
    // ID 5: Submachine Gun (C ID 5, name copies to 0x004d7c98, data at lines 40267-40284)
    // ========================================================================
    5: {
        name: 'Submachine Gun',
        clipSize: 30, // C slot 5 addr 0x4d7cdc = 0x1e = 30
        damage: 5,
        fireRate: 11.35, // 1 / 0.088
        shotCooldown: 0.088, // 0x3db476b0 = 0.088 (C slot 5 struct offset 0x4C at addr 0x4d7ce0)
        spread: 0.082, // 0x3da7ef9e = 0.082 (C slot 5 struct offset 0x54 at addr 0x4d7ce8)
        spreadHeat: 1.2, // 0x3f99999a = 1.200 (C slot 5 struct offset 0x50 at addr 0x4d7ce4)
        projectileSpeed: 1200,
        projectileCount: 1, // _DAT_004d8444 = 1
        reloadTime: 1.2, // weapon_default_reload_time = 0x3f99999a = 1.2
        muzzleFlashAlpha: 0.5,
        projectileType: ProjectileType.SMG,
        flags: WeaponFlags.AUTOMATIC,
        hudIconId: 4, // C slot 5 → hud_icon_id = 4
        ammoClass: 0, // bullet
        damageScale: 1.0,
        hitRadius: 1.0,
        shotSfxId: SoundId.HRPM_FIRE, // _DAT_004d7cf0 = sfx_hrpm_fire
        reloadSfxId: SoundId.SHOTGUN_RELOAD, // sfx_reload_default
    },

    // ========================================================================
    // ID 6: Flamethrower (C ID 8, name at 0x004d7e0c)
    // C code: lines 40297-40327
    // ========================================================================
    6: {
        name: 'Flamethrower',
        clipSize: 30, // C slot 8 addr 0x4d7e50 = 0x1e = 30
        damage: 3,
        fireRate: 123.3, // 1 / 0.00811
        shotCooldown: 0.00811, // 0x3c04ec63 = 0.00811 (C slot 8 struct offset 0x4C at addr 0x4d7e54)
        spread: 0.015, // 0x3c75c28f = 0.015 (C slot 8 struct offset 0x54 at addr 0x4d7e5c)
        spreadHeat: 2.0, // 0x40000000 = 2.000 (C slot 8 struct offset 0x50 at addr 0x4d7e58)
        projectileSpeed: 90, // C: vel = cos(angle)*1.5 at 60fps ≈ 90px/s (slow flame particles)
        projectileCount: 5, // _DAT_004d7d00 = 5 (fire 5 particles per shot for dense plume)
        reloadTime: 1.2, // weapon_default_reload_time = 0x3f99999a = 1.2
        muzzleFlashAlpha: 0.3,
        projectileType: ProjectileType.FIRE_BULLETS,
        flags: WeaponFlags.AUTOMATIC | WeaponFlags.ENERGY,
        hudIconId: 7, // C slot 8 → hud_icon_id = 7
        ammoClass: 1, // fire
        hitRadius: 1.0,
        ammoCost: 0.1, // C: ammo_cost = 0.1 (300 particles per 30-round clip)
        shotSfxId: SoundId.FLAMER_FIRE_01, // sfx_flamer_fire_01 (_DAT_004d7e64? - see code)
        shotSfxVariantCount: 2, // C: flamer has sfx_flamer_fire_01 and sfx_flamer_fire_02
    },

    // ========================================================================
    // ID 7: Plasma Rifle (C ID 9, name at 0x004d7e88)
    // C code: lines 40328-40357
    // ========================================================================
    7: {
        name: 'Plasma Rifle',
        clipSize: 20, // C slot 9 addr 0x4d7ecc = 0x14 = 20
        damage: 15,
        fireRate: 3.44, // 1 / 0.291
        shotCooldown: 0.291, // 0x3e94e545 = 0.291 (C slot 9 struct offset 0x4C at addr 0x4d7ed0)
        spread: 0.182, // 0x3e3a5e35 = 0.182 (C slot 9 struct offset 0x54 at addr 0x4d7ed8)
        spreadHeat: 1.2, // 0x3f99999a = 1.200 (C slot 9 struct offset 0x50 at addr 0x4d7ed4)
        projectileSpeed: 1500,
        projectileCount: 1, // C case 9: fires 1 PLASMA_RIFLE per shot (_DAT_004d7e68=2 is mode flag)
        reloadTime: 1.2, // weapon_default_reload_time = 0x3f99999a = 1.2
        muzzleFlashAlpha: 0.7,
        projectileType: ProjectileType.PLASMA_RIFLE,
        flags: WeaponFlags.AUTOMATIC | WeaponFlags.ENERGY,
        hudIconId: 8, // C slot 9 → hud_icon_id = 8
        ammoClass: 3, // electric/energy
        damageScale: 8.0, // _DAT_004d7e74 = 8
        hitRadius: 1.0,
        shotSfxId: SoundId.FLAMER_FIRE_01, // sfx_flamer_fire_01 (_DAT_004d7e64)
    },

    // ========================================================================
    // ID 8: Multi-Plasma (C ID 10, name at 0x004d7f04)
    // OFF-BY-ONE FIX: REAL values from weapon_plasma_minigun_* labels
    // (decompiler named after next weapon in init order)
    // ========================================================================
    8: {
        name: 'Multi-Plasma',
        clipSize: 8, // REAL: weapon_plasma_minigun_clip = 8
        damage: 12,
        fireRate: 1.61, // 1 / 0.621
        shotCooldown: 0.621, // REAL: 0x3f1eed84 = 0.621 (from weapon_plasma_minigun_fire_rate)
        spread: 0.32, // REAL: 0x3ea3d70a = 0.320 (from weapon_plasma_minigun_spread)
        spreadHeat: 1.4, // REAL: 0x3fb33333 = 1.400 (from weapon_plasma_minigun_damage)
        projectileSpeed: 1350,
        projectileCount: 3,
        reloadTime: 1.2, // weapon_default_reload_time = 0x3f99999a = 1.2
        muzzleFlashAlpha: 0.8,
        projectileType: ProjectileType.PLASMA_RIFLE,
        flags: WeaponFlags.AUTOMATIC | WeaponFlags.ENERGY,
        hudIconId: 9, // C slot 10 → hud_icon_id = 9
        ammoClass: 3, // electric/energy
        damageScale: 1.4, // REAL: 0x3fb33333 = 1.400
        hitRadius: 1.0,
        shotSfxId: SoundId.SHOCK_FIRE, // sfx_shock_fire
    },

    // ========================================================================
    // ID 9: Plasma Minigun (C ID 11, name at 0x004d7f80)
    // C code: weapon_table[11]
    // DECOMPILER MISATTRIBUTION FIX: The decompiler's weapon_plasma_minigun_*
    // labels are off-by-one — they contain Multi-Plasma's values (clip=8,
    // cooldown=0.621). The REAL Plasma Minigun values are in the
    // weapon_gauss_gun_* labels (clip=30, cooldown=0.110).
    // Verified against gameplay video: fires rapidly (~9 shots/sec) from start.
    // ========================================================================
    9: {
        name: 'Plasma Minigun',
        clipSize: 30, // REAL value: weapon_gauss_gun_clip = 0x1e = 30 (misattributed)
        damage: 8,
        fireRate: 9.09, // 1 / 0.110
        shotCooldown: 0.110, // REAL value: 0x3de147ae = 0.110 (from weapon_gauss_gun_fire_rate)
        spread: 0.097, // REAL value: 0x3dc6a7f0 = 0.097 (from weapon_gauss_gun_spread)
        spreadHeat: 1.3, // REAL value: 0x3fa66666 = 1.300 (from weapon_gauss_gun_damage)
        projectileSpeed: 1350,
        projectileCount: 1, // C default pellet_count=1; dedicated handler fires 1
        reloadTime: 1.2, // weapon_default_reload_time = 0x3f99999a = 1.2
        muzzleFlashAlpha: 0.6,
        projectileType: ProjectileType.PLASMA_MINIGUN,
        flags: WeaponFlags.AUTOMATIC | WeaponFlags.ENERGY,
        hudIconId: 10, // C slot 11 → hud_icon_id = 10
        ammoClass: 3, // electric/energy
        damageScale: 1.3, // REAL value: matches spreadHeat from weapon_gauss_gun_damage
        hitRadius: 1.0,
        shotSfxId: SoundId.PLASMA_MINIGUN_FIRE, // sfx_plasmaminigun_fire
    },

    // ========================================================================
    // ID 10: Gauss Gun (C ID 6, name at 0x004d7d14)
    // OFF-BY-ONE FIX: REAL values from weapon_rocket_launcher_* labels
    // (decompiler named after next weapon in init order)
    // ========================================================================
    10: {
        name: 'Gauss Gun',
        clipSize: 6, // REAL: weapon_rocket_launcher_clip = 6
        damage: 215, // 0x43570000 = 215.0 (C flat damage at struct offset 0x70, _DAT_ verified)
        fireRate: 1.67, // 1 / 0.600
        shotCooldown: 0.6, // REAL: 0x3f19999a = 0.600 (from weapon_rocket_launcher_fire_rate)
        spread: 0.42, // REAL: 0x3ed70a3d = 0.420 (from weapon_rocket_launcher_spread)
        spreadHeat: 1.6, // REAL: 0x3fcccccd = 1.600 (from weapon_rocket_launcher_damage)
        projectileSpeed: 1800,
        projectileCount: 1,
        reloadTime: 1.2, // weapon_default_reload_time = 0x3f99999a = 1.2
        muzzleFlashAlpha: 0.9,
        projectileType: ProjectileType.GAUSS_GUN,
        flags: WeaponFlags.NONE,
        hudIconId: 5, // C slot 6 → hud_icon_id = 5
        ammoClass: 0, // bullet
        damageScale: 1.6, // REAL: 0x3fcccccd = 1.600
        hitRadius: 1.0,
        shotSfxId: SoundId.GAUSS_FIRE, // sfx_gauss_fire
    },

    // ========================================================================
    // ID 11: Rocket Launcher (C ID 12, name at 0x004d7ffc)
    // OFF-BY-ONE FIX: REAL values from weapon_seeker_rockets_* labels
    // ========================================================================
    11: {
        name: 'Rocket Launcher',
        clipSize: 8, // REAL: weapon_seeker_rockets_clip = 8
        damage: 50,
        fireRate: 1.35, // 1 / 0.741
        shotCooldown: 0.741, // REAL: 0x3f3da5d6 = 0.741 (from weapon_seeker_rockets_fire_rate)
        spread: 0.42, // REAL: 0x3ed70a3d = 0.420 (from weapon_seeker_rockets_spread)
        spreadHeat: 1.2, // REAL: 0x3f99999a = 1.200 (from weapon_seeker_rockets_damage)
        projectileSpeed: 750,
        projectileCount: 1, // C dedicated handler fires 1 rocket
        reloadTime: 1.2, // weapon_default_reload_time = 0x3f99999a = 1.2
        muzzleFlashAlpha: 1.0,
        projectileType: ProjectileType.ROCKET,
        flags: WeaponFlags.NONE,
        hudIconId: 11,
        ammoClass: 2, // rocket
        hitRadius: 8.0, // C: creature_find_in_radius(pos, 8.0, 0) for rocket collision
        damageScale: 1.2, // REAL: 0x3f99999a = 1.200
        shotSfxId: SoundId.ROCKET_FIRE,
        reloadSfxId: SoundId.AUTORIFLE_RELOAD_ALT, // weapon_seeker_rockets_sfx_reload
    },

    // ========================================================================
    // ID 12: Seeker Rockets (C ID 13, name at 0x004d8078)
    // OFF-BY-ONE FIX: REAL values from weapon_mean_minigun_* labels
    // ========================================================================
    12: {
        name: 'Seeker Rockets',
        clipSize: 8, // REAL: weapon_mean_minigun_clip = 8
        damage: 45,
        fireRate: 3.22, // 1 / 0.311
        shotCooldown: 0.311, // REAL: 0x3e9f22b6 = 0.311 (from weapon_mean_minigun_fire_rate)
        spread: 0.32, // REAL: 0x3ea3d70a = 0.320 (from weapon_mean_minigun_spread)
        spreadHeat: 1.2, // REAL: 0x3f99999a = 1.200 (from weapon_mean_minigun_damage)
        projectileSpeed: 600,
        projectileCount: 5, // weapon_mean_minigun_type = 2 is projectile type, C handler fires 5
        reloadTime: 1.2, // weapon_default_reload_time = 0x3f99999a = 1.2
        muzzleFlashAlpha: 1.0,
        projectileType: ProjectileType.SEEKER_ROCKET,
        flags: WeaponFlags.NONE,
        hudIconId: 12,
        ammoClass: 2, // rocket
        damageScale: 1.2,
        hitRadius: 8.0, // C: creature_find_in_radius(pos, 8.0, 0) for rocket collision
        shotSfxId: SoundId.ROCKET_FIRE, // sfx_rocket_fire
        reloadSfxId: SoundId.AUTORIFLE_RELOAD_ALT, // weapon_mean_minigun_sfx_reload
    },

    // ========================================================================
    // ID 13: Mean Minigun (C ID 7, name at 0x004d7d90)
    // OFF-BY-ONE FIX: REAL values from weapon_plasma_shotgun_* labels
    // ========================================================================
    13: {
        name: 'Mean Minigun',
        clipSize: 120, // REAL: weapon_plasma_shotgun_clip = 0x78 = 120
        damage: 6,
        fireRate: 11.11, // 1 / 0.090
        shotCooldown: 0.09, // REAL: 0x3db851ec = 0.090 (from weapon_plasma_shotgun_fire_rate)
        spread: 0.062, // REAL: 0x3d7df3b6 = 0.062 (from weapon_plasma_shotgun_spread)
        spreadHeat: 4.0, // REAL: 0x40800000 = 4.000 (from weapon_plasma_shotgun_damage)
        projectileSpeed: 1350,
        projectileCount: 1, // C dedicated handler fires 14 projectiles
        reloadTime: 1.2, // weapon_default_reload_time = 0x3f99999a = 1.2
        muzzleFlashAlpha: 0.5,
        projectileType: ProjectileType.MINIGUN,
        flags: WeaponFlags.AUTOMATIC,
        hudIconId: 6, // C slot 7 → hud_icon_id = 6
        ammoClass: 0, // bullet
        damageScale: 4.0, // REAL: 0x40800000 = 4.000
        hitRadius: 1.0,
        shotSfxId: SoundId.AUTORIFLE_FIRE, // weapon_plasma_shotgun_sfx_fire = sfx_autorifle_fire
        reloadSfxId: SoundId.AUTORIFLE_RELOAD_ALT,
    },

    // ========================================================================
    // ID 14: Plasma Shotgun (C ID 14, name at 0x004d80f4)
    // OFF-BY-ONE FIX: REAL values from weapon_blow_torch_* labels
    // ========================================================================
    14: {
        name: 'Plasma Shotgun',
        clipSize: 14, // REAL: weapon_blow_torch_clip = 0xe = 14
        damage: 10,
        fireRate: 2.08, // 1 / 0.480
        shotCooldown: 0.48, // REAL: 0x3ef5c28f = 0.480 (from weapon_blow_torch_fire_rate)
        spread: 0.11, // REAL: 0x3de147ae = 0.110 (from weapon_blow_torch_spread)
        spreadHeat: 3.1, // REAL: 0x40466666 = 3.100 (from weapon_blow_torch_damage)
        projectileSpeed: 1200,
        projectileCount: 3, // weapon_blow_torch_type = 8 is weapon category; C handler fires 3
        reloadTime: 1.2, // weapon_default_reload_time = 0x3f99999a = 1.2
        muzzleFlashAlpha: 0.8,
        projectileType: ProjectileType.PLASMA_RIFLE,
        flags: WeaponFlags.AUTOMATIC | WeaponFlags.ENERGY,
        hudIconId: 13, // C slot 14 → hud_icon_id = 13
        ammoClass: 3, // electric/energy
        damageScale: 3.1, // REAL: 0x40466666 = 3.100
        hitRadius: 1.0,
        shotSfxId: SoundId.PLASMA_SHOTGUN_FIRE, // weapon_blow_torch_sfx_fire = sfx_plasmashotgun_fire
    },

    // ========================================================================
    // ID 15: Blow Torch (C ID 15, name at 0x004d816c)
    // OFF-BY-ONE FIX: REAL values from weapon_hr_flamer_* labels
    // ========================================================================
    15: {
        name: 'Blow Torch',
        clipSize: 30, // REAL: weapon_hr_flamer_clip = 0x1e = 30
        damage: 4,
        fireRate: 163.93, // 1 / 0.0061
        shotCooldown: 0.0061, // REAL: 0x3bc84f90 = 0.0061 (from weapon_hr_flamer_fire_rate)
        spread: 0.01, // REAL: 0x3c23d70a = 0.010 (from weapon_hr_flamer_spread)
        spreadHeat: 1.5, // REAL: 0x3fc00000 = 1.500 (from weapon_hr_flamer_damage)
        projectileSpeed: 90, // C: vel = cos(angle)*1.5 at 60fps ≈ 90px/s (slow flame particles)
        projectileCount: 1, // weapon_hr_flamer_mode = 2, fire 1 particle per shot
        reloadTime: 1.2, // weapon_default_reload_time = 0x3f99999a = 1.2
        muzzleFlashAlpha: 0.4,
        projectileType: ProjectileType.FIRE_BULLETS,
        flags: WeaponFlags.AUTOMATIC | WeaponFlags.ENERGY,
        hudIconId: 14, // C slot 15 → hud_icon_id = 14
        ammoClass: 1, // fire
        hitRadius: 1.0,
        damageScale: 1.5, // REAL: 0x3fc00000 = 1.500
        ammoCost: 0.1, // C: ammo_cost = 0.1 (300 particles per 30-round clip)
        shotSfxId: SoundId.FLAMER_FIRE_01, // weapon_hr_flamer_sfx_fire = sfx_flamer_fire_01
        shotSfxVariantCount: 2, // C: flamer has sfx_flamer_fire_01 and sfx_flamer_fire_02
        reloadSfxId: SoundId.SHOTGUN_RELOAD, // sfx_reload_default
    },

    // ========================================================================
    // ID 16: HR Flamer (C data at lines 40599-40618)
    // ========================================================================
    16: {
        name: 'HR Flamer',
        clipSize: 30, // C slot 16 addr 0x4d8230 = 0x1e = 30
        damage: 5,
        fireRate: 117.65, // 1 / 0.0085
        shotCooldown: 0.0085, // 0x3c0b4396 = 0.0085 (C slot 16 struct offset 0x4C at addr 0x4d8234)
        spread: 0.01, // 0x3c23d70a = 0.010 (C slot 16 struct offset 0x54 at addr 0x4d823c)
        spreadHeat: 1.8, // 0x3fe66666 = 1.800 (C slot 16 struct offset 0x50 at addr 0x4d8238)
        projectileSpeed: 90, // C: vel = cos(angle)*1.5 at 60fps ≈ 90px/s (slow flame particles)
        projectileCount: 1, // weapon_hr_flamer_mode = 2, but fire 1 particle per shot
        reloadTime: 1.2, // weapon_default_reload_time = 0x3f99999a = 1.2
        muzzleFlashAlpha: 0.3,
        projectileType: ProjectileType.FIRE_BULLETS,
        flags: WeaponFlags.AUTOMATIC | WeaponFlags.ENERGY,
        hudIconId: 15, // C slot 16 → hud_icon_id = 15
        ammoClass: 1, // fire
        damageScale: 1.8, // C slot 16 offset 0x50 = 0x3fe66666 = 1.800
        hitRadius: 1.0,
        ammoCost: 0.1, // C: ammo_cost = 0.1 (300 particles per 30-round clip)
        shotSfxId: SoundId.FLAMER_FIRE_01, // weapon_hr_flamer_sfx_fire = sfx_flamer_fire_01
        shotSfxVariantCount: 2, // C: shares the flamer_fire_01/02 variant pair
    },

    // ========================================================================
    // ID 17: Mini Rocket Swarmers (C data at lines 40631-40650)
    // ========================================================================
    17: {
        name: 'Mini Rocket Swarmers',
        clipSize: 5, // C slot 17 addr 0x4d82ac = 5
        damage: 20,
        fireRate: 0.556, // 1 / 1.8
        shotCooldown: 1.8, // 0x3fe66666 = 1.800 (C slot 17 struct offset 0x4C at addr 0x4d82b0)
        spread: 0.12, // 0x3df5c28f = 0.120 (C slot 17 struct offset 0x54 at addr 0x4d82b8 — see _DAT_004d82b8 not found, using weapon_autogun_spread)
        spreadHeat: 1.8, // 0x3fe66666 (C slot 17 struct offset 0x50 at addr 0x4d82b4)
        projectileSpeed: 540,
        projectileCount: 2, // _DAT_004d8248 = 2
        reloadTime: 1.2, // weapon_default_reload_time = 0x3f99999a = 1.2
        muzzleFlashAlpha: 0.7,
        projectileType: ProjectileType.SEEKER_ROCKET,
        flags: WeaponFlags.AUTOMATIC,
        hudIconId: 16, // C slot 17 → hud_icon_id = 16
        ammoClass: 2, // rocket
        hitRadius: 1.0,
        shotSfxId: SoundId.FLAMER_FIRE_01, // _DAT_004d8244 = sfx_flamer_fire_01
    },

    // ========================================================================
    // ID 18: Rocket Minigun (C data at lines 40664-40681)
    // ========================================================================
    18: {
        name: 'Rocket Minigun',
        clipSize: 16, // weapon_pulse_gun_clip = 0x10 = 16 (misnamed; actually W18 clip at slot 18 offset 0x48)
        damage: 35,
        fireRate: 8.33, // 1 / 0.12
        shotCooldown: 0.12, // 0x3df5c28f = 0.120 (C weapon_table offset 0x4C for weapon 18)
        spread: 0.12, // 0x3df5c28f = 0.120
        spreadHeat: 1.8, // 0x3fe66666 = 1.800
        projectileSpeed: 660,
        projectileCount: 1, // C dedicated handler fires 1 rocket per shot (pellet_count=8 in table unused)
        reloadTime: 1.2, // weapon_default_reload_time = 0x3f99999a = 1.2
        muzzleFlashAlpha: 0.9,
        projectileType: ProjectileType.ROCKET_MINIGUN,
        flags: WeaponFlags.AUTOMATIC,
        hudIconId: 17, // C slot 18 → hud_icon_id = 17
        ammoClass: 2, // rocket
        damageScale: 1.8, // weapon_autogun_damage = 0x3fe66666 = 1.800
        hitRadius: 8.0, // C: creature_find_in_radius(pos, 8.0, 0) for rocket collision
        shotSfxId: SoundId.ROCKET_FIRE, // _DAT_004d82c0 = sfx_rocket_fire
        reloadSfxId: SoundId.AUTORIFLE_RELOAD_ALT, // _DAT_004d82c8
    },

    // ========================================================================
    // ID 19: Pulse Gun (C weapon slot 19, struct base 0x004d835C)
    // NOTE: Decompiler globals labeled "weapon_ion_rifle_*" are actually at
    // THIS weapon's struct offsets (off-by-one misattribution pattern).
    // ========================================================================
    19: {
        name: 'Pulse Gun',
        clipSize: 16, // weapon_ion_rifle_clip = 0x10 = 16 (actually W19's clip_size)
        damage: 18,
        fireRate: 10.0, // 1 / 0.100
        shotCooldown: 0.1, // weapon_ion_rifle_fire_rate = 0x3dcccccd = 0.100 (actually W19's shot_cooldown)
        spread: 0.0, // weapon_ion_rifle_spread = 0 (actually W19's spread)
        spreadHeat: 0.1, // 0x3dcccccd = 0.100 (W19 struct offset 0x50)
        projectileSpeed: 250, // C: wave crosses screen diagonal (~1000px) in ~4s → 250 px/s
        projectileCount: 2,
        reloadTime: 1.2, // weapon_default_reload_time = 0x3f99999a = 1.2
        muzzleFlashAlpha: 0.7,
        projectileType: ProjectileType.PULSE_GUN,
        flags: WeaponFlags.AUTOMATIC | WeaponFlags.ENERGY,
        hudIconId: 18, // C slot 19 → hud_icon_id = 18
        ammoClass: 3, // electric/energy
        hitRadius: 1.0,
        damageScale: 0.1, // weapon_ion_rifle_damage = 0x3dcccccd = 0.100 (actually W19's damage)
        shotSfxId: SoundId.PULSE_FIRE, // weapon_ion_rifle_sfx_fire = sfx_pulse_fire (actually W19's sfx)
        reloadSfxId: SoundId.AUTORIFLE_RELOAD_ALT,
    },

    // ========================================================================
    // ID 20: Ion Rifle (C weapon slot 21, struct base 0x004d8454)
    // NOTE: Decompiler globals labeled "weapon_ion_minigun_*" are actually at
    // THIS weapon's struct offsets (off-by-one misattribution pattern).
    // ========================================================================
    20: {
        name: 'Ion Rifle',
        clipSize: 8, // weapon_ion_minigun_clip = 8 (actually W21's clip_size)
        damage: 22,
        fireRate: 2.5, // 1 / 0.400
        shotCooldown: 0.4, // weapon_ion_minigun_fire_rate = 0x3ecccccd = 0.400 (actually W21's shot_cooldown)
        spread: 0.112, // weapon_ion_minigun_spread = 0x3de56042 = 0.112 (actually W21's spread)
        spreadHeat: 1.35, // 0x3faccccd = 1.350 (W21 struct offset 0x50)
        projectileSpeed: 1650,
        projectileCount: 1, // C dedicated handler fires 1
        reloadTime: 1.2, // weapon_default_reload_time = 0x3f99999a = 1.2
        muzzleFlashAlpha: 0.8,
        projectileType: ProjectileType.ION_RIFLE,
        flags: WeaponFlags.AUTOMATIC | WeaponFlags.ENERGY,
        hudIconId: 20, // C slot 21 → hud_icon_id = 20
        ammoClass: 3, // electric/energy
        damageScale: 1.35, // weapon_ion_minigun_damage = 0x3faccccd = 1.350 (actually W21's damage)
        hitRadius: 5.0, // C projectile_spawn: hit_radius = 5.0 for ION_RIFLE
        shotSfxId: SoundId.SHOCK_FIRE_ALT, // weapon_ion_minigun_sfx_fire = sfx_shock_fire_alt (actually W21's sfx)
        reloadSfxId: SoundId.SHOCK_RELOAD, // weapon_ion_minigun_sfx_reload (actually W21's sfx)
    },

    // ========================================================================
    // ID 21: Ion Minigun (C weapon slot 22, struct base 0x004d84D0)
    // NOTE: Decompiler globals labeled "weapon_ion_cannon_*" are actually at
    // THIS weapon's struct offsets (off-by-one misattribution pattern).
    // ========================================================================
    21: {
        name: 'Ion Minigun',
        clipSize: 20, // weapon_ion_cannon_clip = 0x14 = 20 (actually W22's clip_size)
        damage: 12,
        fireRate: 10.0, // 1 / 0.100
        shotCooldown: 0.1, // weapon_ion_cannon_fire_rate = 0x3dcccccd = 0.100 (actually W22's shot_cooldown)
        spread: 0.09, // weapon_ion_cannon_spread = 0x3db851ec = 0.090 (actually W22's spread)
        spreadHeat: 1.8, // 0x3fe66666 = 1.800 (W22 struct offset 0x50)
        projectileSpeed: 1500,
        projectileCount: 1, // C default pellet_count=1
        reloadTime: 1.2, // weapon_default_reload_time = 0x3f99999a = 1.2
        muzzleFlashAlpha: 0.7,
        projectileType: ProjectileType.ION_MINIGUN,
        flags: WeaponFlags.AUTOMATIC | WeaponFlags.ENERGY,
        hudIconId: 21, // C slot 22 → hud_icon_id = 21
        ammoClass: 3, // electric/energy
        damageScale: 1.8, // weapon_ion_cannon_damage = 0x3fe66666 = 1.800 (actually W22's damage)
        hitRadius: 3.0, // C projectile_spawn: hit_radius = 3.0 for ION_MINIGUN
        shotSfxId: SoundId.SHOCK_MINIGUN_FIRE, // weapon_ion_cannon_sfx_fire = sfx_shockminigun_fire (actually W22's sfx)
        reloadSfxId: SoundId.SHOCK_RELOAD, // weapon_ion_cannon_sfx_reload (actually W22's sfx)
    },

    // ========================================================================
    // ID 22: Ion Cannon (C weapon slot 23, struct base 0x004d854C)
    // Values from verified _DAT_ assignments at absolute struct addresses.
    // ========================================================================
    22: {
        name: 'Ion Cannon',
        clipSize: 20, // needs verification (no _DAT_ found)
        damage: 15,
        fireRate: 1.0, // 1 / 1.000
        shotCooldown: 1.0, // _DAT_004d8598 = 0x3f800000 = 1.000 (verified struct offset 0x4C)
        spread: 0.68, // _DAT_004d85a0 = 0x3f2e147b = 0.680 (verified struct offset 0x54)
        spreadHeat: 3.0, // _DAT_004d859c = 0x40400000 = 3.000 (verified struct offset 0x50)
        projectileSpeed: 1500,
        projectileCount: 1, // C dedicated handler fires 1
        reloadTime: 1.2, // weapon_default_reload_time = 0x3f99999a = 1.2
        muzzleFlashAlpha: 0.8,
        projectileType: ProjectileType.ION_CANNON,
        flags: WeaponFlags.AUTOMATIC | WeaponFlags.ENERGY,
        hudIconId: 22, // C slot 23 → hud_icon_id = 22
        ammoClass: 3, // electric/energy
        hitRadius: 10.0, // C projectile_spawn: hit_radius = 10.0 for ION_CANNON
        damageScale: 3.0, // _DAT_004d859c field_0x50 (C damage multiplier)
        shotSfxId: SoundId.SHOCK_FIRE_ALT, // _DAT_004d85a8 = sfx_shock_fire_alt (verified)
        reloadSfxId: SoundId.SHOCK_RELOAD, // _DAT_004d85b0 = sfx_shock_reload (verified)
    },

    // ========================================================================
    // ID 23: Ion Shotgun (C data at lines 40829-40834)
    // ========================================================================
    23: {
        name: 'Ion Shotgun',
        clipSize: 10, // C slot 31 addr 0x4d8974 = 10
        damage: 18,
        fireRate: 1.18, // 1 / 0.85
        shotCooldown: 0.85, // 0x3f59999a = 0.850 (C slot 31 offset 0x4C at addr 0x4d8978)
        spread: 0.27, // 0x3e8a3d71 = 0.270 (C slot 31 offset 0x54 at addr 0x4d8980)
        spreadHeat: 1.9, // 0x3ff33333 = 1.900 (C slot 31 offset 0x50 at addr 0x4d897c)
        projectileSpeed: 1200,
        projectileCount: 4, // _DAT_004d854c = 4
        reloadTime: 1.2, // weapon_default_reload_time = 0x3f99999a = 1.2
        muzzleFlashAlpha: 0.8,
        projectileType: ProjectileType.ION_MINIGUN,  // C line 1568: PROJECTILE_TYPE_ION_MINIGUN
        flags: WeaponFlags.ENERGY,
        hudIconId: 30, // C slot 31 → hud_icon_id = 30
        ammoClass: 3, // electric/energy
        hitRadius: 1.0,
        pelletSpreadMultiplier: 0.0026, // C player.c line 1574: rand()%200-100 * 0.0026
        shotSfxId: SoundId.SHOCK_FIRE_ALT, // _DAT_004d85a8 = sfx_shock_fire_alt
        reloadSfxId: SoundId.SHOCK_RELOAD, // _DAT_004d85b0 = sfx_shock_reload
    },

    // ========================================================================
    // ID 24: Gauss Shotgun (C data at lines 40849-40867)
    // ========================================================================
    24: {
        name: 'Gauss Shotgun',
        clipSize: 4, // C slot 30 addr 0x4d88f8 = 4
        damage: 20,
        fireRate: 0.95, // 1 / 1.05
        shotCooldown: 1.05, // 0x3f866666 = 1.050 (C slot 30 offset 0x4C at addr 0x4d88fc)
        spread: 0.27, // 0x3e8a3d71 = 0.270 (C slot 30 offset 0x54 at addr 0x4d8904)
        spreadHeat: 2.1, // 0x40066666 = 2.100 (C slot 30 offset 0x50 at addr 0x4d8900)
        projectileSpeed: 1500,
        projectileCount: 8, // _DAT_004d89a4 = 8
        reloadTime: 1.2, // weapon_default_reload_time = 0x3f99999a = 1.2
        muzzleFlashAlpha: 0.9,
        projectileType: ProjectileType.GAUSS_GUN,
        flags: WeaponFlags.NONE,
        hudIconId: 29, // C slot 30 → hud_icon_id = 29
        ammoClass: 0, // bullet
        hitRadius: 1.0,
        pelletSpreadMultiplier: 0.002,  // C player.c line 1615: rand()%200-100 * 0.002
        shotSfxId: SoundId.GAUSS_FIRE, // _DAT_004d890c? = sfx_gauss_fire
        reloadSfxId: SoundId.SHOCK_RELOAD, // _DAT_004d8990 = sfx_shock_reload
    },

    // ========================================================================
    // ID 25: Plasma Cannon (C data at lines 40882-40899)
    // ========================================================================
    25: {
        name: 'Plasma Cannon',
        clipSize: 3, // C slot 28 addr 0x4d8800 = 3
        damage: 30,
        fireRate: 1.11, // 1 / 0.9
        shotCooldown: 0.9, // 0x3f666666 = 0.900 (C slot 28 offset 0x4C at addr 0x4d8804)
        spread: 0.6, // 0x3f19999a = 0.600 (C slot 28 offset 0x54 at addr 0x4d880c)
        spreadHeat: 2.7, // 0x402ccccd = 2.700 (C slot 28 offset 0x50 at addr 0x4d8808)
        projectileSpeed: 1200,
        projectileCount: 1, // _DAT_004d891c = 1
        reloadTime: 1.2, // weapon_default_reload_time = 0x3f99999a = 1.2
        muzzleFlashAlpha: 0.9,
        projectileType: ProjectileType.PLASMA_CANNON,
        flags: WeaponFlags.ENERGY,
        hudIconId: 27, // C slot 28 → hud_icon_id = 27
        ammoClass: 3, // electric/energy
        hitRadius: 10.0, // C projectile_spawn: hit_radius = 10.0 for PLASMA_CANNON
        damageScale: 1.22, // weapon_plasma_cannon_damage = 0x3f9c28f6 = 1.220
        shotSfxId: SoundId.SHOCK_FIRE, // _DAT_004d8814 = sfx_shock_fire
        reloadSfxId: SoundId.SHOTGUN_RELOAD, // _DAT_004d8914 = sfx_reload_default
    },

    // ========================================================================
    // ID 26: Evil Scythe (C data at lines 40915-40929)
    // ========================================================================
    26: {
        name: 'Evil Scythe',
        clipSize: 3, // _DAT_004d8800 = 3
        damage: 25,
        fireRate: 1.0, // 1 / 1.0
        shotCooldown: 1.0, // 0x3f800000 = 1.000 (C slot 27 offset 0x4C at addr 0x4d8788)
        spread: 0.68, // 0x3f2e147b = 0.680 (C slot 27 offset 0x54 at addr 0x4d8790)
        spreadHeat: 3.0, // 0x40400000 = 3.000 (C slot 27 offset 0x50 at addr 0x4d878c)
        projectileSpeed: 1050,
        projectileCount: 25, // _DAT_004d8820 = 0x19 = 25
        reloadTime: 1.2, // weapon_default_reload_time = 0x3f99999a = 1.2
        muzzleFlashAlpha: 0.8,
        projectileType: ProjectileType.BLADE_GUN,
        flags: WeaponFlags.NONE,
        hudIconId: 26, // C slot 27 → hud_icon_id = 26
        ammoClass: 3, // electric/energy
        hitRadius: 1.0,
        shotSfxId: SoundId.SHOCK_FIRE_ALT, // _DAT_004d8798 - context suggests shock_fire_alt
        reloadSfxId: SoundId.SHOCK_RELOAD, // _DAT_004d881c = sfx_shock_reload
    },

    // ========================================================================
    // ID 27: Flameburst (C data at lines 40944-40960)
    // ========================================================================
    27: {
        name: 'Flameburst',
        clipSize: 60, // C slot 32 addr 0x4d89f0 = 0x3c = 60
        damage: 15,
        fireRate: 50.0, // 1 / 0.02
        shotCooldown: 0.02, // 0x3ca3d70a = 0.020 (C slot 32 offset 0x4C at addr 0x4d89f4)
        spread: 0.18, // 0x3e3851ec = 0.180 (C slot 32 offset 0x54 at addr 0x4d89fc)
        spreadHeat: 3.0, // 0x40400000 = 3.000
        projectileSpeed: 120, // Slightly faster burst, but still slow flame particles
        projectileCount: 4, // _DAT_004d873c = 4
        reloadTime: 1.2, // weapon_default_reload_time = 0x3f99999a = 1.2
        muzzleFlashAlpha: 0.7,
        projectileType: ProjectileType.FIRE_BULLETS,
        flags: WeaponFlags.ENERGY,
        hudIconId: 31, // C slot 32 → hud_icon_id = 31
        ammoClass: 1, // fire
        hitRadius: 1.0,
        ammoCost: 0.1, // Fire weapon fractional ammo
        shotSfxId: SoundId.SHOCK_FIRE_ALT,
        reloadSfxId: SoundId.SHOCK_RELOAD, // _DAT_004d87a0 = sfx_shock_reload
    },

    // ========================================================================
    // ID 28: Splitter Gun (C data at lines 41006-41013)
    // ========================================================================
    28: {
        name: 'Splitter Gun',
        clipSize: 6, // C slot 29 addr 0x4d887c = 6
        damage: 15,
        fireRate: 1.43, // 1 / 0.70
        shotCooldown: 0.7, // 0x3f333333 = 0.700 (C slot 29 offset 0x4C at addr 0x4d8880)
        spread: 0.28, // 0x3e8f5c29 = 0.280 (C slot 29 offset 0x54 at addr 0x4d8888)
        spreadHeat: 2.2, // 0x400ccccd = 2.200 (C slot 29 offset 0x50 at addr 0x4d8884)
        projectileSpeed: 1200,
        projectileCount: 4, // _DAT_004d8a24 = 4
        reloadTime: 1.2, // weapon_default_reload_time = 0x3f99999a = 1.2
        muzzleFlashAlpha: 0.8,
        projectileType: ProjectileType.SPLITTER_GUN,
        flags: WeaponFlags.NONE,
        hudIconId: 28, // C slot 29 → hud_icon_id = 28
        ammoClass: 3, // electric/energy
        hitRadius: 1.0,
        shotSfxId: SoundId.SHOCK_FIRE_ALT, // _DAT_004d8a80 = sfx_shock_fire_alt
        reloadSfxId: SoundId.SHOCK_RELOAD, // _DAT_004d8a88 = sfx_shock_reload
    },

    // ========================================================================
    // ID 29: Shrinkifier 5k (C data at lines 41037-41054)
    // ========================================================================
    29: {
        name: 'Shrinkifier 5k',
        clipSize: 12, // C slot 29 overflow: _DAT_004d8a6c = 0xc = 12 at Splitter's old addr
        damage: 20,
        fireRate: 1.43, // 1 / 0.70
        shotCooldown: 0.7, // 0x3f333333 = 0.700
        spread: 0.28, // 0x3e8f5c29 = 0.280
        spreadHeat: 2.2, // 0x400ccccd = 2.200
        projectileSpeed: 1200,
        projectileCount: 1,
        reloadTime: 1.2, // weapon_default_reload_time = 0x3f99999a = 1.2
        muzzleFlashAlpha: 0.8,
        projectileType: ProjectileType.SHRINKIFIER,
        flags: WeaponFlags.NONE,
        hudIconId: 23, // C slot 24 → hud_icon_id = 23
        ammoClass: 3, // electric/energy
        damageScale: 6.0, // _DAT_004d88a8 = 0x40c00000 = 6.0
        hitRadius: 1.0,
        shotSfxId: SoundId.SHOCK_FIRE_ALT, // _DAT_004d8890 = sfx_shock_fire_alt
        reloadSfxId: SoundId.SHOCK_RELOAD, // _DAT_004d8898 = sfx_shock_reload
    },

    // ========================================================================
    // ID 30: Blade Gun (C data at lines 41069-41085)
    // ========================================================================
    30: {
        name: 'Blade Gun',
        clipSize: 8, // weapon_plasma_cannon_clip = 8
        damage: 18,
        fireRate: 4.76, // 1 / 0.210
        shotCooldown: 0.21, // 0x3e570a3d = 0.210
        spread: 0.04, // 0x3d23d70a = 0.040
        spreadHeat: 1.22, // 0x3f9c28f6 = 1.220
        projectileSpeed: 1350,
        projectileCount: 23, // weapon_plasma_cannon_projectile_type = 0x17 = 23
        reloadTime: 1.2, // weapon_default_reload_time = 0x3f99999a = 1.2
        muzzleFlashAlpha: 0.8,
        projectileType: ProjectileType.BLADE_GUN,
        flags: WeaponFlags.AUTOMATIC | WeaponFlags.ENERGY,
        hudIconId: 24, // C slot 25 → hud_icon_id = 24
        ammoClass: 3, // electric/energy
        hitRadius: 1.0,
        shotSfxId: SoundId.SHOCK_FIRE_ALT, // weapon_plasma_cannon_sfx_fire
        reloadSfxId: SoundId.SHOCK_RELOAD, // weapon_plasma_cannon_sfx_reload
    },

    // ========================================================================
    // ID 31: Plague Spreader Gun (C data at lines 41100-41115)
    // ========================================================================
    31: {
        name: 'Plague Spreader Gun',
        clipSize: 6, // weapon_plague_spreader_clip = 6
        damage: 22,
        fireRate: 2.86, // 1 / 0.35
        shotCooldown: 0.35, // 0x3eb33333 = 0.350
        spread: 0.04, // 0x3d23d70a = 0.040
        spreadHeat: 3.5, // 0x40600000 = 3.500
        projectileSpeed: 1050,
        projectileCount: 24, // weapon_plague_spreader_projectile_type = 0x18 = 24
        reloadTime: 1.2, // weapon_default_reload_time = 0x3f99999a = 1.2
        muzzleFlashAlpha: 0.7,
        projectileType: ProjectileType.PLAGUE_SPREADER,
        flags: WeaponFlags.ENERGY,
        hudIconId: 40, // C slot 41 → hud_icon_id = 40
        ammoClass: 3, // electric/energy
        hitRadius: 1.0,
        damageScale: 3.5, // weapon_plague_spreader_damage = 0x40600000 = 3.500
        shotSfxId: SoundId.BLOOD_SPILL_01, // sfx_bloodspill_01
    },

    // ========================================================================
    // ID 32: Rainbow Gun (C data at lines 41128-41145)
    // ========================================================================
    32: {
        name: 'Rainbow Gun',
        clipSize: 5, // weapon_rainbow_gun_clip = 5
        damage: 15,
        fireRate: 5.0, // 1 / 0.200
        shotCooldown: 0.2, // 0x3e4ccccd = 0.200
        spread: 0.04, // 0x3d23d70a = 0.040
        spreadHeat: 1.2, // 0x3f99999a = 1.200
        projectileSpeed: 1200,
        projectileCount: 1,
        reloadTime: 1.2, // weapon_default_reload_time = 0x3f99999a = 1.2
        muzzleFlashAlpha: 0.7,
        projectileType: ProjectileType.PLASMA_RIFLE,
        flags: WeaponFlags.ENERGY,
        hudIconId: 42, // C slot 43 → hud_icon_id = 42
        ammoClass: 3, // electric/energy
        hitRadius: 1.0,
        damageScale: 1.2, // weapon_rainbow_gun_damage = 0x3f99999a = 1.200
        shotSfxId: SoundId.BLOOD_SPILL_01, // weapon_rainbow_gun_sfx_fire = sfx_bloodspill_01
        reloadSfxId: SoundId.SHOTGUN_RELOAD, // weapon_rainbow_gun_sfx_reload = sfx_reload_default
    },

    // ========================================================================
    // ID 33: Grim Weapon (C data at lines 41159-41175)
    // ========================================================================
    33: {
        name: 'Grim Weapon',
        clipSize: 10, // weapon_grim_clip = 10
        damage: 20,
        fireRate: 5.0, // 1 / 0.200
        shotCooldown: 0.2, // 0x3e4ccccd = 0.200
        spread: 0.09, // 0x3db851ec = 0.090
        spreadHeat: 1.2, // 0x3f99999a = 1.200
        projectileSpeed: 1350,
        projectileCount: 1,
        reloadTime: 1.2, // weapon_default_reload_time = 0x3f99999a = 1.2
        muzzleFlashAlpha: 0.8,
        projectileType: ProjectileType.PLASMA_CANNON,
        flags: WeaponFlags.ENERGY,
        hudIconId: 43, // C slot 44 → hud_icon_id = 43
        ammoClass: 3, // electric/energy
        hitRadius: 1.0,
        damageScale: 1.2, // weapon_grim_damage = 0x3f99999a = 1.200
        shotSfxId: SoundId.BLOOD_SPILL_01, // weapon_grim_sfx_fire = sfx_bloodspill_01
        reloadSfxId: SoundId.SHOTGUN_RELOAD, // weapon_grim_sfx_reload = sfx_reload_default
    },

    // ========================================================================
    // ID 34: Bubblegun (C data at lines 41189-41204)
    // ========================================================================
    34: {
        name: 'Bubblegun',
        clipSize: 15, // C slot 42 addr 0x4d8ec8 = 0xf = 15
        damage: 10,
        fireRate: 6.21, // 1 / 0.161
        shotCooldown: 0.161, // 0x3e252bd4 = 0.161 (C slot 42 offset 0x4C at addr 0x4d8ecc)
        spread: 0.05, // 0x3d4ccccd = 0.050 (C slot 42 offset 0x54 at addr 0x4d8ed4)
        spreadHeat: 1.2, // 0x3f99999a = 1.200 (C slot 42 offset 0x50 at addr 0x4d8ed0)
        projectileSpeed: 900,
        projectileCount: 1,
        reloadTime: 1.2, // weapon_default_reload_time = 0x3f99999a = 1.2
        muzzleFlashAlpha: 0.5,
        projectileType: ProjectileType.PLASMA_RIFLE,
        flags: WeaponFlags.ENERGY,
        hudIconId: 41, // C slot 42 → hud_icon_id = 41
        ammoClass: 3, // electric/energy
        hitRadius: 1.0,
        damageScale: 1.2, // weapon_bubblegun_damage = 0x3f99999a = 1.200
        shotSfxId: SoundId.BLOOD_SPILL_01, // weapon_bubblegun_sfx_fire = sfx_bloodspill_01
        reloadSfxId: SoundId.SHOTGUN_RELOAD, // weapon_bubblegun_sfx_reload = sfx_reload_default
    },

    // ========================================================================
    // ID 35: Spider Plasma (C data at lines 41218-41234)
    // ========================================================================
    35: {
        name: 'Spider Plasma',
        clipSize: 5, // C slot 26 addr 0x4d8708 = 5
        damage: 10,
        fireRate: 5.0, // 1 / 0.2
        shotCooldown: 0.2, // 0x3e4ccccd = 0.200 (C slot 26 offset 0x4C at addr 0x4d870c)
        spread: 0.04, // 0x3d23d70a = 0.040 (C slot 26 offset 0x54 at addr 0x4d8714)
        spreadHeat: 1.2, // 0x3f99999a = 1.200 (C slot 26 offset 0x50 at addr 0x4d8710)
        projectileSpeed: 1050,
        projectileCount: 8, // _DAT_004d8eec = 8
        reloadTime: 1.2, // weapon_default_reload_time = 0x3f99999a = 1.2
        muzzleFlashAlpha: 0.6,
        projectileType: ProjectileType.SPIDER_PLASMA,
        flags: WeaponFlags.AUTOMATIC | WeaponFlags.ENERGY,
        hudIconId: 25, // C slot 26 → hud_icon_id = 25
        ammoClass: 3, // electric/energy
        hitRadius: 1.0,
        shotSfxId: SoundId.BLOOD_SPILL_01, // _DAT_004d8edc = sfx_bloodspill_01
        reloadSfxId: SoundId.SHOTGUN_RELOAD, // _DAT_004d8ee4 = sfx_reload_default
    },

    // ========================================================================
    // ID 36: Transmutator (C data at lines 41248-41264)
    // ========================================================================
    36: {
        name: 'Transmutator',
        clipSize: 50, // C slot 50 addr 0x4d92a8 = 0x32 = 50
        damage: 15,
        fireRate: 25.0, // 1 / 0.04
        shotCooldown: 0.04, // 0x3d23d70a = 0.040 (C slot 50 offset 0x4C at addr 0x4d92ac)
        spread: 0.04, // 0x3d23d70a = 0.040 (C slot 50 offset 0x54 at addr 0x4d92b4)
        spreadHeat: 5.0, // 0x40a00000 = 5.000 (C slot 50 offset 0x50 at addr 0x4d92b0)
        projectileSpeed: 1200,
        projectileCount: 8, // _DAT_004d872c = 8
        reloadTime: 1.2, // weapon_default_reload_time = 0x3f99999a = 1.2
        muzzleFlashAlpha: 0.7,
        projectileType: ProjectileType.PLASMA_RIFLE,
        flags: WeaponFlags.ENERGY,
        hudIconId: 49, // C slot 50 → hud_icon_id = 49
        ammoClass: 3, // electric/energy
        hitRadius: 1.0,
        shotSfxId: SoundId.BLOOD_SPILL_01, // _DAT_004d871c = sfx_bloodspill_01
        reloadSfxId: SoundId.SHOTGUN_RELOAD, // _DAT_004d8724 = sfx_reload_default
    },

    // ========================================================================
    // ID 37: Blaster R-300 (C data at lines 41278-41293)
    // ========================================================================
    37: {
        name: 'Blaster R-300',
        clipSize: 20, // C slot 51 addr 0x4d9324 = 0x14 = 20
        damage: 15,
        fireRate: 12.5, // 1 / 0.08
        shotCooldown: 0.08, // 0x3da3d70a = 0.080 (C slot 51 offset 0x4C at addr 0x4d9328)
        spread: 0.05, // 0x3d4ccccd = 0.050 (C slot 51 offset 0x54 at addr 0x4d9330)
        spreadHeat: 2.0, // 0x40000000 = 2.000 (C slot 51 offset 0x50 at addr 0x4d932c)
        projectileSpeed: 1500,
        projectileCount: 9, // _DAT_004d92cc = 9
        reloadTime: 1.2, // weapon_default_reload_time = 0x3f99999a = 1.2
        muzzleFlashAlpha: 0.8,
        projectileType: ProjectileType.ASSAULT_RIFLE,
        flags: WeaponFlags.AUTOMATIC,
        hudIconId: 50, // C slot 51 → hud_icon_id = 50
        ammoClass: 0, // bullet
        hitRadius: 1.0,
        shotSfxId: SoundId.SHOCK_FIRE, // _DAT_004d9338 = sfx_shock_fire(?)
        reloadSfxId: SoundId.SHOTGUN_RELOAD, // _DAT_004d92c4 = sfx_reload_default
    },

    // ========================================================================
    // ID 38: Nuke Launcher (C data at lines 41308-41323)
    // ========================================================================
    38: {
        name: 'Nuke Launcher',
        clipSize: 1, // C slot 53 addr 0x4d941c = 1
        damage: 100,
        fireRate: 0.25, // 1 / 4.0
        shotCooldown: 4.0, // 0x40800000 = 4.000 (C slot 53 offset 0x4C at addr 0x4d9420)
        spread: 1.0, // 0x3f800000 = 1.000 (C slot 53 offset 0x54 at addr 0x4d9428)
        spreadHeat: 8.0, // 0x41000000 = 8.000 (C slot 53 offset 0x50 at addr 0x4d9424)
        projectileSpeed: 900,
        projectileCount: 9, // _DAT_004d9348 = 9
        reloadTime: 1.2, // weapon_default_reload_time = 0x3f99999a = 1.2
        muzzleFlashAlpha: 1.0,
        projectileType: ProjectileType.ROCKET,
        flags: WeaponFlags.NONE,
        hudIconId: 52, // C slot 53 → hud_icon_id = 52
        ammoClass: 2, // rocket
        hitRadius: 1.0,
        shotSfxId: SoundId.EXPLOSION_LARGE, // _DAT_004d93b4 = sfx_explosion_large
        reloadSfxId: SoundId.SHOTGUN_RELOAD, // _DAT_004d9340 = sfx_reload_default
    },

    // ========================================================================
    // ID 39: Lighting Rifle (C data at lines 41337-41371)
    // Note: Two entries - first at lines 41337-41353, second at lines 41366-41371
    // ========================================================================
    39: {
        name: 'Lighting Rifle',
        clipSize: 500, // C slot 52 addr 0x4d93a0 = 500
        damage: 50,
        fireRate: 0.25, // 1 / 4.0
        shotCooldown: 4.0, // 0x40800000 = 4.000
        spread: 1.0, // 0x3f800000 = 1.000
        spreadHeat: 8.0, // 0x41000000 = 8.000
        projectileSpeed: 1500,
        projectileCount: 8, // _DAT_004d9440 = 8
        reloadTime: 1.2, // weapon_default_reload_time = 0x3f99999a = 1.2
        muzzleFlashAlpha: 1.0,
        projectileType: ProjectileType.ION_CANNON,
        flags: WeaponFlags.ENERGY,
        hudIconId: 51, // C slot 52 → hud_icon_id = 51
        ammoClass: 3, // electric/energy
        hitRadius: 1.0,
        shotSfxId: SoundId.EXPLOSION_LARGE, // _DAT_004d9430 = sfx_explosion_large
        reloadSfxId: SoundId.SHOTGUN_RELOAD, // _DAT_004d9438 = sfx_reload_default
    },
};

/**
 * Maps C weapon_id (1-indexed, sparse) to TS weapon_id (0-indexed, dense).
 * Computed from weapon_table base address 0x4d7a2c with 0x7C stride.
 * Verified against name string copy destinations in weapon_table_init (weapons.c).
 */
const C_TO_TS_WEAPON_ID: Record<number, number> = {
    1: 0, // Pistol          (name → DAT_004d7aa8)
    2: 1, // Assault Rifle   (name → DAT_004d7b24)
    3: 2, // Shotgun         (name → DAT_004d7ba0)
    4: 3, // Sawed-off Shotgun (name → DAT_004d7c1c)
    5: 5, // Submachine Gun  (name → DAT_004d7c98)
    6: 10, // Gauss Gun       (name → DAT_004d7d14)
    7: 13, // Mean Minigun    (name → DAT_004d7d90)
    8: 6, // Flamethrower    (name → DAT_004d7e0c)
    9: 7, // Plasma Rifle    (name → DAT_004d7e88)
    10: 8, // Multi-Plasma    (name → DAT_004d7f04)
    11: 9, // Plasma Minigun  (name → DAT_004d7f80)
    12: 11, // Rocket Launcher (name → DAT_004d7ffc)
    13: 12, // Seeker Rockets  (name → DAT_004d8078)
    14: 14, // Plasma Shotgun  (name → DAT_004d80f4)
    15: 15, // Blow Torch      (name → DAT_004d8170)
    16: 16, // HR Flamer       (name → DAT_004d81ec)
    17: 17, // Mini Rocket Swarmers (name → DAT_004d8268)
    18: 18, // Rocket Minigun  (name → DAT_004d82e4)
    19: 19, // Pulse Gun       (name → DAT_004d8360)
    20: 4, // Jackhammer      (name → DAT_004d83dc)
    21: 20, // Ion Rifle       (name → DAT_004d8458)
    22: 21, // Ion Minigun     (name → DAT_004d84d4)
    23: 22, // Ion Cannon      (name → DAT_004d8550)
    24: 29, // Shrinkifier 5k
    25: 30, // Blade Gun
    26: 35, // Spider Plasma
    27: 26, // Evil Scythe
    28: 25, // Plasma Cannon
    29: 28, // Splitter Gun
    30: 24, // Gauss Shotgun
    31: 23, // Ion Shotgun
    32: 27, // Flameburst
    41: 31, // Plague Spreader Gun
    42: 34, // Bubblegun
    43: 32, // Rainbow Gun
    44: 33, // Grim Weapon
    50: 36, // Transmutator
    51: 37, // Blaster R-300
    52: 39, // Lighting Rifle
    53: 38, // Nuke Launcher
};

/**
 * Translate a C weapon_id to the corresponding TS weapon_id.
 * Falls back to 0 (Pistol) for unknown IDs.
 */
export function cWeaponIdToTs(cId: number): number {
    return C_TO_TS_WEAPON_ID[cId] ?? 0;
}

/**
 * Total number of selectable weapons in the random weapon pool.
 * C code: iVar1 % 0x21 + 1 = C weapon IDs 1-33 (33 weapons).
 * In TS space these map to 33 unique TS IDs (0-32 range, non-contiguous).
 */
export const SELECTABLE_WEAPON_COUNT = 33;

/**
 * Get weapon stats by ID
 */
export function getWeaponStats(weaponId: number): WeaponStats {
    return WEAPON_DATA[weaponId] || WEAPON_DATA[0];
}

/**
 * Get total weapon count
 */
export function getWeaponCount(): number {
    return Object.keys(WEAPON_DATA).length;
}
