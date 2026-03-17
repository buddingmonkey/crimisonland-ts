/**
 * PerkSelectionScreen - Perk selection UI
 *
 * Port of perk_selection_screen_update from C code (lines 4528-4696)
 * Shows available perks on level up and allows player to choose one.
 *
 * Reference layout (from original game screenshot):
 *  - Panel frame on the LEFT side of the screen, animates in from left
 *  - Title: textured "PICK A PERK" image (ui/ui_textPickAPerk.jaz)
 *  - 5-7 perk choices listed vertically, click to select, hover underlines
 *  - Multi-line description text below the choice list
 *  - Cancel button at the bottom-right of the panel
 *  - Cursor rendered on top
 */

import type { GrimInterface, TextureHandle } from '../../engine/GrimInterface';
import type { AssetManager } from '../../data/AssetManager';
import { PerkId, PERK_META, getSelectablePerkIds, PerkSystem } from '../../systems/PerkSystem';
import { UIElement } from '../UIElement';
import type { SoundSystem } from '../../audio/SoundSystem';
import { SoundId } from '../../audio/SoundId';

/**
 * Input state for perk selection
 */
export interface PerkSelectionInput {
    mouseX: number;
    mouseY: number;
    mouseClicked: boolean;
    upPressed: boolean;
    downPressed: boolean;
    confirmPressed: boolean;
    cancelPressed: boolean;
}

/**
 * Perk selection screen UI component
 *
 * C code reference: perk_selection_screen_update @ lines 4528-4696
 */
export class PerkSelectionScreen {
    private choices: PerkId[] = [];
    private selectedIndex: number = 0;
    private isVisible: boolean = false;
    private soundSystem: SoundSystem | null = null;

    // UI Assets
    private panelElement: UIElement;

    private buttonHandle: TextureHandle = -1;
    private titleHandle: TextureHandle = -1; // "PICK A PERK" texture

    // Animation state
    private animTimeline: number = 0;
    private inputDelay: number = 0;
    private readonly ANIM_DURATION = 400; // Panel slide-in duration (ms)
    private slideProgress: number = 0; // 0 = off-screen left, 1 = final position

    // Colors (from C code lines 4592-4603, converted from IEEE 754 hex floats)
    // Normal: steel blue at 60% opacity; Hover: same at full opacity with underline
    // CSS color strings for drawText (which ignores setColor)
    private readonly TEXT_COLOR_NORMAL = '#46b4f099'; // rgba(70, 180, 240, 0.6)
    private readonly TEXT_COLOR_HOVER = '#46b4f0'; // rgba(70, 180, 240, 1.0)
    private readonly COLOR_HOVER = { r: 70, g: 180, b: 240, a: 255 }; // for setColor (underline)
    private readonly COLOR_DESC = { r: 255, g: 255, b: 255, a: 255 };

    // Panel dimensions — the menupanel texture is 512px wide but asymmetric:
    // Left ~40% is the decorative stem/hinge, right ~60% is the black content area.
    // We draw it full-width and position content inside the black portion.
    private readonly PANEL_TEX_W = 512; // full texture display width
    private readonly PANEL_TEX_H = 400; // texture display height
    private readonly PANEL_CONTENT_LEFT = 190; // where black content area starts (after stem)
    private readonly PANEL_CONTENT_RIGHT = 480; // where black content area ends (before right border)
    private readonly PANEL_CONTENT_TOP = 30; // top border inset
    private readonly PANEL_CONTENT_BOTTOM = 370; // bottom border inset

    // Panel position: left-aligned, pivot at left edge (stem/hinge point)
    private readonly PANEL_MARGIN_LEFT = -30;

    // Content layout inside the black area
    private readonly TITLE_OFFSET_Y = 10; // title Y offset from content top
    private readonly TITLE_TEX_W = 220; // display width of PICK A PERK texture
    private readonly TITLE_TEX_H = 30; // display height of PICK A PERK texture

    // Perk list starts below title
    private readonly LIST_START_Y = 50; // from content top, after title + gap
    private readonly LINE_HEIGHT = 19; // C code line 4553: local_20 = 19.0
    private readonly LINE_HEIGHT_EXPERT = 18; // C code line 4588: local_20 = 18.0
    private readonly CONTENT_PADDING_X = 12; // left padding inside content area

