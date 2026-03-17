/**
 * Fire Guard E2E Tests
 *
 * Verifies that the fire suppression guard prevents the menu/UI click
 * that starts a game from firing a weapon on the first gameplay frame.
 *
 * The guard activates on game start (fireGuardActive = true) and only
 * clears when the mouse button is physically released.
 */

import { describe, it, expect, vi } from 'vitest';
import { WeaponFlags } from '../../data/WeaponTypes';
import { updatePlaying, type GamePlayingContext } from '../../GamePlayingUpdate';

// Mock console
vi.mock('../../console/Console', () => ({
    gameConsole: { log: vi.fn(), print: vi.fn(), getIsOpen: () => false },
}));

// Mock quest system — not active for these tests
vi.mock('../../systems/quest/QuestSystem', () => ({
    questSystem: {
        isActive: () => false,
        getCurrentQuest: () => null,
        getElapsedTimerMs: () => 0,
        getStageMajor: () => 0,
        getStageMinor: () => 0,
        getState: () => 0,
    },
}));

// Mock deep subsystems so we only test fire guard logic, not full gameplay
vi.mock('../../systems/combat/GameplayCollisionUpdate', () => ({
    processCollisionsAndKills: vi.fn(() => ({
        perkPendingCount: 0,
        perkPromptTimer: 0,
        bonusAnimTimer: 0,
        newState: undefined,
        isGameOver: false,
    })),
}));

vi.mock('../../systems/enemy/EnemySystemsUpdate', () => ({
    updateEnemySystems: vi.fn(),
}));

vi.mock('../../systems/modes/SurvivalModeUpdate', () => ({
    updateSurvivalMode: vi.fn(() => ({
        survivalSpawnStage: 0,
        survivalRewardDamageSeen: false,
        survivalRewardFireSeen: false,
        survivalRewardHandoutEnabled: true,
    })),
}));

vi.mock('../../systems/modes/RushModeUpdate', () => ({
    updateRushMode: vi.fn(),
}));

vi.mock('../../systems/modes/TutorialModeUpdate', () => ({
    updateTutorialMode: vi.fn(() => ({
        perkPendingCount: 0,
        shouldReturnToMenu: false,
    })),
}));

/**
 * Build a minimal mock GamePlayingContext for fire guard testing.
 * Only the fields needed by the fire guard logic are fully mocked;
 * others are stubs that satisfy the type checker.
 */
