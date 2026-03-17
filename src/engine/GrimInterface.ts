/**
 * GrimInterface - TypeScript interface mirroring the Grim2D vtable
 *
 * This interface abstracts the rendering, input, and timing functionality
 * that was provided by grim.dll in the original game.
 *
 * Vtable offsets are documented in comments for traceability to decompiled code.
 */

/**
 * Texture handle - opaque identifier for loaded textures
 */
export type TextureHandle = number;

/**
 * Container handle - opaque identifier for PixiJS Containers (scene graph nodes)
 */
export type ContainerHandle = number;

/**
 * Color represented as RGBA values (0-255)
 */
export interface Color {
    r: number;
    g: number;
    b: number;
    a: number;
}

/**
 * 2D point/vector
 */
export interface Vec2 {
    x: number;
    y: number;
}

/**
 * UV coordinates for texture mapping
 */
export interface UVRect {
    u0: number;
    v0: number;
    u1: number;
    v1: number;
}

/**
 * GrimInterface - Core engine abstraction layer
 *
 * Maps to the 84+ method vtable in grim.dll.
 * Implementation will use Pixi.js for rendering.
 */
export interface GrimInterface {
    // ============================================
    // Lifecycle (vtable 0x0 - 0x1C)
    // ============================================

    /** vtable 0x0: Destroy/cleanup interface */
    destroy(): void;

    /** vtable 0x14: Initialize engine, returns success */
    init(): Promise<boolean>;

    /** vtable 0x18: Shutdown engine */
    shutdown(): void;

    // ============================================
    // Timing (vtable 0x34 - 0x40)
    // ============================================

    /** vtable 0x34: Get accumulated time in milliseconds */
    getTime(): number;

    /** vtable 0x38: Set accumulated time */
    setTime(ms: number): void;

    /** vtable 0x3C: Get clamped frame delta time */
    getDeltaTime(): number;

    /** vtable 0x40: Get frames per second */
    getFPS(): number;

    // ============================================
    // Input - Mouse (vtable 0x58 - 0x7C)
    // ============================================

    /** vtable 0x58: Get mouse button state (held) */
    isMouseButtonDown(button: number): boolean;

    /** vtable 0x5C: Get mouse button edge-triggered (just pressed) */
    isMouseButtonPressed(button: number): boolean;

    /** vtable 0x64: Set cached mouse position */
    setMousePosition(x: number, y: number): void;

    /** vtable 0x68: Get cached mouse X position */
    getMouseX(): number;

    /** vtable 0x6C: Get cached mouse Y position */
    getMouseY(): number;

    /** vtable 0x70: Get mouse delta X */
    getMouseDeltaX(): number;

    /** vtable 0x74: Get mouse delta Y */
    getMouseDeltaY(): number;

    // ============================================
    // Input - Keyboard (vtable 0x80)
    // ============================================

    /** vtable 0x80: Routes key/mouse/joystick IDs - check if key is down */
    isKeyDown(key: number): boolean;

    /** Check if key was just pressed this frame */
    isKeyPressed(key: number): boolean;

    /** Get all characters typed this frame (for text input) */
    getKeyChars(): number[];

    // ============================================
    // Input - Flush (vtable 0x4C)
    // ============================================

    /** vtable 0x4C: Clear buffered input/device state */
    flushInput(): void;

    // ============================================
    // Textures (vtable 0xAC - 0xC4)
    // ============================================

    /** vtable 0xAC: Create blank texture in a free slot */
    createTexture(name: string, width: number, height: number): TextureHandle;

    /** vtable 0xB4: Load texture from path */
    loadTexture(name: string, path: string): Promise<TextureHandle>;

    /** vtable 0xB8: Validate texture handle */
    validateTexture(handle: TextureHandle): boolean;

    /** vtable 0xBC: Release texture handle */
    destroyTexture(handle: TextureHandle): void;

    /** vtable 0xC0: Lookup texture handle by name */
    getTextureHandle(name: string): TextureHandle;

    /** vtable 0xC4: Bind texture to stage */
    bindTexture(handle: TextureHandle, stage?: number): void;

    /** Register an external texture and return a handle for it */
    registerTexture(name: string, texture: unknown): TextureHandle;

    /** Get the underlying Pixi renderer (for advanced rendering features) */
    getRenderer(): unknown;

    // ============================================
    // Rendering - Batch (vtable 0xE8 - 0xF0)
    // ============================================

    /** vtable 0xE8: Begin draw batch */
    beginBatch(): void;

    /** vtable 0xEC: Flush batch when vertex buffer fills */
    flushBatch(): void;

    /** vtable 0xF0: End draw batch/flush */
    endBatch(): void;

    // ============================================
    // Rendering - Draw commands (vtable 0xC8 - 0xE4)
    // ============================================

