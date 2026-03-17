/**
 * Projectile - Projectile entity class
 *
 * Represents bullets, plasma bolts, and other projectiles fired by weapons.
 * C-accurate port of projectile_spawn / projectile_update from projectiles.c.
 */

import type { GrimInterface } from '../engine/GrimInterface';
import { ProjectileType } from '../data/WeaponData';

/**
 * Projectile entity
 */
export class Projectile {
    // Position
    public x: number;
    public y: number;

    // Velocity (C: vel_x, vel_y — initialized to cos/sin(angle) * 1.5)
    public vx: number;
    public vy: number;

    // Properties
    public angle: number;
    public damage: number;
    /**
     * C: life_timer — initialized to 0.4 for ALL projectiles.
     *   == 0.4  → alive and active (checked in rendering)
     *   < 0.4   → fading/dying state
     *   <= 0.0  → deactivate
     */
    public lifetime: number;
    public maxLifetime: number = 0.4;
    public speed: number;
    public active: boolean = true;

    // Owner (for collision filtering)
    public ownerId: number; // -1 = player, >= 0 = enemy ID

    // Visual
    private readonly radius: number = 3;

    // Chain lightning properties (C lines 19290-19303)
    public isChainLightning: boolean = false;
    public chainProjectileId: number = -1; // Unique ID for tracking chain projectile

    // Projectile type (determines behavior and visuals)
    public projectileType: ProjectileType = ProjectileType.BULLET;

    // ---- Trail rendering data (C code: projectile struct offsets 0x10-0x20) ----
    // Trail connects from spawn point (tail) to current position (head).
    // C code: trail tail stays at the ORIGIN position. Trail alpha fades via life_timer * 2.5.
    public headX: number = 0; // Current bullet position (leading edge)
    public headY: number = 0;
    public tailX: number = 0; // Spawn position (trailing edge, stays at origin)
    public tailY: number = 0;
    public perpX: number = 0; // Perpendicular offset (for trail width)
    public perpY: number = 0;

    // Spawn position (where the bullet was fired from)
    public spawnX: number = 0;
    public spawnY: number = 0;

    // C-accurate damage properties (for distance-based damage formula)
    // damage = ((100/dist) * damageScale * 30 + 10) * 0.95
    public originX: number = 0; // Firing origin X (for distance calc)
    public originY: number = 0; // Firing origin Y (for distance calc)
    public damageScale: number = 0; // C weapon_table offset 0x70 (0 = use flat damage)
    public hitRadius: number = 1.0; // C projectile hit radius (default 1.0)

    // C-accurate penetration (damage_pool) — Fix #6
    // Gauss=300, Fire=240, Blade=50, Ion=1, others=1
    // On hit: damagePool -= creature.health. If damagePool <= 0, set lifetime = 0.25 (dying)
    public damagePool: number = 1.0;

    // Fire visual overlay flag (C: fire_bullets fires the weapon's own projectile type;
    // the fire visual is a rendering overlay, not a type change)
    public hasFireVisual: boolean = false;

    // C: bonus_spawn_guard — prevents bonus drops from chain/fireblast kills
    public noBonusDrop: boolean = false;

    // Accuracy tracking: set true on first enemy hit to prevent multi-counting
    public hasRecordedHit: boolean = false;

    // C-accurate speed scale — Fix #7
    // C movement: vel * speed_scale * 3.0 * 20.0 * dt
    // Barrel Greaser perk increases substep count (faster effective speed)
    public speedScale: number = 1.0;

    // Terrain dimensions for bounds check — Fix #5
    // C: x < -64 || y < -64 || x > terrain_texture_width + 64 || y > terrain_texture_height + 64
    public terrainWidth: number = 1024;
    public terrainHeight: number = 1024;

    // Ion weapon radius damage support — Fix #10
    // When lifetime < 0.4 (fading), ion projectiles deal continuous AoE
    public ionMasterScale: number = 1.0; // 1.0 normally, 1.2 with Ion Gun Master perk

    // Rocket physics — Fix #12
    // Rockets accelerate each frame. Seekers steer toward target.
    public isRocket: boolean = false;
    public rocketType: 'rocket' | 'seeker' | 'minigun' | 'none' = 'none';
    public rocketTargetId: number = -1; // Seeker rocket target enemy ID
    public isExploding: boolean = false; // Rocket explosion state
    public explosionTimer: number = 0; // Explosion growth timer
    public explosionScale: number = 1.0; // Explosion radius scale

