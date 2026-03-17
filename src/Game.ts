/**
 * Game - Main game class
 *
 * Thin orchestrator: owns the game loop, delegates to
 * GameStateHandler (input/update/render), GameInit (startup),
 * and GamePlayingUpdate (per-frame gameplay).
 */

import { PixiGrimAdapter, BitmapFont } from './engine';
import { gameConsole } from './console/Console';
import type { GrimInterface } from './engine/GrimInterface';
import { AssetManager } from './data';
import { GameStateHandler } from './GameStateHandler';
import { updatePlaying as _updatePlaying } from './GamePlayingUpdate';
import { initGame, startGameSession } from './GameInit';
import { Player } from './entities/Player';

import { GameSystems } from './GameSystems';
import { GameScreens } from './GameScreens';
import { SurvivalState } from './SurvivalState';
import { TerrainState } from './TerrainState';

import { SpriteRenderer } from './rendering/SpriteRenderer';
import { GameplayCursor } from './rendering/GameplayCursor';
import { ScreenFade } from './rendering/ScreenFade';

import { questSystem } from './systems/quest/QuestSystem';

import * as PIXI from 'pixi.js';
import {
    applyBonusEffect as _applyBonusEffect,
    handleChainLightning as _handleChainLightning,
    type BonusEffectContext,
} from './systems/bonus/BonusEffects';
import {
    renderGame as _renderGame,
    renderConsole as _renderConsole,
    type GameRenderContext,
} from './rendering/GameRenderer';

// Re-export enums for backward compatibility
export { GameState, GameMode } from './GameTypes';
import { GameState, GameMode } from './GameTypes';

/**
 * Main Game class
 */
export class Game {
    // --- Core infrastructure ---
    grim: GrimInterface;
    assetManager: AssetManager;
    state: GameState = GameState.Loading;
    private running: boolean = false;
    private backgroundTimerId: ReturnType<typeof setTimeout> | null = null;
    preloadedAssets?: { crimsonPaq: ArrayBuffer; sfxPaq: ArrayBuffer };

    // --- Game mode & flags ---
    gameMode: GameMode = GameMode.Survival;
    // Suppresses weapon firing for N frames after game start to prevent
    // the menu button click from firing a bullet on the first frame.
    fireGuardActive: boolean = false;
    font: BitmapFont | null = null;
    player: Player | null = null;

    // --- Bundled systems, screens, and state groups ---
    readonly systems = new GameSystems();
    readonly screens = new GameScreens();
    readonly survivalState = new SurvivalState();
    readonly terrainState = new TerrainState();

    // --- Rendering ---
    readonly spriteRenderer: SpriteRenderer = new SpriteRenderer();
    readonly gameplayCursor: GameplayCursor = new GameplayCursor();
    screenFade: ScreenFade = new ScreenFade();

    // --- Misc scalar state ---
    lastLevel: number = 1; // unused after XP refactor — kept for safety
    perkPendingCount: number = 0; // C: perk_pending_count — how many perks waiting to be picked
    perkJustSelected: boolean = false; // Tracks perk selection for tutorial progression
    tutorialKillCount: number = 0; // Kill count tracker for tutorial combat stages
    perkPromptTimer: number = 0; // C: perk_prompt_timer — fade animation for prompt text (0-200ms)
    questFailRetryCount: number = 0;

    // Chain lightning state (C lines 19290-19303)
    shockChainLinksLeft: number = 0;
    shockChainProjectileId: number = -1;
    nextProjectileId: number = 0; // Counter for unique projectile IDs

    // Camera offset (C: camera_update @ 00409500)
    // Centers the view on the player: offset = screenCenter - playerPos
    cameraOffsetX: number = 0;
    cameraOffsetY: number = 0;

    // Bonus animation timer (C: bonus_animation_timer += frame_dt * 1.3)
    bonusAnimTimer: number = 0.0;

    // Debug rendering mode (true = debug shapes, false = sprites)
    debugRenderMode: boolean = false;
    debugEnemyHeading: boolean = false;

    // Track whether menu music has started (deferred until first user interaction)
    menuMusicStarted: boolean = false;

