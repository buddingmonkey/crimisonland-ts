/**
 * Analytics.ts – Centralized GA4 event tracking module.
 *
 * Zero dependencies on the game codebase. Every call is a safe no-op when
 * the gtag.js script tag is absent (e.g. local dev / tests).
 */

/* ── Global type augmentation ── */
declare global {
    interface Window {
        gtag: (...args: any[]) => void;
        dataLayer: any[];
    }
}

/* ── Private helper ── */

function track(eventName: string, params?: Record<string, any>): void {
    if (typeof window !== 'undefined' && typeof window.gtag === 'function') {
        window.gtag('event', eventName, params);
    }
}

/* ── Exported tracking functions ── */

// Asset loading
export function trackAssetUploadStart(): void {
    track('asset_upload_start');
}

export function trackAssetUploadComplete(source: 'upload' | 'cached'): void {
    track('asset_upload_complete', { source });
}

// Menu
export function trackMenuNavigate(destination: string): void {
    track('menu_navigate', { destination });
}

// Game session
export function trackGameStart(mode: string, questId?: string): void {
    track('game_start', { mode, quest_id: questId });
}

// Quest mode
export function trackQuestStart(tier: number, index: number, questName: string, isRetry: boolean): void {
    track('quest_start', { tier, index, quest_name: questName, is_retry: isRetry });
}

export function trackQuestComplete(
    tier: number,
    index: number,
    questName: string,
    timeMs: number,
    finalScoreMs: number,
    kills: number,
): void {
    track('quest_complete', {
        tier,
        index,
        quest_name: questName,
        time_ms: timeMs,
        final_score_ms: finalScoreMs,
        kills,
    });
}

export function trackQuestFail(
    tier: number,
    index: number,
    questName: string,
    timeMs: number,
    kills: number,
): void {
    track('quest_fail', {
        tier,
        index,
        quest_name: questName,
        time_ms: timeMs,
        kills,
    });
}

export function trackQuestAction(action: string, tier: number, index: number): void {
    track('quest_action', { action, tier, index });
}

// Survival / Rush
export function trackSurvivalEnd(mode: string, elapsedMs: number, kills: number, score: number): void {
    track('survival_end', { mode, elapsed_ms: elapsedMs, kills, score });
}

export function trackSurvivalAction(action: string): void {
    track('survival_action', { action });
}

// Perks & leveling
export function trackPerkSelected(perkId: number, perkName: string, playerLevel: number): void {
    track('perk_selected', { perk_id: perkId, perk_name: perkName, player_level: playerLevel });
}

export function trackLevelUp(newLevel: number, mode: string): void {
    track('level_up', { new_level: newLevel, mode });
}

// Pause / resume
export function trackGamePause(): void {
    track('game_pause');
}

export function trackGameResume(): void {
    track('game_resume');
}

// Pickups
export function trackWeaponPickup(weaponName: string, weaponId: number): void {
    track('weapon_pickup', { weapon_name: weaponName, weapon_id: weaponId });
}

export function trackBonusPickup(bonusType: string): void {
    track('bonus_pickup', { bonus_type: bonusType });
}
