/**
 * BonusSystem - Powerup spawning and management
 *
 * Port of bonus system from crimsonland.exe_decompiled.c
 */

import { Bonus, BonusType } from '../../entities/Bonus';
import type { GrimInterface } from '../../engine/GrimInterface';
import type { Player } from '../../entities/Player';
import type { SpriteRenderer } from '../../rendering/SpriteRenderer';
import { getWeaponUnlockRegistry } from '../WeaponUnlockRegistry';

/**
 * Bonus/powerup system
 */
export class BonusSystem {
    private bonuses: Bonus[] = [];
    /**
     * World/terrain bounds for edge check.
     * C code: bonus_spawn_at_pos uses grim_context.screen_width/height,
     * but in the TS port entity coordinates are in world space (not screen space),
     * so we must use terrain dimensions here.
     * Default: 1024×1024 matching DEFAULT_TERRAIN_WIDTH/HEIGHT.
     */
    private worldWidth: number = 1024;
    private worldHeight: number = 1024;

    /**
     * Update the world bounds used for the bonus edge check.
     * Call this when terrain is loaded (terrain dimensions may vary).
     */
    setWorldBounds(width: number, height: number): void {
        this.worldWidth = width;
        this.worldHeight = height;
    }

    /**
     * Spawn bonus at position (port of bonus_spawn_at_pos @ 0041f790)
     */
    spawnBonusAt(x: number, y: number, filterCtx?: {
        shockChainLinksLeft: number;
        freezeTimer: number;
        shieldTimer: number;
        hasDeathClock: boolean;
        hasFavouriteWeapon: boolean;
        hasFireBulletsOnGround: boolean;
    }): Bonus | null {
        // Edge check (C line 18090-18092): 32px from edges
        if (x < 32 || x > this.worldWidth - 32 || y < 32 || y > this.worldHeight - 32) {
            return null;
        }

        // Spacing check (C line 18096-18099): 32px between bonuses
        for (const bonus of this.bonuses) {
            if (!bonus.isActive()) continue;

            const dx = x - bonus.x;
            const dy = y - bonus.y;
            const distance = Math.sqrt(dx * dx + dy * dy);

            if (distance < 32) {
                return null; // Too close to existing bonus
            }
        }

        // Pick random type (C line 18107)
        const type = this.pickRandomBonusType(filterCtx);

        // Set amount based on type (C line 18109-18124)
        let amount = 0;
        if (type === BonusType.WEAPON) {
            // C: weapon_pick_random_available() — selects from unlocked weapons
            amount = getWeaponUnlockRegistry().pickRandomAvailable();
        } else if (type === BonusType.POINTS) {
            // C line 18115-18120: 500 or 1000 points
            amount = 500;
            if (Math.floor(Math.random() * 8) < 3) {
                amount = 1000;
            }
        } else if (type === BonusType.HEALTH) {
            amount = 25; // Health restore amount (overridden to 10 in applyBonusEffect)
        }

        // Set default durations for timed bonuses (C bonus_meta_table defaults)
        const BONUS_DEFAULT_DURATION: Partial<Record<BonusType, number>> = {
            [BonusType.SHIELD]: 7.0,
            [BonusType.SPEED]: 8.0,
            [BonusType.REFLEX_BOOST]: 5.0,
            [BonusType.FREEZE]: 5.0,
            [BonusType.FIRE_BULLETS]: 5.0,
            [BonusType.ENERGIZER]: 8.0,
            [BonusType.DOUBLE_EXPERIENCE]: 6.0,
            [BonusType.WEAPON_POWER_UP]: 5.0, // Fix 1: matches C bonus_meta_table
        };
        if (type in BONUS_DEFAULT_DURATION) {
            amount = BONUS_DEFAULT_DURATION[type as BonusType]!;
        }

        const bonus = new Bonus(x, y, type, amount);
        this.bonuses.push(bonus);
        return bonus;
    }

