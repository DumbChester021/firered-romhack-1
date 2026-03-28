// Extracted from RHH src/battle_ai_util.c:1547-1562
// 16 lines
// Dependencies: GetNoOfHitsToKOBattler, NoOfHitsForTargetToFaintBattler

u32 NoOfHitsForTargetToFaintBattler(enum BattlerId battlerDef, enum BattlerId battlerAtk, enum AiConsiderEndure considerEndure)
{
    u32 currNumberOfHits;
    u32 leastNumberOfHits = UNKNOWN_NO_OF_HITS;

    for (u32 moveIndex = 0; moveIndex < MAX_MON_MOVES; moveIndex++)
    {
        currNumberOfHits = GetNoOfHitsToKOBattler(battlerDef, battlerAtk, moveIndex, AI_DEFENDING, considerEndure);
        if (currNumberOfHits != 0)
        {
            if (currNumberOfHits < leastNumberOfHits)
                leastNumberOfHits = currNumberOfHits;
        }
    }
    return leastNumberOfHits;
}
