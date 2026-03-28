// Extracted from RHH src/battle_ai_util.c:5648-5654
// 7 lines
// Dependencies: AI_TryToClearStats, BATTLE_PARTNER, CountPositiveStatStages, min

s32 AI_TryToClearStats(enum BattlerId battlerAtk, enum BattlerId battlerDef, bool32 isDoubleBattle)
{
    if (isDoubleBattle)
        return min(CountPositiveStatStages(battlerDef) + CountPositiveStatStages(BATTLE_PARTNER(battlerDef)), 7);
    else
        return min(CountPositiveStatStages(battlerDef), 4);
}
