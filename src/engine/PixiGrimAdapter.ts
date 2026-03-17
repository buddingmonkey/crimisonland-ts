/**
 * PixiGrimAdapter - Pixi.js implementation of GrimInterface
 *
 * Maps the Grim2D vtable API to Pixi.js rendering calls.
 * This provides the same interface the original game used with grim.dll.
 */

import {
    Application,
    Graphics,
    Sprite,
    Texture,
    Container,
    Assets,
    Rectangle,
    Text,
    TextStyle,
    Mesh,
    MeshGeometry,
} from 'pixi.js';
import type { GrimInterface, TextureHandle, ContainerHandle } from './GrimInterface';
import { InputManager } from './InputManager';
import { FullscreenButton } from '../ui/FullscreenButton';

/**
 * Internal texture slot data
 */
interface TextureSlot {
    name: string;
    texture: Texture;
    width: number;
    height: number;
}

export class PixiGrimAdapter implements GrimInterface {
    private app: Application | null = null;
    private graphics: Graphics | null = null;
    private uiGraphics: Graphics | null = null; // UI overlay graphics (menus, HUD) - renders above game layer
    private consoleGraphics: Graphics | null = null; // Console-specific graphics — renders above all UI
    private activeGraphics: Graphics | null = null; // Currently active graphics layer
    private inputManager: InputManager;

    // Timing
    private startTime: number = 0;
    private accumulatedTime: number = 0;
    private deltaTime: number = 0;
    private fps: number = 0;
    private lastFrameTime: number = 0;
    private frameCount: number = 0;
    private fpsAccumulator: number = 0;

    // Screen dimensions
    private width: number = 800;
    private height: number = 600;

    // Textures - maps handle to texture data
    private textures: Map<TextureHandle, TextureSlot> = new Map();
    private textureNameToHandle: Map<string, TextureHandle> = new Map();
    private nextTextureHandle: TextureHandle = 1;
    private boundTexture: TextureHandle = -1;

    // Rendering state
    private currentColor: { r: number; g: number; b: number; a: number } = { r: 255, g: 255, b: 255, a: 255 };
    private currentRotation: number = 0;
    private clearColor: { r: number; g: number; b: number; a: number } = { r: 0, g: 0, b: 0, a: 255 };

    // UV state (used for sprite texture mapping in Phase 2)
    private uvRect: { u0: number; v0: number; u1: number; v1: number } = { u0: 0, v0: 0, u1: 1, v1: 1 };

    // Blend mode state (C: grim_set_config_var 0x14)
    private currentBlendMode: 'normal' | 'add' | 'add-alpha' | 'multiply' = 'normal';

    // Sprite container for batched rendering
    private spriteContainer: Container | null = null;
    private uiSpriteContainer: Container | null = null; // UI sprites (menus, HUD) — renders above game layer
    private consoleSpriteContainer: Container | null = null; // Console sprites — renders above all UI
    private activeSpriteContainer: Container | null = null; // Currently active sprite container

    // Scene graph - Containers for grouping sprites
    private containers: Map<ContainerHandle, Container> = new Map();
    private nextContainerHandle: ContainerHandle = 1;
    private activeCustomContainer: Container | null = null; // If set, drawQuad adds to this instead of activeSpriteContainer

    // Caches to avoid creating new objects every frame (memory leak prevention)
    private uvTextureCache: Map<string, Texture> = new Map();
    private textStyleCache: Map<string, TextStyle> = new Map();

    // Fullscreen toggle button overlay
    private fullscreenButton: FullscreenButton | null = null;



    constructor(width: number = 800, height: number = 600) {
        this.width = width;
        this.height = height;
        this.inputManager = new InputManager();
    }

    // ============================================
    // Lifecycle
    // ============================================

