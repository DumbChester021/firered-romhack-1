#include "global.h"
#include "battle.h"
#include "battle_anim.h"
#include "battle_ai_util.h"
#include "battle_script_commands.h"
#include "pokemon.h"
#include "random.h"
#include "constants/battle.h"
#include "constants/moves.h"

// AI_CalcDamage: Returns an estimated damage value for the AI's move selection.
// Calls FireRed's existing AI_CalcDmg + TypeCalc (from battle_script_commands.c)
// which use gBattleMoveDamage as an in/out global.
// Returns 0 if the move has no power, or is completely negated by type immunity.
// Sets *typeEffectiveness to the MOVE_RESULT_* flags from TypeCalc.
s32 AI_CalcDamage(u16 move, u8 battlerAtk, u8 battlerDef, u8 *typeEffectiveness)
{
    s32 dmg;
    u8 flags;

    if (gBattleMoves[move].power < 2)
    {
        if (typeEffectiveness != NULL)
            *typeEffectiveness = 0;
        return 0;
    }

    // Save and set up state the same way Cmd_if_can_faint does.
    gDynamicBasePower = 0;
    gBattleStruct->dynamicMoveType = 0;
    gBattleScripting.dmgMultiplier = 1;
    gMoveResultFlags = 0;
    gCritMultiplier = 1;
    gCurrentMove = move;

    AI_CalcDmg(battlerAtk, battlerDef);
    flags = TypeCalc(move, battlerAtk, battlerDef);

    // Apply the AI's simulated RNG factor (97 = ~midpoint of 85–100 range, conservative).
    // This is not index-based like the old VM; we use a fixed midpoint.
    gBattleMoveDamage = gBattleMoveDamage * 97 / 100;
    if (gBattleMoveDamage == 0)
        gBattleMoveDamage = 1;

    // If the move is completely negated (Levitate vs Ground, type immunity, etc.), return 0.
    if (flags & (MOVE_RESULT_DOESNT_AFFECT_FOE | MOVE_RESULT_MISSED))
        dmg = 0;
    else
        dmg = gBattleMoveDamage;

    if (typeEffectiveness != NULL)
        *typeEffectiveness = flags;

    return dmg;
}

// AI_IsFaster: Returns TRUE if battlerAtk moves before battlerDef for the given move,
// accounting for move priority.
bool8 AI_IsFaster(u8 battlerAtk, u8 battlerDef, u16 move)
{
    s8 priority = gBattleMoves[move].priority;
    u16 spdAtk = gBattleMons[battlerAtk].speed;
    u16 spdDef = gBattleMons[battlerDef].speed;

    if (priority > 0)
        return TRUE;
    if (priority < 0)
        return FALSE;

    return spdAtk >= spdDef;
}

// AI_HasMoveEffect: Returns TRUE if any of battlerAtk's current moves have the given effect ID.
bool8 AI_HasMoveEffect(u8 battlerAtk, u16 effect)
{
    u8 i;
    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        u16 move = gBattleMons[battlerAtk].moves[i];
        if (move != MOVE_NONE && gBattleMoves[move].effect == effect)
            return TRUE;
    }
    return FALSE;
}

// AI_CountAlivePokemon: Counts non-fainted (HP > 0) mons in battler's party.
u8 AI_CountAlivePokemon(u8 battler)
{
    struct Pokemon *party = (GetBattlerSide(battler) == B_SIDE_PLAYER)
                             ? gPlayerParty
                             : gEnemyParty;
    u8 count = 0;
    u8 i;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        if (GetMonData(&party[i], MON_DATA_SPECIES, NULL) != SPECIES_NONE
         && GetMonData(&party[i], MON_DATA_HP, NULL) > 0)
            count++;
    }
    return count;
}
