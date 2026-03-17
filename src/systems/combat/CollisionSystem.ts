/**
 * CollisionSystem - Collision detection and response
 *
 * Handles circle-circle collision detection for projectiles, enemies, and player.
 */

import type { Player } from '../../entities/Player';
import type { Enemy } from '../../entities/Enemy';
import { EnemyType } from '../../entities/Enemy';
import type { Projectile } from '../../entities/Projectile';
import { ProjectileType } from '../../data/WeaponData';
import { PerkId } from '../PerkSystem';
import type { EnemyDeathEffects } from '../enemy/EnemyDeathEffects';
import type { BloodEffectSystem } from '../effects/BloodEffectSystem';
import type { EffectSystem } from '../effects/EffectSystem';
import type { SoundSystem } from '../../audio/SoundSystem';
import type { ScoreSystem } from '../ScoreSystem';
import { SoundId, getRandomDeathSound } from '../../audio/SoundId';
import { questSystem } from '../quest/QuestSystem';
import { getPlaguebearerInfectionCount } from '../enemy/EnemySystemsUpdate';

/**
 * Collision system
 */
export class CollisionSystem {
    private soundSystem: SoundSystem | null = null;
    private enemyDeathEffects: EnemyDeathEffects | null = null;
    private bloodEffectSystem: BloodEffectSystem | null = null;
    private effectSystem: EffectSystem | null = null;
    private scoreSystem: ScoreSystem | null = null;

    /**
     * Set sound system reference
     */
    setSoundSystem(soundSystem: SoundSystem): void {
        this.soundSystem = soundSystem;
    }

    /**
     * Set enemy death effects system reference
     */
    setEnemyDeathEffects(effects: EnemyDeathEffects): void {
        this.enemyDeathEffects = effects;
    }

    /**
     * Set blood effect system reference for per-hit blood spawning
     */
    setBloodEffectSystem(bloodSystem: BloodEffectSystem): void {
        this.bloodEffectSystem = bloodSystem;
    }

    /**
     * Set effect system reference for on-hit visual effects
     */
    setEffectSystem(effectSystem: EffectSystem): void {
        this.effectSystem = effectSystem;
    }

    /**
     * Set score system reference for hit accuracy tracking
     */
    setScoreSystem(scoreSystem: ScoreSystem): void {
        this.scoreSystem = scoreSystem;
    }
    /**
     * Check circle-circle collision
     */
    private checkCircleCollision(x1: number, y1: number, r1: number, x2: number, y2: number, r2: number): boolean {
        const dx = x2 - x1;
        const dy = y2 - y1;
        const distanceSquared = dx * dx + dy * dy;
        const radiusSum = r1 + r2;
        return distanceSquared < radiusSum * radiusSum;
    }

