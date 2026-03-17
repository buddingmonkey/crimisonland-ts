/**
 * PauseMenu - In-game pause menu
 *
 * C code reference: game_update_generic_menu @ 00406af0 (gameplay.c:287-303)
 * Rendered when game_state == 5 (paused gameplay state)
 *
 * Renders a semi-transparent overlay over the frozen game world with
 * 3 staggered buttons (OPTIONS, QUIT, BACK) using the same hinge-fold
 * animation as the main menu.
 *
 * Sub-menus: Options (same panel/slider UI from MainMenu)
 */

import type { GrimInterface, TextureHandle } from '../../engine/GrimInterface';
import { UIElement } from '../UIElement';
import { MenuCursor } from '../../rendering/MenuCursor';
import { OptionItem, OptionType } from './OptionItem';
import { BitmapFont } from '../../engine/BitmapFont';
import type { MenuInput } from '../screens/MainMenu';
import type { SoundSystem } from '../../audio/SoundSystem';
import type { MusicSystem } from '../../audio/MusicSystem';
import { SoundId } from '../../audio/SoundId';

/**
 * Actions that the pause menu can return
 */
export enum PauseMenuAction {
    None = 0,
    Resume = 1, // BACK button or ESC — resume gameplay
    Options = 2, // OPTIONS button — show options sub-menu
    QuitToMenu = 3, // QUIT button — return to main menu
}

/**
 * Pause menu item definition
 */
interface PauseMenuItem {
    label: string;
    action: PauseMenuAction;
    x: number;
    y: number;
    labelIndex: number; // Row in ui_itemTexts.jaz sprite sheet
    buttonElement: UIElement; // Individual button element for animations
}

/**
 * Pause menu screen
 *
 * Architecture mirrors MainMenu.ts:
 * - UIElement with container-based rotation for hinge animations
 * - Staggered button positions
 * - Options sub-menu with panel + sliders
 * - MenuCursor for mouse rendering
 */
export class PauseMenu {
    // Shared texture handles (set via setSharedAssets — no duplicate loading)
    private itemTextsHandle: TextureHandle = -1;
    private menuCursor: MenuCursor = new MenuCursor();

    // Title sign element (shared from MainMenu — the Crimsonland logo)
    private titleElement: UIElement | null = null;

    // UI Elements (C code's ui_element_t pattern)
    private menuPanelElement = new UIElement(512.0, 256.0, 20.0, -82.0);

    // Menu items — 3 staggered buttons matching screenshot
    private menuItems: PauseMenuItem[];
    private hoveredIndex: number = -1;

    // Options sub-menu state
    private isOptionsMode: boolean = false;
    private optionsItems: OptionItem[] = [];
    private optionsHoveredIndex: number = -1;
    private optionsMaxTimeline: number = 0;

    // Animation timeline (from C code ui_elements_update_and_render @ line 14759-14787)
    private globalTimeline: number = 0;
    private isExiting: boolean = false;
    private exitAction: PauseMenuAction = PauseMenuAction.None;

    // Per-button animation constants (from C code)
    private readonly ANIMATION_DURATION = 500; // Duration per button (ms)
    private readonly STAGGER_DELAY = 100; // Delay between buttons (ms)

    // Layout constants (same as MainMenu for visual consistency)
    private readonly MENU_LABEL_BASE_X = -60.0;
    private readonly MENU_LABEL_BASE_Y = 210.0;
    private readonly MENU_LABEL_STEP = 60.0;
    private readonly MENU_LABEL_WIDTH = 122;
    private readonly MENU_LABEL_HEIGHT = 28;
    private readonly MENU_LABEL_OFFSET_X = 271.0;
    private readonly MENU_LABEL_OFFSET_Y = -37.0;
    private readonly OPTIONS_CONTENT_PADDING_X = 220;

    // Title sign layout constants (same as MainMenu)
    private readonly MENU_SIGN_POS_Y = 70.0;
    private readonly MENU_SIGN_POS_X_PAD = 4.0;

    // Max timeline for main pause menu
    private maxTimeline: number = 0;

    // Audio systems
    private soundSystem: SoundSystem | null = null;
    private musicSystem: MusicSystem | null = null;

