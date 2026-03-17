/**
 * Player - Player entity class
 *
 * Represents the player character with movement, rotation, health, and weapon state.
 * Based on player_state_t from crimsonland.exe_decompiled.c
 */

import type { GrimInterface } from '../engine/GrimInterface';
import { getWeaponStats, type WeaponStats } from '../data/WeaponData';
import type { PerkSystem } from '../systems/PerkSystem';
import { PerkId } from '../systems/PerkSystem';

import { calculateRegenRate } from '../systems/player/PlayerModifier';
import type { SoundSystem } from '../audio/SoundSystem';
import { SoundId } from '../audio/SoundId';
import type { BloodEffectSystem } from '../systems/effects/BloodEffectSystem';
import { updatePlayerTimers } from './PlayerTimers';
import {
    updateReload as _updateReload,
    switchWeapon as _switchWeapon,
    swapWeapon as _swapWeapon,
    canFire as _canFire,
    startCooldown as _startCooldown,
    startManualReload as _startManualReload,
    type PlayerWeaponContext,
} from './PlayerWeapon';
import { renderPlayer as _renderPlayer, type PlayerRenderContext } from './PlayerRenderer';

/**
 * Player entity
 */
export class Player {
    // Position
    public x: number = 400;
    public y: number = 300;

    // Rotation (radians, 0 = right, increases counter-clockwise)
    public angle: number = 0;
    public aimAngle: number = 0;

    // Health
    public health: number = 100;
    public maxHealth: number = 100;
    public shieldTimer: number = 0; // Invulnerability frames (C line 21117)

    // Movement
    public moveSpeed: number = 0;
    public maxMoveSpeed: number = 2.0;
    public moveAcceleration: number = 5.0;
    public moveDeceleration: number = 15.0;
    public dx: number = 0;
    public dy: number = 0;

    // Aim properties (C lines 11800-11804)
    public aimHeading: number = 0; // Aim direction
    public aimX: number = 0; // Aim target X
    public aimY: number = 0; // Aim target Y

    // Weapon state (C player_reset_all: weapon_id = 1 = C Pistol → TS 0)
    public weaponId: number = 0; // 0 = Pistol (C weapon_id 1, line 2035)
    public clipSize: number = 12; // Magazine capacity (from weapon table)
    public ammo: number = 12; // Current ammo
    public shotCooldown: number = 0.8; // C line 2034
    public reloadTimer: number = 0;
    public reloadTimerMax: number = 0; // For UI progress bar
    public reloadActive: boolean = false;

    // Visual effects
    public muzzleFlashAlpha: number = 0;
    public spreadHeat: number = 0.01; // Weapon accuracy (C line 18376)

    // Spread constants (C code @ lines 13434-13435)
    public readonly MAX_SPREAD_HEAT = 0.48; // Maximum spread heat cap
    public readonly SPREAD_RECOVERY_RATE = 0.5; // Spread recovery per second

    // Speed bonus
    public speedBonusTimer: number = 0; // Speed bonus duration (C line 18341)
    public speedMultiplier: number = 2.0; // Movement speed multiplier (C line 2009: default 2.0)
    private speedBonusBoosted: boolean = false; // Track if +1.0 has been applied this frame

    // Low health effects
    public lowHealthTimer: number = 100.0; // 100.0 = disabled (C line 11703)

    // Weapon power-up
    public weaponPowerUpTimer: number = 0; // Weapon power-up duration (C line 6873)
    public energizerTimer: number = 0; // Energizer bonus duration (C line 6876)
    public reflexBoostTimer: number = 0; // Reflex boost duration (C line 6879)
    public freezeTimer: number = 0; // Freeze bonus duration (C line 6577)

