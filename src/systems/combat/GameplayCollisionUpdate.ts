import { type Player } from '../../entities/Player';
import { type PerkSystem, PerkId } from '../PerkSystem';
import { type WeaponSystem } from './WeaponSystem';
import { type EnemySpawner } from '../enemy/EnemySpawner';
import { type CollisionSystem } from './CollisionSystem';
import { type ScoreSystem } from '../ScoreSystem';
import { type BonusSystem } from '../bonus/BonusSystem';
import { type ParticleSystem } from '../effects/ParticleSystem';
import { type SoundSystem, SoundId } from '../../audio';
import { type MusicSystem } from '../../audio/MusicSystem';
import { type HighScoreSystem, GameMode as HSGameMode } from '../HighScoreSystem';
import { type SaveSystem } from '../SaveSystem';
import { type AchievementSystem } from '../AchievementSystem';
import { type HUD } from '../../ui/HUD';
import { type PerkSelectionScreen } from '../../ui/screens/PerkSelectionScreen';
import { type GameOverScreen } from '../../ui/screens/GameOverScreen';
import { type QuestFailedScreen } from '../../ui/screens/QuestFailedScreen';
import { questSystem } from '../quest/QuestSystem';
import { GameState, GameMode } from '../../Game';
import { getPerkUnlockRegistry } from '../PerkUnlockRegistry';
import { gameConsole } from '../../console/Console';
import { getWeaponStats } from '../../data/WeaponData';

export interface CollisionUpdateContext {
    player: Player;
    perkSystem: PerkSystem;
    weaponSystem: WeaponSystem;
    enemySpawner: EnemySpawner;
    collisionSystem: CollisionSystem;
    scoreSystem: ScoreSystem;
    bonusSystem: BonusSystem;
    particleSystem: ParticleSystem;
    soundSystem: SoundSystem;
    musicSystem: MusicSystem;
    highScoreSystem: HighScoreSystem;
    saveSystem: SaveSystem;
    achievementSystem: AchievementSystem;
    hud: HUD;
    perkSelectionScreen: PerkSelectionScreen;
    gameOverScreen: GameOverScreen;
    questFailedScreen: QuestFailedScreen;
    questFailRetryCount: number;
    gameMode: GameMode;
    perkPendingCount: number;
    perkPromptTimer: number;
    bonusAnimTimer: number;
    survivalRecentDeaths: Array<{ x: number; y: number }>;
    effectSystem: {
        spawnBonusSpawnParticles(x: number, y: number): void;
    };
    shockChainLinksLeft: number;
    handleChainLightning(projectile: any, hitEnemy: any): void;
    applyBonusEffect(bonus: any): void;
}

export interface CollisionUpdateResult {
    perkPendingCount: number;
    perkPromptTimer: number;
    bonusAnimTimer: number;
    newState?: GameState;
    isGameOver: boolean;
}

