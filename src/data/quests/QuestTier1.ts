/**
 * QuestTier1 - Tier 1 quest builder functions
 *
 * Extracted from QuestData.ts
 */

import { QuestSpawnEntry, EnemyTemplate, DEFAULT_TERRAIN_WIDTH } from './QuestTypes';

/** Quest 1-2: Minor Alien Breach (C: quest_build_minor_alien_breach @ 00434990) */
export function buildMinorAlienBreach(): QuestSpawnEntry[] {
    const W = DEFAULT_TERRAIN_WIDTH;
    const HALF = W / 2;
    const spawns: QuestSpawnEntry[] = [];
    // Static entries 0,1
    spawns.push({ triggerTimeMs: 1000, posX: 256, posY: 256, templateId: EnemyTemplate.SPIDER_STANDARD, count: 2 });
    spawns.push({ triggerTimeMs: 1700, posX: 256, posY: 128, templateId: EnemyTemplate.SPIDER_STANDARD, count: 2 });
    // Loop: iVar4 from 2 to 17
    for (let iVar4 = 2; iVar4 <= 0x11; iVar4++) {
        const trigMs = (iVar4 * 5 - 10) * 0x2d0; // 720 per unit
        spawns.push({
            triggerTimeMs: trigMs,
            posX: W + 0x40,
            posY: HALF,
            templateId: EnemyTemplate.SPIDER_STANDARD,
            count: 1,
        });
        if (iVar4 > 6) {
            spawns.push({
                triggerTimeMs: trigMs,
                posX: W + 0x40,
                posY: HALF - 0x100,
                templateId: EnemyTemplate.SPIDER_STANDARD,
                count: 1,
            });
        }
        if (iVar4 === 0xd) {
            // 13
            spawns.push({
                triggerTimeMs: 0x9ab0,
                posX: HALF,
                posY: W + 0x40,
                templateId: EnemyTemplate.SPIDER_TANK,
                count: 1,
            });
            spawns.push({
                triggerTimeMs: trigMs,
                posX: -64,
                posY: HALF + 0x100,
                templateId: EnemyTemplate.SPIDER_STANDARD,
                count: 1,
            });
        } else if (iVar4 > 10) {
            spawns.push({
                triggerTimeMs: trigMs,
                posX: -64,
                posY: HALF + 0x100,
                templateId: EnemyTemplate.SPIDER_STANDARD,
                count: 1,
            });
        }
    }
    return spawns;
}

/** Quest 1-3: Target Practice (C: quest_build_target_practice @ 00438390) */
export function buildTargetPractice(): QuestSpawnEntry[] {
    // Uses crt_rand() for radial positions - we generate deterministic radial placement
    // 30 entries, template 0x36, decreasing spawn interval from 2000ms
    const spawns: QuestSpawnEntry[] = [];
    let trigMs = 2000;
    let step = 2000;
    for (let i = 0; i < 30; i++) {
        const angle = (i * 137.5 * Math.PI) / 180; // golden angle approximation for spread
        const radius = 64 + (i % 8) * 32;
        const x = Math.cos(angle) * radius + 512;
        const y = Math.sin(angle) * radius + 512;
        const heading = Math.atan2(y - 512, x - 512) - Math.PI / 2;
        spawns.push({
            triggerTimeMs: trigMs,
            posX: Math.round(x),
            posY: Math.round(y),
            templateId: EnemyTemplate.SPIDER_BURROW,
            count: 1,
            heading,
        });
        step -= 50;
        if (step < 1100) step = 1100;
        trigMs += step;
    }
    return spawns;
}

/** Quest 1-4: Frontline Assault (C: quest_build_frontline_assault @ 004389e0) */
export function buildFrontlineAssault(): QuestSpawnEntry[] {
    const HALF = 512;
    const spawns: QuestSpawnEntry[] = [];
    let step = 0x9c4; // 2500
    for (let iVar4 = 2; iVar4 < 0x16; iVar4++) {
        // 2..21
        const tmpl =
            iVar4 < 5
                ? EnemyTemplate.SPIDER_STANDARD
                : iVar4 < 10
                    ? EnemyTemplate.SPIDER_WAVE
                    : EnemyTemplate.SPIDER_STANDARD;
        const trigMs = iVar4 * step - 5000;
        spawns.push({ triggerTimeMs: trigMs, posX: HALF, posY: 1088, templateId: tmpl, count: 1 });
        if (iVar4 > 4) {
            spawns.push({
                triggerTimeMs: trigMs,
                posX: -64,
                posY: -64,
                templateId: EnemyTemplate.SPIDER_STANDARD,
                count: 1,
            });
        }
        if (iVar4 > 10) {
            spawns.push({
                triggerTimeMs: trigMs,
                posX: 1088,
                posY: -64,
                templateId: EnemyTemplate.SPIDER_STANDARD,
                count: 1,
            });
        }
        if (iVar4 === 10) {
            const t2 = (step * 5 - 0x9c4) * 2;
            spawns.push({ triggerTimeMs: t2, posX: 1088, posY: 512, templateId: EnemyTemplate.SPIDER_TANK, count: 1 });
            spawns.push({ triggerTimeMs: t2, posX: -64, posY: 512, templateId: EnemyTemplate.SPIDER_TANK, count: 1 });
        }
        step -= 0x32; // 50
        if (step < 0x708) step = 0x708; // 1800
    }
    return spawns;
}

