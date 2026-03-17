/**
 * CameraShake - Camera shake effect system
 *
 * Accurate port of camera shake logic from crimsonland.exe_decompiled.c
 * C code reference: lines 6130-6170, 6205-6206, 6460-6461
 */

/**
 * Camera shake system
 * Implements pulse-based screen shake for explosions and impacts
 */
export class CameraShake {
    private shakeTimer: number = 0.0;
    private shakePulses: number = 0;
    private shakeOffsetX: number = 0.0;
    private shakeOffsetY: number = 0.0;

    /**
     * Start camera shake
     * C code reference: lines 6460-6461 (Nuke bonus)
     *
     * @param pulses Number of shake pulses (Nuke uses 20 = 0x14)
     * @param initialTimer Initial timer value (Nuke uses 0.3 = 0x3e4ccccd)
     */
    startShake(pulses: number, initialTimer: number = 0.3): void {
        this.shakePulses = pulses;
        this.shakeTimer = initialTimer;
    }

    /**
     * Update camera shake
     * C code reference: lines 6130-6170
     *
     * @param dt Delta time in seconds
     * @param timeScaleActive Whether time scaling is active (affects pulse duration)
     */
    update(dt: number, timeScaleActive: boolean = false): void {
        // If timer expired, zero out offsets (C lines 6131-6134)
        if (this.shakeTimer <= 0.0) {
            this.shakeOffsetX = 0.0;
            this.shakeOffsetY = 0.0;
        } else {
            // Decay timer (C line 6136)
            this.shakeTimer -= dt * 3.0;

            // Check if pulse finished (C line 6137)
            if (this.shakeTimer < 0.0) {
                // Decrement pulse counter (C line 6138)
                this.shakePulses--;

                // Check if all pulses exhausted (C line 6139)
                if (this.shakePulses < 1) {
                    // Stop shaking (C line 6140)
                    this.shakeTimer = 0.0;
                } else {
                    // Start next pulse (C lines 6143-6145)
                    this.shakeTimer = timeScaleActive ? 0.06 : 0.1;

                    // Calculate X offset (C lines 6147-6155)
                    // Formula: rand() % (pulses * 60 / 20) + rand() % 10
                    const maxOffset = Math.floor((this.shakePulses * 60) / 20);
                    let offsetX = Math.floor(Math.random() * (maxOffset + 1)) + Math.floor(Math.random() * 10);

                    // Random sign flip (C lines 6151-6154)
                    if (Math.floor(Math.random() * 2) === 0) {
                        offsetX = -offsetX;
                    }
                    this.shakeOffsetX = offsetX;

                    // Calculate Y offset (C lines 6156-6166)
                    let offsetY = Math.floor(Math.random() * (maxOffset + 1)) + Math.floor(Math.random() * 10);

                    // Random sign flip (C lines 6160-6166)
                    if (Math.floor(Math.random() * 2) === 0) {
                        offsetY = -offsetY;
                    }
                    this.shakeOffsetY = offsetY;
                }
            }
        }
    }

    /**
     * Get current shake offset
     * C code reference: lines 6205-6206
     * These offsets are added to camera position
     */
    getOffset(): { x: number; y: number } {
        return {
            x: this.shakeOffsetX,
            y: this.shakeOffsetY,
        };
    }

    /**
     * Check if currently shaking
     */
    isShaking(): boolean {
        return this.shakeTimer > 0.0 || this.shakePulses > 0;
    }

    /**
     * Stop shake immediately
     */
    stop(): void {
        this.shakeTimer = 0.0;
        this.shakePulses = 0;
        this.shakeOffsetX = 0.0;
        this.shakeOffsetY = 0.0;
    }
}
