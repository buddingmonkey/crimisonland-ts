/**
 * EntityRenderer - Entity drawing methods extracted from SpriteRenderer.ts.
 *
 * Contains drawPlayer, drawPlayerTwoLayer, drawEnemy, drawCorpse.
 * C code references: player_render_overlays, creature_render_type, fx_queue_render.
 */

import type { GrimInterface, TextureHandle } from '../engine/GrimInterface';
import type { PlayerRenderOptions, ColorTint } from './SpriteRenderer';
import { EnemyType } from '../entities/Enemy';
import { TROOPER_CONFIG, CREATURE_TYPE_TABLE, getAnimationFrame } from './SpriteSheetConfig';
import { ParticleFrame, getParticleAtlasFrame } from '../data/ParticleAtlas';

/**
 * Duck-typed context for entity rendering.
 * Subset of SpriteRenderer texture fields.
 */
export interface EntityTextureContext {
    readonly playerHandle: TextureHandle;
    readonly particlesHandle: TextureHandle;
    readonly bodysetHandle: TextureHandle;
    readonly muzzleFlashHandle: TextureHandle;
    readonly hasPlayerSprite: boolean;
    readonly hasEnemySprite: boolean;
    readonly hasBodysetSprite: boolean;
    readonly hasParticlesSprite: boolean;
    readonly hasMuzzleFlashSprite: boolean;
    readonly enemyTextureHandles: Map<string, TextureHandle>;
}

/**
 * Draw player sprite with rotation and effects.
 */
export function drawPlayer(
    ctx: EntityTextureContext,
    grim: GrimInterface,
    x: number,
    y: number,
    angle: number,
    radius: number,
    options: PlayerRenderOptions = {},
): void {
    if (!ctx.hasPlayerSprite) return;

    const config = TROOPER_CONFIG;
    const isMoving = options.isMoving ?? false;
    const animTimer = options.animTimer ?? 0;

    let frameIndex: number;
    if (isMoving) {
        frameIndex = getAnimationFrame(config.animations.walk, animTimer);
    } else {
        frameIndex = config.animations.idle.startRow;
    }

    // Frame in 8×8 atlas: column 0, row = frameIndex → flat index = frameIndex * 8
    grim.bindTexture(ctx.playerHandle);
    grim.setAtlasFrame(8, frameIndex * 8);

    if (options.shieldTimer && options.shieldTimer > 0) {
        const flashAmount = Math.sin(options.shieldTimer * 30) * 0.5 + 0.5;
        grim.setColor(Math.floor(200 + flashAmount * 55), Math.floor(200 + flashAmount * 55), 255, 255);
    } else {
        grim.setColor(255, 255, 255, 255);
    }

    grim.setRotation(angle + Math.PI / 2);
    const size = radius * 2.5;
    grim.drawQuad(x - size / 2, y - size / 2, size, size);
    grim.setRotation(0);
}

/**
 * Draw player with two-layer rendering matching C player_render_overlays.
 */