    // Perk timers (C lines 11772-11884)
    public livingFortressTimer: number = 0.0; // Living Fortress defense timer (C line 11772)
    public _hasMoved: boolean = false; // Set in update(), used by updateTimers()
    public fireCoughTimer: number = 0.0; // Fire Cough spawn timer (C line 11783)
    public fireCoughInterval: number = 0.0; // Fire Cough spawn interval — C BSS global starts at 0 (fires immediately), then randomized 2-5s
    public pendingFireCoughSpawn: { x: number; y: number; angle: number; damage: number; speed: number } | null = null;
    public hotTemperedTimer: number = 0.0; // Hot Tempered spawn timer (C line 11850)
    public hotTemperedInterval: number = 2.0; // Hot Tempered spawn interval (2-9s)
    public pendingHotTemperedBurst: boolean = false;

    // Angry Reloader perk flag (C lines 12529-12538)
    public angryReloaderTriggered: boolean = false; // Track if projectiles spawned this reload
    public pendingAngryReloaderBurst: boolean = false; // Pending projectile spawn

    // Damage system properties (C lines 21100-21200)
    // Note: shieldTimer already defined at line 27
    // Note: reloadActive already exists as part of reload system
    public deathTimer: number = 16.0; // Death animation timer (C line 2041: init 16.0)
    public deathFirstFrame: boolean = false; // First death frame uses faster timer rate (C line 2169-2170)
    public pendingFinalRevenge: boolean = false; // Final Revenge explosion pending
    public damageTaken: number = 0; // Cumulative damage taken during quest (C: damage_total)

    // Bonus timers (C lines 6364-6483)
    public fireBulletsTimer: number = 0.0; // Fire bullets rapid fire mode (C lines 6409-6419)

    // Experience/Progression (C: player_state_table.experience, player_state_table.level)
    public experience: number = 0; // Player XP (C line 5773)
    public level: number = 1; // Current level (C: player_state_table.level, starts at 1)
    public doubleXPTimer: number = 0; // 2x XP bonus timer (moved from Game.ts, C: bonus_double_xp_timer)
    public leanMeanExpTimer: number = 0.25; // Lean Mean Exp Machine timer (C line 4718-4726)
    public jinxedCooldown: number = 0.0; // Jinxed effect cooldown (C: jinxed_effect_cooldown)
    public pendingJinxedKill: boolean = false; // Flag: kill random enemy this frame (Jinxed)
    public plaguebearerActive: boolean = false; // Plaguebearer perk active (C: player_plaguebearer_active)

    // Enemy Targeting (C lines 4765-4860)
    // Note: aimX and aimY already defined at lines 42-43
    public evilEyesTarget: any = null; // Evil Eyes target enemy
    public doctorTarget: any = null; // Doctor target enemy

    // Movement heading (separate from aim angle) — C player_reset_all line 2011
    public heading: number = 0; // Body direction (for movement/rendering)
    public movementDecayRate: number = 1.0; // C lines 293-304: ramps toward 1.0 or 0.3
    public size: number = 48.0; // Player size (C line 2008)

    // Man Bomb perk (C lines 144-178)
    public manBombTimer: number = 0.0;
    public manBombCooldownThreshold: number = 4.0;
    public pendingManBombBurst: boolean = false;

    // Alternate Weapon system (C lines 1129-1167)
    public altWeaponId: number = 0; // C line 2024 (C weapon_id 1 = Pistol → TS 0)
    public altAmmo: number = 12;
    public altClipSize: number = 12; // C line 2025
    public altReloadTimer: number = 0.0; // C line 2030
    public altShotCooldown: number = 0.0; // C line 2031
    public altReloadActive: boolean = false; // C line 2026
    public altReloadTimerMax: number = 1.0; // C line 2032
    public weaponSwapCooldown: number = 0; // 200ms cooldown (C: weapon_swap_cooldown_ms)

    // Terrain dimensions for boundary clamping (C: terrain_texture_width/height)
    private terrainWidth: number = 1024;
    private terrainHeight: number = 1024;

    // Sprite rendering
    private readonly radius: number = 16; // Player collision/render radius (used via PlayerRenderContext cast)
    public animTimer: number = 0; // Animation timer for sprite sheet cycling

    // Sound system (for pain sounds)
    private soundSystem: SoundSystem | null = null;

    // Blood effect system (for low-health bleed, set via setBloodEffectSystem)
    private bloodEffectSystem: BloodEffectSystem | null = null;

