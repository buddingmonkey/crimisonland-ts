/**
 * BloodEffectSystem - Blood splatter effects with terrain baking
 *
 * Accurate port of effect_spawn_blood_splatter (effects.c L982-1027),
 * fx_queue_add_random (effects.c L308-351), fx_queue_render (effects.c L401-508),
 * and creature death blood (creatures.c L1673-1695).
 *
 * C code pipeline:
 * 1. Blood particles fly out from death point (effect pool)
 * 2. On expiry (flag 0x80), particles are queued in fx_queue_ground_pool
 * 3. fx_queue_render bakes the ground pool into terrain_render_target
 *    using particles_texture with standard alpha blend (not additive)
 * 4. Result: permanent blood stains on terrain that accumulate
 *
 * This replaces the overlay decal approach with actual render-to-texture
 * baking, matching the C code's terrain_render_target system.
 */

import * as PIXI from 'pixi.js';
import type { GrimInterface, TextureHandle } from '../../engine/GrimInterface';
import type { TerrainRenderer } from '../../rendering/TerrainRenderer';
import { TERRAIN_BUFFER } from '../../rendering/TerrainRenderer';
import { ParticleFrame, PARTICLE_ATLAS, getFrameUV } from '../../data/ParticleAtlas';

// ========================================================================
// Blood effect entry (mirrors C effect_entry_t for blood)
// ========================================================================
interface BloodEffect {
    active: boolean;
    x: number;
    y: number;
    velX: number;
    velY: number;
    rotation: number; // Current rotation (radians)
    rotationStep: number; // Rotation speed (radians/sec)
    halfWidth: number; // Half extent for quad
    halfHeight: number;
    age: number; // Current age (seconds); negative = delayed
    lifetime: number; // Max lifetime (seconds)
    scaleStep: number; // Scale growth rate
    colorR: number;
    colorG: number;
    colorB: number;
    colorA: number;
    flags: number; // C flags (0xc9 for blood)
    effectId: number; // Atlas effect ID
}

// ========================================================================
// Pending terrain stamp (mirrors C fx_queue_entry_t)
// ========================================================================
interface PendingStamp {
    x: number;
    y: number;
    width: number;
    height: number;
    rotation: number;
    colorR: number;
    colorG: number;
    colorB: number;
    colorA: number;
    effectId: number; // Atlas effect ID
}

// ========================================================================
// Pending corpse bake (mirrors C fx_queue_rotated_pool entry)
// Uses bodyset texture + type-based corpse frame selection
// ========================================================================
interface PendingCorpse {
    x: number;
    y: number;
    size: number; // creature.size
    rotation: number; // creature.heading
    colorR: number; // creature.tint_r
    colorG: number; // creature.tint_g
    colorB: number; // creature.tint_b
    colorA: number; // creature.tint_a
    corpseFrame: number; // CREATURE_TYPE_TABLE[typeId].corpseFrame (0-15, 4×4 bodyset grid)
}

// Atlas UV table is in src/data/ParticleAtlas.ts — see ParticleFrame enum.
// UV computation via getFrameUV() from ParticleAtlas.
//
// Blood effects use BLOOD_SPLAT_A through BLOOD_SPLAT_D (8×8 grid blood
// textures) for both flying particles and terrain baking. These are the
// actual red blood splat shapes in the atlas.

/**
 * BloodEffectSystem
 *
 * Manages blood splatter particles and terrain-baked blood stains.
 * C code references:
 * - effect_spawn_blood_splatter @ 0042eb10
 * - fx_queue_add_random @ 00427700
 * - fx_queue_render @ 00427920
 * - creature death blood @ creatures.c L1673-1695
 * - effects_update @ 0042e710
 * - effects_render @ 0042e820
 */
export class BloodEffectSystem {
    // Effect pool (flying blood particles)
    private effects: BloodEffect[] = [];
    private readonly maxEffects = 128;

    // Pending stamps to bake into terrain (C: fx_queue_ground_pool)
    // Accumulated during update(), flushed in bakeToTerrain()
    private pendingStamps: PendingStamp[] = [];

    // Pending corpse bakes (C: fx_queue_rotated_pool)
    // Uses bodyset texture with per-type corpse frame, enemy's actual tint/size
    private pendingCorpses: PendingCorpse[] = [];

