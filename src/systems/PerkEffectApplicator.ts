import { type Player } from '../entities/Player';
import { type PerkSystem } from './PerkSystem';
import { type EnemySpawner } from './enemy/EnemySpawner';
import { InstantPerkEffectResult } from './player/PlayerModifier';
import { clearReload } from '../entities/PlayerWeapon';
import { getWeaponCount } from '../data/WeaponData';
import { gameConsole } from '../console/Console';
import { questSystem } from './quest/QuestSystem';

export interface PerkEffectGameContext {
    player: Player;
    perkSystem: PerkSystem;
    enemySpawner: EnemySpawner;
    lastLevel: number;
    perkPendingCount: number;
}

export interface PerkEffectResult {
    lastLevel: number;
    perkPendingCount: number;
}

export function applyInstantPerkEffectToGame(
    fx: InstantPerkEffectResult,
    ctx: PerkEffectGameContext,
): PerkEffectResult {
    const { player, perkSystem, enemySpawner } = ctx;
    let { lastLevel, perkPendingCount } = ctx;

    player.health = fx.health;
    player.experience = fx.xp;

    // Grim Deal / Fatal Lottery: player death
    if (fx.shouldDie) {
        player.health = -1.0;
    }

    // Infernal Contract: +3 levels, +3 pending perks
    if (fx.extraLevels > 0) {
        lastLevel += fx.extraLevels;
        perkPendingCount += fx.extraPendingPerks;
    }

    // Death Clock: clear regen perks
    for (const clearId of fx.clearPerks) {
        perkSystem.removePerk(clearId);
    }

    // Ammo Maniac: refill all weapon ammo
    if (fx.shouldRefillAllAmmo) {
        player.ammo = player.clipSize;
        player.altAmmo = player.altClipSize;
        clearReload(player);
        player.altReloadTimer = 0;
        player.altReloadActive = false;
        gameConsole.print('All ammo refilled!');
    }

    // Random Weapon: get a random weapon (not pistol, not current)
    // C perk_apply: picks weapon != 0 (pistol) && weapon != current_weapon
    if (fx.shouldGetRandomWeapon) {
        const weaponCount = Math.min(getWeaponCount(), 16); // Only player-selectable weapons (0-15)
        let weaponId = player.weaponId;
        for (let attempt = 0; attempt < 50; attempt++) {
            const candidate = 1 + Math.floor(Math.random() * (weaponCount - 1)); // Range: 1..(weaponCount-1)
            if (candidate !== player.weaponId) {
                weaponId = candidate;
                break;
            }
        }
        player.switchWeapon(weaponId, perkSystem);
        gameConsole.print(`Random weapon: ${player.getWeaponStats().name}`);
    }

    // Breathing Room: shrink enemy hitboxes (C perk_apply lines 213-220: hitbox -= frame_dt)
    if (fx.shouldShrinkEnemyHitboxes) {
        for (const enemy of enemySpawner.getActiveEnemies()) {
            if (enemy.isAlive()) {
                enemy.size -= 1 / 60; // C: hitbox_size -= frame_dt per creature
            }
        }
        gameConsole.print('Breathing Room: enemy hitboxes shrunk!');
    }

    // Lifeline 50/50: kill every other enemy with health <= 500 (C perk_apply lines 175-188)
    if (fx.shouldKillAlternateWeakEnemies) {
        let toggle = false;
        for (const enemy of enemySpawner.getActiveEnemies()) {
            // C line 179-180: skip enemies with flag 4 (bosses)
            if (enemy.isAlive() && enemy.health <= 500 && (enemy.flags & 4) === 0) {
                toggle = !toggle;
                if (toggle) {
                    enemy.takeDamage(enemy.health + 1, 0);
                    // Always fatal — report to quest system
                    questSystem.reportEnemyKilled();
                }
            }
        }
        gameConsole.print('Lifeline 50/50: enemies cleared!');
    }

    // Man Bomb: initial explosion burst
    if (fx.shouldExplode) {
        player.pendingManBombBurst = true;
    }

    // Plaguebearer: set flag (C: plaguebearer_active = 1, perks.c:296)
    if (fx.shouldSetPlaguebearer) {
        player.plaguebearerActive = true;
        gameConsole.print('Plaguebearer activated!');
    }

    return { lastLevel, perkPendingCount };
}
