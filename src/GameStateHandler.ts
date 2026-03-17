/**
 * GameStateHandler - State dispatch and screen-update methods extracted from Game.ts.
 *
 * Contains handleInput(), update(), render(), and all screen-specific update methods.
 */

import { gameConsole } from './console/Console';
import { KeyCode } from './engine/KeyCodes';
import { GameState, GameMode } from './GameTypes';
import { PerkId, PERK_META } from './systems/PerkSystem';
import { applyInstantPerkEffect } from './systems/player/PlayerModifier';
import { applyInstantPerkEffectToGame } from './systems/PerkEffectApplicator';
import {
    handleQuestCompletion as _handleQuestCompletion,
    updateQuestCompleteScreen,
} from './systems/quest/QuestCompletionFlow';
import { handleMenuStateInput } from './ui/menus/MenuInputHandler';
import { handlePauseStateInput } from './ui/menus/PauseInputHandler';
import type { PerkSelectionInput } from './ui/screens/PerkSelectionScreen';
import { GameOverAction, type GameOverInput } from './ui/screens/GameOverScreen';
import { QuestFailedAction, type QuestFailedInput } from './ui/screens/QuestFailedScreen';
import { questSystem } from './systems/quest/QuestSystem';
import type { GrimInterface } from './engine/GrimInterface';
import type { Player } from './entities/Player';
import type { GameSystems } from './GameSystems';
import type { GameScreens } from './GameScreens';
import { StatisticsAction, type StatisticsInput } from './ui/screens/StatisticsScreen';
import { LeaderboardAction, type LeaderboardInput } from './ui/screens/LeaderboardScreen';
import { CreditsAction, type CreditsInput } from './ui/screens/CreditsScreen';
import { AlienZooKeeperAction, type AlienZooKeeperInput } from './ui/screens/AlienZooKeeperScreen';
import type { ScreenFade } from './rendering/ScreenFade';

/**
 * Duck-typed context for GameStateHandler.
 * The Game class satisfies this interface directly — no context copying needed.
 */
export interface GameStateContext {
    // Engine
    readonly grim: GrimInterface;

    // Core state
    state: GameState;
    gameMode: GameMode;
    readonly player: Player | null;
    font: any;

    // Bundled systems and screens
    readonly systems: GameSystems;
    readonly screens: GameScreens;

    // Screen fade
    readonly screenFade: ScreenFade;

    // Mutable state
    perkPendingCount: number;
    perkJustSelected: boolean;
    lastLevel: number;
    questFailRetryCount: number;
    menuMusicStarted: boolean;
    perkPromptTimer: number;

    // Delegates
    startGame(): void;
    regenerateTerrain(tier: number): void;
    updatePlaying(dt: number): void;
    renderGame(): void;
    renderGameSuppressed(): void;
    renderMenuCursor(): void;
    renderConsole(): void;
}

/**
 * Handles game state dispatch and screen-update logic.
 * Extracted from the Game class to reduce monolith size.
 */
export class GameStateHandler {
    // Latch: where ESC from Statistics/Leaderboard should return to (C: highscore_return_latch)
    private returnFromStatistics: GameState = GameState.Menu;