    constructor(x: number = 400, y: number = 300) {
        this.x = x;
        this.y = y;
        void this.radius; // satisfy noUnusedLocals — read via PlayerRenderContext cast
        void this.bloodEffectSystem; // satisfy noUnusedLocals — read via PlayerTimerContext cast

        // Initialize weapon stats from default weaponId (0 = Pistol, C weapon_id 1)
        const weaponStats = getWeaponStats(this.weaponId);
        this.clipSize = weaponStats.clipSize;
        this.ammo = this.clipSize;
    }

    /**
     * Set sound system reference
     * C code reference: player_take_damage @ line 21156
     */
    setSoundSystem(soundSystem: SoundSystem): void {
        this.soundSystem = soundSystem;
    }

    /**
     * Set blood effect system reference
     * Needed for low-health bleed effect in PlayerTimers
     */
    setBloodEffectSystem(bloodEffectSystem: BloodEffectSystem): void {
        this.bloodEffectSystem = bloodEffectSystem;
    }

    /**
     * Set terrain dimensions for boundary clamping
     * Called from Game.ts when terrain is generated
     */
    setTerrainDimensions(width: number, height: number): void {
        this.terrainWidth = width;
        this.terrainHeight = height;
    }

    /**
     * Update player state
     */
    update(dt: number, input: PlayerInput, mouseWorldX: number, mouseWorldY: number, perkSystem?: PerkSystem): void {
        // Death handling: decrement death_timer, skip all other logic (C lines 101-104)
        if (this.health <= 0) {
            // C: first death frame uses 28.0 rate (in player_take_damage), subsequent use 20.0
            if (this.deathFirstFrame) {
                this.deathTimer -= dt * 28.0;
                this.deathFirstFrame = false;
            } else {
                this.deathTimer -= dt * 20.0;
            }
            return;
        }

        // Speed bonus: add 1.0 on entry (C lines 106-109)
        // Base speed_multiplier is 2.0. With speed bonus active it becomes 3.0.
        if (this.speedBonusTimer > 0) {
            this.speedMultiplier += 1.0;
            this.speedBonusBoosted = true;
        }

        // Update aim angle toward mouse
        this.aimAt(mouseWorldX, mouseWorldY);

        // Store previous position for timer reset checks (C lines 926, 932-934)
        const prevX = this.x;
        const prevY = this.y;

        // Handle movement input
        this.updateMovement(dt, input, perkSystem);

        // Reset Man Bomb timer and Living Fortress when player moves (C lines 932-934)
        const hasMoved = this.x !== prevX || this.y !== prevY;
        this._hasMoved = hasMoved;
        if (hasMoved) {
            this.manBombTimer = 0.0;
            this.livingFortressTimer = 0.0;
        }

        // Movement decay rate (C lines 293-304)
        // Ramps toward 1.0 at 0.8*dt when no boost, decays toward 0.3 at -dt when boost active
        if (this.speedBonusTimer <= 0) {
            this.movementDecayRate += dt * 0.8;
            if (this.movementDecayRate > 1.0) this.movementDecayRate = 1.0;
        } else {
            this.movementDecayRate -= dt;
            if (this.movementDecayRate < 0.3) this.movementDecayRate = 0.3;
        }

        // Update timers
        this.updateTimers(dt, perkSystem);

        // Decrement weapon swap cooldown (C: weapon_swap_cooldown_ms)
        if (this.weaponSwapCooldown > 0) {
            this.weaponSwapCooldown -= dt;
            if (this.weaponSwapCooldown < 0) this.weaponSwapCooldown = 0;
        }

        // Health regeneration with perks (C lines 4706-4716)
        if (this.health > 0 && this.health < 100 && perkSystem) {
            const regenRate = calculateRegenRate(dt, perkSystem);
            if (regenRate > 0) {
                this.health += regenRate;
                if (this.health > 100) {
                    this.health = 100;
                }
            }
        }

        // Update animation timer when moving (C lines 12520-12522, 12638-12639)
        // Formula: move_phase += frame_dt * move_speed * 19.0
        const isMoving = Math.abs(this.dx) > 0.1 || Math.abs(this.dy) > 0.1;
        if (isMoving) {
            this.animTimer += dt * this.moveSpeed * 19.0;

            // Compute heading from movement direction
            this.heading = Math.atan2(this.dy, this.dx);
        }

        // Wrap animTimer to [0, 14) range (C lines 1854-1863)
        while (this.animTimer >= 14.0) this.animTimer -= 14.0;
        while (this.animTimer < 0.0) this.animTimer += 14.0;

        // Speed bonus: subtract 1.0 on exit (C lines 1864-1867)
        if (this.speedBonusBoosted) {
            this.speedMultiplier -= 1.0;
            this.speedBonusBoosted = false;
        }
    }

