/**
 * HUDSystem - Heads-Up Display rendering
 *
 * Displays player stats, score, and game information using text rendering.
 */

import type { GrimInterface } from '../engine/GrimInterface';
import type { Player } from '../entities/Player';
import type { ScoreSystem } from './ScoreSystem';

/**
 * HUD rendering system
 */
export class HUDSystem {
    /**
     * Render the HUD
     */
    render(grim: GrimInterface, player: Player, scoreSystem: ScoreSystem): void {
        // Health bar (top left)
        const healthPercent = Math.max(0, Math.min(100, player.health));
        grim.drawText(10, 10, `Health: ${Math.floor(healthPercent)}/100`, 16, '#ffffff');

        // Ammo count (below health)
        grim.drawText(10, 35, `Ammo: ${Math.ceil(player.ammo)}/${player.clipSize}`, 16, '#ffffff');

        // Experience/Level (below ammo) — reads from player.experience (single XP pool, Fix 2)
        const xp = player.experience;
        const level = 'level' in player ? (player as any).level : 1;
        grim.drawText(10, 60, `XP: ${xp} (Lv.${level})`, 16, '#ffffff');

        // Survival time (top right)
        const survivalTime = scoreSystem.getSurvivalTime();
        const minutes = Math.floor(survivalTime / 60);
        const seconds = Math.floor(survivalTime % 60);
        const timeText = `Time: ${minutes}:${seconds.toString().padStart(2, '0')}`;
        grim.drawText(grim.getWidth() - 120, 10, timeText, 16, '#ffffff');

        // Kill count (below time)
        const kills = scoreSystem.getKills();
        grim.drawText(grim.getWidth() - 120, 35, `Kills: ${kills}`, 16, '#ffffff');
    }
}
