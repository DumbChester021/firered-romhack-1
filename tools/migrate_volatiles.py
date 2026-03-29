#!/usr/bin/env python3
"""
Phase B migration: status2 + gStatuses3 → struct Volatiles volatiles

Transforms all call sites in src/ to use the new per-battler named fields.
Run from repo root:
    python3 tools/migrate_volatiles.py [--dry-run]

STATUS2_* → volatiles.fieldName mapping:
  Bit-counter fields use direct integer assignment instead of masking.
  Single-bit flags use direct 0/1 or FALSE/TRUE assignment.

gStatuses3[X] → gBattleMons[X].volatiles.fieldName mapping:
  The battler index expression X is preserved verbatim.
"""

import re
import sys
import os
from pathlib import Path

DRY_RUN = '--dry-run' in sys.argv

REPO = Path(__file__).parent.parent
SRC_DIR = REPO / 'src'

# ---------------------------------------------------------------------------
# STATUS2_* → volatiles.field mapping
# Each entry: (status2_pattern_regex, replacement_template_or_callable)
# ---------------------------------------------------------------------------

# Single-bit fields: STATUS2_FOO → volatiles.field (truthy check)
STATUS2_SINGLE = {
    'STATUS2_FLINCHED':          'flinched',
    'STATUS2_MULTIPLETURNS':     'multipleTurns',
    'STATUS2_FOCUS_ENERGY':      'focusEnergy',
    'STATUS2_TRANSFORMED':       'transformed',
    'STATUS2_RECHARGE':          'rechargeTimer',
    'STATUS2_RAGE':              'rage',
    'STATUS2_SUBSTITUTE':        'substitute',
    'STATUS2_ESCAPE_PREVENTION': 'escapePrevention',
    'STATUS2_NIGHTMARE':         'nightmare',
    'STATUS2_CURSED':            'cursed',
    'STATUS2_FORESIGHT':         'foresight',
    'STATUS2_DEFENSE_CURL':      'defenseCurl',
    'STATUS2_TORMENT':           'torment',
    'STATUS2_DESTINY_BOND':      'destinyBond',
}

# Multi-bit counter fields (masks): STATUS2_FOO → volatiles.field (counter, nonzero = active)
STATUS2_MULTI = {
    'STATUS2_CONFUSION':     'confusionTurns',
    'STATUS2_UPROAR':        'uproarTurns',
    'STATUS2_BIDE':          'bideTurns',
    'STATUS2_LOCK_CONFUSE':  'rampageTurns',
    'STATUS2_WRAPPED':       'wrapped',           # flag; wrapTurns handled separately below
    'STATUS2_INFATUATION':   'infatuation',
}

# Turn-setter macros: STATUS2_FOO_TURN(n) → volatiles.field = n
STATUS2_TURN_SETTERS = {
    r'STATUS2_CONFUSION_TURN\(([^)]+)\)':    'confusionTurns',
    r'STATUS2_UPROAR_TURN\(([^)]+)\)':       'uproarTurns',
    r'STATUS2_BIDE_TURN\(([^)]+)\)':         'bideTurns',
    r'STATUS2_LOCK_CONFUSE_TURN\(([^)]+)\)': 'rampageTurns',
    r'STATUS2_WRAPPED_TURN\(([^)]+)\)':      'wrapTurns',
}

# Special: STATUS2_INFATUATED_WITH(battler) — sets/checks one battler's infatuation bit
# Old: status2 |= STATUS2_INFATUATED_WITH(b)  → volatiles.infatuation |= gBitTable[b]
# Old: status2 & STATUS2_INFATUATED_WITH(b)   → volatiles.infatuation & gBitTable[b]
# Old: status2 &= ~STATUS2_INFATUATED_WITH(b) → volatiles.infatuation &= ~gBitTable[b]

# ---------------------------------------------------------------------------
# STATUS3_* → volatiles.field mapping
# ---------------------------------------------------------------------------

STATUS3_SINGLE = {
    'STATUS3_PERISH_SONG':       'perishSong',
    'STATUS3_MINIMIZED':         'minimize',
    'STATUS3_ROOTED':            'root',
    'STATUS3_IMPRISONED_OTHERS': 'imprison',
    'STATUS3_GRUDGE':            'grudge',
    'STATUS3_MUDSPORT':          'mudSport',
    'STATUS3_WATERSPORT':        'waterSport',
    'STATUS3_ROOST':             'roostActive',
}

