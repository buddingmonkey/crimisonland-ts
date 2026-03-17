import { type Player } from '../../entities/Player';
import { type EnemySpawner } from './EnemySpawner';
import { type PerkSystem, PerkId } from '../PerkSystem';
import { type WeaponSystem } from '../combat/WeaponSystem';
import { type ParticleSystem } from '../effects/ParticleSystem';
import { type SoundSystem, SoundId } from '../../audio';
import { EnemyAI } from './EnemyAI';
import { EnemyTargeting } from './EnemyTargeting';
import { ProjectileSpawner } from '../combat/ProjectileSpawner';
import { ProjectileType } from '../../data/WeaponData';
import { questSystem } from '../quest/QuestSystem';

/** Tracks total enemies killed by plague damage (C: plaguebearer_infection_count) */
let plaguebearerInfectionCount = 0;

/** Get current plaguebearer infection count */
export function getPlaguebearerInfectionCount(): number {
    return plaguebearerInfectionCount;
}

/** Reset plaguebearer infection count (call on game start) */
export function resetPlaguebearerInfectionCount(): void {
    plaguebearerInfectionCount = 0;
}
export interface EnemySystemsContext {
    player: Player;
    enemySpawner: EnemySpawner;
    perkSystem: PerkSystem;
    weaponSystem: WeaponSystem;
    particleSystem: ParticleSystem;
    soundSystem: SoundSystem;
}

/**
 * Updates all enemy-side systems for one frame:
 * - Enemy AI & movement (C: creature_update_all @ 1509-1566)
 * - Energizer proximity eat
 * - Perk-based targeting: Pyrokinetic, Evil Eyes, Doctor
 * - Proximity damage: Radioactive, Mr. Melee
 * - Projectile perks: Fire Cough, Hot Tempered
 * - Man Bomb radial burst
 */
