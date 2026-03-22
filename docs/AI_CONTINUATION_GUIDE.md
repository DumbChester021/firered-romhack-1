# FireRed AI Upgrade — Zero-Context Continuation Guide

> **Read this first.** This document is the single source of truth for continuing work on this project.  
> It is designed to be complete enough that a new AI session with no prior context can pick up immediately.

---

## What This Project Is

A FireRed ROM hack (`feature-AI-upgrade` branch) where the original **ASM bytecode Battle AI** has been fully replaced with **native C** code, and the AI's switching logic has been ported faithfully from the [pokeemerald-expansion (RHH)](https://github.com/rh-hideout/pokeemerald-expansion) codebase.

The ROM is GBA FireRed. The toolchain is `arm-none-eabi-gcc`. Build with `make -j$(nproc)`.  
The repo is at `/mnt/data/Github/prototype/firered-romhack-1` on the `feature-AI-upgrade` branch.

**Save compatibility**: existing saves work. The AI changes are non-breaking.

---

## Current State (as of 2026-03-22)

All implementation is complete. Phases 0–6 are done.

| Phase | What | Status |
|---|---|---|
| 0 | Housekeeping: remove Natural Gift, docs reorg | ✅ Done |
| 1 | Branch `feature-AI-upgrade` created from main | ✅ Done |
| 2 | Research + implementation plan | ✅ Done |
| 2.5 | `battle_ai_util.c/h` — damage calc, speed check, move effect scan | ✅ Done |
| 3 | C dispatch table (`gAIFunctionTable`) replaces ASM VM | ✅ Done |
| 4 | All 9 standard AI flags ported from ASM → C | ✅ Done |
| 4b | Smart switching (`AI_SCRIPT_SMART_SWITCHING`) — faithful RHH port + all Gen 3 mechanics | ✅ Done |
| 6 | Dead ASM removed (3259-line `data/battle_ai_scripts.s`, ~1700 lines of dead C VM code) | ✅ Done |
| 5 | Automated test framework (RHH DSL port) | ⏳ **Next up** |

---

## Key Files

| File | Role |
|---|---|
| `src/battle_ai_main.c` | All 9+ AI flag implementations + `gAIFunctionTable` dispatch |
| `src/battle_ai_util.c` | Shared utilities: damage calc, switching logic (HasBadOdds, WonderGuard, Spikes, etc.) |
| `src/battle_ai_script_commands.c` | Entry points: `BattleAI_ChooseMoveOrAction()`, `BattleAI_SetupAIData()`, `RecordAbilityBattle()` |
| `include/battle_ai_main.h` | `AIFunc` typedef + `extern gAIFunctionTable[]` |
| `include/battle_ai_util.h` | Utility declarations + `AI_EFFECTIVENESS_x*` constants |
| `include/constants/battle_ai.h` | `AI_SCRIPT_*` flag bit constants |
| `src/data/trainers.h` | Per-trainer `aiFlags` — **edit here to enable smart switching** |
| `docs/battle_ai_architecture.md` | Full technical reference (read this for anything not covered here) |

**Deleted in Phase 6:**
- `data/battle_ai_scripts.s` — original 3259-line ASM AI scripts (gone)
- All `Cmd_*` VM handler functions and `sBattleAICmdTable` from `battle_ai_script_commands.c` (gone)

---

## How the AI Works Now

```
Battle turn → BattleAI_ChooseMoveOrAction()
  │
  ├─ [if AI_SCRIPT_SMART_SWITCHING] AI_EvaluateSwitch()
  │     → returns party slot to switch to, or PARTY_SIZE (no switch)
  │     → if switch: sets monToSwitchIntoId, returns B_ACTION_SWITCH
  │
  ├─ BattleAI_SetupAIData()  → initialize scores[4] = 100
  │
  └─ BattleAI_DoAIProcessing()  → iterate set bits in aiFlags
        for each flag bit set:
          gAIFunctionTable[bit](battlerAtk, battlerDef, move, score)
          → returns adjusted score
        → pick highest-scoring move
```

---

## AI Flags Reference

| Bit | Constant | Behavior |
|---|---|---|
| 0 | `AI_SCRIPT_CHECK_BAD_MOVE` | Penalizes impossible/pointless moves (-10 each) |
| 1 | `AI_SCRIPT_CHECK_VIABILITY` | Contextual score adjustments (HP%, weather, stat stages) |
| 2 | `AI_SCRIPT_TRY_TO_FAINT` | Boosts KO moves (+5 or +7 with priority advantage) |
| 3 | `AI_SCRIPT_SETUP_FIRST_TURN` | Boosts setup moves on turn 0 |
| 4 | `AI_SCRIPT_RISKY` | Boosts high-risk moves (50% chance) |
| 5 | `AI_SCRIPT_PREFER_STRONGEST_MOVE` | Random +2 for status moves |
| 6 | `AI_SCRIPT_PREFER_BATON_PASS` | +3 for setup when Baton Pass in moveset |
| 7 | `AI_SCRIPT_DOUBLE_BATTLE` | No-op (FRLG has no double AI) |
| 8 | `AI_SCRIPT_HP_AWARE` | HP-bracket based penalties for inappropriate moves |
| 9 | `AI_SCRIPT_SMART_SWITCHING` | **Pre-move switching evaluation** (see below) |
| 20 | `AI_SCRIPT_ROAMING` | Roaming battle (no scoring) |
| 21 | `AI_SCRIPT_SAFARI` | Safari zone |
| 22 | `AI_SCRIPT_FIRST_BATTLE` | First trainer battle |

