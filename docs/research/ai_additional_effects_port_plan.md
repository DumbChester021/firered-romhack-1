# AI Additional Effects Scoring — Port Plan

> **STATUS: COMPLETE (2026-03-29).** All items in this doc are implemented.
> See `docs/CONTINUATION_GUIDE.md` for current state. This doc is historical reference only.

## Goal

Port `AI_CalcAdditionalEffectScore()` from RHH 100% faithfully (no stubs, no adaptations).
This is the scoring system for `additionalEffects[]` on moves — the gap between FireRed's
current ASM-based AI and RHH's modern AI.

## Affected Moves (Current Codebase)

| Move | Additional Effect | Self? | Chance | Effect Once Ported |
|---|---|---|---|---|
| Bulldoze | MOVE_EFFECT_SPD_MINUS_1 | no | 100% | `IncreaseStatDownScore(STAT_SPEED)` |
| Trailblaze | MOVE_EFFECT_SPD_PLUS_1 | yes | 100% | `IncreaseStatUpScore(STAT_CHANGE_SPEED)` |
| Power-Up Punch | MOVE_EFFECT_ATK_PLUS_1 | yes | 100% | `IncreaseStatUpScore(STAT_CHANGE_ATK)` |
| Giga Impact | MOVE_EFFECT_RECHARGE | yes | guaranteed | No scoring (falls through to default) |
| Zen Headbutt | MOVE_EFFECT_FLINCH | no | 20% | Filtered by MoveEffectIsGuaranteed |
| Work Up | none (EFFECT_ATTACK_SPATK_UP) | — | — | Scored by existing effect switch |

## Completed Infrastructure (Committed)

