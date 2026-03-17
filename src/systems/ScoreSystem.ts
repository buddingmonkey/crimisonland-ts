/**
 * ScoreSystem - Player performance tracking
 *
 * Tracks score, kills, and survival time.
 * XP/level is tracked exclusively in player.experience and player.level (C: player_state_table).
 */

import { EnemyType } from '../entities/Enemy';

/**
 * Score system for tracking player performance
 */
export class ScoreSystem {
    private score: number = 0;
    private kills: number = 0;
    private survivalTime: number = 0; // in seconds
    private shotsFired: number = 0;
    private shotsHit: number = 0;

    // Score values per enemy type
    private static readonly SCORE_VALUES: Record<EnemyType, number> = {
        [EnemyType.Zombie]: 15,
        [EnemyType.Lizard]: 20,
        [EnemyType.Spider]: 15,
        [EnemyType.Spider2]: 20,
        [EnemyType.Alien]: 25,
        [EnemyType.Trooper]: 20,
    };

    /**
     * Add kill and update score
     */
    addKill(enemyType: EnemyType): void {
        this.kills++;
        const points = ScoreSystem.SCORE_VALUES[enemyType] || 10;
        this.score += points;
    }

    /**
     * Add score directly (for bonuses)
     */
    addScore(points: number): void {
        this.score += points;
    }

    /**
     * Update survival time
     */
    update(dt: number): void {
        this.survivalTime += dt;
    }

    /**
     * Get current score
     */
    getScore(): number {
        return this.score;
    }

    /**
     * Get kill count
     */
    getKills(): number {
        return this.kills;
    }

    /**
     * Get survival time in seconds
     */
    getSurvivalTime(): number {
        return this.survivalTime;
    }

    /**
     * Get formatted survival time (MM:SS)
     */
    getFormattedTime(): string {
        const minutes = Math.floor(this.survivalTime / 60);
        const seconds = Math.floor(this.survivalTime % 60);
        return `${minutes.toString().padStart(2, '0')}:${seconds.toString().padStart(2, '0')}`;
    }

    /**
     * Record a shot fired by the player
     */
    recordShot(): void {
        this.shotsFired++;
    }

    /**
     * Record a projectile hitting an enemy
     */
    recordHit(): void {
        this.shotsHit++;
    }

    /**
     * Get hit accuracy percentage (0-100)
     */
    getHitPercent(): number {
        if (this.shotsFired === 0) return 0;
        return Math.round((this.shotsHit / this.shotsFired) * 100);
    }

    /**
     * Reset all stats
     */
    reset(): void {
        this.score = 0;
        this.kills = 0;
        this.survivalTime = 0;
        this.shotsFired = 0;
        this.shotsHit = 0;
    }
}
