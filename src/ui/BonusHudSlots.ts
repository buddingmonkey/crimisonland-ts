/**
 * BonusHudSlots - Sliding HUD panels for active timed bonuses.
 *
 * Port of C code bonus_hud_add_slot() @ 0041a810 and
 * bonus_hud_slot_update_and_render() @ 0041a8b0.
 *
 * Features:
 * - Panels slide in from left edge when a timed bonus is picked up
 * - Shows bonus icon (from bonuses.jaz atlas) + label text + progress bar
 * - Panels slide back out when the timer expires
 * - Up to 16 simultaneous slots
 * - Deduplicates: if same timer is already tracked, replaces old slot
 */

import type { GrimInterface, TextureHandle } from '../engine/GrimInterface';
import type { BitmapFont } from '../engine/BitmapFont';

/** Maximum number of concurrent HUD bonus slots (C: array of 16 + 1) */
const MAX_SLOTS = 16;

/** Slide animation speeds (pixels per second) — from C code */
const SLIDE_IN_SPEED = 350;
const SLIDE_OUT_SPEED = 320;

/** Panel fully-offscreen X (C: -184.0) */
const SLIDE_MIN_X = -184;
/** Panel fully-visible X (C: -2.0) */
const SLIDE_MAX_X = -2;

/** Vertical spacing between slots (C: *xy += 52.0) */
const SLOT_HEIGHT = 52;

/** Panel dimensions (C: 182×53 from ui_indPanel.jaz) */
const PANEL_WIDTH = 182;
const PANEL_HEIGHT = 53;

/** Progress bar dimensions (C: ui_draw_progress_bar at slideX+36, width=100) */
const BAR_OFFSET_X = 36;
const BAR_OFFSET_Y = 21;
const BAR_WIDTH = 100;
const BAR_HEIGHT = 4;

/** Icon position offset (C: slideX - 1, 32×32) */
const ICON_OFFSET_X = -1;
const ICON_SIZE = 32;

/** Label text offset (C: slideX + 36, y + 6) */
const LABEL_OFFSET_X = 36;
const LABEL_OFFSET_Y = 6;

interface BonusHudSlot {
    active: boolean;
    label: string;
    iconId: number;
    slideX: number;
    /** Returns the current timer value (so slot can track externally-managed timers) */
    getTimer: () => number;
    /** Unique key for deduplication (typically the bonus type name) */
    timerKey: string;
}

export class BonusHudSlots {
    private slots: BonusHudSlot[] = [];

    constructor() {
        for (let i = 0; i < MAX_SLOTS; i++) {
            this.slots.push({
                active: false,
                label: '',
                iconId: -1,
                slideX: SLIDE_MIN_X,
                getTimer: () => 0,
                timerKey: '',
            });
        }
    }

    /**
     * Add a bonus indicator slot.
     * Port of C bonus_hud_add_slot() @ 0041a810.
     *
     * Deduplication: if an existing slot has the same timerKey, it is replaced.
     */
    addSlot(label: string, iconId: number, getTimer: () => number, timerKey: string): void {
        // Dedup: deactivate any existing slot with the same timerKey
        for (const slot of this.slots) {
            if (slot.active && slot.timerKey === timerKey) {
                slot.active = false;
            }
        }

        // Find a free slot
        for (const slot of this.slots) {
            if (!slot.active) {
                slot.active = true;
                slot.label = label;
                slot.iconId = iconId;
                slot.slideX = SLIDE_MIN_X;
                slot.getTimer = getTimer;
                slot.timerKey = timerKey;
                return;
            }
        }
        // All slots full — silently drop (matches C: just returns on overflow)
    }

