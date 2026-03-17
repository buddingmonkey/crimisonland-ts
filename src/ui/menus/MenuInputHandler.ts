import { type MainMenu, MenuAction, type MenuInput } from '../screens/MainMenu';
import { type StatisticsScreen } from '../screens/StatisticsScreen';
import { type CreditsScreen } from '../screens/CreditsScreen';
import { type EnemySpawner } from '../../systems/enemy/EnemySpawner';
import { type TutorialSystem } from '../../systems/modes/TutorialSystem';
import { type MusicSystem } from '../../audio/MusicSystem';
import { questSystem } from '../../systems/quest/QuestSystem';
import { TerrainRenderer } from '../../rendering/TerrainRenderer';
import { GameState, GameMode } from '../../Game';
import { gameConsole } from '../../console/Console';
import type { GrimInterface } from '../../engine/GrimInterface';
import { KeyCode } from '../../engine/KeyCodes';

export interface MenuInputContext {
    grim: GrimInterface;
    mainMenu: MainMenu;
    statisticsScreen: StatisticsScreen;
    creditsScreen: CreditsScreen;
    enemySpawner: EnemySpawner;
    tutorialSystem: TutorialSystem;
    musicSystem: MusicSystem;
    setGameMode(mode: GameMode): void;
    startGame(): void;
    regenerateTerrain(tier: number): void;
}

export interface MenuInputResult {
    newState?: GameState;
    newGameMode?: GameMode;
}

export function handleMenuStateInput(ctx: MenuInputContext): MenuInputResult {
    const { grim, mainMenu, statisticsScreen, enemySpawner, tutorialSystem } = ctx;
    let newState: GameState | undefined;
    let newGameMode: GameMode | undefined;

    // Debug: Direct menu item access via number keys (1-5)
    if (grim.isKeyPressed(KeyCode.Digit1)) {
        mainMenu.showPlayMenu();
        gameConsole.print('[DEBUG] Play menu opened via key 1');
    } else if (grim.isKeyPressed(KeyCode.Digit2)) {
        gameConsole.print('[DEBUG] Opening Options via key 2');
        mainMenu.showOptions();
        gameConsole.print('Options menu opened');
    } else if (grim.isKeyPressed(KeyCode.Digit3)) {
        newState = GameState.Statistics;
        statisticsScreen.show();
        gameConsole.print('[DEBUG] Statistics opened via key 3');
    } else if (grim.isKeyPressed(KeyCode.Digit4)) {
        window.open('https://en.wikipedia.org/wiki/Crimsonland', '_blank');
        gameConsole.print('Opening Crimsonland Wikipedia page');
    } else if (grim.isKeyPressed(KeyCode.Digit5)) {
        window.close();
    }

    // Update menu with mouse input
    const mouseDown = grim.isMouseButtonDown(0);
    const mouseClicked = grim.isMouseButtonPressed(0);
    const menuInput: MenuInput = {
        mouseX: grim.getMouseX(),
        mouseY: grim.getMouseY(),
        mouseDown: mouseDown,
        mouseClicked: mouseClicked,
        screenHeight: grim.getHeight(),
        escPressed: grim.isKeyPressed(KeyCode.Escape),
    };

    const action = mainMenu.update(grim.getDeltaTime(), menuInput);
    if (action === MenuAction.StartGame) {
        mainMenu.showPlayMenu();
        gameConsole.print('Play menu opened');
    } else if (
        action === MenuAction.PlayTutorial ||
        action === MenuAction.PlayRush ||
        action === MenuAction.PlaySurvival
    ) {
        if (action === MenuAction.PlayTutorial) {
            newGameMode = GameMode.Tutorial;
        } else if (action === MenuAction.PlayRush) {
            newGameMode = GameMode.Rush;
        } else {
            newGameMode = GameMode.Survival;
        }

        // Set game mode BEFORE startGame() so startNewGame() sees the correct mode
        ctx.setGameMode(newGameMode);

        // Regenerate terrain - survival mode uses C code's tiered probability
        let questTier: number;
        if (newGameMode === GameMode.Survival) {
            const unlockIdx = questSystem.getUnlockIndex();
            questTier = TerrainRenderer.selectSurvivalTier(unlockIdx);
        } else {
            questTier = questSystem.isActive() ? questSystem.getCurrentQuest()?.tier || 1 : 1;
        }
        ctx.regenerateTerrain(questTier);

        // Start tutorial if in tutorial mode
        if (newGameMode === GameMode.Tutorial) {
            tutorialSystem.start();
            gameConsole.print('Tutorial started!');
        }

        // Initialize game (creates player, resets systems)
        ctx.startGame();
        gameConsole.print(`Game started! Mode: ${GameMode[newGameMode]}`);
    } else if (action === MenuAction.PlayQuests) {
        mainMenu.showQuestScreen();
        gameConsole.print('Quest selection screen opened');
    } else if (action === MenuAction.StartQuest) {
        const { tier, index } = mainMenu.getSelectedQuest();
        newGameMode = GameMode.Quest;

        // Set game mode BEFORE startGame() so startNewGame() equips the quest's start weapon
        ctx.setGameMode(newGameMode);

        questSystem.setSpawnCallback((entry) => {
            for (let i = 0; i < entry.count; i++) {
                const enemy = enemySpawner.spawnQuestEnemy(entry.posX, entry.posY, entry.templateId);
                if (enemy) {
                    questSystem.reportEnemySpawned(1);
                }
            }
        });
        questSystem.startQuest(tier, index);

        ctx.regenerateTerrain(tier);

        ctx.startGame();
        gameConsole.print(`Quest ${tier}-${index} started!`);
    } else if (action === MenuAction.Options) {
        mainMenu.showOptions();
        gameConsole.print('Options menu opened');
    } else if (action === MenuAction.Statistics) {
        newState = GameState.Statistics;
        statisticsScreen.show();
        gameConsole.print('Statistics opened');
    } else if (action === MenuAction.Credits) {
        newState = GameState.Credits;
        ctx.creditsScreen.show();
        gameConsole.print('Credits screen opened');
    } else if (action === MenuAction.Quit) {
        window.close();
    }

    return { newState, newGameMode };
}