    // State handler (extracted from Game.ts)
    private stateHandler: GameStateHandler = new GameStateHandler();

    // Expose questSystem singleton for GameRenderContext (HUD quest name display)
    get questSystem() {
        return questSystem;
    }

    // ============================================
    // Compatibility getter aliases
    // Used by duck-typed contexts (GameRenderContext, BonusEffectContext)
    // that reference these fields by their pre-refactor flat names.
    // The `as unknown as` casts bypass TypeScript but JS needs the
    // properties to actually exist on the object.
    // ============================================

    /** @internal duck-type alias for GameRenderContext / BonusEffectContext */
    get weaponSystem() { return this.systems.weaponSystem; }
    get enemySpawner() { return this.systems.enemySpawner; }
    get collisionSystem() { return this.systems.collisionSystem; }
    get perkSystem() { return this.systems.perkSystem; }
    get bonusSystem() { return this.systems.bonusSystem; }
    get scoreSystem() { return this.systems.scoreSystem; }
    get particleSystem() { return this.systems.particleSystem; }
    get effectSystem() { return this.systems.effectSystem; }
    get bloodEffectSystem() { return this.systems.bloodEffectSystem; }
    get soundSystem() { return this.systems.soundSystem; }
    get musicSystem() { return this.systems.musicSystem; }
    get cameraShake() { return this.systems.cameraShake; }
    get tutorialSystem() { return this.systems.tutorialSystem; }
    get highScoreSystem() { return this.systems.highScoreSystem; }
    get saveSystem() { return this.systems.saveSystem; }
    get achievementSystem() { return this.systems.achievementSystem; }
    get enemyDeathEffects() { return this.systems.enemyDeathEffects; }

    /** @internal duck-type alias for GameRenderContext */
    get hud() { return this.screens.hud; }
    get mainMenu() { return this.screens.mainMenu; }
    get pauseMenu() { return this.screens.pauseMenu; }
    get perkSelectionScreen() { return this.screens.perkSelectionScreen; }
    get questCompleteScreen() { return this.screens.questCompleteScreen; }
    get gameOverScreen() { return this.screens.gameOverScreen; }
    get questFailedScreen() { return this.screens.questFailedScreen; }
    get statisticsScreen() { return this.screens.statisticsScreen; }
    get leaderboardScreen() { return this.screens.leaderboardScreen; }
    get creditsScreen() { return this.screens.creditsScreen; }
    get alienZooKeeperScreen() { return this.screens.alienZooKeeperScreen; }

    /** @internal duck-type alias for GameRenderContext (terrain fields) */
    get _terrainSprite() { return this.terrainState.sprite; }
    get terrainRenderer() { return this.terrainState.renderer; }
    get terrainTextureHandle() { return this.terrainState.textureHandle; }
    get terrainSeed() { return this.terrainState.seed; }

    constructor(preloadedAssets?: { crimsonPaq: ArrayBuffer; sfxPaq: ArrayBuffer }) {
        // Default to 800x600 (original game resolution)
        this.grim = new PixiGrimAdapter(800, 600);
        this.assetManager = new AssetManager({ basePath: '/content/' });
        this.preloadedAssets = preloadedAssets;
    }

    /**
     * Initialize the game.
     * Logic extracted to GameInit.ts.
     */
    async init(): Promise<boolean> {
        const result = await initGame(this);

        return result;
    }

