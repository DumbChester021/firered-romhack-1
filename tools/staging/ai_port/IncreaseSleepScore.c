// Extracted from RHH src/battle_ai_util.c:5066-5096
// 31 lines
// Dependencies: ADJUST_SCORE_PTR, AI_CanPutToSleep, BATTLE_PARTNER, CanAIFaintTarget, GetBestDmgMovesFromBattler, GetMoveEffect, HasMoveWithEffect, HasUsableWhileAsleepMove, IncreaseSleepScore, IsPowerBasedOnStatus

void IncreaseSleepScore(enum BattlerId battlerAtk, enum BattlerId battlerDef, enum Move move, s32 *score)
{
    if (gAiLogicData->holdEffects[battlerDef] == HOLD_EFFECT_CURE_SLP || gAiLogicData->holdEffects[battlerDef] == HOLD_EFFECT_CURE_STATUS)
        return;

    if (((gAiThinkingStruct->aiFlags[battlerAtk] & AI_FLAG_TRY_TO_FAINT) && CanAIFaintTarget(battlerAtk, battlerDef, 0)))
    {
        enum Move bestMoves[MAX_MON_MOVES] = {MOVE_NONE};

        GetBestDmgMovesFromBattler(battlerAtk, battlerDef, AI_ATTACKING, bestMoves);

        for (u32 moveIndex = 0; moveIndex < MAX_MON_MOVES; moveIndex++)
        {
            if ((GetMoveEffect(bestMoves[moveIndex]) != EFFECT_FOCUS_PUNCH) && (bestMoves[moveIndex] != MOVE_NONE))
                return;
        }
    }

    if (AI_CanPutToSleep(battlerAtk, battlerDef, gAiLogicData->abilities[battlerDef], move, gAiLogicData->partnerMove))
        ADJUST_SCORE_PTR(DECENT_EFFECT);
    else
        return;

    if ((HasMoveWithEffect(battlerAtk, EFFECT_DREAM_EATER) || HasMoveWithEffect(battlerAtk, EFFECT_NIGHTMARE))
      && !HasUsableWhileAsleepMove(battlerDef))
        ADJUST_SCORE_PTR(WEAK_EFFECT);

    if (IsPowerBasedOnStatus(battlerAtk, EFFECT_DOUBLE_POWER_ON_ARG_STATUS, STATUS1_SLEEP)
      || IsPowerBasedOnStatus(BATTLE_PARTNER(battlerAtk), EFFECT_DOUBLE_POWER_ON_ARG_STATUS, STATUS1_SLEEP))
        ADJUST_SCORE_PTR(WEAK_EFFECT);
}
