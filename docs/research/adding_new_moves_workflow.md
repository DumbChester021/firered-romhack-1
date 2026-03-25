# Adding New Moves to pokefirered — Complete Workflow

This document maps every file and data structure that must be touched when adding a completely new move to the decomp. Steps are ordered by dependency — later steps reference IDs defined in earlier ones.

---

## Overview: All Touchpoints

| # | Category | File(s) | What it does |
|---|----------|---------|--------------|
| 1 | Move ID constant | [moves.h](file:///mnt/data/Github/prototype/firered-romhack-1/include/constants/moves.h) | `#define MOVE_XYZ <id>` and `MOVES_COUNT` |
| 2 | Battle stats | [battle_moves.h](file:///mnt/data/Github/prototype/firered-romhack-1/src/data/battle_moves.h) | Power, type, accuracy, PP, effect, flags, target, priority, category |
| 3 | Display name | [move_names.h](file:///mnt/data/Github/prototype/firered-romhack-1/src/data/text/move_names.h) | In-game name string (max **12 chars**) |
| 4 | Description | [move_descriptions.c](file:///mnt/data/Github/prototype/firered-romhack-1/src/move_descriptions.c) | Description text + pointer array entry |
| 5 | Effect ID (if new) | [battle_move_effects.h](file:///mnt/data/Github/prototype/firered-romhack-1/include/constants/battle_move_effects.h) | `#define EFFECT_XYZ <id>` — only if no existing effect matches |
| 6 | Effect logic (if new) | [src/battle_script_commands.c](file:///mnt/data/Github/prototype/firered-romhack-1/src/battle_script_commands.c), [data/battle_scripts_1.s](file:///mnt/data/Github/prototype/firered-romhack-1/data/battle_scripts_1.s) | Battle script / C handler for the new effect |
| 7 | Level-up learnsets | [level_up_learnsets.h](file:///mnt/data/Github/prototype/firered-romhack-1/src/data/pokemon/level_up_learnsets.h) | `LEVEL_UP_MOVE(lvl, MOVE_XYZ)` per species |
| 8 | Egg moves | [egg_moves.h](file:///mnt/data/Github/prototype/firered-romhack-1/src/data/pokemon/egg_moves.h) | Add to species egg move lists |
| 9a | TM/HM move list | [party_menu.h](file:///mnt/data/Github/prototype/firered-romhack-1/src/data/party_menu.h) (L1197) | `sTMHMMoves[]` and `sTMHMMoves_Duplicate[]` — maps TM slot → move |
| 9b | TM/HM compatibility | [tmhm_learnsets.h](file:///mnt/data/Github/prototype/firered-romhack-1/src/data/pokemon/tmhm_learnsets.h) | 64-bit bitmask per species; `TMHM(TM##_NAME)` |
| 10 | Move tutor | [moves.h](file:///mnt/data/Github/prototype/firered-romhack-1/include/constants/moves.h) (L365+) | `MOVETUTOR_XYZ` defines + tutor learnset tables |
| 11 | Battle animation | [battle_anim_scripts.s](file:///mnt/data/Github/prototype/firered-romhack-1/data/battle_anim_scripts.s) | `gBattleAnims_Moves` pointer table + animation script |
| 12 | AI scripts | [battle_ai_scripts.s](file:///mnt/data/Github/prototype/firered-romhack-1/data/battle_ai_scripts.s) | Effect-based AI checks + optional move-specific checks (e.g. soundproof list) |
| 13 | Easy Chat | [easy_chat_group_move_1.h](file:///mnt/data/Github/prototype/firered-romhack-1/src/data/easy_chat/easy_chat_group_move_1.h), [easy_chat_group_move_2.h](file:///mnt/data/Github/prototype/firered-romhack-1/src/data/easy_chat/easy_chat_group_move_2.h) | Makes the move selectable in Easy Chat |

---

## Step-by-Step

### Step 1 — Define the Move ID

**File:** [moves.h](file:///mnt/data/Github/prototype/firered-romhack-1/include/constants/moves.h)

1. Add a new `#define MOVE_XYZ <next_id>` before `MOVES_COUNT`.
2. Increment `MOVES_COUNT` to match.

```c
#define MOVE_PSYCHO_BOOST 354
#define MOVE_XYZ          355   // ← new
#define MOVES_COUNT       356   // ← was 355
```

> [!IMPORTANT]
> The move ID determines the index into **every** move-indexed array in the codebase. All subsequent tables must have an entry at this index.

---

### Step 2 — Define Battle Stats

**File:** [battle_moves.h](file:///mnt/data/Github/prototype/firered-romhack-1/src/data/battle_moves.h)

Add a struct entry inside `gBattleMoves[MOVES_COUNT]`:

```c
[MOVE_XYZ] =
    {
        .effect = EFFECT_HIT,           // or new effect from Step 5
        .power = 80,
        .type = TYPE_NORMAL,
        .accuracy = 100,
        .pp = 15,
        .secondaryEffectChance = 0,
        .target = MOVE_TARGET_SELECTED,
        .priority = 0,
        .flags = FLAG_MAKES_CONTACT | FLAG_PROTECT_AFFECTED |
                 FLAG_MIRROR_MOVE_AFFECTED | FLAG_KINGS_ROCK_AFFECTED,
        .category = SPLIT_PHYSICAL,     // or SPLIT_SPECIAL / SPLIT_STATUS
    },
```

**Key fields explained:**

| Field | Values/Notes |
|-------|------|
| `.effect` | From [battle_move_effects.h](file:///mnt/data/Github/prototype/firered-romhack-1/include/constants/battle_move_effects.h). Determines the battle script. Reuse existing effects when possible. |
| `.type` | `TYPE_NORMAL`, `TYPE_FIRE`, `TYPE_FAIRY`, etc. from `constants/pokemon.h` |
| `.target` | `MOVE_TARGET_SELECTED`, `MOVE_TARGET_BOTH`, `MOVE_TARGET_USER`, etc. |
| `.flags` | Bitwise OR of: `FLAG_MAKES_CONTACT`, `FLAG_PROTECT_AFFECTED`, `FLAG_MIRROR_MOVE_AFFECTED`, `FLAG_MAGIC_COAT_AFFECTED`, `FLAG_SNATCH_AFFECTED`, `FLAG_KINGS_ROCK_AFFECTED` |
| `.category` | `SPLIT_PHYSICAL`, `SPLIT_SPECIAL`, `SPLIT_STATUS` (your hack has the phys/special split) |

---

### Step 3 — Add the Display Name

**File:** [move_names.h](file:///mnt/data/Github/prototype/firered-romhack-1/src/data/text/move_names.h)

```c
[MOVE_XYZ] = _("MOVE NAME"),
```

> [!WARNING]
> Max length is **12 characters** (`MOVE_NAME_LENGTH` in [include/constants/global.h](file:///mnt/data/Github/prototype/firered-romhack-1/include/constants/global.h) L67). The name is displayed in ALL CAPS in Gen 3.

---

### Step 4 — Add the Description

**File:** [move_descriptions.c](file:///mnt/data/Github/prototype/firered-romhack-1/src/move_descriptions.c)

Two parts in this file:

**Part A** — Define the description string (before the pointer array):
```c
const u8 gMoveDescription_Xyz[] = _("A first line\nsecond line\nthird line\nfourth line.");
```

**Part B** — Add to the pointer array `gMoveDescriptionPointers[]`:
```c
[MOVE_XYZ - 1] = gMoveDescription_Xyz,
```

> [!NOTE]
> The pointer array is offset by `-1` because `MOVE_NONE` (0) has no description. Each line is separated by `\n`. The description box fits ~4 lines of ~18 chars each.

---

### Step 5 — Define a New Effect (Only If Needed)

If an existing `EFFECT_*` already describes the behavior you want (e.g., `EFFECT_HIT`, `EFFECT_BURN_HIT`, `EFFECT_FLINCH_HIT`), **skip this step** and reuse it.

If the move needs new battle logic:

**File:** [battle_move_effects.h](file:///mnt/data/Github/prototype/firered-romhack-1/include/constants/battle_move_effects.h)

```c
#define EFFECT_CAMOUFLAGE 213
#define EFFECT_XYZ        214   // ← new
```

Then implement the battle script in [data/battle_scripts_1.s](file:///mnt/data/Github/prototype/firered-romhack-1/data/battle_scripts_1.s) and/or the C handler in [src/battle_script_commands.c](file:///mnt/data/Github/prototype/firered-romhack-1/src/battle_script_commands.c). This is the most complex part — it requires understanding the battle engine scripting system.

---

### Step 6 — Assign to Pokémon Learnsets

Three independent learnset systems:

#### 6a. Level-Up Learnsets

**File:** [level_up_learnsets.h](file:///mnt/data/Github/prototype/firered-romhack-1/src/data/pokemon/level_up_learnsets.h)

Add `LEVEL_UP_MOVE(level, MOVE_XYZ)` to each species that learns it by level:

```c
static const u16 sBulbasaurLevelUpLearnset[] = {
    LEVEL_UP_MOVE(1, MOVE_TACKLE),
    // ...
    LEVEL_UP_MOVE(30, MOVE_XYZ),    // ← new
    LEVEL_UP_END
};
```

> [!NOTE]
> Level-up entries must be sorted by ascending level. Entries at the same level are learned in array order.

#### 6b. Egg Moves

**File:** [egg_moves.h](file:///mnt/data/Github/prototype/firered-romhack-1/src/data/pokemon/egg_moves.h)

```c
egg_moves(BULBASAUR,
          MOVE_LIGHT_SCREEN,
          // ...
          MOVE_XYZ),    // ← new
```

#### 6c. TM/HM Compatibility (if the move is a TM)

**File:** [tmhm_learnsets.h](file:///mnt/data/Github/prototype/firered-romhack-1/src/data/pokemon/tmhm_learnsets.h)

For every species that can learn the TM, add the `TMHM()` bit:

```c
[SPECIES_BULBASAUR] = TMHM_LEARNSET(TMHM(TM06_TOXIC)
                                    | TMHM(TM51_XYZ)   // ← new
                                    // ...
                                    ),
```

> [!CAUTION]
> The TM/HM system uses a **64-bit bitmask** (stored as two `u32`s). FireRed has 50 TMs + 8 HMs = 58 slots used out of 64 max. Adding new TMs beyond 64 total requires expanding this system.

Additionally, you must update the TM move list tables:

**File:** [party_menu.h](file:///mnt/data/Github/prototype/firered-romhack-1/src/data/party_menu.h)

Update both `sTMHMMoves[]` (L1197) and `sTMHMMoves_Duplicate[]` (L970) to include the new TM's move at the correct index.

You'll also need a corresponding `ITEM_TM##_XYZ` in the items constants.

---

### Step 7 — Move Tutor (Optional)

**File:** [moves.h](file:///mnt/data/Github/prototype/firered-romhack-1/include/constants/moves.h) (bottom section, L365+)

Add `#define MOVETUTOR_XYZ <next_index>` and update the move tutor learnset tables (separate per-species bitmask tables, similar to TM/HM).

---

### Step 8 — Battle Animation

**File:** [battle_anim_scripts.s](file:///mnt/data/Github/prototype/firered-romhack-1/data/battle_anim_scripts.s)

The `gBattleAnims_Moves` table is a `.4byte` pointer array indexed by move ID. Each entry points to an animation script.

**Shortcut:** Point to an existing animation script of a similar move. Example:
```asm
.4byte Move_THUNDERBOLT   @ re-use Thunderbolt's animation for your new move
```

**Full custom animation** requires:
1. Writing an animation script using the battle anim macro language
2. Potentially adding sprite sheets under `graphics/battle_anims/`
3. Adding sprite/palette entries in `src/data/battle_anim.h` or the relevant `battle_anim_*.c` type file

**Porting RHH (pokeemerald-expansion) animations natively:**
Thanks to the upgraded compiler, you can directly 1:1 port Gen 9 animations from RHH to FireRed:
1. Locate the target move's animation script in RHH's `data/battle_anim_scripts.s` (e.g., `gBattleAnimMove_ZenHeadbutt`).
2. Copy it exactly to `firered-romhack-1/data/battle_anim_scripts.s` and link it in the `gBattleAnims_Moves` array.
3. If the script uses unknown macros (e.g., `create_basic_hitsplat_sprite`, `simple_palette_blend`), copy those macro text definitions from RHH's `asm/macros/battle_anim_script.inc` into FireRed's `asm/macros/battle_anim_script.inc` to wrap the standard `createsprite` opcode.
4. Run `make` to catch missing linker dependencies (SpriteTemplates, AnimTasks, AffineAnims).
5. Search RHH's `src/battle_anim_*.c` files for the missing components (e.g., `gZenHeadbuttSpriteTemplate`, `AnimAquaTail`) and port them into FireRed's `src/battle_anim_new.c` (or a relevant file).
6. Ensure any imported `SpriteTemplate`s have `.anims = gDummySpriteAnimTable` and `.images = NULL` added if they weren't explicitly defined in Emerald, to properly match FireRed's struct shape.
7. Recompile. The FireRed `preproc` compiler natively parses RHH's Python-style kwargs (`x=0, y=0`), enabling perfectly 1:1 visual ports!

> [!TIP]
> For initial implementation, reuse an existing animation. Custom animations can be added later and are the most time-consuming part.

---

### Step 9 — AI Handling

**File:** [battle_ai_scripts.s](file:///mnt/data/Github/prototype/firered-romhack-1/data/battle_ai_scripts.s)

The AI operates on **effects**, not individual moves. If your new move reuses an existing effect, the AI already handles it — no changes needed.

Changes needed only when:

1. **New effect:** Add `if_effect EFFECT_XYZ, AI_CBM_XyzHandler` to both `AI_CheckBadMove` and `AI_CheckViability` sections, then write the handler logic.

2. **Sound-based move:** If the move is sound-based, add it to the Soundproof check list at `AI_CheckBadMove_CheckSoundproof`:
```asm
if_move MOVE_XYZ, Score_Minus10
```

3. **Move-specific AI logic:** Occasionally moves need individual checks beyond their effect (rare).

---

### Step 10 — Easy Chat (Optional)

**Files:**
- [easy_chat_group_move_1.h](file:///mnt/data/Github/prototype/firered-romhack-1/src/data/easy_chat/easy_chat_group_move_1.h)
- [easy_chat_group_move_2.h](file:///mnt/data/Github/prototype/firered-romhack-1/src/data/easy_chat/easy_chat_group_move_2.h)

Add `MOVE_XYZ` to one of the arrays (they're alphabetically sorted). This makes the move name available in the Easy Chat system (e.g., for naming Pokémon in chat).

Low priority — can be skipped initially.

---

### Step 11 — Field Move (Only if Applicable)

If the new move is usable outside of battle (like Cut, Fly, Surf):

**File:** [party_menu.h](file:///mnt/data/Github/prototype/firered-romhack-1/src/data/party_menu.h)

- Add to `sFieldMoves[]` array (L1158)
- Add a field move description to `sFieldMoveDescriptionTable[]` (L648)
- Add cursor callback entry to `sFieldMoveCursorCallbacks[]` (L1168)
- Implement the field move setup function

This is a major feature addition — most new moves won't need this.

---

## Quick Reference: Minimum Viable Move

For a new move using an **existing effect** and **no TM/tutor**, the minimum files to touch:

| File | Change |
|------|--------|
| `include/constants/moves.h` | Add ID, bump count |
| `src/data/battle_moves.h` | Add stats struct |
| `src/data/text/move_names.h` | Add display name |
| `src/move_descriptions.c` | Add description + pointer |
| `data/battle_anim_scripts.s` | Add animation pointer (reuse existing) |
| `src/data/pokemon/level_up_learnsets.h` | Add to at least one species |

That's **6 files** minimum.

---

## Constraints & Gotchas

| Constraint | Detail |
|------------|--------|
| Name length | Max 12 characters (`MOVE_NAME_LENGTH`) |
| TM bitmask | 64 bits max → 64 TMs+HMs total. Currently 58 used. |
| Level-up encoding | `LEVEL_UP_MOVE(lvl, move)` = `(lvl << 9) | move` → max move ID = **511** (9 bits) |
| Array ordering | `gBattleMoves`, `gMoveNames`, `gMoveDescriptionPointers` are all indexed by move ID — entries must exist at the correct index |
| Description offset | `gMoveDescriptionPointers` is size `MOVES_COUNT - 1`, indexed by `MOVE_XYZ - 1` |
| Animation table | `gBattleAnims_Moves` must have an entry for every move or the game will crash on use |

> [!CAUTION]
> The 9-bit encoding in `LEVEL_UP_MOVE` means the **maximum move ID is 511**. The current count is 354, giving room for ~157 new moves before this limit is hit. Beyond 511 requires changing the encoding macro.

---

## Your Current Checklist (Validated & Expanded)

- [ ] **Move Base Stats/Info** → Steps 1–4 (ID, stats, name, description)
- [ ] **Effect Logic** → Step 5–6 (only if new effect needed)
- [ ] **Learnsets/Movesets/Egg Moves/TMs** → Step 6a/6b/6c
- [ ] **Move Tutor** → Step 7
- [ ] **AI** → Step 9
- [ ] **Animation/Graphics** → Step 8
- [ ] **Easy Chat** → Step 10 (you were missing this)
- [ ] **Field Move UI** → Step 11 (you were missing this — only for overworld-usable moves)
