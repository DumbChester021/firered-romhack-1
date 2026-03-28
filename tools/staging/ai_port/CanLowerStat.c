// Extracted from RHH src/battle_ai_util.c:2327-2388
// 62 lines
// Dependencies: AI_IsAbilityOnSide, AI_IsFaster, CanLowerStat, CountUsablePartyMons, DoesBattlerIgnoreAbilityChecks, GetActiveGimmick, GetBattlerSide, GetConfig, GetIncomingMoveSpeedCheck, HasBattlerSideMoveWithEffect, IsBattleMoveStatus

bool32 CanLowerStat(enum BattlerId battlerAtk, enum BattlerId battlerDef, struct AiLogicData *aiData, enum Stat stat)
{
    if (gBattleMons[battlerDef].statStages[stat] == MIN_STAT_STAGE)
        return FALSE;

    if (aiData->holdEffects[battlerDef] == HOLD_EFFECT_CLEAR_AMULET)
        return FALSE;

    enum Move move = gAiThinkingStruct->moveConsidered;
    enum Ability abilityAtk = aiData->abilities[battlerAtk];

    if (gSideStatuses[GetBattlerSide(battlerDef)] & SIDE_STATUS_MIST && abilityAtk != ABILITY_INFILTRATOR)
        return FALSE;

    if (!DoesBattlerIgnoreAbilityChecks(battlerAtk, abilityAtk, move))
    {
        if (IS_BATTLER_OF_TYPE(battlerDef, TYPE_GRASS) && AI_IsAbilityOnSide(battlerDef, ABILITY_FLOWER_VEIL))
            return FALSE;

        switch (aiData->abilities[battlerDef])
        {
        case ABILITY_SPEED_BOOST:
            if (stat == STAT_SPEED)
                return FALSE;
        case ABILITY_HYPER_CUTTER:
            if (stat == STAT_ATK)
                return FALSE;
        case ABILITY_BIG_PECKS:
            if (stat == STAT_DEF)
                return FALSE;
        case ABILITY_ILLUMINATE:
            if (GetConfig(B_ILLUMINATE_EFFECT) < GEN_9)
                break;
        case ABILITY_KEEN_EYE:
        case ABILITY_MINDS_EYE:
            if (stat == STAT_ACC)
                return FALSE;
        case ABILITY_CONTRARY:
        case ABILITY_CLEAR_BODY:
        case ABILITY_WHITE_SMOKE:
        case ABILITY_FULL_METAL_BODY:
            return FALSE;
        case ABILITY_SHIELD_DUST:
            if (!IsBattleMoveStatus(move) && GetActiveGimmick(battlerAtk) != GIMMICK_DYNAMAX)
                return FALSE;
            break;
        default:
            break;
        }
    }

    if (stat == STAT_SPEED)
    {
        enum Move predictedMoveSpeedCheck = GetIncomingMoveSpeedCheck(battlerAtk, battlerDef, gAiLogicData);
        // If AI is faster and doesn't have any mons left, lowering speed doesn't give any
        return !(AI_IsFaster(battlerAtk, battlerDef, move, predictedMoveSpeedCheck, DONT_CONSIDER_PRIORITY)
            && CountUsablePartyMons(battlerAtk) == 0
            && !HasBattlerSideMoveWithEffect(battlerAtk, EFFECT_ELECTRO_BALL));
    }

    return TRUE;
}
