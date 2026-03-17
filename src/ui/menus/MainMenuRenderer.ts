/**
 * MainMenuRenderer - Extracted render methods for MainMenu sub-screens.
 *
 * Pulled from MainMenu.ts to reduce file size.
 * These are purely visual methods that read (but don't write) menu state.
 */

import type { GrimInterface, TextureHandle } from '../../engine/GrimInterface';
import type { BitmapFont } from '../../engine/BitmapFont';
import type { UIElement } from '../UIElement';
import { OptionType } from './OptionItem';
import { questSystem } from '../../systems/quest/QuestSystem';
import { getQuestsInTier, isQuestUnlocked } from '../../data/QuestData';

/**
 * Subset of MainMenu fields needed by the sub-screen renderers.
 * Duck-typed: any object with these properties will work.
 */
export interface MenuRenderContext {
    readonly itemTextsHandle: TextureHandle;
    readonly controlsButtonHandle: TextureHandle;
    readonly mediumButtonHandle: TextureHandle;
    readonly menuPanelElement: UIElement;
    readonly questPanelElement: UIElement;
    readonly bitmapFont: BitmapFont;
    readonly OPTIONS_CONTENT_PADDING_X: number;
    readonly MENU_LABEL_WIDTH: number;
    readonly MENU_LABEL_HEIGHT: number;
    readonly MENU_LABEL_BASE_X: number;
    readonly MENU_LABEL_BASE_Y: number;
    readonly MENU_LABEL_STEP: number;
    readonly MENU_LABEL_OFFSET_X: number;
    readonly MENU_LABEL_OFFSET_Y: number;
    readonly questTextHandle: TextureHandle;
    readonly questNumHandles: TextureHandle[];
    readonly questSelectedTier: number;
    readonly questHoveredIndex: number;
    readonly globalTimeline: number;
    readonly playMenuButtons: ReadonlyArray<{
        label: string;
        hoverAnim: number;
        clickAnim: number;
        description: string;
    }>;
    readonly playMenuHoveredIndex: number;
    readonly playMenuSelectedIndex: number;
    readonly playerCount: number;
    readonly dropdownOpen: boolean;
    readonly optionsItems: ReadonlyArray<{
        label: string;
        type: number;
        value: number;
        x: number;
        y: number;
        buttonElement: UIElement;
    }>;
    readonly optionsHoveredIndex: number;

    // Static texture needed by quest screen
    readonly rectOnTexture: TextureHandle;

    // Methods used by rendering
    renderButtonWithLabel(
        grim: GrimInterface,
        x: number,
        y: number,
        rotation: number,
        buttonElement: UIElement,
        labelIndex: number,
        isHovered: boolean,
    ): void;
    renderSliderControl(grim: GrimInterface, x: number, y: number, value: number): void;
}

// ─────────────────────────────────────────────────────────────────
// renderPlayMenuItems
// ─────────────────────────────────────────────────────────────────

/**
 * Render play menu items - panel with game mode buttons, dropdown, descriptions
 * Matches screenshot: same panel as options, with mode buttons inside.
 *
 * Extracted from MainMenu.renderPlayMenuItems().
 */
