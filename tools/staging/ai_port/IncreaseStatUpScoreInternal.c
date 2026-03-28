// Extracted from RHH src/battle_ai_util.c:4825-4947
// 123 lines
// Dependencies: AI_IsFaster, GetBattlerParty, GetIncomingMoveSpeedCheck, GetMonData, GetMoveEffect, GetStagesOfStatChange, GetStatBeingChanged, HasMoveThatChangesKOThreshold, HasMoveWithCategory, HasMoveWithEffect, IncreaseStatUpScoreInternal, IsBattlerPredictedToSwitch, NoOfHitsForTargetToFaintBattler, ShouldRaiseAnyStat

static enum AIScore IncreaseStatUpScoreInternal(enum BattlerId battlerAtk, enum BattlerId battlerDef, enum StatChange statChange, bool32 considerContrary)
{
    enum AIScore tempScore = NO_INCREASE;
    u32 noOfHitsToFaint = NoOfHitsForTargetToFaintBattler(battlerDef, battlerAtk, DONT_CONSIDER_ENDURE);
    enum Move predictedMoveSpeedCheck = GetIncomingMoveSpeedCheck(battlerAtk, battlerDef, gAiLogicData);
    bool32 aiIsFaster = AI_IsFaster(battlerAtk, battlerDef, MOVE_NONE, predictedMoveSpeedCheck, DONT_CONSIDER_PRIORITY); // Don't care about the priority of our setup move, care about outspeeding otherwise
    bool32 shouldSetUp = ((noOfHitsToFaint >= 2 && aiIsFaster) || (noOfHitsToFaint >= 3 && !aiIsFaster) || noOfHitsToFaint == UNKNOWN_NO_OF_HITS);
    enum Stat statId = GetStatBeingChanged(statChange);
    u32 stages = GetStagesOfStatChange(statChange);

    if (considerContrary && gAiLogicData->abilities[battlerAtk] == ABILITY_CONTRARY)
        return NO_INCREASE;

    if (!ShouldRaiseAnyStat(battlerAtk, battlerDef))
        return NO_INCREASE;

    // Don't increase stat if AI is at +4
    if (gBattleMons[battlerAtk].statStages[statId] >= MAX_STAT_STAGE - 2)
        return NO_INCREASE;

    // Don't increase stat if AI has less then 70% HP and number of hits isn't known
    if (gAiLogicData->hpPercents[battlerAtk] < 70 && noOfHitsToFaint == UNKNOWN_NO_OF_HITS)
        return NO_INCREASE;

    // Don't increase stats if player has a move that can change the KO threshold
    if (HasMoveThatChangesKOThreshold(battlerDef, noOfHitsToFaint, aiIsFaster))
        return NO_INCREASE;

    // Stat stages are effectively doubled under Simple.
    if (gAiLogicData->abilities[battlerAtk] == ABILITY_SIMPLE)
        stages *= 2;

    // Predicting switch
    if (IsBattlerPredictedToSwitch(battlerDef))
    {
        struct Pokemon *playerParty = GetBattlerParty(battlerDef);
        // If expected switchin outspeeds and has Encore, don't increase
        for (u32 monIndex = 0; monIndex < MAX_MON_MOVES; monIndex++)
        {
            if (GetMoveEffect(GetMonData(&playerParty[gAiLogicData->mostSuitableMonId[battlerDef]], MON_DATA_MOVE1 + monIndex)) == EFFECT_ENCORE
                && GetMonData(&playerParty[gAiLogicData->mostSuitableMonId[battlerDef]], MON_DATA_PP1 + monIndex) > 0);
            {
                if (GetMonData(&playerParty[gAiLogicData->mostSuitableMonId[battlerDef]], MON_DATA_SPEED) > gBattleMons[battlerAtk].speed)
                    return NO_INCREASE;
            }
        }
        // Otherwise if predicting switch, stat increases are great momentum
        tempScore += WEAK_EFFECT;
    }

    switch (statId)
    {
    case STAT_ATK:
        if (HasMoveWithCategory(battlerAtk, DAMAGE_CATEGORY_PHYSICAL) && shouldSetUp)
        {
            if (stages == 1)
                tempScore += DECENT_EFFECT;
            else if (stages == 6)
                tempScore += BEST_EFFECT;
            else
                tempScore += GOOD_EFFECT;
        }
        break;
    case STAT_DEF:
        if (HasMoveWithCategory(battlerDef, DAMAGE_CATEGORY_PHYSICAL) || !HasMoveWithCategory(battlerDef, DAMAGE_CATEGORY_SPECIAL))
        {
            if (gAiThinkingStruct->aiFlags[battlerAtk] & AI_FLAG_STALL)
                tempScore += WEAK_EFFECT;
            if (stages == 1)
                tempScore += WEAK_EFFECT;
            else
                tempScore += DECENT_EFFECT;
        }
        break;
    case STAT_SPEED:
        if ((noOfHitsToFaint >= 3 && !aiIsFaster) || noOfHitsToFaint == UNKNOWN_NO_OF_HITS)
        {
            if (stages == 1)
                tempScore += DECENT_EFFECT;
            else
                tempScore += GOOD_EFFECT;
        }
        break;
    case STAT_SPATK:
        if (HasMoveWithCategory(battlerAtk, DAMAGE_CATEGORY_SPECIAL) && shouldSetUp)
        {
            if (stages == 1)
                tempScore += DECENT_EFFECT;
            else
                tempScore += GOOD_EFFECT;
        }
        break;
    case STAT_SPDEF:
        if (HasMoveWithCategory(battlerDef, DAMAGE_CATEGORY_SPECIAL) || !HasMoveWithCategory(battlerDef, DAMAGE_CATEGORY_PHYSICAL))
        {
            if (gAiThinkingStruct->aiFlags[battlerAtk] & AI_FLAG_STALL)
                tempScore += WEAK_EFFECT;
            if (stages == 1)
                tempScore += WEAK_EFFECT;
            else
                tempScore += DECENT_EFFECT;
        }
        break;
    case STAT_ACC:
        if (gBattleMons[battlerAtk].statStages[statId] <= DEFAULT_STAT_STAGE - 3) // Increase only if necessary
            tempScore += DECENT_EFFECT;
        break;
    case STAT_EVASION:
        if (noOfHitsToFaint > 3 || noOfHitsToFaint == UNKNOWN_NO_OF_HITS)
            tempScore += GOOD_EFFECT;
        else
            tempScore += DECENT_EFFECT;
        break;
    default:
        break;
    }

    // if already inclined to boost, be slightly more likely to if boost levels matter
    if (tempScore > 0 && HasMoveWithEffect(battlerAtk, EFFECT_STORED_POWER))
        tempScore += WEAK_EFFECT;

    return tempScore;
}
