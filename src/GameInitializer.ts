import { type MainMenu } from './ui/screens/MainMenu';
import { type PerkSelectionScreen } from './ui/screens/PerkSelectionScreen';
import { type QuestCompleteScreen } from './ui/screens/QuestCompleteScreen';
import { type GameOverScreen } from './ui/screens/GameOverScreen';
import { type QuestFailedScreen } from './ui/screens/QuestFailedScreen';
import { type StatisticsScreen } from './ui/screens/StatisticsScreen';
import { type LeaderboardScreen } from './ui/screens/LeaderboardScreen';
import { type CreditsScreen } from './ui/screens/CreditsScreen';
import { type AlienZooKeeperScreen } from './ui/screens/AlienZooKeeperScreen';
import { type SpriteRenderer } from './rendering/SpriteRenderer';
import { type GameplayCursor } from './rendering/GameplayCursor';
import { type HUD } from './ui/HUD';
import { type SoundSystem } from './audio';
import { type MusicSystem } from './audio/MusicSystem';
import { TerrainRenderer } from './rendering/TerrainRenderer';
import { type AssetManager } from './data';
import type { GrimInterface } from './engine/GrimInterface';
import { type PauseMenu } from './ui/menus/PauseMenu';
import { gameConsole } from './console/Console';
import * as PIXI from 'pixi.js';

export interface GameAssets {
    mainMenu: MainMenu;
    perkSelectionScreen: PerkSelectionScreen;
    questCompleteScreen: QuestCompleteScreen;
    gameOverScreen: GameOverScreen;
    questFailedScreen: QuestFailedScreen;
    spriteRenderer: SpriteRenderer;
    gameplayCursor: GameplayCursor;
    hud: HUD;
    soundSystem: SoundSystem;
    musicSystem: MusicSystem;
    statisticsScreen: StatisticsScreen;
    leaderboardScreen: LeaderboardScreen;
    creditsScreen: CreditsScreen;
    alienZooKeeperScreen: AlienZooKeeperScreen;
    terrainRenderer: TerrainRenderer | null;
    assetManager: AssetManager;
    grim: GrimInterface;
}

export interface LoadAllGameAssetsResult {
    terrainTextureHandle: number;
    terrainRenderer: TerrainRenderer | null;
}

export async function loadAllGameAssets(
    assets: GameAssets,
    terrainSeed: number,
    loadFont: () => Promise<void>,
): Promise<LoadAllGameAssetsResult> {
    let terrainTextureHandle = -1;

    await Promise.all([
        // Menu assets (textures from crimson.paq)
        assets.mainMenu
            .loadAssets(assets.assetManager, assets.grim)
            .then(() => gameConsole.print('Menu assets loaded'))
            .catch((error) => gameConsole.print(`Warning: Failed to load menu assets: ${error}`)),

        // Perk selection screen assets (panel, buttons, cursor, font)
        assets.perkSelectionScreen
            .loadAssets(assets.assetManager, assets.grim)
            .then(() => gameConsole.print('Perk selection assets loaded'))
            .catch((error) => gameConsole.print(`Warning: Failed to load perk selection assets: ${error}`)),

        // Quest complete screen assets
        assets.questCompleteScreen
            .loadAssets(assets.assetManager, assets.grim)
            .then(() => gameConsole.print('Quest complete screen assets loaded'))
            .catch((error) => gameConsole.print(`Warning: Failed to load quest complete screen assets: ${error}`)),

        // Game over screen assets
        assets.gameOverScreen
            .loadAssets(assets.assetManager, assets.grim)
            .then(() => gameConsole.print('Game over screen assets loaded'))
            .catch((error) => gameConsole.print(`Warning: Failed to load game over screen assets: ${error}`)),

        // Quest failed screen assets
        assets.questFailedScreen
            .loadAssets(assets.assetManager, assets.grim)
            .then(() => gameConsole.print('Quest failed screen assets loaded'))
            .catch((error) => gameConsole.print(`Warning: Failed to load quest failed screen assets: ${error}`)),

        // AlienZooKeeper gem texture (alien sprite sheet)
        assets.alienZooKeeperScreen
            .loadAssets(assets.assetManager, assets.grim)
            .then(() => gameConsole.print('AlienZooKeeper assets loaded'))
            .catch((error) => gameConsole.print(`Warning: Failed to load AlienZooKeeper assets: ${error}`)),

        // Terrain renderer (textures from crimson.paq)
        (async () => {
            try {
                const renderer = assets.grim.getRenderer() as PIXI.Renderer;
                if (renderer) {
                    // Create TerrainRenderer if not already provided
                    if (!assets.terrainRenderer) {
                        assets.terrainRenderer = new TerrainRenderer(renderer, 1024, 1024);
                    }
                    await assets.terrainRenderer.load(assets.assetManager);
                    const terrainTexture = assets.terrainRenderer.generate(terrainSeed);
                    if (terrainTexture) {
                        terrainTextureHandle = assets.grim.registerTexture('game_terrain', terrainTexture);
                        gameConsole.print('Terrain renderer initialized');
                    }
                }
            } catch (error) {
                gameConsole.print(`Warning: Failed to initialize terrain renderer: ${error}`);
            }
        })(),

        // Sprite renderer (textures from crimson.paq)
        assets.spriteRenderer
            .loadAssets(assets.assetManager, assets.grim)
            .then(() => gameConsole.print('Sprite renderer initialized'))
            .catch((error) => gameConsole.print(`Warning: Failed to initialize sprite renderer: ${error}`)),

        // Gameplay cursor (cursor sprite from crimson.paq)
        assets.gameplayCursor
            .loadAssets(assets.assetManager, assets.grim)
            .then(() => gameConsole.print('Gameplay cursor loaded'))
            .catch((error) => gameConsole.print(`Warning: Failed to load gameplay cursor: ${error}`)),

        // HUD textures (top bar, heart, health bar, weapon icons, ammo indicators, clock)
        assets.hud
            .loadAssets(assets.assetManager, assets.grim)
            .then(() => gameConsole.print('HUD assets loaded'))
            .catch((error) => gameConsole.print(`Warning: Failed to load HUD assets: ${error}`)),

        // Font generation (no PAQ dependency)
        loadFont(),

        // Sound samples from sfx.paq (parallel decoding within)
        assets.soundSystem
            .loadSamplesFromAssetManager(assets.assetManager)
            .then(() => gameConsole.print('Sound system initialized')),

        // Music tracks (fetch from /content/music/ + parallel decoding)
        // C code: audio_init_music loads 4 named tracks (intro, shortie_monk, crimson_theme, crimsonquest)
        // plus game_tunes.txt playlist tracks (gt1_ingame, gt2_harppen) for random in-game music.
        assets.musicSystem
            .loadTracksFromGameTunes()
            .then(() => Promise.all([
                assets.musicSystem.loadSpecificTrack('crimson_theme.ogg'),   // C: music_track_crimson_theme_id (menu, victory)
                assets.musicSystem.loadSpecificTrack('shortie_monk.ogg'),    // C: music_track_shortie_monk_id (death/game-over)
                assets.musicSystem.loadSpecificTrack('crimsonquest.ogg'),    // C: music_track_crimsonquest_id (quest start)
                assets.musicSystem.loadSpecificTrack('intro.ogg'),           // C: music_track_intro_id (intro sequence)
            ]))
            .then(() =>
                gameConsole.print(`Music system initialized with ${assets.musicSystem.getTrackCount()} tracks`),
            ),
    ]);

    return { terrainTextureHandle, terrainRenderer: assets.terrainRenderer };
}

