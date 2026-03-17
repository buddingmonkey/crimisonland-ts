/**
 * QuestTier4 - Tier 4 quest builder functions
 *
 * Extracted from QuestData.ts
 */

import { QuestSpawnEntry, EnemyTemplate, DEFAULT_TERRAIN_WIDTH } from './QuestTypes';

/** Quest 4-1: Major Alien Breach (C: quest_build_major_alien_breach @ 004387f0) */
export function buildMajorAlienBreach(): QuestSpawnEntry[] {
    const spawns: QuestSpawnEntry[] = [];
    let trigMs = 4000;
    let accel = 0;
    while (accel < 0x5dc) {
        // 1500
        spawns.push({
            triggerTimeMs: trigMs,
            posX: 1088,
            posY: 512,
            templateId: EnemyTemplate.SPIDER_GREEN_WAVE,
            count: 2,
        });
        spawns.push({
            triggerTimeMs: trigMs,
            posX: 512,
            posY: -64,
            templateId: EnemyTemplate.SPIDER_GREEN_WAVE,
            count: 2,
        });
        trigMs += 2000 - accel;
        if (trigMs < 1000) trigMs = 1000;
        accel += 0x0f; // 15
    }
    return spawns;
}

/** Quest 4-2: Zombie Time (C: quest_build_zombie_time @ 00438bf0) */
export function buildZombieTime(): QuestSpawnEntry[] {
    const W = DEFAULT_TERRAIN_WIDTH;
    const HALF = W / 2;
    const spawns: QuestSpawnEntry[] = [];
    let trigMs = 0x5dc; // 1500
    while (trigMs < 0x17cdc) {
        // 97500
        spawns.push({
            triggerTimeMs: trigMs,
            posX: W + 0x40,
            posY: HALF,
            templateId: EnemyTemplate.SWARM_SMALL,
            count: 8,
        });
        spawns.push({ triggerTimeMs: trigMs, posX: -64, posY: HALF, templateId: EnemyTemplate.SWARM_SMALL, count: 8 });
        trigMs += 8000;
    }
    return spawns;
}

/** Quest 4-3: Lizard Zombie Pact (C: quest_build_lizard_zombie_pact @ 00439340) */
export function buildLizardZombiePact(): QuestSpawnEntry[] {
    const W = DEFAULT_TERRAIN_WIDTH;
    const HALF = W / 2;
    const spawns: QuestSpawnEntry[] = [];
    let trigMs = 0x5dc; // 1500
    let idx = 0;
    while (trigMs < 0x1bb5c) {
        // 113500
        spawns.push({
            triggerTimeMs: trigMs,
            posX: W + 0x40,
            posY: HALF,
            templateId: EnemyTemplate.SWARM_SMALL,
            count: 6,
        });
        spawns.push({ triggerTimeMs: trigMs, posX: -64, posY: HALF, templateId: EnemyTemplate.SWARM_SMALL, count: 6 });
        if (idx % 5 === 0) {
            const turretIdx = Math.floor(idx / 5);
            const y1 = turretIdx * 0xb4 + 0x100;
            const y2 = turretIdx * 0xb4 + 0x180;
            spawns.push({
                triggerTimeMs: trigMs,
                posX: 356,
                posY: y1,
                templateId: EnemyTemplate.TURRET_SMALL,
                count: turretIdx + 1,
            });
            spawns.push({
                triggerTimeMs: trigMs,
                posX: 356,
                posY: y2,
                templateId: EnemyTemplate.TURRET_SMALL,
                count: turretIdx + 2,
            });
        }
        trigMs += 7000;
        idx++;
    }
    return spawns;
}

/** Quest 4-4: The Collaboration (C: quest_build_the_collaboration @ 00438ee0) */
export function buildTheCollaboration(): QuestSpawnEntry[] {
    const W = DEFAULT_TERRAIN_WIDTH;
    const HALF = W / 2;
    const spawns: QuestSpawnEntry[] = [];
    let trigMs = 0x5dc; // 1500
    let iter = 0;
    while (trigMs < 0x2b55c) {
        // 177500
        const count = iter + 1;
        spawns.push({
            triggerTimeMs: trigMs,
            posX: W + 0x40,
            posY: HALF,
            templateId: EnemyTemplate.SPIDER_WAVE,
            count,
        });
        spawns.push({
            triggerTimeMs: trigMs,
            posX: HALF,
            posY: W + 0x40,
            templateId: EnemyTemplate.SPIDER2_WAVE,
            count,
        });
        spawns.push({ triggerTimeMs: trigMs, posX: -64, posY: HALF, templateId: EnemyTemplate.LIZARD_CIRCLE, count });
        spawns.push({ triggerTimeMs: trigMs, posX: 512, posY: -64, templateId: EnemyTemplate.SWARM_SMALL, count });
        trigMs += 11000;
        iter++;
    }
    return spawns;
}

