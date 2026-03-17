/**
 * QuestTier3 - Tier 3 quest builder functions
 *
 * Extracted from QuestData.ts
 */

import { QuestSpawnEntry, EnemyTemplate, DEFAULT_TERRAIN_WIDTH } from './QuestTypes';

/** Quest 3-1: The Blighting (C: quest_build_the_blighting @ 00438cc0) */
export function buildTheBlighting(): QuestSpawnEntry[] {
    const W = DEFAULT_TERRAIN_WIDTH;
    const HALF = W / 2;
    const spawns: QuestSpawnEntry[] = [];
    // Static entries
    spawns.push({
        triggerTimeMs: 0x5dc,
        posX: W + 0x80,
        posY: HALF,
        templateId: EnemyTemplate.SPIDER_FAST_RED,
        count: 2,
    });
    spawns.push({ triggerTimeMs: 0x5dc, posX: -128, posY: HALF, templateId: EnemyTemplate.SPIDER_FAST_RED, count: 2 });
    spawns.push({ triggerTimeMs: 2000, posX: 896, posY: 128, templateId: EnemyTemplate.HOSTILE_07, count: 1 });
    spawns.push({ triggerTimeMs: 2000, posX: 128, posY: 128, templateId: EnemyTemplate.HOSTILE_07, count: 1 });
    spawns.push({ triggerTimeMs: 2000, posX: 128, posY: 896, templateId: EnemyTemplate.HOSTILE_07, count: 1 });
    spawns.push({ triggerTimeMs: 2000, posX: 896, posY: 896, templateId: EnemyTemplate.HOSTILE_07, count: 1 });
    // Loop: 8 waves
    let trigMs = 4000;
    for (let i = 0; i < 8; i++) {
        if (i === 2 || i === 4)
            spawns.push({
                triggerTimeMs: trigMs,
                posX: -128,
                posY: HALF,
                templateId: EnemyTemplate.SPIDER_FAST_RED,
                count: 4,
            });
        if (i === 3 || i === 5)
            spawns.push({
                triggerTimeMs: trigMs,
                posX: 1152,
                posY: HALF,
                templateId: EnemyTemplate.SPIDER_FAST_RED,
                count: 4,
            });
        const tmpl = i % 2 === 0 ? EnemyTemplate.SPIDER_WAVE : EnemyTemplate.LIZARD_CIRCLE;
        const mod5 = i % 5;
        if (mod5 === 0) {
            spawns.push({ triggerTimeMs: trigMs, posX: W + 0x40, posY: HALF, templateId: tmpl, count: 0x0c });
            trigMs += 15000;
        } else if (mod5 === 1) {
            spawns.push({ triggerTimeMs: trigMs, posX: -64, posY: HALF, templateId: tmpl, count: 0x0c });
            trigMs += 15000;
        } else if (mod5 === 2) {
            spawns.push({ triggerTimeMs: trigMs, posX: HALF, posY: W + 0x40, templateId: tmpl, count: 0x0c });
            trigMs += 15000;
        } else if (mod5 === 3) {
            spawns.push({ triggerTimeMs: trigMs, posX: HALF, posY: -64, templateId: tmpl, count: 0x0c });
            trigMs += 15000;
        }
        // C line 4811: +1000ms runs unconditionally every iteration (not just mod5==4)
        trigMs += 1000;
    }
    return spawns;
}

/** Quest 3-2: Lizard Kings (C: quest_build_lizard_kings @ 00438210) */
export function buildLizardKings(): QuestSpawnEntry[] {
    const spawns: QuestSpawnEntry[] = [];
    // Static entries
    spawns.push({ triggerTimeMs: 0x5dc, posX: 1152, posY: 512, templateId: EnemyTemplate.LIZARD_KING, count: 1 });
    spawns.push({ triggerTimeMs: 0x5dc, posX: -128, posY: 512, templateId: EnemyTemplate.LIZARD_KING, count: 1 });
    spawns.push({ triggerTimeMs: 0x5dc, posX: 1152, posY: 896, templateId: EnemyTemplate.LIZARD_KING, count: 1 });
    // Loop: 28 entries in circle
    let trigMs = 0x5dc; // 1500
    for (let i = 0; i < 0x1c; i++) {
        // 28
        const angle = i * 0.34906587; // ~20 degrees
        const x = Math.cos(angle) * 256 + 512;
        const y = Math.sin(angle) * 256 + 512;
        spawns.push({
            triggerTimeMs: trigMs,
            posX: Math.round(x),
            posY: Math.round(y),
            templateId: EnemyTemplate.LIZARD_KING_CIRCLE,
            count: 1,
            heading: -angle,
        });
        trigMs += 900;
    }
    return spawns;
}

