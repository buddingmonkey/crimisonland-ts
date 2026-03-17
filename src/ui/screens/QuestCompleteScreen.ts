/**
 * QuestCompleteScreen - Quest results screen
 *
 * Port of quest_results_screen_update() from C code (quest.c:249-812).
 * Shows animated statistics after completing a quest:
 *   Phase -1: Score animation (Base Time → Damage Taken → Perk Bonus → Final Time)
 *   Phase  0: High-score check → if rank > 99 skip to Phase 2, else Phase 1
 *   Phase  1: "State your name trooper!" + text input + Ok + rich stats
 *             (Score, Rank, Weapon icon, Frags, Hit%)
 *   Phase  2: Score table + unlock info + 4 buttons
 *
 * Layout mirrors the C code panel position and stat rows.
 */

import type { GrimInterface, TextureHandle } from '../../engine/GrimInterface';
import type { BitmapFont } from '../../engine/BitmapFont';
import type { AssetManager } from '../../data/AssetManager';
import { UIElement } from '../UIElement';
import { getWeaponStats } from '../../data/WeaponData';
import type { SoundSystem } from '../../audio/SoundSystem';
import { SoundId } from '../../audio/SoundId';

/** Actions returned by update() */
export const enum QuestCompleteAction {
    None = 0,
    PlayNext = 1,
    Replay = 2,
    MainMenu = 3,
    HighScores = 4,
    ShowEndNote = 5,
}

/** Input state for the quest complete screen */
export interface QuestCompleteInput {
    mouseX: number;
    mouseY: number;
    mouseClicked: boolean;
    confirmPressed: boolean; // Space / Enter
    cancelPressed: boolean; // Escape
    // Name entry
    charInput: string; // Characters typed this frame
    backspacePressed: boolean;
}

/**
 * Quest results data passed in when the screen is shown.
 */
export interface QuestResultsData {
    /** Total quest timeline in ms (= Base Time before deductions) */
    baseTimeMs: number;
    /** Life bonus in ms (remaining health * 1000, subtracted from base time) */
    lifeBonusMs: number;
    /** Number of unpicked perks at quest end */
    unpickedPerks: number;
    /** Final score in ms (baseTime - damagePenalty - perkBonus) */
    finalTimeMs: number;
    /** Quest name for display */
    questName: string;
    /** Whether this score qualifies for the high score table */
    isHighScore: boolean;
    /** Name of unlocked weapon, if any */
    unlockWeaponName?: string;
    /** Name of unlocked perk, if any */
    unlockPerkName?: string;

    // ── Rich stats for Phase 1/2 display ──
    /** Final score value in seconds (for display) */
    scoreSeconds?: number;
    /** High score rank (1-based). 0 or undefined = unranked */
    rank?: number;
    /** Experience earned */
    experience?: number;
    /** Total frags (kills) */
    frags?: number;
    /** Hit percentage (0-100) */
    hitPercent?: number;
    /** Name of the weapon used most */
    weaponName?: string;
    /** Weapon ID for icon rendering */
    weaponId?: number;
    /** Quest tier (1-5, for advancing to next quest) */
    questTier?: number;
    /** Quest index (1-10, for advancing to next quest) */
    questIndex?: number;
}

export class QuestCompleteScreen {
    // ── Assets ──────────────────────────────────────────────────────────────
    private panelElement: UIElement;
    private titleHandle: TextureHandle = -1; // ui_textWellDone.jaz
    private wiconsTex: TextureHandle = -1; // ui_wicons.jaz (weapon icon atlas 8×2)
    private btnSmallTex: TextureHandle = -1; // ui_button_64x32.jaz (small button bg)
    private btnMediumTex: TextureHandle = -1; // ui_button_128x32.jaz (medium button bg)
    private soundSystem: SoundSystem | null = null;

    // ── State ────────────────────────────────────────────────────────────────
    private _visible: boolean = false;
    private data: QuestResultsData | null = null;

    /**
     * Animation phase (mirrors C ui_screen_phase):
     *  -1 = score animation running
     *   0 = high-score check (instant transition)
     *   1 = name entry active + rich stats
     *   2 = buttons visible
     */
    private phase: number = -1;

    // ── Score animation state (C: quest_results_* globals) ──────────────────
    private animStep: number = 0; // 0=BaseTime 1=LifeBonus 2=PerkBonus 3=FinalTime
    private animDelayMs: number = 700; // countdown between increments
    private animTimerMs: number = 0; // used for flash / fade-in of buttons
    private timeDisplay: number = 0; // currently shown Base Time (ms)
    private lifeBonusDisplay: number = 0; // currently shown Damage Taken (ms)
    private perksDisplay: number = 0; // currently shown perk count
    private scoreDisplay: number = 0; // currently shown Final Time (ms)

