/**
 * QuestTier2 - Tier 2 quest builder functions
 *
 * Extracted from QuestData.ts
 */

import { QuestSpawnEntry, EnemyTemplate, DEFAULT_TERRAIN_WIDTH } from './QuestTypes';

/** Quest 2-1: Everred Pastures (C: quest_build_everred_pastures @ 00437620) */
export function buildEverredPastures(): QuestSpawnEntry[] {
    const W = DEFAULT_TERRAIN_WIDTH;
    const HALF = W / 2;
    const spawns: QuestSpawnEntry[] = [];
    for (let iVar6 = 0; iVar6 < 8; iVar6++) {
        const count = iVar6 + 1;
        const trigMs = iVar6 * 13000 + 0x5dc;
        spawns.push({ triggerTimeMs: trigMs, posX: W + 0x40, posY: HALF, templateId: EnemyTemplate.DIR_EAST, count });
        spawns.push({ triggerTimeMs: trigMs, posX: -64, posY: HALF, templateId: EnemyTemplate.DIR_WEST, count });
        spawns.push({ triggerTimeMs: trigMs, posX: HALF, posY: W + 0x40, templateId: EnemyTemplate.DIR_SOUTH, count });
        spawns.push({ triggerTimeMs: trigMs, posX: HALF, posY: -64, templateId: EnemyTemplate.DIR_NORTH, count });
        if (iVar6 === 3) {
            spawns.push({
                triggerTimeMs: 0x9e34,
                posX: HALF,
                posY: -64,
                templateId: EnemyTemplate.SPIDER2_WAVE,
                count: 8,
            });
            spawns.push({
                triggerTimeMs: 0x9e34,
                posX: HALF,
                posY: 1088,
                templateId: EnemyTemplate.SPIDER2_WAVE,
                count: 8,
            });
        }
    }
    return spawns;
}

/** Quest 2-4: Two Fronts (C: quest_build_two_fronts @ 00436e10) */
export function buildTwoFronts(): QuestSpawnEntry[] {
    const W = DEFAULT_TERRAIN_WIDTH;
    const HALF = W / 2;
    const spawns: QuestSpawnEntry[] = [];
    for (let i = 0; i < 0x28; i++) {
        // 40 iterations
        spawns.push({
            triggerTimeMs: i * 2000 + 1000,
            posX: W + 0x40,
            posY: HALF,
            templateId: EnemyTemplate.SPIDER_WAVE,
            count: 1,
        });
        spawns.push({
            triggerTimeMs: (i * 5 + 5) * 400,
            posX: -64,
            posY: HALF,
            templateId: EnemyTemplate.SPIDER2_WAVE,
            count: 1,
        });
        if (i === 10 || i === 20) {
            const t = i * 2000 + 0x9c4;
            spawns.push({ triggerTimeMs: t, posX: 256, posY: 256, templateId: EnemyTemplate.MINE, count: 1 });
            spawns.push({ triggerTimeMs: t, posX: 768, posY: 768, templateId: EnemyTemplate.HOSTILE_07, count: 1 });
        }
        if (i === 30) {
            spawns.push({ triggerTimeMs: 0xf424, posX: 768, posY: 256, templateId: EnemyTemplate.MINE, count: 1 });
            spawns.push({
                triggerTimeMs: 0xf424,
                posX: 256,
                posY: 768,
                templateId: EnemyTemplate.HOSTILE_07,
                count: 1,
            });
        }
    }
    return spawns;
}

/** Quest 2-5: Sweep Stakes (C: quest_build_sweep_stakes @ 00438480) */
export function buildSweepStakes(): QuestSpawnEntry[] {
    // 64 entries, template TARGET (0x36), radial placement with heading
    // Uses crt_rand() - approximated with deterministic radial spread
    const spawns: QuestSpawnEntry[] = [];
    let trigMs = 2000;
    let step = 2000;
    let outerIdx = 0;
    while (step > 0x2d0) {
        // 720
        const baseAngle = outerIdx * 0.39;
        for (let r = 0x54; r < 0xfc; r += 0x2a) {
            // 84, 126, 168, 210
            const x = Math.cos(baseAngle) * r + 512;
            const y = Math.sin(baseAngle) * r + 512;
            const heading = Math.atan2(y - 512, x - 512) - Math.PI / 2;
            spawns.push({
                triggerTimeMs: trigMs,
                posX: Math.round(x),
                posY: Math.round(y),
                templateId: EnemyTemplate.SPIDER_BURROW,
                count: 1,
                heading,
            });
        }
        let actualStep = step;
        if (step < 600) actualStep = 600;
        step -= 0x50; // 80
        trigMs += actualStep;
        outerIdx++;
    }
    return spawns;
}

/** Quest 2-6: Evil Zombies At Large (C: quest_build_evil_zombies_at_large @ 004374f0) */
export function buildEvilZombiesAtLarge(): QuestSpawnEntry[] {
    const W = DEFAULT_TERRAIN_WIDTH;
    const HALF = W / 2;
    const spawns: QuestSpawnEntry[] = [];
    let trigMs = 0x5dc; // 1500
    let count = 4;
    while (true) {
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
        if (count - 3 >= 10) break;
        count++;
    }
    return spawns;
}