    // Texture references
    private particlesHandle: TextureHandle = -1;
    private particlesTexture: PIXI.Texture | null = null; // PIXI texture for baking
    private bodysetTexture: PIXI.Texture | null = null; // PIXI bodyset texture for corpse baking

    // Terrain renderer reference (for baking)
    private terrainRenderer: TerrainRenderer | null = null;

    constructor() {
        // Pre-allocate effect pool
        for (let i = 0; i < this.maxEffects; i++) {
            this.effects.push(this.createBlankEffect());
        }
    }

    /**
     * Set particles texture handle (for Grim rendering of flying particles)
     */
    setParticlesTexture(handle: TextureHandle): void {
        this.particlesHandle = handle;
    }

    /**
     * Set PIXI texture for terrain baking (from AssetManager)
     */
    setParticlesPixiTexture(texture: PIXI.Texture): void {
        this.particlesTexture = texture;
    }

    /**
     * Set bodyset PIXI texture for corpse baking
     */
    setBodysetPixiTexture(texture: PIXI.Texture): void {
        this.bodysetTexture = texture;
    }

    /**
     * Queue a corpse stamp using the enemy's actual tint, size, heading, and type.
     * Mirrors C code: fx_queue_add_rotated(pos, &creature.tint_r, heading, size, type_id)
     *
     * @param x - Enemy center X
     * @param y - Enemy center Y
     * @param size - Enemy size (creature.size)
     * @param rotation - Enemy heading in radians
     * @param r - tint_r (0-1)
     * @param g - tint_g (0-1)
     * @param b - tint_b (0-1)
     * @param a - tint_a (0-1)
     * @param corpseFrame - CREATURE_TYPE_TABLE[typeId].corpseFrame (4×4 bodyset grid index)
     */
    queueCorpseStamp(
        x: number,
        y: number,
        size: number,
        rotation: number,
        r: number,
        g: number,
        b: number,
        a: number,
        corpseFrame: number,
    ): void {
        this.pendingCorpses.push({ x, y, size, rotation, colorR: r, colorG: g, colorB: b, colorA: a, corpseFrame });
    }

    /**
     * Set terrain renderer for baking stamps
     */
    setTerrainRenderer(terrain: TerrainRenderer): void {
        this.terrainRenderer = terrain;
    }

    // ====================================================================
    // Spawning
    // ====================================================================

    /**
     * Spawn blood splatter particles
     * C code: effect_spawn_blood_splatter @ 0042eb10
     *
     * Colors: WHITE (1,1,1,0.5) — C-accurate!
     * The texture frame 6 provides the actual blood color.
     * When baked into terrain with alpha blend, the texture color
     * permanently stains the terrain pixels.
     *
     * @param x Position X
     * @param y Position Y
     * @param angle Impact angle (radians)
     * @param age Start age offset (0, -0.07, or -0.12 for layered death)
     */
    spawnBloodSplatter(x: number, y: number, angle: number, age: number = 0): void {
        if (this.particlesHandle < 0) return;

        const lifetime = 0.25 - age;
        const reversedAngle = angle + Math.PI;
        const cosA = Math.cos(reversedAngle);
        const sinA = Math.sin(reversedAngle);

        // Spawn 2 particles per call (C: iVar2 = 2; do { ... } while)
        for (let i = 0; i < 2; i++) {
            const slot = this.allocEffectSlot();
            const effect = this.effects[slot];

            effect.active = true;
            effect.x = x;
            effect.y = y;
            effect.effectId = ParticleFrame.BLOOD_SPLAT_A;
            effect.flags = 0xc9; // 0x80|0x40|0x08|0x01

            // C code: WHITE tint (1.0, 1.0, 1.0, 0.5)
            // The particles texture frame 6 provides the actual color.
            // C lines: _effect_template_color_r/g/b = 0x3f800000 (1.0)
            //          _effect_template_color_a = 0x3f000000 (0.5)
            effect.colorR = 1.0;
            effect.colorG = 1.0;
            effect.colorB = 1.0;
            effect.colorA = 0.5;

            effect.age = age;
            effect.lifetime = lifetime;
            effect.rotationStep = 0;
            // C: _effect_template_scale_step = (rand & 0x7f) * 0.03 + 0.1
            effect.scaleStep = ((Math.random() * 128) | 0) * 0.03 + 0.1;

            // Random rotation: (rand & 0x3f - 0x20) * 0.1 + reversedAngle
            const rotOffset = (((Math.random() * 64) | 0) - 0x20) * 0.1;
            effect.rotation = rotOffset + reversedAngle;

            // Random half-size: (rand & 7) + 1
            const halfSize = ((Math.random() * 8) | 0) + 1;
            effect.halfWidth = halfSize;
            effect.halfHeight = halfSize;

            // Velocity: ((rand & 0x3f) + 100) * cos/sin
            const speed = ((Math.random() * 64) | 0) + 100;
            effect.velX = speed * cosA;
            effect.velY = speed * sinA;
        }
    }