    // Description below perk list
    private readonly DESC_GAP = 32; // C code line 4640: local_14 + 32.0
    private readonly DESC_GAP_EXTRA_PERKS = -20; // C code line 4642: -20.0 if > 5 perks
    private readonly DESC_X_OFFSET = -4; // slight left offset for description
    private readonly DESC_WRAP_WIDTH = 260; // word wrap width in pixels

    // Button layout
    private readonly BUTTON_WIDTH = 82;
    private readonly BUTTON_HEIGHT = 32;

    // Hit detection zones (populated during render, checked during update)
    private itemHitAreas: Array<{ x: number; y: number; w: number; h: number }> = [];
    private cancelButtonArea: { x: number; y: number; w: number; h: number } | null = null;

    // Track whether perk expert/master is active (affects layout)
    private hasPerkExpert: boolean = false;
    private hasPerkMaster: boolean = false;

    constructor() {
        // Panel UIElement - uses the menupanel texture
        // Offset: pivot at left edge (stem), panel extends to the right
        // Similar to MainMenu: UIElement(512, 256, 20, -82)
        this.panelElement = new UIElement(this.PANEL_TEX_W, this.PANEL_TEX_H, 0, -this.PANEL_TEX_H / 2);
        this.panelElement.startTime = 0;
        this.panelElement.endTime = this.ANIM_DURATION;
    }

    /**
     * Check if screen is visible
     */
    get visible(): boolean {
        return this.isVisible;
    }

    /**
     * Set sound system reference
     * C code reference: perks.c:158 (sfx_ui_bonus), perks.c:468 (sfx_ui_buttonclick)
     */
    setSoundSystem(soundSystem: SoundSystem): void {
        this.soundSystem = soundSystem;
    }

    /**
     * Load shared UI assets
     */
    async loadAssets(assetManager: AssetManager, grim: GrimInterface): Promise<void> {
        // Load panel texture (reuse menupanel)
        await this.panelElement.load('perk_panel', 'ui/ui_menupanel.jaz', assetManager, grim);

        // Load "PICK A PERK" title texture (C code line 39223)
        const titleTexture = await assetManager.getTexture('ui/ui_textPickAPerk.jaz');
        if (titleTexture) {
            this.titleHandle = grim.registerTexture('perk_title', titleTexture);
        }

        // Load button texture (82x32 small button)
        const buttonTex = await assetManager.getTexture('ui/ui_button_82x32.jaz');
        if (buttonTex) {
            this.buttonHandle = grim.registerTexture('perk_button', buttonTex);
        }
    }

    /**
     * Show the perk selection screen
     *
     * C code reference: lines 4280-4293
     * - Base: 5 choices
     * - Perk Expert: 6 choices
     * - Perk Master: 7 choices
     */
    show(perkSystem: PerkSystem, availablePerks?: PerkId[]): void {
        this.hasPerkMaster = perkSystem.hasPerk(PerkId.PERK_MASTER);
        this.hasPerkExpert = perkSystem.hasPerk(PerkId.PERK_EXPERT);

        let choiceCount = 5;
        if (this.hasPerkMaster) {
            choiceCount = 7;
        } else if (this.hasPerkExpert) {
            choiceCount = 6;
        }

        this.choices = this.generateRandomPerks(choiceCount, perkSystem, availablePerks);
        this.selectedIndex = 0;
        this.isVisible = true;
        this.animTimeline = 0;
        this.inputDelay = 0;
        this.itemHitAreas = [];
        this.cancelButtonArea = null;
    }

    /**
     * Hide the perk selection screen
     */
    hide(): void {
        this.isVisible = false;
        this.choices = [];
        this.selectedIndex = 0;
    }

    /**
     * Generate random perk choices (no duplicates, excludes already owned)
     */
    private generateRandomPerks(count: number, perkSystem: PerkSystem, availablePerks?: PerkId[]): PerkId[] {
        const pool = availablePerks ?? getSelectablePerkIds();
        const available = pool.filter((p) => !perkSystem.hasPerk(p));

        // Fisher-Yates shuffle
        const shuffled = [...available];
        for (let i = shuffled.length - 1; i > 0; i--) {
            const j = Math.floor(Math.random() * (i + 1));
            [shuffled[i], shuffled[j]] = [shuffled[j], shuffled[i]];
        }

        return shuffled.slice(0, Math.min(count, shuffled.length));
    }

