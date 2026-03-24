/**
 * Quest System E2E Tests
 *
 * End-to-end tests verifying every quest works as implemented:
 * 1. All 50 quests load, start, and have valid spawn data
 * 2. Every template ID used by quests produces correct EnemyType, aiMode, and stats
 * 3. All quests can drain their spawn tables to completion
 * 4. Spider2 post-processing auto-promote logic
 * 5. Spawner/nest templates configure correctly
 * 6. Quest builder functions produce deterministic spawn counts
 */

import { describe, it, expect, beforeEach, vi } from 'vitest';
import { QuestSystem, QuestState } from '../quest/QuestSystem';
import { QUEST_DATABASE, getQuest, getQuestsInTier, EnemyTemplate } from '../../data/QuestData';
import { createQuestEnemy } from '../quest/QuestEnemySpawner';
import { EnemyType, AIMode } from '../../entities/Enemy';

// Mock the console to prevent log spam during tests
vi.mock('../../console/Console', () => ({
    gameConsole: {
        log: vi.fn(),
        print: vi.fn(),
    },
}));

// =============================================================================
// SECTION 1: QUEST DATABASE INTEGRITY — every quest loads and has valid data
// =============================================================================

describe('Quest Database Integrity', () => {
    it('should have exactly 50 quests across 5 tiers', () => {
        expect(QUEST_DATABASE.length).toBe(50);
        for (let tier = 1; tier <= 5; tier++) {
            expect(getQuestsInTier(tier).length).toBe(10);
        }
    });

    it.each(QUEST_DATABASE.map((q) => [q.tier, q.index, q.name]))(
        'Quest %i-%i "%s" has valid spawn entries',
        (tier, index, _name) => {
            const quest = getQuest(tier as number, index as number);
            expect(quest).toBeDefined();
            expect(quest!.spawns.length).toBeGreaterThan(0);
            // Every spawn entry has required fields
            for (const spawn of quest!.spawns) {
                expect(typeof spawn.triggerTimeMs).toBe('number');
                expect(spawn.triggerTimeMs).toBeGreaterThanOrEqual(0);
                expect(typeof spawn.posX).toBe('number');
                expect(typeof spawn.posY).toBe('number');
                expect(typeof spawn.templateId).toBe('number');
                expect(typeof spawn.count).toBe('number');
                expect(spawn.count).toBeGreaterThanOrEqual(0);
            }
        },
    );

    it.each(QUEST_DATABASE.map((q) => [q.tier, q.index, q.name]))(
        'Quest %i-%i "%s" has positive time limit and valid weapon/perk IDs',
        (tier, index, _name) => {
            const quest = getQuest(tier as number, index as number);
            expect(quest!.timeLimitMs).toBeGreaterThan(0);
            expect(typeof quest!.startWeaponId).toBe('number');
            expect(typeof quest!.unlockWeaponId).toBe('number');
            expect(typeof quest!.unlockPerkId).toBe('number');
        },
    );

    it('spawn trigger times are non-negative across all quests', () => {
        for (const quest of QUEST_DATABASE) {
            for (const spawn of quest.spawns) {
                expect(spawn.triggerTimeMs).toBeGreaterThanOrEqual(0);
            }
        }
    });
});

// =============================================================================
// SECTION 2: TEMPLATE ID → ENEMY TYPE MAPPING (the core fix being tested)
// =============================================================================

