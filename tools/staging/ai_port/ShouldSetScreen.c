// Extracted from RHH src/battle_ai_util.c:4011-4044
// 34 lines
// Dependencies: AI_GetWeather, GetBattlerSide, HasMoveWithAIEffect, HasMoveWithCategory, ShouldSetScreen

bool32 ShouldSetScreen(enum BattlerId battlerAtk, enum BattlerId battlerDef, enum BattleMoveEffects moveEffect)
{
    enum BattleSide atkSide = GetBattlerSide(battlerAtk);

    // Don't waste a turn if screens will be broken
    if (HasMoveWithAIEffect(battlerDef, AI_EFFECT_BREAK_SCREENS))
        return FALSE;

    switch (moveEffect)
    {
    case EFFECT_AURORA_VEIL:
        // Use only in Hail and only if AI doesn't already have Reflect, Light Screen or Aurora Veil itself active.
        if ((AI_GetWeather() & (B_WEATHER_ICY_ANY))
            && !(gSideStatuses[atkSide] & (SIDE_STATUS_REFLECT | SIDE_STATUS_LIGHTSCREEN | SIDE_STATUS_AURORA_VEIL)))
            return TRUE;
        break;
    case EFFECT_REFLECT:
        // Use only if the player has a physical move and AI doesn't already have Reflect itself active.
        if (HasMoveWithCategory(battlerDef, DAMAGE_CATEGORY_PHYSICAL)
            && !(gSideStatuses[atkSide] & (SIDE_STATUS_REFLECT | SIDE_STATUS_AURORA_VEIL)))
            return TRUE;
        break;
    case EFFECT_LIGHT_SCREEN:
        // Use only if the player has a special move and AI doesn't already have Light Screen itself active.
        if (HasMoveWithCategory(battlerDef, DAMAGE_CATEGORY_SPECIAL)
            && !(gSideStatuses[atkSide] & (SIDE_STATUS_LIGHTSCREEN | SIDE_STATUS_AURORA_VEIL)))
            return TRUE;
        break;
    default:
        break;
    }

    return FALSE;
}