    // Bitmap font for options text rendering
    private bitmapFont: BitmapFont = new BitmapFont();

    // Static slider textures (shared via MainMenu)
    private rectOnTexture: TextureHandle = -1;
    private rectOffTexture: TextureHandle = -1;

    // Controls button for options sub-menu
    private controlsButtonHandle: TextureHandle = -1;

    // Assets loaded flag
    private assetsLoaded: boolean = false;

    constructor() {
        const baseY = this.MENU_LABEL_BASE_Y;
        const xStagger = 20.0;

        // 3 buttons: OPTIONS (slot 0), QUIT (slot 1), BACK (slot 2)
        // Matches the pause menu screenshot from the original game
        this.menuItems = [
            {
                label: 'OPTIONS',
                action: PauseMenuAction.Options,
                x: this.MENU_LABEL_BASE_X - 0 * xStagger,
                y: baseY + 0 * this.MENU_LABEL_STEP,
                labelIndex: 2, // OPTIONS in sprite sheet
                buttonElement: new UIElement(512.0, 64.0, -72.0, -60.0),
            },
            {
                label: 'QUIT',
                action: PauseMenuAction.QuitToMenu,
                x: this.MENU_LABEL_BASE_X - 1 * xStagger,
                y: baseY + 1 * this.MENU_LABEL_STEP,
                labelIndex: 6, // QUIT in sprite sheet
                buttonElement: new UIElement(512.0, 64.0, -72.0, -60.0),
            },
            {
                label: 'BACK',
                action: PauseMenuAction.Resume,
                x: this.MENU_LABEL_BASE_X - 2 * xStagger,
                y: baseY + 2 * this.MENU_LABEL_STEP,
                labelIndex: 7, // BACK in sprite sheet
                buttonElement: new UIElement(512.0, 64.0, -72.0, -60.0),
            },
        ];

        // Initialize per-element timing for staggered animation
        this.menuItems.forEach((item, index) => {
            item.buttonElement.startTime = index * this.STAGGER_DELAY;
            item.buttonElement.endTime = item.buttonElement.startTime + this.ANIMATION_DURATION;
        });

        // Max timeline
        this.maxTimeline = Math.max(...this.menuItems.map((item) => item.buttonElement.endTime));

        // Initialize options sub-menu items (same as MainMenu options)
        this.optionsItems = [
            new OptionItem(OptionType.Slider, 'Sound volume', 8, 80),
            new OptionItem(OptionType.Slider, 'Music volume', 9, 60),
            new OptionItem(OptionType.Slider, 'Graphics detail', 10, 100),
            new OptionItem(OptionType.Slider, 'Mouse sensitivity', 11, 50),
            new OptionItem(OptionType.Toggle, 'UI Info texts', 12, 1),
            new OptionItem(OptionType.Button, 'Back', 14, 0),
        ];

        // Position options items
        this.optionsItems.forEach((item, index) => {
            item.x = this.MENU_LABEL_BASE_X - index * xStagger;
            item.y = baseY + index * this.MENU_LABEL_STEP;
            item.buttonElement.startTime = 0;
            item.buttonElement.endTime = 0;
        });

        // Override BACK button position/timing in options
        const backButton = this.optionsItems[this.optionsItems.length - 1];
        backButton.x = this.MENU_LABEL_BASE_X;
        backButton.buttonElement.startTime = this.STAGGER_DELAY;
        backButton.buttonElement.endTime = backButton.buttonElement.startTime + this.ANIMATION_DURATION;

        // Panel animation timing
        this.menuPanelElement.startTime = 0;
        this.menuPanelElement.endTime = this.ANIMATION_DURATION;

        // Options max timeline
        this.optionsMaxTimeline = Math.max(this.menuPanelElement.endTime, backButton.buttonElement.endTime);
    }

