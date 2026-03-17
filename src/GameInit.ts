/**
 * GameInit - Initialization and game-start logic extracted from Game.ts.
 *
 * Contains initGame(), loadGameFont(), regenerateGameTerrain(),
 * registerGameContextCommands(), and startGameSession().
 */

import { BitmapFont } from './engine';
import { gameConsole } from './console/Console';
import { GameState, GameMode } from './GameTypes';
import { questSystem } from './systems/quest/QuestSystem';
import { loadAllGameAssets, wireGameSystems, type GameAssets } from './GameInitializer';
import { startNewGame } from './GameStarter';
import { registerGameCommands, type GameCommandContext } from './console/GameConsoleCommands';
import type { GrimInterface } from './engine/GrimInterface';
import type { AssetManager } from './data';
import type { Player } from './entities/Player';
import type { GameSystems } from './GameSystems';
import type { GameScreens } from './GameScreens';
import type { SurvivalState } from './SurvivalState';
import type { TerrainState } from './TerrainState';
import type { SpriteRenderer } from './rendering/SpriteRenderer';
import type { GameplayCursor } from './rendering/GameplayCursor';
import type { ScreenFade } from './rendering/ScreenFade';
import { getPerkUnlockRegistry } from './systems/PerkUnlockRegistry';
import { getWeaponUnlockRegistry } from './systems/WeaponUnlockRegistry';

/**
 * Duck-typed context for game initialization.
 * The Game class satisfies this interface directly — no context copying needed.
 */
export interface GameInitContext {
    // Engine
    grim: GrimInterface;
    assetManager: AssetManager;

    // Font
    font: BitmapFont | null;

    // Bundled systems & screens
    readonly systems: GameSystems;
    readonly screens: GameScreens;

    // Grouped state
    readonly survivalState: SurvivalState;
    readonly terrainState: TerrainState;

    // Rendering
    readonly spriteRenderer: SpriteRenderer;
    readonly gameplayCursor: GameplayCursor;
    readonly screenFade: ScreenFade;

    // State
    state: GameState;
    gameMode: GameMode;
    player: Player | null;
    cameraOffsetX: number;
    cameraOffsetY: number;
    fireGuardActive: boolean;
    lastLevel: number;
    perkPendingCount: number;

    // Chain lightning state (kept for noUnusedLocals satisfaction)
    shockChainLinksLeft: number;
    shockChainProjectileId: number;
    nextProjectileId: number;

    // Pre-loaded PAQ buffers (from IndexedDB or upload screen)
    preloadedAssets?: { crimsonPaq: ArrayBuffer; sfxPaq: ArrayBuffer };
}

/**
 * Initialize the game — async setup, PAQ loading, asset loading, font, terrain, wiring.
 *
 * Moved from Game.init() (lines 223–317).
 */