    /**
     * Handle input — console routing + state-specific input dispatch.
     *
     * Moved from Game.handleInput() (lines 508–593).
     */
    handleInput(ctx: GameStateContext): void {
        // Toggle console with tilde/backquote
        if (ctx.grim.isKeyPressed(KeyCode.Backquote)) {
            gameConsole.toggle();
        }

        // If console is open, route input there
        if (gameConsole.getIsOpen()) {
            // Process all character inputs from this frame
            const chars = ctx.grim.getKeyChars();
            for (const charCode of chars) {
                gameConsole.processChar(charCode);
            }

            if (ctx.grim.isKeyPressed(KeyCode.Enter) && gameConsole.isInputReady()) {
                gameConsole.submitInput();
            }

            if (ctx.grim.isKeyPressed(KeyCode.Up)) {
                gameConsole.navigateHistory(1);
            }
            if (ctx.grim.isKeyPressed(KeyCode.Down)) {
                gameConsole.navigateHistory(-1);
            }

            // Scroll console log with PageUp/PageDown
            if (ctx.grim.isKeyPressed(KeyCode.PageUp)) {
                gameConsole.scrollUp(5);
            }
            if (ctx.grim.isKeyPressed(KeyCode.PageDown)) {
                gameConsole.scrollDown(5);
            }

            return; // Don't process game input when console is open
        }

        // Game-specific input handling based on state
        switch (ctx.state) {
            case GameState.Menu: {
                const menuResult = handleMenuStateInput({
                    grim: ctx.grim,
                    mainMenu: ctx.screens.mainMenu,
                    statisticsScreen: ctx.screens.statisticsScreen,
                    creditsScreen: ctx.screens.creditsScreen,
                    enemySpawner: ctx.systems.enemySpawner,
                    tutorialSystem: ctx.systems.tutorialSystem,
                    musicSystem: ctx.systems.musicSystem,
                    setGameMode: (mode) => { ctx.gameMode = mode; },
                    startGame: () => ctx.startGame(),
                    regenerateTerrain: (tier) => ctx.regenerateTerrain(tier),
                });
                if (menuResult.newGameMode !== undefined) {
                    ctx.gameMode = menuResult.newGameMode;
                }
                if (menuResult.newState !== undefined) {
                    ctx.state = menuResult.newState;
                }
                break;
            }

            case GameState.Playing:
                // Escape to pause
                if (ctx.grim.isKeyPressed(KeyCode.Escape)) {
                    ctx.state = GameState.Paused;
                    ctx.screens.pauseMenu.show();
                }

                // C code: no number-key weapon switching — weapons are assigned
                // via pickups (weapon_assign_player), quest starts, and perks only
                break;

            case GameState.Paused: {
                const pauseResult = handlePauseStateInput({
                    grim: ctx.grim,
                    pauseMenu: ctx.screens.pauseMenu,
                    mainMenu: ctx.screens.mainMenu,
                    musicSystem: ctx.systems.musicSystem,
                });
                if (pauseResult.newState !== undefined) {
                    ctx.state = pauseResult.newState;
                }
                break;
            }
        }
    }