    async init(): Promise<boolean> {
        try {
            this.app = new Application();

            await this.app.init({
                width: this.width,
                height: this.height,
                backgroundColor: this.colorToHex(this.clearColor),
                antialias: false,
                resolution: 1,
                autoStart: false, // We manually render in endFrame()
            });

            // Stop PIXI's internal ticker — we drive rendering ourselves via gameLoop()
            this.app.ticker.stop();
            // Only load Pixi devtools in development — tree-shaken from production builds
            if (import.meta.env.DEV) {
                import('@pixi/devtools').then(({ initDevtools }) => {
                    initDevtools({ app: this.app! });
                });
            }

            document.body.appendChild(this.app.canvas);

            // Create sprite container (terrain, entity sprites, effects)
            // Added first so it renders BELOW primitives
            this.spriteContainer = new Container();
            this.spriteContainer.label = 'spriteContainer';
            this.app.stage.addChild(this.spriteContainer);

            // Create graphics object for primitives (player/enemy debug shapes)
            // Added after sprites so it renders ON TOP of terrain
            this.graphics = new Graphics();
            this.graphics.label = 'gameGraphics';
            this.app.stage.addChild(this.graphics);

            // Create UI graphics layer (menus, HUD overlays) - renders above game sprites
            this.uiGraphics = new Graphics();
            this.uiGraphics.label = 'uiGraphics';
            this.app.stage.addChild(this.uiGraphics);

            // Create UI sprite container (menus, HUD) - renders above uiGraphics
            this.uiSpriteContainer = new Container();
            this.uiSpriteContainer.label = 'uiSpriteContainer';
            this.app.stage.addChild(this.uiSpriteContainer);

            // Create console graphics layer - added last so it renders above ALL other layers
            this.consoleGraphics = new Graphics();
            this.consoleGraphics.label = 'consoleGraphics';
            this.app.stage.addChild(this.consoleGraphics);

            // Create console sprite container - renders on top of everything (console text)
            this.consoleSpriteContainer = new Container();
            this.consoleSpriteContainer.label = 'consoleSpriteContainer';
            this.app.stage.addChild(this.consoleSpriteContainer);

            // Default to game graphics layer
            this.activeGraphics = this.graphics;
            this.activeSpriteContainer = this.spriteContainer;

            // Initialize input
            this.inputManager.init(this.app.canvas as HTMLCanvasElement);

            // Create fullscreen toggle button
            this.fullscreenButton = new FullscreenButton();

            // Set up dynamic resize — recompute 4:3 letterbox on window resize
            window.addEventListener('resize', () => this.handleResize());
            this.handleResize(); // Set initial size from current window dimensions

            // Initialize timing
            this.startTime = performance.now();
            this.lastFrameTime = this.startTime;

            return true;
        } catch (error) {
            console.error('Failed to initialize PixiGrimAdapter:', error);
            return false;
        }
    }

    destroy(): void {
        this.shutdown();
    }

    shutdown(): void {
        if (this.app) {
            this.app.destroy(true);
            this.app = null;
        }
        this.textures.clear();
        this.textureNameToHandle.clear();
        // Destroy cached UV textures to release GPU resources
        for (const tex of this.uvTextureCache.values()) {
            tex.destroy();
        }
        this.uvTextureCache.clear();
        this.textStyleCache.clear();
    }

    // ============================================
    // Timing
    // ============================================

    getTime(): number {
        return this.accumulatedTime;
    }

    setTime(ms: number): void {
        this.accumulatedTime = ms;
    }

    getDeltaTime(): number {
        return this.deltaTime;
    }

    getFPS(): number {
        return this.fps;
    }

    // ============================================
    // Input - Mouse
    // ============================================

    isMouseButtonDown(button: number): boolean {
        return this.inputManager.isMouseButtonDown(button);
    }

    isMouseButtonPressed(button: number): boolean {
        return this.inputManager.isMouseButtonPressed(button);
    }

    setMousePosition(x: number, y: number): void {
        this.inputManager.setMousePosition(x, y);
    }

    getMouseX(): number {
        return this.inputManager.getMouseX();
    }

    getMouseY(): number {
        return this.inputManager.getMouseY();
    }

    getMouseDeltaX(): number {
        return this.inputManager.getMouseDeltaX();
    }

    getMouseDeltaY(): number {
        return this.inputManager.getMouseDeltaY();
    }

    // ============================================
    // Input - Keyboard
    // ============================================

    isKeyDown(key: number): boolean {
        return this.inputManager.isKeyDown(key);
    }

    isKeyPressed(key: number): boolean {
        return this.inputManager.isKeyPressed(key);
    }