    /**
     * Regenerate terrain for a specific quest tier.
     * NOT delegated through context — async .then() callbacks need direct
     * access to Game fields (context would be stale by the time they fire).
     * @param tier - Quest tier (1-4)
     */
    regenerateTerrain(tier: number): void {
        if (!this.terrainState.renderer) {
            gameConsole.print(`[Terrain] Renderer not initialized, skipping tier ${tier} generation`);
            return;
        }

        gameConsole.print(`[Terrain] Regenerating for tier ${tier}...`);

        // Destroy old sprite immediately so the fallback render path
        // (GameRenderer.ts L98-102: drawQuad with bound texture) is used
        // during the async gap. Without this, a stale or half-torn-down
        // sprite could produce the "circles with flat shading" artifact.
        if (this.terrainState.sprite) {
            this.terrainState.sprite.destroy();
            this.terrainState.sprite = null;
        }

        // Regenerate asynchronously without blocking
        this.terrainState.renderer
            .regenerate(this.assetManager, tier, this.terrainState.seed)
            .then((texture) => {
                if (texture) {
                    // Register new terrain texture
                    this.terrainState.textureHandle = this.grim.registerTexture('game_terrain', texture);

                    // Create new Sprite for terrain draw.
                    // Uses buffered render texture — no tiling/wrapping.
                    const app = (this.grim as PixiGrimAdapter).getApp();
                    if (app) {
                        this.terrainState.sprite = new PIXI.Sprite(texture);
                        this.terrainState.sprite.blendMode = 'none';
                        app.stage.addChildAt(this.terrainState.sprite, 0);
                    }

                    gameConsole.print(`[Terrain] Tier ${tier} terrain loaded successfully`);

                } else {
                    gameConsole.print(`[Terrain] Failed to generate tier ${tier} terrain`);
                }
            })
            .catch((err) => {
                gameConsole.print(`[Terrain] Error regenerating terrain: ${err}`);
            });
    }



    /**
     * Start a new game.
     * Logic extracted to GameInit.ts.
     */
    startGame(): void {
        startGameSession(this);
    }

    /**
     * Start the game loop
     */
    start(): void {
        if (this.running) return;
        this.running = true;

        // Listen for tab visibility changes to ensure smooth transitions
        // between RAF (visible) and setTimeout (hidden) game loop modes
        document.addEventListener('visibilitychange', () => {
            if (!document.hidden && this.running) {
                // Cancel any pending background timeout to prevent duplicate loops
                if (this.backgroundTimerId !== null) {
                    clearTimeout(this.backgroundTimerId);
                    this.backgroundTimerId = null;
                }
                // Tab became visible — kick the game loop back to RAF
                requestAnimationFrame(() => this.gameLoop());
            }
        });

        this.gameLoop();
    }

    /**
     * Stop the game loop
     */
    stop(): void {
        this.running = false;
    }

    /**
     * Main game loop
     */
    private gameLoop(): void {
        if (!this.running) return;

        // Begin frame (updates timing, clears screen)
        this.grim.beginFrame();

        // Process input
        this.stateHandler.handleInput(this);

        // Update game logic
        this.stateHandler.update(this);

        // Render
        this.stateHandler.render(this);

        // End frame
        this.grim.endFrame();

        // Schedule next frame
        // Use RAF when tab is visible, setTimeout fallback when hidden
        // so loading and game logic continue in the background
        if (document.hidden) {
            this.backgroundTimerId = setTimeout(() => {
                this.backgroundTimerId = null;
                this.gameLoop();
            }, 100); // 10fps background tick
        } else {
            requestAnimationFrame(() => this.gameLoop());
        }
    }

    /**
     * Update playing state.
     * Logic extracted to GamePlayingUpdate.ts.
     */
    updatePlaying(dt: number): void {
        if (!this.player) return;
        // The null-guard above guarantees player is non-null,
        // but GamePlayingContext requires `player: Player` — use type assertion.
        _updatePlaying(this as unknown as import('./GamePlayingUpdate').GamePlayingContext, dt);
    }

    /**
     * Handle quest completion.
     * Logic extracted to GameStateHandler.ts.
     */
    handleQuestCompletion(): void {
        this.stateHandler.handleQuestCompletion(this);
    }

    /**
     * Add a bonus HUD slot (called by BonusEffects via BonusEffectContext).
     * Delegates to HUD.addBonusSlot to show a sliding panel for timed bonuses.
     */
    addBonusHudSlot = (label: string, iconId: number, getTimer: () => number, timerKey: string): void => {
        this.screens.hud.addBonusSlot(label, iconId, getTimer, timerKey);
    };

    /**
     * Apply bonus effect when picked up (C lines 6364-6483).
     * Logic extracted to BonusEffects.ts.
     */
    applyBonusEffect(bonus: any): void {
        _applyBonusEffect(this as unknown as BonusEffectContext, bonus);
    }