    constructor(
        x: number,
        y: number,
        vx: number,
        vy: number,
        damage: number,
        lifetime: number = 0.4,
        ownerId: number = -1,
        projectileType: ProjectileType = ProjectileType.BULLET,
    ) {
        this.x = x;
        this.y = y;
        this.vx = vx;
        this.vy = vy;
        this.damage = damage;
        this.lifetime = lifetime;
        this.maxLifetime = lifetime; // Store initial lifetime
        this.ownerId = ownerId;
        this.projectileType = projectileType;

        // Calculate angle and speed from velocity
        this.angle = Math.atan2(vy, vx);
        this.speed = Math.sqrt(vx * vx + vy * vy);

        // Store spawn position — this becomes the fixed tail of the trail
        this.spawnX = x;
        this.spawnY = y;

        // Compute initial trail geometry
        this.updateTrailGeometry();
    }

    /**
     * Compute trail geometry — Fix #13
     * C code: trail tail stays at the ORIGIN position (spawnX/spawnY).
     * No artificial maxTrailLength cap. Trail alpha is controlled by life_timer * 2.5,
     * which naturally fades the trail as the bullet dies.
     */
    private updateTrailGeometry(): void {
        // Head = current bullet position
        this.headX = this.x;
        this.headY = this.y;

        // Trail tail stays at spawn/origin position (no capping)
        this.tailX = this.spawnX;
        this.tailY = this.spawnY;

        // Perpendicular is 90° rotated from velocity direction
        if (this.speed > 0) {
            const dirX = this.vx / this.speed;
            const dirY = this.vy / this.speed;
            this.perpX = -dirY * 1.0;
            this.perpY = dirX * 1.0;
        }
    }

    /**
     * Update rocket physics — Fix #12
     * C code: secondary_projectile pool (projectiles.c L661-720)
     *
     * Standard rockets: accelerate at (1 + dt*3) while speed < 500
     * Minigun rockets:  accelerate at (1 + dt*4) while speed < 600
     * Seeker rockets:   steer toward target at 800 px/s², speed cap 350
     *                   lifetime decays 0.5× slower
     */
    private updateRocketPhysics(dt: number, enemies?: Array<{ x: number; y: number; active: boolean; health: number }>): void {
        const currentSpeed = Math.sqrt(this.vx * this.vx + this.vy * this.vy);

        switch (this.rocketType) {
            case 'rocket': {
                // C L667-676: if speed < 500, multiply vel by (1 + dt*3)
                if (currentSpeed < 500) {
                    const accel = 1.0 + dt * 3.0;
                    this.vx *= accel;
                    this.vy *= accel;
                }
                break;
            }
            case 'minigun': {
                // C L683-688: if speed < 600, multiply vel by (1 + dt*4)
                if (currentSpeed < 600) {
                    const accel = 1.0 + dt * 4.0;
                    this.vx *= accel;
                    this.vy *= accel;
                }
                break;
            }
            case 'seeker': {
                // C L691-718: Seeker rockets steer toward nearest enemy
                // 1. Find nearest alive enemy (creature_find_nearest)
                // 2. Compute angle from rocket to target using atan2
                // 3. Apply 800 px/s² acceleration toward target
                // 4. If speed > 350, subtract the acceleration (speed cap)

                // Find nearest alive enemy
                let targetX = this.x + this.vx; // Fallback: keep going straight
                let targetY = this.y + this.vy;
                let hasTarget = false;

                if (enemies) {
                    let bestDist = Infinity;
                    for (const enemy of enemies) {
                        if (!enemy.active || enemy.health <= 0) continue;
                        const edx = enemy.x - this.x;
                        const edy = enemy.y - this.y;
                        const dist = Math.sqrt(edx * edx + edy * edy);
                        if (dist < bestDist) {
                            bestDist = dist;
                            targetX = enemy.x;
                            targetY = enemy.y;
                            hasTarget = true;
                        }
                    }
                }

                if (hasTarget) {
                    // C L696-700: angle = atan2(rocket.y - target.y, rocket.x - target.x) - PI/2
                    // Note: C uses atan2(self-target) which points AWAY, then subtracts PI/2.
                    // The result is the angle FROM target TO rocket, rotated -90°.
                    // We simplify: compute angle TO target directly.
                    const angleToTarget = Math.atan2(targetY - this.y, targetX - this.x);

                    // C L701-707: Apply 800 px/s² acceleration in target direction
                    const accelMag = 800.0 * dt;
                    this.vx += Math.cos(angleToTarget) * accelMag;
                    this.vy += Math.sin(angleToTarget) * accelMag;

                    // C L708-717: If speed > 350, subtract the same acceleration (clamp)
                    const newSpeed = Math.sqrt(this.vx * this.vx + this.vy * this.vy);
                    if (newSpeed > 350.0) {
                        this.vx -= Math.cos(angleToTarget) * accelMag;
                        this.vy -= Math.sin(angleToTarget) * accelMag;
                    }
                }
                break;
            }
        }

        // Update speed cache
        this.speed = Math.sqrt(this.vx * this.vx + this.vy * this.vy);
        // Update angle from velocity
        if (this.speed > 0) {
            this.angle = Math.atan2(this.vy, this.vx);
        }
    }

