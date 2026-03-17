/**
 * TutorialSystem - Tutorial stage state machine, text box rendering, and progression
 *
 * C code reference: tutorial_prompt_dialog @ 00408530, tutorial_timeline_update @ 00408990
 *
 * Manages tutorial stages (intro, move, shoot, completion), renders a bordered text box
 * with stage-specific messages, and handles transition animations between stages.
 */

import type { GrimInterface } from '../../engine/GrimInterface';
import type { BitmapFont } from '../../engine/BitmapFont';

/**
 * Tutorial stage enum — matches C code stages 0–9
 */
export enum TutorialStage {
    Inactive = -1,
    Intro = 0, // "In this tutorial you'll learn how to play Crimsonland"
    LearnMove = 1, // "First, learn to move by pushing the arrow keys or WASD"
    PickupBonuses = 2, // "Now pick up the bonuses by walking over them"
    LearnShoot = 3, // "Now learn to shoot. Move the mouse to aim and click to fire"
    ShootEnemies = 4, // "Now, shoot the enemies! Move and shoot at the same time"
    CombatPractice = 5, // "Keep shooting! Pick up bonuses for extra firepower"
    LearnPerks = 6, // "Now let's learn about Perks. You have gained enough XP..."
    PerkInfo = 7, // "Perks can give you extra abilities or stat bonuses..."
    Complete = 8, // "Great! Now you are ready to start playing for real!"
    End = 9, // Sentinel — triggers tutorial end
}

/**
 * Tutorial stage messages — from C code string table (addr 00472534+)
 */
const STAGE_MESSAGES: Record<number, string> = {
    [TutorialStage.Intro]: "In this tutorial you'll learn how to play Crimsonland.",
    [TutorialStage.LearnMove]: 'First, learn to move by pushing the arrow keys or WASD.',
    [TutorialStage.PickupBonuses]: 'Now pick up the bonuses by walking over them.',
    [TutorialStage.LearnShoot]: 'Now learn to shoot. Move the mouse to aim and click to fire!',
    [TutorialStage.ShootEnemies]: 'Now, shoot the enemies! Move and shoot at the same time.',
    [TutorialStage.CombatPractice]: 'Keep shooting! Pick up bonuses for extra firepower.',
    [TutorialStage.LearnPerks]: "Now let's learn about Perks. You have gained enough XP for a perk!",
    [TutorialStage.PerkInfo]: 'Perks can give you extra abilities or stat bonuses.',
    [TutorialStage.Complete]: 'Great! Now you are ready to start playing for real!',
    [TutorialStage.End]: '',
};

/**
 * Input state passed to the tutorial system each frame
 */
export interface TutorialInput {
    /** True if any movement key is held this frame */
    movePressed: boolean;
    /** True if fire (mouse click) was pressed this frame */
    firePressed: boolean;
    /** Mouse X position (for button hit-testing) */
    mouseX: number;
    /** Mouse Y position (for button hit-testing) */
    mouseY: number;
    /** True if mouse was clicked this frame (for buttons) */
    mouseClicked: boolean;
    /** Number of active bonuses on the ground (for PickupBonuses stage) */
    activeBonusCount?: number;
    /** Number of active enemies alive (for ShootEnemies/CombatPractice stages) */
    activeEnemyCount?: number;
    /** True if a perk was just selected this frame (for LearnPerks stage) */
    perkJustSelected?: boolean;
    /** Total kills accumulated this stage (for ShootEnemies/CombatPractice stages) */
    tutorialKillsThisStage?: number;
}

/**
 * Result of tutorial update — tells Game.ts what to do
 */
export enum TutorialAction {
    None = 0,
    /** Tutorial completed — player chose "Play a game" */
    PlayGame = 1,
    /** Player chose "Repeat tutorial" */
    Repeat = 2,
    /** Player chose "Skip tutorial" */
    Skip = 3,
}

