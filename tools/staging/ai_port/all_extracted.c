// === RHH AI Scoring Functions — Extracted for Porting ===
// Functions: AI_CalcAdditionalEffectScore, MoveEffectIsGuaranteed, IncreaseStatUpScore, IncreaseStatUpScoreInternal, IncreaseStatUpScoreContrary, IncreaseStatDownScore, ShouldTryToFlinch, IncreasePoisonScore, IncreaseBurnScore, IncreaseParalyzeScore, IncreaseSleepScore, IncreaseConfusionScore
// Total extracted: 715 lines


// --- AI_CalcAdditionalEffectScore (src/battle_ai_main.c:5870-6224) ---
static s32 AI_CalcAdditionalEffectScore(enum BattlerId battlerAtk, enum BattlerId battlerDef, enum Move move, struct AiLogicData *aiData)
{
    // move data
    s32 score = 0;

    enum Move predictedMove = GetIncomingMove(battlerAtk, battlerDef, aiData);
    bool32 hasPartner = HasPartner(battlerAtk);
    u32 additionalEffectCount = GetMoveAdditionalEffectCount(move);
    enum Move defBestMoves[MAX_MON_MOVES] = {MOVE_NONE};

    // Set battlerDef best dmg moves
    GetBestDmgMovesFromBattler(battlerDef, battlerAtk, AI_DEFENDING, defBestMoves);

    if (IsSheerForceAffected(move, aiData->abilities[battlerAtk])
     && !(move == MOVE_ORDER_UP && gBattleStruct->battlerState[battlerAtk].commanderSpecies != SPECIES_NONE))
    {
        return score;
    }

    // check move additional effects that are likely to happen
    for (u32 effectId = 0; effectId < additionalEffectCount; effectId++)
    {
        const struct AdditionalEffect *additionalEffect = GetMoveAdditionalEffectById(move, effectId);

        // Only consider effects with a guaranteed chance to happen
        if (!MoveEffectIsGuaranteed(battlerAtk, aiData->abilities[battlerAtk], additionalEffect))
            continue;

        // Consider move effects that target self
        if (additionalEffect->self)
        {
            enum StatChange StageStatId;

            if (aiData->abilities[battlerAtk] != ABILITY_CONTRARY)
            {
                switch (additionalEffect->moveEffect)
                {
                case MOVE_EFFECT_ATK_PLUS_1:
                case MOVE_EFFECT_DEF_PLUS_1:
                case MOVE_EFFECT_SPD_PLUS_1:
                case MOVE_EFFECT_SP_ATK_PLUS_1:
                case MOVE_EFFECT_SP_DEF_PLUS_1:
                    StageStatId = STAT_CHANGE_ATK + additionalEffect->moveEffect - MOVE_EFFECT_ATK_PLUS_1;
                    ADJUST_SCORE(IncreaseStatUpScore(battlerAtk, battlerDef, StageStatId));
                    break;
                case MOVE_EFFECT_ATK_PLUS_2:
                case MOVE_EFFECT_DEF_PLUS_2:
                case MOVE_EFFECT_SPD_PLUS_2:
                case MOVE_EFFECT_SP_ATK_PLUS_2:
                case MOVE_EFFECT_SP_DEF_PLUS_2:
                    StageStatId = STAT_CHANGE_ATK_2 + additionalEffect->moveEffect - MOVE_EFFECT_ATK_PLUS_1;
                    ADJUST_SCORE(IncreaseStatUpScore(battlerAtk, battlerDef, StageStatId));
                    break;
                case MOVE_EFFECT_ACC_PLUS_1:
                case MOVE_EFFECT_ACC_PLUS_2:
                    ADJUST_SCORE(IncreaseStatUpScore(battlerAtk, battlerDef, STAT_CHANGE_ACC));
                    break;
                case MOVE_EFFECT_EVS_PLUS_1:
                case MOVE_EFFECT_EVS_PLUS_2:
                    ADJUST_SCORE(IncreaseStatUpScore(battlerAtk, battlerDef, STAT_CHANGE_EVASION));
                    break;
                default:
                    break;
                }
            }
            else
            {
                switch (additionalEffect->moveEffect)
                {
                case MOVE_EFFECT_ATK_MINUS_1:
                case MOVE_EFFECT_DEF_MINUS_1:
                case MOVE_EFFECT_SPD_MINUS_1:
                case MOVE_EFFECT_SP_ATK_MINUS_1:
                case MOVE_EFFECT_SP_DEF_MINUS_1:
                    StageStatId = STAT_CHANGE_ATK + additionalEffect->moveEffect - MOVE_EFFECT_ATK_MINUS_1;
                    ADJUST_SCORE(IncreaseStatUpScoreContrary(battlerAtk, battlerDef, StageStatId));
                    break;
                case MOVE_EFFECT_ATK_MINUS_2:
                case MOVE_EFFECT_DEF_MINUS_2:
                case MOVE_EFFECT_SPD_MINUS_2:
                case MOVE_EFFECT_SP_ATK_MINUS_2:
                case MOVE_EFFECT_SP_DEF_MINUS_2:
                    StageStatId = STAT_CHANGE_ATK + additionalEffect->moveEffect - MOVE_EFFECT_ATK_MINUS_2;
                    ADJUST_SCORE(IncreaseStatUpScoreContrary(battlerAtk, battlerDef, StageStatId));
                    break;
                case MOVE_EFFECT_ACC_MINUS_1:
                case MOVE_EFFECT_ACC_MINUS_2:
                    ADJUST_SCORE(IncreaseStatUpScoreContrary(battlerAtk, battlerDef, STAT_CHANGE_ACC));
                    break;
                case MOVE_EFFECT_EVS_MINUS_1:
                case MOVE_EFFECT_EVS_MINUS_2:
                    ADJUST_SCORE(IncreaseStatUpScoreContrary(battlerAtk, battlerDef, STAT_CHANGE_EVASION));
                    break;
                case MOVE_EFFECT_DEF_SPDEF_DOWN:
                    ADJUST_SCORE(IncreaseStatUpScoreContrary(battlerAtk, battlerDef, STAT_CHANGE_DEF));
                    ADJUST_SCORE(IncreaseStatUpScoreContrary(battlerAtk, battlerDef, STAT_CHANGE_SPDEF));
                    break;
                case MOVE_EFFECT_ATK_DEF_DOWN:
                    ADJUST_SCORE(IncreaseStatUpScoreContrary(battlerAtk, battlerDef, STAT_CHANGE_ATK));
                    ADJUST_SCORE(IncreaseStatUpScoreContrary(battlerAtk, battlerDef, STAT_CHANGE_DEF));
                    break;
                case MOVE_EFFECT_V_CREATE:
                    ADJUST_SCORE(IncreaseStatUpScoreContrary(battlerAtk, battlerDef, STAT_CHANGE_DEF));
                    ADJUST_SCORE(IncreaseStatUpScoreContrary(battlerAtk, battlerDef, STAT_CHANGE_SPEED));
                    ADJUST_SCORE(IncreaseStatUpScoreContrary(battlerAtk, battlerDef, STAT_CHANGE_SPDEF));
                    break;
                default:
                    break;
                }
            }
        }
        else // consider move effects that hinder the target
        {
            if (IsAdditionalEffectBlocked(battlerAtk, aiData->abilities[battlerAtk], battlerDef, aiData->abilities[battlerDef]))
                continue;

            switch (additionalEffect->moveEffect)
            {
            case MOVE_EFFECT_FLINCH:
                if (ShouldTryToFlinch(battlerAtk, battlerDef, aiData->abilities[battlerAtk], aiData->abilities[battlerDef], move))
                    score += 2;
                break;
            case MOVE_EFFECT_SPD_MINUS_1:
            case MOVE_EFFECT_SPD_MINUS_2:
                if (CanLowerStat(battlerAtk, battlerDef, aiData, STAT_SPEED))
                    ADJUST_SCORE(IncreaseStatDownScore(battlerAtk, battlerDef, STAT_SPEED));
                break;
            case MOVE_EFFECT_ACC_MINUS_1:
            case MOVE_EFFECT_ACC_MINUS_2:
                if (CanLowerStat(battlerAtk, battlerDef, aiData, STAT_ACC))
                {
                    u32 scoreIncrease = IncreaseStatDownScore(battlerAtk, battlerDef, STAT_ACC);
                    if (scoreIncrease == WEAK_EFFECT)
                        scoreIncrease = DECENT_EFFECT;
                    ADJUST_SCORE(scoreIncrease);
                }
                break;
            case MOVE_EFFECT_ATK_MINUS_1:
            case MOVE_EFFECT_DEF_MINUS_1:
            case MOVE_EFFECT_SP_ATK_MINUS_1:
            case MOVE_EFFECT_SP_DEF_MINUS_1:
            case MOVE_EFFECT_EVS_MINUS_1:
            {
                enum Stat statId = STAT_ATK + additionalEffect->moveEffect - MOVE_EFFECT_ATK_MINUS_1;
                if (CanLowerStat(battlerAtk, battlerDef, aiData, statId))
                    ADJUST_SCORE(IncreaseStatDownScore(battlerAtk, battlerDef, statId));
                break;
            }
            case MOVE_EFFECT_ATK_MINUS_2:
            case MOVE_EFFECT_DEF_MINUS_2:
            case MOVE_EFFECT_SP_ATK_MINUS_2:
            case MOVE_EFFECT_SP_DEF_MINUS_2:
            case MOVE_EFFECT_EVS_MINUS_2:
            {
                enum Stat statId = STAT_ATK + additionalEffect->moveEffect - MOVE_EFFECT_ATK_MINUS_2;
                if (CanLowerStat(battlerAtk, battlerDef, aiData, statId))
                    ADJUST_SCORE(IncreaseStatDownScore(battlerAtk, battlerDef, statId));
                break;
            }
            case MOVE_EFFECT_RAISE_TEAM_ATTACK:
            case MOVE_EFFECT_RAISE_TEAM_DEFENSE:
            case MOVE_EFFECT_RAISE_TEAM_SPEED:
            case MOVE_EFFECT_RAISE_TEAM_SP_ATK:
            case MOVE_EFFECT_RAISE_TEAM_SP_DEF:
            {
                enum StatChange StageStatId = STAT_CHANGE_ATK + additionalEffect->moveEffect - MOVE_EFFECT_RAISE_TEAM_ATTACK;
                ADJUST_SCORE(IncreaseStatUpScore(battlerAtk, battlerDef, StageStatId));
                if (hasPartner)
                    ADJUST_SCORE(IncreaseStatUpScore(BATTLE_PARTNER(battlerAtk), battlerDef, StageStatId));
                break;
            }
            case MOVE_EFFECT_LOWER_ATTACK_SIDE:
            case MOVE_EFFECT_LOWER_DEFENSE_SIDE:
            case MOVE_EFFECT_LOWER_SPEED_SIDE:
            case MOVE_EFFECT_LOWER_SP_ATK_SIDE:
            case MOVE_EFFECT_LOWER_SP_DEF_SIDE:
            {
                enum Stat statId = STAT_ATK + additionalEffect->moveEffect - MOVE_EFFECT_LOWER_ATTACK_SIDE;
                if (CanLowerStat(battlerAtk, battlerDef, aiData, statId))
                    ADJUST_SCORE(IncreaseStatDownScore(battlerAtk, battlerDef, statId));
                break;
            }
            case MOVE_EFFECT_POISON:
                IncreasePoisonScore(battlerAtk, battlerDef, move, &score);
                break;
            case MOVE_EFFECT_CLEAR_SMOG:
            {
                enum MoveTarget target = AI_GetBattlerMoveTargetType(battlerAtk, move);
                bool32 moveTargetsBothOpponents = HasTwoOpponents(battlerAtk)
                                               && (target == TARGET_FIELD || target == TARGET_ALL_BATTLERS || IsSpreadMove(target));

                score += AI_TryToClearStats(battlerAtk, battlerDef, moveTargetsBothOpponents);
                break;
            }
            case MOVE_EFFECT_BUG_BITE:   // And pluck
                if (gBattleMons[battlerDef].volatiles.substitute || aiData->abilities[battlerDef] == ABILITY_STICKY_HOLD)
                    break;
                else if (GetItemPocket(aiData->items[battlerDef]) == POCKET_BERRIES)
                    ADJUST_SCORE(DECENT_EFFECT);
                break;
            case MOVE_EFFECT_INCINERATE:
                if (gBattleMons[battlerDef].volatiles.substitute || aiData->abilities[battlerDef] == ABILITY_STICKY_HOLD)
                    break;
                else if (GetItemPocket(aiData->items[battlerDef]) == POCKET_BERRIES || aiData->holdEffects[battlerDef] == HOLD_EFFECT_GEMS)
                    ADJUST_SCORE(DECENT_EFFECT);
                break;
            case MOVE_EFFECT_STEALTH_ROCK:
                if (AI_ShouldSetUpHazards(battlerAtk, battlerDef, move, aiData))
                {
                    if (gBattleStruct->battlerState[battlerAtk].isFirstTurn)
                        ADJUST_SCORE(BEST_EFFECT);
                    else
                        ADJUST_SCORE(DECENT_EFFECT);
                }
                break;
            case MOVE_EFFECT_FEINT:
                if (GetMoveEffect(predictedMove) == EFFECT_PROTECT)
                    ADJUST_SCORE(GOOD_EFFECT);
                break;
            case MOVE_EFFECT_THROAT_CHOP:
                for (u32 moveIndex = 0; moveIndex < MAX_MON_MOVES; moveIndex++)
                {
                    if (defBestMoves[moveIndex] == MOVE_NONE)
                    {
                        break;
                    }
                    else
                    {
                        if (IsSoundMove(defBestMoves[moveIndex]))
                        {
                            enum Move predictedMoveSpeedCheck = GetIncomingMoveSpeedCheck(battlerAtk, battlerDef, aiData);

                            if (AI_IsFaster(battlerAtk, battlerDef, move, predictedMoveSpeedCheck, CONSIDER_PRIORITY))
                            {
                                ADJUST_SCORE(GOOD_EFFECT);
                                break;
                            }
                            else
                            {
                                ADJUST_SCORE(DECENT_EFFECT);
                                break;
                            }
                        }
                    }
                }
                break;
            case MOVE_EFFECT_WRAP:
                if (!HasMoveWithEffect(battlerDef, EFFECT_RAPID_SPIN) && ShouldTrap(battlerAtk, battlerDef, move))
                    ADJUST_SCORE(BEST_EFFECT);
                break;
            case MOVE_EFFECT_SALT_CURE:
                if (IS_BATTLER_OF_TYPE(battlerDef, TYPE_WATER) || IS_BATTLER_OF_TYPE(battlerDef, TYPE_STEEL))
                    ADJUST_SCORE(DECENT_EFFECT);
                break;
            case MOVE_EFFECT_SUN:
                if (ShouldSetWeather(battlerAtk, B_WEATHER_SUN))
                    ADJUST_SCORE(DECENT_EFFECT);
                if (ShouldClearWeather(battlerAtk, B_WEATHER_SUN))
                    ADJUST_SCORE(BAD_EFFECT);
                break;
            case MOVE_EFFECT_RAIN:
                if (ShouldSetWeather(battlerAtk, B_WEATHER_RAIN))
                    ADJUST_SCORE(DECENT_EFFECT);
                if (ShouldClearWeather(battlerAtk, B_WEATHER_RAIN))
                    ADJUST_SCORE(BAD_EFFECT);
                break;
            case MOVE_EFFECT_SANDSTORM:
                if (ShouldSetWeather(battlerAtk, B_WEATHER_SANDSTORM))
                    ADJUST_SCORE(DECENT_EFFECT);
                if (ShouldClearWeather(battlerAtk, B_WEATHER_SANDSTORM))
                    ADJUST_SCORE(BAD_EFFECT);
                break;
            case MOVE_EFFECT_HAIL:
                if (ShouldSetWeather(battlerAtk, B_WEATHER_HAIL))
                    ADJUST_SCORE(DECENT_EFFECT);
                if (ShouldClearWeather(battlerAtk, B_WEATHER_HAIL))
                    ADJUST_SCORE(BAD_EFFECT);
                break;
            case MOVE_EFFECT_MISTY_TERRAIN:
                if (ShouldClearFieldStatus(battlerAtk, STATUS_FIELD_MISTY_TERRAIN))
                {
                    ADJUST_SCORE(BAD_EFFECT);
                    break;
                }
                if (ShouldSetFieldStatus(battlerAtk, STATUS_FIELD_MISTY_TERRAIN)
                 || ShouldClearFieldStatus(battlerAtk, gFieldStatuses & STATUS_FIELD_TERRAIN_ANY))
                    ADJUST_SCORE(DECENT_EFFECT);
                break;
            case MOVE_EFFECT_GRASSY_TERRAIN:
                if (ShouldClearFieldStatus(battlerAtk, STATUS_FIELD_GRASSY_TERRAIN))
                {
                    ADJUST_SCORE(BAD_EFFECT);
                    break;
                }
                if (ShouldSetFieldStatus(battlerAtk, STATUS_FIELD_GRASSY_TERRAIN)
                 || ShouldClearFieldStatus(battlerAtk, gFieldStatuses & STATUS_FIELD_TERRAIN_ANY))
                    ADJUST_SCORE(DECENT_EFFECT);
                break;
            case MOVE_EFFECT_ELECTRIC_TERRAIN:
                if (ShouldClearFieldStatus(battlerAtk, STATUS_FIELD_ELECTRIC_TERRAIN))
                {
                    ADJUST_SCORE(BAD_EFFECT);
                    break;
                }
                if (ShouldSetFieldStatus(battlerAtk, STATUS_FIELD_ELECTRIC_TERRAIN)
                 || ShouldClearFieldStatus(battlerAtk, gFieldStatuses & STATUS_FIELD_TERRAIN_ANY))
                    ADJUST_SCORE(DECENT_EFFECT);
                break;
            case MOVE_EFFECT_PSYCHIC_TERRAIN:
                if (ShouldClearFieldStatus(battlerAtk, STATUS_FIELD_PSYCHIC_TERRAIN))
                {
                    ADJUST_SCORE(BAD_EFFECT);
                    break;
                }
                if (ShouldSetFieldStatus(battlerAtk, STATUS_FIELD_PSYCHIC_TERRAIN)
                 || ShouldClearFieldStatus(battlerAtk, gFieldStatuses & STATUS_FIELD_TERRAIN_ANY))
                    ADJUST_SCORE(DECENT_EFFECT);
                break;
            case MOVE_EFFECT_GRAVITY:
                if (!(gFieldStatuses & STATUS_FIELD_GRAVITY) && ShouldSetFieldStatus(battlerAtk, STATUS_FIELD_GRAVITY))
                    ADJUST_SCORE(DECENT_EFFECT);
                break;
            case MOVE_EFFECT_AURORA_VEIL:
                if (ShouldSetScreen(battlerAtk, battlerDef, EFFECT_AURORA_VEIL))
                    ADJUST_SCORE(DECENT_EFFECT);
                break;
            case MOVE_EFFECT_REMOVE_STATUS:
                if (gBattleMons[battlerDef].status1 & GetMoveEffectArg_Status(move))
                {
                    if (ShouldCureStatus(battlerAtk, battlerDef, aiData))
                        ADJUST_SCORE(DECENT_EFFECT);
                    else if (aiData->holdEffects[battlerDef] == HOLD_EFFECT_FLAME_ORB || aiData->holdEffects[battlerDef] == HOLD_EFFECT_TOXIC_ORB)
                        ADJUST_SCORE(WEAK_EFFECT);
                    else
                        ADJUST_SCORE(BAD_EFFECT);
                }
                break;
            case MOVE_EFFECT_BREAK_SCREEN:
                if (gSideStatuses[GetBattlerSide(battlerDef)] & SIDE_STATUS_REFLECT)
                    ADJUST_SCORE(DECENT_EFFECT);
                if (gSideStatuses[GetBattlerSide(battlerDef)] & SIDE_STATUS_LIGHTSCREEN)
                    ADJUST_SCORE(DECENT_EFFECT);
                if (gSideStatuses[GetBattlerSide(battlerDef)] & SIDE_STATUS_AURORA_VEIL)
                    ADJUST_SCORE(DECENT_EFFECT);
                break;
            case MOVE_EFFECT_STEAL_STATS:
                ADJUST_SCORE(AI_ShouldCopyStatChanges(battlerAtk, battlerDef));
                break;
            default:
                break;
            }
        }
    }
    return score;
}

