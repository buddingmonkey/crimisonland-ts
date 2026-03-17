/**
 * GameSystems - Bundled game system instances extracted from Game.ts.
 *
 * Groups the ~17 system singletons that Game.ts previously declared as
 * individual private fields. Game.ts now owns a single `systems` field.
 */

import { WeaponSystem } from './systems/combat/WeaponSystem';
import { EnemySpawner } from './systems/enemy/EnemySpawner';
import { CollisionSystem } from './systems/combat/CollisionSystem';
import { ScoreSystem } from './systems/ScoreSystem';
import { BonusSystem } from './systems/bonus/BonusSystem';
import { PerkSystem } from './systems/PerkSystem';
import { ParticleSystem } from './systems/effects/ParticleSystem';
import { EffectSystem } from './systems/effects/EffectSystem';
import { BloodEffectSystem } from './systems/effects/BloodEffectSystem';
import { EnemyDeathEffects } from './systems/enemy/EnemyDeathEffects';
import { SoundSystem } from './audio';
import { MusicSystem } from './audio/MusicSystem';
import { CameraShake } from './systems/effects/CameraShake';
import { TutorialSystem } from './systems/modes/TutorialSystem';
import { SaveSystem, getSaveSystem } from './systems/SaveSystem';
import { HighScoreSystem, getHighScoreSystem } from './systems/HighScoreSystem';
import { AchievementSystem, getAchievementSystem } from './systems/AchievementSystem';

export class GameSystems {
    readonly weaponSystem = new WeaponSystem();
    readonly enemySpawner = new EnemySpawner();
    readonly collisionSystem = new CollisionSystem();
    readonly scoreSystem = new ScoreSystem();
    readonly bonusSystem = new BonusSystem();
    readonly perkSystem = new PerkSystem();
    readonly particleSystem = new ParticleSystem();
    readonly effectSystem = new EffectSystem();
    readonly bloodEffectSystem = new BloodEffectSystem();
    readonly enemyDeathEffects = new EnemyDeathEffects();
    readonly soundSystem = new SoundSystem();
    readonly musicSystem = new MusicSystem();
    readonly cameraShake = new CameraShake();
    readonly tutorialSystem = new TutorialSystem();
    readonly saveSystem: SaveSystem = getSaveSystem();
    readonly highScoreSystem: HighScoreSystem = getHighScoreSystem();
    readonly achievementSystem: AchievementSystem = getAchievementSystem();
}
