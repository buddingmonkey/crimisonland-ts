/**
 * BonusEffects - Bonus pickup effect handlers extracted from Game.ts.
 *
 * C code reference: bonus application at lines 6364-6483
 * Chain lightning propagation at lines 19290-19303
 */

import { BonusType } from '../../entities/Bonus';
import { clearReload } from '../../entities/PlayerWeapon';
import { gameConsole } from '../../console/Console';
import { SoundId } from '../../audio/SoundId';
import { PerkId } from '../PerkSystem';
import { ProjectileType } from '../../data/WeaponData';
import { BONUS_LABELS, BONUS_ICON_IDS } from '../../data/BonusLabels';
import { questSystem } from '../quest/QuestSystem';

/**
 * Duck-typed context for bonus effect functions.
 * Subset of Game fields needed by applyBonusEffect / handleChainLightning.
 */
export interface BonusEffectContext {
    player: {
        experience: number;
        health: number;
        shieldTimer: number;
        fireBulletsTimer: number;
        shotCooldown: number;
        reloadTimer: number;
        reloadActive: boolean;
        ammo: number;
        clipSize: number;
        energizerTimer: number;
        doubleXPTimer: number;
        reflexBoostTimer: number;
        weaponPowerUpTimer: number;
        speedBonusTimer: number;
        freezeTimer: number;
        switchWeapon(weaponId: number, perkSystem: any): void;
        getWeaponStats(): { name: string };
    } | null;
    perkSystem: { hasPerk(id: PerkId): boolean };
    soundSystem: { playAtPosition(id: SoundId, x: number, y: number, range: number): void };
    enemySpawner: {
        getActiveEnemies(): Array<{
            x: number;
            y: number;
            isAlive(): boolean;
            health: number;
            getRadius(): number;
            takeDamage(amount: number, type: number): void;
        }>;
    };
    weaponSystem: {
        spawnProjectile(x: number, y: number, angle: number, speed: number, damage: number, lifetime: number): any;
        spawnBonusProjectile(x: number, y: number, angle: number, type: ProjectileType, speedOverride?: number, damageOverride?: number, ownerId?: number): any;
    };
    cameraShake: { startShake(pulses: number, intensity: number): void };
    particleSystem: { spawnBurst(x: number, y: number, count: number): void };
    effectSystem: {
        spawnExplosionBurst(x: number, y: number, scale: number): void;
        spawnFreezeShard(x: number, y: number, angle: number): void;
        spawnFreezeShatter(x: number, y: number, angle: number): void;
        spawnFreezeFlash(x: number, y: number): void;
        spawnReflexHalo(x: number, y: number): void;
        spawnBurst(x: number, y: number, count: number): void;
        spawnShockwave(x: number, y: number, scale: number): void;
        spawnFireParticles(x: number, y: number, radius: number, count: number): void;
        spawnBonusPickupParticles(x: number, y: number): void;
    };
    addBonusHudSlot: (label: string, iconId: number, getTimer: () => number, timerKey: string) => void;
    nextProjectileId: number;
    shockChainLinksLeft: number;
    shockChainProjectileId: number;
}

/**
 * Apply bonus effect when picked up (C lines 6364-6483).
 */