// --- MoveEffectIsGuaranteed (src/battle_util.c:9617-9620) ---
bool32 MoveEffectIsGuaranteed(enum BattlerId battler, enum Ability battlerAbility, const struct AdditionalEffect *additionalEffect)
{
    return additionalEffect->chance == 0 || CalcSecondaryEffectChance(battler, battlerAbility, additionalEffect) >= 100;
}

// --- IncreaseStatUpScore (src/battle_ai_util.c:4970-4973) ---
enum AIScore IncreaseStatUpScore(enum BattlerId battlerAtk, enum BattlerId battlerDef, enum StatChange statChange)
{
    return IncreaseStatUpScoreInternal(battlerAtk, battlerDef, statChange, TRUE);
}

// --- IncreaseStatUpScoreInternal (src/battle_ai_util.c:4825-4947) ---
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

// --- IncreaseStatUpScoreContrary (src/battle_ai_util.c:4975-4978) ---
enum AIScore IncreaseStatUpScoreContrary(enum BattlerId battlerAtk, enum BattlerId battlerDef, enum StatChange statChange)
{
    return IncreaseStatUpScoreInternal(battlerAtk, battlerDef, statChange, FALSE);
}

// --- IncreaseStatDownScore (src/battle_ai_util.c:2390-2461) ---
enum AIScore IncreaseStatDownScore(enum BattlerId battlerAtk, enum BattlerId battlerDef, enum Stat stat)
{
    enum AIScore tempScore = NO_INCREASE;

