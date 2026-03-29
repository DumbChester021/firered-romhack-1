# Pokémon FireRed Romhack

A fork of [pret/pokefirered](https://github.com/pret/pokefirered) with Gen 6+ mechanical updates, RHH-faithful architecture ports, and quality-of-life improvements.

## Features (vs. pret/pokefirered)

### Fairy Type
- Added `TYPE_FAIRY` as the 19th type
- Complete type effectiveness table with all Gen 6 interactions:
  - Fairy is super effective against Fighting, Dragon, Dark
  - Fairy resists Fighting, Bug, Dark; immune to Dragon
  - Fairy is weak to Poison, Steel; resisted by Fire, Poison, Steel
  - Steel no longer resists Ghost and Dark (Gen 6 change)
- 18 Pokémon species reclassified with Fairy typing:
  Cleffa, Clefairy, Clefable, Igglybuff, Jigglypuff, Wigglytuff, Mr. Mime, Togepi, Togetic, Marill, Azumarill, Snubbull, Granbull, Azurill, Mawile, Ralts, Kirlia, Gardevoir
- Updated Sweet Kiss, Moonlight and Charm to TYPE_FAIRY from TYPE_NORMAL
- Fairy type label, icon, and TM/HM palette graphics
- Union Room type filter includes Fairy

### Physical/Special Split
- Moves now have an explicit `category` field (Physical, Special, or Status)
- Damage calculation uses per-move category instead of type-based split
- All 355 moves assigned correct categories matching Gen 4+ data
- Physical/Special/Status category icons displayed on summary screen
- Battle accuracy (Hustle) and damage tracking use per-move category

### Modern Move Engine (Gen 9 Synced)
- `gMovesInfo` structural array fully synchronized with the `pokeemerald-expansion` Gen 9 architecture, dropping legacy bitfields for explicit struct fields
- 927 moves up to `Tera Starstorm` populated with strictly accurate modern configurations (Power, Accuracy, PP, Priority, Type, and target constants)
- Complete decoupling of AI heuristics and effect handlers from legacy `EFFECT_` switch-cases in favor of dynamic `.additionalEffects` parsing logic
- Native configuration flags like `.thawsUser`, `.onChargeTurnOnly`, and `.criticalHitStage` adopted over legacy macros
- 13 per-move ban flags matching RHH (`metronomeBanned`, `mimicBanned`, `copycatBanned`, `assistBanned`, `sleepTalkBanned`, `instructBanned`, `encoreBanned`, `gravityBanned`, `meFirstBanned`, `parentalBondBanned`, `skyBattleBanned`, `sketchBanned`, `dampBanned`)
- `ignoresSubstitute` bitfield applied to all 31 sound-based moves
- Upgraded `CMD_ARGS` macro pipeline to parse RHH syntax exactly
- Assembly `preproc` compiler tool upgraded to support RHH's Python-style named keyword arguments (`x=0, y=0`), enabling 1:1 animation script ports

### Battle AI Engine (RHH C Port)
- All 9 AI flags ported from ASM to C with RHH-faithful dispatch table
- Smart switching logic — faithful RHH port with Gen 3 mechanics
- Gen 4+ AI heuristics (Sucker Punch, Shell Smash, Tailwind, Acrobatics, Bug Bite) integrated into `AI_CheckBadMove` and `AI_CheckViability`
- Wild Pokémon AI initialization fix — ported RHH scaling AI logic
- Full `AI_CalcAdditionalEffectScore` pipeline (26 functions, weather/field/terrain scoring)
- `struct AiLogicData` with `simulatedDmg[4][4][4]` damage precalculation
- Status scoring chains: `IncreasePoisonScore`, `IncreaseBurnScore`, `IncreaseParalyzeScore`, `IncreaseSleepScore`, `IncreaseConfusionScore`
- Stat scoring: `IncreaseStatUpScore`, `IncreaseStatDownScore` with Contrary awareness
- Weather/field status AI: `ShouldSetWeather`, `ShouldClearWeather`, `CalcWeatherScore`, `BenefitsFromGravity`, `BenefitsFromTrickRoom`
- Full documentation: [docs/battle_ai_architecture.md](docs/battle_ai_architecture.md)

### Volatiles Migration (`struct Volatiles`)
- Replaced `u32 status2` + `gStatuses3[MAX_BATTLERS_COUNT]` with RHH-style `struct Volatiles` (100+ named bitfields)
- All ~370 call sites migrated via automated Python tool
- `struct BattlerState` with `switchIn:1` replaces `STATUS3_INTIMIDATE_POKES`/`STATUS3_TRACE`

### Type System Modernization (`types[3]`)
- Replaced `u8 type1; u8 type2; u8 unknown;` with `u8 types[3]` array (3-slot type system matching RHH)
- Macros: `IS_BATTLER_OF_TYPE`, `SET_BATTLER_TYPE`, `RESTORE_BATTLER_TYPE`, `IS_BATTLER_TYPELESS`
- Roost-aware `GetBattlerTypes` + `RemoveBattlerType` helpers
- 86 call sites migrated via automated Python tool

### Running Shoes
- Running shoes enabled from the start (no item pickup required)
- Running allowed indoors
- Silently removed the script of the aide after you defeated Brock

### Reusable TMs
- TMs are infinite-use (Gen 5+ behavior) — teaching a TM no longer consumes it
- TM Case no longer shows quantity counts for TMs
- TMs cannot be sold at shops (exploit prevention)
- Shops prevent buying a TM you already own ("You already have that TM")
- TM28 (Dig) removed from Celadon Dept Store (redundant with story reward)
- TM10 (Hidden Power) added to Celadon Dept Store (was previously unobtainable)
- Shop TM prices raised to reflect infinite-use value

### Overworld Poison (`OW_POISON_DAMAGE`)
- Configurable overworld poison behavior via `OW_POISON_DAMAGE` in `include/config.h`
- Defaults to `GEN_LATEST` (Gen 5+: no overworld poison damage)
- Set to `GEN_3` for classic behavior (faint from poison, white-out)
- Set to `GEN_4` for Gen 4 behavior (survive at 1HP, poison cured)
- Generation constants `GEN_1`–`GEN_9` and `GEN_LATEST` added for future config toggles

### Instant & Faster Text Speed
- Added `OPTIONS_TEXT_SPEED_INSTANT` to the Options menu (4th speed setting)
- RHH-style `RunTextPrinters` repeat-loop for instant rendering while preserving `\p` prompts
- Uses delay=1 (not 0) to prevent printer deactivation that skips prompts

### Quality of Life
- Gen 6+ auto-lowercase naming screen keyboard (auto-switches to lowercase after first capital letter)
- Modern compiler (`arm-none-eabi-gcc`) is now the default — no need to pass `MODERN=1`
- Legacy `agbcc` build still available via `make MODERN=0` if needed
- EWRAM optimization: `sMapTilesBackup` moved to heap (98.88% → 92.65% EWRAM usage)

### Bug Fixes (pret-documented)
All bugs documented in the pret/pokefirered decompilation with `#ifdef BUGFIX` / `#ifdef UBFIX` guards are enabled unconditionally. These include:
- **Roamer status corruption** — u8 status field read as u32, corrupting contest stats (`roamer.c`)
- **HP underflow on level up** — currentHP could drop to ≤0 after stat recalc (`pokemon.c`)
- **Nature stat overflow** — u16 overflow for high base stats with positive natures (`pokemon.c`)
- **Unown letter calculation** — incorrect form calculation (`pokemon.c`)
- **Trade data bugs** — incorrect data handling during trades (`trade.c`)
- **Union Room string destination** — prints to wrong buffer (`union_room.c`)
- **Pokéball animation** — animation state bug (`pokeball.c`)
- **Pokédex screen** — display glitch (`pokedex_screen.c`)
- **Oak speech intro** — intro sequence bug (`oak_speech.c`)
- **Map preview window** — window creation bug (`map_preview_screen.c`)
- **Event object NULL deref** — potential freeze with modern compilers (`event_object_movement.c`)
- **Battle script commands** — two battle command bugs (`battle_script_commands.c`)
- **Battle initialization** — battle setup bug (`battle_main.c`)
- **Berry Crush wrong field** — incorrect field used twice (`berry_crush.c`)
- **Dodrio Berry Picking** — column sharing / difficulty bugs (`dodrio_berry_picking.c`)
- **Intro animation** — intro gfx bug (`intro.c`)
- **Heal location** — heal point bug (`heal_location.c`)
- **Text window graphics** — text rendering bug (`text_window_graphics.c`)
- **Wild Pokémon area** — encounter area bug (`wild_pokemon_area.c`)
- **Easy Chat clear** — clears 64 bytes instead of 64 bits (`easy_chat.c`)
- **Map view bounds** — loop reads past array bounds (`fieldmap.c`)
- **Map connection NULL deref** — possible null dereference (`fieldmap.c`)
- **Mystery Gift** — display bug (`mystery_gift_show_card.c`)
- **Trainer class lookup** — class lookup bug (`trainer_class_lookups.h`)
- **Party menu memory leak** — switching tilemap buffers never freed (`party_menu.c`) *(additionally fixed — was only commented)*
- **AI Heuristics**
  - `AI_CountAlivePokemon`: Counts alive party members not currently on field
  - `AI_IsSlower`: Predicts speed order safely handling trick room and switch priorities
  - `BattlerStatCanRise`: Checks if battler stat stages can be increased depending on abilities like Contrary

## Active Test/Debug Changes

> **Note:** This section tracks any temporary test or debug code currently active in the build.
> If you add test code, document it here so it can be found and removed later.

*None currently active.*

## Planned Features

> Items marked ✅ have been implemented. See the continuation guide for details.

### Gameplay Mechanics
- Mega Evolution
- Modern EXP Share
- Forgettable HMs / HM Item Replacement
- BW-style Repel System
- Day/Night Cycle *(implemented but imperfect with bugs — feature branch)*

### Content Expansion
- Expanded Pokédex (Gen 4+ species)
- Updated Learnsets / Base Stats
- Updated Sprites
- New Moves — ✅ Batch 1 & 2 implemented (see [docs/NEW_MOVES_LIST.md](docs/NEW_MOVES_LIST.md))
- Items
- Abilities
- Follower Pokémon

### UI / Visual
- EV/IV Summary Screen
- Nature/Ability Display Colors
- Transparent Textboxes
- Display IMG hooks (show items, trainers via conversations/scripts)
- Decapitalization
- Removal of Last Events replay

### Already Implemented
- ✅ Instant & Faster text speed
- ✅ Auto-lowercase after first capital letter on naming screen
- ✅ Poison Survival — configurable `OW_POISON_DAMAGE`

## Building

See [INSTALL.md](INSTALL.md) for toolchain setup.

```bash
# Build (modern compiler is now the default)
make -j$(nproc)

# Legacy agbcc build (requires agbcc toolchain)
make MODERN=0 -j$(nproc)
```

## Data Verification

Validates Fairy type, Physical/Special split, and Reusable TM data integrity:

```bash
python3 tools/verify_data.py
```

## Credits

- [pret/pokefirered](https://github.com/pret/pokefirered) — base decompilation
- [RHH/pokeemerald-expansion](https://github.com/rh-hideout/pokeemerald-expansion) — reference for Gen 9 move engine, battle AI, Physical/Special split, `OW_POISON_DAMAGE`, animation infrastructure, and text speed patterns
