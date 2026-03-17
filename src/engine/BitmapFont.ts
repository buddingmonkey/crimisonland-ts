/**
 * BitmapFont - Bitmap font renderer for Crimsonland's smallWhite font
 *
 * Implements the C code's GRIM_Font2 bitmap font system (grim.dll lines 5736-5792)
 * Each character is rendered from a 16x16 texture atlas with variable glyph widths.
 */

import type { GrimInterface, Color } from './GrimInterface';
import type { AssetManager } from '../data/AssetManager';

/**
 * BitmapFont - Renders text using a texture atlas and glyph width data
 *
 * C code reference: grim_draw_text_small @ grim.dll:5736
 */
export class BitmapFont {
    private textureHandle: number = -1;
    private glyphWidths: Uint8Array = new Uint8Array(256);

    // Font atlas is 16x16 grid (256 characters)
    private readonly ATLAS_SIZE = 16;
    private readonly CHAR_HEIGHT = 16; // Fixed height for all characters
    private readonly UV_STEP = 1.0 / 16.0; // 0.0625

    /**
     * Load font texture and glyph width data from PAQ
     */
    async loadAssets(assetManager: AssetManager, grim: GrimInterface): Promise<void> {
        // Load font texture (C: line 23394 - texture_get_or_load(s_GRIM_Font2, s_load_smallWhite_tga))
        const fontTexture = await assetManager.getTexture('load/smallWhite.tga');
        if (!fontTexture) {
            console.warn('[BitmapFont] Failed to load smallWhite.tga from PAQ');
            return;
        }

        this.textureHandle = grim.registerTexture('GRIM_Font2', fontTexture);

        // Load glyph widths (C: line 2961-2969 - loads from smallFnt.dat)
        const widthData = assetManager.getFile('load/smallFnt.dat');
        if (widthData && widthData.length >= 256) {
            this.glyphWidths.set(widthData.slice(0, 256));
        } else {
            // Fallback: use fixed width if data file not found
            console.warn('[BitmapFont] smallFnt.dat not found, using fixed width');
            this.glyphWidths.fill(this.CHAR_HEIGHT); // Default to 16px width
        }
    }

    /**
     * Draw text at the specified position
     * C code reference: grim_draw_text_small @ grim.dll:5736-5792
     *
     * @param grim - Grim interface for rendering
     * @param text - Text to render
     * @param x - X position
     * @param y - Y position
     * @param color - Optional color override (calls grim.setColor before drawing)
     */
    drawText(grim: GrimInterface, text: string, x: number, y: number, color?: Color): void {
        if (this.textureHandle === -1 || !text) {
            return;
        }

        // Apply color if provided (used by QuestCompleteScreen stat rows)
        if (color) {
            grim.setColor(color.r, color.g, color.b, color.a);
        }

        // Bind font texture (C: line 5757)
        grim.bindTexture(this.textureHandle);

        let currentX = x;

        // Render each character (C: lines 5772-5786)
        for (let i = 0; i < text.length; i++) {
            const charCode = text.charCodeAt(i);

            // Handle newline
            if (charCode === 10) {
                // '\n'
                continue; // Skip newlines for now (menu text is single-line)
            }

            // Get glyph index (C: line 5775 - uses char_map, but it's identity mapping)
            const glyphIndex = charCode;
            if (glyphIndex >= 256) continue;

            // Calculate UV coordinates for this character in the 16x16 atlas
            // C: lines 5778-5782
            const col = glyphIndex % this.ATLAS_SIZE;
            const row = Math.floor(glyphIndex / this.ATLAS_SIZE);

            const u0 = col * this.UV_STEP + 0.001953125; // Small offset to avoid bleeding
            const v0 = row * this.UV_STEP + 0.001953125;
            const glyphWidth = this.glyphWidths[glyphIndex];
            const u1 = u0 + glyphWidth / 256.0 - 0.001953125;
            const v1 = v0 + this.UV_STEP - 0.001953125;

            // Set UV coordinates
            grim.setUV(u0, v0, u1, v1);

            // Draw character quad (C: line 5783)
            grim.drawQuad(currentX, y, glyphWidth, this.CHAR_HEIGHT);

            // Advance to next character position
            currentX += glyphWidth;
        }
    }

    /**
     * Measure the width of a text string
     * C code reference: lines 5717-5718
     */
    measureText(text: string): number {
        let width = 0;
        for (let i = 0; i < text.length; i++) {
            const charCode = text.charCodeAt(i);
            if (charCode === 10) continue; // Skip newlines
            if (charCode >= 256) continue;
            width += this.glyphWidths[charCode];
        }
        return width;
    }

    /**
     * Get the line height for this font
     * C code reference: GRIM_Font2 line height = 16px (grim.dll:5736)
     */
    getLineHeight(): number {
        return this.CHAR_HEIGHT;
    }

    /**
     * Check if font assets are loaded
     */
    isLoaded(): boolean {
        return this.textureHandle !== -1;
    }
}
