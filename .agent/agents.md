# Crimsonland 2003 TS — Agent Configuration

## Context
TypeScript/PixiJS recreation of Crimsonland (2003). Ported function-by-function
from decompiled C code. Accuracy to the original game is the primary measure.

## Conventions
- Include exact C line numbers in comments when porting
- Preserve C-style hex flag values (0x01, 0x04, etc.)
- Match C behavior exactly unless explicitly noted
- Game content is in PAQ/JAZ format in `content/`
- When implementing particle effects, reference `src/data/ParticleAtlas.ts` for
  sprite names and `docs/particle-atlas-reference.md` for the visual atlas layout.
  Always use `ParticleFrame.*` enum values, never raw frame numbers.

## Architecture
- `src/engine/` — PixiJS adapter implementing `GrimInterface`
- `src/entities/` — Game objects (Player, Enemy, Projectile, etc.)
- `src/systems/` — Game logic (AI, collision, effects, etc.)
- `src/rendering/` — Rendering pipeline
- `src/ui/` — Menu and HUD
- `src/data/` — Data loaders and tables
- `src/audio/` — Sound and music
- `src/console/` — Developer console

## Testing
- `npm test` (Vitest) — 19 unit tests
- `npm run test:e2e` (Playwright) — 6 E2E tests
- Always verify `npm run build` passes

## C Code Reference
- Decompiled source: `crimsonland.exe_decompiled_renamed.c`
- Module breakdown: `c_code_breakdown/`
- Porting tracker: `docs/porting/C_CODE_PORTING_TRACKER.md`