    /**
     * Check projectile hits against enemies
     * Returns array of enemies that were killed
     */
    checkProjectileHits(
        projectiles: Projectile[],
        enemies: Enemy[],
        player: Player,
        perkSystem?: any,
        onProjectileHit?: (projectile: Projectile, enemy: Enemy) => void,
        onSpawnProjectile?: (x: number, y: number, angle: number, type: ProjectileType) => void,
    ): Enemy[] {
        const killedEnemies: Enemy[] = [];

        for (const projectile of projectiles) {
            if (!projectile.isActive()) continue;
            // C: exploding rockets are in AoE phase — skip direct collision checks
            if (projectile.isExploding) continue;
            // C: projectiles in fading phase (lifetime < 0.4) don't run collision detection.
            // Ion weapons deal AoE radius damage during fading (handled in Projectile.update),
            // so they must NOT also get hit-detected here. Rockets use isExploding flag instead.
            if (!projectile.isRocket && projectile.lifetime < 0.4) continue;

            // Check non-enemy projectiles (ownerId < 0: player = -1, bonus = -100)
            // Enemy projectiles (ownerId >= 0) are handled by checkEnemyProjectileHits
            // Chain lightning projectiles use ownerId >= 0 to mark the source enemy to skip
            if (projectile.ownerId < 0 || (projectile as any).isChainLightning) {
                // Player projectiles (and chain lightning) - check against enemies
                for (const enemy of enemies) {
                    // Skip the source enemy for chain lightning projectiles
                    // C: projectile_spawn passes hit enemy index as owner, collision skips owner
                    if ((projectile as any).isChainLightning && projectile.ownerId >= 0) {
                        if (enemies.indexOf(enemy) === projectile.ownerId) continue;
                    }
                    if (!enemy.isAlive()) {
                        // C: secondary projectiles (rockets) are in a separate pool and
                        // NEVER interact with corpses. Skip corpse-hit for all rocket types
                        // to prevent damagePool depletion before reaching alive enemies.
                        const isRocketCorpseSkip =
                            projectile.projectileType === ProjectileType.ROCKET ||
                            projectile.projectileType === ProjectileType.SEEKER_ROCKET ||
                            projectile.projectileType === ProjectileType.ROCKET_MINIGUN;
                        if (isRocketCorpseSkip) continue;

                        // C code: projectiles can hit dying enemies to speed up death animation
                        // creature_apply_damage line 977-979: hitbox_size -= frame_dt * 15
                        if (enemy.isDying && enemy.active) {
                            if (
                                this.checkCircleCollision(
                                    projectile.x,
                                    projectile.y,
                                    projectile.hitRadius,
                                    enemy.x,
                                    enemy.y,
                                    enemy.getRadius(),
                                )
                            ) {
                                enemy.hitCorpse(1 / 60); // ~frame_dt estimate
                                // DamagePool penetration: subtract from pool (corpses cost 1)
                                projectile.damagePool -= 1;
                                if (projectile.damagePool <= 0) {
                                    projectile.lifetime = 0.25; // Start dying
                                    projectile.active = false;
                                }
                                // Blood on corpse hit
                                if (this.bloodEffectSystem && enemy.hasBlood) {
                                    const bloodAngle = projectile.angle - Math.PI / 2;
                                    this.bloodEffectSystem.spawnBloodSplatter(enemy.x, enemy.y, bloodAngle, 0.0);
                                }
                                if (!projectile.isActive()) break;
                            }
                        }
                        continue;
                    }

                    // Don't check alive enemies with an already-consumed projectile
                    if (!projectile.isActive()) break;

                    // Check collision — Fix #4: use projectile.hitRadius instead of hardcoded 3
                    if (
                        this.checkCircleCollision(
                            projectile.x,
                            projectile.y,
                            projectile.hitRadius,
                            enemy.x,
                            enemy.y,
                            enemy.getRadius(),
                        )
                    ) {
                        // Track hit accuracy: record once per projectile (not per enemy for penetrating weapons)
                        if (!projectile.hasRecordedHit) {
                            projectile.hasRecordedHit = true;
                            this.scoreSystem?.recordHit();
                        }
                        // C: uses angle - PI/2 to convert projectile angle to world direction vector
                        // impulse[0] = cos(angle - PI/2) * speed_scale  (X component)
                        // impulse[1] = sin(angle - PI/2) * speed_scale  (Y component)
                        const impulseAngle = projectile.angle - Math.PI / 2;
                        const impulseX = Math.cos(impulseAngle) * (projectile.speedScale ?? 1.0);
                        const impulseY = Math.sin(impulseAngle) * (projectile.speedScale ?? 1.0);

                        // Calculate base damage using C formula when damageScale is set
                        // C projectiles.c line 453:
                        //   dist = sqrt((origin - hit)²); if (dist < 50) dist = 50;
                        //   damage = ((100 / dist) * damageScale * 30 + 10) * 0.95
                        let baseDamage: number;
                        if (projectile.damageScale > 0) {
                            const ox = projectile.originX - enemy.x;
                            const oy = projectile.originY - enemy.y;
                            let travelDist = Math.sqrt(ox * ox + oy * oy);
                            if (travelDist < 50) travelDist = 50; // C line 384-385
                            baseDamage = ((100 / travelDist) * projectile.damageScale * 30 + 10) * 0.95;
                        } else {
                            baseDamage = projectile.damage;
                        }

                        // Poison Bullets perk: 12.5% chance per hit to set poison flag (C projectiles.c lines 273-276)
                        if (perkSystem?.hasPerk(PerkId.POISON_BULLETS)) {
                            if (Math.floor(Math.random() * 8) === 1) {
                                enemy.flags |= 1; // Set poison flag (processed by burning/poison update loop)
                            }
                        }

                        // === DamagePool penetration (Fix 4, C projectiles.c lines 455-477) ===
                        // C: Rockets have SPECIAL on-hit behavior — they DON'T die.
                        // Instead they transition to EXPLODING state and deal AoE damage.
                        // C projectiles.c L804-863: type → EXPLODING, vel_y = scale, timer = 0
                        const isRocketType =
                            projectile.projectileType === ProjectileType.ROCKET ||
                            projectile.projectileType === ProjectileType.SEEKER_ROCKET ||
                            projectile.projectileType === ProjectileType.ROCKET_MINIGUN;

                        if (isRocketType) {
                            // Apply direct hit damage using C formula:
                            // ROCKET: lifetime * 50 + 500
                            // SEEKER: lifetime * 20 + 80
                            // MINIGUN: lifetime * 20 + 40
                            let rocketDamage: number;
                            if (projectile.projectileType === ProjectileType.ROCKET) {
                                rocketDamage = projectile.lifetime * 50.0 + 500.0;
                            } else if (projectile.projectileType === ProjectileType.SEEKER_ROCKET) {
                                rocketDamage = projectile.lifetime * 20.0 + 80.0;
                            } else {
                                rocketDamage = projectile.lifetime * 20.0 + 40.0;
                            }
                            enemy.takeDamage(rocketDamage, 3, impulseX, impulseY, perkSystem, player);

                            // Transition to EXPLODING state (C L804-836)
                            projectile.isExploding = true;
                            projectile.explosionTimer = 0;
                            projectile.vx = 0;
                            projectile.vy = 0;
                            // Scale per type: ROCKET=1.0, SEEKER=0.35, MINIGUN=0.25
                            if (projectile.projectileType === ProjectileType.ROCKET) {
                                projectile.explosionScale = 1.0;
                            } else if (projectile.projectileType === ProjectileType.SEEKER_ROCKET) {
                                projectile.explosionScale = 0.35;
                            } else {
                                projectile.explosionScale = 0.25;
                            }
                            // Rocket stays active — AoE damage handled in Projectile.update

                            // C L808-831: spawn blood debris splash on rocket impact
                            // ROCKET: 20 fx_queue_add_random, SEEKER: 10, MINIGUN: 3
                            if (this.bloodEffectSystem) {
                                let debrisCount = 10; // SEEKER default
                                if (projectile.projectileType === ProjectileType.ROCKET) debrisCount = 20;
                                else if (projectile.projectileType === ProjectileType.ROCKET_MINIGUN) debrisCount = 3;
                                for (let i = 0; i < debrisCount; i++) {
                                    // C: random position in circle around impact point
                                    const randAngle = Math.random() * 6.28;
                                    const randDist = Math.random() * 60;
                                    const debrisX = enemy.x + Math.cos(randAngle) * randDist;
                                    const debrisY = enemy.y + Math.sin(randAngle) * randDist;
                                    this.bloodEffectSystem.addRandomGroundDebris(debrisX, debrisY);
                                }
                            }
                        } else {
                            // Normal projectile damagePool logic
                            // C: damage_pool -= 1.0 per hit
                            projectile.damagePool -= 1.0;

                            if (projectile.damagePool <= 0) {
                                // Pool exhausted: apply full damage, start dying
                                enemy.takeDamage(baseDamage, 1, impulseX, impulseY, perkSystem, player);
                                projectile.lifetime = 0.25;
                                // C projectiles.c L460-467: ION projectiles do NOT deactivate —
                                // they enter fading phase (lifetime < 0.4) where they deal
                                // continuous AoE radius damage and render lightning bolts.
                                // Only non-ION projectiles deactivate immediately.
                                const isIonType =
                                    projectile.projectileType === ProjectileType.ION_RIFLE ||
                                    projectile.projectileType === ProjectileType.ION_MINIGUN ||
                                    projectile.projectileType === ProjectileType.ION_CANNON;
                                if (!isIonType) {
                                    projectile.active = false;
                                }
                            } else {
                                // Pool remaining: use pool value as damage, then subtract creature health
                                enemy.takeDamage(projectile.damagePool, 1, impulseX, impulseY, perkSystem, player);
                                projectile.damagePool -= enemy.health;
                            }
                        }



                        // Spawn blood on hit (C: projectiles.c L308-365)
                        // Per-hit blood splatter: flying particles in bullet direction
                        if (this.bloodEffectSystem && enemy.hasBlood) {
                            const hasBloodyMess = perkSystem?.hasPerk(PerkId.BLOODY_MESS) ?? false; // C: perk_id_bloody_mess_quick_learner = 1
                            const bloodAngle = projectile.angle - Math.PI / 2; // C: angle - 1.5707964

                            // Fix 3: Blade Gun special case — 8 full-circle splatters (C: projectiles.c L19498-19506)
                            // This fires BEFORE the normal/BloodyMess branch
                            if (projectile.projectileType === ProjectileType.BLADE_GUN) {
                                for (let i = 0; i < 8; i++) {
                                    const randAngle = Math.floor(Math.random() * 256) * 0.024543693;
                                    this.bloodEffectSystem.spawnBloodSplatter(enemy.x, enemy.y, randAngle, 0.0);
                                }
                            }

                            if (hasBloodyMess) {
                                // Bloody mess perk: 8 splatters + fx_queue_add_random debris
                                // C: projectiles.c L327-338
                                for (let i = 0; i < 8; i++) {
                                    const randOffset = (((Math.random() * 32) | 0) - 16) * 0.0625;
                                    this.bloodEffectSystem.spawnBloodSplatter(
                                        enemy.x,
                                        enemy.y,
                                        bloodAngle + randOffset,
                                        0.0,
                                    );
                                }
                                // Extra splatter in reverse direction
                                this.bloodEffectSystem.spawnBloodSplatter(enemy.x, enemy.y, bloodAngle + Math.PI, 0.0);
                                // Spread ground debris (C: L346-364)
                                let range = 30;
                                for (let j = 0; j < 4; j++) {
                                    const ox1 = ((Math.random() * range * 2) | 0) - range + enemy.x;
                                    const oy1 = ((Math.random() * range * 2) | 0) - range + enemy.y;
                                    this.bloodEffectSystem.addRandomGroundDebris(ox1, oy1);
                                    const ox2 = ((Math.random() * range * 2) | 0) - range + enemy.x;
                                    const oy2 = ((Math.random() * range * 2) | 0) - range + enemy.y;
                                    this.bloodEffectSystem.addRandomGroundDebris(ox2, oy2);
                                    range += 10;
                                }
                            } else {
                                // Fix 2: Normal per-hit blood is skipped when freeze bonus is active (C: projectiles.c L19531)
                                if (player.freezeTimer <= 0) {
                                    // Normal: 2 blood splatters (C: projectiles.c L312-323)
                                    for (let i = 0; i < 2; i++) {
                                        this.bloodEffectSystem.spawnBloodSplatter(enemy.x, enemy.y, bloodAngle, 0.0);
                                        // 1/8 chance extra reverse splatter (C: rand()&7 == 2)
                                        if (((Math.random() * 8) | 0) === 2) {
                                            this.bloodEffectSystem.spawnBloodSplatter(
                                                enemy.x,
                                                enemy.y,
                                                bloodAngle + Math.PI,
                                                0.0,
                                            );
                                        }
                                    }
                                    // Fix 1: Removed addRandomGroundDebris here — C does NOT spawn ground debris on normal hits
                                }
                            }
                        }

                        // Play bullet hit sound (C code: bullet impact sounds)
                        if (this.soundSystem) {
                            this.soundSystem.playAtPosition(
                                this.getBulletHitSound(projectile.projectileType),
                                enemy.x,
                                enemy.y,
                                800,
                            );
                            // C projectiles.c:431-432 — rockets additionally play sfx_shockwave
                            if (
                                projectile.projectileType === ProjectileType.ROCKET ||
                                projectile.projectileType === ProjectileType.SEEKER_ROCKET ||
                                projectile.projectileType === ProjectileType.ROCKET_MINIGUN
                            ) {
                                this.soundSystem.playAtPosition(SoundId.SHOCKWAVE, enemy.x, enemy.y, 800);
                                // C L780-782: effect_spawn_explosion_burst ONLY for standard ROCKET
                                // (gated by detail_preset > 2 in C; we always use high detail)
                                // Seeker and Minigun rockets do NOT get this multi-layer burst.
                                if (this.effectSystem) {
                                    if (projectile.projectileType === ProjectileType.ROCKET) {
                                        this.effectSystem.spawnExplosionBurst(enemy.x, enemy.y, 0.4);
                                    }
                                    // C L895-907: ALL rocket types spawn 10 sprite debris particles
                                    // on hit (14px sprites at 36° intervals, α=0.37)
                                    this.effectSystem.spawnRocketImpactDebris(enemy.x, enemy.y);
                                }
                            }
                        }

                        // Call projectile hit callback (for chain lightning, etc.)
                        if (onProjectileHit) {
                            onProjectileHit(projectile, enemy);
                        }

                        // === Fix #9: Type-specific on-hit behaviors (C projectiles.c L288-452) ===
                        this.applyOnHitBehavior(projectile, enemy, onSpawnProjectile);

                        // Play enemy death sound — C creature_apply_damage:997-1004
                        // Only on actual kill: sfx_bank_a[rand & 3] when health <= 0 && !(flags & 0x10)
                        if (!enemy.isAlive() && this.soundSystem) {
                            this.soundSystem.playAtPosition(this.getEnemyDeathSound(enemy), enemy.x, enemy.y, 800);
                        }

                        // Handle death effects (C lines 21818-21845)
                        if (this.enemyDeathEffects) {
                            this.enemyDeathEffects.handleEnemyDeath(enemy, null, true);
                        }

                        // Track kills — only count actual deaths, not mere hits
                        // Previously this pushed every hit enemy, causing quest
                        // activeEnemyCount to decrement on non-lethal hits
                        if (!enemy.isAlive()) {
                            // C: bonus_spawn_guard — tag enemy so kill loop skips bonus spawn
                            if (projectile.noBonusDrop) {
                                enemy.noBonusDrop = true;
                            }
                            killedEnemies.push(enemy);
                            // C creatures.c L792-804: spawn freeze shards on kill during active freeze
                            if (player.freezeTimer > 0 && this.effectSystem) {
                                for (let i = 0; i < 8; i++) {
                                    const randAngle = Math.floor(Math.random() * 0x264) * 0.01;
                                    this.effectSystem.spawnFreezeShard(enemy.x, enemy.y, randAngle);
                                }
                                const shatterAngle = Math.floor(Math.random() * 0x264) * 0.01;
                                this.effectSystem.spawnFreezeShatter(enemy.x, enemy.y, shatterAngle);
                                // C creatures.c:804 — fx_queue_add_random(pos) bakes debris to terrain
                                if (this.bloodEffectSystem) {
                                    this.bloodEffectSystem.addRandomGroundDebris(enemy.x, enemy.y);
                                }
                            }
                        }
                    }

                    // If projectile is depleted, stop checking enemies
                    if (!projectile.isActive()) break;
                    // Otherwise, projectile penetrates — continue checking more enemies
                }
            }
        }

        return killedEnemies;
    }

