/**
 * CreditsScreen.ts - Scrolling credits display UI
 *
 * Port of credits_screen_update() from C code (credits.c:200-426).
 * Displays scrolling credit lines with interactive easter egg:
 * clicking lines containing lowercase 'o' flags them; when all are flagged,
 * secret text is injected at the end.
 *
 * Themed to match StatisticsScreen / LeaderboardScreen:
 * panel texture, BitmapFont text, button texture for BACK, slide-in animation.
 */

import type { GrimInterface, TextureHandle } from '../../engine/GrimInterface';
import type { BitmapFont } from '../../engine/BitmapFont';
import { UIElement } from '../UIElement';
import type { MenuCursor } from '../../rendering/MenuCursor';
import type { SoundSystem } from '../../audio';
import { SoundId } from '../../audio/SoundId';

/** Actions returned by update() */
export const enum CreditsAction {
    None = 0,
    Back = 1,
    AlienZooKeeper = 2,
}

/** Input state for the credits screen */
export interface CreditsInput {
    mouseX: number;
    mouseY: number;
    mouseClicked: boolean;
    cancelPressed: boolean; // ESC
}

/** Single credit line entry */
interface CreditLine {
    text: string;
    flags: number; // 1 = heading, 4 = clicked (easter egg)
}

/**
 * CreditsScreen - displays scrolling credits with themed rendering
 */
export class CreditsScreen {
    private visible: boolean = false;
    private soundSystem: SoundSystem | null = null;

    // ── Shared assets (set via setSharedAssets) ──────────────────────────────
    private panelElement: UIElement;
    private btnTex: TextureHandle = -1;
    private menuCursor: MenuCursor | null = null;
    private assetsLoaded: boolean = false;

    // ── Panel layout (matches StatisticsScreen / LeaderboardScreen) ──────────
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

    // ── SECRET button hit area (shown when easter egg is unlocked) ───────────
    private btnSecret: { x: number; y: number; w: number; h: number } | null = null;

    // ── Credit lines ────────────────────────────────────────────────────────
    private lines: CreditLine[] = [];
    private scrollTime: number = 0;
    private secretLineBaseIndex: number = 0;
    private secretUnlocked: boolean = false;

    // ── Scroll parameters (C code: ~16px per line, ~1 line/sec) ─────────────
    private readonly LINE_HEIGHT = 16;
    private readonly VISIBLE_LINES = 15;
    private readonly SCROLL_SPEED = 1.0; // lines per second
    private readonly FADE_DISTANCE = 24; // px from edges for alpha fade

    // ── Cached line positions for click detection in update() ───────────────
    private cachedLineRects: Array<{ index: number; x: number; y: number; w: number; h: number }> = [];

    constructor() {
        this.panelElement = new UIElement(this.PANEL_TEX_W, this.PANEL_TEX_H, 0, -this.PANEL_TEX_H / 2);
        this.panelElement.startTime = 0;
        this.panelElement.endTime = this.ANIM_DURATION;
    }

    /**
     * Set shared asset handles from MainMenu (avoids duplicate texture loading).
     * Called once after MainMenu has loaded its assets.
     */
    setSharedAssets(panelElement: UIElement, buttonHandle: TextureHandle, menuCursor: MenuCursor): void {
        if (panelElement.isLoaded()) {
            (this.panelElement as any).textureHandle = panelElement.getHandle();
        }
        this.btnTex = buttonHandle;
        this.menuCursor = menuCursor;
        this.assetsLoaded = true;
    }

    /**
     * Set sound system for easter egg click sounds.
     */
    setSoundSystem(soundSystem: SoundSystem): void {
        this.soundSystem = soundSystem;
    }

    /**
     * Show the credits screen
     */
    show(): void {
        this.visible = true;
        this.animTimeline = 0;
        this.btnBack = null;
        this.scrollTime = 0;
        this.secretUnlocked = false;
        this.buildCreditLines();
    }