/**
 * TutorialSystem — drives the tutorial flow and renders the text box overlay
 *
 * C code: tutorial_timeline_update (stage progression), tutorial_prompt_dialog (rendering)
 */
export class TutorialSystem {
    private stage: TutorialStage = TutorialStage.Inactive;
    private stageTimer: number = 0; // ms since current stage started
    private transitionTimer: number = 0; // fade transition (-1000..0..1000)
    private active: boolean = false;

    // Text box rendering constants (C code: tutorial_prompt_dialog)
    private readonly BOX_Y = 64; // Y position of text box
    private readonly BOX_PADDING_X = 20; // Horizontal padding inside box
    private readonly BOX_PADDING_Y = 8; // Vertical padding inside box
    private readonly TEXT_HEIGHT = 16; // BitmapFont char height
    private readonly BORDER_THICKNESS = 2; // Border line thickness

    // Button regions for stage 8 (Complete)
    // These are dynamically calculated during render and stored for hit-testing
    private skipButtonRect = { x: 0, y: 0, w: 0, h: 0 };
    private playButtonRect = { x: 0, y: 0, w: 0, h: 0 };
    private repeatButtonRect = { x: 0, y: 0, w: 0, h: 0 };

    /**
     * Start the tutorial from stage 0
     */
    start(): void {
        this.active = true;
        this.stage = TutorialStage.Inactive; // Will advance to 0 via transition
        this.stageTimer = 0;
        // C code: tutorial_stage_transition_timer = 0xFFFFFC18 = -1000 (signed)
        this.transitionTimer = -1000;
    }

    /**
     * Reset the tutorial state
     */
    reset(): void {
        this.active = false;
        this.stage = TutorialStage.Inactive;
        this.stageTimer = 0;
        this.transitionTimer = 0;
    }

    /**
     * Check if tutorial is currently active
     */
    isActive(): boolean {
        return this.active;
    }

    /**
     * Get current tutorial stage
     */
    getStage(): TutorialStage {
        return this.stage;
    }

    /**
     * Update tutorial state machine — called each frame during gameplay
     *
     * C code reference: tutorial_timeline_update @ 00408990
     *
     * @returns TutorialAction indicating what Game.ts should do
     */
    update(dt: number, input: TutorialInput): TutorialAction {
        if (!this.active) return TutorialAction.None;

        // C code uses frame_dt_ms (milliseconds), but Game.ts passes dt in seconds
        const dtMs = dt * 1000;

        // Advance stage timer (C: tutorial_stage_timer += frame_dt_ms)
        this.stageTimer += dtMs;

        // Handle transition animation (C lines: 00408a44–00408a90)
        // transitionTimer < -1: fading in new stage (counting up toward 0)
        // transitionTimer >= 0: stage is visible, counting up
        // transitionTimer > 1000: stage fade-out complete → advance stage
        if (this.transitionTimer < -1) {
            this.transitionTimer += dtMs;
            if (this.transitionTimer >= -1) {
                // Transition complete — advance to next stage
                this.stage++;
                if (this.stage >= TutorialStage.End) {
                    // Wrap around (C: tutorial_stage_index = 0 when == 9)
                    this.stage = TutorialStage.Intro;
                }
                this.transitionTimer = 0;
                this.stageTimer = 0;
            }
            return TutorialAction.None;
        }

        // Check if fading out (positive transition timer)
        if (this.transitionTimer >= 0 && this.transitionTimer > 0) {
            this.transitionTimer += dtMs;
            if (this.transitionTimer > 1000) {
                // Fade-out complete — start fade-in of next stage
                this.transitionTimer = -1000;
            }
            return TutorialAction.None;
        }

        // Stage-specific advancement logic
        const action = this.checkStageCompletion(input);

        return action;
    }

