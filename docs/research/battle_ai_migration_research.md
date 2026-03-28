# Battle AI Migration: FireRed ASM → C
## Research Reference for Manual Implementation

> **Scope:** This document is a technical reference to understand *everything* you need before touching a single file. It does not make changes. It is a map.

---

## 1. The Two Systems Side-by-Side

### FireRed: Bytecode VM

GameFreak built the Gen 3 AI around a **custom bytecode scripting engine**. The AI logic lives in `data/battle_ai_scripts.s` as human-readable macro calls that the assembler converts into raw bytes. At runtime a C interpreter in `src/battle_ai_script_commands.c` reads those bytes one-by-one through a pointer (`sAIScriptPtr`) and dispatches to handler functions.

```
data/battle_ai_scripts.s   →  (assembled to bytes)
src/battle_ai_script_commands.c  →  interprets those bytes at runtime
                                 →  modifies AI_THINKING_STRUCT->score[]
```

This indirection is the core architectural difference. The "AI logic" is **data** (bytes), not code.

### RHH/pokeemerald-expansion: Native C

RHH replaced the entire system. There are no bytecodes, no interpreter, no script pointer. Each AI flag corresponds to a C function that runs directly:

```c
// pokeemerald-expansion
static s32 AI_CheckBadMove(u32 battlerAtk, u32 battlerDef, u32 move, s32 score)
{
    // direct C — full language power, any data access
    if (gBattleMons[battlerDef].status1 & STATUS1_ANY && ...) score -= 10;
    return score;
}
```

The dispatcher in `battle_ai_main.c` calls each function and passes the score through:

```c
for each AI flag set:
    score = sAIFunctionTable[flagIndex](attacker, defender, move, score);
```

---

## 2. FireRed AI Architecture: Full Technical Detail

### 2.1 Files Involved

| File | Role | Size |
|------|------|------|
| `data/battle_ai_scripts.s` | All AI logic as bytecode macros | 3,260 lines / 85 KB |
| `src/battle_ai_script_commands.c` | The bytecode interpreter (VM) | 1,971 lines / 55 KB |
| `src/battle_ai_switch_items.c` | Switching + item use logic (separate from AI move scoring) | ~26 KB |
| `asm/macros/battle_ai_script.inc` | Macro definitions that map names → bytes | 602 lines |
| `include/constants/battle_ai.h` | AI flag constants, AI_USER/AI_TARGET, etc. | small |

### 2.2 The AI Script Table

At the top of `data/battle_ai_scripts.s`:

```asm
gBattleAI_ScriptsTable::
    .4byte AI_CheckBadMove        @ flag bit 0
    .4byte AI_CheckViability      @ flag bit 1
    .4byte AI_TryToFaint          @ flag bit 2
    .4byte AI_SetupFirstTurn      @ flag bit 3
    .4byte AI_Risky               @ flag bit 4
    .4byte AI_PreferStrongestMove @ flag bit 5
    .4byte AI_PreferBatonPass     @ flag bit 6
    .4byte AI_DoubleBattle        @ flag bit 7
    .4byte AI_HPAware             @ flag bit 8
    .4byte AI_Unknown             @ flag bit 9
    .4byte AI_Ret × 10            @ bits 10–19 (empty slots)
    .4byte AI_Roaming             @ flag bit 20
    .4byte AI_Safari              @ flag bit 21
    .4byte AI_FirstBattle         @ flag bit 22
```

Each trainer's `aiFlags` is a bitmask. The interpreter loops through set bits and runs the corresponding script for each of the 4 possible moves, accumulating score changes.

### 2.3 The AI Main Loop

```c
// BattleAI_ChooseMoveOrAction() calls BattleAI_DoAIProcessing() per flag bit
while (AI_THINKING_STRUCT->aiFlags != 0)
{
    if (AI_THINKING_STRUCT->aiFlags & 1)
    {
        // Runs the script at gBattleAI_ScriptsTable[aiLogicId]
        // for each of 4 moves (movesetIndex 0..3)
        BattleAI_DoAIProcessing();
    }
    AI_THINKING_STRUCT->aiFlags >>= 1;
    AI_THINKING_STRUCT->aiLogicId++;
    AI_THINKING_STRUCT->movesetIndex = 0;
}
// After all flags processed: pick highest score, random-break ties
```

