# FireRed Romhack — Zero-Context Continuation Guide

> **Read this first.** Single source of truth for continuing work on this project.

---

## What This Is

A **FireRed decompilation romhack** forked from [pret/pokefirered](https://github.com/pret/pokefirered) with Gen 6+ mechanical upgrades. Codebase: `/mnt/data/Github/prototype/firered-romhack-1`. Build: `make -j$(nproc)`.

Reference codebase for porting: **pokeemerald-expansion (RHH)** at `/mnt/data/Github/prototype/pokeemerald-expansion`.

**Active branch:** `feature-AI-upgrade`

---

## Build & Verify

```bash
cd /mnt/data/Github/prototype/firered-romhack-1
make -j$(nproc) 2>&1 | grep "error:"     # must be empty
wc -c pokefirered_modern.gba             # must be 16777216 (exactly 16MB)
python3 tools/verify_data.py             # validates Fairy/P-S split/TM data
```

---

## Coding Rules

1. **Converge, don't adapt.** Port from RHH using identical names, structs, and signatures. If our name differs from RHH, rename ours.
2. **`FRLG_STUB`** = mechanic that exists in RHH but needs infrastructure not yet in FireRed.
3. **`GEN4_STUB`** = utility function returning neutral value, declared in header, real body later.
4. **No invented AI logic.** Trace to RHH or don't add it.
5. **Build must stay clean.** `make -j$(nproc) 2>&1 | grep "error:"` returns nothing.
6. **Active test/debug code** must be documented in `## Active Test/Debug Changes` in `README.md`.
7. **Named fields, not FLAG_*.** `FLAG_*` constants are removed. Use struct field names directly.
8. **Token efficiency.** For large ports (500+ lines), use Python porting tools instead of reading full files into LLM context.

---

## What's Already Done (Shipped)

### Core Features

| Feature | Status | Notes |
|---|---|---|
| **Fairy Type** | ✅ Done | 19th type, full Gen 6 table, 18 species, graphics |
| **Physical/Special Split** | ✅ Done | Per-move `category` field, all 355 moves assigned, UI icons |
| **Running Shoes from start** | ✅ Done | No item needed, works indoors |
| **Reusable TMs** | ✅ Done | Infinite-use (Gen 5+), sell/dupe blocked |
| **Overworld Poison** | ✅ Done | Configurable via `OW_POISON_DAMAGE` in `include/config.h` |
| **pret Bug Fixes** | ✅ Done | All `#ifdef BUGFIX` / `#ifdef UBFIX` enabled (~25 bugs) |
| **Modern compiler default** | ✅ Done | `arm-none-eabi-gcc` default, no `MODERN=1` needed |

### Move Engine Overhaul (Phases 1–13)

| Phase | Description | Status |
|---|---|---|
| 1 | `struct MoveInfo` expansion (u16 effect/target, named fields, recoil, etc.) | ✅ Done |
| 2 | `struct LevelUpMove` expansion (u16 move + u16 level) | ✅ Done |
| 3 | `additionalEffects[]` system (multi-secondary-effect support) | ✅ Done |
| 5 | Unified `moves_info.h` (names + descriptions + stats in one file) | ✅ Done |
| 6 | Animation infrastructure (opcodes 0x30–0x34, sprites, palettes, INCBINs) | ✅ Done |
| 7 | Gen 4+ moves — batches 1 & 2, base animations up to MOVE_POISON_JAB (364) | ✅ Done |
| 8 | `CMD_ARGS()` macro refactor (RHH assembly syntax parity) | ✅ Done |
| 8.5 | Gen 4–9 moves data sync (927 moves, index consistency) | ✅ Done |
| 9 | Legacy effect macro purge + `.additionalEffects` array finalization | ✅ Done |
| 10 | preproc compiler upgrade (named keyword args) | ✅ Done |
| 11 | Modern compiler syntax and UB fixes (zero warnings on gcc 15+) | ✅ Done |
| 12 | Battle script effect hooks restoration (two-turn attacks, stat modifiers) | ✅ Done |
| 13 | RHH faithfulness audit & move ban system (13 ban flags, `ignoresSubstitute`) | ✅ Done |

### Battle AI (Phases 4a–4c + Tiers A–J)

| Phase | Description | Status |
|---|---|---|
| 4a | All 9 AI flags ported from ASM to C | ✅ Done |
| 4b | Smart switching — faithful RHH port + Gen 3 mechanics | ✅ Done |
| 4c | Gen 4+ AI heuristics (Sucker Punch, Shell Smash, Tailwind, etc.) | ✅ Done |
| 5 | Automated AI test framework (in-ROM DSL from RHH) | ⏳ Pending |
| A–G | Core AI infrastructure (AiLogicData, damage sim, speed, stat helpers) | ✅ Done |
| H | CanSetNonVolatileStatus chain (12 status helpers) | ✅ Done |
| J | AI_CalcAdditionalEffectScore pipeline (26 functions) | ✅ Done |
| J-supp | WeatherChecker + FieldStatusChecker + ShouldCureStatusInternal | ✅ Done |
| Phase A | STATUS_FIELD_* fix + Gravity/TrickRoom AI | ✅ Done |

### Architecture Migrations

| Feature | Description | Status |
|---|---|---|
| **Wild AI Init Fix** | Ported RHH scaling AI logic for wild battles | ✅ Done |
| **EWRAM Optimization** | `sMapTilesBackup` → heap (98.88% → 92.65%) | ✅ Done |
| **Auto-lowercase** | Gen 6+ naming screen keyboard feature | ✅ Done |
| **Instant Text Speed** | `OPTIONS_TEXT_SPEED_INSTANT` + RHH repeat-loop pattern | ✅ Done |
| **Phase B: `struct Volatiles`** | `status2` + `gStatuses3` → 100+ named bitfields | ✅ Done |
| **Phase C: `types[3]`** | `type1,type2,unknown` → `types[3]`, macros, 86 sites | ✅ Done |

---

## Current Hard Limits

| Limit | Cap | Note |
|---|---|---|
| Move ID (learnsets) | **65534** (u16, -1 sentinel) | Effectively unlimited for Gen 1-3 |
| TM slots | **64** (64-bit bitmask) | 6 slots remaining |
| Move effects | **65535** (u16) | Phase 1 complete |
| Move flags | **unlimited** (named fields) | Phase 1 complete |
| Additional effects per move | **3** (2-bit field) | Phase 3 complete |

---

## Key Files Reference

| File | Purpose |
|---|---|
| `include/config.h` | Feature toggles (`OW_POISON_DAMAGE`, etc.) |
| `include/config/battle.h` | `B_*` timer constants for volatile bitfield widths |
| `include/constants/moves.h` | Move ID `#defines` + `MOVES_COUNT` |
| `include/constants/battle_move_effects.h` | `EFFECT_*` constants (214 effects, ends at `EFFECT_CAMOUFLAGE`) |
| `include/constants/battle_ai.h` | AI flag constants (`AI_FLAG_*`) |
| `include/constants/battle.h` | `VOLATILE_DEFINITIONS`, `enum VolatileId`, `MOVE_EFFECT_*`, `STATUS_FIELD_*` |
| `include/constants/pokemon.h` | `LEVEL_UP_END` (0xFFFF), `LEVEL_UP_END_ENTRY`, `LEVEL_UP_MOVE` macro |
| `include/pokemon.h` | `struct MoveInfo`, `struct Volatiles`, `struct BattlePokemon` |
| `include/battle.h` | `struct AiLogicData`, `struct BattlerState`, type macros |
| `src/data/moves_info.h` | **Unified move data** — names, descriptions, stats (Phase 5) |
| `src/move_descriptions.c` | Compilation unit for `moves_info.h` |
| `src/data/pokemon/level_up_learnsets.h` | Level-up moves per species (`struct LevelUpMove[]`) |
| `src/data/pokemon/egg_moves.h` | Egg moves per species |
| `src/data/pokemon/tmhm_learnsets.h` | 64-bit TM/HM bitmask per species (6 slots left) |
| `src/data/party_menu.h` | `sTMHMMoves[]` table mapping TM slot → move |
| `data/battle_scripts_1.s` | Battle effect scripts (ASM macro language) |
| `src/data/battle_scripts_for_move_effects.h` | C table mapping EFFECT → BattleScript |
| `src/battle_script_commands.c` | C handlers for battle script commands |
| `data/battle_anim_scripts.s` | Move animation scripts + `gBattleAnims_Moves` table |
| `asm/macros/battle_anim_script.inc` | Animation bytecode macros (53 opcodes, 0x00–0x34) |
| `src/battle_anim.c` | Animation script interpreter + launch + opcode handlers |
| `include/constants/battle_anim.h` | `ANIM_TAG_*`, `B_ANIM_*`, `BG_*` constants |
| `src/data/battle_anim.h` | Sprite/palette/background registration tables |
| `src/battle_ai_main.c` | All AI flag functions + `gAIFunctionTable` dispatch |
| `src/battle_ai_util.c` | AI utilities: damage calc, switching, status/stat scoring |
| `src/battle_ai_field_statuses.c` | `WeatherChecker`, `FieldStatusChecker`, `CalcWeatherScore` |
| `src/battle_util.c` | `CanSetNonVolatileStatus` chain, `GetBattlerTypes`, `RemoveBattlerType` |
| `src/data/trainers.h` | Per-trainer `aiFlags` |
| `tools/verify_data.py` | Data integrity checker (Fairy type, P/S split, TMs) |
| `tools/audit_move_engine.py` | Pre-flight checker for struct expansion |
| `tools/migrate_volatiles.py` | Python migration script for status2 → struct Volatiles |
| `tools/migrate_types.py` | Python migration script for type1/type2 → types[3] |
| `tools/port_ai_scoring.py` | Python extraction tool for AI scoring functions |

---

## Battle AI — Quick Reference

ASM AI VM fully removed. C-based RHH-faithful dispatch table.

**Type Effectiveness:** Use the `0, 1, 2, 3` multiplier enums defined in `include/battle_ai_util.h`. The legacy FRLG `AI_EFFECTIVENESS_x2` (80/40/20) macros have been permanently deleted to match the `pokeemerald-expansion` architecture.

**Smart switching:** add `AI_SCRIPT_SMART_SWITCHING` to trainer `aiFlags` in `src/data/trainers.h`.
**New move effect AI:** add `case EFFECT_XYZ:` in `AI_CheckBadMove()` / `AI_CheckViability()` in `src/battle_ai_main.c`.

Full switching logic: `docs/battle_ai_architecture.md`

---

## Adding New Moves — Pipeline

1. Ensure the `preproc` tool parses any new `.s` keywords
2. Add move effect handler in `battle_script_commands.c` / `data/battle_scripts_*.s`
3. Add AI logic in `battle_ai_main.c`
4. Port native animation from RHH to `data/battle_anim_scripts.s` (including porting missed macros to `asm/macros/battle_anim_script.inc` and `SpriteTemplate`s to `src/battle_anim_new.c`)
5. Mark move as implemented in `docs/MISSING_GEN4_MOVES.md`

---

## Code Patterns

### Learnset Data Access

```c
// Iteration
for (i = 0; gLevelUpLearnsets[species][i].move != LEVEL_UP_END; i++) {
    u16 move  = gLevelUpLearnsets[species][i].move;
    u16 level = gLevelUpLearnsets[species][i].level;
}

// Array terminator in learnset data files
LEVEL_UP_END_ENTRY   // expands to { LEVEL_UP_END, 0 }
```

### additionalEffects Usage

To give a move multiple secondary effects, use the `ADDITIONAL_EFFECTS(...)` macro in `src/data/moves_info.h`. The old `secondaryEffectChance` field becomes `0` on converted moves to avoid double-triggering.

```c
[MOVE_LAVA_PLUME] = {
    .effect = EFFECT_HIT,
    .power  = 80,
    // ...other fields...
    .secondaryEffectChance = 0,  // must be 0 when additionalEffects is used
    ADDITIONAL_EFFECTS(
        {
            .moveEffect = MOVE_EFFECT_BURN,
            .chance     = 30,
        }
    ),
},

// Self-targeting effect (e.g. Overheat's SpAtk drop on the user):
ADDITIONAL_EFFECTS(
    {
        .moveEffect = MOVE_EFFECT_SP_ATK_MINUS_2,
        .self       = TRUE,
        .chance     = 0,  // guaranteed
    }
),
```

Helpers: `MoveHasAdditionalEffect(move, effect)`, `MoveHasAdditionalEffectSelf(move, effect)`, `CalcSecondaryEffectChance(battler, &effect)`, `HasMoveWithAdditionalEffect(battlerId, effect)` (AI).

---

## RHH Convergence Tracker

### Already Matching RHH

`gBattlerAttacker`, `gBattlerTarget`, `gCurrentMove`, `gBattleMons`, `MAX_MON_MOVES`, `struct AdditionalEffect`, `ADDITIONAL_EFFECTS()`, `MoveHasAdditionalEffect*()`, `EFFECT_*`, `MOVE_EFFECT_*`, `struct MoveInfo` (was `BattleMove`), `gMovesInfo` (was `gBattleMoves`), `DAMAGE_CATEGORY_*` (was `SPLIT_*`), `AI_FLAG_*` (same bits as legacy `AI_SCRIPT_*`), `struct Volatiles` (replaces `status2`/`gStatuses3`), `types[3]` (replaces `type1`/`type2`/`unknown`)

### Completed Renames

| Old | New | Scope |
|---|---|---|
| `struct BattleMove` | `struct MoveInfo` | 7 files |
| `gBattleMoves` | `gMovesInfo` | 29 files, 246 occ |
| `SPLIT_PHYSICAL/SPECIAL/STATUS` | `DAMAGE_CATEGORY_*` | 14 files, 891 occ |

### Remaining Divergences

| Current FireRed | RHH | Change Type | Scope | Status |
|---|---|---|---|---|
| `MOVE_TARGET_*` bitmask `#define`s | `TARGET_*` sequential `enum` | Values + comparison semantics | 911 occ, 12 files | Phase D (next) |
| `gBattleMoveDamage` (single `s32`) | `moveDamage[MAX_BATTLERS_COUNT]` in struct | Global → per-battler array | 232 occ, deep engine refactor | Phase E (future) |
| `u8 gBattlerAttacker` | `enum BattlerId gBattlerAttacker` | Type safety (u8 → enum) | Type change only | Low |
| `bool8` returns | `bool32` returns | Width change | Function signatures | Low |
| `sBattler_AI` | Various AI locals | AI refactoring | When porting AI | Future |

---

## Detailed Phase Logs

<details>
<summary><strong>Move Engine Phases 1–5</strong></summary>

### Phase 1–2: Struct Expansion

#### `struct MoveInfo` (`include/pokemon.h`)
- `effect`: `u8` → `u16` — allows >255 effect IDs
- `target`: `u8` → `u16` — expanded to fit Gen 9 flags (e.g. `MOVE_TARGET_ALL_BATTLERS` = 288)
- `flags` bitfield removed — replaced with 7 named fields:
  - `makesContact`, `ignoresProtect`, `mirrorMoveAffected`, `ignoresKingsRock`
  - `soundMove`, `snatchAffected`, `magicCoatAffected`
- Added: `criticalHitStage` (u8:2), `strikeCount` (u8:4), `argument` (u32), `recoil` (u8%)
- **Phase 3:** Added `numAdditionalEffects` (u8:2) + `additionalEffects[]` pointer for multi-secondary-effect support

#### `struct LevelUpMove` (`include/pokemon.h`)
- Was: packed 16-bit `(level << 9 | moveId)` — capped move IDs at 511
- Now: `{ u16 move; u16 level; }` — no move ID limit

#### Sentinel / Constants (`include/constants/pokemon.h`)
- `LEVEL_UP_END`: `0xFF` → `0xFFFF`
- `LEVEL_UP_END_ENTRY`: new macro `{ LEVEL_UP_END, 0 }` for array terminators
- `FLAG_*` defines: **removed** — see comment block in `constants/pokemon.h` for mapping
- `LEVEL_UP_MOVE_LV`, `LEVEL_UP_MOVE_ID`: **removed**

#### Files Updated (Phases 1–2)
| File | Change |
|---|---|
| `src/data/battle_moves.h` | All 355 entries: `.flags`/`FLAG_*` → named fields |
| `src/data/pokemon/level_up_learnsets.h` | All 386 arrays: `u16[]` → `struct LevelUpMove[]` |
| `src/data/pokemon/level_up_learnset_pointers.h` | Pointer type: `u16*` → `struct LevelUpMove*` |
| `src/pokemon.c` | All bitmask decode → `.move`/`.level` field access |
| `src/battle_ai_main.c` | `u8` effect locals/tables → `u16`, `0xFFFF` sentinels |
| `src/battle_script_commands.c` | `.flags` accesses → named fields |
| `src/battle_util.c` | `.flags` accesses → named fields (6 sites) |
| `src/data/text/move_names.h` | 7 move names corrected to Gen 4+ spelling |

#### Move Name Corrections Applied
| Move | Was | Now |
|---|---|---|
| Vise Grip | `VICEGRIP` | `VISE GRIP` |
| Bubble Beam | `BUBBLEBEAM` | `BUBBLE BEAM` |
| Poison Powder | `POISONPOWDER` | `POISON POWDER` |
| Dragon Breath | `DRAGONBREATH` | `DRAGON BREATH` |
| Ancient Power | `ANCIENTPOWER` | `ANCIENT POWER` |
| Smelling Salt | `SMELLINGSALT` | `SMELLING SALT` |
| Feather Dance | `FEATHERDANCE` | `FEATHER DANCE` |

### Phase 5: Unified `moves_info.h`

Merged `move_names.h`, `move_descriptions.c`, and `battle_moves.h` into a single `src/data/moves_info.h` (6400+ lines). Adding a new move now requires editing only this one file (3 sections within it: name, description, stats).

`src/move_descriptions.c` is now the sole compilation unit — it includes the necessary headers then `#include "data/moves_info.h"`. The old `#include` lines were removed from `src/data.c` and `src/pokemon.c`.

Battle anim scripts remain in `data/battle_anim_scripts.s` (out of scope for Phase 5).

</details>

<details>
<summary><strong>Phase 6: Animation Infrastructure</strong></summary>

Ported RHH battle animation infrastructure to support Gen 4+ moves:

- **Opcodes 0x30–0x34**: Multi-target animation macros + C handlers
- **`gBattleAnims_General` realigned**: 56 entries matching RHH indexing (was 28)
- **Constants**: 116 new `ANIM_TAG_*` (289–404), 55 new `BG_*` (27–81)
- **Graphics**: 928 files imported (sprites, backgrounds, stat_change)
- **INCBINs**: 376 INCBIN + extern declarations in `graphics.c`/`graphics.h`
- **Data tables**: 125 PicTable + 127 PaletteTable entries registered
- **`battle_anim_new.c`**: 9,523 lines ported (Gen 4+ sprite templates + callbacks)
- **Global Anim Refs**: Un-static'd 154 animation handlers/arrays across `battle_anim_*.c` and manually stubbed 3 missing arrays for Gen 8 (DreepyMissile) and Gen 3 (LusterPurge) to satisfy linker requirements

Compat aliases added: `ANIM_TAG_POKEBLOCK` → `ANIM_TAG_SAFARI_BAIT`, `B_ANIM_BAIT_THROW`/`B_ANIM_FOCUS_BAND`.

</details>

<details>
<summary><strong>Phases 7–10: Gen 4+ Moves & Tooling</strong></summary>

### Phase 7: Gen 4+ Moves — In Progress

Currently ported moves are tracked in [`docs/NEW_MOVES_LIST.md`](NEW_MOVES_LIST.md). First and second batches of Gen 4+ moves added (Roost, Confide, Round, Captivate, Tera Blast, Giga Impact, Bulldoze, Trailblaze, Work Up, Power-Up Punch, Zen Headbutt). Moves up to **MOVE_POISON_JAB** (364) have had their base animations ported to prevent crashes.

### Phase 8: `CMD_ARGS()` Macro Refactor

The battle script command interpreter has been upgraded to properly accept exact RHH macro syntax (e.g. `tryhealhalfhealth BS_TARGET, BattleScript_AlreadyAtFullHp` instead of `tryhealhalfhealth BattleScript_AlreadyAtFullHp, BS_ATTACKER`).
- `asm/macros/battle_script.inc` definitions rewritten to closely match RHH's `battler` first conventions
- `src/battle_script_commands.c` now has RHH's `CMD_ARGS()` struct unpacking infrastructure
- `data/battle_scripts_1.s` physical updates completed for applicable swapped argument macros (`tryhealhalfhealth`)

### Phase 8.5: Gen 4-9 Moves Data Synchronization

All 927 Moves from Generation 9 (up to Tera Starstorm) are now perfectly imported into `include/constants/moves.h` and `src/data/moves_info.h` with their RHH baseline properties. Unimplemented functional effects are safely stubbed to `EFFECT_HIT` with structurally padded placeholders in `data/battle_anim_scripts.s`.

### Phase 9: Legacy Effect Macro Purge

The move engine has been completely decoupled from FireRed's legacy switch-case structure and synced 100% with the RHH Gen 9 `.additionalEffects` array system.
- Replaced dead heuristic dependencies (`EFFECT_HIGH_CRITICAL`, `EFFECT_RECHARGE`, `EFFECT_FAKE_OUT`, `EFFECT_ALWAYS_HIT`) with native evaluations like `criticalHitStage` and `accuracy == 0`
- Upgraded `struct MoveInfo` with `thawsUser`, `onChargeTurnOnly`, and `criticalHitStage`
- Perfectly synced `include/constants/battle_move_effects.h` with RHH
- Decoupled `gBattleScriptsForMoveEffects` into scalable C table: `src/data/battle_scripts_for_move_effects.h`

### Phase 10: preproc Compiler Upgrade

Upgraded the FireRed `preproc` compiler tool using RHH's extended `preproc` source.
- FireRed assembly files can now natively parse RHH's Python-style named keyword arguments (e.g. `x=-10`, `y=0`)
- **Bug Fix Note**: Applied custom regex word-boundary checks (`IsIdentifierChar`) to the `CFile::CheckIdentifier` scanner inside `tools/preproc/c_file.cpp`

</details>

<details>
<summary><strong>Phases 11–13: Compiler Fixes, Battle Scripts, Faithfulness Audit</strong></summary>

### Phase 11: Modern Compiler Syntax and UB Fixes

Zero warnings under modern `arm-none-eabi-gcc` 15+ by natively porting fixes from RHH.
- **`-Waggressive-loop-optimizations`**: Flattened `gCanvasPixels` to 1D pointer matrix. Stripped `-1` OOB access in `battle_interface.c` (`ballIconSpritesIds`)
- **`-Wattribute-alias`**: Explicit wrapper functions for incompatible type signature aliases (`GetMonData2`, `GetBoxMonData2`)
- **`-Wstringop-overflow`**: Safely guarded struct bounds in `SetBoxMonData` (`MON_DATA_PP1`...`PP4`) without pragmas

### Phase 12: Battle Script Effect Hooks Restoration

Restored 1:1 functional parity with RHH for missing battle scripts that were previously stubbed to `EFFECT_HIT`.
- **Two-Turn Attacks:** Hooked up `EFFECT_SEMI_INVULNERABLE` and `EFFECT_SOLAR_BEAM` to their respective assembly scripts
- **Missing Stat Modifiers:** Ported `EFFECT_SPECIAL_ATTACK_DOWN` (Confide), `EFFECT_SPEED_UP`, `EFFECT_SPECIAL_ATTACK_DOWN_2` (Eerie Impulse)

### Phase 13: RHH Faithfulness Audit & Move Ban System

Comprehensive audit of all ported Gen 4+ moves against RHH reference.

**EFFECT_RECOIL / EFFECT_STRUGGLE:**
- Added both to `battle_move_effects.h`, mapped to `BattleScript_EffectHit`
- Changed 12 recoil moves from `EFFECT_HIT` to `EFFECT_RECOIL`
- Changed Struggle to `EFFECT_STRUGGLE` + `ADDITIONAL_EFFECTS({ .moveEffect = MOVE_EFFECT_RECOIL_HP_25, .self = TRUE })`

**New MOVE_EFFECT constants** (`include/constants/battle.h`):
- `MOVE_EFFECT_RECOIL_HP_25` (63) — Struggle's Gen 4+ HP%-based recoil
- `MOVE_EFFECT_ROUND` (61) — structural port for Round
- `MOVE_EFFECT_TERA_BLAST` (62) — structural port for Tera Blast

**`ignoresSubstitute` field:** Applied to all 31 sound-based moves. Engine check in `Cmd_attackcanceler` sets `HITMARKER_IGNORE_SUBSTITUTE`.

**`metronomeBanned` field:** Applied to 153 moves. Engine check in `Cmd_metronome`.

**Additional ban flags (all matching RHH):**
- `mimicBanned` (24 moves) — engine check in `IsMoveUncopyableByMimic()`
- `copycatBanned` (49 moves) — data-only (Copycat not yet implemented)
- `assistBanned` (47 moves) — engine check in Assist handler
- `sleepTalkBanned` (37 moves) — engine check in `Cmd_trychoosesleeptalkmove()`
- `instructBanned` (51 moves) — data-only (Instruct not yet implemented)
- `encoreBanned` (13 moves) — engine check in `Cmd_trysetencore()`
- `gravityBanned` (10 moves) — data-only
- `meFirstBanned` (17 moves) — data-only
- `parentalBondBanned` (9 moves) — data-only
- `skyBattleBanned` (41 moves) — data-only
- `sketchBanned` (3 moves) — engine check in `Cmd_copymovepermanently()`
- `dampBanned` (4 moves) — data-only

**Deprecated:** Removed `sMovesForbiddenToCopy` hardcoded array and `IsInvalidForSleepTalkOrAssist()` helper.

**Remaining follow-ups** (wire engine checks when effects are implemented):
- `copycatBanned` — when `EFFECT_COPYCAT` is implemented
- `instructBanned` — when `EFFECT_INSTRUCT` is implemented
- `gravityBanned` — when Gravity field effect handler is implemented
- `meFirstBanned` — when Me First handler is implemented
- `dampBanned` — when RHH-style `CancelerExplodingDamp` is ported

</details>

<details>
<summary><strong>Battle AI Infrastructure (Tiers A–J)</strong></summary>

### Completed AI Infrastructure Ports

**Core infrastructure:**
- `GetMoveAdditionalEffectCount()` / `GetMoveAdditionalEffectById()` — inline in `include/pokemon.h`
- `MoveEffectIsGuaranteed()` / `MoveIsAffectedBySheerForce()` / `IsSheerForceAffected()` — `src/battle_util.c`
- `IsBattlerGrounded()` — `src/battle_util.c` (Gen 3 subset; Gen 4+ #ifdef'd)
- `struct AiLogicData` — `include/battle.h` (full RHH struct, heap-allocated)
- `struct SimulatedDamage` + `simulatedDmg[4][4][4]` field
- `.sheerForceOverride` field added to `struct AdditionalEffect`

**Enums and defines:**
- `enum AIScore`, `enum StatChange`, `ADJUST_SCORE`/`ADJUST_SCORE_PTR` — `include/battle_ai_main.h`
- `enum ConsiderPriority`, `enum DamageCalcContext`, `enum AiConsiderEndure` — `include/battle_ai_util.h`
- `AI_IS_FASTER`/`AI_IS_SLOWER`, `UNKNOWN_NO_OF_HITS` — `include/battle_ai_main.h`
- `AI_FLAG_*` constants — `include/constants/battle_ai.h`
- `BATTLE_TYPE_TWO_OPPONENTS/INGAME_PARTNER/TOWER_LINK_MULTI` — `include/constants/battle.h`

**Speed/priority helpers:**
- `GetBattlerTotalSpeedStat()` / `GetBattleMovePriority()` — `src/battle_main.c`
- `AI_WhoStrikesFirst()` / `AI_IsFaster()` / `AI_IsSlower()` — 5-param RHH signatures

**Damage calculation:**
- `SetBattlerAiData()` — populates simulatedDmg
- `AI_GetDamage()` (static) / `GetNoOfHitsToKO()` / `GetNoOfHitsToKOBattlerDmg()` / `CanEndureHit()` / `GetNoOfHitsToKOBattler()` / `NoOfHitsForTargetToFaintBattler()`

**Utility helpers:**
- `BattlerHasAi()` / `IsAiFlagPresent()` / `IsAiBattlerAware()` / `GetMovesArray()` / `HasMoveWithEffect()`
- `IsBattlerAlive()` / `GetBattlerParty()` / `GetSideParty()` — inlines in `include/battle.h`
- `HasTwoOpponents()` / `HasPartner()` — `src/battle_ai_util.c`
- `DoesSubstituteBlockMove()` / `CanAIFaintTarget()` / `CanTargetFaintAi()` — `src/battle_ai_util.c`

**Stat scoring:**
- `GetStatBeingChanged()` / `GetStagesOfStatChange()` — stat change switches
- `GetBattlerSecondaryDamage()` + 6 sub-helpers / `DoesAbilityRaiseStatsWhenLowered()`
- `IncreaseStatDownScore()` (72 lines) / `IncreaseStatUpScore()` / `IncreaseStatUpScoreContrary()`

**Status scoring (Tier H):**
- `IsNonVolatileStatusBlocked()` / `IsSafeguardProtected()` — `src/battle_util.c`
- `CanSetNonVolatileStatus()` / `CanBePoisoned()` / `CanBeBurned()` / `CanBeParalyzed()` / `CanBeSlept()` / `IsUsableWhileAsleepEffect()` — `src/battle_util.c`
- 12 static AI helpers for status checking — `src/battle_ai_util.c`
- `IncreasePoisonScore()` / `IncreaseBurnScore()` / `IncreaseParalyzeScore()` / `IncreaseSleepScore()` / `IncreaseConfusionScore()`

**AI CalcAdditionalEffectScore (Tier J):**
- `GetIncomingMove`, `HasPartnerIgnoreFlags`, `HasBattlerSideMoveWithEffect`
- `DoesBattlerIgnoreAbilityChecks`, `AI_WeatherHasEffect`, `AI_GetWeather`
- `BattlerWillFaintFromWeather`, `BattlerWillFaintFromSecondaryDamage`
- `IsAdditionalEffectBlocked`, `ShouldTryToFlinch`, `ShouldTrap`
- `GetAIEffectGroup` / `GetAIEffectGroupFromMove` / `HasMoveWithAIEffect` / `HasBattlerSideMoveWithAIEffect`
- `CanLowerStat`, `ShouldSetWeather`, `ShouldClearWeather`, `ShouldSetFieldStatus`, `ShouldClearFieldStatus`
- `ShouldSetScreen`, `ShouldCureStatus`, `AI_TryToClearStats`, `AI_ShouldCopyStatChanges`
- `AI_ShouldSetUpHazards`, `AI_GetBattlerMoveTargetType`, `HasMoveWithLowAccuracy`
- `AI_CalcAdditionalEffectScore` (static, in `src/battle_ai_main.c`)

**AI constants/infrastructure added:**
- `EFFECT_RAPID_SPIN`, `EFFECT_WEATHER`, `EFFECT_WEATHER_AND_SWITCH`, `EFFECT_STEEL_ROLLER`, `EFFECT_ICE_SPINNER`, `EFFECT_OVERWRITE_ABILITY` — `battle_move_effects.h`
- `MOVE_EFFECT_FEINT`, `MOVE_EFFECT_INCINERATE`, `MOVE_EFFECT_SALT_CURE`, `MOVE_EFFECT_GRAVITY`, terrain MOVE_EFFECTs, `MOVE_EFFECT_DEFOG`, `MOVE_EFFECT_HAZE`, `MOVE_EFFECT_REFLECT`, `MOVE_EFFECT_LIGHT_SCREEN`, `MOVE_EFFECT_TORMENT_SIDE` — `constants/battle.h`
- `AI_EFFECT_*` constants + `LOW_ACCURACY_THRESHOLD` — `include/battle_ai_util.h`

**Weather/Field Status AI (Tier J Supplement):**
- `WeatherChecker`, `FieldStatusChecker`, `CalcWeatherScore` — `src/battle_ai_field_statuses.c`
- `DoesAbilityBenefitFromWeather`, `BenefitsFromSun/Rain/Sandstorm/Hail`
- `IsLightSensitiveMove`, `HasLightSensitiveMove`
- `ShouldCureStatusInternal`, `ShouldCureStatus`, `ShouldCureStatusWithItem`
- `IsTargetingPartner`, `HasThawingMove`, `DoesBattlerBenefitFromAllVolatileStatus`
- `IsWeatherActive`, `HasDamagingMoveOfType`, `HasMoveWithFlag`, `IsBattle1v1`
- `HasNonVolatileMoveEffect`, `HasBattlerSideMoveWithAdditionalEffect`

**`struct MoveInfo` additions for weather helpers:**
- `alwaysHitsInRain:1`, `accuracy50InSun:1`, `alwaysHitsInHailSnow:1` fields
- Inline helpers: `MoveAlwaysHitsInRain`, `MoveHas50AccuracyInSun`, `MoveAlwaysHitsInHailSnow`, `IsMoveGravityBanned`
- Inline helpers: `MoveThawsUser`, `GetMoveType`

**Field status infrastructure:**
- `struct FieldTimer` + `gFieldStatuses`/`gFieldTimers` globals
- `ABILITY_SOLAR_POWER = 94`
- `enum FieldEffectOutcome`, `enum WeatherState`, `enum BattleWeather`
- `B_WEATHER_ICY_ANY`, `B_WEATHER_DAMAGING_ANY`, `B_WEATHER_PRIMAL_ANY` composite flags
- `MoveFlag` typedef
- `STATUS_FIELD_*` bit positions corrected to match RHH exactly (12 flags)
- `AI_IsTerrainActive()` / `AI_IsTrickRoomActive()`
- `BenefitsFromGravity()` / `BenefitsFromTrickRoom()` — 1:1 from RHH

**Audit fixes applied:**
- Removed dead `#ifdef AI_FLAG_PREDICT_MOVE` / `#ifdef AI_FLAG_PREDICT_SWITCH`
- Fixed `EFFECT_POISON_GAS` → `EFFECT_POISON` in `PartnerMoveEffectIsStatusSameTarget`
- Fixed `GetMoveTarget()` → `GetMoveTarget(move, 0)` in `DoesPartnerHaveSameMoveEffect`
- `#ifdef ABILITY_SIMPLE` in `IncreaseStatUpScoreInternal` is CORRECT (Gen 4+, not in Gen 3)

</details>

<details>
<summary><strong>Phase B: struct Volatiles Migration</strong></summary>

Replaced `u32 status2` in `struct BattlePokemon` with `struct Volatiles volatiles` (100+ named bitfields from RHH's `VOLATILE_DEFINITIONS` X-macro). Removed `gStatuses3[MAX_BATTLERS_COUNT]` global. All ~370 call sites migrated.

Key files/changes:
- `include/config/battle.h` (NEW) — `B_*` timer constants for bitfield widths
- `include/constants/battle.h` — `enum BattlerId`, `enum SemiInvulnerableState`, `VOLATILE_DEFINITIONS`, `enum VolatileId`, `LEECHSEEDED_BY()`
- `include/pokemon.h` — `struct Volatiles` (UNPACK_VOLATILE_STRUCT macros), `struct BattlePokemon.volatiles`
- `include/battle.h` — `struct BattlerState` with `switchIn:1` (replaces STATUS3_INTIMIDATE_POKES/TRACE), added `battlerState[4]` to `struct BattleStruct`
- `src/battle_main.c` — removed `gStatuses3` EWRAM allocation
- `include/battle_controllers.h` + `src/battle_controllers.c` — `BtlController_EmitStatusIconUpdate` signature: removed `status2` param
- `tools/migrate_volatiles.py` — Python migration script (323 lines transformed across 9 files)
- Build: clean. Verify: 71/0/0.

</details>

<details>
<summary><strong>Phase C: types[3] Migration</strong></summary>

Replaced `u8 type1; u8 type2; u8 unknown;` in `struct BattlePokemon` with `u8 types[3]` array matching RHH architecture (3-slot type system: [0]=base type1, [1]=base type2, [2]=third type defaulting to TYPE_MYSTERY).

Key changes:
- `include/pokemon.h` — `struct BattlePokemon`: `types[3]` (same memory layout/offsets)
- `include/battle.h` — Macros: `IS_BATTLER_OF_TYPE` (checks all 3 slots via `GetBattlerTypes`), `SET_BATTLER_TYPE` (sets all 3), `RESTORE_BATTLER_TYPE` (restores from SpeciesInfo), `IS_BATTLER_TYPELESS` (all TYPE_MYSTERY check)
- `include/battle.h` — Declarations: `GetBattlerTypes(u8 battlerId, u8 types[3])`, `RemoveBattlerType(u8 battler, u8 type)`
- `src/battle_util.c` — Replaced `GetBattlerType1`/`GetBattlerType2` with `GetBattlerTypes` (Roost-aware, fills 3-element array) + added `RemoveBattlerType` (iterates all 3 slots)
- 86 automated changes via `tools/migrate_types.py` across 6 files + 4 manual PokemonSubstruct fixups
- Zero remaining `.type1`/`.type2` or `GetBattlerType1`/`GetBattlerType2` references
- Build: clean. Verify: 71/0/0.

</details>

<details>
<summary><strong>EWRAM Optimization & Misc Quality of Life</strong></summary>

**EWRAM Option 1 COMPLETE:** `sMapTilesBackup` → heap.
- `static EWRAM_DATA u8 sMapTilesBackup[BG_CHAR_SIZE]` (16KB) → `static u8 *sMapTilesBackup`
- `SaveMapTiles()`: `AllocZeroed(BG_CHAR_SIZE)` before DMA copy
- `FreeMapTilesBackup()`: new exported function — called one state after `RestoreMapTiles` in both callers (help_system_util.c state 7, save_failed_screen.c state 8)
- EWRAM: 98.88% → **92.65%** (16,384 bytes freed; 19,320 bytes now free)

*Note: EWRAM Option 2 (`gDecompressionBuffer`) was skipped — Mystery Gift uses it as executable memory, and FR-exclusive overlay systems enforce hardcoded 16KB framebuffer offsets which lack RHH equivalents.*

**Instant & Faster Text Speed:**
- Added `OPTIONS_TEXT_SPEED_INSTANT 3` to `include/constants/global.h`
- Added `gText_TextSpeedInstant` string `"INSTANT"` in `src/strings.c`
- `src/option_menu.c`: bumped text speed item count 3→4
- `src/new_menu_helpers.c`: `sTextSpeedFrameDelays[OPTIONS_TEXT_SPEED_INSTANT] = 1` (not 0 — see note), `IsTextSpeedInstant()` helper
- `src/text.c`: `sWindowVerticalScrollSpeeds` entry, delay-clear condition in `RenderText()`
- `src/text_printer.c`: `RunTextPrinters()` repeat-loop matching RHH pattern, breaking on `RENDER_UPDATE`/`RENDER_FINISH`
- **Critical design note:** Instant delay must be **1** (not 0). FireRed's `AddTextPrinter` treats `speed==0` as "render all text and deactivate printer immediately" — this skips `\p` prompts. RHH uses delay=1 + per-frame render loop.

**Auto-lowercase naming screen:** Ported Gen 6+ `SwapKeyboardToLowerAfterFirstCapitalLetter`.

</details>

---

## Next Sessions (Architecture-First Order)

1. **Phase D** — `MOVE_TARGET_*` → `TARGET_*` enum (911 occ, Python script)
2. **Phase E** — `gBattleMoveDamage` → `moveDamage[MAX_BATTLERS_COUNT]` per-battler (232 occ)

---

## Active Test/Debug Changes

*None currently active.*

---

## Research Docs (`docs/research/`)

| File | Contents |
|---|---|
| `move_engine_upgrade_research.md` | Struct gap analysis + 5-phase port plan |
| `adding_new_moves_workflow.md` | Step-by-step: every file to touch when adding a move |
| `firered_vs_emerald_structure.md` | Deep structural diff: FireRed vs RHH |
| `emerald_expansion_move_structure.md` | RHH field-by-field mapping |
| `missing_items.md` | Gen 4+ items not yet in FireRed |
| `missing_egg_moves.md` | Egg moves not yet in FireRed |
| `battle_ai_migration_research.md` | AI ASM→C migration research log |
| `battle_animation_systems.md` | FireRed vs RHH animation system comparison + porting guide |
| `ai_additional_effects_port_plan.md` | Plan for porting AI_CalcAdditionalEffectScore from RHH |
