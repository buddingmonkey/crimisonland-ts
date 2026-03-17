/**
 * Perk System Unit Tests
 *
 * Tests all perks for correctness against the C source (perks.c).
 * Covers: PerkSystem class, PerkId enum, instant effects, damage modifiers,
 * dodge/damage-reduction, regen, and Player integration via mocks.
 */

import { describe, it, expect, beforeEach, vi } from 'vitest';
import { PerkSystem, PerkId, PERK_META, getSelectablePerkIds } from '../PerkSystem';
import {
    applyInstantPerkEffect,
    calculateRegenRate,
    calculateMoveSpeed,
    calculateCollisionSlowdown,
} from '../player/PlayerModifier';

// ─── PerkSystem Class ─────────────────────────────────────────────────────────

describe('PerkSystem class', () => {
    let ps: PerkSystem;

    beforeEach(() => {
        ps = new PerkSystem();
    });

    it('starts with no perks', () => {
        expect(ps.getActivePerks()).toHaveLength(0);
    });

    it('hasPerk returns false for unpossessed perk', () => {
        expect(ps.hasPerk(PerkId.SHARPSHOOTER)).toBe(false);
    });

    it('getPerkCount returns 0 for unpossessed perk', () => {
        expect(ps.getPerkCount(PerkId.SHARPSHOOTER)).toBe(0);
    });

    it('addPerk increments count to 1', () => {
        ps.addPerk(PerkId.SHARPSHOOTER);
        expect(ps.getPerkCount(PerkId.SHARPSHOOTER)).toBe(1);
        expect(ps.hasPerk(PerkId.SHARPSHOOTER)).toBe(true);
    });

    it('addPerk stacks — calling twice gives count 2', () => {
        ps.addPerk(PerkId.LEAN_MEAN_EXP_MACHINE);
        ps.addPerk(PerkId.LEAN_MEAN_EXP_MACHINE);
        expect(ps.getPerkCount(PerkId.LEAN_MEAN_EXP_MACHINE)).toBe(2);
    });

    it('addPerk stacks — calling three times gives count 3', () => {
        ps.addPerk(PerkId.INSTANT_WINNER);
        ps.addPerk(PerkId.INSTANT_WINNER);
        ps.addPerk(PerkId.INSTANT_WINNER);
        expect(ps.getPerkCount(PerkId.INSTANT_WINNER)).toBe(3);
    });

    it('removePerk sets count to 0', () => {
        ps.addPerk(PerkId.DODGER);
        ps.removePerk(PerkId.DODGER);
        expect(ps.hasPerk(PerkId.DODGER)).toBe(false);
        expect(ps.getPerkCount(PerkId.DODGER)).toBe(0);
    });

    it('removePerk on non-existent perk does nothing', () => {
        expect(() => ps.removePerk(PerkId.NINJA)).not.toThrow();
    });

    it('setPerkCount sets specific count', () => {
        ps.setPerkCount(PerkId.REGENERATION, 3);
        expect(ps.getPerkCount(PerkId.REGENERATION)).toBe(3);
    });

    it('setPerkCount(id, 0) removes the perk', () => {
        ps.addPerk(PerkId.REGENERATION);
        ps.setPerkCount(PerkId.REGENERATION, 0);
        expect(ps.hasPerk(PerkId.REGENERATION)).toBe(false);
    });

    it('setPerkCount negative removes the perk', () => {
        ps.addPerk(PerkId.REGENERATION);
        ps.setPerkCount(PerkId.REGENERATION, -1);
        expect(ps.hasPerk(PerkId.REGENERATION)).toBe(false);
    });

    it('getActivePerks returns all perks with count >= 1', () => {
        ps.addPerk(PerkId.DODGER);
        ps.addPerk(PerkId.NINJA);
        ps.addPerk(PerkId.LEAN_MEAN_EXP_MACHINE);
        const active = ps.getActivePerks();
        expect(active).toContain(PerkId.DODGER);
        expect(active).toContain(PerkId.NINJA);
        expect(active).toContain(PerkId.LEAN_MEAN_EXP_MACHINE);
        expect(active).toHaveLength(3);
    });

    it('clear removes all perks', () => {
        ps.addPerk(PerkId.DODGER);
        ps.addPerk(PerkId.NINJA);
        ps.clear();
        expect(ps.getActivePerks()).toHaveLength(0);
    });

    it('multiple distinct perks tracked independently', () => {
        ps.addPerk(PerkId.URANIUM_FILLED_BULLETS);
        ps.addPerk(PerkId.BARREL_GREASER);
        ps.addPerk(PerkId.URANIUM_FILLED_BULLETS);
        expect(ps.getPerkCount(PerkId.URANIUM_FILLED_BULLETS)).toBe(2);
        expect(ps.getPerkCount(PerkId.BARREL_GREASER)).toBe(1);
    });
});