    /**
     * Update projectile — C-accurate port of projectile_update
     *
     * C code structure (projectiles.c lines 126-618):
     *   if (life_timer <= 0) deactivate
     *   if (life_timer >= 0.4) { // ALIVE phase
     *       bounds check → decay
     *       movement with substeps
     *       collision detection
     *   } else { // FADING phase (life_timer < 0.4)
     *       ion weapons: area damage
     *       gauss: slow decay (0.1)
     *       ion cannon: medium decay (0.7)
     *       standard: normal decay (1.0)
     *   }
     *
     * FIRE_BULLETS uses Python particle physics (separate pool in C).
     */
    update(dt: number, enemies?: Array<{ x: number; y: number; active: boolean; health: number; takeDamage?: (damage: number, type: number, ix: number, iy: number) => void }>): void {
        if (!this.active) return;

        // === Rocket EXPLODING phase (C projectiles.c L620-659) ===
        // Rockets that hit an enemy transition to EXPLODING: sit still, deal growing AoE damage.
        // explosionTimer grows at 3× rate. AoE radius = scale * timer * 80 pixels.
        // AoE DPS = scale * 700 * dt. Deactivate when timer > 1.0.
        if (this.isExploding) {
            this.explosionTimer += dt * 3.0;

            if (this.explosionTimer > 1.0) {
                // C L626-633: explosion finished — deactivate
                // (In C, this also bakes a burn mark on terrain at scale * 256 pixels)
                this.active = false;
                return;
            }

            // C L635-659: deal AoE damage to all enemies within radius
            const aoeRadius = this.explosionScale * this.explosionTimer * 80.0;
            const aoeDamage = this.explosionScale * 700.0 * dt;

            if (enemies && aoeDamage > 0) {
                for (const enemy of enemies) {
                    if (!enemy.active || enemy.health <= 0) continue;
                    const edx = enemy.x - this.x;
                    const edy = enemy.y - this.y;
                    const dist = Math.sqrt(edx * edx + edy * edy);
                    if (dist < aoeRadius) {
                        // C L647-648: knockback = normalized direction * 0.1
                        const knockX = dist > 0 ? (edx / dist) * 0.1 : 0;
                        const knockY = dist > 0 ? (edy / dist) * 0.1 : 0;
                        if (enemy.takeDamage) {
                            enemy.takeDamage(aoeDamage, 3, knockX, knockY);
                        }
                    }
                }
            }
            return; // Don't do regular physics while exploding
        }

        {
            // === Standard projectile physics (C: projectile_update) ===
            // Fire bullets also use this path — C spawns them into the projectile pool
            // with the same movement formula: vel * speedScale * 3.0 * 20.0 * dt

            // Check if expired — Fix #2: ONLY check <= 0.0 (removed < 0.8 check)
            if (this.lifetime <= 0.0) {
                // C projectiles.c L909-913: rockets transition to EXPLODING when
                // lifetime expires (mid-air detonation with scale 0.5)
                if (this.isRocket && !this.isExploding) {
                    this.isExploding = true;
                    this.explosionTimer = 0;
                    this.vx = 0;
                    this.vy = 0;
                    this.explosionScale = 0.5;
                    return;
                }
                this.active = false;
                return;
            }

            // C: secondary projectiles (rockets) have NO 0.4 threshold — they fly
            // while lifetime > 0.0. Primary projectiles use >= 0.4 as alive threshold.
            if (this.isRocket ? this.lifetime > 0.0 : this.lifetime >= 0.4) {
                // === ALIVE phase ===

                // Bounds check — Fix #5: Use terrain dimensions + 64px margin
                if (
                    this.x < -64 ||
                    this.y < -64 ||
                    this.x > this.terrainWidth + 64 ||
                    this.y > this.terrainHeight + 64
                ) {
                    // Out of bounds → start dying
                    this.lifetime -= dt;
                    return;
                }

                // Movement — Fix #7: C formula: vel * speed_scale * 3.0 * 20.0 * dt
                // The C velocity is initialized as cos/sin(angle) * 1.5, so with speed_scale=1:
                //   1.5 * 1.0 * 3.0 * 20.0 = 90 units/frame at 60fps → ~5400px/s
                // Our TS velocity is already in px/s, so we just apply: pos += vel * dt
                // The speedScale is baked into the velocity at spawn time.
                this.x += this.vx * dt;
                this.y += this.vy * dt;

                // === Pulse Gun dynamic hitRadius (C projectile_render L1653-1668) ===
                // C: wave sprite atlas(2,0) scales with distance from origin: size = dist * 0.01 * 16
                // The collider must grow to match the visual wave: hitRadius = dist * 0.01 * 8
                if (this.projectileType === ProjectileType.PULSE_GUN) {
                    const pdx = this.originX - this.x;
                    const pdy = this.originY - this.y;
                    const pDist = Math.sqrt(pdx * pdx + pdy * pdy);
                    this.hitRadius = Math.max(4, pDist * 0.01 * 8);
                }

                // === Rocket physics — Fix #12 (C projectiles.c L661-720) ===
                if (this.isRocket) {
                    this.updateRocketPhysics(dt, enemies);

                    // C lifetime decay per rocket type:
                    // Standard: lifetime -= dt          (L678)
                    // Minigun:  lifetime -= dt          (L689→L678)
                    // Seeker:   lifetime -= dt * 0.5    (L719)
                    if (this.rocketType === 'seeker') {
                        this.lifetime -= dt * 0.5;
                    } else {
                        this.lifetime -= dt;
                    }
                }

                // Update trail geometry
                this.updateTrailGeometry();
            } else {
                // === FADING phase (life_timer < 0.4) ===
                // Type-specific decay — Fix #3

                const pType = this.projectileType;

                if (pType === ProjectileType.ION_RIFLE || pType === ProjectileType.ION_MINIGUN) {
                    // Ion Rifle/Minigun fading: decay at 1:1, deal radius damage
                    // C projectiles.c L586-601: creatures_apply_radius_damage(pos, radius, damage, 7)
                    // ION_RIFLE:  radius = ionMasterScale * 88,  damage = dt * 100
                    // ION_MINIGUN: radius = ionMasterScale * 60, damage = dt * 40
                    this.lifetime -= dt;
                    if (enemies) {
                        const radius = pType === ProjectileType.ION_RIFLE
                            ? this.ionMasterScale * 88.0
                            : this.ionMasterScale * 60.0;
                        const dmg = pType === ProjectileType.ION_RIFLE
                            ? dt * 100.0
                            : dt * 40.0;
                        for (const enemy of enemies) {
                            if (!enemy.active || enemy.health <= 0) continue;
                            const edx = enemy.x - this.x;
                            const edy = enemy.y - this.y;
                            if (Math.sqrt(edx * edx + edy * edy) < radius && enemy.takeDamage) {
                                enemy.takeDamage(dmg, 7, 0, 0);
                            }
                        }
                    }
                } else if (pType === ProjectileType.ION_CANNON) {
                    // Ion Cannon fading: decay at 0.7x, deal radius damage
                    // C projectiles.c L609-613: creatures_apply_radius_damage(pos, ionMaster*128, dt*300, 7)
                    this.lifetime -= dt * 0.7;
                    if (enemies) {
                        const radius = this.ionMasterScale * 128.0;
                        const dmg = dt * 300.0;
                        for (const enemy of enemies) {
                            if (!enemy.active || enemy.health <= 0) continue;
                            const edx = enemy.x - this.x;
                            const edy = enemy.y - this.y;
                            if (Math.sqrt(edx * edx + edy * edy) < radius && enemy.takeDamage) {
                                enemy.takeDamage(dmg, 7, 0, 0);
                            }
                        }
                    }
                } else if (pType === ProjectileType.GAUSS_GUN) {
                    // Gauss Gun: decay at 0.1x (10x slower — makes trails persist)
                    this.lifetime -= dt * 0.1;
                } else {
                    // All others: standard 1:1 decay
                    this.lifetime -= dt;
                }
                return; // Don't move during fading phase
            }

            // Alive-phase lifetime decay — Fix #3
            // Standard projectiles with life_timer >= 0.4: decay at 1:1
            // (only decays while alive, not during fading — fading handled above)
            // Note: lifetime stays at 0.4 while alive (it's a sentinel).
            // It only drops below 0.4 when the projectile is hit/killed.
            // The C code doesn't decay life_timer for alive projectiles normally —
            // it only changes on bounds-exit or on-hit (set to 0.25).
        }

        // Normalize angle to 0-2π range (C lines 19937-19946)
        const TWO_PI = 6.2831855; // 2π (matches C constant)
        while (this.angle > TWO_PI) {
            this.angle -= TWO_PI;
        }
        while (this.angle < 0.0) {
            this.angle += TWO_PI;
        }
    }

