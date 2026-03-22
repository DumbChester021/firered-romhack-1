# FireRed Romhack — Zero-Context Continuation Guide

> **Read this first.** This is the single source of truth for continuing work on this project.  
> Complete enough for a new AI/dev session to pick up immediately with no prior context.

---

## What This Is

A **FireRed decompilation romhack** (`feature-AI-upgrade` branch, forked from [pret/pokefirered](https://github.com/pret/pokefirered)) with Gen 6+ mechanical upgrades and quality-of-life improvements. The codebase is at `/mnt/data/Github/prototype/firered-romhack-1`. Build with `make -j$(nproc)`.

The reference codebase for porting is **pokeemerald-expansion (RHH)** at `/mnt/data/Github/rh-hideout/pokeemerald-expansion`.

**Existing saves are compatible.** All changes are non-breaking.

---

## What's Already Done (Shipped)

| Feature | Status | Notes |
|---|---|---|
| **Fairy Type** | ✅ Done | 19th type, full Gen 6 effectiveness table, 18 species reclassified, graphics |
| **Physical/Special Split** | ✅ Done | Per-move `category` field, all 355 moves assigned, UI icons |
| **Running Shoes from start** | ✅ Done | No item needed, works indoors |
| **Reusable TMs** | ✅ Done | Infinite-use (Gen 5+), shop sell blocked, duplicate buy blocked |
| **Overworld Poison** | ✅ Done | Configurable via `OW_POISON_DAMAGE` in `include/config.h` (default: Gen 5+ no faint) |
| **pret Bug Fixes** | ✅ Done | All `#ifdef BUGFIX` / `#ifdef UBFIX` enabled — ~25 bugs fixed |
| **Battle AI: C Port** | ✅ Done | ASM VM replaced with native C dispatch table (9 flags ported) |
| **Battle AI: Smart Switching** | ✅ Done | Faithful RHH port, all Gen 3 mechanics (Spikes, Wonder Guard, Encore, etc.) |
| **Modern compiler default** | ✅ Done | `arm-none-eabi-gcc` is now the default, no `MODERN=1` needed |

**Branch:** `feature-AI-upgrade` contains all of the above. Main branch is behind.

---

## The Goal: New Moves + Engine Scaling

Adding new moves is the **immediate next objective**. But before adding moves at scale, several engine systems hit hard limits that need upgrading first. These upgrades are **future-proofing multipliers** — do them first so every following move doesn't hit a wall.

### Hard Limits That Block Move Scaling

| Constraint | Current | Cap | Impact |
|---|---|---|---|
| **Move ID** | 354 (Gen 1-3) | **511** (9-bit learnset encoding) | Hit at ~157 more moves. Expanding beyond 511 requires changing `LEVEL_UP_MOVE` encoding. |
| **TM slots** | 58 used (50 TM + 8 HM) | **64** (64-bit bitmask in `tmhm_learnsets.h`) | 6 slots left. Adding new TMs beyond 64 requires replacing the bitmask system. |
| **Move data** | 4–6 separate files per move | — | Every new move requires edits to `battle_moves.h`, `move_names.h`, `move_descriptions.c`, `battle_anim_scripts.s`. High friction. |
| **Learnset encoding** | Single file | — | RHH splits by gen (`level_up_learnsets/gen_1.h`–`gen_9.h`). Manageable for now. |
| **New move effects** | Must write ASM battle scripts | — | New Gen 4+ effects require implementing in `data/battle_scripts_1.s` — most complex part. |

---

## Priority Order for Next Work

### Priority 1 — Add New Moves (Can Start Now, Hit Limits Carefully)

The existing system can handle ~157 more moves (up to ID 511) before the learnset encoding breaks. TM system has 6 slots left, so don't add new TMs carelessly.

**Minimum files for any new move (existing effect, no TM):**

| File | Change |
|---|---|
| `include/constants/moves.h` | Add `#define MOVE_XYZ N`, bump `MOVES_COUNT` |
| `src/data/battle_moves.h` | Add stats struct `[MOVE_XYZ] = { ... }` |
| `src/data/text/move_names.h` | `[MOVE_XYZ] = _("NAME")` — ALLCAPS, max 12 chars |
| `src/move_descriptions.c` | String + pointer in `gMoveDescriptionPointers[MOVE_XYZ - 1]` |
| `data/battle_anim_scripts.s` | `.4byte Move_SIMILAR` — reuse existing animation |
| `src/data/pokemon/level_up_learnsets.h` | Add to at least one species |

> Full workflow: `docs/research/adding_new_moves_workflow.md`  
> RHH → FireRed field mapping: `docs/research/emerald_expansion_move_structure.md`

**New move effects** (Gen 4+ mechanics not yet in FireRed): Must write or port a battle script in `data/battle_scripts_1.s` + C command handler in `src/battle_script_commands.c`. Use RHH as reference. If the mechanic doesn't exist yet (e.g., Trick Room engine behavior), stub it.

**AI handling for new moves**: The new C AI handles moves by effect, not move ID. If reusing an existing effect, AI works automatically. If adding a new effect, add a `case EFFECT_XYZ:` in `AI_CheckBadMove()` and `AI_CheckViability()` in `src/battle_ai_main.c`. See `docs/battle_ai_architecture.md`.

---

### Priority 2 — Engine Upgrades That Unblock Scaling

Do these when you hit a limit, or proactively if planning a large batch:

#### 2a. TM System Expansion (6 slots left)
RHH uses a flat `u16[]` per-species array (`teachable_learnsets.h`) instead of a 64-bit bitmask. No hard limit. To port:
- Replace `TMHM()` bitmask in `src/data/pokemon/tmhm_learnsets.h`  
- Update `sTMHMMoves[]` / `sTMHMMoves_Duplicate[]` in `src/data/party_menu.h`
- Reference: RHH `include/constants/tms_hms.h` + `src/data/pokemon/teachable_learnsets.h`

#### 2b. Move Learnset Encoding (157 moves left before ID 511 cap)
Current `LEVEL_UP_MOVE(lvl, move)` macro encodes as `(lvl << 9) | move` — max move ID = 511. To expand:
- Change encoding to use `u32` with 16-bit move ID field
- Update `GetLevelUpMovesBySpecies()` / `GetMonLevelUpMoves()` in `src/pokemon.c`
- Reference: RHH `struct LevelUpMove { u16 move; u8 level; }` in `level_up_learnsets.h`

#### 2c. Consolidated Move Data (Quality of Life)
RHH stores all move data in a single unified struct in `moves_info.h` — no index sync issues. For FireRed, consider migrating to a unified `gMovesInfo[]` to eliminate the 4–6-file-per-move friction. High effort, high payoff at scale.

---

### Priority 3 — Planned Features (From README)

Ordered by estimated dependency and complexity:

| Feature | Dependency | Complexity |
|---|---|---|
| **Updated Learnsets / Base Stats** | New moves done | Low — data edit only |
| **EV/IV Summary Screen** | None | Medium — UI work |
| **Decapitalization** | None | Low — text data edit |
| **Faster Text Speed** | None | Low |
| **BW-style Repel System** | None | Low-Medium |
| **Forgettable HMs / HM Item Replacement** | None | Medium |
| **Modern EXP Share** | None | Medium |
| **Nature/Ability Display Colors** | None | Medium |
| **New Abilities** | Ability system research | High |
| **Items (new Gen items)** | `docs/research/missing_items.md` | Medium-High |
| **Day/Night Cycle** | Separate branch (has bugs) | High |
| **Follower Pokémon** | Overworld system | Very High |
| **Expanded Pokédex (Gen 4+ species)** | Sprite/data | Very High |
| **Mega Evolution** | Ability + item + battle system | Extremely High |

---

## Key Files Reference

| File | Purpose |
|---|---|
| `include/config.h` | Feature toggles (`OW_POISON_DAMAGE`, etc.) |
| `include/constants/moves.h` | Move ID `#defines` + `MOVES_COUNT` |
| `include/constants/battle_move_effects.h` | `EFFECT_*` constants (214 effects, ends at `EFFECT_CAMOUFLAGE`) |
| `include/constants/battle_ai.h` | AI flag constants (`AI_SCRIPT_*`) |
| `src/data/battle_moves.h` | Move stats (power, type, accuracy, PP, flags, category) |
| `src/data/text/move_names.h` | Move display names (ALLCAPS, max 12 chars) |
| `src/move_descriptions.c` | Move description strings + pointer array |
| `src/data/pokemon/level_up_learnsets.h` | Level-up moves per species |
| `src/data/pokemon/egg_moves.h` | Egg moves per species |
| `src/data/pokemon/tmhm_learnsets.h` | 64-bit TM/HM compatibility bitmask per species |
| `src/data/party_menu.h` | `sTMHMMoves[]` table mapping TM slot → move |
| `data/battle_scripts_1.s` | Battle effect scripts (ASM macro language) |
| `src/battle_script_commands.c` | C handlers for battle script commands |
| `data/battle_anim_scripts.s` | Move animation scripts + `gBattleAnims_Moves` table |
| `src/battle_ai_main.c` | All AI flag functions + `gAIFunctionTable` dispatch |
| `src/battle_ai_util.c` | AI utilities: damage calc, switching logic |
| `src/data/trainers.h` | Per-trainer `aiFlags` (add `AI_SCRIPT_SMART_SWITCHING` here) |
| `tools/verify_data.py` | Data integrity checker (Fairy type, P/S split, TMs) |

---

## Battle AI — Current State

The ASM AI VM is fully removed. The new system is C-based and RHH-faithful.

**To enable smart switching for a trainer** — add `AI_SCRIPT_SMART_SWITCHING` to their `aiFlags` in `src/data/trainers.h`. Disabled by default to preserve existing behavior.

**To add AI awareness for a new move effect** — add a `case EFFECT_XYZ:` in `AI_CheckBadMove()` and `AI_CheckViability()` in `src/battle_ai_main.c`. Return `score` unchanged for effects you don't want to penalize/reward.

Full switching logic reference: `docs/battle_ai_architecture.md`

---

## Build & Verify

```bash
cd /mnt/data/Github/prototype/firered-romhack-1
git checkout feature-AI-upgrade
make -j$(nproc) 2>&1 | grep "error:"   # must be empty
wc -c pokefirered_modern.gba            # must be 16777216 (exactly 16MB)
python3 tools/verify_data.py            # validates Fairy/P-S split/TM data
```

**Quick smoke test in mGBA:**
1. Load ROM → reach title → no freeze ✅
2. Wild battle → mon uses moves, no crash ✅
3. Trainer battle (no smart switching) → AI never voluntarily switches ✅

---

## Coding Rules for This Project

1. **Port, don't invent.** Cite the RHH source if porting. If inventing, document why.
2. **`FRLG_STUB`** = mechanic that exists in RHH but is Gen 4+ or needs infrastructure not yet in FireRed. Must say exactly when to un-stub.
3. **`GEN4_STUB`** = utility function returning neutral value. Declared in header, real body later.
4. **No invented AI logic.** Trace it to RHH or don't add it.
5. **Build must stay clean.** `make -j$(nproc) 2>&1 | grep "error:"` returns nothing.
6. **Active test/debug code** must be documented in the `## Active Test/Debug Changes` section of `README.md` before it's merged.

---

## Research Docs (in `docs/research/`)

| File | What's in it |
|---|---|
| `adding_new_moves_workflow.md` | Step-by-step guide: every file to touch when adding a move |
| `firered_vs_emerald_structure.md` | Deep structural diff: FireRed vs RHH for AI, battle scripts, move data |
| `emerald_expansion_move_structure.md` | RHH field-by-field mapping for porting move data |
| `missing_items.md` | Gen 4+ items not yet in FireRed — research for future item work |
| `missing_egg_moves.md` | Egg moves not yet in FireRed — reference for learnset updates |
| `battle_ai_migration_research.md` | Full research log for the AI ASM→C migration |