export function drawPlayerTwoLayer(
    ctx: EntityTextureContext,
    grim: GrimInterface,
    x: number,
    y: number,
    options: PlayerRenderOptions = {},
): void {
    if (!ctx.hasPlayerSprite) return;

    const heading = options.heading ?? 0;
    const aimAngle = options.aimAngle ?? heading;
    const isDead = options.isDead ?? false;
    const deathTimer = options.deathTimer ?? 16.0;
    const playerSize = options.playerSize ?? 48.0;
    const muzzleFlashAlpha = options.muzzleFlashAlpha ?? 0;
    const shieldTimer = options.shieldTimer ?? 0;
    const isMoving = options.isMoving ?? false;
    const animTimer = options.animTimer ?? 0;

    grim.bindTexture(ctx.playerHandle);

    if (isDead) {
        let frameIndex: number;
        if (deathTimer >= 0.0) {
            frameIndex = Math.floor(deathTimer);
            frameIndex = 32 + Math.max(0, Math.min(19, frameIndex));
        } else {
            frameIndex = 52;
        }

        grim.setAtlasFrame(8, frameIndex);
        grim.setColor(0, 0, 0, 255);
        grim.setRotation(aimAngle + Math.PI / 2);
        const halfSize = playerSize * 0.5;
        const shadowScale = playerSize * 1.03;
        grim.drawQuad(x - halfSize + 1.0, y - halfSize + 1.0, shadowScale, shadowScale);

        grim.setColor(255, 255, 255, 255);
        grim.drawQuad(x - halfSize, y - halfSize, playerSize, playerSize);
        grim.setRotation(0);
        return;
    }

    // ALIVE RENDERING
    let bodyFrameIndex: number;
    if (isMoving) {
        bodyFrameIndex = Math.floor(animTimer) % 15;
    } else {
        bodyFrameIndex = 0;
    }

    const weaponFrameIndex = bodyFrameIndex + 16;



    const weaponOffsetX = Math.cos(aimAngle) * muzzleFlashAlpha * 4.0;
    const weaponOffsetY = Math.sin(aimAngle) * muzzleFlashAlpha * 4.0;

    const halfSize = playerSize * 0.5;

    // RADIOACTIVE AURA (C player_render_overlays L2266-2283)
    // Drawn BEFORE player sprite — green pulsing glow circle under the player
    if (options.hasRadioactivePerk && ctx.hasParticlesSprite) {
        grim.bindTexture(ctx.particlesHandle);
        grim.setBlendMode('add');
        // C: effect_select_texture(0x10) = 4×4 frame 0, but that area has sub-sprite artifacts.
        // Use GLOW_ORB (4×4 frame 3) — a clean 64×64 glow circle for the same visual result.
        const raGlow = getParticleAtlasFrame(ParticleFrame.GLOW_ORB);
        grim.setAtlasFrame(raGlow.atlasSize, raGlow.frame);

        const gameTimeRA = grim.getTime() / 1000.0;
        const pulseAlpha = (Math.sin(gameTimeRA) + 1.0) * 0.1875 + 0.25;
        grim.setColor(77, 153, 77, Math.floor(pulseAlpha * 255)); // C: (0.3, 0.6, 0.3)
        grim.setRotation(0);
        grim.drawQuad(x - 50, y - 50, 100, 100); // 100×100 centered on player

        grim.setBlendMode('normal');
        grim.bindTexture(ctx.playerHandle); // Rebind player texture for shadow/main passes
    }

    // SHADOW PASS
    grim.setAtlasFrame(8, bodyFrameIndex);
    grim.setColor(0, 0, 0, 255);
    grim.setRotation(heading + Math.PI / 2);
    const bodyShadowOff = halfSize - 2.0;
    const bodyShadowScale = playerSize * 1.02;
    grim.drawQuad(x - bodyShadowOff + 1.0, y - bodyShadowOff + 1.0, bodyShadowScale, bodyShadowScale);

    grim.setAtlasFrame(8, weaponFrameIndex);
    grim.setRotation(aimAngle + Math.PI / 2);
    const weaponShadowScale = playerSize * 1.03;
    grim.drawQuad(
        x - halfSize + weaponOffsetX + 1.0,
        y - halfSize + weaponOffsetY + 1.0,
        weaponShadowScale,
        weaponShadowScale,
    );

    // MAIN PASS
    if (shieldTimer > 0) {
        const flashAmount = Math.sin(shieldTimer * 30) * 0.5 + 0.5;
        grim.setColor(Math.floor(200 + flashAmount * 55), Math.floor(200 + flashAmount * 55), 255, 255);
    } else {
        grim.setColor(255, 255, 255, 255);
    }

    grim.setAtlasFrame(8, bodyFrameIndex);
    grim.setRotation(heading + Math.PI / 2);
    grim.drawQuad(x - halfSize, y - halfSize, playerSize, playerSize);

    grim.setAtlasFrame(8, weaponFrameIndex);
    grim.setRotation(aimAngle + Math.PI / 2);
    grim.drawQuad(x - halfSize + weaponOffsetX, y - halfSize + weaponOffsetY, playerSize, playerSize);

    grim.setRotation(0);

    // SHIELD VISUAL (C player_render_overlays L2393-2437)
    // Drawn BEFORE muzzle flash, matching C render order
    if (shieldTimer > 0 && ctx.hasParticlesSprite) {
        grim.bindTexture(ctx.particlesHandle);
        const shieldFrame = getParticleAtlasFrame(ParticleFrame.GLOW_SOFT);
        grim.setAtlasFrame(shieldFrame.atlasSize, shieldFrame.frame); // Bubble (Shield) disc — first particle in particles.jaz

        const gameTime = grim.getTime() / 1000.0;
        let shieldAlpha = (Math.sin(gameTime) + 1.0) * 0.25 + shieldTimer;
        if (shieldTimer < 1.0) shieldAlpha *= shieldTimer;
        if (shieldAlpha > 1.0) shieldAlpha = 1.0;

        grim.setBlendMode('add');

        // C: aim perpendicular offset (L2413-2415)
        const aimPerp = aimAngle - Math.PI / 2;
        const shieldOffsetX = Math.cos(aimPerp) * 3.0;
        const shieldOffsetY = Math.sin(aimPerp) * 3.0;

        const innerPulse = Math.sin(gameTime * 3.0);
        const innerSize = innerPulse + 17.5;
        grim.setColor(91, 180, 255, Math.floor(shieldAlpha * 0.4 * 255));
        grim.setRotation(gameTime * 2.0);
        grim.drawQuad(x - innerSize + shieldOffsetX, y - innerSize + shieldOffsetY, innerSize * 2, innerSize * 2);

        const outerSize = innerPulse * 4.0 + 24.0;
        grim.setColor(91, 180, 255, Math.floor(shieldAlpha * 0.3 * 255));
        grim.setRotation(gameTime * -2.0);
        grim.drawQuad(x - outerSize + shieldOffsetX, y - outerSize + shieldOffsetY, outerSize * 2, outerSize * 2);

        grim.setBlendMode('normal');
        grim.setRotation(0);
    }

    // MUZZLE FLASH (C player_render_overlays L2438-2482)
    // Textured quad drawn at gun barrel position with additive blending
    // C: skip if weapon has "no muzzle flash" flag (flags & 8 = WeaponFlags.ENERGY)
    const weaponFlagsVal = options.weaponFlags ?? 0;
    const skipMuzzleFlash = (weaponFlagsVal & 0x08) !== 0; // WeaponFlags.ENERGY → no muzzle flash
    if (muzzleFlashAlpha > 0 && ctx.hasMuzzleFlashSprite && !skipMuzzleFlash) {
        const isChargeWeapon = (weaponFlagsVal & 0x04) !== 0; // WeaponFlags.CHARGE → half-size flash

        grim.bindTexture(ctx.muzzleFlashHandle);
        grim.setBlendMode('add');
        grim.setUV(0, 0, 1, 1);

        let flashAlpha = muzzleFlashAlpha * 0.8;
        if (flashAlpha > 1.0) flashAlpha = 1.0;
        grim.setColor(255, 255, 255, Math.floor(flashAlpha * 255));

        // C: grim_set_rotation(aim_heading) where aim_heading = TS aimAngle + PI/2
        // Must match weapon layer rotation (line 183) so the flash aligns with the barrel
        grim.setRotation(aimAngle + Math.PI / 2);

        // Offset muzzle flash along the aim direction toward the gun barrel
        // C: cos/sin(aim_heading + PI/2) = cos/sin(aimAngle + PI) = -cos/-sin(aimAngle)
        // This pushes the flash quad center slightly backward (recoil direction)
        const cosAim = Math.cos(aimAngle);
        const sinAim = Math.sin(aimAngle);

        let flashHalf: number, flashDrawSize: number;
        if (isChargeWeapon) {
            // Charge weapon: half-size flash (C: flags & 4)
            flashHalf = playerSize * 0.25;
            flashDrawSize = playerSize * 0.5;
        } else {
            // Ballistic weapon: full-size flash
            flashHalf = playerSize * 0.5;
            flashDrawSize = playerSize;
        }

        const flashX = x - flashHalf + cosAim * muzzleFlashAlpha * 12.0;
        const flashY = y - flashHalf + sinAim * muzzleFlashAlpha * 12.0;
        grim.drawQuad(flashX, flashY, flashDrawSize, flashDrawSize);

        grim.setBlendMode('normal');
        grim.setRotation(0);
    }
}

