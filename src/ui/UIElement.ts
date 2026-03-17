/**
 * UIElement - Generic UI element matching C code's ui_element_t pattern
 *
 * Pairs a texture with display dimensions and pivot offset.
 * Display dimensions can differ from texture size (for stretching).
 *
 * Based on C code's ui_element_load() + ui_element_set_rect() pattern:
 * - ui_element_load: loads JAZ texture
 * - ui_element_set_rect: sets width, height, and pivot offset
 */

import type { GrimInterface, TextureHandle } from '../engine/GrimInterface';
import type { AssetManager } from '../data/AssetManager';

export class UIElement {
    private textureHandle: TextureHandle = -1;

    // Animation state (from C code ui_element_t)
    private counterValue: number = 0; // Hover animation (0-1000)
    private rotationAngle: number = Math.PI / 2; // Start rotated 90° (off-screen) until animation runs

    // Per-element timeline (from C code _pad0[0x12] and _pad0[0xe])
    public startTime: number = 0; // When animation starts (ms)
    public endTime: number = 0; // When animation ends (ms)

    // Rotation matrix (from C code rot_m00, rot_m01, rot_m10, rot_m11 @ line 38286-38291)
    private rotationMatrix: { m00: number; m01: number; m10: number; m11: number } = {
        m00: 1,
        m01: 0,
        m10: 0,
        m11: 1, // Identity matrix (no rotation)
    };

    /**
     * Create a UI element with display dimensions and pivot offset.
     *
     * @param width - Display width (may differ from texture width)
     * @param height - Display height (may differ from texture height)
     * @param offsetX - Pivot offset X (added to position when drawing)
     * @param offsetY - Pivot offset Y (added to position when drawing)
     */
    constructor(
        public readonly width: number,
        public readonly height: number,
        public readonly offsetX: number,
        public readonly offsetY: number,
    ) {}

    /**
     * Load the texture for this element.
     */
    async load(name: string, path: string, assetManager: AssetManager, grim: GrimInterface): Promise<void> {
        const texture = await assetManager.getTexture(path);
        if (texture) {
            this.textureHandle = grim.registerTexture(name, texture);
        }
    }

    /**
     * Check if the texture has been loaded.
     */
    isLoaded(): boolean {
        return this.textureHandle >= 0;
    }

    /**
     * Get the texture handle for advanced usage.
     */
    getHandle(): TextureHandle {
        return this.textureHandle;
    }

    /**
     * Update animation state (from C code ui_element_update @ line 38203-38291)
     *
     * @param dt - Delta time in milliseconds
     * @param hovered - Whether element is currently hovered
     * @param globalTimeline - Global timeline position in milliseconds
     */
    update(dt: number, hovered: boolean, globalTimeline: number): void {
        // Hover animation: counter_value increases/decreases based on hover state
        // From C code @ line 38206-38209
        if (hovered) {
            this.counterValue += dt * 6;
        } else {
            this.counterValue += dt * -2;
        }

        // Clamp to [0, 1000] (from C code @ line 38211-38216)
        if (this.counterValue < 0) {
            this.counterValue = 0;
        }
        if (this.counterValue > 1000) {
            this.counterValue = 1000;
        }

        // Calculate rotation based on timeline position (from C code @ line 38222-38259)
        if (globalTimeline < this.endTime) {
            if (globalTimeline < this.startTime) {
                // Before animation starts - set to initial rotation (90°)
                this.rotationAngle = Math.PI / 2; // 1.5707964
            } else {
                // During animation - interpolate from 90° to 0°
                const elapsed = globalTimeline - this.startTime;
                const duration = this.endTime - this.startTime;
                const progress = elapsed / duration;
                // From C code @ line 38247: angle = 1.5707964 - (progress * 1.5707964)
                this.rotationAngle = (Math.PI / 2) * (1.0 - progress);
            }
        } else {
            // Animation complete - rotation is 0
            this.rotationAngle = 0.0;
        }

        // Update rotation matrix (from C code @ line 38286-38291)
        const cos = Math.cos(this.rotationAngle);
        const sin = Math.sin(this.rotationAngle);
        this.rotationMatrix.m00 = cos;
        this.rotationMatrix.m01 = -sin;
        this.rotationMatrix.m10 = sin;
        this.rotationMatrix.m11 = cos;
    }

