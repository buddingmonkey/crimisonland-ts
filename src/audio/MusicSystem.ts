/**
 * MusicSystem - Background music playback system
 *
 * Port of music functions from crimsonland.exe_decompiled.c
 * C code reference: lines 34225-34750
 *
 * Key C functions:
 * - music_queue_track @ line 34253: Adds track to playlist
 * - music_playlist[] @ line 34725: Random track selection
 * - music_entry_table @ line 34739: Music playback entries
 * - config_blob.music_volume @ line 34740-34741: Volume control
 */

// No external imports needed - uses fetch API for loading

/**
 * MusicSystem - Manages background music playback
 *
 * Features:
 * - Playlist with random track selection (C line 34723-34725)
 * - Looping music playback
 * - Independent volume control from SFX
 */
export class MusicSystem {
    // Web Audio API components
    private audioContext: AudioContext | null = null;
    private gainNode: GainNode | null = null;
    private currentSource: AudioBufferSourceNode | null = null;

    // Track management (C: music_playlist[])
    private tracks: Map<string, AudioBuffer> = new Map();
    private playlist: string[] = [];
    private currentTrack: string | null = null;
    private isPlaying: boolean = false;

    // Volume control (C: config_blob.music_volume)
    private volume: number = 0.6;
    private muted: boolean = false;

    /**
     * Initialize the music system
     * C code reference: part of sfx_system_init @ lines 34449-34493
     */
    async init(): Promise<boolean> {
        try {
            this.audioContext = new AudioContext();

            // Create master gain node for music volume
            this.gainNode = this.audioContext.createGain();
            this.gainNode.connect(this.audioContext.destination);
            this.gainNode.gain.value = this.volume;

            // Chrome autoplay policy: register user-gesture listener to resume
            this.registerUserGestureResume();

            return true;
        } catch (error) {
            console.error('[MusicSystem] Failed to initialize:', error);
            return false;
        }
    }

