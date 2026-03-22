#ifndef GUARD_BATTLE_AI_UTIL_H
#define GUARD_BATTLE_AI_UTIL_H

#include "global.h"

// Damage estimation for the C-based Battle AI.
// Returns estimated damage the move will deal (0 if the move has no power or is completely ineffective).
// Sets *typeEffectiveness to the MOVE_RESULT_* flags from TypeCalc.
s32 AI_CalcDamage(u16 move, u8 battlerAtk, u8 battlerDef, u8 *typeEffectiveness);

// Returns TRUE if battlerAtk moves before battlerDef for the given move (accounts for priority).
bool8 AI_IsFaster(u8 battlerAtk, u8 battlerDef, u16 move);

// Returns TRUE if any of battlerAtk's moves have the given effect ID.
bool8 AI_HasMoveEffect(u8 battlerAtk, u16 effect);

// Counts living (non-fainted) mons in battler's party.
u8 AI_CountAlivePokemon(u8 battler);

#endif // GUARD_BATTLE_AI_UTIL_H
