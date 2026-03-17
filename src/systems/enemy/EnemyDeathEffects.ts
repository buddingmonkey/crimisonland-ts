/**
 * EnemyDeathEffects - Enemy death effects system
 *
 * Handles blood splatter effects and death mechanics.
 * C code reference: creatures.c L1673-1695
 */

import type { Enemy } from '../../entities/Enemy';
import type { BloodEffectSystem } from '../effects/BloodEffectSystem';

/**
 * Enemy death effects system
 */
export class EnemyDeathEffects {
    private bloodSystem: BloodEffectSystem | null = null;

    /**
     * Set blood effect system reference
     */
    setBloodSystem(bloodSystem: BloodEffectSystem): void {
        this.bloodSystem = bloodSystem;
    }

    /**
     * Spawn blood splatter effects on enemy death
     * C code reference: creatures.c L1673-1695
     *
     * Spawns 19 total blood splatters in 3 layers + ground decal
     */
    spawnBloodSplatters(enemy: Enemy): void {
        // Only spawn if enemy has blood flag (C: flags & 4)
        if (!enemy.hasBlood) return;
        if (!this.bloodSystem) return;

        this.bloodSystem.spawnDeathBlood(enemy.x, enemy.y);
    }

    /**
     * Handle enemy death
     * C code reference: creatures.c L1671-1698
     */
    handleEnemyDeath(enemy: Enemy, scoreSystem: any, bodiesFade: boolean = true): void {
        // Increment kill count (C L1671-1672)
        if (scoreSystem && scoreSystem.incrementKills) {
            scoreSystem.incrementKills();
        }

        // Spawn blood effects (C L1673-1695)
        this.spawnBloodSplatters(enemy);

        // Bodies fade option (C L1696-1698)
        if (!bodiesFade) {
            enemy.active = false; // Immediately remove
        }
    }
}
