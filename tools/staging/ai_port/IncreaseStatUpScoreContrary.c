// Extracted from RHH src/battle_ai_util.c:4975-4978
// 4 lines
// Dependencies: IncreaseStatUpScoreContrary, IncreaseStatUpScoreInternal

enum AIScore IncreaseStatUpScoreContrary(enum BattlerId battlerAtk, enum BattlerId battlerDef, enum StatChange statChange)
{
    return IncreaseStatUpScoreInternal(battlerAtk, battlerDef, statChange, FALSE);
}