    /**
     * Check if current stage's completion condition is met
     */
    private checkStageCompletion(input: TutorialInput): TutorialAction {
        switch (this.stage) {
            case TutorialStage.Intro:
                // Auto-advance after 6 seconds (C: stage 0, timer > 6000)
                if (this.stageTimer > 6000) {
                    this.beginTransitionOut();
                }
                break;

            case TutorialStage.LearnMove:
                // Advance when player presses any movement key
                if (input.movePressed) {
                    this.beginTransitionOut();
                }
                break;

            case TutorialStage.PickupBonuses:
                // Advance when all bonuses picked up (bonuses are spawned by TutorialModeUpdate)
                if (input.activeBonusCount !== undefined && input.activeBonusCount === 0 && this.stageTimer > 500) {
                    this.beginTransitionOut();
                }
                break;

            case TutorialStage.LearnShoot:
                // Advance when player fires
                if (input.firePressed) {
                    this.beginTransitionOut();
                }
                break;

            case TutorialStage.ShootEnemies:
                // Advance when kill threshold reached (5 kills) AND all remaining enemies dead
                if (
                    input.tutorialKillsThisStage !== undefined &&
                    input.tutorialKillsThisStage >= 5 &&
                    input.activeEnemyCount !== undefined &&
                    input.activeEnemyCount === 0
                ) {
                    this.beginTransitionOut();
                }
                break;

            case TutorialStage.CombatPractice:
                // Advance when kill threshold reached (10 kills) AND all remaining enemies dead
                if (
                    input.tutorialKillsThisStage !== undefined &&
                    input.tutorialKillsThisStage >= 10 &&
                    input.activeEnemyCount !== undefined &&
                    input.activeEnemyCount === 0
                ) {
                    this.beginTransitionOut();
                }
                break;

            case TutorialStage.LearnPerks:
                // Advance when perk selected (XP is granted by TutorialModeUpdate on stage entry)
                if (input.perkJustSelected) {
                    this.beginTransitionOut();
                }
                break;

            case TutorialStage.PerkInfo:
                // Auto-advance after 6 seconds
                if (this.stageTimer > 6000) {
                    this.beginTransitionOut();
                }
                break;

            case TutorialStage.Complete:
                // Check button clicks (C: tutorial_prompt_dialog button handling)
                if (input.mouseClicked) {
                    if (this.hitTest(input.mouseX, input.mouseY, this.skipButtonRect)) {
                        this.reset();
                        return TutorialAction.Skip;
                    }
                    if (this.hitTest(input.mouseX, input.mouseY, this.playButtonRect)) {
                        this.reset();
                        return TutorialAction.PlayGame;
                    }
                    if (this.hitTest(input.mouseX, input.mouseY, this.repeatButtonRect)) {
                        this.start(); // Restart tutorial
                        return TutorialAction.Repeat;
                    }
                }
                break;
        }

        // Check skip button click on non-completion stages
        if (this.stage !== TutorialStage.Complete && input.mouseClicked) {
            if (this.hitTest(input.mouseX, input.mouseY, this.skipButtonRect)) {
                this.reset();
                return TutorialAction.Skip;
            }
        }

        return TutorialAction.None;
    }

    /**
     * Begin fade-out transition for current stage
     * C code: tutorial_stage_transition_timer = 0xFFFFFC18 (-1000)
     */
    private beginTransitionOut(): void {
        // Set positive to start fade-out, which counts up to 1000
        this.transitionTimer = 1;
    }

