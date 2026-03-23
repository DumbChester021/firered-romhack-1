# Battle Animation Systems — FireRed vs RHH Comparison

> **Purpose:** Reference doc for porting move animations from pokeemerald-expansion (RHH) to this FireRed romhack.

---

## Architecture Overview

Both codebases use the **same fundamental architecture**: animation scripts written in an ASM macro language (`battle_anim_scripts.s`) that reference C-side sprite templates and task functions from `battle_anim_*.c` files. The animation engine interprets bytecode commands (load graphics, create sprites, play sound, wait, etc.).

### High-Level Comparison

| Aspect | FireRed | RHH (pokeemerald-expansion) |
|---|---|---|
| Script file | `data/battle_anim_scripts.s` (11,100 lines) | `data/battle_anim_scripts.s` (34,323 lines) |
| Move animations | **356** `Move_` labels | **941** `Move_` labels |
| C source files | 27 `battle_anim_*.c` | 28 `battle_anim_*.c` |
| Extra C files in RHH | — | `battle_anim_new.c` (9,288 lines), `battle_anim_throw.c` |
| `ANIM_TAG_*` sprites | 289 (ends at `BLUE_RING_2 + 288`) | 405 (adds 116 new tags through `PURPLE_CHAIN + 404`) |
| Move backgrounds (`BG_*`) | 27 (ends at `BG_SOLAR_BEAM_CONTESTS`) | 82 (adds `BG_MAGMA_STORM` through `BG_RAINBOW`) |
| General anims (`B_ANIM_*`) | 28 entries | 53 entries |
| Special anims | 7 entries | 8 entries (+`CRITICAL_CAPTURE_THROW`) |
| Status anims | 9 entries (+`Status_Powder` absent) | 10 entries (+`Status_Powder`) |
| Trap anims | 5 (`BIND`–`SAND_TOMB`) | 9 (+`MAGMA_STORM`–`THUNDER_CAGE`) |
| Sprite data (`src/data/battle_anim.h`) | 1,625 lines | 2,021 lines |
| Include headers | `battle_anim.h`, `constants/battle_anim.h` | +`battle_anim_scripts.h`, `constants/battle_anim_scripts.h` |

---

## ASM Macro Language

### Shared Commands (0x00–0x2F)

The bytecode instruction set is **identical** between codebases. Both use the same `.inc` file at `asm/macros/battle_anim_script.inc`:

| Opcode | Macro | Purpose |
|---|---|---|
| 0x00 | `loadspritegfx TAG` | Load sprite graphics by ANIM_TAG |
| 0x01 | `unloadspritegfx TAG` | Unload sprite graphics |
| 0x02 | `createsprite template, battler, subprio, args...` | Create an animation sprite |
| 0x03 | `createvisualtask addr, priority, args...` | Create a C task for visual effects |
| 0x04 | `delay N` | Wait N frames |
| 0x05 | `waitforvisualfinish` | Wait for all sprites/tasks to finish |
| 0x08 | `end` | End animation script |
| 0x09 | `playse SE` | Play sound effect |
| 0x0A | `monbg BATTLER` | Set up battler background |
| 0x0B | `clearmonbg BATTLER` | Clear battler background |
| 0x0C | `setalpha EVA, EVB` | Set alpha blending |
| 0x0D | `blendoff` | Disable blending |
| 0x0E | `call PTR` | Call subroutine |
| 0x0F | `return` | Return from subroutine |
| 0x10 | `setarg ID, VALUE` | Set gBattleAnimArgs[ID] |
| 0x11 | `choosetwoturnanim P1, P2` | Branch based on multi-turn move |
| 0x12 | `jumpifmoveturn VAL, PTR` | Jump if on specific turn |
| 0x13 | `goto PTR` | Unconditional jump |
| 0x14 | `fadetobg BG` | Fade to background |
| 0x15 | `restorebg` | Restore default background |
| 0x19 | `playsewithpan SE, PAN` | Play sound with stereo panning |
| 0x1C | `loopsewithpan SE, PAN, WAIT, TIMES` | Loop sound with panning |
| 0x1F | `createsoundtask ADDR, args...` | Create a C task for sound |
| 0x21 | `jumpargeq ID, VAL, PTR` | Jump if arg equals value |
| 0x25 | `fadetobgfromset BG_OPP, BG_PLR, BG_CONTEST` | Fade to side-specific BG |
| 0x28 | `splitbgprio BATTLER` | Split BG priority |
| 0x2B | `invisible BATTLER` | Hide battler sprite |
| 0x2C | `visible BATTLER` | Show battler sprite |
| 0x2F | `stopsound` | Stop looping sound |