function createMockContext(overrides: Partial<GamePlayingContext> = {}): GamePlayingContext {
    let mouseDown = false;
    let mousePressed = false;
    const mockGrim = {
        getDeltaTime: () => 16,
        getTime: () => 0,
        getMouseX: () => 400,
        getMouseY: () => 300,
        getMouseDeltaX: () => 0,
        getMouseDeltaY: () => 0,
        getWidth: () => 800,
        getHeight: () => 600,
        isMouseButtonDown: (btn: number) => (btn === 0 ? mouseDown : false),
        isMouseButtonPressed: (btn: number) => (btn === 0 ? mousePressed : false),
        isKeyDown: () => false,
        isKeyPressed: () => false,
        getKeyChars: () => [],
        setCameraOffset: vi.fn(),
        setGraphicsLayer: vi.fn(),
        bindTexture: vi.fn(),
        setColor: vi.fn(),
        setUV: vi.fn(),
        drawQuad: vi.fn(),
        drawRectFilled: vi.fn(),
        drawLine: vi.fn(),
        drawText: vi.fn(),
        drawTextSmall: vi.fn(),
        registerTexture: vi.fn(),
        setClearColor: vi.fn(),
        init: vi.fn(),
        beginFrame: vi.fn(),
        endFrame: vi.fn(),
        // Setter to control mouse state in tests
        _setMouseDown: (v: boolean) => {
            mouseDown = v;
        },
        _setMousePressed: (v: boolean) => {
            mousePressed = v;
        },
    };

    const mockPlayer = {
        x: 400,
        y: 300,
        aimX: 400,
        aimY: 300,
        health: 100,
        maxHealth: 100,
        experience: 0,
        weaponId: 0,
        damage: 0,
        damageTaken: 0,
        reflexBoostTimer: 0,
        isAlive: () => true,
        update: vi.fn(),
        updateReload: vi.fn(),
        render: vi.fn(),
        swapWeapon: vi.fn(),
        getWeaponStats: () => ({ name: 'Test', flags: WeaponFlags.AUTOMATIC }),
    };

    const noopSystem = {
        update: vi.fn(),
        render: vi.fn(),
    };

    const mockWeaponSystem = {
        ...noopSystem,
        fireWeapon: vi.fn(),
        updateSpreadRecovery: vi.fn(),
        getActiveProjectiles: () => [],
        removeProjectile: vi.fn(),
    };
    const mockEnemySpawner = {
        ...noopSystem,
        spawningEnabled: false,
        getActiveEnemies: () => [],
        updateDyingEnemies: () => [],
        spawnQuestEnemy: vi.fn(),
    };

    const mockSystems = {
        perkSystem: { hasPerk: () => false, addPerk: vi.fn() },
        weaponSystem: mockWeaponSystem,
        enemySpawner: mockEnemySpawner,
        collisionSystem: { checkCollisions: () => ({ enemyHits: [], playerHits: [], bonusPickups: [] }) },
        scoreSystem: { ...noopSystem, getSurvivalTime: () => 0, getKills: () => 0, addKill: vi.fn(), addScore: vi.fn(), addExperience: vi.fn(), getHighScore: () => 0 },
        bonusSystem: { ...noopSystem, getBonuses: () => [], spawnBonus: vi.fn() },
        particleSystem: noopSystem,
        effectSystem: noopSystem,
        bloodEffectSystem: { ...noopSystem, renderBloodEffects: vi.fn(), addRandomGroundDebris: vi.fn(), queueCorpseStamp: vi.fn(), bakeToTerrain: vi.fn() },
        soundSystem: { ...noopSystem, setReflexBoostedTimer: vi.fn() },
        musicSystem: { ...noopSystem, play: vi.fn() },
        cameraShake: { update: vi.fn(), getOffset: () => ({ x: 0, y: 0 }) },
        tutorialSystem: { isActive: () => false, start: vi.fn() },
        highScoreSystem: { submitScore: vi.fn() },
        saveSystem: { loadGameStatus: () => ({ questUnlockIndex: 0 }) },
        achievementSystem: { checkAchievements: vi.fn() },
        enemyDeathEffects: noopSystem,
    } as any;

    const mockScreens = {
        hud: { ...noopSystem, addBonusSlot: vi.fn() },
        perkSelectionScreen: { show: vi.fn(), hide: vi.fn() },
        gameOverScreen: { show: vi.fn(), hide: vi.fn() },
        questFailedScreen: { show: vi.fn(), hide: vi.fn() },
    } as any;

    return {
        grim: mockGrim as any,
        state: 4, // GameState.Playing
        gameMode: 1, // GameMode.Survival
        player: mockPlayer as any,
        systems: mockSystems,
        screens: mockScreens,
        survivalState: {
            spawnStage: 0,
            rewardDamageSeen: false,
            rewardFireSeen: false,
            rewardHandoutEnabled: true,
            recentDeaths: [],
        } as any,
        terrainState: {
            renderer: { getWidth: () => 1024, getHeight: () => 1024, getPlayableWidth: () => 1024, getPlayableHeight: () => 1024 },
            textureHandle: -1,
            seed: 0,
            sprite: null,
        } as any,
        gameplayCursor: noopSystem as any,
        screenFade: {
            update: vi.fn(),
            fadeIn: vi.fn(),
            fadeOut: vi.fn(),
            isActive: () => false,
            setAlpha: vi.fn(),
        } as any,
        fireGuardActive: true,
        cameraOffsetX: 512,
        cameraOffsetY: 512,
        perkPendingCount: 0,
        perkPromptTimer: 0,
        shockChainProjectileId: -1,
        shockChainLinksLeft: 0,
        bonusAnimTimer: 0,
        perkJustSelected: false,
        tutorialKillCount: 0,
        questFailRetryCount: 0,
        handleQuestCompletion: vi.fn(),
        handleChainLightning: vi.fn(),
        applyBonusEffect: vi.fn(),
        ...overrides,
    };
}

