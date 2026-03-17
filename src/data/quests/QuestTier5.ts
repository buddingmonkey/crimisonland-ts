/**
 * QuestTier5 - Tier 5 quest builder functions
 *
 * Extracted from QuestData.ts
 */

import { QuestSpawnEntry, EnemyTemplate, DEFAULT_TERRAIN_WIDTH, DEFAULT_TERRAIN_HEIGHT } from './QuestTypes';

/** Quest 5-1: The Beating (C: quest_build_the_beating @ 00435610) */
export function buildTheBeating(): QuestSpawnEntry[] {
    const W = DEFAULT_TERRAIN_WIDTH;
    const H = DEFAULT_TERRAIN_HEIGHT;
    const halfW = W / 2;
    const halfH = H / 2;
    const spawns: QuestSpawnEntry[] = [];
    // Entry 0: fast zombie at (256,256)
    spawns.push({ triggerTimeMs: 500, posX: 256, posY: 256, templateId: EnemyTemplate.SPIDER_FAST_FLAGGED, count: 1 });
    // Entry 1: fast aliens from right edge
    spawns.push({ triggerTimeMs: 8000, posX: W + 32, posY: halfH, templateId: EnemyTemplate.SPIDER_TANK, count: 3 });
    // Entries 2-9: 8 slow zombies from right edge, staggered
    let offset = 0x40; // 64
    for (let i = 0; i < 8; i++) {
        spawns.push({
            triggerTimeMs: 10000 + i * 100,
            posX: offset + W,
            posY: halfH,
            templateId: EnemyTemplate.SPIDER_SMALL,
            count: 8,
        });
        offset += 0x20;
    }
    // Entry 10: fast aliens from left edge
    spawns.push({ triggerTimeMs: 18000, posX: -32, posY: halfH, templateId: EnemyTemplate.SPIDER_TANK, count: 3 });
    // Entries 11-18: 8 slow zombies from left edge
    let leftX = -64;
    for (let i = 0; i < 8; i++) {
        spawns.push({
            triggerTimeMs: 20000 + i * 100,
            posX: leftX,
            posY: halfH,
            templateId: EnemyTemplate.SPIDER_SMALL,
            count: 8,
        });
        leftX -= 0x20;
    }
    // Entries 19-24: melee zombies from top
    let topY = -64;
    for (let i = 0; i < 6; i++) {
        spawns.push({
            triggerTimeMs: 40000 + i * 100,
            posX: halfW,
            posY: topY,
            templateId: EnemyTemplate.SPIDER_MELEE,
            count: 4,
        });
        topY -= 30;
    }
    // Entries 25-30: lizard patrols from bottom
    let iVar2b = 0;
    for (let i = 0; i < 6; i++) {
        const yPos = iVar2b + 0x2c + W;
        spawns.push({
            triggerTimeMs: 40000 + i * 100,
            posX: halfW,
            posY: yPos,
            templateId: EnemyTemplate.SPIDER_PATROL,
            count: 2,
        });
        iVar2b += 0x20;
    }
    return spawns; // 31 entries
}

/** Quest 5-2: The Spanking Of The Dead (C: quest_build_the_spanking_of_the_dead @ 004358a0) */
export function buildTheSpankingOfTheDead(): QuestSpawnEntry[] {
    const spawns: QuestSpawnEntry[] = [];
    // Two initial fast zombies
    spawns.push({ triggerTimeMs: 500, posX: 256, posY: 512, templateId: EnemyTemplate.SPIDER_FAST_FLAGGED, count: 1 });
    spawns.push({ triggerTimeMs: 500, posX: 768, posY: 512, templateId: EnemyTemplate.SPIDER_FAST_FLAGGED, count: 1 });
    // Spiral of small swarm enemies
    let triggerMs = 5000;
    for (let i = 0; triggerMs < 43400; i++) {
        const angle = i * 0.33333334;
        const radius = 512.0 - i * 3.8;
        const px = Math.cos(angle) * radius + 512.0;
        const py = Math.sin(angle) * radius + 512.0;
        spawns.push({
            triggerTimeMs: triggerMs,
            posX: Math.round(px),
            posY: Math.round(py),
            templateId: EnemyTemplate.SWARM_SMALL,
            count: 1,
            heading: angle,
        });
        triggerMs += 300;
    }
    // Two medium swarm waves based on last spiral trigger time
    const lastTrigger = spawns[spawns.length - 1].triggerTimeMs;
    // Two medium swarm waves
    spawns.push({
        triggerTimeMs: lastTrigger + 10000,
        posX: 1280,
        posY: 512,
        templateId: EnemyTemplate.SWARM_MEDIUM,
        count: 16,
    });
    spawns.push({
        triggerTimeMs: lastTrigger + 20000,
        posX: -256,
        posY: 512,
        templateId: EnemyTemplate.SWARM_MEDIUM,
        count: 16,
    });
    return spawns; // ~132 entries
}

