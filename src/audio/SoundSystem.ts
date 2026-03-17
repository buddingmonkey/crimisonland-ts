/**
 * SoundSystem - Web Audio API-based sound effects system
 *
 * Port of the DirectSound-based sound system from crimsonland.exe_decompiled.c
 * C code reference: lines 33327-34853
 */

import { SoundId, SOUND_PATHS } from './SoundId';
import type { AssetManager } from '../data/AssetManager';

/**
 * Cooldown constants from C code
 * C code reference: sfx_play @ lines 34594-34598
 */
const DEFAULT_COOLDOWN = 0.05; // C line 34598: 0.05 seconds
const FLAMER_COOLDOWN = 0.44; // C line 34595: 0.44 seconds for flamethrower

/**
 * Sample rate for Reflex Boosted perk
 * C code reference: sfx_play @ lines 34582-34593
 */
const NORMAL_RATE = 1.0; // C: 0xac44 (44100 Hz) = normal
const REFLEX_BOOSTED_RATE = 0.5; // C: 0x5622 (22050 Hz) = half speed

/**
 * SoundSystem - Manages sound effects playback
 *
 * C code reference: sfx_* functions @ lines 33327-34853
 */
export class SoundSystem {
    private audioContext: AudioContext | null = null;
    private samples: Map<SoundId, AudioBuffer> = new Map();
    private cooldowns: Map<SoundId, number> = new Map(); // C: sfx_cooldown_table
    private masterVolume: number = 1.0; // C: config_blob.sfx_volume
    private reflexBoostedTimer: number = 0; // C: _bonus_reflex_boost_timer
    private initialized: boolean = false;
    private muted: boolean = false;

    /**
     * Initialize the sound system
     * C code reference: sfx_system_init @ lines 34449-34493
     *
     * Web Audio requires user interaction before creating AudioContext,
     * so this must be called after first user click/key.
     */
    async init(): Promise<boolean> {
        if (this.initialized) {
            return true;
        }

        try {
            // Create audio context (equivalent to dsound_init @ line 34471)
            this.audioContext = new AudioContext();

            // Clear all cooldowns (C lines 34482-34486)
            this.cooldowns.clear();

            // Chrome autoplay policy: AudioContext starts 'suspended'.
            // Register a one-time user-gesture listener to resume it.
            this.registerUserGestureResume();

            this.initialized = true;

            return true;
        } catch (error) {
            console.error('[SoundSystem] Failed to initialize:', error);
            this.muted = true;
            return false;
        }
    }

    /**
     * Register a one-shot user-gesture listener that resumes the AudioContext.
     * Chrome, Safari, and Firefox all require a user gesture (click, keydown,
     * touchstart) before audio can play. This listener auto-removes itself
     * once the context is running.
     */
    private registerUserGestureResume(): void {
        if (!this.audioContext) return;

        const ctx = this.audioContext;
        if (ctx.state === 'running') return; // Already running, no need

        const resumeAudio = async () => {
            if (ctx.state === 'suspended') {
                try {
                    await ctx.resume();
                } catch (e) {
                    console.warn('[SoundSystem] Failed to resume AudioContext:', e);
                }
            }
            // Remove all listeners once resumed
            for (const evt of ['click', 'keydown', 'touchstart', 'mousedown'] as const) {
                document.removeEventListener(evt, resumeAudio, { capture: true } as EventListenerOptions);
            }
        };

        // Listen on document with capture to catch the very first interaction
        for (const evt of ['click', 'keydown', 'touchstart', 'mousedown'] as const) {
            document.addEventListener(evt, resumeAudio, { once: false, capture: true });
        }
    }

    /**
     * Resume audio context after user interaction
     * Web Audio contexts start suspended and need user gesture to resume
     */
    async resume(): Promise<void> {
        if (this.audioContext && this.audioContext.state === 'suspended') {
            await this.audioContext.resume();
        }
    }

    /**
     * Load a sound sample from an ArrayBuffer
     * C code reference: sfx_load_sample @ lines 34129-34209
     *
     * @param id Sound ID to load
     * @param audioData ArrayBuffer containing audio data
     * @returns Promise that resolves when loaded
     */
    async loadSampleFromBuffer(id: SoundId, audioData: ArrayBuffer): Promise<boolean> {
        if (!this.audioContext) {
            return false;
        }

        try {
            const audioBuffer = await this.audioContext.decodeAudioData(audioData);
            this.samples.set(id, audioBuffer);
            return true;
        } catch (error) {
            // Failed to decode audio
            return false;
        }
    }