    /** vtable 0xC8: Full-screen quad with current texture */
    drawFullscreenQuad(): void;

    /** vtable 0xCC: Fullscreen color/fade overlay */
    drawFullscreenColor(r: number, g: number, b: number, a: number): void;

    /** vtable 0xD0: UI panel fill/quad */
    drawRectFilled(x: number, y: number, w: number, h: number): void;

    /** vtable 0xD8: Triangle fan circle fill */
    drawCircleFilled(x: number, y: number, radius: number): void;

    /** vtable 0xDC: Triangle strip ring/outline */
    drawCircleOutline(x: number, y: number, radius: number): void;

    /** vtable 0xE0: Line from endpoints with thickness */
    drawLine(x0: number, y0: number, x1: number, y1: number, thickness: number): void;

    /** vtable 0x11C: Draw quad at position with size */
    drawQuad(x: number, y: number, width: number, height: number): void;

    /** vtable 0x120: Draw textured quad with 4 arbitrary corner positions
     *  Used by C code for bullet trails and beam effects.
     *  Corners: (x1,y1)=top-left, (x2,y2)=top-right, (x3,y3)=bottom-right, (x4,y4)=bottom-left
     *  UV coordinates from current setUV/setAtlasFrame are mapped to these corners.
     */
    drawQuadPoints(
        x1: number,
        y1: number,
        x2: number,
        y2: number,
        x3: number,
        y3: number,
        x4: number,
        y4: number,
    ): void;

    // ============================================
    // Rendering - State (vtable 0xFC - 0x118)
    // ============================================

    /** vtable 0xFC: Precompute sin/cos for rotation matrix */
    setRotation(radians: number): void;

    /** vtable 0x100: Set UV coordinates */
    setUV(u0: number, v0: number, u1: number, v1: number): void;

    /** vtable 0x104: Set atlas frame */
    setAtlasFrame(atlasSize: number, frame: number): void;

    /** vtable 0x108: Set sub-rect from grid table */
    setSubRect(atlasSize: number, width: number, height: number, frame: number): void;

    /** vtable 0x110: Set color from RGBA array */
    setColorArray(rgba: [number, number, number, number]): void;

    /** vtable 0x114: Set color from individual components (0-255) */
    setColor(r: number, g: number, b: number, a: number): void;

    /**
     * Set blend mode for subsequent draw calls.
     * Maps to C code: grim_set_config_var(0x14, mode)
     *   'normal' = standard alpha blending (D3DBLEND_INVSRCALPHA)
     *   'add'    = additive blending (D3DBLEND_ONE) - used for glow/particle effects
     */
    setBlendMode(mode: 'normal' | 'add' | 'add-alpha' | 'multiply'): void;

    // ============================================
    // Rendering - Clear (vtable 0x2C)
    // ============================================

    /** vtable 0x2C: Set clear color */
    setClearColor(r: number, g: number, b: number, a: number): void;

    /** Clear the screen */
    clear(): void;

    // ============================================
    // Screen info
    // ============================================

    /** Get backbuffer width */
    getWidth(): number;

    /** Get backbuffer height */
    getHeight(): number;

    // ============================================
    // Text Rendering
    // ============================================

    /** Draw text at position with optional size and color */
    drawText(x: number, y: number, text: string, size?: number, color?: string): void;

    /** Draw small text (size 12) */
    drawTextSmall(x: number, y: number, text: string): void;

    /** Draw large text (size 24) */
    drawTextLarge(x: number, y: number, text: string): void;

    // ============================================
    // Frame management
    // ============================================

    /** Begin a new frame */
    beginFrame(): void;

    /** End frame and present */
    endFrame(): void;

    // ============================================
    // Camera/View Transform
    // ============================================

    /** Switch between graphics layers for proper z-ordering */
    setGraphicsLayer(layer: 'game' | 'ui' | 'console'): void;

    /** Set camera offset for screen shake effects (C lines 6205-6206) */
    setCameraOffset(x: number, y: number): void;

    // ============================================
    // Scene Graph - Containers
    // ============================================

    /** Create a new Container for grouping sprites */
    createContainer(): ContainerHandle;

    /** Destroy a container and remove it from the scene */
    destroyContainer(handle: ContainerHandle): void;

    /** Set container transform (position and rotation) */
    setContainerTransform(handle: ContainerHandle, x: number, y: number, rotation: number): void;

    /** Set the active container - subsequent draw calls add sprites to this container */
    setActiveContainer(handle: ContainerHandle | null): void;

    // ============================================
    // Fullscreen Toggle
    // ============================================

    /** Show the fullscreen toggle button overlay */
    showFullscreenButton(): void;

    /** Hide the fullscreen toggle button overlay */
    hideFullscreenButton(): void;
}