### RHH-Only Commands (0x30–0x34) — ✅ IMPLEMENTED

RHH adds 5 macros that are now also present in FireRed:

| Opcode | Macro | Purpose | Status |
|---|---|---|---|
| 0x30 | `createvisualtaskontargets` | Create visual task looped over targets | ✅ Implemented |
| 0x31 | `createspriteontargets` | Create sprite looped over targets | ✅ Implemented |
| 0x32 | `createspriteontargets_onpos` | Same but preserves battler arg position | ✅ Implemented |
| 0x33 | `jumpifmovetypeequal` | Jump if move type matches | ✅ Implemented |
| 0x34 | `createdragondartsprite` | Dragon Darts-specific sprite | ✅ Stub (parses args, no visual; needs Dreepy sprites) |

**Status:** All 5 opcodes are now functional in FireRed. The ASM macros, C handlers (`Cmd_*`), and helper functions (`GetAnimBattlerId`, `GetSubpriorityForMoveAnim`, `GetBattleAnimMoveTargets`, `CreateSpriteOnTargets`) have been ported. The `jumpifdoublebattle` convenience macro is also available.

RHH animation scripts using these macros will now assemble and execute in FireRed.

---

## Dispatch Tables

### `gBattleAnims_Moves` — Move Animation Lookup

Both codebases use a flat pointer table indexed by move ID:

```asm
gBattleAnims_Moves::
    .4byte Move_NONE        @ MOVE_NONE = 0
    .4byte Move_POUND       @ MOVE_POUND = 1
    ...
    .4byte Move_PSYCHO_BOOST @ last Gen 3 move
```

**FireRed:** 356 entries (MOVE_NONE through MOVE_PSYCHO_BOOST + `Move_COUNT` sentinel).  
**RHH:** 941+ entries (extends through all Gen 4-9 moves).

**Key difference:** In RHH, new move animations use `::` (global label, with extern in `battle_anim_scripts.h`). FireRed uses local labels with no extern header.

### Adding a New Move Animation

The process is identical in both:

1. Add a `.4byte Move_NEWMOVE` entry at the correct index in `gBattleAnims_Moves`
2. Write the `Move_NEWMOVE:` label and animation script below
3. Any new sprite graphics: add `ANIM_TAG_*` constant, graphics data in `src/data/battle_anim.h`, register in `gBattleAnimPicTable[]` / `gBattleAnimPaletteTable[]`
4. Any new C tasks: add function in appropriate `battle_anim_*.c` file, declare extern

### `gBattleAnims_General` — Non-Move Animations

**⚠ These tables are NOT compatible.** The index numbering differs:

| Index | FireRed | RHH |
|---|---|---|
| 0 | `B_ANIM_CASTFORM_CHANGE` | `B_ANIM_STATS_CHANGE` |
| 1 | `B_ANIM_STATS_CHANGE` | `B_ANIM_SUBSTITUTE_FADE` |
| 2 | `B_ANIM_SUBSTITUTE_FADE` | `B_ANIM_SUBSTITUTE_APPEAR` |
| 3 | `B_ANIM_SUBSTITUTE_APPEAR` | `B_ANIM_POKEBLOCK_THROW` |
| 4 | `B_ANIM_BAIT_THROW` | `B_ANIM_ITEM_KNOCKOFF` |
| ... | (offset by 1 for most) | (no Castform entry) |

FireRed has `B_ANIM_CASTFORM_CHANGE` at index 0 (inherited from vanilla FireRed), which RHH does not have. This means **all `B_ANIM_*` constants are off by 1** from index 1 onward, and any code referencing them needs renumbering if porting.

---

## Sprite Graphics Assets

### `ANIM_TAG_*` Constants

Both start at `ANIM_SPRITES_START = 10000` and share tags 0–288 identically. The numbering is **1:1 compatible** for existing Gen 3 sprites.

### New RHH Sprites (289–404)

RHH adds 116 new sprite assets for Gen 4+ moves:

| Range | Examples |
|---|---|
| 289–301 | `WHITE_STREAK`, `PURPLE_JAB`, `TOXIC_SPIKES`, `ENERGY_BALL`, `SEED_BROWN`, `FEINT`, `ACUPRESSURE`, `WRING_OUT` |
| 302–331 | `COLORED_ORBS`, `WORRY_SEED`, `DRAGON_PULSE`, `PSYCHO_CUT`, `STONE_EDGE`, `STEALTH_ROCK`, `POISON_JAB`, `FLASH_CANNON_BALL`, `BERRY_*`, `HYDRO_PUMP` |
| 332–404 | `DRAGON_ASCENT`, `COCOON`, `CORKSCREW`, `MUD_BOMB`, `APPLE`, `TORNADO`, `DREEPY`, `STEEL_BEAM`, `TERA_*`, `BLOOD_MOON`, `BEAM` |

### How Graphics Are Registered

Both use the same pattern in `src/data/battle_anim.h`:

```c
// Compressed sprite sheet
const struct CompressedSpriteSheet gBattleAnimPicTable[] = {
    {gBattleAnimSpriteGfx_Bone, 0x0200, ANIM_TAG_BONE},
    // ...
};

// Compressed palette
const struct CompressedSpritePalette gBattleAnimPaletteTable[] = {
    {gBattleAnimSpritePal_Bone, ANIM_TAG_BONE},
    // ...
};
```

**To port a new sprite:** copy the `.png`/`.4bpp.lz` graphics file to `graphics/battle_anims/sprites/`, add the `extern const u32` in headers, add the entry to both tables, and define the `ANIM_TAG_*` constant.

---

## C-Side Components

### Shared `battle_anim_*.c` Files

Both codebases have these files with **nearly identical** contents:

| File | Purpose | Portable? |
|---|---|---|
| `battle_anim.c` | Script interpreter, animation launch | Core engine — modify, don't replace |
| `battle_anim_bug.c` | Bug-type sprite callbacks | ✅ Direct copy |
| `battle_anim_dark.c` | Dark-type sprite callbacks | ✅ Direct copy |
| `battle_anim_dragon.c` | Dragon-type sprite callbacks | ✅ Direct copy |
| `battle_anim_effects_1.c` | General effect sprites (group 1) | ✅ Direct copy |
| `battle_anim_effects_2.c` | General effect sprites (group 2) | ✅ Direct copy |
| `battle_anim_effects_3.c` | General effect sprites (group 3) | ✅ Direct copy |
| `battle_anim_electric.c` | Electric-type sprite callbacks | ✅ Direct copy |
| `battle_anim_fight.c` | Fighting-type sprite callbacks | ✅ Direct copy |
| `battle_anim_fire.c` | Fire-type sprite callbacks | ✅ Direct copy |
| `battle_anim_flying.c` | Flying-type sprite callbacks | ✅ Direct copy |
| `battle_anim_ghost.c` | Ghost-type sprite callbacks | ✅ Direct copy |
| `battle_anim_ground.c` | Ground-type sprite callbacks | ✅ Direct copy |
| `battle_anim_ice.c` | Ice-type sprite callbacks | ✅ Direct copy |
| `battle_anim_mon_movement.c` | Battler movement tasks | ✅ Direct copy |
| `battle_anim_mons.c` | Battler sprite manipulation | ⚠ Check API diffs |
| `battle_anim_normal.c` | Normal-type / hit splats | ✅ Direct copy |
| `battle_anim_poison.c` | Poison-type sprite callbacks | ✅ Direct copy |
| `battle_anim_psychic.c` | Psychic-type sprite callbacks | ✅ Direct copy |
| `battle_anim_rock.c` | Rock-type sprite callbacks | ✅ Direct copy |
| `battle_anim_smokescreen.c` | Smokescreen effect | ✅ Direct copy |
| `battle_anim_sound_tasks.c` | Sound task functions | ✅ Direct copy |
| `battle_anim_special.c` | Ball throw, level up, switch out | ⚠ FireRed-specific (Safari) |
| `battle_anim_status_effects.c` | Status condition animations | ✅ Direct copy |
| `battle_anim_utility_funcs.c` | Utility tasks (blend, shake, etc.) | ✅ Direct copy |
| `battle_anim_water.c` | Water-type sprite callbacks | ✅ Direct copy |

### RHH-Only Files

| File | Lines | Purpose | Port Required? |
|---|---|---|---|
| `battle_anim_new.c` | 9,288 | **All Gen 4+ sprite templates and callbacks** | Yes — primary source for new move sprites |
| `battle_anim_throw.c` | ~1,500 | Ball throw mechanics (critical capture, etc.) | Only if porting ball mechanics |