    getKeyChars(): number[] {
        return this.inputManager.getKeyChars();
    }

    flushInput(): void {
        this.inputManager.flush();
    }

    // ============================================
    // Textures
    // ============================================

    createTexture(name: string, width: number, height: number): TextureHandle {
        const handle = this.nextTextureHandle++;

        // Create an empty texture (white by default)
        const texture = Texture.WHITE;

        this.textures.set(handle, {
            name,
            texture,
            width,
            height,
        });
        this.textureNameToHandle.set(name, handle);

        return handle;
    }

    async loadTexture(name: string, path: string): Promise<TextureHandle> {
        const handle = this.nextTextureHandle++;

        try {
            const texture = await Assets.load(path);

            this.textures.set(handle, {
                name,
                texture,
                width: texture.width,
                height: texture.height,
            });
            this.textureNameToHandle.set(name, handle);

            return handle;
        } catch (error) {
            console.error(`Failed to load texture ${path}:`, error);
            return -1;
        }
    }

    validateTexture(handle: TextureHandle): boolean {
        return this.textures.has(handle);
    }

    destroyTexture(handle: TextureHandle): void {
        const slot = this.textures.get(handle);
        if (slot) {
            this.textureNameToHandle.delete(slot.name);
            this.textures.delete(handle);
        }
    }

    getTextureHandle(name: string): TextureHandle {
        return this.textureNameToHandle.get(name) ?? -1;
    }

    bindTexture(handle: TextureHandle, _stage: number = 0): void {
        this.boundTexture = handle;
    }

    registerTexture(name: string, texture: unknown): TextureHandle {
        // Cast to PIXI Texture
        const pixiTexture = texture as Texture;

        // Check if already registered
        const existing = this.textureNameToHandle.get(name);
        if (existing !== undefined) {
            return existing;
        }

        const handle = this.nextTextureHandle++;
        this.textures.set(handle, {
            name,
            texture: pixiTexture,
            width: pixiTexture.width,
            height: pixiTexture.height,
        });
        this.textureNameToHandle.set(name, handle);
        return handle;
    }

    getRenderer(): unknown {
        return this.app?.renderer;
    }

    // ============================================
    // Rendering - Batch
    // ============================================

    beginBatch(): void {
        // In Pixi.js, batching is automatic
        // This is a no-op but kept for API compatibility
    }

    flushBatch(): void {
        // Force render in Pixi.js
        if (this.app) {
            this.app.renderer.render(this.app.stage);
        }
    }

    endBatch(): void {
        // In Pixi.js, batching is automatic
    }

    // ============================================
    // Rendering - Draw commands
    // ============================================

    drawFullscreenQuad(): void {
        this.drawQuad(0, 0, this.width, this.height);
    }

    drawFullscreenColor(r: number, g: number, b: number, a: number): void {
        if (!this.activeGraphics || a <= 0) return;

        // PIXI v8 retained mode: container-level alpha is applied at render time
        // (using whatever value it has THEN, not when fill() was called).
        // Pass alpha in fill options so each shape has its own alpha.
        this.activeGraphics.rect(0, 0, this.width, this.height);
        this.activeGraphics.fill({ color: this.rgbToHex(r, g, b), alpha: a / 255 });
    }

    drawRectFilled(x: number, y: number, w: number, h: number): void {
        if (!this.activeGraphics) return;

        // Draw and fill in one go with alpha
        this.activeGraphics.rect(x, y, w, h);
        this.activeGraphics.fill({
            color: this.rgbToHex(this.currentColor.r, this.currentColor.g, this.currentColor.b),
            alpha: this.currentColor.a / 255,
        });
    }

    drawCircleFilled(x: number, y: number, radius: number): void {
        if (!this.activeGraphics) return;

        this.activeGraphics.circle(x, y, radius);
        this.activeGraphics.fill({
            color: this.rgbToHex(this.currentColor.r, this.currentColor.g, this.currentColor.b),
            alpha: this.currentColor.a / 255,
        });
    }

    drawCircleOutline(x: number, y: number, radius: number): void {
        if (!this.activeGraphics) return;

        this.activeGraphics.circle(x, y, radius);
        this.activeGraphics.stroke({
            color: this.rgbToHex(this.currentColor.r, this.currentColor.g, this.currentColor.b),
            alpha: this.currentColor.a / 255,
            width: 2,
        });
    }

