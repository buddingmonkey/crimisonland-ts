/**
 * QuestEnemySpawner - Quest-mode enemy template creation
 *
 * Extracted from EnemySpawner.ts to reduce file size.
 * C code reference: creature_spawn_template @ lines 26070-27700
 */

import { Enemy, EnemyType, AIMode } from '../../entities/Enemy';
import { ProjectileType } from '../../data/WeaponData';

/**
 * Create an enemy for a specific quest template ID.
 *
 * Returns a fully configured Enemy ready to be added to the enemy list.
 * Returns null if templateId is unrecognized (falls back to a generic spider).
 *
 * C code reference: creature_spawn_template @ lines 26070-27700
 * Each template assigns exact type_id, health, move_speed, size, contact_damage,
 * reward_value, tint, flags, ai_mode, and optionally spawner-slot config.
 */
/**
 * Options for quest enemy difficulty scaling.
 * C: creature_spawn_template post-processing (lines 3579-3640)
 */
export interface QuestEnemyOptions {
    /** C: quest_fail_retry_count — number of times player has retried this quest */
    retryCount?: number;
    /** C: config_blob.hardcore — hardcore mode flag */
    hardcoreMode?: boolean;
}

export function createQuestEnemy(posX: number, posY: number, templateId: number, options?: QuestEnemyOptions): Enemy {
    // Helper: convert C move_speed to pixel speed (C: move_speed * 30.0)
    const cSpeed = (s: number) => s * 30.0;
    // Helper: random int in [0, max)
    const randInt = (max: number) => Math.floor(Math.random() * max);

    let enemyType: EnemyType;
    let health!: number;
    let moveSpeed!: number;
    let size!: number;
    let contactDamage!: number;
    let rewardValue!: number;
    let tintR = 1.0,
        tintG = 1.0,
        tintB = 1.0,
        tintA = 1.0;
    let cFlags = 0;
    let aiMode: AIMode = AIMode.CHASE_CIRCLE;
    let fireRate = 0;
    let orbitRadius = 0;
    let orbitAngle = 0;
    let projectileType: ProjectileType | 0 = 0;

    let isSpawner = false;
    let spawnInterval = 0;
    let spawnLimit = 100;
    let spawnChildTemplate = 0;
    let spawnInitialTimer = 1.0;

    switch (templateId) {
        // ===== BOSS / TOUGHGUY =====
        case 0x00: // TOUGHGUY - C line 27426, type_id=0 (Zombie)
            enemyType = EnemyType.Zombie;
            cFlags = 0x44;
            health = 8500;
            moveSpeed = 1.3;
            size = 64;
            contactDamage = 50;
            rewardValue = 6600;
            tintR = 0.6;
            tintG = 0.6;
            tintB = 1.0;
            tintA = 0.8;
            isSpawner = true;
            spawnInterval = 0.7;
            spawnLimit = 812;
            spawnChildTemplate = 0x41;
            break;

        // ===== GENERIC TEMPLATES (randomized stats) =====
        case 0x01: // C line 26135, type_id=4 (Alien)
            enemyType = EnemyType.Alien;
            health = 400;
            moveSpeed = 2.0;
            size = 80;
            contactDamage = 17;
            rewardValue = 1000;
            cFlags = 8;
            tintR = 0.8;
            tintG = 0.7;
            tintB = 0.4;
            break;

        case 0x03: {
            // C line 26870 - type_id=3 (Spider2)
            enemyType = EnemyType.Spider2;
            const s = randInt(15) + 38;
            size = s;
            health = s * 1.1428572 + 20;
            moveSpeed = randInt(18) * 0.1 + 1.1;
            rewardValue = s * 2 + 50;
            contactDamage = randInt(10) + 4;
            tintR = 0.6;
            tintG = 0.6;
            tintB = randInt(25) * 0.01 + 0.8;
            break;
        }
        case 0x04: {
            // C line 26976 - type_id=1 (Lizard)
            enemyType = EnemyType.Lizard;
            const s = randInt(15) + 38;
            size = s;
            health = s * 1.1428572 + 20;
            moveSpeed = randInt(18) * 0.1 + 1.1;
            rewardValue = s * 2 + 50;
            contactDamage = randInt(10) + 4;
            tintR = 0.67;
            tintG = 0.67;
            tintB = 1.0;
            break;
        }
        case 0x05: {
            // C line 26923 - type_id=4 (Alien)
            enemyType = EnemyType.Alien;
            const s = randInt(15) + 38;
            size = s;
            health = s * 1.1428572 + 20;
            moveSpeed = randInt(18) * 0.1 + 1.1;
            rewardValue = s * 2 + 50;
            contactDamage = randInt(10) + 4;
            tintR = 0.6;
            tintG = 0.6;
            tintB = randInt(25) * 0.01 + 0.8;
            break;
        }
        case 0x06: {
            // C line 26996 - type_id=2 (Spider)
            enemyType = EnemyType.Spider;
            const s = randInt(15) + 38;
            size = s;
            health = s * 1.1428572 + 20;
            moveSpeed = randInt(18) * 0.1 + 1.1;
            rewardValue = s * 2 + 50;
            contactDamage = randInt(10) + 4;
            tintR = 0.6;
            tintG = 0.6;
            tintB = randInt(25) * 0.01 + 0.8;
            break;
        }

        // ===== SPAWNER / NEST TEMPLATES =====
        case 0x07: // Nest variant 1 - C line 26734, type_id=2 (Spider)
            enemyType = EnemyType.Spider;
            health = 1000;
            moveSpeed = 2.0;
            size = 50;
            contactDamage = 0;
            rewardValue = 3000;
            cFlags = 4;
            tintR = 1.0;
            tintG = 1.0;
            tintB = 1.0;
            isSpawner = true;
            spawnInterval = 2.2;
            spawnChildTemplate = 0x1d;
            break;
        case 0x08: // Nest variant 2 - C line 27631, type_id=2 (Spider)
            enemyType = EnemyType.Spider;
            health = 1000;
            moveSpeed = 2.0;
            size = 50;
            contactDamage = 0;
            rewardValue = 3000;
            cFlags = 4;
            tintR = 1.0;
            tintG = 1.0;
            tintB = 1.0;
            isSpawner = true;
            spawnInterval = 2.8;
            spawnChildTemplate = 0x1d;
            break;
        case 0x09: // SENTINEL - C line 26712
            enemyType = EnemyType.Spider;
            health = 450;
            moveSpeed = 2.0;
            size = 40;
            contactDamage = 0;
            rewardValue = 1000;
            cFlags = 4;
            tintR = 1.0;
            tintG = 1.0;
            tintB = 1.0;
            isSpawner = true;
            spawnInterval = 2.0;
            spawnLimit = 16;
            spawnChildTemplate = 0x1d;
            break;
        case 0x0a: // MINE - C line 26213
            enemyType = EnemyType.Spider;
            health = 1000;
            moveSpeed = 1.5;
            size = 55;
            contactDamage = 0;
            rewardValue = 3000;
            cFlags = 4;
            tintR = 0.8;
            tintG = 0.7;
            tintB = 0.4;
            isSpawner = true;
            spawnInitialTimer = 2.0;
            spawnInterval = 5.0;
            spawnChildTemplate = 0x32;
            break;
        case 0x0b: // MINE_LARGE - C line 26268
            enemyType = EnemyType.Spider;
            health = 3500;
            moveSpeed = 1.5;
            size = 65;
            contactDamage = 0;
            rewardValue = 5000;
            cFlags = 4;
            tintR = 0.9;
            tintG = 0.1;
            tintB = 0.1;
            isSpawner = true;
            spawnInitialTimer = 2.0;
            spawnInterval = 6.0;
            spawnChildTemplate = 0x3c;
            break;
        case 0x0c: // Small spawner - C line 26694
            enemyType = EnemyType.Spider;
            health = 50;
            moveSpeed = 2.8;
            size = 32;
            contactDamage = 0;
            rewardValue = 1000;
            cFlags = 4;
            tintR = 0.9;
            tintG = 0.8;
            tintB = 0.4;
            isSpawner = true;
            spawnInitialTimer = 1.5; // C: timer_s = 1.5
            spawnInterval = 2.0;
            spawnChildTemplate = 0x31;
            break;
        case 0x0d: // Slow spawner - C line 27653
            enemyType = EnemyType.Spider;
            health = 50;
            moveSpeed = 1.3;
            size = 32;
            contactDamage = 0;
            rewardValue = 1000;
            cFlags = 4;
            tintR = 0.9;
            tintG = 0.8;
            tintB = 0.4;
            isSpawner = true;
            spawnInitialTimer = 2.0;
            spawnInterval = 6.0;
            spawnChildTemplate = 0x31;
            break;
        case 0x0e: // TURRET - C line 26343
            enemyType = EnemyType.Spider;
            health = 50;
            moveSpeed = 2.8;
            size = 32;
            contactDamage = 0;
            rewardValue = 5000;
            cFlags = 4;
            tintR = 0.9;
            tintG = 0.8;
            tintB = 0.4;
            isSpawner = true;
            spawnInitialTimer = 1.5; // C: timer_s = 1.5
            spawnInterval = 1.05;
            spawnLimit = 64;
            spawnChildTemplate = 0x1c;
            break;
        case 0x10: // NEST - C line 26183
            enemyType = EnemyType.Spider;
            health = 50;
            moveSpeed = 2.8;
            size = 32;
            contactDamage = 0;
            rewardValue = 800;
            cFlags = 4;
            tintR = 0.9;
            tintG = 0.8;
            tintB = 0.4;
            isSpawner = true;
            spawnInitialTimer = 1.5; // C: timer_s = 1.5
            spawnInterval = 2.3;
            spawnChildTemplate = 0x32;
            break;

        // ===== MELEE / GHOST-LIKE =====
        case 0x0f: // C line 27676, type_id=2 (Spider) — was misnamed "ZOMBIE_MELEE"
            enemyType = EnemyType.Spider;
            health = 20;
            moveSpeed = 2.9;
            size = 50;
            contactDamage = 35;
            rewardValue = 60;
            tintR = 0.665;
            tintG = 0.385;
            tintB = 0.259;
            tintA = 0.56;
            aiMode = AIMode.CHASE_CIRCLE;
            break;

        // ===== FORMATION TEMPLATES (leader + followers) =====
        case 0x11: // LIZARD_KING - C line 26080, type_id=1 (Lizard)
            enemyType = EnemyType.Lizard;
            health = 1500;
            moveSpeed = 2.1;
            size = 69;
            contactDamage = 150;
            rewardValue = 1000;
            aiMode = AIMode.CLOSE_CIRCLE;
            tintR = 0.99;
            tintG = 0.99;
            tintB = 0.21;
            break;
        case 0x12: // C line 26115, type_id=2 (Spider) — was misnamed "LIZARD_PATROL"
            enemyType = EnemyType.Spider;
            health = 200;
            moveSpeed = 2.2;
            size = 55;
            contactDamage = 14;
            rewardValue = 600;
            tintR = 0.65;
            tintG = 0.85;
            tintB = 0.97;
            break;
        case 0x13: // C line 26155, type_id=2 (Spider), ai_mode=6 — was misnamed "LIZARD_BOSS"
            enemyType = EnemyType.Spider;
            health = 20;
            moveSpeed = 2.9;
            size = 50;
            contactDamage = 35;
            rewardValue = 60;
            tintR = 0.665;
            tintG = 0.385;
            tintB = 0.259;
            tintA = 0.56;
            aiMode = AIMode.ORBIT_ANGLE;
            break;
        case 0x14: // Formation leader A - C line 26462, type_id=2 (Spider)
            enemyType = EnemyType.Spider;
            health = 1500;
            moveSpeed = 2.0;
            size = 50;
            contactDamage = 40;
            rewardValue = 600;
            aiMode = AIMode.DIRECT_CHASE;
            break;
        case 0x15: // C line 26387, type_id=2 (Spider) — was misnamed "ALIEN_BOSS"
            enemyType = EnemyType.Spider;
            health = 1500;
            moveSpeed = 2.0;
            size = 60;
            contactDamage = 40;
            rewardValue = 600;
            aiMode = AIMode.DIRECT_CHASE;
            break;
        case 0x16: // C line 26505, type_id=1 (Lizard) — was misnamed "ALIEN_MECH"
            enemyType = EnemyType.Lizard;
            health = 1500;
            moveSpeed = 2.0;
            size = 64;
            contactDamage = 40;
            rewardValue = 600;
            aiMode = AIMode.DIRECT_CHASE;
            break;
        case 0x17: // C line 26548, type_id=3 (Spider2) — was misnamed "ALIEN_DRONE"
            enemyType = EnemyType.Spider2;
            health = 1500;
            moveSpeed = 2.0;
            size = 60;
            contactDamage = 40;
            rewardValue = 600;
            aiMode = AIMode.DIRECT_CHASE;
            break;
        case 0x18: // C line 26586, type_id=2 (Spider) — was misnamed "GHOST_PATROL_END"
            enemyType = EnemyType.Spider;
            health = 500;
            moveSpeed = 2.0;
            size = 40;
            contactDamage = 40;
            rewardValue = 600;
            aiMode = AIMode.DIRECT_CHASE;
            break;
        case 0x19: // C line 26628, type_id=2 (Spider) — was misnamed "GHOST_PATROL"
            enemyType = EnemyType.Spider;
            health = 50;
            moveSpeed = 3.8;
            size = 55;
            contactDamage = 40;
            rewardValue = 300;
            tintR = 0.95;
            tintG = 0.55;
            tintB = 0.37;
            break;

        // ===== WANDERING / CIRCLING =====
        case 0x1a: // C line 26746, type_id=2 (Spider) — was misnamed "ZOMBIE_WAVE"
            enemyType = EnemyType.Spider;
            health = 50;
            moveSpeed = 2.4;
            size = 50;
            contactDamage = 5;
            rewardValue = 125;
            aiMode = AIMode.CLOSE_CIRCLE;
            tintR = randInt(40) * 0.01 + 0.5;
            tintG = tintR;
            tintB = 1.0;
            break;
        case 0x1b: // C line 26757, type_id=3 (Spider2) — was misnamed "ALIEN_WAVE"
            enemyType = EnemyType.Spider2;
            health = 40;
            moveSpeed = 2.4;
            size = 50;
            contactDamage = 5;
            rewardValue = 125;
            aiMode = AIMode.CLOSE_CIRCLE;
            tintR = randInt(40) * 0.01 + 0.5;
            tintG = tintR;
            tintB = 1.0;
            break;
        case 0x1c: // C line 27614, type_id=1 (Lizard) — was misnamed "GHOST"
            enemyType = EnemyType.Lizard;
            health = 50;
            moveSpeed = 2.4;
            size = 50;
            contactDamage = 5;
            rewardValue = 125;
            aiMode = AIMode.CLOSE_CIRCLE;
            tintR = randInt(40) * 0.01 + 0.5;
            tintG = tintR;
            tintB = 1.0;
            break;

        // ===== RANDOM-STAT WAVE TEMPLATES =====
        case 0x1d: {
            // Spider child (spawned by nests) - C line 27109
            enemyType = EnemyType.Spider;
            const s = randInt(20) + 35;
            size = s;
            health = s * 1.1428572 + 10;
            moveSpeed = randInt(15) * 0.1 + 1.1;
            rewardValue = randInt(100) + 50;
            contactDamage = randInt(10) + 4;
            tintR = randInt(50) * 0.001 + 0.6;
            tintG = randInt(50) * 0.01 + 0.5;
            tintB = randInt(50) * 0.001 + 0.6;
            break;
        }
        case 0x1e: {
            // Tougher spider child - C line 27133
            enemyType = EnemyType.Spider;
            const s = randInt(30) + 35;
            size = s;
            health = s * 2.2857144 + 10;
            moveSpeed = randInt(17) * 0.1 + 1.5;
            rewardValue = randInt(200) + 50;
            contactDamage = randInt(30) + 4;
            tintR = randInt(50) * 0.001 + 0.6;
            tintG = randInt(50) * 0.001 + 0.6;
            tintB = randInt(50) * 0.01 + 0.5;
            break;
        }
        case 0x1f: {
            // Heavy spider child - C line 27158
            enemyType = EnemyType.Spider;
            const s = randInt(30) + 45;
            size = s;
            health = s * 3.7142856 + 30;
            moveSpeed = randInt(21) * 0.1 + 1.6;
            rewardValue = randInt(200) + 80;
            contactDamage = randInt(35) + 8;
            tintR = randInt(50) * 0.01 + 0.5;
            tintG = randInt(50) * 0.001 + 0.6;
            tintB = randInt(50) * 0.001 + 0.6;
            break;
        }
        case 0x20: {
            // Green spider wave - C line 26849
            enemyType = EnemyType.Spider;
            const s = randInt(30) + 40;
            size = s;
            health = s * 1.1428572 + 20;
            moveSpeed = randInt(18) * 0.1 + 1.1;
            rewardValue = s * 2 + 50;
            contactDamage = randInt(10) + 4;
            tintR = 0.3;
            tintG = randInt(40) * 0.01 + 0.6;
            tintB = 0.3;
            break;
        }

        // ===== SPIDER SPECIALS =====
        case 0x21: // SPIDER_NESTED - C line 27238
            enemyType = EnemyType.Spider;
            health = 53;
            moveSpeed = 1.7;
            size = 55;
            contactDamage = 8;
            rewardValue = 120;
            tintR = 0.7;
            tintG = 0.1;
            tintB = 0.51;
            tintA = 0.5;
            break;
        case 0x22: // SPIDER_QUEEN - C line 27249
            enemyType = EnemyType.Spider;
            health = 25;
            moveSpeed = 1.7;
            size = 50;
            contactDamage = 8;
            rewardValue = 150;
            tintR = 0.1;
            tintG = 0.7;
            tintB = 0.51;
            tintA = 0.05;
            break;
        case 0x23: // SPIDER_BROOD - C line 27262
            enemyType = EnemyType.Spider;
            health = 5;
            moveSpeed = 1.7;
            size = 45;
            contactDamage = 8;
            rewardValue = 180;
            tintR = 0.1;
            tintG = 0.7;
            tintB = 0.51;
            tintA = 0.04;
            break;

        // ===== STANDARD ENEMIES =====
        case 0x24: // Green enemy - C line 27183, type_id=2 (Spider)
            enemyType = EnemyType.Spider;
            health = 20;
            moveSpeed = 2.0;
            size = 50;
            contactDamage = 4;
            rewardValue = 110;
            tintR = 0.1;
            tintG = 0.7;
            tintB = 0.11;
            break;
        case 0x25: // C line 27196, type_id=2 (Spider) — was misnamed "ZOMBIE_SLOW"
            enemyType = EnemyType.Spider;
            health = 25;
            moveSpeed = 2.5;
            size = 30;
            contactDamage = 3;
            rewardValue = 125;
            tintR = 0.1;
            tintG = 0.8;
            tintB = 0.11;
            break;
        case 0x26: // C line 27209, type_id=2 (Spider) — was misnamed "ZOMBIE"
            enemyType = EnemyType.Spider;
            health = 50;
            moveSpeed = 2.2;
            size = 45;
            contactDamage = 10;
            rewardValue = 125;
            tintR = 0.6;
            tintG = 0.8;
            tintB = 0.6;
            break;
        case 0x27: // C line 27222, type_id=2 (Spider) — was misnamed "ZOMBIE_FAST"
            enemyType = EnemyType.Spider;
            health = 50;
            moveSpeed = 2.1;
            size = 45;
            contactDamage = 10;
            rewardValue = 125;
            cFlags = 0x400;
            tintR = 1.0;
            tintG = 0.8;
            tintB = 0.1;
            break;
        case 0x28: // C line 27580, type_id=2 (Spider) — was misnamed "ALIEN"
            enemyType = EnemyType.Spider;
            health = 50;
            moveSpeed = 1.7;
            size = 55;
            contactDamage = 8;
            rewardValue = 150;
            tintR = 0.7;
            tintG = 0.1;
            tintB = 0.51;
            break;
        case 0x29: // C line 27276, type_id=2 (Spider) — was misnamed "ALIEN_FAST"
            enemyType = EnemyType.Spider;
            health = 800;
            moveSpeed = 2.5;
            size = 70;
            contactDamage = 20;
            rewardValue = 450;
            tintR = 0.8;
            tintG = 0.8;
            tintB = 0.8;
            break;
        case 0x2a: // C line 27289, type_id=2 (Spider) — was misnamed "LIZARD"
            enemyType = EnemyType.Spider;
            health = 50;
            moveSpeed = 3.1;
            size = 60;
            contactDamage = 8;
            rewardValue = 300;
            tintR = 0.3;
            tintG = 0.3;
            tintB = 0.3;
            break;
        case 0x2b: // C line 27302, type_id=2 (Spider) — was misnamed "LIZARD_FAST"
            enemyType = EnemyType.Spider;
            health = 30;
            moveSpeed = 3.6;
            size = 35;
            contactDamage = 20;
            rewardValue = 450;
            tintR = 1.0;
            tintG = 0.3;
            tintB = 0.3;
            break;
        case 0x2c: // SPIDER - C line 27312, type_id=2 (Spider)
            enemyType = EnemyType.Spider;
            health = 3800;
            moveSpeed = 2.0;
            size = 80;
            contactDamage = 40;
            rewardValue = 1500;
            tintR = 0.85;
            tintG = 0.2;
            tintB = 0.2;
            break;
        case 0x2d: // SPIDER_LARGE - C line 27325, type_id=2 (Spider)
            enemyType = EnemyType.Spider;
            health = 45;
            moveSpeed = 3.1;
            size = 38;
            contactDamage = 3;
            rewardValue = 200;
            tintR = 0.0;
            tintG = 0.9;
            tintB = 0.8;
            aiMode = AIMode.DIRECT_CHASE;
            break;
        case 0x2e: {
            // LIZARD_WAVE - C line 27070
            enemyType = EnemyType.Lizard;
            const s = randInt(30) + 40;
            size = s;
            health = s * 1.1428572 + 20;
            moveSpeed = randInt(18) * 0.1 + 1.1;
            rewardValue = s * 2 + 50;
            contactDamage = randInt(10) + 4;
            tintR = randInt(40) * 0.01 + 0.6;
            tintG = randInt(40) * 0.01 + 0.6;
            tintB = randInt(40) * 0.01 + 0.6;
            break;
        }
        case 0x2f: // C line 27339, type_id=1 (Lizard)
            enemyType = EnemyType.Lizard;
            health = 20;
            moveSpeed = 2.5;
            size = 45;
            contactDamage = 4;
            rewardValue = 150;
            tintR = 0.8;
            tintG = 0.8;
            tintB = 0.8;
            break;
        case 0x30: // LIZARD_KING_CIRCLE - C line 27352, type_id=1 (Lizard)
            enemyType = EnemyType.Lizard;
            health = 1000;
            moveSpeed = 2.0;
            size = 65;
            contactDamage = 10;
            rewardValue = 400;
            tintR = 0.9;
            tintG = 0.8;
            tintB = 0.1;
            break;
        case 0x31: {
            // Lizard child (spawned by nests) - C line 26788
            enemyType = EnemyType.Lizard;
            const s = randInt(30) + 40;
            size = s;
            health = s * 1.1428572 + 10;
            moveSpeed = randInt(18) * 0.1 + 1.1;
            rewardValue = s * 2 + 50;
            contactDamage = s * 0.14 + 4;
            tintR = randInt(30) * 0.01 + 0.6;
            tintG = tintR;
            tintB = 0.38;
            break;
        }
        case 0x32: {
            // Spider2 child (spawned by nests) - C line 27594
            enemyType = EnemyType.Spider2;
            const s = randInt(25) + 40;
            size = s;
            health = s * 1.1428572 + 10;
            moveSpeed = randInt(17) * 0.1 + 1.1;
            rewardValue = s * 2 + 50;
            contactDamage = randInt(10) + 4;
            const tBase = randInt(40) * 0.01 + 0.6;
            tintR = tBase;
            tintG = tBase;
            tintB = tBase;
            break;
        }
        case 0x33: {
            // C line 26807
            enemyType = EnemyType.Spider2;
            const s = randInt(15) + 45;
            size = s;
            health = s * 1.1428572 + 20;
            moveSpeed = randInt(18) * 0.1 + 1.1;
            rewardValue = s * 2 + 50;
            contactDamage = randInt(10) + 4;
            tintR = randInt(40) * 0.01 + 0.6;
            tintG = 0.5;
            tintB = 0.5;
            break;
        }
        case 0x34: {
            // C line 26828
            enemyType = EnemyType.Spider2;
            const s = randInt(20) + 40;
            size = s;
            health = s * 1.1428572 + 20;
            moveSpeed = randInt(18) * 0.1 + 1.1;
            rewardValue = s * 2 + 50;
            contactDamage = randInt(10) + 4;
            tintR = 0.5;
            tintG = randInt(40) * 0.01 + 0.6;
            tintB = 0.5;
            break;
        }
        case 0x35: {
            // C line 27049
            enemyType = EnemyType.Alien;
            const s = randInt(10) + 30;
            size = s;
            health = s * 1.1428572 + 20;
            moveSpeed = randInt(18) * 0.1 + 1.1;
            rewardValue = s * 2 + 50;
            contactDamage = randInt(10) + 4;
            tintR = 0.8;
            tintG = randInt(20) * 0.01 + 0.8;
            tintB = 0.8;
            break;
        }
        case 0x36: // C line 27093, type_id=2 (Spider) — ALIEN_AI7_ORBITER
            enemyType = EnemyType.Spider;
            health = 10;
            moveSpeed = 1.8;
            size = 50;
            contactDamage = 40;
            rewardValue = 150;
            aiMode = AIMode.BURROW;
            orbitRadius = 1.5; // C line 2900: 0x3fc00000 = 1.5f — hold timer before transitioning to orbit
            tintR = 0.65;
            tintG = randInt(5) * 0.01 + 0.65;
            tintB = 0.95;
            break;

        // ===== SHOOTER / FAST TEMPLATES =====
        case 0x37: // Minigun shooter - C line 27468, type_id=4 (Alien)
            enemyType = EnemyType.Alien;
            health = 50;
            moveSpeed = 3.2;
            contactDamage = 10;
            rewardValue = 433;
            cFlags = 0x100;
            size = (Math.random() < 0.5 ? 0 : randInt(4)) + 41;
            tintR = 1.0;
            tintG = 0.75;
            tintB = 0.1;
            break;
        case 0x38: // Fast spider boss var - C line 27448, type_id=3 (Spider2)
            enemyType = EnemyType.Spider2;
            health = 50;
            moveSpeed = 4.8;
            contactDamage = 10;
            rewardValue = 433;
            cFlags = 0x80;
            size = (Math.random() < 0.5 ? 0 : randInt(4)) + 41;
            tintR = 1.0;
            tintG = 0.75;
            tintB = 0.1;
            break;
        case 0x39: // Fast weak - C line 27488, type_id=3 (Spider2)
            enemyType = EnemyType.Spider2;
            health = 4;
            moveSpeed = 4.8;
            contactDamage = 10;
            rewardValue = 50;
            cFlags = 0x80;
            size = (Math.random() < 0.5 ? 0 : randInt(4)) + 26;
            tintR = 0.8;
            tintG = 0.65;
            tintB = 0.1;
            break;

        // ===== BOSS TEMPLATES =====
        case 0x3a: // BOSS_ZOMBIE_V2 (plasma) - C line 27508
            enemyType = EnemyType.Spider2;
            health = 4500;
            moveSpeed = 2.0;
            size = 64;
            contactDamage = 50;
            rewardValue = 4500;
            cFlags = 0x10; // plasma shooter
            fireRate = 0.9;
            orbitAngle = 0.9; // C: orbit_angle = 0.9 (stored for completeness)
            break;
        case 0x3b: // Boss - C line 27365
            enemyType = EnemyType.Spider2;
            health = 1200;
            moveSpeed = 2.0;
            size = 70;
            contactDamage = 20;
            rewardValue = 4000;
            tintR = 0.9;
            tintG = 0.0;
            tintB = 0.0;
            break;
        case 0x3c: // BOSS_ZOMBIE (minigun) - C line 27378
            enemyType = EnemyType.Spider2;
            health = 200;
            moveSpeed = 2.0;
            size = 40;
            contactDamage = 20;
            rewardValue = 200;
            cFlags = 0x100; // minigun shooter
            orbitAngle = 1.0; // User-tuned: ~1 shot/sec (C cooldown formula adds 0–0.3s random)
            projectileType = ProjectileType.SPIDER_PLASMA; // C: PROJECTILE_TYPE_SPIDER_PLASMA (green)
            aiMode = AIMode.DIRECT_CHASE;
            tintR = 0.9;
            tintG = 0.1;
            tintB = 0.1;
            break;
        case 0x3d: {
            // BOSS_ALIEN - C line 27396
            enemyType = EnemyType.Spider2;
            health = 70;
            moveSpeed = 2.6;
            rewardValue = 120;
            const s = randInt(7) + 45;
            size = s;
            contactDamage = s * 0.22;
            const t = randInt(20) * 0.01 + 0.8;
            tintR = t;
            tintG = t;
            tintB = t;
            break;
        }
        case 0x3e: // BOSS_LIZARD - C line 27413
            enemyType = EnemyType.Spider2;
            health = 1000;
            moveSpeed = 2.8;
            size = 64;
            contactDamage = 40;
            rewardValue = 500;
            break;
        case 0x3f: // BOSS_SPIDER - C line 27567
            enemyType = EnemyType.Spider2;
            health = 200;
            moveSpeed = 2.3;
            size = 35;
            contactDamage = 20;
            rewardValue = 210;
            tintR = 0.7;
            tintG = 0.4;
            tintB = 0.1;
            break;

        // ===== SWARM TEMPLATES =====
        case 0x40: // SWARM - C line 27526, type_id=3 (Spider2)
            enemyType = EnemyType.Spider2;
            health = 70;
            moveSpeed = 2.2;
            size = 45;
            contactDamage = 5;
            rewardValue = 160;
            tintR = 0.5;
            tintG = 0.6;
            tintB = 0.9;
            break;
        case 0x41: {
            // SWARM_SMALL - C line 26770, type_id=0 (Zombie)
            enemyType = EnemyType.Zombie;
            const s = randInt(30) + 40;
            size = s;
            health = s * 1.1428572 + 10;
            moveSpeed = s * 0.0025 + 0.9;
            rewardValue = s * 2 + 50;
            contactDamage = randInt(10) + 4;
            const t = randInt(40) * 0.01 + 0.6;
            tintR = t;
            tintG = t;
            tintB = t;
            break;
        }
        case 0x42: // SWARM_MEDIUM - C line 27539, type_id=0 (Zombie)
            enemyType = EnemyType.Zombie;
            health = 200;
            moveSpeed = 1.7;
            size = 45;
            contactDamage = 15;
            rewardValue = 160;
            tintR = 0.9;
            tintG = 0.9;
            tintB = 0.9;
            break;
        case 0x43: // SWARM_LEADER - C line 27552, type_id=0 (Zombie)
            enemyType = EnemyType.Zombie;
            health = 2000;
            moveSpeed = 2.1;
            size = 70;
            contactDamage = 15;
            rewardValue = 460;
            tintR = 0.2;
            tintG = 0.6;
            tintB = 0.1;
            break;

        default: {
            // Unknown templates - use random spider stats
            enemyType = EnemyType.Spider;
            const s = randInt(20) + 40;
            size = s;
            health = s * 1.1428572 + 20;
            moveSpeed = randInt(18) * 0.1 + 1.1;
            rewardValue = s * 2 + 50;
            contactDamage = randInt(10) + 4;
            tintR = 0.8;
            tintG = 0.8;
            tintB = 0.8;
            break;
        }
    }

    // C post-processing: auto-promote Spider2 (type_id=3) — lines 3569-3573
    // If type_id==3 and no plasma flag (0x10) and no fast flag (0x80), add 0x80 + speed boost
    if (enemyType === EnemyType.Spider2 && !(cFlags & 0x10) && !(cFlags & 0x80)) {
        cFlags |= 0x80;
        moveSpeed *= 1.2;
    }

    // Create enemy at specified position
    const enemy = new Enemy(posX, posY, enemyType);
    enemy.active = true;

    // Apply computed stats
    enemy.health = health;
    enemy.maxHealth = health;
    enemy.speed = cSpeed(moveSpeed);
    enemy.maxSpeed = cSpeed(moveSpeed);
    enemy.size = size;
    // NOTE: hitboxSize is intentionally NOT set here.
    // C code always initializes hitbox_size to 16.0 at spawn (creatures.c line 83).
    // hitboxSize is a death-countdown/liveness flag, NOT the visual size.
    // Enemy class default (16.0) is correct.
    enemy.damage = contactDamage;
    enemy.rewardValue = rewardValue;

    // Tinting
    enemy.tintR = tintR;
    enemy.tintG = tintG;
    enemy.tintB = tintB;
    enemy.tintA = tintA;

    // Flags
    enemy.creatureFlags = cFlags;
    enemy.aiMode = aiMode;
    enemy.orbitRadius = orbitRadius;

    // C creatures.c L3570-3572: initialize link_index for stop-and-go timer
    // When flag 0x80 is set (auto-promoted or explicit), link_index starts at 0
    if (cFlags & 0x80) {
        enemy.linkIndex = 0;
    }

    // Heading + orbit phase
    // C creature_spawn line 1824: heading = (rand() % 0x13a) * 0.01 → 0 to ~3.14
    enemy.angle = Math.floor(Math.random() * 0x13a) * 0.01;
    // C creature_alloc_slot line 1730: phase_seed = rand() & 0x17f → integer 0-383
    enemy.phaseSeed = Math.floor(Math.random() * 0x180);

    // Shooter flags
    if (cFlags & 0x10) {
        enemy.canShootPlasma = true;
        if (fireRate > 0) enemy.fireRate = fireRate;
    }
    if (cFlags & 0x100) {
        enemy.canShootMinigun = true;
        if (fireRate > 0) enemy.fireRate = fireRate;
        // C: orbit_angle is the base cooldown for minigun fire rate formula
        if (orbitAngle > 0) enemy.orbitAngle = orbitAngle;
        // C: orbit_radius.projectile_type is the projectile type for minigun enemies
        if (projectileType !== 0) enemy.projectileType = projectileType;
    }

    // Spawner slot setup
    if (isSpawner) {
        enemy.isNestSpawner = true;
        enemy.nestSpawnTimer = spawnInitialTimer;
        enemy.nestSpawnInterval = spawnInterval;
        enemy.nestChildTemplate = spawnChildTemplate;
        enemy.nestSpawnLimit = spawnLimit;
        enemy.nestSpawnCount = 0;
    }

    // === C post-processing: difficulty scaling (creatures.c lines 3579-3640) ===
    const retryCount = options?.retryCount ?? 0;
    const hardcoreMode = options?.hardcoreMode ?? false;

    if (hardcoreMode) {
        // C lines 3627-3631: hardcore mode buffs enemies
        enemy.speed *= 1.05;
        enemy.maxSpeed *= 1.05;
        enemy.damage *= 1.40;
        enemy.health *= 1.20;
        enemy.maxHealth *= 1.20;

        // C lines 3632-3639: spawner interval decreases by 0.2s
        if (enemy.isNestSpawner) {
            enemy.nestSpawnInterval = Math.max(0.1, enemy.nestSpawnInterval - 0.2);
        }
    } else if (retryCount > 0) {
        // C lines 3584-3625: retry difficulty scaling (normal mode only)
        let speedMult: number;
        let damageMult: number;
        let healthMult: number;
        let rewardMult: number;

        switch (retryCount) {
            case 1:
                speedMult = 0.95; damageMult = 0.95; healthMult = 0.95; rewardMult = 0.90;
                break;
            case 2:
                speedMult = 0.90; damageMult = 0.90; healthMult = 0.90; rewardMult = 0.85;
                break;
            case 3:
                speedMult = 0.80; damageMult = 0.80; healthMult = 0.80; rewardMult = 0.85;
                break;
            case 4:
                speedMult = 0.70; damageMult = 0.70; healthMult = 0.70; rewardMult = 0.80;
                break;
            default: // 5+
                speedMult = 0.60; damageMult = 0.50; healthMult = 0.50; rewardMult = 0.80;
                break;
        }

        enemy.speed *= speedMult;
        enemy.maxSpeed *= speedMult;
        enemy.damage *= damageMult;
        enemy.health *= healthMult;
        enemy.maxHealth *= healthMult;
        enemy.rewardValue *= rewardMult;

        // C lines 3617-3624: spawner interval increases on retries
        if (enemy.isNestSpawner) {
            const intervalBoost = Math.min(retryCount * 0.35, 3.0);
            enemy.nestSpawnInterval += intervalBoost;
        }
    }

    // C lines 3579-3583: normal mode spawner interval +0.2s
    // (already handled via the hardcore branch above for spawners)
    if (!hardcoreMode && enemy.isNestSpawner) {
        enemy.nestSpawnInterval += 0.2;
    }

    return enemy;
}
