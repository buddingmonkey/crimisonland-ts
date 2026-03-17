import { Assets, type Texture as PIXITexture } from 'pixi.js';
import bulletTrailGradientUrl from '../assets/bullet-trail-gradient.png';
import { GrimInterface, TextureHandle } from '../engine/GrimInterface';
import { AssetManager } from '../data/AssetManager';
import { BonusType } from '../entities/Bonus';
import { ProjectileType } from '../data/WeaponData';
import { CREATURE_TYPE_TABLE } from './SpriteSheetConfig';
import { EnemyType } from '../entities/Enemy';
import { drawProjectile as _drawProjectile, type ProjectileTextureContext } from './ProjectileRenderer';
import { drawBonus as _drawBonus, type BonusTextureContext } from './BonusRenderer';
import {
    drawPlayer as _drawPlayer,
    drawPlayerTwoLayer as _drawPlayerTwoLayer,
    drawEnemy as _drawEnemy,
    drawCorpse as _drawCorpse,
    type EntityTextureContext,
} from './EntityRenderer';

/**
 * Player rendering options
 */
export interface PlayerRenderOptions {
    /** Current invulnerability/shield timer for flash effect */
    shieldTimer?: number;
    /** Muzzle flash alpha (0-1) */
    muzzleFlashAlpha?: number;
    /** Is the player currently moving? */
    isMoving?: boolean;
    /** Animation timer (increments while moving) */
    animTimer?: number;
    /** Body heading (separate from aim angle for two-layer rendering) */
    heading?: number;
    /** Aim angle (weapon direction, separate from body heading) */
    aimAngle?: number;
    /** Is the player dead? (for death animation rendering) */
    isDead?: boolean;
    /** Death animation timer (counts down from 16.0) */
    deathTimer?: number;
    /** Player size for rendering (C: player.size = 48.0) */
    playerSize?: number;
    /** Weapon flags bitmask (C: weapon_table[id].flags) for muzzle flash size */
    weaponFlags?: number;
    /** Whether the Radioactive perk is active (for green glow aura) */
    hasRadioactivePerk?: boolean;
}

/**
 * Color tint for enemy rendering
 */
export interface ColorTint {
    r: number; // 0-1
    g: number; // 0-1
    b: number; // 0-1
}

/**
 * SpriteRenderer - Centralized entity sprite rendering
 *
 * Loads entity sprites from PAQ archives and provides methods
 * to draw player, enemies, and projectiles with proper rotation and effects.
 */
export class SpriteRenderer {
    // Texture handles
    private playerHandle: TextureHandle = -1;
    // Per-type enemy texture handles (keyed by texture asset path)
    private enemyTextureHandles: Map<string, TextureHandle> = new Map();
    private bodysetHandle: TextureHandle = -1; // bodyset.jaz - corpse sprites
    private projectileHandle: TextureHandle = -1; // projs.jaz - plasma, ion, pulse, splitter, blade renders
    private particlesHandle: TextureHandle = -1; // particles.jaz - muzzle flash, plasma glow
    private particlesPixiTexture: PIXITexture | null = null; // Raw PIXI texture for terrain baking
    private bodysetPixiTexture: PIXITexture | null = null; // Raw PIXI bodyset for corpse baking
    private muzzleFlashHandle: TextureHandle = -1; // muzzleFlash.jaz - muzzle flash glow
    private bulletTrailHandle: TextureHandle = -1; // bulletTrail.tga - bullet motion trail
    private bulletHeadHandle: TextureHandle = -1; // bullet16.tga - bullet head dot
    private bonusHandle: TextureHandle = -1; // bonuses.jaz - bonus/pickup sprites
    private weaponIconHandle: TextureHandle = -1; // C: ui_weapon_icons_texture (ui.jaz)

    // Track which sprites are available
    private hasPlayerSprite = false;
    private hasEnemySprite = false;
    private hasBodysetSprite = false;
    private hasProjectileSprite = false;
    private hasParticlesSprite = false;
    private hasMuzzleFlashSprite = false;
    private hasBulletTrailSprite = false;
    private hasBulletHeadSprite = false;
    private hasBonusSprite = false;
    private hasWeaponIconSprite = false; // Fix 10: weapon icon overlay

    // Loaded state
    private loaded = false;