    // Don't increase score if target is already -3 stat stage
    if (stat != STAT_SPEED && gBattleMons[battlerDef].statStages[stat] <= DEFAULT_STAT_STAGE - 3)
        return NO_INCREASE;

    // Don't decrease stat if target will die to residual damage
    if (GetBattlerSecondaryDamage(battlerDef) >= gBattleMons[battlerDef].hp)
        return NO_INCREASE;

    if (DoesAbilityRaiseStatsWhenLowered(gAiLogicData->abilities[battlerDef]))
        return NO_INCREASE;

    // TODO: Avoid decreasing stat if
    // player can kill ai in 2 hits with decreased attack / sp atk stages
    // ai can kill target in 2 hits without decreasing defense / sp def stages

    switch (stat)
    {
    case STAT_ATK:
        if (HasMoveWithCategory(battlerDef, DAMAGE_CATEGORY_PHYSICAL))
            tempScore += DECENT_EFFECT;
        break;
    case STAT_DEF:
        if (HasMoveWithCategory(battlerAtk, DAMAGE_CATEGORY_PHYSICAL)
         || HasMoveWithCategory(BATTLE_PARTNER(battlerAtk), DAMAGE_CATEGORY_PHYSICAL))
            tempScore += DECENT_EFFECT;
        break;
    case STAT_SPEED:
    {
        enum Move predictedMoveSpeedCheck = GetIncomingMoveSpeedCheck(battlerAtk, battlerDef, gAiLogicData);
        if (AI_IsSlower(battlerAtk, battlerDef, MOVE_NONE, predictedMoveSpeedCheck, DONT_CONSIDER_PRIORITY)
        || AI_IsSlower(BATTLE_PARTNER(battlerAtk), battlerDef, MOVE_NONE, predictedMoveSpeedCheck, DONT_CONSIDER_PRIORITY))
            tempScore += DECENT_EFFECT;
        break;
    }
    case STAT_SPATK:
        if (HasMoveWithCategory(battlerDef, DAMAGE_CATEGORY_SPECIAL))
            tempScore += DECENT_EFFECT;
        break;
    case STAT_SPDEF:
        if (HasMoveWithCategory(battlerAtk, DAMAGE_CATEGORY_SPECIAL)
         || HasMoveWithCategory(BATTLE_PARTNER(battlerAtk), DAMAGE_CATEGORY_SPECIAL))
            tempScore += DECENT_EFFECT;
        break;
    case STAT_ACC:
        tempScore += WEAK_EFFECT;
        if (IsBattlerTrapped(battlerAtk, battlerDef))
            tempScore += DECENT_EFFECT;
        if (gBattleMons[battlerDef].volatiles.leechSeed)
            tempScore += WEAK_EFFECT;
        if (gBattleMons[battlerDef].volatiles.cursed)
            tempScore += WEAK_EFFECT;
        break;
    case STAT_EVASION:
        if (gBattleMons[battlerDef].status1 & STATUS1_PSN_ANY)
            tempScore += WEAK_EFFECT;
        if (gBattleMons[battlerDef].volatiles.leechSeed)
            tempScore += WEAK_EFFECT;
        if (gBattleMons[battlerDef].volatiles.root)
            tempScore += WEAK_EFFECT;
        if (gBattleMons[battlerDef].volatiles.cursed)
            tempScore += WEAK_EFFECT;
        break;
    default:
        break;
    }

