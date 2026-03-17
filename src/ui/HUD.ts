/**
 * HUD - Heads-Up Display
 *
 * Texture-based in-game HUD rendering, ported from C code ui_render_hud()
 * (ui_core.c:993-1557) and hud_update_and_render() (ui_core.c:1566-1644).
 *
 * All coordinates and sizes match the original single-player C code
 * (config_blob.reserved0._20_4_ == 1).
 *
 * C code element overview (single-player path):
 *   Top bar:     drawQuad(0, 0, 512, 64) with gameTop texture
 *   Heart icon:  centered at (27, 21), pulsing size sin²(t*freq)*4+14
 *   Weapon icon: drawQuad(220, 2, 64, 32) from 8×2 wicons atlas
 *   Health bar:  drawQuad(64, 16, 120, 9) with indLife texture
 *   Ammo:        drawQuad(300+i*6, 10, 6, 16) with ammo class texture
 *   XP panel:    drawQuad(-68, iVar2-0x12, 182, 53) with indPanel texture (survival)
 *   Timer:       drawQuad(220, 2, 32, 32) with clockTable/clockPointer (tutorial)
 */

import type { GrimInterface, TextureHandle } from '../engine/GrimInterface';
import type { BitmapFont } from '../engine/BitmapFont';
import type { Player } from '../entities/Player';
import type { ScoreSystem } from '../systems/ScoreSystem';
import type { AssetManager } from '../data/AssetManager';
import { getWeaponStats } from '../data/WeaponData';
import { BonusHudSlots } from './BonusHudSlots';

/**
 * Game mode enum — mirrors Game.ts GameMode ordinal values.
 * Duplicated here to avoid circular dependency (HUD ← Game ← HUD).
 * IMPORTANT: Must match Game.ts GameMode auto-numbered values exactly.
 */
export const enum HudGameMode {
    Survival = 0,
    Rush = 1,
    Quest = 2,
    Tutorial = 3,
}

/** Ammo class → indicator texture path mapping (C: weapon_ammo_class) */
const AMMO_TEXTURE_PATHS: Record<number, string> = {
    0: 'ui/ui_indbullet.jaz', // physical bullet (no underscore!)
    1: 'ui/ui_indfire.jaz', // fire (no underscore!)
    2: 'ui/ui_indrocket.jaz', // rocket (no underscore!)
    3: 'ui/ui_indelectric.jaz', // electric/energy (no underscore!)
};

/**
 * HUD renderer — all rendering matches C code `ui_render_hud`.
 */
export class HUD {
    // Texture handles (-1 = not loaded)
    private topBarTex: TextureHandle = -1; // ui_gameTop.jaz (512×64)
    private heartTex: TextureHandle = -1; // ui_lifeHeart.jaz
    private healthBarTex: TextureHandle = -1; // ui_indLife.jaz (120×9 bar)
    private panelTex: TextureHandle = -1; // ui_indPanel.jaz (182×53)
    private wiconsTex: TextureHandle = -1; // ui_wicons.jaz (8×2 atlas)
    private clockTableTex: TextureHandle = -1; // ui_clockTable.jaz
    private clockHandsTex: TextureHandle = -1; // ui_clockPointer.jaz
    private levelUpTex: TextureHandle = -1; // ui_textLevelUp.jaz (75×25)
    private ammoTextures: Map<number, TextureHandle> = new Map();
    private menuItemTex: TextureHandle = -1; // ui_menuitem.jaz (512×64) — same as main menu
    private bonusTex: TextureHandle = -1; // bonuses.jaz — bonus pickup icons for HUD slots
    private levelCompleteTex: TextureHandle = -1; // ui_textLevComp.jaz (256×32 "Level Complete")

    // Bonus HUD slide panel system (C: bonus_hud_slot_table)
    private bonusHudSlots: BonusHudSlots = new BonusHudSlots();

    // Smoothed XP for animated XP bar (C: survival_xp_smoothed)
    private xpSmoothed: number = 0;

    // Level up banner animation state
    // Banner swings in from right (mirrored menu item) while perk pending, swings out when perk picked
    private levelUpTimer: number = 0; // >0 = swinging in/holding, <0 = swinging out, 0 = hidden
    private static readonly LEVEL_UP_SWING_DURATION = 0.4; // seconds to swing in/out
    // Banner layout — matches main menu UIElement(512, 64, offsetX=-72, offsetY=-60) but mirrored.
    // Pivot is at the right edge of the screen (hinge). Button extends LEFT from pivot.
    // The button's RIGHT edge aligns with the pivot so the dark panel is near the right edge.
    private static readonly BANNER_BTN_W = 512; // native texture width
    private static readonly BANNER_BTN_H = 64; // native texture height
    // offsetY from pivot: same as menu items (-60), so top of button is 60px above pivot.
    // pivotY=60 → button top at y=0 (screen top edge), button bottom at y=64.
    private static readonly BANNER_OFFSET_Y = -60;
    private static readonly BANNER_OFFSET_X = 250;
    private static readonly BANNER_PIVOT_Y = 60; // Y position of pivot
    // Label (LEVEL UP text) position relative to pivot.
    // Main menu label is 343px from button left edge. After UV flip, that maps to
    // 169px from the new left edge = x = -512 + 169 = -343 from pivot.
    private static readonly BANNER_LABEL_OFFSET_X = -450;
    private static readonly BANNER_LABEL_OFFSET_Y = -33;
    private static readonly BANNER_LABEL_W = 75; // ui_textLevelUp.jaz width
    private static readonly BANNER_LABEL_H = 25; // ui_textLevelUp.jaz height