    drawLine(x0: number, y0: number, x1: number, y1: number, thickness: number): void {
        if (!this.activeGraphics) return;

        this.activeGraphics.moveTo(x0, y0);
        this.activeGraphics.lineTo(x1, y1);
        this.activeGraphics.stroke({
            color: this.rgbToHex(this.currentColor.r, this.currentColor.g, this.currentColor.b),
            alpha: this.currentColor.a / 255,
            width: thickness,
        });
    }

    drawQuad(x: number, y: number, width: number, height: number): void {
        if (!this.activeSpriteContainer || !this.app) return;

        const textureSlot = this.textures.get(this.boundTexture);
        let texture = textureSlot?.texture ?? Texture.WHITE;

        // Apply UV coordinates if not using full texture
        if (this.uvRect.u0 !== 0 || this.uvRect.v0 !== 0 || this.uvRect.u1 !== 1 || this.uvRect.v1 !== 1) {
            const source = texture.source;
            const srcW = source.width;
            const srcH = source.height;

            // Include source dimensions in cache key so stale entries from
            // zero-size sources (texture not yet uploaded) are replaced once
            // the real dimensions become available.
            const cacheKey = `${this.boundTexture}:${this.uvRect.u0},${this.uvRect.v0},${this.uvRect.u1},${this.uvRect.v1}:${srcW}x${srcH}`;
            let cached = this.uvTextureCache.get(cacheKey);
            if (!cached && srcW > 0 && srcH > 0) {
                const frame = new Rectangle(
                    this.uvRect.u0 * srcW,
                    this.uvRect.v0 * srcH,
                    (this.uvRect.u1 - this.uvRect.u0) * srcW,
                    (this.uvRect.v1 - this.uvRect.v0) * srcH,
                );
                cached = new Texture({ source, frame });
                this.uvTextureCache.set(cacheKey, cached);
            }
            if (cached) {
                texture = cached;
            }
        }

        const sprite = new Sprite(texture);
        sprite.width = width;
        sprite.height = height;

        // When rotation is applied, rotate around the center of the quad
        // (matching C code's grim_set_rotation behavior)
        const rotation = this.activeCustomContainer ? 0 : this.currentRotation;
        if (rotation !== 0) {
            sprite.anchor.set(0.5, 0.5);
            sprite.x = x + width / 2;
            sprite.y = y + height / 2;
            sprite.rotation = rotation;
        } else {
            sprite.anchor.set(0, 0);
            sprite.x = x;
            sprite.y = y;
        }

        sprite.tint = this.rgbToHex(this.currentColor.r, this.currentColor.g, this.currentColor.b);
        sprite.alpha = this.currentColor.a / 255;
        // 'add-alpha' maps to PIXI 'add-npm' = gl.blendFunc(SRC_ALPHA, ONE)
        // This matches C code: D3DBLEND_SRCALPHA + D3DBLEND_ONE for bullet trails
        sprite.blendMode = this.currentBlendMode === 'add-alpha' ? 'add-npm' : this.currentBlendMode;

        // Add to custom container if set, otherwise use the active sprite container
        const targetContainer = this.activeCustomContainer ?? this.activeSpriteContainer;
        if (targetContainer) {
            targetContainer.addChild(sprite);
        }
    }