    /**
     * Register a one-shot user-gesture listener that resumes the AudioContext.
     * Same pattern as SoundSystem — Chrome/Safari/Firefox all require this.
     */
    private registerUserGestureResume(): void {
        if (!this.audioContext) return;

        const ctx = this.audioContext;
        if (ctx.state === 'running') return;

        const resumeAudio = async () => {
            if (ctx.state === 'suspended') {
                try {
                    await ctx.resume();
                } catch (e) {
                    console.warn('[MusicSystem] Failed to resume AudioContext:', e);
                }
            }
            for (const evt of ['click', 'keydown', 'touchstart', 'mousedown'] as const) {
                document.removeEventListener(evt, resumeAudio, { capture: true } as EventListenerOptions);
            }
        };

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
     * Load tracks from game_tunes.txt file
     * C code reference: console_cmd_snd_add_game_tune @ line 23991
     *
     * Parses lines like: snd_addGameTune gt1_ingame.ogg
     */
    async loadTracksFromGameTunes(): Promise<void> {
        if (!this.audioContext) {
            console.warn('[MusicSystem] Not initialized, cannot load tracks');
            return;
        }

        try {
            // Load the game_tunes.txt file
            const response = await fetch('/content/music/game_tunes.txt');
            const text = await response.text();

            // Parse all snd_addGameTune commands first, then load in parallel
            const trackNames = text
                .split('\n')
                .map((line) => line.trim())
                .filter((line) => line.startsWith('snd_addGameTune '))
                .map((line) => line.substring('snd_addGameTune '.length).trim())
                .filter(Boolean);

            // Load all tracks in parallel for much faster loading
            await Promise.all(trackNames.map((name) => this.loadTrack(name)));
        } catch (error) {
            console.warn('[MusicSystem] Failed to load game_tunes.txt:', error);
        }
    }

    /**
     * Load a single track from the music folder
     * C code reference: sfx_load_tune @ lines 34225-34244
     */
    async loadTrack(filename: string): Promise<boolean> {
        if (!this.audioContext) {
            return false;
        }

        try {
            const path = `/content/music/${filename}`;
            const response = await fetch(path);

            if (!response.ok) {
                console.warn(`[MusicSystem] Failed to fetch ${filename}: ${response.status}`);
                return false;
            }

            const arrayBuffer = await response.arrayBuffer();
            const audioBuffer = await this.audioContext.decodeAudioData(arrayBuffer);

            this.tracks.set(filename, audioBuffer);
            this.playlist.push(filename);

            return true;
        } catch (error) {
            console.warn(`[MusicSystem] Failed to load ${filename}:`, error);
            return false;
        }
    }

    /**
     * Load a specific track (for menu music, etc.)
     */
    async loadSpecificTrack(filename: string): Promise<boolean> {
        if (!this.audioContext) {
            return false;
        }

        // Don't re-load if already loaded
        if (this.tracks.has(filename)) {
            return true;
        }

        try {
            const path = `/content/music/${filename}`;
            const response = await fetch(path);

            if (!response.ok) {
                console.warn(`[MusicSystem] Failed to fetch ${filename}: ${response.status}`);
                return false;
            }

            const arrayBuffer = await response.arrayBuffer();
            const audioBuffer = await this.audioContext.decodeAudioData(arrayBuffer);

            this.tracks.set(filename, audioBuffer);
            // Note: Don't add to playlist - this is a specific track (menu, intro, etc.)

            return true;
        } catch (error) {
            console.warn(`[MusicSystem] Failed to load ${filename}:`, error);
            return false;
        }
    }

    /**
     * Play a random track from the playlist
     * C code reference: lines 34723-34725
     *
     * iVar2 = crt_rand();
     * sfx_id = music_playlist[iVar2 % DAT_004cc8d0];
     */
    playRandom(): void {
        if (this.playlist.length === 0) {
            console.warn('[MusicSystem] No tracks in playlist');
            return;
        }

        // Select random track from playlist (C line 34725)
        const index = Math.floor(Math.random() * this.playlist.length);
        const trackName = this.playlist[index];

        this.play(trackName);
    }

    /**
     * Play a specific track by name
     * C code reference: sfx_entry_start_playback @ line 34739
     */
    play(trackName: string): void {
        if (!this.audioContext || !this.gainNode) {
            console.warn('[MusicSystem] Not initialized');
            return;
        }

        const buffer = this.tracks.get(trackName);
        if (!buffer) {
            console.warn(`[MusicSystem] Track not loaded: ${trackName}`);
            return;
        }

        // Stop current track if playing
        this.stop();

        // Create new source node
        this.currentSource = this.audioContext.createBufferSource();
        this.currentSource.buffer = buffer;
        this.currentSource.connect(this.gainNode);

        // Loop the track
        this.currentSource.loop = true;

        // Start playback
        this.currentSource.start(0);
        this.currentTrack = trackName;
        this.isPlaying = true;
    }

    /**
     * Stop current music playback
     * C code reference: sfx_mute_all @ line 34734
     */
    stop(): void {
        if (this.currentSource) {
            try {
                this.currentSource.stop();
            } catch {
                // Ignore error if already stopped
            }
            this.currentSource.disconnect();
            this.currentSource = null;
        }
        this.currentTrack = null;
        this.isPlaying = false;
    }

    /**
     * Set music volume
     * C code reference: config_blob.music_volume @ line 34740
     *
     * @param volume Volume level (0-1)
     */
    setVolume(volume: number): void {
        this.volume = Math.max(0, Math.min(1, volume));
        if (this.gainNode) {
            this.gainNode.gain.value = this.muted ? 0 : this.volume;
        }
    }

    /**
     * Get current volume
     */
    getVolume(): number {
        return this.volume;
    }

    /**
     * Set muted state
     */
    setMuted(muted: boolean): void {
        this.muted = muted;
        if (this.gainNode) {
            this.gainNode.gain.value = muted ? 0 : this.volume;
        }
    }

    /**
     * Check if muted
     */
    isMuted(): boolean {
        return this.muted;
    }

    /**
     * Check if currently playing
     */
    isCurrentlyPlaying(): boolean {
        return this.isPlaying;
    }

    /**
     * Get current track name
     */
    getCurrentTrack(): string | null {
        return this.currentTrack;
    }

    /**
     * Get number of loaded tracks
     */
    getTrackCount(): number {
        return this.tracks.size;
    }

    /**
     * Get playlist track count
     */
    getPlaylistCount(): number {
        return this.playlist.length;
    }

    /**
     * Update music system (call each frame)
     * Can be used for cross-fade or dynamic music features
     */
    update(_dt: number): void {
        // Currently music loops automatically via source.loop = true
        // This could be extended for cross-fading or dynamic music selection
    }

    /**
     * Shutdown music system
     */
    async shutdown(): Promise<void> {
        this.stop();
        this.tracks.clear();
        this.playlist = [];

        if (this.audioContext) {
            await this.audioContext.close();
            this.audioContext = null;
        }

        this.gainNode = null;
    }
}