    /**
     * Load HUD textures from PAQ archives. Called once during init.
     */
    async loadAssets(assetManager: AssetManager, grim: GrimInterface): Promise<void> {
        const load = async (path: string, name: string): Promise<TextureHandle> => {
            try {
                const texture = await assetManager.getTexture(path);
                if (texture) {
                    return grim.registerTexture(name, texture);
                }
            } catch {
                /* fall through */
            }
            console.warn(`[HUD] Failed to load: ${path}`);
            return -1;
        };

        [
            this.topBarTex,
            this.heartTex,
            this.healthBarTex,
            this.panelTex,
            this.wiconsTex,
            this.clockTableTex,
            this.clockHandsTex,
        ] = await Promise.all([
            load('ui/ui_gameTop.jaz', 'hud_top_bar'),
            load('ui/ui_lifeHeart.jaz', 'hud_heart'),
            load('ui/ui_indLife.jaz', 'hud_health_bar'),
            load('ui/ui_indPanel.jaz', 'hud_panel'),
            load('ui/ui_wicons.jaz', 'hud_weapon_icons'),
            load('ui/ui_clockTable.jaz', 'hud_clock_table'),
            load('ui/ui_clockPointer.jaz', 'hud_clock_hands'),
        ]);

        for (const [classId, path] of Object.entries(AMMO_TEXTURE_PATHS)) {
            const handle = await load(path, `hud_ammo_${classId}`);
            this.ammoTextures.set(Number(classId), handle);
        }

        this.levelUpTex = await load('ui/ui_textLevelUp.jaz', 'hud_level_up');
        this.menuItemTex = await load('ui/ui_menuitem.jaz', 'hud_menuitem');
        this.bonusTex = await load('game/bonuses.jaz', 'hud_bonus_icons');
        this.levelCompleteTex = await load('ui/ui_textLevComp.jaz', 'hud_level_complete');
    }

    /**
     * Trigger the "LEVEL UP" banner animation.
     * Call this when the player gains a level.
     */
    notifyLevelUp(): void {
        this.levelUpTimer = 0.001; // start animation (small epsilon so it's > 0)
    }

    /**
     * Add a bonus HUD slide panel for an active timed bonus.
     * Port of C bonus_hud_add_slot() @ 0041a810.
     */
    addBonusSlot(label: string, iconId: number, getTimer: () => number, timerKey: string): void {
        this.bonusHudSlots.addSlot(label, iconId, getTimer, timerKey);
    }

    /**
     * Clear all bonus HUD slots (e.g., on game restart).
     */
    clearBonusSlots(): void {
        this.bonusHudSlots.clear();
    }