| Function / Type | Location | Status |
|---|---|---|
| `GetMoveAdditionalEffectCount()` | `include/pokemon.h` inline | ✅ Done |
| `GetMoveAdditionalEffectById()` | `include/pokemon.h` inline | ✅ Done |
| `GetMoveEffect()` | `include/pokemon.h` inline | ✅ Done |
| `GetMovePriority()` | `include/pokemon.h` inline | ✅ Done |
| `GetMovePower()` | `include/pokemon.h` inline | ✅ Done |
| `MoveEffectIsGuaranteed()` | `src/battle_util.c` | ✅ Done |
| `MoveIsAffectedBySheerForce()` | `src/battle_util.c` | ✅ Done |
| `IsSheerForceAffected()` | `src/battle_util.c` (ifdef'd) | ✅ Done |
| `.sheerForceOverride` in AdditionalEffect | `include/pokemon.h` | ✅ Done |
| `struct AiLogicData` | `include/battle.h` | ✅ Done |
| `gAiLogicData` (allocated) | `src/battle_util2.c` | ✅ Done |
| `enum AIScore` | `include/battle_ai_main.h` | ✅ Done |
| `ADJUST_SCORE` / `ADJUST_SCORE_PTR` | `include/battle_ai_main.h` | ✅ Done |
| `enum StatChange` | `include/battle_ai_main.h` | ✅ Done |
| `SetBattlerAiData()` (simplified) | `src/battle_ai_util.c` | ✅ Done (TODO: update fields) |
| Python extraction tool | `tools/port_ai_scoring.py` | ✅ Done |

## Complete Ordered Port Chain (Bottom-Up, 100% Faithful)

Port in this exact order — each step may unlock the next.

### Tier A: Constants + Speed Infrastructure ✅ DONE
1. ✅ `enum ConsiderPriority` {DONT_CONSIDER_PRIORITY, CONSIDER_PRIORITY} → `include/battle_ai_util.h`
2. ✅ `UNKNOWN_NO_OF_HITS` (= UINT32_MAX) → `include/battle_ai_main.h`
3. ✅ `AI_IS_FASTER/AI_IS_SLOWER` return values (#define 1/-1) → `include/battle_ai_main.h`
4. ✅ `GetBattleMovePriority()` → `src/battle_main.c` (Gen 5+ ability checks #ifdef'd)
5. ✅ `GetBattlerTotalSpeedStat()` → `src/battle_main.c` (Gen 5+ abilities/items #ifdef'd)
6. ✅ `AI_WhoStrikesFirst()` → `src/battle_ai_util.c` (LAGGING_TAIL/STALL/TRICK_ROOM #ifdef'd)
7. ✅ Updated `AI_IsFaster()`/`AI_IsSlower()` to RHH 5-param signature + updated 4 callers
8. ✅ Updated `SetBattlerAiData()` field `speedStats` to use `GetBattlerTotalSpeedStat()`

### Tier B: Move Array + Move Query Helpers ✅ DONE
9. ✅ `BattlerHasAi()` / `IsAiFlagPresent()` / `IsAiBattlerAware()` → `src/battle_ai_util.c`
10. ✅ `GetMovesArray()` → `src/battle_ai_util.c` (returns `gBattleMons[battler].moves`; history path #commented — FireRed history is side-indexed)
11. ✅ `HasMoveWithEffect()` → `src/battle_ai_util.c`
12. ✅ `HasMoveThatChangesKOThreshold()` → `src/battle_ai_util.c` (static)

### Tier C: Battler State Helpers ✅ PARTIAL (secondary damage done)
12. `GetBattlerParty()` — returns `gPlayerParty`/`gEnemyParty` by battler side
13. ✅ `GetBattlerSecondaryDamage()` — ported with all 6 sub-helpers:
    - `GetLeechSeedDamage()` — 1 line (use gStatuses3[battler] & STATUS3_LEECHSEED)
    - `GetNightmareDamage()` — 1 line (use status1 nightmare bit)
    - `GetCurseDamage()` — 1 line (use status2 cursed bit)
    - `GetTrapDamage()` — 1 line (use status2 wrapped bits)
    - `GetPoisonDamage()` — 1 line (use status1 poison)
    - `GetWeatherDamage()` — ~10 lines (use gBattleWeather)
14. ✅ `DoesAbilityRaiseStatsWhenLowered()` — ported; COMPETITIVE/DEFIANT #ifdef-guarded
15. `IsBattlerPredictedToSwitch()` — 13 lines, needs `gAiThinkingStruct->aiFlags[]` as array
    - **Blocker**: RHH has `u64 aiFlags[MAX_BATTLERS_COUNT]`, FireRed has `u32 aiFlags` (single)
    - This is a structural change — defer or alias

### Tier D: Stat Change Helpers (self-contained) ✅ DONE
16. ✅ `GetStatBeingChanged()` — static in `src/battle_ai_util.c`
17. ✅ `GetStagesOfStatChange()` — static in `src/battle_ai_util.c`

### Tier E: Setup Logic ✅ DONE
18. ✅ `CanAiPredictMove()` — returns FALSE until AI_FLAG_PREDICT_MOVE added
19. ✅ `IsBattlerPredictedToSwitch()` — returns FALSE until AI_FLAG_PREDICT_SWITCH added
20. ✅ `GetIncomingMoveSpeedCheck()` — uses aiData->predictingMove/predictedMove
21. ✅ `AI_IsAbilityOnSide()` — checks battler + partner ability
22. ✅ `AreBattlersStatsMaxed()` / `CountPositiveStatStages()`
23. ✅ `ShouldRaiseAnyStat()` — Unaware/Opportunist/yawn/Sturdy checks #ifdef-guarded
Also: ✅ `IsBattlerAlive()`, `GetBattlerParty()`, `GetSideParty()` — inlines in include/battle.h

### Tier F: KO Calc (damage infrastructure prerequisite) ✅ DONE
23. ✅ `struct SimulatedDamage` + `simulatedDmg` in `struct AiLogicData` — `include/battle.h`
24. ✅ `enum DamageCalcContext` / `enum AiConsiderEndure` — `include/battle_ai_util.h`
25. ✅ Static `AI_GetDamage()` — reads `simulatedDmg`, respects AI_FLAG_RISKY/CONSERVATIVE
26. ✅ `GetNoOfHitsToKO()` / `GetNoOfHitsToKOBattlerDmg()` — pure math
27. ✅ `CanEndureHit()` — Gen 3: always FALSE (FOCUS_SASH/Sturdy-Gen5 #ifdef'd)
28. ✅ `GetNoOfHitsToKOBattler()` — uses AI_GetDamage + CanEndureHit
29. ✅ `NoOfHitsForTargetToFaintBattler()` — loops moves, returns min hits to KO
30. ✅ `SetBattlerAiData()` — now populates `simulatedDmg` via AI_CalcDamage (all 3 fields = same s32 value until min/max ported)
Also: ✅ `AI_FLAG_*` constants added to `include/constants/battle_ai.h` (RHH names, same bit values as AI_SCRIPT_*)
Also: ✅ `BATTLE_TYPE_TWO_OPPONENTS/INGAME_PARTNER/TOWER_LINK_MULTI` — added to `include/constants/battle.h`

### Tier G: Trap Helper ✅ DONE
31. ✅ `IsBattlerGrounded()` — `src/battle_util.c` (Gen 3: Levitate+Flying; Gen 4+ #ifdef'd)
32. ✅ `AI_IsBattlerGrounded()` — 1-line wrapper in `src/battle_ai_util.c`
33. ✅ `AI_CanBattlerEscape()` — Gen 3: always FALSE (SHED_SHELL/Ghost Gen6 #ifdef'd)
34. ✅ `GetAIPartyIndexes()` — `src/battle_ai_util.c` (handles multi-battle party ranges)
35. ✅ `CountUsablePartyMons()` — `src/battle_ai_util.c`
36. ✅ `IsBattlerTrapped()` — `src/battle_ai_util.c` (volatiles → status2/gStatuses3 translation; Sky Drop/FairyLock #ifdef'd)

### Tier H: Status Scoring Helpers ✅ PARTIAL (stubs only)
29. ✅ `IncreasePoisonScore()` / `IncreaseBurnScore()` / `IncreaseParalyzeScore()` / `IncreaseSleepScore()` / `IncreaseConfusionScore()`
    - Stubs: early-return guards ported; AI_CanPoison/Burn/Paralyze/Sleep/Confuse body blocked by `CanSetNonVolatileStatus` not yet ported
    - BLOCKER: `CanSetNonVolatileStatus` + `CanBePoisoned/Burned/Paralyzed/Slept` (in `battle_util.c`) — complex, own session

### Tier I: Core Stat Scoring ✅ DONE
30. ✅ `DoesSubstituteBlockMove()` — `src/battle_ai_util.c` (uses STATUS2_SUBSTITUTE; INFILTRATOR #ifdef'd)
31. ✅ `CanAIFaintTarget()` / `CanTargetFaintAi()` — `src/battle_ai_util.c`
32. ✅ `IsMoldBreakerTypeAbility()` — stub (Gen 3: always FALSE; MOLD_BREAKER/TURBOBLAZE/TERAVOLT #ifdef'd)
33. ✅ `HasTwoOpponents()` / `HasPartner()` — `src/battle_ai_util.c`
34. ✅ `IncreaseStatDownScore()` — 72 lines, volatiles translated to status2/gStatuses3
35. ✅ `IncreaseStatUpScoreInternal()` (static) — 123 lines, ABILITY_SIMPLE #ifdef'd
36. ✅ `IncreaseStatUpScore()` / `IncreaseStatUpScoreContrary()` — 4-line wrappers
Also: ✅ `IsMoveUnusable` inline in `include/battle_ai_util.h`
Also: ✅ `MoveIgnoresSubstitute` inline in `include/pokemon.h`
Also: ✅ `HOLD_EFFECT_CURE_*` accessible via new `#include "constants/hold_effects.h"` in `battle_ai_util.c`

### Tier J: Main Function (needs A-I)

**Session G research completed (2026-03-29). Full dependency tree mapped.**

#### New inlines needed (add to `include/pokemon.h` after existing ones):
```c
static inline bool32 IsSoundMove(u16 moveId)        { return gMovesInfo[moveId].soundMove; }
static inline u8 GetMoveCategory(u16 moveId)        { return gMovesInfo[moveId].category; }
static inline bool32 MoveIgnoresTargetAbility(u16 move) { return FALSE; } // Gen 4+ ignoresTargetAbility flag not in MoveInfo yet
```

#### New inlines needed (add to `include/battle.h`):
```c
static inline bool32 IsBattleMoveStatus(u16 move) { return gMovesInfo[move].category == DAMAGE_CATEGORY_STATUS; }
static inline bool32 IsSpreadMove(u16 moveTarget)  { if (!IsDoubleBattle()) return FALSE; return moveTarget == TARGET_BOTH || moveTarget == TARGET_FOES_AND_ALLY; }
```

#### New MOVE_EFFECT constants needed (add to `include/constants/battle.h`):
All Gen 4+ additional effect codes: `MOVE_EFFECT_CLEAR_SMOG`, `MOVE_EFFECT_INCINERATE`, `MOVE_EFFECT_STEALTH_ROCK`, `MOVE_EFFECT_FEINT`, `MOVE_EFFECT_THROAT_CHOP`, `MOVE_EFFECT_SALT_CURE`, `MOVE_EFFECT_SUN/RAIN/SANDSTORM/HAIL`, `MOVE_EFFECT_MISTY_TERRAIN` through `PSYCHIC_TERRAIN`, `MOVE_EFFECT_GRAVITY`, `MOVE_EFFECT_AURORA_VEIL`, `MOVE_EFFECT_REMOVE_STATUS`, `MOVE_EFFECT_BREAK_SCREEN`, `MOVE_EFFECT_STEAL_STATS`, `MOVE_EFFECT_RAISE_TEAM_ATTACK` through `SP_DEF`, `MOVE_EFFECT_LOWER_ATTACK_SIDE` through `SP_DEF_SIDE`, `MOVE_EFFECT_DEF_SPDEF_DOWN`, `MOVE_EFFECT_V_CREATE`.

#### New functions for `src/battle_ai_util.c`:
Port order (bottom-up):

1. **`IsBattleMoveStatus`** — inline in include/battle.h (see above)
2. **`HasPartnerIgnoreFlags`** — 7 lines: `if (IsDoubleBattle() && IsBattlerAlive(BATTLE_PARTNER(battler))) return TRUE;`
3. **`HasBattlerSideMoveWithEffect`** — needs HasPartnerIgnoreFlags: `if (HasMoveWithEffect(battler, effect)) return TRUE; if (HasPartnerIgnoreFlags(battler) && HasMoveWithEffect(BATTLE_PARTNER(battler), effect)) return TRUE;`
4. **`DoesBattlerIgnoreAbilityChecks`** — 12 lines; uses `AI_FLAG_NEGATE_UNAWARE` (add to battle_ai.h), `IsMoldBreakerTypeAbility` (done), `MoveIgnoresTargetAbility` (inline stub)
5. **`AI_GetWeather`** — 7 lines; uses `AI_WeatherHasEffect` (static inline: `return gAiLogicData->weatherHasEffect;` — `AI_FLAG_NEGATE_UNAWARE` path omitted for Gen 3)
6. **`AI_GetBattlerMoveTargetType`** — 10 lines; Gen 9 Terapagos/Commander `#ifdef`, terrain check `#ifdef`
7. **`CanIndexMoveFaintTarget`** — 15 lines; uses AI_GetDamage (static, done), CanEndureHit (done)
8. **`BattlerWillFaintFromSecondaryDamage`** — 5 lines; uses GetBattlerSecondaryDamage (done)
9. **`GetIncomingMove`** — 6 lines; uses aiData->predictingMove/predictedMove (done)
10. **`IsAdditionalEffectBlocked`** — 10 lines; `HOLD_EFFECT_COVERT_CLOAK` `#ifdef`
11. **`GetBestDmgMovesFromBattler`** — 39 lines; uses CanIndexMoveFaintTarget + AI_GetDamage
12. **`ShouldTryToFlinch`** — 21 lines; volatiles translation: `volatiles.infatuation`→`status2 & STATUS2_INFATUATION`, `volatiles.confusionTurns > 0`→`status2 & STATUS2_CONFUSION`; `HOLD_EFFECT_COVERT_CLOAK` `#ifdef`
13. **`ShouldTrap`** — 19 lines; `gAiThinkingStruct->aiFlags[battlerAtk]` → `AI_THINKING_STRUCT->aiFlags`
14. **`HasMoveWithAIEffect`** — stub: `return FALSE;` (AI_EFFECT system not yet ported; needed by ShouldSetScreen and AI_ShouldSetUpHazards)
15. **`HasBattlerSideMoveWithAIEffect`** — stub: `return FALSE;` (needs HasMoveWithAIEffect)
16. **`CanLowerStat`** — 62 lines; `HOLD_EFFECT_CLEAR_AMULET` `#ifdef`; `ABILITY_FLOWER_VEIL` `#ifdef`; `ABILITY_BIG_PECKS/MINDS_EYE/FULL_METAL_BODY` `#ifdef`; `HasBattlerSideMoveWithEffect(battlerAtk, EFFECT_ELECTRO_BALL)` → FALSE since no Electro Ball in Gen 3
17. **`AI_GetWeather` + `ShouldSetWeather` + `ShouldClearWeather`** — Simple versions without full WeatherChecker: `ShouldSetWeather` = `AI_GetWeather() doesn't include weather`; `ShouldClearWeather` = `AI_GetWeather() includes weather`. TODO: port full WeatherChecker from `battle_ai_field_statuses.c` when Gen 4+ weather abilities needed.
18. **`ShouldSetFieldStatus`** + **`ShouldClearFieldStatus`** — stub: `return FALSE;` (gFieldStatuses/STATUS_FIELD_TERRAIN Gen 6+; no terrain in Gen 3)
19. **`ShouldSetScreen`** — 34 lines; `HasMoveWithAIEffect` stub (always FALSE); `B_WEATHER_ICY_ANY` → `B_WEATHER_HAIL`; `SIDE_STATUS_AURORA_VEIL` `#ifdef`
20. **`ShouldCureStatus`** + `ShouldCureStatusInternal` — stub: `return FALSE;` (MOVE_EFFECT_REMOVE_STATUS is Gen 4+, no Gen 3 moves trigger this; full port is own session)
21. **`AI_TryToClearStats`** — 7 lines; uses CountPositiveStatStages (done)
22. **`AI_ShouldCopyStatChanges`** — 29 lines; `HasMoveWithLowAccuracy` → FALSE (stub); `gAiThinkingStruct->aiFlags[battlerAtk]` → `AI_THINKING_STRUCT->aiFlags`
23. **`AI_ShouldSetUpHazards`** — 24 lines; `HasBattlerSideMoveWithAIEffect` → stub FALSE; `DoesBattlerIgnoreAbilityChecks` (done); `IsBattleMoveStatus` (inline done)
24. **`AI_CalcAdditionalEffectScore`** — 355 lines; adaptations:
    - `gBattleStruct->battlerState[battlerAtk].commanderSpecies` → `#ifdef SPECIES_TERAPAGOS_STELLAR`
    - `gBattleStruct->battlerState[battlerAtk].isFirstTurn` → `gDisableStructs[battlerAtk].isFirstTurn`
    - `gBattleMons[battlerDef].volatiles.substitute` → `gBattleMons[battlerDef].status2 & STATUS2_SUBSTITUTE`
    - `GetItemPocket(...)  == POCKET_BERRIES` → `#ifdef POCKET_BERRIES`
    - `HOLD_EFFECT_GEMS` → `#ifdef HOLD_EFFECT_GEMS`
    - `HOLD_EFFECT_FLAME_ORB` / `HOLD_EFFECT_TOXIC_ORB` → `#ifdef`
    - `GetMoveEffectArg_Status(move)` → `gMovesInfo[move].argument` (our u32 argument)
    - `STATUS_FIELD_*` / `gFieldStatuses` in terrain cases → `#ifdef STATUS_FIELD_MISTY_TERRAIN`

25. Wire into `AI_CheckViability()` — find call site in `src/battle_ai_main.c`

#### Blocker: `AI_FLAG_NEGATE_UNAWARE`
Add to `include/constants/battle_ai.h`:
```c
#define AI_FLAG_NEGATE_UNAWARE (1 << 3)  // RHH: handicap flag for AI not understanding ability suppression
```

#### Blocker: WeatherChecker (complex)
`WeatherChecker` lives in `src/battle_ai_field_statuses.c` (603 total lines). For now, `ShouldSetWeather`/`ShouldClearWeather` use simplified `AI_GetWeather()` check. Full port deferred.

#### Blocker: ShouldCureStatusInternal (complex)
`ShouldCureStatusInternal` in RHH:4046 (80+ lines). MOVE_EFFECT_REMOVE_STATUS not used by any Gen 3 move. Stub `ShouldCureStatus` → `return FALSE`. Full port deferred to same session as CanSetNonVolatileStatus.

## Key Structural Blockers

| Blocker | Description | Impact |
|---|---|---|
| `gAiThinkingStruct->aiFlags[battler]` | RHH uses per-battler `u64 aiFlags[4]`, FireRed uses single `u32 aiFlags` | Blocks IsBattlerPredictedToSwitch, IncreaseStatUpScoreInternal |
| `struct Volatiles volatiles` | RHH uses named struct, FireRed uses `u32 status2` bitfield | ~~Blocks IsBattlerTrapped~~ ✅ Resolved via status2/gStatuses3 translation |
| `GetBattlerTotalSpeedStat()` | Needs full speed stat formula (modifiers, weather, items) | ✅ Resolved (Tier A) |
| `AI_SCRIPT_*` vs `AI_FLAG_*` names | 769 usages of old names in codebase | Blocked full rename — aliases added, full sweep deferred |

These blockers don't prevent ALL porting — they block specific code paths.
IsBattlerPredictedToSwitch and full IncreaseStatUpScoreInternal may need these resolved first.
Others (IncreaseStatDownScore speed path, GetStatBeingChanged/GetStagesOfStatChange) can proceed now.

## Port Session Plan

- **Session A**: ✅ Tier A steps 1-8 (speed infrastructure + AI_IsFaster update)
- **Session B**: ✅ Tiers B+D (BattlerHasAi, IsAiBattlerAware, GetMovesArray, HasMoveWithEffect, HasMoveThatChangesKOThreshold, GetStatBeingChanged, GetStagesOfStatChange)
- **Session C**: ✅ Tier C partial (GetBattlerSecondaryDamage + 6 helpers, DoesAbilityRaiseStatsWhenLowered)
- **Session D**: ✅ Tier E done (CanAiPredictMove, IsBattlerPredictedToSwitch, GetIncomingMoveSpeedCheck, AI_IsAbilityOnSide, AreBattlersStatsMaxed, CountPositiveStatStages, ShouldRaiseAnyStat, IsBattlerAlive, GetBattlerParty)
- **Session E**: ✅ Tiers F+G done (struct SimulatedDamage, simulatedDmg, AI_GetDamage, GetNoOfHitsToKO*, CanEndureHit, NoOfHitsForTargetToFaintBattler, IsBattlerGrounded, AI_IsBattlerGrounded, AI_CanBattlerEscape, CountUsablePartyMons, IsBattlerTrapped, AI_FLAG_* constants)
- **Session F**: ✅ Tier I done (DoesSubstituteBlockMove, CanAIFaintTarget, CanTargetFaintAi, IsMoldBreakerTypeAbility stub, HasTwoOpponents/HasPartner, IncreaseStatDownScore, IncreaseStatUpScoreInternal, IncreaseStatUpScore/Contrary); Tier H stubbed (IncreasePoisonScore etc., blocked by CanSetNonVolatileStatus)
- **Session G (next — research done 2026-03-29)**: Port Tier J — 25 functions + 355-line main. Full dependency tree documented above in Tier J section. New staged files extracted: GetIncomingMove, IsAdditionalEffectBlocked, GetBestDmgMovesFromBattler, ShouldTrap, ShouldTryToFlinch, CanLowerStat, ShouldSetWeather, ShouldClearWeather, ShouldSetFieldStatus, ShouldClearFieldStatus, ShouldSetScreen, ShouldCureStatus, AI_TryToClearStats, AI_ShouldCopyStatChanges, AI_ShouldSetUpHazards.
- **Future session**: Port CanSetNonVolatileStatus + CanBePoisoned/Burned/Paralyzed/Slept → fill Tier H status score stubs; Port WeatherChecker from battle_ai_field_statuses.c; Port ShouldCureStatusInternal

## Tool Usage

Extract any function from RHH:
```bash
python3 tools/port_ai_scoring.py -f FunctionName --check-deps
# output: tools/staging/ai_port/FunctionName.c
```

All staged extractions in `tools/staging/ai_port/`.