/**
 * Draw enemy sprite with C-accurate animation.
 */
export function drawEnemy(
    ctx: EntityTextureContext,
    grim: GrimInterface,
    x: number,
    y: number,
    angle: number,
    size: number,
    tint: ColorTint = { r: 1, g: 1, b: 1 },
    hitFlash: number = 0,
    animPhase: number = 0,
    _isDying: boolean = false,
    hitboxSize: number = 16.0,
    enemyType: EnemyType = EnemyType.Spider,
    creatureFlags: number = 0,
    energizerTimer: number = 0,
    maxHealth: number = 100,
    radioactiveFlash: number = 0,
): void {
    if (!ctx.hasEnemySprite) return;

    const typeIndex = Math.min(enemyType, CREATURE_TYPE_TABLE.length - 1);
    const typeConfig = CREATURE_TYPE_TABLE[typeIndex];

    const textureHandle = ctx.enemyTextureHandles.get(typeConfig.textureKey);
    if (textureHandle === undefined) {
        const firstHandle = ctx.enemyTextureHandles.values().next().value;
        if (firstHandle !== undefined) {
            grim.bindTexture(firstHandle);
        } else {
            return;
        }
    } else {
        grim.bindTexture(textureHandle);
    }

    let frame: number;

    if (hitboxSize >= 16.0) {
        const flags = creatureFlags;
        if ((flags & 4) === 0 || (flags & 0x40) !== 0) {
            frame = Math.floor(animPhase) & 0x1f;
            if ((typeConfig.animFlags & 1) !== 0 && frame > 15) {
                frame = 0x1f - frame;
            }
            if ((flags & 0x10) !== 0) {
                frame = frame + 0x20;
            }
        } else {
            let bounceFrame = Math.floor(animPhase) & 0x0f;
            if (bounceFrame > 7) {
                bounceFrame = 0x0f - bounceFrame;
            }
            frame = typeConfig.baseFrame + 0x10 + bounceFrame;
        }
    } else if (hitboxSize >= 0) {
        const flags = creatureFlags;
        if ((flags & 4) === 0 || (flags & 0x40) !== 0) {
            frame = Math.floor(hitboxSize);
        } else {
            let bounceFrame = Math.floor(animPhase) & 0x0f;
            if (bounceFrame > 7) {
                bounceFrame = 0x0f - bounceFrame;
            }
            frame = typeConfig.baseFrame + 0x10 + bounceFrame;
        }
    } else {
        const flags = creatureFlags;
        if ((flags & 4) === 0 || (flags & 0x40) !== 0) {
            frame = typeConfig.baseFrame + 0x0f;
        } else {
            let bounceFrame = Math.floor(animPhase) & 0x0f;
            if (bounceFrame > 7) {
                bounceFrame = 0x0f - bounceFrame;
            }
            frame = typeConfig.baseFrame + 0x10 + bounceFrame;
        }
    }

    grim.setAtlasFrame(8, frame);

    let r = tint.r;
    let g = tint.g;
    let b = tint.b;

    // Fix 5: Energizer tint override (C L419-434)
    // Non-boss enemies (<500 max HP) shift toward blue when energizer is active
    let energizerAlphaBoost = 1.0;
    if (energizerTimer > 0 && maxHealth < 500) {
        const t = Math.min(1.0, energizerTimer);
        const invT = 1.0 - t;
        r = invT * r + t * 0.5;
        g = invT * g + t * 0.5;
        b = invT * b + t * 1.0;
        // C: alpha = (1-t) * creature.alpha + t * 1.0 — lerp alpha toward fully opaque
        energizerAlphaBoost = invT * 1.0 + t * 1.0; // creature alpha assumed 1.0
    }

    let glowAlphaF = 1.0 * energizerAlphaBoost;
    let mainAlphaF = 1.0 * energizerAlphaBoost;
    // Death fade disabled — corpse baking handles the visual transition
    // (Previously faded out based on hitboxSize when hitboxSize < 0)

    // C-accurate quad sizing (C L337-340, L402-406)
    // size is passed directly from enemy.size, matching the C code's draw_quad dimensions
    const glowSize = size * 1.07;
    const glowOffset = size * 0.5 + 0.7; // C line 337: offset = size*0.5 + 0.7
    const mainOffset = size * 0.5; // C line 402: offset = size*0.5

    // GLOW/SHADOW PASS (C L337-340)
    const glowAlpha = Math.floor(Math.min(255, 255 * glowAlphaF * 0.4));
    grim.setColor(Math.floor(r * 255), Math.floor(g * 255), Math.floor(b * 255), glowAlpha);
    grim.setRotation(angle);
    grim.drawQuad(x - glowOffset, y - glowOffset, glowSize, glowSize);

    // MAIN SPRITE PASS (C L402-406)
    const mainAlpha = Math.floor(255 * mainAlphaF);
    grim.setColor(Math.floor(r * 255), Math.floor(g * 255), Math.floor(b * 255), mainAlpha);
    grim.setRotation(angle);
    grim.drawQuad(x - mainOffset, y - mainOffset, size, size);

    grim.setRotation(0);

    // Fix 4: Hit-flash as additive overlay (C L492-543)
    // C draws the sprite a second time (twice) with additive blending
    // rather than interpolating the tint color toward white
    if (hitFlash > 0) {
        grim.setBlendMode('add');
        const flashAlpha = Math.floor(255 * Math.min(1.0, hitFlash / 0.2));
        grim.setColor(255, 255, 255, flashAlpha);
        grim.setRotation(angle);
        // Draw twice like C does (for a brighter flash)
        grim.drawQuad(x - mainOffset, y - mainOffset, size, size);
        grim.drawQuad(x - mainOffset, y - mainOffset, size, size);
        grim.setBlendMode('normal');
        grim.setRotation(0);
    }

    // Radioactive damage green flash (C lines 21661-21679 VFX)
    // Green-tinted additive overlay when taking radioactive damage
    if (radioactiveFlash > 0) {
        grim.setBlendMode('add');
        const flashAlpha = Math.floor(255 * Math.min(1.0, radioactiveFlash / 0.15));
        grim.setColor(50, 255, 80, flashAlpha);
        grim.setRotation(angle);
        grim.drawQuad(x - mainOffset, y - mainOffset, size, size);
        grim.setBlendMode('normal');
        grim.setRotation(0);
    }
}

