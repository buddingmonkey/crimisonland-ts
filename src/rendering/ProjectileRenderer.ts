/**
 * ProjectileRenderer - Extracted projectile rendering methods from SpriteRenderer.
 *
 * All projectile type-specific drawing: bullets, plasma, special, ion, fire, rockets.
 * C code reference: projectile_render() at line 20366 in crimsonland.exe_decompiled_renamed.c
 */

import type { GrimInterface, TextureHandle } from '../engine/GrimInterface';
import { ProjectileType } from '../data/WeaponData';

/**
 * Texture context for projectile rendering.
 * Duck-typed subset of SpriteRenderer fields.
 */
export interface ProjectileTextureContext {
    readonly particlesHandle: TextureHandle;
    readonly projectileHandle: TextureHandle;
    readonly bulletTrailHandle: TextureHandle;
    readonly bulletHeadHandle: TextureHandle;
    readonly hasParticlesSprite: boolean;
    readonly hasProjectileSprite: boolean;
    readonly hasBulletTrailSprite: boolean;
    readonly hasBulletHeadSprite: boolean;
}

/** Projectile data subset needed for rendering */
export interface ProjectileRenderData {
    x: number;
    y: number;
    angle: number;
    projectileType: ProjectileType;
    lifetime: number;
    maxLifetime: number;
    headX: number;
    headY: number;
    tailX: number;
    tailY: number;
    perpX: number;
    perpY: number;
    hasFireVisual?: boolean;
    speedScale?: number;
    ionMasterScale?: number;
    // Rocket explosion state
    isExploding?: boolean;
    explosionTimer?: number;
    explosionScale?: number;
    // Origin position for distance-based scaling (PULSE_GUN, SPLITTER_GUN, BLADE_GUN)
    originX?: number;
    originY?: number;
    // Frame time for time-based animation (BLADE_GUN spinning, PLAGUE_SPREADER animation)
    frameTime?: number;
}

/**
 * Main dispatch: draw a projectile based on its type.
 */
