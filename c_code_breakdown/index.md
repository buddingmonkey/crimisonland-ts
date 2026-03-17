# Crimsonland Decompiled Code Breakdown

This directory contains the decompiled and renamed C code split into logical modules.
The original monolithic file was ~63,460 lines. These files are for reference/search only and are not meant to compile.

## File Index

| File | Lines | Functions | Description |
|------|-------|-----------|-------------|
| `_globals.c` | 326 | — | Global variable declarations, typedefs, struct definitions, and file header |
| `console.c` | 2,383 | 46 | In-game developer console: command parsing, cvar system, console rendering, log management, input handling, and autocomplete. |
| `config.c` | 861 | 10 | Game configuration defaults, core cvar registration, build path construction, loading screen, and registry read/write helpers. |
| `demo.c` | 780 | 10 | Demo/trial mode: setup variants, purchase interstitials, trial overlay, purchase screen, time-limited gameplay, and version/trial queries. |
| `ui_core.c` | 3,768 | 37 | Core UI primitives: hit-test rectangles, mouse-inside checks, button updates, element layout, text rendering, HUD rendering, cursor, progress bars, screen callbacks, and text wrapping. |
| `input.c` | 1,352 | 8 | Keyboard/mouse/joystick input: key name lookup, keybind display, input polling, fire-key edge detection, and joystick POV checks. |
| `perks.c` | 1,211 | 12 | Perk system: perk application effects, selection screen, choice generation, prompt rendering, effect updates, and perk metadata tables. |
| `weapons.c` | 1,479 | 5 | Weapon system: weapon table initialization, stat lookups, refresh/availability, firing logic, and weapon selection UI. |
| `projectiles.c` | 2,156 | 5 | Projectile and bullet pools: projectile spawning, movement, collision, area damage, and secondary projectile management. |
| `effects.c` | 1,486 | 26 | Visual effects system: effect entry init/free/select/update/render, FX queue management (ground/rotated sprites), particle spawning, electric arcs, plasma explosions, fire particles, shockwaves, and UV table initialization. |
| `bonuses.c` | 1,523 | 16 | Bonus pickup system: bonus application, update/timer logic, random type selection, metadata table, HUD slot management, and availability tracking. |
| `creatures.c` | 4,205 | 23 | Creature/enemy system: creature pool allocation, spawning, reset, damage application, type table initialization (spider, alien, trooper), and active-check logic. |
| `quest.c` | 6,120 | 63 | Quest mode: quest timeline updates, quest file loading/parsing, quest results screen, quest failed screen, and quest metadata initialization. |
| `survival.c` | 655 | 3 | Survival mode: survival update loop, spawn scheduling, wave progression, and survival-specific game logic. |
| `gameplay.c` | 2,685 | 17 | Core gameplay loop: world rendering, main update-and-render, game state reset, victory/game-over screens, startup initialization, main entry point, game mode labels, sequence management, and save/load. |
| `camera.c` | 107 | 1 | Camera system: camera update, follow logic, and offset management. |
| `tutorial.c` | 545 | 2 | Tutorial system: tutorial prompt dialogs, timeline updates, and tutorial state management. |
| `credits.c` | 772 | 6 | Credits screen: line setup, scrolling, build, and screen update/render logic. |
| `highscores.c` | 1,034 | 16 | Highscore system: sentinel initialization, record management, name input, display rendering, and submit/button state. |
| `mod_api.c` | 896 | 40 | Plugin/mod API: GFX wrappers (clear, texture, color, printf), core API (execute, get/set/del var, commands), SFX API bindings, and mod loading/enumeration. |
| `audio.c` | 635 | 19 | Audio system: DirectSound initialization, Vorbis OGG decoding (memory read/seek/open/close, PCM16 conversion), audio format detection/creation, suspend/resume, and grim engine interface loading. |
| `sfx.c` | 902 | 21 | Sound effects: SFX entry init/deinit, playback, volume control, and sound resource management. |
| `renderer.c` | 3,099 | 76 | Renderer interface: backend selection, texture loading/binding, draw calls, state management, render targets, grim engine vtable dispatch wrappers, and texture caching. |
| `math.c` | 2,191 | 61 | 3D/2D math library: vec2/vec3 operations (add, sub, length, scale, normalize, cross, dot, lerp, slerp), mat4x4 transforms (rotate, translate, multiply, build-from-axes), angle normalization, heading calculation, and color operations. |
| `simd.c` | 3,585 | 28 | SIMD math: packed sincos (Chebyshev polynomial approximation), CPUID detection, and SSE/SSE2 helper routines. |
| `terrain.c` | 328 | 3 | Terrain/map system: terrain texture loading, tile rendering, and ground effect baking. |
| `player.c` | 2,769 | 8 | Player state: position, health, experience, movement, fire control, and player sprite rendering. |
| `crt_runtime.c` | 15,608 | 333 | C runtime library: memory management (malloc, free, SBH heap), string operations, file I/O, stdio streams, exception handling, floating-point formatting, timezone/locale, environment variables, TLS, and process startup/exit. |

**Total**: 63,461 lines across 28 files
