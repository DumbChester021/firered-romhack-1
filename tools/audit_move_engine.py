#!/usr/bin/env python3
"""
audit_move_engine.py — Pre-flight check before BattleMove struct expansion.

Detects all code sites that MUST change when:
  - struct BattleMove gains u16 effect (was u8), named flag fields (was u8 bitfield)
  - struct LevelUpMove changes from packed u16 to { u16 move; u16 level; }

Usage:
    python3 tools/audit_move_engine.py [--no-color]

Exit codes:
    0 = all categories empty (safe to proceed)
    1 = issues found (resolve before expanding struct)
"""

import sys
import re
import os
from pathlib import Path

ROOT = Path(__file__).parent.parent
SCAN_EXTS = {".c", ".h", ".s", ".inc"}

NO_COLOR = "--no-color" in sys.argv
RED    = "" if NO_COLOR else "\033[31m"
YELLOW = "" if NO_COLOR else "\033[33m"
GREEN  = "" if NO_COLOR else "\033[32m"
BOLD   = "" if NO_COLOR else "\033[1m"
RESET  = "" if NO_COLOR else "\033[0m"

# ---------------------------------------------------------------------------
# Patterns
# ---------------------------------------------------------------------------

CATEGORIES = [
    {
        "id": "FLAGS_BITFIELD",
        "description": "'.flags & FLAG_*' — must become named field access after struct change",
        "severity": "ERROR",
        "patterns": [
            re.compile(r'\.flags\s*&\s*FLAG_\w+'),
            re.compile(r'FLAG_\w+\s*&\s*.*\.flags'),
        ],
        "exclude_patterns": [
            # Skip the FLAG_ defines themselves
            re.compile(r'^\s*#define\s+FLAG_'),
        ],
    },
    {
        "id": "FLAG_DEFINES_USE",
        "description": "FLAG_* macro uses outside of battle_moves.h — flag after all access sites converted",
        "severity": "WARNING",
        "patterns": [
            re.compile(r'\bFLAG_MAKES_CONTACT\b'),
            re.compile(r'\bFLAG_PROTECT_AFFECTED\b'),
            re.compile(r'\bFLAG_MAGIC_COAT_AFFECTED\b'),
            re.compile(r'\bFLAG_SNATCH_AFFECTED\b'),
            re.compile(r'\bFLAG_MIRROR_MOVE_AFFECTED\b'),
            re.compile(r'\bFLAG_KINGS_ROCK_AFFECTED\b'),
            re.compile(r'\bFLAG_SOUND_MOVE\b'),
        ],
        "skip_files": [
            "src/data/battle_moves.h",   # flag source — ok to have until Phase 1 completes
            "include/constants/pokemon.h",  # defines file
        ],
    },
    {
        "id": "U8_EFFECT_LOCAL",
        "description": "u8 local storing .effect — will silently truncate when effect becomes u16",
        "severity": "ERROR",
        "patterns": [
            re.compile(r'\bu8\s+\w*[Ee]ffect\w*\s*=\s*gBattleMoves\['),
            re.compile(r'\bu8\s+\w*[Ee]ffect\w*\s*=\s*.*gBattleMoves\[.*\]\.effect'),
        ],
    },
    {
        "id": "EFFECT_ARRAY_INDEX",
        "description": "gBattleScriptsForMoveEffects[...effect...] — array must cover u16 range when new effects added",
        "severity": "INFO",
        "patterns": [
            re.compile(r'gBattleScriptsForMoveEffects\['),
        ],
    },
    {
        "id": "LEVELUP_MACRO_ENCODE",
        "description": "LEVEL_UP_MOVE() macro use — encoding changes from bitpack to struct literal",
        "severity": "ERROR",
        "patterns": [
            re.compile(r'\bLEVEL_UP_MOVE\s*\('),
        ],
        "skip_files": [
            "src/data/pokemon/level_up_learnsets.h",  # data file, expected
        ],
    },
    {
        "id": "LEVELUP_BITMASK",
        "description": "LEVEL_UP_MOVE_LV / LEVEL_UP_MOVE_ID bitmask access — must become struct field access",
        "severity": "ERROR",
        "patterns": [
            re.compile(r'\bLEVEL_UP_MOVE_LV\b'),
            re.compile(r'\bLEVEL_UP_MOVE_ID\b'),
            re.compile(r'<<\s*9\b.*level|level.*<<\s*9\b'),  # raw bit shift for level
        ],
    },
    {
        "id": "LEVELUP_END_SENTINEL",
        "description": "LEVEL_UP_END == comparison — sentinel value format changes with struct",
        "severity": "ERROR",
        "patterns": [
            re.compile(r'\bLEVEL_UP_END\b'),
        ],
        "skip_files": [
            "src/data/pokemon/level_up_learnsets.h",  # data file, expected
        ],
    },
    {
        "id": "ASM_BATTLEMOVE_OFFSET",
        "description": "ASM directly referencing BattleMove struct offsets (should be zero)",
        "severity": "ERROR",
        "patterns": [
            re.compile(r'gBattleMoves', re.IGNORECASE),
        ],
        "extensions": {".s", ".inc"},
    },
]