export function drawProjectile(
    ctx: ProjectileTextureContext,
    grim: GrimInterface,
    projectile: ProjectileRenderData,
): void {
    const { x, y, angle, projectileType, lifetime } = projectile;

    // === Rocket EXPLODING state rendering (C projectiles.c L2032-2052) ===
    // C: EXPLODING rockets skip the sprite pass, but get a 140×140 white glow
    // from particles_texture using effect_select_texture(0xd) = GLOW_ORB
    if (projectile.isExploding) {
        const timer = projectile.explosionTimer ?? 0;
        // C L2038-2052: ALL secondary projectiles get a constant 140×140 glow
        // at α=0.48. This is NOT scaled by explosionScale and NOT faded by timer.
        // The 140×140 is the general secondary-projectile glow pass.
        const glowSize = 140.0;
        const alpha = 0.48;
        if (ctx.hasParticlesSprite && timer < 1.0) {
            grim.bindTexture(ctx.particlesHandle);
            // GLOW_ORB = frame 3 in 4×4 grid (golden glow orb)
            grim.setAtlasFrame(4, 3);
            grim.setBlendMode('add');
            grim.setColor(255, 255, 255, Math.floor(alpha * 255));
            grim.setRotation(0);
            grim.drawQuad(
                x - glowSize / 2,
                y - glowSize / 2,
                glowSize,
                glowSize,
            );
            grim.setBlendMode('normal');
        }
        return; // Don't draw rocket sprite while exploding
    }

    // Fire visual overlay: render fire trail regardless of underlying projectile type
    // C code: fire_bullets is a rendering overlay, not a projectile type change
    if (projectile.hasFireVisual) {
        drawFireBulletParticle(ctx, grim, projectile);
        return;
    }

    switch (projectileType) {
        case ProjectileType.PISTOL:
            drawBulletProjectile(ctx, grim, projectile, 1.2, 6, 128, 128, 128, lifetime);
            break;
        case ProjectileType.ASSAULT_RIFLE:
            drawBulletProjectile(ctx, grim, projectile, 1.0, 8, 128, 128, 128, lifetime);
            break;
        case ProjectileType.GAUSS_GUN:
            drawBulletProjectile(ctx, grim, projectile, 1.1, 4, 51, 128, 255, lifetime);
            break;
        case ProjectileType.SHOTGUN:
        case ProjectileType.SMG:
        case ProjectileType.MINIGUN:
            drawBulletProjectile(ctx, grim, projectile, 0.7, 4, 128, 128, 128, lifetime);
            break;
        case ProjectileType.PLASMA_RIFLE:
            drawPlasmaProjectile(ctx, grim, projectile, 56, 255, 255, 255);
            break;
        case ProjectileType.PLASMA_MINIGUN:
            drawPlasmaProjectile(ctx, grim, projectile, 16, 255, 255, 255);
            break;
        case ProjectileType.PLASMA_CANNON:
            drawPlasmaProjectile(ctx, grim, projectile, 84, 255, 255, 255);
            break;
        case ProjectileType.SPIDER_PLASMA:
            drawPlasmaProjectile(ctx, grim, projectile, 16, 77, 255, 77);
            break;
        case ProjectileType.SHRINKIFIER:
            drawPlasmaProjectile(ctx, grim, projectile, 16, 77, 77, 255);
            break;
        case ProjectileType.PULSE_GUN: {
            // C stores angle as heading = velocity_direction + PI/2.
            // C renderer uses raw heading; TS stores velocity_direction, so add PI/2.
            const pulseAngle = angle + Math.PI / 2;
            if (lifetime >= 0.4) {
                // C L1653-1668: Alive — green (0.1,0.6,0.2) wave, distance-scaled, atlas(2,0)
                // C alpha: fStack_4c * 0.7 ≈ 0.7
                const pdx = (projectile.originX ?? x) - x;
                const pdy = (projectile.originY ?? y) - y;
                const pDist = Math.sqrt(pdx * pdx + pdy * pdy);
                const pScale = pDist * 0.01;
                const pSize = Math.max(4, pScale * 16);
                drawPulseWave(ctx, grim, x, y, pulseAngle, 2, 0, 26, 153, 51, pSize, 0.7);
            } else {
                // C L1671-1688: Dying — 56×56 fading WHITE wave, atlas(2,0)
                // C: alpha = clamp(life_timer * 2.5, 0, 1) * fStack_4c
                const fadeAlpha = Math.max(0, Math.min(1, lifetime * 2.5));
                drawPulseWave(ctx, grim, x, y, pulseAngle, 2, 0, 255, 255, 255, 56, fadeAlpha);
            }
            break;
        }
        case ProjectileType.SPLITTER_GUN: {
            // C: SPLITTER_GUN gets BOTH a 0.7x bullet trail (pass 1, L1298/1366-1381)
            // AND a special sprite at atlas(4,3) (pass 3, L1690-1710)
            const sdx = (projectile.originX ?? x) - x;
            const sdy = (projectile.originY ?? y) - y;
            let sDist = Math.sqrt(sdx * sdx + sdy * sdy);
            if (sDist > 20) sDist = 20;
            // First: bullet trail (0.7x perp scale)
            drawBulletProjectile(ctx, grim, projectile, 0.7, 4, 128, 128, 128, lifetime);
            // Second: special projectile sprite on top
            drawSpecialProjectile(ctx, grim, x, y, angle, 4, 3, 255, 255, 255, sDist);
            break;
        }
        case ProjectileType.BLADE_GUN: {
            // C: atlas(4,6), gray (0.8,0.8,0.8), distance-scaled (max 20px)
            // C rotation: time-based spinning (index * 0.1 - quest_spawn_timeline * 0.1)
            const bdx = (projectile.originX ?? x) - x;
            const bdy = (projectile.originY ?? y) - y;
            let bDist = Math.sqrt(bdx * bdx + bdy * bdy);
            if (bDist > 20) bDist = 20;
            const bladeRotation = (projectile.frameTime ?? Date.now() * 0.001) * 0.6;
            drawSpecialProjectile(ctx, grim, x, y, bladeRotation, 4, 6, 204, 204, 204, bDist);
            break;
        }
        case ProjectileType.PLAGUE_SPREADER:
            drawPlagueSpreaderProjectile(ctx, grim, projectile);
            break;
        case ProjectileType.ION_RIFLE:
            drawIonProjectile(ctx, grim, projectile, 2.2);
            break;
        case ProjectileType.ION_MINIGUN:
            drawIonProjectile(ctx, grim, projectile, 1.05);
            break;
        case ProjectileType.ION_CANNON:
            drawIonProjectile(ctx, grim, projectile, 3.5);
            break;
        case ProjectileType.FIRE_BULLETS:
            drawFireBulletParticle(ctx, grim, projectile);
            break;
        case ProjectileType.ROCKET:
            // C L2067-2076: 14×14 sprite; C L2121-2130: 60×60 white glow at alpha 0.68
            drawRocketProjectile(ctx, grim, x, y, angle, 14, 60, 255, 255, 255, 0.68);
            break;
        case ProjectileType.SEEKER_ROCKET:
            // C L2077-2081: 10×10 sprite; C L2132-2144: 40×40 white glow at alpha 0.58
            drawRocketProjectile(ctx, grim, x, y, angle, 10, 40, 255, 255, 255, 0.58);
            break;
        case ProjectileType.ROCKET_MINIGUN:
            // C L2083-2090: 8×8 sprite; C L2106-2119: 30×30 blue glow at alpha 0.158
            drawRocketProjectile(ctx, grim, x, y, angle, 8, 30, 179, 179, 255, 0.158);
            break;
        default:
            drawBulletProjectile(ctx, grim, projectile, 0.7, 4, 128, 128, 128, lifetime);
            break;
    }
}

