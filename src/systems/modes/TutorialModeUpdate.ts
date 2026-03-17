import { type Player } from '../../entities/Player';
import { type EnemySpawner } from '../enemy/EnemySpawner';
import { type PerkSystem } from '../PerkSystem';
import { type BonusSystem } from '../bonus/BonusSystem';
import { TutorialSystem, TutorialAction, TutorialStage, type TutorialInput } from './TutorialSystem';
import type { GrimInterface } from '../../engine/GrimInterface';
import { GameMode } from '../../Game';
import { gameConsole } from '../../console/Console';

export interface TutorialModeContext {
    player: Player;
    enemySpawner: EnemySpawner;
    perkSystem: PerkSystem;
    bonusSystem: BonusSystem;
    tutorialSystem: TutorialSystem;
    grim: GrimInterface;
    perkPendingCount: number;
    /** Set to true by the caller when a perk was selected this frame */
    perkJustSelected: boolean;
    /** Kill count tracker for combat stages — persisted across frames by caller */
    tutorialKillCount: number;
}

export interface TutorialModeResult {
    perkPendingCount: number;
    shouldReturnToMenu: boolean;
    newGameMode?: GameMode;
    /** Kill count — caller stores this and passes it back next frame */
    tutorialKillCount: number;
}

/**
 * Module-level state for stage-transition tracking.
 * Reset when the tutorial restarts.
 */
let previousStage: TutorialStage = TutorialStage.Inactive;
let bonusesSpawnedForStage: boolean = false;
let xpGrantedForStage: boolean = false;
/** Snapshot of alive enemy count at start of frame, used for kill tracking */
let previousAliveCount: number = 0;
/** Number of enemies we spawned this frame (for kill tracking delta) */
let spawnedThisFrame: number = 0;