/** Quest 1-6: The Random Factor (C: quest_build_the_random_factor @ 00436310) */
export function buildTheRandomFactor(): QuestSpawnEntry[] {
    const W = DEFAULT_TERRAIN_WIDTH;
    const HALF = W / 2;
    const spawns: QuestSpawnEntry[] = [];
    let trigMs = 0x5dc; // 1500
    while (trigMs < 0x18c7c) {
        // 101500
        spawns.push({
            triggerTimeMs: trigMs,
            posX: W + 0x40,
            posY: HALF,
            templateId: EnemyTemplate.NEST_SWARM,
            count: 4,
        });
        spawns.push({
            triggerTimeMs: trigMs + 200,
            posX: -64,
            posY: HALF,
            templateId: EnemyTemplate.NEST_SWARM,
            count: 6,
        });
        // C: 20% chance of extra ALIEN_FAST per wave (crt_rand() % 5 == 3)
        if (Math.random() < 0.2) {
            spawns.push({
                triggerTimeMs: trigMs,
                posX: HALF,
                posY: W + 0x40,
                templateId: EnemyTemplate.SPIDER_TANK,
                count: 0,
            });
        }
        trigMs += 10000;
    }
    return spawns;
}

/** Quest 1-7: Spider Wave Syndrome (C: quest_build_spider_wave_syndrome @ 00436440) */
export function buildSpiderWaveSyndrome(): QuestSpawnEntry[] {
    const HALF = 512;
    const spawns: QuestSpawnEntry[] = [];
    let trigMs = 0x5dc; // 1500
    while (trigMs < 0x18894) {
        // 100500
        spawns.push({ triggerTimeMs: trigMs, posX: -64, posY: HALF, templateId: EnemyTemplate.SWARM, count: 6 });
        trigMs += 0x157c; // 5500
    }
    return spawns;
}

/** Quest 1-8: Alien Squads (C: quest_build_alien_squads @ 00434ad0) */
export function buildAlienSquads(): QuestSpawnEntry[] {
    const spawns: QuestSpawnEntry[] = [];
    // Static patrol entries
    spawns.push({ triggerTimeMs: 0x5dc, posX: -256, posY: 256, templateId: EnemyTemplate.SPIDER_PATROL, count: 1 });
    spawns.push({ triggerTimeMs: 0x9c4, posX: -256, posY: 768, templateId: EnemyTemplate.SPIDER_PATROL, count: 1 });
    spawns.push({ triggerTimeMs: 0x157c, posX: 768, posY: -256, templateId: EnemyTemplate.SPIDER_PATROL, count: 1 });
    spawns.push({ triggerTimeMs: 0x2134, posX: 768, posY: 1280, templateId: EnemyTemplate.SPIDER_PATROL, count: 1 });
    spawns.push({ triggerTimeMs: 0x38a4, posX: 1280, posY: 1280, templateId: EnemyTemplate.SPIDER_PATROL, count: 1 });
    spawns.push({ triggerTimeMs: 0x4844, posX: 1280, posY: 768, templateId: EnemyTemplate.SPIDER_PATROL, count: 1 });
    spawns.push({ triggerTimeMs: 25000, posX: -256, posY: 256, templateId: EnemyTemplate.SPIDER_PATROL, count: 1 });
    spawns.push({ triggerTimeMs: 30000, posX: -256, posY: 768, templateId: EnemyTemplate.SPIDER_PATROL, count: 1 });
    // Loop: zombies from corners
    let trigMs = 0x8d68; // 36200
    while (trigMs < 83000) {
        spawns.push({
            triggerTimeMs: trigMs - 400,
            posX: -64,
            posY: -64,
            templateId: EnemyTemplate.SPIDER_STANDARD,
            count: 1,
        });
        spawns.push({
            triggerTimeMs: trigMs,
            posX: 1088,
            posY: 1088,
            templateId: EnemyTemplate.SPIDER_STANDARD,
            count: 1,
        });
        trigMs += 0x708; // 1800
    }
    return spawns;
}

/** Quest 1-10: 8-Legged Terror (C: quest_build_8_legged_terror @ 004362b0) */
export function build8LeggedTerror(): QuestSpawnEntry[] {
    const W = DEFAULT_TERRAIN_WIDTH;
    const HALF = W / 2;
    const spawns: QuestSpawnEntry[] = [];
    // Boss at right side
    spawns.push({
        triggerTimeMs: 1000,
        posX: W - 0x100,
        posY: HALF,
        templateId: EnemyTemplate.BOSS_ZOMBIE_V2,
        count: 1,
    });
    // Loop: boss aliens from corners
    let trigMs = 6000;
    while (trigMs < 0x8fc0) {
        // 36800
        spawns.push({ triggerTimeMs: trigMs, posX: -25, posY: -25, templateId: EnemyTemplate.BOSS_ALIEN, count: 1 });
        spawns.push({ triggerTimeMs: trigMs, posX: 1049, posY: -25, templateId: EnemyTemplate.BOSS_ALIEN, count: 1 });
        spawns.push({ triggerTimeMs: trigMs, posX: -25, posY: 1049, templateId: EnemyTemplate.BOSS_ALIEN, count: 1 });
        spawns.push({ triggerTimeMs: trigMs, posX: 1049, posY: 1049, templateId: EnemyTemplate.BOSS_ALIEN, count: 1 });
        trigMs += 0x898; // 2200
    }
    return spawns;
}
