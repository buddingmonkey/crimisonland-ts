/**
 * EnemyAI - Enemy AI targeting and movement system
 *
 * Port of creature_update_all AI logic from C code (lines 21630-21800)
 * Handles enemy targeting, movement toward player, and special behaviors.
 */

import type { Enemy } from '../../entities/Enemy';
import { EnemyType, AIMode } from '../../entities/Enemy';
import type { Player } from '../../entities/Player';
import type { PerkSystem } from '../PerkSystem';
import { PerkId } from '../PerkSystem';
import { ProjectileType } from '../../data/WeaponData';
import { questSystem } from '../quest/QuestSystem';
import type { ParticleSystem } from '../effects/ParticleSystem';

/**
 * Enemy AI system for targeting and movement
 *
 * C code reference: creature_update_all @ lines 21630-21800
 */
export class EnemyAI {
    /**
     * Update enemy AI - targeting, movement, and special behaviors
     *
     * C code reference: creature_update_all @ lines 1509-1566
     *
     * @param enemy Enemy to update
     * @param player Target player
     * @param dt Delta time in seconds
     * @param perkSystem Player's perk system
     * @param onSpawnProjectile Callback for spawning enemy projectiles (Fix 4)
     * @param onPlaySound Callback for playing positional sound effects
     * @returns Object with flags for caller to handle (energizer eat XP, etc.)
     */
    static updateEnemyAI(
        enemy: Enemy,
        player: Player,
        dt: number,
        perkSystem: PerkSystem,
        onSpawnProjectile?: (x: number, y: number, angle: number, type: ProjectileType, ownerId: number) => void,
        onPlaySound?: (soundId: number, x: number, y: number) => void,
        particleSystem?: ParticleSystem,
    ): { energizerEat: boolean; rewardValue: number } | null {
        if (!enemy.active || enemy.health <= 0) return null;

        // C: perks_update_effects lines 607-616 — Evil Eyes freezes targeted enemy
        // Enemy AI skips all movement and attacks while being the evil eyes target
        if (player.evilEyesTarget === enemy) {
            return null;
        }

        // 1. Calculate distance to player (C lines 1511-1513)
        const dx = enemy.x - player.x;
        const dy = enemy.y - player.y;
        const distance = Math.sqrt(dx * dx + dy * dy);

        // 2. Radioactive perk damage (C lines 1514-1531)
        if (distance < 100.0 && perkSystem.hasPerk(PerkId.RADIOACTIVE)) {
            // Update collision timer at 1.5x speed (C lines 1515)
            enemy.collisionTimer -= dt * 1.5;

            // Check if timer expired and enemy is alive (C line 1516-1517)
            if (enemy.collisionTimer < 0.0 && enemy.health > 0) {
                // Reset collision timer to 0.5 seconds (C line 1518)
                enemy.collisionTimer = 0.5;

                // Set state flag (C line 1519)
                enemy.stateFlag = 0x01;

                // Damage formula: (100 - distance) * 0.3 (C line 1520)
                const damage = (100.0 - distance) * 0.3;
                enemy.health -= damage;

                // Fix 7: Handle death (C lines 1522-1531)
                if (enemy.health < 0.0) {
                    // Special case for zombie type (type_id == 1) (C lines 1523-1524)
                    if (enemy.type === EnemyType.Zombie) {
                        enemy.health = 1.0;
                    } else {
                        // Non-zombie killed by radioactive — trigger death
                        enemy.isDying = true;
                        enemy.deathTimer = 0;
                        enemy.hitboxSize -= dt; // Start death (C line 1529)
                        questSystem.reportEnemyKilled();
                    }
                }

                // Visual effect: green radioactive flash + particles
                enemy.radioactiveFlashTimer = 0.15;
                particleSystem?.spawnRadioactive(enemy.x, enemy.y);

                // Visual effect (C line 1532: fx_queue_add_random) handled by
                // BloodEffectSystem.addRandomGroundDebris() in Game.ts updatePlaying()
            }
        }

        // 3. Enemy projectile spawning (C lines 1534-1551)
        // Fix 4: Enemy projectile spawning via onSpawnProjectile callback
        // C: creature_update_all skips ALL AI (including shooting) when freeze timer > 0
        if (distance > 64.0 && !(player.freezeTimer > 0)) {
            // Plasma rifle enemy (C lines 1535-1540)
            if (enemy.canShootPlasma && enemy.attackCooldown <= 0.0) {
                onSpawnProjectile?.(enemy.x, enemy.y, enemy.heading - Math.PI / 2, ProjectileType.PLASMA_RIFLE, enemy.id);
                enemy.attackCooldown += 1.0; // C line 1539: additive
                // C: sfx_play_panned(sfx_shock_fire)
                onPlaySound?.(38, enemy.x, enemy.y); // SoundId.SHOCK_FIRE = 38
            }

            // Plasma minigun enemy (C lines 1542-1551)
            if (enemy.canShootMinigun && enemy.attackCooldown <= 0.0) {
                const projType = enemy.projectileType || ProjectileType.PLASMA_MINIGUN;
                onSpawnProjectile?.(enemy.x, enemy.y, enemy.heading - Math.PI / 2, projType, enemy.id);
                // Random cooldown: (rand & 3) * 0.1 + orbit_angle (C lines 1547-1549)
                const randomDelay = Math.floor(Math.random() * 4) * 0.1;
                enemy.attackCooldown += randomDelay + enemy.orbitAngle;
                // C: sfx_play_panned(sfx_plasmaminigun_fire)
                onPlaySound?.(39, enemy.x, enemy.y); // SoundId.PLASMA_MINIGUN_FIRE = 39
            }
        }

        // 4. Update attack cooldown (C line 1502-1508)
        if (enemy.attackCooldown <= 0) {
            enemy.attackCooldown = 0;
        } else {
            enemy.attackCooldown -= dt;
        }

        // 5. Fix 8: Energizer proximity eat (C lines 1553-1566)
        if (distance < 20.0) {
            // Push back (C lines 1554-1556)
            enemy.x -= enemy.velX;
            enemy.y -= enemy.velY;

            if (enemy.maxHealth < 380.0 && player.energizerTimer > 0) {
                // Instant removal — no corpse (C line 1564)
                enemy.active = false;
                questSystem.reportEnemyKilled();
                return { energizerEat: true, rewardValue: enemy.rewardValue };
            }
        }

        return null;
    }