export function renderPlayMenuItems(ctx: MenuRenderContext, grim: GrimInterface): void {
    const panelPivotX = -90;
    const panelPivotY = 200;
    const panelRotation = ctx.menuPanelElement.getRotation();

    const panelContainer = grim.createContainer();
    grim.setContainerTransform(panelContainer, panelPivotX, panelPivotY, panelRotation);
    grim.setActiveContainer(panelContainer);

    if (ctx.menuPanelElement.isLoaded()) {
        grim.setColor(255, 255, 255, 255);
        ctx.menuPanelElement.draw(grim, 0, 0);
    }

    const contentX = ctx.menuPanelElement.offsetX + ctx.OPTIONS_CONTENT_PADDING_X;
    const contentY = ctx.menuPanelElement.offsetY + 20;

    // PLAY GAME TITLE
    if (ctx.itemTextsHandle >= 0) {
        grim.bindTexture(ctx.itemTextsHandle);
        grim.setColor(100, 150, 220, 255);
        const vStart = 1 / 8.0;
        const vEnd = 2 / 8.0;
        grim.setUV(0, vStart, 1, vEnd);
        grim.drawQuad(contentX + 10, contentY + 10, ctx.MENU_LABEL_WIDTH, ctx.MENU_LABEL_HEIGHT);
    }

    // PLAYER COUNT DROPDOWN
    const dropdownX = contentX + 130;
    const dropdownY = contentY + 12;
    const dropdownWidth = 82;
    const dropdownHeight = 20;

    if (ctx.controlsButtonHandle >= 0) {
        grim.bindTexture(ctx.controlsButtonHandle);
        grim.setColor(255, 255, 255, 255);
        grim.setUV(0, 0, 1, 1);
        grim.drawQuad(dropdownX, dropdownY, dropdownWidth, dropdownHeight);
    } else {
        grim.setColor(30, 35, 50, 220);
        grim.drawRectFilled(dropdownX, dropdownY, dropdownWidth, dropdownHeight);
    }

    grim.setColor(220, 220, 230, 255);
    ctx.bitmapFont.drawText(grim, `${ctx.playerCount} player`, dropdownX + 6, dropdownY + 5);
    grim.setColor(180, 180, 200, 255);
    ctx.bitmapFont.drawText(grim, '\u25BC', dropdownX + dropdownWidth - 14, dropdownY + 5);

    // MODE BUTTONS
    const buttonStartY = contentY + 50;
    const buttonSpacing = 34;
    const contentWidth = 230;
    const buttonWidth = 128;
    const buttonHeight = 32;
    const buttonX = contentX + (contentWidth - buttonWidth) / 2;

    for (let i = 0; i < ctx.playMenuButtons.length; i++) {
        const btn = ctx.playMenuButtons[i];
        const btnY = buttonStartY + i * buttonSpacing;
        const isHovered = i === ctx.playMenuHoveredIndex;

        const btnHandle = ctx.mediumButtonHandle >= 0 ? ctx.mediumButtonHandle : ctx.controlsButtonHandle;
        if (btnHandle >= 0) {
            grim.bindTexture(btnHandle);
            if (btn.clickAnim > 0) {
                const clickNorm = btn.clickAnim / 1000;
                const r = Math.floor((0.5 + clickNorm * 0.5) * 255);
                const g = Math.floor((0.7 + clickNorm * 0.3) * 255);
                grim.setColor(r, g, 255, 255);
            } else if (isHovered || btn.hoverAnim > 0) {
                const hoverAlpha = Math.max(btn.hoverAnim / 1000, isHovered ? 0.5 : 0);
                const brightness = Math.floor(200 + 55 * hoverAlpha);
                grim.setColor(brightness, brightness, brightness, 255);
            } else {
                grim.setColor(180, 180, 180, 255);
            }
            grim.setUV(0, 0, 1, 1);
            grim.drawQuad(buttonX, btnY, buttonWidth, buttonHeight);
        }

        if (isHovered) {
            grim.setColor(230, 225, 215, 255);
        } else {
            grim.setColor(230, 225, 215, Math.floor(255 * 0.7));
        }
        const textWidth = ctx.bitmapFont.measureText(btn.label);
        const textX = buttonX + (buttonWidth - textWidth) / 2;
        ctx.bitmapFont.drawText(grim, btn.label, textX, btnY + 10);
    }

    // DROPDOWN OPEN LIST
    if (ctx.dropdownOpen && ctx.rectOnTexture >= 0) {
        grim.bindTexture(ctx.rectOnTexture);
        grim.setUV(0, 0, 1, 1);
        for (let i = 0; i < 4; i++) {
            const optY = dropdownY + dropdownHeight + i * dropdownHeight;
            const isSelected = i + 1 === ctx.playerCount;
            grim.setColor(isSelected ? 50 : 25, isSelected ? 50 : 25, isSelected ? 70 : 40, 240);
            grim.drawQuad(dropdownX, optY, dropdownWidth, dropdownHeight);
            grim.setColor(80, 90, 110, 200);
            grim.drawQuad(dropdownX, optY + dropdownHeight - 1, dropdownWidth, 1);
            grim.setColor(220, 220, 230, 255);
            ctx.bitmapFont.drawText(grim, `${i + 1} player`, dropdownX + 6, optY + 5);
        }
        const listTop = dropdownY + dropdownHeight;
        const listHeight = 4 * dropdownHeight;
        grim.setColor(80, 90, 110, 200);
        grim.drawQuad(dropdownX, listTop, 1, listHeight);
        grim.drawQuad(dropdownX + dropdownWidth - 1, listTop, 1, listHeight);
        grim.drawQuad(dropdownX, listTop + listHeight - 1, dropdownWidth, 1);
    }

    // DESCRIPTION TEXT
    const descY = buttonStartY + ctx.playMenuButtons.length * buttonSpacing + 10;
    const descIndex = ctx.playMenuHoveredIndex >= 0 ? ctx.playMenuHoveredIndex : ctx.playMenuSelectedIndex;
    if (descIndex >= 0 && descIndex < ctx.playMenuButtons.length) {
        grim.setColor(160, 150, 100, 200);
        const descText = ctx.playMenuButtons[descIndex].description;
        const descTextWidth = ctx.bitmapFont.measureText(descText);
        const descTextX = contentX + (contentWidth - descTextWidth) / 2;
        ctx.bitmapFont.drawText(grim, descText, descTextX, descY);
    }

    grim.setActiveContainer(null);

    // BACK BUTTON
    const backX = ctx.MENU_LABEL_BASE_X;
    const backY = ctx.MENU_LABEL_BASE_Y + 5 * ctx.MENU_LABEL_STEP;
    const backElement = ctx.optionsItems[ctx.optionsItems.length - 1].buttonElement;
    const backBounds = backElement.getRotatedBounds(backX, backY);
    const mouseX = grim.getMouseX();
    const mouseY = grim.getMouseY();
    const isBackHovered =
        mouseX >= backBounds.left &&
        mouseX <= backBounds.right &&
        mouseY >= backBounds.top &&
        mouseY <= backBounds.bottom;

    ctx.renderButtonWithLabel(grim, backX, backY, backElement.getRotation(), backElement, 7, isBackHovered);
}