// ─────────────────────────────────────────────────────────────────
// Per-type helpers
// ─────────────────────────────────────────────────────────────────

function drawBulletProjectile(
    ctx: ProjectileTextureContext,
    grim: GrimInterface,
    proj: {
        x: number;
        y: number;
        angle: number;
        headX: number;
        headY: number;
        tailX: number;
        tailY: number;
        perpX: number;
        perpY: number;
    },
    trailScale: number,
    bulletSize: number,
    r: number,
    g: number,
    b: number,
    lifetime: number,
): void {
    const lifeAlpha = Math.max(0, Math.min(1.0, lifetime * 2.5));
    const trailAlpha = Math.floor(lifeAlpha * 0.6 * 255);
    const perpSX = proj.perpX * trailScale;
    const perpSY = proj.perpY * trailScale;

    const x1 = proj.headX - perpSX,
        y1 = proj.headY - perpSY;
    const x2 = proj.headX + perpSX,
        y2 = proj.headY + perpSY;
    const x3 = proj.tailX + perpSX,
        y3 = proj.tailY + perpSY;
    const x4 = proj.tailX - perpSX,
        y4 = proj.tailY - perpSY;

    if (ctx.hasBulletTrailSprite) {
        grim.bindTexture(ctx.bulletTrailHandle);
        // UVs map head (v=0) to opaque top of gradient, tail (v=1) to transparent bottom.
        // The gradient texture handles the smooth alpha fade from head to tail.
        grim.setUV(0, 0, 1, 1);
    }

    // C code: SRCBLEND=D3DBLEND_SRCALPHA(5), DESTBLEND=D3DBLEND_ONE(2)
    // = SRC_ALPHA additive: result = src × srcAlpha + dst
    grim.setBlendMode('add-alpha');
    grim.setColor(r, g, b, trailAlpha);
    grim.drawQuadPoints(x1, y1, x2, y2, x3, y3, x4, y4);

    grim.setBlendMode('normal');
    grim.setColor(204, 204, 204, 230);

    if (ctx.hasBulletHeadSprite) {
        grim.bindTexture(ctx.bulletHeadHandle);
        grim.setUV(0, 0, 1, 1);
    }

    grim.setRotation(proj.angle + Math.PI / 2);
    const half = bulletSize / 2;
    grim.drawQuad(proj.x - half, proj.y - half, bulletSize, bulletSize);
    grim.setRotation(0);
}