    /**
     * Aim toward world position
     */
    private aimAt(worldX: number, worldY: number): void {
        const dx = worldX - this.x;
        const dy = worldY - this.y;
        this.aimAngle = Math.atan2(dy, dx);

        // Set aim position for crosshair-based perks (EVIL_EYES, PYROKINETIC, DOCTOR)
        this.aimX = worldX;
        this.aimY = worldY;

        // Smoothly rotate heading toward aim angle
        // For now, snap directly (we can add smooth rotation later)
        this.angle = this.aimAngle;
    }

    /**
     * Update movement based on input
     */
    private updateMovement(dt: number, input: PlayerInput, perkSystem?: PerkSystem): void {
        // Calculate desired movement direction
        let moveX = 0;
        let moveY = 0;

        if (input.moveUp) moveY -= 1;
        if (input.moveDown) moveY += 1;
        if (input.moveLeft) moveX -= 1;
        if (input.moveRight) moveX += 1;

        // Normalize diagonal movement
        const inputMagnitude = Math.sqrt(moveX * moveX + moveY * moveY);
        if (inputMagnitude > 0) {
            moveX /= inputMagnitude;
            moveY /= inputMagnitude;

            // Long Distance Runner perk modifies acceleration (C lines 11958-11975)
            if (perkSystem?.hasPerk(PerkId.LONG_DISTANCE_RUNNER)) {
                // Two-stage acceleration: 4.0/s to 2.0, then +1.0/s to 2.8
                if (this.moveSpeed < 2.0) {
                    this.moveSpeed += dt * 4.0;
                }
                this.moveSpeed += dt;
                if (this.moveSpeed > 2.8) {
                    this.moveSpeed = 2.8; // Higher max speed
                }
            } else {
                // Standard: 5.0/s acceleration, 2.0 max (C lines 11959-11963)
                this.moveSpeed += dt * 5.0;
                if (this.moveSpeed > 2.0) {
                    this.moveSpeed = 2.0;
                }
            }
        } else {
            // Decelerate
            this.moveSpeed -= this.moveDeceleration * dt;
            if (this.moveSpeed < 0) {
                this.moveSpeed = 0;
            }
        }

        // Minigun speed penalty (C lines 12055-12058)
        // C weapon_id 7 = Mean Minigun → TS weapon ID 13 — caps speed at 0.8 (60% penalty)
        if (this.weaponId === 13 && this.moveSpeed > 0.8) {
            this.moveSpeed = 0.8;
        }

        // Apply movement (with speed multiplier from C line 13457-13467)
        this.dx = moveX * this.moveSpeed * 25.0 * this.speedMultiplier;
        this.dy = moveY * this.moveSpeed * 25.0 * this.speedMultiplier;

        // Alternate weapon perk: 0.8x movement penalty (C line 1908-1909)
        if (perkSystem?.hasPerk(PerkId.ALTERNATE_WEAPON)) {
            this.dx *= 0.8;
            this.dy *= 0.8;
        }

        this.x += this.dx * dt;
        this.y += this.dy * dt;

        // World boundary clamping (C lines 1868-1881)
        // C: uses player.size * 0.5 and terrain_texture_width/height
        const halfSize = this.size * 0.5; // 48.0 * 0.5 = 24.0
        const terrainWidth = this.terrainWidth;
        const terrainHeight = this.terrainHeight;

        // Clamp X position (C lines 1869-1874)
        if (this.x < halfSize) {
            this.x = halfSize;
        }
        if (terrainWidth - halfSize < this.x) {
            this.x = terrainWidth - halfSize;
        }

        // Clamp Y position (C lines 1876-1881)
        if (this.y < halfSize) {
            this.y = halfSize;
        }
        if (terrainHeight - halfSize < this.y) {
            this.y = terrainHeight - halfSize;
        }
    }

