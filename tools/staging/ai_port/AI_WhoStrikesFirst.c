// Extracted from RHH src/battle_ai_util.c:1450-1502
// 53 lines
// Dependencies: AI_WhoStrikesFirst, GetBattleMovePriority, GetBattlerTotalSpeedStat

s32 AI_WhoStrikesFirst(enum BattlerId battlerAI, enum BattlerId battler, enum Move aiMoveConsidered, enum Move playerMoveConsidered, enum ConsiderPriority considerPriority)
{
    u32 speedBattlerAI, speedBattler;
    enum HoldEffect holdEffectAI = gAiLogicData->holdEffects[battlerAI];
    enum HoldEffect holdEffectPlayer = gAiLogicData->holdEffects[battler];
    enum Ability abilityAI = gAiLogicData->abilities[battlerAI];
    enum Ability abilityPlayer = gAiLogicData->abilities[battler];

    if (considerPriority == CONSIDER_PRIORITY)
    {
        s8 aiPriority = GetBattleMovePriority(battlerAI, abilityAI, aiMoveConsidered);
        s8 playerPriority = GetBattleMovePriority(battler, abilityPlayer, playerMoveConsidered);

        if (aiPriority > playerPriority)
            return AI_IS_FASTER;
        else if (aiPriority < playerPriority)
            return AI_IS_SLOWER;
    }

    speedBattlerAI = GetBattlerTotalSpeedStat(battlerAI, abilityAI, holdEffectAI);
    speedBattler   = GetBattlerTotalSpeedStat(battler, abilityPlayer, holdEffectPlayer);

    if (holdEffectAI == HOLD_EFFECT_LAGGING_TAIL && holdEffectPlayer != HOLD_EFFECT_LAGGING_TAIL)
        return AI_IS_SLOWER;
    else if (holdEffectAI != HOLD_EFFECT_LAGGING_TAIL && holdEffectPlayer == HOLD_EFFECT_LAGGING_TAIL)
        return AI_IS_FASTER;

    if (abilityAI == ABILITY_STALL && abilityPlayer != ABILITY_STALL)
        return AI_IS_SLOWER;
    else if (abilityAI != ABILITY_STALL && abilityPlayer == ABILITY_STALL)
        return AI_IS_FASTER;

    if (speedBattlerAI > speedBattler)
    {
        if (gFieldStatuses & STATUS_FIELD_TRICK_ROOM)
            return AI_IS_SLOWER;
        else
            return AI_IS_FASTER;
    }
    else if (speedBattlerAI == speedBattler)
    {
        return AI_IS_FASTER;
    }
    else
    {
        if (gFieldStatuses & STATUS_FIELD_TRICK_ROOM)
            return AI_IS_FASTER;
        else
            return AI_IS_SLOWER;
    }

    return AI_IS_SLOWER;
}