function drawPlasmaProjectile(
    ctx: ProjectileTextureContext,
    grim: GrimInterface,
    proj: ProjectileRenderData,
    glowSize: number,
    r: number,
    g: number,
    b: number,
): void {
    // C code reference: projectiles.c lines 1417-1460 (PLASMA_RIFLE rendering)
    // Three layers in additive blend mode:
    //   1. Up to 8 trail segment dots along travel path (α 0.4)
    //   2. Core glow at head position (α 0.45)
    //   3. Large bloom overlay (α 0.3)
    const lifeAlpha = Math.max(0, Math.min(1.0, proj.lifetime * 2.5));
    if (lifeAlpha < 0.01) return;

    const { x, y, angle } = proj;
    // C: speedScale for PLASMA_RIFLE is about 1.0; trail dot size = 22×22
    const speedScale = glowSize / 56.0; // normalize relative to PLASMA_RIFLE's 56
    const dotSize = 22 * speedScale;
    const halfDot = dotSize / 2;
    const bloomSize = glowSize * 4.57; // C: 256 for glowSize=56 → ratio ≈ 4.57
    const halfBloom = bloomSize / 2;
    const halfGlow = glowSize / 2;

    // Trail direction: opposite of travel (behind the projectile)
    // C stores angle with +PI/2 offset, so C uses angle+PI/2 to get backward.
    // TS stores angle as actual movement direction, so we use angle+PI.
    const travelAngle = angle + Math.PI;
    const dirX = Math.cos(travelAngle);
    const dirY = Math.sin(travelAngle);
    const segmentSpacing = speedScale * 2.5;

    if (!ctx.hasParticlesSprite) {
        // Fallback: simple glow circle
        grim.setColor(r, g, b, Math.floor(lifeAlpha * 0.45 * 255));
        grim.drawCircleFilled(x, y, glowSize * 0.5);
        return;
    }

    grim.bindTexture(ctx.particlesHandle);
    // C code: effect_select_texture(0xd) → effect_id_table[13] = {0x40, 3}
    // Frame 3 in 4×4 grid = golden glow orb at (192,0) in particles.jaz
    grim.setAtlasFrame(4, 3);
    grim.setRotation(0);
    grim.setBlendMode('add');

    // --- Layer 1: Trail segment dots (up to 8) along travel path, α = 0.4 ---
    const trailAlpha = Math.floor(0.4 * lifeAlpha * 255);
    if (trailAlpha > 0 && segmentSpacing > 0) {
        grim.setColor(r, g, b, trailAlpha);
        for (let i = 1; i <= 8; i++) {
            const offset = i * segmentSpacing;
            const px = x - dirX * offset;
            const py = y - dirY * offset;
            grim.drawQuad(px - halfDot, py - halfDot, dotSize, dotSize);
        }
    }

    // --- Layer 2: Core glow at head position, α = 0.45 ---
    const coreAlpha = Math.floor(0.45 * lifeAlpha * 255);
    grim.setColor(r, g, b, coreAlpha);
    grim.drawQuad(x - halfGlow, y - halfGlow, glowSize, glowSize);

    // --- Layer 3: Bloom overlay, α = 0.3 ---
    const bloomAlpha = Math.floor(0.3 * lifeAlpha * 255);
    grim.setColor(r, g, b, bloomAlpha);
    grim.drawQuad(x - halfBloom, y - halfBloom, bloomSize, bloomSize);

    grim.setBlendMode('normal');
}

function drawSpecialProjectile(
    ctx: ProjectileTextureContext,
    grim: GrimInterface,
    x: number,
    y: number,
    angle: number,
    atlasSize: number,
    frame: number,
    r: number,
    g: number,
    b: number,
    size: number,
): void {
    if (ctx.hasProjectileSprite) {
        grim.bindTexture(ctx.projectileHandle);
        grim.setAtlasFrame(atlasSize, frame);
        grim.setColor(r, g, b, 255);
        grim.setRotation(angle);
        grim.drawQuad(x - size / 2, y - size / 2, size, size);
        grim.setRotation(0);
    } else {
        grim.setColor(r, g, b, 255);
        grim.drawCircleFilled(x, y, size / 2);
    }
}

/**
 * Draw pulse gun wave — like drawSpecialProjectile but with alpha support.
 * C code: alive phase uses alpha 0.7, dying phase uses lifetime*2.5 fade.
 */
function drawPulseWave(
    ctx: ProjectileTextureContext,
    grim: GrimInterface,
    x: number,
    y: number,
    angle: number,
    atlasSize: number,
    frame: number,
    r: number,
    g: number,
    b: number,
    size: number,
    alpha: number,
): void {
    const a = Math.floor(Math.max(0, Math.min(1, alpha)) * 255);
    // C: pulse gun rendered in second pass with additive blend (glow effect)
    grim.setBlendMode('add-alpha');
    if (ctx.hasProjectileSprite) {
        grim.bindTexture(ctx.projectileHandle);
        grim.setAtlasFrame(atlasSize, frame);
        grim.setColor(r, g, b, a);
        grim.setRotation(angle);
        grim.drawQuad(x - size / 2, y - size / 2, size, size);
        grim.setRotation(0);
    } else {
        grim.setColor(r, g, b, a);
        grim.drawCircleFilled(x, y, size / 2);
    }
    grim.setBlendMode('normal');
}

/**
 * Draw PLAGUE_SPREADER projectile — C-accurate multi-sprite cluster.
 *
 * C reference: projectiles.c L1905-1947 (separate rendering pass, normal blend)
 *
 * The C code renders a cluster of 5 overlapping sprites:
 *   1. Main 60×60 quad at projectile position
 *   2. Velocity-offset 60×60 quad (15px along travel direction)
 *   3-5. Three 52-62px quads at animated 120° intervals with cos/sin offset
 */
