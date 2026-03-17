/**
 * GameRenderer - Render functions extracted from Game.ts.
 *
 * Contains renderGame() and renderConsole() rendering logic.
 */

import type { GrimInterface } from '../engine/GrimInterface';
import { gameConsole } from '../console/Console';
import { getBonusLabel } from '../data/BonusLabels';
import type { ScreenFade } from './ScreenFade';
import { drawFreezeOverlay, drawMonsterVisionGlow, type EntityTextureContext } from './EntityRenderer';
import { drawIonLightningBolts, type ProjectileTextureContext } from './ProjectileRenderer';
import { ProjectileType } from '../data/WeaponData';
import { TERRAIN_BUFFER } from './TerrainRenderer';

/**
 * Duck-typed context for game rendering functions.
 * Subset of Game fields needed by renderGame / renderConsole.
 */
export interface GameRenderContext {
    grim: GrimInterface;
    player: any;
    font: any;
    cameraShake: { getOffset(): { x: number; y: number } };
    cameraOffsetX: number;
    cameraOffsetY: number;
    _terrainSprite: any;
    terrainRenderer: any;
    terrainTextureHandle: number;
    debugRenderMode: boolean;
    debugEnemyHeading: boolean;
    spriteRenderer: any;
    weaponSystem: {
        render(grim: GrimInterface, spriteRenderer: any, debug: boolean): void;
        getActiveProjectiles(): Array<{
            x: number; y: number; angle: number; lifetime: number;
            projectileType: number; speedScale: number; ionMasterScale: number;
        }>;
    };
    enemySpawner: {
        render(grim: GrimInterface, perkSystem: any, spriteRenderer: any, debug: boolean, player?: any): void;
        getActiveEnemies(): any[];
        getAllVisibleEnemies(): any[];
    };
    perkSystem: any;
    bonusSystem: {
        render(grim: GrimInterface, spriteRenderer: any, animTimer: number, elapsedMs: number): void;
        getBonuses(): Array<{ x: number; y: number; type: number; amount: number; isActive(): boolean }>;
    };
    bonusAnimTimer: number;
    particleSystem: { render(grim: GrimInterface, spriteCtx?: any): void };
    effectSystem: { render(grim: GrimInterface, spriteCtx?: any): void };
    bloodEffectSystem: { renderBloodEffects(grim: GrimInterface): void };
    scoreSystem: { getSurvivalTime(): number };
    gameplayCursor: { render(grim: GrimInterface, player: any, shakeX: number, shakeY: number): void };
    hud: {
        render(
            grim: GrimInterface,
            font: any,
            player: any,
            scoreSystem: any,
            gameMode: number,
            gameTime: number,
            dt: number,
            perkPendingCount: number,
            questSystem?: any,
        ): void;
    };
    gameMode: number;
    tutorialSystem: { isActive(): boolean; render(grim: GrimInterface, font: any): void };
    perkPromptTimer: number;
    perkPendingCount: number;
    screenFade?: ScreenFade;
    questSystem?: {
        getCurrentQuest(): { name: string; tier: number; index: number } | null;
        getElapsedTimerMs(): number;
        getStageMajor(): number;
        getStageMinor(): number;
        isActive(): boolean;
        getTimelineMs(): number;
        getTotalKilled(): number;
        getTotalSpawned(): number;
        getPendingSpawnCount(): number;
        getTransitionTimerMs(): number;
    };
    /** When true, skip rendering the gameplay cursor (reticle/crosshair).
     *  Used by overlay states (pause, perk selection, game over, quest screens)
     *  to prevent the reticle from showing through the menu UI.
     *  C code: ui_render_aim_indicators is NOT called during overlay states. */
    suppressGameplayCursor?: boolean;
}

/**
 * Render gameplay — terrain, entities, HUD, cursor.
 */