STATUS3_MULTI = {
    'STATUS3_ALWAYS_HITS':   'lockOn',
    'STATUS3_LEECHSEED':     'leechSeed',
    'STATUS3_CHARGED_UP':    'chargeTimer',
    'STATUS3_YAWN':          'yawn',
}

# STATUS3_SEMI_INVULNERABLE composite and its components mapped to semiInvulnerable enum
# Old: STATUS3_ON_AIR       → semiInvulnerable == STATE_ON_AIR
# Old: STATUS3_UNDERGROUND  → semiInvulnerable == STATE_UNDERGROUND
# Old: STATUS3_UNDERWATER   → semiInvulnerable == STATE_UNDERWATER
# Old: STATUS3_SEMI_INVULNERABLE (composite) → semiInvulnerable != STATE_NONE
STATUS3_SEMI_INVULNERABLE = {
    'STATUS3_ON_AIR':              ('semiInvulnerable', 'STATE_ON_AIR'),
    'STATUS3_UNDERGROUND':         ('semiInvulnerable', 'STATE_UNDERGROUND'),
    'STATUS3_UNDERWATER':          ('semiInvulnerable', 'STATE_UNDERWATER'),
    'STATUS3_SEMI_INVULNERABLE':   ('semiInvulnerable', 'STATE_NONE'),  # != STATE_NONE
}

STATUS3_TURN_SETTERS = {
    r'STATUS3_ALWAYS_HITS_TURN\(([^)]+)\)': 'lockOn',
    r'STATUS3_YAWN_TURN\(([^)]+)\)':        'yawn',
}

# STATUS3_LEECHSEED_BATTLER is the battler bits embedded in leechSeed field
# Old: gStatuses3[X] & STATUS3_LEECHSEED_BATTLER → gBattleMons[X].volatiles.leechSeed (battler bits)
# Old: gStatuses3[X] |= STATUS3_LEECHSEED_BATTLER & gBitTable[b] → handled case by case

# ---------------------------------------------------------------------------
# Regex helpers
# ---------------------------------------------------------------------------

# Matches: gBattleMons[<idx>].status2
BATTLER_STATUS2 = re.compile(
    r'gBattleMons\[([^\]]+)\]\.status2'
)

# Matches: gStatuses3[<idx>]
BATTLER_STATUS3 = re.compile(
    r'gStatuses3\[([^\]]+)\]'
)

def make_volatiles_path(battler_idx: str, field: str) -> str:
    return f'gBattleMons[{battler_idx}].volatiles.{field}'

# ---------------------------------------------------------------------------
# Transform STATUS2 operations
# ---------------------------------------------------------------------------

def transform_status2_expr(battler_idx: str, op: str, rhs: str) -> str | None:
    """
    Given the battler index, operator (& | &= |= = ~), and rhs expression,
    return the transformed C expression or None if unhandled.

    We handle patterns found via grep analysis of the source.
    """
    vpath = f'gBattleMons[{battler_idx}].volatiles'

    # === Turn setter macros first (they contain the counter field name) ===
    for pattern, field in STATUS2_TURN_SETTERS.items():
        m = re.search(pattern, rhs)
        if m:
            turn_val = m.group(1)
            # These appear as: status2 |= STATUS2_FOO_TURN(n)
            # → volatiles.field = n
            return f'{vpath}.{field} = {turn_val}'

    # === STATUS2_INFATUATED_WITH(b) ===
    m = re.search(r'STATUS2_INFATUATED_WITH\(([^)]+)\)', rhs)
    if m:
        b = m.group(1)
        if '|=' in op:
            return f'{vpath}.infatuation |= gBitTable[{b}]'
        elif '&=' in op:
            return f'{vpath}.infatuation &= ~gBitTable[{b}]'
        else:  # & check
            return f'({vpath}.infatuation & gBitTable[{b}])'

    # === Single-bit flags ===
    for const, field in STATUS2_SINGLE.items():
        if const in rhs:
            if op in ('|=',):
                return f'{vpath}.{field} = TRUE'
            elif op in ('&=',) and '~' in rhs:
                return f'{vpath}.{field} = FALSE'
            else:  # & read
                return f'{vpath}.{field}'

    # === Multi-bit counter fields ===
    for const, field in STATUS2_MULTI.items():
        if const in rhs:
            if op in ('|=',):
                # Setting the whole mask (without a TURN macro) means setting = nonzero
                # This pattern is unusual; map to field = 1 (wrapped flag)
                if field == 'wrapped':
                    return f'{vpath}.{field} = TRUE'
                # For other multi-bit masks without a turn macro, unclear — leave for manual
                return None
            elif op in ('&=',) and '~' in rhs:
                # Clearing: status2 &= ~STATUS2_FOO → field = 0
                return f'{vpath}.{field} = 0'
            else:  # & check (read)
                return f'{vpath}.{field}'

    # === Full reset: status2 = 0 ===
    if rhs.strip() == '0':
        # Return a memset-style reset for the whole volatiles struct
        return f'memset(&{vpath}, 0, sizeof(gBattleMons[{battler_idx}].volatiles))'

    return None

