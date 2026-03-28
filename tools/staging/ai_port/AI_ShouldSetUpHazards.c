// Extracted from RHH src/battle_ai_util.c:5687-5710
// 24 lines
// Dependencies: AI_ShouldSetUpHazards, CountUsablePartyMons, DoesBattlerIgnoreAbilityChecks, HasBattlerSideMoveWithAIEffect, HasMoveWithEffect, IsBattleMoveStatus

bool32 AI_ShouldSetUpHazards(enum BattlerId battlerAtk, enum BattlerId battlerDef, enum Move move, struct AiLogicData *aiData)
{
    if (CountUsablePartyMons(battlerDef) == 0
     || HasBattlerSideMoveWithAIEffect(battlerDef, AI_EFFECT_CLEAR_HAZARDS))
        return FALSE;

    if (IsBattleMoveStatus(move))
    {
        if (HasMoveWithEffect(battlerDef, EFFECT_MAGIC_COAT))
            return FALSE;
        if (DoesBattlerIgnoreAbilityChecks(battlerAtk, aiData->abilities[battlerAtk], move))
            return TRUE;
        if (aiData->abilities[battlerDef] == ABILITY_MAGIC_BOUNCE)
            return FALSE;
    }
    else
    {
        if (DoesBattlerIgnoreAbilityChecks(battlerAtk, aiData->abilities[battlerAtk], move))
            return TRUE;
        if (aiData->abilities[battlerDef] == ABILITY_SHIELD_DUST)
            return FALSE;
    }
    return TRUE;
}
