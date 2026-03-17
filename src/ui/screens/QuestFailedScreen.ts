/**
 * QuestFailedScreen - Quest failure results screen
 *
 * Port of quest_failed_screen_update() from C code (quest.c:80-245).
 * Shows rotating retry message, stats block, and navigation buttons.
 *
 *   Phase -1: Init — load high score table, check rank, flush input. Immediately → phase 0
 *   Phase  0: Retry message + stats block + 3 buttons
 *
 * Layout and class structure mirror QuestCompleteScreen.ts exactly.
 */

import type { GrimInterface, TextureHandle } from '../../engine/GrimInterface';
import type { BitmapFont } from '../../engine/BitmapFont';
import type { AssetManager } from '../../data/AssetManager';
import { UIElement } from '../UIElement';
import { getWeaponStats } from '../../data/WeaponData';

/** Actions returned by update() */
export const enum QuestFailedAction {
    None = 0,
    PlayAgain = 1,
    PlayAnother = 2,
    MainMenu = 3,
}

/** Input state for the quest failed screen */
export interface QuestFailedInput {
    mouseX: number;
    mouseY: number;
    mouseClicked: boolean;
    confirmPressed: boolean; // Enter / Space
    cancelPressed: boolean; // Escape
    charInput: string;
    backspacePressed: boolean;
}

/** Data passed in when the screen is shown */
export interface QuestFailedData {
    score: number;
    frags: number;
    hitPercent: number;
    weaponName: string;
    weaponId: number;
    experience: number;
    retryCount: number;
    gameTimeMs: number; // Total game time in ms
}

/** Rotating retry messages (C: quest_failed_screen_update quest.c:132-156) */
const RETRY_MESSAGES = [
    'Quest failed, try again?',
    "You didn't make it, do try again",
    'Third time no good?',
    'No luck this time, have another go',
    'Persistence will be rewarded',
    'Try one more time!',
];

export class QuestFailedScreen {
    // ── Assets ──────────────────────────────────────────────────────────────
    private panelElement: UIElement;
    private titleHandle: TextureHandle = -1;
    private wiconsTex: TextureHandle = -1;
    private btnSmallTex: TextureHandle = -1; // ui_button_64x32.jaz
    private btnMediumTex: TextureHandle = -1; // ui_button_128x32.jaz (medium button bg)

    // ── State ────────────────────────────────────────────────────────────────
    private _visible: boolean = false;
    private data: QuestFailedData | null = null;

    /**
     * Phase (mirrors C ui_screen_phase):
     *  -1 = init
     *   0 = retry message + stats + buttons
     */
    private phase: number = -1;

    // ── Animation ────────────────────────────────────────────────────────────
    private animTimeline: number = 0;
    private readonly ANIM_DURATION = 400;
    private animTimerMs: number = 0;

    // ── Button hit areas ─────────────────────────────────────────────────────
    private btnPlayAgain: { x: number; y: number; w: number; h: number } | null = null;
    private btnPlayAnother: { x: number; y: number; w: number; h: number } | null = null;
    private btnMenu: { x: number; y: number; w: number; h: number } | null = null;

    // ── Panel layout (mirrors QuestCompleteScreen) ───────────────────────────
    private readonly PANEL_TEX_W = 512;
    private readonly PANEL_TEX_H = 400;
    private readonly PANEL_MARGIN_LEFT = -30;
    private readonly CONTENT_LEFT = 190;
    private readonly CONTENT_TOP = 30;

    private readonly TITLE_TEX_W = 256;
    private readonly TITLE_TEX_H = 64;
    // (Button dimensions inline in renderPhase0 — matches play menu 128×32)

    constructor() {
        this.panelElement = new UIElement(this.PANEL_TEX_W, this.PANEL_TEX_H, 0, -this.PANEL_TEX_H / 2);
        this.panelElement.startTime = 0;
        this.panelElement.endTime = this.ANIM_DURATION;
    }

    // ─────────────────────────────────────────────────────────────────────────
    // Asset loading
    // ─────────────────────────────────────────────────────────────────────────

