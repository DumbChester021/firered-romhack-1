# FireRed Romhack — Zero-Context Continuation Guide

> **Read this first.** Single source of truth for continuing work on this project.

---

## What This Is

A **FireRed decompilation romhack** forked from [pret/pokefirered](https://github.com/pret/pokefirered) with Gen 6+ mechanical upgrades. Codebase: `/mnt/data/Github/prototype/firered-romhack-1`. Build: `make -j$(nproc)`.

Reference codebase for porting: **pokeemerald-expansion (RHH)** at `/mnt/data/Github/rh-hideout/pokeemerald-expansion`.

**Active branch:** `feature-AI-upgrade`

---

## What's Already Done (Shipped)

| Feature | Status | Notes |
|---|---|---|
| **Fairy Type** | ✅ Done | 19th type, full Gen 6 table, 18 species, graphics |
| **Physical/Special Split** | ✅ Done | Per-move `category` field, all 355 moves assigned, UI icons |
| **Running Shoes from start** | ✅ Done | No item needed, works indoors |
| **Reusable TMs** | ✅ Done | Infinite-use (Gen 5+), sell/dupe blocked |
| **Overworld Poison** | ✅ Done | Configurable via `OW_POISON_DAMAGE` in `include/config.h` |
| **pret Bug Fixes** | ✅ Done | All `#ifdef BUGFIX` / `#ifdef UBFIX` enabled (~25 bugs) |
| **Battle AI: C Port** | ✅ Done | ASM VM replaced with C dispatch table (9 flags) |
| **Battle AI: Smart Switching** | ✅ Done | Faithful RHH port, Gen 3 mechanics |
| **Wild AI Initialization Fix** | ✅ Done | Ported RHH scaling AI logic to fix empty trainer flags for wild battles |
| **Modern compiler default** | ✅ Done | `arm-none-eabi-gcc` default, no `MODERN=1` needed |
| **Move Engine Overhaul (Phase 1–12)** | ✅ Done | Structural arrays, additionalEffects, modern flags, macros |
| **Animation Infrastructure (Phase 1)** | ✅ Done | Opcodes 0x30–0x34, `GetAnimBattlerId`, `gAnimMoveIndex` |
| **Gen 4+ Moves (Batches 1 & 2)** | ✅ Done | Roost, Confide, Round, Captivate, Tera Blast, Giga Impact, Bulldoze, Trailblaze, Work Up, Power-Up Punch, Zen Headbutt |
| **preproc Tool Upgrade** | ✅ Done | C++ compiler tool upgraded for keyword args (`x=0`) |
| **Battle Script Effect Hooks** | ✅ Done | Restored Gen 1 functionality for Two-Turn moves and basic stat modifications. |

---

## Move Engine Overhaul — Completed

**Branch:** `feature-AI-upgrade` (commits after `1ef3ccfb1`)

### What Changed

#### `struct BattleMove` (`include/pokemon.h`)
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

#### Files Updated
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

### How to Access Learnset Data (New Pattern)
```c
// Iteration
for (i = 0; gLevelUpLearnsets[species][i].move != LEVEL_UP_END; i++) {
    u16 move  = gLevelUpLearnsets[species][i].move;
    u16 level = gLevelUpLearnsets[species][i].level;
}

// Array terminator in learnset data files
LEVEL_UP_END_ENTRY   // expands to { LEVEL_UP_END, 0 }
```

### Phase 5: Unified `moves_info.h` — Complete

Merged `move_names.h`, `move_descriptions.c`, and `battle_moves.h` into a single `src/data/moves_info.h` (6400+ lines). Adding a new move now requires editing only this one file (3 sections within it: name, description, stats).

`src/move_descriptions.c` is now the sole compilation unit — it includes the necessary headers then `#include "data/moves_info.h"`. The old `#include` lines were removed from `src/data.c` and `src/pokemon.c`.

Battle anim scripts remain in `data/battle_anim_scripts.s` (out of scope for Phase 5).

### Phase 6: Animation Infrastructure — Complete

Ported RHH battle animation infrastructure to support Gen 4+ moves:

- **Opcodes 0x30–0x34**: Multi-target animation macros + C handlers
- **`gBattleAnims_General` realigned**: 56 entries matching RHH indexing (was 28)
- **Constants**: 116 new `ANIM_TAG_*` (289–404), 55 new `BG_*` (27–81)
- **Graphics**: 928 files imported (sprites, backgrounds, stat_change)
- **INCBINs**: 376 INCBIN + extern declarations in `graphics.c`/`graphics.h`
- **Data tables**: 125 PicTable + 127 PaletteTable entries registered
- **`battle_anim_new.c`**: 9,523 lines ported (Gen 4+ sprite templates + callbacks)
- **Global Anim Refs**: Un-static'd 154 animation handlers/arrays across `battle_anim_*.c` and manually stubbed 3 missing arrays for Gen 8 (DreepyMissile) and Gen 3 (LusterPurge) to satisfy linker requirements.

Compat aliases added: `ANIM_TAG_POKEBLOCK` → `ANIM_TAG_SAFARI_BAIT`, `B_ANIM_BAIT_THROW`/`B_ANIM_FOCUS_BAND`.

### Phase 7: Gen 4+ Moves — In Progress

Currently ported moves are tracked in [`docs/NEW_MOVES_LIST.md`](NEW_MOVES_LIST.md). First and second batches of Gen 4+ moves added (Roost, Confide, Round, Captivate, Tera Blast, Giga Impact, Bulldoze, Trailblaze, Work Up, Power-Up Punch, Zen Headbutt). Moves up to **MOVE_POISON_JAB** (364) have had their base animations ported to prevent crashes.

Pipeline for adding new moves:
1. Ensure the `preproc` tool parses any new `.s` keywords.
2. Add move effect handler in `battle_script_commands.c` / `data/battle_scripts_*.s`
3. Add AI logic in `battle_ai_main.c`
4. Port native animation from RHH to `data/battle_anim_scripts.s` (including porting missed macros to `asm/macros/battle_anim_script.inc` and `SpriteTemplate`s to `src/battle_anim_new.c`).
5. Mark move as implemented in `docs/MISSING_GEN4_MOVES.md`

### Phase 8: `CMD_ARGS()` Macro Refactor — Complete

The battle script command interpreter has been upgraded to properly accept exact RHH macro syntax (e.g. `tryhealhalfhealth BS_TARGET, BattleScript_AlreadyAtFullHp` instead of `tryhealhalfhealth BattleScript_AlreadyAtFullHp, BS_ATTACKER`).
- `asm/macros/battle_script.inc` definitions rewritten to closely match RHH's `battler` first conventions.
- `src/battle_script_commands.c` now has RHH's `CMD_ARGS()` struct unpacking infrastructure.
- `data/battle_scripts_1.s` physical updates completed for applicable swapped argument macros (`tryhealhalfhealth`).

### Phase 8.5: Gen 4-9 Moves Data Synchronization — Complete
All 927 Moves from Generation 9 (up to Tera Starstorm) are now perfectly imported into `include/constants/moves.h` and `src/data/moves_info.h` with their RHH baseline properties (Power, Accuracy, PP, Target, Category, Priority, Type) to ensure global index consistency. Unimplemented functional effects are safely stubbed to `EFFECT_HIT` with structurally padded placeholders in `data/battle_anim_scripts.s`. 

### Phase 9: Legacy Effect Macro Purge and Array Finalization — Complete
The move engine has been completely decoupled from FireRed's legacy switch-case structure and synced 100% with the RHH Gen 9 `.additionalEffects` array system.
- Replaced dead heuristic dependencies (`EFFECT_HIGH_CRITICAL`, `EFFECT_RECHARGE`, `EFFECT_FAKE_OUT`, `EFFECT_ALWAYS_HIT`) inside `battle_ai_main.c` and `battle_script_commands.c` with native evaluations like `criticalHitStage` and `accuracy == 0`.
- Upgraded `struct BattleMove` configuration with `thawsUser`, `onChargeTurnOnly`, and `criticalHitStage` inside `include/pokemon.h`.
- Perfectly synced `include/constants/battle_move_effects.h` with RHH.
- Decoupled `gBattleScriptsForMoveEffects` from `data/battle_scripts_1.s` into a highly scalable C table: `src/data/battle_scripts_for_move_effects.h`.

### Phase 10: preproc Compiler Upgrade — Complete
Upgraded the FireRed `preproc` compiler tool using RHH's extended `preproc` source.
- FireRed assembly files can now natively parse RHH's Python-style named keyword arguments (e.g. `x=-10`, `y=0`).
- This allows 1:1 copy-pasting of complex animation macros (like `create_basic_hitsplat_sprite`) from Emerald to FireRed.
- **Bug Fix Note**: Applied custom regex word-boundary checks (`IsIdentifierChar`) to the `CFile::CheckIdentifier` scanner inside `tools/preproc/c_file.cpp` to prevent it from maliciously slicing identifiers like `BP_ACTION_DUMMY` during C compilation.

### Phase 11: Modern Compiler Syntax and UB Fixes — Complete
The codebase has been updated to perfectly compile with zero warnings under modern `arm-none-eabi-gcc` 15+ by natively porting fixes from RHH.
- **`-Waggressive-loop-optimizations`**: Flattened `gCanvasPixels` in `image_processing_effects.c` to a 1D pointer matrix to fix bounds checking errors. Stripped decompilation artifacts triggering index `-1` OOB access in `battle_interface.c` (`ballIconSpritesIds`).
- **`-Wattribute-alias`**: Resolved incompatible 2-arg to 3-arg type signature aliases (`GetMonData2`, `GetBoxMonData2`) in `pokemon.c` by writing explicit wrapper functions.
- **`-Wstringop-overflow`**: Safely guarded struct bounds in `SetBoxMonData` (`MON_DATA_PP1`...`PP4`) natively without pragmas.

### Phase 12: Battle Script Effect Hooks Restoration — Complete
Restored 1:1 functional parity with RHH for missing battle scripts that were previously stubbed to `EFFECT_HIT`. 
- **Two-Turn Attacks:** Hooked up `EFFECT_SEMI_INVULNERABLE` and `EFFECT_SOLAR_BEAM` to their respective assembly scripts, ensuring moves like Fly, Dig, and Solar Beam correctly charge instead of striking instantly.
- **Missing Stat Modifiers:** Ported native assembly handlers for missing stat manipulations like `EFFECT_SPECIAL_ATTACK_DOWN` (Confide), `EFFECT_SPEED_UP`, and `EFFECT_SPECIAL_ATTACK_DOWN_2` (Eerie Impulse) into `data/battle_scripts_1.s` and correctly wired them in `src/data/battle_scripts_for_move_effects.h`.

---

## Key Files Reference

| File | Purpose |
|---|---|
| `include/config.h` | Feature toggles (`OW_POISON_DAMAGE`, etc.) |
| `include/constants/moves.h` | Move ID `#defines` + `MOVES_COUNT` |
| `include/constants/battle_move_effects.h` | `EFFECT_*` constants (214 effects, ends at `EFFECT_CAMOUFLAGE`) |
| `include/constants/battle_ai.h` | AI flag constants (`AI_SCRIPT_*`) |
| `include/constants/pokemon.h` | `LEVEL_UP_END` (0xFFFF), `LEVEL_UP_END_ENTRY`, `LEVEL_UP_MOVE` macro |
| `src/data/moves_info.h` | **Unified move data** — names, descriptions, stats (Phase 5) |
| `src/move_descriptions.c` | Compilation unit for `moves_info.h` |
| `src/data/pokemon/level_up_learnsets.h` | Level-up moves per species (`struct LevelUpMove[]`) |
| `src/data/pokemon/egg_moves.h` | Egg moves per species |
| `src/data/pokemon/tmhm_learnsets.h` | 64-bit TM/HM bitmask per species (6 slots left) |
| `src/data/party_menu.h` | `sTMHMMoves[]` table mapping TM slot → move |
| `data/battle_scripts_1.s` | Battle effect scripts (ASM macro language) |
| `src/battle_script_commands.c` | C handlers for battle script commands |
| `data/battle_anim_scripts.s` | Move animation scripts + `gBattleAnims_Moves` table |
| `asm/macros/battle_anim_script.inc` | Animation bytecode macros (53 opcodes, 0x00–0x34) |
| `src/battle_anim.c` | Animation script interpreter + launch + opcode handlers |
| `include/constants/battle_anim.h` | `ANIM_TAG_*`, `B_ANIM_*`, `BG_*` constants |
| `src/data/battle_anim.h` | Sprite/palette/background registration tables |
| `src/battle_ai_main.c` | All AI flag functions + `gAIFunctionTable` dispatch |
| `src/battle_ai_util.c` | AI utilities: damage calc, switching logic |
| `src/data/trainers.h` | Per-trainer `aiFlags` |
| `tools/verify_data.py` | Data integrity checker (Fairy type, P/S split, TMs) |
| `tools/audit_move_engine.py` | Pre-flight checker for struct expansion |

---

## Current Hard Limits

| Limit | Cap | Note |
|---|---|---|
| Move ID (learnsets) | **65534** (u16, -1 sentinel) | Effectively unlimited for Gen 1-3 |
| TM slots | **64** (64-bit bitmask) | 6 slots remaining |
| Move effects | **65535** (u16) | Phase 1 complete |
| Move flags | **unlimited** (named fields) | Phase 1 complete |
| Additional effects per move | **3** (2-bit field) | Phase 3 complete |

### Phase 3: additionalEffects Usage

To give a move multiple secondary effects, use the `ADDITIONAL_EFFECTS(...)` macro in `src/data/battle_moves.h`. The old `secondaryEffectChance` field becomes `0` on converted moves to avoid double-triggering.

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

New helpers available: `MoveHasAdditionalEffect(move, effect)`, `MoveHasAdditionalEffectSelf(move, effect)`, `CalcSecondaryEffectChance(battler, &effect)`, `HasMoveWithAdditionalEffect(battlerId, effect)` (AI).

---

## Battle AI — Current State

ASM AI VM fully removed. C-based RHH-faithful dispatch table.

**Type Effectiveness:** Use the `0, 1, 2, 3` multiplier enums defined in `include/battle_ai_util.h`. The legacy FRLG `AI_EFFECTIVENESS_x2` (80/40/20) macros have been permanently deleted to match the `pokeemerald-expansion` architecture.

**Smart switching:** add `AI_SCRIPT_SMART_SWITCHING` to trainer `aiFlags` in `src/data/trainers.h`.  
**New move effect AI:** add `case EFFECT_XYZ:` in `AI_CheckBadMove()` / `AI_CheckViability()` in `src/battle_ai_main.c`.

Full switching logic: `docs/battle_ai_architecture.md`

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

1. **Port, don't invent.** Cite the RHH source if porting.
2. **`FRLG_STUB`** = mechanic that exists in RHH but needs infrastructure not yet in FireRed.
3. **`GEN4_STUB`** = utility function returning neutral value, declared in header, real body later.
4. **No invented AI logic.** Trace to RHH or don't add it.
5. **Build must stay clean.** `make -j$(nproc) 2>&1 | grep "error:"` returns nothing.
6. **Active test/debug code** must be documented in `## Active Test/Debug Changes` in `README.md`.
7. **Named fields, not FLAG_*.** `FLAG_*` constants are removed. Use struct field names directly.

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