    /**
     * Apply type-specific on-hit behavior — Fix #9
     * C projectiles.c lines 288-452: each weapon type has unique post-hit effects
     */
    private applyOnHitBehavior(
        projectile: Projectile,
        enemy: Enemy,
        onSpawnProjectile?: (x: number, y: number, angle: number, type: ProjectileType) => void,
    ): void {
        const pType = projectile.projectileType;

        switch (pType) {
            case ProjectileType.SPLITTER_GUN:
                // C L288-293: Spawn 2 child projectiles at ±60° (1.0471976 rad)
                if (onSpawnProjectile) {
                    onSpawnProjectile(
                        projectile.x,
                        projectile.y,
                        projectile.angle - 1.0471976,
                        ProjectileType.SPLITTER_GUN,
                    );
                    onSpawnProjectile(
                        projectile.x,
                        projectile.y,
                        projectile.angle + 1.0471976,
                        ProjectileType.SPLITTER_GUN,
                    );
                }
                break;

            case ProjectileType.SHRINKIFIER:
                // C L436-443: Shrink enemy size by 0.65, kill via takeDamage if < 16 (Fix 13)
                enemy.size *= 0.65;
                projectile.lifetime = 0.25; // Force dying state
                if (enemy.size < 16.0) {
                    enemy.takeDamage(enemy.health + 1, 1); // Kill via takeDamage to trigger death handling
                }
                // C: effect_spawn_shrink_fx at shrink impact
                if (this.effectSystem) {
                    this.effectSystem.spawnShrinkFx(enemy.x, enemy.y);
                }
                break;

            case ProjectileType.PULSE_GUN:
                // C L445-448: Push enemy position by movement_delta * 3.0
                // C: local_cc = cos(angle-PI/2) * frame_dt * 20 * speed_scale * 3.0
                // Push = local_cc * 3.0 (proportional to actual per-frame movement)
                // TS: vx is px/s, so per-frame movement ≈ vx * (1/60). Push = that * 3.0
                enemy.x += projectile.vx * (1 / 60) * 3.0;
                enemy.y += projectile.vy * (1 / 60) * 3.0;
                break;

            case ProjectileType.PLAGUE_SPREADER:
                // C L450-451: Set collision flag — enemy becomes contagious
                enemy.collisionFlag = true;
                break;

            case ProjectileType.PLASMA_CANNON:
                // C L416-432: Spawn 12 radial plasma projectiles at 30° intervals
                // 0.5235988 rad = π/6 = 30°
                if (onSpawnProjectile) {
                    const spawnRadius = enemy.size * 0.5 + 1.0; // C: creature.size * 0.5 + 1.0
                    for (let i = 0; i < 12; i++) {
                        const radAngle = i * 0.5235988; // 30° increments
                        const sx = Math.cos(radAngle) * spawnRadius + projectile.x;
                        const sy = Math.sin(radAngle) * spawnRadius + projectile.y;
                        onSpawnProjectile(sx, sy, radAngle, ProjectileType.PLASMA_RIFLE);
                    }
                }
                // Play explosion sound
                if (this.soundSystem) {
                    this.soundSystem.playAtPosition(SoundId.EXPLOSION_MEDIUM, enemy.x, enemy.y, 800);
                    this.soundSystem.playAtPosition(SoundId.SHOCKWAVE, enemy.x, enemy.y, 800);
                }
                // C: fx_spawn_plasma_explosion at impact point
                if (this.effectSystem) {
                    this.effectSystem.spawnPlasmaExplosion(enemy.x, enemy.y, 1.0, 0.3);
                    this.effectSystem.spawnExplosionBurst(enemy.x, enemy.y, 1.5);
                }
                break;

            // Ion weapons: electric arc + shockwave VFX at impact (C L389-414)
            case ProjectileType.ION_MINIGUN:
                // C L389-393: fx_spawn_electric_arc(1.5, 0.1) + fx_spawn_shockwave(0.8)
                if (this.effectSystem) {
                    this.effectSystem.spawnElectricArc(enemy.x, enemy.y, 1.5, 0.1);
                    this.effectSystem.spawnShockwave(enemy.x, enemy.y, 0.8);
                }
                break;
            case ProjectileType.ION_RIFLE:
                // C L395-399: fx_spawn_electric_arc(1.2, 0.4) + fx_spawn_shockwave(1.2)
                if (this.effectSystem) {
                    this.effectSystem.spawnElectricArc(enemy.x, enemy.y, 1.2, 0.4);
                    this.effectSystem.spawnShockwave(enemy.x, enemy.y, 1.2);
                }
                break;
            case ProjectileType.ION_CANNON:
                // C L401-414: fx_spawn_electric_arc(1.0, 1.0) + fx_spawn_shockwave(2.2) + sfx_shockwave
                if (this.effectSystem) {
                    this.effectSystem.spawnElectricArc(enemy.x, enemy.y, 1.0, 1.0);
                    this.effectSystem.spawnShockwave(enemy.x, enemy.y, 2.2);
                }
                if (this.soundSystem) {
                    this.soundSystem.playAtPosition(SoundId.SHOCKWAVE, enemy.x, enemy.y, 800);
                }
                break;

            default:
                // Most projectile types have no special on-hit behavior
                break;
        }
    }