    /**
     * Update game logic — frame-level state dispatcher.
     *
     * Moved from Game.update() (lines 598–681).
     */
    update(ctx: GameStateContext): void {
        const dt = ctx.grim.getDeltaTime() / 1000.0; // Convert to seconds

        // Update screen fade overlay (C: screen_fade_alpha += direction * frame_dt * speed)
        ctx.screenFade.update(dt);

        switch (ctx.state) {
            case GameState.Menu:
                // Start menu music on first interaction (Web Audio requires user interaction)
                if (!ctx.menuMusicStarted && ctx.systems.musicSystem.getTrackCount() > 0) {
                    // Detect actual user interaction (mouse movement, clicks, or key presses)
                    const hasMouseMoved = ctx.grim.getMouseDeltaX() !== 0 || ctx.grim.getMouseDeltaY() !== 0;
                    const hasMouseClicked =
                        ctx.grim.isMouseButtonDown(0) || ctx.grim.isMouseButtonDown(1) || ctx.grim.isMouseButtonDown(2);
                    const hasKeyPressed = ctx.grim.getKeyChars().length > 0;

                    // Only resume audio if user has actually interacted
                    if (hasMouseMoved || hasMouseClicked || hasKeyPressed) {
                        // Resume audio contexts (only once, on first interaction)
                        ctx.systems.soundSystem.resume();
                        ctx.systems.musicSystem.resume();

                        // Start menu music
                        ctx.systems.musicSystem.play('crimson_theme.ogg');
                        ctx.menuMusicStarted = true;
                    }
                }
                break;

            case GameState.Playing:
                ctx.updatePlaying(dt);
                break;

            case GameState.Paused:
                // Pause menu updates handled in handleInput (same loop)
                break;

            case GameState.GameOver:
                if (!gameConsole.getIsOpen()) {
                    this.updateGameOver(ctx);
                }
                break;

            case GameState.QuestFailed:
                if (!gameConsole.getIsOpen()) {
                    this.updateQuestFailed(ctx);
                }
                break;

            case GameState.PerkSelection:
                // Don't process perk clicks when console is open (console renders over perk screen)
                if (!gameConsole.getIsOpen()) {
                    this.updatePerkSelection(ctx);
                }
                break;

            case GameState.QuestComplete:
                if (!gameConsole.getIsOpen()) {
                    this.updateQuestComplete(ctx);
                }
                break;

            case GameState.Statistics: {
                const dtMs = ctx.grim.getDeltaTime();
                if (ctx.screens.leaderboardScreen.isVisible()) {
                    // Dispatch to leaderboard screen
                    const lbInput: LeaderboardInput = {
                        mouseX: ctx.grim.getMouseX(),
                        mouseY: ctx.grim.getMouseY(),
                        mouseClicked: ctx.grim.isMouseButtonPressed(0),
                        cancelPressed: ctx.grim.isKeyPressed(KeyCode.Escape),
                        tabPressed: ctx.grim.isKeyPressed(KeyCode.Tab),
                    };
                    const lbAction = ctx.screens.leaderboardScreen.update(dtMs, lbInput);
                    if (lbAction === LeaderboardAction.Back) {
                        ctx.screens.leaderboardScreen.hide();
                        ctx.state = this.returnFromStatistics;
                        this.returnFromStatistics = GameState.Menu; // Reset latch
                    }
                } else {
                    // Dispatch to statistics screen
                    const statsInput: StatisticsInput = {
                        mouseX: ctx.grim.getMouseX(),
                        mouseY: ctx.grim.getMouseY(),
                        mouseClicked: ctx.grim.isMouseButtonPressed(0),
                        cancelPressed: ctx.grim.isKeyPressed(KeyCode.Escape),
                    };
                    const statsAction = ctx.screens.statisticsScreen.update(dtMs, statsInput);
                    if (statsAction === StatisticsAction.Back) {
                        ctx.screens.statisticsScreen.hide();
                        ctx.state = this.returnFromStatistics;
                        this.returnFromStatistics = GameState.Menu; // Reset latch
                    }
                }
                break;
            }

            case GameState.Credits: {
                const dtMs = ctx.grim.getDeltaTime();
                const creditsInput: CreditsInput = {
                    mouseX: ctx.grim.getMouseX(),
                    mouseY: ctx.grim.getMouseY(),
                    mouseClicked: ctx.grim.isMouseButtonPressed(0),
                    cancelPressed: ctx.grim.isKeyPressed(KeyCode.Escape),
                };
                const creditsAction = ctx.screens.creditsScreen.update(dtMs, creditsInput);
                if (creditsAction === CreditsAction.Back) {
                    ctx.screens.creditsScreen.hide();
                    ctx.state = GameState.Menu;
                } else if (creditsAction === CreditsAction.AlienZooKeeper) {
                    ctx.screens.creditsScreen.hide();
                    ctx.screens.alienZooKeeperScreen.show();
                    ctx.state = GameState.AlienZooKeeper;
                }
                break;
            }

            case GameState.AlienZooKeeper: {
                const dtMs = ctx.grim.getDeltaTime();
                const zkInput: AlienZooKeeperInput = {
                    mouseX: ctx.grim.getMouseX(),
                    mouseY: ctx.grim.getMouseY(),
                    mouseClicked: ctx.grim.isMouseButtonPressed(0),
                    cancelPressed: ctx.grim.isKeyPressed(KeyCode.Escape),
                };
                const zkAction = ctx.screens.alienZooKeeperScreen.update(dtMs, zkInput);
                if (zkAction === AlienZooKeeperAction.Back) {
                    ctx.screens.alienZooKeeperScreen.hide();
                    ctx.state = GameState.Menu;
                }
                break;
            }
        }
    }

