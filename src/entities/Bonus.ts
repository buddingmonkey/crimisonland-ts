/**
 * Bonus - Powerup/pickup entity
 *
 * Port of bonus system from crimsonland.exe_decompiled.c
 */

import type { GrimInterface } from '../engine/GrimInterface';

/**
 * Bonus types (from C code lines 6364-6483)
 */
export enum BonusType {
    NONE = 0,
    WEAPON = 1, // Weapon pickup (C: BONUS_ID_WEAPON)
    POINTS = 2, // Direct XP gain (C: BONUS_ID_POINTS, lines 6481-6483)
    HEALTH = 3, // Health restore (C: BONUS_ID_MEDIKIT)
    SHIELD = 4, // Invulnerability timer (C: BONUS_ID_SHIELD, lines 6364-6371)
    FIRE_BULLETS = 5, // Rapid fire mode (C: BONUS_ID_FIRE_BULLETS, lines 6409-6419)
    ENERGIZER = 6, // Enemies flee (C: BONUS_ID_ENERGIZER, lines 6420-6425)
    DOUBLE_EXPERIENCE = 7, // 2x XP multiplier (C: BONUS_ID_DOUBLE_EXPERIENCE, lines 6426-6431)
    NUKE = 8, // Area damage explosion (C: BONUS_ID_NUKE, lines 6432-6480)
    FIREBLAST = 9, // 16 radial projectiles (C: BONUS_ID_FIREBLAST, lines 6392-6408)
    SHOCK_CHAIN = 10, // Chain lightning (C: BONUS_ID_SHOCK_CHAIN, lines 6372-6391)
    REFLEX_BOOST = 11, // Slow motion (C: BONUS_ID_REFLEX_BOOST, lines 6263-6301)
    WEAPON_POWER_UP = 12, // Faster fire rate + instant reload (C: BONUS_ID_WEAPON_POWER_UP, lines 6302-6312)
    SPEED = 13, // Movement speed boost (C: BONUS_ID_SPEED, lines 6313-6320)
    FREEZE = 14, // Freeze all enemies (C: BONUS_ID_FREEZE, lines 6321-6363)
}

/**
 * Bonus/powerup entity
 */
export class Bonus {
    public x: number;
    public y: number;
    public type: BonusType;
    public amount: number; // Weapon ID, point value, or health amount
    public timeLeft: number; // Lifetime in seconds (10s from C line 18105)
    public timeMax: number = 10.0; // Max lifetime for visual effects
    public active: boolean = true;
    public pickedUp: boolean = false;

    constructor(x: number, y: number, type: BonusType, amount: number) {
        this.x = x;
        this.y = y;
        this.type = type;
        this.amount = amount;
        this.timeLeft = 10.0; // C line 18105
    }

    /**
     * Update bonus (decrement timer)
     * C: bonuses.c lines 316-326 — picked-up bonuses decay 3× faster
     */
    update(dt: number): void {
        if (!this.active) return;

        if (this.pickedUp) {
            this.timeLeft -= dt * 3.0; // 3× faster decay after pickup
        } else {
            this.timeLeft -= dt;
        }
        if (this.timeLeft <= 0) {
            this.active = false;
        }
    }

    /**
     * Mark bonus as picked up — starts post-pickup decay animation.
     * C: bonus.picked_up = 1; bonus.time_left = 0.5;
     * Bonus lingers for 0.5s at 3× decay rate (~0.17s visible).
     */
    markPickedUp(): void {
        this.pickedUp = true;
        this.timeLeft = 0.5;
    }

    /**
     * Check if bonus is active
     */
    isActive(): boolean {
        return this.active && this.timeLeft > 0;
    }

    /**
     * Get pickup radius
     */
    getRadius(): number {
        return 16; // Pickup radius
    }

    /**
     * Render bonus
     */
    render(grim: GrimInterface): void {
        if (!this.isActive()) return;

        const radius = this.getRadius();

        // Pulsing effect based on time left
        const pulse = Math.sin(this.timeLeft * 8) * 0.2 + 0.8;
        const visualRadius = radius * pulse;

        // Color based on type (C code bonus types)
        let r = 255,
            g = 255,
            b = 255;
        switch (this.type) {
            case BonusType.WEAPON:
                r = 100;
                g = 150;
                b = 255; // Blue
                break;
            case BonusType.POINTS:
                r = 255;
                g = 215;
                b = 0; // Gold
                break;
            case BonusType.HEALTH:
                r = 100;
                g = 255;
                b = 100; // Green
                break;
            case BonusType.SHIELD:
                r = 100;
                g = 200;
                b = 255; // Light blue
                break;
            case BonusType.FIRE_BULLETS:
                r = 255;
                g = 100;
                b = 0; // Orange
                break;
            case BonusType.ENERGIZER:
                r = 255;
                g = 255;
                b = 0; // Yellow
                break;
            case BonusType.DOUBLE_EXPERIENCE:
                r = 0;
                g = 255;
                b = 0; // Bright green
                break;
            case BonusType.NUKE:
                r = 255;
                g = 0;
                b = 0; // Red
                break;
            case BonusType.FIREBLAST:
                r = 255;
                g = 150;
                b = 0; // Orange-red
                break;
            case BonusType.SHOCK_CHAIN:
                r = 150;
                g = 150;
                b = 255; // Purple-blue
                break;
            case BonusType.REFLEX_BOOST:
                r = 100;
                g = 100;
                b = 255; // Deep blue
                break;
            case BonusType.WEAPON_POWER_UP:
                r = 200;
                g = 100;
                b = 255; // Purple
                break;
            case BonusType.SPEED:
                r = 0;
                g = 200;
                b = 200; // Cyan
                break;
            case BonusType.FREEZE:
                r = 150;
                g = 220;
                b = 255; // Ice blue
                break;
        }

        // Draw outer glow
        grim.setColor(r, g, b, 100);
        grim.drawCircleFilled(this.x, this.y, visualRadius * 1.5);

        // Draw main circle
        grim.setColor(r, g, b, 255);
        grim.drawCircleFilled(this.x, this.y, visualRadius);

        // Draw inner highlight
        grim.setColor(255, 255, 255, 200);
        grim.drawCircleFilled(this.x, this.y, visualRadius * 0.5);
    }
}