    /**
     * Spawn death blood burst (19 blood splatters in 3 layers)
     * C code: creatures.c L1674-1694
     *
     * @param x Enemy death position X
     * @param y Enemy death position Y
     */
    spawnDeathBlood(x: number, y: number): void {
        // Layer 1: 8 splatters at age = 0.0
        for (let i = 0; i < 8; i++) {
            const angle = ((Math.random() * 0x264) | 0) * 0.01;
            this.spawnBloodSplatter(x, y, angle, 0.0);
        }
        // Layer 2: 6 splatters at age = -0.07
        for (let i = 0; i < 6; i++) {
            const angle = ((Math.random() * 0x264) | 0) * 0.01;
            this.spawnBloodSplatter(x, y, angle, -0.07);
        }
        // Layer 3: 5 splatters at age = -0.12
        for (let i = 0; i < 5; i++) {
            const angle = ((Math.random() * 0x264) | 0) * 0.01;
            this.spawnBloodSplatter(x, y, angle, -0.12);
        }
    }

    /**
     * Directly stamp a blood mark into the terrain.
     * C code: fx_queue_add_random @ 00427700
     *
     * Used by systems that want to place blood directly without
     * flying particles (e.g. initial death splat).
     */
    queueDirectStamp(
        x: number,
        y: number,
        width: number,
        height: number,
        rotation: number,
        r: number,
        g: number,
        b: number,
        a: number,
        effectId: number = ParticleFrame.BLOOD_SPLAT_A,
    ): void {
        this.pendingStamps.push({
            x,
            y,
            width,
            height,
            rotation,
            colorR: r,
            colorG: g,
            colorB: b,
            colorA: a,
            effectId,
        });
    }

    /**
     * Add a random ground debris stamp into the terrain.
     * C code: fx_queue_add_random @ 00427700
     *
     * Randomizes:
     * - effectId: rand()%4+3 → BLOOD_SPLAT_A(3) through BLOOD_SPLAT_D(6)
     * - size: rand()%24-12+30 → 18-42 pixels
     * - rotation: rand()%628 * 0.01 → 0-6.28 radians
     * - grayscale tint: (rand()&0xf)*0.01+0.84 → 0.84-0.99
     * - alpha: 0.78 (C: 0x3f47ae14)
     */
    addRandomGroundDebris(x: number, y: number): void {
        const tint = ((Math.random() * 16) | 0) * 0.01 + 0.84;
        const size = ((Math.random() * 24) | 0) - 12 + 30;
        const rotation = ((Math.random() * 628) | 0) * 0.01;
        const effectId = ((Math.random() * 4) | 0) + ParticleFrame.BLOOD_SPLAT_A;

        // C code positions stamp at (pos.x - size*0.5, pos.y - size*0.5)
        // Our stamp uses anchor(0.5,0.5) so we use the center position directly
        this.pendingStamps.push({
            x,
            y,
            width: size,
            height: size,
            rotation,
            colorR: tint,
            colorG: tint,
            colorB: tint,
            colorA: 0.78, // C: 0x3f47ae14 ≈ 0.78
            effectId,
        });
    }

    // ====================================================================
    // Update
    // ====================================================================