/** Quest 5-3: The Fortress (C: quest_build_the_fortress @ 004352d0) */
export function buildTheFortress(): QuestSpawnEntry[] {
    const spawns: QuestSpawnEntry[] = [];
    // Initial swarm
    spawns.push({ triggerTimeMs: 100, posX: -50, posY: 512, templateId: EnemyTemplate.SWARM, count: 6 });
    // Sentinels in a column
    let entryOffset = 0x200; // 512
    let triggerMs = 0x44c; // 1100
    for (let i = 0; i < 7; i++) {
        const py = entryOffset * 0.125 + 256.0;
        spawns.push({
            triggerTimeMs: triggerMs,
            posX: 768,
            posY: Math.round(py),
            templateId: EnemyTemplate.SENTINEL,
            count: 1,
        });
        triggerMs += 600;
        entryOffset += 0x540; // each step is 0x15 * 0x40 in C pointer math
    }
    // Turret
    spawns.push({ triggerTimeMs: 6500, posX: 128, posY: 512, templateId: EnemyTemplate.TURRET, count: 1 });
    // Mine grid - nested loops over a grid pattern
    let entryIdx = 8; // current entry count before mines
    let outerVal = 0x180; // 384
    while (outerVal < 0x901) {
        // 2305
        let innerTrigger = entryIdx * 600 + 5500;
        for (let inner = 1; inner < 7; inner++) {
            // Skip certain positions (center holes in the fortress)
            if (inner === 1 && (outerVal === 0x480 || outerVal === 0x600)) {
                continue;
            }
            const mx = outerVal * 0.16666667 + 256.0;
            const my = 512.0 - inner * 0x180 * 0.16666667;
            spawns.push({
                triggerTimeMs: innerTrigger,
                posX: Math.round(mx),
                posY: Math.round(my),
                templateId: EnemyTemplate.MINE,
                count: 1,
            });
            innerTrigger += 600;
            entryIdx++;
        }
        outerVal += 0x400; // 1024
    }
    return spawns;
}

/** Quest 5-4: The Gang Wars (C: quest_build_the_gang_wars @ 00435120) */
export function buildTheGangWars(): QuestSpawnEntry[] {
    const halfH = DEFAULT_TERRAIN_HEIGHT * 0.5;
    const spawns: QuestSpawnEntry[] = [];
    // Entry 0: lizard patrol from left (far)
    spawns.push({ triggerTimeMs: 100, posX: -150, posY: halfH, templateId: EnemyTemplate.SPIDER_PATROL, count: 1 });
    // Entry 1: lizard patrol from right
    spawns.push({ triggerTimeMs: 2500, posX: 1174, posY: halfH, templateId: EnemyTemplate.SPIDER_PATROL, count: 1 });
    // Entries 2-11: 10 lizard patrols from left (1174.5 = 0x4492c000 as float)
    let triggerMs = 5500;
    for (let i = 0; i < 10; i++) {
        spawns.push({
            triggerTimeMs: triggerMs,
            posX: 1174,
            posY: halfH,
            templateId: EnemyTemplate.SPIDER_PATROL,
            count: 2,
        });
        triggerMs += 4000;
    }
    // Entry 12: lizard boss from bottom
    spawns.push({ triggerTimeMs: 50500, posX: 512, posY: 1152, templateId: EnemyTemplate.SPIDER_ORBIT_BOSS, count: 1 });
    // Entries 13-22: 10 lizard patrols from left (negative X)
    triggerMs = 59500;
    for (let i = 0; i < 10; i++) {
        spawns.push({
            triggerTimeMs: triggerMs,
            posX: -150,
            posY: halfH,
            templateId: EnemyTemplate.SPIDER_PATROL,
            count: 2,
        });
        triggerMs += 4000;
    }
    // Entry 23: final lizard boss wave
    spawns.push({
        triggerTimeMs: 107500,
        posX: 512,
        posY: 1152,
        templateId: EnemyTemplate.SPIDER_ORBIT_BOSS,
        count: 3,
    });
    return spawns; // 24 entries
}