    /**
     * Render HUD elements — faithful port of C `ui_render_hud`.
     *
     * @param gameMode  HudGameMode ordinal (matches C config_blob.reserved0._24_4_)
     * @param gameTimeS Current game time in seconds (for heart pulse animation)
     */
    render(
        grim: GrimInterface,
        font: BitmapFont,
        player: Player,
        scoreSystem: ScoreSystem,
        gameMode: HudGameMode = HudGameMode.Survival,
        gameTimeS: number = 0,
        dt: number = 0,
        perkPendingCount: number = 0,
        questSystem?: {
            getCurrentQuest(): { name: string; tier: number; index: number } | null;
            getElapsedTimerMs(): number;
            getTransitionTimerMs(): number;
            getStageMajor(): number;
            getStageMinor(): number;
            isActive(): boolean;
            getTimelineMs(): number;
            getTotalKilled(): number;
            getTotalSpawned(): number;
            getPendingSpawnCount(): number;
        },
    ): void {
        // Ensure we're rendering on the UI layer (persists between frames)
        grim.setGraphicsLayer('ui');

        // ══════════════════════════════════════════════════════════════════
        // Determine flag visibility (C: hud_update_and_render lines 1603-1638)
        // ══════════════════════════════════════════════════════════════════
        let showHealth = false;
        let showWeapon = false;
        let showAmmo = false;
        let showXpBar = false;
        let showTimer = false;
        let showQuestPanel = false;

        switch (gameMode) {
            case HudGameMode.Quest:
                // C: reserved0._24_4_ == 3 → hud_show_experience_bar = 1
                // The C experience_bar block (lines 1256-1399) renders quest-specific
                // timer + progress, NOT the survival XP panel.
                showHealth = true;
                showWeapon = true;
                showAmmo = true;
                showQuestPanel = true;
                showXpBar = true;  // XP panel shows below quest timer+progress
                break;
            case HudGameMode.Survival:
            case HudGameMode.Rush:
                // C: reserved0._24_4_ == 1 (survival), 2 (rush)
                showHealth = true;
                showWeapon = true;
                showAmmo = true;
                showXpBar = true; // survival also shows XP bar
                break;
            case HudGameMode.Tutorial:
                // C: reserved0._24_4_ == 4
                showHealth = true;
                showWeapon = false;
                showAmmo = true;
                showTimer = true;
                break;
        }

        // ══════════════════════════════════════════════════════════════════
        // Render HUD (C: ui_render_hud)
        // ══════════════════════════════════════════════════════════════════
        grim.setGraphicsLayer('ui');
        grim.setRotation(0);

        // Alpha multiplier for all HUD elements (fStack_10, in_stack_ffffff8c, etc.)
        // For now, treat as fully visible (1.0)
        const hudAlpha = 1.0;

        // ── Top bar background ──
        // C line 1036-1049: bind iGameUI texture, drawQuad(0, 0, 512, 64)
        if (this.topBarTex >= 0) {
            grim.setBlendMode('normal');
            grim.setUV(0, 0, 1, 1);
            grim.setColor(255, 255, 255, Math.round(hudAlpha * 0.7 * 255));
            grim.bindTexture(this.topBarTex);
            grim.setRotation(0);
            grim.beginBatch();
            grim.drawQuad(0, 0, 512, 64);
            grim.endBatch();
        }

        // ── Heart icon (pulsing) ──
        // C line 1050-1108: single-player: fStack_2c = 21, heart centered at x=27
        if (showHealth && this.heartTex >= 0) {
            grim.setBlendMode('add');
            const cy = 21.0; // C: fStack_2c for single-player
            const freq = player.health < 30 ? 5.0 : 2.0;
            const sinVal = Math.sin(gameTimeS * freq);
            // C: crt_ci_pow() after fsin → sin² (power of 2)
            const halfSize = sinVal * sinVal * 4.0 + 14.0;
            const size = halfSize * 2.0;

            grim.setColor(255, 255, 255, Math.round(hudAlpha * 0.8 * 255));
            grim.bindTexture(this.heartTex);
            grim.setUV(0, 0, 1, 1);
            grim.beginBatch();
            // C line 1105-1106: drawQuad(27 - halfSize, fStack_2c - halfSize, size, size)
            grim.drawQuad(27 - halfSize, cy - halfSize, size, size);
            grim.endBatch();
        }

        // ── Weapon icon ──
        // C line 1110-1137: single-player: drawQuad(220, 2, 64, 32)
        grim.setBlendMode('normal');
        if (showWeapon && this.wiconsTex >= 0) {
            const weaponStats = getWeaponStats(player.weaponId);
            grim.setColor(255, 255, 255, Math.round(hudAlpha * 0.8 * 255));
            grim.bindTexture(this.wiconsTex);
            // C: grim_set_sub_rect(8, 2, 1, hud_icon_id << 1)
            grim.setSubRect(8, 2, 1, weaponStats.hudIconId << 1);
            grim.beginBatch();
            grim.drawQuad(220, 2, 64, 32);
            grim.endBatch();
            grim.setUV(0, 0, 1, 1);
        }

        // ── Health bar ──
        // C line 1139-1173: single-player fVar14=16, drawQuad(64, 16, 120, 9)
        if (showHealth && this.healthBarTex >= 0) {
            grim.setBlendMode('add');
            grim.bindTexture(this.healthBarTex);
            grim.beginBatch();

            // Background bar (dimmed) — C line 1152-1155
            grim.setColor(255, 255, 255, Math.round(hudAlpha * 0.5 * 255));
            grim.setUV(0, 0, 1, 1);
            grim.drawQuad(64, 16, 120, 9);

            // Health fill — C line 1165-1168
            const healthRatio = Math.max(0, Math.min(1, player.health / 100));
            if (healthRatio > 0) {
                grim.setColor(255, 255, 255, Math.round(hudAlpha * 0.8 * 255));
                grim.setUV(0, 0, healthRatio, 1);
                grim.drawQuad(64, 16, healthRatio * 120, 9);
            }

            grim.endBatch();
            grim.setUV(0, 0, 1, 1);
        }

        // ── Ammo indicators ──
        // C line 1174-1249: single-player: fVar14=10, fVar15=300
        if (showAmmo) {
            this.renderAmmo(grim, player, hudAlpha);
        }

        // ── Timer (Tutorial/Survival timer mode) ──
        // C line 1400-1427
        if (showTimer) {
            this.renderTimer(grim, font, scoreSystem, hudAlpha);
        }

        // ── XP panel (Survival mode only) ──
        // C line 1428-1493: panel + XP text + level + progress bar
        if (showXpBar && !showQuestPanel) {
            this.renderXpPanel(grim, font, player, hudAlpha, gameTimeS);
        }

        // ── Quest timer + progress (Quest mode) ──
        // C lines 1256-1399: hud_show_experience_bar block for quest mode
        if (showQuestPanel && questSystem && font) {
            this.renderQuestTimerAndProgress(grim, font, questSystem, hudAlpha);
            // XP panel below progress — same 40px vertical spacing as timer→progress
            // Timer panel at y=67, progress panel at y=107 (40px gap)
            // XP panel at y=147 (another 40px gap)
            if (showXpBar) {
                const questSlideX = questSystem.getTimelineMs() < 1000
                    ? (1000 - questSystem.getTimelineMs()) * -0.128 : 0;
                this.renderXpPanel(grim, font, player, hudAlpha, gameTimeS, questSlideX, 87);
            }
        }

        // ── Bonus HUD slide panels (C: bonus_hud_slot_update_and_render) ──
        this.bonusHudSlots.update(dt);
        if (this.bonusHudSlots.hasActiveSlots() && font) {
            // Stack bonuses below the XP indicator panel.
            // Survival/Rush: XP panel at y=60..113 → startY = 115
            // Quest mode:    XP panel shifted +87 → y=147..200 → startY = 202
            const bonusStartY = (showQuestPanel && showXpBar) ? 202 : 115;
            this.bonusHudSlots.render(grim, font, this.bonusTex, this.panelTex, bonusStartY);
        }

        // ── Level up banner ──
        this.renderLevelUpBanner(grim, dt, perkPendingCount);

        // ── Quest name display (C: ui_core.c:1326-1386 within hud_show_experience_bar block) ──
        if (gameMode === HudGameMode.Quest && questSystem && font) {
            this.renderQuestName(grim, font, questSystem);
        }

        // ── Level Complete overlay (C: ui_core.c:1387-1397) ──
        // Rendered when quest_transition_timer_ms > 0: scale-up animation centered on screen
        if (gameMode === HudGameMode.Quest && questSystem) {
            this.renderLevelComplete(grim, questSystem, hudAlpha);
        }

        grim.setBlendMode('normal');
    }