    /**
     * Render the tutorial text box and buttons
     *
     * C code reference: tutorial_prompt_dialog @ 00408530
     */
    render(grim: GrimInterface, font: BitmapFont | null): void {
        if (!this.active || !font || !font.isLoaded()) return;
        if (this.stage < TutorialStage.Intro || this.stage > TutorialStage.Complete) return;

        const text = STAGE_MESSAGES[this.stage] || '';
        if (!text) return;

        // Calculate alpha from transition timer (C: afStack_5c computation)
        let alpha = 1.0;
        if (this.transitionTimer < -1) {
            // Fading in: alpha = 1.0 - (abs(transitionTimer) / 1000)
            alpha = 1.0 - Math.abs(this.transitionTimer) / 1000;
        } else if (this.transitionTimer > 0) {
            // Fading out: alpha = 1.0 - (transitionTimer / 1000)
            alpha = 1.0 - this.transitionTimer / 1000;
        }
        alpha = Math.max(0, Math.min(1, alpha));
        if (alpha <= 0.01) return;

        // Switch to UI layer for rendering on top of game
        grim.setGraphicsLayer('ui');

        this.renderPromptDialog(grim, font, text, alpha);

        // Render buttons at stage 8 (Complete) — shows "Repeat tutorial", "Play a game", "Skip tutorial"
        if (this.stage === TutorialStage.Complete && this.stageTimer > 1000) {
            const buttonAlpha = Math.min(1.0, (this.stageTimer - 1000) / 1000) * alpha;
            this.renderButtons(grim, font, buttonAlpha);
        }

        // Render "Skip tutorial" button on non-completion stages (C: ui_button_table_c when alpha == 0)
        // Fades in after 1 second, positioned at bottom-left
        if (this.stage !== TutorialStage.Complete && this.stage >= TutorialStage.Intro) {
            const skipAlpha = Math.min(1.0, Math.max(0, (this.stageTimer - 1000) / 1000)) * alpha;
            if (skipAlpha > 0.01) {
                this.renderSkipButton(grim, font, skipAlpha);
            }
        }

        // Reset back to game layer
        grim.setGraphicsLayer('game');
    }

    /**
     * Render the prompt dialog box with text
     *
     * C code: tutorial_prompt_dialog — draws filled rect, outline, centered text
     */
    private renderPromptDialog(grim: GrimInterface, font: BitmapFont, text: string, alpha: number): void {
        const screenW = grim.getWidth();

        // Measure text width (C: grim_measure_text equivalent)
        const textWidth = font.measureText(text);
        const boxWidth = textWidth + this.BOX_PADDING_X * 2;
        const boxHeight = this.TEXT_HEIGHT + this.BOX_PADDING_Y * 2;

        // Center horizontally
        const boxX = (screenW - boxWidth) / 2;
        const boxY = this.BOX_Y;

        // Draw filled background (C: grim_set_color(0,0,0,0xC0*alpha), grim_draw_rect_filled)
        const bgAlpha = Math.floor(192 * alpha); // 0xC0 = 192
        grim.setColor(0, 0, 0, bgAlpha);
        grim.drawRectFilled(boxX, boxY, boxWidth, boxHeight);

        // Draw border outline using 4 lines (C: grim_draw_rect_outline)
        const borderAlpha = Math.floor(255 * alpha);
        grim.setColor(180, 180, 180, borderAlpha);
        const t = this.BORDER_THICKNESS;
        // Top
        grim.drawLine(boxX, boxY, boxX + boxWidth, boxY, t);
        // Bottom
        grim.drawLine(boxX, boxY + boxHeight, boxX + boxWidth, boxY + boxHeight, t);
        // Left
        grim.drawLine(boxX, boxY, boxX, boxY + boxHeight, t);
        // Right
        grim.drawLine(boxX + boxWidth, boxY, boxX + boxWidth, boxY + boxHeight, t);

        // Draw text centered (C: grim_draw_text_small)
        const textX = boxX + this.BOX_PADDING_X;
        const textY = boxY + this.BOX_PADDING_Y;
        grim.setColor(255, 255, 255, borderAlpha);
        font.drawText(grim, text, textX, textY);
    }

