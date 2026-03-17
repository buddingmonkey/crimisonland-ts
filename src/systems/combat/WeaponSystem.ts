/**
 * WeaponSystem - Weapon firing and projectile management
 *
 * Handles weapon definitions, firing logic, and projectile pool.
 */

import { Projectile } from '../../entities/Projectile';
import type { Player } from '../../entities/Player';
import { ProjectileType, WEAPON_DATA } from '../../data/WeaponData';
import type { ParticleSystem } from '../effects/ParticleSystem'; // future use — weapon particle spawning
import type { EffectSystem } from '../effects/EffectSystem';

import type { PerkSystem } from '../PerkSystem';
import { PerkId } from '../PerkSystem';
import { calculateSpreadRecoveryMultiplier } from './WeaponModifier';
import { WeaponFlags } from '../../data/WeaponTypes';
import type { SoundSystem } from '../../audio/SoundSystem';
import type { ScoreSystem } from '../ScoreSystem';
import { SoundId } from '../../audio/SoundId';
import { questSystem } from '../quest/QuestSystem';

/**
 * Weapon system
 */
export class WeaponSystem {
    private projectiles: Projectile[] = [];
    private readonly maxProjectiles: number = 200;
    private soundSystem: SoundSystem | null = null;
    private scoreSystem: ScoreSystem | null = null;
    private particleSystem: ParticleSystem | null = null;
    private effectSystem: EffectSystem | null = null;