// ─────────────────────────────────────────────────────────────────
// renderQuestScreen
// ─────────────────────────────────────────────────────────────────

/**
 * Render quest selection screen - larger panel with tier buttons and quest list.
 *
 * Extracted from MainMenu.renderQuestScreen().
 */
export function renderQuestScreen(ctx: MenuRenderContext, grim: GrimInterface): void {
    grim.setGraphicsLayer('ui');
    grim.setRotation(0);

    const screenH = grim.getHeight();

    const slideT = Math.min(1.0, ctx.globalTimeline / 500);
    const eased = 1 - Math.cos((slideT * Math.PI) / 2);

    const panelMarginLeft = -30;
    const pivotY = screenH / 2 + 10;
    const panelTargetX = panelMarginLeft;
    const panelOffscreenX = -512 - 10;
    const panelX = panelOffscreenX + (panelTargetX - panelOffscreenX) * eased;

    grim.setBlendMode('normal');
    grim.setColor(255, 255, 255, 255);
    ctx.questPanelElement.draw(grim, panelX, pivotY);

    const contentLeft = 190;
    const contentTop = 40;
    const contentX = panelX + contentLeft;
    const contentY = pivotY + ctx.questPanelElement.offsetY + contentTop;

    // QUEST: HEADER
    if (ctx.questTextHandle >= 0) {
        grim.bindTexture(ctx.questTextHandle);
        grim.setColor(255, 255, 255, 255);
        grim.setUV(0, 0, 1, 1);
        grim.drawQuad(contentX + 10, contentY + 4, 80, 32);
    } else {
        grim.setColor(180, 170, 140, 255);
        ctx.bitmapFont.drawText(grim, 'QUEST:', contentX + 10, contentY + 12);
    }

    // TIER BUTTONS
    const tierLabels = ['I', 'II', 'III', 'IV', 'V'];
    const tierButtonStartX = contentX + 100;
    const tierButtonY = contentY + 8;
    const tierButtonWidth = 32;
    const tierButtonHeight = 32;
    const tierButtonSpacing = 36;

    for (let i = 0; i < 5; i++) {
        const btnX = tierButtonStartX + i * tierButtonSpacing;
        const isSelected = i + 1 === ctx.questSelectedTier;

        if (ctx.questNumHandles[i] >= 0) {
            grim.bindTexture(ctx.questNumHandles[i]);
            grim.setColor(isSelected ? 255 : 180, isSelected ? 255 : 180, isSelected ? 255 : 180, 255);
            grim.setUV(0, 0, 1, 1);
            grim.drawQuad(btnX, tierButtonY, tierButtonWidth, tierButtonHeight);
        } else {
            grim.setColor(isSelected ? 200 : 80, isSelected ? 180 : 80, isSelected ? 120 : 100, 255);
            grim.drawRectFilled(btnX, tierButtonY, tierButtonWidth, tierButtonHeight);
            grim.setColor(isSelected ? 255 : 200, isSelected ? 255 : 200, isSelected ? 255 : 200, 255);
            const labelW = ctx.bitmapFont.measureText(tierLabels[i]);
            ctx.bitmapFont.drawText(grim, tierLabels[i], btnX + (tierButtonWidth - labelW) / 2, tierButtonY + 10);
        }
    }

    // QUEST LIST
    const questListStartY = contentY + 55;
    const questRowHeight = 17;
    const unlockIndex = questSystem.getUnlockIndex();
    const quests = getQuestsInTier(ctx.questSelectedTier);

    for (let i = 0; i < quests.length; i++) {
        const quest = quests[i];
        const rowY = questListStartY + i * questRowHeight;
        const isUnlocked = isQuestUnlocked(quest.tier, quest.index, unlockIndex);
        const isHovered = i === ctx.questHoveredIndex;

        const numStr = `${quest.tier}.${quest.index}`;
        const nameStr = isUnlocked ? quest.name : '???';

        if (isHovered && isUnlocked) {
            grim.setColor(100, 180, 255, 255);
        } else if (isUnlocked) {
            grim.setColor(70, 140, 210, 255);
        } else {
            grim.setColor(120, 120, 130, 255);
        }

        ctx.bitmapFont.drawText(grim, numStr, contentX + 38, rowY);
        ctx.bitmapFont.drawText(grim, nameStr, contentX + 85, rowY);

        if (isHovered && isUnlocked) {
            const totalWidth = ctx.bitmapFont.measureText(numStr + '   ' + nameStr);
            grim.setColor(70, 140, 210, 180);
            if (ctx.rectOnTexture >= 0) {
                grim.bindTexture(ctx.rectOnTexture);
                grim.setUV(0, 0, 1, 1);
                grim.drawQuad(contentX + 38, rowY + 13, totalWidth, 1);
            }
        }
    }

    // BACK BUTTON
    const backBtnW = 82;
    const backBtnH = 32;
    const backBtnX = contentX + 190;
    const backBtnY = contentY + 270;

    if (ctx.controlsButtonHandle >= 0) {
        const mouseX = grim.getMouseX();
        const mouseY = grim.getMouseY();
        const isBackHovered =
            mouseX >= backBtnX && mouseX <= backBtnX + backBtnW && mouseY >= backBtnY && mouseY <= backBtnY + backBtnH;

        grim.bindTexture(ctx.controlsButtonHandle);
        grim.setColor(isBackHovered ? 220 : 180, isBackHovered ? 220 : 180, isBackHovered ? 220 : 180, 255);
        grim.setUV(0, 0, 1, 1);
        grim.drawQuad(backBtnX, backBtnY, backBtnW, backBtnH);

        grim.setColor(isBackHovered ? 255 : 200, isBackHovered ? 255 : 200, isBackHovered ? 255 : 200, 255);
        const backTextW = ctx.bitmapFont.measureText('Back');
        ctx.bitmapFont.drawText(grim, 'Back', backBtnX + (backBtnW - backTextW) / 2, backBtnY + 10);
    } else {
        grim.setColor(180, 180, 180, 255);
        ctx.bitmapFont.drawText(grim, 'Back', backBtnX, backBtnY + 10);
    }
}

