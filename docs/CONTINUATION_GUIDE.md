# FireRed Romhack — Zero-Context Continuation Guide

> **Read this first.** Single source of truth for continuing work on this project.

---

## What This Is

A **FireRed decompilation romhack** forked from [pret/pokefirered](https://github.com/pret/pokefirered) with Gen 6+ mechanical upgrades. Codebase: `/mnt/data/Github/prototype/firered-romhack-1`. Build: `make -j$(nproc)`.

Reference codebase for porting: **pokeemerald-expansion (RHH)** at `/mnt/data/Github/rh-hideout/pokeemerald-expansion`.

**Active branch:** `feature-engine-overhaul` *(was `feature-AI-upgrade` — renamed for wider scope)*

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

---

## Current Goal: Move Engine Overhaul

**Branch:** `feature-engine-overhaul`

The move engine must be upgraded before Gen 4+ moves, updated learnsets, or new abilities can be added at scale. The `struct BattleMove` has hard limits (u8 effect, 8-flag bitfield) that block everything downstream.

**Full plan:** `docs/research/move_engine_upgrade_research.md`  
**Execution plan:** see implementation plan artifact in brain dir  
**Audit tool:** `python3 tools/audit_move_engine.py`

### Audit Baseline (as of 2026-03-23)

```
43 ERRORs — must resolve before struct expansion:
  - 11 × .flags & FLAG_* bitfield access  → battle_script_commands.c, battle_util.c
  - 7  × u8 effect local (truncation bug) → battle_ai_main.c
  - 19 × LEVEL_UP_MOVE_LV/ID bitmask     → pokemon.c
  - 6  × LEVEL_UP_END sentinel            → pokemon.c
0 ASM BattleMove offset references        → safe

Run: python3 tools/audit_move_engine.py
Target: exit 0, all ERRORs resolved
```

### Phase Sequence

| Phase | What | Key Files |
|---|---|---|
| **1** | Expand `struct BattleMove`: `u16 effect`, named flag fields, `argument`, `strikeCount`, `criticalHitStage`, `recoil` | `include/pokemon.h`, `src/data/battle_moves.h`, `battle_script_commands.c`, `battle_util.c`, `battle_ai_main.c` |
| **4** | `LevelUpMove` encoding: packed u16 → `{u16 move; u16 level;}` | `include/pokemon.h`, `level_up_learnsets.h`, `pokemon.c` |
| **3** | `additionalEffects[]` array for multi-secondary-effect moves | `include/pokemon.h`, `battle_script_commands.c` |
| **5** | Unified `moves_info.h` (merge 4 files into 1) | New file, retire old ones |

---

## Key Files Reference

| File | Purpose |
|---|---|
| `include/config.h` | Feature toggles (`OW_POISON_DAMAGE`, etc.) |
| `include/constants/moves.h` | Move ID `#defines` + `MOVES_COUNT` |
| `include/constants/battle_move_effects.h` | `EFFECT_*` constants (214 effects, ends at `EFFECT_CAMOUFLAGE`) |
| `include/constants/battle_ai.h` | AI flag constants (`AI_SCRIPT_*`) |
| `include/constants/pokemon.h` | `FLAG_*` defines, `LEVEL_UP_MOVE_LV/ID`, `LEVEL_UP_END` |
| `src/data/battle_moves.h` | Move stats (power, type, accuracy, PP, flags, category) |
| `src/data/text/move_names.h` | Move display names (ALLCAPS, max 12 chars) |
| `src/move_descriptions.c` | Move description strings + pointer array |
| `src/data/pokemon/level_up_learnsets.h` | Level-up moves per species (packed u16 encoding) |
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
| `tools/audit_move_engine.py` | Pre-flight checker for struct expansion (run before any Phase) |

---

## Battle AI — Current State

ASM AI VM fully removed. C-based RHH-faithful dispatch table.

**Smart switching:** add `AI_SCRIPT_SMART_SWITCHING` to trainer `aiFlags` in `src/data/trainers.h`.  
**New move effect AI:** add `case EFFECT_XYZ:` in `AI_CheckBadMove()` / `AI_CheckViability()` in `src/battle_ai_main.c`.

Full switching logic: `docs/battle_ai_architecture.md`

---

## Hard Limits (Current, Before Overhaul)

| Limit | Cap | Note |
|---|---|---|
| Move ID | **511** (9-bit learnset encoding) | 157 moves remaining before Phase 4 needed |
| TM slots | **64** (64-bit bitmask) | 6 slots remaining |
| Move effects | **255** (`u8` in struct) | Phase 1 raises to `u16` |
| Move flags | **8** (`u8` bitfield) | Phase 1 expands to named field bits |

---

## Build & Verify

```bash
cd /mnt/data/Github/prototype/firered-romhack-1
git checkout feature-engine-overhaul
python3 tools/audit_move_engine.py        # must exit 0 before struct changes
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