    /**
     * Update all active blood effects
     * C code: effects_update @ 0042e710
     *
     * When effects expire with flag 0x80, they are queued as pending
     * stamps instead of creating overlay decals. The stamps are baked
     * into the terrain on the next bakeToTerrain() call.
     *
     * @param dt Delta time in seconds
     */
    update(dt: number): void {
        for (const effect of this.effects) {
            if (!effect.active) continue;

            // Advance age
            effect.age += dt;

            // Check expiry
            if (effect.age >= effect.lifetime) {
                // If flag 0x80 set, queue terrain stamp on expiry
                // C code: effects_update L888-897 → fx_queue_add
                //
                // White tint (1,1,1) lets the red blood texture color through.
                // The blood splat frames (8×8 grid row 0, frames 2-5) are
                // red-colored in the particles.jaz texture.
                if ((effect.flags & 0x80) !== 0) {
                    const stampAlpha = (effect.flags & 0x100) !== 0 ? 0.35 : 0.8;
                    this.pendingStamps.push({
                        x: effect.x,
                        y: effect.y,
                        width: effect.halfWidth * 2,
                        height: effect.halfHeight * 2,
                        rotation: effect.rotation,
                        colorR: effect.colorR,
                        colorG: effect.colorG,
                        colorB: effect.colorB,
                        colorA: stampAlpha,
                        effectId: effect.effectId,
                    });
                }
                effect.active = false;
                continue;
            }

            // Skip if age < 0 (delayed spawn)
            if (effect.age < 0) continue;

            // Apply velocity (C L872-875)
            effect.x += effect.velX * dt;
            effect.y += effect.velY * dt;

            // Apply rotation step if flag 0x04 (C L876-878)
            if ((effect.flags & 0x04) !== 0) {
                effect.rotation += effect.rotationStep * dt;
            }

            // Apply scale step if flag 0x08 (C L879-881)
            if ((effect.flags & 0x08) !== 0) {
                effect.halfWidth += effect.scaleStep * dt;
                effect.halfHeight += effect.scaleStep * dt;
            }

            // Apply alpha fade if flag 0x10 (C L882-884)
            if ((effect.flags & 0x10) !== 0) {
                effect.colorA = 1.0 - effect.age / effect.lifetime;
            }
        }
    }

    // ====================================================================
    // Terrain Baking (replaces overlay decals)
    // ====================================================================

