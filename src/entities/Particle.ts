/**
 * Particle - Individual particle entity
 *
 * Accurate port of particle_t structure from crimsonland.exe_decompiled.c
 * C code reference: lines 18560-18650
 */

/**
 * Particle class
 * Represents a single particle in the particle system
 */
export class Particle {
    public active: boolean = false;
    public x: number = 0;
    public y: number = 0;
    public vx: number = 0;
    public vy: number = 0;
    public intensity: number = 1.0;
    public scaleX: number = 1.0;
    public scaleY: number = 1.0;
    public scaleZ: number = 1.0;
    public age: number = 0.0;
    public angle: number = 0.0;
    public spin: number = 0.0;
    public renderFlag: boolean = true;
    public styleId: number = 0; // 0 = fast, 8 = slow
    public targetId: number = -1;
    /** Configurable lifetime in seconds. C fast particles ~0.5s, slow ~0.8s. */
    public lifetime: number = 0.5;
    /** Scale change per second (0 = no change). */
    public scaleStep: number = 0;
    /** Per-particle tint override. -1 = use style default. */
    public tintR: number = -1;
    public tintG: number = -1;
    public tintB: number = -1;

    /**
     * Update particle — C-accurate physics from projectiles.c lines 936-1167
     *
     * The C code does NOT use a simple linear fade. Instead:
     * - Intensity decays at a per-style rate (0.9/sec fast, 0.11/sec slow)
     * - Movement is scaled by velocity × multiplier × intensity
     * - Angle wobbles randomly each frame, velocity is recalculated from angle
     * - Scale grows as intensity drops: scale = 1.0 - intensity * 0.95
     * - Deactivation is based on intensity threshold, not fixed lifetime
     *
     * @param dt Delta time in seconds
     */
    update(dt: number): void {
        if (!this.active) return;

        const isSlow = this.styleId === 8;
        const isFire = this.styleId <= 2; // 0 = Flamethrower, 1 = Blow Torch, 2 = HR Flamer

        // --- Intensity decay (C: projectiles.c line 940 / 959) ---
        if (isSlow) {
            this.intensity -= dt * 0.11;    // C: frame_dt * 0.11
            this.age += dt * 5.0;           // C: frame_dt * 5.0 (faster aging)
        } else if (isFire) {
            this.intensity -= dt * 0.9;     // C: frame_dt * 0.9
            this.age += dt;
        } else {
            // Non-fire, non-slow particles (radioactive etc) use simple update
            this.age += dt;
            this.x += this.vx * dt;
            this.y += this.vy * dt;
            if (this.scaleStep) {
                this.scaleX += this.scaleStep * dt;
            }
            this.intensity = Math.max(0, 1.0 - this.age / this.lifetime);
            if (this.age > this.lifetime) {
                this.active = false;
            }
            return;
        }

        // --- Movement (C: projectiles.c lines 942-978) ---
        if (this.renderFlag) {
            // renderFlag = true means particle hasn't collided with an enemy yet
            const dtVelX = dt * this.vx;
            const dtVelY = dt * this.vy;

            if (isSlow) {
                // Slow particles (style 8): C uses intensity multiplier, 0.55× when fading
                if (this.intensity <= 0.15) {
                    this.x += dtVelX * 0.55 * this.intensity;
                    this.y += dtVelY * 0.55 * this.intensity;
                } else {
                    this.x += dtVelX * this.intensity;
                    this.y += dtVelY * this.intensity;
                }
            } else {
                // Fast particles (style 0/1/2): C uses 2.5× velocity multiplier
                if (this.intensity <= 0.15) {
                    // Low intensity — use minimum 0.15 to keep particles moving slightly
                    this.x += dtVelX * 2.5 * 0.15;
                    this.y += dtVelY * 2.5 * 0.15;
                } else {
                    this.x += dtVelX * 2.5 * this.intensity;
                    this.y += dtVelY * 2.5 * this.intensity;
                }
            }
        }

        // --- Deactivation check (C: projectiles.c lines 981-1163) ---
        // All fire particles (style 0, 1, 2) deactivate when intensity runs out.
        // Slow particles (style 8) also deactivate when intensity <= 0.
        if (this.intensity <= 0) {
            this.active = false;
            return;
        }

        // --- Angle wobble & velocity recalculation (C: lines 984-1014) ---
        if (this.renderFlag) {
            // Random wobble: rand(-50..49) * 0.06 * intensity * dt * wobbleFactor
            const randVal = Math.floor(Math.random() * 100) - 50;

            if (this.styleId === 0) {
                // Style 0 (Flamethrower): strong wobble factor 1.96
                const wobble = randVal * 0.06 * this.intensity * dt * 1.96;
                this.angle -= wobble;
                // Recalculate velocity from angle at magnitude 82
                this.vx = Math.cos(this.angle) * 82.0;
                this.vy = Math.sin(this.angle) * 82.0;
            } else if (isSlow) {
                // Style 8 (slow): wobble factor 1.1, velocity magnitude 62
                const wobble = randVal * 0.06 * this.intensity * dt * 1.1;
                this.angle -= wobble;
                this.vx = Math.cos(this.angle) * 62.0;
                this.vy = Math.sin(this.angle) * 62.0;
            } else {
                // Style 1, 2 (Blow Torch, HR Flamer): wobble factor 1.1, velocity magnitude 82
                const wobble = randVal * 0.06 * this.intensity * dt * 1.1;
                this.angle -= wobble;
                this.vx = Math.cos(this.angle) * 82.0;
                this.vy = Math.sin(this.angle) * 82.0;
            }
        }

        // --- Scale update (C: projectiles.c lines 1016-1025) ---
        // C struct layout (pfVar5 = &spin, offset 11):
        //   pfVar5[-6] = offset 5 = intensity (decays over time)
        //   pfVar5[-5] = offset 6 = scaleX = 1.0 - intensity*0.95 (render R)
        //   pfVar5[-4] = offset 7 = scaleY = same (render G)
        //   pfVar5[-3] = offset 8 = scaleZ = 1.0 stays at spawn value (render B)
        //
        // C render pass 2: grim_set_color(intensity, scaleX, scaleY, scaleZ=1.0)
        //   birth: (1.0, 0.05, 0.05, 1.0) = bright RED
        //   death: (0.0, 1.0,  1.0,  1.0) = transparent (tiny size)
        const clampedIntensity = Math.max(0, Math.min(this.intensity, 1.0));
        const renderScale = 1.0 - clampedIntensity * 0.95;
        this.scaleX = renderScale;   // C: offset 6 — render G channel
        this.scaleY = renderScale;   // C: offset 7 — render B channel
        // scaleZ stays at spawn value 1.0 — C never modifies offset 8 for fire particles
    }

    /**
     * Reset particle to inactive state
     */
    reset(): void {
        this.active = false;
        this.x = 0;
        this.y = 0;
        this.vx = 0;
        this.vy = 0;
        this.intensity = 1.0;
        this.scaleX = 1.0;
        this.scaleY = 1.0;
        this.scaleZ = 1.0;
        this.age = 0.0;
        this.angle = 0.0;
        this.spin = 0.0;
        this.renderFlag = true;
        this.styleId = 0;
        this.targetId = -1;
        this.lifetime = 0.5;
        this.scaleStep = 0;
        this.tintR = -1;
        this.tintG = -1;
        this.tintB = -1;
    }
}
