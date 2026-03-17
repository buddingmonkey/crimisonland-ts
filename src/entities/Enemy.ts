/**
 * Enemy - Enemy entity class
 *
 * Represents hostile creatures that chase and attack the player.
 * Based on enemy logic from crimsonland.exe_decompiled.c
 */

import type { GrimInterface } from '../engine/GrimInterface';
import { CREATURE_TYPE_TABLE } from '../rendering/SpriteSheetConfig';
import { PerkId } from '../systems/PerkSystem';

/**
 * Enemy types — indices match C creature_type_table (gameplay.c L1375-1440).
 * Each index corresponds to a distinct sprite texture and animation config.
 *
 * NOTE: Enum names are legacy from Ghidra's misleading variable naming.
 * Cross-referenced with Python port to confirm correct sprite mapping.
 */
export enum EnemyType {
    Zombie = 0, // C type 0 - zombie.jaz (slow, tough, linear walk)
    Lizard = 1, // C type 1 - lizard.jaz (bounce walk)
    Spider = 2, // C type 2 - alien.jaz (the main "alien/bug" enemy, linear walk)
    Spider2 = 3, // C type 3 - spider_sp1.jaz (bounce walk)
    Alien = 4, // C type 4 - spider_sp2.jaz (fast variant, bounce walk)
    Trooper = 5, // C type 5 - trooper.jaz (enemy trooper, bounce walk)
}

/**
 * AI Mode enum (C lines 21388-21550)
 */
export enum AIMode {
    CHASE_CIRCLE = 0, // Chase or circle at 85% distance
    CLOSE_CIRCLE = 1, // Circle at 55% distance when close
    DIRECT_CHASE = 2, // Always target player directly (C line 1390)
    FOLLOW_LEADER = 3, // Follow another enemy (formation)
    ORBIT_LEADER = 4, // Circle like mode 0, but dies if leader dies (C line 1318)
    LINKED_TO_LEADER = 5, // Dies when leader dies
    ORBIT_ANGLE = 6, // Orbit leader at fixed angle+radius (C line 1365)
    BURROW = 7, // Timer-based emerge/hide behavior
    WIDE_CIRCLE = 8, // Circle at 90% distance
}

/**
 * Enemy entity
 */
export class Enemy {
    // Position
    public x: number;
    public y: number;

    // Movement
    public angle: number = 0;
    public speed: number;
    public maxSpeed: number;
    public animTimer: number = 0;
    public animPhase: number = 0; // C: anim_phase (0-31 or 0-15 for bounce types)

    // C creature flags for rendering/animation mode
    // 0x04 = bounce walk (flag & 4), 0x10 = plasma shooter, 0x40 = override to linear,
    // 0x80 = fast type, 0x100 = minigun shooter
    public creatureFlags: number = 0;

    // Health
    public health: number;
    public maxHealth: number;

    // Properties
    public type: EnemyType;
    public active: boolean = true;
    public damage: number; // Damage dealt to player on contact
    public size: number; // Visual size (from C: 44-63)
    public rewardValue: number; // XP reward on death

    // Color tinting (from C)
    public tintR: number = 1.0;
    public tintG: number = 1.0;
    public tintB: number = 1.0;
    public tintA: number = 1.0;

    // Hit feedback (from C line 18916)
    public hitFlashTimer: number = 0;
    // Green flash for radioactive damage (C lines 21661-21679 VFX)
    public radioactiveFlashTimer: number = 0;

    // Velocity/impulse (from C line 18965-18966)
    public velX: number = 0;
    public velY: number = 0;

    // AI targeting properties (C code: creature_pool @ lines 21630-21800)
    public targetPlayerId: number = 0;
    public attackCooldown: number = 0;
    public collisionTimer: number = 0; // For radioactive perk damage cooldown
    public heading: number = 0; // Direction enemy is facing (radians)
    public isFrozen: boolean = false; // For freeze bonus timer

    // Enemy flags (from C creature_pool flags)
    public canShootPlasma: boolean = false; // flag & 0x10
    public canShootMinigun: boolean = false; // flag & 0x100