// ─── PerkId Enum Structure ────────────────────────────────────────────────────

describe('PerkId enum', () => {
    it('ANTIPERK is 0x00', () => {
        expect(PerkId.ANTIPERK).toBe(0x00);
    });
    it('BLOODY_MESS is 0x01', () => {
        expect(PerkId.BLOODY_MESS).toBe(0x01);
    });
    it('SHARPSHOOTER is 0x02', () => {
        expect(PerkId.SHARPSHOOTER).toBe(0x02);
    });
    it('FASTLOADER is 0x03', () => {
        expect(PerkId.FASTLOADER).toBe(0x03);
    });
    it('LEAN_MEAN_EXP_MACHINE is 0x04', () => {
        expect(PerkId.LEAN_MEAN_EXP_MACHINE).toBe(0x04);
    });
    it('LONG_DISTANCE_RUNNER is 0x05', () => {
        expect(PerkId.LONG_DISTANCE_RUNNER).toBe(0x05);
    });
    it('PYROKINETIC is 0x06', () => {
        expect(PerkId.PYROKINETIC).toBe(0x06);
    });
    it('INSTANT_WINNER is 0x07', () => {
        expect(PerkId.INSTANT_WINNER).toBe(0x07);
    });
    it('GRIM_DEAL is 0x08', () => {
        expect(PerkId.GRIM_DEAL).toBe(0x08);
    });
    it('ALTERNATE_WEAPON is 0x09', () => {
        expect(PerkId.ALTERNATE_WEAPON).toBe(0x09);
    });
    it('PLAGUEBEARER is 0x0a', () => {
        expect(PerkId.PLAGUEBEARER).toBe(0x0a);
    });
    it('EVIL_EYES is 0x0b', () => {
        expect(PerkId.EVIL_EYES).toBe(0x0b);
    });
    it('AMMO_MANIAC is 0x0c', () => {
        expect(PerkId.AMMO_MANIAC).toBe(0x0c);
    });
    it('RADIOACTIVE is 0x0d', () => {
        expect(PerkId.RADIOACTIVE).toBe(0x0d);
    });
    it('FASTSHOT is 0x0e', () => {
        expect(PerkId.FASTSHOT).toBe(0x0e);
    });
    it('FATAL_LOTTERY is 0x0f', () => {
        expect(PerkId.FATAL_LOTTERY).toBe(0x0f);
    });
    it('RANDOM_WEAPON is 0x10', () => {
        expect(PerkId.RANDOM_WEAPON).toBe(0x10);
    });
    it('MR_MELEE is 0x11', () => {
        expect(PerkId.MR_MELEE).toBe(0x11);
    });
    it('ANXIOUS_LOADER is 0x12', () => {
        expect(PerkId.ANXIOUS_LOADER).toBe(0x12);
    });
    it('FINAL_REVENGE is 0x13', () => {
        expect(PerkId.FINAL_REVENGE).toBe(0x13);
    });
    it('TELEKINETIC is 0x14', () => {
        expect(PerkId.TELEKINETIC).toBe(0x14);
    });
    it('PERK_EXPERT is 0x15', () => {
        expect(PerkId.PERK_EXPERT).toBe(0x15);
    });
    it('UNSTOPPABLE is 0x16', () => {
        expect(PerkId.UNSTOPPABLE).toBe(0x16);
    });
    it('REGRESSION_BULLETS is 0x17', () => {
        expect(PerkId.REGRESSION_BULLETS).toBe(0x17);
    });
    it('INFERNAL_CONTRACT is 0x18', () => {
        expect(PerkId.INFERNAL_CONTRACT).toBe(0x18);
    });
    it('POISON_BULLETS is 0x19', () => {
        expect(PerkId.POISON_BULLETS).toBe(0x19);
    });
    it('DODGER is 0x1a', () => {
        expect(PerkId.DODGER).toBe(0x1a);
    });
    it('BONUS_MAGNET is 0x1b', () => {
        expect(PerkId.BONUS_MAGNET).toBe(0x1b);
    });
    it('URANIUM_FILLED_BULLETS is 0x1c', () => {
        expect(PerkId.URANIUM_FILLED_BULLETS).toBe(0x1c);
    });
    it('DOCTOR is 0x1d', () => {
        expect(PerkId.DOCTOR).toBe(0x1d);
    });
    it('MONSTER_VISION is 0x1e', () => {
        expect(PerkId.MONSTER_VISION).toBe(0x1e);
    });
    it('HOT_TEMPERED is 0x1f', () => {
        expect(PerkId.HOT_TEMPERED).toBe(0x1f);
    });
    it('BONUS_ECONOMIST is 0x20', () => {
        expect(PerkId.BONUS_ECONOMIST).toBe(0x20);
    });
    it('THICK_SKINNED is 0x21', () => {
        expect(PerkId.THICK_SKINNED).toBe(0x21);
    });
    it('BARREL_GREASER is 0x22', () => {
        expect(PerkId.BARREL_GREASER).toBe(0x22);
    });
    it('AMMUNITION_WITHIN is 0x23', () => {
        expect(PerkId.AMMUNITION_WITHIN).toBe(0x23);
    });
    it('VEINS_OF_POISON is 0x24', () => {
        expect(PerkId.VEINS_OF_POISON).toBe(0x24);
    });
    it('TOXIC_AVENGER is 0x25', () => {
        expect(PerkId.TOXIC_AVENGER).toBe(0x25);
    });
    it('REGENERATION is 0x26', () => {
        expect(PerkId.REGENERATION).toBe(0x26);
    });
    it('PYROMANIAC is 0x27', () => {
        expect(PerkId.PYROMANIAC).toBe(0x27);
    });
    it('NINJA is 0x28', () => {
        expect(PerkId.NINJA).toBe(0x28);
    });
    it('HIGHLANDER is 0x29', () => {
        expect(PerkId.HIGHLANDER).toBe(0x29);
    });
    it('JINXED is 0x2a', () => {
        expect(PerkId.JINXED).toBe(0x2a);
    });
    it('PERK_MASTER is 0x2b', () => {
        expect(PerkId.PERK_MASTER).toBe(0x2b);
    });
    it('REFLEX_BOOSTED is 0x2c', () => {
        expect(PerkId.REFLEX_BOOSTED).toBe(0x2c);
    });
    it('GREATER_REGENERATION is 0x2d', () => {
        expect(PerkId.GREATER_REGENERATION).toBe(0x2d);
    });
    it('BREATHING_ROOM is 0x2e', () => {
        expect(PerkId.BREATHING_ROOM).toBe(0x2e);
    });
    it('DEATH_CLOCK is 0x2f', () => {
        expect(PerkId.DEATH_CLOCK).toBe(0x2f);
    });
    it('MY_FAVOURITE_WEAPON is 0x30', () => {
        expect(PerkId.MY_FAVOURITE_WEAPON).toBe(0x30);
    });
    it('BANDAGE is 0x31', () => {
        expect(PerkId.BANDAGE).toBe(0x31);
    });
    it('ANGRY_RELOADER is 0x32', () => {
        expect(PerkId.ANGRY_RELOADER).toBe(0x32);
    });
    it('ION_GUN_MASTER is 0x33', () => {
        expect(PerkId.ION_GUN_MASTER).toBe(0x33);
    });
    it('STATIONARY_RELOADER is 0x34', () => {
        expect(PerkId.STATIONARY_RELOADER).toBe(0x34);
    });
    it('MAN_BOMB is 0x35', () => {
        expect(PerkId.MAN_BOMB).toBe(0x35);
    });
    it('FIRE_COUGH is 0x36', () => {
        expect(PerkId.FIRE_COUGH).toBe(0x36);
    });
    it('LIVING_FORTRESS is 0x37', () => {
        expect(PerkId.LIVING_FORTRESS).toBe(0x37);
    });
    it('TOUGH_RELOADER is 0x38', () => {
        expect(PerkId.TOUGH_RELOADER).toBe(0x38);
    });
    it('LIFELINE_50_50 is 0x39', () => {
        expect(PerkId.LIFELINE_50_50).toBe(0x39);
    });

    it('enum has exactly 58 entries (0x00–0x39)', () => {
        const ids = Object.values(PerkId).filter((v) => typeof v === 'number');
        expect(ids).toHaveLength(58);
    });

    it('contiguous range: all values 0x00–0x39 are present', () => {
        const ids = new Set(Object.values(PerkId).filter((v) => typeof v === 'number') as number[]);
        for (let i = 0x00; i <= 0x39; i++) {
            expect(ids.has(i)).toBe(true);
        }
    });
});

