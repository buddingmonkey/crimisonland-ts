import type { GrimInterface, TextureHandle } from '../../engine/GrimInterface';
import { AssetManager } from '../../data/AssetManager';
import { UIElement } from '../UIElement';

/**
 * Option item types
 */
export enum OptionType {
    Slider,
    Toggle,
    Button,
}

/**
 * Individual option menu item (slider, toggle, or button)
 * Uses UIElement pattern like MainMenu for consistent rendering
 */
export class OptionItem {
    // Static slider textures (shared across all instances)
    private static rectOnTexture: TextureHandle = -1;
    private static rectOffTexture: TextureHandle = -1;
    private static checkOnTexture: TextureHandle = -1;
    private static checkOffTexture: TextureHandle = -1;
    private static sliderTexturesLoaded: boolean = false;

    // UI Elements for rendering
    public buttonElement: UIElement;
    private labelTexture: TextureHandle = -1;

    // Position and dimensions
    public x: number = 0;
    public y: number = 0;
    public width: number = 300;
    public height: number = 40;

    // Option state
    public value: number = 0;
    public type: OptionType;
    public label: string;
    public labelIndex: number;

    // Label dimensions (from sprite sheet)
    private readonly LABEL_WIDTH = 200;
    private readonly LABEL_HEIGHT = 30;
    private readonly LABEL_OFFSET_X = 50;
    private readonly LABEL_OFFSET_Y = 5;

    constructor(type: OptionType, label: string, labelIndex: number, initialValue: number) {
        this.type = type;
        this.label = label;
        this.labelIndex = labelIndex;
        this.value = initialValue;

        // Create button element with same dimensions as MainMenu items
        this.buttonElement = new UIElement(512.0, 64.0, -72.0, -60.0);
    }

    /**
     * Load textures for this option item
     */
    async loadAssets(assetManager: AssetManager, grim: GrimInterface): Promise<void> {
        // Load button background texture
        const btnTex = await assetManager.getTexture('ui/ui_menuitem.jaz');
        if (btnTex) {
            const buttonHandle = grim.registerTexture(`option_button_${this.label}`, btnTex);
            (this.buttonElement as any).textureHandle = buttonHandle;
        } else {
            console.warn(`[OptionItem] ${this.label} - Failed to load button texture`);
        }

        // Load label texture
        const lblTex = await assetManager.getTexture('ui/ui_itemtexts.jaz');
        if (lblTex) {
            this.labelTexture = grim.registerTexture(`option_label_${this.label}`, lblTex);
        } else {
            console.warn(`[OptionItem] ${this.label} - Failed to load label texture`);
        }

        // Load slider textures (once for all instances)
        if (!OptionItem.sliderTexturesLoaded) {
            const rectOnTex = await assetManager.getTexture('ui/ui_rectOn.jaz');
            if (rectOnTex) {
                OptionItem.rectOnTexture = grim.registerTexture('ui_rectOn', rectOnTex);
            }

            const rectOffTex = await assetManager.getTexture('ui/ui_rectOff.jaz');
            if (rectOffTex) {
                OptionItem.rectOffTexture = grim.registerTexture('ui_rectOff', rectOffTex);
            }

            const checkOnTex = await assetManager.getTexture('ui/ui_checkOn.jaz');
            if (checkOnTex) {
                OptionItem.checkOnTexture = grim.registerTexture('ui_checkOn', checkOnTex);
            }

            const checkOffTex = await assetManager.getTexture('ui/ui_checkOff.jaz');
            if (checkOffTex) {
                OptionItem.checkOffTexture = grim.registerTexture('ui_checkOff', checkOffTex);
            }

            OptionItem.sliderTexturesLoaded = true;
        }
    }

    /**
     * Update animation state
     * Matches C code's ui_element_update logic
     */
    update(dt: number, isSelected: boolean, globalTimeline: number): void {
        // Update button element animation
        this.buttonElement.update(dt, isSelected, globalTimeline);
    }

    /**
     * Render the option item
     */
    render(grim: GrimInterface): void {
        // Draw button background using UIElement
        if (this.buttonElement.isLoaded()) {
            grim.setColor(255, 255, 255, 255);
            this.buttonElement.drawAnimated(grim, this.x, this.y);
        }

        // Draw label with same rotation as button
        if (this.labelTexture >= 0) {
            grim.bindTexture(this.labelTexture);
            grim.setColor(255, 255, 255, 255);

            // Calculate UV coordinates for this label in the sprite sheet
            const row = this.labelIndex;
            const vStart = (row - 1) / 8.0;
            const vEnd = row / 8.0;
            grim.setUV(0, vStart, 1, vEnd);

            // Get rotation from button element
            const rotationAngle = this.buttonElement.getRotation();

            if (rotationAngle !== 0) {
                // Calculate rotation matrix
                const cos = Math.cos(rotationAngle);
                const sin = Math.sin(rotationAngle);

                // Transform label corners around the button's pivot
                const corners = [
                    { x: this.LABEL_OFFSET_X, y: this.LABEL_OFFSET_Y },
                    { x: this.LABEL_OFFSET_X + this.LABEL_WIDTH, y: this.LABEL_OFFSET_Y + this.LABEL_HEIGHT },
                ];

                // Rotate corners
                const rotated = corners.map((corner) => ({
                    x: this.x + (corner.x * cos - corner.y * sin),
                    y: this.y + (corner.x * sin + corner.y * cos),
                }));

                // Calculate center of rotated label
                const avgX = (rotated[0].x + rotated[1].x) / 2;
                const avgY = (rotated[0].y + rotated[1].y) / 2;

                // Draw at center with rotation
                grim.setRotation(rotationAngle);
                grim.drawQuad(
                    avgX - this.LABEL_WIDTH / 2,
                    avgY - this.LABEL_HEIGHT / 2,
                    this.LABEL_WIDTH,
                    this.LABEL_HEIGHT,
                );
                grim.setRotation(0);
            } else {
                // No rotation - simple draw
                const labelX = this.x + this.LABEL_OFFSET_X;
                const labelY = this.y + this.LABEL_OFFSET_Y;

                grim.drawQuad(labelX, labelY, this.LABEL_WIDTH, this.LABEL_HEIGHT);
            }
        } else {
            console.warn(`[OptionItem] ${this.label} - Label texture not loaded (handle: ${this.labelTexture})`);
        }

        // Render control-specific elements (slider handle, checkbox, etc.)
        this.renderControl(grim);
    }