export function wireGameSystems(assets: GameAssets, pauseMenu: PauseMenu): void {
    // Wire sound/music systems to UI (must happen after loading completes)
    assets.mainMenu.setSoundSystem(assets.soundSystem);
    assets.mainMenu.setMusicSystem(assets.musicSystem);
    assets.perkSelectionScreen.setSoundSystem(assets.soundSystem);
    assets.questCompleteScreen.setSoundSystem(assets.soundSystem);
    assets.gameOverScreen.setSoundSystem(assets.soundSystem);
    assets.questFailedScreen.setSoundSystem(assets.soundSystem);

    // Share MainMenu assets with StatisticsScreen (avoids duplicate loading)
    if (assets.mainMenu.isLoaded()) {
        const shared = assets.mainMenu.getSharedAssets();
        assets.statisticsScreen.setSharedAssets(shared.panelElement, shared.buttonHandle, shared.menuCursor);
        assets.leaderboardScreen.setSharedAssets(shared.panelElement, shared.buttonHandle, shared.menuCursor);
        assets.creditsScreen.setSharedAssets(shared.panelElement, shared.buttonHandle, shared.menuCursor);
        assets.alienZooKeeperScreen.setSharedAssets(shared.buttonHandle, shared.menuCursor);
    }

    // Share the game's terrain texture with MainMenu (avoids duplicate TerrainRenderer)
    if (assets.terrainRenderer) {
        const terrainHandle = assets.grim.getTextureHandle('game_terrain');
        if (terrainHandle >= 0) {
            assets.mainMenu.setTerrainTexture(terrainHandle, assets.terrainRenderer);
        }
    }

    // Share MainMenu assets with PauseMenu (avoids duplicate loading)
    if (assets.mainMenu.isLoaded()) {
        const shared = assets.mainMenu.getSharedAssets();
        pauseMenu.setSharedAssets(
            shared.itemTextsHandle,
            shared.buttonHandle,
            shared.panelElement,
            shared.titleElement,
            shared.menuCursor,
            shared.bitmapFont,
            shared.rectOnTexture,
            shared.rectOffTexture,
            shared.controlsButtonHandle,
        );
    }
    pauseMenu.setSoundSystem(assets.soundSystem);
    pauseMenu.setMusicSystem(assets.musicSystem);
    assets.creditsScreen.setSoundSystem(assets.soundSystem);
    assets.alienZooKeeperScreen.setSoundSystem(assets.soundSystem);
}