    // Projectile attack properties
    public id: number = 0; // Enemy ID for projectile ownership
    public attackRange: number = 200; // Maximum attack distance
    public projectileDamage: number = 10; // Damage dealt by projectiles
    public projectileSpeed: number = 150; // Speed of fired projectiles
    public fireRate: number = 2.0; // Seconds between shots

    // Poison status (C lines 21734-21743)
    public isPoisoned: boolean = false;
    public poisonStrength: number = 0; // 1 = weak, 3 = strong
    public poisonTimer: number = 0.0; // Duration of poison effect

    // Blood flag (C creature.flags & 4, line 21820)
    public hasBlood: boolean = true; // Most enemies have blood

    // Death animation state (C: creature_handle_death with keep_corpse)
    public isDying: boolean = false;
    public deathTimer: number = 0;
    // C code: hitbox_size starts at 16, decrements on death and continued hits
    // >= 16: alive, 0-16: death animation frames, < 0: corpse fade, < -10: deactivate
    public hitboxSize: number = 16.0;

    // State flag (C line 21666)
    public stateFlag: number = 0; // 0x01 when taking radioactive damage

    // Advanced AI properties (C lines 21222-21800)
    public aiMode: AIMode = AIMode.CHASE_CIRCLE; // AI behavior mode
    public targetX: number = 0; // Target position X
    public targetY: number = 0; // Target position Y
    public phaseSeed: number = 0; // For circular movement (C line 21383)
    public linkIndex: number = -1; // Index of leader enemy (for formations)
    public targetOffsetX: number = 0; // Offset from leader (C line 21438)
    public targetOffsetY: number = 0; // Offset from leader (C line 21439)
    public collisionFlag: boolean = false; // Touch damage active (C line 21360)
    public flags: number = 0; // Damage flags: 0x01=poison, 0x02=burning (C lines 21277-21292)

    // C: bonus_spawn_guard — transient flag set when killed by a chain/fireblast projectile
    public noBonusDrop: boolean = false;

    // Force-target override (C line 1382-1394)
    public forceTarget: boolean = false;

    // Orbit fields for AI mode 6 and minigun cooldown (C lines 1365-1377, 1548)
    public orbitAngle: number = 0;
    public orbitRadius: number = 0;
    public projectileType: number = 0; // Minigun projectile type (C line 1544)

    // Spawner slot fields (C: creature_spawn_slot_table)
    // Used by nest/turret/sentinel templates that periodically spawn child enemies
    public isNestSpawner: boolean = false;
    public nestSpawnTimer: number = 0; // Current timer (seconds)
    public nestSpawnInterval: number = 0; // Seconds between spawns
    public nestChildTemplate: number = 0; // Template ID of children to spawn
    public nestSpawnLimit: number = 100; // Max children
    public nestSpawnCount: number = 0; // Current spawned count

    constructor(x: number, y: number, type: EnemyType = EnemyType.Zombie) {
        this.x = x;
        this.y = y;
        this.type = type;

        // Default values - will be overridden by spawn function
        this.maxSpeed = 30;
        this.maxHealth = 20;
        this.damage = 5;
        this.size = 50;
        this.rewardValue = 10;

        this.speed = this.maxSpeed;
        this.health = this.maxHealth;
    }