    /**
     * Render control-specific UI (slider, toggle, etc.)
     * Matches C code at lines 35094-35130 in crimsonland.exe_decompiled.c
     */
    private renderControl(grim: GrimInterface): void {
        if (this.type === OptionType.Slider) {
            this.renderSlider(grim);
        } else if (this.type === OptionType.Toggle) {
            // Render checkbox using ui_checkOff.jaz / ui_checkOn.jaz
            this.renderCheckbox(grim);
        }
        // Buttons don't need additional rendering
    }

    /**
     * Render slider bar (matches C code FUN_0043d9b0)
     * Two-pass rendering:
     * 1. Draw all segments with rectOff at 50% opacity (background)
     * 2. Draw filled segments with rectOn at 100% opacity (foreground)
     */
    private renderSlider(grim: GrimInterface): void {
        if (OptionItem.rectOnTexture === -1 || OptionItem.rectOffTexture === -1) {
            return; // Textures not loaded yet
        }

        // Slider configuration
        const SEGMENT_WIDTH = 8;
        const SEGMENT_HEIGHT = 16;
        const NUM_SEGMENTS = 10; // 10 segments for 0-100 range
        const SLIDER_OFFSET_X = 260; // Position to the right of the label
        const SLIDER_OFFSET_Y = 12; // Vertically centered within the button

        // Calculate filled segments based on value (0-100)
        const filledSegments = Math.floor((this.value / 100) * NUM_SEGMENTS);

        const sliderX = this.x + SLIDER_OFFSET_X;
        const sliderY = this.y + SLIDER_OFFSET_Y;

        // Pass 1: Draw all segments with rectOff at 50% opacity (C lines 35100-35112)
        grim.bindTexture(OptionItem.rectOffTexture);
        grim.setColor(255, 255, 255, 128); // 50% opacity (0.5 * 255 = 128)
        grim.setUV(0, 0, 1, 1);

        for (let i = 0; i < NUM_SEGMENTS; i++) {
            const segmentX = sliderX + i * SEGMENT_WIDTH;
            grim.drawQuad(segmentX, sliderY, SEGMENT_WIDTH, SEGMENT_HEIGHT);
        }

        // Pass 2: Draw filled segments with rectOn at 100% opacity (C lines 35115-35127)
        if (filledSegments > 0) {
            grim.bindTexture(OptionItem.rectOnTexture);
            grim.setColor(255, 255, 255, 255); // 100% opacity
            grim.setUV(0, 0, 1, 1);

            for (let i = 0; i < filledSegments; i++) {
                const segmentX = sliderX + i * SEGMENT_WIDTH;
                grim.drawQuad(segmentX, sliderY, SEGMENT_WIDTH, SEGMENT_HEIGHT);
            }
        }

        // Reset color to full white
        grim.setColor(255, 255, 255, 255);
    }

    /**
     * Render checkbox for toggle options (C: ui_checkOn.jaz / ui_checkOff.jaz)
     */
    private renderCheckbox(grim: GrimInterface): void {
        const checkTex = this.value !== 0 ? OptionItem.checkOnTexture : OptionItem.checkOffTexture;
        if (checkTex === -1) return;

        const CHECK_SIZE = 24;
        const CHECK_OFFSET_X = 280;
        const CHECK_OFFSET_Y = 8;

        grim.bindTexture(checkTex);
        grim.setColor(255, 255, 255, 255);
        grim.setUV(0, 0, 1, 1);
        grim.drawQuad(this.x + CHECK_OFFSET_X, this.y + CHECK_OFFSET_Y, CHECK_SIZE, CHECK_SIZE);
    }

    /**
     * Check if point is inside this option item
     */
    hitTest(x: number, y: number): boolean {
        const bounds = this.buttonElement.getRotatedBounds(this.x, this.y);
        return x >= bounds.left && x <= bounds.right && y >= bounds.top && y <= bounds.bottom;
    }

    /**
     * Adjust value (for sliders and toggles)
     */
    adjustValue(delta: number): void {
        if (this.type === OptionType.Slider) {
            this.value = Math.max(0, Math.min(100, this.value + delta));
        } else if (this.type === OptionType.Toggle) {
            this.value = this.value === 0 ? 1 : 0;
        }
    }
}
