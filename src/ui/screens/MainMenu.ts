/**
 * MainMenu - Main menu screen UI
 *
 * Renders the game's main menu with actual PAQ assets:
 * - Plasma background animation
 * - Logo/title (top-right)
 * - Menu items with staggered left alignment
 * - Pre-rendered text labels from sprite sheet
 */

import type { GrimInterface, TextureHandle } from '../../engine/GrimInterface';
import type { AssetManager } from '../../data/AssetManager';
import { UIElement } from '../UIElement';
import { TerrainRenderer } from '../../rendering/TerrainRenderer';
import { MenuCursor } from '../../rendering/MenuCursor';
import { OptionItem, OptionType } from '../menus/OptionItem';
import { BitmapFont } from '../../engine/BitmapFont';

import type { SoundSystem } from '../../audio/SoundSystem';
import type { MusicSystem } from '../../audio/MusicSystem';
import { SoundId } from '../../audio/SoundId';

import {
    renderPlayMenuItems as _renderPlayMenuItems,
    renderQuestScreen as _renderQuestScreen,
    renderOptionsItems as _renderOptionsItems,
    type MenuRenderContext,
} from '../menus/MainMenuRenderer';
import {
    updateOptionsMode as _updateOptionsMode,
    updatePlayMenuMode as _updatePlayMenuMode,
    updateQuestMode as _updateQuestMode,
    type MenuUpdateContext,
} from '../menus/MainMenuUpdater';

/**
 * Menu item definition
 */
interface MenuItem {
    label: string;
    action: MenuAction;
    x: number; // Staggered X position
    y: number;
    labelIndex: number; // Index in itemTexts sprite sheet
    buttonElement: UIElement; // Individual button element for animations
}

/**
 * Actions that menu can return
 */
export enum MenuAction {
    None = 0,
    StartGame = 1,
    Options = 2,
    Statistics = 3,
    Quit = 4,
    PlayTutorial = 5,
    PlayQuests = 6,
    PlayRush = 7,
    PlaySurvival = 8,
    StartQuest = 9,
    Credits = 10,
}

/**
 * Input state for menu navigation
 */
export interface MenuInput {
    mouseX: number;
    mouseY: number;
    mouseDown: boolean;
    mouseClicked: boolean;
    screenHeight: number; // Logical screen height for layout (variable resolution)
    upPressed?: boolean;
    downPressed?: boolean;
    enterPressed?: boolean;
    escPressed?: boolean;
}

/**
 * Main menu screen
 */
export class MainMenu {
    // Texture handles (using Grim's texture system)
    // Terrain is shared from the game's TerrainRenderer (set via setTerrainTexture)
    private terrainRenderer: TerrainRenderer | null = null;
    private terrainHandle: TextureHandle = -1;
    private itemTextsHandle: TextureHandle = -1;
    private menuCursor: MenuCursor = new MenuCursor();
    private controlsButtonHandle: TextureHandle = -1; // 82x32 button for Controls
    private mediumButtonHandle: TextureHandle = -1; // 128x32 button for Play menu
    private buttonHandle: TextureHandle = -1; // Shared menu button texture

    // UI Elements (using C code's ui_element_t pattern)
    // C code: ui_element_set_rect(element, width, height, {offsetX, offsetY})
    private titleElement = new UIElement(573.44, 143.36, -577.44, -62.0);
    private menuPanelElement = new UIElement(512.0, 256.0, 20.0, -82.0);

    // Menu state - staggered left alignment
    // Each button shifts ~20px right from previous
    // Menu items with calculated positions from C code constants
    // Position = BASE + OFFSET + (index * STEP) for stagger effect
    // labelIndex corresponds to row in ui_itemTexts.jaz sprite sheet
    private menuItems: MenuItem[];
    private hoveredIndex: number = -1;
    private selectedIndex: number = 0; // For keyboard navigation
    private assetsLoaded: boolean = false;

    // Options mode state (C code: same ui_element_table, different elements visible)
    private isOptionsMode: boolean = false;
    private optionsItems: OptionItem[] = [];
    private optionsHoveredIndex: number = -1;
    private optionsSelectedIndex: number = 0;

    // Play menu mode state
    private isPlayMode: boolean = false;
    private playMenuHoveredIndex: number = -1;
    private playMenuSelectedIndex: number = 0;
    private playMaxTimeline: number = 0;
    private playerCount: number = 1;
    private dropdownOpen: boolean = false;