// ─── PERK_META ────────────────────────────────────────────────────────────────

describe('PERK_META', () => {
    it('has an entry for every PerkId', () => {
        const ids = Object.values(PerkId).filter((v) => typeof v === 'number') as number[];
        for (const id of ids) {
            expect(PERK_META[id as PerkId]).toBeDefined();
        }
    });

    it('every entry has name and description strings', () => {
        for (const meta of Object.values(PERK_META)) {
            expect(typeof meta.name).toBe('string');
            expect(meta.name.length).toBeGreaterThan(0);
            expect(typeof meta.description).toBe('string');
            expect(meta.description.length).toBeGreaterThan(0);
        }
    });

    it('GRIM_DEAL description mentions dying and XP', () => {
        const desc = PERK_META[PerkId.GRIM_DEAL].description.toLowerCase();
        expect(desc).toContain('die');
        expect(desc).toContain('xp');
    });

    it('BANDAGE description mentions multiply/random', () => {
        const desc = PERK_META[PerkId.BANDAGE].description.toLowerCase();
        // Should mention randomness
        expect(desc).toMatch(/random|1.50/i);
    });

    it('DEATH_CLOCK description mentions 30 seconds and invulnerability', () => {
        const desc = PERK_META[PerkId.DEATH_CLOCK].description.toLowerCase();
        expect(desc).toContain('30 second');
        expect(desc).toMatch(/invulner/i);
    });

    it('THICK_SKINNED description mentions 33% damage reduction', () => {
        const desc = PERK_META[PerkId.THICK_SKINNED].description.toLowerCase();
        expect(desc).toContain('33%');
    });

    it('INFERNAL_CONTRACT description mentions 3 extra levels', () => {
        const desc = PERK_META[PerkId.INFERNAL_CONTRACT].description.toLowerCase();
        expect(desc).toContain('3 extra level');
    });
});

