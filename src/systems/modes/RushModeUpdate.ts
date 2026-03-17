import { type Player } from '../../entities/Player';
import { type EnemySpawner } from '../enemy/EnemySpawner';
import { AIMode } from '../../entities/Enemy';

export interface RushModeContext {
    player: Player;
    enemySpawner: EnemySpawner;
}

export function updateRushMode(
    ctx: RushModeContext,
    dtMs: number,
    elapsedMs: number,
    terrainW: number,
    terrainH: number,
    numPlayers: number,
    consoleOpen: boolean,
): void {
    const { player, enemySpawner } = ctx;

    // Force shotgun every frame (C: player_state_table.weapon_id = 2, ammo = 30)
    player.weaponId = 2;
    player.ammo = 30;

    // Skip spawning when console is open (C: survival.c line 23)
    if (consoleOpen) {
        return;
    }

    // Cooldown-based spawn loop
    enemySpawner.survivalSpawnCooldown -= numPlayers * dtMs;
    while (enemySpawner.survivalSpawnCooldown < 0) {
        enemySpawner.survivalSpawnCooldown += 250; // Fixed 250ms interval

        // Calculate dynamic tint from elapsed time (C lines 27-56)
        const elapsed = elapsedMs + 1;
        let tintR = elapsed * 8.333333e-6 + 0.3;
        let tintG = elapsed * 10000.0 + 0.3; // saturates to 1.0 almost instantly
        let tintB = Math.sin(elapsed * 0.0001) + 0.3;
        tintR = Math.max(0, Math.min(1, tintR));
        tintG = Math.max(0, Math.min(1, tintG));
        tintB = Math.max(0, Math.min(1, tintB));

        // Spawn from RIGHT edge (C: type=2, ai_mode=8)
        const rx = terrainW + 64;
        const ry = terrainH * 0.5 + Math.cos(elapsedMs * 0.001) * 256;
        const enemy1 = enemySpawner.spawnRushCreature(rx, ry, tintR, tintG, tintB, 2);
        if (enemy1) {
            enemy1.aiMode = AIMode.WIDE_CIRCLE;
        }

        // Spawn from LEFT edge (C: type=3, ai_mode=8, flags |= 0x80, speed *= 1.4)
        const lx = -64;
        const ly = terrainH * 0.5 + Math.sin(elapsedMs * 0.001) * 256;
        const enemy2 = enemySpawner.spawnRushCreature(lx, ly, tintR, tintG, tintB, 3);
        if (enemy2) {
            enemy2.aiMode = AIMode.WIDE_CIRCLE;
            enemy2.creatureFlags |= 0x80;
            enemy2.speed *= 1.4;
            enemy2.maxSpeed = enemy2.speed;
        }
    }
}
