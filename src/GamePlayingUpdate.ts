/**
 * GamePlayingUpdate - Per-frame gameplay update logic extracted from Game.ts.
 *
 * Contains updatePlaying() and getRandomEdgePosition().
 */

import { gameConsole } from './console/Console';
import { KeyCode } from './engine/KeyCodes';
import { GameState, GameMode } from './GameTypes';
import { questSystem } from './systems/quest/QuestSystem';
import { updateSurvivalMode } from './systems/modes/SurvivalModeUpdate';
import { updateRushMode } from './systems/modes/RushModeUpdate';
import { updateTutorialMode } from './systems/modes/TutorialModeUpdate';
import { processCollisionsAndKills } from './systems/combat/GameplayCollisionUpdate';
import { updatePlayerFrame } from './systems/player/PlayerFrameUpdate';
import { updateEnemySystems } from './systems/enemy/EnemySystemsUpdate';
import { CREATURE_TYPE_TABLE } from './rendering/SpriteSheetConfig';
import type { GrimInterface } from './engine/GrimInterface';
import type { Player } from './entities/Player';
import type { GameSystems } from './GameSystems';
import type { GameScreens } from './GameScreens';
import type { SurvivalState } from './SurvivalState';
import type { TerrainState } from './TerrainState';
import type { GameplayCursor } from './rendering/GameplayCursor';
import type { ScreenFade } from './rendering/ScreenFade';
import { getPerkUnlockRegistry } from './systems/PerkUnlockRegistry';

/**
 * Duck-typed context for the updatePlaying function.
 * The Game class satisfies this interface directly — no context copying needed.
 */
export interface GamePlayingContext {
    // Engine
    readonly grim: GrimInterface;

    // Core state (mutable — written back to Game)
    state: GameState;
    gameMode: GameMode;
    readonly player: Player;

    // Bundled systems & screens
    readonly systems: GameSystems;
    readonly screens: GameScreens;

    // Grouped state
    readonly survivalState: SurvivalState;
    readonly terrainState: TerrainState;

    // Rendering
    readonly gameplayCursor: GameplayCursor;
    readonly screenFade: ScreenFade;

    // Mutable state
    fireGuardActive: boolean;
    cameraOffsetX: number;
    cameraOffsetY: number;
    perkPendingCount: number;
    perkPromptTimer: number;
    // Shock chain state — mutable, reset when chain projectile expires (C: projectiles.c:586-591)
    shockChainProjectileId: number;
    shockChainLinksLeft: number;
    bonusAnimTimer: number;
    perkJustSelected: boolean;
    tutorialKillCount: number;
    questFailRetryCount: number;

    // Delegates
    handleQuestCompletion(): void;
    handleChainLightning(projectile: any, hitEnemy: any): void;
    applyBonusEffect(bonus: any): void;
}

/**
 * Get a random edge position for spawning (C: survival.c edge cases).
 *
 * @param edge - 0=top, 1=bottom, 2=left, 3=right
 * @param width - Terrain width
 * @param height - Terrain height
 * @param offset - Distance outside the edge
 */
export function getRandomEdgePosition(
    edge: number,
    width: number,
    height: number,
    offset: number,
): { x: number; y: number } {
    switch (edge) {
        case 0:
            return { x: Math.floor(Math.random() * width), y: -offset };
        case 1:
            return { x: Math.floor(Math.random() * width), y: height + offset };
        case 2:
            return { x: -offset, y: Math.floor(Math.random() * height) };
        case 3:
            return { x: width + offset, y: Math.floor(Math.random() * height) };
        default:
            return { x: Math.floor(Math.random() * width), y: -offset };
    }
}

/**
 * Per-frame gameplay update.
 *
 * Moved from Game.updatePlaying() (lines 686–909).
 */
