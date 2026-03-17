/**
 * LeaderboardScreen.ts - High score display UI
 *
 * Displays high score table with filtering by game mode.
 * Themed to match StatisticsScreen / QuestCompleteScreen:
 * panel texture, BitmapFont text, button textures, slide-in animation.
 */

import type { GrimInterface, TextureHandle } from '../../engine/GrimInterface';
import type { BitmapFont } from '../../engine/BitmapFont';
import { UIElement } from '../UIElement';
import type { MenuCursor } from '../../rendering/MenuCursor';
import { HighScoreSystem, GameMode, getHighScoreSystem } from '../../systems/HighScoreSystem';
import { StatisticsSystem } from '../../systems/StatisticsSystem';

/** Actions returned by update() */
export const enum LeaderboardAction {
    None = 0,
    Back = 1,
}

/** Input state for the leaderboard screen */
export interface LeaderboardInput {
    mouseX: number;
    mouseY: number;
    mouseClicked: boolean;
    cancelPressed: boolean; // ESC
    tabPressed: boolean; // TAB to cycle modes
}

/**
 * LeaderboardScreen - displays high score table with themed rendering
 */
export class LeaderboardScreen {
    private highScoreSystem: HighScoreSystem;
    private visible: boolean = false;
    private selectedMode: GameMode = GameMode.Survival; // Default to Survival

    // ── Shared assets (set via setSharedAssets) ──────────────────────────────
    private panelElement: UIElement;
    private btnTex: TextureHandle = -1;
    private menuCursor: MenuCursor | null = null;
    private assetsLoaded: boolean = false;

    // ── Panel layout (matches StatisticsScreen / QuestCompleteScreen) ────────
    private readonly PANEL_TEX_W = 512;
    private readonly PANEL_TEX_H = 400;
    private readonly PANEL_MARGIN_LEFT = -30;
    private readonly CONTENT_LEFT = 190;
    private readonly CONTENT_TOP = 30;

    // ── Animation ───────────────────────────────────────────────────────────
    private animTimeline: number = 0;
    private readonly ANIM_DURATION = 400; // ms for panel slide-in

    // ── Button hit areas ────────────────────────────────────────────────────
    private btnBack: { x: number; y: number; w: number; h: number } | null = null;
    private btnSurvival: { x: number; y: number; w: number; h: number } | null = null;
    private btnRush: { x: number; y: number; w: number; h: number } | null = null;
    private btnQuest: { x: number; y: number; w: number; h: number } | null = null;