    /**
     * Update the perk selection screen
     *
     * Returns the selected perk ID if confirmed, null otherwise.
     * Returns -1 if cancelled.
     *
     * In the original game, clicking a perk name directly selects it.
     */
    update(input: PerkSelectionInput): PerkId | null | -1 {
        if (!this.isVisible || this.choices.length === 0) {
            return null;
        }

        // Advance animation timeline
        this.animTimeline += 16;
        if (this.animTimeline > this.ANIM_DURATION) {
            this.animTimeline = this.ANIM_DURATION;
        }

        // Update slide progress (0 → 1 over ANIM_DURATION)
        this.slideProgress = Math.min(1.0, this.animTimeline / this.ANIM_DURATION);
        // Ease-out for smooth deceleration
        this.slideProgress = 1.0 - (1.0 - this.slideProgress) * (1.0 - this.slideProgress);

        // Skip input for the first few frames to prevent key pass-through
        // from the console command that triggered the level-up
        this.inputDelay++;
        if (this.inputDelay < 3) {
            return null;
        }

        // Navigate with keyboard
        if (input.upPressed) {
            this.selectedIndex = (this.selectedIndex - 1 + this.choices.length) % this.choices.length;
        }
        if (input.downPressed) {
            this.selectedIndex = (this.selectedIndex + 1) % this.choices.length;
        }

        // Cancel
        if (input.cancelPressed) {
            return -1;
        }

        // Cancel button click
        if (input.mouseClicked && this.cancelButtonArea) {
            const area = this.cancelButtonArea;
            if (
                input.mouseX >= area.x &&
                input.mouseX <= area.x + area.w &&
                input.mouseY >= area.y &&
                input.mouseY <= area.y + area.h
            ) {
                return -1;
            }
        }

        // Mouse hover to update selectedIndex (C: ui_menu_item_update hover detection)
        for (let i = 0; i < this.itemHitAreas.length; i++) {
            const area = this.itemHitAreas[i];
            if (
                input.mouseX >= area.x &&
                input.mouseX <= area.x + area.w &&
                input.mouseY >= area.y &&
                input.mouseY <= area.y + area.h
            ) {
                this.selectedIndex = i;
                // Click on hovered item selects it
                if (input.mouseClicked) {
                    // C perks.c:468 — sfx_play(sfx_ui_buttonclick)
                    this.soundSystem?.play(SoundId.UI_BUTTON_CLICK);
                    // C perks.c:158 — sfx_play(sfx_ui_bonus) on confirm
                    this.soundSystem?.play(SoundId.UI_BONUS);
                    return this.choices[i];
                }
                break;
            }
        }

        // Confirm with Enter (keyboard)
        if (input.confirmPressed) {
            // C perks.c:158 — sfx_play(sfx_ui_bonus)
            this.soundSystem?.play(SoundId.UI_BONUS);
            return this.choices[this.selectedIndex];
        }

        return null;
    }

