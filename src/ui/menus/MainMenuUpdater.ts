/**
 * MainMenuUpdater - Update logic extracted from MainMenu.ts.
 *
 * Contains updateOptionsMode, updatePlayMenuMode, updateQuestMode,
 * handleSliderClick, and getOptionsContentArea.
 */

import { MenuAction, type MenuInput } from '../screens/MainMenu';
import { OptionType } from './OptionItem';
import { SoundId } from '../../audio/SoundId';
import { getQuestsInTier, isQuestUnlocked } from '../../data/QuestData';
import { questSystem } from '../../systems/quest/QuestSystem';

/**
 * Duck-typed context for MainMenu update methods.
 * Subset of MainMenu fields needed by update functions.
 */
export interface MenuUpdateContext {
    // Panel and button elements
    menuPanelElement: {
        update(dt: number, highlighted: boolean, timeline: number): void;
        offsetX: number;
        offsetY: number;
    };
    questPanelElement: { update(dt: number, highlighted: boolean, timeline: number): void; offsetY: number };
    globalTimeline: number;

    // Options mode state
    optionsHoveredIndex: number;
    optionsSelectedIndex: number;
    optionsItems: Array<{
        type: number;
        label: string;
        buttonElement: {
            update(dt: number, highlighted: boolean, timeline: number): void;
            getRotatedBounds(x: number, y: number): { left: number; right: number; top: number; bottom: number };
        };
        x: number;
        y: number;
        adjustValue(delta: number): void;
        value: number;
    }>;

    // Play menu state
    playMenuHoveredIndex: number;
    playMenuSelectedIndex: number;
    playMenuButtons: Array<{
        label: string;
        action: MenuAction;
        hoverAnim: number;
        clickAnim: number;
        description: string;
    }>;
    playerCount: number;
    dropdownOpen: boolean;

    // Quest mode state
    questSelectedTier: number;
    questHoveredIndex: number;
    selectedQuestTier: number;
    selectedQuestIndex: number;

    // Exit/transition
    isExiting: boolean;
    exitAction: MenuAction;

    // Audio
    soundSystem: { play(id: number): void } | null;
    musicSystem: { setVolume(vol: number): void } | null;

    // Layout constants
    readonly OPTIONS_CONTENT_PADDING_X: number;
    readonly MENU_LABEL_BASE_X: number;
    readonly MENU_LABEL_BASE_Y: number;
    readonly MENU_LABEL_STEP: number;
}

/**
 * Update options mode.
 */
export function updateOptionsMode(ctx: MenuUpdateContext, dt: number, input: MenuInput): MenuAction {
    // Update panel animation
    ctx.menuPanelElement.update(dt, false, ctx.globalTimeline);

    // Handle ESC key to return to main menu with exit animation
    if (input.escPressed && !ctx.isExiting) {
        ctx.isExiting = true;
        ctx.exitAction = MenuAction.None;
    }

    // Update hover state and animations for options items
    ctx.optionsHoveredIndex = -1;

    // Check for slider clicks first
    if (input.mouseClicked) {
        for (let i = 0; i < ctx.optionsItems.length - 1; i++) {
            const item = ctx.optionsItems[i];
            if (item.type === OptionType.Slider) {
                if (handleSliderClick(ctx, i, input.mouseX, input.mouseY)) {
                    if (ctx.soundSystem) {
                        ctx.soundSystem.play(SoundId.UI_BUTTON_CLICK);
                    }
                    break;
                }
            }
        }
    }

    // Compute hit-test positions matching the renderer (MainMenuRenderer.renderOptionsItems)
    const { contentX, contentY } = getOptionsContentArea(ctx);
    const optionBaseY = contentY + 55;
    const optionSpacing = 20;
    const hitWidth = 230; // covers label + slider/toggle area

    for (let i = 0; i < ctx.optionsItems.length; i++) {
        const item = ctx.optionsItems[i];

        let isHovered: boolean;
        if (i < ctx.optionsItems.length - 1) {
            // Content items (sliders, toggles) — use panel content positions
            const itemY = optionBaseY + i * optionSpacing;
            isHovered =
                input.mouseX >= contentX &&
                input.mouseX <= contentX + hitWidth &&
                input.mouseY >= itemY &&
                input.mouseY <= itemY + optionSpacing;
        } else {
            // Back button — rendered outside the panel at main-menu button position
            const bounds = item.buttonElement.getRotatedBounds(item.x, item.y);
            isHovered =
                input.mouseX >= bounds.left &&
                input.mouseX <= bounds.right &&
                input.mouseY >= bounds.top &&
                input.mouseY <= bounds.bottom;
        }

        if (isHovered) {
            ctx.optionsHoveredIndex = i;

            if (input.mouseClicked) {
                if (ctx.soundSystem) {
                    ctx.soundSystem.play(SoundId.UI_BUTTON_CLICK);
                }

                ctx.optionsSelectedIndex = i;

                // Handle Back button with exit animation
                if (item.type === OptionType.Button && item.label === 'Back') {
                    ctx.isExiting = true;
                    ctx.exitAction = MenuAction.None;
                }

                // Handle toggle
                if (item.type === OptionType.Toggle) {
                    item.adjustValue(1);
                }
            }
        }

        // Update button animation
        const isHighlighted = isHovered || i === ctx.optionsSelectedIndex;
        item.buttonElement.update(dt, isHighlighted, ctx.globalTimeline);
    }

    return MenuAction.None;
}

