/**
 * DummyEnemy — Stationary test target for E2E testing
 *
 * Extends Enemy so it participates in the existing collision system.
 * Does not move, renders as a cyan debug circle, and records detailed
 * hit data for assertions (damage, projectile velocity, collision angle,
 * position, status effects).
 *
 * Spawn via console: spawn_dummy <x> <y>
 */

import { Enemy, EnemyType } from './Enemy';
import type { GrimInterface } from '../engine/GrimInterface';

/**
 * Record of a single hit on the dummy
 */
export interface HitRecord {
    /** Damage dealt (after perk modifiers) */
    damage: number;
    /** Damage type (1=bullet, 4=fire, 7=ion, etc.) */
    damageType: number;
    /** Knockback impulse X (encodes projectile direction + magnitude) */
    impulseX: number;
    /** Knockback impulse Y */
    impulseY: number;
    /** Dummy position X at time of hit */
    positionX: number;
    /** Dummy position Y at time of hit */
    positionY: number;
    /** Angle the hit came from (radians, from impulse vector) */
    collisionAngle: number;
    /** Impulse magnitude (proxy for projectile force) */
    impulseMagnitude: number;
    /** Timestamp of the hit */
    timestamp: number;
    /** Status effects active after this hit */
    statusEffects: string[];
    /** Remaining health after this hit */
    healthAfter: number;
}

/**
 * Stationary test target enemy
 */
export class DummyEnemy extends Enemy {
    /** Identifies this as a dummy (for filtering) */
    public readonly isDummy: boolean = true;

    /** Ordered log of all hits received */
    public hitLog: HitRecord[] = [];

    /** Optional label for identification when multiple dummies exist */
    public label: string;

    constructor(x: number, y: number, label?: string) {
        super(x, y, EnemyType.Zombie);

        this.label = label ?? `dummy_${Math.floor(x)}_${Math.floor(y)}`;

        // Very high health — dummy is meant to survive many hits
        this.health = 999999;
        this.maxHealth = 999999;

        // No movement
        this.speed = 0;
        this.maxSpeed = 0;

        // Large collision radius for easy targeting
        this.size = 60;

        // No contact damage
        this.damage = 0;

        // No XP reward
        this.rewardValue = 0;

        // Distinctive cyan color
        this.tintR = 0.0;
        this.tintG = 0.9;
        this.tintB = 1.0;

        // Disable shooting
        this.canShootPlasma = false;
        this.canShootMinigun = false;
    }

    /**
     * No-op: dummy does not move or chase
     */
    override update(_dt: number, _playerX: number, _playerY: number, _player?: any): void {
        // Stationary — only decay hit flash timer
        if (this.hitFlashTimer > 0) {
            this.hitFlashTimer -= _dt;
            if (this.hitFlashTimer < 0) this.hitFlashTimer = 0;
        }
    }

    /**
     * Take damage and record detailed hit data
     */
    override takeDamage(
        amount: number,
        damageType: number = 1,
        impulseX: number = 0,
        impulseY: number = 0,
        perkSystem?: any,
        player?: any,
    ): void {
        const healthBefore = this.health;

        // Call parent for actual damage processing
        super.takeDamage(amount, damageType, impulseX, impulseY, perkSystem, player);

        // Calculate collision angle from impulse
        const collisionAngle = impulseX !== 0 || impulseY !== 0 ? Math.atan2(impulseY, impulseX) : 0;

        const impulseMagnitude = Math.sqrt(impulseX * impulseX + impulseY * impulseY);

        // Collect current status effects
        const statusEffects: string[] = [];
        if (this.isPoisoned) statusEffects.push('poisoned');
        if (this.isFrozen) statusEffects.push('frozen');
        if ((this.flags & 0x02) !== 0) statusEffects.push('burning');
        if ((this.flags & 0x01) !== 0) statusEffects.push('poison_dot');

        // Record the hit
        const record: HitRecord = {
            damage: healthBefore - this.health,
            damageType,
            impulseX,
            impulseY,
            positionX: this.x,
            positionY: this.y,
            collisionAngle,
            impulseMagnitude,
            timestamp: Date.now(),
            statusEffects,
            healthAfter: this.health,
        };

        this.hitLog.push(record);

        // Keep dummy alive even if health went to 0
        if (this.health <= 0) {
            this.health = 999999;
            this.active = true;
        }

        // Resist knockback — stay in place
        this.velX = 0;
        this.velY = 0;
    }

    // ============================================
    // Query methods
    // ============================================

    /** Get the full hit log */
    getHitLog(): HitRecord[] {
        return this.hitLog;
    }

    /** Get the most recent hit, or null if none */
    getLastHit(): HitRecord | null {
        return this.hitLog.length > 0 ? this.hitLog[this.hitLog.length - 1] : null;
    }

    /** Get total damage dealt across all hits */
    getTotalDamage(): number {
        return this.hitLog.reduce((sum, h) => sum + h.damage, 0);
    }

    /** Get number of hits received */
    getHitCount(): number {
        return this.hitLog.length;
    }

    /** Reset dummy to pristine state */
    reset(): void {
        this.hitLog = [];
        this.health = 999999;
        this.maxHealth = 999999;
        this.active = true;
        this.isPoisoned = false;
        this.isFrozen = false;
        this.flags = 0;
        this.hitFlashTimer = 0;
        this.velX = 0;
        this.velY = 0;
    }

    // ============================================
    // Rendering — distinctive debug visualization
    // ============================================

    /**
     * Render as a cyan circle with crosshair and health/hit info
     */
    override render(grim: GrimInterface, _perkSystem?: any, _spriteRenderer?: any, _debugMode: boolean = true): void {
        if (!this.isAlive()) return;

        const radius = this.getRadius();

        // Hit flash: blend toward white
        let r = 0,
            g = 230,
            b = 255;
        if (this.hitFlashTimer > 0) {
            const flash = this.hitFlashTimer / 0.2;
            r = Math.floor(r + (255 - r) * flash);
            g = Math.floor(g + (255 - g) * flash);
            b = Math.floor(b + (255 - b) * flash);
        }

        // Outer circle (filled, semi-transparent)
        grim.setColor(r, g, b, 100);
        grim.drawCircleFilled(this.x, this.y, radius);

        // Border circle (bright)
        grim.setColor(r, g, b, 255);
        grim.drawCircleOutline(this.x, this.y, radius);

        // Crosshair lines
        const half = radius * 0.7;
        grim.drawLine(this.x - half, this.y, this.x + half, this.y, 1);
        grim.drawLine(this.x, this.y - half, this.x, this.y + half, 1);

        // Center dot
        grim.setColor(255, 50, 50, 255);
        grim.drawCircleFilled(this.x, this.y, 3);

        // Hit count indicator (small red dots around the rim)
        const hitCount = Math.min(this.hitLog.length, 12); // Max 12 dots
        for (let i = 0; i < hitCount; i++) {
            const angle = (i / 12) * Math.PI * 2 - Math.PI / 2;
            const dotX = this.x + Math.cos(angle) * (radius + 6);
            const dotY = this.y + Math.sin(angle) * (radius + 6);
            grim.setColor(255, 100, 50, 255);
            grim.drawCircleFilled(dotX, dotY, 2);
        }
    }
}