/** Quest 4-5: The Massacre (C: quest_build_the_massacre @ 00439130) */
export function buildTheMassacre(): QuestSpawnEntry[] {
    const W = DEFAULT_TERRAIN_WIDTH;
    const HALF = W / 2;
    const spawns: QuestSpawnEntry[] = [];
    let trigMs = 0x5dc; // 1500
    let i = 0;
    while (trigMs < 0x1656c) {
        // 91500
        spawns.push({
            triggerTimeMs: trigMs,
            posX: W + 0x40,
            posY: HALF,
            templateId: EnemyTemplate.SWARM_SMALL,
            count: i + 3,
        });
        if (i % 2 === 0) {
            spawns.push({
                triggerTimeMs: trigMs,
                posX: W + 0x80,
                posY: HALF,
                templateId: EnemyTemplate.SPIDER_FAST_RED,
                count: i + 1,
            });
        }
        trigMs += 5000;
        i++;
    }
    return spawns;
}

/** Quest 4-6: The Unblitzkrieg (C: quest_build_the_unblitzkrieg @ 00439730) */
export function buildTheUnblitzkrieg(): QuestSpawnEntry[] {
    const spawns: QuestSpawnEntry[] = [];
    // Phase 1: 10 entries along x=824, y increasing
    let trigMs = 500;
    for (let i = 0, offset = 0; offset < 0x1860; i++, offset += 0x270) {
        const y = Math.floor(offset / 10) + 200;
        const tmpl = i % 2 === 0 ? EnemyTemplate.HOSTILE_07 : EnemyTemplate.LIZARD_VARIANT;
        spawns.push({ triggerTimeMs: trigMs, posX: 824, posY: y, templateId: tmpl, count: 1 });
        trigMs += 1800;
    }
    // Phase 2: along y=824, x decreasing
    for (let i = 0, offset = 0; offset < 0x1860; i++, offset += 0x270) {
        const x = 824 - Math.floor(offset / 10);
        const tmpl = i % 2 === 0 ? EnemyTemplate.LIZARD_VARIANT : EnemyTemplate.HOSTILE_07;
        spawns.push({ triggerTimeMs: trigMs, posX: x, posY: 824, templateId: tmpl, count: 1 });
        trigMs += 1500;
    }
    // Center entry
    spawns.push({ triggerTimeMs: trigMs, posX: 512, posY: 512, templateId: EnemyTemplate.HOSTILE_07, count: 1 });
    // Phase 3: along x=200, y values
    for (let i = 0, offset = 0; offset < 0x1860; i++, offset += 0x270) {
        const y = 824 - Math.floor(offset / 10);
        const tmpl = i % 2 === 0 ? EnemyTemplate.LIZARD_VARIANT : EnemyTemplate.HOSTILE_07;
        spawns.push({ triggerTimeMs: trigMs, posX: 200, posY: y, templateId: tmpl, count: 1 });
        trigMs += 1200;
    }
    // Phase 4: along y=200, x increasing
    for (let i = 0, offset = 0; offset < 0x1860; i++, offset += 0x270) {
        const x = 200 + Math.floor(offset / 10);
        const tmpl = i % 2 === 0 ? EnemyTemplate.HOSTILE_07 : EnemyTemplate.LIZARD_VARIANT;
        spawns.push({ triggerTimeMs: trigMs, posX: x, posY: 200, templateId: tmpl, count: 1 });
        trigMs += 800;
    }
    // Phase 5: diagonal
    for (let i = 0, offset = 0; offset < 0x1860; i++, offset += 0x270) {
        const pos = 200 + Math.floor(offset / 10);
        const tmpl = i % 2 === 0 ? EnemyTemplate.LIZARD_VARIANT : EnemyTemplate.HOSTILE_07;
        spawns.push({ triggerTimeMs: trigMs, posX: pos, posY: pos, templateId: tmpl, count: 1 });
        trigMs += 1500;
    }
    // Phase 6: along bottom
    for (let i = 0, offset = 0; offset < 0x1860; i++, offset += 0x270) {
        const x = 824 - Math.floor(offset / 10);
        const tmpl = i % 2 === 0 ? EnemyTemplate.HOSTILE_07 : EnemyTemplate.LIZARD_VARIANT;
        spawns.push({ triggerTimeMs: trigMs, posX: x, posY: 824, templateId: tmpl, count: 1 });
        trigMs += 700;
    }
    // Phase 7: final sweep
    for (let i = 0, offset = 0; offset < 0x1860; i++, offset += 0x270) {
        const y = 200 + Math.floor(offset / 10);
        const tmpl = i % 2 === 0 ? EnemyTemplate.LIZARD_VARIANT : EnemyTemplate.HOSTILE_07;
        spawns.push({ triggerTimeMs: trigMs, posX: 200, posY: y, templateId: tmpl, count: 1 });
        trigMs += 800;
    }
    return spawns;
}

