# AI Additional Effects Scoring — Port Plan

## Problem

FireRed's AI has no scoring for `additionalEffects[]` on moves. RHH evaluates these via two functions:

1. **`AI_CalcMoveEffectScore()`** (~1500 lines) — scores primary move effects (EFFECT_*)
2. **`AI_CalcAdditionalEffectScore()`** (~355 lines) — scores secondary effects from `additionalEffects[]`

Both are called from `AI_CheckViability()` in `src/battle_ai_main.c`.

## Affected Moves (Current)

| Move | Additional Effect | Self? | Chance | AI Scoring Needed |
|---|---|---|---|---|
| Bulldoze | MOVE_EFFECT_SPD_MINUS_1 | no | 100% | `IncreaseStatDownScore(STAT_SPEED)` |
| Trailblaze | MOVE_EFFECT_SPD_PLUS_1 | yes | 100% | `IncreaseStatUpScore(STAT_CHANGE_SPEED)` |
| Power-Up Punch | MOVE_EFFECT_ATK_PLUS_1 | yes | 100% | `IncreaseStatUpScore(STAT_CHANGE_ATK)` |
| Giga Impact | MOVE_EFFECT_RECHARGE | yes | guaranteed | NOT in AdditionalEffectScore — handled by CalcMoveEffectScore |
| Zen Headbutt | MOVE_EFFECT_FLINCH | no | 20% | Filtered out (not guaranteed) — matches RHH |
| Work Up | none (EFFECT_ATTACK_SPATK_UP) | — | — | Already scored by existing switch-case |

## Completed Infrastructure (This Session)

### Ported (compiles, in codebase)
1. **`GetMoveAdditionalEffectCount()`** — inline in `include/pokemon.h:325`
2. **`GetMoveAdditionalEffectById()`** — inline in `include/pokemon.h:330`
3. **`MoveEffectIsGuaranteed()`** — `src/battle_util.c:3283`
4. **`MoveIsAffectedBySheerForce()`** — `src/battle_util.c:3290`
5. **`IsSheerForceAffected()`** — `src/battle_util.c:3305` (ifdef'd for ABILITY_SHEER_FORCE)
6. **`struct AiLogicData`** — `include/battle.h:471` (full struct definition)
7. **`gAiLogicData`** — allocated in `src/battle_util2.c`, extern in `include/battle.h`
8. **`.sheerForceOverride`** field added to `struct AdditionalEffect`
9. **Declarations** — all new functions declared in `include/battle_util.h`

### Python Extraction Tool
- `tools/port_ai_scoring.py` — brace-depth parser, extracts RHH functions + dependency analysis
- `tools/staging/ai_port/` — 12 extracted functions (715 lines total)
- Run: `python3 tools/port_ai_scoring.py --check-deps`

## Remaining Work — Dependency Tree

### Tier 1: AI Score Constants (next session, ~30 min)
Port from `include/battle_ai_util.h`:
- `enum AIScore` — NO_INCREASE, WEAK_EFFECT, DECENT_EFFECT, GOOD_EFFECT, BEST_EFFECT, BAD_EFFECT
- `ADJUST_SCORE()` macro
- `ADJUST_SCORE_PTR()` macro

### Tier 2: SetBattlerAiData (~1 hour)
Port `SetBattlerAiData()` from `src/battle_ai_main.c:615-634`. Deps:
- `AI_DecideKnownAbilityForTurn()` — can simplify to `gBattleMons[battler].ability` initially
- `AI_DecideHoldEffectForTurn()` — can simplify to `GetBattlerHoldEffect(battler)` initially
- `GetBattlerHoldEffectParam()` — may already exist
- `GetHealthPercentage()` — trivial: `hp * 100 / maxHP`
- `GetBattlerTotalSpeedStat()` — exists or can be derived
- `CheckMoveLimitations()` — likely exists
- `IsAiBattlerAssumingStab()` / `RecordMovesBasedOnStab()` — can stub initially

### Tier 3: Stat Scoring Helpers (~2 hours)
**`IncreaseStatUpScoreInternal()`** (123 lines) — deep deps:
- `NoOfHitsForTargetToFaintBattler()` — needs damage calc (stub: return UNKNOWN_NO_OF_HITS)
- `GetIncomingMoveSpeedCheck()` — 11 lines, needs `gAiLogicData->predictedMove`
- `GetStatBeingChanged()` / `GetStagesOfStatChange()` — utility functions (~60 lines combined)
- `ShouldRaiseAnyStat()` — 36 lines
- `HasMoveThatChangesKOThreshold()` — 34 lines, needs damage calc (stub: return FALSE)
- `IsBattlerPredictedToSwitch()` — 13 lines
- `GetBattlerParty()` — likely exists
- `HasMoveWithEffect()` — 12 lines

**`IncreaseStatDownScore()`** (72 lines) — deps:
- `GetBattlerSecondaryDamage()` — 16 lines
- `DoesAbilityRaiseStatsWhenLowered()` — 12 lines
- `GetIncomingMoveSpeedCheck()` — shared with above
- `IsBattlerTrapped()` — 30 lines

### Tier 4: AI_CalcAdditionalEffectScore (~1 hour)
The main function (355 lines) — once Tiers 1-3 are done, this is a direct copy.
Additional deps only for switch cases we don't currently need:
- `IsAdditionalEffectBlocked()` — 10 lines
- Status scoring: `IncreasePoisonScore()`, `IncreaseBurnScore()`, etc. — 22-40 lines each
- Weather/terrain/screen helpers — small functions
- `AI_ShouldCopyStatChanges()`, `AI_ShouldSetUpHazards()`, etc.

### Tier 5: Wire into AI_CheckViability
Add call at end of `AI_CheckViability()`:
```c
score += AI_CalcAdditionalEffectScore(battlerAtk, battlerDef, move, gAiLogicData);
```

## Porting Strategy — Incremental Convergence

**DO NOT read full RHH functions into LLM context.** Use `tools/port_ai_scoring.py`.

### Approach: Full Port with Temporary Stubs
1. Port the full 355-line `AI_CalcAdditionalEffectScore` body from RHH (100% faithful)
2. Port all helper functions that are small (<30 lines) directly
3. For helpers with deep deps (damage calc, prediction), create temporary stubs that return safe defaults
4. Each stub is marked `// STUB: Port from RHH src/battle_ai_util.c:XXXX`
5. Stubs are replaced with real implementations as convergence progresses

### Why Full Port (not minimal)?
- Per project convergence rules: "no adaptations, port everything"
- The function is a clean switch-case — all cases compile even if some deps are stubbed
- Future moves automatically get scoring as their effects are already handled
- Stubs produce conservative behavior (no score change) which is safe

## Session Estimate
- Tier 1: 1 session (~30 min)
- Tier 2: 1 session (~1 hour)
- Tier 3: 1-2 sessions (~2-3 hours)
- Tier 4+5: 1 session (~1 hour)
- **Total: 3-4 sessions to complete full port**

## Notes
- `MoveEffectIsGuaranteed()` filters out non-100% effects (Zen Headbutt's 20% flinch won't be scored — matches RHH)
- Self-targeting effects (`.self = TRUE`) use attacker stats, opponent-targeting use defender stats
- ABILITY_CONTRARY inverts stat change scoring
- `IsSheerForceAffected()` is ifdef'd since ABILITY_SHEER_FORCE (Gen 5) isn't in our constants yet
- EWRAM is at 98.87% — `gAiLogicData` pointer costs only 4 bytes, struct is heap-allocated
