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

### Starter Pokémon
- Starters changed to Clefairy, Togepi, and Azurill (Fairy-type themed)
- I have not updated the Team of the Rival yet to reflect Fairy Change to starter since this is temporaray anyways for testing purposes

### Reusable TMs
- TMs are infinite-use (Gen 5+ behavior) — teaching a TM no longer consumes it
- TM Case no longer shows quantity counts for TMs
- TMs cannot be sold at shops (exploit prevention)
- Shops prevent buying a TM you already own ("You already have that TM")
- TM28 (Dig) removed from Celadon Dept Store (redundant with story reward)
- TM10 (Hidden Power) added to Celadon Dept Store (was previously unobtainable)
- Shop TM prices raised to reflect infinite-use value

## Planned Features

- Day/Night Cycle
- EV/IV Summary Screen
- Forgettable HMs / HM Item Replacement
- BW-style Repel System
- Modern EXP Share
- Decapitalization
- Poison Survival (1 HP in overworld)
- Updated Learnsets / Base Stats
- Mega Evolution
- Follower Pokémon
- Expanded Pokédex (Gen 4+ species)
- Nature/Ability Display Colors

## Building

See [INSTALL.md](INSTALL.md) for toolchain setup.

```bash
# Build (modern compiler)
make MODERN=1 -j$(nproc)
```

## Data Verification

Validates Fairy type, Physical/Special split, and Reusable TM data integrity:

```bash
python3 tools/verify_data.py
```

## Credits

- [pret/pokefirered](https://github.com/pret/pokefirered) — base decompilation
- [RHH/pokeemerald-expansion](https://github.com/rh-hideout/pokeemerald-expansion) — reference for Physical/Special split icons