// =============================================================================
// FIRE GUARD TESTS
// =============================================================================

describe('Fire Guard — prevents menu click from firing weapon', () => {
    it('should suppress fire when guard is active and mouse is held', () => {
        const ctx = createMockContext();
        (ctx.grim as any)._setMouseDown(true); // Mouse still held from UI click
        ctx.fireGuardActive = true;

        updatePlaying(ctx, 0.016);

        // Guard should still be active (mouse not released)
        expect(ctx.fireGuardActive).toBe(true);
        // Weapon should NOT have fired
        expect(ctx.systems.weaponSystem.fireWeapon).not.toHaveBeenCalled();
    });

    it('should clear guard when mouse is released', () => {
        const ctx = createMockContext();
        (ctx.grim as any)._setMouseDown(false); // Mouse released
        ctx.fireGuardActive = true;

        updatePlaying(ctx, 0.016);

        // Guard should be cleared
        expect(ctx.fireGuardActive).toBe(false);
    });

    it('should allow firing after guard is cleared', () => {
        const ctx = createMockContext();

        // Frame 1: mouse released → guard clears, but no fire (mouse not down)
        (ctx.grim as any)._setMouseDown(false);
        ctx.fireGuardActive = true;
        updatePlaying(ctx, 0.016);
        expect(ctx.fireGuardActive).toBe(false);
        expect(ctx.systems.weaponSystem.fireWeapon).not.toHaveBeenCalled();

        // Frame 2: mouse pressed → should fire now
        (ctx.grim as any)._setMouseDown(true);
        updatePlaying(ctx, 0.016);
        expect(ctx.systems.weaponSystem.fireWeapon).toHaveBeenCalled();
    });

    it('should suppress fire for many frames while mouse is held', () => {
        const ctx = createMockContext();
        (ctx.grim as any)._setMouseDown(true);
        ctx.fireGuardActive = true;

        // Simulate 10 frames with mouse held — fire should never happen
        for (let i = 0; i < 10; i++) {
            updatePlaying(ctx, 0.016);
            expect(ctx.fireGuardActive).toBe(true);
            expect(ctx.systems.weaponSystem.fireWeapon).not.toHaveBeenCalled();
        }

        // Release mouse — guard clears
        (ctx.grim as any)._setMouseDown(false);
        updatePlaying(ctx, 0.016);
        expect(ctx.fireGuardActive).toBe(false);
    });

    it('should fire normally when guard is not active', () => {
        const ctx = createMockContext();
        (ctx.grim as any)._setMouseDown(true);
        ctx.fireGuardActive = false; // Guard NOT active

        updatePlaying(ctx, 0.016);

        // Should fire
        expect(ctx.systems.weaponSystem.fireWeapon).toHaveBeenCalled();
    });

    it('should handle guard deactivation and immediate fire in same frame when mouse is not down', () => {
        // Edge case: guard active but mouse already released before the frame
        const ctx = createMockContext();
        (ctx.grim as any)._setMouseDown(false);
        ctx.fireGuardActive = true;

        updatePlaying(ctx, 0.016);

        // Guard should clear and weapon should NOT fire (mouse is not down)
        expect(ctx.fireGuardActive).toBe(false);
        expect(ctx.systems.weaponSystem.fireWeapon).not.toHaveBeenCalled();
    });
});