    /**
     * Fire weapon
     * C code reference: player_fire_weapon (player.c lines 1278-1800)
     */
    fireWeapon(player: Player, targetX: number, targetY: number, perkSystem: PerkSystem): void {
        // Check shot cooldown (C line 12709)
        if (player.shotCooldown > 0) {
            return;
        }

        if (!player.canFire(perkSystem)) return;

        // Check ammo
        let firedWithEmptyClip = false;
        if (player.ammo <= 0) {
            // REGRESSION_BULLETS / AMMUNITION_WITHIN: allow firing with empty clip (C: infinite ammo perks)
            // C code (bVar5): requires experience > 0 for regression bullets cost
            if ((perkSystem.hasPerk(PerkId.REGRESSION_BULLETS) && player.experience > 0) ||
                perkSystem.hasPerk(PerkId.AMMUNITION_WITHIN)) {
                player.ammo = 1; // Replenish 1 round so the shot fires; will be consumed below
                firedWithEmptyClip = true;
                // Cancel any active reload — C code: bVar5 fires regardless of reload state
                if (player.reloadActive) {
                    player.reloadActive = false;
                    player.reloadTimer = 0;
                }
            } else {
                // Start reload if not already reloading
                if (!player.reloadActive) {
                    const weaponStats = player.getWeaponStats();
                    player.reloadActive = true;

                    // Calculate reload time with modifiers (C: player_start_reload @ lines 24-33)
                    let reloadTime = weaponStats.reloadTime;

                    // Fastloader perk: 30% faster (C line 27-28)
                    if (perkSystem.hasPerk(PerkId.FASTLOADER)) {
                        reloadTime *= 0.7;
                    }

                    // Weapon Power-up bonus: 40% faster, stacks with Fastloader (C line 30-31)
                    if (player.weaponPowerUpTimer > 0) {
                        reloadTime *= 0.6;
                    }

                    player.reloadTimer = reloadTime;
                    player.reloadTimerMax = reloadTime; // For UI progress

                    // Play reload sound (C line 12750)
                    if (this.soundSystem && weaponStats.reloadSfxId !== undefined) {
                        this.soundSystem.playAtPosition(weaponStats.reloadSfxId, player.x, player.y, 800);
                    }
                }
                return;
            }
        }

        // Get weapon stats from new data
        const weaponStats = player.getWeaponStats();

        // Calculate base aim angle from player to target
        const baseAngle = Math.atan2(targetY - player.y, targetX - player.x);

        // Gun barrel offset: spawn projectiles from gun tip, not player center
        // C code: fcos/fsin(fVar15) * 25.0 offset (lines 1484-1487, 1588-1590, etc.)
        const barrelOffset = 20.0;
        const spawnX = player.x + Math.cos(baseAngle) * barrelOffset;
        const spawnY = player.y + Math.sin(baseAngle) * barrelOffset;

        // === Fire Bullets dedicated path (C: projectile_spawn lines 28-35) ===
        // When fire bullets bonus is active, C overrides ALL projectile types
        // to PROJECTILE_TYPE_FIRE_BULLETS which gets damagePool=240 (massive penetration)
        // C: fire bullets override only affects projectile_spawn(), NOT fx_spawn_particle().
        // Particle-based weapons (Flamethrower=6, Blow Torch=15, HR Flamer=16) are
        // unaffected by fire bullets in the original game — they keep firing particles.
        const isParticleWeapon = player.weaponId === 6 || player.weaponId === 15 || player.weaponId === 16;
        if (player.fireBulletsTimer > 0 && !isParticleWeapon) {
            // Play fire SFX
            if (this.soundSystem) {
                this.soundSystem.playAtPosition(SoundId.FLAMER_FIRE_01, player.x, player.y, 800);
            }

            // Determine pellet count from weapon table
            const pelletCount = weaponStats.projectileCount;

            // Fire bullet cooldown: C code uses the weapon table's own shot_cooldown
            player.shotCooldown = weaponStats.shotCooldown;

            // C override: projectile type forced to FIRE_BULLETS (projectiles.c L31-35)
            // This gives damagePool=240 via initDamagePool(), enabling penetration
            for (let i = 0; i < pelletCount; i++) {
                const randSpread = (Math.floor(Math.random() * 200) - 100) * 0.0015;
                const fireAngle = baseAngle + randSpread;

                const proj = this.spawnProjectileTyped(
                    player,
                    fireAngle,
                    weaponStats.projectileSpeed,
                    weaponStats.damage,
                    ProjectileType.FIRE_BULLETS,
                    spawnX,
                    spawnY,
                );
                proj.hasFireVisual = true;
            }

            // Muzzle flash (C: 0.413 alpha)
            player.muzzleFlashAlpha += 0.413;
            if (player.muzzleFlashAlpha > 1.0) player.muzzleFlashAlpha = 1.0;

            // Consume ammo
            player.ammo -= weaponStats.ammoCost ?? 1.0;

            // C: Regression Bullets / Ammunition Within — cost for firing with empty clip
            if (firedWithEmptyClip) {
                if (perkSystem.hasPerk(PerkId.REGRESSION_BULLETS)) {
                    player.experience = Math.max(0, player.experience - 50);
                } else if (perkSystem.hasPerk(PerkId.AMMUNITION_WITHIN)) {
                    player.health -= 1.0;
                }
            }

            // Add spread heat (C lines 13706-13709)
            if (!perkSystem.hasPerk(PerkId.SHARPSHOOTER)) {
                player.spreadHeat += weaponStats.spreadHeat * 1.3;
            }
            if (player.spreadHeat > player.MAX_SPREAD_HEAT) {
                player.spreadHeat = player.MAX_SPREAD_HEAT;
            }

            // Prune projectile pool if needed
            if (this.projectiles.length > this.maxProjectiles) {
                this.projectiles = this.projectiles.filter((p) => p.isActive());
            }

            // Record shot for accuracy tracking
            this.scoreSystem?.recordShot();
            return; // Skip generic fire path
        }

        // Per-weapon switch: weapons with custom fire behavior (C player_fire_weapon)
        // These bypass the generic projectile loop
        let handled = false;

        switch (player.weaponId) {
            case 7: {
                // Plasma Rifle (C weapon 0x09, line 1508-1511) — TS weapon ID 7
                // C: projectile_spawn(&pos, angle, PROJECTILE_TYPE_PLASMA_RIFLE, owner_id)
                // Fires a single plasma projectile per shot (rapid-fire stream weapon)
                this.spawnProjectileTyped(
                    player,
                    baseAngle,
                    weaponStats.projectileSpeed,
                    weaponStats.damage,
                    ProjectileType.PLASMA_RIFLE,
                    spawnX,
                    spawnY,
                    weaponStats,
                );
                handled = true;
                break;
            }

            case 9: {
                // Plasma Minigun (C weapon 0x0B, player.c line 1581-1584) — TS weapon ID 9
                // C: projectile_spawn(&pos, angle, PROJECTILE_TYPE_PLASMA_MINIGUN, owner_id)
                // Fires a SINGLE plasma minigun projectile per shot (despite weapon table pellet_count=3)
                this.spawnProjectileTyped(
                    player,
                    baseAngle,
                    weaponStats.projectileSpeed,
                    weaponStats.damage,
                    ProjectileType.PLASMA_MINIGUN,
                    spawnX,
                    spawnY,
                    weaponStats,
                );
                handled = true;
                break;
            }

            case 8: {
                // Multi-Plasma (C weapon 0x0A, lines 1513-1528) — TS weapon ID 8
                // 5 shots: 3 PLASMA_RIFLE at center/±0.314, 2 PLASMA_MINIGUN at ±0.524
                const angle = baseAngle;
                this.spawnProjectileTyped(
                    player,
                    angle - 0.31415927,
                    weaponStats.projectileSpeed,
                    weaponStats.damage,
                    ProjectileType.PLASMA_RIFLE,
                    spawnX,
                    spawnY,
                    weaponStats,
                );
                this.spawnProjectileTyped(
                    player,
                    angle - 0.5235988,
                    weaponStats.projectileSpeed,
                    weaponStats.damage,
                    ProjectileType.PLASMA_MINIGUN,
                    spawnX,
                    spawnY,
                    weaponStats,
                );
                this.spawnProjectileTyped(
                    player,
                    angle,
                    weaponStats.projectileSpeed,
                    weaponStats.damage,
                    ProjectileType.PLASMA_RIFLE,
                    spawnX,
                    spawnY,
                    weaponStats,
                );
                this.spawnProjectileTyped(
                    player,
                    angle + 0.5235988,
                    weaponStats.projectileSpeed,
                    weaponStats.damage,
                    ProjectileType.PLASMA_MINIGUN,
                    spawnX,
                    spawnY,
                    weaponStats,
                );
                this.spawnProjectileTyped(
                    player,
                    angle + 0.31415927,
                    weaponStats.projectileSpeed,
                    weaponStats.damage,
                    ProjectileType.PLASMA_RIFLE,
                    spawnX,
                    spawnY,
                    weaponStats,
                );
                handled = true;
                break;
            }

            case 13: {
                // Mean Minigun (TS weapon ID 13, C weapon 0x07, lines 1755-1769 in C code)
                // 14 PLASMA_MINIGUN pellets with random spread ±0.256 rad, speed scale 1.0-2.0
                for (let i = 0; i < 14; i++) {
                    const randSpread = (((Math.random() * 256) | 0) - 128) * 0.002;
                    const proj = this.spawnProjectileTyped(
                        player,
                        baseAngle + randSpread,
                        weaponStats.projectileSpeed,
                        weaponStats.damage,
                        ProjectileType.PLASMA_MINIGUN,
                        spawnX,
                        spawnY,
                        weaponStats,
                    );
                    // Speed scale: (rand() % 100) * 0.01 + 1.0 = [1.0, 2.0)
                    const speedScale = ((Math.random() * 100) | 0) * 0.01 + 1.0;
                    proj.vx *= speedScale;
                    proj.vy *= speedScale;
                }
                handled = true;
                break;
            }

            case 14: {
                // Plasma Shotgun (TS weapon ID 14, C weapon 0x0E, player.c lines 1755-1769)
                // 14 PLASMA_MINIGUN pellets with random spread ±0.256 rad, speed scale 1.0-2.0
                // C: (rand() & 0xFF - 0x80) * 0.002 + baseAngle
                // C: speed_scale = (rand() % 100) * 0.01 + 1.0
                for (let i = 0; i < 14; i++) {
                    const randSpread = (((Math.random() * 256) | 0) - 128) * 0.002;
                    const proj = this.spawnProjectileTyped(
                        player,
                        baseAngle + randSpread,
                        weaponStats.projectileSpeed,
                        weaponStats.damage,
                        ProjectileType.PLASMA_MINIGUN,
                        spawnX,
                        spawnY,
                        weaponStats,
                    );
                    const speedScale = ((Math.random() * 100) | 0) * 0.01 + 1.0;
                    proj.vx *= speedScale;
                    proj.vy *= speedScale;
                }
                handled = true;
                break;
            }

            case 24: {
                // Gauss Shotgun (TS weapon ID 24, C weapon 0x1E, lines 1586-1620)
                // 6 GAUSS_GUN pellets with random spread ±0.2 rad, speed scale 1.4-2.2
                for (let i = 0; i < 6; i++) {
                    const randSpread = (((Math.random() * 200) | 0) - 100) * 0.002;
                    const proj = this.spawnProjectileTyped(
                        player,
                        baseAngle + randSpread,
                        weaponStats.projectileSpeed,
                        weaponStats.damage,
                        ProjectileType.GAUSS_GUN,
                        spawnX,
                        spawnY,
                        weaponStats,
                    );
                    const speedScale = ((Math.random() * 80) | 0) * 0.01 + 1.4;
                    proj.vx *= speedScale;
                    proj.vy *= speedScale;
                }
                handled = true;
                break;
            }

            case 23: {
                // Ion Shotgun (TS weapon ID 23, C weapon 0x1F, lines 1565-1579)
                // 8 ION_MINIGUN pellets with random spread ±0.26 rad, speed scale 1.4-2.2
                for (let i = 0; i < 8; i++) {
                    const randSpread = (((Math.random() * 200) | 0) - 100) * 0.0026;
                    const proj = this.spawnProjectileTyped(
                        player,
                        baseAngle + randSpread,
                        weaponStats.projectileSpeed,
                        weaponStats.damage,
                        ProjectileType.ION_MINIGUN,
                        spawnX,
                        spawnY,
                        weaponStats,
                    );
                    const speedScale = ((Math.random() * 80) | 0) * 0.01 + 1.4;
                    proj.vx *= speedScale;
                    proj.vy *= speedScale;
                }
                handled = true;
                break;
            }

            case 11: {
                // Rocket Launcher (C weapon 0x0C, player.c lines 1622-1645) — TS weapon ID 11
                // C: fx_spawn_secondary_projectile(&pos, angle, SECONDARY_PROJECTILE_TYPE_ROCKET)
                // Fires a SINGLE rocket projectile per shot
                // C initial speed: cos/sin(angle) * 90.0 (effects.c L294-296)
                this.spawnProjectileTyped(
                    player,
                    baseAngle,
                    90.0,
                    weaponStats.damage,
                    ProjectileType.ROCKET,
                    spawnX,
                    spawnY,
                    weaponStats,
                );
                handled = true;
                break;
            }

            case 12: {
                // Seeker Rockets (C weapon 0x0D, player.c line 1748) — TS weapon ID 12
                // C: fx_spawn_secondary_projectile(&local_10, fVar2, SECONDARY_PROJECTILE_TYPE_SEEKER_ROCKET)
                // Fires a SINGLE seeker rocket per shot (weapon table pellet_count=5 is the type ID, not count)
                // C initial speed: seeker override cos/sin(angle) * 190.0 (effects.c L300-301)
                this.spawnProjectileTyped(
                    player,
                    baseAngle,
                    190.0,
                    weaponStats.damage,
                    ProjectileType.SEEKER_ROCKET,
                    spawnX,
                    spawnY,
                    weaponStats,
                );
                handled = true;
                break;
            }

            case 17: {
                // Mini Rocket Swarmers (C weapon 0x11, lines 1672-1708)
                // Fan of seeker rockets equal to ammo count, centered around aim direction.
                // C code had -PI in startAngle + -PI/2 in fx_spawn_secondary_projectile,
                // but those offsets were C heading coordinate system artifacts.
                // TS baseAngle from atan2() is already the correct aim direction.
                // 60° arc (1.0471976 rad) divided evenly among rockets.
                const ammo = player.ammo;
                const spacing = 1.0471976 / ammo; // Per-rocket step within 60° arc
                const startAngle = baseAngle - 0.5235988; // Center fan around aim (half-arc offset)
                for (let i = 0; i < ammo; i++) {
                    const angle = startAngle + spacing * i;
                    // C fx_spawn_secondary_projectile applies cos/sin(angle - PI/2) * 190,
                    // but that -PI/2 is a C coordinate system offset (heading vs velocity).
                    // TS baseAngle from atan2() is already in velocity coordinates, so no offset needed.
                    const seekerSpeed = 190.0;
                    const vx = Math.cos(angle) * seekerSpeed;
                    const vy = Math.sin(angle) * seekerSpeed;
                    const proj = new Projectile(
                        spawnX,
                        spawnY,
                        vx,
                        vy,
                        weaponStats.damage,
                        2.0, // C: secondary projectile life_timer = 2.0
                        -1,
                        ProjectileType.SEEKER_ROCKET,
                    );
                    this.initDamagePool(proj);
                    proj.hitRadius = 8.0; // C: creature_find_in_radius(pos, 8.0, 0) for all rockets
                    this.projectiles.push(proj);
                    this.initRocketProps(proj);
                }
                // Mini rockets consume ALL ammo (C line 1707: local_38 = ammo)
                player.ammo = 0;
                handled = true;
                break;
            }

            case 18: {
                // Rocket Minigun (C weapon 0x12, player.c lines 1709-1724)
                // C: fx_spawn_secondary_projectile(&pos, angle, SECONDARY_PROJECTILE_TYPE_ROCKET_MINIGUN)
                // Fires a SINGLE rocket minigun projectile per shot (dedicated handler overrides pellet_count=8)
                // C initial speed: cos/sin(angle) * 90.0 (effects.c L294-296)
                this.spawnProjectileTyped(
                    player,
                    baseAngle,
                    90.0,
                    weaponStats.damage,
                    ProjectileType.ROCKET_MINIGUN,
                    spawnX,
                    spawnY,
                    weaponStats,
                );
                handled = true;
                break;
            }

            case 3: {
                // Sawed-off Shotgun (C weapon 0x04, player.c line 1452)
                // 12 SHOTGUN pellets with random spread ±0.4 rad, speed scale 1.0-2.0
                // C: (int)local_28 * 0.004 — wider spread than regular shotgun's 0.0013
                for (let i = 0; i < 12; i++) {
                    const randSpread = (((Math.random() * 200) | 0) - 100) * 0.004;
                    const proj = this.spawnProjectileTyped(
                        player,
                        baseAngle + randSpread,
                        weaponStats.projectileSpeed,
                        weaponStats.damage,
                        ProjectileType.SHOTGUN,
                        spawnX,
                        spawnY,
                        weaponStats,
                    );
                    const speedScale = ((Math.random() * 100) | 0) * 0.01 + 1.0;
                    proj.vx *= speedScale;
                    proj.vy *= speedScale;
                }
                handled = true;
                break;
            }

            case 6: {
                // Flamethrower (C weapon 0x08, lines 1459-1463)
                // C: fx_spawn_particle(&pos, fVar14, &move_dx, 1.0)
                // C's fVar14 = heading - PI/2, but TS baseAngle = atan2(dy,dx)
                // which is the direct aim direction (no offset needed).
                if (this.particleSystem) {
                    this.particleSystem.spawnFastParticle(spawnX, spawnY, baseAngle, 1.0);
                }
                handled = true;
                break;
            }

            case 15: {
                // Blow Torch (C weapon 0x0F, lines 1474-1481)
                // C: fx_spawn_particle then style_id = 1; local_38 = 0.05
                if (this.particleSystem) {
                    const idx = this.particleSystem.spawnFastParticle(spawnX, spawnY, baseAngle, 1.0);
                    if (idx !== -1) {
                        this.particleSystem.setParticleStyleId(idx, 1);
                    }
                }
                handled = true;
                break;
            }

            case 16: {
                // HR Flamer (C weapon 0x10, lines 1465-1472)
                // C: fx_spawn_particle then style_id = 2; local_38 = 0.1
                if (this.particleSystem) {
                    const idx = this.particleSystem.spawnFastParticle(spawnX, spawnY, baseAngle, 1.0);
                    if (idx !== -1) {
                        this.particleSystem.setParticleStyleId(idx, 2);
                    }
                }
                handled = true;
                break;
            }

            case 19: {
                // Pulse Gun (C weapon 0x13, player.c line 1530-1533) — TS weapon ID 19
                // C: projectile_spawn(&pos, angle, PROJECTILE_TYPE_PULSE_GUN, owner_id)
                // Fires a SINGLE pulse projectile per shot (despite weapon table pellet_count)
                this.spawnProjectileTyped(
                    player,
                    baseAngle,
                    weaponStats.projectileSpeed,
                    weaponStats.damage,
                    ProjectileType.PULSE_GUN,
                    spawnX,
                    spawnY,
                    weaponStats,
                );
                handled = true;
                break;
            }

            case 20: {
                // Ion Rifle (C weapon 0x15, player.c line 1545-1548) — TS weapon ID 20
                // C: projectile_spawn(&pos, angle, PROJECTILE_TYPE_ION_RIFLE, owner_id)
                // Fires a SINGLE ion rifle projectile per shot
                this.spawnProjectileTyped(
                    player,
                    baseAngle,
                    weaponStats.projectileSpeed,
                    weaponStats.damage,
                    ProjectileType.ION_RIFLE,
                    spawnX,
                    spawnY,
                    weaponStats,
                );
                handled = true;
                break;
            }

            case 21: {
                // Ion Minigun (C weapon 0x16, player.c line 1550-1553) — TS weapon ID 21
                // C: projectile_spawn(&pos, angle, PROJECTILE_TYPE_ION_MINIGUN, owner_id)
                // Fires a SINGLE ion minigun projectile per shot
                this.spawnProjectileTyped(
                    player,
                    baseAngle,
                    weaponStats.projectileSpeed,
                    weaponStats.damage,
                    ProjectileType.ION_MINIGUN,
                    spawnX,
                    spawnY,
                    weaponStats,
                );
                handled = true;
                break;
            }

            case 22: {
                // Ion Cannon (C weapon 0x17, player.c line 1555-1558) — TS weapon ID 22
                // C: projectile_spawn(&pos, angle, PROJECTILE_TYPE_ION_CANNON, owner_id)
                // Fires a SINGLE ion cannon projectile per shot
                this.spawnProjectileTyped(
                    player,
                    baseAngle,
                    weaponStats.projectileSpeed,
                    weaponStats.damage,
                    ProjectileType.ION_CANNON,
                    spawnX,
                    spawnY,
                    weaponStats,
                );
                handled = true;
                break;
            }

            case 25: {
                // Plasma Cannon (C weapon 0x1C, player.c line 1560-1563) — TS weapon ID 25
                // C: projectile_spawn(&pos, angle, PROJECTILE_TYPE_PLASMA_CANNON, owner_id)
                // Fires a SINGLE plasma cannon projectile per shot
                this.spawnProjectileTyped(
                    player,
                    baseAngle,
                    weaponStats.projectileSpeed,
                    weaponStats.damage,
                    ProjectileType.PLASMA_CANNON,
                    spawnX,
                    spawnY,
                    weaponStats,
                );
                handled = true;
                break;
            }

            case 28: {
                // Splitter Gun (C weapon 0x1D, player.c line 1540-1543) — TS weapon ID 28
                // C: projectile_spawn(&pos, angle, PROJECTILE_TYPE_SPLITTER_GUN, owner_id)
                // Fires a SINGLE splitter projectile per shot (splits on hit)
                this.spawnProjectileTyped(
                    player,
                    baseAngle,
                    weaponStats.projectileSpeed,
                    weaponStats.damage,
                    ProjectileType.SPLITTER_GUN,
                    spawnX,
                    spawnY,
                    weaponStats,
                );
                handled = true;
                break;
            }
        }

        if (!handled) {
            // Generic fire path for all other weapons
            for (let i = 0; i < weaponStats.projectileCount; i++) {
                // C code positional spread system (lines 13177-13189)
                const targetDx = targetX - player.x;
                const targetDy = targetY - player.y;
                const targetDistance = Math.sqrt(targetDx * targetDx + targetDy * targetDy);
                const spreadDistance = targetDistance * 0.5;

                // Random spread angle (C: rand() & 0x1FF * 0.012271847 ≈ 2*PI/512)
                const spreadAngle = Math.random() * 512 * 0.012271847;

                // Spread magnitude (C: distance * spread_heat * (rand & 0x1FF) * 1/512)
                const spreadMagnitude = spreadDistance * player.spreadHeat * (Math.random() * 512) * 0.001953125;

                // Offset the aim point by spread amount in a random direction
                const aimX = targetX + Math.cos(spreadAngle) * spreadMagnitude;
                const aimY = targetY + Math.sin(spreadAngle) * spreadMagnitude;

                // Per-pellet spread for shotguns (C player.c lines 1382-1394)
                let randSpread = 0;
                if (weaponStats.pelletSpreadMultiplier !== undefined) {
                    randSpread = (Math.floor(Math.random() * 200) - 100) * weaponStats.pelletSpreadMultiplier;
                }

                // Recalculate firing angle from player to spread-adjusted aim point
                const finalAngle = Math.atan2(aimY - player.y, aimX - player.x) + randSpread;

                // Calculate velocity with optional per-pellet speed scale
                let speed = weaponStats.projectileSpeed;
                if (weaponStats.pelletSpreadMultiplier !== undefined) {
                    const speedScale = Math.floor(Math.random() * 100) * 0.01 + 1.0;
                    speed *= speedScale;
                }

                // Projectile type from weapon stats (fire bullets use the dedicated path above)
                const effectiveProjectileType = weaponStats.projectileType;

                // Spawn projectile with type from weapon stats (or fire bullets override)
                const projectile = new Projectile(
                    spawnX,
                    spawnY,
                    Math.cos(finalAngle) * speed,
                    Math.sin(finalAngle) * speed,
                    weaponStats.damage,
                    0.4, // C: life_timer = 0.4 for ALL projectiles
                    -1,
                    effectiveProjectileType,
                );

                // Set C-accurate damagePool based on projectile type (C: projectile_spawn)
                this.initDamagePool(projectile);

                // Set C-accurate damage properties for distance-based formula
                if (weaponStats.damageScale !== undefined) {
                    projectile.originX = player.x;
                    projectile.originY = player.y;
                    projectile.damageScale = weaponStats.damageScale;
                }
                if (weaponStats.hitRadius !== undefined) {
                    projectile.hitRadius = weaponStats.hitRadius;
                }

                this.projectiles.push(projectile);
            }
        }

        // Consume ammo (unless already consumed by per-weapon handler)
        if (!handled || player.weaponId !== 17) {
            const ammoCost = weaponStats.ammoCost ?? 1.0;
            player.ammo -= ammoCost;
        }

        // C: Regression Bullets / Ammunition Within — cost for firing with empty clip
        // Regression Bullets takes priority (C perks_generate_choices lines 100-105)
        if (firedWithEmptyClip) {
            if (perkSystem.hasPerk(PerkId.REGRESSION_BULLETS)) {
                player.experience = Math.max(0, player.experience - 50);
            } else if (perkSystem.hasPerk(PerkId.AMMUNITION_WITHIN)) {
                player.health -= 1.0;
            }
        }

        // Set shot cooldown from weapon table (C line 12872-12873)
        let cooldown = weaponStats.shotCooldown;

        // Fastshot perk: 12% faster (C lines 13437-13438)
        if (perkSystem.hasPerk(PerkId.FASTSHOT)) {
            cooldown *= 0.88;
        }

        // Sharpshooter perk: 5% slower (C lines 13440-13441)
        if (perkSystem.hasPerk(PerkId.SHARPSHOOTER)) {
            cooldown *= 1.05;
        }

        player.shotCooldown = cooldown;

        // Shell casing ejection (C: player.c lines 1206-1241)
        // Only for weapons with flag & 1 (AUTOMATIC = ballistic weapons that eject casings)
        if ((weaponStats.flags & WeaponFlags.AUTOMATIC) && this.effectSystem) {
            this.effectSystem.spawnShellCasing(spawnX, spawnY, baseAngle);
        }

        // Set muzzle flash (C line 36784-36786)
        player.muzzleFlashAlpha += weaponStats.muzzleFlashAlpha;
        if (player.muzzleFlashAlpha > 1.0) {
            player.muzzleFlashAlpha = 1.0;
        }

        // Add spread heat (C lines 13706-13709)
        if (!perkSystem.hasPerk(PerkId.SHARPSHOOTER)) {
            player.spreadHeat += weaponStats.spreadHeat * 1.3;
        }

        // Cap spread heat (C lines 13434-13435)
        if (player.spreadHeat > player.MAX_SPREAD_HEAT) {
            player.spreadHeat = player.MAX_SPREAD_HEAT;
        }

        // Prune projectile pool if needed
        if (this.projectiles.length > this.maxProjectiles) {
            this.projectiles = this.projectiles.filter((p) => p.isActive());
        }

        // Play weapon fire sound (C lines 12877-12878)
        if (this.soundSystem && weaponStats.shotSfxId !== undefined) {
            const screenWidth = 800;
            const variantCount = weaponStats.shotSfxVariantCount ?? 1;
            const sfxId = (weaponStats.shotSfxId as number) + Math.floor(Math.random() * variantCount);
            this.soundSystem.playAtPosition(sfxId, player.x, player.y, screenWidth);
        }

        // Record shot for accuracy tracking
        this.scoreSystem?.recordShot();
    }

