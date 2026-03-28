// Extracted from RHH src/battle_ai_util.c:727-736
// 10 lines
// Dependencies: IsAdditionalEffectBlocked, IsMoldBreakerTypeAbility

bool32 IsAdditionalEffectBlocked(enum BattlerId battlerAtk, u32 abilityAtk, enum BattlerId battlerDef, enum Ability abilityDef)
{
    if (gAiLogicData->holdEffects[battlerDef] == HOLD_EFFECT_COVERT_CLOAK)
        return TRUE;

    if (abilityDef == ABILITY_SHIELD_DUST && !IsMoldBreakerTypeAbility(battlerAtk, abilityAtk))
        return TRUE;

    return FALSE;
}
