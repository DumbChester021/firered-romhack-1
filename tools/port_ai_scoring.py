#!/usr/bin/env python3
"""
port_ai_scoring.py — Extract RHH AI scoring functions for porting to FireRed.

Extracts functions by brace-depth parsing from the RHH pokeemerald-expansion repo.
Since we converge to RHH naming, no name translation is needed — just extraction
and dependency identification.

Usage:
    python3 tools/port_ai_scoring.py [--rhh-root PATH] [--output-dir PATH] [--function NAME]

Defaults:
    --rhh-root  /mnt/data/Github/prototype/pokeemerald-expansion
    --output-dir  tools/staging/ai_port
"""

import argparse
import os
import re
import sys
from pathlib import Path


def extract_function(lines, func_name):
    """Extract a function body by brace-depth parsing.
    Returns (start_line, end_line, body_lines) or None.
    """
    # Match function DEFINITION: line must start with optional qualifiers + return type + func name
    # This avoids matching call sites inside other functions
    def_pattern = re.compile(
        rf'^(?:static\s+)?(?:inline\s+)?'  # optional qualifiers
        rf'(?:(?:enum|struct|const|unsigned|signed)\s+)*'  # optional type qualifiers
        rf'[\w*]+\s+'  # return type (e.g., bool32, void, s32, u32, etc.)
        rf'(?:\*\s*)?'  # optional pointer
        rf'{re.escape(func_name)}\s*\('  # function name + opening paren
    )
    start = None
    for i, line in enumerate(lines):
        if def_pattern.search(line) and not line.strip().startswith('//'):
            # Skip forward declarations (have ; before any {)
            # Look ahead up to 10 lines for { vs ;
            is_declaration = False
            for j in range(i, min(i + 10, len(lines))):
                if '{' in lines[j]:
                    break
                if lines[j].rstrip().endswith(';'):
                    is_declaration = True
                    break
            if is_declaration:
                continue
            start = i
            break

    if start is None:
        return None

    # Track braces from the start line through the entire function
    depth = 0
    brace_start = None
    for i in range(start, len(lines)):
        for ch in lines[i]:
            if ch == '{':
                if depth == 0:
                    brace_start = i
                depth += 1
            elif ch == '}':
                depth -= 1
                if depth == 0:
                    return (start, i, lines[start:i + 1])
        # If we haven't found the opening brace within 10 lines, give up
        if brace_start is None and i - start >= 10:
            return None

    return None


def find_called_functions(body_lines):
    """Find all function calls in extracted body."""
    calls = set()
    call_pattern = re.compile(r'\b([A-Z][A-Za-z0-9_]+)\s*\(')
    # Also catch lowercase helpers
    call_pattern2 = re.compile(r'\b([a-z][A-Za-z0-9_]+)\s*\(')
    for line in body_lines:
        stripped = line.strip()
        if stripped.startswith('//'):
            continue
        for m in call_pattern.finditer(line):
            name = m.group(1)
            # Skip macros and common C things
            if name not in ('TRUE', 'FALSE', 'NULL', 'ARRAY_COUNT', 'ADJUST_SCORE',
                           'MAX', 'MIN', 'ABS', 'SWAP', 'BIT', 'IS_TYPE',
                           'IS_BATTLER_OF_TYPE', 'SET_BATTLER_TYPE',
                           'GET_STAT_BUFF_ID', 'GET_STAT_BUFF_VALUE',
                           'STAT_CHANGE', 'STAT_STAGE'):
                calls.add(name)
        for m in call_pattern2.finditer(line):
            name = m.group(1)
            if name not in ('if', 'else', 'for', 'while', 'switch', 'case',
                           'return', 'break', 'continue', 'sizeof', 'typeof',
                           'true', 'false', 'static', 'const', 'enum', 'struct',
                           'void', 'bool', 'bool32', 'u8', 'u16', 'u32', 's8',
                           's16', 's32'):
                calls.add(name)
    return calls


def check_exists_in_firered(func_name, firered_root):
    """Check if a function exists in the FireRed codebase."""
    src_dir = firered_root / 'src'
    inc_dir = firered_root / 'include'
    for search_dir in [src_dir, inc_dir]:
        if not search_dir.exists():
            continue
        for f in search_dir.rglob('*.c'):
            try:
                content = f.read_text()
                if re.search(rf'\b{re.escape(func_name)}\s*\(', content):
                    return str(f.relative_to(firered_root))
            except:
                pass
        for f in search_dir.rglob('*.h'):
            try:
                content = f.read_text()
                if re.search(rf'\b{re.escape(func_name)}\s*\(', content):
                    return str(f.relative_to(firered_root))
            except:
                pass
    return None