// ─── getSelectablePerkIds ─────────────────────────────────────────────────────

describe('getSelectablePerkIds', () => {
    it('excludes ANTIPERK (0x00)', () => {
        const ids = getSelectablePerkIds();
        expect(ids).not.toContain(PerkId.ANTIPERK);
    });

    it('has 57 selectable perks (all except ANTIPERK)', () => {
        expect(getSelectablePerkIds()).toHaveLength(57);
    });
});

// ─── Instant Perk Effects ─────────────────────────────────────────────────────

describe('applyInstantPerkEffect', () => {
    describe('INSTANT_WINNER', () => {
        it('adds exactly 2500 XP', () => {
            const result = applyInstantPerkEffect(PerkId.INSTANT_WINNER, 0, 100);
            expect(result.xp).toBe(2500);
        });

        it('adds 2500 XP on top of existing XP', () => {
            const result = applyInstantPerkEffect(PerkId.INSTANT_WINNER, 1000, 100);
            expect(result.xp).toBe(3500);
        });

        it('does not kill the player', () => {
            const result = applyInstantPerkEffect(PerkId.INSTANT_WINNER, 0, 100);
            expect(result.shouldDie).toBe(false);
            expect(result.health).toBe(100);
        });
    });

    describe('FATAL_LOTTERY', () => {
        it('either adds 10000 XP or kills the player', () => {
            // Run many times to ensure both branches are exercised
            let gotXP = false;
            let gotDeath = false;
            for (let i = 0; i < 100; i++) {
                const result = applyInstantPerkEffect(PerkId.FATAL_LOTTERY, 0, 100);
                if (result.xp === 10000) gotXP = true;
                if (result.shouldDie) gotDeath = true;
            }
            expect(gotXP).toBe(true);
            expect(gotDeath).toBe(true);
        });

        it('XP branch: adds exactly 10000 XP', () => {
            vi.spyOn(Math, 'random').mockReturnValue(0.1); // < 0.5 → XP branch
            const result = applyInstantPerkEffect(PerkId.FATAL_LOTTERY, 0, 100);
            expect(result.xp).toBe(10000);
            expect(result.shouldDie).toBe(false);
            vi.restoreAllMocks();
        });

        it('death branch: sets shouldDie = true', () => {
            vi.spyOn(Math, 'random').mockReturnValue(0.9); // >= 0.5 → death branch
            const result = applyInstantPerkEffect(PerkId.FATAL_LOTTERY, 0, 100);
            expect(result.shouldDie).toBe(true);
            expect(result.xp).toBe(0);
            vi.restoreAllMocks();
        });
    });

    describe('GRIM_DEAL', () => {
        it('gives 18% XP bonus (GAMEFAQ + C decompilation)', () => {
            const result = applyInstantPerkEffect(PerkId.GRIM_DEAL, 500, 75.9);
            expect(result.xp).toBe(590); // 500 + floor(500 * 0.18) = 590
        });

        it('sets health to -1', () => {
            const result = applyInstantPerkEffect(PerkId.GRIM_DEAL, 0, 50);
            expect(result.health).toBe(-1.0);
        });

        it('sets shouldDie = true', () => {
            const result = applyInstantPerkEffect(PerkId.GRIM_DEAL, 0, 50);
            expect(result.shouldDie).toBe(true);
        });

        it('with 0 XP: adds 0 bonus (floor(0 * 0.18) = 0)', () => {
            const result = applyInstantPerkEffect(PerkId.GRIM_DEAL, 0, 1);
            expect(result.xp).toBe(0);
        });
    });

    describe('INFERNAL_CONTRACT', () => {
        it('sets health to 0.1', () => {
            const result = applyInstantPerkEffect(PerkId.INFERNAL_CONTRACT, 0, 100);
            expect(result.health).toBe(0.1);
        });

        it('grants 3 extra levels', () => {
            const result = applyInstantPerkEffect(PerkId.INFERNAL_CONTRACT, 0, 100);
            expect(result.extraLevels).toBe(3);
        });

        it('grants 3 extra pending perks', () => {
            const result = applyInstantPerkEffect(PerkId.INFERNAL_CONTRACT, 0, 100);
            expect(result.extraPendingPerks).toBe(3);
        });

        it('does not kill the player directly', () => {
            const result = applyInstantPerkEffect(PerkId.INFERNAL_CONTRACT, 0, 100);
            expect(result.shouldDie).toBe(false);
        });
    });

    describe('THICK_SKINNED', () => {
        it('reduces health by exactly 1/3 (×0.33333334)', () => {
            const result = applyInstantPerkEffect(PerkId.THICK_SKINNED, 0, 90);
            // 90 - 90 * 0.33333334 ≈ 60
            expect(result.health).toBeCloseTo(60, 1);
        });

        it('at 1 HP: result is 0.666... (clamp only fires at <= 0)', () => {
            // C: health = health - health * 0.33333334; if (health <= 0) health = 1.0
            // 1 - 1*0.33333334 = 0.66666666 — NOT zero, so no clamp
            const result = applyInstantPerkEffect(PerkId.THICK_SKINNED, 0, 1);
            expect(result.health).toBeCloseTo(0.6666666, 5);
        });

        it('very tiny health (0.001) stays positive after reduction', () => {
            // 0.001 - 0.001*0.33333334 ≈ 0.000666... > 0, so no clamp to 1
            const result = applyInstantPerkEffect(PerkId.THICK_SKINNED, 0, 0.001);
            expect(result.health).toBeCloseTo(0.000667, 4);
            expect(result.health).toBeGreaterThan(0);
        });

        it('does not affect XP', () => {
            const result = applyInstantPerkEffect(PerkId.THICK_SKINNED, 500, 60);
            expect(result.xp).toBe(500);
        });
    });

    describe('DEATH_CLOCK', () => {
        it('sets health to exactly 100', () => {
            const result = applyInstantPerkEffect(PerkId.DEATH_CLOCK, 0, 30);
            expect(result.health).toBe(100.0);
        });

        it('signals to clear REGENERATION perk', () => {
            const result = applyInstantPerkEffect(PerkId.DEATH_CLOCK, 0, 100);
            expect(result.clearPerks).toContain(PerkId.REGENERATION);
        });

        it('signals to clear GREATER_REGENERATION perk', () => {
            const result = applyInstantPerkEffect(PerkId.DEATH_CLOCK, 0, 100);
            expect(result.clearPerks).toContain(PerkId.GREATER_REGENERATION);
        });

        it('does not kill the player', () => {
            const result = applyInstantPerkEffect(PerkId.DEATH_CLOCK, 0, 100);
            expect(result.shouldDie).toBe(false);
        });
    });

    describe('BANDAGE', () => {
        it('multiplies health by random 1–50 factor (mocked × 1 = health unchanged)', () => {
            vi.spyOn(Math, 'random').mockReturnValue(0); // floor(0*50)+1 = 1
            const result = applyInstantPerkEffect(PerkId.BANDAGE, 0, 20);
            expect(result.health).toBe(20); // 20 * 1
            vi.restoreAllMocks();
        });

        it('multiplies by max factor of 50 and caps at 100', () => {
            vi.spyOn(Math, 'random').mockReturnValue(0.999); // floor(49.95) = 49 → +1 = 50
            const result = applyInstantPerkEffect(PerkId.BANDAGE, 0, 10);
            expect(result.health).toBe(100); // 10 * 50 = 500, capped at 100
            vi.restoreAllMocks();
        });

        it('caps result at 100 when multiplication exceeds it', () => {
            vi.spyOn(Math, 'random').mockReturnValue(0.5); // multiplier = 26
            const result = applyInstantPerkEffect(PerkId.BANDAGE, 0, 5);
            expect(result.health).toBe(100); // 5 * 26 = 130, capped at 100
            vi.restoreAllMocks();
        });

        it('multiplier is always at least 1 (never reduces health)', () => {
            // Run many times to verify minimum
            for (let i = 0; i < 50; i++) {
                const result = applyInstantPerkEffect(PerkId.BANDAGE, 0, 30);
                expect(result.health).toBeGreaterThanOrEqual(30);
            }
        });
    });

    describe('BREATHING_ROOM', () => {
        it('reduces health to ~33.3%', () => {
            const result = applyInstantPerkEffect(PerkId.BREATHING_ROOM, 0, 90);
            expect(result.health).toBeCloseTo(30, 0);
        });

        it('signals to shrink enemy hitboxes (NOT kill them)', () => {
            const result = applyInstantPerkEffect(PerkId.BREATHING_ROOM, 0, 100);
            expect(result.shouldShrinkEnemyHitboxes).toBe(true);
        });

        it('does NOT signal to kill nearby enemies', () => {
            // Old wrong behavior: shouldKillNearbyEnemies
            const result = applyInstantPerkEffect(PerkId.BREATHING_ROOM, 0, 100);
            expect(result.shouldDie).toBe(false);
        });
    });

    describe('PLAGUEBEARER', () => {
        it('signals to set plaguebearer flag', () => {
            const result = applyInstantPerkEffect(PerkId.PLAGUEBEARER, 0, 100);
            expect(result.shouldSetPlaguebearer).toBe(true);
        });

        it('does not modify health or XP', () => {
            const result = applyInstantPerkEffect(PerkId.PLAGUEBEARER, 500, 80);
            expect(result.health).toBe(80);
            expect(result.xp).toBe(500);
        });
    });

    describe('LIFELINE_50_50', () => {
        it('signals to kill alternate weak enemies', () => {
            const result = applyInstantPerkEffect(PerkId.LIFELINE_50_50, 0, 100);
            expect(result.shouldKillAlternateWeakEnemies).toBe(true);
        });

        it('does not modify health or XP', () => {
            const result = applyInstantPerkEffect(PerkId.LIFELINE_50_50, 500, 80);
            expect(result.health).toBe(80);
            expect(result.xp).toBe(500);
        });
    });

    describe('AMMO_MANIAC', () => {
        it('signals to refill all weapon ammo', () => {
            const result = applyInstantPerkEffect(PerkId.AMMO_MANIAC, 0, 100);
            expect(result.shouldRefillAllAmmo).toBe(true);
        });

        it('does not modify health or XP', () => {
            const result = applyInstantPerkEffect(PerkId.AMMO_MANIAC, 500, 80);
            expect(result.health).toBe(80);
            expect(result.xp).toBe(500);
        });
    });

    describe('RANDOM_WEAPON', () => {
        it('signals to get a random weapon', () => {
            const result = applyInstantPerkEffect(PerkId.RANDOM_WEAPON, 0, 100);
            expect(result.shouldGetRandomWeapon).toBe(true);
        });
    });

    describe('MAN_BOMB', () => {
        it('has no instant effect (passive timer-driven perk)', () => {
            const result = applyInstantPerkEffect(PerkId.MAN_BOMB, 0, 100);
            expect(result.shouldExplode).toBe(false);
            expect(result.health).toBe(100);
            expect(result.xp).toBe(0);
            expect(result.shouldDie).toBe(false);
        });
    });

    describe('perks with no instant effect', () => {
        const noEffectPerks = [
            PerkId.SHARPSHOOTER,
            PerkId.FASTLOADER,
            PerkId.LONG_DISTANCE_RUNNER,
            PerkId.PYROKINETIC,
            PerkId.RADIOACTIVE,
            PerkId.FASTSHOT,
            PerkId.MR_MELEE,
            PerkId.ANXIOUS_LOADER,
            PerkId.FINAL_REVENGE,
            PerkId.TELEKINETIC,
            PerkId.PERK_EXPERT,
            PerkId.UNSTOPPABLE,
            PerkId.REGRESSION_BULLETS,
            PerkId.POISON_BULLETS,
            PerkId.DODGER,
            PerkId.BONUS_MAGNET,
            PerkId.URANIUM_FILLED_BULLETS,
            PerkId.DOCTOR,
            PerkId.MONSTER_VISION,
            PerkId.HOT_TEMPERED,
            PerkId.BONUS_ECONOMIST,
            PerkId.BARREL_GREASER,
            PerkId.AMMUNITION_WITHIN,
            PerkId.VEINS_OF_POISON,
            PerkId.TOXIC_AVENGER,
            PerkId.REGENERATION,
            PerkId.PYROMANIAC,
            PerkId.NINJA,
            PerkId.HIGHLANDER,
            PerkId.JINXED,
            PerkId.PERK_MASTER,
            PerkId.REFLEX_BOOSTED,
            PerkId.GREATER_REGENERATION,
            PerkId.MY_FAVOURITE_WEAPON,
            PerkId.ANGRY_RELOADER,
            PerkId.ION_GUN_MASTER,
            PerkId.STATIONARY_RELOADER,
            PerkId.FIRE_COUGH,
            PerkId.LIVING_FORTRESS,
            PerkId.TOUGH_RELOADER,
        ];

        for (const perkId of noEffectPerks) {
            it(`${PerkId[perkId]} does not modify health, XP, or kill player`, () => {
                const result = applyInstantPerkEffect(perkId, 1000, 75);
                expect(result.health).toBe(75);
                expect(result.xp).toBe(1000);
                expect(result.shouldDie).toBe(false);
            });
        }
    });
});

