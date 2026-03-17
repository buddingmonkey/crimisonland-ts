/**
 * AlienZooKeeperScreen.ts - Secret match-3 puzzle minigame
 *
 * Port of credits_secret_alien_zookeeper_update() from C code (credits.c:510-769).
 * Accessible through the Credits screen easter egg.
 *
 * 6×6 board of 5 gem types. Click two gems to swap, find 3-in-a-row matches.
 * Matched gems are removed, score increments, timer extends.
 * Timer counts down to zero → Game Over.
 */

import type { GrimInterface, TextureHandle } from '../../engine/GrimInterface';
import type { BitmapFont } from '../../engine/BitmapFont';
import type { MenuCursor } from '../../rendering/MenuCursor';
import type { SoundSystem } from '../../audio';
import { SoundId } from '../../audio/SoundId';
import type { AssetManager } from '../../data';

/** Actions returned by update() */
export const enum AlienZooKeeperAction {
    None = 0,
    Back = 1,
}

/** Input state for the AlienZooKeeper screen */
export interface AlienZooKeeperInput {
    mouseX: number;
    mouseY: number;
    mouseClicked: boolean;
    cancelPressed: boolean;
}

/** Direction of a match: vertical (column) or horizontal (row) */
export const enum MatchDirection {
    Vertical = 0,
    Horizontal = 1,
}

/** Result from the match-3 finder */
export interface MatchResult {
    found: boolean;
    index: number; // start index (row-major; leftmost/topmost of the 3)
    direction: MatchDirection;
}

// ── Constants ────────────────────────────────────────────────────────────────

const BOARD_SIZE = 6;
const BOARD_CELLS = BOARD_SIZE * BOARD_SIZE; // 36
const GEM_TYPES = 5; // 0..4
const CELL_PX = 32;
const BOARD_PX = BOARD_SIZE * CELL_PX; // 192
const REMOVED = -3;
const INITIAL_TIMER_MS = 9600; // C: 0x2580
const MATCH_TIMER_BONUS_MS = 2000;
const TIMER_BAR_HEIGHT = 6;

/** Per-type color tints (r, g, b, a) in 0-255 range matching C code setColor calls */
const GEM_COLORS: [number, number, number, number][] = [
    [255, 128, 128, 255], // Type 0: red   — C: (1.0, 0.5, 0.5, 1.0)
    [128, 128, 255, 255], // Type 1: blue  — C: (0.5, 0.5, 1.0, 1.0)
    [255, 128, 255, 255], // Type 2: magenta — C: (1.0, 0.5, 1.0, 1.0)
    [128, 255, 255, 255], // Type 3: cyan  — C: (0.5, 1.0, 1.0, 1.0)
    [128, 255, 128, 255], // Type 4: green — C: (0.5, 1.0, 0.5, 1.0)
];

/**
 * Scan a 6×6 board for the first 3-in-a-row match.
 *
 * Port of credits_secret_match3_find() (credits.c:430-506).
 * Scans rows first (horizontal), then columns (vertical).
 *
 * Horizontal scan: for each row, iterate cols 0..3 and check
 * board[row*6 + col], board[row*6 + col+1], board[row*6 + col+2].
 *
 * Vertical scan: for each col, iterate rows 0..3 and check
 * board[row*6 + col], board[(row+1)*6 + col], board[(row+2)*6 + col].
 *
 * @returns MatchResult with found=true if a match exists.
 */
