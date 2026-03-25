#!/usr/bin/env python3
"""
Verification script for firered-romhack-1 modifications.
Validates Fairy type addition and Physical/Special split data integrity
by parsing source files and checking against expected values.

Usage: python3 tools/verify_data.py
"""

import re
import sys
import os

PROJ_ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

results = {"passed": 0, "failed": 0, "warnings": 0}

def check(description, condition, detail=""):
    if condition:
        print(f"  ✅ {description}")
        results["passed"] += 1
    else:
        print(f"  ❌ {description}")
        if detail:
            print(f"     → {detail}")
        results["failed"] += 1

def warn(description, detail=""):
    print(f"  ⚠️  {description}")
    if detail:
        print(f"     → {detail}")
    results["warnings"] += 1

def read_file(rel_path):
    with open(os.path.join(PROJ_ROOT, rel_path), "r") as f:
        return f.read()

# ─── 1. Constants ────────────────────────────────────────────────────────────

def verify_constants():
    print("\n── Constants (include/constants/pokemon.h) ──")
    src = read_file("include/constants/pokemon.h")

    m = re.search(r"#define\s+TYPE_FAIRY\s+(\d+)", src)
    check("TYPE_FAIRY is defined", m is not None)
    if m:
        check("TYPE_FAIRY == 18", m.group(1) == "18", f"got {m.group(1)}")

    m = re.search(r"#define\s+NUMBER_OF_MON_TYPES\s+(\d+)", src)
    check("NUMBER_OF_MON_TYPES is defined", m is not None)
    if m:
        check("NUMBER_OF_MON_TYPES == 19", m.group(1) == "19", f"got {m.group(1)}")

    m = re.search(r"#define\s+SPLIT_PHYSICAL\s+(\d+)", src)
    check("SPLIT_PHYSICAL defined", m is not None)

    m = re.search(r"#define\s+SPLIT_SPECIAL\s+(\d+)", src)
    check("SPLIT_SPECIAL defined", m is not None)

    m = re.search(r"#define\s+SPLIT_STATUS\s+(\d+)", src)
    check("SPLIT_STATUS defined", m is not None)

# ─── 2. BattleMove struct ────────────────────────────────────────────────────

def verify_struct():
    print("\n── BattleMove struct (include/pokemon.h) ──")
    src = read_file("include/pokemon.h")

    struct_match = re.search(r"struct BattleMove\s*\{([^}]+)\}", src, re.DOTALL)
    check("struct BattleMove found", struct_match is not None)
    if struct_match:
        body = struct_match.group(1)
        check("category field exists", "category" in body)

# ─── 3. Type effectiveness ───────────────────────────────────────────────────

