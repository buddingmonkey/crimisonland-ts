/**
 * StatisticsScreen.ts - Game statistics display UI
 *
 * Displays aggregated player statistics from SaveSystem data.
 * Themed to match QuestCompleteScreen: panel texture, BitmapFont text,
 * button texture for BACK, slide-in animation.
 */

import type { GrimInterface, TextureHandle } from '../../engine/GrimInterface';
import type { BitmapFont } from '../../engine/BitmapFont';
import { UIElement } from '../UIElement';
import type { MenuCursor } from '../../rendering/MenuCursor';
import { StatisticsSystem, getStatisticsSystem } from '../../systems/StatisticsSystem';

/** Actions returned by update() */
export const enum StatisticsAction {
    None = 0,
    Back = 1,
}

/** Input state for the statistics screen */
export interface StatisticsInput {
    mouseX: number;
    mouseY: number;
    mouseClicked: boolean;
    cancelPressed: boolean; // ESC
}

/**
 * StatisticsScreen - displays aggregated game statistics with themed rendering
 */
export class StatisticsScreen {
    private statisticsSystem: StatisticsSystem;
    private visible: boolean = false;

    // ── Shared assets (set via setSharedAssets) ──────────────────────────────
    private panelElement: UIElement;
    private btnTex: TextureHandle = -1;
    private menuCursor: MenuCursor | null = null;
    private assetsLoaded: boolean = false;

    // ── Panel layout (matches QuestCompleteScreen / PerkSelectionScreen) ─────
    private readonly PANEL_TEX_W = 512;
    private readonly PANEL_TEX_H = 400;
    private readonly PANEL_MARGIN_LEFT = -30;
    private readonly CONTENT_LEFT = 190;
    private readonly CONTENT_TOP = 30;

    // ── Animation ───────────────────────────────────────────────────────────
    private animTimeline: number = 0;
    private readonly ANIM_DURATION = 400; // ms for panel slide-in

    // ── BACK button hit area ────────────────────────────────────────────────
    private btnBack: { x: number; y: number; w: number; h: number } | null = null;

    constructor(statisticsSystem?: StatisticsSystem) {
        this.statisticsSystem = statisticsSystem ?? getStatisticsSystem();
        this.panelElement = new UIElement(this.PANEL_TEX_W, this.PANEL_TEX_H, 0, -this.PANEL_TEX_H / 2);
        this.panelElement.startTime = 0;
        this.panelElement.endTime = this.ANIM_DURATION;
    }

    /**
     * Set shared asset handles from MainMenu (avoids duplicate texture loading).
     * Called once after MainMenu has loaded its assets.
     */
    setSharedAssets(panelElement: UIElement, buttonHandle: TextureHandle, menuCursor: MenuCursor): void {
        // Copy panel texture handle from the MainMenu's loaded panel element
        if (panelElement.isLoaded()) {
            (this.panelElement as any).textureHandle = panelElement.getHandle();
        }
        this.btnTex = buttonHandle;
        this.menuCursor = menuCursor;
        this.assetsLoaded = true;
    }

    /**
     * Show the statistics screen
     */
    show(): void {
        this.visible = true;
        this.animTimeline = 0;
        this.btnBack = null;
    }

    /**
     * Hide the statistics screen
     */
    hide(): void {
        this.visible = false;
    }

    /**
     * Check if visible
     */
    isVisible(): boolean {
        return this.visible;
    }

    /**
     * Update the statistics screen.
     * Returns StatisticsAction.Back when user clicks BACK or presses ESC.
     */
    update(dtMs: number, input: StatisticsInput): StatisticsAction {
        if (!this.visible) return StatisticsAction.None;

        // Advance slide-in animation
        if (this.animTimeline < this.ANIM_DURATION) {
            this.animTimeline = Math.min(this.animTimeline + dtMs, this.ANIM_DURATION);
        }

        // Update panel element animation
        this.panelElement.update(dtMs, false, this.animTimeline);

        // ESC → back
        if (input.cancelPressed) {
            return StatisticsAction.Back;
        }

        // BACK button click
        if (input.mouseClicked && this.btnBack && this.hitTest(input.mouseX, input.mouseY, this.btnBack)) {
            return StatisticsAction.Back;
        }

        return StatisticsAction.None;
    }

