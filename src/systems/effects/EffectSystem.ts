/**
 * EffectSystem - Advanced textured particle effects
 *
 * Accurate port of the C effect_pool system from effects.c.
 * This is SEPARATE from the basic ParticleSystem (fast/slow sparks) and
 * the BloodEffectSystem (blood splatters + terrain baking).
 *
 * C code references:
 * - effect_defaults_reset    @ 0042df10  (template reset)
 * - effect_spawn             @ 0042e120  (allocator + UV assignment)
 * - effects_update           @ 0042e710  (flag-driven per-frame update)
 * - effects_render           @ 0042e820  (two-pass additive/normal render)
 * - effect_spawn_freeze_shard   @ 0042ec80
 * - effect_spawn_freeze_shatter @ 0042ee00
 * - effect_spawn_burst          @ 0042ef60
 * - effect_spawn_shrink_fx      @ 0042f080
 * - fx_spawn_electric_arc       @ 0042f270
 * - fx_spawn_plasma_explosion   @ 0042f330
 * - fx_spawn_fire_particles     @ 0042f3f0
 * - fx_spawn_shockwave          @ 0042f540
 * - effect_spawn_explosion_burst @ 0042f6c0
 */

import type { GrimInterface, TextureHandle } from '../../engine/GrimInterface';
import { ParticleFrame, PARTICLE_ATLAS, getParticleUV } from '../../data/ParticleAtlas';

// ========================================================================
// Effect flag bits (from effects_update @ 0042e710)
// ========================================================================
const FLAG_ACTIVE = 0x01; // Bit 0: entry is alive
const FLAG_ROTATION = 0x04; // Bit 2: rotation += dt * rotationStep
const FLAG_SCALE = 0x08; // Bit 3: scale += dt * scaleStep
const FLAG_ALPHA_FADE = 0x10; // Bit 4: colorA = (1 - age/lifetime) * initialAlpha
const FLAG_ADDITIVE = 0x40; // Bit 6: render in Pass 1 (NORMAL blend). Misnomer — C uses D3DBLEND(5,6)=normal for this pass
const FLAG_TERRAIN_BAKE = 0x80; // Bit 7: on death, bake to terrain via fx_queue_add
const FLAG_BAKE_LOW_ALPHA = 0x100; // Bit 8: on death, use alpha 0.35 (vs 0.8)

// Atlas UV table is now in src/data/ParticleAtlas.ts — see ParticleFrame enum.

// ========================================================================
// EffectEntry — mirrors C effect_entry_t
// ========================================================================
interface EffectEntry {
    active: boolean;
    x: number;
    y: number;
    velX: number;
    velY: number;
    rotation: number;
    rotationStep: number;
    halfWidth: number;
    halfHeight: number;
    scale: number;
    scaleStep: number;
    age: number;
    lifetime: number;
    colorR: number; // 0.0–1.0
    colorG: number;
    colorB: number;
    colorA: number;
    initialAlpha: number; // stored for flag 0x10 fade
    flags: number;
    effectId: number;
    // UV coords (set on spawn from PARTICLE_ATLAS)
    u0: number;
    v0: number;
    u1: number;
    v1: number;
}

// ========================================================================
// EffectTemplate — template vars set before spawn
// ========================================================================
interface EffectTemplate {
    velX: number;
    velY: number;
    rotation: number;
    rotationStep: number;
    halfWidth: number;
    halfHeight: number;
    scale: number;
    scaleStep: number;
    age: number;
    lifetime: number;
    colorR: number;
    colorG: number;
    colorB: number;
    colorA: number;
    flags: number;
}

// ========================================================================
// Terrain bake callback type
// ========================================================================
export type TerrainBakeCallback = (
    effectId: number,
    x: number,
    y: number,
    width: number,
    height: number,
    rotation: number,
    r: number,
    g: number,
    b: number,
    a: number,
) => void;

// UV computation is now in src/data/ParticleAtlas.ts — getParticleUV()

/** Mirrors C crt_rand() & mask patterns for small random ranges */
function crtRand(): number {
    return Math.floor(Math.random() * 0x7fffffff);
}

// ========================================================================
// Hex float constants used in the C code (IEEE 754 single precision)
// ========================================================================
// 0x3f800000 = 1.0
// 0x3f000000 = 0.5
// 0x3e99999a = 0.3
// 0x3ecccccd = 0.4
// 0x3f19999a = 0.6
// 0x3f666666 = 0.9
// 0x3dcccccd = 0.1
// 0x42000000 = 32.0
// 0x42100000 = 36.0
// 0x40800000 = 4.0
// 0x3f8ccccd = 1.1
// 0x425c0000 = 55.0

const POOL_SIZE = 384; // generous pool size; C code uses linked list

// ========================================================================
// EffectSystem class
// ========================================================================
export class EffectSystem {
    private pool: EffectEntry[] = [];
    private template: EffectTemplate = this.createDefaultTemplate();
    private particlesTextureHandle: TextureHandle = -1;
    private terrainBakeCallback: TerrainBakeCallback | null = null;