# ---------------------------------------------------------------------------
# Transform STATUS3 operations
# ---------------------------------------------------------------------------

def transform_status3_expr(battler_idx: str, op: str, rhs: str) -> str | None:
    vpath = f'gBattleMons[{battler_idx}].volatiles'

    # === Turn setter macros ===
    for pattern, field in STATUS3_TURN_SETTERS.items():
        m = re.search(pattern, rhs)
        if m:
            turn_val = m.group(1)
            return f'{vpath}.{field} = {turn_val}'

    # === Semi-invulnerable states (bitwise → enum comparison) ===
    # STATUS3_ON_AIR, STATUS3_UNDERGROUND, STATUS3_UNDERWATER, STATUS3_SEMI_INVULNERABLE
    for const, (field, state) in STATUS3_SEMI_INVULNERABLE.items():
        if const in rhs:
            if op in ('|=',):
                if state == 'STATE_NONE':
                    return None  # composite set doesn't make sense
                return f'{vpath}.{field} = {state}'
            elif op in ('&=',) and '~' in rhs:
                return f'{vpath}.{field} = STATE_NONE'
            else:  # & check
                if const == 'STATUS3_SEMI_INVULNERABLE':
                    return f'({vpath}.{field} != STATE_NONE)'
                else:
                    return f'({vpath}.{field} == {state})'

    # === STATUS3_LEECHSEED_BATTLER (battler bits embedded in leechSeed) ===
    if 'STATUS3_LEECHSEED_BATTLER' in rhs:
        if op in ('&=',) and '~' in rhs:
            # Clear the battler bits but preserve the leechSeed flag
            # Old: gStatuses3[X] &= ~STATUS3_LEECHSEED_BATTLER
            # leechSeed stores the battler index; clearing it = leechSeed = 0
            return f'{vpath}.leechSeed = 0'
        elif op in ('|=',):
            # Old: gStatuses3[X] |= STATUS3_LEECHSEED_BATTLER & gBitTable[y]
            # → volatiles.leechSeed = y (battler index)
            # This is context-dependent, leave for manual
            return None
        else:
            # Read: (gStatuses3[X] & STATUS3_LEECHSEED_BATTLER) >> 0 → volatiles.leechSeed
            return f'{vpath}.leechSeed'

    # === Single-bit flags ===
    for const, field in STATUS3_SINGLE.items():
        if const in rhs:
            if op in ('|=',):
                return f'{vpath}.{field} = TRUE'
            elif op in ('&=',) and '~' in rhs:
                return f'{vpath}.{field} = FALSE'
            else:  # & check
                return f'{vpath}.{field}'

    # === Multi-bit counter fields ===
    for const, field in STATUS3_MULTI.items():
        if const in rhs and 'LEECHSEED_BATTLER' not in rhs:
            if op in ('|=',):
                return f'{vpath}.{field} = TRUE'
            elif op in ('&=',) and '~' in rhs:
                return f'{vpath}.{field} = 0'
            else:  # & check
                return f'{vpath}.{field}'

    # === Full reset: gStatuses3[X] = 0 ===
    if rhs.strip() == '0':
        return f'memset(&{vpath}, 0, sizeof(gBattleMons[{battler_idx}].volatiles))'

    return None