    /**
     * Bake all pending stamps into the terrain render texture.
     *
     * C code: fx_queue_render @ 00427920
     *
     * Pipeline:
     * 1. Set render target to terrain_render_target
     * 2. Bind particles_texture
     * 3. For each stamp: set color, rotation, UV from effect_id, draw quad
     * 4. Clear queue
     *
     * Coordinate transformation:
     * The terrain texture (1024×1024) is drawn stretched to fill the screen
     * (e.g. 800×600). Blood stamp positions are in world/screen coordinates,
     * so they must be scaled to terrain texture coordinates:
     *   texX = worldX / screenW * texW
     *   texY = worldY / screenH * texH
     *
     * C code: fVar5 = 1.0 / config_blob.reserved0._112_4_ (quality scale)
     * Applied as: draw_quad((pos_x - w*0.5) * fVar5, (pos_y - h*0.5) * fVar5, w*fVar5, h*fVar5)
     *
     * Blend mode: standard alpha blend (SRC_ALPHA, INV_SRC_ALPHA)
     * With white tint: src = texture color, which stains the terrain.
     */
    bakeToTerrain(): void {
        if (!this.terrainRenderer) return;
        if (this.pendingStamps.length === 0 && this.pendingCorpses.length === 0) return;

        // TilingSprite displays terrain texture at 1:1 pixel scale (no stretch),
        // so screen coordinates map directly to terrain texture coordinates.

        const container = new PIXI.Container();

        // --- Particle blood stamps (fx_queue_ground_pool, particles.jaz) ---
        // Offset positions by TERRAIN_BUFFER because the render texture is
        // larger than the playable area: world (0,0) → texture (BUFFER, BUFFER)
        if (this.particlesTexture) {
            for (const stamp of this.pendingStamps) {
                const atlasEntry = PARTICLE_ATLAS[stamp.effectId as ParticleFrame];
                if (!atlasEntry) continue;

                const uv = getFrameUV(atlasEntry.gridSize, atlasEntry.frame);
                const source = this.particlesTexture.source;
                const frameRect = new PIXI.Rectangle(
                    uv.u0 * source.width,
                    uv.v0 * source.height,
                    (uv.u1 - uv.u0) * source.width,
                    (uv.v1 - uv.v0) * source.height,
                );
                const sprite = new PIXI.Sprite(new PIXI.Texture({ source, frame: frameRect }));
                sprite.width = stamp.width;
                sprite.height = stamp.height;
                sprite.anchor.set(0.5, 0.5);
                sprite.x = stamp.x + TERRAIN_BUFFER;
                sprite.y = stamp.y + TERRAIN_BUFFER;
                sprite.rotation = stamp.rotation;
                const tintR = Math.floor(stamp.colorR * 255);
                const tintG = Math.floor(stamp.colorG * 255);
                const tintB = Math.floor(stamp.colorB * 255);
                sprite.tint = (tintR << 16) | (tintG << 8) | tintB;
                sprite.alpha = stamp.colorA;
                sprite.blendMode = 'normal';
                container.addChild(sprite);
            }
        }

        // --- Corpse stamps (fx_queue_rotated_pool, bodyset.jaz) ---
        // C code fx_queue_render: two passes per corpse:
        //   Pass 1 (shadow): offset (+3,+3), size * 1.03, black tint, alpha * transparency
        //   Pass 2 (main sprite): normal position, normal size, enemy tint * transparency
        // cv_terrainBodiesTransparency defaults to ~0.6
        // Corpse frame from CREATURE_TYPE_TABLE[type_id].corpse_frame → 4×4 bodyset grid
        const TERRAIN_BODIES_TRANSPARENCY = 0.6; // C: cv_terrainBodiesTransparency
        if (this.bodysetTexture) {
            for (const corpse of this.pendingCorpses) {
                // Bodyset is 4×4 grid; corpseFrame = col + row*4
                const col = corpse.corpseFrame % 4;
                const row = Math.floor(corpse.corpseFrame / 4);
                const u0 = col * 0.25;
                const v0 = row * 0.25;

                const source = this.bodysetTexture.source;
                const frameRect = new PIXI.Rectangle(
                    u0 * source.width,
                    v0 * source.height,
                    0.25 * source.width,
                    0.25 * source.height,
                );
                const frameTexture = new PIXI.Texture({ source, frame: frameRect });

                const tintR = Math.floor(corpse.colorR * 255);
                const tintG = Math.floor(corpse.colorG * 255);
                const tintB = Math.floor(corpse.colorB * 255);
                const tintHex = (tintR << 16) | (tintG << 8) | tintB;

                // Pass 1: shadow at (+3,+3) offset, 1.03× size, black tint
                // C: grim_set_color(0,0,0, alpha * cv_terrainBodiesTransparency)
                const shadow = new PIXI.Sprite(frameTexture);
                shadow.width = corpse.size * 1.03;
                shadow.height = corpse.size * 1.03;
                shadow.anchor.set(0.5, 0.5);
                shadow.x = corpse.x + 3 + TERRAIN_BUFFER;
                shadow.y = corpse.y + 3 + TERRAIN_BUFFER;
                shadow.rotation = corpse.rotation;
                shadow.tint = 0x000000; // Black shadow (C: grim_set_color(0,0,0,...))
                shadow.alpha = corpse.colorA * TERRAIN_BODIES_TRANSPARENCY;
                shadow.blendMode = 'normal';
                container.addChild(shadow);

                // Pass 2: main sprite at full size, enemy tint color
                // C: grim_set_color(r,g,b, alpha * cv_terrainBodiesTransparency)
                const main = new PIXI.Sprite(frameTexture);
                main.width = corpse.size;
                main.height = corpse.size;
                main.anchor.set(0.5, 0.5);
                main.x = corpse.x + TERRAIN_BUFFER;
                main.y = corpse.y + TERRAIN_BUFFER;
                main.rotation = corpse.rotation;
                main.tint = tintHex;
                main.alpha = corpse.colorA * TERRAIN_BODIES_TRANSPARENCY;
                main.blendMode = 'normal';
                container.addChild(main);
            }
        }

        if (container.children.length > 0) {
            this.terrainRenderer.bakeBlood(container);
        }

        container.destroy({ children: true });
        this.pendingStamps.length = 0;
        this.pendingCorpses.length = 0;
    }