export function updateTutorialMode(
    ctx: TutorialModeContext,
    scaledDt: number,
    input: { moveUp: boolean; moveDown: boolean; moveLeft: boolean; moveRight: boolean },
): TutorialModeResult {
    const { player, enemySpawner, tutorialSystem, bonusSystem } = ctx;
    let { perkPendingCount, tutorialKillCount } = ctx;

    // C code: player_state_table.health = 100.0 (every frame during tutorial)
    player.health = 100;

    // C code: player_state_table.experience = 0 (except stage 6 where perk is pending)
    if (tutorialSystem.getStage() !== TutorialStage.LearnPerks) {
        player.experience = 0;
        player.level = 1; // Keep level at 1 to prevent perk screen
        perkPendingCount = 0; // C code: tutorial.c line 141 — reset pending perks
    }

    // ---------------------------------------------------------------
    // Stage-transition detection: detect when stage changes
    // ---------------------------------------------------------------
    const currentStage = tutorialSystem.getStage();
    if (currentStage !== previousStage) {
        gameConsole.print(
            `Tutorial stage transition: ${TutorialStage[previousStage]} → ${TutorialStage[currentStage]}`,
        );

        // Reset per-stage state
        bonusesSpawnedForStage = false;
        xpGrantedForStage = false;
        tutorialKillCount = 0;
        previousAliveCount = 0;
        spawnedThisFrame = 0;

        previousStage = currentStage;
    }

    // ---------------------------------------------------------------
    // Stage 2 (PickupBonuses): Spawn 3 bonuses when entering this stage
    // C code ref: tutorial_timeline_update @ 00408990 — bonuses placed near player
    // ---------------------------------------------------------------
    if (currentStage === TutorialStage.PickupBonuses && !bonusesSpawnedForStage) {
        bonusesSpawnedForStage = true;
        const offsets = [
            { dx: 100, dy: 0 }, // right of player
            { dx: -80, dy: 60 }, // bottom-left
            { dx: 50, dy: -80 }, // top-right
        ];
        for (const o of offsets) {
            const bonus = bonusSystem.spawnBonusAt(player.x + o.dx, player.y + o.dy);
            if (bonus) {
                gameConsole.print(
                    `Tutorial: spawned bonus at (${(player.x + o.dx).toFixed(0)}, ${(player.y + o.dy).toFixed(0)})`,
                );
            }
        }
    }

    // ---------------------------------------------------------------
    // Stage 6 (LearnPerks): Grant XP on entry to trigger level-up
    // Level-up threshold at level 1: Math.floor(1000 * 1.12^1) = 1120
    // Setting experience to 1121 will trigger the level-up in GameplayCollisionUpdate
    // ---------------------------------------------------------------
    if (currentStage === TutorialStage.LearnPerks && !xpGrantedForStage) {
        xpGrantedForStage = true;
        player.experience = 1121;
        gameConsole.print('Tutorial: granted XP for perk level-up');
    }

    // ---------------------------------------------------------------
    // Tutorial enemy spawning for combat stages (4 & 5)
    // Track kills: kills = previousAliveCount - currentAliveCount + spawnedThisFrame
    // Stop respawning after kill threshold is reached
    // ---------------------------------------------------------------
    const isCombatStage = currentStage === TutorialStage.ShootEnemies || currentStage === TutorialStage.CombatPractice;

    // Snapshot current alive count BEFORE spawning
    const aliveBeforeSpawn = enemySpawner.getActiveEnemies().filter((e) => e.isAlive()).length;

    // Calculate kills from last frame (only if we had a valid previous count)
    if (isCombatStage && previousAliveCount > 0) {
        // kills = how many died since last frame = previous - current + spawned last frame
        const killsDelta = previousAliveCount - aliveBeforeSpawn + spawnedThisFrame;
        if (killsDelta > 0) {
            tutorialKillCount += killsDelta;
        }
    }
    spawnedThisFrame = 0; // Reset for this frame

    if (isCombatStage) {
        const killThreshold = currentStage === TutorialStage.ShootEnemies ? 5 : 10;
        const targetCount = currentStage === TutorialStage.ShootEnemies ? 3 : 5;
        const shouldStillSpawn = tutorialKillCount < killThreshold;

        if (shouldStillSpawn) {
            const activeCount = aliveBeforeSpawn;
            if (activeCount < targetCount) {
                // Spawn from a random screen edge
                const edge = Math.floor(Math.random() * 4);
                let sx = 0,
                    sy = 0;
                switch (edge) {
                    case 0:
                        sx = Math.random() * 800;
                        sy = -20;
                        break; // Top
                    case 1:
                        sx = 820;
                        sy = Math.random() * 600;
                        break; // Right
                    case 2:
                        sx = Math.random() * 800;
                        sy = 620;
                        break; // Bottom
                    case 3:
                        sx = -20;
                        sy = Math.random() * 600;
                        break; // Left
                }
                // Spawn with low XP for easy enemies
                enemySpawner.survivalSpawnCreature(sx, sy, 0);
                spawnedThisFrame++;
            }
        }
    } else {
        // Clear enemies when not in a combat stage
        if (enemySpawner.getActiveEnemies().length > 0) {
            enemySpawner.clear();
        }
    }

    // Update previousAliveCount for next frame's kill tracking
    previousAliveCount = enemySpawner.getActiveEnemies().filter((e) => e.isAlive()).length;

    const tutInput: TutorialInput = {
        movePressed: input.moveUp || input.moveDown || input.moveLeft || input.moveRight,
        firePressed: ctx.grim.isMouseButtonPressed(0),
        mouseX: ctx.grim.getMouseX(),
        mouseY: ctx.grim.getMouseY(),
        mouseClicked: ctx.grim.isMouseButtonPressed(0),
        activeEnemyCount: enemySpawner.getActiveEnemies().filter((e) => e.isAlive()).length,
        activeBonusCount: bonusSystem.getActiveCount(),
        perkJustSelected: ctx.perkJustSelected,
        tutorialKillsThisStage: tutorialKillCount,
    };
    const tutAction = tutorialSystem.update(scaledDt, tutInput);
    if (tutAction === TutorialAction.Skip || tutAction === TutorialAction.PlayGame) {
        // End tutorial — go back to menu (C: game_state_pending = 1)
        enemySpawner.clear(); // Clean up tutorial enemies
        // Reset module-level state
        previousStage = TutorialStage.Inactive;
        bonusesSpawnedForStage = false;
        xpGrantedForStage = false;
        gameConsole.print('Tutorial ended, returning to menu');
        return { perkPendingCount, shouldReturnToMenu: true, newGameMode: GameMode.Survival, tutorialKillCount };
    } else if (tutAction === TutorialAction.Repeat) {
        // Restart tutorial — reset player state
        player.experience = 0;
        player.level = 1;
        enemySpawner.clear(); // Clean up tutorial enemies
        // Reset module-level state
        previousStage = TutorialStage.Inactive;
        bonusesSpawnedForStage = false;
        xpGrantedForStage = false;
        tutorialKillCount = 0;
        gameConsole.print('Tutorial restarted');
    }

    return { perkPendingCount, shouldReturnToMenu: false, tutorialKillCount };
}
