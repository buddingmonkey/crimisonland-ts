import { type Player } from '../../entities/Player';
import { type ScoreSystem } from '../ScoreSystem';
import { type EnemySpawner } from '../enemy/EnemySpawner';
import { type MusicSystem } from '../../audio/MusicSystem';
import { type MainMenu } from '../../ui/screens/MainMenu';
import { QuestCompleteScreen, QuestCompleteAction, type QuestCompleteInput } from '../../ui/screens/QuestCompleteScreen';
import { type SaveSystem } from '../SaveSystem';
import { type LeaderboardScreen } from '../../ui/screens/LeaderboardScreen';
import { type HighScoreSystem, GameMode as HSGameMode } from '../HighScoreSystem';
import { questSystem } from './QuestSystem';
import { getWeaponStats } from '../../data/WeaponData';
import { GameState, GameMode } from '../../Game';
import { gameConsole } from '../../console/Console';
import type { GrimInterface } from '../../engine/GrimInterface';
import { KeyCode } from '../../engine/KeyCodes';
import { PERK_ANTIPERK } from '../../data/quests/QuestTypes';
import { getPerkUnlockRegistry } from '../PerkUnlockRegistry';
import { getWeaponUnlockRegistry } from '../WeaponUnlockRegistry';
import { PERK_META, PerkId } from '../PerkSystem';
import { WEAPON_DATA } from '../../data/WeaponData';

export interface QuestFlowContext {
    player: Player | null;
    scoreSystem: ScoreSystem;
    perkPendingCount: number;
    questCompleteScreen: QuestCompleteScreen;
    enemySpawner: EnemySpawner;
    musicSystem: MusicSystem;
    mainMenu: MainMenu;
    grim: GrimInterface;
    saveSystem: SaveSystem;
    highScoreSystem: HighScoreSystem;
    leaderboardScreen: LeaderboardScreen;
    startGame(): void;
    regenerateTerrain(tier: number): void;
}

export interface QuestFlowResult {
    newState?: GameState;
    newGameMode?: GameMode;
    perkPendingCount: number;
}

export function handleQuestCompletion(ctx: QuestFlowContext): void {
    const { player, scoreSystem, questCompleteScreen, saveSystem, highScoreSystem } = ctx;
    const quest = questSystem.getCurrentQuest();
    if (!quest) return;

    gameConsole.print(`Quest Complete: ${quest.name}!`);

    // Award weapon unlock (C: quest_results_screen_update lines 664-676)
    let unlockWeaponName: string | null = null;
    if (quest.unlockWeaponId > 0) {
        const weaponRegistry = getWeaponUnlockRegistry();
        weaponRegistry.unlockWeapon(quest.unlockWeaponId);
        // Persist to save system
        saveSystem.setUnlockedWeaponIds(weaponRegistry.getUnlockedWeaponIds());
        const weaponMeta = WEAPON_DATA[quest.unlockWeaponId];
        unlockWeaponName = weaponMeta?.name ?? `Weapon ${quest.unlockWeaponId}`;
        gameConsole.print(`Unlocked weapon: ${unlockWeaponName} (ID: ${quest.unlockWeaponId})`);
    }

    // Unlock perk via PerkUnlockRegistry (C: quest_results_screen_update lines 678-688)
    let unlockPerkName: string | null = null;
    if (quest.unlockPerkId !== PERK_ANTIPERK && quest.unlockPerkId !== PerkId.ANTIPERK) {
        const registry = getPerkUnlockRegistry();
        registry.unlockPerk(quest.unlockPerkId);
        // Persist to save system
        saveSystem.setUnlockedPerkIds(registry.getUnlockedPerkIds());
        const meta = PERK_META[quest.unlockPerkId as PerkId];
        unlockPerkName = meta?.name ?? `Perk 0x${quest.unlockPerkId.toString(16)}`;
        gameConsole.print(`Unlocked perk: ${unlockPerkName} (ID: 0x${quest.unlockPerkId.toString(16)})`);
    }

    // Update quest unlock progress
    const questId = quest.id;
    if (questId >= questSystem.getUnlockIndex()) {
        questSystem.setUnlockIndex(questId + 1);
        saveSystem.setQuestUnlockIndex(questId + 1);
        gameConsole.print(`Quest progress: ${questId + 1}/40 quests unlocked`);
    }

    // Increment quest play count (C: lines 37993-37994)
    saveSystem.incrementQuestPlayCount(quest.tier - 1, quest.index - 1);

    // Reset reflex boost timer on quest completion (C: bonus_reflex_boost_timer = 0)
    if (player) {
        player.reflexBoostTimer = 0;
    }

    // Calculate results data (C: quest_results_final_score formula, quest.c lines 335-370)
    // C: final_score = quest_spawn_timeline - life_bonus - (unpicked_perks * 1000)
    // Lower final time = better score (completed quest faster, with more health)
    const baseTimeMs = questSystem.getTimelineMs();
    // Life Bonus = health * 100 (10% of original C scaling)
    // Remaining health converts to a time bonus: full health (100) subtracts 10s,
    // making the final time lower (better). Low health = small bonus = worse score.
    const lifeBonusMs = player ? Math.max(0, Math.floor(player.health) * 100) : 0;
    const unpickedPerks = ctx.perkPendingCount;
    const finalTimeMs = Math.max(1, baseTimeMs - lifeBonusMs - unpickedPerks * 1000);

    // Save high score record (C: quest.c lines 347-354, 497-623)
    // C: highscore_active_record.score_xp = 0, survival_elapsed_ms = quest_results_final_score
    highScoreSystem.startSession('Player', HSGameMode.Quest);
    highScoreSystem.updateSession({
        scoreXp: 0,
        survivalElapsedMs: finalTimeMs,
        creatureKillCount: scoreSystem.getKills(),
    });
    const rank = highScoreSystem.endSession();
    // C: highscore_rank_result < 100 → show name entry (phase 1)
    const isHighScore = rank >= 0 && rank < 100;

    // Show quest complete screen with rich stats
    const weaponId = player ? player.weaponId : 0;
    const weaponStats = getWeaponStats(weaponId);
    const scoreSeconds = finalTimeMs / 1000;
    const frags = scoreSystem.getKills();

    questCompleteScreen.show({
        baseTimeMs,
        lifeBonusMs,
        unpickedPerks,
        finalTimeMs,
        questName: quest.name,
        isHighScore,
        rank: isHighScore ? rank + 1 : undefined,
        scoreSeconds,
        frags,
        hitPercent: scoreSystem.getHitPercent(),
        experience: 0, // C: quest.c line 64 — highscore_active_record.score_xp = 0
        weaponName: weaponStats.name,
        weaponId,
        questTier: quest.tier,
        questIndex: quest.index,
    });

    // Reset quest system (but keep game world visible in background)
    questSystem.reset();
}