    /**
     * Check enemy collisions with player
     * Port of collision logic from creature_update_all @ lines 1568-1609
     */
    checkEnemyPlayerCollisions(player: Player, enemies: Enemy[], perkSystem?: any): void {
        for (const enemy of enemies) {
            if (!enemy.active || enemy.health <= 0) continue;

            // Distance check (C line 1568)
            if (enemy.size <= 16.0) continue;

            // Calculate distance to player (C line 1511-1513)
            const dx = enemy.x - player.x;
            const dy = enemy.y - player.y;
            const distance = Math.sqrt(dx * dx + dy * dy);

            // Collision check: distance < 30.0 (C line 1569)
            if (distance < 30.0) {
                // Only deal contact damage when cooldown expired and player alive
                if (player.health > 0 && player.energizerTimer <= 0) {
                    if (enemy.attackCooldown <= 0.0) {
                        // Fix 12: Mr. Melee perk: reflect 25 damage (C lines 1580-1584)
                        if (perkSystem?.hasPerk(PerkId.MR_MELEE)) {
                            enemy.takeDamage(25.0, 2);
                            // Report kill if Mr. Melee damage was fatal
                            if (!enemy.isAlive()) {
                                questSystem.reportEnemyKilled();
                            }
                        }

                        // Fix 12: Contact damage perk effects (C lines 1586-1597)
                        if (player.shieldTimer <= 0.0) {
                            if (perkSystem) {
                                if (perkSystem.hasPerk(PerkId.TOXIC_AVENGER)) {
                                    enemy.flags |= 3; // burning + poison (C line 1594)
                                } else if (perkSystem.hasPerk(PerkId.VEINS_OF_POISON)) {
                                    enemy.flags |= 1; // poison only (C line 1591)
                                }
                            }
                        }

                        // Apply damage to player (C line 1599)
                        player.takeDamage(enemy.damage, perkSystem);

                        // Set enemy attack cooldown (C line 1604)
                        enemy.attackCooldown += 1.0;
                    }

                    // Plaguebearer contact infection (C lines 1606-1609)
                    // When player has plaguebearer active AND enemy health < 150
                    // AND infection count < 0x32 (50), infect the enemy
                    if (player.plaguebearerActive && enemy.health < 150.0
                        && getPlaguebearerInfectionCount() < 0x32) {
                        enemy.collisionFlag = true;
                    }
                }

                // Only one collision per frame
                break;
            }
        }
    }

