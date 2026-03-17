import { type PauseMenu, PauseMenuAction } from './PauseMenu';
import { type MainMenu } from '../screens/MainMenu';
import { type MusicSystem } from '../../audio/MusicSystem';
import { GameState, type GameMode } from '../../Game';
import { type MenuInput } from '../screens/MainMenu';
import { KeyCode } from '../../engine/KeyCodes';
import type { GrimInterface } from '../../engine/GrimInterface';

export interface PauseInputContext {
    grim: GrimInterface;
    pauseMenu: PauseMenu;
    mainMenu: MainMenu;
    musicSystem: MusicSystem;
}

export interface PauseInputResult {
    newState?: GameState;
    newGameMode?: GameMode;
}

/**
 * Handles input for the Paused game state: delegates to PauseMenu and
 * processes resume/quit/options actions.
 * C reference: pause_menu_update
 */
export function handlePauseStateInput(ctx: PauseInputContext): PauseInputResult {
    const { grim, pauseMenu, mainMenu, musicSystem } = ctx;

    const pauseInput: MenuInput = {
        mouseX: grim.getMouseX(),
        mouseY: grim.getMouseY(),
        mouseDown: grim.isMouseButtonDown(0),
        mouseClicked: grim.isMouseButtonPressed(0),
        screenHeight: grim.getHeight(),
        escPressed: grim.isKeyPressed(KeyCode.Escape),
    };

    const pauseAction = pauseMenu.update(grim.getDeltaTime(), pauseInput);

    if (pauseAction === PauseMenuAction.Resume) {
        return { newState: GameState.Playing };
    }

    if (pauseAction === PauseMenuAction.QuitToMenu) {
        mainMenu.resetSubMenus();
        musicSystem.play('crimson_theme.ogg');
        return { newState: GameState.Menu };
    }

    // Options handled internally by PauseMenu
    return {};
}