**`battle_anim_new.c` is the most important file for porting.** It contains:
- `SpriteTemplate` structs for every Gen 4+ move animation (e.g., `gPowerTrickSpriteTemplate`, `gCloseCombatFistTemplate`)
- Sprite callback functions for complex new animations (e.g., `SpriteCB_LockingJaw`, `SpriteCB_PyroBallRockBounce`)
- Organized by generation: Gen 4 → Gen 5 → Gen 6 → Gen 7 → Gen 8 → Gen 9

### `battle_anim.h` Header Differences

| Feature | FireRed | RHH |
|---|---|---|
| `LaunchBattleAnimation()` | `(const u8 *const table[], u16 id, bool8 isMoveAnim)` | `(u32 animType, u32 animId)` |
| `ANIM_TYPE` enum | Not present | `ANIM_TYPE_GENERAL`, `_MOVE`, `_STATUS`, `_SPECIAL` |
| `MoveBattlerSpriteToBG()` | `(u8 battlerId, u8)` | `(u8 battlerId, bool8 toBG_2, bool8 setInvisible)` |
| `gAnimMoveIndex` | ✅ Present (renamed from `sAnimMoveIndex`) | ✅ Present |
| `GetAnimBattlerId()` | ✅ Present (ported from RHH) | ✅ Present |
| Battler coord enums | ✅ Same | ✅ Same |
| Stat anim defines | Hardcoded numbers | Uses `MOVE_EFFECT_*` math |

**`LaunchBattleAnimation` difference is cosmetic for porting purposes** — the underlying bytecode engine is the same. You don't need to change the FireRed API just to add new move animations.

---

## Background Tiles (`BG_*`)

FireRed has 27 backgrounds. RHH adds 55 more. When porting an animation that uses `fadetobg BG_XYZ` where `BG_XYZ` doesn't exist in FireRed:

1. Add the `BG_*` constant to `include/constants/battle_anim.h`
2. Add the background image/tilemap/palette to `graphics/battle_anims/backgrounds/`
3. Register it in the background loading function in `src/battle_anim.c` (the `sBattleAnimBackgroundTable` or equivalent)

Alternatively, substitute a visually similar existing background. Many RHH backgrounds are variations on themes already present (e.g., `BG_WATER_2` is similar to existing water BGs).

---

## Porting Workflow — Step by Step

### Scenario A: Porting a Move That Reuses Existing Sprites

This is the simplest and most common case for Gen 4 moves.

1. **Copy the `Move_XYZ:` script block** from RHH's `data/battle_anim_scripts.s` to FireRed's
2. **Add `.4byte Move_XYZ`** at the correct index in `gBattleAnims_Moves`
3. **Verify all `ANIM_TAG_*`** used in the script exist in FireRed — most Gen 3 tags are shared
4. **Verify all `gXyzSpriteTemplate`** references exist — if the template is from a shared `battle_anim_*.c` file, it's already available
5. **Verify all `AnimTask_*`** references exist — same check
6. **Check for RHH-only macros** (0x30–0x34) — if absent, the script will assemble without issues
7. **Build and test**

### Scenario B: Porting a Move That Needs New Sprites

1. Do everything in Scenario A
2. **Add new `ANIM_TAG_*` constant** to `include/constants/battle_anim.h`
3. **Copy graphics** from RHH's `graphics/battle_anims/sprites/` to FireRed's
4. **Add entries** to `gBattleAnimPicTable[]` and `gBattleAnimPaletteTable[]` in `src/data/battle_anim.h`
5. **Copy `SpriteTemplate`** from RHH's `battle_anim_new.c` to your own file (or create a FireRed `battle_anim_new.c`)
6. **Copy sprite callback** if it's a new function from `battle_anim_new.c`
7. **Declare externs** in `include/battle_anim.h`

### Scenario C: Porting a Move That Needs New Backgrounds

1. Do everything in Scenario A/B as needed
2. **Add `BG_*` constant** to `include/constants/battle_anim.h`
3. **Copy BG graphics** from RHH's `graphics/battle_anims/backgrounds/`
4. **Register in background table** in `src/battle_anim.c`

### Scenario D: Porting a Move Using Multi-Target Macros (0x30+)

**✅ No longer a separate scenario.** Opcodes 0x30–0x34 are now implemented in FireRed. Any RHH animation script using these macros will assemble and run without additional porting. Just follow Scenario A/B/C.

---