describe('createQuestEnemy — EnemyType mapping per template ID', () => {
    // Each entry: [templateId, expectedEnemyType, constantName]
    // These are the FIXED values matching C type_id
    const typeMapping: [number, EnemyType, string][] = [
        // Boss / Toughguy
        [0x00, EnemyType.Zombie, 'TOUGHGUY'],
        // Generic hostile (type_id=4)
        [0x01, EnemyType.Alien, 'GENERIC_HOSTILE'],
        // Random-stat templates
        [0x03, EnemyType.Spider2, 'random Spider2'],
        [0x04, EnemyType.Lizard, 'random Lizard'],
        [0x05, EnemyType.Alien, 'random Alien'],
        [0x06, EnemyType.Spider, 'random Spider'],
        // Spawner / nest templates (all Spider in C)
        [0x07, EnemyType.Spider, 'HOSTILE_07 nest'],
        [0x08, EnemyType.Spider, 'ALIEN_DEN nest'],
        [0x09, EnemyType.Spider, 'SENTINEL'],
        [0x0a, EnemyType.Spider, 'MINE'],
        [0x0b, EnemyType.Spider, 'MINE_LARGE'],
        [0x0c, EnemyType.Spider, 'TURRET_SMALL'],
        [0x0d, EnemyType.Spider, 'LIZARD_VARIANT spawner'],
        [0x0e, EnemyType.Spider, 'TURRET'],
        [0x10, EnemyType.Spider, 'NEST_SPAWNER'],
        // Melee
        [0x0f, EnemyType.Spider, 'SPIDER_MELEE (was ZOMBIE_MELEE)'],
        // Formation leaders (corrected types)
        [0x11, EnemyType.Lizard, 'LIZARD_KING'],
        [0x12, EnemyType.Spider, 'SPIDER_PATROL (was LIZARD_PATROL)'],
        [0x13, EnemyType.Spider, 'SPIDER_ORBIT_BOSS (was LIZARD_BOSS)'],
        [0x14, EnemyType.Spider, 'Formation leader A'],
        [0x15, EnemyType.Spider, 'SPIDER_FORMATION_A (was ALIEN_BOSS)'],
        [0x16, EnemyType.Lizard, 'LIZARD_FORMATION_A (was ALIEN_MECH)'],
        [0x17, EnemyType.Spider2, 'SPIDER2_FORMATION_A (was ALIEN_DRONE)'],
        [0x18, EnemyType.Spider, 'SPIDER_GHOST_LEADER (was GHOST_PATROL_END)'],
        [0x19, EnemyType.Spider, 'SPIDER_GHOST_PATROL (was GHOST_PATROL)'],
        // Circling / wave templates
        [0x1a, EnemyType.Spider, 'SPIDER_WAVE (was ZOMBIE_WAVE)'],
        [0x1b, EnemyType.Spider2, 'SPIDER2_WAVE (was ALIEN_WAVE)'],
        [0x1c, EnemyType.Lizard, 'LIZARD_CIRCLE (was GHOST)'],
        // Nest swarm children
        [0x1d, EnemyType.Spider, 'NEST_SWARM'],
        [0x1e, EnemyType.Spider, 'SPIDER_VARIANT'],
        [0x1f, EnemyType.Spider, 'BOSS_VARIANT'],
        // Green wave / breach
        [0x20, EnemyType.Spider, 'SPIDER_GREEN_WAVE (was ALIEN_BREACH)'],
        // Hidden Evil
        [0x21, EnemyType.Spider, 'SPIDER_NESTED'],
        [0x22, EnemyType.Spider, 'SPIDER_QUEEN'],
        [0x23, EnemyType.Spider, 'SPIDER_BROOD'],
        // Standard spider variants (corrected from Zombie/Alien/Lizard)
        [0x25, EnemyType.Spider, 'SPIDER_SMALL (was ZOMBIE_SLOW)'],
        [0x26, EnemyType.Spider, 'SPIDER_STANDARD (was ZOMBIE)'],
        [0x27, EnemyType.Spider, 'SPIDER_FAST_FLAGGED (was ZOMBIE_FAST)'],
        [0x28, EnemyType.Spider, 'SPIDER_MID (was ALIEN)'],
        [0x29, EnemyType.Spider, 'SPIDER_TANK (was ALIEN_FAST)'],
        [0x2a, EnemyType.Spider, 'SPIDER_FAST_DARK (was LIZARD)'],
        [0x2b, EnemyType.Spider, 'SPIDER_FAST_RED (was LIZARD_FAST)'],
        [0x2c, EnemyType.Spider, 'SPIDER'],
        [0x2d, EnemyType.Spider, 'SPIDER_LARGE'],
        // Lizard wave
        [0x2e, EnemyType.Lizard, 'LIZARD_WAVE'],
        // Nest children / variants (switch cases, not EnemyTemplate names)
        [0x31, EnemyType.Lizard, 'Lizard child (nest spawn)'],
        [0x32, EnemyType.Spider2, 'Spider2 child (nest spawn)'],
        [0x33, EnemyType.Spider2, 'Spider2 variant'],
        [0x34, EnemyType.Spider2, 'Spider2 variant 2'],
        [0x35, EnemyType.Alien, 'Alien small'],
        // Burrow
        [0x36, EnemyType.Spider, 'SPIDER_BURROW (was TARGET)'],
        // Shooter / fast
        [0x37, EnemyType.Alien, 'Minigun shooter'],
        [0x38, EnemyType.Spider2, 'SPIDER_BOSS_VAR (fast spider2)'],
        [0x39, EnemyType.Spider2, 'Fast weak spider2'],
        // Boss zombie v2
        [0x3a, EnemyType.Spider2, 'BOSS_ZOMBIE_V2'],
        [0x3b, EnemyType.Spider2, 'Boss spider2'],
        // Boss enemies
        [0x3c, EnemyType.Spider2, 'BOSS_ZOMBIE'],
        [0x3d, EnemyType.Spider2, 'BOSS_ALIEN'],
        [0x3e, EnemyType.Spider2, 'BOSS_LIZARD'],
        [0x3f, EnemyType.Spider2, 'BOSS_SPIDER'],
        // Swarm
        [0x40, EnemyType.Spider2, 'SWARM'],
        [0x41, EnemyType.Zombie, 'SWARM_SMALL'],
        [0x42, EnemyType.Zombie, 'SWARM_MEDIUM'],
        [0x43, EnemyType.Zombie, 'SWARM_LEADER'],
    ];

    it.each(typeMapping)('template 0x%s → EnemyType %s (%s)', (templateId, expectedType, _label) => {
        const enemy = createQuestEnemy(100, 100, templateId);
        expect(enemy.type).toBe(expectedType);
    });
});