    /**
     * Render the perk selection screen
     *
     * Panel is left-aligned (matches original game reference).
     * No dark overlay - game world stays fully visible.
     */
    render(grim: GrimInterface): void {
        if (!this.isVisible) return;

        // Use 'ui' layer for screen-space rendering (not affected by camera offset).
        // Console overlay uses its own 'console' layer above both 'ui' and 'game'.
        grim.setGraphicsLayer('ui');

        const screenH = grim.getHeight();

        // Panel position: left-aligned, vertically centered
        // The texture extends to the RIGHT from this point
        const finalX = this.PANEL_MARGIN_LEFT;
        const pivotY = screenH / 2;

        // --- Panel container with slide-in from left ---
        // Slide: starts fully off-screen to the left, slides to finalX
        const slideOffset = (1.0 - this.slideProgress) * -(this.PANEL_TEX_W + 40);
        const pivotX = finalX + slideOffset;
        const panelContainer = grim.createContainer();
        grim.setContainerTransform(panelContainer, pivotX, pivotY, 0);
        grim.setActiveContainer(panelContainer);

        // --- Draw panel background ---
        // The menupanel texture is asymmetric: left ~40% is stem, right ~60% is content area
        if (this.panelElement.isLoaded()) {
            grim.setColor(255, 255, 255, 255);
            this.panelElement.draw(grim, 0, 0);
        } else {
            // Fallback: dark panel
            grim.setColor(10, 15, 25, 230);
            grim.drawRectFilled(
                this.panelElement.offsetX,
                this.panelElement.offsetY,
                this.PANEL_TEX_W,
                this.PANEL_TEX_H,
            );
        }

        // Content is positioned inside the BLACK area of the texture
        // The black area starts at PANEL_CONTENT_LEFT from the texture's left edge
        const texLeft = this.panelElement.offsetX; // 0 (texture starts at pivot)
        const texTop = this.panelElement.offsetY; // -PANEL_TEX_H/2
        const contentLeft = texLeft + this.PANEL_CONTENT_LEFT + this.CONTENT_PADDING_X;
        const contentTop = texTop + this.PANEL_CONTENT_TOP;
        const contentWidth = this.PANEL_CONTENT_RIGHT - this.PANEL_CONTENT_LEFT - this.CONTENT_PADDING_X * 2;

        // --- Title: "PICK A PERK" texture (C code line 4563-4567) ---
        if (this.titleHandle >= 0) {
            grim.bindTexture(this.titleHandle);
            grim.setColor(255, 255, 255, 255);
            grim.setUV(0, 0, 1, 1);
            // Center the title horizontally in the content area
            const titleX =
                texLeft + this.PANEL_CONTENT_LEFT + (contentWidth + this.CONTENT_PADDING_X * 2 - this.TITLE_TEX_W) / 2;
            grim.drawQuad(titleX, contentTop + this.TITLE_OFFSET_Y, this.TITLE_TEX_W, this.TITLE_TEX_H);
        } else {
            // Fallback: draw text
            grim.drawText(contentLeft + 20, contentTop + this.TITLE_OFFSET_Y, 'PICK A PERK', 18);
        }

        // --- Perk Expert/Master message (C code lines 4569-4588) ---
        const lineHeight = this.hasPerkExpert ? this.LINE_HEIGHT_EXPERT : this.LINE_HEIGHT;
        let listStartY = contentTop + this.LIST_START_Y;

        if (this.hasPerkMaster) {
            grim.drawText(contentLeft, listStartY - 14, 'extra perks from Perk Master', 9, '#8898ac');
            listStartY -= 8;
        } else if (this.hasPerkExpert) {
            grim.drawText(contentLeft, listStartY - 14, 'extra perk from Perk Expert', 9, '#8898ac');
        }

        // Adjust start if expert/master (C code lines 4583-4588)
        if (this.hasPerkExpert || this.hasPerkMaster) {
            listStartY += 0; // expert shortens gap but we account for it in LINE_HEIGHT_EXPERT
        }

        // Clear hit areas
        this.itemHitAreas = [];

        // --- Perk choice list (C code lines 4623-4638) ---
        for (let i = 0; i < this.choices.length; i++) {
            const perkId = this.choices[i];
            const perk = PERK_META[perkId];
            if (!perk) continue;

            const itemY = listStartY + i * lineHeight;
            // Color: brighter + underline when selected (C code lines 4592-4603)
            // drawText uses its own color parameter (ignores setColor), so pass CSS color strings
            const isSelected = i === this.selectedIndex;
            const textColor = isSelected ? this.TEXT_COLOR_HOVER : this.TEXT_COLOR_NORMAL;

            // Draw perk name using engine's drawText (C: grim_draw_text_small_fmt)
            grim.drawText(contentLeft, itemY, perk.name, 13, textColor);

            // Draw underline for selected/hovered item
            if (isSelected) {
                // Estimate text width from character count (monospace ~8px per char at size 13)
                const estWidth = perk.name.length * 8;
                grim.setColor(this.COLOR_HOVER.r, this.COLOR_HOVER.g, this.COLOR_HOVER.b, this.COLOR_HOVER.a);
                grim.drawLine(contentLeft, itemY + 15, contentLeft + estWidth, itemY + 15, 1);
            }

            // Store hit area in screen space (add pivot offset)
            this.itemHitAreas.push({
                x: pivotX + contentLeft,
                y: pivotY + itemY,
                w: contentWidth,
                h: lineHeight,
            });
        }

        // --- Description text (C code lines 4640-4650) ---
        let descGap = this.DESC_GAP;
        if (this.choices.length > 5) {
            descGap += this.DESC_GAP_EXTRA_PERKS; // compress for 6+ perks
        }
        const descY = listStartY + this.choices.length * lineHeight + descGap;
        const descX = contentLeft + this.DESC_X_OFFSET;

        if (this.choices.length > 0) {
            const selectedPerk = PERK_META[this.choices[this.selectedIndex]];
            if (selectedPerk) {
                grim.setColor(this.COLOR_DESC.r, this.COLOR_DESC.g, this.COLOR_DESC.b, this.COLOR_DESC.a);
                // Word-wrap description using engine drawText
                this.drawWrappedText(grim, descX, descY, selectedPerk.description, this.DESC_WRAP_WIDTH, 12);
            }
        }

        // --- Cancel button (bottom-right of content area) ---
        const contentBottom = texTop + this.PANEL_CONTENT_BOTTOM;
        const buttonY = contentBottom - this.BUTTON_HEIGHT - 8;
        const buttonX = texLeft + this.PANEL_CONTENT_RIGHT - this.BUTTON_WIDTH - this.CONTENT_PADDING_X;
        this.renderButton(grim, buttonX, buttonY, 'Cancel');
        this.cancelButtonArea = {
            x: pivotX + buttonX,
            y: pivotY + buttonY,
            w: this.BUTTON_WIDTH,
            h: this.BUTTON_HEIGHT,
        };

        // Release container (don't destroy - PixiJS needs it until endFrame renders)
        grim.setActiveContainer(null);

        // Note: Cursor rendering is handled centrally by Game.ts using the shared
        // MenuCursor (with glow), matching C code's ui_cursor_render() at perks.c:465.
    }