    /**
     * Spawn a projectile of a specific type (for per-weapon custom fire patterns)
     * C code reference: projectile_spawn (various weapon switch cases)
     */
    private spawnProjectileTyped(
        player: Player,
        angle: number,
        speed: number,
        damage: number,
        projectileType: ProjectileType,
        spawnX?: number,
        spawnY?: number,
        weaponStats?: { damageScale?: number; hitRadius?: number },
    ): Projectile {
        const sx = spawnX ?? player.x;
        const sy = spawnY ?? player.y;
        const vx = Math.cos(angle) * speed;
        const vy = Math.sin(angle) * speed;
        // C: secondary projectiles (rockets) use life_timer = 2.0 (effects.c L290)
        // C: regular projectiles use life_timer = 0.4 (projectiles.c)
        const isRocketType =
            projectileType === ProjectileType.ROCKET ||
            projectileType === ProjectileType.SEEKER_ROCKET ||
            projectileType === ProjectileType.ROCKET_MINIGUN;
        const lifetime = isRocketType ? 2.0 : 0.4;
        const projectile = new Projectile(
            sx,
            sy,
            vx,
            vy,
            damage,
            lifetime,
            -1,
            projectileType,
        );
        // Set C-accurate damagePool
        this.initDamagePool(projectile);

        // Set C-accurate damage properties for distance-based formula
        // C: damage = ((100/dist) * damageScale * 30 + 10) * 0.95
        if (weaponStats?.damageScale !== undefined) {
            projectile.originX = player.x;
            projectile.originY = player.y;
            projectile.damageScale = weaponStats.damageScale;
        }
        if (weaponStats?.hitRadius !== undefined) {
            projectile.hitRadius = weaponStats.hitRadius;
        }

        this.projectiles.push(projectile);

        // Initialize rocket physics properties (C: secondary projectile pool)
        // Must be set after push so isRocket flag is active during update
        this.initRocketProps(projectile);

        return projectile;
    }

