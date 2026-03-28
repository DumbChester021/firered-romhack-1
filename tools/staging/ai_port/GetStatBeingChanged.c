// Extracted from RHH src/battle_ai_util.c:4762-4793
// 32 lines
// Dependencies: GetStatBeingChanged

static enum Stat GetStatBeingChanged(enum StatChange statChange)
{
    switch (statChange)
    {
    case STAT_CHANGE_ATK:
    case STAT_CHANGE_ATK_2:
    case STAT_CHANGE_ATK_3:
    case STAT_CHANGE_ATK_MAX:
        return STAT_ATK;
    case STAT_CHANGE_DEF:
    case STAT_CHANGE_DEF_2:
    case STAT_CHANGE_DEF_3:
        return STAT_DEF;
    case STAT_CHANGE_SPEED:
    case STAT_CHANGE_SPEED_2:
    case STAT_CHANGE_SPEED_3:
        return STAT_SPEED;
    case STAT_CHANGE_SPATK:
    case STAT_CHANGE_SPATK_2:
    case STAT_CHANGE_SPATK_3:
        return STAT_SPATK;
    case STAT_CHANGE_SPDEF:
    case STAT_CHANGE_SPDEF_2:
    case STAT_CHANGE_SPDEF_3:
        return STAT_SPDEF;
    case STAT_CHANGE_ACC:
        return STAT_ACC;
    case STAT_CHANGE_EVASION:
        return STAT_EVASION;
    }
    return 0; // STAT_HP, should never be getting changed
}