    constructor() {
        for (let i = 0; i < POOL_SIZE; i++) {
            this.pool.push(this.createEntry());
        }
    }

    // ────────────────────────────────────────────────────────────────────
    // Setup
    // ────────────────────────────────────────────────────────────────────

    setParticlesTexture(handle: TextureHandle): void {
        this.particlesTextureHandle = handle;
    }

    setTerrainBakeCallback(cb: TerrainBakeCallback): void {
        this.terrainBakeCallback = cb;
    }

    // ────────────────────────────────────────────────────────────────────
    // Pool management
    // ────────────────────────────────────────────────────────────────────

    private createEntry(): EffectEntry {
        return {
            active: false,
            x: 0,
            y: 0,
            velX: 0,
            velY: 0,
            rotation: 0,
            rotationStep: 0,
            halfWidth: 0,
            halfHeight: 0,
            scale: 1.0,
            scaleStep: 0,
            age: 0,
            lifetime: 0.5,
            colorR: 1,
            colorG: 1,
            colorB: 1,
            colorA: 1,
            initialAlpha: 1,
            flags: 0,
            effectId: 0,
            u0: 0,
            v0: 0,
            u1: 0.25,
            v1: 0.25,
        };
    }

    private createDefaultTemplate(): EffectTemplate {
        // C: effect_defaults_reset @ 0042df10
        return {
            velX: 0,
            velY: 0,
            rotation: 0,
            rotationStep: 1.0, // 0x3f800000
            halfWidth: 32.0, // 0x42000000
            halfHeight: 32.0, // 0x42000000
            scale: 1.0, // 0x3f800000
            scaleStep: 1.0, // 0x3f800000
            age: 0,
            lifetime: 0.5, // 0x3f000000
            colorR: 1.0, // 0x3f800000
            colorG: 1.0,
            colorB: 1.0,
            colorA: 1.0,
            flags: FLAG_ACTIVE,
        };
    }

    /**
     * Allocate an effect entry from the pool, copy template, compute UVs.
     * C: effect_spawn @ 0042e120
     */
    private spawn(effectId: number, x: number, y: number): EffectEntry | null {
        // Find free slot
        let entry: EffectEntry | null = null;
        for (let i = 0; i < POOL_SIZE; i++) {
            if (!this.pool[i].active) {
                entry = this.pool[i];
                break;
            }
        }
        // If no free slot, pick random (overwrite)
        if (!entry) {
            entry = this.pool[crtRand() % POOL_SIZE];
        }

        const t = this.template;

        // Copy template fields
        entry.active = true;
        entry.x = x;
        entry.y = y;
        entry.velX = t.velX;
        entry.velY = t.velY;
        entry.rotation = t.rotation;
        entry.rotationStep = t.rotationStep;
        entry.halfWidth = t.halfWidth;
        entry.halfHeight = t.halfHeight;
        entry.scale = t.scale;
        entry.scaleStep = t.scaleStep;
        entry.age = t.age;
        entry.lifetime = t.lifetime;
        entry.colorR = t.colorR;
        entry.colorG = t.colorG;
        entry.colorB = t.colorB;
        entry.colorA = t.colorA;
        entry.initialAlpha = t.colorA;
        entry.flags = t.flags;
        entry.effectId = effectId;

        // Compute UVs from PARTICLE_ATLAS
        const atlasEntry = PARTICLE_ATLAS[effectId as ParticleFrame];
        if (atlasEntry) {
            const uv = getParticleUV(effectId as ParticleFrame);
            entry.u0 = uv.u0;
            entry.v0 = uv.v0;
            entry.u1 = uv.u1;
            entry.v1 = uv.v1;
        }

        return entry;
    }

    // ────────────────────────────────────────────────────────────────────
    // Update — C: effects_update @ 0042e710
    // ────────────────────────────────────────────────────────────────────

    update(dt: number): void {
        for (const e of this.pool) {
            if (!e.active) continue;

            e.age += dt;

            if (e.age >= e.lifetime) {
                // On death: terrain bake if flag 0x80
                if (e.flags & FLAG_TERRAIN_BAKE && this.terrainBakeCallback) {
                    const alpha = e.flags & FLAG_BAKE_LOW_ALPHA ? 0.35 : 0.8;
                    this.terrainBakeCallback(
                        e.effectId,
                        e.x,
                        e.y,
                        e.halfWidth * 2,
                        e.halfHeight * 2,
                        e.rotation,
                        e.colorR,
                        e.colorG,
                        e.colorB,
                        alpha,
                    );
                }
                e.active = false;
                continue;
            }

            // Skip rendering/updating effects with negative age
            // (C: if (0.0 <= fVar2) — age must be >= 0 for updates)
            if (e.age < 0) continue;

            // Position update (always when active + age >= 0)
            e.x += e.velX * dt;
            e.y += e.velY * dt;

            // Rotation (flag 0x04)
            if (e.flags & FLAG_ROTATION) {
                e.rotation += e.rotationStep * dt;
            }

            // Scale (flag 0x08)
            if (e.flags & FLAG_SCALE) {
                e.scale += e.scaleStep * dt;
            }

            // Alpha fade (flag 0x10)
            // C: pfVar4[6] = 1.0 - fVar2 / pfVar4[1];
            // Directly overwrites colorA with (1 - age/lifetime), ignoring initial value.
            if (e.flags & FLAG_ALPHA_FADE) {
                e.colorA = 1.0 - e.age / e.lifetime;
            }
        }
    }