    /**
     * Try to spawn bonus on enemy kill (port of bonus_try_spawn_on_kill @ 0041f8d0)
     *
     * C code logic:
     * - If player holds pistol (weapon_id 0): 75% chance to drop a weapon pickup
     *   - Prevents dropping same weapon player already has
     *   - Prevents dropping if Favourite Weapon perk is active
     * - Else: ~11% base drop rate (rand % 9 == 1)
     *   - Sub-check: If player holds pistol and base missed, 20% extra (rand % 5 == 1)
     * - Bonus Magnet perk adds extra 10% chance if base and pistol checks fail
     * - Duplicate prevention: max 1 of each non-POINTS type on ground
     * - Proximity override: if weapon drops within 56px of player, convert to POINTS(100)
     */
    trySpawnOnKill(
        x: number,
        y: number,
        playerWeaponId: number,
        playerX: number = 0,
        playerY: number = 0,
        hasBonusMagnet: boolean = false,
        hasFavouriteWeapon: boolean = false,
        shockChainLinksLeft: number = 0,
        freezeTimer: number = 0,
        shieldTimer: number = 0,
        hasDeathClock: boolean = false,
    ): { x: number; y: number } | null {
        // C line 1024-1026: If player has pistol (ID 0 in TS, ID 1 in C), 75% chance to drop weapon
        if (playerWeaponId === 0) {
            const rand = Math.floor(Math.random() * 4); // (rand & 3) < 3 = 75%
            if (rand < 3) {
                const bonus = this.spawnBonusAt(x, y); // pistol path: always weapon, no filter needed
                if (bonus) {
                    bonus.type = BonusType.WEAPON;
                    // C: weapon_pick_random_available() — pick from unlocked weapons
                    bonus.amount = getWeaponUnlockRegistry().pickRandomAvailable();

                    // Re-roll if we got pistol (C lines 1031-1033)
                    if (bonus.amount === 0) {
                        bonus.amount = getWeaponUnlockRegistry().pickRandomAvailable();
                    }

                    // Duplicate check: max 1 weapon pickup on ground (C lines 1036-1044)
                    if (this.countBonusesOfType(BonusType.WEAPON) > 1) {
                        bonus.active = false;
                        return null;
                    }

                    // Don't drop same weapon player already has (C lines 1046-1048)
                    if (bonus.amount === playerWeaponId) {
                        bonus.active = false;
                        return null;
                    }

                    // C line 1047: My Favourite Weapon perk blocks weapon drops on pistol path too
                    if (hasFavouriteWeapon) {
                        bonus.active = false;
                        return null;
                    }

                    return { x: bonus.x, y: bonus.y }; // Fix 2: return position for spawn particles
                }
                return null;
            }
        }

        // Standard drop path (C lines 1054-1066)
        // Base chance: rand % 9 == 1 (~11%)
        const baseRand = Math.floor(Math.random() * 9);
        let shouldDrop = baseRand === 1;

        // Sub-check for pistol holders: if base miss, extra 20% chance (C line 1056)
        if (!shouldDrop && playerWeaponId === 0) {
            shouldDrop = Math.floor(Math.random() * 5) === 1;
        }

        // Bonus Magnet perk: extra 10% chance (C lines 1057-1062)
        if (!shouldDrop && hasBonusMagnet) {
            shouldDrop = Math.floor(Math.random() * 10) === 2;
        }

        if (!shouldDrop) {
            return null;
        }

        // Build filter context for pickRandomBonusType (C lines 482-510)
        const hasFireBulletsOnGround = this.countBonusesOfType(BonusType.FIRE_BULLETS) > 0;
        const filterCtx = {
            shockChainLinksLeft,
            freezeTimer,
            shieldTimer,
            hasDeathClock,
            hasFavouriteWeapon,
            hasFireBulletsOnGround,
        };

        const bonus = this.spawnBonusAt(x, y, filterCtx);
        if (!bonus) return null;

        // Note: My Favourite Weapon filter is now handled inside pickRandomBonusType
        // via the filterCtx, so the post-hoc check here is no longer needed.
        // Kept as a safety fallback in case pickRandomBonusType exhausts retries.
        if (bonus.type === BonusType.WEAPON && hasFavouriteWeapon) {
            bonus.active = false;
            return null;
        }

        // Proximity override: weapon near player becomes points (C lines 1067-1072)
        if (bonus.type === BonusType.WEAPON) {
            const dx = x - playerX;
            const dy = y - playerY;
            const dist = Math.sqrt(dx * dx + dy * dy);
            if (dist < 56.0) {
                bonus.type = BonusType.POINTS;
                bonus.amount = 100;
            }
        }

        // Duplicate check: max 1 of each non-POINTS type on ground (C lines 1073-1082)
        if (bonus.type !== BonusType.POINTS) {
            if (this.countBonusesOfType(bonus.type) > 1) {
                bonus.active = false;
                return null;
            }
        }

        // Don't drop weapon player already has (C lines 1084-1087)
        if (bonus.type === BonusType.WEAPON && bonus.amount === playerWeaponId) {
            bonus.active = false;
            return null;
        }

        return { x: bonus.x, y: bonus.y }; // Fix 2: return position for spawn particles
    }