## Practical Strategy for Batch Porting

### Recommended Order

1. **First:** Port animations that use only existing Gen 3 sprites and tasks (many Gen 4 moves reuse them via palette swaps)
2. **Second:** Create `src/battle_anim_new.c` in FireRed as a home for new sprite templates
3. **Third:** Batch-port new `ANIM_TAG_*` graphics that many moves share (e.g., `ANIM_TAG_ENERGY_BALL`, `ANIM_TAG_STONE_EDGE`)
4. **Fourth:** Add new backgrounds as needed

### Quick Wins: Moves That Likely Need Zero New Assets

Many Gen 4+ moves in RHH reuse Gen 3 sprite tags creatively. Example pattern from RHH:

```asm
Move_CLOSE_COMBAT::
    loadspritegfx ANIM_TAG_IMPACT          @ exists in FireRed
    loadspritegfx ANIM_TAG_HANDS_AND_FEET  @ exists in FireRed
    call SetHighSpeedBg                     @ helper, check if exists
    createsprite gFistFootRandomPosSpriteTemplate, ...
```

Look for moves that only reference `ANIM_TAG_*` values ≤ 288 — those sprites already exist in FireRed.

### Stub Approach for Missing Animations

For moves where porting the full animation is too complex, you can temporarily clone an existing similar animation:

```asm
Move_CLOSE_COMBAT:
    goto Move_CROSS_CHOP  @ temporary: reuse Cross Chop animation
```

---

## Key Gotchas

1. **`B_ANIM_*` general constants are offset by 1** — FireRed has `CASTFORM_CHANGE` at index 0, RHH doesn't. Don't blindly copy `B_ANIM_*` values from RHH code. *(Planned fix: realign table to match RHH.)*

2. **Contest logic** — FireRed has no contests. Any `jumpifcontest` branches are dead code and can be ignored, but the macros themselves work fine (they just never jump).

3. **Sound effects** — Both share the same `SE_M_*` constants for Gen 3 sounds. RHH may reference sounds not in FireRed; check `include/constants/songs.h`.

4. **`gBattlerSpriteIds` vs `GetBattlerSpriteId`** — FireRed declares `gBattlerSpriteIds[]` as extern in `battle_anim.h`, RHH doesn't. Minor difference for task porting.

5. **`battle_anim_scripts.h`** — RHH has a header that provides `extern const u8 Move_XYZ[]` declarations for all move animation labels. FireRed doesn't have this. You only need it if C code references animation labels directly (rare).

6. **Background loading** — FireRed and RHH may load BG tiledata slightly differently. Always verify the `LoadMoveBg()`/background registration path.

---

## File Reference

### FireRed Animation Files
| Path | Purpose |
|---|---|
| `data/battle_anim_scripts.s` | All animation scripts (11,100 lines) |
| `asm/macros/battle_anim_script.inc` | ASM macro definitions (346 lines, 53 opcodes) |
| `include/battle_anim.h` | C function/variable externs (327 lines) |
| `include/constants/battle_anim.h` | ANIM_TAG, B_ANIM, BG, F_PAL constants (474 lines) |
| `src/battle_anim.c` | Script interpreter + animation launcher (2,003 lines) |
| `src/data/battle_anim.h` | Sprite sheet/palette tables (1,625 lines) |
| `src/battle_anim_*.c` (27 files) | Sprite callbacks and visual task functions |

### RHH Animation Files (for reference when porting)
| Path | Purpose |
|---|---|
| `data/battle_anim_scripts.s` | All animation scripts (34,323 lines) |
| `asm/macros/battle_anim_script.inc` | ASM macro definitions (354 lines, 53 opcodes) |
| `include/battle_anim.h` | C function/variable externs (562 lines) |
| `include/battle_anim_scripts.h` | `extern const u8 Move_*[]` declarations |
| `include/constants/battle_anim.h` | ANIM_TAG, B_ANIM, BG, F_PAL constants (670 lines) |
| `include/constants/battle_anim_scripts.h` | Animation script label constants |
| `src/battle_anim.c` | Script interpreter + animation launcher |
| `src/data/battle_anim.h` | Sprite sheet/palette tables (2,021 lines) |
| `src/battle_anim_new.c` | **Gen 4-9 sprite templates + callbacks (9,288 lines)** |
| `src/battle_anim_throw.c` | Ball throw / critical capture mechanics |
| `src/battle_anim_*.c` (28 files) | Sprite callbacks and visual task functions |