export function renderGame(ctx: GameRenderContext): void {

    // Draw ground/terrain background
    // C: terrain_render() draws a fullscreen quad with UV = -camOffset/terrainSize.
    // Instead of TilingSprite (which wraps), we use a regular Sprite with buffer zones
    // so blood/corpse stamps near edges don't appear on the opposite side.
    if (ctx._terrainSprite && !ctx.debugRenderMode) {
        // Reset scale to 1:1 (menu may have scaled up to fill viewport)
        ctx._terrainSprite.scale.set(1, 1);
        ctx._terrainSprite.x = ctx.cameraOffsetX - TERRAIN_BUFFER;
        ctx._terrainSprite.y = ctx.cameraOffsetY - TERRAIN_BUFFER;
        ctx._terrainSprite.visible = true;
    } else if (ctx.terrainRenderer && ctx.terrainTextureHandle >= 0 && !ctx.debugRenderMode) {
        ctx.grim.bindTexture(ctx.terrainTextureHandle);
        ctx.grim.setColor(255, 255, 255, 255);
        ctx.grim.setUV(0, 0, 1, 1);
        ctx.grim.drawQuad(0, 0, ctx.grim.getWidth(), ctx.grim.getHeight());
    } else if (!ctx.debugRenderMode) {
        const time = ctx.grim.getTime();
        const groundColor = Math.sin(time / 1000) * 10 + 40;
        ctx.grim.setColor(groundColor, groundColor / 2, groundColor / 2, 255);
        ctx.grim.drawRectFilled(0, 0, ctx.grim.getWidth(), ctx.grim.getHeight());
    }

    // Apply camera offset (shake already included)
    ctx.grim.setCameraOffset(ctx.cameraOffsetX, ctx.cameraOffsetY);

    // Render order matches C gameplay_render_world:
    // 1. Dead player (rendered under enemies)
    // 2. Enemies
    // 3. Alive player with glow effects (rendered over enemies)
    // 4. Projectiles (rendered over everything)

    // Dead player first (C: player_render_overlays for dead player)
    if (ctx.player && !ctx.player.isAlive()) {
        ctx.player.render(ctx.grim, ctx.spriteRenderer, ctx.debugRenderMode, ctx.perkSystem);
    }

    // Monster Vision glow pass — yellow disc under enemies (C: creature_render_all L576-587)
    // Drawn BEFORE creature sprites, matching C render order.
    if (ctx.spriteRenderer && ctx.perkSystem?.hasPerk?.(0x1e /* PerkId.MONSTER_VISION */)) {
        const spriteCtx = ctx.spriteRenderer as unknown as EntityTextureContext;
        const visibleEnemies = ctx.enemySpawner.getAllVisibleEnemies();
        drawMonsterVisionGlow(spriteCtx, ctx.grim, visibleEnemies);
    }

    // Render enemies
    ctx.enemySpawner.render(ctx.grim, ctx.perkSystem, ctx.spriteRenderer, ctx.debugRenderMode, ctx.player);

    // Freeze overlay pass — ice crystal on every living enemy (C creatures.c L624-658)
    // Drawn AFTER creature_render_type, BEFORE player overlay, matching C render order.
    if (ctx.player && ctx.player.freezeTimer > 0 && ctx.spriteRenderer) {
        const spriteCtx = ctx.spriteRenderer as unknown as EntityTextureContext;
        const visibleEnemies = ctx.enemySpawner.getAllVisibleEnemies();
        drawFreezeOverlay(spriteCtx, ctx.grim, visibleEnemies, ctx.player.freezeTimer);
    }

    // Alive player with glow effects (C: player_render_overlays for alive player)
    if (ctx.player && ctx.player.isAlive()) {
        ctx.player.render(ctx.grim, ctx.spriteRenderer, ctx.debugRenderMode, ctx.perkSystem);
    }

    // Render projectiles
    ctx.weaponSystem.render(ctx.grim, ctx.spriteRenderer, ctx.debugRenderMode);

    // Ion lightning bolt pass — C: projectiles.c lines 1848-1890
    // Dying ION projectiles (lifetime < 0.4) draw lightning bolts to nearby enemies
    if (ctx.spriteRenderer && !ctx.debugRenderMode) {
        const projectiles = ctx.weaponSystem.getActiveProjectiles();
        const enemies = ctx.enemySpawner.getActiveEnemies();
        const spriteCtx = ctx.spriteRenderer as unknown as ProjectileTextureContext;

        for (const proj of projectiles) {
            // Only dying-phase ION projectiles
            if (proj.lifetime >= 0.4 || proj.lifetime <= 0) continue;
            const pType = proj.projectileType;
            if (
                pType !== ProjectileType.ION_RIFLE &&
                pType !== ProjectileType.ION_MINIGUN &&
                pType !== ProjectileType.ION_CANNON
            ) continue;

            // C: beamScale per type
            let beamScale = 2.2;
            if (pType === ProjectileType.ION_MINIGUN) beamScale = 1.05;
            else if (pType === ProjectileType.ION_CANNON) beamScale = 3.5;

            const ionMaster = proj.ionMasterScale ?? 1.0;
            const searchRadius = beamScale * ionMaster * 40.0;
            const lifeAlpha = Math.max(0, Math.min(1.0, proj.lifetime * 2.5));

            // Find enemies within radius
            const targets: Array<{ x: number; y: number }> = [];
            for (const enemy of enemies) {
                if (!enemy.isAlive || (typeof enemy.isAlive === 'function' && !enemy.isAlive())) continue;
                const dx = enemy.x - proj.x;
                const dy = enemy.y - proj.y;
                const dist = Math.sqrt(dx * dx + dy * dy);
                if (dist < searchRadius && dist > 0) {
                    targets.push({ x: enemy.x, y: enemy.y });
                }
            }

            if (targets.length > 0) {
                drawIonLightningBolts(
                    spriteCtx, ctx.grim,
                    proj.x, proj.y, proj.angle,
                    beamScale, lifeAlpha, targets,
                );
            }
        }
    }

    // Debug: draw bright pink heading arrows on enemies
    if (ctx.debugEnemyHeading) {
        const enemies = ctx.enemySpawner.getActiveEnemies();
        for (const enemy of enemies) {
            const len = enemy.getRadius() * 2.0;
            const endX = enemy.x + Math.cos(enemy.angle) * len;
            const endY = enemy.y + Math.sin(enemy.angle) * len;
            ctx.grim.setColor(255, 0, 255, 255);
            ctx.grim.drawLine(enemy.x, enemy.y, endX, endY, 2);
        }
    }

    // Render bonuses
    const elapsedMs = ctx.scoreSystem.getSurvivalTime() * 1000;
    ctx.bonusSystem.render(ctx.grim, ctx.spriteRenderer, ctx.bonusAnimTimer, elapsedMs);

    // ── Proximity tooltip text (C: bonus_render lines 23158-23179) ──
    // C: distance from player_state_table.aim_x/aim_y to bonus.pos < 24.0
    // C uses camera_offset_x + aim_x for screen-space text positioning, but
    // TS drawTextSmall renders in the game layer which already has camera transform,
    // so we use world-space coordinates directly.
    if (ctx.player) {
        const aimX = ctx.player.aimX;
        const aimY = ctx.player.aimY;
        const bonuses = ctx.bonusSystem.getBonuses();
        for (const bonus of bonuses) {
            if (!bonus.isActive()) continue;
            const dx = aimX - bonus.x;
            const dy = aimY - bonus.y;
            const dist = Math.sqrt(dx * dx + dy * dy);
            if (dist < 24.0) {
                const label = getBonusLabel(bonus.type, bonus.amount);
                if (label) {
                    // C: fVar14 = camera_offset_x + aim_x + 16.0  (screen space)
                    // TS: world space (camera offset applied by container)
                    let textX = aimX + 16.0;
                    const textY = aimY - 7.0;
                    // Clamp: convert to screen space for bounds check
                    const estWidth = label.length * 8;
                    const screenX = ctx.cameraOffsetX + textX;
                    const screenW = ctx.grim.getWidth();
                    if (screenX + estWidth > screenW) {
                        textX = screenW - estWidth - ctx.cameraOffsetX;
                    }
                    ctx.grim.setColor(255, 255, 255, 255);
                    ctx.grim.drawTextSmall(textX, textY, label);
                }
                break; // C: goto LAB_00429df8 — only one tooltip at a time
            }
        }
    }

    // Render particles
    ctx.particleSystem.render(ctx.grim, ctx.spriteRenderer);

    // Render advanced effects (C: effects_render — explosions, freeze, electric, etc.)
    // Rendered AFTER particles but BEFORE blood, matching C render order.
    ctx.effectSystem.render(ctx.grim, ctx.spriteRenderer);

    // Render blood effects
    ctx.bloodEffectSystem.renderBloodEffects(ctx.grim);

    // Screen fade overlay (C: gameplay_render_world L89-91)
    // Drawn LAST in the world render pass, BEFORE the HUD.
    // Must render on UI layer because the game layer has camera offset applied,
    // which would shift the fullscreen quad off-screen.
    // C code: grim_draw_fullscreen_color uses backbuffer coordinates (no camera transform).
    if (ctx.screenFade && ctx.screenFade.isActive()) {
        ctx.grim.setGraphicsLayer('ui');
        ctx.screenFade.render(ctx.grim);
        ctx.grim.setGraphicsLayer('game');
    }

    // Switch to UI layer
    ctx.grim.setGraphicsLayer('ui');

    // Draw gameplay cursor (C: ui_render_aim_indicators — only during active gameplay)
    // Pass actual camera offset (not shake) so the arrow stays relative to the player
    // even at map edges. The cursor renders on the UI layer (no camera transform).
    if (ctx.player && !ctx.suppressGameplayCursor) {
        ctx.gameplayCursor.render(ctx.grim, ctx.player, ctx.cameraOffsetX, ctx.cameraOffsetY);
    }

    // Render HUD
    if (ctx.player && ctx.font) {
        ctx.hud.render(
            ctx.grim,
            ctx.font,
            ctx.player,
            ctx.scoreSystem,
            ctx.gameMode as number,
            ctx.grim.getTime() / 1000,
            ctx.grim.getDeltaTime() / 1000.0,
            ctx.perkPendingCount,
            ctx.questSystem,
        );

        // Render tutorial overlay
        if (ctx.gameMode === 3 /* GameMode.Tutorial */ && ctx.tutorialSystem.isActive()) {
            ctx.tutorialSystem.render(ctx.grim, ctx.font);
        }
    }

    // Perk prompt
    if (ctx.perkPromptTimer > 0) {
        const alpha = Math.min(1.0, ctx.perkPromptTimer * 0.005);
        const promptText = 'Press Mouse2 to pick a perk';
        const screenW = ctx.grim.getWidth();
        const estTextWidth = promptText.length * 8;
        const promptX = screenW - estTextWidth - 16;
        const promptY = 63;
        ctx.grim.setColor(255, 255, 255, Math.floor(alpha * 255));
        ctx.grim.drawText(promptX, promptY, promptText, 13);
    }

    // Switch back to game layer
    ctx.grim.setGraphicsLayer('game');
}