    // ── Name entry state ─────────────────────────────────────────────────────
    private playerName: string = '';
    private readonly MAX_NAME_LENGTH = 16;

    // ── Button hit areas ─────────────────────────────────────────────────────
    private btnPlayNext: { x: number; y: number; w: number; h: number } | null = null;
    private btnReplay: { x: number; y: number; w: number; h: number } | null = null;
    private btnHighScores: { x: number; y: number; w: number; h: number } | null = null;
    private btnMenu: { x: number; y: number; w: number; h: number } | null = null;
    private btnOk: { x: number; y: number; w: number; h: number } | null = null;

    // ── Panel layout (mirrors PerkSelectionScreen) ───────────────────────────
    private readonly PANEL_TEX_W = 512;
    private readonly PANEL_TEX_H = 400;
    private readonly PANEL_MARGIN_LEFT = -30;

    // Content area inside the panel (black region)
    private readonly CONTENT_LEFT = 190;
    private readonly CONTENT_TOP = 30;

    // Animation
    private animTimeline: number = 0;
    private readonly ANIM_DURATION = 400; // ms for panel slide-in

    // ── C code layout constants ──────────────────────────────────────────────
    // Title drawn at 256×64 in C: ui_draw_textured_quad(x, y, 0x100, 0x40, texture)
    private readonly TITLE_TEX_W = 256;
    private readonly TITLE_TEX_H = 64;

    // Stats layout
    private readonly STATS_START_Y = 56 + 40 + 20; // C: local_c + 56 (title) + 40 (gap) + 20 (first row offset)
    private readonly ROW_HEIGHT = 20; // C: local_c += 20
    private readonly VALUE_COL_OFFSET = 132; // C: local_10 + 132.0

    // Button dimensions
    // (Button dimensions now inline in renderPhase2 — matches play menu 128×32)

    constructor() {
        // Panel UIElement — same setup as PerkSelectionScreen
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
            console.warn(`[QuestCompleteScreen] Failed to load: ${path}`);
            return -1;
        };

        // Load panel texture (same as PerkSelectionScreen)
        await this.panelElement.load('qcs_panel', 'ui/ui_menupanel.jaz', assetManager, grim);