/**
 * Draw corpse sprite from bodyset.jaz.
 */
export function drawCorpse(
    ctx: EntityTextureContext,
    grim: GrimInterface,
    x: number,
    y: number,
    rotation: number,
    tint: ColorTint = { r: 1, g: 1, b: 1 },
    scale: number = 1.0,
    enemyType: EnemyType = EnemyType.Spider,
): void {
    if (!ctx.hasBodysetSprite) return;

    const typeIndex = Math.min(enemyType, CREATURE_TYPE_TABLE.length - 1);
    const corpseFrame = CREATURE_TYPE_TABLE[typeIndex].corpseFrame;

    grim.bindTexture(ctx.bodysetHandle);
    grim.setAtlasFrame(4, corpseFrame);

    grim.setColor(Math.floor(tint.r * 255), Math.floor(tint.g * 255), Math.floor(tint.b * 255), 128);

    grim.setRotation(rotation);

    const size = scale * 30.0;
    grim.drawQuad(x - size / 2, y - size / 2, size, size);

    grim.setRotation(0);
}

/**
 * Freeze overlay pass — ice crystal sprite on every active enemy.
 * C code reference: creatures.c lines 624-658.
 *
 * Draws particles atlas frame 0x0E (ice crystal) on each visible enemy
 * with additive blending. Alpha fades during the last 1 second of freeze timer.
 *
 * @param enemies — array of duck-typed enemy objects (position, heading, size, alive)
 */