export function updateQuestCompleteScreen(ctx: QuestFlowContext): QuestFlowResult {
    const { questCompleteScreen, enemySpawner, musicSystem, mainMenu, grim } = ctx;
    let perkPendingCount = ctx.perkPendingCount;
    let newState: GameState | undefined;
    let newGameMode: GameMode | undefined;

    const dtMs = grim.getDeltaTime();

    const chars = grim.getKeyChars();
    const charInput = chars.map((c) => String.fromCharCode(c)).join('');

    const input: QuestCompleteInput = {
        mouseX: grim.getMouseX(),
        mouseY: grim.getMouseY(),
        mouseClicked: grim.isMouseButtonPressed(0),
        confirmPressed: grim.isKeyPressed(KeyCode.Enter) || grim.isKeyPressed(KeyCode.Space),
        cancelPressed: grim.isKeyPressed(KeyCode.Escape),
        charInput,
        backspacePressed: grim.isKeyPressed(KeyCode.Backspace),
    };

    const action = questCompleteScreen.update(dtMs, input);

    switch (action) {
        case QuestCompleteAction.PlayNext: {
            // Read data BEFORE hide() — hide() nullifies this.data
            const qData = questCompleteScreen.getData();
            questCompleteScreen.hide();
            if (qData && qData.questTier && qData.questIndex) {
                let nextTier = qData.questTier;
                let nextIndex = qData.questIndex + 1;
                if (nextIndex > 10) {
                    nextTier++;
                    nextIndex = 1;
                }
                if (nextTier <= 5) {
                    questSystem.setSpawnCallback((entry) => {
                        for (let i = 0; i < entry.count; i++) {
                            const enemy = enemySpawner.spawnQuestEnemy(entry.posX, entry.posY, entry.templateId);
                            if (enemy) {
                                questSystem.reportEnemySpawned(1);
                            }
                        }
                    });
                    questSystem.startQuest(nextTier, nextIndex);
                    newGameMode = GameMode.Quest;
                    ctx.regenerateTerrain(nextTier);
                    ctx.startGame();
                    gameConsole.print(`Starting quest ${nextTier}-${nextIndex}`);
                } else {
                    newState = GameState.Menu;
                    musicSystem.play('crimson_theme.ogg');
                    gameConsole.print('All quests complete!');
                }
            } else {
                newState = GameState.Menu;
                musicSystem.play('crimson_theme.ogg');
            }
            break;
        }

        case QuestCompleteAction.Replay: {
            // Read data BEFORE hide() — hide() nullifies this.data
            const replayData = questCompleteScreen.getData();
            questCompleteScreen.hide();
            gameConsole.print('Replaying quest...');
            newGameMode = GameMode.Quest;
            // Re-initialize the quest so the starting weapon is applied correctly.
            // handleQuestCompletion() calls questSystem.reset(), so currentQuest is null here.
            // Without re-calling startQuest(), GameStarter skips weapon assignment (C line 2035).
            if (replayData?.questTier && replayData?.questIndex) {
                questSystem.setSpawnCallback((entry) => {
                    for (let i = 0; i < entry.count; i++) {
                        const enemy = enemySpawner.spawnQuestEnemy(entry.posX, entry.posY, entry.templateId);
                        if (enemy) {
                            questSystem.reportEnemySpawned(1);
                        }
                    }
                });
                questSystem.startQuest(replayData.questTier, replayData.questIndex);
                ctx.regenerateTerrain(replayData.questTier);
            }
            ctx.startGame();
            break;
        }

        case QuestCompleteAction.MainMenu:
            questCompleteScreen.hide();
            newGameMode = GameMode.Survival;
            newState = GameState.Menu;
            mainMenu.showPlayMenu();
            mainMenu.hidePlayMenu();
            musicSystem.play('crimson_theme.ogg');
            break;

        case QuestCompleteAction.HighScores:
            ctx.leaderboardScreen.show();
            newState = GameState.Statistics;
            break;

        case QuestCompleteAction.ShowEndNote:
            // C: game_state_pending = 0x15 → credits/end-note screen after final quest (5-10)
            questCompleteScreen.hide();
            gameConsole.print('All quests complete! Showing end note / credits.');
            newState = GameState.Credits;
            break;
    }

    return { newState, newGameMode, perkPendingCount };
}
