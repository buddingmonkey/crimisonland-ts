/**
 * SoundId - Enumeration of all sound effect IDs
 *
 * Port of sound IDs from crimsonland.exe_decompiled.c
 * C code reference: audio_init_sfx @ lines 34358-34432
 */

/**
 * Sound effect IDs matching C globals
 * C code reference: sfx_* globals loaded in audio_init_sfx (lines 34358-34432)
 */
export enum SoundId {
    // Player sounds
    TROOPER_INPAIN_01 = 0, // C: sfx_trooper_inpain_01 (line 34358)
    TROOPER_INPAIN_02 = 1, // C: sfx_trooper_inpain_02 (line 34359)
    TROOPER_INPAIN_03 = 2, // C: _sfx_trooper_inpain_03 (line 34360)
    TROOPER_DIE_01 = 3, // C: sfx_trooper_die_01 (line 34361)
    TROOPER_DIE_02 = 4, // C: sfx_trooper_die_02 (line 34362)
    TROOPER_DIE_03 = 5, // C: sfx_trooper_die_03 (line 34363)

    // Zombie enemy sounds
    ZOMBIE_DIE_01 = 6, // C: sfx_zombie_die_01 (line 34364)
    ZOMBIE_DIE_02 = 7, // C: sfx_zombie_die_02 (line 34365)
    ZOMBIE_DIE_03 = 8, // C: sfx_zombie_die_03 (line 34366)
    ZOMBIE_DIE_04 = 9, // C: sfx_zombie_die_04 (line 34367)
    ZOMBIE_ATTACK_01 = 10, // C: sfx_zombie_attack_01 (line 34368)
    ZOMBIE_ATTACK_02 = 11, // C: sfx_zombie_attack_02 (line 34369)

    // Alien enemy sounds
    ALIEN_DIE_01 = 12, // C: sfx_alien_die_01 (line 34370)
    ALIEN_DIE_02 = 13, // C: sfx_alien_die_02 (line 34371)
    ALIEN_DIE_03 = 14, // C: sfx_alien_die_03 (line 34372)
    ALIEN_DIE_04 = 15, // C: sfx_alien_die_04 (line 34373)
    ALIEN_ATTACK_01 = 16, // C: sfx_alien_attack_01 (line 34374)
    ALIEN_ATTACK_02 = 17, // C: sfx_alien_attack_02 (line 34375)

    // Lizard enemy sounds
    LIZARD_DIE_01 = 18, // C: sfx_lizard_die_01 (line 34376)
    LIZARD_DIE_02 = 19, // C: sfx_lizard_die_02 (line 34377)
    LIZARD_DIE_03 = 20, // C: sfx_lizard_die_03 (line 34378)
    LIZARD_DIE_04 = 21, // C: sfx_lizard_die_04 (line 34379)
    LIZARD_ATTACK_01 = 22, // C: sfx_lizard_attack_01 (line 34380)
    LIZARD_ATTACK_02 = 23, // C: sfx_lizard_attack_02 (line 34381)

    // Spider enemy sounds
    SPIDER_DIE_01 = 24, // C: sfx_spider_die_01 (line 34382)
    SPIDER_DIE_02 = 25, // C: sfx_spider_die_02 (line 34383)
    SPIDER_DIE_03 = 26, // C: sfx_spider_die_03 (line 34384)
    SPIDER_DIE_04 = 27, // C: sfx_spider_die_04 (line 34385)
    SPIDER_ATTACK_01 = 28, // C: sfx_spider_attack_01 (line 34386)
    SPIDER_ATTACK_02 = 29, // C: sfx_spider_attack_02 (line 34387)

