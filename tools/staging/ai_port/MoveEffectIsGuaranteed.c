// Extracted from RHH src/battle_util.c:9617-9620
// 4 lines
// Dependencies: CalcSecondaryEffectChance, MoveEffectIsGuaranteed

bool32 MoveEffectIsGuaranteed(enum BattlerId battler, enum Ability battlerAbility, const struct AdditionalEffect *additionalEffect)
{
    return additionalEffect->chance == 0 || CalcSecondaryEffectChance(battler, battlerAbility, additionalEffect) >= 100;
}
