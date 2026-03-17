/**
 * GameplayCursor - Renders the in-game cursor/crosshair
 *
 * Implements the multi-layered cursor from the original game:
 *   1. Spread circle at aim position (filled dark + bright outline)
 *   2. Reload clock gauge at aim position (two sprite textures: table + pointer)
 *   3. Aim enhancement overlay (additive glow + crosshair sprite)
 *   4. Animated glow quads around mouse cursor (additive blend, particles texture)
 *   5. Base cursor sprite at mouse position (ui_cursor.jaz, 32×32)
 *
 * C code references:
 *   ui_cursor_render @ 0041a040 (ui_core.c:817-851)
 *   ui_render_aim_indicators @ 0040a510 (ui_core.c:261-393)
 *   ui_render_aim_enhancement @ 0041a320 (ui_core.c:855-892)
 *   ui_draw_clock_gauge @ 004061e0 (ui_core.c:210-234)
 *   ui_draw_clock_gauge_at @ 0040a4c0 (ui_core.c:242-252)
 */

import type { GrimInterface, TextureHandle } from '../engine/GrimInterface';
import type { AssetManager } from '../data/AssetManager';
import type { Player } from '../entities/Player';

export class GameplayCursor {
    // Texture handles
    private particlesHandle: TextureHandle = -1; // game/particles.jaz - glow particles
    private clockTableHandle: TextureHandle = -1; // ui/ui_clockTable.jaz - clock face
    private clockPointerHandle: TextureHandle = -1; // ui/ui_clockPointer.jaz - clock hand
    private aimHandle: TextureHandle = -1; // ui/ui_aim.jaz - aim crosshair
    private arrowHandle: TextureHandle = -1; // ui/ui_arrow.jaz - movement direction arrow

    // Animation timers

    // C: ui_perk_select_idx += frame_dt * 1.1 (line 824)

    // C: perk_screen_anim_timer_b += frame_dt (line 865 — aim enhancement)
    private aimEnhancementTimer: number = 0;

    // Smoothly-interpolated arrow angle (lerps toward player.heading)
    private arrowAngle: number = 0;

    /**
     * Load all cursor-related textures
     * C code (gameplay.c lines 1739-1741, 1797-1799):
     *   texture_cursor_id  = texture_get_or_load_alt("ui/ui_cursor.jaz")
     *   texture_aim_id     = texture_get_or_load_alt("ui/ui_aim.jaz")
     *   ui_clock_table_texture  = texture_get_or_load_alt("ui/ui_clockTable.jaz")
     *   ui_clock_hands_texture  = texture_get_or_load_alt("ui/ui_clockPointer.jaz")
     *   particles_texture  = texture_get_or_load_alt("game/particles.jaz")
     */
    async loadAssets(assetManager: AssetManager, grim: GrimInterface): Promise<void> {
        // Particles sprite sheet (for aim enhancement glow)
        const particlesTexture = await assetManager.getTexture('game/particles.jaz');
        if (particlesTexture) {
            this.particlesHandle = grim.registerTexture('cursor_particles', particlesTexture);
        }

        // Clock gauge: table (face) + pointer (hand)
        const clockTableTexture = await assetManager.getTexture('ui/ui_clockTable.jaz');
        if (clockTableTexture) {
            this.clockTableHandle = grim.registerTexture('clock_table', clockTableTexture);
        }

        const clockPointerTexture = await assetManager.getTexture('ui/ui_clockPointer.jaz');
        if (clockPointerTexture) {
            this.clockPointerHandle = grim.registerTexture('clock_pointer', clockPointerTexture);
        }

        // Aim crosshair sprite
        const aimTexture = await assetManager.getTexture('ui/ui_aim.jaz');
        if (aimTexture) {
            this.aimHandle = grim.registerTexture('aim_crosshair', aimTexture);
        }

        // Movement direction arrow (C: texture_arrow_id from load/arrow.tga, gameplay.c:1700)
        // Note: C uses texture_arrow_id (load/arrow.tga), NOT texture_arrow_alt_id (ui/ui_arrow.jaz).
        const arrowTexture = await assetManager.getTexture('load/arrow.tga');
        if (arrowTexture) {
            this.arrowHandle = grim.registerTexture('move_arrow', arrowTexture);
        }
    }

    /**
     * Update animation timers
     * C code: ui_cursor_render lines 823-824
     */
    update(dt: number): void {
        this.aimEnhancementTimer += dt;
    }