    // Weapon fire sounds
    PISTOL_FIRE = 30, // C: sfx_pistol_fire (line 34388)
    PISTOL_RELOAD = 31, // C: sfx_pistol_reload (line 34389)
    SHOTGUN_FIRE = 32, // C: sfx_shotgun_fire (line 34390)
    SHOTGUN_RELOAD = 33, // C: sfx_shotgun_reload (line 34391)
    AUTORIFLE_FIRE = 34, // C: sfx_autorifle_fire (line 34392)
    AUTORIFLE_RELOAD = 35, // C: sfx_autorifle_reload (line 34393)
    GAUSS_FIRE = 36, // C: sfx_gauss_fire (line 34394)
    HRPM_FIRE = 37, // C: sfx_hrpm_fire (line 34395)
    SHOCK_FIRE = 38, // C: sfx_shock_fire (line 34396)
    PLASMA_MINIGUN_FIRE = 39, // C: sfx_plasmaminigun_fire (line 34397)
    PLASMA_SHOTGUN_FIRE = 40, // C: sfx_plasmashotgun_fire (line 34398)
    PULSE_FIRE = 41, // C: sfx_pulse_fire (line 34399)
    FLAMER_FIRE_01 = 42, // C: sfx_flamer_fire_01 (line 34400)
    FLAMER_FIRE_02 = 43, // C: sfx_flamer_fire_02 (line 34401)
    SHOCK_RELOAD = 44, // C: sfx_shock_reload (line 34402)
    SHOCK_FIRE_ALT = 45, // C: sfx_shock_fire_alt (line 34403)
    SHOCK_MINIGUN_FIRE = 46, // C: sfx_shockminigun_fire (line 34404)
    ROCKET_FIRE = 47, // C: sfx_rocket_fire (line 34405)
    ROCKET_MINI_FIRE = 48, // C: sfx_rocketmini_fire (line 34406)
    AUTORIFLE_RELOAD_ALT = 49, // C: sfx_autorifle_reload_alt (line 34407)

    // Impact sounds
    BULLET_HIT_01 = 50, // C: sfx_bullet_hit_01 (line 34408)
    BULLET_HIT_02 = 51, // C: _sfx_bullet_hit_02 (line 34409)
    BULLET_HIT_03 = 52, // C: _sfx_bullet_hit_03 (line 34410)
    BULLET_HIT_04 = 53, // C: _sfx_bullet_hit_04 (line 34411)
    BULLET_HIT_05 = 54, // C: _sfx_bullet_hit_05 (line 34412)
    BULLET_HIT_06 = 55, // C: _sfx_bullet_hit_06 (line 34413)
    SHOCK_HIT_01 = 56, // C: sfx_shock_hit_01 (line 34414)

    // Explosion sounds
    EXPLOSION_SMALL = 57, // C: sfx_explosion_small (line 34415)
    EXPLOSION_MEDIUM = 58, // C: sfx_explosion_medium (line 34416)
    EXPLOSION_LARGE = 59, // C: sfx_explosion_large (line 34417)
    SHOCKWAVE = 60, // C: sfx_shockwave (line 34418)

    // Quest/special sounds
    QUEST_HIT = 61, // C: sfx_questhit (line 34419)

    // UI sounds
    UI_BONUS = 62, // C: sfx_ui_bonus (line 34420)
    UI_BUTTON_CLICK = 63, // C: sfx_ui_buttonclick (line 34424)
    UI_PANEL_CLICK = 64, // C: sfx_ui_panelclick (line 34425)
    UI_LEVEL_UP = 65, // C: sfx_ui_levelup (line 34426)
    UI_TYPE_CLICK_01 = 66, // C: _sfx_ui_typeclick_01 (line 34427)
    UI_TYPE_CLICK_02 = 67, // C: _sfx_ui_typeclick_02 (line 34428)
    UI_TYPE_ENTER = 68, // C: sfx_ui_typeenter (line 34429)
    UI_CLINK_01 = 69, // C: sfx_ui_clink_01 (line 34430)

    // Effect sounds
    BLOOD_SPILL_01 = 70, // C: sfx_bloodspill_01 (line 34431)
    BLOOD_SPILL_02 = 71, // C: _sfx_bloodspill_02 (line 34432)
}