    /**
     * Load a sound sample via fetch (for standalone files)
     * C code reference: sfx_load_sample @ lines 34129-34209
     *
     * @param id Sound ID to load
     * @returns Promise that resolves when loaded
     */
    async loadSample(id: SoundId): Promise<boolean> {
        if (!this.audioContext) {
            return false;
        }

        const path = SOUND_PATHS[id];
        if (!path) {
            console.warn(`[SoundSystem] No path for sound ID ${id}`);
            return false;
        }

        try {
            const response = await fetch(path);
            if (!response.ok) {
                // Sound file not found - this is expected during development
                // C code: prints warning but continues (line 34179)
                return false;
            }

            const arrayBuffer = await response.arrayBuffer();
            return this.loadSampleFromBuffer(id, arrayBuffer);
        } catch (error) {
            // Failed to load - sound files may not exist yet
            return false;
        }
    }

    /**
     * Load all sound samples from AssetManager (PAQ archive)
     * C code reference: audio_init_sfx @ lines 34336-34444
     *
     * @param assetManager The AssetManager with loaded sfx.paq
     */
    async loadSamplesFromAssetManager(assetManager: AssetManager): Promise<void> {
        if (!this.audioContext) {
            console.warn('[SoundSystem] Cannot load samples - not initialized');
            return;
        }

        let loaded = 0;
        let failed = 0;

        // Collect all decode promises and run in parallel for much faster loading
        const decodePromises: Promise<void>[] = [];

        for (const id of Object.values(SoundId).filter((v) => typeof v === 'number')) {
            const soundId = id as SoundId;
            const path = SOUND_PATHS[soundId];

            if (!path) continue;

            // Get audio data from PAQ via AssetManager
            const audioData = assetManager.getAudioData(path);
            if (!audioData) {
                failed++;
                continue;
            }

            decodePromises.push(
                this.loadSampleFromBuffer(soundId, audioData)
                    .then((success) => {
                        if (success) {
                            loaded++;
                        } else {
                            failed++;
                        }
                    })
                    .catch(() => {
                        failed++;
                    }),
            );
        }

        await Promise.all(decodePromises);
    }

    /**
     * Load all sound samples via fetch (fallback)
     * C code reference: audio_init_sfx @ lines 34336-34444
     */
    async loadAllSamples(): Promise<void> {
        const loadPromises: Promise<boolean>[] = [];

        for (const id of Object.values(SoundId).filter((v) => typeof v === 'number')) {
            loadPromises.push(this.loadSample(id as SoundId));
        }

        const results = await Promise.all(loadPromises);
        void results; // Results tracked internally by loadSample
    }

    /**
     * Play a sound effect with centered pan
     * C code reference: sfx_play @ lines 34561-34604
     *
     * @param id Sound ID to play
     * @param volume Optional volume multiplier (0-1)
     * @returns true if sound was played
     */
    play(id: SoundId, volume: number = 1.0): boolean {
        return this.playInternal(id, 0, volume);
    }

    /**
     * Play a sound effect with stereo panning
     * C code reference: sfx_play_panned @ lines 34609-34663
     *
     * @param id Sound ID to play
     * @param pan Stereo position (-1 = left, 0 = center, 1 = right)
     * @param volume Optional volume multiplier (0-1)
     * @returns true if sound was played
     */
    playPanned(id: SoundId, pan: number, volume: number = 1.0): boolean {
        // Clamp pan to [-1, 1] (C converts from -10000 to 10000 range)
        const clampedPan = Math.max(-1, Math.min(1, pan));
        return this.playInternal(id, clampedPan, volume);
    }

    /**
     * Play a sound at a world position
     * Converts world coordinates to stereo pan based on screen center
     *
     * @param id Sound ID to play
     * @param x World X position
     * @param y World Y position (unused for now)
     * @param screenWidth Screen width for pan calculation
     * @param volume Optional volume multiplier
     */
    playAtPosition(id: SoundId, x: number, _y: number, screenWidth: number, volume: number = 1.0): boolean {
        // Calculate pan based on X position relative to center
        // Range: -1 (left edge) to +1 (right edge)
        const centerX = screenWidth / 2;
        const pan = (x - centerX) / centerX;
        return this.playPanned(id, pan, volume);
    }

