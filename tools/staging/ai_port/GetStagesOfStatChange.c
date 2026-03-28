// Extracted from RHH src/battle_ai_util.c:4795-4823
// 29 lines
// Dependencies: GetStagesOfStatChange

static u32 GetStagesOfStatChange(enum StatChange statChange)
{
    switch (statChange)
    {
    case STAT_CHANGE_ATK:
    case STAT_CHANGE_DEF:
    case STAT_CHANGE_SPEED:
    case STAT_CHANGE_SPATK:
    case STAT_CHANGE_SPDEF:
    case STAT_CHANGE_ACC:
    case STAT_CHANGE_EVASION:
        return 1;
    case STAT_CHANGE_ATK_2:
    case STAT_CHANGE_DEF_2:
    case STAT_CHANGE_SPEED_2:
    case STAT_CHANGE_SPATK_2:
    case STAT_CHANGE_SPDEF_2:
        return 2;
    case STAT_CHANGE_ATK_3:
    case STAT_CHANGE_DEF_3:
    case STAT_CHANGE_SPEED_3:
    case STAT_CHANGE_SPATK_3:
    case STAT_CHANGE_SPDEF_3:
        return 3;
    case STAT_CHANGE_ATK_MAX:
            return 6;
    }
    return 0; // STAT_HP, should never be getting changed
}