    // Quest screen mode state
    private isQuestMode: boolean = false;
    private questSelectedTier: number = 1;
    private questHoveredIndex: number = -1;
    private questMaxTimeline: number = 0;
    private questTextHandle: TextureHandle = -1; // ui_textQuest.jaz
    private questNumHandles: TextureHandle[] = [-1, -1, -1, -1, -1]; // ui_num1-5.jaz
    private selectedQuestTier: number = 1; // For returning to Game.ts
    private selectedQuestIndex: number = 1; // For returning to Game.ts
    // Separate larger panel for quest screen (512×400, same texture as QuestCompleteScreen)
    private questPanelElement = new UIElement(512.0, 400.0, 0.0, -200.0);

    // Play menu button data (C code: ui_button_t pattern)
    private playMenuButtons: {
        label: string;
        action: MenuAction;
        hoverAnim: number; // 0-1000 (C: hover_anim)
        clickAnim: number; // 0-1000 (C: click_anim)
        description: string;
    }[] = [
            {
                label: 'Tutorial',
                action: MenuAction.PlayTutorial,
                hoverAnim: 0,
                clickAnim: 0,
                description: 'Learn the basics of Crimsonland',
            },
            {
                label: 'Quests',
                action: MenuAction.PlayQuests,
                hoverAnim: 0,
                clickAnim: 0,
                description: 'Unlock new weapons and perks in Quest mode',
            },
            {
                label: 'Rush',
                action: MenuAction.PlayRush,
                hoverAnim: 0,
                clickAnim: 0,
                description: 'Rush mode. Fast enemies!',
            },
            {
                label: 'Survival',
                action: MenuAction.PlaySurvival,
                hoverAnim: 0,
                clickAnim: 0,
                description: 'Survive for as long as you can',
            },
        ];

    // Animation timeline (from C code ui_elements_timeline @ line 14759-14787)
    private globalTimeline: number = 0; // Global timeline counter (ms)
    private transitionDirection: number = 1; // 1 = intro (forward), 0 = exit (backward)
    private maxTimeline: number = 0; // Maximum timeline value for main menu
    private optionsMaxTimeline: number = 0; // Maximum timeline value for options menu

    // Per-button animation constants (from C code)
    private readonly ANIMATION_DURATION = 500; // Duration per button (ms)
    private readonly STAGGER_DELAY = 100; // Delay between buttons (ms)

    // Options panel layout constant (shared between rendering and hit detection)
    private readonly OPTIONS_CONTENT_PADDING_X = 220; // Position of content area inside panel frame

    // Exit animation state (from C code ui_transition_direction)
    private isExiting: boolean = false;
    private exitAction: MenuAction = MenuAction.None;

    // Audio systems
    private soundSystem: SoundSystem | null = null;
    private musicSystem: MusicSystem | null = null;

    // Bitmap font for rendering text
    private bitmapFont: BitmapFont = new BitmapFont();

