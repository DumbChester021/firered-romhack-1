#ifndef GUARD_BATTLE_AI_MAIN_H
#define GUARD_BATTLE_AI_MAIN_H

#include "global.h"

// AI flag function pointer type.
// Each AI flag function receives the attacker/defender battler IDs, the move being evaluated,
// and the current score. It returns the updated score.
typedef s32 (*AIFunc)(u8 battlerAtk, u8 battlerDef, u16 move, s32 score);

// The function-pointer table indexed by AI flag bit position.
// Declared here so battle_ai_script_commands.c can call through it in BattleAI_DoAIProcessing.
extern const AIFunc gAIFunctionTable[];
extern const u32 gAIFunctionTableSize;

// RHH: StatChange enum (pokeemerald-expansion/include/battle_ai_main.h:15-35)
// Indexes into the stat-change scoring helpers. Ordered to match MOVE_EFFECT offsets.
enum StatChange
{
    STAT_CHANGE_ATK,
    STAT_CHANGE_DEF,
    STAT_CHANGE_SPEED,
    STAT_CHANGE_SPATK,
    STAT_CHANGE_SPDEF,
    STAT_CHANGE_ATK_2,
    STAT_CHANGE_DEF_2,
    STAT_CHANGE_SPEED_2,
    STAT_CHANGE_SPATK_2,
    STAT_CHANGE_SPDEF_2,
    STAT_CHANGE_ATK_3,
    STAT_CHANGE_DEF_3,
    STAT_CHANGE_SPEED_3,
    STAT_CHANGE_SPATK_3,
    STAT_CHANGE_SPDEF_3,
    STAT_CHANGE_ATK_MAX,
    STAT_CHANGE_ACC,
    STAT_CHANGE_EVASION
};

// RHH: AI scoring constants (pokeemerald-expansion/include/battle_ai_main.h:42-53)
// Used by AI_CalcMoveEffectScore and AI_CalcAdditionalEffectScore helpers.
enum AIScore
{
    NO_INCREASE    =  0,
    WEAK_EFFECT    =  1,
    DECENT_EFFECT  =  2,
    GOOD_EFFECT    =  3,
    BEST_EFFECT    =  4,
    PERFECT_EFFECT = 10,
    BAD_EFFECT     = -1,
    AWFUL_EFFECT   = -3,
    WORST_EFFECT   = -10
};

// RHH: ADJUST_SCORE / ADJUST_SCORE_PTR (pokeemerald-expansion/include/battle_ai_main.h:84-113)
// In RHH these also call TestRunner_Battle_AIAdjustScore when TESTING=1.
// We have no test framework, so they reduce to the direct arithmetic.
#define ADJUST_SCORE(val)     do { score    += (val); } while (0)
#define ADJUST_SCORE_PTR(val) do { (*score) += (val); } while (0)

// RHH: AI_WhoStrikesFirst return values (pokeemerald-expansion/src/battle_ai_util.c:1438-1439)
#define AI_IS_FASTER  1
#define AI_IS_SLOWER -1

// RHH: UNKNOWN_NO_OF_HITS sentinel (pokeemerald-expansion/src/battle_ai_util.c)
// Returned by NoOfHitsForTargetToFaintBattler when damage can't be determined.
#define UNKNOWN_NO_OF_HITS UINT32_MAX

#endif // GUARD_BATTLE_AI_MAIN_H