def verify_type_effectiveness():
    print("\n── Type effectiveness (src/battle_main.c) ──")
    src = read_file("src/battle_main.c")

    m = re.search(r"gTypeEffectiveness\[(\d+)\]", src)
    check("gTypeEffectiveness array found", m is not None)
    if m:
        check("Array size == 366", m.group(1) == "366", f"got {m.group(1)}")

    expected_fairy_entries = [
        ("TYPE_FIGHTING", "TYPE_FAIRY", "TYPE_MUL_NOT_EFFECTIVE"),
        ("TYPE_POISON", "TYPE_FAIRY", "TYPE_MUL_SUPER_EFFECTIVE"),
        ("TYPE_BUG", "TYPE_FAIRY", "TYPE_MUL_NOT_EFFECTIVE"),
        ("TYPE_DRAGON", "TYPE_FAIRY", "TYPE_MUL_NO_EFFECT"),
        ("TYPE_DARK", "TYPE_FAIRY", "TYPE_MUL_NOT_EFFECTIVE"),
        ("TYPE_STEEL", "TYPE_FAIRY", "TYPE_MUL_SUPER_EFFECTIVE"),
        ("TYPE_FAIRY", "TYPE_FIRE", "TYPE_MUL_NOT_EFFECTIVE"),
        ("TYPE_FAIRY", "TYPE_POISON", "TYPE_MUL_NOT_EFFECTIVE"),
        ("TYPE_FAIRY", "TYPE_STEEL", "TYPE_MUL_NOT_EFFECTIVE"),
        ("TYPE_FAIRY", "TYPE_FIGHTING", "TYPE_MUL_SUPER_EFFECTIVE"),
        ("TYPE_FAIRY", "TYPE_DRAGON", "TYPE_MUL_SUPER_EFFECTIVE"),
        ("TYPE_FAIRY", "TYPE_DARK", "TYPE_MUL_SUPER_EFFECTIVE"),
    ]

    for atk, dfn, eff in expected_fairy_entries:
        pattern = rf"{atk}\s*,\s*{dfn}\s*,\s*{eff}"
        found = re.search(pattern, src)
        check(f"{atk} → {dfn} = {eff}", found is not None)

    ghost_steel = re.search(r"TYPE_GHOST\s*,\s*TYPE_STEEL\s*,\s*TYPE_MUL_NOT_EFFECTIVE", src)
    check("Ghost→Steel NVE removed (Gen 6)", ghost_steel is None,
          "Entry still present — should be removed per Gen 6")

    dark_steel = re.search(r"TYPE_DARK\s*,\s*TYPE_STEEL\s*,\s*TYPE_MUL_NOT_EFFECTIVE", src)
    check("Dark→Steel NVE removed (Gen 6)", dark_steel is None,
          "Entry still present — should be removed per Gen 6")

# ─── 4. Species types ────────────────────────────────────────────────────────

def verify_species():
    print("\n── Species Fairy types (src/data/pokemon/species_info.h) ──")
    src = read_file("src/data/pokemon/species_info.h")

    expected = {
        "SPECIES_CLEFAIRY":   ("TYPE_FAIRY", "TYPE_FAIRY"),
        "SPECIES_CLEFABLE":   ("TYPE_FAIRY", "TYPE_FAIRY"),
        "SPECIES_JIGGLYPUFF": ("TYPE_NORMAL", "TYPE_FAIRY"),
        "SPECIES_WIGGLYTUFF": ("TYPE_NORMAL", "TYPE_FAIRY"),
        "SPECIES_MR_MIME":    ("TYPE_PSYCHIC", "TYPE_FAIRY"),
        "SPECIES_TOGEPI":     ("TYPE_FAIRY", "TYPE_FAIRY"),
        "SPECIES_TOGETIC":    ("TYPE_FAIRY", "TYPE_FLYING"),
        "SPECIES_MARILL":     ("TYPE_WATER", "TYPE_FAIRY"),
        "SPECIES_AZUMARILL":  ("TYPE_WATER", "TYPE_FAIRY"),
        "SPECIES_SNUBBULL":   ("TYPE_FAIRY", "TYPE_FAIRY"),
        "SPECIES_GRANBULL":   ("TYPE_FAIRY", "TYPE_FAIRY"),
        "SPECIES_AZURILL":    ("TYPE_NORMAL", "TYPE_FAIRY"),
        "SPECIES_MAWILE":     ("TYPE_STEEL", "TYPE_FAIRY"),
        "SPECIES_RALTS":      ("TYPE_PSYCHIC", "TYPE_FAIRY"),
        "SPECIES_KIRLIA":     ("TYPE_PSYCHIC", "TYPE_FAIRY"),
        "SPECIES_GARDEVOIR":  ("TYPE_PSYCHIC", "TYPE_FAIRY"),
    }

    for species, (exp_t1, exp_t2) in expected.items():
        # Find species block and extract type
        pattern = rf'\[{species}\]\s*=\s*\{{[^}}]*\.types\s*=\s*\{{(\w+)\s*,\s*(\w+)\}}'
        m = re.search(pattern, src, re.DOTALL)
        if m:
            actual_t1, actual_t2 = m.group(1), m.group(2)
            check(f"{species} → {exp_t1}/{exp_t2}",
                  actual_t1 == exp_t1 and actual_t2 == exp_t2,
                  f"got {actual_t1}/{actual_t2}")
        else:
            check(f"{species} found in species_info", False, "species entry not found")

    # Optional species
    for species, exp_types in [
        ("SPECIES_CLEFFA", ("TYPE_FAIRY", "TYPE_FAIRY")),
        ("SPECIES_IGGLYBUFF", ("TYPE_NORMAL", "TYPE_FAIRY")),
    ]:
        pattern = rf'\[{species}\]\s*=\s*\{{[^}}]*\.types\s*=\s*\{{(\w+)\s*,\s*(\w+)\}}'
        m = re.search(pattern, src, re.DOTALL)
        if m:
            actual_t1, actual_t2 = m.group(1), m.group(2)
            check(f"{species} → {exp_types[0]}/{exp_types[1]}",
                  actual_t1 == exp_types[0] and actual_t2 == exp_types[1],
                  f"got {actual_t1}/{actual_t2}")
        else:
            warn(f"{species} not found (may not exist in this dex)")

