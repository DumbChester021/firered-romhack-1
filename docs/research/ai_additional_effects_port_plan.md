# AI Additional Effects Scoring — Port Plan

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

### Tier E: Setup Logic
18. `CanAiPredictMove()` — needed by GetIncomingMoveSpeedCheck
19. `GetIncomingMoveSpeedCheck()` — 11 lines, needs CanAiPredictMove + gAiLogicData->predictingMove
20. `AI_IsAbilityOnSide()` — needed by ShouldRaiseAnyStat, IsBattlerTrapped
21. `AreBattlersStatsMaxed()` — needed by ShouldRaiseAnyStat
22. `ShouldRaiseAnyStat()` — 36 lines, needs 14+20+21 + many more (deep deps)
    - Consider porting after its deeper deps

### Tier F: KO Calc (damage infrastructure prerequisite)
23. `AI_CalcDamage()` — RHH's full version (our version is simplified)
24. `GetNoOfHitsToKOBattler()` — needs AI_CalcDamage
25. `NoOfHitsForTargetToFaintBattler()` — 16 lines, needs 24

### Tier G: Trap Helper
26. `AI_CanBattlerEscape()` — needed by IsBattlerTrapped
27. `CountUsablePartyMons()` — needed by IsBattlerTrapped
28. `IsBattlerTrapped()` — 30 lines, needs 26+27 + gAiLogicData fields + volatiles struct

### Tier H: Status Scoring Helpers
29. `IncreasePoisonScore()` / `IncreaseBurnScore()` / `IncreaseParalyzeScore()` / `IncreaseSleepScore()` / `IncreaseConfusionScore()`
    - Each: 20-40 lines, need AI_CanPoison/AI_CanBurn etc.

### Tier I: Core Stat Scoring (needs A-G)
30. `IncreaseStatDownScore()` — 72 lines, needs: 7+14+13+10+19+28
31. `IncreaseStatUpScoreInternal()` — 123 lines, needs: 7+25+22+18+10+16+17+gAiThinkingStruct.aiFlags[battler]
32. `IncreaseStatUpScore()` / `IncreaseStatUpScoreContrary()` — wrappers for 31

### Tier J: Main Function (needs A-I)
33. Various small helpers (IsAdditionalEffectBlocked, ShouldTrap, etc.)
34. `AI_CalcAdditionalEffectScore()` — 355 lines — port in full
35. Wire into `AI_CheckViability()`

## Key Structural Blockers

| Blocker | Description | Impact |
|---|---|---|
| `gAiThinkingStruct->aiFlags[battler]` | RHH uses per-battler `u64 aiFlags[4]`, FireRed uses single `u32 aiFlags` | Blocks IsBattlerPredictedToSwitch, IncreaseStatUpScoreInternal |
| `struct Volatiles volatiles` | RHH uses named struct, FireRed uses `u32 status2` bitfield | Blocks IsBattlerTrapped, IncreaseStatDownScore (leechSeed/cursed/root fields) |
| `GetBattlerTotalSpeedStat()` | Needs full speed stat formula (modifiers, weather, items) | Blocks AI_WhoStrikesFirst |

These blockers don't prevent ALL porting — they block specific code paths.
IsBattlerPredictedToSwitch and full IncreaseStatUpScoreInternal may need these resolved first.
Others (IncreaseStatDownScore speed path, GetStatBeingChanged/GetStagesOfStatChange) can proceed now.

## Port Session Plan

- **Session A**: ✅ Tier A steps 1-8 (speed infrastructure + AI_IsFaster update)
- **Session B**: ✅ Tiers B+D (BattlerHasAi, IsAiBattlerAware, GetMovesArray, HasMoveWithEffect, HasMoveThatChangesKOThreshold, GetStatBeingChanged, GetStagesOfStatChange)
- **Session C**: ✅ Tier C partial (GetBattlerSecondaryDamage + 6 helpers, DoesAbilityRaiseStatsWhenLowered)
- **Session D (next)**: Tier E (GetIncomingMoveSpeedCheck, ShouldRaiseAnyStat) + remaining Tier C (GetBattlerParty, IsBattlerPredictedToSwitch)
- **Session C**: Tier C part (GetBattlerSecondaryDamage + secondary-dmg helpers)
- **Session D**: Tier E (CanAiPredictMove, GetIncomingMoveSpeedCheck, ShouldRaiseAnyStat)
- **Session E**: Tier F+G (damage calc, IsBattlerTrapped)
- **Session F**: Tiers H+I (status helpers, IncreaseStatDown/UpScore)
- **Session G**: Tier J (AI_CalcAdditionalEffectScore + wire)

## Tool Usage

Extract any function from RHH:
```bash
python3 tools/port_ai_scoring.py -f FunctionName --check-deps
# output: tools/staging/ai_port/FunctionName.c
```

All staged extractions in `tools/staging/ai_port/`.
