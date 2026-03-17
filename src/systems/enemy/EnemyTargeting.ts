/**
 * EnemyTargeting - Find and target enemies near crosshair
 *
 * Port of C code lines 4765-4860
 * Enables Pyrokinetic, Evil Eyes, and Doctor perks
 */

import type { Enemy } from '../../entities/Enemy';
import type { Player } from '../../entities/Player';
import { PerkId } from '../PerkSystem';
import type { PerkSystem } from '../PerkSystem';


/**
 * Enemy targeting system for crosshair-based perks
 * C code reference: lines 4765-4860
 */
export class EnemyTargeting {
    // Target radius around aim position (C line 4769)
    private static readonly TARGET_RADIUS = 12.0;



    // Pyrokinetic cooldown between burns (C line 4780)
    private static readonly PYROKINETIC_COOLDOWN = 0.5;

    /**
     * Find closest enemy within radius of aim position
     * Port of creature_find_in_radius @ C line 4769
     *
     * @param aimX Crosshair X position
     * @param aimY Crosshair Y position
     * @param enemies Enemy array
     * @returns Closest enemy within radius, or null
     */
    static findTargetInCrosshair(aimX: number, aimY: number, enemies: Enemy[]): Enemy | null {
        let closestEnemy: Enemy | null = null;
        let closestDist = this.TARGET_RADIUS;

        for (const enemy of enemies) {
            if (!enemy.active) continue;

            // Calculate distance to aim position
            const dx = enemy.x - aimX;
            const dy = enemy.y - aimY;
            const dist = Math.sqrt(dx * dx + dy * dy);

            // Track closest enemy within radius
            if (dist < closestDist) {
                closestDist = dist;
                closestEnemy = enemy;
            }
        }

        return closestEnemy;
    }

    /**
     * Apply targeting perk effects
     * Port of C lines 4765-4860
     *
     * @param player Player entity
     * @param enemies Enemy array
     * @param perkSystem Perk system
     * @param dt Delta time
     */
    static updateTargetingPerks(player: Player, enemies: Enemy[], perkSystem: PerkSystem, dt: number): void {
        // Check if any targeting perks are active (C lines 4765-4767)
        const hasPyrokinetic = perkSystem.hasPerk(PerkId.PYROKINETIC);
        const hasEvilEyes = perkSystem.hasPerk(PerkId.EVIL_EYES);
        const hasDoctor = perkSystem.hasPerk(PerkId.DOCTOR);

        if (!hasPyrokinetic && !hasEvilEyes && !hasDoctor) {
            return;
        }

        // Reset target (C line 4768)
        player.evilEyesTarget = null;
        player.doctorTarget = null;

        // Find target enemy (C line 4769)
        const target = this.findTargetInCrosshair(player.aimX, player.aimY, enemies);

        if (target) {
            // Pyrokinetic: Burn enemy with particles (C lines 4775-4814)
            if (hasPyrokinetic) {
                this.applyPyrokineticEffect(target, dt);
            }

            // Evil Eyes: Store target for damage (C lines 4815-4818)
            if (hasEvilEyes) {
                player.evilEyesTarget = target;
            }

            // Doctor: Store target for healing (C lines 4771-4774)
            if (hasDoctor) {
                player.doctorTarget = target;
            }
        }
    }

    /**
     * Apply Pyrokinetic burning effect
     * Port of C perks_update_effects lines 567-606
     *
     * C code behavior: pyrokinetic does NOT deal direct damage.
     * It sets the burning flag (flags |= 2) on the targeted enemy every 0.5s.
     * The actual damage (180 DPS) comes from the burning damage loop
     * in EnemySystemsUpdate.ts (C creature_update_all lines 1130-1145).
     *
     * @param enemy Enemy to burn
     * @param dt Delta time
     */
    private static applyPyrokineticEffect(enemy: Enemy, dt: number): void {
        // Use collision timer as cooldown (C lines 569-572)
        enemy.collisionTimer -= dt;

        if (enemy.collisionTimer < 0.0) {
            enemy.collisionTimer = this.PYROKINETIC_COOLDOWN;

            // Set burning flag — the burning damage loop (180 DPS) handles the rest
            // C code spawns fire particles here; burning flag causes actual damage
            enemy.flags |= 2;
        }
    }

    // C perks_update_effects lines 607-616: Evil Eyes does NOT deal damage.
    // It sets evil_eyes_target_creature, which freezes the enemy (handled in EnemyAI.ts).
    // Doctor (C lines 556-566) only sets doctor_perk_target_creature for HUD health bar.
    // +20% bullet damage is in DamageCalculator.ts.
}