    return (tempScore > BEST_EFFECT) ? BEST_EFFECT : tempScore; // don't inflate score so only max +4
}

// --- ShouldTryToFlinch (src/battle_ai_util.c:3754-3774) ---
bool32 ShouldTryToFlinch(enum BattlerId battlerAtk, enum BattlerId battlerDef, enum Ability atkAbility, enum Ability defAbility, enum Move move)
{
    enum Move predictedMoveSpeedCheck = GetIncomingMoveSpeedCheck(battlerAtk, battlerDef, gAiLogicData);
    if (((!IsMoldBreakerTypeAbility(battlerAtk, gAiLogicData->abilities[battlerAtk]) && (defAbility == ABILITY_SHIELD_DUST || defAbility == ABILITY_INNER_FOCUS))
      || gAiLogicData->holdEffects[battlerDef] == HOLD_EFFECT_COVERT_CLOAK
      || DoesSubstituteBlockMove(battlerAtk, battlerDef, move)
      || AI_IsSlower(battlerAtk, battlerDef, move, predictedMoveSpeedCheck, CONSIDER_PRIORITY))) // Opponent goes first
    {
        return FALSE;
    }
    else if ((atkAbility == ABILITY_SERENE_GRACE
      || gBattleMons[battlerDef].status1 & STATUS1_PARALYSIS
      || gBattleMons[battlerDef].volatiles.infatuation
      || gBattleMons[battlerDef].volatiles.confusionTurns > 0)
      || ((AI_IsFaster(battlerAtk, battlerDef, move, predictedMoveSpeedCheck, CONSIDER_PRIORITY)) && CanTargetFaintAi(battlerDef, battlerAtk)))
    {
        return TRUE;   // good idea to flinch
    }

    return FALSE;   // don't try to flinch
}

