# Crimsonland 2003 — TypeScript Remake

A faithful TypeScript/PixiJS recreation of **Crimsonland** (2003), the classic top-down survival shooter.

🎮 **Play**: https://buddingmonkey.github.io/crimisonland-ts/

## About

Ground-up recreation ported function-by-function from decompiled C code.
The goal is pixel-perfect behavioral parity with the original 2003 release.

**Status**: ~98% of actionable C code ported — 123 TypeScript files (40,896 lines)
with 32 test files (12,107 lines). All 56 perks, 22 weapons, 50 quest templates,
and 40 quests implemented.

## Game Assets Required

This project does not include the original game assets. You'll need to supply
your own crimson.paq and sfx.paq files. The game will prompt you to upload
them on first launch, and they'll be stored in your browser for future sessions.

## Controls

### Gameplay
| Action | Key |
|--------|-----|
| Move | **WASD** or **Arrow Keys** |
| Aim | **Mouse** |
| Fire | **Left Click** |
| Reload / Swap Weapons | **R** (reload normally; swaps weapons with Alternate Weapon perk) |
| Swap Weapons (alt) | **Tab** (requires Alternate Weapon perk) |
| Open Perk Selection | **Right Click** or **Space** (when perks available) |
| Pause | **Escape** |
| Fullscreen | **Fullscreen button** (in-game UI) |

### Menus
| Action | Key |
|--------|-----|
| Navigate | **W/S**, **Up/Down**, or **Mouse** |
| Confirm | **Enter** or **Left Click** |
| Back / Cancel | **Escape** |
| Quick-select item | **1–5** |

### Developer Console
| Action | Key |
|--------|-----|
| Toggle console | **` (Backtick)** |
| Submit command | **Enter** |
| Command history | **Up/Down** |
| Scroll output | **PageUp/PageDown** |

## Unimplemented Features

The following features from the original C code have not been ported:

- **Multiplayer** — entire mode not implemented (single-player only)
- **Survival Typing Mode** — entire mode not implemented

See [C_CODE_PORTING_TRACKER.md](docs/porting/C_CODE_PORTING_TRACKER.md) for
detailed porting progress.

## Development

### Prerequisites
- Node.js 18+

### Run Locally
```
npm install
npm run dev
```

### Run Tests
```
npm test              # Unit + E2E tests (Vitest)
npx vitest run        # Run all tests once
npx vitest --watch    # Watch mode
```

### Build
```
npm run build
```

## Architecture

- `src/engine/` — PixiJS adapter implementing `GrimInterface`
- `src/entities/` — Game objects (Player, Enemy, Projectile, etc.)
- `src/systems/` — Game logic systems (AI, collision, effects, etc.)
- `src/rendering/` — Rendering pipeline
- `src/ui/` — Menu and HUD components
- `src/data/` — Data loaders and tables
- `src/audio/` — Sound and music systems

## C Code Reference

- Decompiled sources at project root
- Module breakdown: `c_code_breakdown/`
- Porting tracker: `docs/porting/C_CODE_PORTING_TRACKER.md`

## Credits

- Original game by **10tons Ltd** (2003)
- TypeScript port by **Andrew Eiche and Google Antigravity**