    /**
     * Set particle system reference for fire weapon particle spawning
     * C code: fire weapons (flamethrower, blow torch, HR flamer) use fx_spawn_particle
     * instead of projectile_spawn — particles are in a separate pool.
     */
    setParticleSystem(particleSystem: ParticleSystem): void {
        this.particleSystem = particleSystem;
    }

    /**
     * Set effect system reference for shell casing spawning
     * C code: weapons with flag & 1 eject shell casings via effect_spawn(0x12, ...)
     */
    setEffectSystem(effectSystem: EffectSystem): void {
        this.effectSystem = effectSystem;
    }

    /**
     * Set sound system reference
     */
    setSoundSystem(soundSystem: SoundSystem): void {
        this.soundSystem = soundSystem;
    }

    /**
     * Set score system reference (for shot accuracy tracking)
     */
    setScoreSystem(scoreSystem: ScoreSystem): void {
        this.scoreSystem = scoreSystem;
    }

    /**
     * Update spread heat recovery
     * Spread heat decreases over time when not firing
     * C code reference: estimated from gameplay behavior
     */
    updateSpreadRecovery(player: Player, dt: number, perkSystem?: PerkSystem): void {
        if (player.spreadHeat > 0) {
            // C: Sharpshooter gives 2× spread recovery speed (Fix 14)
            const recoveryMult = perkSystem ? calculateSpreadRecoveryMultiplier(perkSystem) : 1.0;
            player.spreadHeat -= player.SPREAD_RECOVERY_RATE * recoveryMult * dt;
            if (player.spreadHeat < 0) {
                player.spreadHeat = 0;
            }
        }
    }