function drawPlagueSpreaderProjectile(
    ctx: ProjectileTextureContext,
    grim: GrimInterface,
    proj: ProjectileRenderData,
): void {
    const { x, y, angle, lifetime } = proj;
    const isAlive = lifetime >= 0.4;

    if (!ctx.hasProjectileSprite) {
        // Fallback: simple cluster of circles
        grim.setColor(255, 255, 255, 255);
        grim.drawCircleFilled(x, y, 15);
        return;
    }

    grim.bindTexture(ctx.projectileHandle);
    // C: uses particles_texture with normal blend (config 0x13=1, 0x14=6)
    grim.setBlendMode('normal');

    if (isAlive) {
        grim.setColor(255, 255, 255, 255);

        // 1. Main 60×60 quad
        grim.drawQuad(x - 30, y - 30, 60, 60);

        // 2. Velocity-offset 60×60 quad (15px along angle + PI/2 direction)
        const velAngle = angle + Math.PI / 2;
        const offX = Math.cos(velAngle) * 15;
        const offY = Math.sin(velAngle) * 15;
        grim.drawQuad(x + offX - 30, y + offY - 30, 60, 60);

        // 3-5. Three animated sub-sprites at 120° intervals
        // C: uses (index + fStack_150) as time counter, with 2pi/3 spacing
        const t = proj.frameTime ?? Date.now() * 0.001;
        for (let i = 0; i < 3; i++) {
            const subAngle = t + i * 2.0943952; // 120° apart
            const subCos = Math.cos(subAngle);
            const subSin = Math.sin(subAngle);
            // C sizes: 52, 62, 62 for the three sub-quads
            const subSize = i === 0 ? 52 : 62;
            const subOff = i === 0 ? 11 : 10;
            grim.drawQuad(
                x + subCos * subOff - subSize / 2,
                y + subSin * subOff - subSize / 2,
                subSize,
                subSize,
            );
        }
    } else {
        // C: dying phase — fading glow that grows
        const fadeAlpha = Math.max(0, Math.min(1, lifetime * 2.5));
        grim.setColor(255, 255, 255, Math.floor(fadeAlpha * 255));
        // C: size = fadeAlpha * 40 + 32 (width), half = fadeAlpha * 20 + 16
        const fadeSize = fadeAlpha * 40 + 32;
        grim.drawQuad(x - fadeSize / 2, y - fadeSize / 2, fadeSize, fadeSize);
    }
}

/**
 * Draw ION projectile — C-accurate particle trail rendering.
 *
 * C reference: projectiles.c lines 1729-1893
 *
 * The C code uses atlas frame (4,2) — the flame/glow sprite —
 * composited along the beam path in additive blend to create a
 * blue-white fireball-like energy beam.
 *
 * Color: (0.5, 0.6, 1.0) for ion weapons (vs (1.0, 0.6, 0.1) for fire bullets)
 */