export function findMatch3(board: number[]): MatchResult {
    const noMatch: MatchResult = { found: false, index: 0, direction: MatchDirection.Vertical };

    // ── Horizontal scan (C code: first loop, out_dir = 1) ────────────────
    for (let row = 0; row < BOARD_SIZE; row++) {
        for (let col = 0; col < BOARD_SIZE - 2; col++) {
            const idx = row * BOARD_SIZE + col;
            const val = board[idx];
            if (val < 0) continue; // skip removed/empty
            let count = 1;
            if (board[idx + 1] === val) count++;
            if (board[idx + 2] === val) count++;
            if (count === 3) {
                return { found: true, index: idx, direction: MatchDirection.Horizontal };
            }
        }
    }

    // ── Vertical scan (C code: second loop, out_dir = 0) ─────────────────
    for (let col = 0; col < BOARD_SIZE; col++) {
        for (let row = 0; row < BOARD_SIZE - 2; row++) {
            const idx = row * BOARD_SIZE + col;
            const val = board[idx];
            if (val < 0) continue;
            let count = 1;
            if (board[idx + BOARD_SIZE] === val) count++;
            if (board[idx + BOARD_SIZE * 2] === val) count++;
            if (count === 3) {
                return { found: true, index: idx, direction: MatchDirection.Vertical };
            }
        }
    }

    return noMatch;
}

/**
 * Generate a random board with no initial matches.
 * Fills all 36 cells with random 0..4 values, then re-rolls if any match exists.
 * C code: credits_secret_alien_zookeeper_update lines 726-741.
 */
export function generateBoard(): number[] {
    let board: number[];
    do {
        board = [];
        for (let i = 0; i < BOARD_CELLS; i++) {
            board.push(Math.floor(Math.random() * GEM_TYPES));
        }
    } while (findMatch3(board).found);
    return board;
}

/**
 * Remove matched gems from the board (set to REMOVED).
 * C code: lines 664-672 — sets the 3 cells of the match to -3.
 */
export function removeMatch(board: number[], match: MatchResult): void {
    if (!match.found) return;
    const stride = match.direction === MatchDirection.Horizontal ? 1 : BOARD_SIZE;
    board[match.index] = REMOVED;
    board[match.index + stride] = REMOVED;
    board[match.index + stride * 2] = REMOVED;
}

/**
 * Replace removed cells (-3) with random gems.
 * C code: lines 698-708.
 */
export function fillRemovedCells(board: number[]): void {
    for (let i = 0; i < board.length; i++) {
        if (board[i] === REMOVED) {
            board[i] = Math.floor(Math.random() * GEM_TYPES);
        }
    }
}

/**
 * Swap two cells in the board and check for matches.
 * If a match is found, remove it and return true.
 * The swap is always kept (C code does not swap back on no-match).
 */
export function trySwap(board: number[], idxA: number, idxB: number): { matched: boolean; match: MatchResult } {
    // Swap (unconditional, matching C behavior)
    const tmp = board[idxA];
    board[idxA] = board[idxB];
    board[idxB] = tmp;

    const match = findMatch3(board);
    if (match.found) {
        removeMatch(board, match);
        return { matched: true, match };
    }

    // No match — swap stays in place (C code does NOT swap back)
    return { matched: false, match };
}

/**
 * AlienZooKeeper match-3 minigame screen.
 */
export class AlienZooKeeperScreen {
    private visible: boolean = false;

    // ── Board state ──────────────────────────────────────────────────────────
    private board: number[] = [];
    private selectedIndex: number = -1;
    private score: number = 0;
    private timerMs: number = 0;
    private animTimeMs: number = 0;

    // ── Shared assets ────────────────────────────────────────────────────────
    private menuCursor: MenuCursor | null = null;
    private btnTex: TextureHandle = -1;
    private gemTex: TextureHandle = -1;
    private soundSystem: SoundSystem | null = null;
    private assetsReady: boolean = false;

    // ── Button hit rects ─────────────────────────────────────────────────────
    private btnReset: { x: number; y: number; w: number; h: number } | null = null;
    private btnBack: { x: number; y: number; w: number; h: number } | null = null;

    /**
     * Set shared asset handles after loading.
     */
    setSharedAssets(buttonHandle: TextureHandle, menuCursor: MenuCursor): void {
        this.btnTex = buttonHandle;
        this.menuCursor = menuCursor;
    }

    setSoundSystem(soundSystem: SoundSystem): void {
        this.soundSystem = soundSystem;
    }

