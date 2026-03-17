/**
 * PlayerRenderer - Player rendering extracted from Player.ts.
 *
 * Contains render() and renderHealthBar() logic.
 */

import type { GrimInterface } from '../engine/GrimInterface';
import { getWeaponStats } from '../data/WeaponData';
import { PerkId } from '../systems/PerkSystem';

/**
 * Duck-typed subset of Player fields needed by render functions.
 */
export interface PlayerRenderContext {
    x: number;
    y: number;
    angle: number;
    heading: number;
    radius: number;
    size: number;
    dx: number;
    dy: number;
    health: number;
    maxHealth: number;
    shieldTimer: number;
    muzzleFlashAlpha: number;
    animTimer: number;
    deathTimer: number;
    weaponId: number;
    isAlive(): boolean;
}

/**
 * Render player sprite or debug shapes.
 */
export function renderPlayer(
    ctx: PlayerRenderContext,
    grim: GrimInterface,
    spriteRenderer?: any,
    debugMode: boolean = true,
    perkSystem?: any,
): void {
    // Dead player rendering
    if (!ctx.isAlive()) {
        if (spriteRenderer && !debugMode && spriteRenderer.canDrawPlayer()) {
            spriteRenderer.drawPlayerTwoLayer(grim, ctx.x, ctx.y, {
                heading: ctx.heading,
                aimAngle: ctx.angle,
                shieldTimer: 0,
                muzzleFlashAlpha: 0,
                isMoving: false,
                animTimer: 0,
                isDead: true,
                deathTimer: ctx.deathTimer,
                playerSize: ctx.size,
            });
        } else {
            grim.setColor(80, 80, 80, 150);
            grim.drawCircleFilled(ctx.x, ctx.y, ctx.radius);
        }
        return;
    }

    const canDraw = spriteRenderer?.canDrawPlayer();
    const useSprites = spriteRenderer && !debugMode && canDraw;

    if (useSprites) {
        const isMoving = Math.abs(ctx.dx) > 0.1 || Math.abs(ctx.dy) > 0.1;
        const weaponStats = getWeaponStats(ctx.weaponId);

        spriteRenderer.drawPlayerTwoLayer(grim, ctx.x, ctx.y, {
            heading: ctx.heading,
            aimAngle: ctx.angle,
            shieldTimer: ctx.shieldTimer,
            muzzleFlashAlpha: ctx.muzzleFlashAlpha,
            isMoving: isMoving,
            animTimer: ctx.animTimer,
            isDead: false,
            deathTimer: ctx.deathTimer,
            playerSize: ctx.size,
            weaponFlags: weaponStats.flags,
            hasRadioactivePerk: perkSystem?.hasPerk?.(PerkId.RADIOACTIVE) ?? false,
        });
    } else {
        // Debug rendering
        if (ctx.shieldTimer > 0) {
            const flashAmount = Math.sin(ctx.shieldTimer * 30) * 0.5 + 0.5;
            grim.setColor(
                50 + Math.floor(flashAmount * 205),
                100 + Math.floor(flashAmount * 155),
                200 + Math.floor(flashAmount * 55),
                255,
            );
        } else {
            grim.setColor(50, 100, 200, 255);
        }
        grim.drawCircleFilled(ctx.x, ctx.y, ctx.radius);

        const lineLength = ctx.radius * 1.5;
        const endX = ctx.x + Math.cos(ctx.angle) * lineLength;
        const endY = ctx.y + Math.sin(ctx.angle) * lineLength;
        grim.setColor(255, 255, 255, 255);
        grim.drawLine(ctx.x, ctx.y, endX, endY, 2);

        if (ctx.muzzleFlashAlpha > 0) {
            const flashRadius = ctx.radius * 0.5;
            const flashX = ctx.x + Math.cos(ctx.angle) * ctx.radius;
            const flashY = ctx.y + Math.sin(ctx.angle) * ctx.radius;
            grim.setColor(255, 255, 100, Math.floor(ctx.muzzleFlashAlpha * 255));
            grim.drawCircleFilled(flashX, flashY, flashRadius);
        }
    }
}