export function updatePlaying(ctx: GamePlayingContext, dt: number): void {
    // Suppress fire until the mouse button is released after game start.
    // This prevents the menu/screen click that started the game from firing.
    if (ctx.fireGuardActive) {
        if (!ctx.grim.isMouseButtonDown(0)) {
            ctx.fireGuardActive = false; // Mouse released — allow firing
        }
    }
    const suppressFire = ctx.fireGuardActive;

    // Player input, movement, camera, weapon firing, and per-frame system ticks
    const frameResult = updatePlayerFrame(
        {
            player: ctx.player,
            grim: ctx.grim,
            perkSystem: ctx.systems.perkSystem,
            weaponSystem: ctx.systems.weaponSystem,
            cameraShake: ctx.systems.cameraShake,
            particleSystem: ctx.systems.particleSystem,
            effectSystem: ctx.systems.effectSystem,
            bloodEffectSystem: ctx.systems.bloodEffectSystem,
            soundSystem: ctx.systems.soundSystem,
            gameplayCursor: ctx.gameplayCursor,
            terrainRenderer: ctx.terrainState.renderer,
            cameraOffsetX: ctx.cameraOffsetX,
            cameraOffsetY: ctx.cameraOffsetY,
            suppressFire,
            shockChainState: ctx as { shockChainProjectileId: number; shockChainLinksLeft: number },
            enemies: ctx.systems.enemySpawner.getActiveEnemies(),
        },
        dt,
    );
    const { scaledDt, input } = frameResult;
    ctx.cameraOffsetX = frameResult.cameraOffsetX;
    ctx.cameraOffsetY = frameResult.cameraOffsetY;

    // Update quest system if in quest mode (C code: quest_update @ lines 4866-4931)
    if (ctx.gameMode === GameMode.Quest && questSystem.isActive()) {
        questSystem.update(scaledDt * 1000); // Convert to ms

        // Check for quest completion
        if (questSystem.getState() === 3) {
            // COMPLETE
            ctx.handleQuestCompletion();
        }
    }

    // Update tutorial system if in tutorial mode (C: tutorial_timeline_update)
    if (ctx.gameMode === GameMode.Tutorial && ctx.systems.tutorialSystem.isActive()) {
        const tutResult = updateTutorialMode(
            {
                player: ctx.player,
                enemySpawner: ctx.systems.enemySpawner,
                perkSystem: ctx.systems.perkSystem,
                bonusSystem: ctx.systems.bonusSystem,
                tutorialSystem: ctx.systems.tutorialSystem,
                grim: ctx.grim,
                perkPendingCount: ctx.perkPendingCount,
                perkJustSelected: ctx.perkJustSelected,
                tutorialKillCount: ctx.tutorialKillCount,
            },
            scaledDt,
            input,
        );
        ctx.perkJustSelected = false; // Consume the flag after tutorial reads it
        ctx.perkPendingCount = tutResult.perkPendingCount;
        ctx.tutorialKillCount = tutResult.tutorialKillCount;
        if (tutResult.shouldReturnToMenu) {
            ctx.state = GameState.Menu;
            if (tutResult.newGameMode !== undefined) ctx.gameMode = tutResult.newGameMode;
        }
    }

    // =================================================================
    // Survival / Rush mode-specific update (C: survival_update, rush_mode_update)
    // Must run BEFORE enemy AI update so newly spawned enemies participate
    // =================================================================
    const terrainW = ctx.terrainState.renderer?.getPlayableWidth() ?? 1024;
    const terrainH = ctx.terrainState.renderer?.getPlayableHeight() ?? 1024;
    const numPlayers = 1; // Single player
    const dtMs = scaledDt * 1000; // frame_dt_ms
    const elapsedMs = Math.floor(ctx.systems.scoreSystem.getSurvivalTime() * 1000);

    if (ctx.gameMode === GameMode.Rush && ctx.player) {
        updateRushMode(
            { player: ctx.player, enemySpawner: ctx.systems.enemySpawner },
            dtMs,
            elapsedMs,
            terrainW,
            terrainH,
            numPlayers,
            gameConsole.getIsOpen(),
        );
    }

    if (ctx.gameMode === GameMode.Survival && ctx.player) {
        const survResult = updateSurvivalMode(
            {
                player: ctx.player,
                enemySpawner: ctx.systems.enemySpawner,
                perkSystem: ctx.systems.perkSystem,
                scoreSystem: ctx.systems.scoreSystem,
                survivalSpawnStage: ctx.survivalState.spawnStage,
                survivalRewardDamageSeen: ctx.survivalState.rewardDamageSeen,
                survivalRewardFireSeen: ctx.survivalState.rewardFireSeen,
                survivalRewardHandoutEnabled: ctx.survivalState.rewardHandoutEnabled,
                survivalRecentDeaths: ctx.survivalState.recentDeaths,
                getRandomEdgePosition: (e, w, h, o) => getRandomEdgePosition(e, w, h, o),
            },
            dtMs,
            elapsedMs,
            terrainW,
            terrainH,
            numPlayers,
        );
        ctx.survivalState.spawnStage = survResult.survivalSpawnStage;
        ctx.survivalState.rewardDamageSeen = survResult.survivalRewardDamageSeen;
        ctx.survivalState.rewardFireSeen = survResult.survivalRewardFireSeen;
        ctx.survivalState.rewardHandoutEnabled = survResult.survivalRewardHandoutEnabled;
    }

    // Update enemies — AI/movement always runs
    // spawningEnabled no longer matters for survival/rush (spawning handled above)
    const prevSpawning = ctx.systems.enemySpawner.spawningEnabled;
    ctx.systems.enemySpawner.spawningEnabled = false;
    ctx.systems.enemySpawner.update(scaledDt, ctx.player.x, ctx.player.y, ctx.player.experience, ctx.player);
    ctx.systems.enemySpawner.spawningEnabled = prevSpawning;

    // Update dying enemies (death animations) and bake completed corpses
    const completedCorpses = ctx.systems.enemySpawner.updateDyingEnemies(scaledDt);
    for (const corpse of completedCorpses) {
        // C code: fx_queue_add_rotated(pos, &creature.tint_r, heading, size, type_id)
        // Pass the enemy's actual tint, size, heading, and type for correct corpse rendering
        if (corpse.hasBlood) {
            // Also spawn blood debris stamps (fx_queue_add_random)
            ctx.systems.bloodEffectSystem.addRandomGroundDebris(corpse.x, corpse.y);
        }
        // Always queue corpse sprite (baked into terrain with enemy's color/size/rotation)
        const typeIdx = Math.min(corpse.type, CREATURE_TYPE_TABLE.length - 1); // clamp to known types
        // C creatures.c:1655-1662 — spawner enemies (flag &4, no &0x40) use nest corpse
        // bodyset.jaz row 1, col 2 (0-indexed) = frame index 6
        const corpseFrame = ((corpse.creatureFlags & 4) !== 0 && (corpse.creatureFlags & 0x40) === 0)
            ? 6
            : CREATURE_TYPE_TABLE[typeIdx].corpseFrame;
        // C creatures.c: corpse is drawn at enemy.size (same as live sprite)
        const visualSize = corpse.size;
        ctx.systems.bloodEffectSystem.queueCorpseStamp(
            corpse.x,
            corpse.y,
            visualSize,
            corpse.angle,
            corpse.tintR,
            corpse.tintG,
            corpse.tintB,
            1.0,
            corpseFrame,
        );
    }

    // Enemy AI, perk-based targeting, man bomb burst
    updateEnemySystems(
        {
            player: ctx.player,
            enemySpawner: ctx.systems.enemySpawner,
            perkSystem: ctx.systems.perkSystem,
            weaponSystem: ctx.systems.weaponSystem,
            particleSystem: ctx.systems.particleSystem,
            soundSystem: ctx.systems.soundSystem,
        },
        scaledDt,
        dt, // Raw unscaled dt for perk timers (C: fire_cough/hot_tempered use pre-scale frame_dt)
    );

    // Check collisions, process kills, bonuses, level-ups, and game over
    const collisionResult = processCollisionsAndKills(
        {
            player: ctx.player,
            perkSystem: ctx.systems.perkSystem,
            weaponSystem: ctx.systems.weaponSystem,
            enemySpawner: ctx.systems.enemySpawner,
            collisionSystem: ctx.systems.collisionSystem,
            scoreSystem: ctx.systems.scoreSystem,
            bonusSystem: ctx.systems.bonusSystem,
            particleSystem: ctx.systems.particleSystem,
            soundSystem: ctx.systems.soundSystem,
            musicSystem: ctx.systems.musicSystem,
            highScoreSystem: ctx.systems.highScoreSystem,
            saveSystem: ctx.systems.saveSystem,
            achievementSystem: ctx.systems.achievementSystem,
            hud: ctx.screens.hud,
            perkSelectionScreen: ctx.screens.perkSelectionScreen,
            gameOverScreen: ctx.screens.gameOverScreen,
            questFailedScreen: ctx.screens.questFailedScreen,
            questFailRetryCount: ctx.questFailRetryCount,
            gameMode: ctx.gameMode,
            perkPendingCount: ctx.perkPendingCount,
            perkPromptTimer: ctx.perkPromptTimer,
            bonusAnimTimer: ctx.bonusAnimTimer,
            survivalRecentDeaths: ctx.survivalState.recentDeaths,
            effectSystem: ctx.systems.effectSystem,
            shockChainLinksLeft: ctx.shockChainLinksLeft,
            handleChainLightning: (proj, enemy) => ctx.handleChainLightning(proj, enemy),
            applyBonusEffect: (bonus) => ctx.applyBonusEffect(bonus),
        },
        dt,
        scaledDt,
    );
    ctx.perkPendingCount = collisionResult.perkPendingCount;
    ctx.perkPromptTimer = collisionResult.perkPromptTimer;
    ctx.bonusAnimTimer = collisionResult.bonusAnimTimer;

    // Deferred quest completion check: runs AFTER all kill-reporting phases
    // (weaponSystem.update AoE, updateEnemySystems burning/poison, processCollisionsAndKills direct hits)
    // so activeEnemyCount reflects every kill from this frame.
    if (ctx.gameMode === GameMode.Quest && questSystem.isActive()) {
        questSystem.checkCompletion();
        if (questSystem.getState() === 3) { // COMPLETE
            ctx.handleQuestCompletion();
        }
    }

    if (collisionResult.newState !== undefined) {
        ctx.state = collisionResult.newState;
        // Fade out to black on game over / quest failed (C: screen_fade_alpha → 1.0)
        if (collisionResult.isGameOver) {
            ctx.screenFade.fadeOut(3.0); // C: frame_dt * 3.0 rate
        }
    }
    if (collisionResult.newState === GameState.PerkSelection) {
        return;
    }

    // Check for perk pick activation (C code: gameplay_update_and_render lines 495-526)
    // key_pick_perk = 0x101 = Mouse2 (right-click), also Space (0x39) and numpad+ (0x4e)
    // C: gameplay.c line 496 — perk screen blocked in Rush mode (config_blob._24_4_ != 2)
    if (
        !collisionResult.isGameOver &&
        ctx.perkPendingCount > 0 &&
        ctx.player.isAlive() &&
        !ctx.grim.isMouseButtonDown(0) &&
        ctx.gameMode !== GameMode.Rush
    ) {
        const rightClicked = ctx.grim.isMouseButtonPressed(2);
        const spacePressed = ctx.grim.isKeyPressed(KeyCode.Space);
        if (rightClicked || spacePressed) {
            const availablePerks = getPerkUnlockRegistry().getAvailablePerks(ctx.player.level);
            ctx.screens.perkSelectionScreen.show(ctx.systems.perkSystem, availablePerks);
            ctx.state = GameState.PerkSelection;
            return;
        }
    }
}
