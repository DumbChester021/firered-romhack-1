// Extracted from RHH src/battle_ai_util.c:213-223
// 11 lines
// Dependencies: CanAiPredictMove, GetIncomingMoveSpeedCheck, GetMoveEffect, GetMovePower

enum Move GetIncomingMoveSpeedCheck(enum BattlerId battler, enum BattlerId opposingBattler, struct AiLogicData *aiData)
{
    if (aiData->predictingMove && CanAiPredictMove(battler))
    {
        // Ignore moves that don't do damage or only have priority one time
        if (GetMovePower(aiData->predictedMove[opposingBattler]) != 0 && GetMoveEffect(aiData->predictedMove[opposingBattler]) != EFFECT_FIRST_TURN_ONLY)
            return aiData->predictedMove[opposingBattler];
    }

    return MOVE_NONE;
}
