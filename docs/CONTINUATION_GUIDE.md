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
| **Battle AI: C Port** | Phase 4 | All 9 AI flags ported from ASM to C | ✅ Done |
| Phase 4b | Smart switching — faithful RHH port + Gen 3 mechanics fully implemented | ✅ Done |
| Phase 4c | Gen 4+ AI Heuristics (Sucker Punch, Shell Smash, Tailwind, etc.) | ✅ Done |
| Phase 5 | Automated AI test framework (in-ROM DSL from RHH) | ⏳ Pending |9 prediction/setup heuristics |
| **Wild AI Initialization Fix** | ✅ Done | Ported RHH scaling AI logic to fix empty trainer flags for wild battles |
| **Modern compiler default** | ✅ Done | `arm-none-eabi-gcc` default, no `MODERN=1` needed |
| **Move Engine Overhaul (Phase 1–12)** | ✅ Done | Structural arrays, additionalEffects, modern flags, macros |
| **Animation Infrastructure (Phase 1)** | ✅ Done | Opcodes 0x30–0x34, `GetAnimBattlerId`, `gAnimMoveIndex` |
| **Gen 4+ Moves (Batches 1 & 2)** | ✅ Done | Roost, Confide, Round, Captivate, Tera Blast, Giga Impact, Bulldoze, Trailblaze, Work Up, Power-Up Punch, Zen Headbutt |
| **preproc Tool Upgrade** | ✅ Done | C++ compiler tool upgraded for keyword args (`x=0`) |
| **Battle Script Effect Hooks** | ✅ Done | Restored Gen 1 functionality for Two-Turn moves and basic stat modifications. |
| **RHH Faithfulness Audit** | ✅ Done | EFFECT_RECOIL, EFFECT_STRUGGLE, ignoresSubstitute, 13 ban flags (all RHH flags ported) |

---

## Move Engine Overhaul — Completed

**Branch:** `feature-AI-upgrade` (commits after `1ef3ccfb1`)

### What Changed

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
- Upgraded `struct MoveInfo` configuration with `thawsUser`, `onChargeTurnOnly`, and `criticalHitStage` inside `include/pokemon.h`.
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

### Phase 13: RHH Faithfulness Audit & Move Ban System — Complete

Comprehensive audit of all ported Gen 4+ moves against RHH reference, plus structural ports for move restriction flags.

#### EFFECT_RECOIL / EFFECT_STRUGGLE
- Added `EFFECT_RECOIL` and `EFFECT_STRUGGLE` to `include/constants/battle_move_effects.h`
- Mapped both to `BattleScript_EffectHit` in `src/data/battle_scripts_for_move_effects.h`
- Changed 12 recoil moves from `EFFECT_HIT` to `EFFECT_RECOIL`: Take Down, Double-Edge, Submission, Volt Tackle, Flare Blitz, Brave Bird, Wood Hammer, Head Smash, Wild Charge, Head Charge, Light of Ruin, Wave Crash
- Changed Struggle from `EFFECT_HIT` + `.recoil = 25` to `EFFECT_STRUGGLE` + `ADDITIONAL_EFFECTS({ .moveEffect = MOVE_EFFECT_RECOIL_HP_25, .self = TRUE })`

#### New MOVE_EFFECT constants (`include/constants/battle.h`)
- `MOVE_EFFECT_RECOIL_HP_25` (63) — Struggle's Gen 4+ HP%-based recoil
- `MOVE_EFFECT_ROUND` (61) — structural port for Round (doubles priority, no-op in singles)
- `MOVE_EFFECT_TERA_BLAST` (62) — structural port for Tera Blast (no-op without Tera system)

#### `ignoresSubstitute` field
- Added `ignoresSubstitute:1` bitfield to `struct MoveInfo` in `include/pokemon.h`
- Engine check in `Cmd_attackcanceler` (`src/battle_script_commands.c`): sets `HITMARKER_IGNORE_SUBSTITUTE` when flag is set
- Applied to all 31 sound-based moves matching RHH

