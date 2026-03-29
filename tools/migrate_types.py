#!/usr/bin/env python3
"""
Phase C Migration Script: type1/type2 → types[3]
Transforms direct field access, GetBattlerType1/2 calls, and type init patterns.
"""
import re
import sys
import os

# Files to process for .type1/.type2 → .types[0]/.types[1] field access
FIELD_ACCESS_FILES = [
    "src/pokemon.c",
    "src/battle_main.c",
    "src/battle_script_commands.c",
    "src/battle_ai_main.c",
    "src/battle_ai_util.c",
    "src/battle_ai_switch_items.c",
]

# Files to process for GetBattlerType1/2 call replacement
FUNC_CALL_FILES = [
    "src/battle_script_commands.c",
    "src/battle_ai_main.c",
    "src/battle_ai_util.c",
    "src/battle_ai_switch_items.c",
    "src/battle_main.c",
]

def migrate_field_access(content, filepath):
    """Replace .type1 → .types[0], .type2 → .types[1] for BattlePokemon access."""
    changes = 0

    # Pattern: gBattleMons[...].type1 or ->type1
    # Exclude: PokemonSubstruct references (those use .type1 as a union member name)
    # Exclude: monType1/monType2 variable names

    # .type1 → .types[0] (field access on BattlePokemon)
    # Must be preceded by . or -> and NOT be part of 'monType1' or 'substruct'
    old = content

    # Direct field: .type1 (not followed by alphanumeric — avoid matching .type1Something)
    content = re.sub(r'\.type1(?![a-zA-Z0-9_])', '.types[0]', content)
    content = re.sub(r'\.type2(?![a-zA-Z0-9_])', '.types[1]', content)
    content = re.sub(r'-\>type1(?![a-zA-Z0-9_])', '->types[0]', content)
    content = re.sub(r'-\>type2(?![a-zA-Z0-9_])', '->types[1]', content)

    if content != old:
        changes = 1

    return content, changes

def migrate_func_calls(content, filepath):
    """Replace GetBattlerType1(x) → gBattleMons[x].types[0], etc."""
    changes = 0
    old = content

    # GetBattlerType1(expr) → gBattleMons[expr].types[0]
    # GetBattlerType2(expr) → gBattleMons[expr].types[1]
    # These are simple single-argument function calls
    content = re.sub(
        r'GetBattlerType1\(([^)]+)\)',
        r'gBattleMons[\1].types[0]',
        content
    )
    content = re.sub(
        r'GetBattlerType2\(([^)]+)\)',
        r'gBattleMons[\1].types[1]',
        content
    )

    if content != old:
        changes = 1

    return content, changes

def add_type2_init(content, filepath):
    """
    After lines that set types[0] and types[1] from SpeciesInfo, add types[2] = TYPE_MYSTERY.
    Pattern: types[1] = gSpeciesInfo[...].types[1]; → append types[2] = TYPE_MYSTERY;
    """
    changes = 0
    lines = content.split('\n')
    new_lines = []
    i = 0
    while i < len(lines):
        new_lines.append(lines[i])
        # Check if this line sets types[1] from SpeciesInfo and next line doesn't already set types[2]
        if '.types[1] = gSpeciesInfo[' in lines[i] and '.types[1];' in lines[i]:
            # Check if next line already has types[2]
            if i + 1 < len(lines) and '.types[2]' in lines[i + 1]:
                pass  # already handled
            else:
                # Extract the battler prefix (e.g., "    gBattleMons[battlerId]")
                match = re.match(r'(\s*)(.*?)\.types\[1\]\s*=', lines[i])
                if match:
                    indent = match.group(1)
                    prefix = match.group(2)
                    new_lines.append(f'{indent}{prefix}.types[2] = TYPE_MYSTERY;')
                    changes += 1
        i += 1

    return '\n'.join(new_lines), changes

def main():
    root = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    total_changes = 0

    print("=== Phase C: type1/type2 → types[3] Migration ===\n")

    # Pass 1: Field access migration
    print("--- Pass 1: Field access (.type1/.type2 → .types[0]/.types[1]) ---")
    for f in FIELD_ACCESS_FILES:
        path = os.path.join(root, f)
        if not os.path.exists(path):
            print(f"  SKIP {f} (not found)")
            continue
        with open(path, 'r') as fh:
            content = fh.read()
        new_content, changes = migrate_field_access(content, f)
        if changes:
            with open(path, 'w') as fh:
                fh.write(new_content)
            # Count actual replacements
            count = content.count('.type1') - new_content.count('.type1') + \
                    content.count('.type2') - new_content.count('.type2')
            print(f"  {f}: {count} replacements")
            total_changes += count
        else:
            print(f"  {f}: no changes")

    # Pass 2: Function call migration
    print("\n--- Pass 2: GetBattlerType1/2() → .types[] ---")
    for f in FUNC_CALL_FILES:
        path = os.path.join(root, f)
        if not os.path.exists(path):
            print(f"  SKIP {f} (not found)")
            continue
        with open(path, 'r') as fh:
            content = fh.read()
        new_content, changes = migrate_func_calls(content, f)
        if changes:
            with open(path, 'w') as fh:
                fh.write(new_content)
            count = content.count('GetBattlerType1') - new_content.count('GetBattlerType1') + \
                    content.count('GetBattlerType2') - new_content.count('GetBattlerType2')
            print(f"  {f}: {count} replacements")
            total_changes += count
        else:
            print(f"  {f}: no changes")

    # Pass 3: Add types[2] = TYPE_MYSTERY initialization
    print("\n--- Pass 3: Add types[2] = TYPE_MYSTERY initialization ---")
    init_files = ["src/pokemon.c", "src/battle_main.c", "src/battle_script_commands.c"]
    for f in init_files:
        path = os.path.join(root, f)
        if not os.path.exists(path):
            print(f"  SKIP {f} (not found)")
            continue
        with open(path, 'r') as fh:
            content = fh.read()
        new_content, changes = add_type2_init(content, f)
        if changes:
            with open(path, 'w') as fh:
                fh.write(new_content)
            print(f"  {f}: {changes} initializations added")
            total_changes += changes
        else:
            print(f"  {f}: no changes")

    print(f"\n=== Total: {total_changes} changes ===")

    # Verify no remaining .type1/.type2 in battle code (excluding battle_util.c which we handle manually)
    print("\n--- Verification: remaining .type1/.type2 in battle source ---")
    check_files = FIELD_ACCESS_FILES + FUNC_CALL_FILES
    check_files = list(set(check_files))
    remaining = 0
    for f in check_files:
        path = os.path.join(root, f)
        if not os.path.exists(path):
            continue
        with open(path, 'r') as fh:
            content = fh.read()
        for line_no, line in enumerate(content.split('\n'), 1):
            # Skip comments
            stripped = line.lstrip()
            if stripped.startswith('//') or stripped.startswith('*'):
                continue
            if re.search(r'\.type1(?![a-zA-Z0-9_])', line) or re.search(r'\.type2(?![a-zA-Z0-9_])', line):
                print(f"  WARNING: {f}:{line_no}: {line.strip()}")
                remaining += 1
    if remaining == 0:
        print("  All clear — no remaining .type1/.type2 references.")
    else:
        print(f"  {remaining} remaining references need manual review.")

if __name__ == '__main__':
    main()