    /**
     * Spawn a projectile directly (for bonus effects)
     * C code reference: projectile_spawn @ various lines
     */
    spawnProjectile(
        x: number,
        y: number,
        angle: number,
        speed: number,
        damage: number,
        ownerId: number = -100,
    ): Projectile {
        const vx = Math.cos(angle) * speed;
        const vy = Math.sin(angle) * speed;

        const projectile = new Projectile(x, y, vx, vy, damage, 0.4, ownerId); // C: life_timer = 0.4
        this.initDamagePool(projectile);
        this.projectiles.push(projectile);

        // Prune if needed
        if (this.projectiles.length > this.maxProjectiles) {
            this.projectiles = this.projectiles.filter((p) => p.isActive());
        }

        return projectile;
    }

    /**
     * Spawn a typed projectile for bonus effects (Nuke, Fireblast, Shock Chain).
     * Looks up WEAPON_DATA for default speed/damage by ProjectileType.
     * C code reference: projectile_spawn with explicit type (bonuses.c)
     */
    spawnBonusProjectile(
        x: number,
        y: number,
        angle: number,
        type: ProjectileType,
        speedOverride?: number,
        damageOverride?: number,
        ownerId: number = -100,
    ): Projectile {
        // Look up weapon data for this projectile type to get default speed/damage
        let speed = speedOverride ?? 400;
        let damage = damageOverride ?? 10;
        if (speedOverride === undefined || damageOverride === undefined) {
            for (const wid of Object.keys(WEAPON_DATA)) {
                const ws = WEAPON_DATA[Number(wid)];
                if (ws.projectileType === type) {
                    if (speedOverride === undefined) speed = ws.projectileSpeed;
                    if (damageOverride === undefined) damage = ws.damage;
                    break;
                }
            }
        }

        const vx = Math.cos(angle) * speed;
        const vy = Math.sin(angle) * speed;
        const projectile = new Projectile(x, y, vx, vy, damage, 0.4, ownerId, type);
        this.initDamagePool(projectile);

        // Set damageScale from weapon data (C: weapon_table[type].damage_scale)
        // C always uses distance-based damage: ((100/dist) * damageScale * 30 + 10) * 0.95
        for (const wid of Object.keys(WEAPON_DATA)) {
            const ws = WEAPON_DATA[Number(wid)];
            if (ws.projectileType === type && ws.damageScale !== undefined) {
                projectile.damageScale = ws.damageScale;
                projectile.originX = x;
                projectile.originY = y;
                break;
            }
        }

        this.projectiles.push(projectile);

        // Prune if needed
        if (this.projectiles.length > this.maxProjectiles) {
            this.projectiles = this.projectiles.filter((p) => p.isActive());
        }

        return projectile;
    }