    async loadAssets(assetManager: AssetManager, grim: GrimInterface): Promise<void> {
        const load = async (path: string, name: string): Promise<TextureHandle> => {
            try {
                const texture = await assetManager.getTexture(path);
                if (texture) return grim.registerTexture(name, texture);
            } catch {
                /* fall through */
            }
            console.warn(`[QuestFailedScreen] Failed to load: ${path}`);
            return -1;
        };

        await this.panelElement.load('qfs_panel', 'ui/ui_menupanel.jaz', assetManager, grim);
        this.titleHandle = await load('ui/ui_textReaper.jaz', 'qfs_title');
        this.wiconsTex = await load('ui/ui_wicons.jaz', 'qfs_wicons');
        this.btnSmallTex = await load('ui/ui_button_64x32.jaz', 'qfs_btn_small');
        this.btnMediumTex = await load('ui/ui_button_128x32.jaz', 'qfs_btn_medium');
    }

    // ─────────────────────────────────────────────────────────────────────────
    // Show / Hide
    // ─────────────────────────────────────────────────────────────────────────

    show(data: QuestFailedData): void {
        this.data = data;
        this._visible = true;
        this.animTimeline = 0;
        this.phase = -1;
        this.animTimerMs = 0;

        this.btnPlayAgain = null;
        this.btnPlayAnother = null;
        this.btnMenu = null;
    }

    hide(): void {
        this._visible = false;
        this.data = null;
        this.phase = -1;
    }

    isVisible(): boolean {
        return this._visible;
    }

    setSoundSystem(_soundSystem: unknown): void {
        // Stored for future use (sound effects on button clicks)
    }

    // ─────────────────────────────────────────────────────────────────────────
    // Update
    // ─────────────────────────────────────────────────────────────────────────

    update(dtMs: number, input: QuestFailedInput): QuestFailedAction {
        if (!this._visible || !this.data) return QuestFailedAction.None;

        // Slide-in animation
        if (this.animTimeline < this.ANIM_DURATION) {
            this.animTimeline = Math.min(this.animTimeline + dtMs, this.ANIM_DURATION);
        }
        this.panelElement.update(dtMs, false, this.animTimeline);

        switch (this.phase) {
            case -1:
                return this.updateInit();
            case 0:
                return this.updateButtons(dtMs, input);
        }

        return QuestFailedAction.None;
    }

    // ── Phase -1: Init ───────────────────────────────────────────────────────
    // C: quest_failed_screen_update Phase -1 (quest.c:120-128)

    private updateInit(): QuestFailedAction {
        // Immediately transition to buttons (no name entry for quest failed)
        this.phase = 0;
        this.animTimerMs = 0;
        return QuestFailedAction.None;
    }

    // ── Phase 0: Message + Buttons ───────────────────────────────────────────
    // C: quest_failed_screen_update Phase 0 (quest.c:129-241)

    private updateButtons(dtMs: number, input: QuestFailedInput): QuestFailedAction {
        // Fade in timer (0→500ms)
        if (this.animTimerMs < 500) {
            this.animTimerMs = Math.min(500, this.animTimerMs + dtMs);
        }

        if (input.mouseClicked) {
            const mx = input.mouseX;
            const my = input.mouseY;

            if (this.btnPlayAgain && this.hitTest(mx, my, this.btnPlayAgain)) {
                return QuestFailedAction.PlayAgain;
            }
            if (this.btnPlayAnother && this.hitTest(mx, my, this.btnPlayAnother)) {
                return QuestFailedAction.PlayAnother;
            }
            if (this.btnMenu && this.hitTest(mx, my, this.btnMenu)) {
                return QuestFailedAction.MainMenu;
            }
        }

        // Escape → main menu
        if (input.cancelPressed) {
            return QuestFailedAction.MainMenu;
        }

        return QuestFailedAction.None;
    }

    private hitTest(mx: number, my: number, rect: { x: number; y: number; w: number; h: number }): boolean {
        return mx >= rect.x && mx <= rect.x + rect.w && my >= rect.y && my <= rect.y + rect.h;
    }

    // ─────────────────────────────────────────────────────────────────────────
    // Render
    // ─────────────────────────────────────────────────────────────────────────