    /**
     * Draw a textured quad with 4 arbitrary corner positions.
     * Used by bullet trail rendering to create oriented strips between head/tail positions.
     * C code: grim_draw_quad_points(x1,y1, x2,y2, x3,y3, x4,y4)
     *
     * Uses a PixiJS Mesh with the currently bound texture and UV coordinates.
     * This allows gradient textures to create per-vertex alpha effects (e.g., bullet trail fade).
     *
     * Corner/UV mapping (matches C code vertex color slot order):
     *   Vertex 0 (x1,y1) → UV (u0, v0) — head left  (color slot 0)
     *   Vertex 1 (x2,y2) → UV (u1, v0) — head right  (color slot 1)
     *   Vertex 2 (x3,y3) → UV (u1, v1) — tail right  (color slot 2)
     *   Vertex 3 (x4,y4) → UV (u0, v1) — tail left   (color slot 3)
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
    ): void {
        if (!this.activeSpriteContainer) return;

        const textureSlot = this.textures.get(this.boundTexture);
        const texture = textureSlot?.texture ?? Texture.WHITE;

        // Build mesh geometry with 4 vertices
        const positions = new Float32Array([x1, y1, x2, y2, x3, y3, x4, y4]);
        const uvs = new Float32Array([
            this.uvRect.u0,
            this.uvRect.v0, // vertex 0 (head left)
            this.uvRect.u1,
            this.uvRect.v0, // vertex 1 (head right)
            this.uvRect.u1,
            this.uvRect.v1, // vertex 2 (tail right)
            this.uvRect.u0,
            this.uvRect.v1, // vertex 3 (tail left)
        ]);
        const indices = new Uint32Array([0, 1, 2, 0, 2, 3]);

        const geometry = new MeshGeometry({
            positions,
            uvs,
            indices,
        });

        const mesh = new Mesh({ geometry, texture });
        mesh.tint = this.rgbToHex(this.currentColor.r, this.currentColor.g, this.currentColor.b);
        // 'add-alpha' maps to PIXI 'add-npm' = gl.blendFunc(SRC_ALPHA, ONE)
        mesh.blendMode = this.currentBlendMode === 'add-alpha' ? 'add-npm' : this.currentBlendMode;
        mesh.alpha = this.currentColor.a / 255;

        const targetContainer = this.activeCustomContainer ?? this.activeSpriteContainer;
        if (targetContainer) {
            targetContainer.addChild(mesh);
        }
    }

    // ============================================
    // Rendering - State
    // ============================================

    setRotation(radians: number): void {
        this.currentRotation = radians;
    }

    setUV(u0: number, v0: number, u1: number, v1: number): void {
        this.uvRect = { u0, v0, u1, v1 };
    }

    setAtlasFrame(atlasSize: number, frame: number): void {
        const cellSize = 1.0 / atlasSize;
        const col = frame % atlasSize;
        const row = Math.floor(frame / atlasSize);

        this.uvRect = {
            u0: col * cellSize,
            v0: row * cellSize,
            u1: (col + 1) * cellSize,
            v1: (row + 1) * cellSize,
        };
    }

    setSubRect(atlasSize: number, width: number, height: number, frame: number): void {
        const cellSize = 1.0 / atlasSize;
        const col = frame % atlasSize;
        const row = Math.floor(frame / atlasSize);

        this.uvRect = {
            u0: col * cellSize,
            v0: row * cellSize,
            u1: col * cellSize + width * cellSize,
            v1: row * cellSize + height * cellSize,
        };
    }

    setColorArray(rgba: [number, number, number, number]): void {
        this.currentColor = { r: rgba[0], g: rgba[1], b: rgba[2], a: rgba[3] };
    }

    setColor(r: number, g: number, b: number, a: number): void {
        this.currentColor = { r, g, b, a };
    }

    setBlendMode(mode: 'normal' | 'add' | 'add-alpha' | 'multiply'): void {
        this.currentBlendMode = mode;
    }

    // ============================================
    // Rendering - Clear
    // ============================================

    setClearColor(r: number, g: number, b: number, _a: number): void {
        this.clearColor = { r, g, b, a: _a };
        if (this.app) {
            this.app.renderer.background.color = this.rgbToHex(r, g, b);
        }
    }

    clear(): void {
        if (this.graphics) {
            this.graphics.clear();
        }
        if (this.uiGraphics) {
            this.uiGraphics.clear();
        }
        if (this.consoleGraphics) {
            this.consoleGraphics.clear();
        }
        if (this.spriteContainer) {
            // Destroy all children to release GPU resources (textures, geometry, etc.)
            // removeChildren() alone only detaches from the display tree, causing memory leaks
            for (const child of this.spriteContainer.children) {
                child.destroy();
            }
            this.spriteContainer.removeChildren();
        }
        if (this.uiSpriteContainer) {
            for (const child of this.uiSpriteContainer.children) {
                child.destroy();
            }
            this.uiSpriteContainer.removeChildren();
        }
        if (this.consoleSpriteContainer) {
            for (const child of this.consoleSpriteContainer.children) {
                child.destroy();
            }
            this.consoleSpriteContainer.removeChildren();
        }
    }

    // ============================================
    // Screen info
    // ============================================

    getWidth(): number {
        return this.width;
    }

    getHeight(): number {
        return this.height;
    }

    /**
     * Recompute the logical resolution and CSS scaling for 4:3 letterbox.
     * Called on window resize events and once during init().
     *
     * Strategy:
     * 1. Compute largest 4:3 rectangle that fits the browser window (min 800×600)
     * 2. Resize Pixi renderer to that logical resolution
     * 3. CSS-scale the canvas element to fit the viewport, centered with black bars
     * 4. Update InputManager coordinate transform for accurate mouse tracking
     */
    private handleResize(): void {
        if (!this.app) return;

        const windowW = window.innerWidth;
        const windowH = window.innerHeight;

        // Fixed reference resolution matching C code (config_blob.screen_width/height).
        // this.width / this.height stay at 800×600 — never reassigned here.
        // Every system calling grim.getWidth()/getHeight() sees the same viewport
        // as the original game, keeping zoom level consistent regardless of window size.
        const REF_W = this.width;  // 800
        const REF_H = this.height; // 600

        // Fit the fixed 4:3 reference into the window
        const cssScale = Math.min(windowW / REF_W, windowH / REF_H);
        const cssW = Math.round(REF_W * cssScale);
        const cssH = Math.round(REF_H * cssScale);

        // Use device pixel ratio for sharp rendering on HiDPI screens
        const dpr = window.devicePixelRatio || 1;
        const renderW = Math.round(cssW * dpr);
        const renderH = Math.round(cssH * dpr);

        // Resize Pixi renderer to native pixel resolution
        this.app.renderer.resize(renderW, renderH);

        // Scale the stage so 800×600 game coordinates fill the full renderer
        const stageScale = renderW / REF_W;
        this.app.stage.scale.set(stageScale, stageScale);

        // Set canvas CSS size (renderer sets width/height attrs, we control CSS)
        const canvas = this.app.canvas as HTMLCanvasElement;
        canvas.style.width = `${cssW}px`;
        canvas.style.height = `${cssH}px`;
        canvas.style.position = 'absolute';
        // Remove any CSS transform (we use stage scale instead)
        canvas.style.transform = '';
        canvas.style.transformOrigin = '';

        // Center the canvas in the viewport with letterbox / pillarbox
        const offsetX = (windowW - cssW) / 2;
        const offsetY = (windowH - cssH) / 2;
        canvas.style.left = `${offsetX}px`;
        canvas.style.top = `${offsetY}px`;

        // Update InputManager coordinate transform.
        // Mouse events arrive in CSS pixels; cssScale maps them back to 800×600 game coords.
        this.inputManager.setScaleAndOffset(cssScale, offsetX, offsetY);

        // Keep fullscreen button anchored to canvas bottom-right
        if (this.fullscreenButton) {
            this.fullscreenButton.updatePosition(offsetX, offsetY, cssW, cssH);
        }
    }

