// Extracted from RHH src/battle_ai_util.c:190-202
// 13 lines
// Dependencies: IsBattlerPredictedToSwitch

bool32 IsBattlerPredictedToSwitch(enum BattlerId battler)
{
    // Check for prediction flag on AI, whether they're using those predictions this turn, and whether the AI thinks the player should switch
    for (enum BattlerId battlerIndex = 0; battlerIndex < MAX_BATTLERS_COUNT; battlerIndex++)
    {
        if (gAiThinkingStruct->aiFlags[battlerIndex] & AI_FLAG_PREDICT_SWITCH)
        {
            if (gAiLogicData->predictingSwitch && gAiLogicData->shouldSwitch & (1u << battler))
                return TRUE;
        }
    }
    return FALSE;
}