export function applyBonusEffect(ctx: BonusEffectContext, bonus: any): void {
    if (!ctx.player) return;

    // Fix 9: Play bonus pickup sound (C line 23: sfx_play(sfx_ui_bonus))
    ctx.soundSystem.playAtPosition(SoundId.UI_BONUS, bonus.x, bonus.y, 800);

    // BONUS_ECONOMIST perk: 1.5× bonus durations (C: bonus_economist multiplier)
    const multiplier = ctx.perkSystem.hasPerk(PerkId.BONUS_ECONOMIST) ? 1.5 : 1.0;

    switch (bonus.type) {
        case BonusType.WEAPON:
            // Switch to picked up weapon (C: weapon_assign_player)
            ctx.player.switchWeapon(bonus.amount, ctx.perkSystem);
            const weaponName = ctx.player.getWeaponStats().name || 'Unknown';
            gameConsole.print(`Picked up ${weaponName}!`);
            break;

        case BonusType.POINTS:
            // Direct XP gain (C lines 6481-6483)
            ctx.player.experience += bonus.amount;
            gameConsole.print(`+${bonus.amount} XP!`);
            break;

        case BonusType.HEALTH:
            // C line 36-38: Medikit restores exactly 10 HP, cap at 100
            if (ctx.player.health < 100.0) {
                ctx.player.health = Math.min(ctx.player.health + 10.0, 100.0);
            }
            gameConsole.print('+10 health!');
            break;

        case BonusType.SHIELD:
            // Invulnerability timer (C lines 6364-6371)
            if (ctx.player.shieldTimer <= 0) {
                ctx.addBonusHudSlot(
                    BONUS_LABELS[BonusType.SHIELD],
                    BONUS_ICON_IDS[BonusType.SHIELD],
                    () => ctx.player!.shieldTimer,
                    'shield',
                );
            }
            ctx.player.shieldTimer += bonus.amount * multiplier;
            gameConsole.print('Shield activated!');
            break;

        case BonusType.FIRE_BULLETS:
            // Rapid fire mode (C lines 6409-6419)
            if (ctx.player.fireBulletsTimer <= 0) {
                ctx.addBonusHudSlot(
                    BONUS_LABELS[BonusType.FIRE_BULLETS],
                    BONUS_ICON_IDS[BonusType.FIRE_BULLETS],
                    () => ctx.player!.fireBulletsTimer,
                    'fire_bullets',
                );
            }
            ctx.player.fireBulletsTimer += multiplier * 5.0;
            // Reset weapon state for instant reload (C lines 6415-6418)
            // C also sets weapon_reset_latch = 0; intentionally omitted — the TS weapon system
            // has no latch mechanism, and shotCooldown + reloadTimer reset achieves the same effect.
            ctx.player.shotCooldown = 0.0;
            clearReload(ctx.player);
            ctx.player.ammo = ctx.player.clipSize;
            gameConsole.print('Fire Bullets activated!');
            break;

        case BonusType.ENERGIZER:
            // 8x XP multiplier (C lines 6420-6425)
            if (ctx.player.energizerTimer <= 0) {
                ctx.addBonusHudSlot(
                    BONUS_LABELS[BonusType.ENERGIZER],
                    BONUS_ICON_IDS[BonusType.ENERGIZER],
                    () => ctx.player!.energizerTimer,
                    'energizer',
                );
            }
            ctx.player.energizerTimer += multiplier * 8.0;
            gameConsole.print('Energizer! 8x XP!');
            break;

        case BonusType.DOUBLE_EXPERIENCE:
            // 2x XP multiplier (C lines 6426-6431)
            if (ctx.player.doubleXPTimer <= 0) {
                ctx.addBonusHudSlot(
                    BONUS_LABELS[BonusType.DOUBLE_EXPERIENCE],
                    BONUS_ICON_IDS[BonusType.DOUBLE_EXPERIENCE],
                    () => ctx.player!.doubleXPTimer,
                    'double_xp',
                );
            }
            ctx.player.doubleXPTimer += multiplier * 6.0;
            gameConsole.print('Double XP!');
            break;

        case BonusType.NUKE:
            // Area damage explosion (C lines 6432-6480)
            {
                const nukeX = bonus.x;
                const nukeY = bonus.y;
                const nukeRadius = 256.0;

                // Damage all enemies in radius (C lines 6464-6476)
                for (const enemy of ctx.enemySpawner.getActiveEnemies()) {
                    if (!enemy.isAlive()) continue;

                    const dx = enemy.x - nukeX;
                    const dy = enemy.y - nukeY;
                    const distance = Math.sqrt(dx * dx + dy * dy);

                    if (distance <= nukeRadius) {
                        // Damage formula: (256 - distance) * 5.0 (C line 6472)
                        const damage = (nukeRadius - distance) * 5.0;
                        if (damage > 0) {
                            enemy.takeDamage(damage, 3); // Damage type 3 = explosion
                            // Report kill to quest system so activeEnemyCount decrements
                            if (!enemy.isAlive()) {
                                questSystem.reportEnemyKilled();
                            }
                        }
                    }
                }

                // Spawn 4-7 pistol projectiles (C lines 6433-6448)
                const pistolCount = (Math.floor(Math.random() * 256) & 3) + 4; // (rand & 3) + 4
                for (let i = 0; i < pistolCount; i++) {
                    const angle = Math.floor(Math.random() * 0x274) * 0.01;
                    const speedScale = Math.floor(Math.random() * 50) * 0.01 + 0.5;
                    const pistolSpeed = 5400 * speedScale;
                    const pistolDamage = 25;
                    ctx.weaponSystem.spawnBonusProjectile(nukeX, nukeY, angle, ProjectileType.PISTOL, pistolSpeed, pistolDamage);
                }

                // Spawn 2 gauss gun projectiles (C lines 6450-6458)
                for (let i = 0; i < 2; i++) {
                    const angle = Math.floor(Math.random() * 0x274) * 0.01;
                    const gaussSpeed = 5400;
                    const gaussDamage = 100;
                    ctx.weaponSystem.spawnBonusProjectile(nukeX, nukeY, angle, ProjectileType.GAUSS_GUN, gaussSpeed, gaussDamage);
                }

                // Camera shake (C lines 6460-6461)
                ctx.cameraShake.startShake(20, 0.2);

                // Fix 6: Play nuke sounds (C lines 254-255)
                ctx.soundSystem.playAtPosition(SoundId.EXPLOSION_LARGE, nukeX, nukeY, 800);
                ctx.soundSystem.playAtPosition(SoundId.SHOCKWAVE, nukeX, nukeY, 800);

                // Explosion burst VFX (C line 235: effect_spawn_explosion_burst)
                ctx.effectSystem.spawnExplosionBurst(nukeX, nukeY, 1.0);

                gameConsole.print('NUKE!');
            }
            break;

        case BonusType.FIREBLAST:
            // 16 radial projectiles (C lines 6392-6408)
            {
                const fireblastX = bonus.x;
                const fireblastY = bonus.y;
                const projectileCount = 16; // 0x10 in C code (C line 6405)

                for (let i = 0; i < projectileCount; i++) {
                    const angle = i * 0.3926991; // π/8 radians, 22.5°
                    const proj = ctx.weaponSystem.spawnBonusProjectile(fireblastX, fireblastY, angle, ProjectileType.PLASMA_RIFLE, 5400);
                    proj.noBonusDrop = true; // C: bonus_spawn_guard (bonuses.c:169,182)
                }

                // Fix 8: Play fireblast sound
                ctx.soundSystem.playAtPosition(SoundId.EXPLOSION_MEDIUM, fireblastX, fireblastY, 800);

                gameConsole.print('Fireblast!');
            }
            break;

        case BonusType.SHOCK_CHAIN:
            // Chain lightning (C lines 6372-6391)
            {
                const shockX = bonus.x;
                const shockY = bonus.y;

                // Find nearest enemy (C line 6382)
                let nearestEnemy = null;
                let nearestDistance = Infinity;

                for (const enemy of ctx.enemySpawner.getActiveEnemies()) {
                    if (!enemy.isAlive()) continue;

                    const dx = enemy.x - shockX;
                    const dy = enemy.y - shockY;
                    const distance = Math.sqrt(dx * dx + dy * dy);

                    if (distance < nearestDistance) {
                        nearestDistance = distance;
                        nearestEnemy = enemy;
                    }
                }

                if (nearestEnemy) {
                    const dx = nearestEnemy.x - shockX;
                    const dy = nearestEnemy.y - shockY;
                    const angleToEnemy = Math.atan2(dy, dx);
                    const projectileAngle = angleToEnemy;

                    const projectileId = ctx.nextProjectileId++;
                    ctx.shockChainLinksLeft = 32; // 0x20
                    ctx.shockChainProjectileId = projectileId;

                    const projectile = ctx.weaponSystem.spawnBonusProjectile(
                        shockX,
                        shockY,
                        projectileAngle,
                        ProjectileType.ION_RIFLE,
                    );

                    projectile.isChainLightning = true;
                    projectile.chainProjectileId = projectileId;
                    projectile.noBonusDrop = true; // C: bonus_spawn_guard (bonuses.c:149,165)
                }

                // Fix 7: Play shock chain sound
                ctx.soundSystem.playAtPosition(SoundId.SHOCK_HIT_01, shockX, shockY, 800);

                gameConsole.print('Shock Chain!');
            }
            break;

        case BonusType.REFLEX_BOOST:
            // Slow motion effect (C lines 6263-6301)
            if (ctx.player.reflexBoostTimer <= 0) {
                ctx.addBonusHudSlot(
                    BONUS_LABELS[BonusType.REFLEX_BOOST],
                    BONUS_ICON_IDS[BonusType.REFLEX_BOOST],
                    () => ctx.player!.reflexBoostTimer,
                    'reflex_boost',
                );
            }
            ctx.player.reflexBoostTimer += bonus.amount * multiplier;
            // C bonuses.c lines 56-77: single expanding blue halo ring on pickup
            ctx.effectSystem.spawnReflexHalo(bonus.x, bonus.y);
            gameConsole.print('Reflex Boost!');
            break;

        case BonusType.WEAPON_POWER_UP:
            // Faster fire rate + instant reload (C lines 6302-6312)
            if (ctx.player.weaponPowerUpTimer <= 0) {
                ctx.addBonusHudSlot(
                    BONUS_LABELS[BonusType.WEAPON_POWER_UP],
                    BONUS_ICON_IDS[BonusType.WEAPON_POWER_UP],
                    () => ctx.player!.weaponPowerUpTimer,
                    'weapon_power_up',
                );
            }
            ctx.player.weaponPowerUpTimer += bonus.amount * multiplier;
            // C: weapon_reset_latch = 0 — omitted, purpose unclear from decompiled code
            ctx.player.shotCooldown = 0.0;
            clearReload(ctx.player);
            ctx.player.ammo = ctx.player.clipSize;
            gameConsole.print('Weapon Power-Up!');
            break;

        case BonusType.SPEED:
            // Movement speed boost (C lines 6313-6320)
            if (ctx.player.speedBonusTimer <= 0) {
                ctx.addBonusHudSlot(
                    BONUS_LABELS[BonusType.SPEED],
                    BONUS_ICON_IDS[BonusType.SPEED],
                    () => ctx.player!.speedBonusTimer,
                    'speed',
                );
            }
            ctx.player.speedBonusTimer += bonus.amount * multiplier;
            gameConsole.print('Speed Boost!');
            break;

        case BonusType.FREEZE:
            // Freeze timer (C bonuses.c:97-139)
            if (ctx.player.freezeTimer <= 0) {
                ctx.addBonusHudSlot(
                    BONUS_LABELS[BonusType.FREEZE],
                    BONUS_ICON_IDS[BonusType.FREEZE],
                    () => ctx.player!.freezeTimer,
                    'freeze',
                );
            }
            ctx.player.freezeTimer += bonus.amount * multiplier;
            // C bonuses.c:103-116: shatter enemies with health <= 0 (already dying)
            // Spawns 8 freeze shards + 1 freeze shatter per dying enemy, then deactivates
            for (const enemy of ctx.enemySpawner.getActiveEnemies()) {
                if (enemy.isAlive()) continue; // only health <= 0
                if (enemy.health > 0) continue;
                for (let i = 0; i < 8; i++) {
                    const randAngle = Math.floor(Math.random() * 0x264) * 0.01;
                    ctx.effectSystem.spawnFreezeShard(enemy.x, enemy.y, randAngle);
                }
                const shatterAngle = Math.floor(Math.random() * 0x264) * 0.01;
                ctx.effectSystem.spawnFreezeShatter(enemy.x, enemy.y, shatterAngle);
            }
            // C: expanding blue flash at bonus position (bonuses.c:117-134)
            ctx.effectSystem.spawnFreezeFlash(bonus.x, bonus.y);
            ctx.soundSystem.playAtPosition(SoundId.SHOCKWAVE, bonus.x, bonus.y, 800);
            gameConsole.print('Freeze!');
            break;
    }

    // C: bonuses.c lines 260-293 — spawn 12 blue-white celebration particles on pickup
    // Skipped for NUKE since it has its own explosion VFX
    if (bonus.type !== BonusType.NUKE) {
        ctx.effectSystem.spawnBonusPickupParticles(bonus.x, bonus.y);
    }
}

