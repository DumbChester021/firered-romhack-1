# Pokémon FireRed Romhack

A fork of [pret/pokefirered](https://github.com/pret/pokefirered) with Gen 6+ mechanical updates and quality-of-life improvements.

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

### Build System
- Modern compiler (`arm-none-eabi-gcc`) is now the default — no need to pass `MODERN=1`
- Legacy `agbcc` build still available via `make MODERN=0` if needed

## Active Test/Debug Changes

> **Note:** This section tracks any temporary test or debug code currently active in the build.
> If you add test code, document it here so it can be found and removed later.

*None currently active.*

## Planned Features

- Day/Night Cycle (Implmented but imperfect with bugs, as a Feature Branch for now)
- EV/IV Summary Screen
- Forgettable HMs / HM Item Replacement
- BW-style Repel System
- Modern EXP Share
- Decapitalization
- Poison Survival — ✅ Implemented as configurable `OW_POISON_DAMAGE`
- Updated Learnsets / Base Stats
- Mega Evolution
- Follower Pokémon
- Expanded Pokédex (Gen 4+ species)
- Nature/Ability Display Colors
- Text input auto change to small case after first letter
- Faster text writer speeds
- Display IMG can be hooked via conversations, scripts etc.. could show items, trainers etc..
- Transparent Textboxes
- Updated Sprites
- Removal of Last Events replay
- New Moves
- Items
- Abilities


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
- [RHH/pokeemerald-expansion](https://github.com/rh-hideout/pokeemerald-expansion) — reference for Physical/Special split icons and `OW_POISON_DAMAGE` pattern