    /**
     * Apply experience-based scaling to enemy stats (C lines 5104-5160)
     * Must be called after construction to scale difficulty based on player XP
     */
    applyXPScaling(playerXP: number): void {
        // Move speed scaling (C line 5104)
        // Formula: (xp / 4000) * 0.045 + 0.9
        const baseSpeed = (playerXP / 4000) * 0.045 + 0.9;
        this.maxSpeed = baseSpeed * 30.0; // Convert to pixel speed (C: move_speed * 30.0)

        // Type-specific speed modifiers (C lines 5105-5119)
        if (this.type === EnemyType.Spider2) {
            // C type 3: 30% faster, flag 0x80 (C lines 5107-5108)
            this.maxSpeed *= 1.3;
            this.creatureFlags |= 0x80;
        } else if (this.type === EnemyType.Zombie) {
            // C type 0: 40% slower, min 1.3 (C lines 5115-5119)
            this.maxSpeed *= 0.6;
            const minSpeed = 1.3 * 30.0;
            if (this.maxSpeed < minSpeed) {
                this.maxSpeed = minSpeed;
            }
        }

        // Cap at 3.5 (C lines 5122-5124)
        const maxSpeedCap = 3.5 * 30.0;
        if (this.maxSpeed > maxSpeedCap) {
            this.maxSpeed = maxSpeedCap;
        }

        this.speed = this.maxSpeed;

        // Health scaling (C lines 5112-5113)
        // Formula: xp * 0.00125 + random(0-15) + 52.0
        const randomHealth = Math.floor(Math.random() * 16); // 0-15
        this.health = playerXP * 0.00125 + randomHealth + 52.0;

        // C type 0 (Zombie): 50% more health (C line 5120)
        if (this.type === EnemyType.Zombie) {
            this.health *= 1.5;
        }

        this.maxHealth = this.health;

        // Tint color scaling based on XP tier (C lines 5127-5160)
        if (playerXP < 50000) {
            // Tier 1: 0-50k XP (C lines 5127-5135)
            this.tintR = 1.0 - 1.0 / (playerXP / 1000 + 10.0);
            this.tintG = Math.random() * 0.1 + 0.9 - 1.0 / (playerXP / 10000 + 10.0);
            this.tintB = Math.random() * 0.1 + 0.7;
        } else if (playerXP < 100000) {
            // Tier 2: 50k-100k XP (C lines 5137-5146)
            this.tintR = 0.9 - 1.0 / (playerXP / 1000 + 10.0);
            this.tintG = Math.random() * 0.1 + 0.8 - 1.0 / (playerXP / 10000 + 10.0);
            this.tintB = (playerXP - 50000) * 0.000006 + Math.random() * 0.1 + 0.7;
        } else {
            // Tier 3: 100k+ XP (C lines 5148-5160)
            this.tintR = 1.0 - 1.0 / (playerXP / 1000 + 10.0);
            this.tintG = Math.random() * 0.1 + 0.9 - 1.0 / (playerXP / 10000 + 10.0);
            this.tintB = Math.random() * 0.1 + 1.0 - (playerXP - 100000) * 0.000003;

            // Cap tint_b at 0.5 minimum (C lines 5159-5160)
            if (this.tintB < 0.5) {
                this.tintB = 0.5;
            }
        }
    }

    /**
     * Get collision radius (based on size)
     */
    getRadius(): number {
        return this.size * 0.14285715 + 3.0; // C: creature_find_in_radius formula (size / 7 + 3)
    }

    /**
     * Smoothly rotate current angle toward target angle at given rate.
     * Exact port of C angle_approach (math.c L119-169).
     *
     * Key: C multiplies by frame_dt INSIDE this function (L154),
     * so the 1.0 cap means max angular *input* is 1.0, and actual
     * delta per frame = dt * min(shortestArc, 1.0) * rate.
     */
    static angleApproach(current: number, target: number, rate: number, dt: number): number {
        const TWO_PI = 6.2831855; // C: 6.2831855
        // Normalize current to [0, 2π] (C L127-135)
        let angle = current;
        while (angle < 0.0) angle += TWO_PI;
        while (angle > TWO_PI) angle -= TWO_PI;

        // Direct arc distance (C L136)
        const directDist = Math.abs(target - angle);
        // Wrap-around arc distance (C L138-145)
        const maxA = Math.max(angle, target);
        const minA = Math.min(angle, target);
        const wrapDist = Math.abs((TWO_PI - maxA) + minA);

        // Shortest arc, capped at 1.0 radian (C L147-151)
        let arcLen = Math.min(directDist, wrapDist);
        if (arcLen > 1.0) arcLen = 1.0;

        // Delta = dt * arcLen * rate (C L154, L161)
        const delta = dt * arcLen * rate;

        // Apply in correct direction (C L153-167)
        if (directDist <= wrapDist) {
            // Shorter via direct path
            if (angle < target) {
                return angle + delta;
            } else {
                return angle - delta;
            }
        } else {
            // Shorter via wrap-around
            if (target < angle) {
                return angle + delta;
            } else {
                return angle - delta;
            }
        }
    }