    // ====================================================================
    // Render (flying particles only — decals are baked into terrain)
    // ====================================================================

    /**
     * Render flying blood particles
     * C code: effects_render @ 0042e820
     *
     * This only renders the in-flight particles.
     * Once they expire, they're baked into terrain (no overlay needed).
     */
    renderBloodEffects(grim: GrimInterface): void {
        if (this.particlesHandle < 0) return;

        let hasActive = false;
        for (const e of this.effects) {
            if (e.active && e.age >= 0) {
                hasActive = true;
                break;
            }
        }
        if (!hasActive) return;

        grim.bindTexture(this.particlesHandle);

        // Blood uses non-additive blend (flags 0xc9 has bit 0x40 set → first render pass)
        // C: effects_render pass 1: grim_set_config_var(0x14, 6) = INV_SRC_ALPHA dest blend
        // with grim_set_config_var(0x13 left at default 5) = SRC_ALPHA src blend
        // → standard alpha blend
        grim.setBlendMode('normal');

        for (const effect of this.effects) {
            if (!effect.active) continue;
            if (effect.age < 0) continue; // Not yet visible

            grim.setColor(
                Math.floor(effect.colorR * 255),
                Math.floor(effect.colorG * 255),
                Math.floor(effect.colorB * 255),
                Math.floor(effect.colorA * 255),
            );
            grim.setRotation(effect.rotation);

            // Select atlas texture region
            this.selectEffectTexture(grim, effect.effectId);

            // Draw centered quad
            const w = effect.halfWidth * 2;
            const h = effect.halfHeight * 2;
            grim.drawQuad(effect.x - effect.halfWidth, effect.y - effect.halfHeight, w, h);
        }

        grim.setRotation(0);
        grim.setBlendMode('normal');
    }

    /**
     * Clear all effects and pending stamps
     */
    clear(): void {
        for (const effect of this.effects) {
            effect.active = false;
        }
        this.pendingStamps.length = 0;
        this.pendingCorpses.length = 0;
    }

    /**
     * Get active effect count (for debugging)
     */
    getActiveEffectCount(): number {
        let count = 0;
        for (const e of this.effects) {
            if (e.active) count++;
        }
        return count;
    }

    /**
     * Get pending stamp count (for debugging)
     */
    getPendingStampCount(): number {
        return this.pendingStamps.length;
    }

    // ====================================================================
    // Private helpers
    // ====================================================================

    /**
     * Allocate an effect slot (find free or replace random)
     * C code: effect_spawn free list, fallback to random
     */
    private allocEffectSlot(): number {
        // Find first inactive
        for (let i = 0; i < this.maxEffects; i++) {
            if (!this.effects[i].active) return i;
        }
        // Pool full: replace random slot
        return (Math.random() * this.maxEffects) | 0;
    }

    /**
     * Create a blank effect entry
     */
    private createBlankEffect(): BloodEffect {
        return {
            active: false,
            x: 0,
            y: 0,
            velX: 0,
            velY: 0,
            rotation: 0,
            rotationStep: 0,
            halfWidth: 1,
            halfHeight: 1,
            age: 0,
            lifetime: 0.25,
            scaleStep: 0,
            colorR: 1,
            colorG: 1,
            colorB: 1,
            colorA: 1,
            flags: 0,
            effectId: ParticleFrame.BLOOD_SPLAT_A,
        };
    }

    /**
     * Select effect texture UV region on particles atlas
     * C code: effect_select_texture @ 0042e0a0
     *
     * Maps ParticleFrame → (gridSize, frame) → grim.setAtlasFrame()
     */
    private selectEffectTexture(grim: GrimInterface, effectId: number): void {
        const entry = PARTICLE_ATLAS[effectId as ParticleFrame];
        if (entry) {
            grim.setAtlasFrame(entry.gridSize, entry.frame);
        } else {
            // Fallback: full texture
            grim.setUV(0, 0, 1, 1);
        }
    }
}
