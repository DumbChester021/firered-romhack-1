# Move Engine Architecture Upgrade Research

> **Purpose:** Defines the structural gaps between FireRed's move engine and RHH's `MoveInfo`
> system, and prescribes the minimal porting work that unblocks Gen 4+ moves, updated
> stats/learnsets, and new mechanics. Scope is **Gen 1–3 fidelity with a scalable foundation**,
> not a full RHH feature parity port.

---

## Background: What Breaks Without This

FireRed's `BattleMove` struct is 10 bytes and was designed for Gen 1–3 only. Adding Gen 4+
moves hits these hard limits in the current struct:

| Limit | Current | Symptom |
|---|---|---|
| `effect` is `u8` | Max 255 effects | Gen 4+ has 300+ effects. ID overflow = wrong effect fires. |
| `flags` is `u8` | 8 flags (5 used, 3 free) | Can't express: punch/bite/sound/wind/dance/slice/ballistic/powder per move. Needed for abilities like Iron Fist, Soundproof, etc. |
| One secondary effect per move | `secondaryEffectChance` implies a single `effect` | Can't represent moves with 2 secondary effects (e.g. Sparkling Aria: heals burn + doesn't make contact). |
| No `argument` field | Two-turn moves hardcode via `effect` enum | Sky Drop, Phantom Force, etc. pass STATUS3 bit via `argument` in RHH. Without it, new two-turn moves need a special-cased effect ID per move. |
| `power` is `u8` | Max 255 | Z-Moves (need 200+ for some) are fine, but technically a constraint. |
| `LevelUpMove.move` is 9-bit | Max move ID 511 | Hit at 157 new moves. Changing encoding requires touching `GetLevelUpMovesBySpecies()` and `GetMonLevelUpMoves()`. |
| Move data in 4–6 files | No structural limit | Every new move requires edits to `battle_moves.h`, `move_names.h`, `move_descriptions.c`, `battle_anim_scripts.s`. High friction, easy to desync. |

**Audit baseline** (`python3 tools/audit_move_engine.py` — 2026-03-23):
- 11 × `.flags & FLAG_*` bitfield access — `battle_script_commands.c`, `battle_util.c`
- 7 × `u8 effect` local (silent truncation) — `battle_ai_main.c`
- 19 × `LEVEL_UP_MOVE_LV/ID` bitmask + sentinel — `pokemon.c`
- **0** ASM `gBattleMoves` references — struct expansion is ASM-safe

---

## Struct Comparison: FireRed vs RHH

### FireRed `struct BattleMove` (`include/pokemon.h:238`)

```c
struct BattleMove {
    u8  effect;               // max 255 effects — HARD LIMIT
    u8  power;                // max 255 power
    u8  type;
    u8  accuracy;
    u8  pp;
    u8  secondaryEffectChance; // only ONE secondary effect per move
    u8  target;
    s8  priority;
    u8  flags;                // 8-bit bitfield — HARD LIMIT (8 flags max)
    u8  category;             // SPLIT_PHYSICAL/SPECIAL/STATUS (our addition)
};
// Total: 10 bytes
```

Current flag bits (`include/constants/battle.h`):
```
FLAG_MAKES_CONTACT
FLAG_PROTECT_AFFECTED
FLAG_MAGIC_COAT_AFFECTED
FLAG_SNATCH_AFFECTED
FLAG_MIRROR_MOVE_AFFECTED  ← effectively 5 used, 3 free
FLAG_KINGS_ROCK_AFFECTED
FLAG_SOUND_MOVE            ← free slot
FLAG_UNUSED                ← free slot
```

### RHH `struct MoveInfo` (`include/pokemon.h:461`)

