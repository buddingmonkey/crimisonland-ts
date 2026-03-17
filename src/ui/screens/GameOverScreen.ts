/**
 * GameOverScreen - Game Over results screen (Survival / Rush death)
 *
 * Port of game_over_screen_update() from C code (gameplay.c:670-980).
 * Shows high-score name entry (if qualifying) then stats + navigation buttons.
 *
 *   Phase -1: Init — load high score table, check rank, route to Phase 0 or 1
 *   Phase  0: "State your name trooper!" + text input + Ok button + rich stats
 *   Phase  1: Stats block + 3 buttons: Play Again, High Scores, Main Menu
 *
 * Layout and class structure mirror QuestCompleteScreen.ts exactly.
 */

import type { GrimInterface, TextureHandle } from '../../engine/GrimInterface';
import type { BitmapFont } from '../../engine/BitmapFont';
import type { AssetManager } from '../../data/AssetManager';
import { UIElement } from '../UIElement';
import { getWeaponStats } from '../../data/WeaponData';
import type { SoundSystem } from '../../audio/SoundSystem';
import { SoundId } from '../../audio/SoundId';

/** Actions returned by update() */
export const enum GameOverAction {
    None = 0,
    PlayAgain = 1,
    HighScores = 2,
    MainMenu = 3,
}

/** Input state for the game over screen */
export interface GameOverInput {
    mouseX: number;
    mouseY: number;
    mouseClicked: boolean;
    confirmPressed: boolean; // Enter / Space
    cancelPressed: boolean; // Escape
    charInput: string; // Characters typed this frame
    backspacePressed: boolean;
}

/** Data passed in when the screen is shown */
export interface GameOverData {
    score: number; // XP or survival time in ms (depending on mode)
    scoreDisplayMode: 'xp' | 'time'; // Quest uses XP, Survival/Rush uses time
    frags: number;
    hitPercent: number;
    weaponName: string;
    weaponId: number;
    experience: number;
    gameMode: number; // For saving to high score record
    rank: number; // High score rank (0-based). >= 100 = unranked
    gameTimeMs: number; // Total game time in ms
}

export class GameOverScreen {
    // ── Assets ──────────────────────────────────────────────────────────────
    private panelElement: UIElement;
    private titleHandle: TextureHandle = -1; // ui_textReaper.jaz
    private wiconsTex: TextureHandle = -1; // ui_wicons.jaz (weapon icon atlas 8×2)
    private btnSmallTex: TextureHandle = -1; // ui_button_64x32.jaz (small button bg)
    private soundSystem: SoundSystem | null = null;

    // ── State ────────────────────────────────────────────────────────────────
    private _visible: boolean = false;
    private data: GameOverData | null = null;

    /**
     * Phase (mirrors C ui_screen_phase):
     *  -1 = init (load high score, check rank, route)
     *   0 = name entry active + rich stats
     *   1 = buttons visible + stats
     */
    private phase: number = -1;

    // ── Name entry state ─────────────────────────────────────────────────────
    private playerName: string = '';
    private readonly MAX_NAME_LENGTH = 20; // C: highscore_max_name_length = 0x14

    // ── Animation ────────────────────────────────────────────────────────────
    private animTimeline: number = 0;
    private readonly ANIM_DURATION = 400; // ms for panel slide-in
    private animTimerMs: number = 0; // fade-in timer

    // ── Button hit areas ─────────────────────────────────────────────────────
    private btnPlayAgain: { x: number; y: number; w: number; h: number } | null = null;
    private btnHighScores: { x: number; y: number; w: number; h: number } | null = null;
    private btnMenu: { x: number; y: number; w: number; h: number } | null = null;
    private btnOk: { x: number; y: number; w: number; h: number } | null = null;

    // ── Panel layout (mirrors QuestCompleteScreen) ───────────────────────────
    private readonly PANEL_TEX_W = 512;
    private readonly PANEL_TEX_H = 400;
    private readonly PANEL_MARGIN_LEFT = -30;
    private readonly CONTENT_LEFT = 190;
    private readonly CONTENT_TOP = 30;

