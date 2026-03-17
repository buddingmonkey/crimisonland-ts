/**
 * SurvivalSpawner - Survival mode enemy creation extracted from EnemySpawner.ts.
 *
 * Port of survival_spawn_creature @ 00407510 in crimsonland.exe_decompiled.c
 */

import { Enemy, EnemyType } from '../../entities/Enemy';

/**
 * Create a survival-mode enemy with type/stats based on player experience.
 * Returns null if creation is skipped (caller manages capacity).
 *
 * @param x - spawn X
 * @param y - spawn Y
 * @param experience - player experience (drives enemy type selection and scaling)
 */
export function createSurvivalEnemy(x: number, y: number, experience: number): Enemy {
    const enemy = new Enemy(x, y);

    // Select type based on experience (C survival_spawn_creature lines 23-73)
    let typeId = EnemyType.Spider; // C default: type_id = 2
    const rand1 = Math.floor(Math.random() * 10);

    if (experience < 12000) {
        typeId = rand1 < 9 ? EnemyType.Spider : EnemyType.Spider2;
    } else if (experience < 25000) {
        if (rand1 < 4) typeId = EnemyType.Zombie;
        else typeId = EnemyType.Spider2;
        if (rand1 > 8) typeId = EnemyType.Spider;
    } else if (experience < 42000) {
        if (rand1 < 5) {
            typeId = EnemyType.Spider;
        } else {
            typeId = Math.random() < 0.5 ? EnemyType.Spider2 : EnemyType.Alien;
        }
    } else if (experience < 50000) {
        typeId = EnemyType.Spider;
    } else if (experience < 90000) {
        typeId = EnemyType.Alien;
    } else {
        if (experience > 110000) {
            if (rand1 < 6) typeId = EnemyType.Spider;
            else if (rand1 < 9) typeId = EnemyType.Alien;
            else typeId = EnemyType.Zombie;
        } else {
            typeId = EnemyType.Zombie;
        }
    }

    // Special override: 1/32 chance for Spider2 (C line 76-78: type_id = 3)
    if ((Math.floor(Math.random() * 256) & 0x1f) === 2) {
        typeId = EnemyType.Spider2;
    }

    enemy.type = typeId;
    enemy.active = true;

    // Size (line 5100)
    enemy.size = Math.floor(Math.random() * 20) + 44;

    // Heading (line 5102)
    enemy.angle = Math.floor(Math.random() * 314) * 0.01;

    // Move speed (line 5104)
    let moveSpeed = (experience / 4000) * 0.045 + 0.9;

    // Type-specific speed modifiers (C lines 90-109)
    if (typeId === EnemyType.Spider2) {
        moveSpeed *= 1.3;
        enemy.creatureFlags |= 0x80; // C flag for fast type
    }
    if (typeId === EnemyType.Zombie) {
        moveSpeed *= 0.6;
        if (moveSpeed < 1.3) moveSpeed = 1.3;
    }
    if (moveSpeed > 3.5) moveSpeed = 3.5;

    enemy.speed = moveSpeed * 25.0; // Scale for our coordinate system
    enemy.maxSpeed = enemy.speed;

    // Health (C lines 96-106)
    let health = experience * 0.00125 + Math.floor(Math.random() * 16) + 52.0;
    if (typeId === EnemyType.Zombie) {
        health *= 1.5;
    }
    enemy.health = health;
    enemy.maxHealth = health;

    // Contact damage (line 5166)
    enemy.damage = enemy.size * 0.0952381;

    // Color tinting (lines 5127-5162)
    if (experience < 50000) {
        enemy.tintR = 1.0 - 1.0 / (experience / 1000 + 10.0);
        enemy.tintG = Math.random() * 10 * 0.01 + 0.9 - 1.0 / (experience / 10000 + 10.0);
        enemy.tintB = Math.random() * 10 * 0.01 + 0.7;
    } else if (experience < 100000) {
        enemy.tintR = 0.9 - 1.0 / (experience / 1000 + 10.0);
        enemy.tintG = Math.random() * 10 * 0.01 + 0.8 - 1.0 / (experience / 10000 + 10.0);
        enemy.tintB = (experience - 50000) * 0.000006 + Math.random() * 10 * 0.01 + 0.7;
    } else {
        enemy.tintR = 1.0 - 1.0 / (experience / 1000 + 10.0);
        enemy.tintG = Math.random() * 10 * 0.01 + 0.9 - 1.0 / (experience / 10000 + 10.0);
        let tintB = Math.random() * 10 * 0.01 + 1.0 - (experience - 100000) * 0.000003;
        if (tintB < 0.5) tintB = 0.5;
        enemy.tintB = tintB;
    }

    // Reward value (C lines 152-158)
    if (enemy.rewardValue === 0) {
        enemy.rewardValue = health * 0.4 + enemy.damage * 0.8 + moveSpeed * 5.0 + (Math.floor(Math.random() * 10) + 10);
    }

    // Rare enemy tiers (C lines 159-213)
    // Tier 1: Red (1/90 chance)
    const rareRoll1 = Math.floor(Math.random() * 180);
    if (rareRoll1 < 2) {
        enemy.tintR = 0.9;
        enemy.health = 65.0;
        enemy.tintG = 0.4;
        enemy.rewardValue = 320.0;
        enemy.tintB = 0.4;
        enemy.tintA = 1.0;
    } else {
        // Tier 2: Green (1/120 chance)
        const rareRoll2 = Math.floor(Math.random() * 240);
        if (rareRoll2 < 2) {
            enemy.tintR = 0.4;
            enemy.health = 85.0;
            enemy.tintG = 0.9;
            enemy.rewardValue = 420.0;
            enemy.tintB = 0.4;
            enemy.tintA = 1.0;
        } else {
            // Tier 3: Blue (1/180 chance)
            const rareRoll3 = Math.floor(Math.random() * 360);
            if (rareRoll3 < 2) {
                enemy.tintR = 0.4;
                enemy.health = 125.0;
                enemy.tintG = 0.4;
                enemy.rewardValue = 520.0;
                enemy.tintB = 0.9;
                enemy.tintA = 1.0;
            }
        }
    }

    // Tier 4: Purple (4/1320 chance) — additive to health
    const rareRoll4 = Math.floor(Math.random() * 1320);
    if (rareRoll4 < 4) {
        enemy.tintR = 0.84;
        enemy.health += 230.0;
        enemy.tintG = 0.24;
        enemy.size = 80.0;
        enemy.tintB = 0.89;
        enemy.rewardValue = 600.0;
        enemy.tintA = 1.0;
    } else {
        // Tier 5: Gold (4/1620 chance) — additive to health
        const rareRoll5 = Math.floor(Math.random() * 1620);
        if (rareRoll5 < 4) {
            enemy.tintR = 0.94;
            enemy.health += 2230.0;
            enemy.tintG = 0.84;
            enemy.size = 85.0;
            enemy.tintB = 0.29;
            enemy.rewardValue = 900.0;
            enemy.tintA = 1.0;
        }
    }

    // Final reward multiplier (C line 218)
    enemy.rewardValue *= 0.8;

    // Tint clamping (C lines 219-249)
    enemy.tintR = Math.max(0.0, Math.min(1.0, enemy.tintR));
    enemy.tintG = Math.max(0.0, Math.min(1.0, enemy.tintG));
    enemy.tintB = Math.max(0.0, Math.min(1.0, enemy.tintB));
    enemy.tintA = Math.max(0.0, Math.min(1.0, enemy.tintA));

    enemy.maxHealth = enemy.health;

    return enemy;
}