    /**
     * Update enemy AI and movement
     * C code: creature_update_all lines 1406-1454 (movement), 1475-1500 (animation)
     */
    update(dt: number, playerX: number, playerY: number, player?: any): void {
        if (!this.active) return;

        // Skip update if frozen (C line 21270)
        if (player?.freezeTimer > 0) {
            return;
        }

        // Spider stop-and-go timer (C creatures.c L1147-1166)
        // When flag 0x80 is set, linkIndex acts as ms timer cycling move/hold phases:
        //   linkIndex < 0 (move phase): enemy moves, timer increments toward 0.
        //     When reaching 0: set ai_mode=7 (BURROW=hold), start positive timer.
        //   linkIndex >= 0 (hold/stop phase): timer decrements toward 0.
        //     When reaching 0: start negative (move) timer. ai_mode cleared by EnemyAI.
        if ((this.creatureFlags & 0x80) !== 0) {
            const dtMs = dt * 1000; // C uses frame_dt_ms (integer milliseconds)
            if (this.linkIndex < 0) {
                // Move phase: counting up toward 0
                this.linkIndex += dtMs;
                if (this.linkIndex >= 0) {
                    this.aiMode = AIMode.BURROW; // ai_mode = 7: hold still
                    this.linkIndex = (Math.floor(Math.random() * 512)) + 500; // (rand & 0x1ff) + 500
                }
            } else {
                // Hold/stop phase (or initial state at 0): counting down
                this.linkIndex -= dtMs;
                if (this.linkIndex < 1) {
                    // Start move phase with random negative timer
                    this.linkIndex = -700 - Math.floor(Math.random() * 1024); // -700 - (rand & 0x3ff)
                }
            }
        }

        // Decrement hit flash timer
        if (this.hitFlashTimer > 0) {
            this.hitFlashTimer -= dt;
            if (this.hitFlashTimer < 0) this.hitFlashTimer = 0;
        }
        // Decrement radioactive flash timer
        if (this.radioactiveFlashTimer > 0) {
            this.radioactiveFlashTimer -= dt;
            if (this.radioactiveFlashTimer < 0) this.radioactiveFlashTimer = 0;
        }

        // Use AI-calculated target position (set by EnemySpawner via calculateAITarget)
        // If targetX/Y are not set (0,0), fall back to chasing player directly
        let targetX = this.targetX;
        let targetY = this.targetY;

        if (targetX === 0 && targetY === 0) {
            targetX = playerX;
            targetY = playerY;
        }

        // C move_speed is in world units (~1/30 of our pixel speed)
        const cMoveSpeed = this.speed / 30.0;

        // Near-target slowdown factor — default 1.0, computed in movement block
        let speedFactor = 1.0;

        // C creatures.c:1406-1440 — spawner enemies (flag &4) are stationary
        // Unless flag &0x40 is also set (override to linear movement)
        if ((this.creatureFlags & 4) !== 0 && (this.creatureFlags & 0x40) === 0) {
            // Spawner: no movement, zero velocities (C lines 1437-1439)
            this.velX = 0;
            this.velY = 0;
            // Clamp position to map bounds (C lines 1424-1436)
            if (this.x < this.size) this.x = this.size;
            if (this.y < this.size) this.y = this.size;
            const maxCoord = 1024 - this.size;
            if (this.x > maxCoord) this.x = maxCoord;
            if (this.y > maxCoord) this.y = maxCoord;
        } else {
            // C line 1407: skip movement for ai_mode=7 (hold/orbiter during hold phase)
            if (this.aiMode !== AIMode.BURROW) {
                // Calculate direction to target
                const dx = targetX - this.x;
                const dy = targetY - this.y;
                const distance = Math.sqrt(dx * dx + dy * dy);

                // Near-target slowdown factor (C lines 1312-1313)
                // Fix 11: C only applies this for mode 5 (LINKED_TO_LEADER)
                if (this.aiMode === AIMode.LINKED_TO_LEADER && distance < 64.0) {
                    speedFactor = distance * 0.015625; // 1/64
                }

                if (distance > 0) {
                    // Fix 1: Heading-based turning (C lines 1406-1420)
                    // Compute target heading with C's +PI/2 offset
                    const targetHeading = Math.atan2(dy, dx) + Math.PI / 2;

                    // Gradually turn toward target (C: angle_approach)
                    this.heading = Enemy.angleApproach(this.heading, targetHeading, cMoveSpeed * 0.33333334 * 4.0, dt);

                    // Compute velocity from heading (C lines 1412-1419)
                    const moveAngle = this.heading - Math.PI / 2;
                    this.velX = Math.cos(moveAngle) * dt * speedFactor * cMoveSpeed * 30.0;
                    this.velY = Math.sin(moveAngle) * dt * speedFactor * cMoveSpeed * 30.0;

                    // Apply position (C: vec2_add_inplace, line 1420)
                    this.x += this.velX;
                    this.y += this.velY;

                    // Set rendering angle from heading
                    this.angle = moveAngle;
                }
            }
        }

        // C-accurate anim_phase update (creatures.c L1475-1500)
        // C formula: anim_rate * move_speed * dt * (30/size) * speed_factor * multiplier
        // Branch uses per-creature runtime flags (not static type animFlags)
        const animRate = CREATURE_TYPE_TABLE[this.type]?.animRate ?? 1.0;
        const sizeFactor = 30.0 / this.size;

        if ((this.creatureFlags & 4) === 0 || (this.creatureFlags & 0x40) !== 0) {
            // LINEAR path (C lines 1476-1487): multiplier 25.0, wrap at 31.0
            // C line 1478: skip anim for ai_mode=7 (hold/orbiter) during hold phase
            if (this.aiMode !== AIMode.BURROW) {
                this.animPhase += animRate * cMoveSpeed * dt * sizeFactor * speedFactor * 25.0;
                while (this.animPhase > 31.0) {
                    this.animPhase -= 31.0;
                }
            }
        } else {
            // SPAWNER/BOUNCE path (C lines 1489-1500): multiplier 22.0, wrap at 15.0
            this.animPhase += animRate * cMoveSpeed * dt * sizeFactor * speedFactor * 22.0;
            while (this.animPhase > 15.0) {
                this.animPhase -= 15.0;
            }
        }
    }

