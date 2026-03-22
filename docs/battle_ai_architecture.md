# Battle AI Architecture

> **Audience**: A developer with no prior context on this codebase.  
> **Purpose**: Fully document the ported C Battle AI system, its flags, utilities, testing strategy, and extension points. Sufficient to continue work without needing to read prior conversation history.

---

## 1. Overview

FireRed's original AI was an **ASM bytecode interpreter** (`data/battle_ai_scripts.s`). Each AI "flag" was a script executed by the VM in `src/battle_ai_script_commands.c`.

We replaced this with a **native C dispatch table** (`src/battle_ai_main.c`). The VM infrastructure is still present (and its scripts still exist as dead code) but is no longer called. The ASM scripts are scheduled for removal in **Phase 6**.

### Key Files

| File | Role |
|---|---|
| `src/battle_ai_main.c` | All AI flag implementations + dispatch table |
| `src/battle_ai_util.c` | Shared AI utilities (damage calc, speed check, etc.) |
| `src/battle_ai_script_commands.c` | Entry point: `BattleAI_ChooseMoveOrAction()`, `BattleAI_SetupAIData()` |
| `include/battle_ai_main.h` | Exposes `gAIFunctionTable`, `AIFunc` typedef |
| `include/battle_ai_util.h` | Exposes utility function declarations |
| `include/constants/battle_ai.h` | AI flag constants (`AI_SCRIPT_*`) |
| `data/battle_ai_scripts.s` | **Dead code** — original ASM scripts, pending removal |

---

## 2. Control Flow

```
Battle turn start
└─ HandleTurnActionSelectionState()  [src/battle_main.c]
   └─ BtlController_EmitChooseAction() → AI controller response
      └─ BattleAI_ChooseMoveOrAction()  [src/battle_ai_script_commands.c]
         ├─ [Phase 4b] AI_EvaluateSwitch() → if switch: return B_ACTION_SWITCH
         ├─ BattleAI_SetupAIData()      → initializes scores[4] = 100 each
         └─ BattleAI_DoAIProcessing()   → iterates set bits in aiFlags
            └─ for each flag bit set:
               └─ gAIFunctionTable[flagIndex](battlerAtk, battlerDef, move, score)
                  → returns adjusted score
         └─ pick move slot with highest score
```

---

## 3. AI Flags

Each flag is a bit in `gTrainers[trainerIdx].aiFlags` (see `include/constants/battle_ai.h`). The dispatch table `gAIFunctionTable[]` in `battle_ai_main.c` maps bit index → C function.

Every flag function has the signature:
```c
static s32 FlagName(u8 battlerAtk, u8 battlerDef, u16 move, s32 score);
```
It receives the current move being evaluated and the running score, and returns the adjusted score.

### Flag Reference