    /**
     * Render the game — state-based render dispatch.
     *
     * Moved from Game.render() (lines 683–796).
     */
    render(ctx: GameStateContext): void {
        // Hide fullscreen button by default; show only for menu states
        ctx.grim.hideFullscreenButton();

        // Render based on state
        switch (ctx.state) {
            case GameState.Menu:
                ctx.grim.showFullscreenButton();
                this.renderMenu(ctx);
                break;

            case GameState.Playing:
                ctx.renderGame();
                break;

            case GameState.Paused:
                ctx.grim.showFullscreenButton();
                ctx.renderGameSuppressed(); // Suppress gameplay reticle
                // Switch to UI layer so overlay + menu render ABOVE game world
                ctx.grim.setGraphicsLayer('ui');
                ctx.grim.drawFullscreenColor(0, 0, 0, 128);
                ctx.screens.pauseMenu.render(ctx.grim);
                // MenuCursor already rendered by PauseMenu.render()
                ctx.grim.setGraphicsLayer('game');
                break;

            case GameState.GameOver:
                ctx.renderGameSuppressed(); // C: game_over_screen_update renders world, then ui_cursor_render
                ctx.grim.setGraphicsLayer('ui');
                if (ctx.font) {
                    ctx.screens.gameOverScreen.render(ctx.grim, ctx.font, ctx.grim.getMouseX(), ctx.grim.getMouseY());
                }
                ctx.renderMenuCursor(); // C: ui_cursor_render() at gameplay.c:978
                ctx.grim.setGraphicsLayer('game');
                break;

            case GameState.QuestFailed:
                ctx.renderGameSuppressed(); // C: quest_failed_screen_update renders world, then ui_cursor_render
                ctx.grim.setGraphicsLayer('ui');
                if (ctx.font) {
                    ctx.screens.questFailedScreen.render(ctx.grim, ctx.font, ctx.grim.getMouseX(), ctx.grim.getMouseY());
                }
                ctx.renderMenuCursor(); // C: ui_cursor_render() at quest.c:243
                ctx.grim.setGraphicsLayer('game');
                break;

            case GameState.PerkSelection:
                ctx.renderGameSuppressed(); // C: game_update_generic_menu renders world, then ui_cursor_render
                ctx.grim.setGraphicsLayer('ui');
                ctx.screens.perkSelectionScreen.render(ctx.grim);
                ctx.renderMenuCursor(); // C: ui_cursor_render() at perks.c:465
                ctx.grim.setGraphicsLayer('game');
                break;

            case GameState.QuestComplete:
                ctx.renderGameSuppressed(); // C: quest_results_screen_update renders world, then ui_cursor_render
                ctx.grim.setGraphicsLayer('ui');
                if (ctx.font) {
                    ctx.screens.questCompleteScreen.render(ctx.grim, ctx.font, ctx.grim.getMouseX(), ctx.grim.getMouseY());
                }
                ctx.renderMenuCursor(); // C: ui_cursor_render() at quest.c:811
                ctx.grim.setGraphicsLayer('game');
                break;

            case GameState.Statistics:
                // Render menu as background
                this.renderMenu(ctx);
                // Render statistics or leaderboard overlay
                if (ctx.font) {
                    if (ctx.screens.leaderboardScreen.isVisible()) {
                        ctx.screens.leaderboardScreen.render(
                            ctx.grim,
                            ctx.font,
                            ctx.grim.getMouseX(),
                            ctx.grim.getMouseY(),
                        );
                    } else {
                        ctx.screens.statisticsScreen.render(
                            ctx.grim,
                            ctx.font,
                            ctx.grim.getMouseX(),
                            ctx.grim.getMouseY(),
                        );
                    }
                }
                ctx.renderMenuCursor();
                break;

            case GameState.Credits:
                // Render menu as background
                this.renderMenu(ctx);
                // Render credits overlay
                if (ctx.font) {
                    ctx.screens.creditsScreen.render(ctx.grim, ctx.font, ctx.grim.getMouseX(), ctx.grim.getMouseY());
                }
                ctx.renderMenuCursor();
                break;

            case GameState.AlienZooKeeper:
                // Render menu as background
                this.renderMenu(ctx);
                // Render AlienZooKeeper overlay
                if (ctx.font) {
                    ctx.screens.alienZooKeeperScreen.render(
                        ctx.grim,
                        ctx.font,
                        ctx.grim.getMouseX(),
                        ctx.grim.getMouseY(),
                    );
                }
                ctx.renderMenuCursor();
                break;
        }

        // Render console on top if open — uses dedicated 'console' layer above all UI
        if (gameConsole.getIsOpen()) {
            ctx.renderConsole();
        }
    }