#### `metronomeBanned` field
- Added `metronomeBanned:1` bitfield to `struct MoveInfo` in `include/pokemon.h`
- Engine check in `Cmd_metronome` (`src/battle_script_commands.c`): skips moves with flag set
- Applied to 153 moves matching RHH (includes gimmick moves: Tera, Mega, Z-Move, Dynamax)
- All gimmick-related moves are banned even though gimmick systems aren't yet implemented

#### Remaining ban flags — Complete
Added 6 additional per-move ban flags matching RHH:
- `mimicBanned` (24 moves) — engine check in `IsMoveUncopyableByMimic()`
- `copycatBanned` (49 moves) — data-only (Copycat not yet implemented)
- `assistBanned` (47 moves) — engine check in Assist handler
- `sleepTalkBanned` (37 moves) — engine check in `Cmd_trychoosesleeptalkmove()`
- `instructBanned` (51 moves) — data-only (Instruct not yet implemented)
- `encoreBanned` (13 moves) — engine check in `Cmd_trysetencore()`

**Deprecated:** Removed `sMovesForbiddenToCopy` hardcoded array and `IsInvalidForSleepTalkOrAssist()` helper. All move restriction checks now use per-move bitfield flags matching RHH architecture.

#### Additional ban flags — Complete
Added 6 more per-move ban flags matching RHH:
- `gravityBanned` (10 moves) — data-only (Gravity not yet implemented)
- `meFirstBanned` (17 moves) — data-only (Me First not yet implemented)
- `parentalBondBanned` (9 moves) — data-only (Parental Bond ability not yet implemented)
- `skyBattleBanned` (41 moves) — data-only (Sky Battles not planned)
- `sketchBanned` (3 moves) — engine check in `Cmd_copymovepermanently()` (replaced hardcoded MOVE_STRUGGLE/MOVE_SKETCH checks)
- `dampBanned` (4 moves) — data-only (Damp check currently routes through battle scripts; will wire flag when RHH-style canceler is ported)

#### Phase 13 — Remaining Follow-ups
- **`copycatBanned` engine check**: Copycat (`EFFECT_COPYCAT`) is stubbed to `EFFECT_HIT`. When implemented, add `gMovesInfo[move].copycatBanned` check.
- **`instructBanned` engine check**: Instruct (`EFFECT_INSTRUCT`) is stubbed to `EFFECT_HIT`. When implemented, add `gMovesInfo[move].instructBanned` check.
- **`gravityBanned` engine check**: Wire into Gravity field effect handler when Gravity is implemented.
- **`meFirstBanned` engine check**: Wire into Me First handler when implemented.
- **`dampBanned` engine check**: Wire into RHH-style `CancelerExplodingDamp` when move canceler is ported.

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

1. **Converge, don't adapt.** Port from RHH using identical names, structs, and signatures. If our name differs from RHH, rename ours.
2. **`FRLG_STUB`** = mechanic that exists in RHH but needs infrastructure not yet in FireRed.
3. **`GEN4_STUB`** = utility function returning neutral value, declared in header, real body later.
4. **No invented AI logic.** Trace to RHH or don't add it.
5. **Build must stay clean.** `make -j$(nproc) 2>&1 | grep "error:"` returns nothing.
6. **Active test/debug code** must be documented in `## Active Test/Debug Changes` in `README.md`.
7. **Named fields, not FLAG_*.** `FLAG_*` constants are removed. Use struct field names directly.
8. **Token efficiency.** For large ports (500+ lines), use Python porting tools instead of reading full files into LLM context.

---

## RHH Convergence Tracker

Names/structures that still differ from RHH and need renaming when touched:

**Already matching RHH:** `gBattlerAttacker`, `gBattlerTarget`, `gCurrentMove`, `gBattleMons`, `MAX_MON_MOVES`, `struct AdditionalEffect`, `ADDITIONAL_EFFECTS()`, `MoveHasAdditionalEffect*()`, `EFFECT_*`, `MOVE_EFFECT_*`