| Bit | Constant | Function | Behavior | Vanilla source lines |
|---|---|---|---|---|
| 0 | `AI_SCRIPT_CHECK_BAD_MOVE` | `AI_CheckBadMove` | Applies `score - 10` for pointless/impossible moves. Checks type immunity, ability immunities, already-statused foe, maxed stats, etc. | ASM 52–631 |
| 1 | `AI_SCRIPT_CHECK_VIABILITY` | `AI_CheckViability` | Fine-tunes score +/- based on context (HP %, weather, stat stages, speed). 40+ per-effect handlers. | ASM 653–2766 |
| 2 | `AI_SCRIPT_TRY_TO_FAINT` | `AI_TryToFaint` | Uses `AI_CalcDamage()` to check if move can KO. +5 if yes, +7 if KO with priority while outsped. | ASM 2767–2789 |
| 3 | `AI_SCRIPT_SETUP_FIRST_TURN` | `AI_SetupFirstTurn` | On turn 0 only: +2 (random 80/256 chance) if move is a setup effect (50-entry list). | ASM 2791–2858 |
| 4 | `AI_SCRIPT_RISKY` | `AI_Risky` | +2 (random 128/256 chance) for 19 "risky" effects (OHKO, Metronome, Counter, etc.). | ASM 2869–2898 |
| 5 | `AI_SCRIPT_PREFER_STRONGEST_MOVE` | `AI_PreferStrongestMove` | Random +2 for zero-power (status) moves. Mirrors `get_how_powerful_move_is`. | ASM 2860–2867 |
| 6 | `AI_SCRIPT_PREFER_BATON_PASS` | `AI_PreferBatonPass` | +3 for setup moves when user has Baton Pass in its moveset. | ASM 2900–2947 |
| 7 | `AI_SCRIPT_DOUBLE_BATTLE` | `AI_DoubleBattle` | Empty in FRLG. Returns score unchanged. | ASM 2950–2951 |
| 8 | `AI_SCRIPT_HP_AWARE` | `AI_HPAware` | Based on user/target HP bracket (>70 / >30 / ≤30): penalizes setup/recovery moves when they're inappropriate. Four HP-bracket effect lists. | ASM 2953–3260 |
| 9 | `AI_SCRIPT_SMART_SWITCHING` | `AI_SmartSwitching` | **Phase 4b — not yet implemented.** Pre-move: evaluates whether to switch. No-op scoring slot. | New |
| 20 | `AI_SCRIPT_ROAMING` | `AI_Roaming` | Roaming legendary battles. No scoring (handled elsewhere). | — |
| 21 | `AI_SCRIPT_SAFARI` | `AI_Safari` | Safari zone. No scoring. | — |
| 22 | `AI_SCRIPT_FIRST_BATTLE` | `AI_FirstBattle` | Trainer's first battle scripting. No scoring. | — |

### Which trainers use which flags

Default flag assignment in `BattleAI_SetupAIData()`:

| Trainer type | Default flags |
|---|---|
| Generic trainer (Lv ≤ 20) | `CHECK_BAD_MOVE` |
| Generic trainer (Lv > 20) | `CHECK_BAD_MOVE | TRY_TO_FAINT | CHECK_VIABILITY` |
| Named trainer (gym leaders, rivals) | Defined in `gTrainers[]` in `src/data/trainers.h` |
| Safari | `AI_SCRIPT_SAFARI` only |
| Roaming | `AI_SCRIPT_ROAMING` only |

---

## 4. Utility Layer (`battle_ai_util.c/h`)

```c
// Damage estimation — wraps AI_CalcDmg + TypeCalc
s32  AI_CalcDamage(u16 move, u8 battlerAtk, u8 battlerDef, u8 *typeFlags);

// Speed comparison (accounts for stat stages, paralysis)
bool8 AI_IsFaster(u8 battlerAtk, u8 battlerDef, u16 move);

// Scan battler's known moveset for a given effect
bool8 AI_HasMoveEffect(u8 battler, u8 effect);

// Count alive party members not currently on field
u8 AI_CountAlivePokemon(u8 battler);
```

### Gen 4+ Extension Stubs

The following are declared in `battle_ai_util.h` but return 0/FALSE. When Gen 4+ mechanics are added, implement these:

```c
// Returns a simple "rating" for an ability in battle context (0 = bad, higher = better)
// GEN4_STUB: always returns 0
s32 AI_GetAbilityRating(u8 ability);

// Returns TRUE if a terrain effect is currently active
// GEN4_STUB: always returns FALSE (no terrain in FRLG)
bool8 AI_IsTerrainActive(u8 terrainFlag);

// Returns TRUE if Trick Room is active
// GEN4_STUB: always returns FALSE
bool8 AI_IsTrickRoomActive(void);
```

---

## 5. Smart Switching (`AI_SCRIPT_SMART_SWITCHING`, bit 9) — Design

> **Status**: Planned (Phase 4b). Not yet implemented.

### Architecture

Smart switching runs **before** move selection, not inside the per-move scoring loop. The hook point is `BattleAI_ChooseMoveOrAction()`:

```c
// In BattleAI_ChooseMoveOrAction(), before BattleAI_SetupAIData():
if (AI_THINKING_STRUCT->aiFlags & AI_SCRIPT_SMART_SWITCHING)
{
    u8 switchTarget = AI_EvaluateSwitch(battlerAtk, battlerDef);
    if (switchTarget != PARTY_SIZE)
    {
        *(gBattleStruct->monToSwitchIntoId + battlerAtk) = switchTarget;
        return B_ACTION_SWITCH;
    }
}
```

`B_ACTION_SWITCH` is already handled by `HandleTurnActionSelectionState()` in `battle_main.c`. `gBattleStruct->monToSwitchIntoId[battler]` stores which party slot to switch to.

### `AI_EvaluateSwitch()` Logic

```c
u8 AI_EvaluateSwitch(u8 battlerAtk, u8 battlerDef):
  1. if CountAlive(battlerAtk) == 0: return PARTY_SIZE  // no one to switch to
  2. Compute "matchup score" for current mon vs battlerDef:
     - All 4 moves not very effective OR immune → bad matchup
     - Defender's ability absorbs attacker's primary STAB type → very bad
     - Attacker is paralyzed/confused AND slower than target → bad
  3. If not bad matchup: return PARTY_SIZE (no switch)
  4. For each benched party member (alive, not on field):
     - Compute "candidate score": type coverage + speed advantage
  5. If best candidate score >= SWITCH_THRESHOLD (3): return that slot
  6. Else: return PARTY_SIZE
```

### Trainer Flag Usage

To enable smart switching for a trainer, add `AI_SCRIPT_SMART_SWITCHING` to its `aiFlags` in `src/data/trainers.h`:
```c
// Example: Blaine uses smart switching
{ .partyFlags = ..., .aiFlags = AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT
                               | AI_SCRIPT_CHECK_VIABILITY | AI_SCRIPT_SMART_SWITCHING, ... }
```

---

## 6. Important Globals Reference

These are the key globals the AI reads. Understanding them is essential for any AI work.

| Global | Type | What it holds |
|---|---|---|
| `gBattleMons[battler]` | `struct BattlePokemon` | All battle stats for all 4 battler slots |
| `gBattleMons[b].statStages[STAT_*]` | `u8` | Stat stages (6 = neutral, 0 = -6, 12 = +6) |
| `gBattleMons[b].status1` | `u32` | STATUS1_* flags (sleep, burn, paralysis, etc.) |
| `gBattleMons[b].status2` | `u32` | STATUS2_* flags (confusion, infatuation, etc.) |
| `gStatuses3[battler]` | `u32` | STATUS3_* flags (leech seed, embargo, etc.) |
| `gSideStatuses[side]` | `u16` | SIDE_STATUS_* (reflect, light screen, spikes, etc.) |
| `gBattleWeather` | `u16` | B_WEATHER_* flags |
| `gLastMoves[battler]` | `u16` | Last move used by each battler |
| `gDisableStructs[battler]` | `struct DisableStruct` | Disable, Encore, firstTurn, stockpile, etc. |
| `AI_THINKING_STRUCT->aiFlags` | `u32` | Current AI flag bitmask |
| `AI_THINKING_STRUCT->score[i]` | `s32` | Score for move slot i (initialized to 100) |
| `gBattleResults.battleTurnCounter` | `u8` | Turns elapsed (0 on first turn) |

---

## 7. Adding a New AI Flag

1. **Add constant** in `include/constants/battle_ai.h`:
   ```c
   #define AI_SCRIPT_MY_NEW_FLAG  (1 << 10)
   ```

2. **Declare function** in the forward-declared section of `src/battle_ai_main.c`:
   ```c
   static s32 AI_MyNewFlag(u8 battlerAtk, u8 battlerDef, u16 move, s32 score);
   ```

3. **Add to table** in `gAIFunctionTable`:
   ```c
   [10] = AI_MyNewFlag,
   ```