    constructor() {
        // Position calculation from Python port:
        // pos_x = MENU_LABEL_BASE_X - (slot * 20)  // Gets MORE NEGATIVE (left) per slot
        // pos_y = MENU_LABEL_BASE_Y + (slot * MENU_LABEL_STEP)
        // This creates positions: X=[-60, -80, -100, -120], allowing stalks to extend off-screen LEFT

        const baseY = this.MENU_LABEL_BASE_Y; // 210
        const xStagger = 20.0; // Each slot moves 20px more left

        this.menuItems = [
            {
                label: 'PLAY GAME',
                action: MenuAction.StartGame,
                x: this.MENU_LABEL_BASE_X - 0 * xStagger,
                y: baseY + 0 * this.MENU_LABEL_STEP,
                labelIndex: 1,
                buttonElement: new UIElement(512.0, 64.0, -72.0, -60.0),
            },
            {
                label: 'OPTIONS',
                action: MenuAction.Options,
                x: this.MENU_LABEL_BASE_X - 1 * xStagger,
                y: baseY + 1 * this.MENU_LABEL_STEP,
                labelIndex: 2,
                buttonElement: new UIElement(512.0, 64.0, -72.0, -60.0),
            },
            {
                label: 'STATISTICS',
                action: MenuAction.Statistics,
                x: this.MENU_LABEL_BASE_X - 2 * xStagger,
                y: baseY + 2 * this.MENU_LABEL_STEP,
                labelIndex: 3,
                buttonElement: new UIElement(512.0, 64.0, -72.0, -60.0),
            },
            {
                label: 'OTHER GAMES',
                action: MenuAction.Credits,
                x: this.MENU_LABEL_BASE_X - 3 * xStagger,
                y: baseY + 3 * this.MENU_LABEL_STEP,
                labelIndex: 5,
                buttonElement: new UIElement(512.0, 64.0, -72.0, -60.0),
            },
            {
                label: 'QUIT',
                action: MenuAction.Quit,
                x: this.MENU_LABEL_BASE_X - 4 * xStagger,
                y: baseY + 4 * this.MENU_LABEL_STEP,
                labelIndex: 6,
                buttonElement: new UIElement(512.0, 64.0, -72.0, -60.0),
            },
        ];

        // Initialize per-element timing (from C code _pad0[0x12] and _pad0[0xe])
        // Each button has startTime and endTime for staggered animation
        this.menuItems.forEach((item, index) => {
            item.buttonElement.startTime = index * this.STAGGER_DELAY;
            item.buttonElement.endTime = item.buttonElement.startTime + this.ANIMATION_DURATION;
        });

        // Calculate max timeline (from C code ui_elements_max_timeline @ line 37820)
        this.maxTimeline = Math.max(...this.menuItems.map((item) => item.buttonElement.endTime));

        // Initialize options menu items
        // Animation structure: Panel (item 0) folds out, content inside folds with it, BACK button (item 1) follows
        // Note: Initial values will be updated from audio systems in showOptions()
        this.optionsItems = [
            new OptionItem(OptionType.Slider, 'Sound volume', 8, 80), // Matches original lowercase
            new OptionItem(OptionType.Slider, 'Music volume', 9, 60), // Matches original lowercase
            new OptionItem(OptionType.Slider, 'Graphics detail', 10, 100), // Matches original lowercase
            new OptionItem(OptionType.Slider, 'Mouse sensitivity', 11, 50), // Matches original lowercase
            new OptionItem(OptionType.Toggle, 'UI Info texts', 12, 1), // Matches original
            new OptionItem(OptionType.Button, 'Back', 14, 0), // BACK button
        ];

        // Position options items (no individual stagger - they fold with the panel)
        this.optionsItems.forEach((item, index) => {
            item.x = this.MENU_LABEL_BASE_X - index * xStagger;
            item.y = baseY + index * this.MENU_LABEL_STEP;
            // Sliders/toggles don't animate individually - they appear with the panel
            item.buttonElement.startTime = 0;
            item.buttonElement.endTime = 0;
        });

        // Override BACK button X position and timing
        const backButton = this.optionsItems[this.optionsItems.length - 1];
        backButton.x = this.MENU_LABEL_BASE_X; // Same as PLAY GAME (index 0)
        // BACK button is item 1 in the animation sequence (after panel)
        backButton.buttonElement.startTime = this.STAGGER_DELAY; // 100ms
        backButton.buttonElement.endTime = backButton.buttonElement.startTime + this.ANIMATION_DURATION; // 600ms

        // Panel is item 0 in the animation sequence
        this.menuPanelElement.startTime = 0;
        this.menuPanelElement.endTime = this.ANIMATION_DURATION; // 500ms

        // Calculate max timeline for options menu (panel and BACK button)
        this.optionsMaxTimeline = Math.max(this.menuPanelElement.endTime, backButton.buttonElement.endTime); // Should be 600ms

        // Play menu uses same panel + BACK button timing as options
        this.playMaxTimeline = this.optionsMaxTimeline;

        // Quest screen uses same panel + BACK button timing
        this.questMaxTimeline = this.optionsMaxTimeline;

        // Quest panel timing (separate larger panel)
        this.questPanelElement.startTime = 0;
        this.questPanelElement.endTime = this.ANIMATION_DURATION;
    }

    /**
     * Set sound system reference (C line 4399)
     */
    setSoundSystem(soundSystem: SoundSystem): void {
        this.soundSystem = soundSystem;
    }

    /**
     * Set music system reference
     */
    setMusicSystem(musicSystem: MusicSystem): void {
        this.musicSystem = musicSystem;
    }

    // === EXACT CONSTANTS FROM ORIGINAL C CODE @ 1024x768 ===
    // Based on ui_menu_layout_init and verified port constants
    // Note: Button/title dimensions are now in UIElement instances

    // Label dimensions from sprite sheet (ui_itemTexts.jaz)
    // C code: ui_element_set_rect(..., 124.0, 30.0, ...)
    // Port constants: MENU_LABEL_WIDTH = 122.0, HEIGHT = 28.0
    private readonly MENU_LABEL_WIDTH = 122; // Renamed from labelWidth
    private readonly MENU_LABEL_HEIGHT = 28; // Renamed from labelHeight

    // Menu layout positioning constants (1024x768)
    private readonly MENU_LABEL_BASE_X = -60.0;
    private readonly MENU_LABEL_BASE_Y = 210.0;
    private readonly MENU_LABEL_STEP = 60.0; // Stagger between items

    // Label offset from button pivot (from Python reference)
    private readonly MENU_LABEL_OFFSET_X = 271.0;
    private readonly MENU_LABEL_OFFSET_Y = -37.0;

