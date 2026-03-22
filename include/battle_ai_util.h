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

// Smart Switching: evaluates whether battlerAtk should switch out.
// Returns the party slot index to switch to, or PARTY_SIZE if no switch is warranted.
u8 AI_EvaluateSwitch(u8 battlerAtk, u8 battlerDef);

// ============================================================================
// Gen 4+ Extension Stubs
// These return safe neutral values for now.
// When Gen 4+ mechanics are implemented, replace the stub bodies.
// ============================================================================

// GEN4_STUB: Returns a battle desirability rating for an ability (0 = bad/irrelevant).
s32 AI_GetAbilityRating(u8 ability);

// GEN4_STUB: Returns TRUE if the given terrain flag is currently active.
// terrainFlag is a B_TERRAIN_* constant (not defined in FRLG — define when needed).
bool8 AI_IsTerrainActive(u8 terrainFlag);

// GEN4_STUB: Returns TRUE if Trick Room is currently active on the field.
bool8 AI_IsTrickRoomActive(void);

#endif // GUARD_BATTLE_AI_UTIL_H