/** Quest 4-7: Gauntlet (C: quest_build_gauntlet @ 00436b30) */
export function buildGauntlet(): QuestSpawnEntry[] {
    const W = DEFAULT_TERRAIN_WIDTH;
    const HALF = W / 2;
    const spawns: QuestSpawnEntry[] = [];
    const mineCount = 9; // DIFF + 9
    // Phase 1: circular mine placement
    for (let i = 0; i < mineCount; i++) {
        const angle = (i * 2 * Math.PI) / mineCount;
        const x = Math.cos(angle) * 158 + 512;
        const y = Math.sin(angle) * 158 + 512;
        spawns.push({
            triggerTimeMs: i * 200,
            posX: Math.round(x),
            posY: Math.round(y),
            templateId: EnemyTemplate.MINE,
            count: 1,
        });
    }
    // Phase 2: swarm waves from 4 directions
    let trigMs = 4000;
    for (let count = 2; count - 1 < mineCount; count++) {
        spawns.push({
            triggerTimeMs: trigMs,
            posX: W + 0x40,
            posY: HALF,
            templateId: EnemyTemplate.SWARM_SMALL,
            count,
        });
        spawns.push({ triggerTimeMs: trigMs, posX: -64, posY: HALF, templateId: EnemyTemplate.SWARM_SMALL, count });
        spawns.push({
            triggerTimeMs: trigMs,
            posX: HALF,
            posY: W + 0x40,
            templateId: EnemyTemplate.SWARM_SMALL,
            count,
        });
        spawns.push({ triggerTimeMs: trigMs, posX: HALF, posY: -64, templateId: EnemyTemplate.SWARM_SMALL, count });
        trigMs += 0x157c; // 5500
    }
    // Phase 3: larger mine circle
    const mineCount2 = 17; // DIFF + 0x11
    let mineTrig = 0xa604; // 42500
    for (let i = 0; i < mineCount2; i++) {
        const angle = (i * 2 * Math.PI) / mineCount2;
        const x = Math.cos(angle) * 258 + 512;
        const y = Math.sin(angle) * 258 + 512;
        spawns.push({
            triggerTimeMs: mineTrig,
            posX: Math.round(x),
            posY: Math.round(y),
            templateId: EnemyTemplate.MINE,
            count: 1,
        });
        mineTrig += 500;
    }
    return spawns;
}

/** Quest 4-8: Syntax Terror (C: quest_build_syntax_terror @ 00436b30) */
export function buildSyntaxTerror(): QuestSpawnEntry[] {
    const spawns: QuestSpawnEntry[] = [];
    let outerTrig = 0x5dc; // 1500
    let outerParam = 0x14c9; // 5321
    let outerIdx = 0;
    while (outerParam < 0x159d) {
        // 5533
        let innerStep = 0x4c5; // 1221
        let innerTrig = outerTrig;
        for (let iVar5 = 0; iVar5 < 9; iVar5++) {
            // DIFF + 9
            const x = (((iVar5 * iVar5 * 0x4c + 0xec) * iVar5 + outerParam * outerIdx) % 0x380) + 0x40;
            const y = ((innerStep * iVar5 + (outerIdx * outerIdx * 0x4c + 0x1b) * outerIdx) % 0x380) + 0x40;
            spawns.push({ triggerTimeMs: innerTrig, posX: x, posY: y, templateId: EnemyTemplate.HOSTILE_07, count: 1 });
            innerTrig += 300;
            innerStep += 0x15;
        }
        outerParam += 0x35; // 53
        outerIdx++;
        outerTrig += 30000;
    }
    return spawns;
}