    /**
     * Update all projectiles
     *
     * @param shockChainState - Optional shock chain state for chain termination cleanup.
     *   When a chain lightning projectile expires (goes inactive), resets the global chain
     *   state to prevent stale data. C code reference: projectiles.c:586-591
     */
    update(
        dt: number,
        shockChainState?: { shockChainProjectileId: number; shockChainLinksLeft: number },
        enemies?: Array<{ x: number; y: number; active: boolean; health: number }>,
    ): void {
        for (const projectile of this.projectiles) {
            if (projectile.isActive()) {
                // Track enemies alive before update to detect AoE kills
                // (rocket explosions and ion fading deal damage inside Projectile.update,
                // which has no quest system access — we must detect and report kills here)
                const hasAoE = enemies && (projectile.isExploding ||
                    (projectile.lifetime < 0.4 && (
                        projectile.projectileType === ProjectileType.ION_RIFLE ||
                        projectile.projectileType === ProjectileType.ION_MINIGUN ||
                        projectile.projectileType === ProjectileType.ION_CANNON
                    )));

                // Snapshot alive enemies that could be killed by AoE
                let aliveBeforeUpdate: boolean[] | null = null;
                if (hasAoE && enemies) {
                    aliveBeforeUpdate = enemies.map(e => e.active && e.health > 0);
                }

                projectile.update(dt, enemies);

                // Report any enemies killed by AoE damage to quest system
                if (aliveBeforeUpdate && enemies) {
                    for (let i = 0; i < enemies.length; i++) {
                        if (aliveBeforeUpdate[i] && enemies[i].health <= 0) {
                            questSystem.reportEnemyKilled();
                        }
                    }
                }

                // C: projectiles.c:586-591 — when an ion chain projectile enters dying/expiry,
                // reset the shock chain state so stale chain data doesn't persist
                if (
                    shockChainState &&
                    !projectile.isActive() &&
                    projectile.isChainLightning &&
                    projectile.chainProjectileId === shockChainState.shockChainProjectileId
                ) {
                    shockChainState.shockChainProjectileId = -1;
                    shockChainState.shockChainLinksLeft = 0;
                }
            }
        }
    }

