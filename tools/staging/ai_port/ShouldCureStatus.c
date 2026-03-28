// Extracted from RHH src/battle_ai_util.c:4132-4135
// 4 lines
// Dependencies: ShouldCureStatus, ShouldCureStatusInternal

bool32 ShouldCureStatus(enum BattlerId battlerAtk, enum BattlerId battlerDef, struct AiLogicData *aiData)
{
    return ShouldCureStatusInternal(battlerAtk, battlerDef, FALSE, aiData);
}