    /**
     * Update reload timer.
     * Logic extracted to PlayerWeapon.ts.
     */
    updateReload(dt: number, fireKeyPressed: boolean, isMoving: boolean, perkSystem?: any): void {
        _updateReload(this as unknown as PlayerWeaponContext, dt, fireKeyPressed, isMoving, perkSystem);
    }

    /**
     * Update timers (C: player_update @ 004136b0, line 11721-11736)
     * Timer update logic is in PlayerTimers.ts.
     */
    updateTimers(dt: number, perkSystem?: any): void {
        updatePlayerTimers(this as unknown as import('./PlayerTimers').PlayerTimerContext, dt, perkSystem);
    }

    /**
     * Check if weapon can fire.
     * Logic extracted to PlayerWeapon.ts.
     */
    canFire(perkSystem?: PerkSystem): boolean {
        return _canFire(this as unknown as PlayerWeaponContext, perkSystem);
    }

    /**
     * Start weapon cooldown after firing.
     * Logic extracted to PlayerWeapon.ts.
     */
    startCooldown(duration: number, perkSystem?: any): void {
        _startCooldown(this as unknown as PlayerWeaponContext, duration, perkSystem);
    }

    /**
     * Apply damage to player with perk modifiers (C lines 21100-21200)
     */
    takeDamage(amount: number, perkSystem?: PerkSystem): void {
        // Death Clock - complete invulnerability (C lines 21107-21110)
        if (perkSystem?.hasPerk(PerkId.DEATH_CLOCK)) {
            return;
        }

        let damage = amount;

        // Tough Reloader - 50% damage reduction while reloading (C lines 21111-21114)
        if (perkSystem?.hasPerk(PerkId.TOUGH_RELOADER) && this.reloadActive) {
            damage *= 0.5;
        }

        // Shield timer check (C lines 21117-21120)
        if (this.shieldTimer > 0.0) {
            return; // No damage taken
        }

        // Thick Skinned - 33% damage reduction (C lines 21122-21125)
        let damageMultiplier = 1.0;
        if (perkSystem?.hasPerk(PerkId.THICK_SKINNED)) {
            // THICK_SKINNED
            damageMultiplier = 0.666;
        }

        // Dodge perks (C lines 21127-21141)
        let dodged = false;
        if (perkSystem?.hasPerk(PerkId.NINJA)) {
            // NINJA
            // 33% dodge chance (C lines 21136-21139)
            if (Math.floor(Math.random() * 3) === 0) {
                dodged = true;
            }
        } else if (perkSystem?.hasPerk(PerkId.DODGER)) {
            // DODGER
            // 20% dodge chance (C lines 21130-21132)
            if (Math.floor(Math.random() * 5) === 0) {
                dodged = true;
            }
        }

        if (dodged) {
            return; // Dodged the attack
        }

        // Apply damage (C lines 21142-21152)
        if (!perkSystem?.hasPerk(PerkId.HIGHLANDER)) {
            // Normal damage application
            const actualDamage = damageMultiplier * damage;
            this.health -= actualDamage;
            this.damageTaken += actualDamage;
        } else {
            // Highlander: 10% chance of instant death (C lines 21148-21151)
            if (Math.floor(Math.random() * 10) === 0) {
                this.health = 0.0;
            }
        }

        if (this.health < 0) {
            this.health = 0;
        }

        // Death handling (C lines 2161-2205)
        if (this.health <= 0.0) {
            // Flag first death frame for faster timer rate in update() (C lines 2169-2170)
            this.deathFirstFrame = true;

            // Final Revenge perk - explosion on death (C lines 2174-2205)
            // C: if/else — die sound only plays when NO Final Revenge
            if (perkSystem?.hasPerk(PerkId.FINAL_REVENGE)) {
                this.pendingFinalRevenge = true;
                if (this.soundSystem) {
                    this.soundSystem.playAtPosition(SoundId.EXPLOSION_LARGE, this.x, this.y, 800);
                    this.soundSystem.playAtPosition(SoundId.SHOCKWAVE, this.x, this.y, 800);
                }
            } else {
                // C player.c:2181 — sfx_play_panned((rand()&1) + sfx_trooper_die_01)
                if (this.soundSystem) {
                    const dieSound = Math.random() < 0.5 ? SoundId.TROOPER_DIE_01 : SoundId.TROOPER_DIE_02;
                    this.soundSystem.playAtPosition(dieSound, this.x, this.y, 800);
                }
            }

            return; // C: bVar7 check — skip further processing on death
        }

        // Pain sound when surviving (C lines 2161-2163)
        if (this.soundSystem) {
            const painSounds = [SoundId.TROOPER_INPAIN_01, SoundId.TROOPER_INPAIN_02, SoundId.TROOPER_INPAIN_03];
            const soundId = painSounds[Math.floor(Math.random() * 3)];
            this.soundSystem.playAtPosition(soundId, this.x, this.y, 800);
        }

        // Heading scatter and spread heat on damage (C lines 2207-2217)
        // Only when NOT dodged and NOT Unstoppable
        if (!perkSystem?.hasPerk(PerkId.UNSTOPPABLE)) {
            this.heading += (Math.floor(Math.random() * 100) - 50) * 0.04;
            this.spreadHeat += damage * 0.01;
            if (this.spreadHeat > 0.48) this.spreadHeat = 0.48;
        }

        // Low health timer trigger (C lines 2219-2222)
        // Only when health <= 20 AND 12.5% random chance
        if (this.health <= 20.0 && Math.floor(Math.random() * 8) === 3) {
            this.lowHealthTimer = 0.0;
        }
    }