    /**
     * Render main menu (and menu background for overlay states).
     * MainMenu.render() draws the terrain via drawQuad(), so we hide
     * the PIXI terrain sprite to avoid double-rendering.
     */
    private renderMenu(ctx: GameStateContext): void {
        // Reset camera offset so menu items render at correct screen positions.
        // During gameplay, setCameraOffset moves spriteContainer/graphics to follow
        // the player. Without this reset, the stale offset shifts menu items off-screen.
        ctx.grim.setCameraOffset(0, 0);
        ctx.screens.mainMenu.render(ctx.grim);
    }

    /**
     * Update perk selection screen.
     *
     * C code reference: perk_selection_screen_update @ lines 4528-4696
     * Moved from Game.updatePerkSelection() (lines 916–965).
     */
    private updatePerkSelection(ctx: GameStateContext): void {
        // Build input state from keyboard + mouse
        const input: PerkSelectionInput = {
            mouseX: ctx.grim.getMouseX(),
            mouseY: ctx.grim.getMouseY(),
            mouseClicked: ctx.grim.isMouseButtonPressed(0),
            upPressed: ctx.grim.isKeyPressed(KeyCode.Up) || ctx.grim.isKeyPressed(KeyCode.W),
            downPressed: ctx.grim.isKeyPressed(KeyCode.Down) || ctx.grim.isKeyPressed(KeyCode.S),
            confirmPressed: ctx.grim.isKeyPressed(KeyCode.Enter),
            cancelPressed: ctx.grim.isKeyPressed(KeyCode.Escape),
        };

        // Update perk selection
        const result = ctx.screens.perkSelectionScreen.update(input);

        // Handle selection result
        if (result === -1) {
            // Cancelled - return to game without selecting (optional, C allows cancel)
            ctx.screens.perkSelectionScreen.hide();
            ctx.state = GameState.Playing;
            gameConsole.print('Perk selection cancelled.');
        } else if (result !== null) {
            // Perk selected - apply it (C line 4400: perk_apply)
            const perkId = result as PerkId;
            ctx.systems.perkSystem.addPerk(perkId);
            ctx.perkPendingCount = Math.max(0, ctx.perkPendingCount - 1);
            ctx.perkJustSelected = true; // Signal tutorial progression

            // Apply instant perk effects (C: perk_apply @ lines 144-298)
            if (ctx.player) {
                const fx = applyInstantPerkEffect(perkId, ctx.player.experience, ctx.player.health);
                const fxResult = applyInstantPerkEffectToGame(fx, {
                    player: ctx.player,
                    perkSystem: ctx.systems.perkSystem,
                    enemySpawner: ctx.systems.enemySpawner,
                    lastLevel: ctx.lastLevel,
                    perkPendingCount: ctx.perkPendingCount,
                });
                ctx.lastLevel = fxResult.lastLevel;
                ctx.perkPendingCount = fxResult.perkPendingCount;
            }

            ctx.screens.perkSelectionScreen.hide();
            ctx.state = GameState.Playing;

            // Get perk name for feedback
            const perkName = PERK_META[perkId]?.name || 'Unknown';
            gameConsole.print(`Selected perk: ${perkName}`);
        }
    }

