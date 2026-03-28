// Extracted from RHH src/battle_ai_util.c:5844-5855
// 12 lines
// Dependencies: DoesAbilityRaiseStatsWhenLowered

bool32 DoesAbilityRaiseStatsWhenLowered(enum Ability ability)
{
    switch (ability)
    {
    case ABILITY_CONTRARY:
    case ABILITY_COMPETITIVE:
    case ABILITY_DEFIANT:
        return TRUE;
    default:
        return FALSE;
    }
}
