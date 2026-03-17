/**
 * ParticleSystem - Manages particle pool and spawning
 *
 * Accurate port of particle system from crimsonland.exe_decompiled.c
 * C code reference: lines 18560-18650
 */

import { Particle } from '../../entities/Particle';
import type { GrimInterface, TextureHandle } from '../../engine/GrimInterface';
import { ParticleFrame, getParticleAtlasFrame } from '../../data/ParticleAtlas';

/**
 * Minimal sprite context needed for texture-based particle rendering.
 * Duck-typed so SpriteRenderer (and mocks) satisfy it.
 */
export interface ParticleSpriteContext {
    readonly hasParticlesSprite: boolean;
    readonly particlesHandle: TextureHandle;
}

/**
 * Particle system
 * Manages a pool of particles for visual effects
 */
export class ParticleSystem {
    private particles: Particle[] = [];
    private readonly maxParticles: number = 128; // Pool size from C code

    constructor() {
        // Initialize particle pool (C: particle_pool)
        for (let i = 0; i < this.maxParticles; i++) {
            this.particles.push(new Particle());
        }
    }

    /**
     * Spawn a fast particle
     * C code reference: fx_spawn_particle @ lines 18564-18603
     *
     * @param x X position
     * @param y Y position
     * @param angle Angle in radians
     * @param intensity Brightness/alpha (0-1)
     * @returns Index of spawned particle, or -1 if pool full
     */
    spawnFastParticle(x: number, y: number, angle: number, intensity: number = 1.0): number {
        // Find free particle slot (C lines 18572-18584)
        let index = -1;
        for (let i = 0; i < this.maxParticles; i++) {
            if (!this.particles[i].active) {
                index = i;
                break;
            }
        }

        // If no free slot, pick random one (C lines 18579-18583)
        if (index === -1) {
            index = Math.floor(Math.random() * 128) & 0x7f;
        }

        const particle = this.particles[index];

        // Initialize particle (C lines 18585-18602)
        particle.active = true;
        particle.x = x;
        particle.y = y;

        // Velocity: cos/sin(angle) * 90 (C lines 18589-18591)
        particle.vx = Math.cos(angle) * 90.0;
        particle.vy = Math.sin(angle) * 90.0;

        particle.intensity = intensity;
        particle.scaleX = 1.0;
        particle.scaleY = 1.0;
        particle.scaleZ = 1.0;
        particle.age = 0.0;
        particle.angle = angle;

        // Random spin: rand % 0x274 * 0.01 (C line 18599)
        particle.spin = Math.floor(Math.random() * 0x274) * 0.01;

        particle.renderFlag = true;
        particle.styleId = 0; // Fast particle style (C line 18601)
        particle.lifetime = 0.5; // Fast particles: ~0.5s

        return index;
    }

    /**
     * Spawn a slow particle
     * C code reference: fx_spawn_particle_slow @ lines 18611-18650
     *
     * @param x X position
     * @param y Y position
     * @param angle Angle in radians
     * @returns Index of spawned particle, or -1 if pool full
     */
    spawnSlowParticle(x: number, y: number, angle: number): number {
        // Find free particle slot (C lines 18619-18631)
        let index = -1;
        for (let i = 0; i < this.maxParticles; i++) {
            if (!this.particles[i].active) {
                index = i;
                break;
            }
        }

        // If no free slot, pick random one (C lines 18626-18630)
        if (index === -1) {
            index = Math.floor(Math.random() * 128) & 0x7f;
        }

        const particle = this.particles[index];

        // Initialize particle (C lines 18632-18649)
        particle.active = true;
        particle.x = x;
        particle.y = y;

        // Velocity: cos/sin(angle) * 30 (C lines 18636-18638)
        particle.vx = Math.cos(angle) * 30.0;
        particle.vy = Math.sin(angle) * 30.0;

        particle.intensity = 1.0;
        particle.scaleX = 1.0;
        particle.scaleY = 1.0;
        particle.scaleZ = 1.0;
        particle.age = 0.0;
        particle.angle = angle;

        // Random spin: rand % 0x274 * 0.01 (C line 18646)
        particle.spin = Math.floor(Math.random() * 0x274) * 0.01;

        particle.renderFlag = true;
        particle.styleId = 8; // Slow particle style (C line 18648)
        particle.targetId = -1; // (C line 18649)
        particle.lifetime = 0.8; // Slow particles: ~0.8s

        return index;
    }