    /**
     * Heal
     */
    heal(amount: number): void {
        this.health += amount;
        if (this.health > this.maxHealth) {
            this.health = this.maxHealth;
        }
    }

    /**
     * Get current weapon stats
     */
    getWeaponStats(): WeaponStats {
        return getWeaponStats(this.weaponId);
    }

    /**
     * Switch to a different weapon.
     * Logic extracted to PlayerWeapon.ts.
     */
    switchWeapon(weaponId: number, perkSystem?: any): void {
        _switchWeapon(this as unknown as PlayerWeaponContext, weaponId, perkSystem);
    }

    /**
     * Start a manual reload.
     * Logic extracted to PlayerWeapon.ts (C: player_start_reload @ 00413430).
     */
    startReload(perkSystem?: any, playSoundCb?: () => void): boolean {
        return _startManualReload(this as unknown as PlayerWeaponContext, perkSystem, playSoundCb);
    }

    /**
     * Swap to alternate weapon.
     * Logic extracted to PlayerWeapon.ts.
     */
    swapWeapon(perkSystem?: any): boolean {
        return _swapWeapon(this as unknown as PlayerWeaponContext, perkSystem);
    }

    /**
     * Check if player is alive
     */
    isAlive(): boolean {
        return this.health > 0;
    }

    /**
     * Render player.
     * Logic extracted to PlayerRenderer.ts.
     */
    render(grim: GrimInterface, spriteRenderer?: any, debugMode: boolean = true, perkSystem?: PerkSystem): void {
        _renderPlayer(this as unknown as PlayerRenderContext, grim, spriteRenderer, debugMode, perkSystem);
    }
}

/**
 * Player input state
 */
export interface PlayerInput {
    moveUp: boolean;
    moveDown: boolean;
    moveLeft: boolean;
    moveRight: boolean;
    fire: boolean;
}