    /**
     * Load the gem texture (alien sprite sheet).
     * Should be called once during game initialization.
     */
    async loadAssets(assetManager: AssetManager, grim: GrimInterface): Promise<void> {
        const texture = await assetManager.getTexture('game/alien.jaz');
        if (texture) {
            this.gemTex = grim.registerTexture('alien_zookeeper_gems', texture);
        }
        this.assetsReady = true;
    }

    show(): void {
        this.visible = true;
        this.board = generateBoard();
        this.selectedIndex = -1;
        this.score = 0;
        this.timerMs = INITIAL_TIMER_MS;
        this.animTimeMs = 0;
        this.btnReset = null;
        this.btnBack = null;
    }

    hide(): void {
        this.visible = false;
    }

    isVisible(): boolean {
        return this.visible;
    }

    // ── Accessors for testing ────────────────────────────────────────────────
    getBoard(): number[] {
        return this.board;
    }
    getScore(): number {
        return this.score;
    }
    getTimerMs(): number {
        return this.timerMs;
    }
    getSelectedIndex(): number {
        return this.selectedIndex;
    }

    /**
     * Update the AlienZooKeeper screen.
     * Returns AlienZooKeeperAction.Back when user clicks Back.
     */
    update(dtMs: number, input: AlienZooKeeperInput): AlienZooKeeperAction {
        if (!this.visible) return AlienZooKeeperAction.None;

        // Advance animation timer
        this.animTimeMs += dtMs;

        // Advance game timer (count down)
        if (this.timerMs > 0) {
            this.timerMs -= dtMs;
            if (this.timerMs <= 0) {
                this.timerMs = 0;
                this.soundSystem?.play(SoundId.TROOPER_DIE_01);
            }
        }

        // Fill any removed cells with new random gems
        fillRemovedCells(this.board);

        // ESC → back
        if (input.cancelPressed) {
            return AlienZooKeeperAction.Back;
        }

        // Button clicks
        if (input.mouseClicked) {
            // Reset button
            if (this.btnReset && this.hitTest(input.mouseX, input.mouseY, this.btnReset)) {
                this.board = generateBoard();
                this.selectedIndex = -1;
                this.score = 0;
                this.timerMs = INITIAL_TIMER_MS;
                return AlienZooKeeperAction.None;
            }

            // Back button
            if (this.btnBack && this.hitTest(input.mouseX, input.mouseY, this.btnBack)) {
                return AlienZooKeeperAction.Back;
            }
        }

        // Board click — only when timer > 0
        if (input.mouseClicked && this.timerMs > 0) {
            this.handleBoardClick(input.mouseX, input.mouseY);
        }

        return AlienZooKeeperAction.None;
    }

    /**
     * Handle a click on the board area.
     * C code: lines 647-677.
     */
    private handleBoardClick(mx: number, my: number): void {
        // Compute board origin (must match render layout)
        const boardOrigin = this.getBoardOrigin();
        const bx = mx - boardOrigin.x;
        const by = my - boardOrigin.y;

        if (bx < 0 || by < 0 || bx >= BOARD_PX || by >= BOARD_PX) return;

        const col = Math.floor(bx / CELL_PX);
        const row = Math.floor(by / CELL_PX);
        const idx = row * BOARD_SIZE + col;

        // Skip removed cells
        if (this.board[idx] === REMOVED) return;

        this.soundSystem?.play(SoundId.UI_CLINK_01);

        if (this.selectedIndex === -1) {
            // First selection
            this.selectedIndex = idx;
        } else {
            // Second selection — swap
            const result = trySwap(this.board, this.selectedIndex, idx);
            if (result.matched) {
                this.score++;
                this.soundSystem?.play(SoundId.UI_BONUS);
                this.timerMs += MATCH_TIMER_BONUS_MS;
            }
            this.selectedIndex = -1;
        }
    }

    /**
     * Compute the board's top-left origin (centered on screen).
     */
    private getBoardOrigin(): { x: number; y: number } {
        // Fixed layout: board centered at screen center, offset up slightly
        return { x: 304, y: 160 };
    }