    // ────────────────────────────────────────────────────────────────────
    // Render — C: effects_render @ 0042e820
    // Two-pass: additive (flag 0x40) then normal blend
    // ────────────────────────────────────────────────────────────────────

    render(grim: GrimInterface, spriteCtx?: { hasParticlesSprite: boolean; particlesHandle: TextureHandle }): void {
        // Need a texture to render
        let texHandle = this.particlesTextureHandle;
        if (spriteCtx && spriteCtx.hasParticlesSprite) {
            texHandle = spriteCtx.particlesHandle;
        }
        if (texHandle < 0) return;

        grim.bindTexture(texHandle);

        // Pass 1: Normal blend for FLAG_ADDITIVE (0x40) effects
        // C: grim_set_config_var(0x13, 5), (0x14, 6) = D3DBLEND SRC_ALPHA/INVSRCALPHA = normal
        grim.setBlendMode('normal');
        for (const e of this.pool) {
            if (!e.active || e.age < 0) continue;
            if (!(e.flags & FLAG_ADDITIVE)) continue;
            this.renderEffect(grim, e);
        }

        // Pass 2: Additive blend for non-FLAG_ADDITIVE effects
        // C: grim_set_config_var(0x14, 2) = D3DBLEND SRC_ALPHA/ONE = additive
        grim.setBlendMode('add');
        for (const e of this.pool) {
            if (!e.active || e.age < 0) continue;
            if (e.flags & FLAG_ADDITIVE) continue;
            this.renderEffect(grim, e);
        }

        // Restore state
        grim.setBlendMode('normal');
        grim.setRotation(0);
    }

    private renderEffect(grim: GrimInterface, e: EffectEntry): void {
        const alpha = Math.floor(e.colorA * 255);
        if (alpha <= 0) return;

        grim.setColor(Math.floor(e.colorR * 255), Math.floor(e.colorG * 255), Math.floor(e.colorB * 255), alpha);

        // Use setAtlasFrame instead of setUV — direct UV setting causes errors
        const atlasEntry = PARTICLE_ATLAS[e.effectId as ParticleFrame];
        if (atlasEntry) {
            grim.setAtlasFrame(atlasEntry.gridSize, atlasEntry.frame);
        }

        grim.setRotation(e.rotation);

        const hw = e.halfWidth * e.scale;
        const hh = e.halfHeight * e.scale;
        grim.drawQuad(e.x - hw, e.y - hh, hw * 2, hh * 2);
    }

    // ────────────────────────────────────────────────────────────────────
    // Clear all effects
    // ────────────────────────────────────────────────────────────────────
    clear(): void {
        for (const e of this.pool) {
            e.active = false;
        }
    }

    getActiveCount(): number {
        let count = 0;
        for (const e of this.pool) {
            if (e.active) count++;
        }
        return count;
    }

    // ════════════════════════════════════════════════════════════════════
    // SPAWN FUNCTIONS — each sets template vars then calls spawn()
    // All hex float constants decoded from IEEE 754 single-precision.
    // ════════════════════════════════════════════════════════════════════

    /**
     * Spawn a freeze shard flying outward at the given angle.
     * C: effect_spawn_freeze_shard @ 0042ec80 (L1036-1071)
     */
    spawnFreezeShard(x: number, y: number, angle: number): void {
        const t = this.template;

        t.colorR = 1.0; // 0x3f800000
        t.flags = 0x1cd; // active + rotation + scale + alpha + terrain bake
        t.colorG = 1.0;
        t.colorB = 1.0;
        t.colorA = 0.5; // 0x3f000000

        const r1 = crtRand();
        t.age = 0;
        t.lifetime = (r1 & 0xf) * 0.01 + 0.2;

        const angleFlipped = angle + Math.PI; // C: angle + 3.1415927
        const r2 = crtRand();
        t.rotation = (r2 % 100) * 0.01 + angleFlipped;

        const r3 = crtRand();
        t.halfWidth = (r3 % 5) + 7;
        t.halfHeight = t.halfWidth;

        t.velX = Math.cos(angleFlipped) * 114.0;
        t.velY = Math.sin(angleFlipped) * 114.0;

        const r4 = crtRand();
        t.rotationStep = ((r4 % 0x14) * 0.1 - 1.0) * 4.0;

        const r5 = crtRand();
        // C: -(uVar2 & 0xf) * 0.1 — negative scale step (shard shrinks)
        t.scaleStep = -(r5 & 0xf) * 0.1;

        t.scale = 1.0;

        const r6 = crtRand();
        // Random freeze shard: FREEZE_SHARD_A(8), B(9), or C(10)
        this.spawn((r6 % 3) + ParticleFrame.FREEZE_SHARD_A, x, y);
    }