    render(grim: GrimInterface, font: BitmapFont, mouseX: number, mouseY: number): void {
        if (!this._visible || !this.data) return;

        grim.setGraphicsLayer('ui');
        grim.setRotation(0);

        const screenH = grim.getHeight();

        // Panel slide-in
        const slideT = Math.min(1.0, this.animTimeline / this.ANIM_DURATION);
        const eased = 1 - Math.cos((slideT * Math.PI) / 2);

        const pivotX = this.PANEL_MARGIN_LEFT;
        const pivotY = screenH / 2;
        const panelTargetX = pivotX;
        const panelOffscreenX = -this.PANEL_TEX_W - 10;
        const panelX = panelOffscreenX + (panelTargetX - panelOffscreenX) * eased;

        // ── Panel background ──
        grim.setBlendMode('normal');
        grim.setColor(255, 255, 255, 255);
        this.panelElement.draw(grim, panelX, pivotY);

        const cx = panelX + this.CONTENT_LEFT;
        const cy = pivotY + this.panelElement.offsetY + this.CONTENT_TOP + 20;

        // ── Title texture ──
        const contentW = 256;
        if (this.titleHandle >= 0) {
            grim.setBlendMode('normal');
            grim.setColor(255, 255, 255, 255);
            grim.bindTexture(this.titleHandle);
            grim.setUV(0, 0, 1, 1);
            grim.beginBatch();
            const titleX = cx + (contentW - this.TITLE_TEX_W) / 2;
            grim.drawQuad(titleX, cy, this.TITLE_TEX_W, this.TITLE_TEX_H);
            grim.endBatch();
        } else {
            grim.setColor(255, 255, 255, 255);
            font.drawText(grim, 'QUEST FAILED', cx + 20, cy + 20);
        }

        if (this.phase === 0) {
            this.renderPhase0(grim, font, cx, cy, mouseX, mouseY);
        }
    }

    // ── Phase 0: Retry message + Stats + Buttons ─────────────────────────────