/**
 * Render console overlay.
 */
export function renderConsole(ctx: GameRenderContext): void {
    const width = ctx.grim.getWidth();
    const consoleHeight = gameConsole.getHeight();

    ctx.grim.setGraphicsLayer('console');

    // Console background
    ctx.grim.setColor(0, 0, 0, 200);
    ctx.grim.drawRectFilled(0, 0, width, consoleHeight);

    // Console border
    ctx.grim.setColor(100, 100, 100, 255);
    ctx.grim.drawLine(0, consoleHeight, width, consoleHeight, 2);

    // Input line background
    ctx.grim.setColor(30, 30, 30, 255);
    ctx.grim.drawRectFilled(0, consoleHeight - 25, width, 25);

    // Render text if font is loaded
    if (ctx.font && ctx.font.isLoaded()) {
        const visibleLines = 19;
        const log = gameConsole.getVisibleLog(visibleLines);
        let y = 10;
        const lineHeight = ctx.font.getLineHeight() + 2;

        for (const entry of log) {
            ctx.font.drawText(ctx.grim, entry.text, 10, y, { r: 200, g: 200, b: 200, a: 255 });
            y += lineHeight;
        }

        // Scroll indicators
        const scrollOffset = gameConsole.getScrollOffset();
        const totalLog = gameConsole.getLog().length;

        if (scrollOffset > 0) {
            const indicatorY = consoleHeight - 32;
            ctx.font.drawText(ctx.grim, '--- more below (PgDn) ---', width / 2 - 80, indicatorY, {
                r: 150,
                g: 150,
                b: 50,
                a: 255,
            });
        }

        if (totalLog > visibleLines && totalLog - scrollOffset > visibleLines) {
            ctx.font.drawText(ctx.grim, '--- more above (PgUp) ---', width / 2 - 80, 2, {
                r: 150,
                g: 150,
                b: 50,
                a: 255,
            });
        }

        // Draw input line
        const input = gameConsole.getInputBuffer();
        const inputY = consoleHeight - 18;
        ctx.font.drawText(ctx.grim, `> ${input}_`, 10, inputY, { r: 255, g: 255, b: 255, a: 255 });
    }

    ctx.grim.setGraphicsLayer('game');
}