function drawIonProjectile(
    ctx: ProjectileTextureContext,
    grim: GrimInterface,
    proj: ProjectileRenderData,
    beamScale: number,
): void {
    const { x, y, angle, lifetime } = proj;
    const lifeAlpha = Math.max(0, Math.min(1.0, lifetime * 2.5));
    if (lifeAlpha < 0.01) return;

    // C: speedScale stored on projectile, defaults to 1.0
    const speedScale = beamScale;

    // Alive phase (lifetime == 0.4) — draw beam trail
    const isAlive = lifetime >= 0.4;

    if (isAlive) {
        if (!ctx.hasProjectileSprite) {
            // Fallback: simple line + circles (no projectile texture)
            const beamWidth = 4 * beamScale;
            const beamLength = 16 * beamScale;
            const cos = Math.cos(angle);
            const sin = Math.sin(angle);
            grim.setColor(128, 153, 255, 255);
            grim.drawLine(x, y, x - cos * beamLength, y - sin * beamLength, beamWidth);
            grim.setColor(128, 153, 255, 100);
            grim.drawCircleFilled(x, y, beamWidth * 1.5);
            grim.setColor(255, 255, 255, 200);
            grim.drawCircleFilled(x, y, beamWidth * 0.5);
            return;
        }

        // --- C-accurate ion beam rendering ---
        // C: binds projectile_texture (projs.jaz), sets atlas frame (4,2)
        // The trail uses the energy wave sprite from projs.jaz (NOT particles.jaz)
        grim.bindTexture(ctx.projectileHandle);
        grim.setAtlasFrame(4, 2);
        grim.setRotation(angle);
        grim.setBlendMode('add');

        // C: trail extends from head backward along travel direction
        // Position is head pos; trail goes backward to origin
        const headX = proj.headX;
        const headY = proj.headY;
        const tailX = proj.tailX;
        const tailY = proj.tailY;
        const dx = headX - tailX;
        const dy = headY - tailY;
        const trailLength = Math.sqrt(dx * dx + dy * dy);

        // C: fVar30 = cos(angle+PI/2) * speedScale, fVar23 = sin(angle+PI/2) * speedScale
        // Direction from head back toward tail (behind the projectile)
        const travelAngle = angle + Math.PI;
        const dirX = Math.cos(travelAngle);
        const dirY = Math.sin(travelAngle);

        // C: trail segment spacing = speedScale * 3.1, capped at 9.0
        const segStep = Math.min(speedScale * 3.1, 9.0);
        // C: quad size = speedScale * 32.0
        const quadSize = speedScale * 32.0;
        const halfQuad = quadSize / 2;
        // C: head glow size = speedScale * 16.0 (half of quadSize)
        const glowHalf = speedScale * 16.0;

        // C: clamp trail to 256 px max, offset if longer
        const clampedLength = Math.min(trailLength, 256.0);
        const startOffset = trailLength > 256.0 ? trailLength - 256.0 : 0.0;

        // --- Trail segment quads along beam path ---
        if (clampedLength > 0 && segStep > 0) {
            let dist = startOffset;
            while (dist < trailLength) {
                // C: alpha = ((dist - startOffset) / clampedLength) * masterAlpha * lifeAlpha
                const t = (dist - startOffset) / clampedLength;
                const segAlpha = Math.floor(t * lifeAlpha * 255);
                if (segAlpha > 0) {
                    // C: color (0.5, 0.6, 1.0) for ion weapons
                    grim.setColor(128, 153, 255, segAlpha);
                    const px = headX + dirX * dist;
                    const py = headY + dirY * dist;
                    grim.drawQuad(px - halfQuad, py - halfQuad, quadSize, quadSize);
                }
                dist += segStep;
            }
        }

        // --- Head glow sprite at projectile head (C: color 1.0, 1.0, 0.7) ---
        grim.setRotation(angle);
        grim.setColor(255, 255, 179, Math.floor(lifeAlpha * 255));
        grim.drawQuad(x - glowHalf, y - glowHalf, glowHalf * 2, glowHalf * 2);

        grim.setRotation(0);
        grim.setBlendMode('normal');
    } else {
        // --- Dying/fading phase (lifetime < 0.4) ---
        // C: stationary glow at head position + expanding radius
        if (!ctx.hasProjectileSprite) {
            grim.setColor(128, 153, 255, Math.floor(lifeAlpha * 200));
            grim.drawCircleFilled(x, y, 16);
            return;
        }

        grim.bindTexture(ctx.projectileHandle);
        grim.setAtlasFrame(4, 2);
        grim.setRotation(0);
        grim.setBlendMode('add');

        // C: stationary 32×32 glow at head with color (0.5, 0.6, 1.0)
        grim.setColor(128, 153, 255, Math.floor(lifeAlpha * 255));
        grim.drawQuad(x - 16, y - 16, 32, 32);

        // C: expanding radius glow — fStack_190 = speedScale * ionMaster * 40.0
        const ionMaster = proj.ionMasterScale ?? 1.0;
        const radiusGlow = speedScale * ionMaster * 40.0;
        grim.setColor(128, 153, 255, Math.floor(lifeAlpha * 0.3 * 255));
        grim.drawQuad(x - radiusGlow, y - radiusGlow, radiusGlow * 2, radiusGlow * 2);

        grim.setBlendMode('normal');
    }
}