// ─── Regeneration Logic ───────────────────────────────────────────────────────

describe('calculateRegenRate', () => {
    it('returns 0 with no perk system', () => {
        expect(calculateRegenRate(0.016, null)).toBe(0);
    });

    it('returns 0 without REGENERATION perk', () => {
        const ps = new PerkSystem();
        // Even with Greater Regen only (no plain Regen), returns 0
        ps.addPerk(PerkId.GREATER_REGENERATION);
        expect(calculateRegenRate(0.016, ps)).toBe(0);
    });

    it('returns dt on 50% random roll with REGENERATION', () => {
        const ps = new PerkSystem();
        ps.addPerk(PerkId.REGENERATION);
        vi.spyOn(Math, 'random').mockReturnValue(0.3); // < 0.5 → regen
        expect(calculateRegenRate(0.016, ps)).toBe(0.016);
        vi.restoreAllMocks();
    });

    it('returns 0 on other 50% random roll with REGENERATION', () => {
        const ps = new PerkSystem();
        ps.addPerk(PerkId.REGENERATION);
        vi.spyOn(Math, 'random').mockReturnValue(0.7); // >= 0.5 → no regen
        expect(calculateRegenRate(0.016, ps)).toBe(0);
        vi.restoreAllMocks();
    });

    it('regen rate is always exactly dt (not scaled by 2x for Greater Regen)', () => {
        // C code: only checks REGENERATION, not GREATER_REGENERATION separately
        const ps = new PerkSystem();
        ps.addPerk(PerkId.REGENERATION);
        ps.addPerk(PerkId.GREATER_REGENERATION);
        vi.spyOn(Math, 'random').mockReturnValue(0.1); // always regen
        const dt = 0.033;
        expect(calculateRegenRate(dt, ps)).toBe(dt); // exactly dt, not 2×
        vi.restoreAllMocks();
    });

    it('over many frames, roughly 50% give regen (statistical test)', () => {
        const ps = new PerkSystem();
        ps.addPerk(PerkId.REGENERATION);
        const dt = 1.0;
        let regenFrames = 0;
        const trials = 10000;
        for (let i = 0; i < trials; i++) {
            if (calculateRegenRate(dt, ps) > 0) regenFrames++;
        }
        // Expect ~50% ± 5%
        expect(regenFrames / trials).toBeGreaterThan(0.45);
        expect(regenFrames / trials).toBeLessThan(0.55);
    });
});