```c
struct MoveInfo {
    const u8 *name;           // embedded — no more move_names.h
    const u8 *description;    // embedded — no more move_descriptions.c
    u16 effect;               // 65535 effects possible
    u16 type:5;
    u16 category:2;
    u16 power:9;              // up to 511
    u16 accuracy:7;
    u16 target:9;
    u8  pp;
    union { u8 effect; u8 powerOverride; } zMove;

    s32 priority:4;
    u32 recoil:7;             // % recoil, replaces hardcoded per-effect recoil
    u32 strikeCount:4;        // replaces EFFECT_MULTI_HIT for fixed-count moves
    u32 criticalHitStage:2;   // replaces EFFECT_HIGH_CRITICAL
    u32 alwaysCriticalHit:1;
    u32 numAdditionalEffects:2; // number of entries in additionalEffects[]

    // ~35 individual boolean flag bits (replaces 8-bit flags field):
    u32 makesContact:1;
    u32 ignoresProtect:1;
    u32 magicCoatAffected:1;
    u32 snatchAffected:1;
    u32 ignoresKingsRock:1;
    u32 punchingMove:1;       // Iron Fist, Bulletproof
    u32 bitingMove:1;         // Strong Jaw
    u32 pulseMove:1;          // Mega Launcher
    u32 soundMove:1;          // Soundproof / Throat Spray
    u32 ballisticMove:1;      // Bulletproof
    u32 powderMove:1;         // Overcoat / Grass immunity
    u32 danceMove:1;          // Dancer ability
    u32 windMove:1;           // Wind Rider / Wind Power
    u32 slicingMove:1;        // Sharpness
    u32 healingMove:1;
    u32 minimizeDoubleDamage:1;
    u32 ignoresTargetAbility:1;
    u32 damagesUnderground:1;
    u32 damagesUnderwater:1;
    u32 damagesAirborne:1;
    u32 damagesAirborneDoubleDamage:1;
    u32 thawsUser:1;
    u32 ignoresSubstitute:1;
    // ... ban flags (gravity, sleep talk, instruct, encore, etc.)
    u32 gravityBanned:1;
    u32 sleepTalkBanned:1;
    u32 instructBanned:1;
    u32 encoreBanned:1;
    // ...

    u32 argument;             // two-turn arg: STRINGID | (STATUS3_BIT << 16)

    const struct AdditionalEffect *additionalEffects; // array of secondary effects

    // Contest data (SKIP — not used in FRLG)
    u8  contestEffect;
    u8  contestCategory:3;
    u8  contestComboStarterId;
    u8  contestComboMoves[MAX_COMBO_MOVES];

    const u8 *battleAnimScript; // embedded — no more battle_anim_scripts.s table
};
// Total: ~80+ bytes (ROM-resident const data, no RAM cost)

struct AdditionalEffect {
    u16 moveEffect;
    u8  self:1;
    u8  onlyIfTargetRaisedStats:1;
    u8  onChargeTurnOnly:1;
    u8  chance; // 0 = primary effect (always), >0 = secondary %
};
```

---

## What to Port (Priority Ordered)

Port only what unblocks your immediate goals. Everything else stubs or ignores.

### Phase 1 — Expand `BattleMove` struct (Required for any Gen 4+ moves)

**Goal:** Remove the `u8 effect` and `u8 flags` hard limits. Zero save-compatibility risk
(struct is ROM data, not saved). Zero gameplay change if existing values are preserved.

**Changes to `include/pokemon.h`:**

```c
struct BattleMove {
    u16 effect;              // was u8 — now 65535 effects
    u8  power;
    u8  type;
    u8  accuracy;
    u8  pp;
    u8  secondaryEffectChance;
    u8  target;
    s8  priority;
    u8  category;

    // Replace u8 flags bitfield with individual booleans:
    u8  makesContact:1;
    u8  ignoresProtect:1;
    u8  magicCoatAffected:1;
    u8  snatchAffected:1;
    u8  mirrorMoveAffected:1;
    u8  ignoresKingsRock:1;
    u8  soundMove:1;
    u8  punchingMove:1;
    u8  bitingMove:1;
    u8  pulseMove:1;
    u8  powderMove:1;
    u8  danceMove:1;
    u8  slicingMove:1;
    u8  ballisticMove:1;
    u8  windMove:1;
    u8  healingMove:1;
    // quality-of-life:
    u8  criticalHitStage:2; // 0=normal, 1=high crit, 2=guaranteed (was EFFECT_HIGH_CRITICAL hack)
    u8  strikeCount:4;      // 0=use effect logic, 2=always 2 hits, etc.
    s8  recoil;             // % recoil in 1/100 (neg=recoil, pos=drain); 0=use effect
    // two-turn support:
    u32 argument;           // STRINGID | (STATUS3_BIT << 16) for semi-invulnerable moves
};
```

