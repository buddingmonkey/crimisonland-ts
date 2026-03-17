import { Player } from './entities/Player';
import { type WeaponSystem } from './systems/combat/WeaponSystem';
import { type CollisionSystem } from './systems/combat/CollisionSystem';
import { type EnemySpawner } from './systems/enemy/EnemySpawner';
import { type BonusSystem } from './systems/bonus/BonusSystem';
import { type PerkSystem } from './systems/PerkSystem';
import { type ScoreSystem } from './systems/ScoreSystem';
import { type BloodEffectSystem } from './systems/effects/BloodEffectSystem';
import { type EnemyDeathEffects } from './systems/enemy/EnemyDeathEffects';
import { type SoundSystem } from './audio';
import { type MusicSystem } from './audio/MusicSystem';
import { type ParticleSystem } from './systems/effects/ParticleSystem';
import { type EffectSystem } from './systems/effects/EffectSystem';
import { type SpriteRenderer } from './rendering/SpriteRenderer';
import { type TerrainRenderer } from './rendering/TerrainRenderer';
import { GameMode } from './Game';
import { questSystem } from './systems/quest/QuestSystem';
import { resetPlaguebearerInfectionCount } from './systems/enemy/EnemySystemsUpdate';
import { gameConsole } from './console/Console';
import type { GrimInterface } from './engine/GrimInterface';

export interface GameStarterContext {
    terrainRenderer: TerrainRenderer | null;
    spriteRenderer: SpriteRenderer;
    grim: GrimInterface;
    gameMode: GameMode;
    weaponSystem: WeaponSystem;
    collisionSystem: CollisionSystem;
    enemySpawner: EnemySpawner;
    bonusSystem: BonusSystem;
    perkSystem: PerkSystem;
    scoreSystem: ScoreSystem;
    bloodEffectSystem: BloodEffectSystem;
    enemyDeathEffects: EnemyDeathEffects;
    musicSystem: MusicSystem;
    soundSystem: SoundSystem;
    particleSystem: ParticleSystem;
    effectSystem: EffectSystem;
}

export interface GameStarterResult {
    player: Player;
    cameraOffsetX: number;
    cameraOffsetY: number;
    lastLevel: number;
    perkPendingCount: number;
    survivalSpawnStage: number;
    survivalRewardDamageSeen: boolean;
    survivalRewardFireSeen: boolean;
    survivalRewardHandoutEnabled: boolean;
    survivalRecentDeaths: Array<{ x: number; y: number }>;
}

/**
 * Creates a fresh player and wires all systems for a new game session.
 * C references: game_start, player_spawn, camera_update @ 00409500
 */
export function startNewGame(ctx: GameStarterContext): GameStarterResult {
    const {
        terrainRenderer,
        spriteRenderer,
        grim,
        gameMode,
        weaponSystem,
        collisionSystem,
        enemySpawner,
        bonusSystem,
        perkSystem,
        scoreSystem,
        bloodEffectSystem,
        enemyDeathEffects,
        musicSystem,
        soundSystem,
        particleSystem,
        effectSystem,
    } = ctx;

    const terrainW = terrainRenderer?.getPlayableWidth() ?? 1024;
    const terrainH = terrainRenderer?.getPlayableHeight() ?? 1024;

    // Create player at center of terrain (C: pos = terrain_size * 0.5)
    const player = new Player(terrainW * 0.5, terrainH * 0.5);
    player.setTerrainDimensions(terrainW, terrainH);
    player.setBloodEffectSystem(bloodEffectSystem);

    // Set starting weapon based on game mode
    if (gameMode === GameMode.Quest) {
        const quest = questSystem.getCurrentQuest();
        if (quest) {
            player.switchWeapon(quest.startWeaponId, perkSystem);
            gameConsole.print(`Quest: ${quest.name}`);
            gameConsole.print(`Starting weapon: ${player.getWeaponStats().name}`);
        }
    }

    // Wire all systems
    weaponSystem.clear();
    weaponSystem.setParticleSystem(particleSystem);
    weaponSystem.setEffectSystem(effectSystem);
    weaponSystem.setSoundSystem(soundSystem);
    weaponSystem.setScoreSystem(scoreSystem);
    collisionSystem.setSoundSystem(soundSystem);
    collisionSystem.setEnemyDeathEffects(enemyDeathEffects);
    collisionSystem.setBloodEffectSystem(bloodEffectSystem);
    collisionSystem.setEffectSystem(effectSystem);
    collisionSystem.setScoreSystem(scoreSystem);
    enemySpawner.clear();
    bonusSystem.clear();
    perkSystem.clear();
    scoreSystem.reset();
    resetPlaguebearerInfectionCount();

    // Wire quest system audio (C: sfx_questhit + music_crimsonquest during transition)
    questSystem.setSoundSystem(soundSystem);
    questSystem.setMusicSystem(musicSystem);

    // Reset survival/rush mode state (C: survival.c globals)
    enemySpawner.survivalSpawnCooldown = 0;

    // Wire blood effect system
    bloodEffectSystem.clear();
    bloodEffectSystem.setParticlesTexture(spriteRenderer.getParticlesHandle());
    const particlesPixi = spriteRenderer.getParticlesPixiTexture();
    if (particlesPixi) bloodEffectSystem.setParticlesPixiTexture(particlesPixi);
    const bodysetPixi = spriteRenderer.getBodysetPixiTexture();
    if (bodysetPixi) bloodEffectSystem.setBodysetPixiTexture(bodysetPixi);
    if (terrainRenderer) bloodEffectSystem.setTerrainRenderer(terrainRenderer);
    enemyDeathEffects.setBloodSystem(bloodEffectSystem);

    // Wire effect system (C: effect_pool textures + terrain bake)
    effectSystem.clear();
    effectSystem.setParticlesTexture(spriteRenderer.getParticlesHandle());
    // Wire terrain bake: route EffectSystem bake (shell casings, freeze shards)
    // through BloodEffectSystem's existing stamp → terrain pipeline.
    // C code: fx_queue_render bakes both blood AND effect stamps into terrain_render_target.
    effectSystem.setTerrainBakeCallback((effectId, x, y, width, height, rotation, r, g, b, a) => {
        bloodEffectSystem.queueDirectStamp(x, y, width, height, rotation, r, g, b, a, effectId);
    });

    // Initialize camera centered on player (C: camera_update @ 00409500)
    const screenW = grim.getWidth();
    const screenH = grim.getHeight();
    let cameraOffsetX = screenW / 2 - player.x;
    let cameraOffsetY = screenH / 2 - player.y;
    if (cameraOffsetX > -1.0) cameraOffsetX = -1.0;
    if (cameraOffsetY > -1.0) cameraOffsetY = -1.0;
    if (cameraOffsetX < screenW - terrainW) cameraOffsetX = screenW - terrainW;
    if (cameraOffsetY < screenH - terrainH) cameraOffsetY = screenH - terrainH;

    // Switch to gameplay music (random track, C line 34723-34725)
    musicSystem.playRandom();

    gameConsole.print('Player spawned. Use WASD to move, mouse to aim, click to fire.');

    return {
        player,
        cameraOffsetX,
        cameraOffsetY,
        lastLevel: 1,
        perkPendingCount: 0,
        survivalSpawnStage: 0,
        survivalRewardDamageSeen: false,
        survivalRewardFireSeen: false,
        survivalRewardHandoutEnabled: true,
        survivalRecentDeaths: [],
    };
}