    /**
     * Ammo indicators — C lines 1174-1249
     *
     * Single-player path: fVar14=10, fVar15=300
     * Each icon: drawQuad(i*6 + 300, 10, 6, 16)
     * Full alpha for remaining ammo, 30% for spent.
     */
    private renderAmmo(grim: GrimInterface, player: Player, hudAlpha: number): void {
        const weaponStats = getWeaponStats(player.weaponId);
        const ammoHandle = this.ammoTextures.get(weaponStats.ammoClass);

        if (!ammoHandle || ammoHandle < 0) return;

        // C line 1175: set rotation and blend mode
        grim.setBlendMode('normal');
        grim.setRotation(0);
        grim.setUV(0, 0, 1, 1);
        grim.bindTexture(ammoHandle);
        grim.beginBatch();

        // C line 1212-1216: clip cap at 30, display cap at 20
        const clipSize = weaponStats.clipSize;
        let displayCount = Math.min(clipSize, 30);
        if (displayCount > 20) displayCount = 20;

        const currentAmmo = Math.floor(player.ammo);

        for (let i = 0; i < displayCount; i++) {
            // C line 1224-1231: full alpha if i < ammo, else 30%
            const alpha = i < currentAmmo ? Math.round(hudAlpha * 255) : Math.round(hudAlpha * 0.3 * 255);
            grim.setColor(255, 255, 255, alpha);
            // C: drawQuad(iVar17 + fVar15, player_index*0xe + fVar14, 6, 16)
            // Single-player: fVar15=300, fVar14=10, player_index=0
            grim.drawQuad(300 + i * 6, 10, 6, 16);
        }

        grim.endBatch();

        // Extra ammo text if ammo > display count
        // C line 1237-1244: grim_draw_text_small_fmt at (iVar6*6 + fVar20 + 8, player*0xe + fVar21 + 1)
        if (currentAmmo > displayCount) {
            grim.setColor(255, 255, 255, Math.round(hudAlpha * 255));
            const textX = displayCount * 6 + 300 + 8;
            grim.drawTextSmall(textX, 11, `+${currentAmmo - displayCount}`);
        }
    }

    /**
     * Timer — C lines 1400-1427
     *
     * Clock table: drawQuad(220, 2, 32, 32) at 90% alpha
     * Clock hands: same position, rotated by elapsed seconds * 0.10471976
     * Text: grim_draw_text_small_fmt(255, 10, "%d seconds", elapsed/1000)
     */
    private renderTimer(grim: GrimInterface, font: BitmapFont, scoreSystem: ScoreSystem, hudAlpha: number): void {
        const alpha = Math.round(hudAlpha * 0.9 * 255);

        // Clock face
        if (this.clockTableTex >= 0) {
            grim.setBlendMode('normal');
            grim.setColor(255, 255, 255, alpha);
            grim.setUV(0, 0, 1, 1);
            grim.bindTexture(this.clockTableTex);
            grim.setRotation(0);
            grim.beginBatch();
            grim.drawQuad(220, 2, 32, 32);
            grim.endBatch();
        }

        // Clock hands (rotating)
        if (this.clockHandsTex >= 0) {
            grim.setBlendMode('add');
            grim.setColor(255, 255, 255, alpha);
            grim.setUV(0, 0, 1, 1);
            grim.bindTexture(this.clockHandsTex);
            // C line 1416-1417: rotation = (elapsed/1000) * 0.10471976 ≈ 2π/60
            const elapsedSeconds = scoreSystem.getSurvivalTime();
            grim.setRotation(elapsedSeconds * 0.10471976);
            grim.beginBatch();
            grim.drawQuad(220, 2, 32, 32);
            grim.endBatch();
            grim.setRotation(0);
        }

        // Timer text
        // C line 1424-1426: grim_draw_text_small_fmt(grim, 255, 10, "%d seconds", elapsed/1000)
        grim.setBlendMode('normal');
        grim.setColor(255, 255, 255, Math.round(hudAlpha * 255));
        font.drawText(grim, scoreSystem.getFormattedTime(), 255, 10);
    }