export function drawFreezeOverlay(
    ctx: EntityTextureContext,
    grim: GrimInterface,
    enemies: ReadonlyArray<{
        x: number;
        y: number;
        heading: number;
        size: number;
        isAlive(): boolean;
        shouldRender(): boolean;
    }>,
    freezeTimer: number,
): void {
    if (freezeTimer <= 0) return;
    if (!ctx.hasParticlesSprite) return;

    // C: alpha = saturate(freeze_timer) * 0.7
    let alpha = 1.0;
    if (freezeTimer < 1.0) {
        alpha = Math.max(0.0, freezeTimer);
    }
    alpha = alpha * 0.7;

    const alphaInt = Math.floor(alpha * 255);
    if (alphaInt <= 0) return;

    // Bind particles texture and select frame for freeze crystal overlay
    // Uses 4×4 grid frame 4 = (0,64) = Ice Large chunk — visually verified as correct ice pattern
    grim.bindTexture(ctx.particlesHandle);
    grim.setAtlasFrame(4, 4); // Ice Large chunk — confirmed correct for frozen enemy overlay
    // C: grim_set_config_var(0x13,5), (0x14,6) = D3DBLEND_SRCALPHA/INVSRCALPHA = normal
    grim.setBlendMode('normal');

    let enemyIndex = 0;
    for (const enemy of enemies) {
        if (!enemy.isAlive()) {
            enemyIndex++;
            continue;
        }

        // C: grim_set_color(1.0, 1.0, 1.0, alpha) — white with computed alpha
        grim.setColor(255, 255, 255, alphaInt);
        // C: rotation = creature_index * 0.01 + creature.heading
        grim.setRotation(enemyIndex * 0.01 + enemy.heading);

        const halfSize = enemy.size * 0.5;
        grim.drawQuad(enemy.x - halfSize, enemy.y - halfSize, enemy.size, enemy.size);

        enemyIndex++;
    }

    grim.setBlendMode('normal');
    grim.setRotation(0);
}