    /**
     * Calculate AI target position based on AI mode
     * C code reference: creature_update_all lines 1240-1378
     *
     * @param enemy Enemy to calculate target for
     * @param player Target player
     * @param distance Distance to player
     * @param enemies All enemies (for leader following)
     */
    static calculateAITarget(enemy: Enemy, player: Player, distance: number, enemies: Enemy[], dt: number = 0): void {
        // Calculate fixed orbit angle per enemy (C line 1239)
        // C: fVar17 = (int)phase_seed * 3.7 * PI — phase_seed is integer 0-383
        // This is a FIXED angle per enemy, NOT dynamic based on position
        const phaseAngle = Math.floor(enemy.phaseSeed) * 3.7 * Math.PI;

        // First pass: modes that set targetX/Y in the initial switch (C lines 1241-1316)
        switch (enemy.aiMode) {
            case AIMode.CHASE_CIRCLE: // Mode 0 (C lines 1242-1259)
                if (distance > 800.0) {
                    enemy.targetX = player.x;
                    enemy.targetY = player.y;
                } else {
                    enemy.targetX = Math.cos(phaseAngle) * distance * 0.85 + player.x;
                    enemy.targetY = Math.sin(phaseAngle) * distance * 0.85 + player.y;
                }
                break;

            case AIMode.CLOSE_CIRCLE: // Mode 1 (C lines 1272-1283)
                if (distance > 800.0) {
                    enemy.targetX = player.x;
                    enemy.targetY = player.y;
                } else {
                    enemy.targetX = Math.cos(phaseAngle) * distance * 0.55 + player.x;
                    enemy.targetY = Math.sin(phaseAngle) * distance * 0.55 + player.y;
                }
                break;

            case AIMode.WIDE_CIRCLE: // Mode 8 (C lines 1261-1271)
                enemy.targetX = Math.cos(phaseAngle) * distance * 0.9 + player.x;
                enemy.targetY = Math.sin(phaseAngle) * distance * 0.9 + player.y;
                break;

            case AIMode.FOLLOW_LEADER: // Mode 3 (C lines 1284-1294)
                if (enemy.linkIndex >= 0 && enemy.linkIndex < enemies.length) {
                    const leader = enemies[enemy.linkIndex];
                    if (leader.health > 0) {
                        enemy.targetX = leader.x + enemy.targetOffsetX;
                        enemy.targetY = leader.y + enemy.targetOffsetY;
                    } else {
                        enemy.aiMode = AIMode.CHASE_CIRCLE;
                    }
                }
                break;

            case AIMode.LINKED_TO_LEADER: {
                // Mode 5 (C lines 1296-1316)
                if (enemy.linkIndex >= 0 && enemy.linkIndex < enemies.length) {
                    const leader = enemies[enemy.linkIndex];
                    if (leader.health <= 0) {
                        // Leader dead → mode 0 + 1000 damage (C lines 1299-1302)
                        enemy.aiMode = AIMode.CHASE_CIRCLE;
                        enemy.takeDamage(1000.0, 1);
                        if (!enemy.isAlive()) {
                            questSystem.reportEnemyKilled();
                        }
                    } else {
                        // Follow leader with offset
                        enemy.targetX = leader.x + enemy.targetOffsetX;
                        enemy.targetY = leader.y + enemy.targetOffsetY;
                    }
                }
                break;
            }

            case AIMode.BURROW: // Mode 7 (C lines 1344-1363) — HOLD_TIMER / orbiter
                // Hold at current position during first pass; transition logic in second pass below
                enemy.targetX = enemy.x;
                enemy.targetY = enemy.y;
                break;

            default:
                enemy.targetX = player.x;
                enemy.targetY = player.y;
                break;
        }

        // Second pass: modes 4, 6, 7 that run after the initial switch (C lines 1317-1378)
        const aiMode2 = enemy.aiMode;

        if (aiMode2 === AIMode.ORBIT_LEADER) {
            // Fix 9 — Mode 4: Circle like mode 0 but if leader dead → mode 0 + 1000 damage (C lines 1318-1342)
            if (enemy.linkIndex >= 0 && enemy.linkIndex < enemies.length) {
                const leader = enemies[enemy.linkIndex];
                if (leader.health <= 0) {
                    enemy.aiMode = AIMode.CHASE_CIRCLE;
                    enemy.takeDamage(1000.0, 1);
                    if (!enemy.isAlive()) {
                        questSystem.reportEnemyKilled();
                    }
                } else {
                    if (distance <= 800.0) {
                        enemy.targetX = Math.cos(phaseAngle) * distance * 0.85 + player.x;
                        enemy.targetY = Math.sin(phaseAngle) * distance * 0.85 + player.y;
                    } else {
                        enemy.targetX = player.x;
                        enemy.targetY = player.y;
                    }
                }
            }
        } else if (aiMode2 === AIMode.ORBIT_ANGLE) {
            // Fix 9 — Mode 6: Orbit leader at fixed angle+radius (C lines 1365-1378)
            if (enemy.linkIndex >= 0 && enemy.linkIndex < enemies.length) {
                const leader = enemies[enemy.linkIndex];
                if (leader.health <= 0) {
                    enemy.aiMode = AIMode.CHASE_CIRCLE;
                } else {
                    const totalAngle = enemy.orbitAngle + enemy.heading;
                    enemy.targetX = Math.cos(totalAngle) * enemy.orbitRadius + leader.x;
                    enemy.targetY = Math.sin(totalAngle) * enemy.orbitRadius + leader.y;
                }
            }
        } else if (aiMode2 === AIMode.BURROW) {
            // Mode 7: Timer-based hold → orbit transition (C lines 1344-1363)
            // Python: ALIEN_AI7_ORBITER / HOLD_TIMER
            //
            // For template 0x36 (flags=0, orbit_radius=1.5):
            //   - orbitRadius counts down by dt each frame
            //   - When orbitRadius <= 0: switch to mode 0 (CHASE_CIRCLE → orbits player)
            //   - During countdown: hold at current position (target = self)
            const hasTimerFlag = (enemy.creatureFlags & 0x80) !== 0;
            if (!hasTimerFlag || enemy.linkIndex < 1) {
                if (enemy.orbitRadius <= 0 || hasTimerFlag) {
                    // Timer expired or 0x80 flag → transition to orbit player (C line 1349)
                    enemy.aiMode = AIMode.CHASE_CIRCLE;
                } else {
                    // Countdown: hold position, decrement timer (C lines 1352-1356)
                    enemy.targetX = enemy.x;
                    enemy.targetY = enemy.y;
                    enemy.orbitRadius -= dt;
                }
            } else {
                // 0x80 flag with positive link_index: hold position (C lines 1360-1362)
                enemy.targetX = enemy.x;
                enemy.targetY = enemy.y;
            }
        }
    }

    /**
     * Calculate distance between enemy and player
     *
     * C code reference: lines 21658-21660
     */
    static getDistanceToPlayer(enemy: Enemy, player: Player): number {
        const dx = enemy.x - player.x;
        const dy = enemy.y - player.y;
        return Math.sqrt(dx * dx + dy * dy);
    }

    /**
     * Calculate angle from enemy to player
     */
    static getAngleToPlayer(enemy: Enemy, player: Player): number {
        const dx = player.x - enemy.x;
        const dy = player.y - enemy.y;
        return Math.atan2(dy, dx);
    }
}