/** Quest 3-3: The Killing (C: quest_build_the_killing @ 004393e0) */
export function buildTheKilling(): QuestSpawnEntry[] {
    const W = DEFAULT_TERRAIN_WIDTH;
    const HALF = W / 2;
    const spawns: QuestSpawnEntry[] = [];
    let trigMs = 2000;
    for (let i = 0; i < 10; i++) {
        const tmplMod = i % 3;
        const tmpl =
            tmplMod === 0
                ? EnemyTemplate.SPIDER_WAVE
                : tmplMod === 1
                    ? EnemyTemplate.SPIDER2_WAVE
                    : EnemyTemplate.LIZARD_CIRCLE;
        const posMod = i % 5;
        if (posMod === 0) {
            spawns.push({ triggerTimeMs: trigMs, posX: W + 0x40, posY: HALF, templateId: tmpl, count: 0x0c });
        } else if (posMod === 1) {
            spawns.push({ triggerTimeMs: trigMs, posX: -64, posY: HALF, templateId: tmpl, count: 0x0c });
        } else if (posMod === 2) {
            spawns.push({ triggerTimeMs: trigMs, posX: HALF, posY: W + 0x40, templateId: tmpl, count: 0x0c });
        } else if (posMod === 3) {
            spawns.push({ triggerTimeMs: trigMs, posX: HALF, posY: -64, templateId: tmpl, count: 0x0c });
        } else {
            // Phase 4: randomized positions — approximated with center-area spawns
            spawns.push({
                triggerTimeMs: trigMs,
                posX: 400,
                posY: 400,
                templateId: EnemyTemplate.HOSTILE_07,
                count: 3,
            });
            spawns.push({
                triggerTimeMs: trigMs + 1000,
                posX: 600,
                posY: 600,
                templateId: EnemyTemplate.HOSTILE_07,
                count: 3,
            });
        }
        trigMs += 6000;
    }
    return spawns;
}

/** Quest 3-5: Surrounded By Reptiles (C: quest_build_surrounded_by_reptiles @ 00439610) */
export function buildSurroundedByReptiles(): QuestSpawnEntry[] {
    const spawns: QuestSpawnEntry[] = [];
    // Phase 1: pairs along x=256 and x=768
    let offset = 0;
    let trigMs = 1000;
    while (trigMs < 5000) {
        const y = offset * 0.2 + 256;
        spawns.push({
            triggerTimeMs: trigMs,
            posX: 256,
            posY: Math.round(y),
            templateId: EnemyTemplate.LIZARD_VARIANT,
            count: 1,
        });
        spawns.push({
            triggerTimeMs: trigMs,
            posX: 768,
            posY: Math.round(y),
            templateId: EnemyTemplate.LIZARD_VARIANT,
            count: 1,
        });
        offset += 0x200;
        trigMs += 800;
    }
    // Phase 2: pairs along y=256 and y=768
    offset = 0;
    trigMs = 8000;
    while (trigMs < 12000) {
        const x = offset * 0.2 + 256;
        spawns.push({
            triggerTimeMs: trigMs,
            posX: Math.round(x),
            posY: 256,
            templateId: EnemyTemplate.LIZARD_VARIANT,
            count: 1,
        });
        spawns.push({
            triggerTimeMs: trigMs,
            posX: Math.round(x),
            posY: 768,
            templateId: EnemyTemplate.LIZARD_VARIANT,
            count: 1,
        });
        offset += 0x200;
        trigMs += 800;
    }
    return spawns;
}

/** Quest 3-6: The Lizquidation (C: quest_build_the_lizquidation @ 00438a30) */
export function buildTheLizquidation(): QuestSpawnEntry[] {
    const W = DEFAULT_TERRAIN_WIDTH;
    const HALF = W / 2;
    const spawns: QuestSpawnEntry[] = [];
    for (let i = 0; i < 10; i++) {
        const trigMs = i * 8000 + 0x5dc;
        spawns.push({
            triggerTimeMs: trigMs,
            posX: W + 0x40,
            posY: HALF,
            templateId: EnemyTemplate.LIZARD_WAVE,
            count: i + 6,
        });
        spawns.push({
            triggerTimeMs: trigMs,
            posX: -64,
            posY: HALF,
            templateId: EnemyTemplate.LIZARD_WAVE,
            count: i + 6,
        });
        if (i === 4) {
            spawns.push({
                triggerTimeMs: 0x5dc,
                posX: W + 0x80,
                posY: HALF,
                templateId: EnemyTemplate.SPIDER_FAST_RED,
                count: 2,
            });
        }
    }
    return spawns;
}