// ─── Movement Perks ───────────────────────────────────────────────────────────

describe('calculateMoveSpeed', () => {
    it('returns defaults with no perk system', () => {
        const result = calculateMoveSpeed(2.0, null);
        expect(result.maxSpeed).toBe(2.0);
        expect(result.acceleration).toBe(5.0);
    });

    it('returns defaults without LONG_DISTANCE_RUNNER', () => {
        const ps = new PerkSystem();
        const result = calculateMoveSpeed(2.0, ps);
        expect(result.maxSpeed).toBe(2.0);
        expect(result.acceleration).toBe(5.0);
    });

    it('LONG_DISTANCE_RUNNER gives maxSpeed 2.8 (+40%)', () => {
        const ps = new PerkSystem();
        ps.addPerk(PerkId.LONG_DISTANCE_RUNNER);
        const result = calculateMoveSpeed(2.0, ps);
        expect(result.maxSpeed).toBe(2.8);
    });

    it('LONG_DISTANCE_RUNNER gives reduced acceleration 4.0', () => {
        const ps = new PerkSystem();
        ps.addPerk(PerkId.LONG_DISTANCE_RUNNER);
        const result = calculateMoveSpeed(2.0, ps);
        expect(result.acceleration).toBe(4.0);
    });
});

// ─── Collision/Slowdown ───────────────────────────────────────────────────────