    /**
     * Set sound system reference
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

    /**
     * Set shared asset handles from MainMenu (avoids duplicate texture loading)
     * Called once after MainMenu has loaded its assets.
     */
    setSharedAssets(
        itemTextsHandle: TextureHandle,
        buttonHandle: TextureHandle,
        panelElement: UIElement,
        titleElement: UIElement,
        menuCursor: MenuCursor,
        bitmapFont: BitmapFont,
        rectOnTexture: TextureHandle,
        rectOffTexture: TextureHandle,
        controlsButtonHandle: TextureHandle,
    ): void {
        this.itemTextsHandle = itemTextsHandle;
        this.rectOnTexture = rectOnTexture;
        this.rectOffTexture = rectOffTexture;
        this.controlsButtonHandle = controlsButtonHandle;

        // Share button texture with all menu items
        if (buttonHandle >= 0) {
            for (const item of this.menuItems) {
                (item.buttonElement as any).textureHandle = buttonHandle;
            }
            for (const item of this.optionsItems) {
                (item.buttonElement as any).textureHandle = buttonHandle;
            }
        }

        // Copy panel texture handle from the MainMenu's loaded panel element
        if (panelElement.isLoaded()) {
            (this.menuPanelElement as any).textureHandle = panelElement.getHandle();
        }

        // Share title element (Crimsonland logo)
        this.titleElement = titleElement;

        // Share cursor and font
        this.menuCursor = menuCursor;
        this.bitmapFont = bitmapFont;

        this.assetsLoaded = true;
    }

    /**
     * Check if assets are loaded
     */
    isLoaded(): boolean {
        return this.assetsLoaded;
    }

    /**
     * Show the pause menu (reset animation to play intro)
     */
    show(): void {
        this.globalTimeline = 0;
        this.isExiting = false;
        this.exitAction = PauseMenuAction.None;
        this.hoveredIndex = -1;
        this.isOptionsMode = false;
    }

    /**
     * Show options sub-menu
     */
    showOptions(): void {
        this.isOptionsMode = true;
        this.globalTimeline = 0;
        this.optionsHoveredIndex = -1;

        // Sync slider values from audio systems
        if (this.soundSystem) {
            this.optionsItems[0].value = Math.round(this.soundSystem.getMasterVolume() * 100);
        }
        if (this.musicSystem) {
            this.optionsItems[1].value = Math.round(this.musicSystem.getVolume() * 100);
        }
    }

    /**
     * Hide options sub-menu (return to pause menu items)
     */
    hideOptions(): void {
        this.isOptionsMode = false;
        this.globalTimeline = 0;
        this.hoveredIndex = -1;
    }

    /**
     * Update pause menu state
     * Returns PauseMenuAction when a button is clicked and exit animation completes.
     */
    update(dt: number, input: MenuInput): PauseMenuAction {
        // Update cursor animation
        this.menuCursor.update(dt);

        // Update mode-specific logic
        let action = PauseMenuAction.None;
        if (this.isOptionsMode) {
            action = this.updateOptionsMode(dt, input);
        } else {
            action = this.updateMainMode(dt, input);
        }

        // Advance or decrement timeline
        if (!this.isExiting) {
            this.globalTimeline += dt;
        } else {
            this.globalTimeline -= dt;
        }

        // Clamp timeline
        if (this.globalTimeline < 0) {
            this.globalTimeline = 0;
            if (this.isExiting) {
                const exitAction = this.exitAction;
                this.isExiting = false;

                // If exiting options back to pause menu
                if (this.isOptionsMode && exitAction === PauseMenuAction.None) {
                    this.hideOptions();
                }

                this.exitAction = PauseMenuAction.None;
                return exitAction;
            }
        }

        const currentMax = this.isOptionsMode ? this.optionsMaxTimeline : this.maxTimeline;
        if (this.globalTimeline > currentMax) {
            this.globalTimeline = currentMax;
        }

        return action;
    }