    /**
     * Level up banner — swings in from right (mirrored main menu item) when level up occurs,
     * stays visible while perk is pending, swings out when perk is picked.
     *
     * Animation: pivot at right edge of screen, rotation from -π/2 → 0 (swing in from right).
     * Texture: ui_menuitem.jaz (same dark button as main menu) + ui_textLevelUp.jaz on top.
     */
    private renderLevelUpBanner(grim: GrimInterface, dt: number, perkPendingCount: number): void {
        const hasPerk = perkPendingCount > 0;

        const dur = HUD.LEVEL_UP_SWING_DURATION;

        // State transitions
        if (hasPerk && this.levelUpTimer <= 0) {
            // Start swing-in: timer goes from 0.001 up to dur
            this.levelUpTimer = 0.001;
        } else if (!hasPerk && this.levelUpTimer > 0) {
            // Start swing-out: reverse from current progress
            // Convert current positive progress to equivalent negative position
            const currentProgress = Math.min(1.0, this.levelUpTimer / dur);
            this.levelUpTimer = -(dur * (1.0 - currentProgress));
        }

        if (this.levelUpTimer === 0) return;

        // Advance timer
        if (this.levelUpTimer > 0) {
            this.levelUpTimer = Math.min(this.levelUpTimer + dt, dur);
        } else {
            this.levelUpTimer = Math.min(this.levelUpTimer + dt, 0);
        }

        // Calculate swing progress: 0 = fully folded (pointing down), 1 = fully open (pointing left)
        let progress: number;
        if (this.levelUpTimer > 0) {
            progress = Math.min(1.0, this.levelUpTimer / dur);
        } else {
            progress = Math.max(0.0, 1.0 + this.levelUpTimer / dur);
        }

        if (progress <= 0) {
            this.levelUpTimer = 0;
            return;
        }

        // Rotation: starts at -π/2 (pointing DOWN, 6 o'clock), rotates clockwise to 0 (pointing LEFT, 9 o'clock)
        // Negative rotation = clockwise in screen space
        const rotation = -(Math.PI / 2) * (1.0 - progress);

        // Pivot beyond canvas right edge so dark panel is partially off-screen right.
        // Use dynamic screen width (original: 1020 at 1024px = screenW - 4)
        const pivotX = grim.getWidth() - 4 + HUD.BANNER_OFFSET_X;
        const pivotY = HUD.BANNER_PIVOT_Y;

        // Create container at pivot (right edge), rotation applied around this point
        const container = grim.createContainer();
        grim.setContainerTransform(container, pivotX, pivotY, rotation);
        grim.setActiveContainer(container);

        const btnW = HUD.BANNER_BTN_W;
        const btnH = HUD.BANNER_BTN_H;
        const offsetY = HUD.BANNER_OFFSET_Y;

        // Draw button background. Full 512px width, right edge at pivot (x=640 on screen).
        // Dark panel (after UV flip) is on the right side, near the right edge of screen.
        if (this.menuItemTex >= 0) {
            grim.setBlendMode('normal');
            grim.setColor(255, 255, 255, 255);
            grim.bindTexture(this.menuItemTex);
            grim.setRotation(0);
            grim.setUV(1, 0, 0, 1); // Horizontally mirrored
            grim.beginBatch();
            grim.drawQuad(-btnW, offsetY, btnW, btnH);
            grim.endBatch();
        }

        // Draw "LEVEL UP" text inside the dark panel area.
        if (this.levelUpTex >= 0) {
            const lblW = HUD.BANNER_LABEL_W;
            const lblH = HUD.BANNER_LABEL_H;
            const lblX = HUD.BANNER_LABEL_OFFSET_X;
            const lblY = HUD.BANNER_LABEL_OFFSET_Y;
            grim.setBlendMode('normal');
            grim.setColor(255, 255, 255, 255);
            grim.bindTexture(this.levelUpTex);
            grim.setRotation(0);
            grim.setUV(0, 0, 1, 1);
            grim.beginBatch();
            grim.drawQuad(lblX, lblY, lblW, lblH);
            grim.endBatch();
        }

        grim.setActiveContainer(null);
    }