### Default flag assignment (in `BattleAI_SetupAIData()`):
```
Trainer level ≤ 20 → CHECK_BAD_MOVE only
Trainer level  > 20 → CHECK_BAD_MOVE | TRY_TO_FAINT | CHECK_VIABILITY
Named trainers (gym leaders, rivals) → defined per-trainer in src/data/trainers.h
```

---

## Smart Switching (`AI_SCRIPT_SMART_SWITCHING`)

**Disabled by default** — add to `aiFlags` in `src/data/trainers.h` to enable.

```c
// Example — enable for Elite Four:
{ .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT
           | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_SMART_SWITCHING, ... }
```

### What it does:

All logic is in `src/battle_ai_util.c`. Every function cites its RHH source file + line number.

| Function | RHH source | Behavior |
|---|---|---|
| `AI_EvaluateSwitch()` | `battle_ai_switch_items.c:1001` | Entry point |
| `IsAbilityPreventingEscape()` | `:1015` | Don't switch if Arena Trap / Shadow Tag / Magnet Pull traps us |
| `ShouldSwitchIfWonderGuard()` | `:220` | Force switch vs Shedinja if no SE move |
| `HasBadOdds()` | `:71` | Switch if OHKO-threatened while outsped, or type-disadvantaged with no SE move |
| `CanMonSurviveHazardSwitchin()` | `:700` | Only switch into a mon that survives Spikes damage |
| `ShouldSwitchIfEncored()` | `:1098` | Switch if Encore-locked into a status move |
| `FindMonWithFlagsAndSuperEffective()` | `:750` | Find a party mon with a SE move that also resists the last move hit us (`gLastLandedMoves`) |
| `AI_GetTypeEffectiveness()` | `battle_ai_util.c:1013` | MOVE_RESULT_* flags → `AI_EFFECTIVENESS_x*` enum |
| `AI_GetTypeEffectivenessForPartyMon()` | `battle_util.c:10487` | Type check for benched mons (uses slot-2 scratch) |

### Remaining `FRLG_STUB` markers (all genuinely Gen 4+):

| Stub | Unlock when |
|---|---|
| `ABILITY_REGENERATOR` HP threshold | Gen 5 ability added |
| Stealth Rock / Toxic Spikes in hazard check | Gen 4 hazards ported |
| `AI_DATA->mostSuitableMonId` | Full RHH AI_DATA precompute system ported |
| Levitate immunity in Arena Trap check | `GetMonAbility()` added to util layer |
| `FindMonThatAbsorbsOpponentsMove` | Same as above |
| `ShouldSwitchIfBadChoiceLock` | Choice items added |
| `AreAttackingStatsLowered` | Stat-stage history tracking added |

---

## How to Add a New AI Flag

1. Add constant in `include/constants/battle_ai.h`:
   ```c
   #define AI_SCRIPT_MY_FLAG  (1 << 10)
   ```

2. Add the function signature in `src/battle_ai_main.c`:
   ```c
   static s32 AI_MyFlag(u8 battlerAtk, u8 battlerDef, u16 move, s32 score);
   ```

3. Add to table in `gAIFunctionTable`:
   ```c
   [10] = AI_MyFlag,
   ```

4. Implement the function. Return `score` unchanged for moves you don't want to affect.

5. Add to trainer `aiFlags` in `src/data/trainers.h`.

---

## How to Add a New Move Effect Handler

When a new move effect needs AI awareness:

1. Add `case EFFECT_MY_EFFECT:` in `AI_CheckBadMove()` to prevent impossible use.
2. Add `case EFFECT_MY_EFFECT:` in `AI_CheckViability()` to score it.
3. If it's a Gen 4+ move and the mechanic isn't yet in the engine, add `// GEN4_STUB` and return `score` unchanged.

---

## Build & Verify

```bash
cd /mnt/data/Github/prototype/firered-romhack-1
git checkout feature-AI-upgrade
make -j$(nproc) 2>&1 | grep "error:"    # must be empty
wc -c pokefirered_modern.gba             # must be exactly 16777216
```

**Quick smoke test in mGBA:**
1. Load ROM → reach title → no freeze ✅
2. Wild battle → wild mon uses moves, no crash ✅
3. Fight Brock (no `SMART_SWITCHING` flag) → AI never voluntarily switches ✅

---

## What's Next (Phase 5)

Port the RHH test framework so AI behavior can be verified automatically:

- Port `test/test_runner.c` and `test/test_runner_battle.c` from RHH
- Port the `GIVEN/WHEN/SCORE_GT/EXPECT_MOVE` DSL macros from `include/test/battle.h`
- Add `make BATTLE_TEST=1` build target
- Write test files:
  - `test/battle/ai/ai_check_bad_move.c`
  - `test/battle/ai/ai_check_viability.c`
  - `test/battle/ai/ai_trytofaint.c`
  - `test/battle/ai/ai_smart_switching.c`
- Run test ROM headlessly in mGBA, all pass

**RHH reference for the test framework:**  
`/mnt/data/Github/rh-hideout/pokeemerald-expansion/test/` (fully functional reference)

---

## Important Coding Rules for This Project

1. **Port, don't invent.** Every function must cite its RHH source file + line number.
2. **FRLG_STUB** = feature that exists in RHH but is genuinely Gen 4+ or requires infrastructure not yet in FireRed. Must include exact condition for when to un-stub.
3. **GEN4_STUB** = stub function in the utility layer returning `0` or `FALSE`. Only for things that will eventually be real.
4. **No invented logic.** If you can't trace it to RHH, it doesn't belong here.
5. **Build must stay clean.** `make -j$(nproc) 2>&1 | grep "error:"` must return nothing.
