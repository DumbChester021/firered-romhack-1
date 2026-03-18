"""
missing_items.py
Compares include/constants/items.h from this FireRed repo against
pokeemerald-expansion include/constants/items.h to identify items
that exist in the expansion but not in the FireRed hack.
Results are grouped by category and written to docs/missing_items.md.

Reference: pret/pokeemerald-expansion (tracks Gen I-IX canonical item list).
"""
from __future__ import annotations

import re
from pathlib import Path

REPO_ROOT = Path("/mnt/data/Github/prototype/firered-romhack-1")
EXPANSION_ROOT = Path("/mnt/data/Github/prototype/pokeemerald-expansion")

FIRERED_ITEMS_H   = REPO_ROOT / "include/constants/items.h"
EXPANSION_ITEMS_H = EXPANSION_ROOT / "include/constants/items.h"

OUTPUT_MD = REPO_ROOT / "docs/missing_items.md"

# ---------------------------------------------------------------------------
# Category map: prefix patterns in expansion constants -> human-readable label.
# Order matters — first match wins.
# ---------------------------------------------------------------------------
CATEGORY_PATTERNS = [
    # TMs / HMs (handled separately via TM/HM range detection)
    ("TM_HM", [r"^ITEM_TM\d+$", r"^ITEM_HM\d+$"]),

    # Berries
    ("Berries", [r"_BERRY$"]),

    # Poké Balls
    ("Poké Balls", [
        r"_BALL$", r"^ITEM_SAFARI_BALL$",
    ]),

    # Vitamins / EV items
    ("Vitamins & EV Items", [
        r"^ITEM_HP_UP$", r"^ITEM_PROTEIN$", r"^ITEM_IRON$", r"^ITEM_CALCIUM$",
        r"^ITEM_ZINC$", r"^ITEM_CARBOS$", r"^ITEM_PP_UP$", r"^ITEM_PP_MAX$",
        r"^ITEM_RARE_CANDY$",
        r"_FEATHER$", r"_WING$",
        r"^ITEM_POWER_WEIGHT$", r"^ITEM_POWER_BRACER$", r"^ITEM_POWER_BELT$",
        r"^ITEM_POWER_LENS$", r"^ITEM_POWER_BAND$", r"^ITEM_POWER_ANKLET$",
        r"^ITEM_MACHO_BRACE$",
        r"^ITEM_EXP_CANDY_", r"_MOCHI$",
        r"^ITEM_BOTTLE_CAP$", r"^ITEM_GOLD_BOTTLE_CAP$",
        r"_MINT$",
    ]),

    # Battle items (X Items + Dire Hit + Guard Spec)
    ("Battle Items", [
        r"^ITEM_X_", r"^ITEM_DIRE_HIT$", r"^ITEM_GUARD_SPEC$",
        r"^ITEM_ADRENALINE_ORB$", r"^ITEM_MAX_MUSHROOMS$",
    ]),

    # Medicine / Healing
    ("Medicine & Healing", [
        r"^ITEM_POTION$", r"^ITEM_SUPER_POTION$", r"^ITEM_HYPER_POTION$",
        r"^ITEM_MAX_POTION$", r"^ITEM_FULL_RESTORE$",
        r"^ITEM_REVIVE$", r"^ITEM_MAX_REVIVE$",
        r"^ITEM_FRESH_WATER$", r"^ITEM_SODA_POP$", r"^ITEM_LEMONADE$",
        r"^ITEM_MOOMOO_MILK$",
        r"^ITEM_ANTIDOTE$", r"^ITEM_BURN_HEAL$", r"^ITEM_ICE_HEAL$",
        r"^ITEM_AWAKENING$", r"^ITEM_PARALYZE_HEAL$", r"^ITEM_FULL_HEAL$",
        r"^ITEM_ETHER$", r"^ITEM_MAX_ETHER$", r"^ITEM_ELIXIR$", r"^ITEM_MAX_ELIXIR$",
        r"^ITEM_ENERGY_POWDER$", r"^ITEM_ENERGY_ROOT$",
        r"^ITEM_HEAL_POWDER$", r"^ITEM_REVIVAL_HERB$",
        r"^ITEM_BERRY_JUICE$", r"^ITEM_SACRED_ASH$",
        r"^ITEM_LAVA_COOKIE$", r"^ITEM_OLD_GATEAU$",
        r"^ITEM_CASTELIACONE$", r"^ITEM_LUMIOSE_GALETTE$",
        r"^ITEM_SHALOUR_SABLE$", r"^ITEM_BIG_MALASADA$",
        r"^ITEM_PEWTER_CRUNCHIES$", r"^ITEM_RAGE_CANDY_BAR$",
        r"^ITEM_SWEET_HEART$", r"^ITEM_MAX_HONEY$",
        r"^ITEM_REMEDY$", r"^ITEM_FINE_REMEDY$", r"^ITEM_SUPERB_REMEDY$",
        r"^ITEM_JUBILIFE_MUFFIN$",
    ]),

    # Evolution Stones & items
    ("Evolution Items", [
        r"_STONE$", r"^ITEM_ICE_STONE$",
        r"^ITEM_DRAGON_SCALE$", r"^ITEM_UP_GRADE$", r"^ITEM_UPGRADE$",
        r"^ITEM_PROTECTOR$", r"^ITEM_ELECTIRIZER$", r"^ITEM_MAGMARIZER$",
        r"^ITEM_DUBIOUS_DISC$", r"^ITEM_REAPER_CLOTH$", r"^ITEM_PRISM_SCALE$",
        r"^ITEM_WHIPPED_DREAM$", r"^ITEM_SACHET$", r"^ITEM_OVAL_STONE$",
        r"_SWEET$", r"_APPLE$", r"_POT$",
        r"^ITEM_LINKING_CORD$", r"^ITEM_BLACK_AUGURITE$", r"^ITEM_PEAT_BLOCK$",
        r"_MASK$", r"_TEACUP$",
        r"^ITEM_SYRUPY_APPLE$", r"^ITEM_METAL_ALLOY$",
        r"^ITEM_GALARICA_CUFF$", r"^ITEM_GALARICA_WREATH$",
        r"_NECTAR$",
    ]),

    # Type-boosting held items (type gems, plates, type boosts)
    ("Type-boosting Held Items", [
        r"_GEM$",
        r"_PLATE$",
        r"^ITEM_SILK_SCARF$", r"^ITEM_CHARCOAL$", r"^ITEM_MYSTIC_WATER$",
        r"^ITEM_MAGNET$", r"^ITEM_MIRACLE_SEED$", r"^ITEM_NEVER_MELT_ICE$",
        r"^ITEM_BLACK_BELT$", r"^ITEM_POISON_BARB$", r"^ITEM_SOFT_SAND$",
        r"^ITEM_SHARP_BEAK$", r"^ITEM_TWISTED_SPOON$", r"^ITEM_SILVER_POWDER$",
        r"^ITEM_HARD_STONE$", r"^ITEM_SPELL_TAG$", r"^ITEM_DRAGON_FANG$",
        r"^ITEM_BLACK_GLASSES$", r"^ITEM_METAL_COAT$",
        r"^ITEM_CHARCOAL$", r"^ITEM_FAIRY_FEATHER$",
    ]),

    # Species-specific held items
    ("Species-specific Held Items", [
        r"^ITEM_LIGHT_BALL$", r"^ITEM_LEEK$", r"^ITEM_STICK$",
        r"^ITEM_THICK_CLUB$", r"^ITEM_LUCKY_PUNCH$",
        r"^ITEM_METAL_POWDER$", r"^ITEM_QUICK_POWDER$",
        r"^ITEM_DEEP_SEA_SCALE$", r"^ITEM_DEEP_SEA_TOOTH$",
        r"^ITEM_SOUL_DEW$", r"^ITEM_ADAMANT_ORB$", r"^ITEM_LUSTROUS_ORB$",
        r"^ITEM_GRISEOUS_ORB$", r"^ITEM_ADAMANT_CRYSTAL$",
        r"^ITEM_GRISEOUS_CORE$", r"^ITEM_LUSTROUS_GLOBE$",
        r"^ITEM_RUSTED_SWORD$", r"^ITEM_RUSTED_SHIELD$",
        r"^ITEM_BERSERK_GENE$",
    ]),

    # Incenses
    ("Incenses", [r"_INCENSE$"]),

    # Choice Items
    ("Choice Items", [r"^ITEM_CHOICE_"]),

    # Mega Stones
    ("Mega Stones", [r"ITE$", r"^ITEM_VENUSAURITE$", r"^ITEM_BLASTOISINITE$"]),

    # Z-Crystals
    ("Z-Crystals", [r"_Z$", r"IUM_Z$"]),

    # Drives & Memories (Genesect / Silvally)
    ("Drives & Memories", [r"_DRIVE$", r"_MEMORY$"]),

    # Terrain Seeds, Weather Rocks, Status Orbs
    ("Held Battle Items", [
        r"_SEED$", r"_ROCK$", r"^ITEM_FLAME_ORB$", r"^ITEM_TOXIC_ORB$",
        r"^ITEM_ABSORB_BULB$", r"^ITEM_CELL_BATTERY$",
        r"^ITEM_LUMINOUS_MOSS$", r"^ITEM_SNOWBALL$",
        r"^ITEM_WEAKNESS_POLICY$", r"^ITEM_ASSAULT_VEST$",
        r"^ITEM_SAFETY_GOGGLES$", r"^ITEM_THROAT_SPRAY$",
        r"^ITEM_EJECT_PACK$", r"^ITEM_HEAVY_DUTY_BOOTS$",
        r"^ITEM_BLUNDER_POLICY$", r"^ITEM_ROOM_SERVICE$",
        r"^ITEM_UTILITY_UMBRELLA$", r"^ITEM_EJECT_BUTTON$",
        r"^ITEM_RED_CARD$", r"^ITEM_RING_TARGET$",
        r"^ITEM_BINDING_BAND$", r"^ITEM_EVIOLITE$",
        r"^ITEM_FLOAT_STONE$", r"^ITEM_ROCKY_HELMET$",
        r"^ITEM_AIR_BALLOON$", r"^ITEM_PROTECTIVE_PADS$",
        r"^ITEM_TERRAIN_EXTENDER$",
        r"^ITEM_ABILITY_SHIELD$", r"^ITEM_CLEAR_AMULET$",
        r"^ITEM_PUNCHING_GLOVE$", r"^ITEM_COVERT_CLOAK$",
        r"^ITEM_LOADED_DICE$", r"^ITEM_MIRROR_HERB$",
        r"^ITEM_BOOSTER_ENERGY$",
    ]),

    # General held items
    ("General Held Items", [
        r"^ITEM_BRIGHT_POWDER$", r"^ITEM_WHITE_HERB$", r"^ITEM_EXP_SHARE$",
        r"^ITEM_QUICK_CLAW$", r"^ITEM_SOOTHE_BELL$", r"^ITEM_MENTAL_HERB$",
        r"^ITEM_KINGS_ROCK$", r"^ITEM_AMULET_COIN$", r"^ITEM_CLEANSE_TAG$",
        r"^ITEM_SMOKE_BALL$", r"^ITEM_FOCUS_BAND$", r"^ITEM_LUCKY_EGG$",
        r"^ITEM_SCOPE_LENS$", r"^ITEM_LEFTOVERS$", r"^ITEM_SHELL_BELL$",
        r"^ITEM_WIDE_LENS$", r"^ITEM_MUSCLE_BAND$", r"^ITEM_WISE_GLASSES$",
        r"^ITEM_EXPERT_BELT$", r"^ITEM_LIGHT_CLAY$", r"^ITEM_LIFE_ORB$",
        r"^ITEM_POWER_HERB$", r"^ITEM_FOCUS_SASH$", r"^ITEM_ZOOM_LENS$",
        r"^ITEM_METRONOME$", r"^ITEM_IRON_BALL$", r"^ITEM_LAGGING_TAIL$",
        r"^ITEM_DESTINY_KNOT$", r"^ITEM_BLACK_SLUDGE$", r"^ITEM_GRIP_CLAW$",
        r"^ITEM_STICKY_BARB$", r"^ITEM_SHED_SHELL$", r"^ITEM_BIG_ROOT$",
        r"^ITEM_RAZOR_CLAW$", r"^ITEM_RAZOR_FANG$",
        r"^ITEM_CHOICE_SCARF$", r"^ITEM_CHOICE_SPECS$",
    ]),

    # Apricorns
    ("Apricorns", [r"_APRICORN$"]),

    # Fossils
    ("Fossils", [r"_FOSSIL$", r"^ITEM_OLD_AMBER$", r"^ITEM_FOSSILIZED_"]),

    # Mulch
    ("Mulch", [r"_MULCH$"]),

    # Tera Shards (Gen IX)
    ("Tera Shards / Mechanics", [
        r"_TERA_SHARD$", r"^ITEM_TERA_ORB$", r"^ITEM_STELLAR_TERA_SHARD$",
    ]),

    # Gen IX misc
    ("Gen IX Items", [
        r"^ITEM_AUSPICIOUS_ARMOR$", r"^ITEM_MALICIOUS_ARMOR$",
        r"^ITEM_LEADERS_CREST$", r"^ITEM_GIMMIGHOUL_COIN$",
        r"^ITEM_BIG_BAMBOO_SHOOT$", r"^ITEM_TINY_BAMBOO_SHOOT$",
        r"^ITEM_SCROLL_OF_DARKNESS$", r"^ITEM_SCROLL_OF_WATERS$",
        r"^ITEM_FAIRY_FEATHER$", r"^ITEM_GLIMMERING_CHARM$",
        r"^ITEM_CORNERSTONE_MASK$", r"^ITEM_WELLSPRING_MASK$",
        r"^ITEM_HEARTHFLAME_MASK$",
        r"^ITEM_UNREMARKABLE_TEACUP$", r"^ITEM_MASTERPIECE_TEACUP$",
        r"^ITEM_SWAP_SNACK$", r"^ITEM_CHOICE_DUMPLING$",
        r"^ITEM_TWICE_SPICED_RADISH$",
        r"^ITEM_AUX_",
    ]),

    # Ability modifiers
    ("Ability Modifiers", [
        r"^ITEM_ABILITY_CAPSULE$", r"^ITEM_ABILITY_PATCH$",
    ]),

    # Charms
    ("Charms & Key Items (Gen 4+)", [
        r"_CHARM$", r"^ITEM_SHINY_CHARM$", r"^ITEM_OVAL_CHARM$",
        r"^ITEM_CATCHING_CHARM$", r"^ITEM_EXP_CHARM$",
        r"^ITEM_DYNAMAX_BAND$", r"^ITEM_DYNAMAX_CANDY$", r"^ITEM_MAX_MUSHROOMS$",
        r"^ITEM_ROTOM_CATALOG$", r"^ITEM_GRACIDEA$", r"^ITEM_REVEAL_GLASS$",
        r"^ITEM_DNA_SPLICERS$", r"^ITEM_ZYGARDE_CUBE$",
        r"^ITEM_N_SOLARIZER$", r"^ITEM_N_LUNARIZER$",
        r"^ITEM_REINS_OF_UNITY$", r"^ITEM_PRISON_BOTTLE$",
        r"^ITEM_MEGA_RING$", r"^ITEM_Z_POWER_RING$",
        r"^ITEM_WISHING_PIECE$", r"^ITEM_GALARICA_TWIG$",
        r"^ITEM_ARMORITE_ORE$", r"^ITEM_DYNITE_ORE$",
        r"^ITEM_POKE_RADAR$", r"^ITEM_POKEMON_BOX_LINK$",
        r"^ITEM_DOWSING_MACHINE$", r"^ITEM_OLD_SEA_MAP$",
        r"^ITEM_MAGMA_EMBLEM$",
        r"^ITEM_LINKING_CORD$",
    ]),

    # Treasures
    ("Treasures", [
        r"^ITEM_NUGGET$", r"^ITEM_BIG_NUGGET$",
        r"^ITEM_TINY_MUSHROOM$", r"^ITEM_BIG_MUSHROOM$", r"^ITEM_BALM_MUSHROOM$",
        r"^ITEM_PEARL$", r"^ITEM_BIG_PEARL$", r"^ITEM_PEARL_STRING$",
        r"^ITEM_STARDUST$", r"^ITEM_STAR_PIECE$", r"^ITEM_COMET_SHARD$",
        r"^ITEM_HEART_SCALE$", r"^ITEM_HONEY$", r"^ITEM_RARE_BONE$",
        r"^ITEM_ODD_KEYSTONE$", r"^ITEM_PRETTY_FEATHER$",
        r"^ITEM_RELIC_", r"^ITEM_STRANGE_SOUVENIR$",
        r"^ITEM_SHOAL_SALT$", r"^ITEM_SHOAL_SHELL$",
        r"_SHARD$",  # colored shards
    ]),

    # Flutes
    ("Flutes", [r"_FLUTE$", r"^ITEM_LURE$", r"^ITEM_SUPER_LURE$", r"^ITEM_MAX_LURE$"]),

    # Mail
    ("Mail", [r"_MAIL$"]),

    # Scarves (contest)
    ("Contest Items", [r"_SCARF$"]),
]