**Files to update after struct change:**
- `src/data/battle_moves.h` — replace `FLAG_*` macros with `.field = TRUE`, expand all `effect` values to match (they map 1:1 currently)
- `include/constants/battle.h` — remove `FLAG_*` defines (or keep as compat macros → `0`)
- `src/battle_script_commands.c` — all `gBattleMoves[move].flags & FLAG_X` → `gBattleMoves[move].makesContact` etc.
- `src/battle_ai_main.c` / `src/battle_ai_util.c` — same flag access pattern
- `src/battle_util.c`, `src/battle_main.c` — scan for `gBattleMoves[x].flags`

**Effort estimate:** 2–3 sessions. Mechanical, no logic changes.

---

### Phase 2 — Expand `effect` constants to u16 (`include/constants/battle_move_effects.h`)

Once `effect` is `u16` in the struct, the constants file just needs any values above 255 to be `u16`
literals (they already compile as `int`, so no change is strictly required). But document the
boundary: current FireRed effects end at `EFFECT_CAMOUFLAGE` (214). New Gen 4+ effects start at
215+. Reserve 215–499 for Gen 4, 500–699 for Gen 5, etc.

No code change needed beyond the struct field width expansion in Phase 1.

---

### Phase 3 — `additionalEffects` array (Enables multi-secondary-effect moves)

This is the RHH mechanism that replaces the `effect` + `secondaryEffectChance` single-effect
limitation. It's needed for moves like:
- Tri Attack (Burn/Freeze/Paralysis randomly)
- Sparkling Aria (heals burn target + has contact flag behavior)
- Scale Shot (raises speed, lowers defense, multi-hit)

**Minimal port:** Add to struct (Phase 1 can include this):

```c
struct AdditionalEffect {
    u16 moveEffect;
    u8  self:1;
    u8  chance; // 0=always, >0=percentage
};

struct BattleMove {
    // ... existing fields ...
    u8 numAdditionalEffects;        // 0–3
    const struct AdditionalEffect *additionalEffects;
};
```

The battle script command `SetMoveEffect()` / `TrySetCantSelectMoveTarget()` in
`src/battle_script_commands.c` needs updating to iterate `additionalEffects[]` instead of using
the single `secondaryEffectChance` path. This is the most complex part of Phase 3.