    /**
     * Render the statistics screen
     */
    render(grim: GrimInterface, font: BitmapFont, mouseX: number = 0, mouseY: number = 0): void {
        if (!this.visible) return;

        // Use the passed-in font (engine BitmapFont from Game.ts)
        const renderFont = font;

        grim.setGraphicsLayer('ui');
        grim.setRotation(0);

        const width = grim.getWidth();
        const height = grim.getHeight();

        // ── Semi-transparent dark overlay ────────────────────────────────────
        grim.setColor(0, 0, 0, 180);
        grim.drawRectFilled(0, 0, width, height);

        // ── Panel slide-in ──────────────────────────────────────────────────
        const slideT = Math.min(1.0, this.animTimeline / this.ANIM_DURATION);
        const eased = 1 - Math.cos((slideT * Math.PI) / 2);

        const pivotX = this.PANEL_MARGIN_LEFT;
        const pivotY = height / 2;

        const panelTargetX = pivotX;
        const panelOffscreenX = -this.PANEL_TEX_W - 10;
        const panelX = panelOffscreenX + (panelTargetX - panelOffscreenX) * eased;

        // ── Panel background ────────────────────────────────────────────────
        if (this.assetsLoaded) {
            grim.setBlendMode('normal');
            grim.setColor(255, 255, 255, 255);
            this.panelElement.draw(grim, panelX, pivotY);
        }

        // Content area origin (in screen coords)
        const cx = panelX + this.CONTENT_LEFT;
        const cy = pivotY + this.panelElement.offsetY + this.CONTENT_TOP + 20;

        // Content area width for centering
        const contentW = 256;

        // ── Title "STATISTICS" ──────────────────────────────────────────────
        grim.setColor(255, 200, 50, 255);
        const title = 'STATISTICS';
        const titleW = renderFont.measureText(title);
        renderFont.drawText(grim, title, cx + (contentW - titleW) / 2, cy + 8);

        // ── Stats data ──────────────────────────────────────────────────────
        const stats = this.statisticsSystem.getStats();

        const leftCol = cx + 16;
        const rightCol = cx + 150;
        let y = cy + 40;

        // Section: Games Played
        grim.setColor(200, 150, 50, 255);
        renderFont.drawText(grim, '--- GAMES PLAYED ---', leftCol, y);
        y += 22;

        grim.setColor(255, 255, 255, 255);
        renderFont.drawText(grim, `Total Games: ${stats.totalGamesPlayed}`, leftCol, y);
        y += 18;
        renderFont.drawText(grim, `Survival: ${stats.survivalGamesPlayed}`, leftCol, y);
        renderFont.drawText(grim, `Rush: ${stats.rushGamesPlayed}`, rightCol, y);
        y += 18;
        renderFont.drawText(grim, `Quest: ${stats.questGamesPlayed}`, leftCol, y);
        renderFont.drawText(grim, `Other: ${stats.otherGamesPlayed}`, rightCol, y);
        y += 28;

        // Section: Quest Progress
        grim.setColor(200, 150, 50, 255);
        renderFont.drawText(grim, '--- QUEST PROGRESS ---', leftCol, y);
        y += 22;

        grim.setColor(255, 255, 255, 255);
        renderFont.drawText(grim, `Quests Unlocked: ${stats.questsUnlocked} / ${stats.totalQuests}`, leftCol, y);
        y += 18;

        // Progress bar (sprite-layer rect for correct z-order)
        const barWidth = 160;
        const barHeight = 10;
        this.drawSpriteRect(grim, leftCol, y, barWidth, barHeight, 50, 50, 50, 255);
        const fillW = Math.floor((barWidth * stats.questProgress) / 100);
        if (fillW > 0) {
            this.drawSpriteRect(grim, leftCol, y, fillW, barHeight, 100, 200, 100, 255);
        }
        grim.setColor(255, 255, 255, 255);
        renderFont.drawText(grim, `${stats.questProgress}%`, leftCol + barWidth + 8, y);
        y += 28;

        // Section: Top Weapons
        grim.setColor(200, 150, 50, 255);
        renderFont.drawText(grim, '--- TOP WEAPONS ---', leftCol, y);
        y += 22;

        grim.setColor(255, 255, 255, 255);
        if (stats.topWeapons.length === 0) {
            grim.setColor(150, 150, 150, 255);
            renderFont.drawText(grim, 'No weapon data yet', leftCol, y);
            y += 18;
        } else {
            for (let i = 0; i < stats.topWeapons.length && i < 5; i++) {
                const weapon = stats.topWeapons[i];
                const name = StatisticsSystem.getWeaponName(weapon.weaponId);
                renderFont.drawText(grim, `${i + 1}. ${name}: ${weapon.usageCount} uses`, leftCol, y);
                y += 16;
            }
        }
        y += 10;

        // Section: Most Played Quest
        if (stats.mostPlayedQuest) {
            grim.setColor(200, 150, 50, 255);
            renderFont.drawText(grim, '--- FAVORITE QUEST ---', leftCol, y);
            y += 22;

            grim.setColor(255, 255, 255, 255);
            const q = stats.mostPlayedQuest;
            renderFont.drawText(grim, `Quest ${q.tier}-${q.index}: Played ${q.playCount} times`, leftCol, y);
            y += 22;
        }

        // ── BACK button ─────────────────────────────────────────────────────
        const buttonWidth = 128;
        const buttonHeight = 32;
        const btnX = cx + (contentW - buttonWidth) / 2;
        // Place button near bottom of panel content area
        const btnY = cy + this.PANEL_TEX_H - 120;

        this.btnBack = { x: btnX, y: btnY, w: buttonWidth, h: buttonHeight };
        const hovered = this.hitTest(mouseX, mouseY, this.btnBack);

        // Draw button texture background
        if (this.btnTex >= 0) {
            grim.bindTexture(this.btnTex);
            if (hovered) {
                grim.setColor(255, 255, 255, 255);
            } else {
                grim.setColor(180, 180, 180, 200);
            }
            grim.setUV(0, 0, 1, 1);
            grim.drawQuad(btnX, btnY, buttonWidth, buttonHeight);
        }

        // Button label
        const backLabel = 'BACK';
        const backLabelW = renderFont.measureText(backLabel);
        const textX = btnX + (buttonWidth - backLabelW) / 2;
        const textY = btnY + 10;
        if (hovered) {
            grim.setColor(230, 225, 215, 255);
        } else {
            grim.setColor(230, 225, 215, 180);
        }
        renderFont.drawText(grim, backLabel, textX, textY);

        // ── Menu cursor ─────────────────────────────────────────────────────
        if (this.menuCursor) {
            this.menuCursor.render(grim);
        }
    }

    // ── Helpers ──────────────────────────────────────────────────────────────

    private hitTest(mx: number, my: number, rect: { x: number; y: number; w: number; h: number }): boolean {
        return mx >= rect.x && mx <= rect.x + rect.w && my >= rect.y && my <= rect.y + rect.h;
    }

    /**
     * Draw a colored rect in the sprite layer (correct z-order within sprite container).
     * Uses drawQuad with unbound texture (Texture.WHITE) so rect renders above graphics layer.
     */
    private drawSpriteRect(
        grim: GrimInterface,
        x: number,
        y: number,
        w: number,
        h: number,
        r: number,
        g: number,
        b: number,
        a: number,
    ): void {
        grim.setColor(r, g, b, a);
        grim.bindTexture(-1); // unbind → Texture.WHITE
        grim.setUV(0, 0, 1, 1);
        grim.beginBatch();
        grim.drawQuad(x, y, w, h);
        grim.endBatch();
    }
}
