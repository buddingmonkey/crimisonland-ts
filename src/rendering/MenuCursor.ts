/**
 * MenuCursor - Renders the menu cursor with glow effect
 *
 * Implements ui_cursor_render @ 0041a040 (ui_core.c:817-851)
 * This is the cursor used in menus and non-gameplay states.
 * During gameplay (full version), this is NOT rendered — only
 * ui_render_aim_indicators (GameplayCursor) is used.
 *
 * Rendering layers:
 *   1. Animated glow quads (additive blend, particles texture, golden orb)
 *   2. Cursor pointer sprite (normal blend, ui_cursor.jaz, 32×32)
 */

import type { GrimInterface, TextureHandle } from '../engine/GrimInterface';
import type { AssetManager } from '../data/AssetManager';

export class MenuCursor {
    private cursorHandle: TextureHandle = -1; // ui/ui_cursor.jaz
    private particlesHandle: TextureHandle = -1; // game/particles.jaz

    // Animation timers (C: ui_cursor_render lines 823-824)
    // perk_screen_anim_timer_a += frame_dt
    // ui_perk_select_idx += frame_dt * 1.1
    private glowTimer: number = 0;
    private rotationTimer: number = 0;

    /**
     * Load cursor textures
     * C: texture_cursor_id = texture_get_or_load_alt("ui/ui_cursor.jaz")
     *    particles_texture = texture_get_or_load_alt("game/particles.jaz")
     */
    async loadAssets(assetManager: AssetManager, grim: GrimInterface): Promise<void> {
        const cursorTexture = await assetManager.getTexture('ui/ui_cursor.jaz');
        if (cursorTexture) {
            this.cursorHandle = grim.registerTexture('menu_cursor_glow', cursorTexture);
        }

        const particlesTexture = await assetManager.getTexture('game/particles.jaz');
        if (particlesTexture) {
            this.particlesHandle = grim.registerTexture('menu_cursor_particles', particlesTexture);
        }
    }

    /**
     * Update animation timers (C: lines 823-824)
     * Note: MainMenu passes dt in milliseconds, but C code's frame_dt is in seconds.
     * We convert to seconds here for correct timing.
     */
    update(dt: number): void {
        const dtSeconds = dt / 1000;
        this.glowTimer += dtSeconds;
        this.rotationTimer += dtSeconds * 1.1;
    }

    /**
     * Render the menu cursor with glow
     * C code: ui_cursor_render (ui_core.c:817-851)
     *
     * 1. Bind particles_texture, effect_select_texture(0xd) → setAtlasFrame(4, 3)
     *    grim_set_config_var(0x14, 2) → additive blend
     *    alpha = (sin(rotationTimer) + 2.0) * 0.32
     *    Draw 4 overlapping glow quads at mouse position
     *
     * 2. Bind texture_cursor_id (ui/ui_cursor.jaz)
     *    grim_set_config_var(0x14, 6) → normal blend
     *    Draw 32×32 at (mouseX - 2, mouseY - 2)
     */
    render(grim: GrimInterface): void {
        const mouseX = grim.getMouseX();
        const mouseY = grim.getMouseY();

        // === Glow quads (C: lines 825-840) ===
        // C code: fsin(rotationTimer) → crt_ci_pow() → (result + 2.0) * 0.32
        // The crt_ci_pow() squares the sine result for smoother pulsing:
        //   sin²(t) range [0, 1] → (sin²(t) + 2.0) * 0.32 = range [0.64, 0.96]
        // This gives a gentle glow pulse that never drops too low.
        const sinVal = Math.sin(this.rotationTimer);
        const sinSquared = sinVal * sinVal; // crt_ci_pow = squaring
        const alpha = (sinSquared + 2.0) * 0.32; // Range [0.64, 0.96]

        grim.setBlendMode('add');

        if (this.particlesHandle >= 0) {
            grim.bindTexture(this.particlesHandle);
            // effect_select_texture(0xd) → effect_id_table[0xd] = {0x40, 3}
            grim.setAtlasFrame(4, 3);
            grim.setColor(255, 255, 255, Math.floor(alpha * 255));
            grim.setRotation(0);

            // C: 4 overlapping glow quads (lines 835-839)
            grim.drawQuad(mouseX - 28, mouseY - 28, 64, 64);
            grim.drawQuad(mouseX - 10, mouseY - 18, 64, 64);
            grim.drawQuad(mouseX - 18, mouseY - 10, 64, 64);
            // C: (mouseX - 64 + 16, mouseY - 64 + 16, 128, 128)
            grim.drawQuad(mouseX - 48, mouseY - 48, 128, 128);
        }

        // === Cursor sprite (C: lines 841-849) ===
        grim.setBlendMode('normal');

        if (this.cursorHandle >= 0) {
            grim.bindTexture(this.cursorHandle);
            grim.setUV(0, 0, 1, 1);
            grim.setColor(255, 255, 255, 255);
            grim.setRotation(0);
            // C: grim_draw_quad(ui_mouse_x - 2.0, ui_mouse_y - 2.0, 32.0, 32.0)
            grim.drawQuad(mouseX - 2, mouseY - 2, 32, 32);
        }
    }
}