def parse_item_defines(path: Path) -> dict[str, int]:
    """Return {ITEM_CONSTANT_NAME: integer_value} from a constants/items.h file.

    Handles both `#define ITEM_X N` (FireRed) and enum-style `ITEM_X = N,` (expansion).
    Alias entries (ITEM_X = ITEM_Y) are resolved transitively.
    """
    raw: dict[str, str] = {}  # name -> raw rhs (may be another name or an int)
    define_pat = re.compile(r"#define\s+(ITEM_\w+)\s+(\w+)")
    enum_pat = re.compile(r"^\s*(ITEM_\w+)\s*=\s*(\w+)")

    with path.open() as f:
        for line in f:
            line = line.strip()
            m = define_pat.match(line) or enum_pat.match(line)
            if m:
                name, rhs = m.group(1), m.group(2)
                raw[name] = rhs

    # Resolve to integers
    resolved: dict[str, int] = {}

    def resolve(name: str, seen: set) -> int | None:
        if name in resolved:
            return resolved[name]
        if name in seen:
            return None
        seen.add(name)
        rhs = raw.get(name)
        if rhs is None:
            return None
        try:
            val = int(rhs, 0)
        except ValueError:
            val = resolve(rhs, seen)
        if val is not None:
            resolved[name] = val
        return val

    for name in raw:
        resolve(name, set())

    return resolved


