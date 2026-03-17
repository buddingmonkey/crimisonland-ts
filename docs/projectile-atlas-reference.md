# Projectile Atlas Reference (projs.jaz)

> [!IMPORTANT]
> The projectile spritesheet (`game/projs.jaz`) is a **separate** texture from
> `particles.jaz`. The C code binds it via `projectile_texture` for ion beams,
> fire bullets, pulse gun, splitter gun, and blade gun rendering.
> **Do not confuse with `particles_texture`** — they use different atlas layouts.

## Texture File
- **Path**: `game/projs.jaz`
- **C variable**: `projectile_texture`
- **TS handle**: `SpriteRenderer.projectileHandle`

## Known Sprites (from visual inspection)

| Atlas Call | Grid | Frame | Description |
|-----------|------|-------|-------------|
| `(2, 0)` | 2×2 | 0 | **Pulse Gun energy wave** — large 3×2-cell spanning sprite, greenish energy pulse |
| `(4, 2)` | 4×4 | 2 | **Ion/Fire beam trail sprite** — energy wave/glow used for ion beam segments |
| `(4, 3)` | 4×4 | 3 | **Rocket/missile sprite** — red-orange missile with fins, used for all rocket types |
| `(4, 6)` | 4×4 | 6 | **Blade Gun projectile** — circular spinning blade (shuriken) |

> [!NOTE]
> The first sprite in the grid is a **large multi-cell sprite** (energy wave) that
> spans approximately 3×2 cells of the 4×4 grid. Other sprites (white glow,
> missile, circular blade) occupy individual cells in the lower portion.

## C Rendering Pass Structure

The C `projectile_render()` function has three distinct rendering passes:

1. **Bullet trail pass** (lines 1240-1387): Uses `bullet_trail_texture` for
   bullet-type projectiles (pistol, assault rifle, shotgun, etc.)
2. **Plasma pass** (lines 1392-1637): Uses `particles_texture` with frame `(4,3)`
   for plasma projectile glow orbs
3. **Special projectile pass** (lines 1643-1898): Uses `projectile_texture`
   (projs.jaz) for ion beams, fire bullets, pulse gun, splitter, and blade gun

> [!CAUTION]
> **Common agent mistake**: Ion beam and fire bullet rendering must bind
> `projectileHandle` (projs.jaz), NOT `particlesHandle` (particles.jaz).
> Using the wrong texture produces a faint reddish appearance from the
> flame particle sprite instead of the correct energy wave.