    /**
     * Update all active particles
     * @param dt Delta time in seconds
     */
    update(dt: number): void {
        for (const particle of this.particles) {
            if (particle.active) {
                particle.update(dt);
            }
        }
    }

    /**
     * Render all active particles
     * C code reference: bonuses.c bonus_render (lines 1386-1467)
     *
     * The C code renders fire particles in THREE passes with color transitions:
     *
     * Pass 1 — Glow halo: effect_select_texture(0xd) (Yellow Glow, frame 3),
     *   white at alpha 0.065, size grows with sin((1-intensity)*PI/2)*55+4.
     *   Only draws every-other fast particle (skip odd indices, skip style 8).
     *
     * Pass 2 — Main fire sprite: effect_select_texture(0xc) in C, but we use
     *   FLAME_SPRITE (Explosion, frame 5) for the correct fire visual.
     *   COLOR = (intensity, scaleX, scaleY, 1.0) from particle struct.
     *   Since scaleX/Y = 1.0 - intensity*0.95, this creates:
     *     birth:  (1.0, 0.05, 0.05, 1.0) = bright RED
     *     mid:    (0.5, 0.53, 0.53, 1.0) = warm ORANGE
     *     dying:  (0.0, 0.95, 0.95, 1.0) = faint CYAN (but tiny size)
     *   Size = sin((1-intensity)*PI/2)*24, style 1 at 0.8× scale.
     *
     * Pass 3 — Slow particles (style 8): effect_select_texture(2) (Large Circle TL),
     *   white at intensity alpha, size based on spin oscillation.
     *
     * @param grim Graphics interface
     * @param spriteCtx Optional sprite context for texture-based rendering.
     */
    render(grim: GrimInterface, spriteCtx?: ParticleSpriteContext): void {
        const useSprites = !!(spriteCtx && spriteCtx.hasParticlesSprite);

        if (useSprites) {
            grim.setBlendMode('add');
            grim.bindTexture(spriteCtx!.particlesHandle);

            // === PASS 1: Glow halo (C: bonuses.c lines 1386-1421) ===
            // C: effect_select_texture(0xd) → GLOW_ORB (golden glow orb)
            const glowFrame = getParticleAtlasFrame(ParticleFrame.GLOW_ORB);
            grim.setAtlasFrame(glowFrame.atlasSize, glowFrame.frame);
            grim.setRotation(0);
            grim.setColor(255, 255, 255, Math.floor(0.065 * 255)); // C: white at alpha 0.065

            for (let i = 0; i < this.particles.length; i++) {
                const p = this.particles[i];
                if (!p.active) continue;
                // C: only every-other particle (index & 1 == 0) and not style 8
                if ((i & 1) !== 0) continue;
                if (p.styleId === 8) continue;
                if (p.styleId > 2 && p.styleId !== 8) continue; // Only fire particles get glow

                // C: size = (sin((1 - intensity) * PI/2) + 0.1) * 55 + 4, min 16
                const t = Math.max(0, Math.min(1, 1.0 - p.intensity));
                let glowSize = (Math.sin(t * Math.PI / 2) + 0.1) * 55 + 4;
                if (glowSize < 16) glowSize = 16;

                grim.drawQuad(
                    p.x - glowSize,
                    p.y - glowSize,
                    glowSize * 2,
                    glowSize * 2,
                );
            }

            // === PASS 2: Main fire sprite (C: bonuses.c line 1425) ===
            // C: effect_select_texture(0xc) → FLAME_SPRITE (Explosion, frame 5)
            const fireFrame = getParticleAtlasFrame(ParticleFrame.FLAME_SPRITE);
            grim.setAtlasFrame(fireFrame.atlasSize, fireFrame.frame);

            for (const p of this.particles) {
                if (!p.active) continue;
                if (p.styleId === 8) continue; // Slow particles rendered in pass 3

                if (p.styleId <= 2) {
                    // Fire particles: color from C struct fields after update.
                    // C: grim_set_color(pfVar5[-6], pfVar5[-5], pfVar5[-4], pfVar5[-3])
                    //   pfVar5 = &spin, so offsets relative to pfVar13 = &vel_y (pfVar5 = pfVar13+7):
                    //   pfVar5[-6] = pfVar13[1] = scaleX = renderScale (1 - intensity*0.95)
                    //   pfVar5[-5] = pfVar13[2] = scaleY = renderScale (same)
                    //   pfVar5[-4] = pfVar13[3] = scaleZ = 1.0 (unchanged from spawn)
                    //   pfVar5[-3] = pfVar13[4] = clamped intensity (written at line 1022)
                    //
                    // Result: dim at birth → brighter mid-life → fully transparent at death
                    const renderScale = Math.max(0, Math.min(1, p.scaleX)); // 1 - intensity*0.95
                    const clampedInt = Math.max(0, Math.min(1, p.intensity));
                    const r = Math.floor(renderScale * 255);
                    const g = Math.floor(renderScale * 255);
                    const b = Math.floor(1.0 * 255); // scaleZ = 1.0 constant
                    const a = Math.floor(clampedInt * 255); // alpha = clamped intensity → FADES OUT

                    grim.setColor(r, g, b, a);
                    grim.setRotation(p.spin); // C: grim_set_rotation(*pfVar5) where pfVar5=&spin

                    // C: size = sin((1 - pfVar5[-2]) * PI/2) * 24, style 1 at 0.8×
                    // pfVar5[-2] = pfVar13[5] = intensity (decays from 1.0 to 0.0)
                    const tFire = Math.max(0, Math.min(1, 1.0 - p.intensity));
                    let fireSize = Math.sin(tFire * Math.PI / 2) * 24;
                    if (p.styleId === 1) fireSize *= 0.8; // C: style 1 (Blow Torch) at 0.8×
                    if (fireSize < 2) fireSize = 2;

                    grim.drawQuad(
                        p.x - fireSize,
                        p.y - fireSize,
                        fireSize * 2,
                        fireSize * 2,
                    );
                } else {
                    // Other non-fire, non-slow particles (radioactive etc)
                    // C: effect_select_texture(0x10) → SHADOW_DISC (frame 0 in 4×4 grid)
                    const glowDiscFrame = getParticleAtlasFrame(ParticleFrame.SHADOW_DISC);
                    grim.setAtlasFrame(glowDiscFrame.atlasSize, glowDiscFrame.frame);
                    if (p.tintR >= 0) {
                        const a = Math.floor(Math.max(0, Math.min(1, p.intensity)) * 255);
                        grim.setColor(p.tintR, p.tintG, p.tintB, a);
                    } else {
                        const a = Math.floor(Math.max(0, Math.min(1, p.intensity)) * 255);
                        grim.setColor(255, 255, 255, a);
                    }
                    grim.setRotation(p.angle);
                    const size = 8 * p.scaleX;
                    grim.drawQuad(p.x - size / 2, p.y - size / 2, size, size);
                }
            }

            // === PASS 3: Slow particles (C: bonuses.c lines 1449-1467) ===
            // C: effect_select_texture(2) → PROJECTILE_TRAIL (Large Circle TL quarter)
            const slowFrame = getParticleAtlasFrame(ParticleFrame.PROJECTILE_TRAIL);
            grim.setAtlasFrame(slowFrame.atlasSize, slowFrame.frame);

            for (const p of this.particles) {
                if (!p.active) continue;
                if (p.styleId !== 8) continue;

                // C: piVar8[-4] = clamped intensity (scaleZ in our struct)
                const a = Math.floor(Math.max(0, Math.min(1, p.scaleZ)) * 255);
                grim.setColor(255, 255, 255, a);

                // C: piVar8[-1] = spin (NOT age) for oscillation: sin(spin)*3+15
                // C: piVar8[-7] = scaleX for scale multiplier
                const oscSize = (Math.sin(p.spin) * 3 + 15) * p.scaleX * 7;
                const perpSize = (15 - Math.sin(p.spin) * 3) * p.scaleX * 7;

                grim.drawQuad(
                    p.x - perpSize,
                    p.y - oscSize,
                    perpSize * 2,
                    oscSize * 2,
                );
            }

            grim.setRotation(0);
            grim.setBlendMode('normal');
        } else {
            // Fallback: colored circles when no sprite context
            for (const p of this.particles) {
                if (!p.active) continue;
                const isFire = p.styleId <= 2;

                if (p.tintR >= 0) {
                    const a = Math.floor(Math.max(0, Math.min(1, p.intensity)) * 255);
                    grim.setColor(p.tintR, p.tintG, p.tintB, a);
                } else if (isFire) {
                    // C-accurate fire color: (intensity, scaleX, scaleY, 1.0)
                    const r = Math.floor(Math.max(0, Math.min(1, p.intensity)) * 255);
                    const g = Math.floor(Math.max(0, Math.min(1, p.scaleX)) * 255);
                    const b = Math.floor(Math.max(0, Math.min(1, p.scaleY)) * 255);
                    grim.setColor(r, g, b, 255);
                } else if (p.styleId === 8) {
                    const a = Math.floor(Math.max(0, Math.min(1, p.intensity)) * 255);
                    grim.setColor(255, 255, 255, a);
                } else {
                    const a = Math.floor(Math.max(0, Math.min(1, p.intensity)) * 255);
                    grim.setColor(255, 255, 255, a);
                }
                const size = isFire ? Math.sin(Math.max(0, 1.0 - p.scaleX) * Math.PI / 2) * 24 : 2 * p.scaleX;
                grim.drawCircleFilled(p.x, p.y, Math.max(2, size));
            }
        }
    }

