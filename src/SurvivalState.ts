/**
 * SurvivalState - Survival mode state fields extracted from Game.ts.
 *
 * Groups the 5 survival-specific fields (C: survival.c globals)
 * that Game.ts previously declared individually.
 */

export class SurvivalState {
    spawnStage: number = 0;
    rewardDamageSeen: boolean = false;
    rewardFireSeen: boolean = false;
    rewardHandoutEnabled: boolean = true;
    recentDeaths: Array<{ x: number; y: number }> = [];
}
