import re

early_pokemon = [
    "Bulbasaur", "Ivysaur", "Venusaur",
    "Charmander", "Charmeleon", "Charizard",
    "Squirtle", "Wartortle", "Blastoise",
    "Caterpie", "Metapod", "Butterfree",
    "Weedle", "Kakuna", "Beedrill",
    "Pidgey", "Pidgeotto", "Pidgeot",
    "Rattata", "Raticate", "AlolanRattata", "AlolanRaticate",
    "Spearow", "Fearow",
    "Ekans", "Arbok",
    "Pikachu", "Raichu", "AlolanRaichu",
    "Sandshrew", "Sandslash", "AlolanSandshrew", "AlolanSandslash",
    "NidoranF", "Nidorina", "Nidoqueen",
    "NidoranM", "Nidorino", "Nidoking",
    "Clefairy", "Clefable",
    "Jigglypuff", "Wigglytuff",
    "Zubat", "Golbat", "Crobat",
    "Oddish", "Gloom", "Vileplume", "Bellossom",
    "Paras", "Parasect",
    "Venonat", "Venomoth",
    "Diglett", "Dugtrio", "AlolanDiglett", "AlolanDugtrio",
    "Meowth", "Persian", "AlolanMeowth", "AlolanPersian", "GalarianMeowth",
    "Psyduck", "Golduck",
    "Mankey", "Primeape", "Annihilape",
    "Abra", "Kadabra", "Alakazam",
    "Geodude", "Graveler", "Golem", "AlolanGeodude", "AlolanGraveler", "AlolanGolem",
    "Onix",
    "Staryu", "Starmie"
]

rhh_file = "/mnt/data/Github/rh-hideout/pokeemerald-expansion/src/data/pokemon/level_up_learnsets/gen_9.h"
fr_file = "/mnt/data/Github/prototype/firered-romhack-1/src/data/pokemon/level_up_learnsets.h"

with open(rhh_file, "r") as f:
    rhh_content = f.read()

learnsets = {}
for mon in early_pokemon:
    arr_name = f"s{mon}LevelUpLearnset"
    pattern = rf"(static const struct LevelUpMove {arr_name}\[\]\s*=\s*{{)(.*?)(}};\n)"
    match = re.search(pattern, rhh_content, re.DOTALL)
    if match:
        body = match.group(2)
        # RHH uses LEVEL_UP_END, FR uses LEVEL_UP_END_ENTRY
        body = body.replace("LEVEL_UP_END", "LEVEL_UP_END_ENTRY")
        learnsets[arr_name] = match.group(1) + body + match.group(3)

with open(fr_file, "r") as f:
    fr_content = f.read()

replaced_count = 0
for arr_name, new_data in learnsets.items():
    pattern = rf"(static const struct LevelUpMove {arr_name}\[\]\s*=\s*{{)(.*?)(}};\n)"
    if re.search(pattern, fr_content, re.DOTALL):
        fr_content = re.sub(pattern, lambda m: new_data, fr_content, flags=re.DOTALL)
        replaced_count += 1
    else:
        # Some arrays might not exist in FR (e.g. Alolan, Galarian forms)
        pass

with open(fr_file, "w") as f:
    f.write(fr_content)

print(f"Successfully replaced {replaced_count} learnsets in firered using Gen 9 RHH data.")
