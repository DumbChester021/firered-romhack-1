// Extracted from RHH src/battle_ai_main.c:5870-6224
// 355 lines
// Dependencies: AI_CalcAdditionalEffectScore, AI_GetBattlerMoveTargetType, AI_IsFaster, AI_ShouldCopyStatChanges, AI_ShouldSetUpHazards, AI_TryToClearStats, BATTLE_PARTNER, CanLowerStat, GetBattlerSide, GetBestDmgMovesFromBattler, GetIncomingMove, GetIncomingMoveSpeedCheck, GetItemPocket, GetMoveAdditionalEffectById, GetMoveAdditionalEffectCount, GetMoveEffect, GetMoveEffectArg_Status, HasMoveWithEffect, HasPartner, HasTwoOpponents, IncreasePoisonScore, IncreaseStatDownScore, IncreaseStatUpScore, IncreaseStatUpScoreContrary, IsAdditionalEffectBlocked, IsSheerForceAffected, IsSoundMove, IsSpreadMove, MoveEffectIsGuaranteed, ShouldClearFieldStatus, ShouldClearWeather, ShouldCureStatus, ShouldSetFieldStatus, ShouldSetScreen, ShouldSetWeather, ShouldTrap, ShouldTryToFlinch

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