/**
 * Handle chain lightning propagation (C lines 19290-19303).
 * Called when a projectile hits an enemy.
 */
export function handleChainLightning(ctx: BonusEffectContext, projectile: any, hitEnemy: any): void {
    if (!projectile.isChainLightning) return;
    if (ctx.shockChainLinksLeft <= 0) return;
    if (projectile.chainProjectileId !== ctx.shockChainProjectileId) return;

    ctx.shockChainLinksLeft--;

    let nearestEnemy = null;
    let nearestDistance = Infinity;

    const activeEnemies = ctx.enemySpawner.getActiveEnemies();
    for (const enemy of activeEnemies) {
        if (enemy === hitEnemy) continue;
        if (!enemy.isAlive()) continue;

        const dx = enemy.x - hitEnemy.x;
        const dy = enemy.y - hitEnemy.y;
        const distance = Math.sqrt(dx * dx + dy * dy);

        if (distance > 100.0 && distance < nearestDistance) {
            nearestDistance = distance;
            nearestEnemy = enemy;
        }
    }

    if (nearestEnemy) {
        const dx = nearestEnemy.x - hitEnemy.x;
        const dy = nearestEnemy.y - hitEnemy.y;
        const angle = Math.atan2(dy, dx);
        const projectileAngle = angle;

        const newProjectileId = ctx.nextProjectileId++;
        ctx.shockChainProjectileId = newProjectileId;

        // C: projectile_spawn(pos, angle, ION_RIFLE, iVar7) — iVar7 is the hit enemy index
        // Setting ownerId to hit enemy's index prevents the chain from re-hitting the source
        const hitEnemyIndex = activeEnemies.indexOf(hitEnemy as any);

        const newProjectile = ctx.weaponSystem.spawnBonusProjectile(
            hitEnemy.x,
            hitEnemy.y,
            projectileAngle,
            ProjectileType.ION_RIFLE,
            undefined,  // speedOverride
            undefined,  // damageOverride
            hitEnemyIndex >= 0 ? hitEnemyIndex : undefined, // ownerId = hit enemy index
        );

        newProjectile.isChainLightning = true;
        newProjectile.chainProjectileId = newProjectileId;
        newProjectile.noBonusDrop = true; // C: bonus_spawn_guard (projectiles.c:397,406)
    }
}
