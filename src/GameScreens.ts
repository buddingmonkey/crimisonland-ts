/**
 * GameScreens - Bundled UI screen instances extracted from Game.ts.
 *
 * Groups the ~11 UI screen singletons that Game.ts previously declared
 * as individual private fields. Game.ts now owns a single `screens` field.
 */

import { HUD } from './ui/HUD';
import { GameOverScreen } from './ui/screens/GameOverScreen';
import { PerkSelectionScreen } from './ui/screens/PerkSelectionScreen';
import { QuestCompleteScreen } from './ui/screens/QuestCompleteScreen';
import { QuestFailedScreen } from './ui/screens/QuestFailedScreen';
import { MainMenu } from './ui/screens/MainMenu';
import { PauseMenu } from './ui/menus/PauseMenu';
import { StatisticsScreen } from './ui/screens/StatisticsScreen';
import { LeaderboardScreen } from './ui/screens/LeaderboardScreen';
import { CreditsScreen } from './ui/screens/CreditsScreen';
import { AlienZooKeeperScreen } from './ui/screens/AlienZooKeeperScreen';

export class GameScreens {
    readonly hud = new HUD();
    readonly mainMenu = new MainMenu();
    readonly pauseMenu = new PauseMenu();
    readonly gameOverScreen = new GameOverScreen();
    readonly questFailedScreen = new QuestFailedScreen();
    readonly perkSelectionScreen = new PerkSelectionScreen();
    readonly questCompleteScreen = new QuestCompleteScreen();
    readonly statisticsScreen = new StatisticsScreen();
    readonly leaderboardScreen = new LeaderboardScreen();
    readonly creditsScreen = new CreditsScreen();
    readonly alienZooKeeperScreen = new AlienZooKeeperScreen();
}