    /**
     * Render all projectiles
     */
    render(grim: any, spriteRenderer?: any, debugMode: boolean = true): void {
        for (const projectile of this.projectiles) {
            if (projectile.isActive()) {
                projectile.render(grim, spriteRenderer, debugMode);
            }
        }
    }

    /**
     * Get all active projectiles
     */
    getActiveProjectiles(): Projectile[] {
        return this.projectiles.filter((p) => p.isActive());
    }

    /**
     * Clear all projectiles
     */
    clear(): void {
        this.projectiles = [];
    }

    /**
     * Initialize damagePool based on projectile type
     * C code reference: projectile_spawn @ 00420440 (lines 62-91)
     *
     * Gauss=300, Fire=240, Blade=50, Ion Minigun/Rifle=1 (single hit), others=1
     */
    private initDamagePool(projectile: Projectile): void {
        switch (projectile.projectileType) {
            case ProjectileType.GAUSS_GUN:
                projectile.damagePool = 300.0;
                break;
            case ProjectileType.FIRE_BULLETS:
                projectile.damagePool = 240.0;
                break;
            case ProjectileType.BLADE_GUN:
                projectile.damagePool = 50.0;
                break;
            default:
                projectile.damagePool = 1.0;
                break;
        }
    }

    /**
     * Initialize rocket physics properties based on projectile type.
     * C code: rockets are in a separate "secondary projectile" pool with
     * distinct physics (acceleration, homing, speed caps).
     */
    private initRocketProps(projectile: Projectile): void {
        switch (projectile.projectileType) {
            case ProjectileType.ROCKET:
                projectile.isRocket = true;
                projectile.rocketType = 'rocket';
                break;
            case ProjectileType.SEEKER_ROCKET:
                projectile.isRocket = true;
                projectile.rocketType = 'seeker';
                break;
            case ProjectileType.ROCKET_MINIGUN:
                projectile.isRocket = true;
                projectile.rocketType = 'minigun';
                break;
        }
    }