    /**
     * Count active bonuses of a given type (for duplicate prevention)
     */
    countBonusesOfType(type: BonusType): number {
        let count = 0;
        for (const bonus of this.bonuses) {
            if (bonus.isActive() && bonus.type === type) {
                count++;
            }
        }
        return count;
    }

    /**
     * Pick random bonus type (port of bonus_pick_random_type @ 00412470)
     *
     * C code distribution (lines 447-522):
     * - Roll rand % 0xa2 (162)
     * - If roll < 13: WEAPON (ID 1) → ~8% chance
     * - If roll 13-14: Special ENERGIZER check (1/64 chance) → very rare
     * - Roll 15+: Distribute among types 1-14 in blocks of 10
     *   - 15-24: WEAPON, 25-34: POINTS, 35-44: HEALTH, 45-54: SHIELD
     *   - 55-64: FIRE_BULLETS, 65-74: ENERGIZER, 75-84: DOUBLE_EXPERIENCE
     *   - 85-94: NUKE, 95-104: FIREBLAST, 105-114: SHOCK_CHAIN
     *   - 115-124: REFLEX_BOOST, 125-134: WEAPON_POWER_UP, 135-144: SPEED
     *   - 145-154: FREEZE
     *   - 155+: POINTS (fallback)
     *
     * Retry loop (max 100 attempts) with gameplay filters:
     * - Block SHOCK_CHAIN during active chain
     * - Block FREEZE if freeze already active
     * - Block SHIELD if shield already active
     * - Block WEAPON if My Favourite Weapon perk active
     * - Block HEALTH if Death Clock perk active
     * - Block WEAPON if fire_bullets already on ground
     */
    private pickRandomBonusType(filterCtx?: {
        shockChainLinksLeft: number;
        freezeTimer: number;
        shieldTimer: number;
        hasDeathClock: boolean;
        hasFavouriteWeapon: boolean;
        hasFireBulletsOnGround: boolean;
    }): BonusType {
        // Types ordered to match C enum (1-14): WEAPON through FREEZE
        const types: BonusType[] = [
            BonusType.WEAPON,            // 1
            BonusType.POINTS,            // 2
            BonusType.HEALTH,            // 3
            BonusType.SHIELD,            // 4
            BonusType.FIRE_BULLETS,      // 5
            BonusType.ENERGIZER,         // 6
            BonusType.DOUBLE_EXPERIENCE, // 7
            BonusType.NUKE,              // 8
            BonusType.FIREBLAST,         // 9
            BonusType.SHOCK_CHAIN,       // 10
            BonusType.REFLEX_BOOST,      // 11
            BonusType.WEAPON_POWER_UP,   // 12
            BonusType.SPEED,             // 13
            BonusType.FREEZE,            // 14
        ];

        for (let attempt = 0; attempt < 100; attempt++) {
            // C code: rand % 162
            const rand = Math.floor(Math.random() * 162);
            let candidateType: BonusType;

            if (rand < 13) {
                candidateType = BonusType.WEAPON; // ~8% extra weapon chance
            } else if (rand < 15) {
                // Energizer is very rare in C code (1/64 chance after special roll)
                if (Math.floor(Math.random() * 64) === 0) {
                    candidateType = BonusType.ENERGIZER;
                } else {
                    // Fall through to normal distribution — treat as first slot (WEAPON)
                    candidateType = BonusType.WEAPON;
                }
            } else {
                // Distribute among types in blocks of 10
                const typeIndex = Math.floor((rand - 15) / 10);
                if (typeIndex >= 0 && typeIndex < types.length) {
                    candidateType = types[typeIndex];
                } else {
                    // 155+: fallback to POINTS
                    candidateType = BonusType.POINTS;
                }
            }

            // Apply gameplay filters (only if filterCtx provided)
            if (filterCtx) {
                // C line 482: block SHOCK_CHAIN during active chain
                if (filterCtx.shockChainLinksLeft >= 1 && candidateType === BonusType.SHOCK_CHAIN) continue;
                // C line 504: block FREEZE if freeze already active
                if (filterCtx.freezeTimer > 0 && candidateType === BonusType.FREEZE) continue;
                // C line 505-506: block SHIELD if shield already active
                if (filterCtx.shieldTimer > 0 && candidateType === BonusType.SHIELD) continue;
                // C line 507-508: block WEAPON if My Favourite Weapon perk active
                if (filterCtx.hasFavouriteWeapon && candidateType === BonusType.WEAPON) continue;
                // C line 509: block HEALTH if Death Clock perk active
                if (filterCtx.hasDeathClock && candidateType === BonusType.HEALTH) continue;
                // C line 510: block WEAPON if fire_bullets already on ground
                if (filterCtx.hasFireBulletsOnGround && candidateType === BonusType.WEAPON) continue;
            }

            return candidateType;
        }

        // C line 520: fallback after 100 retries
        return BonusType.POINTS;
    }