    /**
     * Get trail alpha — Fix #13
     * C code: clamp(life_timer * 2.5, 0, 1)
     * At life_timer = 0.4: alpha = 1.0 (full)
     * As bullet fades (life_timer → 0): alpha → 0
     */
    getTrailAlpha(): number {
        const alpha = this.lifetime * 2.5;
        if (alpha < 0) return 0;
        if (alpha > 1) return 1;
        return alpha;
    }

    /**
     * Render projectile with type-specific visuals
     * Uses SpriteRenderer for textured rendering when available,
     * falls back to colored circles in debug mode
     */
    render(grim: GrimInterface, spriteRenderer?: any, debugMode: boolean = true): void {
        if (!this.active) return;

        // Use texture-based rendering when sprite renderer is available and not in debug mode
        if (spriteRenderer && !debugMode && spriteRenderer.canDrawProjectile()) {
            spriteRenderer.drawProjectile(grim, this);
            return;
        }

        // ---------- Debug / fallback rendering (original colored circles) ----------

        // Enemy projectiles have distinct orange/red color
        if (this.ownerId >= 0) {
            grim.setColor(255, 100, 0, 255); // Orange
            grim.drawCircleFilled(this.x, this.y, this.radius + 1);
            grim.setColor(255, 50, 0, 150); // Red glow
            grim.drawCircleFilled(this.x, this.y, this.radius + 3);
            return;
        }

        // Render based on projectile type (debug fallback)
        switch (this.projectileType) {
            case ProjectileType.PISTOL:
            case ProjectileType.ASSAULT_RIFLE:
            case ProjectileType.SHOTGUN:
            case ProjectileType.SMG:
            case ProjectileType.MINIGUN:
                // C: bullet_trail_texture quad + bullet_head sprite
                // Trail: PISTOL=1.2x, ASSAULT_RIFLE=1.0x, GAUSS=1.1x blue, rest=0.7x
                // Head: PISTOL=6px, ASSAULT_RIFLE=8px, rest=4px
                grim.setColor(128, 128, 128, 200);
                grim.drawCircleFilled(this.x, this.y, this.radius);
                // Motion trail
                const trailLength = 8;
                const trailX = this.x - Math.cos(this.angle) * trailLength;
                const trailY = this.y - Math.sin(this.angle) * trailLength;
                grim.setColor(128, 128, 128, 100);
                grim.drawLine(this.x, this.y, trailX, trailY, 2);
                break;

            case ProjectileType.GAUSS_GUN:
                // C: blue trail (0.2, 0.5, 1.0), 1.1x perp scale, 4px bullet head
                {
                    const gaussAlpha = this.getTrailAlpha();
                    const gaussTrailLen = 20;
                    const gaussTailX = this.x - Math.cos(this.angle) * gaussTrailLen;
                    const gaussTailY = this.y - Math.sin(this.angle) * gaussTrailLen;
                    grim.setColor(51, 128, 255, Math.floor(gaussAlpha * 200));
                    grim.drawLine(this.x, this.y, gaussTailX, gaussTailY, 2);
                    grim.setColor(51, 128, 255, 255);
                    grim.drawCircleFilled(this.x, this.y, 2);
                }
                break;

            case ProjectileType.PLASMA_RIFLE:
                // C: 56px glow, white (1,1,1), 8-segment trail, 256px bloom
                {
                    const pAlpha = this.getTrailAlpha();
                    grim.setColor(255, 255, 255, Math.floor(pAlpha * 0.45 * 255));
                    grim.drawCircleFilled(this.x, this.y, 28);
                    grim.setColor(255, 255, 255, Math.floor(pAlpha * 0.3 * 200));
                    grim.drawCircleFilled(this.x, this.y, 64);
                }
                break;

            case ProjectileType.PLASMA_MINIGUN:
                // C: 16px glow, white (1,1,1), 3-segment trail
                {
                    const pmAlpha = this.getTrailAlpha();
                    grim.setColor(255, 255, 255, Math.floor(pmAlpha * 0.45 * 255));
                    grim.drawCircleFilled(this.x, this.y, 8);
                    grim.setColor(255, 255, 255, Math.floor(pmAlpha * 0.15 * 200));
                    grim.drawCircleFilled(this.x, this.y, 30);
                }
                break;

            case ProjectileType.PLASMA_CANNON:
                // C: 84px glow, white (1,1,1), 18-segment trail, 256px bloom
                {
                    const pcAlpha = this.getTrailAlpha();
                    grim.setColor(255, 255, 255, Math.floor(pcAlpha * 0.45 * 255));
                    grim.drawCircleFilled(this.x, this.y, 42);
                    grim.setColor(255, 255, 255, Math.floor(pcAlpha * 0.3 * 200));
                    grim.drawCircleFilled(this.x, this.y, 64);
                }
                break;

            case ProjectileType.SPIDER_PLASMA:
                // C: 16px glow, GREEN (0.3, 1.0, 0.3), 3-segment trail
                {
                    const spAlpha = this.getTrailAlpha();
                    grim.setColor(77, 255, 77, Math.floor(spAlpha * 0.45 * 255));
                    grim.drawCircleFilled(this.x, this.y, 8);
                    grim.setColor(77, 255, 77, Math.floor(spAlpha * 0.15 * 200));
                    grim.drawCircleFilled(this.x, this.y, 30);
                }
                break;

            case ProjectileType.SHRINKIFIER:
                // C: 16px glow, BLUE (0.3, 0.3, 1.0), 3-segment trail
                {
                    const shAlpha = this.getTrailAlpha();
                    grim.setColor(77, 77, 255, Math.floor(shAlpha * 0.45 * 255));
                    grim.drawCircleFilled(this.x, this.y, 8);
                    grim.setColor(77, 77, 255, Math.floor(shAlpha * 0.15 * 200));
                    grim.drawCircleFilled(this.x, this.y, 30);
                }
                break;

            case ProjectileType.ROCKET:
                // C: 14×14 sprite atlas(4,3), gray (0.8,0.8,0.8)
                // Glow trail: 60×60 white at alpha 0.68
                grim.setColor(204, 204, 204, 255);
                grim.drawCircleFilled(this.x, this.y, 7);
                {
                    const rtAngle = this.angle - Math.PI / 2;
                    const rtX = this.x - Math.cos(rtAngle) * 9;
                    const rtY = this.y - Math.sin(rtAngle) * 9;
                    grim.setColor(255, 255, 255, Math.floor(0.68 * 200));
                    grim.drawCircleFilled(rtX, rtY, 30);
                }
                break;

            case ProjectileType.SEEKER_ROCKET:
                // C: 10×10 sprite atlas(4,3), gray (0.8,0.8,0.8)
                // Glow trail: 40×40 white at alpha 0.58
                grim.setColor(204, 204, 204, 255);
                grim.drawCircleFilled(this.x, this.y, 5);
                {
                    const srAngle = this.angle - Math.PI / 2;
                    const srX = this.x - Math.cos(srAngle) * 9;
                    const srY = this.y - Math.sin(srAngle) * 9;
                    grim.setColor(255, 255, 255, Math.floor(0.58 * 200));
                    grim.drawCircleFilled(srX, srY, 20);
                }
                break;

            case ProjectileType.ROCKET_MINIGUN:
                // C: 8×8 sprite atlas(4,3), gray (0.8,0.8,0.8)
                // Glow trail: 30×30 blue (0.7,0.7,1.0) at alpha 0.158
                grim.setColor(204, 204, 204, 255);
                grim.drawCircleFilled(this.x, this.y, 4);
                {
                    const rmAngle = this.angle - Math.PI / 2;
                    const rmX = this.x - Math.cos(rmAngle) * 9;
                    const rmY = this.y - Math.sin(rmAngle) * 9;
                    grim.setColor(179, 179, 255, Math.floor(0.158 * 255));
                    grim.drawCircleFilled(rmX, rmY, 15);
                }
                break;

            case ProjectileType.ION_RIFLE:
                // C: blue-white (0.5,0.6,1.0), beam scale 2.2, atlas(4,2)
                // Beam trail segments along path, head glow at (1.0,1.0,0.7)
                {
                    const irAlpha = this.getTrailAlpha();
                    const irBeamScale = 2.2;
                    const irBeamLen = irBeamScale * 32;
                    const irCos = Math.cos(this.angle + Math.PI);
                    const irSin = Math.sin(this.angle + Math.PI);
                    grim.setColor(128, 153, 255, Math.floor(irAlpha * 200));
                    grim.drawLine(this.x, this.y,
                        this.x + irCos * irBeamLen, this.y + irSin * irBeamLen,
                        Math.max(2, irBeamScale * 3));
                    grim.setColor(255, 255, 179, Math.floor(irAlpha * 255));
                    grim.drawCircleFilled(this.x, this.y, irBeamScale * 8);
                }
                break;

            case ProjectileType.ION_MINIGUN:
                // C: blue-white (0.5,0.6,1.0), beam scale 1.05, atlas(4,2)
                {
                    const imAlpha = this.getTrailAlpha();
                    const imBeamScale = 1.05;
                    const imBeamLen = imBeamScale * 32;
                    const imCos = Math.cos(this.angle + Math.PI);
                    const imSin = Math.sin(this.angle + Math.PI);
                    grim.setColor(128, 153, 255, Math.floor(imAlpha * 200));
                    grim.drawLine(this.x, this.y,
                        this.x + imCos * imBeamLen, this.y + imSin * imBeamLen,
                        Math.max(2, imBeamScale * 3));
                    grim.setColor(255, 255, 179, Math.floor(imAlpha * 255));
                    grim.drawCircleFilled(this.x, this.y, imBeamScale * 8);
                }
                break;

            case ProjectileType.ION_CANNON:
                // C: blue-white (0.5,0.6,1.0), beam scale 3.5, atlas(4,2)
                {
                    const icAlpha = this.getTrailAlpha();
                    const icBeamScale = 3.5;
                    const icBeamLen = icBeamScale * 32;
                    const icCos = Math.cos(this.angle + Math.PI);
                    const icSin = Math.sin(this.angle + Math.PI);
                    grim.setColor(128, 153, 255, Math.floor(icAlpha * 200));
                    grim.drawLine(this.x, this.y,
                        this.x + icCos * icBeamLen, this.y + icSin * icBeamLen,
                        Math.max(2, icBeamScale * 3));
                    grim.setColor(255, 255, 179, Math.floor(icAlpha * 255));
                    grim.drawCircleFilled(this.x, this.y, icBeamScale * 8);
                }
                break;

            case ProjectileType.FIRE_BULLETS:
                // C: Rendered like ion beam but ORANGE (1.0, 0.6, 0.1), beam scale 0.8
                // atlas(4,2), same beam trail structure as ion weapons
                {
                    const fbAlpha = this.getTrailAlpha();
                    const fbBeamScale = 0.8;
                    const fbBeamLen = fbBeamScale * 32;
                    const fbCos = Math.cos(this.angle + Math.PI);
                    const fbSin = Math.sin(this.angle + Math.PI);
                    grim.setColor(255, 153, 25, Math.floor(fbAlpha * 200));
                    grim.drawLine(this.x, this.y,
                        this.x + fbCos * fbBeamLen, this.y + fbSin * fbBeamLen,
                        Math.max(2, fbBeamScale * 3));
                    grim.setColor(255, 255, 179, Math.floor(fbAlpha * 255));
                    grim.drawCircleFilled(this.x, this.y, fbBeamScale * 8);
                }
                break;

            case ProjectileType.PULSE_GUN:
                // C: Green (0.1, 0.6, 0.2), atlas(2,0), distance-scaled size
                // Size = distance_from_origin * 0.01 * 16, then half for radius
                {
                    const pdx = this.originX - this.x;
                    const pdy = this.originY - this.y;
                    const pDist = Math.sqrt(pdx * pdx + pdy * pdy);
                    const pScale = pDist * 0.01;
                    const pSize = Math.max(4, pScale * 16);
                    grim.setColor(26, 153, 51, Math.floor(0.7 * 255));
                    grim.drawCircleFilled(this.x, this.y, pSize / 2);
                }
                break;

            case ProjectileType.SPLITTER_GUN:
                // C: atlas(4,3), white (1.0, 1.0, 1.0), distance-scaled (max 20px)
                // Also gets a 0.7x bullet trail in C pass 1
                {
                    const sdx = this.originX - this.x;
                    const sdy = this.originY - this.y;
                    let sDist = Math.sqrt(sdx * sdx + sdy * sdy);
                    if (sDist > 20) sDist = 20;
                    const sHalf = sDist * 0.5;
                    // Trail
                    const sTailX = this.x - Math.cos(this.angle) * 8;
                    const sTailY = this.y - Math.sin(this.angle) * 8;
                    grim.setColor(128, 128, 128, 100);
                    grim.drawLine(this.x, this.y, sTailX, sTailY, 1);
                    // Head sprite
                    grim.setColor(255, 255, 255, 255);
                    grim.drawCircleFilled(this.x, this.y, Math.max(2, sHalf));
                }
                break;

            case ProjectileType.BLADE_GUN:
                // C: atlas(4,6), gray (0.8, 0.8, 0.8), distance-scaled (max 20px)
                // Time-based spinning rotation (C: index*0.1 - quest_spawn_timeline*0.1)
                {
                    const bdx = this.originX - this.x;
                    const bdy = this.originY - this.y;
                    let bDist = Math.sqrt(bdx * bdx + bdy * bdy);
                    if (bDist > 20) bDist = 20;
                    const bHalf = bDist * 0.5;
                    // Spinning visual — use time-based rotation approximation
                    // C: rotation = (float)(int)fVar27 * 0.1 - (float)quest_spawn_timeline * 0.1
                    const spinAngle = (Date.now() * 0.006) % (Math.PI * 2);
                    const bCos = Math.cos(spinAngle);
                    const bSin = Math.sin(spinAngle);
                    grim.setColor(204, 204, 204, 255);
                    // Draw spinning cross for blade visual
                    grim.drawLine(
                        this.x - bCos * bHalf, this.y - bSin * bHalf,
                        this.x + bCos * bHalf, this.y + bSin * bHalf, 2);
                    grim.drawLine(
                        this.x - bSin * bHalf, this.y + bCos * bHalf,
                        this.x + bSin * bHalf, this.y - bCos * bHalf, 2);
                }
                break;

            case ProjectileType.PLAGUE_SPREADER:
                // C: White multi-sprite cluster, 60px main + animated sub-sprites
                // Main: 60×60, then offset copies with time-based rotation
                {
                    const plague_time = (Date.now() * 0.003) % (Math.PI * 2);
                    grim.setColor(255, 255, 255, 255);
                    grim.drawCircleFilled(this.x, this.y, 15);
                    // Sub-sprites at animated offsets (C: 3 extra quads at 120° intervals)
                    for (let i = 0; i < 3; i++) {
                        const subAngle = plague_time + i * 2.0943952; // 120° apart
                        const offX = Math.cos(subAngle) * 10;
                        const offY = Math.sin(subAngle) * 10;
                        grim.setColor(255, 255, 255, 200);
                        grim.drawCircleFilled(this.x + offX, this.y + offY, 12);
                    }
                }
                break;

            default:
                // Fallback to gray bullet rendering
                grim.setColor(128, 128, 128, 255);
                grim.drawCircleFilled(this.x, this.y, this.radius);
                break;
        }
    }

    /**
     * Deactivate projectile (hit something)
     */
    deactivate(): void {
        this.active = false;
    }

    /**
     * Check if projectile is still active
     */
    isActive(): boolean {
        return this.active;
    }
}
