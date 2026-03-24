import re
import glob
import os

files_to_check = glob.glob('src/battle*.c')

def process_file(filepath):
    with open(filepath, 'r') as f:
        content = f.read()
    
    # Don't replace initialization assignments like `gBattleMons[i].type1 = type;`
    # Replace when it's just reading the property.
    # Actually, assignment is rare in battle engine outside of specific edge cases like Conversion, Camouflage, reflect type.
    # We should use a regex that captures reads, but realistically it's easier to just replace all `gBattleMons[X].type1` except a few known ones.
    # Or just replace `gBattleMons\[(.*?)\]\.type([12])` with `GetBattlerType\2(\1)`
    # Let's inspect manually if we do assignment! 
    # gBattleMons[gActiveBattler].type1 = ... in battle_main.c (initialization)
    
    # Let's be smart: only replace if it's NOT followed by an equals sign `=`.
    # E.g. `gBattleMons[x].type1` not followed by ` = ` or `=`
    
    # Regex: replace `gBattleMons[X].typeY` not followed optionally by whitespace then '='
    # Negative lookahead: (?!\s*=)
    new_content = re.sub(r'gBattleMons\[([^\]]+)\]\.type([12])(?!\s*=)', 
                         r'GetBattlerType\2(\1)', 
                         content)

    # Some macros like IS_BATTLER_OF_TYPE might use it. We'll update include/battle.h manually.

    if new_content != content:
        with open(filepath, 'w') as f:
            f.write(new_content)
        print(f"Updated {filepath}")

for f in files_to_check:
    process_file(f)