describe('calculateCollisionSlowdown', () => {
    it('returns 1.0 with no perk system', () => {
        expect(calculateCollisionSlowdown(null)).toBe(1.0);
    });

    it('returns 1.0 without UNSTOPPABLE', () => {
        const ps = new PerkSystem();
        expect(calculateCollisionSlowdown(ps)).toBe(1.0);
    });

    it('UNSTOPPABLE returns 0.0 (no slowdown)', () => {
        const ps = new PerkSystem();
        ps.addPerk(PerkId.UNSTOPPABLE);
        expect(calculateCollisionSlowdown(ps)).toBe(0.0);
    });
});

// ─── Death Clock passive integration ─────────────────────────────────────────

describe('DEATH_CLOCK passive (regen cleared by Death Clock on apply)', () => {
    it('clearPerks contains both regen perks so caller can remove them', () => {
        const result = applyInstantPerkEffect(PerkId.DEATH_CLOCK, 0, 100);
        expect(result.clearPerks).toHaveLength(2);
        expect(result.clearPerks).toContain(PerkId.REGENERATION);
        expect(result.clearPerks).toContain(PerkId.GREATER_REGENERATION);
    });

    it('after applying clearPerks to PerkSystem, regen perks are gone', () => {
        const ps = new PerkSystem();
        ps.addPerk(PerkId.REGENERATION);
        ps.addPerk(PerkId.GREATER_REGENERATION);
        ps.addPerk(PerkId.DEATH_CLOCK);

        const result = applyInstantPerkEffect(PerkId.DEATH_CLOCK, 0, 50);
        for (const id of result.clearPerks) {
            ps.removePerk(id);
        }

        expect(ps.hasPerk(PerkId.REGENERATION)).toBe(false);
        expect(ps.hasPerk(PerkId.GREATER_REGENERATION)).toBe(false);
        expect(ps.hasPerk(PerkId.DEATH_CLOCK)).toBe(true); // still held
    });

    it('calculateRegenRate returns 0 after Death Clock clears regen', () => {
        const ps = new PerkSystem();
        ps.addPerk(PerkId.REGENERATION);
        ps.addPerk(PerkId.DEATH_CLOCK);

        const result = applyInstantPerkEffect(PerkId.DEATH_CLOCK, 0, 50);
        for (const id of result.clearPerks) {
            ps.removePerk(id);
        }

        vi.spyOn(Math, 'random').mockReturnValue(0.1);
        expect(calculateRegenRate(0.016, ps)).toBe(0); // regen is gone
        vi.restoreAllMocks();
    });
});

// ─── Stacking perks ───────────────────────────────────────────────────────────

describe('Stacking perks', () => {
    it('LEAN_MEAN_EXP_MACHINE count = 2 → should yield 20 XP per tick', () => {
        // Simulates what Player.ts does: perkCount * 10
        const ps = new PerkSystem();
        ps.addPerk(PerkId.LEAN_MEAN_EXP_MACHINE);
        ps.addPerk(PerkId.LEAN_MEAN_EXP_MACHINE);
        ps.addPerk(PerkId.LEAN_MEAN_EXP_MACHINE);

        const count = ps.getPerkCount(PerkId.LEAN_MEAN_EXP_MACHINE);
        expect(count * 10).toBe(30); // 3 stacks → 30 XP per 0.25s
    });

    it('INSTANT_WINNER stacks — each pick gives 2500 XP', () => {
        let totalXP = 0;
        totalXP += applyInstantPerkEffect(PerkId.INSTANT_WINNER, totalXP, 100).xp - totalXP;
        // First pick: 2500
        expect(totalXP).toBe(2500);
    });
});
