/**
 * ScreenFade - Fullscreen black overlay for state transitions
 *
 * C code: grim_draw_fullscreen_color(0, 0, 0, screen_fade_alpha)
 * Called at end of gameplay_render_world (L89-91) and in game_update_generic_menu (L298).
 *
 * The C game uses screen_fade_alpha (0.0–1.0) ramped by frame_dt * 2.0 or 3.0
 * to achieve smooth fade-to-black and fade-from-black transitions:
 * - Fade-in: alpha ramps from 1.0 → 0.0 (screen starts black, becomes visible)
 * - Fade-out: alpha ramps from 0.0 → 1.0 (screen becomes black)
 */

import type { GrimInterface } from '../engine/GrimInterface';

export class ScreenFade {
    private alpha: number = 0;
    private direction: number = 0; // -1 = fading in, +1 = fading out, 0 = idle
    private speed: number = 2.0; // alpha change per second (C: frame_dt * 2.0)

    /**
     * Start fade-in (screen starts black, fades to transparent).
     * C: screen_fade_alpha = 1.0; screen_fade_in_flag = true
     * @param speed Alpha change per second (default 2.0, matching C frame_dt * 2.0)
     */
    fadeIn(speed: number = 2.0): void {
        this.alpha = 1.0;
        this.direction = -1;
        this.speed = speed;
    }

    /**
     * Start fade-out (screen fades to black).
     * C: screen_fade_alpha ramps 0→1
     * @param speed Alpha change per second (default 2.0)
     */
    fadeOut(speed: number = 2.0): void {
        this.direction = 1;
        this.speed = speed;
    }

    /**
     * Update fade alpha.
     * C: screen_fade_alpha += direction * frame_dt * speed
     * @param dt Delta time in seconds
     */
    update(dt: number): void {
        if (this.direction !== 0) {
            this.alpha += this.direction * this.speed * dt;
            if (this.alpha <= 0) {
                this.alpha = 0;
                this.direction = 0;
            } else if (this.alpha >= 1.0) {
                this.alpha = 1.0;
                this.direction = 0;
            }
        }
    }

    /**
     * Render the fade overlay.
     * C: grim_draw_fullscreen_color(0, 0, 0, screen_fade_alpha)
     * Draws on the current graphics layer (should be game layer, above world, below HUD).
     */
    render(grim: GrimInterface): void {
        if (this.alpha > 0) {
            grim.drawFullscreenColor(0, 0, 0, Math.floor(this.alpha * 255));
        }
    }

    /** Get current alpha (0.0–1.0) */
    getAlpha(): number {
        return this.alpha;
    }

    /** Whether the overlay is currently visible */
    isActive(): boolean {
        return this.alpha > 0;
    }

    /** Whether a fade-out has completed (alpha reached 1.0 and stopped) */
    isFadeOutComplete(): boolean {
        return this.alpha >= 1.0 && this.direction === 0;
    }

    /** Whether any fade animation is in progress */
    isFading(): boolean {
        return this.direction !== 0;
    }

    /** Force alpha to a specific value (for instant transitions) */
    setAlpha(alpha: number): void {
        this.alpha = Math.max(0, Math.min(1, alpha));
        this.direction = 0;
    }
}
