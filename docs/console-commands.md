# Console Commands

Open the console with the **`~`** (tilde/backquote) key. Scroll with **PageUp/PageDown**. Navigate history with **Up/Down** arrows.

## Built-in Commands

| Command | Usage | Description |
|---------|-------|-------------|
| `help` | `help` | Show built-in command help |
| `cmdlist` | `cmdlist` | List all registered commands |
| `vars` | `vars` | List all console variables (cvars) |
| `set` | `set <var> <value>` | Set a console variable |
| `echo` | `echo <text>` / `echo on|off` | Print text or toggle command echo |
| `clear` | `clear` | Clear the console log |
| `quit` | `quit` | Quit (no-op in browser) |

## Game Info

| Command | Usage | Description |
|---------|-------|-------------|
| `version` | `version` | Show game version info |
| `state` | `state` | Show current game state (Menu, Playing, etc.) |
| `fps` | `fps` | Show current FPS |
| `time` | `time` | Show elapsed game time |

## Game Control

| Command | Usage | Description |
|---------|-------|-------------|
| `start` | `start` | Start a new survival game |
| `start_tutorial` | `start_tutorial` | Start the tutorial |

## Player Commands

| Command | Usage | Description |
|---------|-------|-------------|
| `player_damage` | `player_damage <amount>` | Deal damage to the player |
| `player_heal` | `player_heal <amount>` | Heal the player |
| `weapon_switch` | `weapon_switch <id>` | Switch weapon by ID (0=Pistol, 1=AR, 2=Shotgun, ...) |
| `weapon_add` | `weapon_add <id\|name>` | Add weapon by ID or name; no args lists all weapons |
| `ammo_refill` | `ammo_refill` | Refill current weapon's ammo to full clip |
| `reflex_boost` | `reflex_boost <seconds>` | Activate reflex boost (slow-mo) for N seconds |
| `freeze` | `freeze <seconds>` | Freeze all enemies for N seconds |
| `sv_score_addexp` | `sv_score_addexp <amount>` | Add experience points |

## Perk Commands

| Command | Usage | Description |
|---------|-------|-------------|
| `perk_add` | `perk_add <hex_id>` | Add a perk by hex ID (e.g. `1c` for Uranium Bullets) |
| `perk_remove` | `perk_remove <hex_id>` | Remove a perk by hex ID |
| `perk_list` | `perk_list` | List all active perks |

## Enemy / Debug

| Command | Usage | Description |
|---------|-------|-------------|
| `debug_enemies` | `debug_enemies` | Show active enemy count and first enemy info |
| `spawn_enemy` | `spawn_enemy <type> [x] [y]` | Spawn enemy by type (0=Zombie, 1=Lizard, 2=Spider, 3=Spider2, 4=Alien, 5=Trooper) |
| `render_mode` | `render_mode <debug\|sprite>` | Toggle between debug shapes and sprite rendering |

## Quest Commands

| Command | Usage | Description |
|---------|-------|-------------|
| `quest_list` | `quest_list` | List all quests grouped by tier |
| `quest_start` | `quest_start <tier> <index>` | Start a specific quest (e.g. `quest_start 1 1`) |
| `quest_info` | `quest_info` | Show current quest status, timeline, and enemy counts |
| `quest_skip` | `quest_skip` | Force-complete the active quest |
| `quest_unlock` | `quest_unlock <index>` | Set the quest unlock index (0–39) |

## Asset Commands

| Command | Usage | Description |
|---------|-------|-------------|
| `assets_list` | `assets_list [prefix]` | List loaded asset files, optionally filtered by prefix |
| `assets_info` | `assets_info` | Show total file and texture counts |
| `list_terrain` | `list_terrain` | List terrain files in the PAQ archive |
| `list_gfx` | `list_gfx` | List gfx files in the PAQ archive |

## E2E Test Commands

| Command | Usage | Description |
|---------|-------|-------------|
| `test_env_start` | `test_env_start` | Start game with enemy spawning disabled (for testing) |
| `test_env_stop` | `test_env_stop` | Re-enable enemy spawning |
| `spawn_dummy` | `spawn_dummy <x> <y> [label]` | Spawn a dummy enemy at coordinates with optional label |
| `dummy_report` | `dummy_report` | Report hit data for all active dummies |
| `dummy_clear` | `dummy_clear` | Remove all dummy enemies |
| `dummy_reset` | `dummy_reset` | Reset hit data on all dummies |
