#ifndef GUARD_BATTLE_AI_UTIL_H
#define GUARD_BATTLE_AI_UTIL_H

#include "global.h"
#include "constants/moves.h"

// RHH: IsMoveUnusable (pokeemerald-expansion/include/battle_ai_util.h:71-77)
// Returns TRUE if a move slot should be skipped during AI move evaluation.
static inline bool32 IsMoveUnusable(u32 moveIndex, u16 move, u32 moveLimitations)
{
    return move == MOVE_NONE
        || move == MOVE_UNAVAILABLE
        || (moveLimitations & (1u << moveIndex));
}

// RHH: LEFT_FOE / RIGHT_FOE (pokeemerald-expansion/include/constants/battle.h:62-63)
#ifndef LEFT_FOE
#define LEFT_FOE(battler)  ((BATTLE_OPPOSITE(battler)) & BIT_SIDE)
#define RIGHT_FOE(battler) (((BATTLE_OPPOSITE(battler)) & BIT_SIDE) | BIT_FLANK)
#endif

// RHH: ConsiderPriority enum (pokeemerald-expansion/include/battle_ai_util.h:65-69)
// Controls whether AI_WhoStrikesFirst checks move priority before comparing speed.
enum ConsiderPriority
{
    DONT_CONSIDER_PRIORITY,
    CONSIDER_PRIORITY,
};

// RHH: enum DamageCalcContext (pokeemerald-expansion/include/battle_ai_util.h:17-23)
// Selects which battler's damage perspective to use in AI_GetDamage.
enum DamageCalcContext
{
    AI_DEFENDING,
    AI_ATTACKING,
};

// RHH: enum AiConsiderEndure (pokeemerald-expansion/include/battle_ai_util.h:25-29)
// Controls whether GetNoOfHitsToKOBattler accounts for Focus Sash / Sturdy.
enum AiConsiderEndure
{
    CONSIDER_ENDURE,
    DONT_CONSIDER_ENDURE,
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

// RHH: BattlerHasAi / IsAiFlagPresent / IsAiBattlerAware
// (pokeemerald-expansion/src/battle_controllers.c:103, src/battle_ai_util.c:139/150)
bool32 BattlerHasAi(u8 battler);
bool32 IsAiFlagPresent(u32 flag);
bool32 IsAiBattlerAware(u8 battler);

// RHH: GetMovesArray (pokeemerald-expansion/src/battle_ai_util.c:2528)
// Returns pointer to battler's move array (or history moves if AI is unaware of battler).
u16 *GetMovesArray(u8 battler);

// RHH: HasMoveWithEffect (pokeemerald-expansion/src/battle_ai_util.c:2610)
// Returns TRUE if any of battler's moves have the given battle move effect ID.
bool32 HasMoveWithEffect(u8 battler, u16 effect);

// RHH: GetBattlerSecondaryDamage (pokeemerald-expansion/src/battle_ai_util.c:3417)
// Returns total expected residual damage (leech seed, poison, trap, etc.) this turn.
u32 GetBattlerSecondaryDamage(u8 battlerId);

// RHH: DoesAbilityRaiseStatsWhenLowered (pokeemerald-expansion/src/battle_ai_util.c:5844)
// Returns TRUE for Contrary/Competitive/Defiant — abilities that benefit from stat drops.
bool32 DoesAbilityRaiseStatsWhenLowered(u8 ability);

// RHH: Tier E — setup logic helpers
bool32 CanAiPredictMove(u8 battlerId);
bool32 IsBattlerPredictedToSwitch(u8 battler);
u16 GetIncomingMoveSpeedCheck(u8 battler, u8 opposingBattler, struct AiLogicData *aiData);
bool32 AreBattlersStatsMaxed(u8 battlerId);
u32 CountPositiveStatStages(u8 battlerId);
bool32 AI_IsAbilityOnSide(u8 battlerId, u8 ability);
bool32 ShouldRaiseAnyStat(u8 battlerAtk, u8 battlerDef);

// RHH: SetBattlerAiData (pokeemerald-expansion/src/battle_ai_main.c:615)
// Populates gAiLogicData fields for one battler. Call for both battlers before scoring.
void SetBattlerAiData(u8 battler, struct AiLogicData *aiData);

// RHH: Tier H/I pre-reqs
bool32 DoesSubstituteBlockMove(u8 battlerAtk, u8 battlerDef, u16 move);
bool32 CanAIFaintTarget(u8 battlerAtk, u8 battlerDef, u32 numHits);
bool32 CanTargetFaintAi(u8 battlerDef, u8 battlerAtk);
bool32 HasTwoOpponents(u8 battler);
bool32 HasPartner(u8 battler);
enum AIScore IncreaseStatDownScore(u8 battlerAtk, u8 battlerDef, u8 stat);
enum AIScore IncreaseStatUpScore(u8 battlerAtk, u8 battlerDef, enum StatChange statChange);
enum AIScore IncreaseStatUpScoreContrary(u8 battlerAtk, u8 battlerDef, enum StatChange statChange);
void IncreasePoisonScore(u8 battlerAtk, u8 battlerDef, u16 move, s32 *score);
void IncreaseBurnScore(u8 battlerAtk, u8 battlerDef, u16 move, s32 *score);
void IncreaseParalyzeScore(u8 battlerAtk, u8 battlerDef, u16 move, s32 *score);
void IncreaseSleepScore(u8 battlerAtk, u8 battlerDef, u16 move, s32 *score);
void IncreaseConfusionScore(u8 battlerAtk, u8 battlerDef, u16 move, s32 *score);

// RHH: Tier F — KO calculation helpers
// (pokeemerald-expansion/src/battle_ai_util.c:1362-1561)
bool32 CanEndureHit(u8 battler, u8 battlerTarget, u16 move);
u32 GetNoOfHitsToKO(u32 dmg, s32 hp);
u32 GetNoOfHitsToKOBattlerDmg(u32 dmg, u8 battlerDef);
u32 GetNoOfHitsToKOBattler(u8 battlerAtk, u8 battlerDef, u32 moveIndex, enum DamageCalcContext calcContext, enum AiConsiderEndure considerEndure);
u32 NoOfHitsForTargetToFaintBattler(u8 battlerDef, u8 battlerAtk, enum AiConsiderEndure considerEndure);

// RHH: Tier G — trap detection helpers
// (pokeemerald-expansion/src/battle_ai_util.c:68, 469-510, 4553-4585, 6349-6365)
bool32 AI_IsBattlerGrounded(u8 battler);
bool32 AI_CanBattlerEscape(u8 battler);
void GetAIPartyIndexes(u8 battler, s32 *firstId, s32 *lastId);
s32 CountUsablePartyMons(u8 battlerId);
bool32 IsBattlerTrapped(u8 battlerAtk, u8 battlerDef);

// RHH: Tier F-G supplement
// (pokeemerald-expansion/src/battle_ai_util.c:2513, 1589)
bool32 CanIndexMoveFaintTarget(u8 battlerAtk, u8 battlerDef, u32 moveIndex, enum DamageCalcContext calcContext);
void GetBestDmgMovesFromBattler(u8 battlerAtk, u8 battlerDef, enum DamageCalcContext calcContext, u16 *bestMoves);

#endif // GUARD_BATTLE_AI_UTIL_H
