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
| **Modern compiler default** | ✅ Done | `arm-none-eabi-gcc` default, no `MODERN=1` needed |
| **Move Engine Overhaul (Phase 1, 2, 3, 4)** | ✅ Done | See section below |

---

## Move Engine Overhaul — Completed

**Branch:** `feature-AI-upgrade` (commits after `1ef3ccfb1`)

### What Changed

#### `struct BattleMove` (`include/pokemon.h`)
- `effect`: `u8` → `u16` — allows >255 effect IDs
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

### What Remains (Optional / Future)
- **Phase 3:** `additionalEffects[]` array for multi-secondary-effect moves
- **Phase 5:** Unified `moves_info.h` (merge 4 files into 1 per RHH)

---

## Key Files Reference

| File | Purpose |
|---|---|
| `include/config.h` | Feature toggles (`OW_POISON_DAMAGE`, etc.) |
| `include/constants/moves.h` | Move ID `#defines` + `MOVES_COUNT` |
| `include/constants/battle_move_effects.h` | `EFFECT_*` constants (214 effects, ends at `EFFECT_CAMOUFLAGE`) |
| `include/constants/battle_ai.h` | AI flag constants (`AI_SCRIPT_*`) |
| `include/constants/pokemon.h` | `LEVEL_UP_END` (0xFFFF), `LEVEL_UP_END_ENTRY`, `LEVEL_UP_MOVE` macro |
| `src/data/battle_moves.h` | Move stats — uses named flag fields, not `FLAG_*` |
| `src/data/text/move_names.h` | Move display names (ALLCAPS, max 13 chars) |
| `src/move_descriptions.c` | Move description strings + pointer array |
| `src/data/pokemon/level_up_learnsets.h` | Level-up moves per species (`struct LevelUpMove[]`) |
| `src/data/pokemon/egg_moves.h` | Egg moves per species |
| `src/data/pokemon/tmhm_learnsets.h` | 64-bit TM/HM bitmask per species (6 slots left) |
| `src/data/party_menu.h` | `sTMHMMoves[]` table mapping TM slot → move |
| `data/battle_scripts_1.s` | Battle effect scripts (ASM macro language) |
| `src/battle_script_commands.c` | C handlers for battle script commands |
| `data/battle_anim_scripts.s` | Move animation scripts + `gBattleAnims_Moves` table |
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