    private readonly MENU_SIGN_POS_Y = 70.0;
    private readonly MENU_SIGN_POS_X_PAD = 4.0; // Right edge padding

    /**
     * Set shared terrain texture from the game's TerrainRenderer.
     * Called by wireGameSystems() after both MainMenu and TerrainRenderer are loaded.
     */
    setTerrainTexture(handle: TextureHandle, terrainRenderer: TerrainRenderer): void {
        this.terrainHandle = handle;
        this.terrainRenderer = terrainRenderer;
    }

    /**
     * Load menu textures from AssetManager and register with GrimInterface
     */
    async loadAssets(assetManager: AssetManager, grim: GrimInterface): Promise<void> {

        // Title sign - using UIElement pattern
        await this.titleElement.load('menu_title', 'ui/ui_signcrimson.jaz', assetManager, grim);

        // Menu panel - using UIElement pattern
        await this.menuPanelElement.load('menu_panel', 'ui/ui_menupanel.jaz', assetManager, grim);

        // Menu item buttons - load texture for each button element
        const buttonTexture = await assetManager.getTexture('ui/ui_menuitem.jaz');
        if (buttonTexture) {
            this.buttonHandle = grim.registerTexture('menu_menuitem', buttonTexture);
            // Assign the same texture to all main menu button elements
            for (const item of this.menuItems) {
                (item.buttonElement as any).textureHandle = this.buttonHandle;
            }
        }

        // Item labels sprite sheet (pre-rendered text: PLAY GAME, OPTIONS, STATISTICS, QUIT)
        const itemTextsTexture = await assetManager.getTexture('ui/ui_itemTexts.jaz');
        if (itemTextsTexture) {
            this.itemTextsHandle = grim.registerTexture('menu_itemTexts', itemTextsTexture);
        }

        // Menu cursor with glow (C: ui_cursor_render)
        await this.menuCursor.loadAssets(assetManager, grim);

        // Load slider textures for options menu (static, shared across all sliders)
        if (!MainMenu.sliderTexturesLoaded) {
            const rectOnTex = await assetManager.getTexture('ui/ui_rectOn.jaz');
            if (rectOnTex) {
                MainMenu.rectOnTexture = grim.registerTexture('slider_rectOn', rectOnTex);
            }

            const rectOffTex = await assetManager.getTexture('ui/ui_rectOff.jaz');
            if (rectOffTex) {
                MainMenu.rectOffTexture = grim.registerTexture('slider_rectOff', rectOffTex);
            }

            MainMenu.sliderTexturesLoaded = true;
        }

        // Load assets for options items (button elements)
        if (this.buttonHandle >= 0) {
            for (const item of this.optionsItems) {
                (item.buttonElement as any).textureHandle = this.buttonHandle;
            }
        }
        if (itemTextsTexture) {
            const labelHandle = grim.registerTexture('options_itemtexts', itemTextsTexture);
            for (const item of this.optionsItems) {
                (item as any).labelTexture = labelHandle;
            }
        }

        // Load Controls button texture (82x32 small button)
        const controlsButtonTex = await assetManager.getTexture('ui/ui_button_82x32.jaz');
        if (controlsButtonTex) {
            this.controlsButtonHandle = grim.registerTexture('controls_button', controlsButtonTex);
        }

        // Load medium button texture (128x32) for Play menu buttons
        // C code: ui_buttonMd = ui_button_128x32.jaz
        const mediumButtonTex = await assetManager.getTexture('ui/ui_button_128x32.jaz');
        if (mediumButtonTex) {
            this.mediumButtonHandle = grim.registerTexture('medium_button', mediumButtonTex);
        }

        // Load quest screen textures (C code: gameplay.c lines 1780-1789)
        const questTextTex = await assetManager.getTexture('ui/ui_textQuest.jaz');
        if (questTextTex) {
            this.questTextHandle = grim.registerTexture('quest_text', questTextTex);
        }
        const numNames = ['ui/ui_num1.jaz', 'ui/ui_num2.jaz', 'ui/ui_num3.jaz', 'ui/ui_num4.jaz', 'ui/ui_num5.jaz'];
        for (let i = 0; i < 5; i++) {
            const numTex = await assetManager.getTexture(numNames[i]);
            if (numTex) {
                this.questNumHandles[i] = grim.registerTexture(`quest_num${i + 1}`, numTex);
            }
        }

        // Load quest panel (larger panel, same texture as other menus)
        await this.questPanelElement.load('quest_panel', 'ui/ui_menupanel.jaz', assetManager, grim);

        // Load bitmap font for text rendering (C: line 23394)
        await this.bitmapFont.loadAssets(assetManager, grim);

        this.assetsLoaded = true;
        this._ensureContextFields(); // satisfy noUnusedLocals — fields read via MenuUpdateContext cast
    }