// --- IncreasePoisonScore (src/battle_ai_util.c:4980-5001) ---
void IncreasePoisonScore(enum BattlerId battlerAtk, enum BattlerId battlerDef, enum Move move, s32 *score)
{
    if (((gAiThinkingStruct->aiFlags[battlerAtk] & AI_FLAG_TRY_TO_FAINT) && CanAIFaintTarget(battlerAtk, battlerDef, 0))
            || gAiLogicData->holdEffects[battlerDef] == HOLD_EFFECT_CURE_PSN || gAiLogicData->holdEffects[battlerDef] == HOLD_EFFECT_CURE_STATUS)
        return;

    if (AI_CanPoison(battlerAtk, battlerDef, gAiLogicData->abilities[battlerDef], move, gAiLogicData->partnerMove) && gAiLogicData->hpPercents[battlerDef] > 20)
    {
        if (!HasDamagingMove(battlerDef))
            ADJUST_SCORE_PTR(DECENT_EFFECT);

        if (gAiThinkingStruct->aiFlags[battlerAtk] & AI_FLAG_STALL && HasMoveWithEffect(battlerAtk, EFFECT_PROTECT))
            ADJUST_SCORE_PTR(WEAK_EFFECT);    // stall tactic

        if (IsPowerBasedOnStatus(battlerAtk, EFFECT_DOUBLE_POWER_ON_ARG_STATUS, STATUS1_PSN_ANY)
         || HasMoveWithEffect(battlerAtk, EFFECT_VENOM_DRENCH)
         || gAiLogicData->abilities[battlerAtk] == ABILITY_MERCILESS)
            ADJUST_SCORE_PTR(DECENT_EFFECT);
        else
            ADJUST_SCORE_PTR(WEAK_EFFECT);
    }
}