/**
 * Update play menu mode.
 */
export function updatePlayMenuMode(ctx: MenuUpdateContext, dt: number, input: MenuInput): MenuAction {
    // Update panel animation
    ctx.menuPanelElement.update(dt, false, ctx.globalTimeline);

    // Handle ESC key
    if (input.escPressed && !ctx.isExiting) {
        ctx.isExiting = true;
        ctx.exitAction = MenuAction.None;
    }

    // Calculate button layout positions
    const panelPivotX = -90;
    const panelPivotY = 200;
    const contentX = panelPivotX + ctx.menuPanelElement.offsetX + ctx.OPTIONS_CONTENT_PADDING_X;
    const contentY = panelPivotY + ctx.menuPanelElement.offsetY + 20;
    const buttonStartY = contentY + 50;
    const buttonSpacing = 34;
    const contentWidth = 230;
    const buttonWidth = 128;
    const buttonHeight = 32;
    const buttonX = contentX + (contentWidth - buttonWidth) / 2;

    // Handle dropdown toggle
    const dropdownX = contentX + 130;
    const dropdownY = contentY + 12;
    const dropdownWidth = 82;
    const dropdownHeight = 20;
    let dropdownConsumedClick = false;

    if (input.mouseClicked) {
        const inDropdownHeader =
            input.mouseX >= dropdownX &&
            input.mouseX <= dropdownX + dropdownWidth &&
            input.mouseY >= dropdownY &&
            input.mouseY <= dropdownY + dropdownHeight;

        if (ctx.dropdownOpen) {
            const listBottom = dropdownY + dropdownHeight + 4 * dropdownHeight;
            const inDropdownList =
                input.mouseX >= dropdownX &&
                input.mouseX <= dropdownX + dropdownWidth &&
                input.mouseY >= dropdownY + dropdownHeight &&
                input.mouseY <= listBottom;

            if (inDropdownList) {
                for (let i = 0; i < 4; i++) {
                    const optY = dropdownY + dropdownHeight + i * dropdownHeight;
                    if (input.mouseY >= optY && input.mouseY <= optY + dropdownHeight) {
                        ctx.playerCount = i + 1;
                        ctx.dropdownOpen = false;
                        dropdownConsumedClick = true;
                        if (ctx.soundSystem) {
                            ctx.soundSystem.play(SoundId.UI_BUTTON_CLICK);
                        }
                        break;
                    }
                }
            } else if (inDropdownHeader) {
                ctx.dropdownOpen = false;
                dropdownConsumedClick = true;
            } else {
                ctx.dropdownOpen = false;
            }
        } else if (inDropdownHeader) {
            ctx.dropdownOpen = true;
            dropdownConsumedClick = true;
            if (ctx.soundSystem) {
                ctx.soundSystem.play(SoundId.UI_BUTTON_CLICK);
            }
        }
    }

    // Update play menu buttons
    ctx.playMenuHoveredIndex = -1;
    let clickedAction = MenuAction.None;

    for (let i = 0; i < ctx.playMenuButtons.length; i++) {
        const btn = ctx.playMenuButtons[i];
        const btnY = buttonStartY + i * buttonSpacing;

        const isHovered =
            input.mouseX >= buttonX &&
            input.mouseX <= buttonX + buttonWidth &&
            input.mouseY >= btnY &&
            input.mouseY <= btnY + buttonHeight;

        if (isHovered) {
            ctx.playMenuHoveredIndex = i;
        }

        const isActive = isHovered || i === ctx.playMenuSelectedIndex;
        if (isActive) {
            btn.hoverAnim += dt * 6;
        } else {
            btn.hoverAnim += dt * -4;
        }

        if (btn.hoverAnim < 0) btn.hoverAnim = 0;
        if (btn.hoverAnim > 1000) btn.hoverAnim = 1000;

        if (btn.clickAnim > 0) {
            btn.clickAnim += dt * -6;
            if (btn.clickAnim < 0) btn.clickAnim = 0;
        }

        if (isHovered && input.mouseClicked && !ctx.isExiting && !dropdownConsumedClick) {
            btn.clickAnim = 1000;
            ctx.playMenuSelectedIndex = i;

            if (ctx.soundSystem) {
                ctx.soundSystem.play(SoundId.UI_BUTTON_CLICK);
            }

            ctx.isExiting = true;
            ctx.exitAction = btn.action;
        }
    }

    // BACK button hit test
    const backX = ctx.MENU_LABEL_BASE_X;
    const backY = ctx.MENU_LABEL_BASE_Y + 5 * ctx.MENU_LABEL_STEP;
    const backBounds = ctx.optionsItems[ctx.optionsItems.length - 1].buttonElement.getRotatedBounds(backX, backY);
    const backHovered =
        input.mouseX >= backBounds.left &&
        input.mouseX <= backBounds.right &&
        input.mouseY >= backBounds.top &&
        input.mouseY <= backBounds.bottom;

    if (backHovered && input.mouseClicked && !ctx.isExiting) {
        if (ctx.soundSystem) {
            ctx.soundSystem.play(SoundId.UI_BUTTON_CLICK);
        }
        ctx.isExiting = true;
        ctx.exitAction = MenuAction.None;
    }

    // Update BACK button animation
    const backElement = ctx.optionsItems[ctx.optionsItems.length - 1].buttonElement;
    backElement.update(dt, backHovered, ctx.globalTimeline);

    return clickedAction;
}

