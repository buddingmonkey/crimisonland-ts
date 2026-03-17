/**
 * GameTypes - Shared enums extracted from Game.ts.
 *
 * All game-state and game-mode constants live here so that other modules
 * can import them without pulling in the entire Game class.
 */

/**
 * Game state enum
 */
export enum GameState {
    Loading,
    Menu,
    Options,
    Statistics, // Shows statistics/leaderboard screens
    Playing,
    Paused,
    GameOver, // C state 7 — Survival/Rush death
    QuestFailed, // C state 12 — Quest mode death
    PerkSelection,
    QuestComplete, // C state 8 — Quest success
    Credits, // Credits screen (C: credits_screen_update)
    AlienZooKeeper, // Secret match-3 minigame (C state 0x1a)
}

/**
 * Game mode enum
 */
export enum GameMode {
    Survival, // mode 1 — Endless survival mode with dynamic spawning
    Rush, // mode 2 — Rush mode: forced shotgun, edge spawns, no level-ups
    Quest, // mode 3 — Quest-driven mode with timeline-based spawns
    Tutorial, // mode 8 — Tutorial mode with guided stages
}
