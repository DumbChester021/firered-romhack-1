// Extracted from RHH src/battle_ai_util.c:1589-1627
// 39 lines
// Dependencies: AI_GetDamage, CanAIFaintTarget, CanIndexMoveFaintTarget, GetBestDmgMovesFromBattler, GetMovePower, GetMovesArray, IsMoveUnusable

void GetBestDmgMovesFromBattler(enum BattlerId battlerAtk, enum BattlerId battlerDef, enum DamageCalcContext calcContext, enum Move *bestMoves)
{
    struct AiLogicData *aiData = gAiLogicData;
    u32 bestDmg = 0;
    enum Move *moves = GetMovesArray(battlerAtk);
    u32 moveLimitations = aiData->moveLimitations[battlerAtk];
    u32 countBestMoves = 0;

    if (CanAIFaintTarget(battlerAtk, battlerDef, 1))
    {
        for (u32 moveIndex = 0; moveIndex < MAX_MON_MOVES; moveIndex++)
        {
            if (CanIndexMoveFaintTarget(battlerAtk, battlerDef, moveIndex, AI_ATTACKING))
                bestMoves[countBestMoves++] = moves[moveIndex];
        }
    }
    else
    {
        for (u32 moveIndex = 0; moveIndex < MAX_MON_MOVES; moveIndex++)
        {
            if (IsMoveUnusable(moveIndex, moves[moveIndex], moveLimitations)
            || (GetMovePower(moves[moveIndex]) == 0)
            || (AI_GetDamage(battlerAtk, battlerDef, moveIndex, calcContext, aiData) == 0))
                continue;

            if (bestDmg < AI_GetDamage(battlerAtk, battlerDef, moveIndex, calcContext, aiData))
            {
                countBestMoves = 0;
                bestDmg = AI_GetDamage(battlerAtk, battlerDef, moveIndex, calcContext, aiData);
                *bestMoves = 0;
                bestMoves[countBestMoves++] = moves[moveIndex];
            }
            else if (bestDmg == AI_GetDamage(battlerAtk, battlerDef, moveIndex, calcContext, aiData))
            {
                bestMoves[countBestMoves++] = moves[moveIndex];
            }
        }
    }
}
