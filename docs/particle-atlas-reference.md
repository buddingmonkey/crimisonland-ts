# Particle Atlas Reference

> **For agents implementing particle effects.** Always use `ParticleFrame.*` enum constants from `src/data/ParticleAtlas.ts`. Never use raw frame numbers.

## Texture: `game/particles.jaz` (256×256 px)

Packed inside `content/crimson.paq`. Loaded at runtime by `AssetManager`.

## Grid System

The atlas is subdivided into grids. `gridSize` determines cell pixel size:

| gridSize | Grid | Cell Size | Use Case |
|----------|------|-----------|----------|
| 2 | 2×2 | 128×128 px | Large expansion flashes |
| 4 | 4×4 | 64×64 px | Most particle effects |
| 8 | 8×8 | 32×32 px | Blood splat variants |
| 16 | 16×16 | 16×16 px | (unused) |

Frame index is **row-major**: `frame = col + row × gridSize`

## Human-Verified 8×8 Grid Layout (32×32 px per cell)

```
         Col 0           Col 1         Col 2         Col 3         Col 4            Col 5           Col 6            Col 7
  Row 0: Bubble(Shield)  Blood Lg 1    Blood Lg 2    Blood Lg 3    Blood Med        Blood Small     Yellow Glow 0,0  Yellow Glow 1,0
  Row 1: Ice Small 1     Ice Small 2   Ice Small 3   Bullet Casing Empty            Empty           Yellow Glow 0,1  Yellow Glow 1,1
  Row 2: Ice Large 0,0   Ice Large 1,0 Explosion 0,0 Explosion 1,0 White Glow 0,0   White Glow 1,0  Smoke 0,0        Smoke 1,0
  Row 3: Ice Large 0,1   Ice Large 1,1 Explosion 0,1 Explosion 1,1 White Glow 0,1   White Glow 1,1  Smoke 0,1        Smoke 1,1
  Row 4: Burst 0,0       Burst 1,0     Burst 2,0     Burst 3,0     Large Circle 0,0 Lg Circle 1,0   Lg Circle 2,0    Lg Circle 3,0
  Row 5: Burst 0,1       Burst 1,1     Burst 2,1     Burst 3,1     Large Circle 0,1 Lg Circle 1,1   Lg Circle 2,1    Lg Circle 3,1
  Row 6: Burst 0,2       Burst 1,2     Burst 2,2     Burst 3,2     Large Circle 0,2 Lg Circle 2,2   Lg Circle 2,2    Lg Circle 3,2
  Row 7: Burst 0,3       Burst 1,3     Burst 2,3     Burst 3,3     Large Circle 0,3 Lg Circle 1,3   Lg Circle 2,3    Lg Circle 3,3
```

**Multi-cell sprites** (span multiple 32px cells):

| Sprite | Cells | Pixel Size |
|---|---|---|
| Yellow Glow | cols 6-7, rows 0-1 | 64×64 px |
| Ice Large | cols 0-1, rows 2-3 | 64×64 px |
| Explosion | cols 2-3, rows 2-3 | 64×64 px |
| White Glow | cols 4-5, rows 2-3 | 64×64 px |
| Smoke | cols 6-7, rows 2-3 | 64×64 px |
| Burst | cols 0-3, rows 4-7 | 128×128 px |
| Large Circle | cols 4-7, rows 4-7 | 128×128 px |

## 4×4 Grid (64×64 px per cell)

Each 4×4 cell covers a 2×2 block of the 8×8 grid above:

| Frame | Pixel Pos | Contents |
|---|---|---|
| 0 | (0,0) | Bubble (Shield) glow disc + Blood Lg 1 + Ice Small 1,2 |
| 1 | (64,0) | Blood Lg 2,3 + Ice Small 3 + Bullet Casing |
| 2 | (128,0) | Blood Med + Blood Small + 2 empty |
| 3 | (192,0) | Yellow Glow (complete 64×64) |
| 4 | (0,64) | Ice Large (complete 64×64) |
| 5 | (64,64) | Explosion (complete 64×64) |
| 6 | (128,64) | White Glow (complete 64×64) |
| 7 | (192,64) | Smoke (complete 64×64) |
| 8 | (0,128) | Burst top-left quarter |
| 9 | (64,128) | Burst top-right quarter |
| 10 | (128,128) | Large Circle top-left quarter |
| 11 | (192,128) | Large Circle top-right quarter |
| 12 | (0,192) | Burst bottom-left quarter |
| 13 | (64,192) | Burst bottom-right quarter |
| 14 | (128,192) | Large Circle bottom-left quarter |
| 15 | (192,192) | Large Circle bottom-right quarter |

## ParticleFrame Enum Reference