    /**
     * Four-way shatter burst (4× center crystal id=0xe) plus 4 random freeze shards.
     * C: effect_spawn_freeze_shatter @ 0042ee00 (L1080-1119)
     */
    spawnFreezeShatter(x: number, y: number, angle: number): void {
        const t = this.template;

        // Center burst crystals
        t.colorR = 1.0;
        t.flags = 0x5d; // active + rotation + alpha + additive
        t.colorG = 1.0;
        t.colorB = 1.0;
        t.colorA = 0.5; // 0x3f000000
        t.age = 0;
        t.lifetime = 1.1; // 0x3f8ccccd
        t.scaleStep = 0;
        t.scale = 1.0;

        for (let i = 0; i < 4; i++) {
            const a = i * (Math.PI / 2) + angle; // C: i * 1.5707964 + angle
            t.rotation = a;
            t.velX = Math.cos(a) * 42.0;
            t.velY = Math.sin(a) * 42.0;

            const r1 = crtRand();
            t.halfWidth = (r1 % 10) + 0x12; // 18–27
            t.halfHeight = t.halfWidth;

            const r2 = crtRand();
            t.rotationStep = ((r2 % 0x14) * 0.1 - 1.0) * 1.9;

            this.spawn(ParticleFrame.FREEZE_OVERLAY, x, y);
        }

        // 4 random freeze shards
        for (let i = 0; i < 4; i++) {
            const r = crtRand();
            this.spawnFreezeShard(x, y, (r % 0x264) * 0.01);
        }
    }

    /**
     * Expanding blue-purple flash at freeze bonus pickup position.
     * C: bonuses.c lines 117-134 (inline effect_spawn(1, pos))
     *
     * This is NOT a shockwave — it's a single expanding circle with
     * colors (0.3, 0.5, 0.8, 1.0) at normal blend (flags 0x19).
     * Scale step 50.0 makes it grow fast from 32px to ~430px in 0.25s.
     */
    spawnFreezeFlash(x: number, y: number): void {
        const t = this.template;

        t.colorR = 0.3;    // 0x3e99999a
        t.flags = 0x19;    // active + scale + alpha fade (normal blend)
        t.colorG = 0.5;    // 0x3f000000
        t.colorB = 0.8;    // 0x3f4ccccd
        t.colorA = 1.0;    // 0x3f800000
        t.lifetime = 0.25; // 0x3e800000
        t.age = 0;
        t.halfWidth = 32.0;  // 0x42000000
        t.halfHeight = 32.0;
        t.rotation = 0;
        t.velX = 0;
        t.velY = 0;
        t.scaleStep = 50.0;  // 0x42480000
        t.scale = 1.0;

        this.spawn(ParticleFrame.EXPANSION_FLASH, x, y);
    }

    /**
     * Generic radial burst of glow particles.
     * C: effect_spawn_burst @ 0042ef60 (L1128-1158)
     */
    spawnBurst(x: number, y: number, count: number): void {
        const t = this.template;

        t.colorR = 0.4; // 0x3ecccccd
        t.flags = 0x1d; // active + rotation + scale + alpha + additive
        t.colorG = 0.5; // 0x3f000000
        t.colorB = 1.0; // 0x3f800000
        t.colorA = 0.5; // 0x3f000000
        t.age = 0;
        t.lifetime = 0.5; // 0x3f000000
        t.halfWidth = 32.0; // 0x42000000
        t.halfHeight = 32.0;
        t.scale = 1.0;

        for (let i = 0; i < count; i++) {
            const r1 = crtRand();
            t.rotation = (r1 & 0x7f) * 0.049087387; // random angle

            const r2 = crtRand();
            t.velX = (r2 & 0x7f) - 0x40; // -64 to +63

            const r3 = crtRand();
            t.velY = (r3 & 0x7f) - 0x40;

            const r4 = crtRand();
            t.scaleStep = (r4 % 100) * 0.01 + 0.1; // 0.1–1.09

            this.spawn(ParticleFrame.GLOW_SOFT, x, y);
        }
    }

