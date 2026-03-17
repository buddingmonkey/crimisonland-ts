/**
 * GameConsoleCommands - Console command registration for the Game class
 *
 * Extracted from Game.ts to reduce file size.
 * registerGameCommands() is called from Game.registerCommands().
 */

import { gameConsole } from './Console';
import { GameState, GameMode } from '../Game';
import { Enemy, EnemyType } from '../entities/Enemy';
import { getWeaponCount, getWeaponStats, WEAPON_DATA } from '../data/WeaponData';
import { getWeaponUnlockRegistry } from '../systems/WeaponUnlockRegistry';
import type { Player } from '../entities/Player';
import { clearReload } from '../entities/PlayerWeapon';
import type { EnemySpawner } from '../systems/enemy/EnemySpawner';
import type { PerkSystem } from '../systems/PerkSystem';
import type { AssetManager } from '../data';
import type { GrimInterface } from '../engine/GrimInterface';
import type { BloodEffectSystem } from '../systems/effects/BloodEffectSystem';
import type { EnemyDeathEffects } from '../systems/enemy/EnemyDeathEffects';
import type { ScoreSystem } from '../systems/ScoreSystem';
import type { TutorialSystem } from '../systems/modes/TutorialSystem';
import type { QuestCompleteScreen } from '../ui/screens/QuestCompleteScreen';
import { questSystem } from '../systems/quest/QuestSystem';
import { QUEST_DATABASE } from '../data/QuestData';
import type { AlienZooKeeperScreen } from '../ui/screens/AlienZooKeeperScreen';

/**
 * Context interface – the subset of Game members needed by console commands.
 * Avoids a circular import (Game → GameConsoleCommands → Game).
 */
export interface GameCommandContext {
    getState(): GameState;
    setState(s: GameState): void;
    getGameMode(): GameMode;
    setGameMode(m: GameMode): void;
    getGrim(): GrimInterface;
    getPlayer(): Player | null;
    startGame(): void;
    startTutorial(): void;
    regenerateTerrain(tier: number): void;
    getEnemySpawner(): EnemySpawner;
    getPerkSystem(): PerkSystem;
    getAssetManager(): AssetManager;
    getBloodEffectSystem(): BloodEffectSystem;
    getEnemyDeathEffects(): EnemyDeathEffects;
    getScoreSystem(): ScoreSystem;
    getTutorialSystem(): TutorialSystem;
    getQuestCompleteScreen(): QuestCompleteScreen;
    getDebugRenderMode(): boolean;
    setDebugRenderMode(v: boolean): void;
    getDebugEnemyHeading(): boolean;
    setDebugEnemyHeading(v: boolean): void;
    getAlienZooKeeperScreen(): AlienZooKeeperScreen;
}

/**
 * Register all game console commands onto the gameConsole singleton.
 * Called once during Game.init().
 */