**FRLG_STUB path:** If a new move has a secondary effect that needs new infrastructure (e.g.,
applying terrain — we don't have terrain), stub the `MOVE_EFFECT_*` handler in
`src/battle_script_commands.c` to no-op, but still define the struct entry so the move's primary
damage works.

---

### Phase 4 — `LevelUpMove` encoding expansion

**Current** (`include/pokemon.h:261`):
```c
struct LevelUpMove {
    u16 move:9;   // max move ID 511
    u16 level:7;  // max level 100 (fine)
};
```

**RHH replacement:**
```c
struct LevelUpMove {
    u16 move;    // full u16, max 65535 move IDs
    u16 level;   // full u16 (level > 100 never happens but safe)
};
```

**Files to update:**
- `include/pokemon.h` — change struct
- `src/data/pokemon/level_up_learnsets.h` — `LEVEL_UP_MOVE(lvl, move)` macro becomes `{ move, lvl }`; terminator `LEVEL_UP_END` becomes `{ 0xFFFF, 0 }` or similar
- `src/pokemon.c` — `GetLevelUpMovesBySpecies()`, `GetMonLevelUpMoves()` — update terminator check

**Effort:** 1 session. Data-only change, terminator sentinel is the only tricky part.

---

### Phase 5 — Unified move data file (`gMovesInfo`)

Merges `battle_moves.h` + `move_names.h` + `move_descriptions.c` + `battle_anim_scripts.s`
table into one file. This is **pure quality-of-life** — no functional change.

```
Current: add 1 move = edit 4–6 files, must keep indexes in sync
After: add 1 move = edit 1 struct entry in moves_info.h
```

The RHH approach embeds `.name`, `.description`, and `.battleAnimScript` directly in the struct
entry. For FireRed:
- `.description` can embed directly since it's a ROM string pointer
- `.name` is trickier because FireRed uses a fixed-length encoded string array for Japanese
  charmap; can use `COMPOUND_STRING()` pattern from RHH if charmap is patched
- `.battleAnimScript` — embed pointer directly instead of using the `gBattleAnims_Moves[]` index table

This is the highest-effort phase but also the highest developer-experience payoff. Do this
**after** Phases 1–4 are working.

---

## What to NOT Port (Out of Scope)

| RHH Feature | Reason to Skip |
|---|---|
| `zMove` field | No Z-Move infrastructure in FRLG |
| `contestEffect` / `contestCategory` | No contests in FRLG |
| `contestComboMoves` | Same |
| Dynamax / Tera fields | No infrastructure |
| `gravityBanned`, `skyBattleBanned`, `instructBanned` | No Gravity move, Sky Battle, or Instruct yet — stub as `0` |
| `parentalBondBanned` | No Parental Bond ability yet |
| `encoreBanned` | Encore exists in FRLG but ban flag isn't needed for Gen 1–3 moves |
| `metronomeBanned` / `sketchBanned` | Only needed when adding moves that should be banned |

For any flag your codebase doesn't yet use: **define it in the struct but leave it `0` for all
existing moves.** Cost = 0 at runtime (ROM data), benefit = struct is forward-compatible when
you need it.

---

## Recommended Port Order

```
Phase 1 (Required first, unblocks everything):
  → Expand BattleMove struct: u8 effect → u16, u8 flags → individual fields, add argument + recoil + strikeCount

Phase 2 (Follows immediately, zero extra effort):
  → Update effect constants file to reflect u16 capacity, document ID ranges

Phase 4 (Do before adding >157 new moves):
  → LevelUpMove encoding: 9-bit → u16 move field

Phase 3 (Do when you need multi-secondary-effect moves):
  → additionalEffects array + SetMoveEffect() iteration

Phase 5 (Do when move count is large enough that 4-file friction hurts):
  → Unified moves_info.h consolidation
```

---

## Key Files Touched Per Phase

| Phase | Files Modified |
|---|---|
| 1 | `include/pokemon.h`, `include/constants/battle.h`, `src/data/battle_moves.h`, `src/battle_script_commands.c`, `src/battle_util.c`, `src/battle_main.c`, `src/battle_ai_main.c`, `src/battle_ai_util.c` |
| 2 | `include/constants/battle_move_effects.h` |
| 3 | `include/pokemon.h` (AdditionalEffect struct), `src/battle_script_commands.c` (SetMoveEffect), `src/data/battle_moves.h` |
| 4 | `include/pokemon.h` (LevelUpMove), `src/data/pokemon/level_up_learnsets.h`, `src/pokemon.c` |
| 5 | `src/data/moves_info.h` (new), `src/data/text/move_names.h` (deprecated), `src/move_descriptions.c` (deprecated), `data/battle_anim_scripts.s` (table removed) |

---

## Verification After Each Phase

Run after every phase to confirm nothing broke:

```bash
make -j$(nproc) 2>&1 | grep "error:"   # must be empty
wc -c pokefirered_modern.gba            # must be 16777216
python3 tools/verify_data.py           # Fairy/P-S/TM integrity
```

After Phase 1 specifically, also do a battle smoke test in mGBA:
1. Trainer battle → all Pokemon use moves → no crash, no wrong type display
2. Confirm a contact move (Tackle) still triggers Rough Skin / Static (flag bit still read)
3. Confirm a sound move (Growl, Snore) still bypasses Substitute (if testing that feature)