/**
 * Update quest screen mode.
 */
export function updateQuestMode(ctx: MenuUpdateContext, dt: number, input: MenuInput): MenuAction {
    ctx.questPanelElement.update(dt, false, ctx.globalTimeline);

    if (input.escPressed && !ctx.isExiting) {
        ctx.isExiting = true;
        ctx.exitAction = MenuAction.None;
    }

    // Quest panel layout — use actual logical screen height (variable resolution)
    const screenH = input.screenHeight;
    const panelMarginLeft = -30;
    const panelX = panelMarginLeft;
    const panelY = screenH / 2 + 10;

    const contentLeft = 190;
    const contentTop = 40;
    const contentX = panelX + contentLeft;
    const contentY = panelY + ctx.questPanelElement.offsetY + contentTop;

    // Tier button positions
    const tierButtonStartX = contentX + 100;
    const tierButtonY = contentY + 8;
    const tierButtonWidth = 32;
    const tierButtonHeight = 32;
    const tierButtonSpacing = 36;

    if (input.mouseClicked && !ctx.isExiting) {
        for (let i = 0; i < 5; i++) {
            const btnX = tierButtonStartX + i * tierButtonSpacing;
            if (
                input.mouseX >= btnX &&
                input.mouseX <= btnX + tierButtonWidth &&
                input.mouseY >= tierButtonY &&
                input.mouseY <= tierButtonY + tierButtonHeight
            ) {
                ctx.questSelectedTier = i + 1;
                ctx.questHoveredIndex = -1;
                if (ctx.soundSystem) {
                    ctx.soundSystem.play(SoundId.UI_BUTTON_CLICK);
                }
                break;
            }
        }
    }

    // Quest list positions
    const questListStartY = contentY + 55;
    const questRowHeight = 17;
    const questListX = contentX + 30;
    const questListWidth = 250;

    ctx.questHoveredIndex = -1;
    const unlockIndex = questSystem.getUnlockIndex();
    const quests = getQuestsInTier(ctx.questSelectedTier);

    for (let i = 0; i < quests.length; i++) {
        const quest = quests[i];
        const rowY = questListStartY + i * questRowHeight;
        const isHovered =
            input.mouseX >= questListX &&
            input.mouseX <= questListX + questListWidth &&
            input.mouseY >= rowY &&
            input.mouseY <= rowY + questRowHeight;

        if (isHovered) {
            ctx.questHoveredIndex = i;

            if (input.mouseClicked && !ctx.isExiting) {
                if (isQuestUnlocked(quest.tier, quest.index, unlockIndex)) {
                    ctx.selectedQuestTier = quest.tier;
                    ctx.selectedQuestIndex = quest.index;
                    if (ctx.soundSystem) {
                        ctx.soundSystem.play(SoundId.UI_BUTTON_CLICK);
                    }
                    ctx.isExiting = true;
                    ctx.exitAction = MenuAction.StartQuest;
                }
            }
        }
    }

    // BACK button inside panel
    const backBtnW = 82;
    const backBtnH = 32;
    const backBtnX = contentX + 190;
    const backBtnY = contentY + 270;
    const backHovered =
        input.mouseX >= backBtnX &&
        input.mouseX <= backBtnX + backBtnW &&
        input.mouseY >= backBtnY &&
        input.mouseY <= backBtnY + backBtnH;

    if (backHovered && input.mouseClicked && !ctx.isExiting) {
        if (ctx.soundSystem) {
            ctx.soundSystem.play(SoundId.UI_BUTTON_CLICK);
        }
        ctx.isExiting = true;
        ctx.exitAction = MenuAction.None;
    }

    return MenuAction.None;
}