    // ── C code layout constants ──────────────────────────────────────────────
    private readonly TITLE_TEX_W = 256;
    private readonly TITLE_TEX_H = 64;
    private readonly BTN_W = 140;
    private readonly BTN_H = 22;
    private readonly BTN_GAP = 32; // C: 32px between buttons

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
            console.warn(`[GameOverScreen] Failed to load: ${path}`);
            return -1;
        };

        await this.panelElement.load('gos_panel', 'ui/ui_menupanel.jaz', assetManager, grim);
        this.titleHandle = await load('ui/ui_textReaper.jaz', 'gos_title');
        this.wiconsTex = await load('ui/ui_wicons.jaz', 'gos_wicons');
        this.btnSmallTex = await load('ui/ui_button_64x32.jaz', 'gos_btn_small');
    }

    // ─────────────────────────────────────────────────────────────────────────
    // Show / Hide
    // ─────────────────────────────────────────────────────────────────────────

    show(data: GameOverData): void {
        this.data = data;
        this._visible = true;
        this.animTimeline = 0;
        this.phase = -1;
        this.animTimerMs = 0;
        this.playerName = '';

        this.btnPlayAgain = null;
        this.btnHighScores = null;
        this.btnMenu = null;
        this.btnOk = null;
    }

    hide(): void {
        this._visible = false;
        this.data = null;
        this.phase = -1;
    }

    isVisible(): boolean {
        return this._visible;
    }

    setSoundSystem(soundSystem: SoundSystem): void {
        this.soundSystem = soundSystem;
    }

    // ─────────────────────────────────────────────────────────────────────────
    // Update
    // ─────────────────────────────────────────────────────────────────────────

    update(dtMs: number, input: GameOverInput): GameOverAction {
        if (!this._visible || !this.data) return GameOverAction.None;

        // Slide-in animation
        if (this.animTimeline < this.ANIM_DURATION) {
            this.animTimeline = Math.min(this.animTimeline + dtMs, this.ANIM_DURATION);
        }
        this.panelElement.update(dtMs, false, this.animTimeline);

        switch (this.phase) {
            case -1:
                return this.updateInit();
            case 0:
                return this.updateNameEntry(dtMs, input);
            case 1:
                return this.updateButtons(dtMs, input);
        }

        return GameOverAction.None;
    }

    // ── Phase -1: Init ───────────────────────────────────────────────────────
    // C: game_over_screen_update Phase -1 (gameplay.c:743-877)
    // Load high score table, check rank. Immediately route.

    private updateInit(): GameOverAction {
        const data = this.data!;
        if (data.rank < 100) {
            // Qualifies for high score → name entry
            this.phase = 0;
            this.animTimerMs = 0;
        } else {
            // No high score → skip to buttons
            this.phase = 1;
            this.animTimerMs = 0;
        }
        return GameOverAction.None;
    }

    // ── Phase 0: Name entry ──────────────────────────────────────────────────
    // C: game_over_screen_update Phase 0 (gameplay.c:786-873)

    private updateNameEntry(dtMs: number, input: GameOverInput): GameOverAction {
        // Fade in timer (0→500ms)
        if (this.animTimerMs < 500) {
            this.animTimerMs = Math.min(500, this.animTimerMs + dtMs);
        }

        // Append typed characters
        for (const ch of input.charInput) {
            if (this.playerName.length < this.MAX_NAME_LENGTH) {
                this.playerName += ch;
            }
        }

        // Backspace
        if (input.backspacePressed && this.playerName.length > 0) {
            this.playerName = this.playerName.slice(0, -1);
        }

        // Check Ok button click
        if (input.mouseClicked && this.btnOk && this.hitTest(input.mouseX, input.mouseY, this.btnOk)) {
            return this.submitName();
        }

        // Confirm name with Enter
        if (input.confirmPressed) {
            return this.submitName();
        }

        return GameOverAction.None;
    }

    private submitName(): GameOverAction {
        if (this.playerName.trim().length > 0) {
            // Valid name → save and advance to buttons
            this.soundSystem?.play(SoundId.UI_TYPE_ENTER);
            this.phase = 1;
            this.animTimerMs = 0;
        } else {
            // Empty/whitespace → reject
            this.soundSystem?.play(SoundId.SHOCK_HIT_01);
        }
        return GameOverAction.None;
    }

    // ── Phase 1: Buttons ─────────────────────────────────────────────────────
    // C: game_over_screen_update Phase 1 (gameplay.c:882-976)

    private updateButtons(dtMs: number, input: GameOverInput): GameOverAction {
        // Fade in timer (0→500ms)
        if (this.animTimerMs < 500) {
            this.animTimerMs = Math.min(500, this.animTimerMs + dtMs);
        }

        if (input.mouseClicked) {
            const mx = input.mouseX;
            const my = input.mouseY;

            if (this.btnPlayAgain && this.hitTest(mx, my, this.btnPlayAgain)) {
                return GameOverAction.PlayAgain;
            }
            if (this.btnHighScores && this.hitTest(mx, my, this.btnHighScores)) {
                return GameOverAction.HighScores;
            }
            if (this.btnMenu && this.hitTest(mx, my, this.btnMenu)) {
                return GameOverAction.MainMenu;
            }
        }

        // Escape → main menu
        if (input.cancelPressed) {
            return GameOverAction.MainMenu;
        }

        return GameOverAction.None;
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

        // Panel slide-in progress (0→1)
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

        // Content area origin
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
            font.drawText(grim, 'GAME OVER', cx + 20, cy + 20);
        }

        // Render phase-specific content
        if (this.phase === 0) {
            this.renderNameEntry(grim, font, cx, cy, mouseX, mouseY);
        } else if (this.phase === 1) {
            this.renderButtons(grim, font, cx, cy, mouseX, mouseY);
        }
    }

    // ── Phase 0: Name entry + rich stats ─────────────────────────────────────
    // C: game_over_screen_update Phase 0 (gameplay.c:786-873)
    // + ui_text_input_render (ui_core.c:2066-2313)

    private renderNameEntry(
        grim: GrimInterface,
        font: BitmapFont,
        cx: number,
        cy: number,
        mouseX: number,
        mouseY: number,
    ): void {
        const alpha = Math.min(1.0, this.animTimerMs * 0.002);
        const a = Math.round(alpha * 255);
        const a70 = Math.round(alpha * 0.7 * 255);
        const a80 = Math.round(alpha * 0.8 * 255);

        const contentW = 256;
        const statsX = cx + 32;
        const contentCenterX = cx + contentW / 2;

        // C: local_c after title (56px), Phase adds 22
        let curY = cy + 56 + 22;

        // ── "State your name trooper!" ──
        grim.setColor(255, 255, 255, a);
        const subtitleText = 'State your name trooper!';
        const subtitleW = font.measureText(subtitleText);
        font.drawText(grim, subtitleText, contentCenterX - subtitleW / 2, curY);
        curY += 32; // C: local_c += 32

        // ── Name input box ──
        // C: Width = highscore_input_width = 0xa6 = 166
        const inputX = statsX - 10;
        const inputY = curY;
        const inputW = 166; // C: 0xa6
        const inputH = 18;

        // White outline box
        grim.setBlendMode('normal');
        grim.setColor(255, 255, 255, a);
        this.drawSpriteRect(grim, inputX, inputY, inputW, 1);
        this.drawSpriteRect(grim, inputX, inputY + inputH, inputW, 1);
        this.drawSpriteRect(grim, inputX, inputY, 1, inputH + 1);
        this.drawSpriteRect(grim, inputX + inputW, inputY, 1, inputH + 1);

        // Black fill inside
        grim.setColor(0, 0, 0, a);
        this.drawSpriteRect(grim, inputX + 1, inputY + 1, inputW - 2, inputH - 1);

        // Player name text
        grim.setColor(255, 255, 255, a80);
        const cursor = Math.floor(Date.now() / 500) % 2 === 0 ? '|' : '';
        font.drawText(grim, this.playerName + cursor, inputX + 4, inputY + 2);

        // ── "Ok" button ──
        // C: ui_button_update at (local_10 + 170, local_c - 8)
        const okBtnX = inputX + inputW + 4;
        const okBtnY = inputY - 8;
        const okBtnW = 82;
        const okBtnH = 32;

        if (this.btnSmallTex >= 0) {
            grim.setColor(255, 255, 255, a);
            grim.bindTexture(this.btnSmallTex);
            grim.setUV(0, 0, 1, 1);
            grim.beginBatch();
            grim.drawQuad(okBtnX, okBtnY, okBtnW, okBtnH);
            grim.endBatch();
        }

        this.btnOk = { x: okBtnX, y: okBtnY + 2, w: okBtnW, h: 28 };
        const okHovered = this.hitTest(mouseX, mouseY, this.btnOk);
        const okTextAlpha = okHovered ? a : a70;
        grim.setColor(255, 255, 255, okTextAlpha);
        const okTextW = font.measureText('Ok');
        font.drawText(grim, 'Ok', okBtnX + okBtnW * 0.5 - okTextW / 2 + 1, okBtnY + 10);

        // ── Rich stats display ──
        curY += 30;
        this.renderStatsBlock(grim, font, contentCenterX, curY + 16, a, a70, a80);
    }

    // ── Phase 1: Stats + buttons ─────────────────────────────────────────────

    private renderButtons(
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
        const a80 = Math.round(alpha * 0.8 * 255);

        const statsX = cx + 32;
        const contentCenterX = cx + 256 / 2;

        let curY = cy + 56 + 6;

        // ── High score info ──
        if (data.rank >= 100) {
            grim.setColor(255, 255, 255, a);
            font.drawText(grim, 'Score too low for top 100', statsX + 8, curY + 6);
            curY += 6;
        }

        // ── Stats block ──
        const stY = curY + 16;
        this.renderStatsBlock(grim, font, contentCenterX, stY, a, Math.round(alpha * 0.7 * 255), a80);

        // Advance past stats block (score + sep + weapon + frags = ~110px)
        curY = stY + 110;

        // ── 3 Buttons (C: 32px apart) ──
        const btnX = statsX;
        this.btnPlayAgain = { x: btnX, y: curY, w: this.BTN_W, h: this.BTN_H };
        curY += this.BTN_GAP;
        this.btnHighScores = { x: btnX, y: curY, w: this.BTN_W, h: this.BTN_H };
        curY += this.BTN_GAP;
        this.btnMenu = { x: btnX, y: curY, w: this.BTN_W, h: this.BTN_H };

        const buttons = [
            { rect: this.btnPlayAgain, label: 'Play Again' },
            { rect: this.btnHighScores, label: 'High scores' },
            { rect: this.btnMenu, label: 'Main Menu' },
        ];

        for (const btn of buttons) {
            const hovered = this.hitTest(mouseX, mouseY, btn.rect);
            const textA = Math.round(alpha * 255);
            if (hovered) {
                grim.setColor(255, 255, 255, textA);
            } else {
                grim.setColor(200, 200, 200, Math.round(alpha * 0.8 * 255));
            }
            font.drawText(grim, btn.label, btn.rect.x, btn.rect.y + 4);

            if (hovered) {
                grim.setBlendMode('normal');
                grim.setColor(255, 255, 255, Math.round(alpha * 0.5 * 255));
                grim.drawRectFilled(btn.rect.x, btn.rect.y + btn.rect.h - 2, btn.rect.w, 1);
            }
        }
    }

    // ── Shared stats block ───────────────────────────────────────────────────
    // C: ui_text_input_render (ui_core.c:2066-2313) — shared by GameOver, QuestFailed, QuestComplete

    private renderStatsBlock(
        grim: GrimInterface,
        font: BitmapFont,
        contentCenterX: number,
        stY: number,
        a: number,
        a70: number,
        a80: number,
    ): void {
        const data = this.data!;
        const blockW = 96 + 80;
        const stX = contentCenterX - blockW / 2;

        // ── Score column ──
        const scoreCenterX = stX + 32;
        grim.setColor(230, 230, 230, a80);
        const scoreLabelW = font.measureText('Score');
        font.drawText(grim, 'Score', scoreCenterX - scoreLabelW / 2, stY);

        grim.setColor(230, 230, 255, a);
        let scoreStr: string;
        if (data.scoreDisplayMode === 'time') {
            scoreStr = (data.score * 0.001).toFixed(2) + ' secs';
        } else {
            scoreStr = '' + data.score;
        }
        const scoreValW = font.measureText(scoreStr);
        font.drawText(grim, scoreStr, scoreCenterX - scoreValW / 2, stY + 15);

        // Rank (only if rank < 100)
        if (data.rank < 100) {
            grim.setColor(230, 230, 230, a80);
            const rankStr = 'Rank: ' + this.formatOrdinal(data.rank + 1);
            const rankW = font.measureText(rankStr);
            font.drawText(grim, rankStr, scoreCenterX - rankW / 2, stY + 30);
        }

        // ── Vertical separator ──
        const sepX = stX + 96 - 16;
        grim.setBlendMode('normal');
        grim.setColor(255, 255, 255, a);
        this.drawSpriteRect(grim, sepX, stY, 2, 48);

        // ── Game Time column ──
        const timeX = stX + 96;
        grim.setColor(230, 230, 230, a80);
        font.drawText(grim, 'Game time', timeX + 6, stY);

        grim.setColor(230, 230, 230, a80);
        const totalSec = Math.floor(data.gameTimeMs / 1000);
        const mins = Math.floor(totalSec / 60);
        const secs = totalSec % 60;
        const timeStr = secs < 10 ? `${mins}:0${secs}` : `${mins}:${secs}`;
        font.drawText(grim, timeStr, timeX + 40, stY + 19);

        // ── Horizontal weapon bar ──
        const weapBarY = stY + 52;
        grim.setBlendMode('normal');
        grim.setColor(255, 255, 255, a);
        this.drawSpriteRect(grim, stX - 16, weapBarY, 192, 2);
        const weapY = weapBarY + 4;

        // ── Weapon icon (64×32) ──
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

        // ── Bottom weapon bar ──
        const bottomBarY = weapY + 48;
        grim.setBlendMode('normal');
        grim.setColor(255, 255, 255, a);
        this.drawSpriteRect(grim, stX - 16, bottomBarY, 192, 2);
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

    private formatOrdinal(n: number): string {
        const suffix = ['th', 'st', 'nd', 'rd'];
        const v = n % 100;
        return n + (suffix[(v - 20) % 10] || suffix[v] || suffix[0]);
    }

    getPlayerName(): string {
        return this.playerName.trim();
    }
}