/** Quest 5-5: Knee deep in the Dead (C: quest_build_knee_deep_in_the_dead @ 00434f00) */
export function buildKneeDeepInTheDead(): QuestSpawnEntry[] {
    const halfH = DEFAULT_TERRAIN_HEIGHT * 0.5;
    const spawns: QuestSpawnEntry[] = [];
    // Entry 0: swarm leader
    spawns.push({ triggerTimeMs: 100, posX: -50, posY: halfH, templateId: EnemyTemplate.SWARM_LEADER, count: 1 });
    // Main loop: iVar5 from 500 stepping 1500, while < 96500
    let iVar5 = 500;
    let uVar7 = 0;
    while (iVar5 < 96500) {
        // Every 8th iteration: spawn a swarm leader
        if ((uVar7 & 7) === 0) {
            spawns.push({
                triggerTimeMs: iVar5 - 2,
                posX: -50,
                posY: halfH,
                templateId: EnemyTemplate.SWARM_LEADER,
                count: 1,
            });
        }
        // Always: spawn small swarm
        const swarmCount = uVar7 > 0x20 ? 2 : 1;
        spawns.push({
            triggerTimeMs: iVar5,
            posX: -50,
            posY: halfH,
            templateId: EnemyTemplate.SWARM_SMALL,
            count: swarmCount,
        });
        // Phase 2: extra small swarm at y+158
        if (iVar5 > 12500) {
            spawns.push({
                triggerTimeMs: iVar5 + 500,
                posX: -50,
                posY: halfH + 158,
                templateId: EnemyTemplate.SWARM_SMALL,
                count: 1,
            });
        }
        // Phase 3: extra small swarm at y-158
        if (iVar5 > 24500) {
            spawns.push({
                triggerTimeMs: iVar5 + 1000,
                posX: -50,
                posY: halfH - 158,
                templateId: EnemyTemplate.SWARM_SMALL,
                count: 1,
            });
        }
        // Phase 4: medium swarm at y-258
        if (iVar5 > 36500) {
            spawns.push({
                triggerTimeMs: iVar5 + 1300,
                posX: -50,
                posY: halfH - 258,
                templateId: EnemyTemplate.SWARM_MEDIUM,
                count: 1,
            });
        }
        // Phase 5: medium swarm at y+258
        if (iVar5 > 48500) {
            spawns.push({
                triggerTimeMs: iVar5 + 300,
                posX: -50,
                posY: halfH + 258,
                templateId: EnemyTemplate.SWARM_MEDIUM,
                count: 1,
            });
        }
        iVar5 += 1500;
        uVar7++;
    }
    return spawns;
}

/** Quest 5-8: Monster Blues (C: quest_build_monster_blues @ 00434860) */
export function buildMonsterBlues(): QuestSpawnEntry[] {
    const halfH = DEFAULT_TERRAIN_HEIGHT * 0.5;
    const spawns: QuestSpawnEntry[] = [];
    // 4 static entries
    spawns.push({ triggerTimeMs: 500, posX: -50, posY: halfH, templateId: EnemyTemplate.SPIDER, count: 10 });
    spawns.push({
        triggerTimeMs: 7500,
        posX: 1074,
        posY: halfH,
        templateId: EnemyTemplate.SPIDER_FAST_DARK,
        count: 10,
    });
    spawns.push({
        triggerTimeMs: 17500,
        posX: 512,
        posY: 1088,
        templateId: EnemyTemplate.SPIDER_FAST_FLAGGED,
        count: 12,
    });
    spawns.push({
        triggerTimeMs: 17500,
        posX: 512,
        posY: -64,
        templateId: EnemyTemplate.SPIDER_FAST_FLAGGED,
        count: 12,
    });
    // 64 looped entries
    let triggerMs = 27500;
    for (let i = 0; i < 64; i++) {
        const mod4 = i & 3;
        let templateId: number;
        if (mod4 === 0) {
            templateId = EnemyTemplate.SPIDER_FAST_DARK; // 6
        } else if (mod4 === 1) {
            templateId = EnemyTemplate.SPIDER_FAST_FLAGGED; // 3 (-(uint)(uVar2!=1)&2)+3 = 3 when uVar2==1)
        } else {
            templateId = EnemyTemplate.SPIDER; // 5 when mod4=2, (-(1)&2)+3=5; and 3 when mod4=3
            // Actually: (-(uint)(uVar2 != 1) & 2) + 3
            // When uVar2!=1: -(1)&2 = 0xFFFFFFFE & 2 = 2, +3 = 5
            // When uVar2==1: -(0)&2 = 0, +3 = 3
            // So: mod4==0 -> 6, mod4==1 -> 3, mod4==2 or 3 -> 5
            templateId = 5; // Spider (raw C value, maps to template 5)
        }
        const count = Math.floor(i / 8) + 2;
        spawns.push({ triggerTimeMs: triggerMs, posX: -50, posY: 512, templateId, count });
        triggerMs += 900;
    }
    return spawns; // 68 entries
}