    /**
     * XP panel — C lines 1428-1493
     *
     * Panel texture at (-68, iVar2-0x12, 182, 53) where iVar2=0x4e=78
     * → drawQuad(-68, 60, 182, 53)
     * "Exp" text at (4, 78)
     * XP value at (26, 74)
     * Level number at (85, 79)
     */
    private renderXpPanel(
        grim: GrimInterface,
        font: BitmapFont,
        player: Player,
        hudAlpha: number,
        _gameTimeS: number,
        slideX: number = 0,
        yOffset: number = 0,
    ): void {
        // C: iVar2 = 0x4e = 78 initially
        const iVar2 = 0x4e + yOffset; // 78 (or shifted for quest mode)

        // Panel background
        if (this.panelTex >= 0) {
            grim.setBlendMode('normal');
            grim.setColor(255, 255, 255, Math.round(hudAlpha * 255));
            grim.bindTexture(this.panelTex);
            grim.setRotation(0);
            grim.setUV(0, 0, 1, 1);
            grim.beginBatch();
            // C line 1434: drawQuad(-68, iVar2 - 0x12, 182, 53) → (-68, 60, 182, 53)
            grim.drawQuad(slideX - 68, iVar2 - 0x12, 182, 53);
            grim.endBatch();
        }

        // Smooth XP towards actual
        if (player.experience === 0) {
            this.xpSmoothed = 0;
        } else if (this.xpSmoothed < player.experience) {
            const step = Math.max(
                1,
                Math.abs(this.xpSmoothed - player.experience) > 1000
                    ? Math.floor(Math.abs(this.xpSmoothed - player.experience) / 100)
                    : 1,
            );
            this.xpSmoothed = Math.min(player.experience, this.xpSmoothed + step);
        } else if (this.xpSmoothed > player.experience) {
            const step = Math.max(
                1,
                Math.abs(this.xpSmoothed - player.experience) > 1000
                    ? Math.floor(Math.abs(this.xpSmoothed - player.experience) / 100)
                    : 1,
            );
            this.xpSmoothed = Math.max(player.experience, this.xpSmoothed - step);
        }

        // "Xp" label — C line 1470-1471: grim_draw_text_small_fmt(grim, 4, iVar2, ...)
        grim.setColor(255, 255, 255, Math.round(hudAlpha * 0.9 * 255));
        font.drawText(grim, 'Xp', slideX + 4, iVar2);

        // XP value — C line 1472-1473: grim_draw_text_small_fmt(grim, 26, iVar2-4, ...)
        font.drawText(grim, `${this.xpSmoothed}`, slideX + 26, iVar2 - 4);

        // Level — C line 1476-1477: at (85, iVar2+1) with colored text
        // Use player.level (authoritative, advanced by level-up check in GameplayCollisionUpdate)
        grim.setColor(255, 200, 100, Math.round(hudAlpha * 255));
        font.drawText(grim, `${player.level}`, slideX + 85, iVar2 + 1);

        // XP Progress bar — C line 1486-1492: ui_draw_progress_bar
        // Y position: iVar2 + 0xd = iVar2 + 13
        // Width: 54.0
        // Ratio: current_xp / threshold_for_next_level
        // C threshold formula: 1000 + floor(pow(level, 1.8) * 1000)
        const threshold = 1000 + Math.floor(Math.pow(player.level, 1.8) * 1000);
        const xpRatio = Math.min(1.0, player.experience / threshold);

        // Use drawQuad instead of drawRectFilled so bars render on sprite layer (on top of panel)
        grim.bindTexture(-1); // white texture for solid color
        grim.setRotation(0);
        grim.setUV(0, 0, 1, 1);
        grim.setBlendMode('normal');

        // Draw progress bar background (darkened: 60% RGB, 40% alpha)
        const barColor = { r: 100, g: 150, b: 255 }; // Blue color for XP bar
        grim.setColor(
            Math.round(barColor.r * 0.6),
            Math.round(barColor.g * 0.6),
            Math.round(barColor.b * 0.6),
            Math.round(hudAlpha * 0.4 * 255),
        );
        grim.beginBatch();
        grim.drawQuad(slideX + 26, iVar2 + 13, 54, 4);

        // Draw filled portion (full color)
        if (xpRatio > 0) {
            grim.setColor(barColor.r, barColor.g, barColor.b, Math.round(hudAlpha * 0.7 * 255));
            grim.drawQuad(slideX + 26, iVar2 + 14, (54 - 2) * xpRatio, 2);
        }
        grim.endBatch();
    }

