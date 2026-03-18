import re

firered_egg_moves = "/mnt/data/Github/prototype/firered-romhack-1/src/data/pokemon/egg_moves.h"
firered_moves = "/mnt/data/Github/prototype/firered-romhack-1/include/constants/moves.h"
rrh_egg_moves = "/mnt/data/Github/prototype/pokeemerald-expansion/src/data/pokemon/egg_moves.h"

valid_firered_moves = set()
with open(firered_moves, "r") as f:
    for line in f:
        match = re.match(r"#define\s+(MOVE_\w+)", line)
        if match:
            valid_firered_moves.add(match.group(1))

firered_species = set()
with open(firered_egg_moves, "r") as f:
    for line in f:
        match = re.search(r"egg_moves\s*\(\s*(\w+)\s*,", line)
        if match:
            # Handle potential naming differences: MR_MIME vs MRMIME, MIME_JR, MIME_JR_, MIME_JR etc.
            # But the egg_moves macro usually uses the exact species name without SPECIES_.
            firered_species.add(match.group(1).upper())

# Add some known name adjustments (MIME_JR vs MIME_JR_ etc if they existed, but we only have Gen 1-3)
# To be safe, let's just use the exact names from Firered.
firered_species.add("NIDORAN_F")
firered_species.add("NIDORAN_M")
firered_species.add("MR_MIME")

new_moves = {}

active_family = None
with open(rrh_egg_moves, "r") as f:
    for line in f:
        match_family = re.match(r"#if P_FAMILY_(\w+)", line)
        if match_family:
            active_family = match_family.group(1).upper()
            continue
            
        match_end = re.match(r"#endif //P_FAMILY_(\w+)", line)
        if match_end:
            active_family = None
            continue
            
        # Match moves
        if active_family:
            # Let's map family name back to a potential firered species name
            # P_FAMILY_NIDORAN -> NIDORAN_F / NIDORAN_M
            family_base = active_family
            # For simplicity, if the family matches any prefix of a firered species, we count it.
            # Or if it's NIDORAN, we consider it.
            matches_firered = False
            if family_base in firered_species:
                matches_firered = True
            elif family_base == "NIDORAN":
                matches_firered = True
            elif family_base == "MR_MIME":
                matches_firered = True
            
            if matches_firered:
                match_move = re.search(r"(MOVE_\w+)", line)
                if match_move:
                    m = match_move.group(1)
                    if m not in valid_firered_moves and m != "MOVE_UNAVAILABLE":
                        if m not in new_moves:
                            new_moves[m] = set()
                        new_moves[m].add(family_base)

# Generate artifact
artifact_path = "/mnt/data/Github/prototype/firered-romhack-1/docs/missing_egg_moves.md"
with open(artifact_path, "w") as out:
    out.write("# Missing Egg Moves for FireRed Pokémon\n\n")
    out.write("Based on the `pokeemerald-expansion`, here are the egg moves that FireRed Pokémon have in later generations, but are currently not implemented in this FireRed repository (`include/constants/moves.h`).\n\n")
    
    sorted_moves = sorted(new_moves.items(), key=lambda x: (-len(x[1]), x[0]))
    out.write("| Move | Learned By (Family) | Number of Families |\n")
    out.write("|------|---------------------|--------------------|\n")
    for move, species_set in sorted_moves:
         species_list = ", ".join(sorted(list(species_set)))
         out.write(f"| `{move}` | {species_list} | {len(species_set)} |\n")
    
    out.write("\n")
    out.write(f"Total missing moves: {len(sorted_moves)}\n")

print("Artifact generated.")
