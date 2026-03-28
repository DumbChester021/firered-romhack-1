// Extracted from RHH src/battle_ai_util.c:5003-5042
// 40 lines
// Dependencies: ADJUST_SCORE_PTR, AI_CanBurn, BATTLE_PARTNER, CanAIFaintTarget, GetBestDmgMovesFromBattler, GetMoveCategory, GetSpeciesBaseAttack, GetSpeciesBaseSpAttack, HasMoveWithCategory, IncreaseBurnScore, IsPowerBasedOnStatus

void IncreaseBurnScore(enum BattlerId battlerAtk, enum BattlerId battlerDef, enum Move move, s32 *score)
{
    if (((gAiThinkingStruct->aiFlags[battlerAtk] & AI_FLAG_TRY_TO_FAINT) && CanAIFaintTarget(battlerAtk, battlerDef, 0))
            || gAiLogicData->holdEffects[battlerDef] == HOLD_EFFECT_CURE_BRN || gAiLogicData->holdEffects[battlerDef] == HOLD_EFFECT_CURE_STATUS)
        return;

    if (AI_CanBurn(battlerAtk, battlerDef, gAiLogicData->abilities[battlerDef], BATTLE_PARTNER(battlerAtk), move, gAiLogicData->partnerMove))
    {
        if (HasMoveWithCategory(battlerDef, DAMAGE_CATEGORY_PHYSICAL)
            || (!(gAiThinkingStruct->aiFlags[battlerAtk] & AI_FLAG_OMNISCIENT) // Not Omniscient but expects physical attacker
                && GetSpeciesBaseAttack(gBattleMons[battlerDef].species) >= GetSpeciesBaseSpAttack(gBattleMons[battlerDef].species) + 10))
        {
            enum Move defBestMoves[MAX_MON_MOVES] = {MOVE_NONE};
            bool32 hasPhysical = FALSE;

            GetBestDmgMovesFromBattler(battlerAtk, battlerDef, AI_DEFENDING, defBestMoves);

            for (u32 moveIndex = 0; moveIndex < MAX_MON_MOVES; moveIndex++)
            {
                if (defBestMoves[moveIndex] == MOVE_NONE)
                    break;

                if (GetMoveCategory(defBestMoves[moveIndex]) == DAMAGE_CATEGORY_PHYSICAL)
                {
                    hasPhysical = TRUE;
                    break;
                }
            }

            if (hasPhysical)
                ADJUST_SCORE_PTR(DECENT_EFFECT);
            else
                ADJUST_SCORE_PTR(WEAK_EFFECT);
        }

        if (IsPowerBasedOnStatus(battlerAtk, EFFECT_DOUBLE_POWER_ON_ARG_STATUS, STATUS1_BURN)
          || IsPowerBasedOnStatus(BATTLE_PARTNER(battlerAtk), EFFECT_DOUBLE_POWER_ON_ARG_STATUS, STATUS1_BURN))
            ADJUST_SCORE_PTR(WEAK_EFFECT);
    }
}