export function updateEnemySystems(ctx: EnemySystemsContext, scaledDt: number, rawDt?: number): void {
    // C: fire_cough and hot_tempered timers run BEFORE the time_scale modification
    // (player.c line 310), so they always use unscaled frame_dt.
    const perkTimerDt = rawDt ?? scaledDt;
    const { player, enemySpawner, perkSystem, weaponSystem, particleSystem, soundSystem } = ctx;

    // Update dying enemies (death animations) and bake completed corpses
    // NOTE: corpse baking into terrain is handled in-place here for completeness;
    // the BloodEffectSystem is called directly by Game.ts before this function.

    // Enemy Targeting perks: Pyrokinetic, Evil Eyes, Doctor (C lines 4765-4860)
    // C: perks_update_effects() runs BEFORE creature_update_all() (gameplay.c:355 vs :380)
    // Evil Eyes sets the target here; EnemyAI.ts reads it below to freeze the target.
    EnemyTargeting.updateTargetingPerks(player, enemySpawner.getActiveEnemies(), perkSystem, scaledDt);

    // Update enemy AI - targeting and movement (C code: creature_update_all @ 1509-1566)
    for (const enemy of enemySpawner.getActiveEnemies()) {
        const result = EnemyAI.updateEnemyAI(
            enemy,
            player,
            scaledDt,
            perkSystem,
            (x: number, y: number, angle: number, type: ProjectileType, ownerId: number) => {
                // C: projectile_spawn gives ALL projectiles the same velocity (cos/sin * 1.5).
                // C movement formula: vel * speed_scale * 3.0 * 20.0 per substep.
                // User-timed: ~5s to cross 600px screen = 120 px/s.
                // Must NOT use spawnChildProjectile — that looks up WEAPON_DATA player speeds.
                const ENEMY_PROJECTILE_SPEED = 144; // C: ~120 px/s + 20% tuning (user-timed)
                const ENEMY_PROJECTILE_DAMAGE = 10; // C: projectile_update L19487: health -= 10.0
                const proj = weaponSystem.spawnBonusProjectile(x, y, angle, type, ENEMY_PROJECTILE_SPEED, ENEMY_PROJECTILE_DAMAGE, ownerId);
                proj.ownerId = ownerId; // Mark as enemy projectile so collision system routes to player-only damage
            },
            (soundId: number, x: number, y: number) => {
                soundSystem.playAtPosition(soundId, x, y, 800);
            },
            particleSystem,
        );

        // Fix 8: Handle energizer proximity eat
        // C creatures.c:1559-1560: __ftol() SET is a Ghidra x87 FPU artifact — actually ADD
        if (result?.energizerEat) {
            player.experience += Math.floor(result.rewardValue);
            particleSystem.spawnBurst(enemy.x, enemy.y, 6);
            soundSystem.play(SoundId.UI_BONUS);
        }
    }

    // Jinxed perk: kill random enemy (C perks_update_effects lines 627-646)
    if (player.pendingJinxedKill) {
        player.pendingJinxedKill = false;
        const enemies = enemySpawner.getActiveEnemies();
        if (enemies.length > 0) {
            for (let attempt = 0; attempt < 10; attempt++) {
                const idx = Math.floor(Math.random() * enemies.length);
                const target = enemies[idx];
                if (target && target.active && target.health > 0) {
                    // C perks.c:643: __ftol() SET is a Ghidra x87 FPU artifact — actually ADD
                    player.experience += Math.floor(target.rewardValue);
                    target.health = -1.0;
                    target.hitboxSize -= scaledDt * 20.0; // C line 641
                    questSystem.reportEnemyKilled();
                    break;
                }
            }
        }
    }

    // Fix 7: Process burning/poison flags (C: creature_update_all lines 1130-1145)
    const activeEnemies = enemySpawner.getActiveEnemies();
    for (const enemy of activeEnemies) {
        if (!enemy.active || enemy.health <= 0) continue;
        if ((enemy.flags & 2) !== 0) {
            // Burning: 180 DPS, damage_type 0 (C line 1132)
            enemy.takeDamage(scaledDt * 180.0, 0);
            if (!enemy.isAlive()) questSystem.reportEnemyKilled();
        } else if ((enemy.flags & 1) !== 0) {
            // Poison: 60 DPS, damage_type 0 (C line 1141)
            enemy.takeDamage(scaledDt * 60.0, 0);
            if (!enemy.isAlive()) questSystem.reportEnemyKilled();
        }
    }

    // Fix 9: Plague collision damage (C lines 1211-1233)
    for (const enemy of activeEnemies) {
        if (!enemy.active || enemy.health <= 0) continue;
        if (enemy.collisionFlag && enemy.hitboxSize === 16.0) {
            enemy.collisionTimer -= scaledDt;
            if (enemy.collisionTimer < 0) {
                enemy.stateFlag = 1;
                enemy.collisionTimer += 0.5;
                enemy.health -= 15.0;
                if (enemy.health < 0) {
                    enemy.isDying = true;
                    enemy.deathTimer = 0;
                    questSystem.reportEnemyKilled();
                    plaguebearerInfectionCount++;
                    // C lines 1223-1230: creature_handle_death + sfx_play_panned
                    soundSystem.playAtPosition(
                        SoundId.ZOMBIE_DIE_01 + Math.floor(Math.random() * 2),
                        enemy.x, enemy.y, 800,
                    );
                }
                // C line 1232: fx_queue_add_random — ground debris on each plague tick
                particleSystem.spawnBurst(enemy.x, enemy.y, 1);
            }
        }
    }

    // Fix 9: Plague spreading (C creature_check_collision_radius lines 1041-1071)
    // Called per-creature when perk_count_get(plaguebearer) != 0 AND infection_count < 0x3c (60)
    // C spreading is BIDIRECTIONAL: if A is infected & B nearby with health<150, B gets infected,
    // AND if B is infected & A has health<150, A gets infected.
    if (perkSystem.hasPerk(PerkId.PLAGUEBEARER) && plaguebearerInfectionCount < 0x3c) {
        for (const enemy of activeEnemies) {
            if (!enemy.active) continue;
            for (const other of activeEnemies) {
                if (other === enemy || !other.active) continue;
                const dx = other.x - enemy.x;
                const dy = other.y - enemy.y;
                if (Math.sqrt(dx * dx + dy * dy) < 45.0) {
                    // Bidirectional: if enemy is infected and other has health<150, infect other
                    if (enemy.collisionFlag && other.health < 150.0) {
                        other.collisionFlag = true;
                    }
                    // Reverse: if other is infected and enemy has health<150, infect enemy
                    if (other.collisionFlag && enemy.health < 150.0) {
                        enemy.collisionFlag = true;
                    }
                    break; // C: returns after first match (early exit per creature)
                }
            }
        }
    }

    // Projectile Spawning perks: Fire Cough, Hot Tempered
    // Pass weaponSystem so projectiles get proper damagePool via initDamagePool
    ProjectileSpawner.updateFireCough(player, perkSystem, weaponSystem, perkTimerDt,
        (soundId, x, y) => soundSystem.playAtPosition(soundId, x, y, 800));
    ProjectileSpawner.updateHotTempered(player, perkSystem, weaponSystem, perkTimerDt);

    // Man Bomb burst: spawn 8 radial projectiles (C player.c lines 144-178)
    // C: alternates PROJECTILE_TYPE_ION_MINIGUN (even) / ION_RIFLE (odd)
    // C: angle = i * 0.7853982 + (rand() % 50) * 0.01 - 0.25
    if (player.pendingManBombBurst) {
        player.pendingManBombBurst = false;
        for (let i = 0; i < 8; i++) {
            const type = (i & 1) === 0
                ? ProjectileType.ION_MINIGUN
                : ProjectileType.ION_RIFLE;
            const jitter = (Math.random() * 50 | 0) * 0.01 - 0.25;
            const angle = i * 0.7853982 + jitter;
            weaponSystem.spawnChildProjectile(player.x, player.y, angle, type);
        }
        soundSystem.play(SoundId.EXPLOSION_SMALL);
    }

    // Final Revenge: area explosion on player death (C player.c lines 2174-2204)
    // C: when player dies with perk, spawn explosion burst at player pos,
    // then damage all enemies within 512 units: damage = (512 - distance) * 5
    if (player.pendingFinalRevenge && !player.isAlive()) {
        player.pendingFinalRevenge = false;
        const px = player.x;
        const py = player.y;
        const RADIUS = 512.0;

        // Visual explosion burst (C: effect_spawn_explosion_burst(pos, 1.8))
        particleSystem.spawnBurst(px, py, 20);

        // Damage all enemies within radius (C lines 2188-2201)
        for (const enemy of enemySpawner.getActiveEnemies()) {
            if (!enemy.active || !enemy.isAlive()) continue;
            const edx = enemy.x - px;
            const edy = enemy.y - py;
            // C: quick AABB check first (|dx| <= 512 && |dy| <= 512)
            if (Math.abs(edx) > RADIUS || Math.abs(edy) > RADIUS) continue;
            const dist = Math.sqrt(edx * edx + edy * edy);
            const dmg = RADIUS - dist;
            if (dmg > 0) {
                enemy.takeDamage(dmg * 5.0, 3); // C: damage_type=3
                if (!enemy.isAlive()) {
                    questSystem.reportEnemyKilled();
                }
            }
        }

        soundSystem.play(SoundId.EXPLOSION_LARGE);
    }
}