/** Quest 5-9: Nagolipoli (C: quest_build_nagolipoli @ 00434480) */
export function buildNagolipoli(): QuestSpawnEntry[] {
    const spawns: QuestSpawnEntry[] = [];
    // Circle 1: 8 swarm enemies in a circle (radius 128, center 512,512)
    for (let i = 0; i < 8; i++) {
        const angle = i * 0.7853982; // pi/4
        const px = Math.cos(angle) * 128.0 + 512.0;
        const py = Math.sin(angle) * 128.0 + 512.0;
        spawns.push({
            triggerTimeMs: 2000,
            posX: Math.round(px),
            posY: Math.round(py),
            templateId: EnemyTemplate.SWARM,
            count: 1,
            heading: angle,
        });
    }
    // Circle 2: 12 swarm enemies in a circle (radius 178, center 512,512)
    for (let i = 0; i < 12; i++) {
        const angle = i * 0.5235988; // pi/6
        const px = Math.cos(angle) * 178.0 + 512.0;
        const py = Math.sin(angle) * 178.0 + 512.0;
        spawns.push({
            triggerTimeMs: 8000,
            posX: Math.round(px),
            posY: Math.round(py),
            templateId: EnemyTemplate.SWARM,
            count: 1,
            heading: angle,
        });
    }
    // Ghost waves from 4 corners, trigger 13000 stepping 800, while < 38600
    let triggerMs = 13000;
    let loopCount = 0;
    while (triggerMs < 38600) {
        const ghostCount = Math.floor(loopCount / 8) + 1;
        spawns.push({
            triggerTimeMs: triggerMs,
            posX: -64,
            posY: -64,
            templateId: EnemyTemplate.LIZARD_CIRCLE,
            count: ghostCount,
            heading: 1.0471976,
        });
        spawns.push({
            triggerTimeMs: triggerMs,
            posX: 1088,
            posY: -64,
            templateId: EnemyTemplate.LIZARD_CIRCLE,
            count: ghostCount,
            heading: -1.0471976,
        });
        spawns.push({
            triggerTimeMs: triggerMs,
            posX: -64,
            posY: 1088,
            templateId: EnemyTemplate.LIZARD_CIRCLE,
            count: ghostCount,
            heading: -1.0471976,
        });
        spawns.push({
            triggerTimeMs: triggerMs,
            posX: 1088,
            posY: 1088,
            templateId: EnemyTemplate.LIZARD_CIRCLE,
            count: ghostCount,
            heading: 3.926991,
        });
        triggerMs += 800;
        loopCount++;
    }
    // 6 mines in a vertical line (x=64, y varies)
    for (let i = 0; i < 6; i++) {
        spawns.push({
            triggerTimeMs: 40000 + i * 100,
            posX: 64,
            posY: i * 85.333336 + 256,
            templateId: EnemyTemplate.MINE,
            count: 1,
        });
    }
    // 6 more mines in a vertical line (x=960, y varies)
    for (let i = 0; i < 6; i++) {
        spawns.push({
            triggerTimeMs: 45000 + i * 100,
            posX: 960,
            posY: i * 85.333336 + 256,
            templateId: EnemyTemplate.MINE,
            count: 1,
        });
    }
    // 2 large mines
    spawns.push({
        triggerTimeMs: 50000,
        posX: 512,
        posY: 256,
        templateId: EnemyTemplate.MINE_LARGE,
        count: 1,
        heading: 3.1415927,
    });
    spawns.push({
        triggerTimeMs: 50000,
        posX: 512,
        posY: 768,
        templateId: EnemyTemplate.MINE_LARGE,
        count: 1,
        heading: 3.1415927,
    });
    // Final ghost wave from bottom with 8 ghosts each
    const finalTrigger = 55000;
    spawns.push({
        triggerTimeMs: finalTrigger,
        posX: 512,
        posY: 1088,
        templateId: EnemyTemplate.LIZARD_CIRCLE,
        count: 8,
        heading: 3.926991,
    });
    spawns.push({
        triggerTimeMs: finalTrigger,
        posX: 512,
        posY: -64,
        templateId: EnemyTemplate.LIZARD_CIRCLE,
        count: 8,
        heading: 3.926991,
    });
    return spawns;
}