/** Quest 4-9: The Annihilation (C: quest_build_the_annihilation @ 00438f90) */
export function buildTheAnnihilation(): QuestSpawnEntry[] {
    const spawns: QuestSpawnEntry[] = [];
    // Entry 0: lizard_fast pair
    spawns.push({ triggerTimeMs: 500, posX: 128, posY: 512, templateId: EnemyTemplate.SPIDER_FAST_RED, count: 2 });
    // Phase 1: 12 entries alternating x=832/896
    let trigMs = 500;
    let yOffset = 0;
    for (let i = 0; i < 12; i++) {
        const y = Math.floor(yOffset / 12) + 128;
        const x = i % 2 === 0 ? 832 : 896;
        spawns.push({ triggerTimeMs: trigMs, posX: x, posY: y, templateId: EnemyTemplate.HOSTILE_07, count: 1 });
        trigMs += 500;
        yOffset += 0x300;
    }
    // Phase 2: from trigger 45000
    yOffset = 0;
    trigMs = 45000;
    for (let i = 0; trigMs < 0xbdd8; i++) {
        // 48600
        const y = Math.floor(yOffset / 12) + 128;
        const x = i % 2 === 0 ? 896 : 832;
        spawns.push({ triggerTimeMs: trigMs, posX: x, posY: y, templateId: EnemyTemplate.HOSTILE_07, count: 1 });
        trigMs += 300;
        yOffset += 0x300;
    }
    return spawns;
}

/** Quest 4-10: The End of All (C: quest_build_the_end_of_all @ 00439830) */
export function buildTheEndOfAll(): QuestSpawnEntry[] {
    const spawns: QuestSpawnEntry[] = [];
    // 4 boss zombies at corners
    spawns.push({ triggerTimeMs: 3000, posX: 128, posY: 128, templateId: EnemyTemplate.BOSS_ZOMBIE, count: 1 });
    spawns.push({ triggerTimeMs: 6000, posX: 896, posY: 128, templateId: EnemyTemplate.BOSS_ZOMBIE, count: 1 });
    spawns.push({ triggerTimeMs: 9000, posX: 128, posY: 896, templateId: EnemyTemplate.BOSS_ZOMBIE, count: 1 });
    spawns.push({ triggerTimeMs: 12000, posX: 896, posY: 896, templateId: EnemyTemplate.BOSS_ZOMBIE, count: 1 });
    // Phase 1: 6 entries in circle, template 7, radius 80
    let trigMs = 13000;
    for (let i = 0; i < 6; i++) {
        const angle = i * 1.0471976; // pi/3
        const x = Math.cos(angle) * 80 + 512;
        const y = Math.sin(angle) * 80 + 512;
        spawns.push({
            triggerTimeMs: trigMs,
            posX: Math.round(x),
            posY: Math.round(y),
            templateId: EnemyTemplate.HOSTILE_07,
            count: 1,
        });
        trigMs += 300;
    }
    // Phase 2: large mine at center
    const lastTrig1 = spawns[spawns.length - 1].triggerTimeMs;
    spawns.push({ triggerTimeMs: lastTrig1, posX: 512, posY: 512, templateId: EnemyTemplate.MINE_LARGE, count: 1 });
    // Phase 3: boss zombies alternating sides, y increasing
    trigMs = 18000;
    let bAlternate = false;
    let yVal = 0x100; // 256
    while (yVal < 0x300) {
        // 768
        const x = bAlternate ? 1152 : -128;
        spawns.push({ triggerTimeMs: trigMs, posX: x, posY: yVal, templateId: EnemyTemplate.BOSS_ZOMBIE, count: 2 });
        bAlternate = !bAlternate;
        yVal += 0x80; // step by 128
        trigMs += 1000;
    }
    // Phase 4: 6 entries in offset circle, template 7, radius 80
    trigMs = 43000;
    for (let i = 0; i < 6; i++) {
        const angle = i * 1.0471976 + 0.5235988; // offset by pi/6
        const x = Math.cos(angle) * 80 + 512;
        const y = Math.sin(angle) * 80 + 512;
        spawns.push({
            triggerTimeMs: trigMs,
            posX: Math.round(x),
            posY: Math.round(y),
            templateId: EnemyTemplate.HOSTILE_07,
            count: 1,
        });
        trigMs += 300;
    }
    // Phase 5 (non-hardcore): boss zombies alternating sides again
    trigMs = 48000;
    bAlternate = false;
    yVal = 0x100;
    while (yVal < 0x300) {
        const x = bAlternate ? 1152 : -128;
        spawns.push({ triggerTimeMs: trigMs, posX: x, posY: yVal, templateId: EnemyTemplate.BOSS_ZOMBIE, count: 2 });
        bAlternate = !bAlternate;
        yVal += 0x80;
        trigMs += 1000;
    }
    return spawns;
}