    /**
     * Handle quest completion.
     * Awards weapon/perk unlocks and shows the quest complete results screen.
     *
     * C code reference: quest completion handling @ lines 4891-4926
     * Moved from Game.handleQuestCompletion() (lines 972–991).
     */
    handleQuestCompletion(ctx: GameStateContext): void {
        _handleQuestCompletion({
            player: ctx.player,
            scoreSystem: ctx.systems.scoreSystem,
            perkPendingCount: ctx.perkPendingCount,
            questCompleteScreen: ctx.screens.questCompleteScreen,
            enemySpawner: ctx.systems.enemySpawner,
            musicSystem: ctx.systems.musicSystem,
            mainMenu: ctx.screens.mainMenu,
            grim: ctx.grim,
            saveSystem: ctx.systems.saveSystem,
            highScoreSystem: ctx.systems.highScoreSystem,
            leaderboardScreen: ctx.screens.leaderboardScreen,
            startGame: () => ctx.startGame(),
            regenerateTerrain: (tier) => ctx.regenerateTerrain(tier),
        });
        ctx.perkPendingCount = 0;
        ctx.perkPromptTimer = 0; // Clear "Press Mouse2" prompt text
        ctx.state = GameState.QuestComplete;

        // Fade out to black on quest completion (C: screen_fade_alpha → 1.0)
        ctx.screenFade.fadeOut(2.0);
    }

    /**
     * Update quest complete screen.
     *
     * Moved from Game.updateQuestComplete() (lines 996–1017).
     */
    private updateQuestComplete(ctx: GameStateContext): void {
        const questResult = updateQuestCompleteScreen({
            player: ctx.player,
            scoreSystem: ctx.systems.scoreSystem,
            perkPendingCount: ctx.perkPendingCount,
            questCompleteScreen: ctx.screens.questCompleteScreen,
            enemySpawner: ctx.systems.enemySpawner,
            musicSystem: ctx.systems.musicSystem,
            mainMenu: ctx.screens.mainMenu,
            grim: ctx.grim,
            saveSystem: ctx.systems.saveSystem,
            highScoreSystem: ctx.systems.highScoreSystem,
            leaderboardScreen: ctx.screens.leaderboardScreen,
            startGame: () => ctx.startGame(),
            regenerateTerrain: (tier) => ctx.regenerateTerrain(tier),
        });
        ctx.perkPendingCount = questResult.perkPendingCount;
        if (questResult.newGameMode !== undefined) {
            ctx.gameMode = questResult.newGameMode;
        }
        if (questResult.newState !== undefined) {
            // Set return latch when going to Statistics from QuestComplete
            if (questResult.newState === GameState.Statistics) {
                this.returnFromStatistics = GameState.QuestComplete;
            }
            ctx.state = questResult.newState;
        }
    }