def categorize(item_name: str) -> str:
    for category, patterns in CATEGORY_PATTERNS:
        for pat in patterns:
            if re.search(pat, item_name):
                return category
    return "Other"


def tm_move_name(item_name: str, expansion_tms: dict[str, str]) -> str:
    return expansion_tms.get(item_name, "")


def parse_expansion_tm_move_names() -> dict[str, str]:
    """Return {ITEM_TMnn: 'Move Name'} by reading FOREACH_TM in tms_hms.h."""
    tms_hms_h = EXPANSION_ROOT / "include/constants/tms_hms.h"
    moves: list[str] = []
    in_foreach = False
    with tms_hms_h.open() as f:
        for line in f:
            stripped = line.strip()
            if stripped.startswith("#define FOREACH_TM"):
                in_foreach = True
                continue
            if in_foreach:
                # Each entry is F(MOVE_NAME) \
                m = re.search(r"F\((\w+)\)", stripped)
                if m:
                    moves.append(m.group(1))
                # End of macro (no trailing backslash)
                if not stripped.endswith("\\"):
                    break
    result = {}
    for i, move in enumerate(moves, start=1):
        tm_key = f"ITEM_TM{i:02d}" if i < 100 else f"ITEM_TM{i}"
        result[tm_key] = move.replace("_", " ").title()
    return result