    /**
     * Take damage (port of creature_apply_damage from C line 18907)
     */
    takeDamage(
        amount: number,
        damageType: number = 1, // 1 = bullet (default)
        impulseX: number = 0,
        impulseY: number = 0,
        perkSystem?: any, // PerkSystem, optional for now
        player?: any, // Player, for energizer check
    ): void {
        // Energizer instant-kill (C line 21547)
        if (player?.energizerTimer > 0 && this.maxHealth < 380) {
            this.health = 0;
            this.isDying = true;
            this.deathTimer = 0;
            // Double impulse on death
            this.velX -= impulseX * 2;
            this.velY -= impulseY * 2;
            // Award XP on energizer kill (Fix 12)
            this._awardKillXP(perkSystem, player);
            return; // Skip normal damage processing
        }

        // Set hit flash timer (C line 18916)
        this.hitFlashTimer = 0.2;

        let damage = amount;

        // Apply perk modifiers (C creature_apply_damage lines 918-962)
        if (perkSystem) {
            // Bullet damage modifiers (C line 18917-18941)
            if (damageType === 1) {
                // BULLET
                // Uranium filled bullets: +100% (C line 918-921)
                if (perkSystem.hasPerk?.(PerkId.URANIUM_FILLED_BULLETS)) {
                    damage = damage + damage; // +100%
                }

                // Living Fortress: scale damage by stationary timer (C lines 944-955)
                if (perkSystem.hasPerk?.(PerkId.LIVING_FORTRESS) && player) {
                    if (player.health > 0) {
                        damage = (player.livingFortressTimer * 0.05 + 1.0) * damage;
                    }
                }

                // Barrel greaser: +40% (C line 934-937)
                if (perkSystem.hasPerk?.(PerkId.BARREL_GREASER)) {
                    damage = damage * 1.4;
                }
                // Doctor: +20% (C line 938-941)
                if (perkSystem.hasPerk?.(PerkId.DOCTOR)) {
                    damage = damage * 1.2;
                }
            }
            // Fire damage modifier (C line 960-962)
            else if (damageType === 4) {
                // FIRE
                // Pyromaniac: +50% (C line 960-962)
                if (perkSystem.hasPerk?.(PerkId.PYROMANIAC)) {
                    damage = damage * 1.5;
                }
            }
            // Ion damage modifier (C line 952-954)
            else if (damageType === 7) {
                // ION
                // Ion gun master: +20% (C line 952-954)
                if (perkSystem.hasPerk?.(PerkId.ION_GUN_MASTER)) {
                    damage = damage * 1.2;
                }
            }
        }

        // Heading stagger on bullet hit (C creature_apply_damage lines 964-972)
        if (damageType === 1 && (this.flags & 4) === 0) {
            const randVal = ((Math.floor(Math.random() * 128) - 64) * 0.002) / (this.size * 0.025);
            const clamped = Math.min(randVal, Math.PI / 2);
            this.heading += clamped;
        }

        // Apply damage (C line 964)
        this.health -= damage;

        // Apply impulse/knockback (C line 965-966)
        this.velX -= impulseX;
        this.velY -= impulseY;

        // Handle death (C line 967-974)
        if (this.health <= 0) {
            this.health = 0;
            this.isDying = true;
            this.deathTimer = 0;

            // Double impulse on death (C line 972-974)
            this.velX -= impulseX * 2;
            this.velY -= impulseY * 2;

            // Award XP on kill — route all kills through here (Fix 12)
            this._awardKillXP(perkSystem, player);
        }
    }

