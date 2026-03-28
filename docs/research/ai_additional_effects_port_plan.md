# AI Additional Effects Scoring — Port Plan

## Problem

FireRed's AI has no scoring for `additionalEffects[]` on moves. RHH evaluates these via two functions:

1. **`AI_CalcMoveEffectScore()`** (~1500 lines) — scores primary move effects (EFFECT_*)
2. **`AI_CalcAdditionalEffectScore()`** (~300 lines) — scores secondary effects from `additionalEffects[]`

Both are called from `AI_CheckViability()` in `src/battle_ai_main.c`.

## Affected Moves (Current)

| Move | Additional Effect | AI Impact |
|---|---|---|
| Bulldoze | MOVE_EFFECT_SPD_MINUS_1 (100%) | Speed drop invisible to AI |
| Trailblaze | MOVE_EFFECT_SPD_PLUS_1 (100% self) | Speed boost invisible to AI |
| Power-Up Punch | MOVE_EFFECT_ATK_PLUS_1 (100% self) | Attack boost invisible to AI |
| Giga Impact | MOVE_EFFECT_RECHARGE (100% self) | Recharge penalty invisible to AI |
| Zen Headbutt | MOVE_EFFECT_FLINCH (20%) | Non-guaranteed — RHH also doesn't score |

As more Gen 4+ moves are ported, this gap grows.

## Required RHH Functions

### Priority 1: AI_CalcAdditionalEffectScore
- **File:** `src/battle_ai_main.c` lines 5870-6240
- **Size:** ~370 lines
- **Dependencies:** `GetMoveAdditionalEffectCount()`, `GetMoveAdditionalEffectById()`, `MoveEffectIsGuaranteed()`
- **Helper functions needed:** `IncreaseStatUpScore()`, `IncreaseStatDownScore()`, `ShouldTryToFlinch()`, `IncreaseConfusionScore()`, `IncreasePoisonScore()`, `IncreaseBurnScore()`, etc.
- These helpers are in `src/battle_ai_util.c`

### Priority 2: AI_CalcMoveEffectScore
- **File:** `src/battle_ai_main.c` lines 4298-5867
- **Size:** ~1570 lines
- **Dependencies:** Everything in Priority 1 plus many more helpers
- **This replaces our current `AI_CheckViability()` switch-case logic**

## Porting Strategy — Token-Efficient

**DO NOT read these 1500+ line functions into LLM context.** Instead:

### Step 1: Build a Python Porting Tool
Create `tools/port_ai_scoring.py` that:
1. Reads RHH's `src/battle_ai_main.c` and `src/battle_ai_util.c`
2. Extracts target function bodies by brace-depth parsing
3. NO name mappings needed — we converge to RHH names (rename FireRed to match)
4. Identifies missing dependencies (functions/structs/constants not yet in FireRed)
5. Lists what needs to be ported or renamed as prerequisites
6. Copies function bodies directly to staging file for review

### Step 2: Port Helper Functions First
Port from `src/battle_ai_util.c`:
- `IncreaseStatUpScore()` / `IncreaseStatDownScore()`
- `ShouldTryToFlinch()`
- `MoveEffectIsGuaranteed()`
- Status scoring helpers (poison, burn, paralyze, etc.)

### Step 3: Port AI_CalcAdditionalEffectScore
- Smaller function (~370 lines), handles our immediate gap
- Only needs the helpers from Step 2

### Step 4: Port AI_CalcMoveEffectScore
- Larger function, replaces current viability switch
- Many more effect handlers
- Port incrementally: only handlers for effects we actually use

## Convergence Strategy (NO Name Mappings)

Per project rules, we do NOT translate RHH names to FireRed names. We RENAME FireRed to match RHH.
When porting AI functions, the prerequisite renames include:

| Current FireRed Name | RHH Name | Action |
|---|---|---|
| `gBattleMoves` | `gMovesInfo` | Rename globally when touching AI port |
| `SPLIT_PHYSICAL` etc. | `DAMAGE_CATEGORY_PHYSICAL` | Rename globally |
| `gBattleMons[x].status2` bitfield | `gBattleMons[x].volatiles.*` | Structural change — port volatiles struct |
| `.additionalEffects[i]` direct | `GetMoveAdditionalEffectById()` | Port the accessor function |
| `.numAdditionalEffects` direct | `GetMoveAdditionalEffectCount()` | Port the accessor function |
| (missing) | `struct AiLogicData` | Port the struct + data gathering |

These renames should be done as a preparatory commit before the AI port itself.

## Call Integration Point

In `AI_CheckViability()` (`src/battle_ai_main.c`), after the existing switch-case:
```c
// After existing effect-specific scoring...
score += AI_CalcAdditionalEffectScore(sBattler_AI, gBattlerTarget, move);
```

## Notes
- `MoveEffectIsGuaranteed()` filters out non-100% effects (so 20% flinch on Zen Headbutt won't be scored — matching RHH behavior)
- Self-targeting effects (`.self = TRUE`) use attacker stats, opponent-targeting use defender stats
- ABILITY_CONTRARY inverts stat change scoring
- As convergence progresses, the porting tool becomes simpler — eventually just a copy