    /**
     * Check enemy projectile hits against player
     */
    checkEnemyProjectileHits(projectiles: Projectile[], player: Player, perkSystem?: any): void {
        for (const projectile of projectiles) {
            if (!projectile.isActive()) continue;

            // Only check enemy-owned projectiles (ownerId >= 0)
            if (projectile.ownerId < 0) continue;

            // Check collision with player (projectile radius ~3, player radius ~12)
            if (this.checkCircleCollision(projectile.x, projectile.y, 3, player.x, player.y, 12)) {
                // C code (projectiles.c:267): always 10.0 damage regardless of projectile type
                player.takeDamage(10.0, perkSystem);

                // C code (projectiles.c:264): life_timer = 0.25 (enter fading phase)
                // C code (projectiles.c:216): life_timer < 0.4 skips collision block entirely
                // Clear ownerId so the ownerId >= 0 guard prevents re-collision during fade
                projectile.lifetime = 0.25;
                projectile.ownerId = -1;
            }
        }
    }

    /**
     * Get enemy-specific death sound based on enemy type
     * C code reference: Different enemy types have different death sounds
     */
    private getEnemyDeathSound(enemy: Enemy): SoundId {
        switch (enemy.type) {
            case EnemyType.Zombie:
                // Zombie death sounds (4 variants)
                return getRandomDeathSound(SoundId.ZOMBIE_DIE_01, 4);

            case EnemyType.Alien:
                // Alien death sounds (4 variants)
                return getRandomDeathSound(SoundId.ALIEN_DIE_01, 4);

            case EnemyType.Lizard:
                // Lizard death sounds (4 variants)
                return getRandomDeathSound(SoundId.LIZARD_DIE_01, 4);

            case EnemyType.Spider:
            case EnemyType.Spider2:
                // Spider death sounds (4 variants)
                return getRandomDeathSound(SoundId.SPIDER_DIE_01, 4);

            case EnemyType.Trooper:
                // Trooper death sounds (3 variants)
                return getRandomDeathSound(SoundId.TROOPER_DIE_01, 3);

            default:
                // Fallback to zombie death sounds
                return getRandomDeathSound(SoundId.ZOMBIE_DIE_01, 4);
        }
    }

    /**
     * Get bullet hit sound based on projectile type
     * C code reference: Bullet hit sounds for impacts
     */
    private getBulletHitSound(projectileType: number): SoundId {
        // C: ION weapons use sfx_shock_hit, rockets use sfx_shockwave,
        // plasma uses shock_hit, bullets use random bullet_hit
        switch (projectileType) {
            case ProjectileType.ION_RIFLE:
            case ProjectileType.ION_MINIGUN:
            case ProjectileType.ION_CANNON:
            case ProjectileType.PLASMA_RIFLE:
            case ProjectileType.PLASMA_MINIGUN:
            case ProjectileType.PLASMA_CANNON:
            case ProjectileType.SHRINKIFIER:
                return SoundId.SHOCK_HIT_01;

            case ProjectileType.ROCKET:
            case ProjectileType.SEEKER_ROCKET:
            case ProjectileType.ROCKET_MINIGUN:
                return SoundId.EXPLOSION_MEDIUM;

            default:
                // Bullets, fire, etc: random bullet hit (1 of 6)
                return SoundId.BULLET_HIT_01 + Math.floor(Math.random() * 6);
        }
    }
}