    /**
     * Award XP on kill — C creature_handle_death lines 770-787 (Fix 12)
     * Routes all kill XP through this single method (bullet, poison, burning, plague, radioactive).
     *
     * XP always accumulates (ADD). The decompiled C code shows SET (`experience = value`)
     * for the non-Bloody-Mess path, but this is a Ghidra x87 FPU decompilation artifact —
     * the FPU ADD is lost when tracking the __ftol() conversion. Evidence:
     *   - All integer-arithmetic XP ops (Lean Mean, Instant Winner, bonuses) correctly show ADD
     *   - Only __ftol()-based ops show SET (creature kills, Jinxed, energizer)
     *   - Game would be unplayable without XP accumulation (threshold 2000+, rewards 50-600)
     *   - Bloody Mess is documented as "30% more XP" multiplier, not a SET/ADD toggle
     */
    private _awardKillXP(perkSystem?: any, player?: any): void {
        if (!player) return;

        const baseXP = Math.floor(this.rewardValue);
        const hasBloodyMess = perkSystem?.hasPerk?.(PerkId.BLOODY_MESS) ?? false;

        // Bloody Mess: 30% XP bonus per kill (C: "guarantees a 30% better experience")
        const bloodyMult = hasBloodyMess ? 1.3 : 1.0;
        const xpGain = Math.floor(baseXP * bloodyMult);
        player.experience += xpGain;

        // Double XP timer: C creatures.c:779-787
        // Awards the same XP again, effectively doubling the kill reward
        if (player.doubleXPTimer > 0) {
            player.experience += xpGain;
        }
    }
    /**
     * Check if enemy should fire projectile
     */
    shouldFireProjectile(playerX: number, playerY: number): boolean {
        // Only enemies with plasma/minigun can fire
        if (!this.canShootPlasma && !this.canShootMinigun) return false;

        // Check attack cooldown
        if (this.attackCooldown > 0) return false;

        // Calculate distance to player
        const dx = playerX - this.x;
        const dy = playerY - this.y;
        const distance = Math.sqrt(dx * dx + dy * dy);

        // Check if in range (not too far, not too close)
        if (distance > this.attackRange) return false;
        if (distance < 50) return false; // Too close, use melee instead

        return true;
    }