    /**
     * Render the AlienZooKeeper screen.
     */
    render(grim: GrimInterface, font: BitmapFont, mouseX: number = 0, mouseY: number = 0): void {
        if (!this.visible) return;

        grim.setGraphicsLayer('ui');
        grim.setRotation(0);

        const width = grim.getWidth();
        const height = grim.getHeight();

        // ── Semi-transparent dark overlay ─────────────────────────────────────
        grim.setColor(0, 0, 0, 180);
        grim.drawRectFilled(0, 0, width, height);

        // ── Layout ───────────────────────────────────────────────────────────
        const boardOrigin = this.getBoardOrigin();
        const bx = boardOrigin.x;
        const by = boardOrigin.y;

        // ── Title "AlienZooKeeper" ───────────────────────────────────────────
        grim.setColor(255, 255, 255, 255);
        const title = 'AlienZooKeeper';
        const titleW = font.measureText(title);
        font.drawText(grim, title, bx + (BOARD_PX - titleW) / 2, by - 40);

        // ── Subtitle ─────────────────────────────────────────────────────────
        grim.setColor(255, 255, 255, 180);
        const sub1 = 'a puzzle game unfinished';
        font.drawText(grim, sub1, bx + 12, by - 24);
        const sub2 = '...or something more?';
        font.drawText(grim, sub2, bx + 18, by - 12);

        // ── Score ────────────────────────────────────────────────────────────
        grim.setColor(255, 255, 255, 180);
        const scoreText = `score: ${this.score}`;
        const scoreW = font.measureText(scoreText);
        font.drawText(grim, scoreText, bx + (BOARD_PX - scoreW) / 2, by - 54);

        // ── Board background (filled + outline) ─────────────────────────────
        grim.setColor(255, 255, 255, 180);
        grim.drawRectFilled(bx, by, BOARD_PX, BOARD_PX);
        grim.setColor(255, 255, 255, 255);
        // Outline: draw 4 lines
        grim.drawLine(bx, by, bx + BOARD_PX, by, 1);
        grim.drawLine(bx + BOARD_PX, by, bx + BOARD_PX, by + BOARD_PX, 1);
        grim.drawLine(bx + BOARD_PX, by + BOARD_PX, bx, by + BOARD_PX, 1);
        grim.drawLine(bx, by + BOARD_PX, bx, by, 1);

        // ── Timer bar ────────────────────────────────────────────────────────
        const timerBarY = by + BOARD_PX + 4;
        const timerFill = Math.min(BOARD_PX, Math.floor(this.timerMs / 100));
        grim.setColor(255, 255, 255, 255);
        if (timerFill > 0) {
            grim.drawRectFilled(bx, timerBarY, timerFill, TIMER_BAR_HEIGHT);
        }
        // Timer bar outline
        grim.drawLine(bx, timerBarY, bx + BOARD_PX, timerBarY, 1);
        grim.drawLine(bx + BOARD_PX, timerBarY, bx + BOARD_PX, timerBarY + TIMER_BAR_HEIGHT, 1);
        grim.drawLine(bx + BOARD_PX, timerBarY + TIMER_BAR_HEIGHT, bx, timerBarY + TIMER_BAR_HEIGHT, 1);
        grim.drawLine(bx, timerBarY + TIMER_BAR_HEIGHT, bx, timerBarY, 1);

        // ── Selection highlight ──────────────────────────────────────────────
        if (this.selectedIndex >= 0 && this.selectedIndex < BOARD_CELLS) {
            const selCol = this.selectedIndex % BOARD_SIZE;
            const selRow = Math.floor(this.selectedIndex / BOARD_SIZE);
            const sx = bx + selCol * CELL_PX + 4;
            const sy = by + selRow * CELL_PX + 4;
            grim.setColor(255, 255, 255, 200);
            grim.drawRectFilled(sx, sy, 24, 24);
            grim.setColor(255, 255, 255, 255);
            grim.drawLine(sx, sy, sx + 24, sy, 1);
            grim.drawLine(sx + 24, sy, sx + 24, sy + 24, 1);
            grim.drawLine(sx + 24, sy + 24, sx, sy + 24, 1);
            grim.drawLine(sx, sy + 24, sx, sy, 1);
        }

        // ── Gem rendering ────────────────────────────────────────────────────
        if (this.assetsReady && this.gemTex >= 0) {
            grim.beginBatch();
            grim.bindTexture(this.gemTex);
            grim.setRotation(0);

            for (let row = 0; row < BOARD_SIZE; row++) {
                for (let col = 0; col < BOARD_SIZE; col++) {
                    const idx = row * BOARD_SIZE + col;
                    const gemType = this.board[idx];
                    if (gemType === REMOVED) continue;

                    // Animated frame index (C: (anim_time / 50 + gemType * 2) & 0x1F)
                    let frameIndex = (Math.floor(this.animTimeMs / 50) + gemType * 2) & 0x1f;
                    // Handle negative modulo (shouldn't happen with unsigned, but be safe)
                    if (frameIndex < 0) frameIndex += 32;

                    grim.setAtlasFrame(8, frameIndex);

                    // Color tint
                    const color = GEM_COLORS[gemType] || GEM_COLORS[0];
                    grim.setColor(color[0], color[1], color[2], color[3]);

                    grim.drawQuad(bx + col * CELL_PX, by + row * CELL_PX, CELL_PX, CELL_PX);
                }
            }

            grim.endBatch();
        }

        // ── Game Over text (flashing) ────────────────────────────────────────
        if (this.timerMs === 0) {
            const flashVal = Math.cos(this.animTimeMs * 0.005);
            if (flashVal > 0) {
                grim.setColor(255, 255, 255, 255);
                const goText = 'Game Over';
                const goW = font.measureText(goText);
                font.drawText(grim, goText, bx + (BOARD_PX - goW) / 2, by + BOARD_PX / 2 - 8);
            }
        }

        // ── Buttons ──────────────────────────────────────────────────────────
        const buttonW = 80;
        const buttonH = 28;
        const buttonY = timerBarY + TIMER_BAR_HEIGHT + 12;

        // Reset button
        const resetX = bx;
        this.btnReset = { x: resetX, y: buttonY, w: buttonW, h: buttonH };
        this.renderButton(grim, font, 'Reset', this.btnReset, mouseX, mouseY);

        // Back button
        const backX = bx + BOARD_PX - buttonW;
        this.btnBack = { x: backX, y: buttonY, w: buttonW, h: buttonH };
        this.renderButton(grim, font, 'Back', this.btnBack, mouseX, mouseY);

        // ── Menu cursor ──────────────────────────────────────────────────────
        if (this.menuCursor) {
            this.menuCursor.render(grim);
        }
    }

    /**
     * Render a button with label.
     */
    private renderButton(
        grim: GrimInterface,
        font: BitmapFont,
        label: string,
        rect: { x: number; y: number; w: number; h: number },
        mouseX: number,
        mouseY: number,
    ): void {
        const hovered = this.hitTest(mouseX, mouseY, rect);

        if (this.btnTex >= 0) {
            grim.bindTexture(this.btnTex);
            grim.setColor(hovered ? 255 : 180, hovered ? 255 : 180, hovered ? 255 : 180, hovered ? 255 : 200);
            grim.setUV(0, 0, 1, 1);
            grim.drawQuad(rect.x, rect.y, rect.w, rect.h);
        }

        const labelW = font.measureText(label);
        grim.setColor(230, 225, 215, hovered ? 255 : 180);
        font.drawText(grim, label, rect.x + (rect.w - labelW) / 2, rect.y + 8);
    }

    private hitTest(mx: number, my: number, rect: { x: number; y: number; w: number; h: number }): boolean {
        return mx >= rect.x && mx <= rect.x + rect.w && my >= rect.y && my <= rect.y + rect.h;
    }
}