**Completed renames:**
- `struct BattleMove` → `struct MoveInfo` (7 files)
- `gBattleMoves` → `gMovesInfo` (29 files, 246 occurrences)
- `SPLIT_PHYSICAL/SPECIAL/STATUS` → `DAMAGE_CATEGORY_*` (14 files, 891 occurrences)

**Completed AI infrastructure ports (Tiers A–G done):**
- `GetMoveAdditionalEffectCount()` / `GetMoveAdditionalEffectById()` — inline in `include/pokemon.h`
- `MoveEffectIsGuaranteed()` / `MoveIsAffectedBySheerForce()` / `IsSheerForceAffected()` — `src/battle_util.c`
- `IsBattlerGrounded()` — `src/battle_util.c` (Gen 3 subset; Gen 4+ #ifdef'd)
- `struct AiLogicData` — `include/battle.h` (full RHH struct, heap-allocated)
- `struct SimulatedDamage` + `simulatedDmg[4][4][4]` field in `struct AiLogicData`
- `gAiLogicData` — allocated in `src/battle_util2.c`
- `.sheerForceOverride` field added to `struct AdditionalEffect`
- `enum AIScore`, `enum StatChange`, `ADJUST_SCORE`/`ADJUST_SCORE_PTR` — `include/battle_ai_main.h`
- `enum ConsiderPriority`, `enum DamageCalcContext`, `enum AiConsiderEndure` — `include/battle_ai_util.h`
- `AI_IS_FASTER`/`AI_IS_SLOWER` (#define 1/-1), `UNKNOWN_NO_OF_HITS` — `include/battle_ai_main.h`
- `AI_FLAG_*` constants — `include/constants/battle_ai.h` (RHH names; same bits as legacy AI_SCRIPT_*)
- `BATTLE_TYPE_TWO_OPPONENTS/INGAME_PARTNER/TOWER_LINK_MULTI` — `include/constants/battle.h`
- `GetBattlerTotalSpeedStat()` / `GetBattleMovePriority()` — `src/battle_main.c`
- `AI_WhoStrikesFirst()` — `src/battle_ai_util.c` (5-param RHH signature)
- `AI_IsFaster()` / `AI_IsSlower()` — 5-param RHH signatures, 4 callers updated
- `SetBattlerAiData()` — `src/battle_ai_util.c` (now populates simulatedDmg)
- `BattlerHasAi()` / `IsAiFlagPresent()` / `IsAiBattlerAware()` / `GetMovesArray()` / `HasMoveWithEffect()` / `HasMoveThatChangesKOThreshold()`
- `GetStatBeingChanged()` / `GetStagesOfStatChange()` — stat change switches
- `GetBattlerSecondaryDamage()` + 6 sub-helpers / `DoesAbilityRaiseStatsWhenLowered()`
- `CanAiPredictMove()` / `IsBattlerPredictedToSwitch()` / `GetIncomingMoveSpeedCheck()` / `AI_IsAbilityOnSide()` / `AreBattlersStatsMaxed()` / `CountPositiveStatStages()` / `ShouldRaiseAnyStat()`
- `IsBattlerAlive()` / `GetBattlerParty()` / `GetSideParty()` — inlines in `include/battle.h`
- `AI_GetDamage()` (static) / `GetNoOfHitsToKO()` / `GetNoOfHitsToKOBattlerDmg()` / `CanEndureHit()` / `GetNoOfHitsToKOBattler()` / `NoOfHitsForTargetToFaintBattler()`
- `AI_IsBattlerGrounded()` / `AI_CanBattlerEscape()` / `GetAIPartyIndexes()` / `CountUsablePartyMons()` / `IsBattlerTrapped()`
- Python extraction tool: `tools/port_ai_scoring.py`; 24 staged functions in `tools/staging/ai_port/`

- `IsMoveUnusable` inline — `include/battle_ai_util.h`
- `MoveIgnoresSubstitute` inline — `include/pokemon.h`
- `DoesSubstituteBlockMove()` / `CanAIFaintTarget()` / `CanTargetFaintAi()` — `src/battle_ai_util.c`
- `IsMoldBreakerTypeAbility()` stub — `src/battle_util.c` (moved from battle_ai_util.c per RHH; declared in `battle_util.h`)
- `HasTwoOpponents()` / `HasPartner()` — `src/battle_ai_util.c`
- `IncreaseStatDownScore()` (72 lines, volatiles→status2/gStatuses3) — `src/battle_ai_util.c`
- `IncreaseStatUpScoreInternal()` (static, 123 lines) / `IncreaseStatUpScore()` / `IncreaseStatUpScoreContrary()` — `src/battle_ai_util.c`

**Tier H — CanSetNonVolatileStatus chain (2026-03-29, COMPLETE):**
- `IsNonVolatileStatusBlocked()` (static) / `IsSafeguardProtected()` (static) — `src/battle_util.c`
- `CanSetNonVolatileStatus()` (Gen 3 faithful, Gen 4+ #ifdef'd) — `src/battle_util.c`
- `CanBePoisoned()` / `CanBeBurned()` / `CanBeParalyzed()` / `CanBeSlept()` / `IsUsableWhileAsleepEffect()` — `src/battle_util.c`
- 12 static AI helpers: `HasDamagingMove`, `HasUsableWhileAsleepMove`, `HasMoveWithMoveEffectExcept`, `IsPowerBasedOnStatus`, `DoesPartnerHaveSameMoveEffect`, `PartnerMoveEffectIsStatusSameTarget`, `AI_CanBeConfused`, `AI_CanPoison`, `AI_CanBurn`, `AI_CanParalyze`, `AI_CanPutToSleep`, `AI_CanConfuse` — `src/battle_ai_util.c`
- `IncreasePoisonScore()` / `IncreaseBurnScore()` / `IncreaseParalyzeScore()` / `IncreaseSleepScore()` / `IncreaseConfusionScore()` — full ports, `src/battle_ai_util.c`

**Tier F-G supplement (2026-03-29, COMPLETE):**
- `CanIndexMoveFaintTarget()` / `GetBestDmgMovesFromBattler()` — `src/battle_ai_util.c`
- `GetSpeciesBaseAttack()` / `GetSpeciesBaseSpAttack()` — `src/pokemon.c`

**Audit fixes applied (2026-03-29):**
- Removed dead `#ifdef AI_FLAG_PREDICT_MOVE` / `#ifdef AI_FLAG_PREDICT_SWITCH` (constants always defined)
- Fixed `EFFECT_POISON_GAS` → `EFFECT_POISON` in `PartnerMoveEffectIsStatusSameTarget`
- Fixed `GetMoveTarget()` → `GetMoveTarget(move, 0)` in `DoesPartnerHaveSameMoveEffect`
- `#ifdef ABILITY_SIMPLE` in `IncreaseStatUpScoreInternal` is CORRECT (Gen 4+, not in Gen 3)

**Tiers A–J are fully ported, build clean, 71/0/0 verify. AI additional effects scoring COMPLETE.**

**Tier J — AI_CalcAdditionalEffectScore** (see `docs/research/ai_additional_effects_port_plan.md`):

**COMPLETE (2026-03-29).** All 26 Tier J functions ported, full `GetAIEffectGroup`/`GetAIEffectGroupFromMove` infrastructure, wired into `AI_CheckViability`. Build: clean. Verify: 71/0/0.

Functions ported (all in `src/battle_ai_util.c`):
- `GetIncomingMove`, `HasPartnerIgnoreFlags`, `HasBattlerSideMoveWithEffect`
- `DoesBattlerIgnoreAbilityChecks`, `AI_WeatherHasEffect` (static), `AI_GetWeather`
- `BattlerWillFaintFromWeather`, `BattlerWillFaintFromSecondaryDamage`
- `IsAdditionalEffectBlocked`, `ShouldTryToFlinch`, `ShouldTrap`
- `GetAIEffectGroup` (static), `GetAIEffectGroupFromMove` (static), `HasMoveWithAIEffect`, `HasBattlerSideMoveWithAIEffect`
- `CanLowerStat`, `ShouldSetWeather`, `ShouldClearWeather`, `ShouldSetFieldStatus`, `ShouldClearFieldStatus`
- `ShouldSetScreen`, `ShouldCureStatus`, `AI_TryToClearStats`, `AI_ShouldCopyStatChanges`
- `AI_ShouldSetUpHazards`, `AI_GetBattlerMoveTargetType`, `HasMoveWithLowAccuracy`
- `AI_CalcAdditionalEffectScore` (static, in `src/battle_ai_main.c`)

Infrastructure additions:
- `EFFECT_RAPID_SPIN`, `EFFECT_WEATHER`, `EFFECT_WEATHER_AND_SWITCH`, `EFFECT_STEEL_ROLLER`, `EFFECT_ICE_SPINNER`, `EFFECT_OVERWRITE_ABILITY` added to `battle_move_effects.h`
- `MOVE_EFFECT_FEINT`, `MOVE_EFFECT_INCINERATE`, `MOVE_EFFECT_SALT_CURE`, `MOVE_EFFECT_GRAVITY`, terrain MOVE_EFFECTs, `MOVE_EFFECT_DEFOG`, `MOVE_EFFECT_HAZE`, `MOVE_EFFECT_REFLECT`, `MOVE_EFFECT_LIGHT_SCREEN`, `MOVE_EFFECT_TORMENT_SIDE` added to `constants/battle.h`
- `AI_EFFECT_*` constants + `LOW_ACCURACY_THRESHOLD` added to `include/battle_ai_util.h`

Deferred (own sessions):
- `WeatherChecker` (`battle_ai_field_statuses.c`, 603 lines)
- `ShouldCureStatusInternal` (80+ lines) — `ShouldCureStatus` is stub returning FALSE
- `ShouldSetWeather`/`ShouldClearWeather` are stubs (FALSE after weather check)

**NEXT SESSION: WeatherChecker port** OR add more Gen 4+ moves.

**Future sessions:**
- Port `WeatherChecker` from `battle_ai_field_statuses.c` (603 lines, own session)
- Port `ShouldCureStatusInternal` (80+ lines, deferred)

**Remaining structural changes** (not simple renames — values/semantics differ):

| Current FireRed | RHH | Change Type | Scope | Status |
|---|---|---|---|---|
| `MOVE_TARGET_*` bitmask `#define`s | `TARGET_*` sequential `enum` | Values + comparison semantics change | 911 occ, 12 files + engine bitwise checks | Future |
| `gBattleMoveDamage` (single `s32`) | `moveDamage[MAX_BATTLERS_COUNT]` in struct | Global → per-battler array | 232 occ, deep engine refactor | Future |
| `u32 status2` bitfield | `struct Volatiles volatiles` | Bitfield → named struct | 1200+ occ, every battle file | Future |
| `u8 type1, type2` | `enum Type types[3]` | 2 fields → array of 3 | Struct layout + all access sites | Future |
| `u8 gBattlerAttacker` | `enum BattlerId gBattlerAttacker` | Type safety (u8 → enum) | Type change only | Low |
| `bool8` returns | `bool32` returns | Width change | Function signatures | Low |
| `sBattler_AI` | Various AI locals | AI refactoring | When porting AI | Future |

This table should be updated as convergence progresses.

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
| `ai_additional_effects_port_plan.md` | Plan for porting AI_CalcAdditionalEffectScore from RHH (token-efficient Python tool approach) |