    /**
     * Quest timer + progress — C lines 1256-1399 (hud_show_experience_bar block, quest mode)
     *
     * Renders:
     *   Panel 1 (slide-in):  drawQuad(fVar18 - 90, 67, 182, 53)  — slides in over first 1s
     *   Panel 2 (static):    drawQuad(-80, 107, 182, 53)
     *   Clock face:          drawQuad(fVar18 + 2, 78, 32, 32) with clockTable texture
     *   Clock hands:         drawQuad(fVar18 + 2, 78, 32, 32) rotated by (timeline/1000)*0.10471976
     *   Timer text:          draw_text_small_fmt(fVar18 + 34, 86, "m:ss")
     *   "Progress" label:    draw_text_small_fmt(18, 122, "Progress")
     *   Progress bar:        ui_draw_progress_bar(xy, 70, killRatio, rgba) at y ≈ 122
     */
    private renderQuestTimerAndProgress(
        grim: GrimInterface,
        font: BitmapFont,
        questSystem: {
            getTimelineMs(): number;
            getTotalKilled(): number;
            getTotalSpawned(): number;
            getPendingSpawnCount(): number;
            isActive(): boolean;
        },
        hudAlpha: number,
    ): void {
        if (!questSystem.isActive()) return;

        const timelineMs = questSystem.getTimelineMs();

        // ── Slide-in animation (C lines 1264-1266) ──
        // fVar18 starts at -128 and slides to 0 over the first 1000ms of timeline
        let slideX = 0.0;
        if (timelineMs < 1000) {
            slideX = (1000 - timelineMs) * -0.128;
        }

        // ── Panel 1: slide-in panel (C line 1267) ──
        // drawQuad(fVar18 - 90, 67, 182, 53)
        if (this.panelTex >= 0) {
            grim.setBlendMode('normal');
            grim.setColor(255, 255, 255, Math.round(hudAlpha * 255));
            grim.bindTexture(this.panelTex);
            grim.setRotation(0);
            grim.setUV(0, 0, 1, 1);
            grim.beginBatch();
            grim.drawQuad(slideX - 90, 67, 182, 53);
            grim.endBatch();
        }

        // ── Panel 2: slide-in panel (C line 1268) ──
        // drawQuad(-80, 107, 182, 53) — also slides in like Panel 1
        if (this.panelTex >= 0) {
            grim.setBlendMode('normal');
            grim.setColor(255, 255, 255, Math.round(hudAlpha * 255));
            grim.bindTexture(this.panelTex);
            grim.setRotation(0);
            grim.setUV(0, 0, 1, 1);
            grim.beginBatch();
            grim.drawQuad(slideX - 80, 107, 182, 53);
            grim.endBatch();
        }

        // ── Clock face (C lines 1272-1277) ──
        // drawQuad(fVar18 + 2, 78, 32, 32) with clockTable texture at 90% alpha
        if (this.clockTableTex >= 0) {
            grim.setBlendMode('normal');
            grim.setColor(255, 255, 255, Math.round(hudAlpha * 0.9 * 255));
            grim.setUV(0, 0, 1, 1);
            grim.bindTexture(this.clockTableTex);
            grim.setRotation(0);
            grim.beginBatch();
            grim.drawQuad(slideX + 5, 81, 26, 26);
            grim.endBatch();
        }

        // ── Clock hands (C lines 1280-1286) ──
        // Rotation = (quest_spawn_timeline / 1000) * 0.10471976 ≈ 2π/60
        if (this.clockHandsTex >= 0) {
            grim.setBlendMode('add');
            grim.setColor(255, 255, 255, Math.round(hudAlpha * 0.9 * 255));
            grim.setUV(0, 0, 1, 1);
            grim.bindTexture(this.clockHandsTex);
            const elapsedSeconds = Math.floor(timelineMs / 1000);
            grim.setRotation(elapsedSeconds * 0.10471976);
            grim.beginBatch();
            grim.drawQuad(slideX + 5, 81, 26, 26);
            grim.endBatch();
            grim.setRotation(0);
        }

        // ── Timer text (C lines 1287-1296) ──
        // Format: "m:ss" — C: format_time_seconds(quest_spawn_timeline / 1000)
        // C: grim_draw_text_small_fmt at (fVar21, 86), fVar21 = fVar21 + 32 ≈ slideX + 34
        grim.setBlendMode('normal');
        grim.setColor(255, 255, 255, Math.round(hudAlpha * 0.9 * 255));
        const totalSeconds = Math.floor(timelineMs / 1000);
        const minutes = Math.floor(totalSeconds / 60);
        const seconds = totalSeconds % 60;
        const timerText = seconds < 10 ? `${minutes}:0${seconds}` : `${minutes}:${seconds}`;
        font.drawText(grim, timerText, slideX + 34, 86);

        // ── "Progress" label (C lines 1298-1300) ──
        // C: grim_set_config_var(0x18, 0x3ee66666 = 0.45) — smaller font scale
        // C: grim_draw_text_small_fmt(grim, 18, 122, "Progress")
        grim.setColor(255, 255, 255, Math.round(hudAlpha * 0.9 * 255));
        font.drawText(grim, 'Progress', slideX + 18, 122);

        // ── Progress bar (C lines 1301-1324) ──
        // C: ratio = creature_kill_count / (creature_spawned_count + pending)
        // C: ui_draw_progress_bar(xy, 70.0, ratio, rgba)
        // Progress bar color: C lines 1303-1306:
        //   r = 0x3e4ccccd = 0.2, g = 0x3f4ccccd = 0.8, b = 0x3e99999a = 0.3, a = hudAlpha * 0.8
        const totalKilled = questSystem.getTotalKilled();
        const totalSpawned = questSystem.getTotalSpawned();
        const pendingSpawns = questSystem.getPendingSpawnCount();
        const totalEnemies = totalSpawned + pendingSpawns;
        const killRatio = totalEnemies > 0 ? Math.min(1.0, totalKilled / totalEnemies) : 0;

        // Progress bar position — below the "Progress" label
        // C: ui_draw_progress_bar uses xy from stack, positioned at roughly (26, 135)
        // The bar is 70px wide, 4px tall
        const barX = slideX + 16;
        const barY = 138;
        const barWidth = 60;

        grim.bindTexture(-1); // solid color (no texture)
        grim.setRotation(0);
        grim.setUV(0, 0, 1, 1);
        grim.setBlendMode('normal');

        // Background bar (C: rgba * 0.6 for RGB, rgba[3] * 0.4 for alpha)
        // C color: r=0.2*0.6=0.12, g=0.8*0.6=0.48, b=0.3*0.6=0.18
        grim.setColor(
            Math.round(0.12 * 255),
            Math.round(0.48 * 255),
            Math.round(0.18 * 255),
            Math.round(hudAlpha * 0.8 * 0.4 * 255),
        );
        grim.beginBatch();
        grim.drawQuad(barX, barY, barWidth, 4);

        // Filled portion (C: full rgba color)
        // C color: r=0.2, g=0.8, b=0.3, a=hudAlpha*0.8
        if (killRatio > 0) {
            grim.setColor(
                Math.round(0.2 * 255),
                Math.round(0.8 * 255),
                Math.round(0.3 * 255),
                Math.round(hudAlpha * 0.8 * 255),
            );
            grim.drawQuad(barX, barY + 1, (barWidth - 2) * killRatio, 2);
        }
        grim.endBatch();
    }