    /**
     * Update game over screen (Survival/Rush death).
     *
     * C code: game_over_screen_update (gameplay.c:670-980)
     * Moved from Game.updateGameOver() (lines 1023–1057).
     */
    private updateGameOver(ctx: GameStateContext): void {
        const dtMs = ctx.grim.getDeltaTime();
        const chars = ctx.grim.getKeyChars();
        const charInput = chars.map((c) => String.fromCharCode(c)).join('');

        const input: GameOverInput = {
            mouseX: ctx.grim.getMouseX(),
            mouseY: ctx.grim.getMouseY(),
            mouseClicked: ctx.grim.isMouseButtonPressed(0),
            confirmPressed: ctx.grim.isKeyPressed(KeyCode.Enter) || ctx.grim.isKeyPressed(KeyCode.Space),
            cancelPressed: ctx.grim.isKeyPressed(KeyCode.Escape),
            charInput,
            backspacePressed: ctx.grim.isKeyPressed(KeyCode.Backspace),
        };

        const action = ctx.screens.gameOverScreen.update(dtMs, input);

        switch (action) {
            case GameOverAction.PlayAgain:
                ctx.screens.gameOverScreen.hide();
                ctx.startGame(); // Restart same mode
                break;
            case GameOverAction.HighScores:
                this.returnFromStatistics = GameState.GameOver;
                ctx.screens.leaderboardScreen.show();
                ctx.state = GameState.Statistics;
                break;
            case GameOverAction.MainMenu:
                ctx.screens.gameOverScreen.hide();
                ctx.state = GameState.Menu;
                ctx.systems.musicSystem.play('crimson_theme.ogg');
                ctx.screenFade.setAlpha(0); // Clear fade for menu
                break;
        }
    }

    /**
     * Update quest failed screen (Quest death).
     *
     * C code: quest_failed_screen_update (quest.c:80-245)
     * Moved from Game.updateQuestFailed() (lines 1063–1101).
     */
    private updateQuestFailed(ctx: GameStateContext): void {
        const dtMs = ctx.grim.getDeltaTime();
        const chars = ctx.grim.getKeyChars();
        const charInput = chars.map((c) => String.fromCharCode(c)).join('');

        const input: QuestFailedInput = {
            mouseX: ctx.grim.getMouseX(),
            mouseY: ctx.grim.getMouseY(),
            mouseClicked: ctx.grim.isMouseButtonPressed(0),
            confirmPressed: ctx.grim.isKeyPressed(KeyCode.Enter) || ctx.grim.isKeyPressed(KeyCode.Space),
            cancelPressed: ctx.grim.isKeyPressed(KeyCode.Escape),
            charInput,
            backspacePressed: ctx.grim.isKeyPressed(KeyCode.Backspace),
        };

        const action = ctx.screens.questFailedScreen.update(dtMs, input);

        switch (action) {
            case QuestFailedAction.PlayAgain: {
                ctx.screens.questFailedScreen.hide();
                ctx.questFailRetryCount++;
                // Re-initialize quest system (C: game_state_pending = 9 → quest_start_selected)
                // Must set spawn callback and call startQuest() before startGame()
                // so the quest has a spawn table and the player gets the correct weapon.
                const retryTier = questSystem.getStageMajor();
                const retryIndex = questSystem.getStageMinor();
                questSystem.setSpawnCallback((entry) => {
                    for (let i = 0; i < entry.count; i++) {
                        const enemy = ctx.systems.enemySpawner.spawnQuestEnemy(entry.posX, entry.posY, entry.templateId);
                        if (enemy) {
                            questSystem.reportEnemySpawned(1);
                        }
                    }
                });
                questSystem.startQuest(retryTier, retryIndex);
                // Regenerate terrain to clear baked blood/corpses (C: terrain_generate in quest_start_selected)
                ctx.regenerateTerrain(retryTier);
                ctx.startGame();
                break;
            }
            case QuestFailedAction.PlayAnother:
                ctx.screens.questFailedScreen.hide();
                ctx.questFailRetryCount = 0;
                ctx.state = GameState.Menu;
                ctx.systems.musicSystem.play('crimson_theme.ogg');
                ctx.screenFade.setAlpha(0); // Clear fade for menu
                ctx.screens.mainMenu.showPlayMenu(); // Navigate to play sub-menu
                ctx.screens.mainMenu.showQuestScreen(); // Then open quest selection
                break;
            case QuestFailedAction.MainMenu:
                ctx.screens.questFailedScreen.hide();
                ctx.questFailRetryCount = 0;
                ctx.state = GameState.Menu;
                ctx.systems.musicSystem.play('crimson_theme.ogg');
                ctx.screenFade.setAlpha(0); // Clear fade for menu
                break;
        }
    }
}