    /**
     * Hide the credits screen
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
     * Update the credits screen.
     * Returns CreditsAction.Back when user clicks BACK or presses ESC.
     */
    update(dtMs: number, input: CreditsInput): CreditsAction {
        if (!this.visible) return CreditsAction.None;

        // Advance slide-in animation
        if (this.animTimeline < this.ANIM_DURATION) {
            this.animTimeline = Math.min(this.animTimeline + dtMs, this.ANIM_DURATION);
        }

        // Update panel element animation
        this.panelElement.update(dtMs, false, this.animTimeline);

        // Advance scroll (C: _credits_scroll_time += frame_dt)
        this.scrollTime += dtMs / 1000.0;

        // Wrap scroll if past end
        if (this.scrollTime * this.SCROLL_SPEED > this.lines.length + 2) {
            this.scrollTime = 0;
        }

        // ESC → back
        if (input.cancelPressed) {
            return CreditsAction.Back;
        }

        // BACK button click
        if (input.mouseClicked && this.btnBack && this.hitTest(input.mouseX, input.mouseY, this.btnBack)) {
            return CreditsAction.Back;
        }

        // SECRET button click (AlienZooKeeper)
        if (
            input.mouseClicked &&
            this.secretUnlocked &&
            this.btnSecret &&
            this.hitTest(input.mouseX, input.mouseY, this.btnSecret)
        ) {
            return CreditsAction.AlienZooKeeper;
        }

        // Easter egg: click detection on credit lines using cached rects from render
        if (input.mouseClicked) {
            for (const rect of this.cachedLineRects) {
                if (this.hitTest(input.mouseX, input.mouseY, rect)) {
                    this.handleLineClick(rect.index);
                    break;
                }
            }
        }

        return CreditsAction.None;
    }

    /**
     * Render the credits screen
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

        // Content area origin
        const cx = panelX + this.CONTENT_LEFT;
        const cy = pivotY + this.panelElement.offsetY + this.CONTENT_TOP + 20;
        const contentW = 256;

        // ── Title "CREDITS" ─────────────────────────────────────────────────
        grim.setColor(255, 200, 50, 255);
        const title = 'CREDITS';
        const titleW = renderFont.measureText(title);
        renderFont.drawText(grim, title, cx + (contentW - titleW) / 2, cy + 4);

        // ── Scrolling credit lines ──────────────────────────────────────────
        const scrollAreaTop = cy + 28;
        const scrollAreaHeight = this.VISIBLE_LINES * this.LINE_HEIGHT;
        const scrollAreaBottom = scrollAreaTop + scrollAreaHeight;

        // Current scroll position in fractional lines
        const scrollPos = this.scrollTime * this.SCROLL_SPEED;
        const topIndex = Math.floor(scrollPos) - this.VISIBLE_LINES;
        const bottomIndex = Math.floor(scrollPos) + 1;
        const subPixelOffset = (scrollPos - Math.floor(scrollPos)) * this.LINE_HEIGHT;

        // Begin batch for efficiency
        this.cachedLineRects = []; // Reset for this frame
        for (let i = 0; i <= bottomIndex - topIndex; i++) {
            const lineIndex = topIndex + i;
            if (lineIndex < 0 || lineIndex >= this.lines.length) continue;

            const line = this.lines[lineIndex];
            if (!line.text) continue;

            const y = scrollAreaTop + i * this.LINE_HEIGHT - subPixelOffset;

            // Skip lines outside visible area
            if (y < scrollAreaTop - this.LINE_HEIGHT || y > scrollAreaBottom) continue;

            // ── Edge fade (C code: fStack_28 alpha modulation) ──────────
            let alpha = 1.0;
            const fadeTop = scrollAreaTop + this.FADE_DISTANCE;
            const fadeBottom = scrollAreaBottom - this.FADE_DISTANCE;
            if (y < fadeTop) {
                alpha = Math.max(0, (y - scrollAreaTop + this.LINE_HEIGHT) / (this.FADE_DISTANCE + this.LINE_HEIGHT));
            } else if (y > fadeBottom) {
                alpha = Math.max(0, (scrollAreaBottom - y) / this.FADE_DISTANCE);
            }
            alpha = Math.min(1, Math.max(0, alpha));

            // ── Line color (C code: credits_screen_update color logic) ──
            const flags = line.flags;
            let r: number, g: number, b: number;
            if ((flags & 4) !== 0) {
                // Clicked (easter egg) — green tint
                if ((flags & 1) !== 0) {
                    // Heading + clicked
                    r = 230;
                    g = 255;
                    b = 230;
                } else {
                    // Normal + clicked
                    r = 100;
                    g = 180;
                    b = 100;
                }
            } else if ((flags & 1) !== 0) {
                // Heading — white/gold
                r = 255;
                g = 255;
                b = 255;
            } else {
                // Normal — grey
                r = 130;
                g = 130;
                b = 180;
            }

            grim.setColor(r, g, b, Math.round(alpha * 255));

            // Center text within content area (C code: centers on fStack_10 + 140)
            const textW = renderFont.measureText(line.text);
            const textX = cx + (contentW - textW) / 2;
            renderFont.drawText(grim, line.text, textX, y);

            // Cache line rect for click detection in update()
            if (textW > 0) {
                this.cachedLineRects.push({ index: lineIndex, x: textX, y: y - 2, w: textW, h: this.LINE_HEIGHT });
            }
        }

        // ── BACK button ─────────────────────────────────────────────────────
        const buttonWidth = 128;
        const buttonHeight = 32;
        const btnX = cx + (contentW - buttonWidth) / 2;
        const btnY = cy + this.PANEL_TEX_H - 120;

        this.btnBack = { x: btnX, y: btnY, w: buttonWidth, h: buttonHeight };
        const hovered = this.hitTest(mouseX, mouseY, this.btnBack);

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

        // ── SECRET button (visible when easter egg unlocked) ────────────────
        if (this.secretUnlocked) {
            const secretBtnW = 128;
            const secretBtnH = 32;
            const secretBtnX = cx + (contentW - secretBtnW) / 2;
            const secretBtnY = btnY - 40;

            this.btnSecret = { x: secretBtnX, y: secretBtnY, w: secretBtnW, h: secretBtnH };
            const secretHovered = this.hitTest(mouseX, mouseY, this.btnSecret);

            if (this.btnTex >= 0) {
                grim.bindTexture(this.btnTex);
                if (secretHovered) {
                    grim.setColor(255, 220, 100, 255);
                } else {
                    grim.setColor(200, 180, 80, 200);
                }
                grim.setUV(0, 0, 1, 1);
                grim.drawQuad(secretBtnX, secretBtnY, secretBtnW, secretBtnH);
            }

            const secretLabel = 'SECRET';
            const secretLabelW = renderFont.measureText(secretLabel);
            const secretTextX = secretBtnX + (secretBtnW - secretLabelW) / 2;
            const secretTextY = secretBtnY + 10;
            if (secretHovered) {
                grim.setColor(255, 255, 200, 255);
            } else {
                grim.setColor(255, 255, 200, 180);
            }
            renderFont.drawText(grim, secretLabel, secretTextX, secretTextY);
        } else {
            this.btnSecret = null;
        }

        // ── Menu cursor ─────────────────────────────────────────────────────
        if (this.menuCursor) {
            this.menuCursor.render(grim);
        }
    }

    // ── Easter egg logic ────────────────────────────────────────────────────

    /**
     * Handle clicking a credit line.
     * C code: credits_screen_update lines 313-323
     */
    private handleLineClick(index: number): void {
        if (index < 0 || index >= this.lines.length) return;

        const line = this.lines[index];
        if (line.text.includes('o')) {
            // Line contains lowercase 'o' — flag it
            if ((line.flags & 4) === 0) {
                this.soundSystem?.play(SoundId.UI_BONUS);
            }
            line.flags |= 4;
            this.checkSecretUnlock();
        } else {
            // Wrong click — unflag the most recent flagged line
            this.clearLastFlag(index);
        }
    }

