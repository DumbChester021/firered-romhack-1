// Extracted from RHH src/battle_ai_util.c:205-210
// 6 lines
// Dependencies: CanAiPredictMove, GetIncomingMove

enum Move GetIncomingMove(enum BattlerId battler, enum BattlerId opposingBattler, struct AiLogicData *aiData)
{
    if (aiData->predictingMove && CanAiPredictMove(battler))
        return aiData->predictedMove[opposingBattler];
    return aiData->lastUsedMove[opposingBattler];
}