export async function initGame(ctx: GameInitContext): Promise<boolean> {
    gameConsole.print('Initializing Crimsonland...');

    const success = await ctx.grim.init();
    if (!success) {
        gameConsole.print('Failed to initialize rendering engine');
        return false;
    }

    // Load PAQ archives (must complete before other asset loading)
    gameConsole.print('Loading game assets...');
    try {
        if (ctx.preloadedAssets) {
            // Pre-loaded mode: PAQ data was loaded from IndexedDB or upload screen
            ctx.assetManager.loadPaqFromBuffer(ctx.preloadedAssets.crimsonPaq, 'crimson.paq');
            gameConsole.print(`Loaded crimson.paq from cache (${ctx.assetManager.fileCount} files)`);

            ctx.assetManager.loadPaqFromBuffer(ctx.preloadedAssets.sfxPaq, 'sfx.paq');
            gameConsole.print(`Loaded sfx.paq from cache (${ctx.assetManager.fileCount} total files)`);
        } else {
            // Fetch mode: load from content/ directory (dev server)
            await ctx.assetManager.loadPaq('crimson.paq');
            gameConsole.print(`Loaded crimson.paq (${ctx.assetManager.fileCount} files)`);

            await ctx.assetManager.loadPaq('sfx.paq');
            gameConsole.print(`Loaded sfx.paq (${ctx.assetManager.fileCount} total files)`);
        }
    } catch (error) {
        gameConsole.print(`Warning: Failed to load PAQ archives: ${error}`);
    }

    // Register game console commands (no async dependency)
    registerGameContextCommands(ctx);

    // Set initial clear color (dark red-ish like original)
    ctx.grim.setClearColor(32, 16, 16, 255);

    // Initialize audio contexts (must happen before sample/track loading)
    await ctx.systems.soundSystem.init();
    await ctx.systems.musicSystem.init();

    // Phase 2: Run all independent loading phases in parallel
    // Dependencies: all phases below depend on PAQ data (loaded above)
    // and audio contexts (initialized above), but NOT on each other.
    gameConsole.print('Loading assets in parallel...');

    const gameAssets: GameAssets = {
        mainMenu: ctx.screens.mainMenu,
        perkSelectionScreen: ctx.screens.perkSelectionScreen,
        questCompleteScreen: ctx.screens.questCompleteScreen,
        gameOverScreen: ctx.screens.gameOverScreen,
        questFailedScreen: ctx.screens.questFailedScreen,
        statisticsScreen: ctx.screens.statisticsScreen,
        leaderboardScreen: ctx.screens.leaderboardScreen,
        creditsScreen: ctx.screens.creditsScreen,
        alienZooKeeperScreen: ctx.screens.alienZooKeeperScreen,
        spriteRenderer: ctx.spriteRenderer,
        gameplayCursor: ctx.gameplayCursor,
        hud: ctx.screens.hud,
        soundSystem: ctx.systems.soundSystem,
        musicSystem: ctx.systems.musicSystem,
        terrainRenderer: ctx.terrainState.renderer,
        assetManager: ctx.assetManager,
        grim: ctx.grim,
    };

    const loaded = await loadAllGameAssets(gameAssets, ctx.terrainState.seed, () => loadGameFont(ctx));
    ctx.terrainState.textureHandle = loaded.terrainTextureHandle;
    if (loaded.terrainRenderer) {
        ctx.terrainState.renderer = loaded.terrainRenderer;
    }

    // Camera init fix: center on terrain (C: camera_offset_x = terrain_texture_width * 0.5, gameplay.c L1441)
    // Prevents incorrect rendering at (0,0) before startGame() is called
    const initTerrainW = ctx.terrainState.renderer?.getPlayableWidth() ?? 1024;
    const initTerrainH = ctx.terrainState.renderer?.getPlayableHeight() ?? 1024;
    ctx.cameraOffsetX = initTerrainW * 0.5;
    ctx.cameraOffsetY = initTerrainH * 0.5;

    // NOTE: onResize callback is registered by Game.ts after init
    // to avoid closing over a dead context object.

    wireGameSystems(gameAssets, ctx.screens.pauseMenu);

    // Menu music will start on first user interaction (see update() method)

    // Load game status (C: game_load_status @ lines 11225-11291)
    const gameStatus = ctx.systems.saveSystem.loadGameStatus();
    gameConsole.print(`Loaded game status (quest unlock: ${gameStatus.questUnlockIndex})`);

    // Sync quest unlock index with save system
    questSystem.setUnlockIndex(gameStatus.questUnlockIndex);

    // Load unlocked perks from save data into PerkUnlockRegistry
    const savedPerkIds = gameStatus.unlockedPerkIds ?? [];
    if (savedPerkIds.length > 0) {
        getPerkUnlockRegistry().loadUnlockedPerks(savedPerkIds);
        gameConsole.print(`Loaded ${savedPerkIds.length} unlocked perks`);
    }

    // Load unlocked weapons from save data into WeaponUnlockRegistry
    // C: weapon_refresh_available @ 00452e40
    const weaponRegistry = getWeaponUnlockRegistry();
    const savedWeaponIds = gameStatus.unlockedWeaponIds ?? [];
    if (savedWeaponIds.length > 0) {
        weaponRegistry.loadUnlockedWeapons(savedWeaponIds);
        gameConsole.print(`Loaded ${savedWeaponIds.length} unlocked weapons`);
    } else {
        // No saved weapons — rebuild from quest progress
        weaponRegistry.refreshAvailable(gameStatus.questUnlockIndex);
        gameConsole.print(`Refreshed weapon availability from quest progress (${weaponRegistry.getUnlockedCount()} weapons)`);
    }

    gameConsole.print('Crimsonland initialized');
    gameConsole.print('Press ~ to open console');

    // Satisfy noUnusedLocals — chain lightning fields are written here awaiting future C-port
    void ctx.shockChainLinksLeft;
    void ctx.shockChainProjectileId;
    void ctx.nextProjectileId;

    ctx.state = GameState.Menu;
    return true;
}