    /**
     * Walk backward from index to find the last line with flag 4 and clear it.
     * C code: credits_line_clear_flag (credits.c:27-45)
     */
    private clearLastFlag(fromIndex: number): void {
        for (let i = fromIndex; i >= 0; i--) {
            if ((this.lines[i].flags & 4) !== 0) {
                this.lines[i].flags &= ~4;
                this.soundSystem?.play(SoundId.TROOPER_INPAIN_01);
                return;
            }
        }
    }

    /**
     * Check if all 'o'-containing lines are flagged (easter egg unlock).
     * C code: credits_screen_update lines 361-402
     */
    private checkSecretUnlock(): void {
        if (this.secretUnlocked) return;

        for (const line of this.lines) {
            if (line.text && line.text.includes('o') && (line.flags & 4) === 0) {
                return; // Not all flagged yet
            }
        }

        // All 'o'-containing lines are flagged — unlock secret text!
        this.secretUnlocked = true;
        const base = this.secretLineBaseIndex;
        if (base < this.lines.length) {
            const secretTexts = [
                'Inside Dead Let Mighty Blood',
                'Do Firepower See Mark Of',
                'The Sacrifice Old Center',
                'Yourself Ground First For',
                'Triangle Cube Last Not Flee',
                '0001001110000010101110011',
                '0101001011100010010101100',
                '011111001000111',
                ' 4 bits for index, < OOOPS I me',
                ' 4 bits for index',
            ];
            for (let i = 0; i < secretTexts.length && base + i < this.lines.length; i++) {
                this.lines[base + i].text = secretTexts[i];
                this.lines[base + i].flags |= 4;
            }
        }
    }

