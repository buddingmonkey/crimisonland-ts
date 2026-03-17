/**
 * QuestDatabase - Quest database, lookup functions
 *
 * Extracted from QuestData.ts
 */

import { QuestMeta, QuestSpawnEntry, EnemyTemplate, PERK_ANTIPERK } from './QuestTypes';
import {
    buildMinorAlienBreach,
    buildTargetPractice,
    buildFrontlineAssault,
    buildTheRandomFactor,
    buildSpiderWaveSyndrome,
    buildAlienSquads,
    build8LeggedTerror,
} from './QuestTier1';
import {
    buildEverredPastures,
    buildTwoFronts,
    buildSweepStakes,
    buildEvilZombiesAtLarge,
    buildSurvivalOfTheFastest,
    buildGhostPatrols,
    buildArachnoidFarm,
} from './QuestTier2';
import {
    buildTheBlighting,
    buildLizardKings,
    buildTheKilling,
    buildSurroundedByReptiles,
    buildTheLizquidation,
    buildSpidersInc,
    buildLizardRaze,
    buildDejaVu,
} from './QuestTier3';
import {
    buildMajorAlienBreach,
    buildZombieTime,
    buildLizardZombiePact,
    buildTheCollaboration,
    buildTheMassacre,
    buildTheUnblitzkrieg,
    buildGauntlet,
    buildSyntaxTerror,
    buildTheAnnihilation,
    buildTheEndOfAll,
} from './QuestTier4';
import {
    buildTheBeating,
    buildTheSpankingOfTheDead,
    buildTheFortress,
    buildTheGangWars,
    buildKneeDeepInTheDead,
    buildMonsterBlues,
    buildNagolipoli,
} from './QuestTier5';

export type { QuestMeta, QuestSpawnEntry };

/**
 * Quest database - all 50 quests
 *
 * C code references:
 * - quest_database_init: lines 31469-31927
 * - Quest builders: lines 28890-31456
 */
