import re

fallback_map = {
    "MOVE_BUG_BITE": "Move_BITE",
    "MOVE_SUCKER_PUNCH": "Move_FAINT_ATTACK",
    "MOVE_ASSURANCE": "Move_FAINT_ATTACK",
    "MOVE_DISARMING_VOICE": "Move_HYPER_VOICE",
    "MOVE_NUZZLE": "Move_SPARK",
    "MOVE_LOW_SWEEP": "Move_LOW_KICK",
    "MOVE_ROCK_POLISH": "Move_AGILITY",
}

moves = []
with open("include/constants/moves.h", "r") as f:
    for line in f:
        m = re.match(r"#define (MOVE_[A-Z0-9_]+)\s+([0-9]+)", line.strip())
        if m:
            moves.append((m.group(1), int(m.group(2))))

max_move = max(m[1] for m in moves)
move_dict = {m[1]: m[0] for m in moves}

with open("data/battle_anim_scripts.s", "r") as f:
    anim_content = f.read()

# find labels with single or double colons
valid_labels = set(re.findall(r"(Move_[A-Za-z0-9_]+):", anim_content))
# also check if any are exported explicitly or exist in other files
# we know Move_NONE exists. We should trust fallbacks. If it's a native move < 355 it usually exists.
# Wait, some animations might be in other files? Actually all are in battle_anim_scripts.s

new_table = ["gBattleAnims_Moves::"]
missing_labels = []
for i in range(max_move + 1):
    if i in move_dict:
        move_macro = move_dict[i]
        move_anim = "Move_" + move_macro.replace("MOVE_", "")
        
        if move_macro in fallback_map:
            move_anim = fallback_map[move_macro]
        elif move_anim not in valid_labels and move_anim != "Move_NONE":
            # Just assume it exists? No, if it doesn't exist, compilation will FAIL with undefined reference!
            # Let's map to Move_NONE to be safe
            missing_labels.append(move_anim)
            move_anim = "Move_NONE"
        new_table.append(f"\t.4byte {move_anim}")
    else:
        new_table.append("\t.4byte Move_NONE")

new_table_str = "\n".join(new_table) + "\n\n"

start_idx = anim_content.find("gBattleAnims_Moves::")
lines = anim_content[start_idx:].split('\n')
end_line_idx = 0
for i, line in enumerate(lines):
    if i == 0 or line.strip().startswith(".4byte") or line.strip() == "":
        pass
    else:
        end_line_idx = i
        break
end_idx = start_idx + sum(len(l)+1 for l in lines[:end_line_idx])

with open("data/battle_anim_scripts.s", "w") as f:
    f.write(anim_content[:start_idx] + new_table_str + anim_content[end_idx:])

print(f"Updated gBattleAnims_Moves. Missing {len(missing_labels)} labels replaced with NONE.")
