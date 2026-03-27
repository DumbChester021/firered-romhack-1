import re
import os

target_moves = [
    "ROOST", "FLARE_BLITZ", "BRAVE_BIRD", "EARTH_POWER", "BUG_BUZZ",
    "DARK_PULSE", "ENERGY_BALL", "SEED_BOMB", "X_SCISSOR", "POISON_JAB",
    "GIGA_IMPACT", "CAPTIVATE", "ROUND", "CONFIDE", "TERA_BLAST",
    "ZEN_HEADBUTT", "BULLDOZE", "WORK_UP", "POWER_UP_PUNCH", "TRAILBLAZE",
    "BUG_BITE", "SUCKER_PUNCH", "ASSURANCE", "DISARMING_VOICE", "NUZZLE",
    "LOW_SWEEP", "ROCK_POLISH", "WORRY_SEED", "SHELL_SMASH", "EERIE_IMPULSE"
]

files_to_check = {
    "moves_info": "src/data/moves_info.h",
    "ai_main": "src/battle_ai_main.c",
    "anim_scripts": "data/battle_anim_scripts.s",
    "scripts": "data/battle_scripts_1.s",
    "effects": "src/data/battle_scripts_for_move_effects.h",
    "cmd": "src/battle_script_commands.c"
}

results = {m: {} for m in target_moves}

# 1. Read moves_info
with open(files_to_check["moves_info"], "r") as f:
    content = f.read()
for m in target_moves:
    pattern = rf"\[MOVE_{m}\]\s*=\s*{{(.*?)}}"
    match = re.search(pattern, content, re.DOTALL)
    if match:
        body = match.group(1)
        results[m]["effect"] = re.search(r"\.effect\s*=\s*([A-Z0-9_]+)", body).group(1) if ".effect" in body else "UNKNOWN"
        results[m]["power"] = re.search(r"\.power\s*=\s*([0-9]+)", body).group(1) if ".power" in body else "0"
        results[m]["category"] = re.search(r"\.category\s*=\s*([A-Z0-9_]+)", body).group(1) if ".category" in body else "UNKNOWN"
    else:
        results[m]["effect"] = "MISSING"

# 2. Check AI
with open(files_to_check["ai_main"], "r") as f:
    ai_content = f.read()
for m in target_moves:
    eff = results[m].get("effect", "")
    results[m]["has_ai"] = eff in ai_content or m in ai_content

# 3. Check Anim
with open(files_to_check["anim_scripts"], "r") as f:
    anim = f.read()
# Extract the gBattleAnims_Moves array
anim_array = re.search(r"gBattleAnims_Moves::(.*?)(?=\n\n|\Z)", anim, re.DOTALL)
anim_content = anim_array.group(1) if anim_array else ""
for m in target_moves:
    results[m]["has_anim"] = f"Move_{m}" in anim or f"Move_{m}" in anim_content

print("Move | Effect | Power | Category | AI | Anim")
print("---|---|---|---|---|---")
for m in target_moves:
    r = results[m]
    print(f"{m} | {r.get('effect')} | {r.get('power')} | {r.get('category')} | {r.get('has_ai')} | {r.get('has_anim')}")