/**
 * Handle slider click interaction.
 */
export function handleSliderClick(ctx: MenuUpdateContext, itemIndex: number, mouseX: number, mouseY: number): boolean {
    const { contentX, contentY } = getOptionsContentArea(ctx);
    // Match renderer layout (MainMenuRenderer.renderOptionsItems)
    const optionBaseY = contentY + 55;
    const optionSpacing = 20;
    const sliderOffsetX = 163;
    const sliderX = contentX + sliderOffsetX;
    const y = optionBaseY + itemIndex * optionSpacing;

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
        ctx.optionsItems[itemIndex].value = Math.round(newValue);

        if (itemIndex === 0 && ctx.soundSystem) {
            (ctx.soundSystem as any).setMasterVolume(newValue / 100);
        } else if (itemIndex === 1 && ctx.musicSystem) {
            ctx.musicSystem.setVolume(newValue / 100);
        }

        return true;
    }

    return false;
}

/**
 * Get options content area coordinates.
 */
export function getOptionsContentArea(ctx: MenuUpdateContext): { contentX: number; contentY: number } {
    const panelPivotX = -90;
    const pivotY = 200;
    const panelContentX = panelPivotX + ctx.menuPanelElement.offsetX;
    const panelContentY = pivotY + ctx.menuPanelElement.offsetY;
    const contentPaddingX = ctx.OPTIONS_CONTENT_PADDING_X;
    const contentPaddingY = 20;

    return {
        contentX: panelContentX + contentPaddingX,
        contentY: panelContentY + contentPaddingY,
    };
}