// --- IncreaseBurnScore (src/battle_ai_util.c:5003-5042) ---
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

// --- IncreaseParalyzeScore (src/battle_ai_util.c:5044-5064) ---
void IncreaseParalyzeScore(enum BattlerId battlerAtk, enum BattlerId battlerDef, enum Move move, s32 *score)
{
    if (((gAiThinkingStruct->aiFlags[battlerAtk] & AI_FLAG_TRY_TO_FAINT) && CanAIFaintTarget(battlerAtk, battlerDef, 0))
            || gAiLogicData->holdEffects[battlerDef] == HOLD_EFFECT_CURE_PAR || gAiLogicData->holdEffects[battlerDef] == HOLD_EFFECT_CURE_STATUS)
        return;

    if (AI_CanParalyze(battlerAtk, battlerDef, gAiLogicData->abilities[battlerDef], move, gAiLogicData->partnerMove))
    {
        u32 atkSpeed = gAiLogicData->speedStats[battlerAtk];
        u32 defSpeed = gAiLogicData->speedStats[battlerDef];

        if ((defSpeed >= atkSpeed && defSpeed / 2 < atkSpeed) // You'll go first after paralyzing foe
          || IsPowerBasedOnStatus(battlerAtk, EFFECT_DOUBLE_POWER_ON_ARG_STATUS, STATUS1_PARALYSIS)
          || (HasMoveWithMoveEffectExcept(battlerAtk, MOVE_EFFECT_FLINCH, EFFECT_FIRST_TURN_ONLY)) // filter out Fake Out
          || gBattleMons[battlerDef].volatiles.infatuation
          || gBattleMons[battlerDef].volatiles.confusionTurns > 0)
            ADJUST_SCORE_PTR(GOOD_EFFECT);
        else
            ADJUST_SCORE_PTR(DECENT_EFFECT);
    }
}

