// Extracted from RHH src/battle_ai_util.c:2242-2254
// 13 lines
// Dependencies: FieldStatusChecker, ShouldSetFieldStatus

bool32 ShouldSetFieldStatus(enum BattlerId battler, u32 fieldStatus)
{
    if (gFieldStatuses & fieldStatus)
    {
        if (!(fieldStatus & STATUS_FIELD_TRICK_ROOM))
            return FALSE;
        // DOUBLE_TRICK_ROOM_ON_LAST_TURN_CHANCE
        else if (gFieldTimers.trickRoomTimer != 1)
            return FALSE;
    }

    return FieldStatusChecker(battler, fieldStatus, FIELD_EFFECT_POSITIVE);
}