def main():
    firered_items = parse_item_defines(FIRERED_ITEMS_H)
    expansion_items = parse_item_defines(EXPANSION_ITEMS_H)

    firered_names = set(firered_items.keys())
    # Filter to canonical primary defines only (exclude aliases that resolve to same value)
    # We only want items the FireRed hack doesn't have
    missing: list[str] = []
    for name in sorted(expansion_items):
        if name not in firered_names:
            missing.append(name)

    # Exclude FireRed-specific key items that naturally won't be in expansion (they ARE there)
    # and meta-constants like FIRST_BERRY_INDEX etc.
    exclusion_pats = [
        r"_INDEX$", r"_COUNT$", r"^MAX_BERRY_INDEX$", r"^FIRST_MAIL_INDEX$",
        r"^LAST_BERRY_INDEX$",
        r"^ITEM_STRANGE_BALL$",  # internal expansion only
        r"^ITEM_ENIGMA_BERRY_E_READER$",  # e-Reader only
    ]

    def is_excluded(name: str) -> bool:
        for pat in exclusion_pats:
            if re.search(pat, name):
                return True
        return False

    missing = [n for n in missing if not is_excluded(n)]

    expansion_tm_moves = parse_expansion_tm_move_names()

    # Group by category
    categories: dict[str, list[str]] = {}
    for name in missing:
        cat = categorize(name)
        categories.setdefault(cat, []).append(name)

    # Sort categories: put TM_HM first, then Berries, then rest alphabetically
    def cat_sort_key(c: str) -> str:
        if c == "TM_HM":
            return "00"
        if c == "Berries":
            return "01"
        if c == "Battle Items":
            return "02"
        if c == "Vitamins & EV Items":
            return "03"
        if c == "Medicine & Healing":
            return "04"
        return c

    sorted_cats = sorted(categories.keys(), key=cat_sort_key)

    total = sum(len(v) for v in categories.values())

    with OUTPUT_MD.open("w") as out:
        out.write("# Missing Items — FireRed Hack vs pokeemerald-expansion\n\n")
        out.write(
            "Items present in `pokeemerald-expansion` (tracks canonical Gen I–IX item list) "
            "but absent from `include/constants/items.h` in this FireRed repository.\n\n"
        )
        out.write(
            "> **Reference:** pret/pokeemerald-expansion `include/constants/items.h`\n\n"
        )
        out.write(f"**Total missing items: {total}**\n\n")

        # Table of contents
        out.write("## Categories\n\n")
        for cat in sorted_cats:
            anchor = cat.lower().replace(" ", "-").replace("/", "").replace("&", "").replace("(", "").replace(")", "").replace("+", "")
            anchor = re.sub(r"-+", "-", anchor).strip("-")
            count = len(categories[cat])
            out.write(f"- [{cat}](#{anchor}) — {count} missing\n")
        out.write("\n---\n\n")

        for cat in sorted_cats:
            items_in_cat = sorted(categories[cat])
            out.write(f"## {cat}\n\n")

            if cat == "TM_HM":
                out.write("| Constant | Move |\n")
                out.write("|----------|------|\n")
                for item in items_in_cat:
                    move = expansion_tm_moves.get(item, "") or "*Unassigned in expansion*"
                    out.write(f"| `{item}` | {move} |\n")
            else:
                out.write("| Constant |\n")
                out.write("|----------|\n")
                for item in items_in_cat:
                    out.write(f"| `{item}` |\n")

            out.write("\n")

    # --- Section: ID number changes for shared items ---
    shared = {}
    for name in firered_names:
        if name in expansion_items and name in firered_items:
            fr_id = firered_items[name]
            ex_id = expansion_items[name]
            if fr_id != ex_id:
                shared[name] = (fr_id, ex_id)

    with OUTPUT_MD.open("a") as out:
        out.write("---\n\n")
        out.write("## Item ID Changes (Same Name, Different Slot)\n\n")
        out.write(
            "These items exist in **both** repos under the same constant name, "
            "but their numeric IDs differ. Any code or data that references raw item "
            "numbers (save files, scripts, shops, etc.) must account for this.\n\n"
        )
        out.write(f"**{len(shared)} items with changed IDs.**\n\n")
        out.write("| Constant | FireRed ID | Expansion ID | Δ |\n")
        out.write("|----------|-----------|--------------|---|\n")
        for name in sorted(shared, key=lambda n: shared[n][0]):
            fr_id, ex_id = shared[name]
            delta = ex_id - fr_id
            sign = f"+{delta}" if delta > 0 else str(delta)
            out.write(f"| `{name}` | {fr_id} | {ex_id} | {sign} |\n")

    print(f"Done. {total} missing items written to {OUTPUT_MD}")
    print(f"      {len(shared)} items with changed IDs documented.")
    print("\nTop categories by missing count:")
    for cat in sorted(categories, key=lambda c: -len(categories[c]))[:10]:
        print(f"  {len(categories[cat]):3d}  {cat}")


if __name__ == "__main__":
    main()