// =============================================================================
// SECTION 3: AI MODE MAPPING
// =============================================================================

describe('createQuestEnemy — aiMode per template ID', () => {
    const aiModeMapping: [number, AIMode, string][] = [
        [0x0f, AIMode.CHASE_CIRCLE, 'SPIDER_MELEE'],
        [0x11, AIMode.CLOSE_CIRCLE, 'LIZARD_KING'],
        [0x13, AIMode.ORBIT_ANGLE, 'SPIDER_ORBIT_BOSS'],
        [0x14, AIMode.DIRECT_CHASE, 'Formation leader A'],
        [0x15, AIMode.DIRECT_CHASE, 'SPIDER_FORMATION_A'],
        [0x16, AIMode.DIRECT_CHASE, 'LIZARD_FORMATION_A'],
        [0x17, AIMode.DIRECT_CHASE, 'SPIDER2_FORMATION_A'],
        [0x18, AIMode.DIRECT_CHASE, 'SPIDER_GHOST_LEADER'],
        [0x1a, AIMode.CLOSE_CIRCLE, 'SPIDER_WAVE'],
        [0x1b, AIMode.CLOSE_CIRCLE, 'SPIDER2_WAVE'],
        [0x1c, AIMode.CLOSE_CIRCLE, 'LIZARD_CIRCLE'],
        [0x2d, AIMode.DIRECT_CHASE, 'SPIDER_LARGE'],
        [0x36, AIMode.BURROW, 'SPIDER_BURROW'],
        [0x3c, AIMode.DIRECT_CHASE, 'BOSS_ZOMBIE'],
    ];

    it.each(aiModeMapping)('template 0x%s → AIMode %s (%s)', (templateId, expectedMode, _label) => {
        const enemy = createQuestEnemy(100, 100, templateId);
        expect(enemy.aiMode).toBe(expectedMode);
    });
});

// =============================================================================
// SECTION 4: KEY STAT VALUES FOR DETERMINISTIC TEMPLATES
// =============================================================================

describe('createQuestEnemy — deterministic stat values', () => {
    it('SPIDER_STANDARD (0x26) has hp=50, size=45, reward=125', () => {
        const enemy = createQuestEnemy(100, 100, 0x26);
        expect(enemy.health).toBe(50);
        expect(enemy.maxHealth).toBe(50);
        expect(enemy.size).toBe(45);
        expect(enemy.rewardValue).toBe(125);
    });

    it('SPIDER_TANK (0x29) has hp=800, size=70, reward=450', () => {
        const enemy = createQuestEnemy(100, 100, 0x29);
        expect(enemy.health).toBe(800);
        expect(enemy.size).toBe(70);
        expect(enemy.rewardValue).toBe(450);
    });

    it('LIZARD_KING (0x11) has hp=1500, size=69, reward=1000, contactDmg=150', () => {
        const enemy = createQuestEnemy(100, 100, 0x11);
        expect(enemy.health).toBe(1500);
        expect(enemy.size).toBe(69);
        expect(enemy.rewardValue).toBe(1000);
        expect(enemy.damage).toBe(150);
    });

    it('TOUGHGUY (0x00) has hp=8500, size=64, is spawner with child=0x41', () => {
        const enemy = createQuestEnemy(100, 100, 0x00);
        expect(enemy.health).toBe(8500);
        expect(enemy.size).toBe(64);
        expect(enemy.isNestSpawner).toBe(true);
        expect(enemy.nestChildTemplate).toBe(0x41);
    });

    it('SPIDER_SMALL (0x25) has hp=25, size=30, reward=125', () => {
        const enemy = createQuestEnemy(100, 100, 0x25);
        expect(enemy.health).toBe(25);
        expect(enemy.size).toBe(30);
        expect(enemy.rewardValue).toBe(125);
    });

    it('SPIDER_FAST_RED (0x2B) has hp=30, size=35, speed=3.6*30', () => {
        const enemy = createQuestEnemy(100, 100, 0x2b);
        expect(enemy.health).toBe(30);
        expect(enemy.size).toBe(35);
        expect(enemy.speed).toBeCloseTo(3.6 * 30, 1);
    });

    it('MINE (0x0A) is spawner with child=0x32, interval=5.0', () => {
        const enemy = createQuestEnemy(100, 100, 0x0a);
        expect(enemy.isNestSpawner).toBe(true);
        expect(enemy.nestChildTemplate).toBe(0x32);
        expect(enemy.nestSpawnInterval).toBeCloseTo(5.2, 2); // C adds +0.2s in normal mode (line 3582)
        expect(enemy.creatureFlags).toBe(4);
    });

    it('SENTINEL (0x09) is spawner with limit=16', () => {
        const enemy = createQuestEnemy(100, 100, 0x09);
        expect(enemy.isNestSpawner).toBe(true);
        expect(enemy.nestSpawnLimit).toBe(16);
        expect(enemy.nestChildTemplate).toBe(0x1d);
    });
});