# ─── 5. Move categories ──────────────────────────────────────────────────────

def verify_move_categories():
    print("\n── Move categories (src/data/moves_info.h) ──")
    src = read_file("src/data/moves_info.h")

    move_blocks = re.findall(r'\[(MOVE_\w+)\]\s*=\s*\{(.*?)\}', src, re.DOTALL)
    total = len(move_blocks)
    check(f"Found {total} move entries", total > 350)

    missing_category = []
    for name, body in move_blocks:
        if ".category" not in body:
            missing_category.append(name)

    check("All moves have .category field",
          len(missing_category) == 0,
          f"{len(missing_category)} missing: {', '.join(missing_category[:10])}")

    spot_checks = {
        "MOVE_POUND": "SPLIT_PHYSICAL",
        "MOVE_EMBER": "SPLIT_SPECIAL",
        "MOVE_GROWL": "SPLIT_STATUS",
        "MOVE_FIRE_PUNCH": "SPLIT_PHYSICAL",
        "MOVE_FLAMETHROWER": "SPLIT_SPECIAL",
        "MOVE_SWORDS_DANCE": "SPLIT_STATUS",
        "MOVE_WATERFALL": "SPLIT_PHYSICAL",
        "MOVE_GUST": "SPLIT_SPECIAL",
        "MOVE_BITE": "SPLIT_PHYSICAL",
    }

    for move_name, exp_cat in spot_checks.items():
        for name, body in move_blocks:
            if name == move_name:
                cat_match = re.search(r'\.category\s*=\s*(\w+)', body)
                if cat_match:
                    check(f"{move_name} → {exp_cat}",
                          cat_match.group(1) == exp_cat,
                          f"got {cat_match.group(1)}")
                break

# ─── 6. Damage calculation ───────────────────────────────────────────────────

def verify_damage_calc():
    print("\n── Damage calculation (src/pokemon.c) ──")
    src = read_file("src/pokemon.c")

    check("Uses SPLIT_PHYSICAL in CalculateBaseDamage", "SPLIT_PHYSICAL" in src)
    check("Uses SPLIT_SPECIAL in CalculateBaseDamage", "SPLIT_SPECIAL" in src)
    check("No old IS_TYPE_PHYSICAL macro in pokemon.c", "IS_TYPE_PHYSICAL" not in src)
    check("No old IS_TYPE_SPECIAL macro in pokemon.c", "IS_TYPE_SPECIAL" not in src)

# ─── 7. UI elements ──────────────────────────────────────────────────────────

def verify_ui():
    print("\n── UI elements ──")
    src_menu = read_file("include/menu.h")
    check("MENU_INFO_ICON_PHYSICAL defined", "MENU_INFO_ICON_PHYSICAL" in src_menu)
    check("MENU_INFO_ICON_SPECIAL defined", "MENU_INFO_ICON_SPECIAL" in src_menu)
    check("MENU_INFO_ICON_STATUS defined", "MENU_INFO_ICON_STATUS" in src_menu)

    src_list = read_file("src/list_menu.c")
    check("TYPE_FAIRY icon entry in list_menu.c", "TYPE_FAIRY" in src_list)
    check("MENU_INFO_ICON_PHYSICAL entry in list_menu.c",
          "MENU_INFO_ICON_PHYSICAL" in src_list)

    src_type = read_file("src/battle_main.c")
    check("FAIRY in gTypeNames", '"FAIRY"' in src_type)

