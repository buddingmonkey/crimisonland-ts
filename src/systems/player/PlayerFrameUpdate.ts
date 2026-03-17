import { type Player, type PlayerInput } from '../../entities/Player';
import { type WeaponSystem } from '../combat/WeaponSystem';
import { type PerkSystem, PerkId } from '../PerkSystem';
import { type CameraShake } from '../effects/CameraShake';
import { type ParticleSystem } from '../effects/ParticleSystem';
import { type BloodEffectSystem } from '../effects/BloodEffectSystem';
import { type EffectSystem } from '../effects/EffectSystem';
import { type SoundSystem } from '../../audio';
import { type GameplayCursor } from '../../rendering/GameplayCursor';
import { type TerrainRenderer } from '../../rendering/TerrainRenderer';
import { KeyCode } from '../../engine/KeyCodes';
import type { GrimInterface } from '../../engine/GrimInterface';
import { gameConsole } from '../../console/Console';

export interface PlayerFrameContext {
    player: Player;
    grim: GrimInterface;
    perkSystem: PerkSystem;
    weaponSystem: WeaponSystem;
    cameraShake: CameraShake;
    particleSystem: ParticleSystem;
    effectSystem: EffectSystem;
    bloodEffectSystem: BloodEffectSystem;
    soundSystem: SoundSystem;
    gameplayCursor: GameplayCursor;
    terrainRenderer: TerrainRenderer | null;
    cameraOffsetX: number;
    cameraOffsetY: number;
    suppressFire?: boolean; // Suppress firing until mouse is released after game start
    // Shock chain state — passed through for chain termination cleanup (C: projectiles.c:586-591)
    shockChainState?: { shockChainProjectileId: number; shockChainLinksLeft: number };
    // Enemy array for seeker rocket homing (C: creature_pool accessed globally)
    enemies?: Array<{ x: number; y: number; active: boolean; health: number }>;
}

export interface PlayerFrameResult {
    scaledDt: number;
    input: PlayerInput;
    cameraOffsetX: number;
    cameraOffsetY: number;
    mouseWorldX: number;
    mouseWorldY: number;
}

/**
 * Per-frame player update: gathers input, moves player, fires weapon,
 * updates camera, and ticks per-frame subsystems (particles, blood, sound, cursor).
 * C references: player_update, camera_update, effects_update, audio_update
 */