Every move starts at score 100. Scripts **subtract** (bad moves) or **add** (viable moves). The move with the highest final score wins.

### 2.4 The VM State Machine

`BattleAI_DoAIProcessing()` runs a 3-state machine:

```
AIState_SettingUp    → load sAIScriptPtr from table, set moveConsidered
AIState_Processing   → sBattleAICmdTable[*sAIScriptPtr]()  ← dispatch
When AI_ACTION_DONE: → advance movesetIndex, loop or finish
```

The script pointer (`sAIScriptPtr`) advances by the byte width of each command's arguments after every dispatch. `end` (0x5A) triggers `AI_ACTION_DONE`.

### 2.5 The Command Set

94 commands total (0x00–0x5D). Key categories:

**Conditional branches** (the backbone of all AI logic):
- `if_random_less_than percent, ptr` (0x00) — probabilistic branching
- `if_hp_less_than battler, percent, ptr` (0x05) — HP checks
- `if_status / if_not_status battler, statusMask, ptr` (0x09/0x0A) — status1 checks
- `if_status2 / if_status3` (0x0B/0x0D) — secondary/volatile status
- `if_side_affecting battler, flag, ptr` (0x0F) — screens, spikes, etc.
- `if_type_effectiveness effectiveness, ptr` (0x31) — damage multiplier check
- `if_effect effect, ptr` (0x37) — **the main move dispatch** (checks current move's effect ID)
- `if_stat_level_{less,more,equal} battler, stat, level, ptr` (0x39–0x3C)
- `if_can_faint / if_cant_faint ptr` (0x3D/0x3E)
- `if_has_move_with_effect battler, effect, ptr` (0x41)
- `if_would_go_first battler, ptr` (0x28)

**Data getters** (load a value into `funcResult` for subsequent `if_equal` etc.):
- `get_ability battler` (0x2F)
- `get_gender battler` (0x49)
- `get_hold_effect battler` (0x48)
- `get_weather` (0x36)
- `get_how_powerful_move_is` (0x24) — checks `sDiscouragedPowerfulMoveEffects`
- `get_stockpile_count battler` (0x4B)
- `get_protect_count battler` (0x51)
- `get_used_held_item battler` (0x4D)
- `get_type byte` (0x22) — loads type of move/user/target into funcResult
- `count_alive_pokemon battler` (0x2C)

**Control flow:**
- `goto ptr` (0x59) — unconditional jump
- `call ptr` (0x58) — subroutine call (stack push, unused in practice in FR)
- `end` (0x5A) — end processing current move

**Score modification:**
- `score signedByte` (0x04) — the only way to change score in ASM

**Limits of the command set** (things you *cannot* do without adding new commands):
- Cannot compute estimated damage
- Cannot access individual PP values
- Cannot access species, item ID directly (only hold effect, not item)
- Cannot do loop-style iteration (no counter/loop commands)
- Cannot call arbitrary C functions
- `if_effect` takes only 1 byte: so effect IDs >255 are out of range

### 2.6 AI Script Pattern

Every AI handler follows this pattern:

```asm
AI_CheckBadMove_CheckEffect::
    if_effect EFFECT_SLEEP, AI_CBM_Sleep      @ if current move has SLEEP effect → jump
    if_effect EFFECT_EXPLOSION, AI_CBM_Explosion
    ... (one line per effect)
    end                                        @ no match → no score change

AI_CBM_Sleep::
    get_ability AI_TARGET
    if_equal ABILITY_INSOMNIA, Score_Minus10   @ load ability, if Insomnia → -10
    if_equal ABILITY_VITAL_SPIRIT, Score_Minus10
    if_status AI_TARGET, STATUS1_ANY, Score_Minus10
    end

Score_Minus10::
    score -10
    end
```

Translation to C is direct — each label becomes an `if/else if` chain in a function.

---

## 3. RHH AI Architecture: How It Works

### 3.1 Files Involved

| File | Role | Size |
|------|------|------|
| `src/battle_ai_main.c` | All AI scoring logic as C functions | ~5,400 lines |
| `src/battle_ai_util.c` | Utility functions for AI (damage estimates, etc.) | ~4,000 lines |
| `src/battle_ai_switch_items.c` | Switch/item logic | ~2,300 lines |

### 3.2 Structure

Each AI flag is a function with this signature:

```c
static s32 AI_CheckBadMove(u32 battlerAtk, u32 battlerDef, u32 move, s32 score);
```

These functions use a `switch` on `gMovesInfo[move].effect`:

```c
static s32 AI_CheckBadMove(u32 battlerAtk, u32 battlerDef, u32 move, s32 score)
{
    u32 effect = gMovesInfo[move].effect;

    // type effectiveness check
    if (GetTypeEffectiveness(move, battlerAtk, battlerDef) == AI_EFFECTIVENESS_x0)
        return AI_SCORE_INVALID;

    switch (effect)
    {
    case EFFECT_SLEEP:
        if (gBattleMons[battlerDef].ability == ABILITY_INSOMNIA
            || gBattleMons[battlerDef].ability == ABILITY_VITAL_SPIRIT
            || gBattleMons[battlerDef].status1 & STATUS1_ANY
            || gSideStatuses[GetBattlerSide(battlerDef)] & SIDE_STATUS_SAFEGUARD)
            score -= 10;
        break;
    case EFFECT_NATURAL_GIFT:
        if (!ItemId_GetHoldEffect(gBattleMons[battlerAtk].item) == HOLD_EFFECT_NONE)
            score -= 10;  // penalise if no berry held
        break;
    // ... hundreds more cases
    }
    return score;
}
```

The caller in `battle_ai_main.c` iterates all 4 moves and passes the score through each active AI flag function.

### 3.3 What RHH Gains Over FireRed

| Capability | FireRed ASM VM | RHH C |
|------------|----------------|-------|
| Estimate damage | ❌ No command | ✅ `AI_CalcDamage()` |
| Access any game struct | ❌ Only what commands expose | ✅ Any global, any field |
| Complex conditions | ❌ Only what commands can check | ✅ Full C logic |
| Add new check | Requires new VM command (C change) | Just add code in the function |
| Effect IDs > 255 | ❌ 1-byte limit in `if_effect` | ✅ `u16`/`u32` switch |
| Loop over party members | ❌ No loop command | ✅ `for (i = 0; i < 6; i++)` |
| Detect held item directly | Only hold *effect*, not item ID | Item ID, hold effect, any field |

---

## 4. The Migration: Three Approaches

### 4.1 Approach A — Full Rewrite to C (Emerald-style)

Replace `data/battle_ai_scripts.s` and `src/battle_ai_script_commands.c` entirely with C functions modeled on `battle_ai_main.c` from RHH.

**Files affected:**
- `src/battle_ai_script_commands.c` — **delete or gut** (keep `BattleAI_SetupAIData`, `BattleAI_ChooseMoveOrAction` entry points, strip the interpreter)
- `data/battle_ai_scripts.s` — **delete** (replaced by C)
- **NEW:** `src/battle_ai_main.c` — the new C AI
- **NEW** (optional): `src/battle_ai_util.c` — helper functions
- `asm/macros/battle_ai_script.inc` — no longer needed
- `include/battle_ai_script_commands.h` — update function declarations
- `ld_script.ld` — no script_data section needed (or keep and leave empty)

**Effort:** Very high. 3–6 weeks if doing it carefully with testing.

**Payoff:** Every future move with custom AI is a `case EFFECT_XYZ:` and a few lines of C.

### 4.2 Approach B — Hybrid: Keep ASM, Extend VM with New C Commands

Keep `battle_ai_scripts.s` unchanged. When you need to handle a new effect (e.g., `EFFECT_NATURAL_GIFT`), either:

1. Add a new VM command in `battle_ai_script_commands.c` (e.g., `Cmd_get_held_item_id`)
2. Add an `if_effect` line in `data/battle_ai_scripts.s` pointing to a new handler

**Files affected per new feature:**
- `src/battle_ai_script_commands.c` — add new `Cmd_` functions (if needed)
- `asm/macros/battle_ai_script.inc` — add macro for new command
- `data/battle_ai_scripts.s` — add `if_effect EFFECT_XYZ, AI_Handler_Xyz` + handler

**Effort:** Low per feature but accumulates. The VM's 1-byte effect limit (max effect ID 255) becomes a wall if you add many Gen 4+ effects.

### 4.3 Approach C — Incremental Rewrite (Recommended if you want full C)

Port one AI flag function at a time. Start with `AI_CheckBadMove` (the most mechanical), verify it matches behavior, then move to `AI_CheckViability`, etc.

**Order:**
1. `AI_CheckBadMove` — cleanest to port, mostly negative score adjustments
2. `AI_TryToFaint` — damage-awareness, needs `AI_CalcDamage()` eventually
3. `AI_CheckViability` — positive scoring, similar structure to CBM
4. `AI_SetupFirstTurn` — simple
5. `AI_HPAware` — HP thresholds only
6. `AI_Risky`, `AI_PreferStrongestMove`, `AI_PreferBatonPass` — small
7. `AI_DoubleBattle` — most complex single flag

---

## 5. Step-by-Step: How to Rewrite AI_CheckBadMove in C

This section shows the *exact* mental process for porting one AI script to C. Repeat for each flag.

### Step 1: Read what the ASM does

Open `data/battle_ai_scripts.s`. Find `AI_CheckBadMove::`. Trace each branch:

```asm
AI_CheckBadMove::
    get_how_powerful_move_is          @ loads funcResult
    if_equal MOVE_POWER_DISCOURAGED, AI_CheckBadMove_CheckSoundproof
                                      @ if discouraged move → skip type check

AI_CBM_CheckIfNegatesType::
    if_type_effectiveness AI_EFFECTIVENESS_x0, Score_Minus10  @ immune → -10
    get_ability AI_TARGET
    if_equal ABILITY_VOLT_ABSORB, CheckIfVoltAbsorbCancelsElectric
    if_equal ABILITY_WATER_ABSORB, CheckIfWaterAbsorbCancelsWater
    ...
```

Translate:

```c
static s32 AI_CheckBadMove(u32 battlerAtk, u32 battlerDef, u32 move, s32 score)
{
    u32 effect = gMovesInfo[move].effect;
    u32 ability = gBattleMons[battlerDef].ability;

    // "get_how_powerful_move_is" → check sDiscouragedPowerfulMoveEffects
    bool isDiscouraged = IsEffectInList(effect, sDiscouragedPowerfulMoveEffects);

    if (!isDiscouraged)
    {
        // type effectiveness check
        if (GetTypeEffectiveness(move, battlerAtk, battlerDef) == AI_EFFECTIVENESS_x0)
            return score - 10;

        // ability-based cancellation
        if (ability == ABILITY_VOLT_ABSORB && MoveIsType(move, TYPE_ELECTRIC)) return score - 12;
        if (ability == ABILITY_WATER_ABSORB && MoveIsType(move, TYPE_WATER))   return score - 12;
        if (ability == ABILITY_FLASH_FIRE   && MoveIsType(move, TYPE_FIRE))    return score - 12;
        if (ability == ABILITY_WONDER_GUARD)
        {
            if (GetTypeEffectiveness(move, battlerAtk, battlerDef) != AI_EFFECTIVENESS_x2)
                return score - 10;
        }
        if (ability == ABILITY_LEVITATE && MoveIsType(move, TYPE_GROUND)) return score - 10;
    }
    
    // Soundproof check
    if (ability == ABILITY_SOUNDPROOF)
    {
        static const u16 sSoundMoves[] = { MOVE_GROWL, MOVE_ROAR, MOVE_SING, ... };
        if (IsMoveInList(move, sSoundMoves)) return score - 10;
    }

    // Per-effect logic
    switch (effect)
    {
    case EFFECT_SLEEP:
        if (ability == ABILITY_INSOMNIA || ability == ABILITY_VITAL_SPIRIT)  return score - 10;
        if (gBattleMons[battlerDef].status1 & STATUS1_ANY)                   return score - 10;
        break;
    case EFFECT_EXPLOSION:
        if (GetTypeEffectiveness(move, battlerAtk, battlerDef) == AI_EFFECTIVENESS_x0) return score - 10;
        if (ability == ABILITY_DAMP) return score - 10;
        ... etc
    ...
    }
    return score;
}
```

### Step 2: Identify helper functions you need

The ASM hides implementation inside `Cmd_*` functions. Things you'll need to write or port:

| ASM command | What you need in C |
|-------------|-------------------|
| `get_how_powerful_move_is` | Check if effect is in `sDiscouragedPowerfulMoveEffects[]` |
| `if_type_effectiveness x0` | `GetTypeEffectiveness(move, attacker, defender)` — already exists in `battle_util.c` |
| `get_ability AI_TARGET` | `gBattleMons[battlerDef].ability` |
| `if_status AI_TARGET, STATUS1_ANY` | `gBattleMons[battlerDef].status1 & STATUS1_ANY` |
| `if_side_affecting AI_USER, SIDE_STATUS_LIGHTSCREEN` | `gSideStatuses[GetBattlerSide(battlerAtk)] & SIDE_STATUS_LIGHTSCREEN` |
| `if_stat_level_equal AI_USER, STAT_ATK, 12` | `gBattleMonsMisc[battlerAtk].statChanges[STAT_ATK] == 12` |
| `count_alive_pokemon AI_USER` | Count non-fainted mons in attacker's party |
| `if_has_move_with_effect AI_TARGET, EFFECT_DREAM_EATER` | Loop over `gBattleMons[battlerDef].moves[]`, check gMovesInfo[move].effect |
| `get_weather` | `gBattleWeather` |
| `if_can_faint` | `GetBattleDamage() >= gBattleMons[battlerDef].hp` — RHH has `AI_CalcDamage()` |
| `is_first_turn_for AI_USER` | `gDisableStructs[battlerAtk].isFirstTurn` |
| `get_stockpile_count AI_USER` | `gDisableStructs[battlerAtk].stockpileCount` |
| `get_used_held_item AI_USER` | `gBattleStruct->usedHeldItems[battlerAtk]` |
| `get_hold_effect AI_TARGET` | `ItemId_GetHoldEffect(gBattleMons[battlerDef].item)` |
| `get_protect_count AI_USER` | `gDisableStructs[battlerAtk].protectUses` |

Most of these just become a single expression. The tricky ones are `if_can_faint` (needs damage estimation) and `count_alive_pokemon` (needs a party loop).

---

## 6. Key Hurdles

### 6.1 The `if_effect` 1-Byte Limit

The macro `if_effect byte, ptr` stores the effect ID as 1 byte — max 255.

FireRed has 214 effects (0–213). If you add Gen 4+ effects past ID 213, they still fit in 1 byte. But if you ever reach effect ID 256+, the ASM VM **cannot handle them** without changing both the macro and the `Cmd_if_effect` C handler.

**In the hybrid approach:** Keep new Gen 4+ effects below 255, or port to C before you add that many.

**In the full C rewrite:** Not a problem — C switch uses `u16` or larger.

### 6.2 The `if_has_move_with_effect` 1-Byte Limit

Same problem: `if_has_move_with_effect battler, effect, ptr` encodes effect as 1 byte. Same ceiling of 255.

### 6.3 ROM Space

The current ROM (`pokefirered_modern.gba`) is 16 MB. The decompilation uses a modern linker script (`ld_script_modern.ld`), which means the ROM can be expanded if needed. With `MODERN=1` (which is now your default), you're not locked to GameFreak's original ROM size. You have room to add C code.

But be aware: **the AI bytecode lives in `.section script_data`** and is loaded as ROM data. The C functions you write will live in the code sections. Both count against ROM size. The linker will tell you if you overflow.

### 6.4 Keeping `BattleAI_SetupAIData` and the Entry Points

When rewriting, these functions in `battle_ai_script_commands.c` **must be kept intact** because they're called from elsewhere:

- `BattleAI_HandleItemUseBeforeAISetup()` — called during battle init
- `BattleAI_SetupAIData()` — initializes `AI_THINKING_STRUCT`, called before each decision
- `BattleAI_ChooseMoveOrAction()` — the main entry, called from `battle_controller_opponent.c`
- `RecordAbilityBattle()` — called by battle scripts when an ability activates
- `RecordItemEffectBattle()` — called by battle scripts when a held item triggers

You can gut the interpreter loop in `BattleAI_DoAIProcessing()` and replace it with direct C function calls, but the outer wrappers need to survive.

### 6.5 Matching aiFlags Semantics

`AI_THINKING_STRUCT->aiFlags` is a bitmask set from the trainer data:

```c
AI_THINKING_STRUCT->aiFlags = gTrainers[gTrainerBattleOpponent_A].aiFlags;
```

In Emerald the flags map directly to function pointers (same index). You must preserve the **same flag bit assignments** so trainer `aiFlags` values still work:

| Bit | Script | C function name |
|-----|--------|-----------------|
| 0 | `AI_CheckBadMove` | `AI_CheckBadMove` |
| 1 | `AI_CheckViability` | `AI_CheckViability` |
| 2 | `AI_TryToFaint` | `AI_TryToFaint` |
| 3 | `AI_SetupFirstTurn` | `AI_SetupFirstTurn` |
| 4 | `AI_Risky` | `AI_Risky` |
| 5 | `AI_PreferStrongestMove` | `AI_PreferStrongestMove` |
| 6 | `AI_PreferBatonPass` | `AI_PreferBatonPass` |
| 7 | `AI_DoubleBattle` | `AI_DoubleBattle` |
| 8 | `AI_HPAware` | `AI_HPAware` |
| 9 | `AI_Unknown` | (keep as no-op) |
| 20 | `AI_Roaming` | `AI_Roaming` |
| 21 | `AI_Safari` | `AI_Safari` |
| 22 | `AI_FirstBattle` | `AI_FirstBattle` |

The table (`gBattleAI_ScriptsTable`) must become a function pointer table.

### 6.6 Score Data Type

In ASM: `score` is a `s8` addition (signed 1-byte delta). In C: `score` should be `s32` for the function return. The initial value is `100`. The minimum is `0` (floored in the original). Preserve that floor.

### 6.7 `BattleHistory` and `funcResult`

The ASM VM has a shared `funcResult` field in `AI_THINKING_STRUCT` that "getter" commands write to before conditional commands read it. In C this disappears — you just use local variables in the function.

`BattleHistory` (tracking opponent's moves/abilities seen) is used by some commands. In C you read it directly: `BATTLE_HISTORY->abilities[side]`, `BATTLE_HISTORY->usedMoves[side][i]`.

---

## 7. Adapting RHH's Better AI Logic

RHH's `AI_CheckBadMove` has Emerald's improvements (which are *already commented* in your `battle_ai_scripts.s`). Specifically:

```asm
@ If_side_affecting AI_TARGET, SIDE_STATUS_SAFEGUARD, Score_Minus10  @ Improvement in Emerald
```

There are **6 places** in your ASM where Emerald improvements are commented out. In C you simply uncomment them (write the equivalent). These are:

| Location | Emerald improvement |
|----------|-------------------|
| `AI_CBM_Sleep` | Check Safeguard |
| `AI_CBM_Poison` | Check Safeguard |
| `AI_CBM_Paralyze` | Check Safeguard |
| `AI_CBM_Confuse` | Check Safeguard |
| `AI_CBM_WillOWisp` | Check Safeguard |
| `AI_CBM_FutureSight` | Also penalize if *user's* side already has future attack pending |
| `AI_CBM_SpeedDown` | Check Speed Boost ability |
| `AI_CheckViability` | `AI_CV_Swagger` handler |

RHH also adds entirely new AI flag functions (`AI_FLAG_HELP_ALLY`, `AI_FLAG_STALL`, etc.) that have no FireRed equivalent. You can add those later; they're independent.

---

## 8. The Structural Change to `BattleAI_DoAIProcessing`

### Current (VM-based):

```c
static void BattleAI_DoAIProcessing(void)
{
    // ... state machine ...
    case AIState_Processing:
        sBattleAICmdTable[*sAIScriptPtr](); // read a byte, dispatch function
    // ...
}
```

### After C rewrite:

```c
typedef s32 (*AIFunc)(u32 battlerAtk, u32 battlerDef, u32 move, s32 score);

static const AIFunc sAIFunctionTable[] =
{
    AI_CheckBadMove,        // bit 0
    AI_CheckViability,      // bit 1
    AI_TryToFaint,          // bit 2
    AI_SetupFirstTurn,      // bit 3
    AI_Risky,               // bit 4
    AI_PreferStrongestMove, // bit 5
    AI_PreferBatonPass,     // bit 6
    AI_DoubleBattle,        // bit 7
    AI_HPAware,             // bit 8
    AI_Unknown,             // bit 9
    ... (NULL entries for 10–19) ...
    AI_Roaming,             // bit 20
    AI_Safari,              // bit 21
    AI_FirstBattle,         // bit 22
};

static void BattleAI_DoAIProcessing(void)
{
    u32 flags = AI_THINKING_STRUCT->aiFlags;
    u32 flagIdx = 0;
    while (flags)
    {
        if ((flags & 1) && sAIFunctionTable[flagIdx] != NULL)
        {
            for (u32 i = 0; i < MAX_MON_MOVES; i++)
            {
                u32 move = gBattleMons[gBattlerAttacker].moves[i];
                if (move == MOVE_NONE || gBattleMons[gBattlerAttacker].pp[i] == 0) continue;
                AI_THINKING_STRUCT->score[i] = sAIFunctionTable[flagIdx](
                    gBattlerAttacker, gBattlerTarget, move,
                    AI_THINKING_STRUCT->score[i]);
                if (AI_THINKING_STRUCT->score[i] < 0)
                    AI_THINKING_STRUCT->score[i] = 0;
            }
        }
        flags >>= 1;
        flagIdx++;
    }
}
```

---

## 9. File-by-File Change Plan

### Files to DELETE or gut:
- `data/battle_ai_scripts.s` — becomes empty (or keep with only table/labels for binary matching)
- `asm/macros/battle_ai_script.inc` — no longer needed (keep for reference)

### Files to HEAVILY MODIFY:
- `src/battle_ai_script_commands.c`
  - Remove: `sAIScriptPtr`, `sBattleAICmdTable`, all 94 `Cmd_*` functions
  - Keep: `BattleAI_SetupAIData()`, `BattleAI_ChooseMoveOrAction()`, `BattleAI_HandleItemUseBeforeAISetup()`, `RecordAbilityBattle()`, `RecordItemEffectBattle()`
  - Rewrite: `BattleAI_DoAIProcessing()` as function-pointer dispatch

### Files to CREATE:
- `src/battle_ai_main.c` — all the AI flag functions as C
  - One function per AI flag: `AI_CheckBadMove`, `AI_CheckViability`, ...
  - Optionally split into multiple files later
- `include/battle_ai_main.h` — declarations

### Files that do NOT need to change:
- `src/battle_ai_switch_items.c` — already C, handles item/switch logic separately
- `data/battle_scripts_1.s` — battle script macros unaffected
- `src/battle_script_commands.c` — battle effects unaffected
- All trainer data (`gTrainers`) — `aiFlags` meanings stay the same
- `include/constants/battle_ai.h` — AI flag constants stay the same

---

## 10. Testing Approach (Manual — No Automated Tests)

This codebase has no unit test framework. Verification is behavioral.

### Phase 1: Per-flag behavioral parity

For each ported flag:
1. Build and load in emulator (mGBA)
2. Force a trainer with *only* that AI flag (edit a trainer's `aiFlags` temporarily)
3. Set up a scenario that exercises the ported logic:
   - For `AI_CheckBadMove`: put your mon to sleep, observe if AI avoids sleep moves
   - For `AI_CheckBadMove` type immunity: use a Ghost-type, observe AI avoids Normal moves
4. Compare to the original ASM behavior (revert commit, test same scenario)

### Phase 2: Full game regression

Play through at least 5 trainer battles with varied AI flag configs (Gym leaders use multiple flags). Observe no crashes, no infinite loops, no obviously wrong move choices.

### Phase 3: Edge cases

- AI with only 1 move
- AI with all moves at 0 PP (Struggle situation)
- Double battles
- Safari and Roaming battles (those use very simple AI)

---

## 11. Recommended Reading Order (to do this yourself)

If you want to execute this migration without relying on LLM assistance for the code writing, read these in order:

1. **`asm/macros/battle_ai_script.inc`** — full file, know what every macro compiles to
2. **`src/battle_ai_script_commands.c`** lines 1–460 — understand the VM dispatch loop, `BattleAI_SetupAIData`, `BattleAI_ChooseMoveOrAction`
3. **`src/battle_ai_script_commands.c`** lines 461–1971 — understand every `Cmd_*` implementation. These become your C helpers.
4. **`data/battle_ai_scripts.s`** — read `AI_CheckBadMove` (lines 52–603) completely. Trace the flow manually.
5. **`data/battle_ai_scripts.s`** `AI_CheckViability` (lines 653–776) + all its handlers
6. **`include/constants/battle_ai.h`** — understand `AI_SCRIPT_*` bitmasks
7. **`src/battle_ai_switch_items.c`** lines 1–50 — understand what's *not* AI move scoring (so you don't accidentally duplicate it)
8. **pokeemerald-expansion `src/battle_ai_main.c`** — read one full function (e.g., `AI_CheckBadMove`) to see the C pattern. This is your template.

---

## 12. Quick Reference: What Maps to What

```
ASM macro                           C equivalent
─────────────────────────────────   ──────────────────────────────────────────
if_type_effectiveness x0, ptr   →   GetTypeEffectiveness(move, atk, def) == 0
get_ability AI_TARGET           →   gBattleMons[battlerDef].ability
if_equal ABILITY_X, ptr         →   if (ability == ABILITY_X)
if_status AI_TARGET, S1_ANY     →   gBattleMons[battlerDef].status1 & STATUS1_ANY
if_status2 AI_USER, S2_SUB      →   gBattleMons[battlerAtk].status2 & STATUS2_SUBSTITUTE
if_status3 AI_TARGET, S3_ROOTED →   gStatuses3[battlerDef] & STATUS3_ROOTED
if_side_affecting AI_USER, X    →   gSideStatuses[GetBattlerSide(battlerAtk)] & X
if_stat_level_equal AI_USER, S, N   gBattleMonsMisc[battlerAtk].statChanges[S] == N
count_alive_pokemon AI_USER     →   CountAlivePokemon(battlerAtk) (write this helper)
get_weather                     →   gBattleWeather
if_equal AI_WEATHER_RAIN, ptr   →   if (gBattleWeather & WEATHER_RAIN_ANY)
get_hold_effect AI_TARGET       →   ItemId_GetHoldEffect(gBattleMons[battlerDef].item)
get_used_held_item AI_USER      →   gBattleStruct->usedHeldItems[battlerAtk]
is_first_turn_for AI_USER       →   gDisableStructs[battlerAtk].isFirstTurn
get_stockpile_count AI_USER     →   gDisableStructs[battlerAtk].stockpileCount
get_protect_count AI_USER       →   gDisableStructs[battlerAtk].protectUses
if_can_faint ptr                →   AI_CalcDamage(...) >= gBattleMons[battlerDef].hp
if_has_move_with_effect B, E    →   loop over B's moves, check effect == E
count_alive_pokemon AI_USER     →   loop B's party, count hp > 0 && species != 0
score -10                       →   score -= 10; return score; (inside switch case)
end                             →   (implicit: fall through to return score)
goto Label                      →   restructure as nested if/else or goto in C
```

---

## 13. Summary: What Makes This Hard

1. **Volume** — 9 AI flag scripts × up to 200+ effect handlers = a lot of manual translation
2. **No direct damage estimation** in FireRed AI (the VM has no `Cmd_calc_damage`). RHH's improved AI does this. If you want that improvement, you need to port or write `AI_CalcDamage()` — that's a significant addition from `battle_ai_util.c`
3. **Binary parity is not required** — you're writing a ROM hack, not a decompilation. You only need behavioral correctness
4. **The VM's `funcResult` register** — the two-step pattern of `get_X` then `if_equal value` maps cleanly to local variables in C but you have to trace it manually per-handler to know what `funcResult` contains at each `if_equal` call
5. **Emerald's `AI_CheckViability` is 2.5× longer than FireRed's** — the scoring logic for viable moves is much more sophisticated. You can port FireRed first and then cherry-pick Emerald improvements

The actual C code per function is straightforward once you understand the VM. The barrier is *knowing the VM* well enough to translate it correctly.