    /**
     * Internal play implementation
     */
    private playInternal(id: SoundId, pan: number, volume: number): boolean {
        // Check if muted or not initialized (C line 34576)
        if (this.muted || !this.audioContext || !this.initialized) {
            return false;
        }

        // Opportunistic resume: if context is still suspended (user hasn't
        // interacted yet, or gesture fired during loading), try to resume now.
        // This is a no-op if already running. The actual resume will take effect
        // on the *next* play call since resume() is async, but it ensures the
        // context gets unblocked as soon as possible.
        if (this.audioContext.state === 'suspended') {
            this.audioContext.resume().catch(() => {});
            return false; // Can't play yet — context still waking up
        }

        // Check if sample exists (C line 34573)
        const buffer = this.samples.get(id);
        if (!buffer) {
            return false;
        }

        // Check cooldown (C lines 34579-34581)
        const cooldown = this.cooldowns.get(id) ?? 0;
        if (cooldown > 0) {
            return false;
        }

        // Set cooldown for this sound (C lines 34594-34598)
        if (id === SoundId.FLAMER_FIRE_01 || id === SoundId.FLAMER_FIRE_02) {
            this.cooldowns.set(id, FLAMER_COOLDOWN);
        } else {
            this.cooldowns.set(id, DEFAULT_COOLDOWN);
        }

        // Create and configure source node
        const source = this.audioContext.createBufferSource();
        source.buffer = buffer;

        // Apply playback rate for Reflex Boosted effect (C lines 34582-34593)
        if (this.reflexBoostedTimer > 0) {
            source.playbackRate.value = REFLEX_BOOSTED_RATE;
        } else {
            source.playbackRate.value = NORMAL_RATE;
        }

        // Create gain node for volume
        const gainNode = this.audioContext.createGain();
        gainNode.gain.value = volume * this.masterVolume;

        // Create stereo panner for positioning
        const pannerNode = this.audioContext.createStereoPanner();
        pannerNode.pan.value = pan;

        // Connect: source -> panner -> gain -> destination
        source.connect(pannerNode);
        pannerNode.connect(gainNode);
        gainNode.connect(this.audioContext.destination);

        // Start playback
        source.start();

        return true;
    }

    /**
     * Update sound system (call each frame)
     * C code reference: audio_update @ lines 34667-34698
     *
     * @param dt Delta time in seconds
     */
    update(dt: number): void {
        if (this.muted) {
            return;
        }

        // Decay all cooldowns (C lines 34679-34685)
        for (const [id, cooldown] of this.cooldowns.entries()) {
            if (cooldown > 0) {
                const newCooldown = cooldown - dt;
                if (newCooldown <= 0) {
                    this.cooldowns.delete(id);
                } else {
                    this.cooldowns.set(id, newCooldown);
                }
            }
        }

        // Decay reflex boosted timer
        if (this.reflexBoostedTimer > 0) {
            this.reflexBoostedTimer = Math.max(0, this.reflexBoostedTimer - dt);
        }
    }

    /**
     * Set master volume
     * C code: config_blob.sfx_volume
     *
     * @param volume Volume (0-1)
     */
    setMasterVolume(volume: number): void {
        this.masterVolume = Math.max(0, Math.min(1, volume));
    }

    /**
     * Get master volume
     */
    getMasterVolume(): number {
        return this.masterVolume;
    }

    /**
     * Set reflex boosted timer (for slow-motion sound effect)
     * C code reference: _bonus_reflex_boost_timer (line 34582)
     *
     * @param time Time in seconds
     */
    setReflexBoostedTimer(time: number): void {
        this.reflexBoostedTimer = time;
    }

    /**
     * Set muted state
     * C code: config_blob.reserved0[0] flag
     */
    setMuted(muted: boolean): void {
        this.muted = muted;
    }

    /**
     * Check if muted
     */
    isMuted(): boolean {
        return this.muted;
    }

    /**
     * Check if a sample is loaded
     */
    hasSample(id: SoundId): boolean {
        return this.samples.has(id);
    }

    /**
     * Get cooldown remaining for a sound
     */
    getCooldown(id: SoundId): number {
        return this.cooldowns.get(id) ?? 0;
    }

    /**
     * Shutdown sound system
     * C code reference: audio_shutdown_all @ lines 34546-34556
     */
    async shutdown(): Promise<void> {
        if (this.audioContext) {
            await this.audioContext.close();
            this.audioContext = null;
        }
        this.samples.clear();
        this.cooldowns.clear();
        this.initialized = false;
    }
}