/**
 * Load the bitmap font from PAQ assets.
 *
 * Moved from Game.loadFont() (lines 322–335).
 */
export async function loadGameFont(ctx: GameInitContext): Promise<void> {
    ctx.font = new BitmapFont();
    await ctx.font.loadAssets(ctx.assetManager, ctx.grim);

    if (!ctx.font.isLoaded()) {
        gameConsole.print('Warning: Failed to load font');
    }
}

/**
 * Regenerate terrain for a specific quest tier.
 *
 * @param tier - Quest tier (1-4)
 * Moved from Game.regenerateTerrain() (lines 341–388).
 */
export function regenerateGameTerrain(ctx: GameInitContext, tier: number): void {
    if (!ctx.terrainState.renderer) {
        gameConsole.print(`[Terrain] Renderer not initialized, skipping tier ${tier} generation`);
        return;
    }

    gameConsole.print(`[Terrain] Regenerating for tier ${tier}...`);

    // Regenerate asynchronously without blocking
    ctx.terrainState.renderer
        .regenerate(ctx.assetManager, tier, ctx.terrainState.seed)
        .then((texture) => {
            if (texture) {
                // Register new terrain texture
                ctx.terrainState.textureHandle = ctx.grim.registerTexture('game_terrain', texture);

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
 * Register game-specific console commands.
 *
 * Moved from Game.registerCommands() (lines 393–395).
 */
export function registerGameContextCommands(ctx: GameInitContext): void {
    registerGameCommands(ctx as unknown as GameCommandContext);
}

/**
 * Start a new game session — creates player, resets systems, sets state.
 *
 * Moved from Game.startGame() (lines 400–434).
 */
export function startGameSession(ctx: GameInitContext): void {
    const result = startNewGame({
        terrainRenderer: ctx.terrainState.renderer,
        spriteRenderer: ctx.spriteRenderer,
        grim: ctx.grim,
        gameMode: ctx.gameMode,
        weaponSystem: ctx.systems.weaponSystem,
        collisionSystem: ctx.systems.collisionSystem,
        enemySpawner: ctx.systems.enemySpawner,
        bonusSystem: ctx.systems.bonusSystem,
        perkSystem: ctx.systems.perkSystem,
        scoreSystem: ctx.systems.scoreSystem,
        bloodEffectSystem: ctx.systems.bloodEffectSystem,
        enemyDeathEffects: ctx.systems.enemyDeathEffects,
        musicSystem: ctx.systems.musicSystem,
        soundSystem: ctx.systems.soundSystem,
        particleSystem: ctx.systems.particleSystem,
        effectSystem: ctx.systems.effectSystem,
    });
    ctx.player = result.player;
    ctx.cameraOffsetX = result.cameraOffsetX;
    ctx.cameraOffsetY = result.cameraOffsetY;
    ctx.lastLevel = result.lastLevel;
    ctx.perkPendingCount = result.perkPendingCount;
    ctx.survivalState.spawnStage = result.survivalSpawnStage;
    ctx.survivalState.rewardDamageSeen = result.survivalRewardDamageSeen;
    ctx.survivalState.rewardFireSeen = result.survivalRewardFireSeen;
    ctx.survivalState.rewardHandoutEnabled = result.survivalRewardHandoutEnabled;
    ctx.survivalState.recentDeaths = result.survivalRecentDeaths;
    ctx.state = GameState.Playing;
    ctx.fireGuardActive = true; // Suppress firing until mouse is released (menu click guard)

    // Fade in from black (C: screen_fade_alpha = 1.0, fade_in_flag = true)
    ctx.screenFade.fadeIn(2.0);
}