# ---------------------------------------------------------------------------
# Scanner
# ---------------------------------------------------------------------------

def scan_file(path: Path, category: dict) -> list[tuple[int, str]]:
    exts = category.get("extensions", SCAN_EXTS)
    if path.suffix not in exts:
        return []
    skip_files = category.get("skip_files", [])
    rel = str(path.relative_to(ROOT))
    if any(rel.endswith(s) or rel == s for s in skip_files):
        return []
    exclude_patterns = category.get("exclude_patterns", [])

    hits = []
    try:
        lines = path.read_text(encoding="utf-8", errors="replace").splitlines()
    except Exception:
        return []

    for lineno, line in enumerate(lines, 1):
        if any(ep.search(line) for ep in exclude_patterns):
            continue
        for pat in category["patterns"]:
            if pat.search(line):
                hits.append((lineno, line.rstrip()))
                break
    return hits


def run_audit():
    all_files = [
        p for p in ROOT.rglob("*")
        if p.is_file() and p.suffix in SCAN_EXTS
        and ".git" not in p.parts
        and "build" not in p.parts
    ]

    total_errors = 0
    total_warnings = 0

    for cat in CATEGORIES:
        results: dict[str, list] = {}
        for f in all_files:
            hits = scan_file(f, cat)
            if hits:
                results[str(f.relative_to(ROOT))] = hits

        sev = cat["severity"]
        color = RED if sev == "ERROR" else (YELLOW if sev == "WARNING" else "")
        count = sum(len(v) for v in results.values())

        print(f"\n{BOLD}{color}[{sev}] {cat['id']}{RESET}")
        print(f"  {cat['description']}")
        print(f"  Found: {count} site(s) across {len(results)} file(s)")

        if results:
            for rel_path, hits in sorted(results.items()):
                print(f"  {BOLD}{rel_path}{RESET}")
                for lineno, content in hits[:10]:  # cap output per file
                    print(f"    L{lineno}: {content.strip()[:120]}")
                if len(hits) > 10:
                    print(f"    ... and {len(hits) - 10} more")

        if sev == "ERROR":
            total_errors += count
        elif sev == "WARNING":
            total_warnings += count

    print(f"\n{'='*60}")
    if total_errors == 0 and total_warnings == 0:
        print(f"{GREEN}{BOLD}AUDIT CLEAN — safe to proceed with struct expansion.{RESET}")
    else:
        print(f"{RED}{BOLD}{total_errors} ERROR(S){RESET}  {YELLOW}{total_warnings} WARNING(S){RESET}")
        if total_errors > 0:
            print(f"{RED}Resolve all ERRORs before expanding struct.{RESET}")

    return 1 if total_errors > 0 else 0


if __name__ == "__main__":
    sys.exit(run_audit())