    /**
     * Update main pause menu mode (3 buttons)
     */
    private updateMainMode(dt: number, input: MenuInput): PauseMenuAction {
        // Handle ESC to resume directly
        if (input.escPressed && !this.isExiting) {
            this.isExiting = true;
            this.exitAction = PauseMenuAction.Resume;
        }

        this.hoveredIndex = -1;
        for (let i = 0; i < this.menuItems.length; i++) {
            const item = this.menuItems[i];

            // Hit test against rotated bounds
            const bounds = item.buttonElement.getRotatedBounds(item.x, item.y);
            const isHovered =
                input.mouseX >= bounds.left &&
                input.mouseX <= bounds.right &&
                input.mouseY >= bounds.top &&
                input.mouseY <= bounds.bottom;

            if (isHovered) {
                this.hoveredIndex = i;

                if (input.mouseClicked && !this.isExiting) {
                    // Play click sound
                    if (this.soundSystem) {
                        this.soundSystem.play(SoundId.UI_BUTTON_CLICK);
                    }

                    if (item.action === PauseMenuAction.Options) {
                        // Options: directly switch to options sub-menu (no exit animation needed)
                        this.showOptions();
                        return PauseMenuAction.None;
                    }

                    // Other actions: trigger exit animation
                    this.isExiting = true;
                    this.exitAction = item.action;
                }
            }

            // Update button animation
            const isHighlighted = isHovered;
            item.buttonElement.update(dt, isHighlighted, this.globalTimeline);
        }

        return PauseMenuAction.None;
    }

    /**
     * Update options sub-menu mode
     */
    private updateOptionsMode(dt: number, input: MenuInput): PauseMenuAction {
        // Update panel animation
        this.menuPanelElement.update(dt, false, this.globalTimeline);

        // Handle ESC to return to pause menu
        if (input.escPressed && !this.isExiting) {
            this.isExiting = true;
            this.exitAction = PauseMenuAction.None; // None = back to pause menu
        }

        // Check for slider clicks
        if (input.mouseClicked) {
            for (let i = 0; i < this.optionsItems.length - 1; i++) {
                const item = this.optionsItems[i];
                if (item.type === OptionType.Slider) {
                    if (this.handleSliderClick(i, input.mouseX, input.mouseY)) {
                        if (this.soundSystem) {
                            this.soundSystem.play(SoundId.UI_BUTTON_CLICK);
                        }
                        break;
                    }
                }
            }
        }

        // Update hover and button animations
        this.optionsHoveredIndex = -1;
        for (let i = 0; i < this.optionsItems.length; i++) {
            const item = this.optionsItems[i];

            const bounds = item.buttonElement.getRotatedBounds(item.x, item.y);
            const isHovered =
                input.mouseX >= bounds.left &&
                input.mouseX <= bounds.right &&
                input.mouseY >= bounds.top &&
                input.mouseY <= bounds.bottom;

            if (isHovered) {
                this.optionsHoveredIndex = i;

                if (input.mouseClicked) {
                    if (this.soundSystem) {
                        this.soundSystem.play(SoundId.UI_BUTTON_CLICK);
                    }

                    // Handle Back button
                    if (item.type === OptionType.Button && item.label === 'Back') {
                        this.isExiting = true;
                        this.exitAction = PauseMenuAction.None;
                    }

                    // Handle toggle
                    if (item.type === OptionType.Toggle) {
                        item.adjustValue(1);
                    }
                }
            }

            const isHighlighted = isHovered;
            item.buttonElement.update(dt, isHighlighted, this.globalTimeline);
        }

        return PauseMenuAction.None;
    }

    /**
     * Handle slider click interaction (matches MainMenu.handleSliderClick)
     */
    private handleSliderClick(itemIndex: number, mouseX: number, mouseY: number): boolean {
        const { contentX, contentY } = this.getOptionsContentArea();
        const optionStartY = contentY + 35;
        const optionSpacing = 28;
        const sliderX = contentX + 150;
        const y = optionStartY + itemIndex * optionSpacing;

        const SEGMENT_WIDTH = 8;
        const SEGMENT_HEIGHT = 16;
        const NUM_SEGMENTS = 10;

        if (
            mouseX >= sliderX &&
            mouseX < sliderX + NUM_SEGMENTS * SEGMENT_WIDTH &&
            mouseY >= y &&
            mouseY < y + SEGMENT_HEIGHT
        ) {
            const segmentIndex = Math.floor((mouseX - sliderX) / SEGMENT_WIDTH);
            const clampedSegment = Math.max(0, Math.min(NUM_SEGMENTS - 1, segmentIndex));
            const newValue = ((clampedSegment + 1) / NUM_SEGMENTS) * 100;
            this.optionsItems[itemIndex].value = Math.round(newValue);

            // Update audio volumes
            if (itemIndex === 0 && this.soundSystem) {
                this.soundSystem.setMasterVolume(newValue / 100);
            }
            if (itemIndex === 1 && this.musicSystem) {
                this.musicSystem.setVolume(newValue / 100);
            }

            return true;
        }
        return false;
    }

