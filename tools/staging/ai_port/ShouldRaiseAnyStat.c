// Extracted from RHH src/battle_ai_util.c:2192-2227
// 36 lines
// Dependencies: AI_IsAbilityOnSide, AreBattlersStatsMaxed, CanBattlerKOTargetIgnoringSturdy, CanBeSlept, CountPositiveStatStages, GetBattlerSecondaryDamage, HasBattlerSideMoveWithAIEffect, HasBattlerSideUsedMoveWithEffect, RandomPercentage, ShouldRaiseAnyStat

bool32 ShouldRaiseAnyStat(enum BattlerId battlerAtk, enum BattlerId battlerDef)
{
    if (AreBattlersStatsMaxed(battlerAtk))
        return FALSE;

    // Don't increase stats if opposing battler has Unaware
    if (AI_IsAbilityOnSide(battlerDef, ABILITY_UNAWARE))
        return FALSE;

    // Don't increase stats if Yawn'd
    if (gBattleMons[battlerAtk].volatiles.yawn && CanBeSlept(battlerDef, battlerDef, gAiLogicData->abilities[battlerDef], BLOCKED_BY_SLEEP_CLAUSE))
        return FALSE;

    // Don't set up if AI is dead to residual damage from weather
    if (GetBattlerSecondaryDamage(battlerAtk) >= gBattleMons[battlerAtk].hp)
        return FALSE;

    // Don't increase stats if opposing battler has Opportunist
    if (AI_IsAbilityOnSide(battlerDef, ABILITY_OPPORTUNIST))
        return FALSE;

    // Don't increase stats if opposing battler has used Haze effect or AI effect
    if (!RandomPercentage(RNG_AI_BOOST_INTO_HAZE, BOOST_INTO_HAZE_CHANCE)
      && HasBattlerSideUsedMoveWithEffect(battlerDef, EFFECT_HAZE))
        return FALSE;

    if (CountPositiveStatStages(battlerAtk) > 0
      && HasBattlerSideMoveWithAIEffect(battlerDef, AI_EFFECT_RESET_STATS))
        return FALSE;

    // Don't increase stats if AI could KO target through Sturdy effect, as otherwise it always 2HKOs
    if (CanBattlerKOTargetIgnoringSturdy(battlerAtk, battlerDef))
        return FALSE;

    return TRUE;
}