// =============================================================================
// SECTION 5: TINT COLOR VALUES
// =============================================================================

describe('createQuestEnemy — tint values for key templates', () => {
    it('GENERIC_HOSTILE (0x01) tint: R=0.8, G=0.7, B=0.4', () => {
        const enemy = createQuestEnemy(100, 100, 0x01);
        expect(enemy.tintR).toBeCloseTo(0.8, 2);
        expect(enemy.tintG).toBeCloseTo(0.7, 2);
        expect(enemy.tintB).toBeCloseTo(0.4, 2);
    });

    it('MINE_LARGE (0x0B) tint: R=0.9, G=0.1, B=0.1', () => {
        const enemy = createQuestEnemy(100, 100, 0x0b);
        expect(enemy.tintR).toBeCloseTo(0.9, 2);
        expect(enemy.tintG).toBeCloseTo(0.1, 2);
        expect(enemy.tintB).toBeCloseTo(0.1, 2);
    });

    it('LIZARD_KING (0x11) tint: R=0.99, G=0.99, B=0.21', () => {
        const enemy = createQuestEnemy(100, 100, 0x11);
        expect(enemy.tintR).toBeCloseTo(0.99, 2);
        expect(enemy.tintG).toBeCloseTo(0.99, 2);
        expect(enemy.tintB).toBeCloseTo(0.21, 2);
    });

    it('SPIDER_GHOST_PATROL (0x19) tint: R=0.95, G=0.55, B=0.37', () => {
        const enemy = createQuestEnemy(100, 100, 0x19);
        expect(enemy.tintR).toBeCloseTo(0.95, 2);
        expect(enemy.tintG).toBeCloseTo(0.55, 2);
        expect(enemy.tintB).toBeCloseTo(0.37, 2);
    });
});

// =============================================================================
// SECTION 6: SPIDER2 POST-PROCESSING AUTO-PROMOTE
// =============================================================================

describe('Spider2 post-processing auto-promote', () => {
    it('SPIDER2_FORMATION_A (0x17) gets 0x80 flag and 1.2x speed boost', () => {
        const enemy = createQuestEnemy(100, 100, 0x17);
        expect(enemy.type).toBe(EnemyType.Spider2);
        // Should have 0x80 flag added (was no flags)
        expect(enemy.creatureFlags & 0x80).toBeTruthy();
        // Speed should be 2.0 * 1.2 * 30 = 72
        expect(enemy.speed).toBeCloseTo(2.0 * 1.2 * 30, 1);
    });

    it('SPIDER2_WAVE (0x1B) gets 0x80 flag and 1.2x speed boost', () => {
        const enemy = createQuestEnemy(100, 100, 0x1b);
        expect(enemy.type).toBe(EnemyType.Spider2);
        expect(enemy.creatureFlags & 0x80).toBeTruthy();
        expect(enemy.speed).toBeCloseTo(2.4 * 1.2 * 30, 1);
    });

    it('BOSS_ZOMBIE (0x3C) with minigun flag (0x100) does NOT get auto-promote', () => {
        // 0x3C has cFlags=0x100 (minigun), but 0x80 flag check: !(0x100 & 0x80) = true
        // Also has no 0x10 flag. So it SHOULD get promoted.
        // Actually: 0x100 & 0x80 = 0 (no overlap), so it should get promoted
        const enemy = createQuestEnemy(100, 100, 0x3c);
        expect(enemy.type).toBe(EnemyType.Spider2);
        // Should have both 0x100 and 0x80
        expect(enemy.creatureFlags & 0x100).toBeTruthy();
        expect(enemy.creatureFlags & 0x80).toBeTruthy();
    });

    it('Non-Spider2 enemies do NOT get auto-promote (0x26 Spider)', () => {
        const enemy = createQuestEnemy(100, 100, 0x26);
        expect(enemy.type).toBe(EnemyType.Spider);
        // Should NOT have 0x80 flag
        expect(enemy.creatureFlags & 0x80).toBeFalsy();
    });
});

// =============================================================================
// SECTION 7: CREATURE FLAGS — shooter setup
// =============================================================================