| Enum Constant | ID | Grid | Frame | Visual | Used For |
|---|---|---|---|---|---|
| `GLOW_SOFT` | 0x00 | 4×4 | 0 | Bubble (Shield) disc | Bursts, shockwaves, fire ring |
| `EXPANSION_FLASH` | 0x01 | 2×2 | 0 | Top-left 128px quadrant | Expansion flashes, electric arcs |
| `PROJECTILE_TRAIL` | 0x02 | 4×4 | 10 | Large Circle TL quarter | Projectile trails, slow particles |
| `BLOOD_SPLAT_A` | 0x03 | 8×8 | 2 | Blood Large 2 | Blood terrain baking |
| `BLOOD_SPLAT_B` | 0x04 | 8×8 | 3 | Blood Large 3 | Blood terrain baking |
| `BLOOD_SPLAT_C` | 0x05 | 8×8 | 4 | Blood Medium | Blood terrain baking |
| `BLOOD_SPLAT_D` | 0x06 | 8×8 | 5 | Blood Small | Blood terrain baking |
| `BLOOD_SPLATTER` | 0x07 | 4×4 | 6 | White Glow (tinted) | Flying blood particles |
| `FREEZE_SHARD_A` | 0x08 | 8×8 | 8 | Ice Small 1 (0,32) | Freeze shard variant A |
| `FREEZE_SHARD_B` | 0x09 | 8×8 | 9 | Ice Small 2 (32,32) | Freeze shard variant B |
| `FREEZE_SHARD_C` | 0x0a | 8×8 | 10 | Ice Small 3 (64,32) | Freeze shard variant C |
| `FLAME_SPRITE` | 0x0b | 4×4 | 5 | Explosion (complete 64×64) | Flame particle fire sprite |
| `EXPLOSION_SPARKLE` | 0x0c | 4×4 | 5 | Explosion (64×64) | Explosion debris sparkles |
| `GLOW_ORB` | 0x0d | 4×4 | 3 | Yellow Glow | Cursor, aim, glow halos |
| `FREEZE_OVERLAY` | 0x0e | 4×4 | 8 | Burst TL quarter | Freeze crystal overlay on creatures |
| `EXPANSION_RING` | 0x0f | 2×2 | 3 | Large Circle (128×128 ring) | Nuke expansion ring, reflex boost halo |
| `SHADOW_DISC` | 0x10 | 4×4 | 0 | Bubble (Shield) disc | Shadow disc (rendered black) |
| `SMOKE_RING` | 0x11 | 4×4 | 7 | Smoke (complete 64×64) | Smoke ring in explosions |
| `SHELL_CASING` | 0x12 | 4×4 | 2 | Blood Med/Small area | Tiny brass bullet casing |

## How to Use

### Spawning effects in `EffectSystem`

```typescript
import { ParticleFrame } from '../../data/ParticleAtlas';

// Use the enum constant in spawn calls:
this.spawn(ParticleFrame.GLOW_SOFT, x, y);
this.spawn(ParticleFrame.EXPANSION_FLASH, x, y);
```

### Setting atlas frame for rendering

```typescript
import { ParticleFrame, getParticleAtlasFrame } from '../../data/ParticleAtlas';

const { atlasSize, frame } = getParticleAtlasFrame(ParticleFrame.GLOW_ORB);
grim.setAtlasFrame(atlasSize, frame);
```

### Computing UV coordinates

```typescript
import { ParticleFrame, getParticleUV } from '../../data/ParticleAtlas';

const uv = getParticleUV(ParticleFrame.FREEZE_SHARD_A);
// → { u0: 0.25, v0: 0.75, u1: 0.5, v1: 1.0 }
```

## Cross-Reference: Spawn Functions → ParticleFrames

| Spawn Function | Frames Used |
|---|---|
| `spawnBurst` | `GLOW_SOFT` |
| `spawnFreezeShard` | `FREEZE_SHARD_A`, `B`, `C` (random) |
| `spawnFreezeShatter` | `FREEZE_OVERLAY` + random shards |
| `spawnFreezeFlash` | `EXPANSION_FLASH` |
| `spawnShrinkFx` | `EXPANSION_FLASH` + `GLOW_SOFT` |
| `spawnElectricArc` | `EXPANSION_FLASH` |
| `spawnPlasmaExplosion` | `EXPANSION_FLASH` |
| `spawnFireParticles` | `GLOW_SOFT` |
| `spawnShockwave` | `GLOW_SOFT` |
| `spawnExplosionBurst` | `EXPANSION_RING` + `SMOKE_RING` + `GLOW_SOFT` + `EXPLOSION_SPARKLE` |
| `spawnReflexHalo` | `EXPANSION_RING` |
| `spawnShellCasing` | `SHELL_CASING` |
| `spawnBloodSplatter` | `BLOOD_SPLAT_A` |
| `addRandomGroundDebris` | `BLOOD_SPLAT_A` through `BLOOD_SPLAT_D` (random) |
| `drawMonsterVisionGlow` | `SHADOW_DISC` (yellow tint) |
| `spawnRadioactive` | `SHADOW_DISC` (green tint) |
| Radioactive player aura | `SHADOW_DISC` (green tint, additive) |