    /**
     * Check if assets are loaded
     */
    isLoaded(): boolean {
        return this.assetsLoaded;
    }

    /**
     * Get the MenuCursor instance for shared rendering.
     * Used by Game.ts to render the menu cursor in overlay states
     * (QuestComplete, QuestFailed, GameOver, PerkSelection).
     * C code: ui_cursor_render() is called at the end of each overlay state's update function.
     */
    getMenuCursor(): MenuCursor {
        return this.menuCursor;
    }

    /**
     * Get shared asset handles for PauseMenu (avoids duplicate texture loading)
     */
    getSharedAssets(): {
        itemTextsHandle: TextureHandle;
        buttonHandle: TextureHandle;
        panelElement: UIElement;
        titleElement: UIElement;
        menuCursor: MenuCursor;
        bitmapFont: BitmapFont;
        rectOnTexture: TextureHandle;
        rectOffTexture: TextureHandle;
        controlsButtonHandle: TextureHandle;
    } {
        return {
            itemTextsHandle: this.itemTextsHandle,
            buttonHandle: this.buttonHandle,
            panelElement: this.menuPanelElement,
            titleElement: this.titleElement,
            menuCursor: this.menuCursor,
            bitmapFont: this.bitmapFont,
            rectOnTexture: MainMenu.rectOnTexture,
            rectOffTexture: MainMenu.rectOffTexture,
            controlsButtonHandle: this.controlsButtonHandle,
        };
    }

    /**
     * Show options menu (swap menu items with options items)
     */
    showOptions(): void {
        this.isOptionsMode = true;
        this.globalTimeline = 0; // Reset timeline to trigger intro animation
        this.optionsSelectedIndex = 0;
        this.optionsHoveredIndex = -1;

        // Initialize slider values from audio systems
        if (this.soundSystem) {
            this.optionsItems[0].value = Math.round(this.soundSystem.getMasterVolume() * 100);
        }
        if (this.musicSystem) {
            this.optionsItems[1].value = Math.round(this.musicSystem.getVolume() * 100);
        }
    }

    /**
     * Hide options menu (return to main menu items)
     */
    hideOptions(): void {
        this.isOptionsMode = false;
        this.globalTimeline = 0; // Reset timeline to trigger intro animation
        this.selectedIndex = 0;
        this.hoveredIndex = -1;
    }

    /**
     * Check if currently in options mode
     */
    isInOptionsMode(): boolean {
        return this.isOptionsMode;
    }

    /**
     * Show play menu (panel with game mode buttons)
     */
    showPlayMenu(): void {
        this.isPlayMode = true;
        this.globalTimeline = 0; // Reset timeline to trigger intro animation
        this.playMenuSelectedIndex = 0;
        this.playMenuHoveredIndex = -1;
        this.dropdownOpen = false;

        // Reset button animations
        for (const btn of this.playMenuButtons) {
            btn.hoverAnim = 0;
            btn.clickAnim = 0;
        }
    }

    /**
     * Hide play menu (return to main menu items)
     */
    hidePlayMenu(): void {
        this.isPlayMode = false;
        this.globalTimeline = 0; // Reset timeline to trigger intro animation
        this.selectedIndex = 0;
        this.hoveredIndex = -1;
    }

    /**
     * Reset all sub-menu flags to return to the top-level main menu.
     * Used by PauseInputHandler when quitting to menu to avoid the
     * show/hide hack that could flash a single frame of a sub-menu.
     */
    resetSubMenus(): void {
        this.isPlayMode = false;
        this.isOptionsMode = false;
        this.isQuestMode = false;
        this.globalTimeline = 0;
        this.selectedIndex = 0;
        this.hoveredIndex = -1;
    }

    /**
     * Check if currently in play menu mode
     */
    isInPlayMode(): boolean {
        return this.isPlayMode;
    }

    /**
     * Show quest screen (panel with tier buttons and quest list)
     */
    showQuestScreen(): void {
        this.isQuestMode = true;
        this.isPlayMode = false;
        this.globalTimeline = 0;
        this.questSelectedTier = 1;
        this.questHoveredIndex = -1;
    }

    /**
     * Hide quest screen (return to play menu)
     */
    hideQuestScreen(): void {
        this.isQuestMode = false;
        this.globalTimeline = 0;
        this.playMenuSelectedIndex = 0;
        this.playMenuHoveredIndex = -1;
    }