    /**
     * Spawn a child projectile from on-hit effects (Fix #9)
     * Used by Splitter Gun and Plasma Cannon to spawn child projectiles.
     * Looks up weapon data for the correct speed/damage.
     * C code: projectile_spawn(pos, angle, type, owner_id=-100)
     */
    spawnChildProjectile(x: number, y: number, angle: number, type: ProjectileType): Projectile {
        // Find weapon data for this projectile type to get speed/damage
        let speed = 400; // Default fallback
        let damage = 10;
        for (const wid of Object.keys(WEAPON_DATA)) {
            const ws = WEAPON_DATA[Number(wid)];
            if (ws.projectileType === type) {
                speed = ws.projectileSpeed;
                damage = ws.damage;
                break;
            }
        }
        const vx = Math.cos(angle) * speed;
        const vy = Math.sin(angle) * speed;
        const projectile = new Projectile(x, y, vx, vy, damage, 0.4, -1, type);
        this.initDamagePool(projectile);
        // Set damageScale from weapon data
        for (const wid of Object.keys(WEAPON_DATA)) {
            const ws = WEAPON_DATA[Number(wid)];
            if (ws.projectileType === type && ws.damageScale !== undefined) {
                projectile.damageScale = ws.damageScale;
                projectile.originX = x;
                projectile.originY = y;
                break;
            }
        }
        this.projectiles.push(projectile);
        return projectile;
    }
}