// ─────────────────────────────────────────────────────────────────
// renderOptionsItems
// ─────────────────────────────────────────────────────────────────

/**
 * Render options menu - single panel with text labels and sprite-based sliders.
 *
 * Extracted from MainMenu.renderOptionsItems().
 */
export function renderOptionsItems(ctx: MenuRenderContext, grim: GrimInterface): void {
    const panelPivotX = -90;
    const panelPivotY = 200;
    const panelRotation = ctx.menuPanelElement.getRotation();

    const panelContainer = grim.createContainer();
    grim.setContainerTransform(panelContainer, panelPivotX, panelPivotY, panelRotation);
    grim.setActiveContainer(panelContainer);

    if (ctx.menuPanelElement.isLoaded()) {
        grim.setColor(255, 255, 255, 255);
        ctx.menuPanelElement.draw(grim, 0, 0);
    }

    const contentX = ctx.menuPanelElement.offsetX + ctx.OPTIONS_CONTENT_PADDING_X;
    const contentY = ctx.menuPanelElement.offsetY + 20;

    // OPTIONS TITLE
    if (ctx.itemTextsHandle >= 0) {
        grim.bindTexture(ctx.itemTextsHandle);
        grim.setColor(100, 150, 220, 255);
        const vStart = 2 / 8.0;
        const vEnd = 3 / 8.0;
        grim.setUV(0, vStart, 1, vEnd);
        grim.drawQuad(contentX + 10, contentY + 8, ctx.MENU_LABEL_WIDTH, ctx.MENU_LABEL_HEIGHT);
    }

    // OPTION ITEMS
    const optionBaseY = contentY + 55;
    const optionSpacing = 20;
    const labelOffsetX = 18;
    const sliderOffsetX = 163;

    for (let i = 0; i < ctx.optionsItems.length - 1; i++) {
        const item = ctx.optionsItems[i];
        const itemY = optionBaseY + i * optionSpacing;
        const isHovered = i === ctx.optionsHoveredIndex;

        if (item.type === OptionType.Toggle) {
            const checkmark = item.value ? '\u2611' : '\u2610';
            grim.setColor(140, 180, 220, 255);
            grim.drawText(contentX + labelOffsetX - 2, itemY - 1, checkmark, 14);

            if (isHovered) {
                grim.setColor(255, 220, 180, 255);
            } else {
                grim.setColor(160, 160, 180, 255);
            }
            ctx.bitmapFont.drawText(grim, 'UI Info texts', contentX + labelOffsetX + 18, itemY);
        } else {
            if (isHovered) {
                grim.setColor(255, 220, 180, 255);
            } else {
                grim.setColor(160, 160, 180, 255);
            }
            ctx.bitmapFont.drawText(grim, item.label + ':', contentX + labelOffsetX, itemY);
        }

        if (item.type === OptionType.Slider) {
            ctx.renderSliderControl(grim, contentX + sliderOffsetX, itemY, item.value);
        }
    }

    // CONTROLS BUTTON
    if (ctx.controlsButtonHandle >= 0) {
        const controlsY = optionBaseY + 5 * optionSpacing + 25;
        const controlsX = contentX + 78;

        grim.bindTexture(ctx.controlsButtonHandle);
        grim.setColor(255, 255, 255, 255);
        grim.setUV(0, 0, 1, 1);
        grim.drawQuad(controlsX, controlsY, 82, 32);

        grim.setColor(180, 200, 230, 255);
        ctx.bitmapFont.drawText(grim, 'Controls', controlsX + 16, controlsY + 9);
    }

    // BACK BUTTON
    grim.setActiveContainer(null);

    const backX = ctx.MENU_LABEL_BASE_X;
    const backY = ctx.MENU_LABEL_BASE_Y + 5 * ctx.MENU_LABEL_STEP;
    const backElement = ctx.optionsItems[ctx.optionsItems.length - 1].buttonElement;
    const backBounds = backElement.getRotatedBounds(backX, backY);
    const mouseX = grim.getMouseX();
    const mouseY = grim.getMouseY();
    const isBackHovered =
        mouseX >= backBounds.left &&
        mouseX <= backBounds.right &&
        mouseY >= backBounds.top &&
        mouseY <= backBounds.bottom;

    ctx.renderButtonWithLabel(grim, backX, backY, backElement.getRotation(), backElement, 7, isBackHovered);
}