    /**
     * Update all bonuses
     *
     * When hasBonusMagnet is true, active bonuses are attracted toward the player
     * at MAGNET_SPEED px/s. This creates the "attract bonuses" effect described
     * by the Bonus Magnet perk (0x1b).
     */
    update(dt: number, hasBonusMagnet: boolean = false, playerX: number = 0, playerY: number = 0): void {
        for (const bonus of this.bonuses) {
            if (bonus.isActive()) {
                bonus.update(dt);

                // Bonus Magnet: attract active (non-picked-up) bonuses toward player
                // Skip weapon pickups — magnet only attracts power-up bonuses, not guns
                if (hasBonusMagnet && !bonus.pickedUp && bonus.type !== BonusType.WEAPON) {
                    const dx = playerX - bonus.x;
                    const dy = playerY - bonus.y;
                    const dist = Math.sqrt(dx * dx + dy * dy);
                    if (dist > 2.0) {
                        // Move toward player at 60 px/s
                        const speed = 60.0 * dt;
                        bonus.x += (dx / dist) * speed;
                        bonus.y += (dy / dist) * speed;
                    }
                }
            }
        }

        // Remove expired bonuses
        if (this.bonuses.length > 20) {
            this.bonuses = this.bonuses.filter((b) => b.isActive());
        }
    }

    /**
     * Check if player picks up any bonuses
     * Returns array of picked up bonuses
     *
     * C code: bonus_update @ line 6886: SQRT(dx*dx + dy*dy) < 26.0
     * Uses raw center-to-center distance, NOT radius sum.
     *
     * Implements Telekinetic perk (C line 25826-25829):
     * - Base pickup distance: 26.0
     * - With Telekinetic: multiplied range
     */
    checkPickups(player: Player, hasTelekinetic: boolean = false): Bonus[] {
        const pickedUp: Bonus[] = [];

        // C code: raw distance < 26.0 (line 6886)
        const basePickupDist = 26.0;
        // Telekinetic perk increases pickup range significantly
        const pickupDist = hasTelekinetic ? basePickupDist * 3.0 : basePickupDist;

        for (const bonus of this.bonuses) {
            if (!bonus.isActive()) continue;
            if (bonus.pickedUp) continue; // Already picked up, in decay animation

            // C: SQRT(bonus.pos - player.pos) < 26.0
            const dx = player.x - bonus.x;
            const dy = player.y - bonus.y;
            const distance = Math.sqrt(dx * dx + dy * dy);

            if (distance < pickupDist) {
                bonus.markPickedUp(); // Start post-pickup decay (0.5s at 3× rate)
                pickedUp.push(bonus);
            }
        }

        return pickedUp;
    }

    /**
     * Render all bonuses
     *
     * When spriteRenderer is provided and bonus sprites are loaded, uses the
     * bonuses.jaz atlas for proper sprite rendering (matching C code bonus_render).
     * Otherwise falls back to debug circle rendering.
     */
    render(grim: GrimInterface, spriteRenderer?: SpriteRenderer, animTimer?: number, elapsedMs?: number): void {
        const useSpriteRenderer = spriteRenderer && spriteRenderer.canDrawBonus();
        let bonusIndex = 0;

        for (const bonus of this.bonuses) {
            if (bonus.isActive()) {
                if (useSpriteRenderer) {
                    spriteRenderer!.drawBonus(
                        grim,
                        bonus.x,
                        bonus.y,
                        bonus.type,
                        bonus.amount,
                        bonus.timeLeft,
                        bonus.timeMax,
                        bonusIndex,
                        animTimer ?? 0,
                        elapsedMs ?? 0,
                    );
                } else {
                    bonus.render(grim);
                }
                bonusIndex++;
            }
        }
    }

    /**
     * Clear all bonuses
     */
    clear(): void {
        this.bonuses = [];
    }

    /**
     * Get active bonus count
     */
    getActiveCount(): number {
        return this.bonuses.filter((b) => b.isActive()).length;
    }

    /**
     * Get all bonus entries (active and inactive).
     * Used by proximity tooltip rendering.
     */
    getBonuses(): Bonus[] {
        return this.bonuses;
    }
}