export function processCollisionsAndKills(
    ctx: CollisionUpdateContext,
    dt: number,
    scaledDt: number,
): CollisionUpdateResult {
    const {
        player,
        perkSystem,
        weaponSystem,
        enemySpawner,
        collisionSystem,
        scoreSystem,
        bonusSystem,
        soundSystem,
        highScoreSystem,
        saveSystem,
        achievementSystem,
        hud,
        perkSelectionScreen,
        gameMode,
    } = ctx;
    let { perkPendingCount, perkPromptTimer, bonusAnimTimer, survivalRecentDeaths } = ctx;
    let newState: GameState | undefined;
    let isGameOver = false;

    // Check collisions
    // Projectiles vs Enemies
    const kills = collisionSystem.checkProjectileHits(
        weaponSystem.getActiveProjectiles(),
        enemySpawner.getActiveEnemies(),
        player,
        perkSystem,
        (projectile, enemy) => ctx.handleChainLightning(projectile, enemy),
        (x, y, angle, type) => {
            weaponSystem.spawnChildProjectile(x, y, angle, type);
        },
    );

    // Fire particle collisions (C: particle_pool update in projectile_update, lines 936-1087)
    // Flamethrower/Blow Torch/HR Flamer spawn particles instead of projectiles.
    // Particles deal intensity*10 damage on contact via creature_find_in_radius.
    const activeEnemies = enemySpawner.getActiveEnemies();
    ctx.particleSystem.checkFireParticleCollisions(
        activeEnemies,
        (enemyIndex: number, damage: number) => {
            const enemy = activeEnemies[enemyIndex];
            if (enemy && enemy.isAlive()) {
                enemy.takeDamage(damage, 4, 0, 0, perkSystem, player); // C: damage_type = 4 (fire)
                if (!enemy.isAlive()) {
                    kills.push(enemy);
                }
            }
        },
    );

    // Track kills (XP is now awarded in CollisionSystem via Fix 2/3)
    for (const enemy of kills) {
        scoreSystem.addKill(enemy.type);

        // Report kill to quest system if in quest mode
        if (gameMode === GameMode.Quest) {
            questSystem.reportEnemyKilled();
        }

        // Track recent deaths for survival reward weapon logic (C: survival_recent_death_pos)
        if (gameMode === GameMode.Survival) {
            survivalRecentDeaths.push({ x: enemy.x, y: enemy.y });
            while (survivalRecentDeaths.length > 3) {
                survivalRecentDeaths.shift();
            }
        }

        // Try to spawn bonus at enemy position (C: bonus_try_spawn_on_kill)
        // C creatures.c:789-791: skip when bonus_spawn_guard is set (chain/fireblast kills)
        if (enemy.noBonusDrop) continue;
        const hasBonusMagnet = perkSystem.hasPerk(PerkId.BONUS_MAGNET);
        const hasFavouriteWeapon = perkSystem.hasPerk(PerkId.MY_FAVOURITE_WEAPON);
        const hasDeathClock = perkSystem.hasPerk(PerkId.DEATH_CLOCK);
        const spawnedBonus = bonusSystem.trySpawnOnKill(
            enemy.x,
            enemy.y,
            player.weaponId,
            player.x,
            player.y,
            hasBonusMagnet,
            hasFavouriteWeapon,
            ctx.shockChainLinksLeft,
            player.freezeTimer,
            player.shieldTimer,
            hasDeathClock,
        );
        // Fix 2: Spawn 16 textured glow particles at bonus spawn position (C: bonus_spawn_at lines 912-932)
        if (spawnedBonus) {
            ctx.effectSystem.spawnBonusSpawnParticles(spawnedBonus.x, spawnedBonus.y);
        }
    }

    // Update bonuses (Bonus Magnet: attract toward player when perk active)
    const hasBonusMagnetForUpdate = perkSystem.hasPerk(PerkId.BONUS_MAGNET);
    bonusSystem.update(scaledDt, hasBonusMagnetForUpdate, player.x, player.y);

    // Update bonus animation timer (C: bonus_animation_timer += frame_dt * 1.3)
    bonusAnimTimer += scaledDt * 1.3;

    // Check bonus pickups (TELEKINETIC = larger pickup radius)
    const hasTelekinetic = perkSystem.hasPerk(PerkId.TELEKINETIC);
    const pickedUpBonuses = bonusSystem.checkPickups(player, hasTelekinetic);
    for (const bonus of pickedUpBonuses) {
        ctx.applyBonusEffect(bonus);
        // Pickup particles now spawned inside applyBonusEffect (BonusEffects.ts)
    }

    // Enemies vs Player
    collisionSystem.checkEnemyPlayerCollisions(player, enemySpawner.getActiveEnemies(), perkSystem);

    // Enemy Projectiles vs Player (C: projectile_update player_find_in_radius check)
    collisionSystem.checkEnemyProjectileHits(weaponSystem.getActiveProjectiles(), player, perkSystem);

    // Update survival time
    scoreSystem.update(dt);

    // Check for level up (C code: gameplay_update_and_render lines 466-478)
    // C: skip level-up in Rush mode (config_blob._24_4_ != 2)
    // Use `while` so large XP bonuses that cross multiple thresholds grant all earned levels
    if (gameMode !== GameMode.Rush) {
        let levelledUp = false;
        while (true) {
            const threshold = 1000 + Math.floor(Math.pow(player.level, 1.8) * 1000);
            if (player.experience <= threshold) break;

            player.level++;
            perkPendingCount++;
            levelledUp = true;
            // Play level up sound (C: sfx_play(sfx_ui_levelup) @ line 5887)
            soundSystem.play(SoundId.UI_LEVEL_UP);
            // Trigger level up banner animation
            hud.notifyLevelUp();
            gameConsole.print(
                `Level ${player.level}! XP: ${player.experience}/${threshold}. Press Mouse2 to pick a perk.`,
            );
        }

        // Tutorial mode: open perk screen immediately (no prompt wait)
        if (levelledUp && gameMode === GameMode.Tutorial) {
            const availablePerks = getPerkUnlockRegistry().getAvailablePerks(player.level);
            perkSelectionScreen.show(perkSystem, availablePerks);
            return {
                perkPendingCount,
                perkPromptTimer,
                bonusAnimTimer,
                newState: GameState.PerkSelection,
                isGameOver: false,
            };
        }
    }

    // Update perk prompt timer (C: perk_prompt_timer, 0-200ms fade)
    const perkDtMs = dt * 1000;
    if (perkPendingCount > 0) {
        perkPromptTimer = Math.min(200, perkPromptTimer + perkDtMs);
    } else {
        perkPromptTimer = Math.max(0, perkPromptTimer - perkDtMs);
    }

    // Check for game over
    if (!player.isAlive()) {
        // Save high score (C: highscore_save_record @ lines 32824-32864)
        const gameModeId =
            gameMode === GameMode.Rush
                ? HSGameMode.Rush
                : gameMode === GameMode.Survival
                    ? HSGameMode.Survival
                    : HSGameMode.Quest;
        highScoreSystem.startSession('Player', gameModeId);
        // C: quest.c line 64 — highscore_active_record.score_xp = 0 for quest mode
        // C: quest mode uses quest timeline time, not survival time
        const isQuestMode = gameMode === GameMode.Quest;
        highScoreSystem.updateSession({
            scoreXp: isQuestMode ? 0 : player.experience,
            survivalElapsedMs: isQuestMode
                ? Math.floor(questSystem.getTimelineMs())
                : Math.floor(scoreSystem.getSurvivalTime() * 1000),
            creatureKillCount: scoreSystem.getKills(),
        });
        const rank = highScoreSystem.endSession();
        if (rank !== -1) {
            gameConsole.print(`High score saved! Rank: ${rank + 1}`);
        }

        // Increment mode play count (C: lines 38001-38016)
        saveSystem.incrementModePlayCount(gameModeId);

        // Check achievements (kills, survival, score)
        achievementSystem.checkKillMilestones(scoreSystem.getKills());
        achievementSystem.checkSurvivalMilestones(Math.floor(scoreSystem.getSurvivalTime() * 1000));
        achievementSystem.checkScoreMilestones(player.experience);

        // Stop all music and play game-over track (C: sfx_mute_all + sfx_play_exclusive)
        ctx.musicSystem.stop();
        ctx.musicSystem.play('shortie_monk.ogg');

        // Route to correct screen based on game mode
        // C formula (gameplay.c:450): game_state_pending = (-(game_mode != 3) & 0xFFFFFFFB) + 0xC;
        // Quest mode (3) → state 12 (QuestFailed), Survival/Rush → state 7 (GameOver)
        isGameOver = true;
        perkPendingCount = 0; // Clear pending perks so level-up banner swings out on death
        const gameTimeMs = Math.floor(scoreSystem.getSurvivalTime() * 1000);
        const weaponId = player.weaponId;
        const weaponName = getWeaponStats(weaponId).name;

        if (gameMode === GameMode.Quest) {
            newState = GameState.QuestFailed;
            ctx.questFailedScreen.show({
                score: Math.floor(questSystem.getTimelineMs()), // C: quest score = timeline time (int), not kill points
                frags: scoreSystem.getKills(),
                hitPercent: scoreSystem.getHitPercent(),
                weaponName,
                weaponId,
                experience: 0, // C: quest.c line 64 — highscore_active_record.score_xp = 0
                retryCount: ctx.questFailRetryCount,
                gameTimeMs,
            });
            gameConsole.print('Quest Failed! Try again.');
        } else {
            newState = GameState.GameOver;
            ctx.gameOverScreen.show({
                score: gameMode === GameMode.Survival || gameMode === GameMode.Rush ? gameTimeMs : player.experience,
                scoreDisplayMode: gameMode === GameMode.Survival || gameMode === GameMode.Rush ? 'time' : 'xp',
                frags: scoreSystem.getKills(),
                hitPercent: scoreSystem.getHitPercent(),
                weaponName,
                weaponId,
                experience: player.experience,
                gameMode: gameModeId,
                rank,
                gameTimeMs,
            });
            gameConsole.print('Game Over!');
        }
    }

    return { perkPendingCount, perkPromptTimer, bonusAnimTimer, newState, isGameOver };
}
