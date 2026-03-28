// Extracted from RHH src/battle_ai_util.c:3776-3794
// 19 lines
// Dependencies: AI_CanBattlerEscape, BattlerWillFaintFromSecondaryDamage, CanTargetFaintAi, IsBattlerTrapped, ShouldTrap

bool32 ShouldTrap(enum BattlerId battlerAtk, enum BattlerId battlerDef, enum Move move)
{
    if (AI_CanBattlerEscape(battlerDef))
        return FALSE;

    if (IsBattlerTrapped(battlerAtk, battlerDef))
        return FALSE;

    if (BattlerWillFaintFromSecondaryDamage(battlerDef, gAiLogicData->abilities[battlerDef]))
        return TRUE;    // battler is taking secondary damage with low HP

    if (gAiThinkingStruct->aiFlags[battlerAtk] & AI_FLAG_STALL)
    {
        if (!CanTargetFaintAi(battlerDef, battlerAtk))
            return TRUE;    // attacker goes first and opponent can't kill us
    }

    return FALSE;
}
