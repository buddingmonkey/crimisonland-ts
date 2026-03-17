/**
 * EnemySpawner - Enemy spawning and management system
 *
 * Accurate port of survival_spawn_creature from crimsonland.exe_decompiled.c
 */

import { Enemy, EnemyType, AIMode } from '../../entities/Enemy';
import { DummyEnemy } from '../../entities/DummyEnemy';
import type { GrimInterface } from '../../engine/GrimInterface';
import { EnemyAI } from './EnemyAI';
import { createQuestEnemy } from '../quest/QuestEnemySpawner';
import { createSurvivalEnemy } from '../modes/SurvivalSpawner';
import { questSystem } from '../quest/QuestSystem';

/**
 * Enemy spawner system
 */
export class EnemySpawner {
    private enemies: Enemy[] = [];
    private readonly maxEnemies: number = 100;
    private updateTick: number = 0; // Update tick counter (C line 21260)
    private freezeTimer: number = 0; // Global freeze timer (C line 21270)

    /** C: survival_spawn_cooldown — cooldown between spawns in ms */
    public survivalSpawnCooldown: number = 0;

    /** When false, no new enemies spawn but existing ones still update */
    public spawningEnabled: boolean = true;

    /**
     * Spawn an enemy using survival mode logic (from C).
     * Creation logic extracted to SurvivalSpawner.ts.
     */
    survivalSpawnCreature(x: number, y: number, experience: number): Enemy | null {
        if (this.enemies.length >= this.maxEnemies) {
            return null;
        }

        const enemy = createSurvivalEnemy(x, y, experience);

        // Assign unique ID for projectile ownership
        enemy.id = this.enemies.length;

        this.enemies.push(enemy);
        return enemy;
    }

    /**
     * Spawn a Rush mode creature at the given position with tint color.
     * C: creature_spawn(&pos, &tint, type) in rush_mode_update
     * Uses type-specific base stats per C's creature_spawn formula (no XP scaling).
     */
    spawnRushCreature(x: number, y: number, tintR: number, tintG: number, tintB: number, typeId: number): Enemy | null {
        if (this.enemies.length >= this.maxEnemies) {
            return null;
        }

        const enemy = new Enemy(x, y, typeId as EnemyType);
        enemy.type = typeId;
        enemy.active = true;

        // Size: random(20) + 44 → range 44-63 (C survival_spawn_creature line 5100)
        const size = Math.floor(Math.random() * 20) + 44;
        enemy.size = size;

        // Health: size * 1.14 + 20 → ~70–92 (C line 5114)
        const health = size * 1.14 + 20;
        enemy.health = health;
        enemy.maxHealth = health;

        // Contact damage: size * 0.0952381 (C line 5166)
        enemy.damage = size * 0.0952381;

        // Speed: base move_speed=0.9 (no XP), scaled to pixel units (C line 5104)
        // Type 2 (Spider): 0.9 * 25.0 = 22.5
        // Type 3 (Spider2): 0.9 * 1.3 * 25.0 = 29.25 (+flag 0x80)
        let moveSpeed = 0.9; // base move_speed, no XP scaling in Rush
        if (typeId === EnemyType.Spider2) {
            moveSpeed *= 1.3;
            enemy.creatureFlags |= 0x80; // C line 98: flag for fast type
        }
        enemy.speed = moveSpeed * 25.0;
        enemy.maxSpeed = enemy.speed;

        // Reward value (C lines 152-158, then *= 0.8 at line 218)
        const rewardRaw = health * 0.4 + enemy.damage * 0.8 + moveSpeed * 5.0 + Math.floor(Math.random() * 10) + 10;
        enemy.rewardValue = rewardRaw * 0.8; // C line 218: final multiplier

        // Apply tint from caller (Rush uses time-based tint, NOT XP-based)
        enemy.tintR = tintR;
        enemy.tintG = tintG;
        enemy.tintB = tintB;
        enemy.tintA = 1.0;

        // Random heading (C line 5102)
        enemy.angle = Math.floor(Math.random() * 314) * 0.01;

        // Assign unique ID
        enemy.id = this.enemies.length;

        this.enemies.push(enemy);
        return enemy;
    }