    /**
     * Main render method - draws gameplay cursor layers
     *
     * IMPORTANT: In the full version C code, ui_cursor_render() is NOT called
     * during gameplay_update_and_render(). The function returns at line 634
     * (game_is_full_version() != 0) before reaching ui_cursor_render() at line 658.
     *
     * Only ui_render_aim_indicators() is called (gameplay.c:551), which draws:
     *   1. Spread circle + reload clock gauge (lines 288-319)
     *   2. Aim enhancement glow + crosshair, per living player (lines 380-389)
     *
     * The glow quads and cursor pointer sprite (ui_cursor_render) are ONLY
     * rendered in menus and demo/trial mode — NOT during active gameplay.
     */
    render(grim: GrimInterface, player: Player, cameraOffsetX: number, cameraOffsetY: number): void {
        const mouseX = grim.getMouseX();
        const mouseY = grim.getMouseY();

        // === ui_render_aim_indicators (C: ui_core.c:261-393) ===
        // C: grim_set_config_var(0x13, 5); grim_set_config_var(0x14, 6);
        // = standard alpha blend (SrcAlpha, InvSrcAlpha)
        grim.setBlendMode('normal');

        if (player.isAlive()) {
            // Layer 1: Spread circle at aim/mouse position (C: lines 288-310)
            this.renderSpreadCircle(grim, player, mouseX, mouseY);

            // Layer 2: Reload clock gauge at aim/mouse position (C: lines 311-319)
            if (player.reloadTimer > 0 && player.reloadTimerMax > 0) {
                this.renderClockGauge(grim, mouseX, mouseY, player.reloadTimer, player.reloadTimerMax);
            }

            // Layer 2.5: Movement direction arrow (C: second loop, lines 326-378)
            this.renderMoveArrow(grim, player, cameraOffsetX, cameraOffsetY);

            // Layer 3: Aim enhancement overlay (C: lines 380-389 → ui_render_aim_enhancement)
            this.renderAimEnhancement(grim, mouseX, mouseY);
        }
    }

    /**
     * Render spread circle at aim/mouse position
     * C code: ui_render_aim_indicators lines 288-310
     *
     * spreadRadius = distance(aim, player) * spread_heat * 0.5, min 6.0
     * C: grim_set_uv(0.5, 0.5, 0.5, 0.5) → UV point = solid color fill
     * C: filled color = (0.0, 0.0, 0.1, 0.3)
     * C: outline uses bullet_trail_texture UV(0.5, 0.0, 0.5, 1.0), color(1.0, 1.0, 1.0, 0.55)
     */
    private renderSpreadCircle(grim: GrimInterface, player: Player, mouseX: number, mouseY: number): void {
        // Distance from player screen position (center) to mouse
        const playerScreenX = grim.getWidth() / 2;
        const playerScreenY = grim.getHeight() / 2;
        const dx = mouseX - playerScreenX;
        const dy = mouseY - playerScreenY;
        const distance = Math.sqrt(dx * dx + dy * dy);
        let spreadRadius = distance * player.spreadHeat * 0.5;
        if (spreadRadius < 6.0) {
            spreadRadius = 6.0;
        }

        // Filled dark circle (C: color 0.0, 0.0, 0.1, 0.3)
        grim.setColor(0, 0, 25, 77);
        grim.drawCircleFilled(mouseX, mouseY, spreadRadius);

        // Outline circle (C: color 1.0, 1.0, 1.0, 0.55)
        // (In C this uses bullet_trail_texture, we use plain white)
        grim.setColor(255, 255, 255, 140);
        grim.drawCircleOutline(mouseX, mouseY, spreadRadius);
    }