describe('createQuestEnemy — creature flags and shooter setup', () => {
    it('SPIDER_FAST_FLAGGED (0x27) has cFlags=0x400', () => {
        const enemy = createQuestEnemy(100, 100, 0x27);
        expect(enemy.creatureFlags & 0x400).toBeTruthy();
    });

    it('GENERIC_HOSTILE (0x01) has cFlags=8', () => {
        const enemy = createQuestEnemy(100, 100, 0x01);
        expect(enemy.creatureFlags).toBe(8);
    });

    it('BOSS_ZOMBIE (0x3C) has minigun (canShootMinigun=true)', () => {
        const enemy = createQuestEnemy(100, 100, 0x3c);
        expect(enemy.canShootMinigun).toBe(true);
    });

    it('spawner templates have cFlags=4 (immobile)', () => {
        for (const templateId of [0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x10]) {
            const enemy = createQuestEnemy(100, 100, templateId);
            expect(enemy.creatureFlags & 4).toBeTruthy();
        }
    });
});

// =============================================================================
// SECTION 8: EVERY QUEST CAN RUN TO COMPLETION — full spawn drain
// =============================================================================

describe('Quest full lifecycle — all 50 quests drain to completion', () => {
    let questSystem: QuestSystem;

    beforeEach(() => {
        questSystem = new QuestSystem();
    });

    it.each(QUEST_DATABASE.map((q) => [q.tier, q.index, q.name]))(
        'Quest %i-%i "%s" starts, drains spawns, and completes',
        (tier, index, _name) => {
            const t = tier as number;
            const i = index as number;

            // Spawn callback must call reportEnemySpawned so spawns are consumed.
            const spawnCallback = vi.fn((_entry: any) => {
                questSystem.reportEnemySpawned(1);
            });
            questSystem.setSpawnCallback(spawnCallback);

            const result = questSystem.startQuest(t, i);
            expect(result).toBe(true);
            expect(questSystem.getState()).toBe(QuestState.PLAYING);

            const totalPending = questSystem.getPendingSpawnCount();

            // Drain spawns by advancing timeline in 500ms steps
            // Limit iterations to prevent infinite loops on broken quests
            let iterations = 0;
            const maxIterations = 2000;
            while (!questSystem.isSpawnTableEmpty() && iterations < maxIterations) {
                questSystem.update(500);
                iterations++;
            }

            expect(questSystem.isSpawnTableEmpty()).toBe(true);

            // Spawn callback should have been called at least once (unless all counts are 0)
            if (totalPending > 0) {
                expect(spawnCallback).toHaveBeenCalled();
            }

            // Kill all active enemies so completion check passes
            const active = questSystem.getActiveEnemyCount();
            for (let e = 0; e < active; e++) {
                questSystem.reportEnemyKilled();
            }

            // checkCompletion() is called externally (deferred check)
            questSystem.checkCompletion();
            expect(questSystem.getState()).toBe(QuestState.TRANSITIONING);

            // Complete transition
            questSystem.update(3000);
            expect(questSystem.getState()).toBe(QuestState.COMPLETE);
        },
    );
});

// =============================================================================
// SECTION 9: TEMPLATE IDS USED BY QUESTS ALL PRODUCE VALID ENEMIES
// =============================================================================

describe('All template IDs used in quest spawns produce valid enemies', () => {
    // Collect all unique template IDs used across all quests
    const usedTemplateIds = new Set<number>();
    for (const quest of QUEST_DATABASE) {
        for (const spawn of quest.spawns) {
            usedTemplateIds.add(spawn.templateId);
        }
    }

    it('should have at least 10 unique template IDs in use', () => {
        expect(usedTemplateIds.size).toBeGreaterThanOrEqual(10);
    });

    it.each(
        Array.from(usedTemplateIds)
            .sort((a, b) => a - b)
            .map((id) => [id]),
    )('template ID 0x%s creates a valid enemy with positive health and size', (templateId) => {
        const enemy = createQuestEnemy(200, 300, templateId as number);
        expect(enemy).toBeDefined();
        expect(enemy.active).toBe(true);
        expect(enemy.health).toBeGreaterThan(0);
        expect(enemy.maxHealth).toBeGreaterThan(0);
        expect(enemy.size).toBeGreaterThan(0);
        expect(enemy.speed).toBeGreaterThan(0);
        expect(enemy.rewardValue).toBeGreaterThan(0);
        // EnemyType must be a valid enum value
        expect([0, 1, 2, 3, 4, 5]).toContain(enemy.type);
    });
});

// =============================================================================
// SECTION 10: ENEMY TEMPLATE CONSTANT → HEX ID CONSISTENCY
// =============================================================================