export function updatePlayerFrame(ctx: PlayerFrameContext, dt: number): PlayerFrameResult {
    const {
        player,
        grim,
        perkSystem,
        weaponSystem,
        cameraShake,
        particleSystem,
        effectSystem,
        bloodEffectSystem,
        soundSystem,
        gameplayCursor,
        terrainRenderer,
    } = ctx;

    // Gather player input
    const input: PlayerInput = {
        moveUp: grim.isKeyDown(KeyCode.W) || grim.isKeyDown(KeyCode.Up),
        moveDown: grim.isKeyDown(KeyCode.S) || grim.isKeyDown(KeyCode.Down),
        moveLeft: grim.isKeyDown(KeyCode.A) || grim.isKeyDown(KeyCode.Left),
        moveRight: grim.isKeyDown(KeyCode.D) || grim.isKeyDown(KeyCode.Right),
        fire: ctx.suppressFire ? false : grim.isMouseButtonDown(0),
    };

    // Calculate time scale (C line 6775-6776, 25927-25930)
    let timeScale = 1.0;
    if (perkSystem.hasPerk(PerkId.REFLEX_BOOSTED)) timeScale = 0.5;
    if (player.reflexBoostTimer > 0) {
        // C gameplay.c lines 322-331: base 0.3, ramp back in final 1s
        let reflexScale = 0.3;
        if (player.reflexBoostTimer < 1.0) {
            reflexScale = (1.0 - player.reflexBoostTimer) * 0.7 + 0.3;
        }
        timeScale = Math.min(timeScale, reflexScale);
    }
    const scaledDt = dt * timeScale;

    // Convert mouse screen coords to world coords (C: camera_offset applied)
    const mouseWorldX = grim.getMouseX() - ctx.cameraOffsetX;
    const mouseWorldY = grim.getMouseY() - ctx.cameraOffsetY;

    // Update player (pass perkSystem for speed bonus, man bomb, etc.)
    player.update(scaledDt, input, mouseWorldX, mouseWorldY, perkSystem);

    // Update reload timer (C: player_update @ 004136b0, line 12505-12564)
    const isMoving = input.moveUp || input.moveDown || input.moveLeft || input.moveRight;
    // Anxious Loader needs mouse-pressed (single press detection) not mouse-down (held),
    // so that the player must actually "mash" the fire button to speed up reload.
    const firePressed = ctx.suppressFire ? false : grim.isMouseButtonPressed(0);
    player.updateReload(scaledDt, firePressed, isMoving, perkSystem);

    // Handle weapon firing
    // C behavior: ALL weapons fire continuously when mouse is held (input_primary_is_down).
    // The weapon's shot_cooldown timer is the only mechanism that controls fire rate.
    // player_fire_weapon() is called every frame; it internally checks shot_cooldown <= 0.
    // There is NO semi-auto concept in the C code.
    const fireHeld = ctx.suppressFire ? false : grim.isMouseButtonDown(0);
    if (fireHeld) {
        weaponSystem.fireWeapon(player, mouseWorldX, mouseWorldY, perkSystem);
    }

    // Camera update (C: camera_update @ 00409500)
    const screenW = grim.getWidth();
    const screenH = grim.getHeight();
    const terrainW = terrainRenderer?.getPlayableWidth() ?? 1024;
    const terrainH = terrainRenderer?.getPlayableHeight() ?? 1024;
    let cameraOffsetX = screenW / 2 - player.x;
    let cameraOffsetY = screenH / 2 - player.y;
    // Add shake offsets BEFORE clamping (C lines 88-89: shake added first, then clamped)
    // This ensures shake near map edges cannot show out-of-bounds terrain.
    const shakeOffset = cameraShake.getOffset();
    cameraOffsetX += shakeOffset.x;
    cameraOffsetY += shakeOffset.y;
    // Clamp to terrain bounds (C lines 90-102)
    if (cameraOffsetX > -1.0) cameraOffsetX = -1.0;
    if (cameraOffsetY > -1.0) cameraOffsetY = -1.0;
    if (cameraOffsetX < screenW - terrainW) cameraOffsetX = screenW - terrainW;
    if (cameraOffsetY < screenH - terrainH) cameraOffsetY = screenH - terrainH;
    // TODO: C code has camera_follow_x/y for survival typing mode (survival.c L422-469)
    // When survival typing mode is implemented, camera should follow found creatures

    // Update projectiles (pass shock chain state for chain termination cleanup)
    weaponSystem.update(scaledDt, ctx.shockChainState, ctx.enemies);
    weaponSystem.updateSpreadRecovery(player, scaledDt, perkSystem);

    // Update camera shake (C lines 6130-6170)
    cameraShake.update(scaledDt);

    // Update particles (C lines 18560-18650)
    particleSystem.update(scaledDt);

    // Update advanced effects (C: effects_update @ 0042e710)
    effectSystem.update(scaledDt);

    // Update blood effects (C: effects_update @ 0042e710)
    bloodEffectSystem.update(scaledDt);
    bloodEffectSystem.bakeToTerrain();

    // Update sound system cooldowns (C: audio_update @ lines 34667-34698)
    soundSystem.update(scaledDt);

    // Update gameplay cursor animation timers
    gameplayCursor.update(dt);

    // Sync reflex boosted timer with sound system
    if (perkSystem.hasPerk(PerkId.REFLEX_BOOSTED)) {
        soundSystem.setReflexBoostedTimer(1.0);
    } else if (player.reflexBoostTimer > 0) {
        soundSystem.setReflexBoostedTimer(player.reflexBoostTimer);
    }

    // Reload / Weapon Swap: R key (C: key_reload, default Mouse3 = 0x102)
    // C behavior: when Alternate Weapon perk is active, reload key swaps weapons
    // instead of reloading (C lines 12890-12897, 13046-13083).
    // Without the perk, R triggers manual reload (C: player_start_reload).
    if (grim.isKeyPressed(KeyCode.R) || grim.isKeyPressed(KeyCode.Tab)) {
        if (perkSystem.hasPerk(PerkId.ALTERNATE_WEAPON)) {
            // Weapon swap (C lines 13046-13083)
            if (player.swapWeapon(perkSystem)) {
                const weaponStats = player.getWeaponStats();
                gameConsole.print(`Swapped to ${weaponStats.name}`);
                // Play reload sound of newly active weapon (C line 13074)
                if (weaponStats.reloadSfxId !== undefined) {
                    soundSystem.playAtPosition(weaponStats.reloadSfxId, player.x, player.y, 800);
                }
            }
        } else if (grim.isKeyPressed(KeyCode.R)) {
            // Manual reload — only on R, not Tab (C lines 12890-12897)
            if (player.reloadTimer === 0) {
                const weaponStats = player.getWeaponStats();
                player.startReload(perkSystem, () => {
                    if (weaponStats.reloadSfxId !== undefined) {
                        soundSystem.playAtPosition(weaponStats.reloadSfxId, player.x, player.y, 800);
                    }
                });
            }
        }
    }

    return { scaledDt, input, cameraOffsetX, cameraOffsetY, mouseWorldX, mouseWorldY };
}