    /**
     * Set rotation angle for hinge animation
     */
    setRotation(angle: number): void {
        this.rotationAngle = angle;
    }

    /**
     * Get normalized counter value (0.0 to 1.0)
     */
    getCounterNormalized(): number {
        return this.counterValue / 1000;
    }

    /**
     * Get current rotation angle
     */
    getRotation(): number {
        return this.rotationAngle;
    }

    /**
     * Get the bounding box of the element after rotation
     * Returns the axis-aligned bounding box that contains the rotated quad
     */
    getRotatedBounds(x: number, y: number): { left: number; right: number; top: number; bottom: number } {
        if (this.rotationAngle === 0) {
            // No rotation - simple bounds
            return {
                left: x + this.offsetX,
                right: x + this.offsetX + this.width,
                top: y + this.offsetY,
                bottom: y + this.offsetY + this.height,
            };
        }

        // Calculate rotated corners
        const pivotX = x + this.offsetX;
        const pivotY = y + this.offsetY;
        const [m00, m01, m10, m11] = this.getRotationMatrix();

        const corners = [
            { x: 0, y: 0 }, // Top-left (pivot)
            { x: this.width, y: 0 }, // Top-right
            { x: this.width, y: this.height }, // Bottom-right
            { x: 0, y: this.height }, // Bottom-left
        ];

        const rotated = corners.map((corner) => ({
            x: pivotX + corner.x * m00 + corner.y * m01,
            y: pivotY + corner.x * m10 + corner.y * m11,
        }));

        // Find axis-aligned bounding box
        const xs = rotated.map((p) => p.x);
        const ys = rotated.map((p) => p.y);

        return {
            left: Math.min(...xs),
            right: Math.max(...xs),
            top: Math.min(...ys),
            bottom: Math.max(...ys),
        };
    }

    /**
     * Get 2D rotation matrix (from C code @ line 38286-38291)
     * Returns [m00, m01, m10, m11] for 2D rotation
     * Matrix is updated in update() method
     */
    private getRotationMatrix(): [number, number, number, number] {
        return [this.rotationMatrix.m00, this.rotationMatrix.m01, this.rotationMatrix.m10, this.rotationMatrix.m11];
    }

    /**
     * Draw at position (x, y), applying pivot offset.
     * The element is drawn at (x + offsetX, y + offsetY) with the specified dimensions.
     */
    draw(grim: GrimInterface, x: number, y: number): void {
        if (this.textureHandle < 0) return;

        grim.bindTexture(this.textureHandle);
        grim.setUV(0, 0, 1, 1);
        grim.drawQuad(x + this.offsetX, y + this.offsetY, this.width, this.height);
    }

    /**
     * Draw with rotation applied (hinge effect)
     * Rotates around the left edge (pivot point)
     */
    drawAnimated(grim: GrimInterface, x: number, y: number): void {
        if (this.textureHandle < 0) {
            console.warn('[UIElement.drawAnimated] textureHandle is negative, returning early');
            return;
        }

        grim.bindTexture(this.textureHandle);
        grim.setUV(0, 0, 1, 1);

        // If no rotation, use simple draw
        if (this.rotationAngle === 0) {
            grim.drawQuad(x + this.offsetX, y + this.offsetY, this.width, this.height);
            return;
        }

        // Apply rotation around left edge (hinge point)
        // Draw at offset position with rotation
        // This is close enough - perfect alignment would require complex pivot math
        grim.setRotation(this.rotationAngle);
        grim.drawQuad(x + this.offsetX, y + this.offsetY, this.width, this.height);
        grim.setRotation(0);
    }

    /**
     * Draw with custom UV coordinates (for sprite sheets).
     */
    drawWithUV(grim: GrimInterface, x: number, y: number, u0: number, v0: number, u1: number, v1: number): void {
        if (this.textureHandle < 0) return;

        grim.bindTexture(this.textureHandle);
        grim.setUV(u0, v0, u1, v1);
        grim.drawQuad(x + this.offsetX, y + this.offsetY, this.width, this.height);
    }
}