    /**
     * Update spawner and all enemies
     * C code reference: creature_update_all @ lines 21222-21800
     */
    update(dt: number, playerX: number, playerY: number, _experience: number, player?: any): void {
        // Increment update tick (C line 21260)
        this.updateTick++;

        // Update freeze timer (C line 21270)
        if (this.freezeTimer > 0) {
            this.freezeTimer -= dt;
            if (this.freezeTimer < 0) this.freezeTimer = 0;
        }

        // Spawning is now driven by Game.ts (cooldown loop for Survival/Rush)
        // No automatic spawning in EnemySpawner.update() — this matches C architecture
        // where survival_update() and rush_mode_update() call spawn functions directly.

        // Update all enemies
        for (const enemy of this.enemies) {
            // Update hit flash timer for ALL active enemies (alive + dying)
            // C lines 21266-21268: timer decrements every frame regardless of state
            // Without this, dying enemies stay white because isAlive() gates the old decrement
            if (enemy.active && enemy.hitFlashTimer > 0) {
                enemy.hitFlashTimer -= dt;
            }

            if (!enemy.isAlive()) continue;

            // Skip AI if frozen (C line 21270)
            if (this.freezeTimer > 0) {
                continue;
            }

            // DOT (burning/poison) damage is handled by EnemySystemsUpdate.ts (Fix 7)
            // to avoid double-application.

            // Plague collision damage is handled by EnemySystemsUpdate.ts (Fix 9)
            // to avoid double damage application and to centralize visuals/sounds.

            // Evil Eyes freeze: C creatures.c:1235-1240
            // When this creature IS the evil eyes target, skip ALL AI, movement, and animation
            if (player?.evilEyesTarget === enemy) {
                continue;
            }

            // Retarget every 70 ticks (C line 21325: creature_update_tick % 0x46)
            if (this.updateTick % 0x46 === 0) {
                // Find nearest player (simplified for single player)
                enemy.targetPlayerId = 0;
            }

            // Calculate AI target position based on mode (C lines 21388-21550)
            const distance = Math.sqrt((enemy.x - playerX) ** 2 + (enemy.y - playerY) ** 2);

            // Call AI targeting to set enemy.targetX/Y
            EnemyAI.calculateAITarget(
                enemy,
                { x: playerX, y: playerY } as any, // Player object
                distance,
                this.enemies,
                dt,
            );

            // Fix 2: forceTarget override (C lines 1379-1394)
            // With dynamic orbit targets, re-evaluate each frame
            enemy.forceTarget = false;
            const tdx = enemy.targetX - enemy.x;
            const tdy = enemy.targetY - enemy.y;
            const targetDist = Math.sqrt(tdx * tdx + tdy * tdy);
            if (targetDist < 40.0) enemy.forceTarget = true;
            if (targetDist > 400.0) enemy.forceTarget = true;
            if (enemy.forceTarget || enemy.aiMode === AIMode.DIRECT_CHASE) {
                enemy.targetX = playerX;
                enemy.targetY = playerY;
            }

            // Nest spawner update (C: creature_spawn_slot_table)
            if (enemy.isNestSpawner && enemy.nestSpawnCount < enemy.nestSpawnLimit) {
                enemy.nestSpawnTimer -= dt;
                if (enemy.nestSpawnTimer <= 0) {
                    enemy.nestSpawnTimer = enemy.nestSpawnInterval;
                    enemy.nestSpawnCount++;
                    // Spawn child at parent position
                    const child = this.spawnQuestEnemy(enemy.x, enemy.y, enemy.nestChildTemplate);
                    if (child) {
                        questSystem.reportEnemySpawned(1);
                    }
                }
            }

            // Regular enemy update
            enemy.update(dt, playerX, playerY, player);
        }

        // Remove fully dead enemies periodically (not dying ones — they're still animating)
        if (this.enemies.length > 50) {
            this.enemies = this.enemies.filter((e) => e.active);
        }
    }