    /**
     * Healing implosion — center shrinking flash + 4 outward sparks.
     * C: effect_spawn_shrink_fx @ 0042f080 (L1167-1215)
     */
    spawnShrinkFx(x: number, y: number): void {
        const t = this.template;

        // Center shrink flash (ID 1 = expansion flash, but scaleStep < 0 = shrinks)
        t.colorR = 0.3; // 0x3e99999a
        t.flags = 0x19; // active + scale + alpha + additive
        t.colorG = 0.6; // 0x3f19999a
        t.colorB = 0.9; // 0x3f666666
        t.colorA = 1.0; // 0x3f800000
        t.age = 0;
        t.lifetime = 0.3; // 0x3e99999a
        t.halfWidth = 36.0; // 0x42100000
        t.halfHeight = 36.0;
        t.rotation = 0;
        t.velX = 0;
        t.velY = 0;
        t.scaleStep = -4.0;
        t.scale = 1.0;
        this.spawn(ParticleFrame.EXPANSION_FLASH, x, y);

        // Outward sparks (4 particles at high detail)
        t.colorB = 1.0; // 0x3f800000
        t.colorR = 0.4; // 0x3ecccccd
        t.flags = 0x1d; // active + rotation + scale + alpha + additive
        t.colorG = 0.5; // 0x3f000000
        t.colorA = 0.5; // 0x3f000000
        t.age = 0;
        t.lifetime = 0.3; // 0x3e99999a
        t.halfWidth = 32.0; // 0x42000000
        t.halfHeight = 32.0;
        t.scale = 1.0;

        const sparkCount = 4; // High detail (C: detail_preset >= 3)
        for (let i = 0; i < sparkCount; i++) {
            const r1 = crtRand();
            t.rotation = (r1 & 0x7f) * 0.049087387;

            const r2 = crtRand();
            t.velX = ((r2 & 0x7f) - 0x40) * 1.4;

            const r3 = crtRand();
            t.velY = ((r3 & 0x7f) - 0x40) * 1.4;

            const r4 = crtRand();
            t.scaleStep = (r4 % 100) * 0.01 + 0.1;

            this.spawn(ParticleFrame.GLOW_SOFT, x, y);
        }
    }

    /**
     * Electric arc glow at impact point.
     * C: fx_spawn_electric_arc @ 0042f270 (L1224-1244)
     * @param scale - radius multiplier (C arg2)
     * @param duration - lifetime base (C arg3)
     */
    spawnElectricArc(x: number, y: number, scale: number = 1.0, duration: number = 0.2): void {
        const t = this.template;

        t.lifetime = duration * 0.8;
        t.colorG = 0.6; // 0x3f19999a
        t.scaleStep = scale * 45.0;
        t.colorR = 0.6; // 0x3f19999a
        t.flags = 0x19; // active + scale + alpha + additive
        t.colorB = 0.9; // 0x3f666666
        t.colorA = 1.0; // 0x3f800000
        t.age = 0;
        t.halfWidth = 4.0; // 0x40800000
        t.halfHeight = 4.0;
        t.rotation = 0;
        t.velX = 0;
        t.velY = 0;
        t.scale = 1.0;

        this.spawn(ParticleFrame.EXPANSION_FLASH, x, y);
    }

    /**
     * Plasma impact explosion glow.
     * C: fx_spawn_plasma_explosion @ 0042f330 (L1253-1273)
     * @param scale - radius multiplier (C arg2)
     * @param lifetime - effect lifetime (C arg3, passed as int but used as float)
     */
    spawnPlasmaExplosion(x: number, y: number, scale: number = 1.0, lifetime: number = 0.3): void {
        const t = this.template;

        t.scaleStep = scale * 45.0;
        t.colorB = 0.3; // 0x3e99999a
        t.colorR = 0.9; // 0x3f666666
        t.colorG = 0.6; // 0x3f19999a
        t.flags = 0x19; // active + scale + alpha + additive
        t.colorA = 1.0; // 0x3f800000
        t.age = 0.1; // 0x3dcccccd — starts with slight age offset
        t.lifetime = lifetime;
        t.halfWidth = 4.0; // 0x40800000
        t.halfHeight = 4.0;
        t.rotation = 0;
        t.velX = 0;
        t.velY = 0;
        t.scale = 1.0;

        this.spawn(ParticleFrame.EXPANSION_FLASH, x, y);
    }

    /**
     * Radial fire particle ring.
     * C: fx_spawn_fire_particles @ 0042f3f0 (L1282-1332)
     * @param radius - spread radius (C arg2)
     * @param count - number of particles (C arg3)
     */
    spawnFireParticles(x: number, y: number, radius: number, count: number): void {
        const t = this.template;

        t.colorR = 1.0; // 0x3f800000
        t.flags = 0x19; // active + scale + alpha + additive
        t.colorG = 0.9; // 0x3f666666
        t.colorB = 0.1; // 0x3dcccccd
        t.colorA = 1.0; // 0x3f800000
        t.halfWidth = 4.0; // 0x40800000
        t.halfHeight = 4.0;
        t.rotation = 0;
        t.velX = 0;
        t.velY = 0;
        t.scaleStep = 55.0; // 0x425c0000
        t.scale = 1.0;

        for (let i = 0; i < count; i++) {
            const r1 = crtRand();
            const angle = (r1 & 0x1ff) * (1.0 / 512.0) * (Math.PI * 2); // (r1 & 0x1ff) * 0.001953125 * 6.2831855

            const r2 = crtRand();
            const dist = r2 % Math.floor(radius);

            const px = Math.cos(angle) * dist + x;
            const py = Math.sin(angle) * dist + y;

            const r3 = crtRand();
            // C: -(r3 & 0xff) * 0.0012 — negative age (delayed start)
            t.age = -(r3 & 0xff) * 0.0012;
            t.lifetime = 0.1 - t.age; // total visible time is always ~0.1s

            this.spawn(ParticleFrame.GLOW_SOFT, px, py);
        }
    }