    /**
     * Get active particle count
     */
    getActiveCount(): number {
        return this.particles.filter((p) => p.active).length;
    }

    /**
     * Clear all particles
     */
    clear(): void {
        for (const particle of this.particles) {
            particle.reset();
        }
    }

    /**
     * Set the style ID of a particle by index.
     * Used by fire weapon variants: Blow Torch (style 1), HR Flamer (style 2).
     * C code: fx_spawn_particle returns index, then caller sets style_id.
     */
    setParticleStyleId(index: number, styleId: number): void {
        if (index >= 0 && index < this.maxParticles) {
            this.particles[index].styleId = styleId;
        }
    }

    /**
     * Get particles array for external collision checking.
     */
    getParticles(): readonly Particle[] {
        return this.particles;
    }

    /**
     * Check fire particle collisions against enemies.
     * C code reference: projectiles.c particle_pool update loop (lines 936-1087)
     *
     * C collision logic:
     *   creature_find_in_radius(pos, intensity * 8.0)
     *   creature_apply_damage(enemy, intensity * 10.0, 4, impulse)
     *
     * Fire particles (style 0, 1, 2) check for enemy collisions while their
     * renderFlag is true. On first hit, renderFlag is set to false (C: render_flag=0)
     * and the particle homes toward the hit enemy.
     *
     * @param enemies Array of enemies to check against
     * @param onHit Callback when a particle hits an enemy (enemyIndex, damage, particleX, particleY)
     */
    checkFireParticleCollisions(
        enemies: { x: number; y: number; isAlive(): boolean; active: boolean; getRadius(): number }[],
        onHit?: (enemyIndex: number, damage: number, x: number, y: number) => void,
    ): void {
        for (const particle of this.particles) {
            if (!particle.active) continue;
            // Only fire particles (style 0, 1, 2) deal damage
            if (particle.styleId > 2) continue;
            // Only check while renderFlag is true (C: render_flag check)
            if (!particle.renderFlag) continue;

            // C: collision radius = intensity * 8.0
            const collisionRadius = particle.intensity * 8.0;

            for (let i = 0; i < enemies.length; i++) {
                const enemy = enemies[i];
                if (!enemy.active || !enemy.isAlive()) continue;

                const dx = particle.x - enemy.x;
                const dy = particle.y - enemy.y;
                const distSq = dx * dx + dy * dy;
                const radiusSum = collisionRadius + enemy.getRadius();

                if (distSq < radiusSum * radiusSum) {
                    // C: damage = intensity * 10.0
                    const damage = particle.intensity * 10.0;

                    // C: render_flag = 0 → particle stops checking for new targets
                    particle.renderFlag = false;

                    // C: for style 8 (slow), particle snaps to enemy pos and stops
                    // For style 0 (fast), particle adjusts direction toward enemy
                    particle.targetId = i;

                    if (onHit) {
                        onHit(i, damage, particle.x, particle.y);
                    }
                    break;
                }
            }
        }
    }