    /**
     * Render reload clock gauge at aim/mouse position
     * C code: ui_draw_clock_gauge (ui_core.c:210-234)
     * Called via: ui_draw_clock_gauge_at(&aim_screen, 48.0, reload_timer / reload_timer_max)
     *
     * C code flow:
     *   1. grim_set_color(1.0, 0.7, 0.1, 0.8) — orange-amber color set BEFORE call (line 311)
     *   2. ui_draw_clock_gauge_at checks if progress > 0, then calls ui_draw_clock_gauge
     *   3. ui_draw_clock_gauge draws:
     *      - Clock face (ui_clock_table_texture) at 32×32, centered at aim position, no rotation
     *      - Clock hand (ui_clock_hands_texture) at 32×32, same position, rotated by progress
     *   4. The __ftol() calls snap aim_screen_x/y to integer coords for pixel-perfect rendering
     *   5. reload_timer counts DOWN from reload_timer_max to 0
     *      progress = reload_timer / reload_timer_max → starts at 1.0, approaches 0.0
     *      Gauge is visible for the entire reload duration (progress > 0)
     */
    private renderClockGauge(
        grim: GrimInterface,
        aimX: number,
        aimY: number,
        reloadTimer: number,
        reloadTimerMax: number,
    ): void {
        const progress = reloadTimer / reloadTimerMax;
        if (progress <= 0) return;

        // Position: The __ftol() calls just snap aim_x/y to integers.
        // The 32×32 quad draws with its TOP-LEFT at the aim point,
        // giving a natural ~16px bottom-right offset from the aim center.
        // The "radius" parameter (48.0) is NOT used as a pixel offset.
        const gaugeX = Math.floor(aimX);
        const gaugeY = Math.floor(aimY);

        // Color: ui_draw_clock_gauge (line 222) OVERRIDES the color to WHITE:
        //   grim_set_color(1.0, 1.0, 1.0, unaff_EBX)
        // where unaff_EBX = 0.8 (the alpha from the caller's grim_set_color at line 311)
        // The orange (1.0,0.7,0.1) set before the call is overridden, NOT applied.
        const colorR = 255;
        const colorG = 255;
        const colorB = 255;
        const colorA = 204; // 0.8 * 255

        // Draw clock face (table) — no rotation
        if (this.clockTableHandle >= 0) {
            grim.bindTexture(this.clockTableHandle);
            grim.setUV(0, 0, 1, 1);
            grim.setColor(colorR, colorG, colorB, colorA);
            grim.setRotation(0);
            grim.drawQuad(gaugeX, gaugeY, 32, 32);
        }

        // Draw clock pointer (hand) — rotated based on reload progress
        if (this.clockPointerHandle >= 0) {
            grim.bindTexture(this.clockPointerHandle);
            grim.setUV(0, 0, 1, 1);
            grim.setColor(colorR, colorG, colorB, colorA);
            // Progress 1.0→0.0 = full rotation → no rotation
            // Clock hand sweeps as reload progresses
            const rotation = progress * Math.PI * 2;
            grim.setRotation(rotation);
            grim.drawQuad(gaugeX, gaugeY, 32, 32);
            grim.setRotation(0);
        }

        // Fallback if no clock textures loaded
        if (this.clockTableHandle < 0 && this.clockPointerHandle < 0) {
            grim.setColor(colorR, colorG, colorB, colorA);
            const segments = 24;
            const startAngle = -Math.PI / 2;
            const sweepAngle = progress * Math.PI * 2;
            const gaugeRadius = 16;
            const segmentCount = Math.max(1, Math.floor(segments * progress));
            const angleStep = sweepAngle / segmentCount;
            for (let i = 0; i < segmentCount; i++) {
                const a1 = startAngle + i * angleStep;
                const a2 = startAngle + (i + 1) * angleStep;
                grim.drawLine(
                    aimX + Math.cos(a1) * gaugeRadius,
                    aimY + Math.sin(a1) * gaugeRadius,
                    aimX + Math.cos(a2) * gaugeRadius,
                    aimY + Math.sin(a2) * gaugeRadius,
                    2,
                );
            }
        }
    }