        this.titleHandle = await load('ui/ui_textWellDone.jaz', 'qcs_title');
        this.wiconsTex = await load('ui/ui_wicons.jaz', 'qcs_wicons');
        this.btnSmallTex = await load('ui/ui_button_64x32.jaz', 'qcs_btn_small');
        this.btnMediumTex = await load('ui/ui_button_128x32.jaz', 'qcs_btn_medium');
    }

    // ─────────────────────────────────────────────────────────────────────────
    // Show / Hide
    // ─────────────────────────────────────────────────────────────────────────

    show(data: QuestResultsData): void {
        this.data = data;
        this._visible = true;
        this.animTimeline = 0;

        // Initialise animation state (C: quest_results_screen_flags init block)
        this.phase = -1;
        this.animStep = 0;
        this.animDelayMs = 700;
        this.animTimerMs = 0;
        this.timeDisplay = 0;
        this.lifeBonusDisplay = 0;
        this.perksDisplay = 0;
        this.scoreDisplay = 0;
        this.playerName = '';

        this.btnPlayNext = null;
        this.btnReplay = null;
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

    /**
     * Set sound system reference.
     * C code: quest.c plays sfx_ui_clink_01 on score increments, sfx_shock_hit_01 at reveal.
     */
    setSoundSystem(soundSystem: SoundSystem): void {
        this.soundSystem = soundSystem;
    }

    // ─────────────────────────────────────────────────────────────────────────
    // Update
    // ─────────────────────────────────────────────────────────────────────────

    /**
     * Update the screen.  Returns a QuestCompleteAction when the player
     * chooses an option, or QuestCompleteAction.None while still running.
     */
    update(dtMs: number, input: QuestCompleteInput): QuestCompleteAction {
        if (!this._visible || !this.data) return QuestCompleteAction.None;

        // Slide-in animation
        if (this.animTimeline < this.ANIM_DURATION) {
            this.animTimeline = Math.min(this.animTimeline + dtMs, this.ANIM_DURATION);
        }

        // Update panel element animation
        this.panelElement.update(dtMs, false, this.animTimeline);

        switch (this.phase) {
            case -1:
                return this.updateScoreAnimation(dtMs, input);
            case 0:
                // Phase 0: instant check — do we qualify for high score?
                return this.updateHighScoreCheck();
            case 1:
                return this.updateNameEntry(dtMs, input);
            case 2:
                return this.updateButtons(dtMs, input);
        }

        return QuestCompleteAction.None;
    }

    // ── Phase -1: Score animation ─────────────────────────────────────────────

    private updateScoreAnimation(dtMs: number, input: QuestCompleteInput): QuestCompleteAction {
        const data = this.data!;

        // Countdown delay
        this.animDelayMs -= dtMs;

        if (this.animDelayMs < 1) {
            if (this.animStep < 3) {
                if (this.animStep === 0) {
                    // Base Time: increment by 2000ms each tick, 40ms delay (C: 0x28 = 40)
                    this.timeDisplay += 2000;
                    this.animDelayMs = 40;
                    this.scoreDisplay = this.timeDisplay;
                    // C quest.c:312 — sfx_play(sfx_ui_clink_01) on each tick
                    this.soundSystem?.play(SoundId.UI_CLINK_01);
                    if (data.baseTimeMs <= this.timeDisplay) {
                        this.timeDisplay = data.baseTimeMs;
                        this.scoreDisplay = this.timeDisplay;
                        this.animStep = 1;
                    }
                } else if (this.animStep === 1) {
                    // Damage Taken: increment by 1000ms each tick, 150ms delay (C: 0x96 = 150)
                    this.lifeBonusDisplay += 1000;
                    this.animDelayMs = 150;
                    this.scoreDisplay -= 1000;
                    // C quest.c:328 — sfx_play(sfx_ui_clink_01) on each tick
                    this.soundSystem?.play(SoundId.UI_CLINK_01);
                    if (data.lifeBonusMs <= this.lifeBonusDisplay) {
                        this.lifeBonusDisplay = data.lifeBonusMs;
                        this.animStep = 2;
                    }
                } else if (this.animStep === 2) {
                    // Unpicked Perk Bonus: one perk at a time, 300ms delay
                    this.perksDisplay += 1;
                    this.animDelayMs = 300;
                    this.scoreDisplay -= 1000;
                    // C quest.c:342 — sfx_play(sfx_ui_clink_01) on each perk tick
                    this.soundSystem?.play(SoundId.UI_CLINK_01);
                    if (data.unpickedPerks <= this.perksDisplay) {
                        this.perksDisplay = data.unpickedPerks;
                        this.animStep = 3;
                        this.animDelayMs = 1000;
                        this.scoreDisplay = data.finalTimeMs;
                        // C quest.c:355 — sfx_play(sfx_shock_hit_01) when final score revealed
                        this.soundSystem?.play(SoundId.SHOCK_HIT_01);
                    }
                }
            } else if (this.animStep === 3) {
                // Flash Final Time (C: 50ms pulses, count up)
                this.animDelayMs = 50;
                this.animTimerMs += 1;
            }
        }

        // After 10 flashes, auto-advance
        if (this.animStep === 3 && this.animTimerMs > 10) {
            this.animTimerMs = 0;
            this.phase = 0; // go to high score check
            return QuestCompleteAction.None;
        }

        // Space / Enter / click skips animation
        if (input.confirmPressed || input.mouseClicked) {
            // Snap to final values
            this.timeDisplay = data.baseTimeMs;
            this.lifeBonusDisplay = data.lifeBonusMs;
            this.perksDisplay = data.unpickedPerks;
            this.scoreDisplay = data.finalTimeMs;
            this.animStep = 3;
            this.animTimerMs = 0;
            this.phase = 0; // go to high score check
        }

        return QuestCompleteAction.None;
    }

    // ── Phase 0: High-score check ─────────────────────────────────────────────

    private updateHighScoreCheck(): QuestCompleteAction {
        const data = this.data!;
        if (data.isHighScore) {
            // Qualifies for high score → name entry
            this.phase = 1;
            this.animTimerMs = 0;
        } else {
            // No high score → skip name entry, go to buttons
            this.phase = 2;
            this.animTimerMs = 0;
        }
        return QuestCompleteAction.None;
    }

    // ── Phase 1: Name entry ───────────────────────────────────────────────────

    private updateNameEntry(dtMs: number, input: QuestCompleteInput): QuestCompleteAction {
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

        // Check Ok button click — go directly to next quest
        if (input.mouseClicked && this.btnOk && this.hitTest(input.mouseX, input.mouseY, this.btnOk)) {
            if (this.playerName.trim().length > 0) {
                return QuestCompleteAction.PlayNext;
            }
        }

        // Confirm name with Enter — go directly to next quest
        if (input.confirmPressed && this.playerName.trim().length > 0) {
            return QuestCompleteAction.PlayNext;
        }

        return QuestCompleteAction.None;
    }

    // ── Phase 2: Buttons ──────────────────────────────────────────────────────

    private updateButtons(dtMs: number, input: QuestCompleteInput): QuestCompleteAction {
        // Fade in timer (0→500ms)
        if (this.animTimerMs < 500) {
            this.animTimerMs = Math.min(500, this.animTimerMs + dtMs);
        }

        if (input.mouseClicked) {
            const mx = input.mouseX;
            const my = input.mouseY;

            if (this.btnPlayNext && this.hitTest(mx, my, this.btnPlayNext)) {
                // C: quest 5-10 is the final quest — "Show End Note" transitions to credits
                if (this.data && this.data.questTier === 5 && this.data.questIndex === 10) {
                    return QuestCompleteAction.ShowEndNote;
                }
                return QuestCompleteAction.PlayNext;
            }
            if (this.btnReplay && this.hitTest(mx, my, this.btnReplay)) {
                return QuestCompleteAction.Replay;
            }
            if (this.btnHighScores && this.hitTest(mx, my, this.btnHighScores)) {
                return QuestCompleteAction.HighScores;
            }
            if (this.btnMenu && this.hitTest(mx, my, this.btnMenu)) {
                return QuestCompleteAction.MainMenu;
            }
        }

        // Escape → main menu
        if (input.cancelPressed) {
            return QuestCompleteAction.MainMenu;
        }

        return QuestCompleteAction.None;
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
        // Ease: cosine
        const eased = 1 - Math.cos((slideT * Math.PI) / 2);

        // Panel slides in from the left
        const pivotX = this.PANEL_MARGIN_LEFT;
        const pivotY = screenH / 2;

        const panelTargetX = pivotX;
        const panelOffscreenX = -this.PANEL_TEX_W - 10;
        const panelX = panelOffscreenX + (panelTargetX - panelOffscreenX) * eased;

        // ── Panel background ──────────────────────────────────────────────────
        grim.setBlendMode('normal');
        grim.setColor(255, 255, 255, 255);
        this.panelElement.draw(grim, panelX, pivotY);

        // Content area origin (in screen coords)
        // +20 shifts inner content down relative to panel frame
        const cx = panelX + this.CONTENT_LEFT;
        const cy = pivotY + this.panelElement.offsetY + this.CONTENT_TOP;

        // ── "WELL DONE TROOPER!" title ─────────────────────────────────────────
        // C: ui_draw_textured_quad(x, y, 256, 64, texture_quest_panel_id)
        // Center the title in the content area
        const contentW = 256; // width of the black area inside the panel
        if (this.titleHandle >= 0) {
            grim.setBlendMode('normal');
            grim.setColor(255, 255, 255, 255);
            grim.bindTexture(this.titleHandle);
            grim.setUV(0, 0, 1, 1);
            grim.beginBatch();
            // Center title: cx + (contentW - titleW) / 2
            const titleX = cx + (contentW - this.TITLE_TEX_W) / 2;
            grim.drawQuad(titleX, cy, this.TITLE_TEX_W, this.TITLE_TEX_H);
            grim.endBatch();
        } else {
            // Fallback: draw text
            grim.setColor(255, 255, 255, 255);
            font.drawText(grim, 'WELL DONE TROOPER!', cx + 20, cy + 20);
        }

        // C code layout tracking variable (mirrors local_c)
        // After title: local_c = initial + 56 (title area)
        // Then: local_c += 40 (gap before stats)
        // Then: local_c += 20 (first row nudge)
        // local_10 is the x for text, with values at local_10 + 132

        const statsX = cx + 32; // C: local_10 + 32 (offset into content)
        const valueX = statsX + this.VALUE_COL_OFFSET;

        // Render phase-specific content
        if (this.phase === -1) {
            // ── Phase -1: Stats animation ──
            this.renderStatsPhase(grim, font, statsX, valueX, cy);
        } else if (this.phase === 1) {
            // ── Phase 1: Name entry + rich stats ──
            this.renderPhase1(grim, font, statsX, valueX, cx, cy, mouseX, mouseY);
        } else if (this.phase === 2) {
            // ── Phase 2: Score table + unlocks + buttons ──
            this.renderPhase2(grim, font, statsX, valueX, cx, cy, mouseX, mouseY);
        }
    }

    // ── Phase -1: Stats animation rendering ──────────────────────────────────

    private renderStatsPhase(grim: GrimInterface, font: BitmapFont, statsX: number, valueX: number, cy: number): void {
        // C: local_c starts at title area + 56, then += 40, then += 20
        let curY = cy + this.STATS_START_Y;

        // Flash alpha for current step (C: 1.0 - animTimer * 0.1, clamped 0-1)
        // animTimerMs only increments during step 3 (fade-out/auto-advance)
        const flashAlpha = Math.max(0, Math.min(1, 1.0 - this.animTimerMs * 0.1));

        // Base Time row (C: step 0 = green, step > 0 = dim white, step < 0 = impossible)
        this.renderStatRow(
            grim,
            font,
            statsX,
            curY,
            valueX,
            'Base Time:',
            this.formatTime(this.timeDisplay),
            this.animStep,
            0,
            flashAlpha,
        );
        curY += this.ROW_HEIGHT;

        // Life Bonus row (C: "Life Bonus:")
        this.renderStatRow(
            grim,
            font,
            statsX,
            curY,
            valueX,
            'Life Bonus:',
            this.formatTime(this.lifeBonusDisplay),
            this.animStep,
            1,
            flashAlpha,
        );
        curY += this.ROW_HEIGHT;

        // Unpicked Perk Bonus row
        this.renderStatRow(
            grim,
            font,
            statsX,
            curY,
            valueX,
            'Unpicked Perk Bonus:',
            this.formatTime(this.perksDisplay * 1000),
            this.animStep,
            2,
            flashAlpha,
        );
        curY += this.ROW_HEIGHT;

        // Separator line (C: grim_draw_rect_outline at local_10 - 4, width 168, height 1)
        const lineAlpha = Math.round(flashAlpha * 255);
        grim.setBlendMode('normal');
        grim.setColor(255, 255, 255, lineAlpha);
        this.drawSpriteRect(grim, statsX - 4, curY + 1, 168, 1);
        curY += 8; // C: local_c += 8

        // Final Time row — always white at full flashAlpha (C: color 1,1,1,fVar3)
        const finalColor = { r: 255, g: 255, b: 255, a: lineAlpha };
        font.drawText(grim, 'Final Time:', statsX, curY, finalColor);
        font.drawText(grim, this.formatTime(this.scoreDisplay), valueX, curY, finalColor);
    }

    // ── Phase 1: Name entry + rich stats ─────────────────────────────────────
    // C code: quest_results_screen_update Phase 1 (quest.c:550-639)
    // + ui_text_input_render (ui_core.c:2066-2313)
    // Layout: local_10 = content X, local_c = content Y cursor

    private renderPhase1(
        grim: GrimInterface,
        font: BitmapFont,
        statsX: number,
        _valueX: number,
        _cx: number,
        cy: number,
        mouseX: number,
        mouseY: number,
    ): void {
        const data = this.data!;
        const alpha = Math.min(1.0, this.animTimerMs * 0.002);
        const a = Math.round(alpha * 255);
        const a70 = Math.round(alpha * 0.7 * 255);
        const a80 = Math.round(alpha * 0.8 * 255);

        // Content area width for centering
        const contentW = 256; // black area inside panel
        const contentCenterX = statsX - 32 + contentW / 2; // center of content area

        // C: local_c tracks Y cursor. After title (56px), Phase 1 adds 22.
        let curY = cy + 56 + 22;

        // ── "State your name trooper!" ──
        // C: grim_draw_text_small_fmt at (local_10 + 42, local_c)
        // Center this text in the content area
        grim.setColor(255, 255, 255, a);
        const subtitleText = 'State your name trooper!';
        const subtitleW = font.measureText(subtitleText);
        font.drawText(grim, subtitleText, contentCenterX - subtitleW / 2, curY);
        curY += 32; // C: local_c += 32

        // ── Name input box ──
        // C: ui_text_input_update → grim_draw_rect_outline(xy, width, 18)
        // Width = quest_back_button_height = 0xa6 = 166
        const inputX = statsX - 10; // shift left to center with OK button
        const inputY = curY;
        const inputW = 166; // C: 0xa6 = 166
        const inputH = 18; // C: 18px height

        // White outline box (C: grim_draw_rect_outline with color 1,1,1,1)
        grim.setBlendMode('normal');
        grim.setColor(255, 255, 255, a);
        this.drawSpriteRect(grim, inputX, inputY, inputW, 1); // top
        this.drawSpriteRect(grim, inputX, inputY + inputH, inputW, 1); // bottom
        this.drawSpriteRect(grim, inputX, inputY, 1, inputH + 1); // left
        this.drawSpriteRect(grim, inputX + inputW, inputY, 1, inputH + 1); // right

        // Black fill inside (C: grim_draw_rect_filled with color 0,0,0,alpha)
        grim.setColor(0, 0, 0, a);
        this.drawSpriteRect(grim, inputX + 1, inputY + 1, inputW - 2, inputH - 1);

        // Player name text (C: grim_draw_text_small at x+4, y+2, alpha=0.8)
        grim.setColor(255, 255, 255, a80);
        const cursor = Math.floor(Date.now() / 500) % 2 === 0 ? '|' : '';
        font.drawText(grim, this.playerName + cursor, inputX + 4, inputY + 2);

        // ── "Ok" button with texture background ──
        // C: ui_button_update — button at (local_10 + 170, local_c - 8)
        const okBtnX = inputX + inputW + 4;
        const okBtnY = inputY - 8;
        const okBtnW = 82; // C: small button width
        const okBtnH = 32; // C: button texture height

        // Draw button texture background
        if (this.btnSmallTex >= 0) {
            grim.setColor(255, 255, 255, a);
            grim.bindTexture(this.btnSmallTex);
            grim.setUV(0, 0, 1, 1);
            grim.beginBatch();
            grim.drawQuad(okBtnX, okBtnY, okBtnW, okBtnH);
            grim.endBatch();
        }

        // Button hit area
        this.btnOk = { x: okBtnX, y: okBtnY + 2, w: okBtnW, h: 28 };

        // "Ok" text centered on button
        const okHovered = this.hitTest(mouseX, mouseY, this.btnOk);
        const okTextAlpha = okHovered ? a : a70;
        grim.setColor(255, 255, 255, okTextAlpha);
        const okTextW = font.measureText('Ok');
        font.drawText(grim, 'Ok', okBtnX + okBtnW * 0.5 - okTextW / 2 + 1, okBtnY + 10);

        // ── Rich stats display ──
        // C: local_c += 30 after input, then ui_text_input_render at (local_10 + 26, local_c + 16)
        curY += 30; // C: local_c += 30

        // fStack_10 = input_x + 4 (from ui_text_input_render: *(float*)input_state + 4)
        // fStack_c = input_y (local_c + 16 from quest.c:635)
        // We center the score/experience block in the content area
        const blockW = 96 + 80; // Score column (64) + gap + Experience column (80) ≈ 176
        const stX = contentCenterX - blockW / 2; // center the block
        const stY = curY + 16;

        // ── Score column ──
        // C: "Score" at (fStack_10 + 32) - measureText/2
        const scoreCenterX = stX + 32; // center of 64px Score column

        // "Score" label — C: color (0.9, 0.9, 0.9, alpha*0.8)
        grim.setColor(230, 230, 230, a80);
        const scoreLabelW = font.measureText('Score');
        font.drawText(grim, 'Score', scoreCenterX - scoreLabelW / 2, stY);

        // Score value — C: color (0.9, 0.9, 1.0, alpha), at fStack_c + 15
        grim.setColor(230, 230, 255, a);
        const scoreStr =
            data.scoreSeconds !== undefined
                ? data.scoreSeconds.toFixed(2) + ' secs'
                : this.formatTime(data.finalTimeMs);
        const scoreValW = font.measureText(scoreStr);
        font.drawText(grim, scoreStr, scoreCenterX - scoreValW / 2, stY + 15);

        // "Rank: Xth" — C: color (0.9, 0.9, 0.9, alpha*0.8), at fStack_c + 30
        if (data.rank !== undefined && data.rank > 0) {
            grim.setColor(230, 230, 230, a80);
            const rankStr = 'Rank: ' + this.formatOrdinal(data.rank);
            const rankW = font.measureText(rankStr);
            font.drawText(grim, rankStr, scoreCenterX - rankW / 2, stY + 30);
        }

        // ── Vertical separator ──
        // C: ui_stats_render_row() at fStack_10 + 96: draws 1×48 rect
        // fStack_10 -= 16 before drawing, then += 16 after
        const sepX = stX + 96 - 16;
        grim.setBlendMode('normal');
        grim.setColor(255, 255, 255, a);
        this.drawSpriteRect(grim, sepX, stY, 2, 48);

        // ── Experience column ──
        // C: fStack_10 + 96 = start of Experience column
        // Experience label at fStack_10 (left-aligned), value centered at fStack_10 + 32
        const expX = stX + 96;
        const expCenterX = expX + 32;
        grim.setColor(230, 230, 230, a80);
        font.drawText(grim, 'Experience', expX, stY);

        if (data.experience !== undefined) {
            grim.setColor(230, 230, 230, a80);
            const expStr = '' + data.experience;
            const expW = font.measureText(expStr);
            font.drawText(grim, expStr, expCenterX - expW / 2, stY + 15);
        }

        // ── Horizontal weapon bar above weapon section ──
        // C: fStack_c += 52 then ui_stats_render_weapon_bar()
        // ui_stats_render_weapon_bar: 192×1 line at fStack_10 - 16
        const weapBarY = stY + 52;
        grim.setBlendMode('normal');
        grim.setColor(255, 255, 255, a);
        this.drawSpriteRect(grim, stX - 16, weapBarY, 192, 2);
        const weapY = weapBarY + 4; // C: fStack_c += 4 after weapon bar

        // ── Weapon icon (64×32) ──
        // C: grim_draw_quad(fStack_10, fStack_c, 64, 32) with wicons atlas
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
        // C: (0x20 - measureText/2) + fStack_10, clamped to >= 0
        if (data.weaponName) {
            grim.setColor(230, 230, 230, a70);
            const nameW = font.measureText(data.weaponName);
            let nameX = 0x20 - nameW / 2 + weapX;
            if (nameX < 0) nameX = 0;
            font.drawText(grim, data.weaponName, nameX, weapY + 32);
        }

        // Frags + Hit % (right side, aligned with weapon icon top)
        // C: fStack_10 + 110, fStack_c + 1 for Frags; fStack_c + 15 for Hit%
        const fragX = weapX + 110;
        if (data.frags !== undefined) {
            grim.setColor(230, 230, 230, a80);
            font.drawText(grim, 'Frags: ' + data.frags, fragX, weapY + 1);
        }
        if (data.hitPercent !== undefined) {
            grim.setColor(230, 230, 230, a80);
            font.drawText(grim, 'Hit %: ' + data.hitPercent + '%', fragX, weapY + 15);
        }

        // ── Bottom weapon bar ──
        // C: fStack_c += 48 then ui_stats_render_weapon_bar()
        const bottomBarY = weapY + 48;
        grim.setBlendMode('normal');
        grim.setColor(255, 255, 255, a);
        this.drawSpriteRect(grim, stX - 16, bottomBarY, 192, 2);
    }

    // ── Phase 2: Score table + unlocks + buttons ─────────────────────────────

    private renderPhase2(
        grim: GrimInterface,
        font: BitmapFont,
        statsX: number,
        _valueX: number,
        _cx: number,
        cy: number,
        mouseX: number,
        mouseY: number,
    ): void {
        const data = this.data!;
        const alpha = Math.min(1.0, this.animTimerMs * 0.002);

        // C: fVar3 = local_c + 56 (after title)
        let curY = cy + 56;

        // ── High score info ──
        if (!data.isHighScore) {
            // C: local_c += 6, draw text, local_c += 6
            curY += 6;
            grim.setColor(255, 255, 255, Math.round(alpha * 255));
            font.drawText(grim, 'Score too low for top 100', statsX + 8, curY);
            curY += 6;
        }

        // C: ui_text_input_render area — 78+6=84 px
        // In quest mode Phase 2, weapon bar is skipped (C line 2211)
        // Just leave space for Score/Rank display
        const scoreBlockY = curY + 16;
        grim.setColor(230, 230, 230, Math.round(alpha * 0.8 * 255));
        font.drawText(grim, 'Score', statsX + 6, scoreBlockY);

        grim.setColor(230, 230, 255, Math.round(alpha * 255));
        const scoreStr =
            data.scoreSeconds !== undefined
                ? data.scoreSeconds.toFixed(2) + ' secs'
                : this.formatTime(data.finalTimeMs);
        font.drawText(grim, scoreStr, statsX, scoreBlockY + 15);

        if (data.rank !== undefined && data.rank > 0) {
            grim.setColor(230, 230, 230, Math.round(alpha * 0.8 * 255));
            font.drawText(grim, 'Rank: ' + this.formatOrdinal(data.rank), statsX + 2, scoreBlockY + 30);
        }

        curY += 84; // C: local_c += 78 + 6

        // ── Unlock display ──
        if (data.unlockWeaponName) {
            grim.setColor(255, 255, 255, Math.round(alpha * 0.7 * 255));
            font.drawText(grim, 'Weapon unlocked:', statsX, curY + 1);
            curY += 14;
            grim.setColor(255, 255, 255, Math.round(alpha * 0.9 * 255));
            font.drawText(grim, data.unlockWeaponName, statsX, curY);
            curY += 16;
        }

        if (data.unlockPerkName) {
            grim.setColor(255, 255, 255, Math.round(alpha * 0.7 * 255));
            font.drawText(grim, 'Perk unlocked:', statsX, curY + 1);
            curY += 14;
            grim.setColor(255, 255, 255, Math.round(alpha * 0.9 * 255));
            font.drawText(grim, data.unlockPerkName, statsX, curY);
            curY += 16;
        }

        curY += 6; // C: local_c += 6 before buttons

        // ── 4 Buttons (C: 32px apart, local_10 += 20 offset) ──
        const btnX = statsX + 20; // C: local_10 = local_10 + 20.0
        const buttonWidth = 128;
        const buttonHeight = 32;
        const buttonSpacing = 32; // C: local_c += 32.0

        this.btnPlayNext = { x: btnX, y: curY, w: buttonWidth, h: buttonHeight };
        curY += buttonSpacing;
        this.btnReplay = { x: btnX, y: curY, w: buttonWidth, h: buttonHeight };
        curY += buttonSpacing;
        this.btnHighScores = { x: btnX, y: curY, w: buttonWidth, h: buttonHeight };
        curY += buttonSpacing;
        this.btnMenu = { x: btnX, y: curY, w: buttonWidth, h: buttonHeight };

        // C: quest 5-10 is the final quest — button label changes to "Show End Note"
        const isFinalQuest = data.questTier === 5 && data.questIndex === 10;
        const buttons = [
            { rect: this.btnPlayNext, label: isFinalQuest ? 'Show End Note' : 'Play Next' },
            { rect: this.btnReplay, label: 'Play Again' },
            { rect: this.btnHighScores, label: 'High scores' },
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

    // ── Stat row helper ──────────────────────────────────────────────────────

    /**
     * Render a stat row matching C code color logic:
     * - currentStep == rowStep: active (green, alpha = flashAlpha)
     * - currentStep > rowStep: done (white, alpha = flashAlpha * 0.4)
     * - currentStep < rowStep: not yet reached (white, alpha = flashAlpha * 0.2)
     */
    private renderStatRow(
        grim: GrimInterface,
        font: BitmapFont,
        labelX: number,
        y: number,
        valueX: number,
        label: string,
        value: string,
        currentStep: number,
        rowStep: number,
        flashAlpha: number,
    ): void {
        let r: number, g: number, b: number, a: number;

        if (currentStep === rowStep) {
            // Active (currently animating): green (C: 0.1, 0.8, 0.1)
            r = 26;
            g = 204;
            b = 26;
            a = Math.round(flashAlpha * 255);
        } else if (currentStep > rowStep) {
            // Done: white at 40% alpha (C: 1.0, 1.0, 1.0, local_18 * 0.4)
            r = 255;
            g = 255;
            b = 255;
            a = Math.round(flashAlpha * 0.4 * 255);
        } else {
            // Not yet reached: white at 20% alpha (C: 1.0, 1.0, 1.0, local_18 * 0.2)
            r = 255;
            g = 255;
            b = 255;
            a = Math.round(flashAlpha * 0.2 * 255);
        }

        // Pass color directly to font.drawText (BitmapFont ignores grim.setColor)
        const color = { r, g, b, a };
        font.drawText(grim, label, labelX, y, color);
        font.drawText(grim, value, valueX, y, color);
    }

    // ─────────────────────────────────────────────────────────────────────────
    // Helpers
    // ─────────────────────────────────────────────────────────────────────────

    /**
     * Draw a colored rect in the sprite layer (not the graphics layer).
     * drawRectFilled uses PixiJS Graphics which renders BELOW the sprite layer,
     * making rects invisible when covered by sprites/text. This uses drawQuad
     * with an unbound texture (falls back to Texture.WHITE) so the rect renders
     * at the correct z-order within the sprite container.
     */
    private drawSpriteRect(grim: GrimInterface, x: number, y: number, w: number, h: number): void {
        grim.bindTexture(-1); // unbind → Texture.WHITE
        grim.setUV(0, 0, 1, 1);
        grim.beginBatch();
        grim.drawQuad(x, y, w, h);
        grim.endBatch();
    }

    /** Format milliseconds as M:SS (e.g. 1:45) — matches C format_time_seconds */
    private formatTime(ms: number): string {
        if (ms <= 0) return '0:00';
        const totalSec = Math.floor(ms / 1000);
        const sec = totalSec % 60;
        const min = Math.floor(totalSec / 60);
        return `${min}:${sec.toString().padStart(2, '0')}`;
    }

    /** Format ordinal (1→1st, 2→2nd, etc.) — matches C format_ordinal */
    private formatOrdinal(n: number): string {
        const suffix = ['th', 'st', 'nd', 'rd'];
        const v = n % 100;
        return n + (suffix[(v - 20) % 10] || suffix[v] || suffix[0]);
    }

    /** Get the entered player name (for saving to high score) */
    getPlayerName(): string {
        return this.playerName.trim();
    }

    /** Get the quest results data (for PlayNext action) */
    getData(): QuestResultsData | null {
        return this.data;
    }
}