    /**
     * Expanding shockwave ring of particles.
     * C: fx_spawn_shockwave @ 0042f540 (L1341-1385)
     * @param scale - overall scale multiplier
     */
    spawnShockwave(x: number, y: number, scale: number): void {
        const t = this.template;

        const s = scale * 0.8; // C: fVar1 = arg2 * 0.8

        t.colorR = 0.4; // 0x3ecccccd
        t.lifetime = s * 0.7; // C: fVar1 * 0.7
        t.colorA = 0.5; // 0x3f000000
        t.flags = 0x1d; // active + rotation + scale + alpha + additive
        t.colorG = 0.5; // 0x3f000000
        t.colorB = 1.0; // 0x3f800000
        t.age = 0;
        t.scale = 1.0;

        // C: clamp lifetime to 1.1
        if (t.lifetime > 1.1) {
            t.lifetime = 1.1;
        }

        t.halfWidth = s * 32.0; // C: fVar1 * 32.0
        t.halfHeight = t.halfWidth;

        // C: count = (int)ftol(???) — the count is derived from scale-based computation
        // In the C code, count seems to be a fixed loop count. Looking at the loop,
        // it iterates pvVar5 times where pvVar5 starts at pvVar2 (result of __ftol).
        // The ftol result is from the halfWidth computation context.
        // Based on analysis: count is based on shockwave scale, typically around 4-12 particles
        const particleCount = Math.max(4, Math.floor(s * 10));

        for (let i = 0; i < particleCount; i++) {
            const r1 = crtRand();
            t.rotation = (r1 & 0x7f) * 0.049087387;

            const r2 = crtRand();
            t.velX = ((r2 & 0x7f) - 0x40) * s * 1.4;

            const r3 = crtRand();
            t.velY = ((r3 & 0x7f) - 0x40) * s * 1.4;

            const r4 = crtRand();
            t.scaleStep = ((r4 % 100) * 0.01 + 0.1) * s;

            this.spawn(ParticleFrame.GLOW_SOFT, x, y);
        }
    }

    /**
     * Full multi-layer explosion burst.
     * C: effect_spawn_explosion_burst @ 0042f6c0 (L1394-1483)
     *
     * Layers:
     * 1. Expansion ring (EXPANSION_RING — Large Circle, flags 0x19, scale animation)
     * 2. Smoke rings (ID 0x11, flags 0x5d) — only at high detail
     * 3. Bright glow (ID 0, flags 0x19)
     * 4. Debris sparkles (ID 0xc, flags 0x1d)
     */
    spawnExplosionBurst(x: number, y: number, scale: number): void {
        const t = this.template;

        // ── Layer 1: Expansion ring (Large Circle) ──
        t.scaleStep = scale * 25.0;
        t.colorR = 0.6; // 0x3f19999a
        t.flags = 0x19; // active + scale + alpha + additive
        t.colorG = 0.6; // 0x3f19999a
        t.colorB = 0.6; // 0x3f19999a
        t.colorA = 1.0; // 0x3f800000
        t.lifetime = 0.35;
        t.age = -0.1; // delayed start
        t.halfWidth = 32.0; // 0x42000000
        t.halfHeight = 32.0;
        t.rotation = 0;
        t.velX = 0;
        t.velY = 0;
        t.scale = 1.0;
        this.spawn(ParticleFrame.EXPANSION_RING, x, y);

        // ── Layer 2: Smoke rings (high detail only — we always use high) ──
        t.colorB = 0.1; // 0x3dcccccd
        t.colorR = 0.1; // 0x3dcccccd
        t.flags = 0x5d; // active + rotation + alpha + additive
        t.colorG = 0.1; // 0x3dcccccd
        t.colorA = 1.0; // 0x3f800000
        t.rotation = 0;
        t.velX = 0;
        t.velY = 0;
        t.scale = 1.0;

        for (let i = 0; i < 2; i++) {
            t.halfWidth = 32.0;
            t.halfHeight = 32.0;
            t.age = i * 0.2 - 0.5; // C: (float)(int)pos * 0.2 - 0.5
            t.lifetime = i * 0.2 + 0.6; // C: (float)(int)pos * 0.2 + 0.6

            const r1 = crtRand();
            t.rotationStep = 1.4;
            t.rotation = (r1 % 0x266) * 0.02;
            t.scaleStep = scale * 5.0;

            this.spawn(ParticleFrame.SMOKE_RING, x, y);
        }

        // ── Layer 3: Bright expansion glow ──
        t.scaleStep = scale * 45.0;
        t.colorR = 1.0; // 0x3f800000
        t.flags = 0x19;
        t.colorG = 1.0;
        t.colorB = 1.0;
        t.colorA = 1.0;
        t.age = 0;
        t.lifetime = 0.3;
        t.halfWidth = 32.0;
        t.halfHeight = 32.0;
        t.rotation = 0;
        t.velX = 0;
        t.velY = 0;
        t.scale = 1.0;
        // C: effect_spawn(0, pos) = effect_id 0 = {0x40, 0} = 4×4 frame 0 (GLOW_SOFT).
        // However, 4×4 frame 0 contains mixed sub-sprites (bubble+blood+ice) that
        // become clearly visible when scaled up in WebGL/additive blend. Use GLOW_ORB
        // (4×4 frame 3, clean golden glow) for identical visual intent without artifacts.
        this.spawn(ParticleFrame.GLOW_ORB, x, y);

        // ── Layer 4: Debris sparkles ──
        t.colorB = 1.0;
        t.colorR = 1.0;
        t.flags = 0x1d; // active + rotation + scale + alpha + additive
        t.colorG = 1.0;
        t.colorA = 1.0;
        t.lifetime = 0.7;
        t.age = 0;
        t.halfWidth = 32.0;
        t.halfHeight = 32.0;
        t.scale = 1.0;

        // C: detail >= 2 → 3 or 4 particles; detail < 2 → 1
        const debrisCount = 4; // high detail: (3 < detail_preset) + 3 = 4

        for (let i = 0; i < debrisCount; i++) {
            const r1 = crtRand();
            t.rotation = (r1 % 0x13a) * 0.02;

            const r2 = crtRand();
            t.velX = (r2 & 0x3f) * 2 - 0x40;

            const r3 = crtRand();
            t.velY = (r3 & 0x3f) * 2 - 0x40;

            const r4 = crtRand();
            t.scaleStep = ((r4 - 3) & 7) * scale; // C: (iVar2 - 3U & 7) * scale

            const r5 = crtRand();
            t.rotationStep = (r5 + 3) & 7; // C: (iVar2 + 3U & 7)

            this.spawn(ParticleFrame.EXPLOSION_SPARKLE, x, y);
        }
    }