    /**
     * Fire projectile at player
     * Returns projectile data for spawning
     */
    fireProjectile(
        playerX: number,
        playerY: number,
    ): { x: number; y: number; vx: number; vy: number; damage: number; ownerId: number } {
        // Calculate angle to player
        const dx = playerX - this.x;
        const dy = playerY - this.y;
        const angle = Math.atan2(dy, dx);

        // Calculate velocity
        const vx = Math.cos(angle) * this.projectileSpeed;
        const vy = Math.sin(angle) * this.projectileSpeed;

        // Set attack cooldown
        this.attackCooldown = this.fireRate;

        // Return projectile data
        return {
            x: this.x,
            y: this.y,
            vx,
            vy,
            damage: this.projectileDamage,
            ownerId: this.id,
        };
    }

    /**
     * Check if enemy is alive (excludes dying enemies)
     */
    isAlive(): boolean {
        return this.active && this.health > 0 && !this.isDying;
    }

    /**
     * Check if enemy should be rendered (alive OR dying)
     */
    shouldRender(): boolean {
        return this.active && (this.isAlive() || this.isDying);
    }

    /**
     * Apply projectile hit to a dying enemy's corpse.
     * C code: creature_apply_damage line 977-979
     * hitbox_size -= frame_dt * 15 per hit
     */
    hitCorpse(dt: number): void {
        if (!this.isDying) return;
        this.hitboxSize -= dt * 15.0;
    }

    /**
     * Update death animation. Returns true when enemy is fully deactivated.
     *
     * C code lifecycle driven by hitboxSize:
     * - hitboxSize 16→0: death animation (16 frames)
     * - hitboxSize 0→-10: corpse with alpha fade
     * - hitboxSize < -10: deactivate
     *
     * hitboxSize decrements passively by dt each frame,
     * and additionally by dt*15 per projectile hit (via hitCorpse).
     */
    updateDeath(dt: number): boolean {
        if (!this.isDying) return false;

        this.deathTimer += dt;

        // Two-phase hitbox decrement matching C creatures.c:
        // L1622: death animation phase (hitboxSize > 0): fast fade
        // L1619: corpse fade phase (hitboxSize <= 0): slower fade
        if (this.hitboxSize > 0) {
            this.hitboxSize -= dt * 28.0; // C L1622: death animation phase
        } else {
            this.hitboxSize -= dt * 20.0; // C L1619: corpse fade phase
        }

        // C L1622-1641: heading-based linear slide while hitboxSize > 0
        // ONLY for linear-type enemies (flags & 4 == 0 || flags & 0x40 != 0)
        // Bounce-type enemies (flags & 4, no 0x40) get vel=0 (no slide)
        if (this.hitboxSize > 0) {
            if ((this.creatureFlags & 4) === 0 || (this.creatureFlags & 0x40) !== 0) {
                const moveAngle = this.heading - Math.PI / 2;
                const slideSpeed = this.hitboxSize * dt * 9.0;
                this.x -= Math.cos(moveAngle) * slideSpeed;
                this.y -= Math.sin(moveAngle) * slideSpeed;
            }
        }

        // C code: deactivate when hitbox_size < -10 (render line 407)
        if (this.hitboxSize < -10.0) {
            this.active = false;
            return true; // Signal to bake corpse debris
        }
        return false;
    }