    /**
     * Check if currently in quest screen mode
     */
    isInQuestMode(): boolean {
        return this.isQuestMode;
    }

    /**
     * Get the selected quest (tier + index) for Game.ts to start
     */
    getSelectedQuest(): { tier: number; index: number } {
        return { tier: this.selectedQuestTier, index: this.selectedQuestIndex };
    }

    /**
     * Update menu state (from C code ui_elements_update_and_render @ line 14759-14787)
     */
    update(dt: number, input: MenuInput): MenuAction {
        // Update menu cursor animation (C: ui_cursor_render timers)
        this.menuCursor.update(dt);

        // Update button elements FIRST with current timeline (before increment)
        // This ensures labels and buttons animate in perfect sync
        let action = MenuAction.None;
        if (this.isQuestMode) {
            action = this.updateQuestMode(dt, input);
        } else if (this.isPlayMode) {
            action = this.updatePlayMenuMode(dt, input);
        } else if (this.isOptionsMode) {
            action = this.updateOptionsMode(dt, input);
        } else {
            action = this.updateMainMenuMode(dt, input);
        }

        // THEN increment/decrement timeline for next frame
        if (!this.isExiting) {
            // Intro animation - advance timeline forward (from C code @ line 14766-14769)
            const delta = dt * (this.transitionDirection ? 1 : -1); // Using existing transitionDirection logic
            this.globalTimeline += delta;
        } else {
            // Exit animation - run timeline backward
            this.globalTimeline -= dt;
        }

        // Clamp timeline to [0, maxTimeline] (from C code @ line 14766-14787)
        if (this.globalTimeline < 0) {
            this.globalTimeline = 0;
            if (this.isExiting) {
                // Exit animation complete
                const exitAction = this.exitAction;
                this.isExiting = false;

                // If we're in options mode and exiting, switch back to main menu
                if (this.isOptionsMode && exitAction === MenuAction.None) {
                    this.hideOptions();
                }

                // If we're in play mode and exiting with no action, switch back to main menu
                if (this.isPlayMode && exitAction === MenuAction.None) {
                    this.hidePlayMenu();
                }

                // If we're in quest mode and exiting with no action, switch back to play menu
                if (this.isQuestMode && exitAction === MenuAction.None) {
                    this.hideQuestScreen();
                    this.showPlayMenu();
                }

                this.exitAction = MenuAction.None;
                return exitAction;
            }
        }
        // Clamp to appropriate max timeline based on current mode
        let currentMaxTimeline = this.maxTimeline;
        if (this.isOptionsMode) currentMaxTimeline = this.optionsMaxTimeline;
        if (this.isPlayMode) currentMaxTimeline = this.playMaxTimeline;
        if (this.isQuestMode) currentMaxTimeline = this.questMaxTimeline;
        if (this.globalTimeline > currentMaxTimeline) {
            this.globalTimeline = currentMaxTimeline;
        }

        return action;
    }

    /**
     * Update main menu mode
     */
    private updateMainMenuMode(dt: number, input: MenuInput): MenuAction {
        this.hoveredIndex = -1;
        for (let i = 0; i < this.menuItems.length; i++) {
            const item = this.menuItems[i];

            // Hit test against the rotated UIElement bounds
            const bounds = item.buttonElement.getRotatedBounds(item.x, item.y);
            const isHovered =
                input.mouseX >= bounds.left &&
                input.mouseX <= bounds.right &&
                input.mouseY >= bounds.top &&
                input.mouseY <= bounds.bottom;

            if (isHovered) {
                this.hoveredIndex = i;

                if (input.mouseClicked && !this.isExiting) {
                    // Play button click sound (C line 4399)
                    if (this.soundSystem) {
                        this.soundSystem.play(SoundId.UI_BUTTON_CLICK);
                    }

                    // All selections trigger exit animation for fold-out effect
                    this.isExiting = true;
                    this.exitAction = item.action;
                    // Don't return yet - let exit animation play
                }
            }

            // Update button animation with global timeline (from C code ui_element_update)
            // The element's update() method will calculate rotation based on its startTime/endTime
            // Highlight if hovered by mouse OR selected by keyboard
            const isHighlighted = isHovered || i === this.selectedIndex;
            item.buttonElement.update(dt, isHighlighted, this.globalTimeline);
        }

        return MenuAction.None;
    }

    /**
     * Update options mode.
     * Logic extracted to MainMenuUpdater.ts.
     */
    private updateOptionsMode(dt: number, input: MenuInput): MenuAction {
        return _updateOptionsMode(this as unknown as MenuUpdateContext, dt, input);
    }