    /**
     * Rocket impact sprite debris circle — spawned for ALL rocket types on hit.
     * C: projectiles.c L895-907 — 10 fx_spawn_sprite calls at 36° intervals.
     *
     * Each sprite is 14×14 at α=0.37, with random radial velocity (0-80 px/s).
     * The 10 sprites are evenly spaced at 0.62831855 rad (36°) intervals.
     */
    spawnRocketImpactDebris(x: number, y: number): void {
        const t = this.template;

        t.colorR = 1.0;
        t.colorG = 1.0;
        t.colorB = 1.0;
        t.colorA = 0.37; // C: sprite_effect_pool[idx].color_a = 0.37
        t.flags = 0x19; // active + scale + alpha (additive blend)
        t.halfWidth = 7.0; // 14×14 → half = 7
        t.halfHeight = 7.0;
        t.rotation = 0;
        t.scale = 1.0;
        t.scaleStep = 3.0; // C: sprite_effect grows at dt*3.0 (L925)
        t.age = 0;
        t.lifetime = 0.37; // matches alpha — visible until faded

        for (let i = 0; i < 10; i++) {
            // C: angle = i * 0.62831855 (36° per step, 10 steps = full circle)
            const angle = i * 0.62831855;

            // C: velocity = rand(0..800) * 0.1 along angle direction
            const r = crtRand();
            const speed = (r % 800) * 0.1;
            const dirX = Math.cos(angle);
            const dirY = Math.sin(angle);
            t.velX = speed * dirX;
            t.velY = speed * dirY;

            this.spawn(ParticleFrame.GLOW_ORB, x, y);
        }
    }

    /**
     * Expanding blue halo ring for Reflex Boost bonus pickup.
     * C: bonuses.c lines 56-77 — effect_spawn(1, &pos)
     *
     * Uses the Large Circle ring sprite (EXPANSION_RING) which scales up
     * rapidly via scaleStep=50 from 32px to ~430px in 0.25s, with alpha
     * fading out (flags 0x19 = active + scale + alpha_fade).
     *
     * Colors: R=0x3f19999a (0.6), G=0x3f19999a (0.6), B=0x3f800000 (1.0),
     *         A=0x3f800000 (1.0) — blue-white tint.
     */
    spawnReflexHalo(x: number, y: number): void {
        const t = this.template;

        t.colorR = 0.6;    // 0x3f19999a
        t.flags = 0x19;    // active + scale + alpha fade (normal blend)
        t.colorG = 0.6;    // 0x3f19999a
        t.colorB = 1.0;    // 0x3f800000
        t.colorA = 1.0;    // 0x3f800000
        t.lifetime = 0.25; // 0x3e800000
        t.age = 0;
        t.halfWidth = 32.0;  // 0x42000000
        t.halfHeight = 32.0;
        t.rotation = 0;
        t.velX = 0;
        t.velY = 0;
        t.scaleStep = 50.0;  // 0x42480000
        t.scale = 1.0;

        this.spawn(ParticleFrame.EXPANSION_RING, x, y);
    }

    /**
     * Bonus pickup celebration particles.
     * C: bonuses.c lines 260-293 — 12 blue-white particles on pickup (non-NUKE).
     */
    spawnBonusPickupParticles(x: number, y: number): void {
        this.spawnBonusParticles(x, y, 12);
    }

