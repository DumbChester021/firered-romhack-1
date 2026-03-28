// Extracted from RHH src/battle_ai_util.c:4727-4760
// 34 lines
// Dependencies: GetMoveAdditionalEffectById, GetMoveAdditionalEffectCount, GetMovePriority, GetMovesArray, HasMoveThatChangesKOThreshold

static bool32 HasMoveThatChangesKOThreshold(enum BattlerId battlerId, u32 noOfHitsToFaint, bool32 aiIsFaster)
{
    enum Move *moves = GetMovesArray(battlerId);

    for (u32 moveIndex = 0; moveIndex < MAX_MON_MOVES; moveIndex++)
    {
        if (moves[moveIndex] == MOVE_NONE || moves[moveIndex] == MOVE_UNAVAILABLE)
            continue;
        if (noOfHitsToFaint <= 2)
        {
            if (GetMovePriority(moves[moveIndex]) > 0)
                return TRUE;

            u32 additionalEffectCount = GetMoveAdditionalEffectCount(moves[moveIndex]);
            for (u32 effectIndex = 0; effectIndex < additionalEffectCount; effectIndex++)
            {
                const struct AdditionalEffect *additionalEffect = GetMoveAdditionalEffectById(moves[moveIndex], effectIndex);
                switch (additionalEffect->moveEffect)
                {
                case MOVE_EFFECT_SPD_MINUS_1:
                case MOVE_EFFECT_SPD_MINUS_2:
                {
                    if (aiIsFaster && !additionalEffect->self)
                        return TRUE;
                }
                default:
                    break;
                }
            }
        }
    }

    return FALSE;
}
