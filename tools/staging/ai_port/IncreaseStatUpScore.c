// Extracted from RHH src/battle_ai_util.c:4970-4973
// 4 lines
// Dependencies: IncreaseStatUpScore, IncreaseStatUpScoreInternal

enum AIScore IncreaseStatUpScore(enum BattlerId battlerAtk, enum BattlerId battlerDef, enum StatChange statChange)
{
    return IncreaseStatUpScoreInternal(battlerAtk, battlerDef, statChange, TRUE);
}
