/**
 * InputManager - Handles keyboard and mouse input state
 *
 * Tracks current and previous frame input states to detect
 * edge-triggered events (just pressed, just released).
 */
export class InputManager {
    // Keyboard state
    private keysDown: Set<number> = new Set();
    private keysPressed: Set<number> = new Set();
    private keysReleased: Set<number> = new Set();
    private keyCharQueue: number[] = []; // Queue of character codes from this frame

    // Mouse state
    private mouseX: number = 0;
    private mouseY: number = 0;
    private mouseDeltaX: number = 0;
    private mouseDeltaY: number = 0;
    private mouseButtonsDown: Set<number> = new Set();
    private mouseButtonsPressed: Set<number> = new Set();
    private mouseButtonsReleased: Set<number> = new Set();

    // Previous frame mouse position for delta calculation
    private prevMouseX: number = 0;
    private prevMouseY: number = 0;

    // Canvas reference for coordinate conversion
    private canvas: HTMLCanvasElement | null = null;

    // CSS transform state for letterbox scaling
    // Updated by PixiGrimAdapter.handleResize() after each window resize
    private cssScale: number = 1;
    private canvasOffsetX: number = 0;
    private canvasOffsetY: number = 0;

    /**
     * Initialize input listeners on the given canvas
     */
    init(canvas: HTMLCanvasElement): void {
        this.canvas = canvas;

        // Hide browser cursor — game renders its own cursor sprite
        canvas.style.cursor = 'none';

        // Keyboard events (on document for global capture)
        document.addEventListener('keydown', this.onKeyDown.bind(this));
        document.addEventListener('keyup', this.onKeyUp.bind(this));

        // Mouse events — all on document so CDP/Playwright events are captured
        // (CDP dispatches at document level, canvas-scoped listeners miss them)
        document.addEventListener('mousemove', this.onMouseMove.bind(this));
        document.addEventListener('mousedown', this.onMouseDown.bind(this));
        document.addEventListener('mouseup', this.onMouseUp.bind(this));
        canvas.addEventListener('contextmenu', (e) => e.preventDefault());

        // Prevent default for game keys
        document.addEventListener('keydown', (e) => {
            // Prevent scrolling with arrow keys, space, etc.
            if ([32, 37, 38, 39, 40].includes(e.keyCode)) {
                e.preventDefault();
            }
        });
    }

    /**
     * Call at the end of each frame to reset edge-triggered states
     */
    update(): void {
        // Clear per-frame state
        this.keysPressed.clear();
        this.keysReleased.clear();
        this.mouseButtonsPressed.clear();
        this.mouseButtonsReleased.clear();
        this.keyCharQueue = []; // Clear character queue

        // Update mouse delta
        this.mouseDeltaX = this.mouseX - this.prevMouseX;
        this.mouseDeltaY = this.mouseY - this.prevMouseY;
        this.prevMouseX = this.mouseX;
        this.prevMouseY = this.mouseY;
    }

    /**
     * Clear all input state
     */
    flush(): void {
        this.keysDown.clear();
        this.keysPressed.clear();
        this.keysReleased.clear();
        this.mouseButtonsDown.clear();
        this.mouseButtonsPressed.clear();
        this.mouseButtonsReleased.clear();
        this.keyCharQueue = [];
        this.mouseDeltaX = 0;
        this.mouseDeltaY = 0;
    }

    // ============================================
    // Keyboard
    // ============================================

    isKeyDown(keyCode: number): boolean {
        return this.keysDown.has(keyCode);
    }

    isKeyPressed(keyCode: number): boolean {
        return this.keysPressed.has(keyCode);
    }

    isKeyReleased(keyCode: number): boolean {
        return this.keysReleased.has(keyCode);
    }

    getKeyChars(): number[] {
        return this.keyCharQueue;
    }

    private onKeyDown(event: KeyboardEvent): void {
        const keyCode = event.keyCode;
        if (!this.keysDown.has(keyCode)) {
            this.keysPressed.add(keyCode);
        }
        this.keysDown.add(keyCode);

        // Add character to queue for text input
        if (event.key.length === 1) {
            this.keyCharQueue.push(event.key.charCodeAt(0));
        } else if (keyCode === 13) {
            this.keyCharQueue.push(13); // Enter
        } else if (keyCode === 8) {
            this.keyCharQueue.push(8); // Backspace
        }
    }

    private onKeyUp(event: KeyboardEvent): void {
        const keyCode = event.keyCode;
        this.keysDown.delete(keyCode);
        this.keysReleased.add(keyCode);
    }

    // ============================================
    // Mouse
    // ============================================

    getMouseX(): number {
        return this.mouseX;
    }

    getMouseY(): number {
        return this.mouseY;
    }

    getMouseDeltaX(): number {
        return this.mouseDeltaX;
    }

    getMouseDeltaY(): number {
        return this.mouseDeltaY;
    }

    setMousePosition(x: number, y: number): void {
        this.mouseX = x;
        this.mouseY = y;
    }

    /**
     * Set CSS scale factor and canvas offset for letterbox coordinate transform.
     * Called by PixiGrimAdapter after each window resize.
     */
    setScaleAndOffset(scale: number, offsetX: number, offsetY: number): void {
        this.cssScale = scale;
        this.canvasOffsetX = offsetX;
        this.canvasOffsetY = offsetY;
    }

    isMouseButtonDown(button: number): boolean {
        return this.mouseButtonsDown.has(button);
    }

    isMouseButtonPressed(button: number): boolean {
        return this.mouseButtonsPressed.has(button);
    }

    isMouseButtonReleased(button: number): boolean {
        return this.mouseButtonsReleased.has(button);
    }

    private onMouseMove(event: MouseEvent): void {
        this.updateMousePosition(event);
    }

    private onMouseDown(event: MouseEvent): void {
        // Also update cursor position — CDP clicks may not send a preceding mousemove
        this.updateMousePosition(event);
        const button = event.button;
        if (!this.mouseButtonsDown.has(button)) {
            this.mouseButtonsPressed.add(button);
        }
        this.mouseButtonsDown.add(button);
    }

    private onMouseUp(event: MouseEvent): void {
        this.updateMousePosition(event);
        const button = event.button;
        this.mouseButtonsDown.delete(button);
        this.mouseButtonsReleased.add(button);
    }

    /** Update mouseX/mouseY from any MouseEvent's clientX/clientY.
     *  Transforms DOM coords through CSS scale + offset for letterbox support. */
    private updateMousePosition(event: MouseEvent): void {
        if (this.canvas) {
            // Map DOM pixel coords → logical coords through CSS scale/offset
            this.mouseX = (event.clientX - this.canvasOffsetX) / this.cssScale;
            this.mouseY = (event.clientY - this.canvasOffsetY) / this.cssScale;
        }
    }
}