    // ============================================
    // Frame management
    // ============================================

    beginFrame(): void {
        const now = performance.now();
        this.deltaTime = now - this.lastFrameTime;
        this.lastFrameTime = now;
        this.accumulatedTime = now - this.startTime;

        // FPS calculation
        this.frameCount++;
        this.fpsAccumulator += this.deltaTime;
        if (this.fpsAccumulator >= 1000) {
            this.fps = this.frameCount;
            this.frameCount = 0;
            this.fpsAccumulator = 0;
        }

        // Clear for new frame
        this.clear();
    }

    endFrame(): void {
        // Update input state for next frame
        this.inputManager.update();

        // Manually render the stage (ticker is stopped, we control rendering)
        if (this.app) {
            this.app.renderer.render(this.app.stage);
        }
    }

    // ============================================
    // Utility methods
    // ============================================

    private colorToHex(color: { r: number; g: number; b: number }): number {
        return (color.r << 16) | (color.g << 8) | color.b;
    }

    private rgbToHex(r: number, g: number, b: number): number {
        return (r << 16) | (g << 8) | b;
    }

    // ============================================
    // Text Rendering
    // ============================================

    drawText(x: number, y: number, text: string, size: number = 16, color: string = '#ffffff'): void {
        if (!this.activeSpriteContainer) return;

        // Cache TextStyle objects to avoid creating new ones every frame
        const styleKey = `${size}:${color}`;
        let style = this.textStyleCache.get(styleKey);
        if (!style) {
            style = new TextStyle({
                fontFamily: 'monospace',
                fontSize: size,
                fill: color,
            });
            this.textStyleCache.set(styleKey, style);
        }

        const textObj = new Text({ text, style });
        textObj.x = x;
        textObj.y = y;

        // Add to active custom container if set, otherwise to the active sprite container
        // (respects setGraphicsLayer so text renders on the correct layer)
        const targetContainer = this.activeCustomContainer || this.activeSpriteContainer;
        targetContainer.addChild(textObj);
    }

