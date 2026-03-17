import { type Player } from '../../entities/Player';
import { type EnemySpawner } from '../enemy/EnemySpawner';
import { type PerkSystem } from '../PerkSystem';
import { type ScoreSystem } from '../ScoreSystem';
import { gameConsole } from '../../console/Console';

export interface SurvivalModeContext {
    player: Player;
    enemySpawner: EnemySpawner;
    perkSystem: PerkSystem;
    scoreSystem: ScoreSystem;
    survivalSpawnStage: number;
    survivalRewardDamageSeen: boolean;
    survivalRewardFireSeen: boolean;
    survivalRewardHandoutEnabled: boolean;
    survivalRecentDeaths: Array<{ x: number; y: number }>;
    getRandomEdgePosition(edge: number, width: number, height: number, offset: number): { x: number; y: number };
}

export interface SurvivalModeResult {
    survivalSpawnStage: number;
    survivalRewardDamageSeen: boolean;
    survivalRewardFireSeen: boolean;
    survivalRewardHandoutEnabled: boolean;
}

export function updateSurvivalMode(
    ctx: SurvivalModeContext,
    dtMs: number,
    elapsedMs: number,
    terrainW: number,
    terrainH: number,
    numPlayers: number,
): SurvivalModeResult {
    let { survivalSpawnStage, survivalRewardDamageSeen, survivalRewardFireSeen, survivalRewardHandoutEnabled } = ctx;
    const { player, enemySpawner } = ctx;

    // Skip reward weapons, scripted stages, and spawning when console is open
    // C: survival.c line 115 — if (console_open_flag != '\0') return;
    if (gameConsole.getIsOpen()) {
        return { survivalSpawnStage, survivalRewardDamageSeen, survivalRewardFireSeen, survivalRewardHandoutEnabled };
    }

    // ===== Survival Reward Weapons (C: survival.c lines 127-152) =====
    // Gauss Shotgun reward: after 64 seconds, still using pistol
    if (!survivalRewardDamageSeen && !survivalRewardFireSeen && elapsedMs > 64000 && survivalRewardHandoutEnabled) {
        if (player.weaponId === 1) {
            // assault rifle (survival mode starting weapon)
            player.switchWeapon(0x18, ctx.perkSystem); // Gauss Shotgun
        }
        survivalRewardHandoutEnabled = false;
        survivalRewardDamageSeen = true;
        survivalRewardFireSeen = true;
    }

    // Flamethrower reward: 3 recent deaths near player, health < 15
    if (ctx.survivalRecentDeaths.length >= 3 && !survivalRewardFireSeen) {
        const avgX = ctx.survivalRecentDeaths.reduce((s, d) => s + d.x, 0) / 3;
        const avgY = ctx.survivalRecentDeaths.reduce((s, d) => s + d.y, 0) / 3;
        const ddx = player.x - avgX;
        const ddy = player.y - avgY;
        if (Math.sqrt(ddx * ddx + ddy * ddy) < 16 && player.health < 15) {
            player.switchWeapon(0x19, ctx.perkSystem); // Flamethrower
            survivalRewardFireSeen = true;
            survivalRewardHandoutEnabled = false;
        }
    }

    // ===== Survival Scripted Stages (C: survival.c lines 154-283) =====
    const level = player.level;

    if (survivalSpawnStage === 0 && level >= 5) {
        survivalSpawnStage = 1;
        enemySpawner.spawnQuestEnemy(-164, 512, 0x12);
        enemySpawner.spawnQuestEnemy(1188, 512, 0x12);
    }
    if (survivalSpawnStage === 1 && level >= 9) {
        survivalSpawnStage = 2;
        enemySpawner.spawnQuestEnemy(1088, 512, 0x2c);
    }
    if (survivalSpawnStage === 2 && level >= 11) {
        survivalSpawnStage = 3;
        for (let i = 0; i < 12; i++) {
            enemySpawner.spawnQuestEnemy(1088, i * 42.666668 + 256, 0x35);
        }
    }
    if (survivalSpawnStage === 3 && level >= 13) {
        survivalSpawnStage = 4;
        for (let i = 0; i < 4; i++) {
            enemySpawner.spawnQuestEnemy(1088, i * 64 + 384, 0x2b);
        }
    }
    if (survivalSpawnStage === 4 && level >= 15) {
        survivalSpawnStage = 5;
        for (let i = 0; i < 4; i++) {
            enemySpawner.spawnQuestEnemy(1088, i * 64 + 384, 0x38);
        }
        for (let i = 0; i < 4; i++) {
            enemySpawner.spawnQuestEnemy(-64, i * 64 + 384, 0x38);
        }
    }
    if (survivalSpawnStage === 5 && level >= 17) {
        survivalSpawnStage = 6;
        enemySpawner.spawnQuestEnemy(1088, 512, 0x3a);
    }
    if (survivalSpawnStage === 6 && level >= 19) {
        survivalSpawnStage = 7;
        enemySpawner.spawnQuestEnemy(640, 512, 0x01);
    }
    if (survivalSpawnStage === 7 && level >= 21) {
        survivalSpawnStage = 8;
        enemySpawner.spawnQuestEnemy(384, 256, 0x01);
        enemySpawner.spawnQuestEnemy(640, 768, 0x01);
    }
    if (survivalSpawnStage === 8 && level >= 26) {
        survivalSpawnStage = 9;
        for (let i = 0; i < 4; i++) {
            enemySpawner.spawnQuestEnemy(1088, i * 64 + 384, 0x3c);
        }
        for (let i = 0; i < 4; i++) {
            enemySpawner.spawnQuestEnemy(-64, i * 64 + 384, 0x3c);
        }
    }
    if (survivalSpawnStage === 9 && level >= 32) {
        survivalSpawnStage = 10;
        enemySpawner.spawnQuestEnemy(1088, 512, 0x3a);
        enemySpawner.spawnQuestEnemy(-64, 512, 0x3a);
        for (let i = 0; i < 4; i++) {
            enemySpawner.spawnQuestEnemy(i * 64 + 384, -64, 0x3c);
        }
        for (let i = 0; i < 4; i++) {
            enemySpawner.spawnQuestEnemy(i * 64 + 384, 1088, 0x3c);
        }
    }

    // ===== Survival Spawn Loop (C: survival.c lines 284-380) =====
    enemySpawner.survivalSpawnCooldown -= numPlayers * dtMs;

    while (enemySpawner.survivalSpawnCooldown < 0) {
        let interval = 500 - Math.floor(elapsedMs / 1800);

        if (interval < 0) {
            // Batch spawn: ceil(-interval / 2) extra enemies
            const extraSpawns = Math.ceil(-interval / 2);
            interval = Math.max(1, interval + extraSpawns * 2);
            for (let i = 0; i < extraSpawns; i++) {
                const edge = Math.floor(Math.random() * 4);
                const pos = ctx.getRandomEdgePosition(edge, terrainW, terrainH, 40);
                enemySpawner.survivalSpawnCreature(pos.x, pos.y, player.experience);
            }
        }

        if (interval < 1) interval = 1;
        enemySpawner.survivalSpawnCooldown += interval;

        // Always spawn one enemy per tick
        const edge = Math.floor(Math.random() * 4);
        const pos = ctx.getRandomEdgePosition(edge, terrainW, terrainH, 40);
        enemySpawner.survivalSpawnCreature(pos.x, pos.y, player.experience);
    }

    return { survivalSpawnStage, survivalRewardDamageSeen, survivalRewardFireSeen, survivalRewardHandoutEnabled };
}