/**
 * Get a random death sound for an enemy type
 * C code implicit: randomized enemy death sounds
 *
 * @param baseId First sound ID in the set (e.g., ZOMBIE_DIE_01)
 * @param count Number of variants (e.g., 4 for zombies)
 * @returns Random sound ID from the set
 */
export function getRandomDeathSound(baseId: SoundId, count: number): SoundId {
    return baseId + Math.floor(Math.random() * count);
}

/**
 * Get a random attack sound for an enemy type
 * C code implicit: randomized enemy attack sounds
 */
export function getRandomAttackSound(baseId: SoundId, count: number): SoundId {
    return baseId + Math.floor(Math.random() * count);
}

/**
 * Get a random bullet hit sound
 * C code: randomized bullet hit sounds (sfx_bullet_hit_01-06)
 */
export function getRandomBulletHitSound(): SoundId {
    return SoundId.BULLET_HIT_01 + Math.floor(Math.random() * 6);
}

/**
 * Sound file paths by ID
 * Maps SoundId to the asset path for loading from sfx.paq
 * Note: Paths are filenames only (no sfx/ prefix) as that's how they're stored in the PAQ
 */
export const SOUND_PATHS: Record<SoundId, string> = {
    [SoundId.TROOPER_INPAIN_01]: 'trooper_inPain_01.ogg',
    [SoundId.TROOPER_INPAIN_02]: 'trooper_inPain_02.ogg',
    [SoundId.TROOPER_INPAIN_03]: 'trooper_inPain_03.ogg',
    [SoundId.TROOPER_DIE_01]: 'trooper_die_01.ogg',
    [SoundId.TROOPER_DIE_02]: 'trooper_die_02.ogg',
    [SoundId.TROOPER_DIE_03]: 'trooper_die_03.ogg',
    [SoundId.ZOMBIE_DIE_01]: 'zombie_die_01.ogg',
    [SoundId.ZOMBIE_DIE_02]: 'zombie_die_02.ogg',
    [SoundId.ZOMBIE_DIE_03]: 'zombie_die_03.ogg',
    [SoundId.ZOMBIE_DIE_04]: 'zombie_die_04.ogg',
    [SoundId.ZOMBIE_ATTACK_01]: 'zombie_attack_01.ogg',
    [SoundId.ZOMBIE_ATTACK_02]: 'zombie_attack_02.ogg',
    [SoundId.ALIEN_DIE_01]: 'alien_die_01.ogg',
    [SoundId.ALIEN_DIE_02]: 'alien_die_02.ogg',
    [SoundId.ALIEN_DIE_03]: 'alien_die_03.ogg',
    [SoundId.ALIEN_DIE_04]: 'alien_die_04.ogg',
    [SoundId.ALIEN_ATTACK_01]: 'alien_attack_01.ogg',
    [SoundId.ALIEN_ATTACK_02]: 'alien_attack_02.ogg',
    [SoundId.LIZARD_DIE_01]: 'lizard_die_01.ogg',
    [SoundId.LIZARD_DIE_02]: 'lizard_die_02.ogg',
    [SoundId.LIZARD_DIE_03]: 'lizard_die_03.ogg',
    [SoundId.LIZARD_DIE_04]: 'lizard_die_04.ogg',
    [SoundId.LIZARD_ATTACK_01]: 'lizard_attack_01.ogg',
    [SoundId.LIZARD_ATTACK_02]: 'lizard_attack_02.ogg',
    [SoundId.SPIDER_DIE_01]: 'spider_die_01.ogg',
    [SoundId.SPIDER_DIE_02]: 'spider_die_02.ogg',
    [SoundId.SPIDER_DIE_03]: 'spider_die_03.ogg',
    [SoundId.SPIDER_DIE_04]: 'spider_die_04.ogg',
    [SoundId.SPIDER_ATTACK_01]: 'spider_attack_01.ogg',
    [SoundId.SPIDER_ATTACK_02]: 'spider_attack_02.ogg',
    [SoundId.PISTOL_FIRE]: 'pistol_fire.ogg',
    [SoundId.PISTOL_RELOAD]: 'pistol_reload.ogg',
    [SoundId.SHOTGUN_FIRE]: 'shotgun_fire.ogg',
    [SoundId.SHOTGUN_RELOAD]: 'shotgun_reload.ogg',
    [SoundId.AUTORIFLE_FIRE]: 'autorifle_fire.ogg',
    [SoundId.AUTORIFLE_RELOAD]: 'autorifle_reload.ogg',
    [SoundId.GAUSS_FIRE]: 'gauss_fire.ogg',
    [SoundId.HRPM_FIRE]: 'hrpm_fire.ogg',
    [SoundId.SHOCK_FIRE]: 'shock_fire.ogg',
    [SoundId.PLASMA_MINIGUN_FIRE]: 'plasmaMinigun_fire.ogg',
    [SoundId.PLASMA_SHOTGUN_FIRE]: 'plasmaShotgun_fire.ogg',
    [SoundId.PULSE_FIRE]: 'pulse_fire.ogg',
    [SoundId.FLAMER_FIRE_01]: 'flamer_fire_01.ogg',
    [SoundId.FLAMER_FIRE_02]: 'flamer_fire_02.ogg',
    [SoundId.SHOCK_RELOAD]: 'shock_reload.ogg',
    [SoundId.SHOCK_FIRE_ALT]: 'shock_fire.ogg',
    [SoundId.SHOCK_MINIGUN_FIRE]: 'shockMinigun_fire.ogg',
    [SoundId.ROCKET_FIRE]: 'rocket_fire.ogg',
    [SoundId.ROCKET_MINI_FIRE]: 'rocketmini_fire.ogg',
    [SoundId.AUTORIFLE_RELOAD_ALT]: 'autorifle_reload.ogg',
    [SoundId.BULLET_HIT_01]: 'bullet_hit_01.ogg',
    [SoundId.BULLET_HIT_02]: 'bullet_hit_02.ogg',
    [SoundId.BULLET_HIT_03]: 'bullet_hit_03.ogg',
    [SoundId.BULLET_HIT_04]: 'bullet_hit_04.ogg',
    [SoundId.BULLET_HIT_05]: 'bullet_hit_05.ogg',
    [SoundId.BULLET_HIT_06]: 'bullet_hit_06.ogg',
    [SoundId.SHOCK_HIT_01]: 'shock_hit_01.ogg',
    [SoundId.EXPLOSION_SMALL]: 'explosion_small.ogg',
    [SoundId.EXPLOSION_MEDIUM]: 'explosion_medium.ogg',
    [SoundId.EXPLOSION_LARGE]: 'explosion_large.ogg',
    [SoundId.SHOCKWAVE]: 'shockwave.ogg',
    [SoundId.QUEST_HIT]: 'questHit.ogg',
    [SoundId.UI_BONUS]: 'ui_bonus.ogg',
    [SoundId.UI_BUTTON_CLICK]: 'ui_buttonClick.ogg',
    [SoundId.UI_PANEL_CLICK]: 'ui_panelClick.ogg',
    [SoundId.UI_LEVEL_UP]: 'ui_levelUp.ogg',
    [SoundId.UI_TYPE_CLICK_01]: 'ui_typeClick_01.ogg',
    [SoundId.UI_TYPE_CLICK_02]: 'ui_typeClick_02.ogg',
    [SoundId.UI_TYPE_ENTER]: 'ui_typeEnter.ogg',
    [SoundId.UI_CLINK_01]: 'ui_clink_01.ogg',
    [SoundId.BLOOD_SPILL_01]: 'bloodSpill_01.ogg',
    [SoundId.BLOOD_SPILL_02]: 'bloodSpill_02.ogg',
};