/**
 * Monster Vision glow pass — yellow glow disc under every active enemy.
 * C code reference: creature_render_all (creatures.c lines 576-587).
 *
 * Draws particles atlas effect 0x10 (SHADOW_DISC = frame 0 in 4×4 grid)
 * with yellow color (1.0, 1.0, 0.0) and 90×90 size centered on each enemy.
 * Alpha fades during the last 10 hitboxSize units of death animation.
 *
 * @param enemies — array of duck-typed enemy objects
 * @param perkSystem — perk system to check for MONSTER_VISION perk
 */
export function drawMonsterVisionGlow(
    ctx: EntityTextureContext,
    grim: GrimInterface,
    enemies: ReadonlyArray<{
        x: number;
        y: number;
        isAlive(): boolean;
        shouldRender(): boolean;
        hitboxSize: number;
        isDying: boolean;
        active: boolean;
    }>,
): void {
    if (!ctx.hasParticlesSprite) return;

    grim.bindTexture(ctx.particlesHandle);
    // C: effect_select_texture(0x10) = 4×4 frame 0, but that area has sub-sprite artifacts.
    // Use GLOW_ORB (4×4 frame 3) — a clean 64×64 glow circle for the same visual result.
    const mvGlow = getParticleAtlasFrame(ParticleFrame.GLOW_ORB);
    grim.setAtlasFrame(mvGlow.atlasSize, mvGlow.frame);
    grim.setBlendMode('add');
    grim.setRotation(0);

    for (const enemy of enemies) {
        if (!enemy.active) continue;

        // C: alpha = 1.0 when hitboxSize >= 0, else fade based on (hitboxSize + 10) * 0.1
        let alpha = 1.0;
        if (enemy.hitboxSize < 0) {
            alpha = (enemy.hitboxSize + 10.0) * 0.1;
            if (alpha > 1.0) alpha = 1.0;
            if (alpha < 0.0) alpha = 0.0;
        }

        // C: grim_set_color(1.0, 1.0, 0.0, alpha * scale_factor)
        grim.setColor(255, 255, 0, Math.floor(alpha * 200));
        // C: 90×90 quad centered on creature
        grim.drawQuad(enemy.x - 45, enemy.y - 45, 90, 90);
    }

    grim.setBlendMode('normal');
}
