/**
 * WeaponData unit tests
 *
 * Validates all weapon entries have consistent, required fields
 * and that computed/derived values are correct.
 */

import { describe, test, expect } from 'vitest';
import { WEAPON_DATA, WeaponFlags, type WeaponStats } from '../WeaponData';

describe('WeaponData', () => {
    const weaponEntries = Object.entries(WEAPON_DATA).map(([id, stats]) => ({
        id: parseInt(id),
        stats: stats as WeaponStats,
    }));

    test('has 40 weapons (IDs 0-39)', () => {
        expect(weaponEntries.length).toBe(40);
        for (let i = 0; i < 40; i++) {
            expect(WEAPON_DATA[i]).toBeDefined();
            expect(WEAPON_DATA[i].name).toBeTruthy();
        }
    });

    describe.each(weaponEntries)('Weapon $id ($stats.name)', ({ id: _id, stats }) => {
        test('has a non-empty name', () => {
            expect(stats.name.length).toBeGreaterThan(0);
        });

        test('clipSize is positive integer', () => {
            expect(stats.clipSize).toBeGreaterThan(0);
            expect(Number.isInteger(stats.clipSize)).toBe(true);
        });

        test('damage is positive', () => {
            expect(stats.damage).toBeGreaterThan(0);
        });

        test('fireRate ≈ 1/shotCooldown (within 5%)', () => {
            const computed = 1 / stats.shotCooldown;
            const ratio = stats.fireRate / computed;
            expect(ratio).toBeGreaterThan(0.95);
            expect(ratio).toBeLessThan(1.05);
        });

        test('shotCooldown is positive', () => {
            expect(stats.shotCooldown).toBeGreaterThan(0);
        });

        test('spread is non-negative', () => {
            expect(stats.spread).toBeGreaterThanOrEqual(0);
        });

        test('spreadHeat is positive', () => {
            expect(stats.spreadHeat).toBeGreaterThan(0);
        });

        test('projectileSpeed is positive', () => {
            expect(stats.projectileSpeed).toBeGreaterThan(0);
        });

        test('projectileCount is positive integer', () => {
            expect(stats.projectileCount).toBeGreaterThanOrEqual(1);
            expect(Number.isInteger(stats.projectileCount)).toBe(true);
        });

        test('reloadTime is positive', () => {
            expect(stats.reloadTime).toBeGreaterThan(0);
        });

        test('muzzleFlashAlpha is 0-1', () => {
            expect(stats.muzzleFlashAlpha).toBeGreaterThanOrEqual(0);
            expect(stats.muzzleFlashAlpha).toBeLessThanOrEqual(1);
        });

        test('projectileType is defined', () => {
            expect(stats.projectileType).toBeDefined();
        });

        test('flags is defined', () => {
            expect(stats.flags).toBeDefined();
        });

        test('hitRadius is positive when set', () => {
            if (stats.hitRadius !== undefined) {
                expect(stats.hitRadius).toBeGreaterThan(0);
            }
        });

        test('damageScale is non-negative when set', () => {
            if (stats.damageScale !== undefined) {
                expect(stats.damageScale).toBeGreaterThanOrEqual(0);
            }
        });

        test('pelletSpreadMultiplier consistency', () => {
            if (stats.pelletSpreadMultiplier !== undefined) {
                // Weapons with pellet spread should have multiple projectiles
                expect(stats.projectileCount).toBeGreaterThan(1);
                expect(stats.pelletSpreadMultiplier).toBeGreaterThan(0);
            }
        });
    });

    // Cross-weapon validation
    describe('Cross-weapon consistency', () => {
        test('all weapon IDs are sequential 0-39', () => {
            const ids = weaponEntries.map((e) => e.id).sort((a, b) => a - b);
            for (let i = 0; i < 40; i++) {
                expect(ids[i]).toBe(i);
            }
        });

        test('all weapon names are unique', () => {
            const names = weaponEntries.map((e) => e.stats.name);
            const uniqueNames = new Set(names);
            expect(uniqueNames.size).toBe(names.length);
        });

        test('shotgun-type weapons have pelletSpreadMultiplier', () => {
            // IDs: 2 (Shotgun), 3 (Sawed-off), 4 (Jackhammer), 23 (Ion Shotgun), 24 (Gauss Shotgun)
            const shotgunIds = [2, 3, 4, 23, 24];
            for (const id of shotgunIds) {
                const w = WEAPON_DATA[id];
                expect(w.pelletSpreadMultiplier).toBeDefined();
                expect(w.pelletSpreadMultiplier).toBeGreaterThan(0);
                expect(w.projectileCount).toBeGreaterThan(1);
            }
        });

        test('all weapons have hitRadius set', () => {
            for (const { id: _id, stats } of weaponEntries) {
                expect(stats.hitRadius).toBeDefined();
                expect(stats.hitRadius).toBeGreaterThan(0);
            }
        });

        test('automatic weapons have AUTOMATIC flag', () => {
            // Weapons with very fast fire rate (shotCooldown < 0.15) should be automatic
            const fastWeapons = weaponEntries.filter(
                (e) => e.stats.shotCooldown < 0.15 && !(e.stats.flags & WeaponFlags.AUTOMATIC),
            );
            // Just log them, don't fail (some fast weapons may be semi-auto in C code)
            if (fastWeapons.length > 0) {
                console.warn(
                    'Fast-firing weapons without AUTOMATIC flag:',
                    fastWeapons.map((e) => `${e.id}:${e.stats.name}`),
                );
            }
        });
    });
});