/** Quest 3-7: Spiders Inc. (C: quest_build_spiders_inc @ 004390d0) */
export function buildSpidersInc(): QuestSpawnEntry[] {
    const W = DEFAULT_TERRAIN_WIDTH;
    const HALF = W / 2;
    const spawns: QuestSpawnEntry[] = [];
    // Static entries
    spawns.push({
        triggerTimeMs: 500,
        posX: HALF,
        posY: W + 0x40,
        templateId: EnemyTemplate.SPIDER_BOSS_VAR,
        count: 1,
    });
    spawns.push({
        triggerTimeMs: 500,
        posX: HALF + 0x40,
        posY: W + 0x40,
        templateId: EnemyTemplate.SPIDER_BOSS_VAR,
        count: 1,
    });
    spawns.push({ triggerTimeMs: 500, posX: HALF, posY: -64, templateId: EnemyTemplate.SWARM, count: 4 });
    // Loop: pairs of spider boss variants
    let trigMs = 17000;
    let idx = 0;
    while (trigMs < 0x1a1f8) {
        // 107000
        const count = Math.floor(idx / 2) + 3;
        spawns.push({
            triggerTimeMs: trigMs,
            posX: HALF,
            posY: W + 0x40,
            templateId: EnemyTemplate.SPIDER_BOSS_VAR,
            count,
        });
        spawns.push({ triggerTimeMs: trigMs, posX: HALF, posY: -64, templateId: EnemyTemplate.SPIDER_BOSS_VAR, count });
        trigMs += 6000;
        idx++;
    }
    return spawns;
}

/** Quest 3-8: Lizard Raze (C: quest_build_lizard_raze @ 00439490) */
export function buildLizardRaze(): QuestSpawnEntry[] {
    const W = DEFAULT_TERRAIN_WIDTH;
    const HALF = W / 2;
    const spawns: QuestSpawnEntry[] = [];
    // Main loop: lizard waves from both sides
    let trigMs = 0x5dc; // 1500
    while (trigMs < 0x1656c) {
        // 91500
        spawns.push({
            triggerTimeMs: trigMs,
            posX: W + 0x40,
            posY: HALF,
            templateId: EnemyTemplate.LIZARD_WAVE,
            count: 6,
        });
        spawns.push({ triggerTimeMs: trigMs, posX: -64, posY: HALF, templateId: EnemyTemplate.LIZARD_WAVE, count: 6 });
        trigMs += 6000;
    }
    // Static turrets
    spawns.push({ triggerTimeMs: 10000, posX: 128, posY: 256, templateId: EnemyTemplate.TURRET_SMALL, count: 1 });
    spawns.push({ triggerTimeMs: 10000, posX: 128, posY: 384, templateId: EnemyTemplate.TURRET_SMALL, count: 1 });
    spawns.push({ triggerTimeMs: 10000, posX: 128, posY: 512, templateId: EnemyTemplate.TURRET_SMALL, count: 1 });
    return spawns;
}

/** Quest 3-9: Deja Vu (C: quest_build_deja_vu @ 004385d0) */
export function buildDejaVu(): QuestSpawnEntry[] {
    // 72 entries, template 0x0d, radial placement (uses crt_rand)
    const spawns: QuestSpawnEntry[] = [];
    let trigMs = 2000;
    let step = 2000;
    let outerIdx = 0;
    while (step > 0x230) {
        // 560
        const baseAngle = outerIdx * 0.35;
        for (let r = 0x54; r < 0xfc; r += 0x2a) {
            // 84, 126, 168, 210
            const x = Math.cos(baseAngle) * r + 512;
            const y = Math.sin(baseAngle) * r + 512;
            spawns.push({
                triggerTimeMs: trigMs,
                posX: Math.round(x),
                posY: Math.round(y),
                templateId: EnemyTemplate.LIZARD_VARIANT,
                count: 1,
            });
        }
        trigMs += step;
        step -= 0x50; // 80
        outerIdx++;
    }
    return spawns;
}