    /**
     * Handle chain lightning propagation (C lines 19290-19303).
     * Logic extracted to BonusEffects.ts.
     */
    handleChainLightning(projectile: any, hitEnemy: any): void {
        _handleChainLightning(this as unknown as BonusEffectContext, projectile, hitEnemy);
    }

    /**
     * Render gameplay.
     * Logic extracted to GameRenderer.ts.
     */
    renderGame(): void {
        _renderGame(this as unknown as GameRenderContext);
    }

    /**
     * Render gameplay with gameplay cursor (reticle) suppressed.
     * Used by overlay states (pause, perk selection, game over, quest screens)
     * where the menu cursor replaces the gameplay reticle.
     */
    renderGameSuppressed(): void {
        (this as any).suppressGameplayCursor = true;
        _renderGame(this as unknown as GameRenderContext);
        (this as any).suppressGameplayCursor = false;
    }

    /**
     * Render the shared menu cursor (pointer with animated glow).
     */
    renderMenuCursor(): void {
        const cursor = this.screens.mainMenu.getMenuCursor();
        cursor.update(this.grim.getDeltaTime());
        cursor.render(this.grim);
    }

    /**
     * Render console overlay.
     * Logic extracted to GameRenderer.ts.
     */
    renderConsole(): void {
        _renderConsole(this as unknown as GameRenderContext);
    }

    /**
     * Get the Grim interface
     */
    getGrim(): GrimInterface {
        return this.grim;
    }

    /**
     * Get current game state
     */
    getState(): GameState {
        return this.state;
    }

    // ============================================
    // Test introspection getters (used by Playwright E2E bridge)
    // ============================================

    getPlayer(): Player | null {
        return this.player;
    }

    getEnemySpawner() {
        return this.systems.enemySpawner;
    }

    getScoreSystem() {
        return this.systems.scoreSystem;
    }

    getGameMode(): GameMode {
        return this.gameMode;
    }

    // ============================================
    // GameCommandContext implementation
    // (used by GameConsoleCommands.ts)
    // ============================================

    /** @internal – GameCommandContext interface */
    setState(s: GameState): void {
        this.state = s;
    }

    /** @internal – GameCommandContext interface */
    setGameMode(m: GameMode): void {
        this.gameMode = m;
    }

    /** @internal – GameCommandContext interface */
    startTutorial(): void {
        this.systems.tutorialSystem.start();
    }

    /** @internal – GameCommandContext interface */
    getPerkSystem() {
        return this.systems.perkSystem;
    }

    /** @internal – GameCommandContext interface */
    getAssetManager(): AssetManager {
        return this.assetManager;
    }

    /** @internal – GameCommandContext interface */
    getBloodEffectSystem() {
        return this.systems.bloodEffectSystem;
    }

    /** @internal – GameCommandContext interface */
    getEnemyDeathEffects() {
        return this.systems.enemyDeathEffects;
    }

    /** @internal – GameCommandContext interface */
    getQuestCompleteScreen() {
        return this.screens.questCompleteScreen;
    }

    /** @internal – GameCommandContext interface */
    getDebugRenderMode(): boolean {
        return this.debugRenderMode;
    }

    /** @internal – GameCommandContext interface */
    setDebugRenderMode(v: boolean): void {
        this.debugRenderMode = v;
    }

    /** @internal – GameCommandContext interface */
    getDebugEnemyHeading(): boolean {
        return this.debugEnemyHeading;
    }

    /** @internal – GameCommandContext interface */
    setDebugEnemyHeading(v: boolean): void {
        this.debugEnemyHeading = v;
    }

    getTutorialStage(): number {
        return this.systems.tutorialSystem.getStage();
    }

    /** @internal – GameCommandContext interface */
    getTutorialSystem() {
        return this.systems.tutorialSystem;
    }

    /** @internal – GameCommandContext interface */
    getAlienZooKeeperScreen() {
        return this.screens.alienZooKeeperScreen;
    }

    isTutorialActive(): boolean {
        return this.systems.tutorialSystem.isActive();
    }
}