def main():
    parser = argparse.ArgumentParser(description='Extract RHH AI functions for porting')
    parser.add_argument('--rhh-root', default='/mnt/data/Github/prototype/pokeemerald-expansion',
                       help='Path to RHH pokeemerald-expansion repo')
    parser.add_argument('--output-dir', default='tools/staging/ai_port',
                       help='Output directory for extracted functions')
    parser.add_argument('--function', '-f', action='append', dest='functions',
                       help='Function name to extract (can specify multiple)')
    parser.add_argument('--file', action='append', dest='files',
                       help='RHH source file to search (relative to rhh-root)')
    parser.add_argument('--check-deps', action='store_true',
                       help='Check which dependencies exist in FireRed')
    parser.add_argument('--firered-root', default='.',
                       help='Path to FireRed repo root')
    args = parser.parse_args()

    rhh_root = Path(args.rhh_root)
    firered_root = Path(args.firered_root)
    output_dir = Path(args.output_dir)
    output_dir.mkdir(parents=True, exist_ok=True)

    # Default files to search
    default_files = [
        'src/battle_ai_main.c',
        'src/battle_ai_util.c',
        'src/battle_util.c',
    ]
    search_files = args.files if args.files else default_files

    # Default functions if none specified
    default_functions = [
        'AI_CalcAdditionalEffectScore',
        'MoveEffectIsGuaranteed',
        'IncreaseStatUpScore',
        'IncreaseStatUpScoreInternal',
        'IncreaseStatUpScoreContrary',
        'IncreaseStatDownScore',
        'ShouldTryToFlinch',
        'IncreasePoisonScore',
        'IncreaseBurnScore',
        'IncreaseParalyzeScore',
        'IncreaseSleepScore',
        'IncreaseConfusionScore',
    ]
    target_funcs = args.functions if args.functions else default_functions

    # Load all source files
    file_contents = {}
    for rel_path in search_files:
        full_path = rhh_root / rel_path
        if full_path.exists():
            file_contents[rel_path] = full_path.read_text().splitlines()
        else:
            print(f"WARNING: {full_path} not found", file=sys.stderr)

    # Extract each function
    all_deps = set()
    extracted = {}

    for func_name in target_funcs:
        found = False
        for rel_path, lines in file_contents.items():
            result = extract_function(lines, func_name)
            if result:
                start, end, body = result
                extracted[func_name] = {
                    'file': rel_path,
                    'start': start + 1,  # 1-indexed
                    'end': end + 1,
                    'lines': len(body),
                    'body': body,
                }
                deps = find_called_functions(body)
                all_deps.update(deps)
                extracted[func_name]['deps'] = deps
                found = True
                print(f"✓ {func_name}: {rel_path}:{start+1}-{end+1} ({len(body)} lines)")
                break
        if not found:
            print(f"✗ {func_name}: NOT FOUND", file=sys.stderr)

    # Write extracted functions to staging files
    for func_name, info in extracted.items():
        out_file = output_dir / f"{func_name}.c"
        with open(out_file, 'w') as f:
            f.write(f"// Extracted from RHH {info['file']}:{info['start']}-{info['end']}\n")
            f.write(f"// {info['lines']} lines\n")
            f.write(f"// Dependencies: {', '.join(sorted(info['deps']))}\n\n")
            f.write('\n'.join(info['body']))
            f.write('\n')
        print(f"  → {out_file}")

    # Write combined file
    combined = output_dir / 'all_extracted.c'
    with open(combined, 'w') as f:
        f.write("// === RHH AI Scoring Functions — Extracted for Porting ===\n")
        f.write(f"// Functions: {', '.join(extracted.keys())}\n")
        f.write(f"// Total extracted: {sum(e['lines'] for e in extracted.values())} lines\n\n")
        for func_name, info in extracted.items():
            f.write(f"\n// --- {func_name} ({info['file']}:{info['start']}-{info['end']}) ---\n")
            f.write('\n'.join(info['body']))
            f.write('\n')
    print(f"\n→ Combined: {combined}")

    # Dependency analysis
    if args.check_deps:
        print("\n=== Dependency Analysis ===")
        # Remove functions we already extracted
        external_deps = all_deps - set(extracted.keys())
        missing = []
        present = []
        for dep in sorted(external_deps):
            location = check_exists_in_firered(dep, firered_root)
            if location:
                present.append((dep, location))
            else:
                missing.append(dep)

        if present:
            print(f"\nAlready in FireRed ({len(present)}):")
            for name, loc in present:
                print(f"  ✓ {name} → {loc}")

        if missing:
            print(f"\nMISSING from FireRed ({len(missing)}):")
            for name in missing:
                # Try to find in RHH to show where it comes from
                for rel_path, lines in file_contents.items():
                    result = extract_function(lines, name)
                    if result:
                        print(f"  ✗ {name} → RHH {rel_path}:{result[0]+1} ({result[2].__len__()} lines)")
                        break
                else:
                    print(f"  ✗ {name} → location unknown")

    # Summary
    print(f"\n=== Summary ===")
    print(f"Extracted: {len(extracted)} functions, {sum(e['lines'] for e in extracted.values())} total lines")
    print(f"Total dependencies found: {len(all_deps)}")
    if extracted:
        all_extracted_deps = set()
        for info in extracted.values():
            all_extracted_deps.update(info['deps'])
        unresolved = all_extracted_deps - set(extracted.keys())
        print(f"Unresolved dependencies: {len(unresolved)}")
        if unresolved and not args.check_deps:
            print("  (run with --check-deps to see which exist in FireRed)")


if __name__ == '__main__':
    main()