4. **Implement** the function. Return `score` unchanged for moves you don't want to affect.

5. **Assign to trainers** in `src/data/trainers.h` or in `BattleAI_SetupAIData()`.

---

## 8. Adding Support for a New Move Effect

When adding a move with a new `EFFECT_*` constant:

1. Define the constant in `include/constants/battle_move_effects.h`.
2. Add a `case EFFECT_MY_NEW_EFFECT:` in `AI_CheckBadMove()` to filter impossible uses.
3. Add a `case EFFECT_MY_NEW_EFFECT:` in `AI_CheckViability()` to tune the score.
4. Add to `AI_HPAware`'s effect lists if it's a setup/support move.

If the move is Gen 4+ and not yet mechanically implemented in the game engine, add a `// GEN4_STUB` comment and return `score` unchanged.

---

## 9. Testing Strategy

### Build Verification
```bash
make -j$(nproc) 2>&1 | grep "error:"
wc -c pokefirered_modern.gba  # must be exactly 16777216 (16MB)
```

### Behavioral Smoke Tests (Manual, mGBA)

| Test | Steps | Pass Condition |
|---|---|---|
| Boot check | Open ROM, reach title | No freeze, correct graphics |
| Wild battle | Enter tall grass, fight | Wild mon uses a move, no crash |
| Trainer without switch flag | Fight Brock | AI uses moves, never voluntarily switches |
| Trainer with switch flag | Modify `aiFlags` in `src/data/trainers.h`, fight | AI switches when outmatched |
| Bad move filter | Put player in a state that makes AI's move useless (e.g., already poisoned) | AI avoids re-applying poison |
| KO pressure | Get player mon to 1HP, AI has killing move | AI picks the killing move |

### Common Failure Signatures

| Symptom | Likely cause |
|---|---|
| Freeze on trainer turn | Null function pointer in `gAIFunctionTable` or bad flag index |
| AI picks move slot 0 every turn | `score[]` all at 100, no differentiation |
| AI re-applies poison/sleep | `AI_CheckBadMove` status check missing |
| AI never switches | `AI_EvaluateSwitch` threshold too high or bail condition too strict |
| Game boots but crashes in battle | `AI_CalcDamage` reading bad memory (check utility includes) |

---

## 10. What We Did NOT Port (Future Work)

These RHH features are not present and were deliberately skipped:

| Feature | Reason skipped |
|---|---|
| `AI_FLAG_WEIGH_ABILITY_ACTIVATION` | Requires full ability interaction matrix |
| `AI_FLAG_ACE_POKEMON` | Requires trainer data extension |
| Expanded `AI_DoubleBattle` targeting | Only useful if double-battle trainers are prioritized |
| Gen 4+ terrain/weather scoring | Terrain doesn't exist in FRLG engine |
| Full `AI_CheckViability` parity with RHH | RHH has 200+ handlers for Gen 4-9 moves |

To implement any of these, follow the pattern in Section 7.

---

## 11. Phase Status

| Phase | Description | Status |
|---|---|---|
| Phase 0 | Housekeeping (remove Natural Gift) | ✅ Done |
| Phase 1 | Branch setup (`feature-AI-upgrade`) | ✅ Done |
| Phase 2 | Research & planning | ✅ Done |
| Phase 2.5 | `battle_ai_util.c/h` (damage calc utilities) | ✅ Done |
| Phase 3 | Structural plumbing (C dispatch table, `BattleAI_DoAIProcessing` rewrite) | ✅ Done |
| Phase 4 | All 9 AI flags ported from ASM to C | ✅ Done |
| Phase 4b | Smart switching + Gen 4+ stubs | 🔄 In progress |
| Phase 5 | Automated AI test framework (in-ROM DSL from RHH) | ⏳ Pending |
| Phase 6 | Remove dead ASM scripts from `data/battle_ai_scripts.s` | ⏳ Pending |