    /**
     * Ensures all texture handles and flags are considered 'read' by TypeScript.
     * These fields are read through EntityTextureContext / ProjectileTextureContext /
     * BonusTextureContext via `this as unknown as XContext` casts in the public draw*
     * methods, but TypeScript's noUnusedLocals cannot trace through the cast.
     * This method is never called at runtime; it exists solely to satisfy the compiler.
     */
    private _ensureContextFields(): void {
        void this.playerHandle;
        void this.bodysetHandle;
        void this.projectileHandle;
        void this.muzzleFlashHandle;
        void this.bulletTrailHandle;
        void this.bulletHeadHandle;
        void this.bonusHandle;
        void this.weaponIconHandle;
        void this.hasBodysetSprite;
        void this.hasProjectileSprite;
        void this.hasParticlesSprite;
        void this.hasMuzzleFlashSprite;
        void this.hasBulletTrailSprite;
        void this.hasBulletHeadSprite;
        void this.hasWeaponIconSprite;
    }

    /**
     * Load all entity sprites from AssetManager
     */
    async loadAssets(assetManager: AssetManager, grim: GrimInterface): Promise<void> {
        // Try to load player sprite (trooper.jaz)
        const playerTexture = await assetManager.getTexture('game/trooper.jaz');
        if (playerTexture) {
            this.playerHandle = grim.registerTexture('entity_player', playerTexture);
            this.hasPlayerSprite = true;
        } else {
            console.warn('[SpriteRenderer] No player sprite found (trooper.jaz), using debug rendering');
        }

        // Load per-type enemy textures from creature_type_table
        // C code loads: zombie.jaz, lizard.jaz, spider_sp1.jaz, spider_sp2.jaz, alien.jaz
        const uniqueTextures = new Set<string>();
        for (const typeConfig of CREATURE_TYPE_TABLE) {
            uniqueTextures.add(typeConfig.textureKey);
        }

        let loadedCount = 0;
        for (const textureKey of uniqueTextures) {
            const texture = await assetManager.getTexture(textureKey);
            if (texture) {
                const name = textureKey.replace('game/', '').replace('.jaz', '');
                const handle = grim.registerTexture(`entity_${name}`, texture);
                this.enemyTextureHandles.set(textureKey, handle);
                loadedCount++;
            } else {
                console.warn(`[SpriteRenderer] Missing enemy texture: ${textureKey}`);
            }
        }
        this.hasEnemySprite = loadedCount > 0;

        // Load bodyset.jaz for corpse sprites
        // C code: bodyset_texture = grim_get_texture_handle("bodyset")
        const bodysetTexture = await assetManager.getTexture('game/bodyset.jaz');
        if (bodysetTexture) {
            this.bodysetHandle = grim.registerTexture('entity_bodyset', bodysetTexture);
            this.bodysetPixiTexture = bodysetTexture as PIXITexture;
            this.hasBodysetSprite = true;
        } else {
            console.warn('[SpriteRenderer] No bodyset sprite found (bodyset.jaz)');
        }

        // Try to load projectile sprite (projs.jaz contains projectile sprites)
        // C code: projectile_texture = texture_get_or_load("projs", "game/projs.jaz")
        const projectileTexture = await assetManager.getTexture('game/projs.jaz');
        if (projectileTexture) {
            this.projectileHandle = grim.registerTexture('entity_projectile', projectileTexture);
            this.hasProjectileSprite = true;
        } else {
            console.warn('[SpriteRenderer] No projectile sprite found (projs.jaz), using debug rendering');
        }

        // Try to load particles sprite (particles.jaz - muzzle flash glow, plasma glow)
        // C code: particles_texture = texture_get_or_load_alt("game/particles.jaz")
        const particlesTexture = await assetManager.getTexture('game/particles.jaz');
        if (particlesTexture) {
            this.particlesHandle = grim.registerTexture('entity_particles', particlesTexture);
            this.particlesPixiTexture = particlesTexture as PIXITexture;
            this.hasParticlesSprite = true;
        } else {
            console.warn('[SpriteRenderer] No particles sprite found (particles.jaz)');
        }

        // Load muzzle flash texture (muzzleFlash.jaz)
        // C code: DAT_0048f7e0 = texture_get_or_load_alt("game/muzzleFlash.jaz")
        const muzzleFlashTexture = await assetManager.getTexture('game/muzzleFlash.jaz');
        if (muzzleFlashTexture) {
            this.muzzleFlashHandle = grim.registerTexture('entity_muzzleflash', muzzleFlashTexture);
            this.hasMuzzleFlashSprite = true;
        } else {
            console.warn('[SpriteRenderer] No muzzle flash sprite found (muzzleFlash.jaz)');
        }

        // Load bullet trail gradient texture (4×256 opaque→transparent PNG).
        // The C code uses per-vertex color slots (grim_set_color_slot) for the
        // head→tail alpha fade, but PIXI v8 Mesh doesn't support per-vertex alpha.
        // Instead we bake the fade into a gradient texture and map it via UVs.
        // The PAQ's bulletTrail.tga is a solid/opaque strip (C relied on vertex
        // colors for fade), so we always use our gradient PNG.
        try {
            const gradientTexture = await Assets.load(bulletTrailGradientUrl);
            this.bulletTrailHandle = grim.registerTexture('bullet_trail_gradient', gradientTexture);
            this.hasBulletTrailSprite = true;
        } catch {
            console.warn('[SpriteRenderer] Failed to load bullet trail gradient PNG');
        }

        // Try to load bullet head texture (bullet16.tga / bullet_i)
        // C code: projectile_bullet_texture = grim_get_texture_handle("bullet_i")
        const bulletHeadTexture = await assetManager.getTexture('load/bullet16.tga');
        if (bulletHeadTexture) {
            this.bulletHeadHandle = grim.registerTexture('bullet_head', bulletHeadTexture);
            this.hasBulletHeadSprite = true;
        } else {
            console.warn('[SpriteRenderer] No bullet head texture found (load/bullet16.tga)');
        }

        // Try to load bonus sprites (bonuses.jaz)
        // C code: texture_get_or_load("bonuses", "game/bonuses.jaz")
        // bonus_texture = grim_get_texture_handle("bonuses")
        const bonusTexture = await assetManager.getTexture('game/bonuses.jaz');
        if (bonusTexture) {
            this.bonusHandle = grim.registerTexture('entity_bonuses', bonusTexture);
            this.hasBonusSprite = true;
        } else {
            console.warn('[SpriteRenderer] No bonus sprite found (bonuses.jaz), using debug rendering');
        }

        // Fix 10: Try to load weapon HUD icons texture (C: ui_weapon_icons_texture)
        // Located at game/ui/ui_wicons.jaz — 8-column atlas of weapon HUD icons
        const weaponIconsTexture = await assetManager.getTexture('ui/ui_wicons.jaz');
        if (weaponIconsTexture) {
            this.weaponIconHandle = grim.registerTexture('weapon_icons', weaponIconsTexture);
            this.hasWeaponIconSprite = true;
        } else {
            // Fallback: use bonuses.jaz frame 1 (already handled in drawBonus)
        }

        this.loaded = true;
        this._ensureContextFields(); // satisfy noUnusedLocals — fields are read via context casts
    }