    constructor(highScoreSystem?: HighScoreSystem) {
        this.highScoreSystem = highScoreSystem ?? getHighScoreSystem();
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
     * Show the leaderboard screen
     */
    show(): void {
        this.visible = true;
        this.selectedMode = GameMode.Survival;
        this.animTimeline = 0;
        this.btnBack = null;
        this.btnSurvival = null;
        this.btnRush = null;
        this.btnQuest = null;
    }

    /**
     * Hide the leaderboard screen
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
     * Cycle through game mode filters (for TAB key support)
     */
    cycleMode(): void {
        if (this.selectedMode === GameMode.Survival) {
            this.selectedMode = GameMode.Rush;
        } else if (this.selectedMode === GameMode.Rush) {
            this.selectedMode = GameMode.Quest;
        } else {
            this.selectedMode = GameMode.Survival;
        }
    }

    /**
     * Set mode directly (for click support)
     */
    setMode(mode: GameMode): void {
        this.selectedMode = mode;
    }

    /**
     * Get current mode name for display
     */
    private getModeName(mode: GameMode): string {
        switch (mode) {
            case GameMode.Survival:
                return 'SURVIVAL';
            case GameMode.Rush:
                return 'RUSH';
            case GameMode.Quest:
                return 'QUEST';
            default:
                return 'SURVIVAL';
        }
    }

    /**
     * Update the leaderboard screen.
     * Returns LeaderboardAction.Back when user clicks BACK or presses ESC.
     */
    update(dtMs: number, input: LeaderboardInput): LeaderboardAction {
        if (!this.visible) return LeaderboardAction.None;

        // Advance slide-in animation
        if (this.animTimeline < this.ANIM_DURATION) {
            this.animTimeline = Math.min(this.animTimeline + dtMs, this.ANIM_DURATION);
        }

        // Update panel element animation
        this.panelElement.update(dtMs, false, this.animTimeline);

        // ESC → back
        if (input.cancelPressed) {
            return LeaderboardAction.Back;
        }

        // TAB → cycle modes
        if (input.tabPressed) {
            this.cycleMode();
        }

        // BACK button click
        if (input.mouseClicked && this.btnBack && this.hitTest(input.mouseX, input.mouseY, this.btnBack)) {
            return LeaderboardAction.Back;
        }

        // Mode tab clicks
        if (input.mouseClicked) {
            if (this.btnSurvival && this.hitTest(input.mouseX, input.mouseY, this.btnSurvival)) {
                this.selectedMode = GameMode.Survival;
            }
            if (this.btnRush && this.hitTest(input.mouseX, input.mouseY, this.btnRush)) {
                this.selectedMode = GameMode.Rush;
            }
            if (this.btnQuest && this.hitTest(input.mouseX, input.mouseY, this.btnQuest)) {
                this.selectedMode = GameMode.Quest;
            }
        }

        return LeaderboardAction.None;
    }

    /**
     * Render the leaderboard screen
     */
    render(grim: GrimInterface, font: BitmapFont, mouseX: number = 0, mouseY: number = 0): void {
        if (!this.visible) return;

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

        // ── Title "HIGH SCORES" ─────────────────────────────────────────────
        grim.setColor(255, 200, 50, 255);
        const title = 'HIGH SCORES';
        const titleW = renderFont.measureText(title);
        renderFont.drawText(grim, title, cx + (contentW - titleW) / 2, cy + 8);

        // ── Mode tab buttons ────────────────────────────────────────────────
        const tabY = cy + 32;
        const tabW = 72;
        const tabH = 24;
        const tabGap = 8;
        const totalTabW = tabW * 3 + tabGap * 2;
        const tabStartX = cx + (contentW - totalTabW) / 2;

        const modes: GameMode[] = [GameMode.Survival, GameMode.Rush, GameMode.Quest];
        const tabRects: Array<{ x: number; y: number; w: number; h: number }> = [];

        for (let i = 0; i < modes.length; i++) {
            const mode = modes[i];
            const tabX = tabStartX + i * (tabW + tabGap);
            const rect = { x: tabX, y: tabY, w: tabW, h: tabH };
            tabRects.push(rect);
            const isActive = this.selectedMode === mode;
            const isHovered = this.hitTest(mouseX, mouseY, rect);

            // Draw tab button background
            if (this.btnTex >= 0) {
                grim.bindTexture(this.btnTex);
                if (isActive) {
                    grim.setColor(255, 255, 255, 255);
                } else if (isHovered) {
                    grim.setColor(200, 200, 200, 220);
                } else {
                    grim.setColor(140, 140, 140, 180);
                }
                grim.setUV(0, 0, 1, 1);
                grim.drawQuad(tabX, tabY, tabW, tabH);
            }

            // Tab label
            const label = this.getModeName(mode);
            const labelW = renderFont.measureText(label);
            if (isActive) {
                grim.setColor(255, 230, 180, 255);
            } else if (isHovered) {
                grim.setColor(230, 225, 215, 220);
            } else {
                grim.setColor(180, 180, 180, 160);
            }
            renderFont.drawText(grim, label, tabX + (tabW - labelW) / 2, tabY + 7);
        }

        // Store hit areas for mode tabs
        this.btnSurvival = tabRects[0];
        this.btnRush = tabRects[1];
        this.btnQuest = tabRects[2];

        // ── Column headers ──────────────────────────────────────────────────
        const headerY = tabY + tabH + 14;
        grim.setColor(200, 150, 50, 255);
        renderFont.drawText(grim, '#', cx + 4, headerY);
        renderFont.drawText(grim, 'NAME', cx + 24, headerY);
        renderFont.drawText(grim, 'SCORE', cx + 118, headerY);
        renderFont.drawText(grim, 'TIME', cx + 178, headerY);
        renderFont.drawText(grim, 'KILLS', cx + 228, headerY);

        // ── Separator line ──────────────────────────────────────────────────
        const sepY = headerY + 14;
        grim.setColor(200, 150, 50, 120);
        grim.bindTexture(-1);
        grim.setUV(0, 0, 1, 1);
        grim.beginBatch();
        grim.drawQuad(cx + 2, sepY, contentW - 4, 1);
        grim.endBatch();

        // ── Score records ───────────────────────────────────────────────────
        const records = this.highScoreSystem.getRecords(this.selectedMode, 10);
        let y = sepY + 6;
        const rowH = 18;

        for (let i = 0; i < records.length; i++) {
            const record = records[i];
            const rank = i + 1;

            // Alternating row background (subtle)
            if (i % 2 === 0) {
                grim.setColor(255, 255, 255, 15);
                grim.bindTexture(-1);
                grim.setUV(0, 0, 1, 1);
                grim.beginBatch();
                grim.drawQuad(cx + 2, y - 1, contentW - 4, rowH);
                grim.endBatch();
            }

            // Gold/Silver/Bronze for top 3
            if (rank === 1) grim.setColor(255, 215, 0, 255);
            else if (rank === 2) grim.setColor(192, 192, 192, 255);
            else if (rank === 3) grim.setColor(205, 127, 50, 255);
            else grim.setColor(220, 220, 220, 200);

            renderFont.drawText(grim, `${rank}.`, cx + 4, y);
            renderFont.drawText(grim, record.playerName.substring(0, 10), cx + 24, y);
            renderFont.drawText(grim, `${record.scoreXp}`, cx + 118, y);
            renderFont.drawText(grim, StatisticsSystem.formatTime(record.survivalElapsedMs), cx + 178, y);
            renderFont.drawText(grim, `${record.creatureKillCount}`, cx + 228, y);

            y += rowH;
        }

        // Empty message if no records
        if (records.length === 0) {
            grim.setColor(150, 150, 150, 200);
            const emptyText = 'No high scores yet';
            const emptyW = renderFont.measureText(emptyText);
            renderFont.drawText(grim, emptyText, cx + (contentW - emptyW) / 2, sepY + 60);
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
}