# ---------------------------------------------------------------------------
# Line-level transformation
# ---------------------------------------------------------------------------

# Pattern: EXPR op= RHS;   or   EXPR op RHS   (in condition)
# We operate on the whole line. Use a two-pass approach:
#   1. Replace full assignment statements
#   2. Replace read-only checks (in conditions)

def try_transform_statement(line: str) -> str | None:
    """Try to transform a statement line involving status2 or gStatuses3."""
    # Check for assignment operators first (most specific)
    # Patterns: xxx.status2 op= rhs;  or  gStatuses3[i] op= rhs;

    # Assignment: gBattleMons[idx].status2 op= rhs;
    m = re.search(
        r'(gBattleMons\[([^\]]+)\]\.status2)\s*([|&]?=)\s*([^;]+);',
        line
    )
    if m:
        full_lhs, idx, op, rhs = m.group(1), m.group(2), m.group(3), m.group(4)
        # Normalize compound assignment
        actual_op = op  # '=', '|=', '&='
        if actual_op == '=' and rhs.strip() != '0':
            # Could be a copy like: status2 = otherStatus2; — leave alone
            if 'status2' in rhs or 'STATUS' not in rhs:
                return None
        result = transform_status2_expr(idx, actual_op, rhs)
        if result:
            indent = line[:len(line) - len(line.lstrip())]
            return line.replace(m.group(0), result + ';')

    # Read: gBattleMons[idx].status2 & STATUS2_FOO (in expression, no assignment)
    # Replace inline
    def replace_status2_check(m2):
        idx = m2.group(1)
        vpath = f'gBattleMons[{idx}].volatiles'
        # Find which STATUS2 constant follows
        rest = line[m2.end():]
        # Check what's after
        for const, field in {**STATUS2_SINGLE, **STATUS2_MULTI}.items():
            if rest.lstrip().startswith(f'& {const}') or rest.lstrip().startswith(f'&{const}'):
                return f'{vpath}.{field}'
        return m2.group(0)  # fallback: no change

    # Assignment: gStatuses3[idx] op= rhs;
    m = re.search(
        r'(gStatuses3\[([^\]]+)\])\s*([|&]?=)\s*([^;]+);',
        line
    )
    if m:
        full_lhs, idx, op, rhs = m.group(1), m.group(2), m.group(3), m.group(4)
        result = transform_status3_expr(idx, op, rhs)
        if result:
            return line.replace(m.group(0), result + ';')

    return None


