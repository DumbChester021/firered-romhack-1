// Extracted from RHH src/battle_ai_util.c:5656-5684
// 29 lines
// Dependencies: AI_ShouldCopyStatChanges, HasMoveWithCategory, HasMoveWithLowAccuracy

bool32 AI_ShouldCopyStatChanges(enum BattlerId battlerAtk, enum BattlerId battlerDef)
{
    // Want to copy positive stat changes
    for (enum Stat statId = STAT_ATK; statId < NUM_BATTLE_STATS; statId++)
    {
        if (gBattleMons[battlerDef].statStages[statId] > gBattleMons[battlerAtk].statStages[statId])
        {
            switch (statId)
            {
            case STAT_ATK:
                return (HasMoveWithCategory(battlerAtk, DAMAGE_CATEGORY_PHYSICAL));
            case STAT_SPATK:
                return (HasMoveWithCategory(battlerAtk, DAMAGE_CATEGORY_SPECIAL));
            case STAT_ACC:
                return HasMoveWithLowAccuracy(battlerAtk, battlerDef, LOW_ACCURACY_THRESHOLD, FALSE);
            case STAT_EVASION:
            case STAT_SPEED:
                return TRUE;
            case STAT_DEF:
            case STAT_SPDEF:
                return (gAiThinkingStruct->aiFlags[battlerAtk] & AI_FLAG_STALL);
            default:
                break;
            }
        }
    }

    return FALSE;
}