    /**
     * Render "Repeat tutorial", "Play a game", "Skip tutorial" buttons
     *
     * C code: tutorial_prompt_dialog button section (ui_button_table_b, _c, _d)
     */
    private renderButtons(grim: GrimInterface, font: BitmapFont, alpha: number): void {
        const screenW = grim.getWidth();
        const buttonY = this.BOX_Y + this.TEXT_HEIGHT + this.BOX_PADDING_Y * 2 + 20;
        const buttonH = this.TEXT_HEIGHT + 8;
        const buttonSpacing = 16;

        const labels = ['Repeat tutorial', 'Play a game', 'Skip tutorial'];
        const widths = labels.map((l) => font.measureText(l) + 20);
        const totalWidth = widths.reduce((s, w) => s + w, 0) + buttonSpacing * (labels.length - 1);
        let x = (screenW - totalWidth) / 2;

        const rects = [this.repeatButtonRect, this.playButtonRect, this.skipButtonRect];

        for (let i = 0; i < labels.length; i++) {
            const bx = x;
            const bw = widths[i];

            // Store for hit-testing
            rects[i].x = bx;
            rects[i].y = buttonY;
            rects[i].w = bw;
            rects[i].h = buttonH;

            // Button background
            const bgAlpha = Math.floor(128 * alpha);
            grim.setColor(40, 40, 60, bgAlpha);
            grim.drawRectFilled(bx, buttonY, bw, buttonH);

            // Button border
            const borderAlpha = Math.floor(200 * alpha);
            grim.setColor(150, 150, 170, borderAlpha);
            grim.drawLine(bx, buttonY, bx + bw, buttonY, 1);
            grim.drawLine(bx, buttonY + buttonH, bx + bw, buttonY + buttonH, 1);
            grim.drawLine(bx, buttonY, bx, buttonY + buttonH, 1);
            grim.drawLine(bx + bw, buttonY, bx + bw, buttonY + buttonH, 1);

            // Button text
            const textAlpha = Math.floor(255 * alpha);
            grim.setColor(255, 255, 255, textAlpha);
            font.drawText(grim, labels[i], bx + 10, buttonY + 4);

            x += bw + buttonSpacing;
        }
    }

    /**
     * Simple AABB hit test
     */
    private hitTest(mx: number, my: number, rect: { x: number; y: number; w: number; h: number }): boolean {
        return mx >= rect.x && mx <= rect.x + rect.w && my >= rect.y && my <= rect.y + rect.h;
    }

    /**
     * Render a standalone "Skip tutorial" button at bottom-left
     *
     * C code: ui_button_table_c.label = s_Skip_tutorial when alpha is 0
     * Position: (10, screen_height - 50) per C code fStack_24 = 10.0, afStack_20[0] = screen_height - 0x32
     */
    private renderSkipButton(grim: GrimInterface, font: BitmapFont, alpha: number): void {
        const screenH = grim.getHeight();
        const label = 'Skip tutorial';
        const bw = font.measureText(label) + 20;
        const bh = this.TEXT_HEIGHT + 8;
        const bx = 10;
        const by = screenH - 50;

        // Store for hit-testing
        this.skipButtonRect.x = bx;
        this.skipButtonRect.y = by;
        this.skipButtonRect.w = bw;
        this.skipButtonRect.h = bh;

        // Button background
        const bgAlpha = Math.floor(128 * alpha);
        grim.setColor(40, 40, 60, bgAlpha);
        grim.drawRectFilled(bx, by, bw, bh);

        // Button border
        const borderAlpha = Math.floor(200 * alpha);
        grim.setColor(150, 150, 170, borderAlpha);
        grim.drawLine(bx, by, bx + bw, by, 1);
        grim.drawLine(bx, by + bh, bx + bw, by + bh, 1);
        grim.drawLine(bx, by, bx, by + bh, 1);
        grim.drawLine(bx + bw, by, bx + bw, by + bh, 1);

        // Button text
        const textAlpha = Math.floor(255 * alpha);
        grim.setColor(255, 255, 255, textAlpha);
        font.drawText(grim, label, bx + 10, by + 4);
    }
}