    /**
     * Update dying enemies (advance death animations).
     * Returns list of enemies whose death animation just completed (for corpse baking).
     */
    updateDyingEnemies(dt: number): Enemy[] {
        const completed: Enemy[] = [];
        for (const enemy of this.enemies) {
            if (enemy.isDying && enemy.active) {
                const done = enemy.updateDeath(dt);
                if (done) {
                    completed.push(enemy);
                }
            }
        }
        return completed;
    }

    /**
     * Render all enemies
     * @param grim - Graphics interface
     * @param perkSystem - Optional perk system for Monster Vision
     * @param spriteRenderer - Optional sprite renderer for textured rendering
     * @param debugMode - If true, always use debug (circle/line) rendering
     */
    render(grim: GrimInterface, perkSystem?: any, spriteRenderer?: any, debugMode: boolean = true, player?: any): void {
        for (const enemy of this.enemies) {
            if (enemy.shouldRender()) {
                enemy.render(grim, perkSystem, spriteRenderer, debugMode, player);
            }
        }
    }

    /**
     * Get all active enemies
     */
    getActiveEnemies(): Enemy[] {
        return this.enemies.filter((e) => e.isAlive());
    }

    /**
     * Add an externally-created enemy to the spawner's internal list
     */
    addEnemy(enemy: Enemy): void {
        this.enemies.push(enemy);
    }

    /**
     * Get all enemies that should be rendered (alive + dying)
     */
    getAllVisibleEnemies(): Enemy[] {
        return this.enemies.filter((e) => e.shouldRender());
    }

    /**
     * Clear all enemies
     */
    clear(): void {
        this.enemies = [];
        this.survivalSpawnCooldown = 0;
    }

    /**
     * Get enemy count
     */
    getEnemyCount(): number {
        return this.getActiveEnemies().length;
    }

    /**
     * Spawn a quest enemy at a specific position with a specific template ID
     * C code reference: creature_spawn_template @ lines 26070-27700
     * Each template assigns exact type_id, health, move_speed, size, contact_damage,
     * reward_value, tint, flags, ai_mode, and optionally spawner-slot config.
     *
     * Template creation logic is in QuestEnemySpawner.ts.
     */
    spawnQuestEnemy(posX: number, posY: number, templateId: number): Enemy | null {
        // Count only alive enemies — dying enemies (in death animation) shouldn't
        // block new spawns. Previously this used enemies.length which included
        // dying enemies (~1s death animation), causing spawns to silently fail
        // when dead enemies accumulated from fast-killing weapons like Mean Minigun.
        const aliveCount = this.enemies.filter(e => e.isAlive()).length;
        if (aliveCount >= this.maxEnemies) {
            return null;
        }
        const enemy = createQuestEnemy(posX, posY, templateId, {
            retryCount: questSystem.getFailRetryCount(),
            hardcoreMode: questSystem.isHardcoreMode(),
        });
        enemy.id = this.enemies.length;
        this.enemies.push(enemy);
        return enemy;
    }

    // ============================================
    // Dummy enemy support (for E2E testing)
    // ============================================

    /**
     * Spawn a stationary dummy target at the given position.
     * Dummies participate in normal collision detection but don't move.
     */
    spawnDummy(x: number, y: number, label?: string): DummyEnemy {
        const dummy = new DummyEnemy(x, y, label);
        dummy.id = this.enemies.length;
        this.enemies.push(dummy);
        return dummy;
    }

    /**
     * Get all active dummy enemies
     */
    getDummies(): DummyEnemy[] {
        return this.enemies.filter((e): e is DummyEnemy => e.isAlive() && (e as any).isDummy === true);
    }

    /**
     * Remove all dummy enemies
     */
    clearDummies(): void {
        this.enemies = this.enemies.filter((e) => !(e as any).isDummy);
    }
}