export function registerGameCommands(ctx: GameCommandContext): void {
    gameConsole.registerCommand('version', () => {
        gameConsole.print('Crimsonland TypeScript v1.0.0');
        gameConsole.print('Based on Crimsonland v1.9.93 (GOG Classic)');
    });

    gameConsole.registerCommand('state', () => {
        gameConsole.print(`Current state: ${GameState[ctx.getState()]}`);
    });

    gameConsole.registerCommand('fps', () => {
        gameConsole.print(`FPS: ${ctx.getGrim().getFPS()}`);
    });

    gameConsole.registerCommand('time', () => {
        gameConsole.print(`Time: ${(ctx.getGrim().getTime() / 1000).toFixed(2)}s`);
    });

    gameConsole.registerCommand('start', () => {
        ctx.setGameMode(GameMode.Survival);
        ctx.startGame();
        gameConsole.print('Survival game started!');
    });

    gameConsole.registerCommand('start_tutorial', () => {
        ctx.setGameMode(GameMode.Tutorial);
        ctx.startGame();
        ctx.startTutorial();
        gameConsole.print('Tutorial started!');
    });

    // Debug/cheat commands
    gameConsole.registerCommand('sv_score_addexp', (args: string[]) => {
        const player = ctx.getPlayer();
        if (!player || !player.isAlive()) {
            gameConsole.print('Error: No active game');
            return;
        }
        const amount = parseInt(args[0] || '0');
        if (isNaN(amount)) {
            gameConsole.print('Usage: sv_score_addexp <amount>');
            return;
        }
        player.experience += amount;
        gameConsole.print(`Added ${amount} XP. Total: ${player.experience} (Level ${player.level})`);
    });

    gameConsole.registerCommand('debug_enemies', () => {
        const player = ctx.getPlayer();
        if (!player || !player.isAlive()) {
            gameConsole.print('Error: No active game');
            return;
        }
        const enemies = ctx.getEnemySpawner().getActiveEnemies();
        gameConsole.print(`Active enemies: ${enemies.length}`);
        if (enemies.length > 0) {
            const e = enemies[0];
            gameConsole.print(`First enemy: type=${e.type} speed=${e.speed.toFixed(1)} health=${e.health.toFixed(1)}`);
        }
    });

    // Spawn a specific enemy type for debugging sprites/rotation
    const enemyTypeNames: Record<number, string> = {
        0: 'Zombie',
        1: 'Lizard',
        2: 'Spider',
        3: 'Spider2',
        4: 'Alien',
        5: 'Trooper',
    };
    gameConsole.registerCommand('spawn_enemy', (args: string[]) => {
        const player = ctx.getPlayer();
        if (!player || !player.isAlive()) {
            gameConsole.print('Error: No active game');
            return;
        }
        if (args.length === 0) {
            gameConsole.print('Usage: spawn_enemy <type> [x] [y]');
            gameConsole.print('Types: 0=Zombie, 1=Lizard, 2=Spider, 3=Spider2, 4=Alien, 5=Trooper');
            gameConsole.print('If x/y omitted, spawns 100px to the right of player');
            return;
        }
        const typeId = parseInt(args[0]);
        if (isNaN(typeId) || typeId < 0 || typeId > 5) {
            gameConsole.print('Invalid type. Use 0-5: Zombie, Lizard, Spider, Spider2, Alien, Trooper');
            return;
        }
        const spawnX = args[1] ? parseFloat(args[1]) : player.x + 100;
        const spawnY = args[2] ? parseFloat(args[2]) : player.y;

        // Create enemy directly
        const enemy = new Enemy(spawnX, spawnY, typeId as EnemyType);
        enemy.active = true;
        enemy.health = 500; // High health so it doesn't die easily
        enemy.type = typeId;
        enemy.size = 50;
        enemy.hitboxSize = 50;
        enemy.speed = 0; // Stationary for visual inspection
        enemy.damage = 0; // No damage for safe debugging

        // Face toward player
        const dx = player.x - spawnX;
        const dy = player.y - spawnY;
        enemy.angle = Math.atan2(dy, dx);

        // Add to spawner's internal enemy list
        ctx.getEnemySpawner().addEnemy(enemy);

        const name = enemyTypeNames[typeId] || `Type${typeId}`;
        gameConsole.print(
            `Spawned ${name} (type ${typeId}) at (${spawnX.toFixed(0)}, ${spawnY.toFixed(0)}) angle=${((enemy.angle * 180) / Math.PI).toFixed(1)}°`,
        );
        gameConsole.print(
            `  creatureFlags=0x${enemy.creatureFlags.toString(16)} animPhase=${enemy.animPhase.toFixed(1)}`,
        );
    });

    // Toggle debug heading arrows on enemies
    gameConsole.registerCommand('debug_heading', () => {
        const next = !ctx.getDebugEnemyHeading();
        ctx.setDebugEnemyHeading(next);
        gameConsole.print(`Enemy heading arrows: ${next ? 'ON' : 'OFF'}`);
    });

    // Perk commands for testing
    gameConsole.registerCommand('perk_add', (args: string[]) => {
        const perkId = parseInt(args[0] || '0', 16); // Parse as hex
        if (isNaN(perkId)) {
            gameConsole.print('Usage: perk_add <perk_id_hex>');
            gameConsole.print('Example: perk_add 1c (uranium bullets)');
            return;
        }
        ctx.getPerkSystem().addPerk(perkId);
        gameConsole.print(`Added perk 0x${perkId.toString(16)}`);
    });

    gameConsole.registerCommand('perk_remove', (args: string[]) => {
        const perkId = parseInt(args[0] || '0', 16); // Parse as hex
        if (isNaN(perkId)) {
            gameConsole.print('Usage: perk_remove <perk_id_hex>');
            return;
        }
        ctx.getPerkSystem().removePerk(perkId);
        gameConsole.print(`Removed perk 0x${perkId.toString(16)}`);
    });

    gameConsole.registerCommand('perk_list', () => {
        const perks = ctx.getPerkSystem().getActivePerks();
        if (perks.length === 0) {
            gameConsole.print('No active perks');
            return;
        }
        gameConsole.print(`Active perks (${perks.length}):`);
        const perkNames: Record<number, string> = {
            0x1c: 'Uranium Bullets (+100%)',
            0x1d: 'Doctor (+20%)',
            0x22: 'Barrel Greaser (+40%)',
            0x27: 'Pyromaniac (+50% fire)',
            0x28: 'Ion Gun Master (+20% ion)',
            0x30: 'Vulture (2x drops)',
        };
        for (const perk of perks) {
            const name = perkNames[perk] || 'Unknown';
            gameConsole.print(`  0x${perk.toString(16)}: ${name}`);
        }
    });

    // Player damage/health commands
    gameConsole.registerCommand('player_damage', (args: string[]) => {
        const player = ctx.getPlayer();
        if (!player || !player.isAlive()) {
            gameConsole.print('Error: No active game');
            return;
        }
        const damage = parseFloat(args[0] || '10');
        if (isNaN(damage)) {
            gameConsole.print('Usage: player_damage <amount>');
            return;
        }
        player.takeDamage(damage, ctx.getPerkSystem());
        gameConsole.print(`Dealt ${damage} damage. Health: ${player.health.toFixed(1)}`);
    });

    gameConsole.registerCommand('player_heal', (args: string[]) => {
        const player = ctx.getPlayer();
        if (!player || !player.isAlive()) {
            gameConsole.print('Error: No active game');
            return;
        }
        const amount = parseFloat(args[0] || '25');
        if (isNaN(amount)) {
            gameConsole.print('Usage: player_heal <amount>');
            return;
        }
        player.heal(amount);
        gameConsole.print(`Healed ${amount} HP. Health: ${player.health.toFixed(1)}`);
    });

    // Weapon commands
    gameConsole.registerCommand('weapon_switch', (args: string[]) => {
        const player = ctx.getPlayer();
        if (!player || !player.isAlive()) {
            gameConsole.print('Error: No active game');
            return;
        }
        const weaponId = parseInt(args[0] || '0');
        const maxId = getWeaponCount() - 1;
        if (isNaN(weaponId) || weaponId < 0 || weaponId > maxId) {
            gameConsole.print(`Usage: weapon_switch <0-${maxId}>`);
            gameConsole.print('0=Pistol, 1=AR, 2=Shotgun, 3=Sawed-off, 4=Jackhammer, ...');
            return;
        }
        player.switchWeapon(weaponId, ctx.getPerkSystem());
        const weaponName = player.getWeaponStats().name;
        gameConsole.print(`Switched to ${weaponName}. Ammo: ${player.ammo}/${player.clipSize}`);
    });

    gameConsole.registerCommand('weapon_add', (args: string[]) => {
        const player = ctx.getPlayer();
        if (!player || !player.isAlive()) {
            gameConsole.print('Error: No active game');
            return;
        }
        const maxId = getWeaponCount() - 1;
        if (args.length === 0) {
            gameConsole.print(`Usage: weapon_add <id|name>`);
            gameConsole.print('Available weapons:');
            for (let i = 0; i <= maxId; i++) {
                const stats = getWeaponStats(i);
                gameConsole.print(`  ${i}: ${stats.name}`);
            }
            return;
        }
        // Try parsing as number first, then search by name
        let weaponId = parseInt(args[0]);
        if (isNaN(weaponId)) {
            const searchName = args.join(' ').toLowerCase();
            const entry = Object.entries(WEAPON_DATA).find(
                ([, stats]: [string, unknown]) => (stats as { name: string }).name.toLowerCase() === searchName,
            );
            if (!entry) {
                gameConsole.print(`Unknown weapon: ${args.join(' ')}`);
                gameConsole.print('Use "weapon_add" with no args to list all weapons');
                return;
            }
            weaponId = parseInt(entry[0]);
        }
        if (weaponId < 0 || weaponId > maxId) {
            gameConsole.print(`Invalid weapon ID. Range: 0-${maxId}`);
            return;
        }
        player.switchWeapon(weaponId, ctx.getPerkSystem());
        const weaponName = player.getWeaponStats().name;
        gameConsole.print(`Added ${weaponName} (ID ${weaponId}). Ammo: ${player.ammo}/${player.clipSize}`);
    });

    gameConsole.registerCommand('ammo_refill', () => {
        const player = ctx.getPlayer();
        if (!player || !player.isAlive()) {
            gameConsole.print('Error: No active game');
            return;
        }
        player.ammo = player.clipSize;
        clearReload(player);
        const weaponName = player.getWeaponStats().name;
        gameConsole.print(`Refilled ${weaponName}. Ammo: ${player.ammo}/${player.clipSize}`);
    });

    // Reflex boost timer command
    gameConsole.registerCommand('reflex_boost', (args: string[]) => {
        const player = ctx.getPlayer();
        if (!player || !args[0]) {
            gameConsole.print('Usage: reflex_boost <seconds>');
            return;
        }
        const seconds = parseFloat(args[0]);
        if (isNaN(seconds) || seconds < 0) {
            gameConsole.print('Usage: reflex_boost <seconds>');
            return;
        }
        player.reflexBoostTimer = seconds;
        gameConsole.print(`Reflex boost activated for ${seconds} seconds`);
    });

    // Freeze timer command
    gameConsole.registerCommand('freeze', (args: string[]) => {
        const player = ctx.getPlayer();
        if (!player || !args[0]) {
            gameConsole.print('Usage: freeze <seconds>');
            return;
        }
        const seconds = parseFloat(args[0]);
        if (isNaN(seconds) || seconds < 0) {
            gameConsole.print('Usage: freeze <seconds>');
            return;
        }
        player.freezeTimer = seconds;
        gameConsole.print(`Freeze activated for ${seconds} seconds`);
    });

    // Asset manager debug commands
    gameConsole.registerCommand('assets_list', (args: string[]) => {
        const prefix = args[0] || '';
        const files = ctx.getAssetManager().listFiles(prefix);
        gameConsole.print(`Files matching "${prefix}": ${files.length}`);
        const sample = files.slice(0, 10);
        sample.forEach((f) => gameConsole.print(`  ${f}`));
        if (files.length > 10) {
            gameConsole.print(`  ... and ${files.length - 10} more`);
        }
    });

    gameConsole.registerCommand('assets_info', () => {
        gameConsole.print(`Total files: ${ctx.getAssetManager().fileCount}`);
        gameConsole.print(`Cached textures: ${ctx.getAssetManager().textureCount}`);
    });

    // Render mode toggle
    gameConsole.registerCommand('render_mode', (args: string[]) => {
        if (!args[0]) {
            gameConsole.print(`Current render mode: ${ctx.getDebugRenderMode() ? 'debug' : 'sprite'}`);
            gameConsole.print('Usage: render_mode <debug|sprite>');
            return;
        }
        if (args[0] === 'debug') {
            ctx.setDebugRenderMode(true);
            gameConsole.print('Switched to debug render mode');
        } else if (args[0] === 'sprite') {
            ctx.setDebugRenderMode(false);
            gameConsole.print('Switched to sprite render mode');
        } else {
            gameConsole.print('Usage: render_mode <debug|sprite>');
        }
    });

    // List terrain files in PAQ
    gameConsole.registerCommand('list_terrain', () => {
        const terFiles = ctx.getAssetManager().listFiles('ter/');
        gameConsole.print(`Found ${terFiles.length} terrain files:`);
        terFiles.forEach((f: string) => gameConsole.print(`  ${f}`));
    });

    // List gfx files in PAQ
    gameConsole.registerCommand('list_gfx', () => {
        const gfxFiles = ctx.getAssetManager().listFiles('gfx/');
        gameConsole.print(`Found ${gfxFiles.length} gfx files:`);
        gfxFiles.forEach((f: string) => gameConsole.print(`  ${f}`));
    });

    // Quest commands for testing (no menu integration yet)
    gameConsole.registerCommand('quest_list', () => {
        gameConsole.print('Available Quests:');
        for (let tier = 1; tier <= 5; tier++) {
            gameConsole.print(`  Tier ${tier}:`);
            const tierQuests = QUEST_DATABASE.filter((q: any) => q.tier === tier);
            for (const quest of tierQuests) {
                gameConsole.print(`    ${tier}-${quest.index}: ${quest.name} (${quest.timeLimitMs / 1000}s)`);
            }
        }
        gameConsole.print(`Total: ${QUEST_DATABASE.length} quests`);
    });

    gameConsole.registerCommand('quest_start', (args: string[]) => {
        if (args.length !== 2) {
            gameConsole.print('Usage: quest_start <tier> <index>');
            gameConsole.print('Example: quest_start 1 1');
            return;
        }
        const tier = parseInt(args[0]);
        const index = parseInt(args[1]);
        if (isNaN(tier) || isNaN(index) || tier < 1 || tier > 5 || index < 1 || index > 10) {
            gameConsole.print('Invalid tier (1-5) or index (1-10)');
            return;
        }
        // Start quest with spawn callback

        questSystem.setSpawnCallback((entry: any) => {
            // Spawn all enemies from this spawn entry
            for (let i = 0; i < entry.count; i++) {
                ctx.getEnemySpawner().spawnQuestEnemy(entry.posX, entry.posY, entry.templateId);
                questSystem.reportEnemySpawned(1);
            }
        });
        questSystem.startQuest(tier, index);
        // Set game mode to Quest and start the game
        ctx.setGameMode(GameMode.Quest);

        // Regenerate terrain for quest tier (must be done before startGame)
        ctx.regenerateTerrain(tier);

        if (ctx.getState() !== GameState.Playing) {
            ctx.startGame();
        }
        gameConsole.print(`Started quest ${tier}-${index} in Quest mode`);
    });

    gameConsole.registerCommand('quest_info', () => {
        const quest = questSystem.getCurrentQuest();
        if (!quest) {
            gameConsole.print('No quest active');
            return;
        }
        const state = questSystem.getState();
        const stateNames = ['INACTIVE', 'PLAYING', 'TRANSITIONING', 'COMPLETE'];
        gameConsole.print(`Quest: ${quest.name}`);
        gameConsole.print(`State: ${stateNames[state]}`);
        gameConsole.print(`Timeline: ${(questSystem.getTimelineMs() / 1000).toFixed(1)}s`);
        gameConsole.print(`Time Limit: ${quest.timeLimitMs / 1000}s`);
        gameConsole.print(`Active Enemies: ${questSystem.getActiveEnemyCount()}`);
        gameConsole.print(`Pending Spawns: ${questSystem.getPendingSpawnCount()}`);
    });

    gameConsole.registerCommand('quest_skip', () => {
        if (!questSystem.isActive()) {
            gameConsole.print('No active quest to skip');
            return;
        }
        questSystem.forceComplete();
        gameConsole.print('Quest force-completed');
    });

    gameConsole.registerCommand('quest_complete', () => {
        // Show quest complete screen with dummy data for testing
        ctx.getQuestCompleteScreen().show({
            baseTimeMs: 60000, // 1:00
            lifeBonusMs: 100000, // Full health (100 * 1000)
            unpickedPerks: 0,
            finalTimeMs: 60000, // 1:00
            questName: 'Test Quest',
            isHighScore: true,
            unlockWeaponName: 'Plasma Rifle',
            unlockPerkName: 'Fatal Attraction',
            scoreSeconds: 60.55,
            rank: 1,
            experience: 17730,
            frags: 30,
            hitPercent: 41,
            weaponName: 'Shotgun',
            weaponId: 1,
            questTier: 1,
            questIndex: 1,
        });
        ctx.setState(GameState.QuestComplete);
        gameConsole.print('Quest complete screen shown (test mode)');
    });

    gameConsole.registerCommand('quest_unlock', (args: string[]) => {
        if (args.length !== 1) {
            gameConsole.print('Usage: quest_unlock <index>');
            gameConsole.print(`Current unlock index: ${questSystem.getUnlockIndex()}`);
            return;
        }
        const index = parseInt(args[0]);
        if (isNaN(index) || index < 0 || index > 39) {
            gameConsole.print('Invalid index (0-39)');
            return;
        }
        questSystem.setUnlockIndex(index);
        gameConsole.print(`Unlock index set to ${index}`);
    });

    // ============================================
    // Test environment commands (E2E testing)
    // ============================================

    gameConsole.registerCommand('test_env_start', () => {
        ctx.startGame();
        ctx.getEnemySpawner().spawningEnabled = false;
        ctx.getEnemySpawner().clear(); // Remove any enemies that spawned during startGame
        gameConsole.print('Test environment started (no enemy spawning)');
    });

    gameConsole.registerCommand('test_env_stop', () => {
        ctx.getEnemySpawner().spawningEnabled = true;
        gameConsole.print('Enemy spawning re-enabled');
    });

    // ============================================
    // Dummy enemy commands (E2E testing)
    // ============================================

    gameConsole.registerCommand('spawn_dummy', (args: string[]) => {
        if (args.length < 2) {
            gameConsole.print('Usage: spawn_dummy <x> <y> [label]');
            return;
        }
        const x = parseFloat(args[0]);
        const y = parseFloat(args[1]);
        if (isNaN(x) || isNaN(y)) {
            gameConsole.print('Error: x and y must be numbers');
            return;
        }
        const label = args[2] || undefined;
        const dummy = ctx.getEnemySpawner().spawnDummy(x, y, label);
        gameConsole.print(`Spawned dummy '${dummy.label}' at (${x}, ${y})`);
    });

    gameConsole.registerCommand('dummy_report', () => {
        const dummies = ctx.getEnemySpawner().getDummies();
        if (dummies.length === 0) {
            gameConsole.print('No dummies active');
            return;
        }
        for (const d of dummies) {
            gameConsole.print(`--- ${d.label} at (${Math.round(d.x)}, ${Math.round(d.y)}) ---`);
            gameConsole.print(`  Hits: ${d.getHitCount()}  Total dmg: ${d.getTotalDamage().toFixed(1)}`);
            const last = d.getLastHit();
            if (last) {
                gameConsole.print(
                    `  Last hit: dmg=${last.damage.toFixed(1)} type=${last.damageType} angle=${((last.collisionAngle * 180) / Math.PI).toFixed(1)}°`,
                );
                gameConsole.print(
                    `  Impulse: (${last.impulseX.toFixed(1)}, ${last.impulseY.toFixed(1)}) mag=${last.impulseMagnitude.toFixed(1)}`,
                );
                if (last.statusEffects.length > 0) {
                    gameConsole.print(`  Effects: ${last.statusEffects.join(', ')}`);
                }
            }
        }
    });

    gameConsole.registerCommand('dummy_clear', () => {
        const count = ctx.getEnemySpawner().getDummies().length;
        ctx.getEnemySpawner().clearDummies();
        gameConsole.print(`Cleared ${count} dummy(s)`);
    });

    gameConsole.registerCommand('dummy_reset', () => {
        const dummies = ctx.getEnemySpawner().getDummies();
        for (const d of dummies) {
            d.reset();
        }
        gameConsole.print(`Reset ${dummies.length} dummy(s)`);
    });

    // Blood effect debug commands
    gameConsole.registerCommand('blood_test', () => {
        const player = ctx.getPlayer();
        if (player) {
            ctx.getBloodEffectSystem().spawnDeathBlood(player.x, player.y);
            gameConsole.print(`Spawned death blood at player (${player.x.toFixed(0)}, ${player.y.toFixed(0)})`);
            gameConsole.print(
                `Active effects: ${ctx.getBloodEffectSystem().getActiveEffectCount()}, pending stamps: ${ctx.getBloodEffectSystem().getPendingStampCount()}`,
            );
        } else {
            gameConsole.print('No player active');
        }
    });

    gameConsole.registerCommand('kill_all', () => {
        if (ctx.getState() !== GameState.Playing) {
            gameConsole.print('Not in game');
            return;
        }
        const enemies = ctx.getEnemySpawner().getActiveEnemies();
        let killed = 0;
        for (const enemy of enemies) {
            if (enemy.isAlive()) {
                // Trigger death effects
                ctx.getEnemyDeathEffects().handleEnemyDeath(enemy, ctx.getScoreSystem());
                enemy.takeDamage(9999, 1, 0, 0, ctx.getPerkSystem(), ctx.getPlayer()!);
                killed++;
            }
        }
        gameConsole.print(`Killed ${killed} enemies`);
    });

    // Weapon unlock registry inspection
    gameConsole.registerCommand('weapon_unlocks', () => {
        const registry = getWeaponUnlockRegistry();
        const ids = registry.getUnlockedWeaponIds();
        gameConsole.print(`Unlocked weapons (${ids.length}):`);
        for (const id of ids) {
            const stats = getWeaponStats(id);
            gameConsole.print(`  ID ${id}: ${stats.name}`);
        }
    });

    // Set initial cvars
    gameConsole.setCvar('con_monoFont', '1');
    gameConsole.setCvar('game_debug', '0');

    // Easter egg: launch AlienZooKeeper minigame directly
    gameConsole.registerCommand('alien_zookeeper', () => {
        const screen = ctx.getAlienZooKeeperScreen();
        screen.show();
        ctx.setState(GameState.AlienZooKeeper);
        gameConsole.print('AlienZooKeeper started!');
    });
}
