// Extracted from RHH src/battle_ai_util.c:2390-2461
// 72 lines
// Dependencies: AI_IsSlower, BATTLE_PARTNER, DoesAbilityRaiseStatsWhenLowered, GetBattlerSecondaryDamage, GetIncomingMoveSpeedCheck, HasMoveWithCategory, IncreaseStatDownScore, IsBattlerTrapped

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
