/**
 * TerrainState - Terrain-related state fields extracted from Game.ts.
 *
 * Groups the terrain renderer, texture handle, seed, and sprite
 * that Game.ts previously declared individually.
 */

import type { TerrainRenderer } from './rendering/TerrainRenderer';
import * as PIXI from 'pixi.js';

export class TerrainState {
    renderer: TerrainRenderer | null = null;
    textureHandle: number = -1;
    seed: number = Date.now();
    /** Sprite for terrain background — uses buffered render texture (no wrapping) */
    sprite: PIXI.Sprite | null = null;
}