    /**
     * Update play menu mode.
     * Logic extracted to MainMenuUpdater.ts.
     */
    private updatePlayMenuMode(dt: number, input: MenuInput): MenuAction {
        return _updatePlayMenuMode(this as unknown as MenuUpdateContext, dt, input);
    }

    /**
     * Update quest screen mode.
     * Logic extracted to MainMenuUpdater.ts.
     */
    private updateQuestMode(dt: number, input: MenuInput): MenuAction {
        return _updateQuestMode(this as unknown as MenuUpdateContext, dt, input);
    }

    /**
     * Void-reads all private fields that are accessed via MenuUpdateContext / MenuRenderContext
     * casts in delegated methods. TypeScript's noUnusedLocals cannot trace through
     * `this as unknown as XContext`, so this method makes the fields appear 'read'.
     * Called once from loadAssets; not called at runtime in any other path.
     */
    private _ensureContextFields(): void {
        void this.mediumButtonHandle;
        void this.optionsHoveredIndex;
        void this.optionsSelectedIndex;
        void this.playMenuHoveredIndex;
        void this.playMenuSelectedIndex;
        void this.playerCount;
        void this.dropdownOpen;
        void this.questSelectedTier;
        void this.questHoveredIndex;
        void this.questTextHandle;
        void this.OPTIONS_CONTENT_PADDING_X;
    }

    /**
     * Render the menu
     */
    render(grim: GrimInterface): void {
        const width = grim.getWidth();
        const height = grim.getHeight();

        // Draw terrain background or fallback
        if (this.terrainHandle >= 0 && this.terrainRenderer) {
            grim.bindTexture(this.terrainHandle);
            grim.setColor(255, 255, 255, 255);
            // The terrain texture includes a buffer zone around the playable area.
            // Show only the center (playable) portion so terrain scale matches gameplay.
            const texW = this.terrainRenderer.getWidth();
            const texH = this.terrainRenderer.getHeight();
            const pw = this.terrainRenderer.getPlayableWidth();
            const ph = this.terrainRenderer.getPlayableHeight();
            const u0 = (texW - pw) / 2 / texW;
            const v0 = (texH - ph) / 2 / texH;
            const u1 = 1 - u0;
            const v1 = 1 - v0;
            grim.setUV(u0, v0, u1, v1);
            grim.drawQuad(0, 0, width, height);
        } else {
            // Fallback: brown earth color matching terrain base
            grim.setColor(63, 56, 26, 255);
            grim.drawRectFilled(0, 0, width, height);
        }

        // Draw title using UIElement - positioned from RIGHT edge per Python reference
        // Python: pos_x = screen_width + MENU_SIGN_POS_X_PAD (4), offset_x = -576.44
        if (this.titleElement.isLoaded()) {
            grim.setColor(255, 255, 255, 255);
            const titlePosX = width + this.MENU_SIGN_POS_X_PAD; // Right edge + 4
            this.titleElement.draw(grim, titlePosX, this.MENU_SIGN_POS_Y);
        } else {
            // Fallback title
            const titlePosX = width + this.MENU_SIGN_POS_X_PAD;
            const titleX = titlePosX + this.titleElement.offsetX;
            const titleY = this.MENU_SIGN_POS_Y + this.titleElement.offsetY;
            grim.setColor(150, 30, 30, 255);
            grim.drawRectFilled(titleX, titleY, this.titleElement.width, this.titleElement.height);
            grim.setColor(255, 200, 200, 255);
            grim.drawText(titleX + 100, titleY + 30, 'CRIMSONLAND', 24);
        }

        // Render menu items based on current mode (C code: same background, different elements visible)
        if (this.isQuestMode) {
            this.renderQuestScreen(grim);
        } else if (this.isPlayMode) {
            this.renderPlayMenuItems(grim);
        } else if (this.isOptionsMode) {
            this.renderOptionsItems(grim);
        } else {
            this.renderMainMenuItems(grim);
        }

        // Draw cursor with glow (C: ui_cursor_render — always visible in menus)
        this.menuCursor.render(grim);

        // Version info
        this.renderVersionInfo(grim);
    }