    /**
     * Render aim enhancement overlay
     * C code: ui_render_aim_enhancement @ 0041a320 (ui_core.c:855-892)
     *
     * Called from ui_render_aim_indicators third loop (lines 380-389)
     * for each alive player.
     *
     * Draws:
     *   1. Additive glow quad: particles_texture effect 0xd (golden orb),
     *      64×64 at (aimX-32, aimY-32), alpha = cv_aimEnhancementFade (clamped 0-1)
     *   2. Aim crosshair: texture_aim_id (ui/ui_aim.jaz),
     *      20×20 at (aimX-10, aimY-10), normal blend, same alpha
     */
    private renderAimEnhancement(grim: GrimInterface, aimX: number, aimY: number): void {
        // For now, use full alpha (cv_aimEnhancementFade not tracked yet)
        const aimAlpha = 1.0;

        // Step 1: Additive glow using particles (golden orb)
        if (this.particlesHandle >= 0) {
            grim.setBlendMode('add');
            grim.bindTexture(this.particlesHandle);
            // effect_select_texture(0xd) → effect_id_table[0xd] = {0x40, 3}
            grim.setAtlasFrame(4, 3);
            grim.setColor(255, 255, 255, Math.floor(aimAlpha * 255));
            grim.setRotation(0);
            // C: grim_draw_quad(*pfStack_24 - 32.0, pfStack_24[1] - 32.0, 64.0, 64.0)
            grim.drawQuad(aimX - 32, aimY - 32, 64, 64);
        }

        // Step 2: Aim crosshair sprite (normal blend)
        // C: grim_set_config_var(0x14, 6) → normal alpha blend
        grim.setBlendMode('normal');
        if (this.aimHandle >= 0) {
            grim.bindTexture(this.aimHandle);
            grim.setUV(0, 0, 1, 1);
            grim.setColor(255, 255, 255, Math.floor(aimAlpha * 255));
            grim.setRotation(0);
            // C: grim_draw_quad(*pfStack_24 - 10.0, pfStack_24[1] - 10.0, 20.0, 20.0)
            grim.drawQuad(aimX - 10, aimY - 10, 20, 20);
        } else {
            // Fallback: simple crosshair lines if no aim texture
            grim.setColor(255, 255, 255, Math.floor(aimAlpha * 200));
            grim.drawLine(aimX - 8, aimY, aimX - 3, aimY, 1);
            grim.drawLine(aimX + 3, aimY, aimX + 8, aimY, 1);
            grim.drawLine(aimX, aimY - 8, aimX, aimY - 3, 1);
            grim.drawLine(aimX, aimY + 3, aimX, aimY + 8, 1);
            grim.drawCircleFilled(aimX, aimY, 1);
        }
    }

    /**
     * Render movement direction arrow
     * C code: ui_render_aim_indicators second loop (ui_core.c:326-378)
     *
     * Draws a 32×32 textured arrow 60px ahead of the player along the
     * heading direction, rotated to match the heading.
     *
     * C heading convention: heading = atan2(dy,dx) + π/2  (0 = up/north)
     * TS heading convention: heading = atan2(dy,dx)        (0 = right/east)
     *
     * The arrow persists always (C: gated on input-type flag, always true
     * for keyboard). Heading is smoothly interpolated (C: heading_normalize_or_calc
     * + gradual updates via frame_dt * 0.5), so we lerp arrowAngle toward heading.
     *
     * Single-player color: (1.0, 1.0, 1.0, 0.3) — white at 30% alpha.
     */
    private renderMoveArrow(grim: GrimInterface, player: Player, cameraOffsetX: number, cameraOffsetY: number): void {
        if (this.arrowHandle < 0) return;

        // Smoothly interpolate arrow angle toward player heading
        // C: heading is updated gradually via heading += delta * frame_dt * 0.5
        const targetAngle = player.heading;
        let diff = targetAngle - this.arrowAngle;
        // Normalize diff to [-π, π]
        while (diff > Math.PI) diff -= Math.PI * 2;
        while (diff < -Math.PI) diff += Math.PI * 2;
        // Lerp speed: ~8.0 per second gives smooth but responsive tracking
        const lerpSpeed = 8.0;
        const dt = grim.getDeltaTime() / 1000.0;
        if (Math.abs(diff) < 0.01) {
            this.arrowAngle = targetAngle;
        } else {
            this.arrowAngle += diff * Math.min(1.0, lerpSpeed * dt);
        }

        const heading = this.arrowAngle;

        // Player screen position = camera offset + player world position
        // C: fVar5 = camera_offset_x + player.pos_x + cos(angle) * 60 - 16
        //    aim_screen_y = camera_offset_y + player.pos_y + sin(angle) * 60 - 16
        const playerScreenX = cameraOffsetX + player.x;
        const playerScreenY = cameraOffsetY + player.y;

        // Arrow position: 60px ahead along heading direction, centered on 32×32 quad
        const arrowX = playerScreenX + Math.cos(heading) * 60.0 - 16.0;
        const arrowY = playerScreenY + Math.sin(heading) * 60.0 - 16.0;

        // Rotation: arrow.tga sprite points UP at rotation=0.
        // Add π/2 (90° CW) to rotate it to match the heading direction.
        grim.setRotation(heading + Math.PI / 2);

        // C: grim_bind_texture(texture_arrow_id, 0)
        grim.bindTexture(this.arrowHandle);
        grim.setUV(0, 0, 1, 1);

        // Single-player: (1.0, 1.0, 1.0, 0.3) — white at 30% alpha
        grim.setColor(255, 255, 255, 77);

        // C: grim_draw_quad(aim_screen_x, aim_screen_y, 32.0, 32.0)
        grim.drawQuad(arrowX, arrowY, 32, 32);

        // Reset rotation for subsequent draws
        grim.setRotation(0);
    }
}