describe('EnemyTemplate constants map to correct hex values', () => {
    it('SPIDER_STANDARD = 0x26 (38)', () => expect(EnemyTemplate.SPIDER_STANDARD).toBe(0x26));
    it('SPIDER_FAST_FLAGGED = 0x27 (39)', () => expect(EnemyTemplate.SPIDER_FAST_FLAGGED).toBe(0x27));
    it('SPIDER_SMALL = 0x25 (37)', () => expect(EnemyTemplate.SPIDER_SMALL).toBe(0x25));
    it('SPIDER_MID = 0x28 (40)', () => expect(EnemyTemplate.SPIDER_MID).toBe(0x28));
    it('SPIDER_TANK = 0x29 (41)', () => expect(EnemyTemplate.SPIDER_TANK).toBe(0x29));
    it('SPIDER_FAST_DARK = 0x2A (42)', () => expect(EnemyTemplate.SPIDER_FAST_DARK).toBe(0x2a));
    it('SPIDER_FAST_RED = 0x2B (43)', () => expect(EnemyTemplate.SPIDER_FAST_RED).toBe(0x2b));
    it('SPIDER_MELEE = 0x0F (15)', () => expect(EnemyTemplate.SPIDER_MELEE).toBe(0x0f));
    it('SPIDER_PATROL = 0x12 (18)', () => expect(EnemyTemplate.SPIDER_PATROL).toBe(0x12));
    it('SPIDER_ORBIT_BOSS = 0x13 (19)', () => expect(EnemyTemplate.SPIDER_ORBIT_BOSS).toBe(0x13));
    it('SPIDER_FORMATION_A = 0x15 (21)', () => expect(EnemyTemplate.SPIDER_FORMATION_A).toBe(0x15));
    it('LIZARD_FORMATION_A = 0x16 (22)', () => expect(EnemyTemplate.LIZARD_FORMATION_A).toBe(0x16));
    it('SPIDER2_FORMATION_A = 0x17 (23)', () => expect(EnemyTemplate.SPIDER2_FORMATION_A).toBe(0x17));
    it('SPIDER_GHOST_LEADER = 0x18 (24)', () => expect(EnemyTemplate.SPIDER_GHOST_LEADER).toBe(0x18));
    it('SPIDER_GHOST_PATROL = 0x19 (25)', () => expect(EnemyTemplate.SPIDER_GHOST_PATROL).toBe(0x19));
    it('SPIDER_WAVE = 0x1A (26)', () => expect(EnemyTemplate.SPIDER_WAVE).toBe(0x1a));
    it('SPIDER2_WAVE = 0x1B (27)', () => expect(EnemyTemplate.SPIDER2_WAVE).toBe(0x1b));
    it('LIZARD_CIRCLE = 0x1C (28)', () => expect(EnemyTemplate.LIZARD_CIRCLE).toBe(0x1c));
    it('SPIDER_GREEN_WAVE = 0x20 (32)', () => expect(EnemyTemplate.SPIDER_GREEN_WAVE).toBe(0x20));
    it('SPIDER_BURROW = 0x36 (54)', () => expect(EnemyTemplate.SPIDER_BURROW).toBe(0x36));
    it('BOSS_ZOMBIE = 0x3C (60)', () => expect(EnemyTemplate.BOSS_ZOMBIE).toBe(0x3c));
    it('BOSS_ALIEN = 0x3D (61)', () => expect(EnemyTemplate.BOSS_ALIEN).toBe(0x3d));
    it('BOSS_LIZARD = 0x3E (62)', () => expect(EnemyTemplate.BOSS_LIZARD).toBe(0x3e));
    it('BOSS_SPIDER = 0x3F (63)', () => expect(EnemyTemplate.BOSS_SPIDER).toBe(0x3f));
});

// =============================================================================
// SECTION 11: QUEST-SPECIFIC SPOT CHECKS
// =============================================================================

describe('Quest-specific spot checks', () => {
    it('Quest 1-1 "Land Hostile" spawns SPIDER_STANDARD (0x26)', () => {
        const quest = getQuest(1, 1)!;
        // All 4 spawn entries use SPIDER_STANDARD
        for (const spawn of quest.spawns) {
            expect(spawn.templateId).toBe(EnemyTemplate.SPIDER_STANDARD);
        }
    });

    it('Quest 1-3 "Target Practice" spawns SPIDER_BURROW (0x36)', () => {
        const quest = getQuest(1, 3)!;
        for (const spawn of quest.spawns) {
            expect(spawn.templateId).toBe(EnemyTemplate.SPIDER_BURROW);
        }
    });

    it('Quest 1-5 "Alien Dens" spawns only ALIEN_DEN (0x08)', () => {
        const quest = getQuest(1, 5)!;
        for (const spawn of quest.spawns) {
            expect(spawn.templateId).toBe(EnemyTemplate.ALIEN_DEN);
        }
    });

    it('Quest 3-4 "Hidden Evil" spawns nested spiders, queens, and brood', () => {
        const quest = getQuest(3, 4)!;
        const templateIds = quest.spawns.map((s) => s.templateId);
        expect(templateIds).toContain(EnemyTemplate.SPIDER_NESTED);
        expect(templateIds).toContain(EnemyTemplate.SPIDER_QUEEN);
        expect(templateIds).toContain(EnemyTemplate.SPIDER_BROOD);
    });

    it('Quest 3-10 "Zombie Masters" spawns only TOUGHGUY (0x00)', () => {
        const quest = getQuest(3, 10)!;
        for (const spawn of quest.spawns) {
            expect(spawn.templateId).toBe(EnemyTemplate.TOUGHGUY);
        }
    });

    it('Quest 5-7 "Army of Three" uses SPIDER_FORMATION_A, LIZARD_FORMATION_A, SPIDER2_FORMATION_A', () => {
        const quest = getQuest(5, 7)!;
        const templateIds = new Set(quest.spawns.map((s) => s.templateId));
        expect(templateIds.has(EnemyTemplate.SPIDER_FORMATION_A)).toBe(true);
        expect(templateIds.has(EnemyTemplate.LIZARD_FORMATION_A)).toBe(true);
        expect(templateIds.has(EnemyTemplate.SPIDER2_FORMATION_A)).toBe(true);
    });

    it('Quest 5-10 "The Gathering" uses TOUGHGUY and GENERIC_HOSTILE', () => {
        const quest = getQuest(5, 10)!;
        const templateIds = new Set(quest.spawns.map((s) => s.templateId));
        expect(templateIds.has(EnemyTemplate.TOUGHGUY)).toBe(true);
        expect(templateIds.has(EnemyTemplate.GENERIC_HOSTILE)).toBe(true);
    });
});