function drawFireBulletParticle(
    ctx: ProjectileTextureContext,
    grim: GrimInterface,
    proj: ProjectileRenderData,
): void {
    // C code reference: lines 20626-20680 (fire bullets share the ion rendering pass)
    const lifeAlpha = Math.max(0, Math.min(1.0, proj.lifetime * 2.5));
    if (lifeAlpha < 0.01) return;

    const speedScale = 0.8;
    const spriteSize = speedScale * 32.0; // 25.6px
    const halfSize = spriteSize / 2;

    if (!ctx.hasProjectileSprite) {
        // Fallback: orange circle
        grim.setColor(255, 153, 25, Math.floor(lifeAlpha * 255));
        grim.drawCircleFilled(proj.x, proj.y, halfSize);
        return;
    }

    // C: binds projectile_texture (projs.jaz), sets atlas frame (4,2)
    grim.bindTexture(ctx.projectileHandle);
    grim.setAtlasFrame(4, 2);
    grim.setBlendMode('add');

    // --- Beam trail extending backward from head toward tail ---
    const dx = proj.headX - proj.tailX;
    const dy = proj.headY - proj.tailY;
    const trailLength = Math.sqrt(dx * dx + dy * dy);
    const step = Math.min(speedScale * 3.1, 9.0); // C: step = speedScale * 3.1, capped at 9.0

    if (trailLength > 0 && step > 0) {
        // Direction from head back toward tail
        const dirX = -dx / trailLength;
        const dirY = -dy / trailLength;
        const maxDist = Math.min(trailLength, 256.0);

        for (let d = 0; d < maxDist; d += step) {
            const t = 1.0 - d / maxDist; // 1 at head, 0 at trail end
            const px = proj.headX + dirX * d;
            const py = proj.headY + dirY * d;
            const segAlpha = Math.floor(t * lifeAlpha * 255);
            if (segAlpha > 0) {
                grim.setColor(255, 153, 25, segAlpha); // Orange (1.0, 0.6, 0.1)
                grim.drawQuad(px - halfSize, py - halfSize, spriteSize, spriteSize);
            }
        }
    }

    // --- Head sprite (bright white-yellow, C: 1.0, 1.0, 0.7) ---
    grim.setColor(255, 255, 179, Math.floor(lifeAlpha * 255));
    grim.setRotation(proj.angle);
    grim.drawQuad(proj.x - halfSize, proj.y - halfSize, spriteSize, spriteSize);
    grim.setRotation(0);
    grim.setBlendMode('normal');
}

function drawRocketProjectile(
    ctx: ProjectileTextureContext,
    grim: GrimInterface,
    x: number,
    y: number,
    angle: number,
    spriteSize: number,
    glowTrailSize: number,
    glowR: number,
    glowG: number,
    glowB: number,
    glowAlphaScale: number,
): void {
    // C rendering has 3 passes for secondary projectiles:
    // 1. General glow (particles_texture, effect 0xd, 140×140, alpha 0.48)
    // 2. Rocket sprite (projectile_texture / projs.jaz, atlas(4,3)) — NORMAL blend
    // 3. Type-specific trailing glow (particles_texture, behind rocket) — ADDITIVE on top
    //
    // Critical: C renders sprites BEFORE trailing glows (L2055-2094 then L2096-2149).
    // The additive glow ON TOP of the sprite makes the rocket visible with a bright halo.

    // C: glow trail is offset BEHIND the rocket by cos/sin(angle - PI/2) * 9.0
    const trailAngle = angle - Math.PI / 2;
    const trailOffsetX = Math.cos(trailAngle) * 9.0;
    const trailOffsetY = Math.sin(trailAngle) * 9.0;
    const trailX = x - trailOffsetX;
    const trailY = y - trailOffsetY;

    // --- Pass 0: General 140×140 glow for ALL active secondary projectiles ---
    // C L2032-2052: particles_texture, effect_select_texture(0xd) = glow orb,
    // SRCBLEND=SRC_ALPHA(5), DESTBLEND=ONE(2) = additive blend.
    // Color (1,1,1, masterAlpha * 0.48). Offset by cos/sin(angle-PI/2) * 5.
    // This large white halo is what makes the small rocket sprites visible.
    if (ctx.hasParticlesSprite) {
        const glowOffX = Math.cos(trailAngle) * 5.0;
        const glowOffY = Math.sin(trailAngle) * 5.0;
        const glowX = x - glowOffX;
        const glowY = y - glowOffY;
        grim.bindTexture(ctx.particlesHandle);
        grim.setAtlasFrame(4, 3); // GLOW_ORB = frame 3 in 4×4 grid
        grim.setBlendMode('add');
        grim.setColor(255, 255, 255, Math.floor(0.48 * 255));
        grim.setRotation(0);
        grim.drawQuad(glowX - 70, glowY - 70, 140, 140);
        grim.setBlendMode('normal');
    }

    // --- Pass 1: Rocket sprite (projs.jaz, atlas frame (4,3) = rocket/missile) ---
    // C L2058-2094: projectile_texture with atlas(4,3), color (0.8, 0.8, 0.8), NORMAL blend
    // Rendered FIRST so the sprite is the base layer
    if (ctx.hasProjectileSprite) {
        grim.bindTexture(ctx.projectileHandle);
        grim.setAtlasFrame(4, 3); // Rocket sprite in projs.jaz (upper-right cell)
        grim.setColor(204, 204, 204, 255); // C: (0.8, 0.8, 0.8) gray
        // C: angle = aim_heading = velocity_direction + PI/2 (fx_spawn_secondary_projectile
        // uses cos/sin(angle - PI/2) for velocity). C renders at this raw angle.
        // TS: angle = velocity_direction (no offset), so add PI/2 to match C orientation.
        grim.setRotation(angle + Math.PI / 2);
        const half = spriteSize / 2;
        grim.drawQuad(x - half, y - half, spriteSize, spriteSize);
        grim.setRotation(0);
    } else {
        // Fallback: orange circle when projs.jaz isn't loaded
        grim.setColor(255, 100, 0, 255);
        grim.drawCircleFilled(x, y, spriteSize / 2);
    }

    // --- Pass 2: Trailing glow (particles.jaz, behind rocket) ---
    // C L2096-2149: type-specific glow colors and sizes, ADDITIVE blend
    // Rendered AFTER sprite so glow adds brightness on top, creating halo effect
    if (ctx.hasParticlesSprite) {
        grim.bindTexture(ctx.particlesHandle);
        // C: effect_select_texture(0xd) → frame 3 of 4×4 grid (golden glow orb)
        grim.setAtlasFrame(4, 3);
        grim.setBlendMode('add-alpha');
        grim.setColor(glowR, glowG, glowB, Math.floor(glowAlphaScale * 255));
        grim.setRotation(0);
        grim.drawQuad(
            trailX - glowTrailSize / 2,
            trailY - glowTrailSize / 2,
            glowTrailSize,
            glowTrailSize,
        );
        grim.setBlendMode('normal');
    }
}

