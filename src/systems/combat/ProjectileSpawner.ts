/**
 * ProjectileSpawner - Periodic projectile spawning from player
 *
 * Port of C code lines 11783-11884
 * Enables Fire Cough and Hot Tempered perks
 */

import type { Player } from '../../entities/Player';
import { PerkId } from '../PerkSystem';
import type { PerkSystem } from '../PerkSystem';
import { ProjectileType } from '../../data/WeaponData';
import type { WeaponSystem } from './WeaponSystem';

/**
 * Projectile spawning system for perk-based periodic projectiles
 * C code reference: lines 11783-11884
 */
export class ProjectileSpawner {
    // Fire Cough constants (C lines 11783-11849)
    private static readonly FIRE_COUGH_OFFSET = 16.0; // C line 11806
    private static readonly FIRE_COUGH_ANGLE_OFFSET = -Math.PI / 2 - 0.150915; // C line 11801

    // Hot Tempered constants (C lines 11850-11884)
    private static readonly HOT_TEMPERED_PROJECTILE_COUNT = 8; // C line 11874
    private static readonly HOT_TEMPERED_ANGLE_STEP = 0.7853982; // C line 11872 (π/4, 45°)

    /**
     * Update Fire Cough perk
     * Port of C player.c lines 190-254
     *
     * C behavior:
     * - Timer accumulates frame_dt while perk active
     * - When timer >= cooldown threshold (initially ~4s, then random 2-5s):
     *   - Spawns PROJECTILE_TYPE_FIRE_BULLETS aimed at crosshair
     *   - Spawn position offset from player by 16 units at aimHeading + angle offset
     *   - Plays reload SFX
     *   - Resets timer and randomizes next interval
     */
    static updateFireCough(
        player: Player,
        perkSystem: PerkSystem,
        weaponSystem: WeaponSystem,
        dt: number,
        soundCallback?: (soundId: number, x: number, y: number) => void,
    ): void {
        // Check if perk is active (C lines 190-192)
        if (!perkSystem.hasPerk(PerkId.FIRE_COUGH)) {
            player.fireCoughTimer = 0.0;
            return;
        }

        // Accumulate timer (C lines 195-196)
        player.fireCoughTimer += dt;

        // Check if ready to spawn (C line 197)
        if (player.fireCoughTimer >= player.fireCoughInterval) {
            // Calculate spawn position with offset (C lines 207-215)
            const angle = player.aimAngle + this.FIRE_COUGH_ANGLE_OFFSET;
            const offsetX = Math.cos(angle) * this.FIRE_COUGH_OFFSET;
            const offsetY = Math.sin(angle) * this.FIRE_COUGH_OFFSET;
            const spawnX = player.x + offsetX;
            const spawnY = player.y + offsetY;

            // Calculate projectile angle toward aim position (C lines 216-232)
            const dx = player.aimX - player.x;
            const dy = player.aimY - player.y;
            const projectileAngle = Math.atan2(dy, dx);

            // Spawn fire projectile via WeaponSystem for proper damagePool init
            // C line 235: projectile_spawn(&local_10, local_30[0], PROJECTILE_TYPE_FIRE_BULLETS, owner)
            // Use spawnBonusProjectile with explicit speed: C projectile_spawn gives ALL projectiles
            // the same base velocity (cos*1.5, movement dt*60), NOT the Flamethrower's particle speed.
            // spawnChildProjectile would pick up speed=90 from Flamethrower (first FIRE_BULLETS weapon).
            const proj = weaponSystem.spawnBonusProjectile(spawnX, spawnY, projectileAngle, ProjectileType.FIRE_BULLETS, 1200);
            proj.hasFireVisual = true;

            // Play SFX (C lines 204-205: sfx_player_fire_reload_a + sfx_player_fire_reload_b)
            // sfx_player_fire_reload_a = sfx_autorifle_fire (SoundId 34)
            // sfx_player_fire_reload_b = sfx_plasmaminigun_fire (SoundId 39)
            if (soundCallback) {
                soundCallback(34, player.x, player.y); // SoundId.AUTORIFLE_FIRE
                soundCallback(39, player.x, player.y); // SoundId.PLASMA_MINIGUN_FIRE
            }

            // Reset timer (C lines 247-248)
            player.fireCoughTimer -= player.fireCoughInterval;

            // Random interval 2-5 seconds (C lines 249-254)
            // C: rand() & 0x80000003 → 0-3 (with signed fixup), then +2
            const randomOffset = Math.floor(Math.random() * 4); // 0-3
            player.fireCoughInterval = randomOffset + 2.0;
        }
    }

    /**
     * Update Hot Tempered perk
     * Port of C player.c lines 257-291
     *
     * C behavior:
     * - Timer accumulates frame_dt while perk active
     * - When timer >= cooldown threshold (random 2-9s):
     *   - Spawns 8 radial projectiles alternating PLASMA_MINIGUN/PLASMA_RIFLE
     *   - Plays explosion SFX
     *   - Resets timer and randomizes next interval
     */
    static updateHotTempered(player: Player, perkSystem: PerkSystem, weaponSystem: WeaponSystem, dt: number): void {
        // Check if perk is active (C lines 257-259)
        if (!perkSystem.hasPerk(PerkId.HOT_TEMPERED)) {
            player.hotTemperedTimer = 0.0;
            return;
        }

        // Accumulate timer (C lines 262-263)
        player.hotTemperedTimer += dt;

        // Check if ready to spawn (C line 264)
        if (player.hotTemperedTimer >= player.hotTemperedInterval) {
            // Spawn 8 projectiles in circle (C lines 272-281)
            for (let i = 0; i < this.HOT_TEMPERED_PROJECTILE_COUNT; i++) {
                const angle = i * this.HOT_TEMPERED_ANGLE_STEP;

                // Alternate between plasma types (C lines 273-278)
                const type =
                    (i & 1) === 0
                        ? ProjectileType.PLASMA_MINIGUN
                        : ProjectileType.PLASMA_RIFLE;

                // Spawn via WeaponSystem for proper damagePool init
                weaponSystem.spawnChildProjectile(player.x, player.y, angle, type);
            }

            // Reset timer (C lines 283-284)
            player.hotTemperedTimer -= player.hotTemperedInterval;

            // Random interval 2-9 seconds (C lines 285-290)
            // C: rand() & 0x80000007 → 0-7, then +2
            const randomOffset = Math.floor(Math.random() * 8); // 0-7
            player.hotTemperedInterval = randomOffset + 2.0;
        }
    }
}