    /**
     * Update slide animations.
     * Port of C bonus_hud_slot_update_and_render() animation logic.
     */
    update(dt: number): void {
        for (const slot of this.slots) {
            if (!slot.active) continue;

            const timerValue = slot.getTimer();
            if (timerValue > 0) {
                // Timer still active → slide in
                slot.slideX = Math.min(SLIDE_MAX_X, slot.slideX + SLIDE_IN_SPEED * dt);
            } else {
                // Timer expired → slide out
                slot.slideX -= SLIDE_OUT_SPEED * dt;
            }

            // Clamp visible position
            if (slot.slideX > SLIDE_MAX_X) {
                slot.slideX = SLIDE_MAX_X;
            }

            // Deactivate when fully offscreen
            if (slot.slideX < SLIDE_MIN_X) {
                slot.active = false;
                slot.slideX = SLIDE_MIN_X;
            }
        }
    }

    /**
     * Render all active bonus HUD slots.
     * Port of C bonus_hud_slot_update_and_render() rendering logic.
     *
     * @param startY  Y position to begin stacking panels (below XP panel area)
     */
    render(
        grim: GrimInterface,
        font: BitmapFont,
        bonusTex: TextureHandle,
        panelTex: TextureHandle,
        startY: number = 115,
    ): void {
        let y = startY;

        for (const slot of this.slots) {
            if (!slot.active) continue;

            const timerValue = slot.getTimer();
            const alpha = 0.7; // C: in_stack_0000000c * 0.7

            // ── Panel background (ui_indPanel.jaz) ──
            // C: drawQuad(slideX, y - 11, 182, 53) with panel texture
            if (panelTex >= 0) {
                grim.setBlendMode('normal');
                grim.bindTexture(panelTex);
                grim.setRotation(0);
                grim.setUV(0, 0, 1, 1);
                grim.setColor(255, 255, 255, Math.round(alpha * 255));
                grim.beginBatch();
                grim.drawQuad(slot.slideX, y - 11, PANEL_WIDTH, PANEL_HEIGHT);
                grim.endBatch();
            }

            // ── Bonus icon (bonuses.jaz atlas) ──
            // C: drawQuad(slideX - 1, y, 32, 32) with bonus atlas frame
            if (bonusTex >= 0 && slot.iconId >= 0) {
                grim.setBlendMode('normal');
                grim.setColor(255, 255, 255, 255);
                grim.bindTexture(bonusTex);
                grim.setAtlasFrame(4, slot.iconId);
                grim.beginBatch();
                grim.drawQuad(slot.slideX + ICON_OFFSET_X, y, ICON_SIZE, ICON_SIZE);
                grim.endBatch();
            }

            // ── Progress bar ──
            // C: ui_draw_progress_bar at (slideX + 36, y + 21), width 100, ratio = timer * 0.05
            const ratio = Math.max(0, Math.min(1, timerValue * 0.05));
            const barX = slot.slideX + BAR_OFFSET_X;
            const barY = y + BAR_OFFSET_Y;

            // Bar background (dark)
            grim.bindTexture(-1);
            grim.setUV(0, 0, 1, 1);
            grim.setRotation(0);
            grim.setBlendMode('normal');
            grim.setColor(25, 76, 153, Math.round(alpha * 255)); // C: {0.1, 0.3, 0.6}
            grim.beginBatch();
            grim.drawQuad(barX, barY, BAR_WIDTH, BAR_HEIGHT);

            // Bar fill (bright)
            if (ratio > 0) {
                grim.setColor(51, 128, 255, Math.round(alpha * 255));
                grim.drawQuad(barX, barY, BAR_WIDTH * ratio, BAR_HEIGHT);
            }
            grim.endBatch();

            // ── Label text ──
            // C: grim_draw_text_small(slideX + 36, y + 6, label)
            grim.setColor(255, 255, 255, Math.round(alpha * 255));
            font.drawText(grim, slot.label, slot.slideX + LABEL_OFFSET_X, y + LABEL_OFFSET_Y, {
                r: 255,
                g: 255,
                b: 255,
                a: Math.round(alpha * 255),
            });

            y += SLOT_HEIGHT;
        }
    }

    /** Reset all slots (e.g., on game restart) */
    clear(): void {
        for (const slot of this.slots) {
            slot.active = false;
            slot.slideX = SLIDE_MIN_X;
        }
    }

    /** Check if any slots are active */
    hasActiveSlots(): boolean {
        return this.slots.some((s) => s.active);
    }
}