    drawTextSmall(x: number, y: number, text: string): void {
        this.drawText(x, y, text, 12, '#ffffff');
    }

    drawTextLarge(x: number, y: number, text: string): void {
        this.drawText(x, y, text, 24, '#ffffff');
    }

    /**
     * Switch between graphics and sprite layers
     * @param layer - 'game' for world graphics/sprites (behind UI), 'ui' for overlay graphics/sprites (on top)
     */
    setGraphicsLayer(layer: 'game' | 'ui' | 'console'): void {
        if (layer === 'console') {
            this.activeGraphics = this.consoleGraphics;
            this.activeSpriteContainer = this.consoleSpriteContainer;
        } else if (layer === 'ui') {
            this.activeGraphics = this.uiGraphics;
            this.activeSpriteContainer = this.uiSpriteContainer;
        } else {
            this.activeGraphics = this.graphics;
            this.activeSpriteContainer = this.spriteContainer;
        }
    }

    /**
     * Set camera offset for world-space rendering (camera centering + shake).
     * C code reference: camera_update @ 00409500, lines 6205-6206
     *
     * Moves only the game-world containers (spriteContainer + graphics),
     * NOT the stage itself. This leaves the terrain TilingSprite and UI
     * containers unaffected — terrain scrolls via tilePosition, and UI
     * renders in screen space.
     */
    setCameraOffset(x: number, y: number): void {
        if (this.spriteContainer) {
            this.spriteContainer.x = x;
            this.spriteContainer.y = y;
        }
        if (this.graphics) {
            this.graphics.x = x;
            this.graphics.y = y;
        }
    }

    /**
     * Get the Pixi.js application instance (for advanced usage)
     */
    getApp(): Application | null {
        return this.app;
    }

    // ============================================
    // Scene Graph - Containers
    // ============================================

    createContainer(): ContainerHandle {
        const container = new Container();
        const handle = this.nextContainerHandle++;
        this.containers.set(handle, container);

        // Add to the active sprite container by default
        if (this.activeSpriteContainer) {
            this.activeSpriteContainer.addChild(container);
        }

        return handle;
    }

    destroyContainer(handle: ContainerHandle): void {
        const container = this.containers.get(handle);
        if (container) {
            container.destroy({ children: true });
            this.containers.delete(handle);

            // Clear active if this was the active container
            if (this.activeCustomContainer === container) {
                this.activeCustomContainer = null;
            }
        }
    }

    setContainerTransform(handle: ContainerHandle, x: number, y: number, rotation: number): void {
        const container = this.containers.get(handle);
        if (container) {
            container.x = x;
            container.y = y;
            container.rotation = rotation;
        }
    }

    setActiveContainer(handle: ContainerHandle | null): void {
        if (handle === null) {
            this.activeCustomContainer = null;
        } else {
            const container = this.containers.get(handle);
            if (container) {
                this.activeCustomContainer = container;
            }
        }
    }

    // ============================================
    // Fullscreen Toggle
    // ============================================

    showFullscreenButton(): void {
        if (this.fullscreenButton) {
            this.fullscreenButton.show();
        }
    }

    hideFullscreenButton(): void {
        if (this.fullscreenButton) {
            this.fullscreenButton.hide();
        }
    }
}