    /**
     * Check if sprites are loaded
     */
    isLoaded(): boolean {
        return this.loaded;
    }

    /**
     * Check if player sprite is available
     */
    canDrawPlayer(): boolean {
        return this.hasPlayerSprite;
    }

    /**
     * Check if enemy sprite is available
     */
    canDrawEnemy(): boolean {
        return this.hasEnemySprite;
    }

    /**
     * Check if projectile rendering is available
     * Always true - drawProjectile has built-in fallbacks for missing textures
     */
    canDrawProjectile(): boolean {
        return this.loaded;
    }

    /**
     * Get particles texture handle (for BloodEffectSystem flying particles)
     */
    getParticlesHandle(): TextureHandle {
        return this.particlesHandle;
    }

    /**
     * Get muzzle flash texture handle
     */
    getMuzzleFlashHandle(): TextureHandle {
        return this.muzzleFlashHandle;
    }

    /**
     * Get raw PIXI particles texture (for BloodEffectSystem terrain baking)
     */
    getParticlesPixiTexture(): PIXITexture | null {
        return this.particlesPixiTexture;
    }

    /**
     * Get raw PIXI bodyset texture (for BloodEffectSystem corpse baking)
     */
    getBodysetPixiTexture(): PIXITexture | null {
        return this.bodysetPixiTexture;
    }