    /**
     * Get options content area coordinates
     */
    private getOptionsContentArea(): { contentX: number; contentY: number } {
        const panelPivotX = -90;
        const panelPivotY = 200;
        const contentX = panelPivotX + this.menuPanelElement.offsetX + this.OPTIONS_CONTENT_PADDING_X;
        const contentY = panelPivotY + this.menuPanelElement.offsetY + 20;
        return { contentX, contentY };
    }

    /**
     * Render the pause menu
     * C code: game_update_generic_menu — renders over frozen game world
     */
    render(grim: GrimInterface): void {
        // NOTE: Semi-transparent overlay is drawn by Game.ts BEFORE this call
        // to ensure correct z-order (game → overlay → menu UI)

        // Draw title sign (Crimsonland logo) — matches MainMenu.render()
        // C code: ui_elements_update_and_render draws both title and buttons
        if (this.titleElement && this.titleElement.isLoaded()) {
            const width = grim.getWidth();
            grim.setColor(255, 255, 255, 255);
            const titlePosX = width + this.MENU_SIGN_POS_X_PAD;
            this.titleElement.draw(grim, titlePosX, this.MENU_SIGN_POS_Y);
        }

        // Render menu items based on current mode
        if (this.isOptionsMode) {
            this.renderOptionsItems(grim);
        } else {
            this.renderMainMenuItems(grim);
        }

        // Draw cursor with glow (C: ui_cursor_render — always visible in menus)
        this.menuCursor.render(grim);
    }