    /**
     * Bonus spawn glow particles.
     * C: bonuses.c lines 903-932 — 16 blue-white particles when bonus drops.
     */
    spawnBonusSpawnParticles(x: number, y: number): void {
        this.spawnBonusParticles(x, y, 16);
    }

    /**
     * Shared implementation for bonus pickup/spawn particles.
     * C: effect_template_color = {0.4, 0.5, 1.0, 0.5}, flags 0x1d,
     *    lifetime 0.4, halfWidth 32, scaleStep 0.1,
     *    velocity (rand & 0x7f) - 0x40 for both axes.
     */
    private spawnBonusParticles(x: number, y: number, count: number): void {
        const t = this.template;

        t.colorR = 0.4; // 0x3ecccccd
        t.flags = 0x1d; // active + rotation + scale + alpha + additive
        t.colorG = 0.5; // 0x3f000000
        t.colorB = 1.0; // 0x3f800000
        t.colorA = 0.5; // 0x3f000000
        t.age = 0;
        t.lifetime = 0.4;
        t.halfWidth = 32.0; // 0x42000000
        t.halfHeight = 32.0;
        t.scale = 1.0;
        t.scaleStep = 0.1; // fixed 0.1 (C: effect_template_scale_step = 0.1)

        for (let i = 0; i < count; i++) {
            const r1 = crtRand();
            t.rotation = (r1 & 0x7f) * 0.049087387; // random angle

            t.velX = (Math.floor(Math.random() * 128) - 64); // (rand & 0x7f) - 0x40
            t.velY = (Math.floor(Math.random() * 128) - 64);

            this.spawn(ParticleFrame.GLOW_SOFT, x, y);
        }
    }

    /**
     * Spawn a shell casing ejected from the player's gun.
     * C: player.c lines 1206-1241 (inline before effect_spawn(0x12, &local_10))
     *
     * Only spawned for weapons with flag & 1 (AUTOMATIC / ballistic weapons).
     * The casing is a tiny brass particle that flies out at the aim angle
     * with random velocity, tumbles with random rotation, then bakes
     * permanently into the terrain when its short lifetime expires.
     *
     * C template values:
     *   flags         = 0x1c5 (active + rotation + additive + terrain_bake + bake_low_alpha)
     *   colorRGBA     = (1.0, 1.0, 1.0, 0.6)   — 0x3f19999a for alpha
     *   lifetime      = 0x3e19999a = 0.15
     *   halfWidth     = 0x40000000 = 2.0
     *   halfHeight    = 0x40000000 = 2.0
     *   velocity      = cos/sin(aimAngle + rand) * (1.0 + rand*0.023) * 100
     *   rotation      = rand(-32..31) * 0.1
     *   rotationStep  = ((rand%20) * 0.1 - 1.0) * 14.0
     *   scaleStep     = 0
     *
     * @param x - Spawn position X (gun barrel tip)
     * @param y - Spawn position Y (gun barrel tip)
     * @param aimAngle - Player aim heading (radians)
     */
    spawnShellCasing(x: number, y: number, aimAngle: number): void {
        const t = this.template;

        // C: effect_template_color = {1.0, 1.0, 1.0, 0.6}
        t.colorR = 1.0; // 0x3f800000
        t.colorG = 1.0; // 0x3f800000
        t.colorB = 1.0; // 0x3f800000
        t.colorA = 0.6; // 0x3f19999a

        // C: flags = 0x1c5  (active|rotation|additive|terrain_bake|bake_low_alpha)
        t.flags = 0x01 | 0x04 | 0x40 | 0x80 | 0x100; // 0x1c5

        // C: lifetime = 0x3e19999a = 0.15
        t.lifetime = 0.15;
        t.age = 0;

        // C: velocity direction = aimAngle + (rand & 0x3f) * 0.01
        const r1 = crtRand();
        const casingAngle = aimAngle + (r1 & 0x3f) * 0.01;

        // C: velocity magnitude = (1.0 + (rand & 0x3f) * 0.022727273)
        const r2 = crtRand();
        const speedScale = 1.0 + (r2 & 0x3f) * 0.022727273;

        t.velX = Math.cos(casingAngle) * speedScale * 100.0;
        t.velY = Math.sin(casingAngle) * speedScale * 100.0;

        // C: halfWidth = halfHeight = 0x40000000 = 2.0
        t.halfWidth = 2.0;
        t.halfHeight = 2.0;

        // C: rotation = (rand & 0x3f - 0x20) * 0.1 → random in [-3.2, 3.1]
        const r3 = crtRand();
        t.rotation = ((r3 & 0x3f) - 0x20) * 0.1;

        // C: rotation_step = ((rand % 20) * 0.1 - 1.0) * 14.0
        const r4 = crtRand();
        t.rotationStep = ((r4 % 0x14) * 0.1 - 1.0) * 14.0;

        // C: scale_step = 0 (casings don't grow/shrink)
        t.scaleStep = 0;
        t.scale = 1.0;

        this.spawn(ParticleFrame.SHELL_CASING, x, y);
    }
}
