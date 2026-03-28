// Extracted from RHH src/battle_ai_util.c:2610-2621
// 12 lines
// Dependencies: GetMoveEffect, GetMovesArray, HasMoveWithEffect

bool32 HasMoveWithEffect(enum BattlerId battler, enum BattleMoveEffects effect)
{
    enum Move *moves = GetMovesArray(battler);

    for (u32 moveIndex = 0; moveIndex < MAX_MON_MOVES; moveIndex++)
    {
        if (moves[moveIndex] != MOVE_NONE && moves[moveIndex] != MOVE_UNAVAILABLE && GetMoveEffect(moves[moveIndex]) == effect)
            return TRUE;
    }

    return FALSE;
}