    /**
     * Render main pause menu items (OPTIONS, QUIT, BACK)
     */
    private renderMainMenuItems(grim: GrimInterface): void {
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
     * Render a button with label using Container-based rotation
     * Mirrors MainMenu.renderButtonWithLabel exactly
     */
    private renderButtonWithLabel(
        grim: GrimInterface,
        x: number,
        y: number,
        rotation: number,
        buttonElement: UIElement,
        labelIndex: number,
        isHovered: boolean,
    ): void {
        const buttonContainer = grim.createContainer();
        grim.setContainerTransform(buttonContainer, x, y, rotation);
        grim.setActiveContainer(buttonContainer);

        // Draw button background
        if (buttonElement.isLoaded()) {
            grim.setColor(255, 255, 255, 255);
            buttonElement.draw(grim, 0, 0);
        }

        // Draw label sprite from sprite sheet
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
     * Render options sub-menu (panel with sliders, toggles, BACK button)
     * Mirrors MainMenu.renderOptionsItems
     */
    private renderOptionsItems(grim: GrimInterface): void {
        const panelPivotX = -90;
        const panelPivotY = 200;
        const panelRotation = this.menuPanelElement.getRotation();

        // Create container for panel + content
        const panelContainer = grim.createContainer();
        grim.setContainerTransform(panelContainer, panelPivotX, panelPivotY, panelRotation);
        grim.setActiveContainer(panelContainer);

        // Draw panel background
        if (this.menuPanelElement.isLoaded()) {
            grim.setColor(255, 255, 255, 255);
            this.menuPanelElement.draw(grim, 0, 0);
        }

        // Content area inside panel
        const contentX = this.menuPanelElement.offsetX + this.OPTIONS_CONTENT_PADDING_X;
        const contentY = this.menuPanelElement.offsetY + 20;

        // === OPTIONS TITLE ===
        if (this.itemTextsHandle >= 0) {
            grim.bindTexture(this.itemTextsHandle);
            grim.setColor(100, 150, 220, 255);
            const vStart = 2 / 8.0;
            const vEnd = 3 / 8.0;
            grim.setUV(0, vStart, 1, vEnd);
            grim.drawQuad(contentX + 10, contentY + 8, this.MENU_LABEL_WIDTH, this.MENU_LABEL_HEIGHT);
        }

        // === OPTION ITEMS ===
        const optionBaseY = contentY + 55;
        const optionSpacing = 20;
        const labelOffsetX = 18;
        const sliderOffsetX = 163;

        for (let i = 0; i < this.optionsItems.length - 1; i++) {
            const item = this.optionsItems[i];
            const itemY = optionBaseY + i * optionSpacing;
            const isHovered = i === this.optionsHoveredIndex;

            // Set item position for hit detection (world space)
            item.x = panelPivotX + contentX + 100;
            item.y = panelPivotY + itemY;

            if (item.type === OptionType.Toggle) {
                const checkmark = item.value ? '\u2611' : '\u2610';
                grim.setColor(140, 180, 220, 255);
                grim.drawText(contentX + labelOffsetX - 2, itemY - 1, checkmark, 14);

                if (isHovered) {
                    grim.setColor(255, 220, 180, 255);
                } else {
                    grim.setColor(160, 160, 180, 255);
                }
                this.bitmapFont.drawText(grim, 'UI Info texts', contentX + labelOffsetX + 18, itemY);
            } else {
                if (isHovered) {
                    grim.setColor(255, 220, 180, 255);
                } else {
                    grim.setColor(160, 160, 180, 255);
                }
                this.bitmapFont.drawText(grim, item.label + ':', contentX + labelOffsetX, itemY);
            }

            // Draw slider control
            if (item.type === OptionType.Slider) {
                this.renderSliderControl(grim, contentX + sliderOffsetX, itemY, item.value);
            }
        }

        // === CONTROLS BUTTON ===
        if (this.controlsButtonHandle >= 0) {
            const controlsY = optionBaseY + 5 * optionSpacing + 25;
            const controlsX = contentX + 78;

            grim.bindTexture(this.controlsButtonHandle);
            grim.setColor(255, 255, 255, 255);
            grim.setUV(0, 0, 1, 1);
            grim.drawQuad(controlsX, controlsY, 82, 32);

            grim.setColor(180, 200, 230, 255);
            this.bitmapFont.drawText(grim, 'Controls', controlsX + 16, controlsY + 9);
        }

        // Done with panel container
        grim.setActiveContainer(null);

        // === BACK BUTTON ===
        const backButton = this.optionsItems[this.optionsItems.length - 1];
        const backIsHovered = this.optionsHoveredIndex === this.optionsItems.length - 1;

        this.renderButtonWithLabel(
            grim,
            backButton.x,
            backButton.y,
            backButton.buttonElement.getRotation(),
            backButton.buttonElement,
            7, // BACK label index in sprite sheet
            backIsHovered,
        );
    }

    /**
     * Render slider control using sprite bars (matches MainMenu.renderSliderControl)
     */
    private renderSliderControl(grim: GrimInterface, x: number, y: number, value: number): void {
        if (this.rectOnTexture === -1 || this.rectOffTexture === -1) {
            // Fallback to text
            const barLength = Math.floor(value / 10);
            const bar = '█'.repeat(barLength) + '░'.repeat(10 - barLength);
            grim.setColor(100, 150, 200, 255);
            grim.drawText(x, y, bar, 12);
            return;
        }

        const SEGMENT_WIDTH = 8;
        const SEGMENT_HEIGHT = 16;
        const NUM_SEGMENTS = 10;
        const filledSegments = Math.floor((value / 100) * NUM_SEGMENTS);

        // Pass 1: Background segments
        grim.bindTexture(this.rectOffTexture);
        grim.setColor(255, 255, 255, 128);
        grim.setUV(0, 0, 1, 1);

        for (let i = 0; i < NUM_SEGMENTS; i++) {
            grim.drawQuad(x + i * SEGMENT_WIDTH, y, SEGMENT_WIDTH, SEGMENT_HEIGHT);
        }

        // Pass 2: Filled segments
        if (filledSegments > 0) {
            grim.bindTexture(this.rectOnTexture);
            grim.setColor(255, 255, 255, 255);
            grim.setUV(0, 0, 1, 1);

            for (let i = 0; i < filledSegments; i++) {
                grim.drawQuad(x + i * SEGMENT_WIDTH, y, SEGMENT_WIDTH, SEGMENT_HEIGHT);
            }
        }

        grim.setColor(255, 255, 255, 255);
    }
}