    // ── Credit lines construction ───────────────────────────────────────────

    /**
     * Build credit lines from C code (credits_build_lines, credits.c:53-188).
     */
    private buildCreditLines(): void {
        this.lines = [];

        const set = (text: string, flags: number): void => {
            this.lines.push({ text, flags });
        };

        set('', 0);
        set('Crimsonland', 1);
        set('', 0);
        set('', 0);
        set('Game Design:', 1);
        set('Tero Alatalo', 0);
        set('', 0);
        set('Programming:', 1);
        set('Tero Alatalo', 0);
        set('', 0);
        set('Producer:', 1);
        set('Zach Young', 0);
        set('', 0);
        set('2D Art:', 1);
        set('Tero Alatalo', 0);
        set('', 0);
        set('3D Modelling:', 1);
        set('Tero Alatalo', 0);
        set('Timo Palonen', 0);
        set('', 0);
        set('Music:', 1);
        set('10tons entertainment', 0);
        set('Ville Eriksson', 0);
        set('', 0);
        set('Sound Effects:', 1);
        set('Ion Hardie', 0);
        set('Tero Alatalo', 0);
        set('10tons entertainment', 0);
        set('Ville Eriksson', 0);
        set('', 0);
        set('Manual:', 1);
        set('Miikka Kulmala', 0);
        set('Zach Young', 0);
        set('', 0);
        set('Special thanks to:', 1);
        set('Ismo Alatalo, Juho Alatalo', 0);
        set('Peter Hajba / Remedy', 0);
        set('', 0);
        set('Play testers:', 1);
        set('Avraham Petrosyan', 0);
        set('Bryce Baker', 0);
        set('Dan Ruskin', 0);
        set('Dirk Bunk', 0);
        set('Eric Dallaire', 0);
        set('Erik Van Pelt', 0);
        set('Ernie Ramirez', 0);
        set('Ion Hardie', 0);
        set('James C. Smith', 0);
        set('Jarkko Forsbacka', 0);
        set('Jeff McAteer', 0);
        set('Juha Alatalo', 0);
        set('Kalle Hahl', 0);
        set('Lars Brubaker', 0);
        set('Lee Cooper', 0);
        set('Markus Lassila', 0);
        set('Matti Alanen', 0);
        set('Miikka Kulmala', 0);
        set('Mika Alatalo', 0);
        set('Mike Colonnese', 0);
        set('Simon Hallam', 0);
        set('Toni Nurminen', 0);
        set('10tons entertainment', 0);
        set('Ville Eriksson', 0);
        set('Ville Valtonen', 0);
        set('Zach Young', 0);
        set('', 0);
        // Note: C code has "Greeting to:" lines overwriting index 0x42 multiple times
        // We include the last value that stuck
        set('', 0);
        set('2003 (c) 10tons entertainment', 0);
        set('10tons logo by', 0);
        set('Pasi Heinonen', 0);
        set('', 0);
        set('', 0);
        set('', 0);
        set('Uses Vorbis Audio Decompression', 0);
        set('2003 (c) Xiph.Org Foundation', 0);
        set('(see vorbis.txt)', 0);
        set('', 0);
        set('', 0);
        set('', 0);
        set('', 0);
        set('', 0);
        set('', 0);
        set('', 0);

        // Secret line base index (C: credits_secret_line_base_index = 0x54 = 84)
        this.secretLineBaseIndex = this.lines.length;

        // Padding + secret placeholder lines
        set('', 0);
        set('', 0);
        set('', 0);
        set('You can stop watching now.', 0);
        set('', 0);
        set('', 0);
        set('', 0);
        set('', 0);
        set('', 0);
        set('', 0);
        set('', 0);
        set('', 0);
        set('', 0);
        set('', 0);
        set('', 0);

        // More padding
        for (let i = 0; i < 20; i++) {
            set('', 0);
        }

        // Hint lines at very end (C: index 0x77-0x78)
        set('Click the ones with the round one', 0);
        set('...and be patient.', 0);
        set('', 0);
        set('', 0);
        set('', 0);
        set('', 0);
        set('', 0);
    }

    // ── Helpers ──────────────────────────────────────────────────────────────

    private hitTest(mx: number, my: number, rect: { x: number; y: number; w: number; h: number }): boolean {
        return mx >= rect.x && mx <= rect.x + rect.w && my >= rect.y && my <= rect.y + rect.h;
    }
}