    private renderPhase0(
        grim: GrimInterface,
        font: BitmapFont,
        cx: number,
        cy: number,
        mouseX: number,
        mouseY: number,
    ): void {
        const data = this.data!;
        const alpha = Math.min(1.0, this.animTimerMs * 0.002);
        const a = Math.round(alpha * 255);
        const a70 = Math.round(alpha * 0.7 * 255);
        const a80 = Math.round(alpha * 0.8 * 255);

        const statsX = cx + 32;
        const contentCenterX = cx + 256 / 2;

        // ── Retry message (C: quest.c:132-157) ──
        // C: local_14 = fVar1 + 70 + 16 = panel_y + 86
        let curY = cy + 56 + 20; // after title
        const msgIndex = Math.min(data.retryCount, RETRY_MESSAGES.length - 1);
        const msg = RETRY_MESSAGES[msgIndex] || RETRY_MESSAGES[0];
        grim.setColor(255, 255, 255, a);
        font.drawText(grim, msg, statsX - 2, curY);
        curY += 16;

        // ── Stats block (no Rank for QuestFailed — C line 2165) ──
        curY += 6;
        const stX = contentCenterX - (96 + 80) / 2;
        const stY = curY;

        // Score
        const scoreCenterX = stX + 32;
        grim.setColor(230, 230, 230, a80);
        const scoreLabelW = font.measureText('Score');
        font.drawText(grim, 'Score', scoreCenterX - scoreLabelW / 2, stY);

        grim.setColor(230, 230, 255, a);
        // C: ui_core.c:2151 — quest modes use "%.2f secs" format (score_ms * 0.001)
        const scoreStr = (data.score * 0.001).toFixed(2) + ' secs';
        const scoreValW = font.measureText(scoreStr);
        font.drawText(grim, scoreStr, scoreCenterX - scoreValW / 2, stY + 15);

        // NO Rank display for Quest Failed (C: game_state_id != 0xc check at ui_core.c:2165)

        // Vertical separator
        const sepX = stX + 96 - 16;
        grim.setBlendMode('normal');
        grim.setColor(255, 255, 255, a);
        this.drawSpriteRect(grim, sepX, stY, 2, 48);

        // Game Time column
        const timeX = stX + 96;
        grim.setColor(230, 230, 230, a80);
        font.drawText(grim, 'Game time', timeX + 6, stY);

        grim.setColor(230, 230, 230, a80);
        const totalSec = Math.floor(data.gameTimeMs / 1000);
        const mins = Math.floor(totalSec / 60);
        const secs = totalSec % 60;
        const timeStr = secs < 10 ? `${mins}:0${secs}` : `${mins}:${secs}`;
        font.drawText(grim, timeStr, timeX + 40, stY + 19);

        // Horizontal weapon bar
        const weapBarY = stY + 52;
        grim.setBlendMode('normal');
        grim.setColor(255, 255, 255, a);
        this.drawSpriteRect(grim, stX - 16, weapBarY, 192, 2);
        const weapY = weapBarY + 4;

        // Weapon icon (64×32)
        const weapX = stX;
        if (this.wiconsTex >= 0 && data.weaponId !== undefined) {
            const weaponStats = getWeaponStats(data.weaponId);
            grim.setColor(255, 255, 255, a);
            grim.bindTexture(this.wiconsTex);
            grim.setSubRect(8, 2, 1, weaponStats.hudIconId << 1);
            grim.beginBatch();
            grim.drawQuad(weapX, weapY, 64, 32);
            grim.endBatch();
            grim.setUV(0, 0, 1, 1);
        }

        // Weapon name centered under icon
        if (data.weaponName) {
            grim.setColor(230, 230, 230, a70);
            const nameW = font.measureText(data.weaponName);
            let nameX = 0x20 - nameW / 2 + weapX;
            if (nameX < 0) nameX = 0;
            font.drawText(grim, data.weaponName, nameX, weapY + 32);
        }

        // Frags + Hit %
        const fragX = weapX + 110;
        grim.setColor(230, 230, 230, a80);
        font.drawText(grim, 'Frags: ' + data.frags, fragX, weapY + 1);
        font.drawText(grim, 'Hit %: ' + data.hitPercent + '%', fragX, weapY + 15);

        // Bottom weapon bar
        const bottomBarY = weapY + 48;
        grim.setBlendMode('normal');
        grim.setColor(255, 255, 255, a);
        this.drawSpriteRect(grim, stX - 16, bottomBarY, 192, 2);

        // ── 3 Buttons (styled like play menu) ──
        curY = bottomBarY + 6;
        const btnX = statsX;
        const buttonWidth = 128;
        const buttonHeight = 32;
        const buttonSpacing = 32;

        this.btnPlayAgain = { x: btnX, y: curY, w: buttonWidth, h: buttonHeight };
        curY += buttonSpacing;
        this.btnPlayAnother = { x: btnX, y: curY, w: buttonWidth, h: buttonHeight };
        curY += buttonSpacing;
        this.btnMenu = { x: btnX, y: curY, w: buttonWidth, h: buttonHeight };

        const buttons = [
            { rect: this.btnPlayAgain, label: 'Play Again' },
            { rect: this.btnPlayAnother, label: 'Play Another' },
            { rect: this.btnMenu, label: 'Main Menu' },
        ];

        const btnHandle = this.btnMediumTex >= 0 ? this.btnMediumTex : this.btnSmallTex;

        for (const btn of buttons) {
            const hovered = this.hitTest(mouseX, mouseY, btn.rect);

            // Draw button texture background
            if (btnHandle >= 0) {
                grim.bindTexture(btnHandle);
                if (hovered) {
                    grim.setColor(255, 255, 255, Math.round(alpha * 255));
                } else {
                    grim.setColor(180, 180, 180, Math.round(alpha * 0.8 * 255));
                }
                grim.setUV(0, 0, 1, 1);
                grim.drawQuad(btn.rect.x, btn.rect.y, buttonWidth, buttonHeight);
            }

            // Draw centered text label
            const textW = font.measureText(btn.label);
            const textX = btn.rect.x + (buttonWidth - textW) / 2;
            const textY = btn.rect.y + 10;
            if (hovered) {
                grim.setColor(230, 225, 215, Math.round(alpha * 255));
            } else {
                grim.setColor(230, 225, 215, Math.round(alpha * 0.7 * 255));
            }
            font.drawText(grim, btn.label, textX, textY);
        }
    }

    // ─────────────────────────────────────────────────────────────────────────
    // Helpers
    // ─────────────────────────────────────────────────────────────────────────

    private drawSpriteRect(grim: GrimInterface, x: number, y: number, w: number, h: number): void {
        grim.bindTexture(-1);
        grim.setUV(0, 0, 1, 1);
        grim.beginBatch();
        grim.drawQuad(x, y, w, h);
        grim.endBatch();
    }
}