    /**
     * Draw word-wrapped text using engine drawText
     * Manually splits into lines that fit within maxWidth
     */
    private drawWrappedText(
        grim: GrimInterface,
        x: number,
        y: number,
        text: string,
        maxWidth: number,
        size: number,
    ): void {
        const words = text.split(' ');
        let currentLine = '';
        let lineY = y;
        const lineSpacing = size + 4;
        // Estimate char width for monospace font at given size
        const charWidth = size * 0.6;

        for (const word of words) {
            const testLine = currentLine ? currentLine + ' ' + word : word;
            const testWidth = testLine.length * charWidth;

            if (testWidth > maxWidth && currentLine) {
                grim.drawText(x, lineY, currentLine, size);
                currentLine = word;
                lineY += lineSpacing;
            } else {
                currentLine = testLine;
            }
        }

        if (currentLine) {
            grim.drawText(x, lineY, currentLine, size);
        }
    }

    /**
     * Render a small button with label text
     */
    private renderButton(grim: GrimInterface, x: number, y: number, label: string): void {
        if (this.buttonHandle >= 0) {
            grim.bindTexture(this.buttonHandle);
            grim.setColor(255, 255, 255, 255);
            grim.setUV(0, 0, 1, 1);
            grim.drawQuad(x, y, this.BUTTON_WIDTH, this.BUTTON_HEIGHT);
        } else {
            grim.setColor(60, 60, 70, 220);
            grim.drawRectFilled(x, y, this.BUTTON_WIDTH, this.BUTTON_HEIGHT);
        }

        // Button label text
        grim.setColor(180, 180, 190, 255);
        // Center the label in the button
        const estWidth = label.length * 7;
        const textX = x + (this.BUTTON_WIDTH - estWidth) / 2;
        grim.drawText(textX, y + 9, label, 12);
    }

    /**
     * Get current selection index
     */
    getSelectedIndex(): number {
        return this.selectedIndex;
    }

    /**
     * Get current choices
     */
    getChoices(): readonly PerkId[] {
        return this.choices;
    }
}