/**
 * Draw lightning bolts from a dying ION projectile to nearby enemies.
 *
 * C reference: projectiles.c lines 1848-1890
 *
 * Called as a separate pass after per-projectile rendering, because it
 * needs access to enemy positions (which the per-projectile renderer doesn't have).
 *
 * @param ctx       Texture context
 * @param grim      Rendering interface
 * @param projX     Projectile position X
 * @param projY     Projectile position Y
 * @param projAngle Projectile angle
 * @param beamScale Speed scale of the projectile (e.g. 2.2 for ION_RIFLE)
 * @param lifeAlpha Alpha multiplier based on lifetime
 * @param targets   Array of {x, y} positions for nearby enemies in range
 */
export function drawIonLightningBolts(
    ctx: ProjectileTextureContext,
    grim: GrimInterface,
    projX: number,
    projY: number,
    projAngle: number,
    beamScale: number,
    lifeAlpha: number,
    targets: ReadonlyArray<{ x: number; y: number }>,
): void {
    if (targets.length === 0 || !ctx.hasProjectileSprite) return;

    grim.bindTexture(ctx.projectileHandle);
    grim.setBlendMode('add');

    // C: perpendicular direction for beam width
    const perpAngle = projAngle + Math.PI / 2;
    const perpCos = Math.cos(perpAngle);
    const perpSin = Math.sin(perpAngle);

    for (const target of targets) {
        // --- Lightning bolt quad strip from projectile to target ---
        // C: grim_set_uv_point(0, 0.625, 0.0); (1, 0.625, 0.25); (2, 0.625, 0.25); (3, 0.625, 0.0)
        grim.setUV(0.625, 0.0, 0.625, 0.25);
        grim.setColor(128, 153, 255, Math.floor(lifeAlpha * 255));

        // Inner bolt: ±10px perpendicular offset
        const innerOffset = 10.0;
        const x1 = projX - perpCos * innerOffset;
        const y1 = projY - perpSin * innerOffset;
        const x2 = projX + perpCos * innerOffset;
        const y2 = projY + perpSin * innerOffset;
        const x3 = target.x + perpCos * innerOffset;
        const y3 = target.y + perpSin * innerOffset;
        const x4 = target.x - perpCos * innerOffset;
        const y4 = target.y - perpSin * innerOffset;

        grim.drawQuadPoints(x1, y1, x2, y2, x3, y3, x4, y4);

        // Outer bolt: ±4px extra offset (thicker glow layer)
        const outerExtra = 4.0;
        grim.drawQuadPoints(
            x1 - perpCos * outerExtra,
            y1 - perpSin * outerExtra,
            x2 + perpCos * outerExtra,
            y2 + perpSin * outerExtra,
            x3 + perpCos * outerExtra,
            y3 + perpSin * outerExtra,
            x4 - perpCos * outerExtra,
            y4 - perpSin * outerExtra,
        );

        // --- Glow sprite at target enemy position ---
        // C: grim_set_atlas_frame(4,2); grim_draw_quad at target pos
        const glowSize = beamScale * 32.0;
        const halfGlow = glowSize / 2;
        grim.setAtlasFrame(4, 2);
        grim.setColor(128, 153, 255, Math.floor(lifeAlpha * 255));
        grim.drawQuad(target.x - halfGlow, target.y - halfGlow, glowSize, glowSize);
    }

    grim.setBlendMode('normal');
}