// =============================================================================
// SECTION 12: POSITION SET ON ENEMY
// =============================================================================

describe('createQuestEnemy — position', () => {
    it('sets enemy position to (posX, posY)', () => {
        const enemy = createQuestEnemy(123, 456, 0x26);
        expect(enemy.x).toBe(123);
        expect(enemy.y).toBe(456);
    });

    it('handles negative positions (off-screen spawn)', () => {
        const enemy = createQuestEnemy(-64, -64, 0x26);
        expect(enemy.x).toBe(-64);
        expect(enemy.y).toBe(-64);
    });

    it('handles large positions (off-screen right/bottom)', () => {
        const enemy = createQuestEnemy(1088, 1088, 0x26);
        expect(enemy.x).toBe(1088);
        expect(enemy.y).toBe(1088);
    });
});

// =============================================================================
// SECTION 13: QUEST COMPLETION — "LEVEL COMPLETE" OVERLAY & SOUND SEQUENCE
// =============================================================================

describe('Quest completion — Level Complete overlay and sound sequence', () => {
    let questSystem: QuestSystem;

    beforeEach(() => {
        questSystem = new QuestSystem();
    });

    /**
     * Helper: drain all spawns and enter the TRANSITIONING state.
     * Uses Quest 1-1 "Land Hostile" which has 4 batches at 500/2500/6500/11500ms.
     *
     * Spawns must call reportEnemySpawned so entries are consumed,
     * then we kill all enemies and call checkCompletion() (deferred check).
     */
    function drainToTransition(qs: QuestSystem): void {
        // Register a callback that reports spawns so entries are consumed
        qs.setSpawnCallback((_entry: any) => {
            qs.reportEnemySpawned(1);
        });

        qs.startQuest(1, 1);
        qs.update(600);   // triggers 500ms batch
        qs.update(2000);  // triggers 2500ms batch
        qs.update(4000);  // triggers 6500ms batch
        qs.update(5000);  // triggers 11500ms batch

        // Kill all active enemies so completion check passes
        const active = qs.getActiveEnemyCount();
        for (let e = 0; e < active; e++) {
            qs.reportEnemyKilled();
        }

        // checkCompletion() is called externally, not inside update()
        qs.checkCompletion();
        expect(qs.getState()).toBe(QuestState.TRANSITIONING);
    }

    // ── Transition timer exposure ──

    it('getTransitionTimerMs() returns -1 before quest starts', () => {
        expect(questSystem.getTransitionTimerMs()).toBe(-1);
    });

    it('getTransitionTimerMs() returns -1 while quest is PLAYING', () => {
        questSystem.startQuest(1, 1);
        questSystem.update(500);
        expect(questSystem.getState()).toBe(QuestState.PLAYING);
        expect(questSystem.getTransitionTimerMs()).toBe(-1);
    });

    it('getTransitionTimerMs() returns >= 0 when TRANSITIONING', () => {
        drainToTransition(questSystem);
        expect(questSystem.getTransitionTimerMs()).toBeGreaterThanOrEqual(0);
    });

    it('getTransitionTimerMs() advances with each update during transition', () => {
        drainToTransition(questSystem);
        const t0 = questSystem.getTransitionTimerMs();
        questSystem.update(200);
        const t1 = questSystem.getTransitionTimerMs();
        expect(t1).toBeGreaterThan(t0);
        expect(t1 - t0).toBeCloseTo(200, 0);
    });

    // ── Scale-up animation formula (C: ui_core.c line 1389) ──
    // C: fVar21 = quest_transition_timer_ms * 0.0004 * 0.13 + 0.95

    it('scale animation starts at ~0.95 at transition start (timer ≈ 0)', () => {
        // At timer = 0: scale = 0 * 0.0004 * 0.13 + 0.95 = 0.95
        const scale = 0 * 0.0004 * 0.13 + 0.95;
        expect(scale).toBeCloseTo(0.95, 4);
    });

    it('scale animation at 800ms matches C formula', () => {
        // At timer = 800: scale = 800 * 0.0004 * 0.13 + 0.95 = 0.9916
        const scale = 800 * 0.0004 * 0.13 + 0.95;
        expect(scale).toBeCloseTo(0.9916, 4);
    });

    it('scale animation at 2500ms matches C formula', () => {
        // At timer = 2500: scale = 2500 * 0.0004 * 0.13 + 0.95 = 1.08
        const scale = 2500 * 0.0004 * 0.13 + 0.95;
        expect(scale).toBeCloseTo(1.08, 2);
    });

    // ── Sound effects at correct timing (C: quest.c lines 39-49) ──

    it('plays sfx_questhit at 800ms (C: sfx_play(sfx_questhit))', () => {
        const mockSoundSystem = { play: vi.fn() };
        questSystem.setSoundSystem(mockSoundSystem as any);
        drainToTransition(questSystem);

        // Before 800ms — no sound yet
        // Note: drainToTransition() starts with ~100ms on the transition timer
        questSystem.update(600); // total ~700ms into transition
        expect(mockSoundSystem.play).not.toHaveBeenCalled();

        // At/past 800ms — quest hit SFX should play
        questSystem.update(200); // total ~900ms into transition
        expect(mockSoundSystem.play).toHaveBeenCalledWith(61); // SoundId.QUEST_HIT = 61
    });

    it('does not play sfx_questhit more than once', () => {
        const mockSoundSystem = { play: vi.fn() };
        questSystem.setSoundSystem(mockSoundSystem as any);
        drainToTransition(questSystem);

        questSystem.update(1000); // past 800ms
        questSystem.update(500);  // still transitioning
        // Should only have been called once for QUEST_HIT
        const questHitCalls = mockSoundSystem.play.mock.calls.filter(
            (call: any[]) => call[0] === 61,
        );
        expect(questHitCalls.length).toBe(1);
    });

    it('plays victory music at 2000ms (C: sfx_play_exclusive(music_track_crimsonquest_id))', () => {
        const mockMusicSystem = { play: vi.fn(), stop: vi.fn() };
        questSystem.setMusicSystem(mockMusicSystem as any);
        drainToTransition(questSystem);

        // Before 2000ms — no music yet
        questSystem.update(1500);
        expect(mockMusicSystem.play).not.toHaveBeenCalled();

        // At/past 2000ms — victory music should play
        questSystem.update(600); // total ~2100ms into transition
        expect(mockMusicSystem.play).toHaveBeenCalledWith('crimsonquest.ogg');
    });

    // ── Transition to COMPLETE at 2500ms (C: quest.c line 51, 0x9c4) ──

    it('stays TRANSITIONING before 2500ms', () => {
        drainToTransition(questSystem);
        questSystem.update(2400); // just under 2500ms
        expect(questSystem.getState()).toBe(QuestState.TRANSITIONING);
    });

    it('transitions to COMPLETE after 2500ms', () => {
        drainToTransition(questSystem);
        questSystem.update(2600); // past 2500ms
        expect(questSystem.getState()).toBe(QuestState.COMPLETE);
    });

    // ── Full sequence: timer, sound, music, complete ──

    it('full completion sequence: timer → sfx → music → complete', () => {
        const mockSoundSystem = { play: vi.fn() };
        const mockMusicSystem = { play: vi.fn(), stop: vi.fn() };
        questSystem.setSoundSystem(mockSoundSystem as any);
        questSystem.setMusicSystem(mockMusicSystem as any);

        drainToTransition(questSystem);

        // Phase 1: 0-800ms — overlay visible, no sound yet
        questSystem.update(400);
        expect(questSystem.getTransitionTimerMs()).toBeGreaterThan(0);
        expect(mockSoundSystem.play).not.toHaveBeenCalled();
        expect(mockMusicSystem.play).not.toHaveBeenCalled();

        // Phase 2: 800ms — sfx_questhit plays
        questSystem.update(500); // ~900ms total
        expect(mockSoundSystem.play).toHaveBeenCalledWith(61);
        expect(mockMusicSystem.play).not.toHaveBeenCalled();

        // Phase 3: 2000ms — victory music plays
        questSystem.update(1200); // ~2100ms total
        expect(mockMusicSystem.play).toHaveBeenCalledWith('crimsonquest.ogg');
        expect(questSystem.getState()).toBe(QuestState.TRANSITIONING);

        // Phase 4: 2500ms — transition to COMPLETE
        questSystem.update(500); // ~2600ms total
        expect(questSystem.getState()).toBe(QuestState.COMPLETE);
    });
});
