// Extracted from RHH src/battle_ai_util.c:2256-2259
// 4 lines
// Dependencies: FieldStatusChecker, ShouldClearFieldStatus

bool32 ShouldClearFieldStatus(enum BattlerId battler, u32 fieldStatus)
{
    return FieldStatusChecker(battler, fieldStatus, FIELD_EFFECT_NEGATIVE);
}