    /**
     * Spawn 1-2 green radioactive particles at a position.
     * C code reference: radioactive perk VFX (lines 21661-21679)
     *
     * @param x X position (enemy or player)
     * @param y Y position
     */
    spawnRadioactive(x: number, y: number): void {
        const count = 1 + Math.floor(Math.random() * 2); // 1-2 particles
        for (let i = 0; i < count; i++) {
            const angle = Math.random() * Math.PI * 2;
            const speed = 15 + Math.random() * 15; // 15-30

            // Find free particle slot
            let index = -1;
            for (let j = 0; j < this.maxParticles; j++) {
                if (!this.particles[j].active) {
                    index = j;
                    break;
                }
            }
            if (index === -1) {
                index = Math.floor(Math.random() * 128) & 0x7f;
            }

            const p = this.particles[index];
            p.active = true;
            p.x = x + (Math.random() - 0.5) * 10; // slight position jitter
            p.y = y + (Math.random() - 0.5) * 10;
            p.vx = Math.cos(angle) * speed;
            p.vy = Math.sin(angle) * speed;
            p.intensity = 0.5 + Math.random() * 0.2; // 0.5-0.7
            p.scaleX = 0.3 + Math.random() * 0.2; // 0.3-0.5
            p.scaleY = p.scaleX;
            p.scaleZ = 1.0;
            p.age = 0;
            p.angle = angle;
            p.spin = Math.floor(Math.random() * 0x274) * 0.01;
            p.renderFlag = true;
            p.styleId = 16; // radioactive style
            p.targetId = -1;
            p.lifetime = 0.5 + Math.random() * 0.5; // 0.5-1.0s
            p.scaleStep = 0;
            // Green tint
            p.tintR = 50;
            p.tintG = 255;
            p.tintB = 80;
        }
    }

    /**
     * Spawn a burst of particles in a radial pattern
     * C code reference: effect_spawn_burst (used by energizer eat, line 1561)
     *
     * @param x Center X position
     * @param y Center Y position
     * @param count Number of particles to spawn
     */
    spawnBurst(x: number, y: number, count: number): void {
        const angleStep = (Math.PI * 2) / count;
        for (let i = 0; i < count; i++) {
            const angle = i * angleStep + Math.random() * 0.3; // slight randomness
            this.spawnFastParticle(x, y, angle, 1.0);
        }
    }
}