# ─── 8. Move type reclassification check ─────────────────────────────────────

def verify_move_types():
    print("\n── Move type reclassifications (informational) ──")
    src = read_file("src/data/moves_info.h")

    moves_to_check = {
        "MOVE_SWEET_KISS": "TYPE_FAIRY",
        "MOVE_CHARM": "TYPE_FAIRY",
        "MOVE_MOONLIGHT": "TYPE_FAIRY",
    }

    move_blocks = re.findall(r'\[(MOVE_\w+)\]\s*=\s*\{(.*?)\}', src, re.DOTALL)

    for move_name, expected_type in moves_to_check.items():
        for name, body in move_blocks:
            if name == move_name:
                type_match = re.search(r'\.type\s*=\s*(\w+)', body)
                if type_match:
                    actual = type_match.group(1)
                    if actual != expected_type:
                        warn(f"{move_name} is {actual} (Gen 6+ expects {expected_type})")
                    else:
                        check(f"{move_name} → {expected_type}", True)
                break

# ─── Main ─────────────────────────────────────────────────────────────────────

def main():
    print("=" * 60)
    print("  FireRed Romhack Data Verification")
    print("=" * 60)

    verify_constants()
    verify_struct()
    verify_type_effectiveness()
    verify_species()
    verify_move_categories()
    verify_damage_calc()
    verify_ui()
    verify_move_types()
    verify_reusable_tms()

    print("\n" + "=" * 60)
    print(f"  Results: {results['passed']} passed, {results['failed']} failed, {results['warnings']} warnings")
    print("=" * 60)

    if results["failed"] > 0:
        sys.exit(1)
    else:
        sys.exit(0)


def verify_reusable_tms():
    """Verify reusable TM implementation."""
    print("\n--- Reusable TMs ---")

    party_menu = read_file("src/party_menu.c")
    tm_case = read_file("src/tm_case.c")
    shop = read_file("src/shop.c")

    # TMs must NOT be removed from bag after teaching
    tm_removal_pattern = re.compile(
        r'if\s*\(\s*gSpecialVar_ItemId\s*<\s*ITEM_HM01\s*\)\s*\n\s*RemoveBagItem',
        re.MULTILINE
    )
    check(
        "party_menu.c: no TM consumption (RemoveBagItem guarded by ITEM_HM01)",
        not tm_removal_pattern.search(party_menu),
        "Found RemoveBagItem call guarded by ITEM_HM01 check"
    )

    # TM Case must NOT display quantity for TMs
    quantity_pattern = re.compile(
        r'!IS_HM.*BagGetQuantityByPocketPosition',
        re.DOTALL
    )
    check(
        "tm_case.c: TM quantity display removed",
        not quantity_pattern.search(tm_case),
        "Found TM quantity display code"
    )

    # TM selling must be disabled (function body should just show "can't buy that")
    sell_func_match = re.search(
        r'static void Task_SelectedTMHM_Sell\(.*?\)\s*\{(.*?)\n\}',
        tm_case, re.DOTALL
    )
    sell_disabled = True
    if sell_func_match:
        sell_body = sell_func_match.group(1)
        sell_disabled = "tQuantitySelected" not in sell_body and "ItemId_GetPrice" not in sell_body
    check(
        "tm_case.c: TM selling disabled",
        sell_disabled,
        "Task_SelectedTMHM_Sell still has sell quantity/price logic"
    )

    # Shop must check for already-owned TMs
    check(
        "shop.c: already-own TM check present",
        "POCKET_TM_CASE" in shop and "CheckBagHasItem" in shop,
        "Missing TM already-owned check in shop buy flow"
    )

if __name__ == "__main__":
    main()