// --- IncreaseSleepScore (src/battle_ai_util.c:5066-5096) ---
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

// --- IncreaseConfusionScore (src/battle_ai_util.c:5098-5115) ---
void IncreaseConfusionScore(enum BattlerId battlerAtk, enum BattlerId battlerDef, enum Move move, s32 *score)
{
    if (((gAiThinkingStruct->aiFlags[battlerAtk] & AI_FLAG_TRY_TO_FAINT) && CanAIFaintTarget(battlerAtk, battlerDef, 0))
            || gAiLogicData->holdEffects[battlerDef] == HOLD_EFFECT_CURE_CONFUSION || gAiLogicData->holdEffects[battlerDef] == HOLD_EFFECT_CURE_STATUS)
        return;

    if (AI_CanConfuse(battlerAtk, battlerDef, gAiLogicData->abilities[battlerDef], BATTLE_PARTNER(battlerAtk), move, gAiLogicData->partnerMove)
      && gAiLogicData->holdEffects[battlerDef] != HOLD_EFFECT_CURE_CONFUSION
      && gAiLogicData->holdEffects[battlerDef] != HOLD_EFFECT_CURE_STATUS)
    {
        if (gBattleMons[battlerDef].status1 & STATUS1_PARALYSIS
          || gBattleMons[battlerDef].volatiles.infatuation
          || (gAiLogicData->abilities[battlerAtk] == ABILITY_SERENE_GRACE && HasMoveWithMoveEffectExcept(battlerAtk, MOVE_EFFECT_FLINCH, EFFECT_FIRST_TURN_ONLY)))
            ADJUST_SCORE_PTR(GOOD_EFFECT);
        else
            ADJUST_SCORE_PTR(DECENT_EFFECT);
    }
}