    /**
     * Check if bonus sprite is available
     */
    canDrawBonus(): boolean {
        return this.hasBonusSprite;
    }

    /**
     * Draw player sprite.
     * Rendering logic extracted to EntityRenderer.ts.
     */
    drawPlayer(
        grim: GrimInterface,
        x: number,
        y: number,
        angle: number,
        radius: number,
        options: PlayerRenderOptions = {},
    ): void {
        _drawPlayer(this as unknown as EntityTextureContext, grim, x, y, angle, radius, options);
    }

    /**
     * Draw player with two-layer rendering.
     * Rendering logic extracted to EntityRenderer.ts.
     */
    drawPlayerTwoLayer(grim: GrimInterface, x: number, y: number, options: PlayerRenderOptions = {}): void {
        _drawPlayerTwoLayer(this as unknown as EntityTextureContext, grim, x, y, options);
    }

    /**
     * Draw enemy sprite.
     * Rendering logic extracted to EntityRenderer.ts.
     */
    drawEnemy(
        grim: GrimInterface,
        x: number,
        y: number,
        angle: number,
        size: number,
        tint: ColorTint = { r: 1, g: 1, b: 1 },
        hitFlash: number = 0,
        animPhase: number = 0,
        isDying: boolean = false,
        hitboxSize: number = 16.0,
        enemyType: EnemyType = EnemyType.Spider,
        creatureFlags: number = 0,
        energizerTimer: number = 0,
        maxHealth: number = 100,
        radioactiveFlash: number = 0,
    ): void {
        _drawEnemy(
            this as unknown as EntityTextureContext,
            grim,
            x,
            y,
            angle,
            size,
            tint,
            hitFlash,
            animPhase,
            isDying,
            hitboxSize,
            enemyType,
            creatureFlags,
            energizerTimer,
            maxHealth,
            radioactiveFlash,
        );
    }

    /**
     * Draw corpse sprite.
     * Rendering logic extracted to EntityRenderer.ts.
     */
    drawCorpse(
        grim: GrimInterface,
        x: number,
        y: number,
        rotation: number,
        tint: ColorTint = { r: 1, g: 1, b: 1 },
        scale: number = 1.0,
        enemyType: EnemyType = EnemyType.Spider,
    ): void {
        _drawCorpse(this as unknown as EntityTextureContext, grim, x, y, rotation, tint, scale, enemyType);
    }

    /**
     * Draw projectile sprite based on type.
     * Rendering logic extracted to ProjectileRenderer.ts.
     */
    drawProjectile(
        grim: GrimInterface,
        projectile: {
            x: number;
            y: number;
            angle: number;
            projectileType: ProjectileType;
            lifetime: number;
            maxLifetime: number;
            headX: number;
            headY: number;
            tailX: number;
            tailY: number;
            perpX: number;
            perpY: number;
            hasFireVisual?: boolean;
            speedScale?: number;
            ionMasterScale?: number;
            // Rocket explosion state (C projectiles.c L620-659)
            isExploding?: boolean;
            explosionTimer?: number;
            explosionScale?: number;
            // Origin position for distance-based scaling (PULSE_GUN, SPLITTER_GUN, BLADE_GUN)
            originX?: number;
            originY?: number;
            // Frame time for time-based animation (BLADE_GUN spinning, PLAGUE_SPREADER animation)
            frameTime?: number;
        },
    ): void {
        _drawProjectile(this as unknown as ProjectileTextureContext, grim, projectile);
    }

    // ============================================================
    // Bonus/pickup rendering
    // ============================================================

    /**
     * Draw a bonus/pickup sprite.
     * Rendering logic extracted to BonusRenderer.ts.
     */
    drawBonus(
        grim: GrimInterface,
        x: number,
        y: number,
        bonusType: BonusType,
        amount: number,
        timeLeft: number,
        timeMax: number,
        bonusIndex: number,
        animTimer: number,
        elapsedMs: number,
    ): void {
        _drawBonus(
            this as unknown as BonusTextureContext,
            grim,
            x,
            y,
            bonusType,
            amount,
            timeLeft,
            timeMax,
            bonusIndex,
            animTimer,
            elapsedMs,
        );
    }


}