    /**
     * Render enemy
     * @param grim - Graphics interface
     * @param _perkSystem - Unused (Monster Vision glow handled by EntityRenderer.drawMonsterVisionGlow)
     * @param spriteRenderer - Optional sprite renderer for textured rendering
     * @param debugMode - If true, always use debug (circle/line) rendering
     */
    render(grim: GrimInterface, _perkSystem?: any, spriteRenderer?: any, debugMode: boolean = true, player?: any): void {
        if (!this.shouldRender()) return;

        const radius = this.getRadius();

        // Use sprite rendering if available and not in debug mode
        const useSprites = spriteRenderer && !debugMode && spriteRenderer.canDrawEnemy();

        if (useSprites) {
            // Sprite rendering mode — pass per-type animation data
            spriteRenderer.drawEnemy(
                grim,
                this.x,
                this.y,
                this.angle,
                this.size,
                { r: this.tintR, g: this.tintG, b: this.tintB },
                this.hitFlashTimer,
                this.animPhase,
                this.isDying,
                this.hitboxSize,
                this.type,
                this.creatureFlags,
                player?.energizerTimer ?? 0, // Fix 5: energizer tint override
                this.maxHealth,
                this.radioactiveFlashTimer,
            );
        } else {
            // Debug rendering mode (circles and lines)
            // Draw body with tint color (from C)
            // If hit flash is active, blend toward white
            let r = this.tintR;
            let g = this.tintG;
            let b = this.tintB;

            if (this.hitFlashTimer > 0) {
                // Flash white (interpolate toward 1.0)
                const flashAmount = this.hitFlashTimer / 0.2; // 0.2 is max timer
                r = r + (1.0 - r) * flashAmount;
                g = g + (1.0 - g) * flashAmount;
                b = b + (1.0 - b) * flashAmount;
            }

            grim.setColor(Math.floor(r * 255), Math.floor(g * 255), Math.floor(b * 255), 255);
            grim.drawCircleFilled(this.x, this.y, radius);

            // Draw direction indicator (darker)
            const lineLength = radius * 1.2;
            const endX = this.x + Math.cos(this.angle) * lineLength;
            const endY = this.y + Math.sin(this.angle) * lineLength;
            grim.setColor(
                Math.floor(this.tintR * 128),
                Math.floor(this.tintG * 128),
                Math.floor(this.tintB * 128),
                255,
            );
            grim.drawLine(this.x, this.y, endX, endY, 2);
        }

        // Monster Vision glow is handled by drawMonsterVisionGlow() in EntityRenderer.ts
        // (yellow additive glow disc under enemies, no health bars — matching C code)

        // Doctor perk: Show health bar on crosshair-targeted enemy (C lines 556-566)
        // C sets doctor_perk_target_creature which causes a health bar to render on that enemy
        if (player?.doctorTarget === this) {
            this.renderDoctorHealthBar(grim);
        }
    }


    /**
     * Render Doctor perk health bar below enemy.
     * C code: doctor_perk_target_creature triggers a health bar on the targeted enemy.
     * Positioned below the enemy (unlike Monster Vision which is above).
     */
    renderDoctorHealthBar(grim: GrimInterface): void {
        // Health bar dimensions — proportional to enemy size
        const barWidth = Math.max(this.size * 1.2, 24);
        const barHeight = 4;
        const barX = this.x - barWidth / 2;
        const barY = this.y + this.size * 0.14285715 + 6; // Below the enemy

        // Calculate alpha based on death state
        let alpha = 1.0;
        if (this.isDying) {
            alpha = (this.hitboxSize + 10.0) * 0.1;
            if (alpha > 1.0) alpha = 1.0;
            if (alpha < 0.0) alpha = 0.0;
        }

        // Background bar (dark, semi-transparent)
        grim.setColor(0, 0, 0, Math.floor(160 * alpha));
        grim.drawRectFilled(barX - 1, barY - 1, barWidth + 2, barHeight + 2);

        // Health fill — green→yellow→red based on health %
        const healthPct = Math.max(0, Math.min(1, this.health / this.maxHealth));
        const fillWidth = barWidth * healthPct;

        // Color: green at 100%, yellow at 50%, red at 0%
        let r: number, g: number;
        if (healthPct > 0.5) {
            // Green → Yellow
            r = Math.floor((1.0 - (healthPct - 0.5) * 2) * 255);
            g = 255;
        } else {
            // Yellow → Red
            r = 255;
            g = Math.floor(healthPct * 2 * 255);
        }

        grim.setColor(r, g, 0, Math.floor(220 * alpha));
        if (fillWidth > 0) {
            grim.drawRectFilled(barX, barY, fillWidth, barHeight);
        }
    }
}