    /**
     * Quest name display — C lines 1326-1386 in ui_render_hud
     *
     * Draws the quest name centered on screen using the mono font,
     * with a 2-second fade-in/hold/fade-out animation based on quest_elapsed_timer_ms.
     * Also draws the stage number (e.g. "1-1") below it at 50% alpha.
     *
     * C font rendering details:
     * - grim_draw_text_mono with scale 0.8: each character quad = 25.6×25.6px, advance = 12.8px
     * - We use grim.drawText() with fontSize ~24px to match this visual weight.
     */
    private renderQuestName(
        grim: GrimInterface,
        _font: BitmapFont,
        questSystem: {
            getCurrentQuest(): { name: string; tier: number; index: number } | null;
            getElapsedTimerMs(): number;
            getStageMajor(): number;
            getStageMinor(): number;
            isActive(): boolean;
            getTimelineMs(): number;
            getTotalKilled(): number;
            getTotalSpawned(): number;
            getPendingSpawnCount(): number;
        },
    ): void {
        if (!questSystem.isActive()) return;

        const quest = questSystem.getCurrentQuest();
        if (!quest) return;

        const elapsed = questSystem.getElapsedTimerMs();

        // ── Fade animation (C lines 1326-1341) ──
        // 0-500ms:     fade in  → alpha = (elapsed * 2) * 0.001
        // 500-1500ms:  hold     → alpha = 1.0
        // 1500-2000ms: fade out → alpha = 1.0 - (elapsed * 2 - 3000) * 0.001
        // 2000ms+:     hidden   → alpha = 0.0
        let fadeAlpha: number;
        if (elapsed < 500) {
            fadeAlpha = Math.min(1.0, elapsed * 2 * 0.001);
        } else if (elapsed < 1500) {
            fadeAlpha = 1.0;
        } else if (elapsed < 2000) {
            fadeAlpha = Math.max(0.0, Math.min(1.0, 1.0 - (elapsed * 2 - 3000) * 0.001));
        } else {
            fadeAlpha = 0.0;
        }

        if (fadeAlpha <= 0) return;

        const screenW = grim.getWidth();
        const screenH = grim.getHeight();

        // ── Quest name text (C lines 1346-1364) ──
        // C: grim_set_config_var(0x18, 0x3f4ccccd = 0.8) — font scale
        // C: grim_draw_text_mono renders at scale*32 = 25.6px quads, scale*16 = 12.8px advance
        // C: smaller scale 0x3f400000 = 0.75 when screen_width < 641
        // Using grim.drawText() with monospace font to match the larger C mono font.
        const monoFontSize = screenW < 641 ? 20 : 24;
        // Monospace character width ≈ fontSize * 0.6
        const monoCharWidth = monoFontSize * 0.6;

        const name = quest.name;
        const nameTextWidth = name.length * monoCharWidth;
        // C: screen_width/2 - strlen * scale * 8.0 (centers the text)
        const nameX = Math.floor(screenW / 2 - nameTextWidth / 2);
        // C: screen_height/2 - 0x20
        const nameY = Math.floor(screenH / 2 - 32);

        const nameColor = `rgba(255,255,255,${fadeAlpha.toFixed(3)})`;
        grim.drawText(nameX, nameY, name, monoFontSize, nameColor);

        // ── Stage number (C lines 1367-1385) ──
        // Format: "major-minor" (e.g. "1-1")
        // C: grim_set_color(1,1,1, fVar16 * 0.5) → 50% alpha relative to fade
        let stageMajor = questSystem.getStageMajor();
        let stageMinor = questSystem.getStageMinor();
        // C: normalize stage_minor > 10 → increment major, subtract 10
        if (stageMinor > 10) {
            stageMajor += 1;
            stageMinor -= 10;
        }
        const stageText = `${stageMajor}-${stageMinor}`;
        const stageFontSize = Math.floor(monoFontSize * 0.75);
        const stageCharWidth = stageFontSize * 0.6;
        const stageTextWidth = stageText.length * stageCharWidth;
        const stageX = Math.floor(screenW / 2 - stageTextWidth / 2);
        // Below the quest name, with some spacing
        const stageY = nameY + monoFontSize + 6;

        const stageAlpha = fadeAlpha * 0.5;
        const stageColor = `rgba(255,255,255,${stageAlpha.toFixed(3)})`;
        grim.drawText(stageX, stageY, stageText, stageFontSize, stageColor);
    }

    /**
     * Level Complete overlay — C lines 1387-1397 in ui_render_hud
     *
     * When quest_transition_timer_ms > 0, draws the "Level Complete" texture
     * (ui_textLevComp.jaz) centered on screen with a scale-up animation.
     *
     * C code:
     *   fVar21 = quest_transition_timer_ms * 0.0004 * 0.13 + 0.95
     *   grim_set_color(1,1,1, alpha * hudAlpha)
     *   grim_bind_texture(texture_level_complete_id, 0)
     *   grim_draw_quad(
     *       screen_width/2 - fVar21*128,
     *       screen_height/2 - fVar21*16,
     *       fVar21*256, fVar21*32
     *   )
     */
    private renderLevelComplete(
        grim: GrimInterface,
        questSystem: {
            getTransitionTimerMs(): number;
        },
        hudAlpha: number,
    ): void {
        const transitionMs = questSystem.getTransitionTimerMs();
        if (transitionMs <= 0) return;
        if (this.levelCompleteTex < 0) return;

        // C: fVar21 = quest_transition_timer_ms * 0.0004 * 0.13 + 0.95
        // Scale starts at 0.95 and grows slowly over time
        const scale = transitionMs * 0.0004 * 0.13 + 0.95;

        const screenW = grim.getWidth();
        const screenH = grim.getHeight();

        // C lines 1390-1396: centered quad, alpha from HUD alpha
        grim.setBlendMode('normal');
        grim.setColor(255, 255, 255, Math.round(hudAlpha * 255));
        grim.bindTexture(this.levelCompleteTex);
        grim.setRotation(0);
        grim.setUV(0, 0, 1, 1);
        grim.beginBatch();
        grim.drawQuad(
            screenW / 2 - scale * 128,
            screenH / 2 - scale * 16,
            scale * 256,
            scale * 32,
        );
        grim.endBatch();
    }
}