def transform_inline_reads(line: str) -> str:
    """
    Replace inline read expressions:
      gBattleMons[X].status2 & STATUS2_FOO  → gBattleMons[X].volatiles.field
      gStatuses3[X] & STATUS3_FOO            → gBattleMons[X].volatiles.field
    """
    changed = False

    # STATUS2 inline reads
    def sub_status2(m):
        idx = m.group(1)
        vpath = f'gBattleMons[{idx}].volatiles'
        pos = m.end()
        suffix = line[pos:]

        # Check for & STATUS2_INFATUATED_WITH(b)
        mf = re.match(r'\s*&\s*STATUS2_INFATUATED_WITH\(([^)]+)\)', suffix)
        if mf:
            b = mf.group(1)
            return f'({vpath}.infatuation & gBitTable[{b}])', pos + len(mf.group(0))

        # Check each STATUS2 constant
        for const, field in {**STATUS2_SINGLE, **STATUS2_MULTI}.items():
            pat = re.match(r'\s*&\s*' + re.escape(const) + r'\b', suffix)
            if pat:
                return f'{vpath}.{field}', pos + len(pat.group(0))

        # No known STATUS2 found after the access
        return None, pos

    # STATUS3 inline reads
    def sub_status3(m):
        idx = m.group(1)
        vpath = f'gBattleMons[{idx}].volatiles'
        pos = m.end()
        suffix = line[pos:]

        # Semi-invulnerable composites
        for const, (field, state) in STATUS3_SEMI_INVULNERABLE.items():
            pat = re.match(r'\s*&\s*' + re.escape(const) + r'\b', suffix)
            if pat:
                if const == 'STATUS3_SEMI_INVULNERABLE':
                    return f'({vpath}.{field} != STATE_NONE)', pos + len(pat.group(0))
                else:
                    return f'({vpath}.{field} == {state})', pos + len(pat.group(0))

        # Leech seed battler bits
        pat = re.match(r'\s*&\s*STATUS3_LEECHSEED_BATTLER\b', suffix)
        if pat:
            return f'{vpath}.leechSeed', pos + len(pat.group(0))

        # Single + multi
        for const, field in {**STATUS3_SINGLE, **STATUS3_MULTI}.items():
            pat = re.match(r'\s*&\s*' + re.escape(const) + r'\b', suffix)
            if pat:
                return f'{vpath}.{field}', pos + len(pat.group(0))

        return None, pos

    # Process STATUS2 reads (left to right, avoiding double-replacement)
    result = line
    offset = 0
    for m in BATTLER_STATUS2.finditer(line):
        new_expr, end_pos = sub_status2(m)
        if new_expr:
            old_expr = line[m.start():end_pos]
            result = result.replace(old_expr, new_expr, 1)
            changed = True

    line = result
    offset = 0
    result = line
    for m in BATTLER_STATUS3.finditer(line):
        new_expr, end_pos = sub_status3(m)
        if new_expr:
            old_expr = line[m.start():end_pos]
            result = result.replace(old_expr, new_expr, 1)
            changed = True

    return result


def transform_line(line: str) -> tuple[str, bool]:
    """Transform a single line. Returns (new_line, was_changed)."""
    if 'status2' not in line and 'gStatuses3' not in line:
        return line, False

    # Try statement-level transform first
    new_line = try_transform_statement(line)
    if new_line and new_line != line:
        return new_line, True

    # Then try inline read transforms
    new_line2 = transform_inline_reads(line)
    if new_line2 != line:
        return new_line2, True

    return line, False


# ---------------------------------------------------------------------------
# File processing
# ---------------------------------------------------------------------------

def process_file(path: Path) -> tuple[int, list[int]]:
    """Returns (num_changed_lines, list_of_unhandled_line_numbers)."""
    text = path.read_text(encoding='utf-8', errors='replace')
    lines = text.splitlines(keepends=True)

    new_lines = []
    changed = 0
    unhandled = []

    for i, line in enumerate(lines, 1):
        new_line, was_changed = transform_line(line)
        new_lines.append(new_line)
        if was_changed:
            changed += 1
        elif ('status2' in line or 'gStatuses3' in line):
            # Line still contains status2/gStatuses3 — unhandled
            unhandled.append(i)

    if changed > 0 and not DRY_RUN:
        path.write_text(''.join(new_lines), encoding='utf-8')

    return changed, unhandled


# ---------------------------------------------------------------------------
# Main
# ---------------------------------------------------------------------------

def main():
    files = sorted(SRC_DIR.glob('**/*.c')) + sorted(SRC_DIR.glob('**/*.h'))
    # Also check include/ headers
    include_dir = REPO / 'include'
    files += sorted(include_dir.glob('**/*.h'))

    total_changed = 0
    total_unhandled = 0
    unhandled_report = []

    for path in files:
        try:
            changed, unhandled = process_file(path)
        except Exception as e:
            print(f'ERROR processing {path}: {e}')
            continue
        if changed or unhandled:
            rel = path.relative_to(REPO)
            if changed:
                mode = '(dry-run)' if DRY_RUN else ''
                print(f'  {rel}: {changed} line(s) transformed {mode}')
                total_changed += changed
            for lineno in unhandled:
                unhandled_report.append((rel, lineno))
                total_unhandled += 1

    print(f'\n--- Summary ---')
    print(f'  Lines transformed: {total_changed}')
    print(f'  Unhandled occurrences: {total_unhandled}')
    if unhandled_report:
        print('\n  Unhandled (need manual fix):')
        for rel, lineno in unhandled_report:
            print(f'    {rel}:{lineno}')


if __name__ == '__main__':
    main()