export const QUEST_DATABASE: QuestMeta[] = [
    // ========== TIER 1 (lines 31477-31543) ==========

    // Quest 1-1: Land Hostile (C: quest_build_land_hostile, lines 28895-28922)
    {
        id: 0,
        tier: 1,
        index: 1,
        name: 'Land Hostile',
        startWeaponId: 0, // Pistol (C: start_weapon_id=1 → TS 0)
        timeLimitMs: 120000, // 2 minutes
        unlockWeaponId: 1, // Assault Rifle (C: unlock_weapon_id=2 → TS 1)
        unlockPerkId: PERK_ANTIPERK,
        spawns: [
            { triggerTimeMs: 500, posX: 512, posY: 1088, templateId: EnemyTemplate.SPIDER_STANDARD, count: 1 },
            { triggerTimeMs: 2500, posX: -64, posY: 1088, templateId: EnemyTemplate.SPIDER_STANDARD, count: 2 },
            { triggerTimeMs: 6500, posX: -64, posY: -64, templateId: EnemyTemplate.SPIDER_STANDARD, count: 3 },
            { triggerTimeMs: 11500, posX: 1088, posY: -64, templateId: EnemyTemplate.SPIDER_STANDARD, count: 4 },
        ],
    },

    // Quest 1-2: Minor Alien Breach (C: quest_build_minor_alien_breach, lines 28932-29028)
    {
        id: 1,
        tier: 1,
        index: 2,
        name: 'Minor Alien Breach',
        startWeaponId: 0,
        timeLimitMs: 120000,
        unlockWeaponId: 3, // Sawed-off
        unlockPerkId: 0x1c, // First tier perk
        spawns: buildMinorAlienBreach(),
    },

    // Quest 1-3: Target Practice
    {
        id: 2,
        tier: 1,
        index: 3,
        name: 'Target Practice',
        startWeaponId: 0,
        timeLimitMs: 65000,
        unlockWeaponId: 8, // Multi-Plasma
        unlockPerkId: PERK_ANTIPERK,
        spawns: buildTargetPractice(),
    },

    // Quest 1-4: Frontline Assault
    {
        id: 3,
        tier: 1,
        index: 4,
        name: 'Frontline Assault',
        startWeaponId: 0,
        timeLimitMs: 300000,
        unlockWeaponId: 5, // SMG
        unlockPerkId: 0x1d,
        spawns: buildFrontlineAssault(),
    },

    // Quest 1-5: Alien Dens
    {
        id: 4,
        tier: 1,
        index: 5,
        name: 'Alien Dens',
        startWeaponId: 0,
        timeLimitMs: 180000,
        unlockWeaponId: 6, // Flamethrower
        unlockPerkId: 0x1e,
        // C: quest_build_alien_dens @ 00436720 — 5 entries, all template 0x08 (ALIEN_DEN)
        spawns: [
            { triggerTimeMs: 1500, posX: 256, posY: 256, templateId: EnemyTemplate.ALIEN_DEN, count: 1 },
            { triggerTimeMs: 1500, posX: 768, posY: 768, templateId: EnemyTemplate.ALIEN_DEN, count: 1 },
            { triggerTimeMs: 23500, posX: 512, posY: 512, templateId: EnemyTemplate.ALIEN_DEN, count: 0 },
            { triggerTimeMs: 38500, posX: 256, posY: 768, templateId: EnemyTemplate.ALIEN_DEN, count: 1 },
            { triggerTimeMs: 38500, posX: 768, posY: 256, templateId: EnemyTemplate.ALIEN_DEN, count: 1 },
        ],
    },

    // Quest 1-6: The Random Factor
    {
        id: 5,
        tier: 1,
        index: 6,
        name: 'The Random Factor',
        startWeaponId: 0,
        timeLimitMs: 300000,
        unlockWeaponId: 12, // Seeker Rockets
        unlockPerkId: PERK_ANTIPERK,
        spawns: buildTheRandomFactor(),
    },

    // Quest 1-7: Spider Wave Syndrome
    {
        id: 6,
        tier: 1,
        index: 7,
        name: 'Spider Wave Syndrome',
        startWeaponId: 0,
        timeLimitMs: 240000,
        unlockWeaponId: 9, // Plasma Minigun
        unlockPerkId: PERK_ANTIPERK,
        spawns: buildSpiderWaveSyndrome(),
    },

    // Quest 1-8: Alien Squads
    {
        id: 7,
        tier: 1,
        index: 8,
        name: 'Alien Squads',
        startWeaponId: 0,
        timeLimitMs: 180000,
        unlockWeaponId: 21, // Ion Minigun
        unlockPerkId: PERK_ANTIPERK,
        spawns: buildAlienSquads(),
    },

    // Quest 1-9: Nesting Grounds
    {
        id: 8,
        tier: 1,
        index: 9,
        name: 'Nesting Grounds',
        startWeaponId: 0,
        timeLimitMs: 240000,
        unlockWeaponId: 7, // Plasma Rifle
        unlockPerkId: 0x1f,
        // C: quest_build_nesting_grounds @ 004364a0 — 12 entries
        spawns: [
            { triggerTimeMs: 1500, posX: 512, posY: 1088, templateId: EnemyTemplate.NEST_SWARM, count: 6 },
            { triggerTimeMs: 8000, posX: 256, posY: 256, templateId: EnemyTemplate.SENTINEL, count: 1 },
            { triggerTimeMs: 13000, posX: 512, posY: 512, templateId: EnemyTemplate.SENTINEL, count: 1 },
            { triggerTimeMs: 18000, posX: 768, posY: 768, templateId: EnemyTemplate.SENTINEL, count: 1 },
            { triggerTimeMs: 25000, posX: 512, posY: 1088, templateId: EnemyTemplate.NEST_SWARM, count: 6 },
            { triggerTimeMs: 39000, posX: 512, posY: 1088, templateId: EnemyTemplate.NEST_SWARM, count: 3 },
            { triggerTimeMs: 41100, posX: 384, posY: 512, templateId: EnemyTemplate.SENTINEL, count: 1 },
            { triggerTimeMs: 42100, posX: 640, posY: 512, templateId: EnemyTemplate.SENTINEL, count: 1 },
            { triggerTimeMs: 43100, posX: 512, posY: 640, templateId: EnemyTemplate.SENTINEL, count: 1 },
            { triggerTimeMs: 44100, posX: 512, posY: 512, templateId: EnemyTemplate.ALIEN_DEN, count: 1 },
            { triggerTimeMs: 50000, posX: 512, posY: 1088, templateId: EnemyTemplate.SPIDER_VARIANT, count: 5 },
            { triggerTimeMs: 55000, posX: 512, posY: 1088, templateId: EnemyTemplate.BOSS_VARIANT, count: 2 },
        ],
    },

    // Quest 1-10: 8-Legged Terror
    {
        id: 9,
        tier: 1,
        index: 10,
        name: '8-Legged Terror',
        startWeaponId: 0,
        timeLimitMs: 240000,
        unlockWeaponId: 4, // Jackhammer
        unlockPerkId: 0x20,
        spawns: build8LeggedTerror(),
    },

    // ========== TIER 2 (lines 31544-31620) ==========

    // Quest 2-1: Everred Pastures
    {
        id: 10,
        tier: 2,
        index: 1,
        name: 'Everred Pastures',
        startWeaponId: 0,
        timeLimitMs: 300000,
        unlockWeaponId: 11, // Rocket Launcher
        unlockPerkId: 0x21,
        spawns: buildEverredPastures(),
    },

    // Quest 2-2: Spider Spawns
    {
        id: 11,
        tier: 2,
        index: 2,
        name: 'Spider Spawns',
        startWeaponId: 0,
        timeLimitMs: 300000,
        unlockWeaponId: 10, // Gauss Gun
        unlockPerkId: 0x22,
        // C: quest_build_spider_spawns @ 00436d70 — 11 entries
        spawns: [
            { triggerTimeMs: 1500, posX: 128, posY: 128, templateId: EnemyTemplate.NEST_SPAWNER, count: 1 },
            { triggerTimeMs: 1500, posX: 896, posY: 896, templateId: EnemyTemplate.NEST_SPAWNER, count: 1 },
            { triggerTimeMs: 1500, posX: 896, posY: 128, templateId: EnemyTemplate.NEST_SPAWNER, count: 1 },
            { triggerTimeMs: 1500, posX: 128, posY: 896, templateId: EnemyTemplate.NEST_SPAWNER, count: 1 },
            { triggerTimeMs: 3000, posX: -64, posY: 512, templateId: EnemyTemplate.SPIDER_BOSS_VAR, count: 2 },
            { triggerTimeMs: 18000, posX: 512, posY: 512, templateId: EnemyTemplate.MINE, count: 1 },
            { triggerTimeMs: 20500, posX: 448, posY: 448, templateId: EnemyTemplate.NEST_SPAWNER, count: 1 },
            { triggerTimeMs: 26000, posX: 576, posY: 448, templateId: EnemyTemplate.NEST_SPAWNER, count: 1 },
            { triggerTimeMs: 21000, posX: 1088, posY: 512, templateId: EnemyTemplate.SPIDER_BOSS_VAR, count: 2 },
            { triggerTimeMs: 31500, posX: 576, posY: 576, templateId: EnemyTemplate.NEST_SPAWNER, count: 1 },
            { triggerTimeMs: 22000, posX: 448, posY: 576, templateId: EnemyTemplate.NEST_SPAWNER, count: 1 },
        ],
    },

    // Quest 2-3: Arachnoid Farm
    {
        id: 12,
        tier: 2,
        index: 3,
        name: 'Arachnoid Farm',
        startWeaponId: 0,
        timeLimitMs: 240000,
        unlockWeaponId: 13, // Mean Minigun
        unlockPerkId: 0x23,
        spawns: buildArachnoidFarm(),
    },

    // Quest 2-4: Two Fronts
    {
        id: 13,
        tier: 2,
        index: 4,
        name: 'Two Fronts',
        startWeaponId: 0,
        timeLimitMs: 240000,
        unlockWeaponId: 15, // Blow Torch
        unlockPerkId: 0x24,
        spawns: buildTwoFronts(),
    },

    // Quest 2-5: Sweep Stakes
    {
        id: 14,
        tier: 2,
        index: 5,
        name: 'Sweep Stakes',
        startWeaponId: 10, // Gauss Gun (C: start_weapon_id=6 → TS 10)
        timeLimitMs: 35000,
        unlockWeaponId: 18, // Rocket Minigun
        unlockPerkId: 0x25,
        spawns: buildSweepStakes(),
    },

    // Quest 2-6: Evil Zombies At Large
    {
        id: 15,
        tier: 2,
        index: 6,
        name: 'Evil Zombies At Large',
        startWeaponId: 0,
        timeLimitMs: 180000,
        unlockWeaponId: 20, // Ion Rifle
        unlockPerkId: 0x26,
        spawns: buildEvilZombiesAtLarge(),
    },

    // Quest 2-7: Survival Of The Fastest
    {
        id: 16,
        tier: 2,
        index: 7,
        name: 'Survival Of The Fastest',
        startWeaponId: 5, // SMG
        timeLimitMs: 120000,
        unlockWeaponId: 14, // Plasma Shotgun
        unlockPerkId: 0x27,
        spawns: buildSurvivalOfTheFastest(),
    },

    // Quest 2-8: Land Of Lizards
    {
        id: 17,
        tier: 2,
        index: 8,
        name: 'Land Of Lizards',
        startWeaponId: 0,
        timeLimitMs: 180000,
        unlockWeaponId: 19, // Pulse Gun
        unlockPerkId: 0x28,
        // C: quest_build_land_of_lizards @ 00437ba0 — 4 turret entries
        spawns: [
            { triggerTimeMs: 2000, posX: 256, posY: 256, templateId: EnemyTemplate.TURRET, count: 1 },
            { triggerTimeMs: 12000, posX: 768, posY: 256, templateId: EnemyTemplate.TURRET, count: 1 },
            { triggerTimeMs: 22000, posX: 256, posY: 768, templateId: EnemyTemplate.TURRET, count: 1 },
            { triggerTimeMs: 32000, posX: 768, posY: 768, templateId: EnemyTemplate.TURRET, count: 1 },
        ],
    },

    // Quest 2-9: Ghost Patrols
    {
        id: 18,
        tier: 2,
        index: 9,
        name: 'Ghost Patrols',
        startWeaponId: 0,
        timeLimitMs: 180000,
        unlockWeaponId: 17, // Mini Rocket Swarmers
        unlockPerkId: 0x29,
        spawns: buildGhostPatrols(),
    },

    // Quest 2-10: Spideroids
    {
        id: 19,
        tier: 2,
        index: 10,
        name: 'Spideroids',
        startWeaponId: 0,
        timeLimitMs: 360000,
        unlockWeaponId: 16, // HR Flamer
        unlockPerkId: 0x2a,
        // C: quest_build_spideroids @ 004373c0 — 3 entries (normal mode)
        spawns: [
            { triggerTimeMs: 1000, posX: 1088, posY: 512, templateId: EnemyTemplate.GENERIC_HOSTILE, count: 1 },
            { triggerTimeMs: 3000, posX: -64, posY: 512, templateId: EnemyTemplate.GENERIC_HOSTILE, count: 1 },
            { triggerTimeMs: 6000, posX: 1088, posY: 256, templateId: EnemyTemplate.GENERIC_HOSTILE, count: 1 },
        ],
    },

    // ========== TIER 3 (lines 31621-31697) ==========

    // Quest 3-1: The Blighting
    {
        id: 20,
        tier: 3,
        index: 1,
        name: 'The Blighting',
        startWeaponId: 0,
        timeLimitMs: 300000,
        unlockWeaponId: 0,
        unlockPerkId: 0x2b,
        spawns: buildTheBlighting(),
    },

    // Quest 3-2: Lizard Kings
    {
        id: 21,
        tier: 3,
        index: 2,
        name: 'Lizard Kings',
        startWeaponId: 0,
        timeLimitMs: 180000,
        unlockWeaponId: 0,
        unlockPerkId: 0x2c,
        spawns: buildLizardKings(),
    },

    // Quest 3-3: The Killing
    {
        id: 22,
        tier: 3,
        index: 3,
        name: 'The Killing',
        startWeaponId: 0,
        timeLimitMs: 300000,
        unlockWeaponId: 0,
        unlockPerkId: PERK_ANTIPERK,
        spawns: buildTheKilling(),
    },

    // Quest 3-4: Hidden Evil  (Monster Vision unlock quest!)
    {
        id: 23,
        tier: 3,
        index: 4,
        name: 'Hidden Evil',
        startWeaponId: 0,
        timeLimitMs: 300000,
        unlockWeaponId: 0,
        unlockPerkId: 0x2d, // Monster Vision perk
        // C: quest_build_hidden_evil @ 00435a30 — 5 entries, all from bottom edge
        spawns: [
            { triggerTimeMs: 500, posX: 512, posY: 1088, templateId: EnemyTemplate.SPIDER_NESTED, count: 50 },
            { triggerTimeMs: 15000, posX: 512, posY: 1088, templateId: EnemyTemplate.SPIDER_QUEEN, count: 30 },
            { triggerTimeMs: 25000, posX: 512, posY: 1088, templateId: EnemyTemplate.SPIDER_BROOD, count: 20 },
            { triggerTimeMs: 30000, posX: 512, posY: 1088, templateId: EnemyTemplate.SPIDER_BROOD, count: 30 },
            { triggerTimeMs: 35000, posX: 512, posY: 1088, templateId: EnemyTemplate.SPIDER_QUEEN, count: 30 },
        ],
    },

    // Quest 3-5: Surrounded By Reptiles
    {
        id: 24,
        tier: 3,
        index: 5,
        name: 'Surrounded By Reptiles',
        startWeaponId: 0,
        timeLimitMs: 300000,
        unlockWeaponId: 0,
        unlockPerkId: 0x2e,
        spawns: buildSurroundedByReptiles(),
    },

    // Quest 3-6: The Lizquidation
    {
        id: 25,
        tier: 3,
        index: 6,
        name: 'The Lizquidation',
        startWeaponId: 0,
        timeLimitMs: 300000,
        unlockWeaponId: 0,
        unlockPerkId: 0x2f,
        spawns: buildTheLizquidation(),
    },

    // Quest 3-7: Spiders Inc.
    {
        id: 26,
        tier: 3,
        index: 7,
        name: 'Spiders Inc.',
        startWeaponId: 9, // Plasma Minigun (C: start_weapon_id=0xb → TS 9)
        timeLimitMs: 300000,
        unlockWeaponId: 0,
        unlockPerkId: 0x2f,
        spawns: buildSpidersInc(),
    },

    // Quest 3-8: Lizard Raze
    {
        id: 27,
        tier: 3,
        index: 8,
        name: 'Lizard Raze',
        startWeaponId: 0,
        timeLimitMs: 300000,
        unlockWeaponId: 0,
        unlockPerkId: 0x30,
        spawns: buildLizardRaze(),
    },

    // Quest 3-9: Deja Vu
    {
        id: 28,
        tier: 3,
        index: 9,
        name: 'Deja Vu',
        startWeaponId: 10, // Gauss Gun (C: start_weapon_id=6 → TS 10)
        timeLimitMs: 120000,
        unlockWeaponId: 24, // Gauss Shotgun (C: unlock_weapon_id=0x1E=30 → TS 24)
        unlockPerkId: PERK_ANTIPERK,
        spawns: buildDejaVu(),
    },

    // Quest 3-10: Zombie Masters
    {
        id: 29,
        tier: 3,
        index: 10,
        name: 'Zombie Masters',
        startWeaponId: 0,
        timeLimitMs: 300000,
        unlockWeaponId: 0,
        unlockPerkId: 0x31,
        // C: quest_build_zombie_masters @ 004360a0 — 4 entries, all template 0x00 (TOUGHGUY)
        spawns: [
            { triggerTimeMs: 1000, posX: 256, posY: 256, templateId: EnemyTemplate.TOUGHGUY, count: 0 },
            { triggerTimeMs: 6000, posX: 512, posY: 256, templateId: EnemyTemplate.TOUGHGUY, count: 1 },
            { triggerTimeMs: 14000, posX: 768, posY: 256, templateId: EnemyTemplate.TOUGHGUY, count: 0 },
            { triggerTimeMs: 18000, posX: 768, posY: 768, templateId: EnemyTemplate.TOUGHGUY, count: 1 },
        ],
    },

    // ========== TIER 4 (lines 31698-31824) ==========

    // Quest 4-1: Major Alien Breach
    {
        id: 30,
        tier: 4,
        index: 1,
        name: 'Major Alien Breach',
        startWeaponId: 18, // Rocket Minigun
        timeLimitMs: 300000,
        unlockWeaponId: 0,
        unlockPerkId: 0x32,
        spawns: buildMajorAlienBreach(),
    },

    // Quest 4-2: Zombie Time
    {
        id: 31,
        tier: 4,
        index: 2,
        name: 'Zombie Time',
        startWeaponId: 0,
        timeLimitMs: 300000,
        unlockWeaponId: 0,
        unlockPerkId: 0x33,
        spawns: buildZombieTime(),
    },

    // Quest 4-3: Lizard Zombie Pact
    {
        id: 32,
        tier: 4,
        index: 3,
        name: 'Lizard Zombie Pact',
        startWeaponId: 0,
        timeLimitMs: 300000,
        unlockWeaponId: 0,
        unlockPerkId: 0x34,
        spawns: buildLizardZombiePact(),
    },

    // Quest 4-4: The Collaboration
    {
        id: 33,
        tier: 4,
        index: 4,
        name: 'The Collaboration',
        startWeaponId: 0,
        timeLimitMs: 360000,
        unlockWeaponId: 25, // Plasma Cannon (C: unlock_weapon_id=0x1C=28 → TS 25)
        unlockPerkId: PERK_ANTIPERK,
        spawns: buildTheCollaboration(),
    },

    // Quest 4-5: The Massacre
    {
        id: 34,
        tier: 4,
        index: 5,
        name: 'The Massacre',
        startWeaponId: 0,
        timeLimitMs: 300000,
        unlockWeaponId: 0,
        unlockPerkId: 0x2e,
        spawns: buildTheMassacre(),
    },

    // Quest 4-6: The Unblitzkrieg
    {
        id: 35,
        tier: 4,
        index: 6,
        name: 'The Unblitzkrieg',
        startWeaponId: 0,
        timeLimitMs: 600000, // 10 minutes!
        unlockWeaponId: 0,
        unlockPerkId: PERK_ANTIPERK,
        spawns: buildTheUnblitzkrieg(),
    },

    // Quest 4-7: Gauntlet
    {
        id: 36,
        tier: 4,
        index: 7,
        name: 'Gauntlet',
        startWeaponId: 0,
        timeLimitMs: 300000,
        unlockWeaponId: 0,
        unlockPerkId: PERK_ANTIPERK,
        spawns: buildGauntlet(),
    },

    // Quest 4-8: Syntax Terror
    {
        id: 37,
        tier: 4,
        index: 8,
        name: 'Syntax Terror',
        startWeaponId: 0,
        timeLimitMs: 300000,
        unlockWeaponId: 0,
        unlockPerkId: PERK_ANTIPERK,
        spawns: buildSyntaxTerror(),
    },

    // Quest 4-9: The Annihilation
    {
        id: 38,
        tier: 4,
        index: 9,
        name: 'The Annihilation',
        startWeaponId: 0,
        timeLimitMs: 300000,
        unlockWeaponId: 0,
        unlockPerkId: PERK_ANTIPERK,
        spawns: buildTheAnnihilation(),
    },

    // Quest 4-10: The End Of All (Final Quest!)
    {
        id: 39,
        tier: 4,
        index: 10,
        name: 'The End Of All',
        startWeaponId: 0,
        timeLimitMs: 480000, // 8 minutes
        unlockWeaponId: 0,
        unlockPerkId: PERK_ANTIPERK,
        spawns: buildTheEndOfAll(),
    },

    // ========== TIER 5 (C: quest_database_init lines 5861-5930) ==========

    // Quest 5-1: The Beating (C: quest_build_the_beating @ 00435610)
    {
        id: 40,
        tier: 5,
        index: 1,
        name: 'The Beating',
        startWeaponId: 0,
        timeLimitMs: 480000,
        unlockWeaponId: 0,
        unlockPerkId: PERK_ANTIPERK,
        spawns: buildTheBeating(),
    },

    // Quest 5-2: The Spanking Of The Dead (C: quest_build_the_spanking_of_the_dead @ 004358a0)
    {
        id: 41,
        tier: 5,
        index: 2,
        name: 'The Spanking Of The Dead',
        startWeaponId: 0,
        timeLimitMs: 480000,
        unlockWeaponId: 0,
        unlockPerkId: PERK_ANTIPERK,
        spawns: buildTheSpankingOfTheDead(),
    },

    // Quest 5-3: The Fortress (C: quest_build_the_fortress @ 004352d0)
    {
        id: 42,
        tier: 5,
        index: 3,
        name: 'The Fortress',
        startWeaponId: 0,
        timeLimitMs: 480000,
        unlockWeaponId: 0,
        unlockPerkId: PERK_ANTIPERK,
        spawns: buildTheFortress(),
    },

    // Quest 5-4: The Gang Wars (C: quest_build_the_gang_wars @ 00435120)
    {
        id: 43,
        tier: 5,
        index: 4,
        name: 'The Gang Wars',
        startWeaponId: 0,
        timeLimitMs: 480000,
        unlockWeaponId: 0,
        unlockPerkId: PERK_ANTIPERK,
        spawns: buildTheGangWars(),
    },

    // Quest 5-5: Knee deep in the Dead (C: quest_build_knee_deep_in_the_dead @ 00434f00)
    {
        id: 44,
        tier: 5,
        index: 5,
        name: 'Knee deep in the Dead',
        startWeaponId: 0,
        timeLimitMs: 480000,
        unlockWeaponId: 0,
        unlockPerkId: PERK_ANTIPERK,
        spawns: buildKneeDeepInTheDead(),
    },

    // Quest 5-6: Cross Fire (C: quest_build_cross_fire @ 00435480)
    {
        id: 45,
        tier: 5,
        index: 6,
        name: 'Cross Fire',
        startWeaponId: 0,
        timeLimitMs: 480000,
        unlockWeaponId: 0,
        unlockPerkId: PERK_ANTIPERK,
        // C: quest_build_cross_fire @ 00435480 — 7 entries
        spawns: [
            { triggerTimeMs: 100, posX: 1074, posY: 512, templateId: EnemyTemplate.SWARM, count: 6 },
            { triggerTimeMs: 5500, posX: -40, posY: 512, templateId: EnemyTemplate.BOSS_ZOMBIE, count: 4 },
            { triggerTimeMs: 15500, posX: -40, posY: 512, templateId: EnemyTemplate.BOSS_ZOMBIE, count: 6 },
            { triggerTimeMs: 18500, posX: 512, posY: 512, templateId: EnemyTemplate.GENERIC_HOSTILE, count: 2 },
            { triggerTimeMs: 25500, posX: -100, posY: 512, templateId: EnemyTemplate.BOSS_ZOMBIE, count: 8 },
            { triggerTimeMs: 26000, posX: 512, posY: 1152, templateId: EnemyTemplate.SWARM, count: 6 },
            { triggerTimeMs: 26000, posX: 512, posY: -128, templateId: EnemyTemplate.SWARM, count: 6 },
        ],
    },

    // Quest 5-7: Army of Three (C: quest_build_army_of_three @ 00434ca0)
    {
        id: 46,
        tier: 5,
        index: 7,
        name: 'Army of Three',
        startWeaponId: 0,
        timeLimitMs: 480000,
        unlockWeaponId: 0,
        unlockPerkId: PERK_ANTIPERK,
        spawns: [
            { triggerTimeMs: 500, posX: -64, posY: 256, templateId: EnemyTemplate.SPIDER_FORMATION_A, count: 1 },
            { triggerTimeMs: 5500, posX: -64, posY: 512, templateId: EnemyTemplate.SPIDER_FORMATION_A, count: 1 },
            { triggerTimeMs: 15000, posX: -64, posY: 768, templateId: EnemyTemplate.SPIDER_FORMATION_A, count: 1 },
            { triggerTimeMs: 19500, posX: -64, posY: 768, templateId: EnemyTemplate.SPIDER2_FORMATION_A, count: 1 },
            { triggerTimeMs: 22500, posX: -64, posY: 512, templateId: EnemyTemplate.SPIDER2_FORMATION_A, count: 1 },
            { triggerTimeMs: 26500, posX: -64, posY: 256, templateId: EnemyTemplate.SPIDER2_FORMATION_A, count: 1 },
            { triggerTimeMs: 35500, posX: -64, posY: 256, templateId: EnemyTemplate.LIZARD_FORMATION_A, count: 1 },
            { triggerTimeMs: 39500, posX: -64, posY: 512, templateId: EnemyTemplate.LIZARD_FORMATION_A, count: 1 },
            { triggerTimeMs: 42500, posX: -64, posY: 768, templateId: EnemyTemplate.LIZARD_FORMATION_A, count: 1 },
            { triggerTimeMs: 52500, posX: 512, posY: 1152, templateId: EnemyTemplate.SPIDER_FORMATION_A, count: 3 },
            { triggerTimeMs: 56500, posX: 512, posY: -256, templateId: EnemyTemplate.SPIDER2_FORMATION_A, count: 3 },
        ],
    },

    // Quest 5-8: Monster Blues (C: quest_build_monster_blues @ 00434860)
    {
        id: 47,
        tier: 5,
        index: 8,
        name: 'Monster Blues',
        startWeaponId: 0,
        timeLimitMs: 480000,
        unlockWeaponId: 0,
        unlockPerkId: PERK_ANTIPERK,
        spawns: buildMonsterBlues(),
    },

    // Quest 5-9: Nagolipoli (C: quest_build_nagolipoli @ 00434480)
    {
        id: 48,
        tier: 5,
        index: 9,
        name: 'Nagolipoli',
        startWeaponId: 0,
        timeLimitMs: 480000,
        unlockWeaponId: 0,
        unlockPerkId: PERK_ANTIPERK,
        spawns: buildNagolipoli(),
    },

    // Quest 5-10: The Gathering (C: quest_build_the_gathering @ 004349c0)
    {
        id: 49,
        tier: 5,
        index: 10,
        name: 'The Gathering',
        startWeaponId: 0,
        timeLimitMs: 480000,
        unlockWeaponId: 0,
        unlockPerkId: PERK_ANTIPERK,
        // C: quest_build_the_gathering @ 004349c0 — 13 entries
        spawns: [
            { triggerTimeMs: 500, posX: 256, posY: 512, templateId: EnemyTemplate.GENERIC_HOSTILE, count: 1 },
            { triggerTimeMs: 9500, posX: 768, posY: 512, templateId: EnemyTemplate.GENERIC_HOSTILE, count: 2 },
            { triggerTimeMs: 15500, posX: 256, posY: 512, templateId: EnemyTemplate.BOSS_ZOMBIE_V2, count: 2 },
            { triggerTimeMs: 24500, posX: 768, posY: 512, templateId: EnemyTemplate.BOSS_ZOMBIE_V2, count: 2 },
            { triggerTimeMs: 30500, posX: 256, posY: 512, templateId: EnemyTemplate.TOUGHGUY, count: 2 },
            { triggerTimeMs: 39500, posX: 768, posY: 512, templateId: EnemyTemplate.TOUGHGUY, count: 2 },
            { triggerTimeMs: 54500, posX: 64, posY: 64, templateId: EnemyTemplate.BOSS_ZOMBIE, count: 2 },
            { triggerTimeMs: 54500, posX: 960, posY: 64, templateId: EnemyTemplate.BOSS_ZOMBIE, count: 1 },
            { triggerTimeMs: 54500, posX: 64, posY: 960, templateId: EnemyTemplate.BOSS_ZOMBIE, count: 2 },
            { triggerTimeMs: 54500, posX: 960, posY: 960, templateId: EnemyTemplate.BOSS_ZOMBIE, count: 1 },
            { triggerTimeMs: 90500, posX: -128, posY: 512, templateId: EnemyTemplate.BOSS_ZOMBIE_V2, count: 6 },
            { triggerTimeMs: 99500, posX: 1152, posY: 512, templateId: EnemyTemplate.GENERIC_HOSTILE, count: 4 },
            { triggerTimeMs: 109500, posX: 1152, posY: 512, templateId: EnemyTemplate.GENERIC_HOSTILE, count: 2 },
        ],
    },
];

/**
 * Get quest by tier and index
 */
export function getQuest(tier: number, index: number): QuestMeta | undefined {
    return QUEST_DATABASE.find((q) => q.tier === tier && q.index === index);
}

/**
 * Get quest by ID
 */
export function getQuestById(id: number): QuestMeta | undefined {
    return QUEST_DATABASE.find((q) => q.id === id);
}

/**
 * Get all quests in a tier
 */
export function getQuestsInTier(tier: number): QuestMeta[] {
    return QUEST_DATABASE.filter((q) => q.tier === tier);
}

/**
 * Get quest count
 */
export function getQuestCount(): number {
    return QUEST_DATABASE.length;
}

/**
 * Check if quest is unlocked based on unlock index
 * C: quest_unlock_index tracking
 */
export function isQuestUnlocked(tier: number, index: number, unlockIndex: number): boolean {
    // Quest ID in sequential order: (tier - 1) * 10 + (index - 1)
    const questSeqId = (tier - 1) * 10 + (index - 1);
    // First two quests always unlocked, then based on unlockIndex
    return questSeqId <= unlockIndex + 1;
}
