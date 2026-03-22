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

#endif // GUARD_BATTLE_AI_MAIN_H