    /**
     * Render a button with label using Container-based rotation
     * Reusable helper for both main menu and options menu buttons
     */
    renderButtonWithLabel(
        grim: GrimInterface,
        x: number,
        y: number,
        rotation: number,
        buttonElement: UIElement,
        labelIndex: number,
        isHovered: boolean,
    ): void {
        // Create container for this button
        const buttonContainer = grim.createContainer();
        grim.setContainerTransform(buttonContainer, x, y, rotation);
        grim.setActiveContainer(buttonContainer);

        // Draw button background
        if (buttonElement.isLoaded()) {
            grim.setColor(255, 255, 255, 255);
            buttonElement.draw(grim, 0, 0);
        }

        // Draw label sprite
        if (this.itemTextsHandle >= 0) {
            grim.bindTexture(this.itemTextsHandle);
            if (isHovered) {
                grim.setColor(255, 220, 180, 255); // Warm highlighted color
            } else {
                grim.setColor(180, 180, 200, 255); // Cool neutral color
            }

            const vStart = labelIndex / 8.0;
            const vEnd = (labelIndex + 1) / 8.0;
            grim.setUV(0, vStart, 1, vEnd);
            grim.drawQuad(
                this.MENU_LABEL_OFFSET_X,
                this.MENU_LABEL_OFFSET_Y,
                this.MENU_LABEL_WIDTH,
                this.MENU_LABEL_HEIGHT,
            );
        }

        grim.setActiveContainer(null);
    }

    /**
     * Render main menu items
     */
    private renderMainMenuItems(grim: GrimInterface): void {
        // Draw menu items with staggered left alignment
        for (let i = 0; i < this.menuItems.length; i++) {
            const item = this.menuItems[i];
            const isHovered = i === this.hoveredIndex;
            const rotationAngle = item.buttonElement.getRotation();

            this.renderButtonWithLabel(
                grim,
                item.x,
                item.y,
                rotationAngle,
                item.buttonElement,
                item.labelIndex,
                isHovered,
            );
        }
    }

    /**
     * Render play menu items - panel with game mode buttons, dropdown, descriptions.
     * Rendering logic extracted to MainMenuRenderer.ts.
     */
    private renderPlayMenuItems(grim: GrimInterface): void {
        _renderPlayMenuItems(this as unknown as MenuRenderContext, grim);
    }

    /**
     * Render quest selection screen.
     * Rendering logic extracted to MainMenuRenderer.ts.
     */
    private renderQuestScreen(grim: GrimInterface): void {
        _renderQuestScreen(this as unknown as MenuRenderContext, grim);
    }

    /**
     * Render options menu.
     * Rendering logic extracted to MainMenuRenderer.ts.
     */
    private renderOptionsItems(grim: GrimInterface): void {
        _renderOptionsItems(this as unknown as MenuRenderContext, grim);
    }

    // Static slider texture handles
    private static rectOnTexture: number = -1;
    private static rectOffTexture: number = -1;
    private static sliderTexturesLoaded: boolean = false;

    /**
     * Render a slider control using sprite-based bars
     * Matches C code FUN_0043d9b0 (lines 35094-35130)
     */
    renderSliderControl(grim: GrimInterface, x: number, y: number, value: number): void {
        if (MainMenu.rectOnTexture === -1 || MainMenu.rectOffTexture === -1) {
            // Fallback to text if textures not loaded
            const barLength = Math.floor(value / 10);
            const bar = '█'.repeat(barLength) + '░'.repeat(10 - barLength);
            grim.setColor(100, 150, 200, 255);
            grim.drawText(x, y, bar, 12);
            return;
        }

        // Slider configuration
        const SEGMENT_WIDTH = 8;
        const SEGMENT_HEIGHT = 16;
        const NUM_SEGMENTS = 10;

        // Calculate filled segments based on value (0-100)
        const filledSegments = Math.floor((value / 100) * NUM_SEGMENTS);

        // Pass 1: Draw all segments with rectOff at 50% opacity
        grim.bindTexture(MainMenu.rectOffTexture);
        grim.setColor(255, 255, 255, 128);
        grim.setUV(0, 0, 1, 1);

        for (let i = 0; i < NUM_SEGMENTS; i++) {
            const segmentX = x + i * SEGMENT_WIDTH;
            grim.drawQuad(segmentX, y, SEGMENT_WIDTH, SEGMENT_HEIGHT);
        }

        // Pass 2: Draw filled segments with rectOn at 100% opacity
        if (filledSegments > 0) {
            grim.bindTexture(MainMenu.rectOnTexture);
            grim.setColor(255, 255, 255, 255);
            grim.setUV(0, 0, 1, 1);

            for (let i = 0; i < filledSegments; i++) {
                const segmentX = x + i * SEGMENT_WIDTH;
                grim.drawQuad(segmentX, y, SEGMENT_WIDTH, SEGMENT_HEIGHT);
            }
        }

        // Reset color
        grim.setColor(255, 255, 255, 255);
    }

    /**
     * Render version info
     * (Menu cursor rendering is now handled by MenuCursor class)
     */
    private renderVersionInfo(grim: GrimInterface): void {
        const height = grim.getHeight();
        grim.setColor(100, 100, 100, 255);
        grim.drawText(10, height - 20, 'TypeScript Port v0.1', 12);
    }
}