/** Quest 2-7: Survival Of The Fastest (C: quest_build_survival_of_the_fastest @ 00437160) */
export function buildSurvivalOfTheFastest(): QuestSpawnEntry[] {
    const spawns: QuestSpawnEntry[] = [];
    // Phase 1: 6 entries along y=256, x=256..688
    let trigMs = 500;
    for (let x = 0x100; x < 0x2b0; x += 0x48) {
        // 256..688, step 72
        spawns.push({ triggerTimeMs: trigMs, posX: x, posY: 256, templateId: EnemyTemplate.NEST_SPAWNER, count: 1 });
        trigMs += 900;
    }
    // Phase 2: 6 entries along x=688, y=256..688
    trigMs = 5900;
    for (let y = 0x100; y < 0x2b0; y += 72) {
        spawns.push({ triggerTimeMs: trigMs, posX: 688, posY: y, templateId: EnemyTemplate.NEST_SPAWNER, count: 1 });
        trigMs += 900;
    }
    // Phase 3: 4 entries along y=688, x=688..400
    trigMs = 11300;
    for (let i = 0, x = 0x2b0; i < 4; i++, x -= 72) {
        spawns.push({ triggerTimeMs: trigMs, posX: x, posY: 688, templateId: EnemyTemplate.NEST_SPAWNER, count: 1 });
        trigMs += 900;
    }
    // Phase 4: 4 entries along x=400, y=688..400
    trigMs = 14900;
    for (let i = 0, y = 0x2b0; i < 4; i++, y -= 72) {
        spawns.push({ triggerTimeMs: trigMs, posX: 400, posY: y, templateId: EnemyTemplate.NEST_SPAWNER, count: 1 });
        trigMs += 900;
    }
    // Phase 5: 2 entries along y=400, x=400..544
    trigMs = 18500;
    for (let x = 400; x < 0x220; x += 0x48) {
        // 544
        spawns.push({ triggerTimeMs: trigMs, posX: x, posY: 400, templateId: EnemyTemplate.NEST_SPAWNER, count: 1 });
        trigMs += 900;
    }
    // Static corner entries
    spawns.push({ triggerTimeMs: 0x571c, posX: 128, posY: 128, templateId: EnemyTemplate.NEST_SPAWNER, count: 1 });
    spawns.push({ triggerTimeMs: 0x571c, posX: 896, posY: 128, templateId: EnemyTemplate.HOSTILE_07, count: 1 });
    spawns.push({ triggerTimeMs: 0x5eec, posX: 128, posY: 896, templateId: EnemyTemplate.HOSTILE_07, count: 1 });
    spawns.push({ triggerTimeMs: 0x5eec, posX: 896, posY: 896, templateId: EnemyTemplate.NEST_SPAWNER, count: 1 });
    return spawns;
}

/** Quest 2-9: Ghost Patrols (C: quest_build_ghost_patrols @ 004360e0) */
export function buildGhostPatrols(): QuestSpawnEntry[] {
    const HALF = 512;
    const spawns: QuestSpawnEntry[] = [];
    // Entry 0: lizard_fast pair
    spawns.push({ triggerTimeMs: 0x5dc, posX: 1152, posY: HALF, templateId: EnemyTemplate.SPIDER_FAST_RED, count: 2 });
    // Loop: 12 ghost patrols alternating sides
    let trigMs = 0x9c4; // 2500
    let loopCount = 0;
    while (trigMs < 0x7ef4) {
        // 32500
        const x = loopCount % 2 === 0 ? -128 : 1152;
        spawns.push({
            triggerTimeMs: trigMs,
            posX: x,
            posY: HALF,
            templateId: EnemyTemplate.SPIDER_GHOST_PATROL,
            count: 1,
        });
        loopCount++;
        trigMs += 0x9c4;
    }
    // Final lizard_fast
    spawns.push({
        triggerTimeMs: loopCount * 0x9c4 - 0x9c4,
        posX: -264,
        posY: HALF,
        templateId: EnemyTemplate.SPIDER_FAST_RED,
        count: 1,
    });
    // Ghost patrol end
    const finalTrig = (loopCount + 1 + 0x10 + (loopCount + 1) * 4) * 500;
    spawns.push({
        triggerTimeMs: finalTrig,
        posX: -128,
        posY: HALF,
        templateId: EnemyTemplate.SPIDER_GHOST_LEADER,
        count: 1,
    });
    return spawns;
}

/** Quest 2-3: Arachnoid Farm (C: quest_build_arachnoid_farm @ 00436620) */
export function buildArachnoidFarm(): QuestSpawnEntry[] {
    const spawns: QuestSpawnEntry[] = [];
    // Phase 1: 4 mines along y=256
    let trigMs = 500;
    for (let i = 0; i < 4; i++) {
        spawns.push({
            triggerTimeMs: trigMs,
            posX: i * 102.4 + 256,
            posY: 256,
            templateId: EnemyTemplate.MINE,
            count: 1,
        });
        trigMs += 500;
    }
    // Phase 2: 4 mines along y=768
    trigMs = 10500;
    for (let i = 0; i < 4; i++) {
        spawns.push({
            triggerTimeMs: trigMs,
            posX: i * 102.4 + 256,
            posY: 768,
            templateId: EnemyTemplate.MINE,
            count: 1,
        });
        trigMs += 500;
    }
    // Phase 3: 7 nest spawners along y=512
    trigMs = 0x9e34; // 40500
    for (let i = 0; i < 7; i++) {
        spawns.push({
            triggerTimeMs: trigMs,
            posX: i * 64 + 256,
            posY: 512,
            templateId: EnemyTemplate.NEST_SPAWNER,
            count: 1,
        });
        trigMs += 0xdac; // 3500
    }
    return spawns;
}
