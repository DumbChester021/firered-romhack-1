#ifndef GUARD_BATTLE_AI_UTIL_H
#define GUARD_BATTLE_AI_UTIL_H

#include "global.h"

// RHH: ConsiderPriority enum (pokeemerald-expansion/include/battle_ai_util.h:65-69)
// Controls whether AI_WhoStrikesFirst checks move priority before comparing speed.
enum ConsiderPriority
{
    DONT_CONSIDER_PRIORITY,
    CONSIDER_PRIORITY,
};

// ============================================================================
// AI_EFFECTIVENESS_x* constants
// RHH source: include/battle_ai_util.h (AI_EFFECTIVENESS_* enum)
// Same values and semantics — translates from uq4_12_t fixed-point to simple
// byte enum so the rest of the switch logic is structurally identical to RHH.
// ============================================================================
#define AI_EFFECTIVENESS_x0    0  // Immune (no damage)
#define AI_EFFECTIVENESS_x0_5  1  // Not very effective
#define AI_EFFECTIVENESS_x1    2  // Neutral
#define AI_EFFECTIVENESS_x2    3  // Super effective
// FRLG_STUB: RHH also has x0_125, x0_25, x4, x8 for triple-weakness combos.
//   Add these when dual-type combinations with 4x or more are needed.

// Damage estimation for the C-based Battle AI.
// Returns estimated damage the move will deal (0 if the move has no power or is completely ineffective).
// Sets *typeEffectiveness to the MOVE_RESULT_* flags from TypeCalc.
s32 AI_CalcDamage(u16 move, u8 battlerAtk, u8 battlerDef, u8 *typeEffectiveness);

// RHH: AI_WhoStrikesFirst (pokeemerald-expansion/src/battle_ai_util.c:1450)
// Returns AI_IS_FASTER or AI_IS_SLOWER by comparing speeds (and optionally priorities).
s32 AI_WhoStrikesFirst(u8 battlerAtk, u8 battlerDef, u16 aiMove, u16 playerMove, enum ConsiderPriority considerPriority);

// RHH 5-param wrappers (pokeemerald-expansion/include/battle_ai_util.h:80-81)
// Returns TRUE if battlerAtk moves before (or slower than) battlerDef.
bool8 AI_IsFaster(u8 battlerAtk, u8 battlerDef, u16 aiMove, u16 playerMove, enum ConsiderPriority considerPriority);
bool8 AI_IsSlower(u8 battlerAtk, u8 battlerDef, u16 aiMove, u16 playerMove, enum ConsiderPriority considerPriority);

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

// Phase 3: additionalEffects AI helper.
// RHH source: pokeemerald-expansion/include/battle_ai_util.h
// Returns TRUE if any of battlerId's moves have additionalEffects containing moveEffect.
bool8 HasMoveWithAdditionalEffect(u8 battlerId, u16 moveEffect);

bool8 HasMoveWithCategory(u8 battler, u8 category);
bool8 BattlerStatCanRise(u8 battler, u8 stat);
u32 GetBattlerSideSpeedAverage(u8 battler);

// RHH: SetBattlerAiData (pokeemerald-expansion/src/battle_ai_main.c:615)
// Populates gAiLogicData fields for one battler. Call for both battlers before scoring.
void SetBattlerAiData(u8 battler, struct AiLogicData *aiData);

#endif // GUARD_BATTLE_AI_UTIL_H
