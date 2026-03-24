#include "global.h"
#include "battle.h"
#include "battle_anim.h"
#include "util.h"
#include "item.h"
#include "random.h"
#include "battle_ai_script_commands.h"
#include "battle_ai_main.h"
#include "battle_ai_util.h"
#include "constants/abilities.h"
#include "constants/battle_ai.h"
#include "constants/battle_move_effects.h"
#include "constants/moves.h"
#include "pokemon.h"

#define AI_ACTION_DONE          0x0001
#define AI_ACTION_FLEE          0x0002
#define AI_ACTION_WATCH         0x0004
#define AI_ACTION_DO_NOT_ATTACK 0x0008
#define AI_ACTION_UNK5          0x0010
#define AI_ACTION_UNK6          0x0020
#define AI_ACTION_UNK7          0x0040
#define AI_ACTION_UNK8          0x0080

#define AI_THINKING_STRUCT (gBattleResources->ai)
#define BATTLE_HISTORY (gBattleResources->battleHistory)

// AI states
enum
{
    AIState_SettingUp,
    AIState_Processing,
    AIState_FinishedProcessing,
    AIState_DoNotProcess
};


static void RecordLastUsedMoveByTarget(void);
static void BattleAI_DoAIProcessing(void);


static const u16 sDiscouragedPowerfulMoveEffects[] =
{
    EFFECT_EXPLOSION,
    EFFECT_DREAM_EATER,
    EFFECT_RAZOR_WIND,
    EFFECT_SKY_ATTACK,
    EFFECT_RECHARGE,
    EFFECT_SKULL_BASH,
    EFFECT_SOLAR_BEAM,
    EFFECT_SPIT_UP,
    EFFECT_FOCUS_PUNCH,
    EFFECT_SUPERPOWER,
    EFFECT_ERUPTION,
    EFFECT_OVERHEAT,
    0xFFFF
};

void BattleAI_HandleItemUseBeforeAISetup(void)
{
    s32 i;
    u8 *data = (u8 *)BATTLE_HISTORY;

    for (i = 0; i < sizeof(struct BattleHistory); i++)
        data[i] = 0;

    // Items are allowed to use in ONLY trainer battles.
    if ((gBattleTypeFlags & BATTLE_TYPE_TRAINER)
        && (gTrainerBattleOpponent_A != TRAINER_SECRET_BASE)
        && !(gBattleTypeFlags & (BATTLE_TYPE_TRAINER_TOWER | BATTLE_TYPE_EREADER_TRAINER | BATTLE_TYPE_BATTLE_TOWER | BATTLE_TYPE_SAFARI | BATTLE_TYPE_LINK))
        )
    {
        for (i = 0; i < MAX_TRAINER_ITEMS; i++)
        {
            if (gTrainers[gTrainerBattleOpponent_A].items[i] != 0)
            {
                BATTLE_HISTORY->trainerItems[BATTLE_HISTORY->itemsNo] = gTrainers[gTrainerBattleOpponent_A].items[i];
                BATTLE_HISTORY->itemsNo++;
            }
        }
    }

    BattleAI_SetupAIData();
}

void BattleAI_SetupAIData(void)
{
    s32 i;
    u8 *data = (u8 *)AI_THINKING_STRUCT;
    u8 moveLimitations;

    // Clear AI data.
    for (i = 0; i < sizeof(struct AI_ThinkingStruct); i++)
        data[i] = 0;

    for (i = 0; i < MAX_MON_MOVES; i++)
        AI_THINKING_STRUCT->score[i] = 100;

    moveLimitations = CheckMoveLimitations(gActiveBattler, 0, 0xFF);

    // Ignore moves that aren't possible to use.
    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        if (gBitTable[i] & moveLimitations)
            AI_THINKING_STRUCT->score[i] = 0;

        AI_THINKING_STRUCT->simulatedRNG[i] = 100 - (Random() % 16);
    }

    gBattleResources->AI_ScriptsStack->size = 0;
    gBattlerAttacker = gActiveBattler;

    // Decide a random target battlerId in doubles.
    if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE)
    {
        gBattlerTarget = (Random() & BIT_FLANK);

        if (gAbsentBattlerFlags & gBitTable[gBattlerTarget])
            gBattlerTarget ^= BIT_FLANK;
    }
    // There's only one choice in single battles.
    else
    {
        gBattlerTarget = gBattlerAttacker ^ BIT_SIDE;
    }

    // Choose proper trainer ai scripts.
    // Fire Red, why all the returns?!?
    if (gBattleTypeFlags & BATTLE_TYPE_SAFARI)
    {
        AI_THINKING_STRUCT->aiFlags = AI_SCRIPT_SAFARI;
        return;
    }
    else if (gBattleTypeFlags & BATTLE_TYPE_ROAMER)
    {
        AI_THINKING_STRUCT->aiFlags = AI_SCRIPT_ROAMING;
        return;
    }
    else if (!(gBattleTypeFlags & (BATTLE_TYPE_TRAINER_TOWER | BATTLE_TYPE_EREADER_TRAINER | BATTLE_TYPE_BATTLE_TOWER)) && (gTrainerBattleOpponent_A != TRAINER_SECRET_BASE))
    {
        if (gBattleTypeFlags & BATTLE_TYPE_WILD_SCRIPTED)
        {
            AI_THINKING_STRUCT->aiFlags = AI_SCRIPT_CHECK_BAD_MOVE;
            return;
        }
        else if (gBattleTypeFlags & BATTLE_TYPE_LEGENDARY_FRLG)
        {
            AI_THINKING_STRUCT->aiFlags = (AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY);
            return;
        }
        else if (!(gBattleTypeFlags & BATTLE_TYPE_TRAINER))
        {
            u32 avgLevel = GetMonData(&gEnemyParty[0], MON_DATA_LEVEL);
            if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE)
                avgLevel = (GetMonData(&gEnemyParty[0], MON_DATA_LEVEL) + GetMonData(&gEnemyParty[1], MON_DATA_LEVEL)) / 2;

            AI_THINKING_STRUCT->aiFlags = AI_SCRIPT_CHECK_BAD_MOVE;
            if (avgLevel >= 20)
                AI_THINKING_STRUCT->aiFlags |= AI_SCRIPT_CHECK_VIABILITY;
            if (avgLevel >= 60)
                AI_THINKING_STRUCT->aiFlags |= AI_SCRIPT_TRY_TO_FAINT;
            if (avgLevel >= 80)
                AI_THINKING_STRUCT->aiFlags |= AI_SCRIPT_HP_AWARE;

            return;
        }
    }
    else
    {
        AI_THINKING_STRUCT->aiFlags = (AI_SCRIPT_CHECK_BAD_MOVE | AI_SCRIPT_TRY_TO_FAINT | AI_SCRIPT_CHECK_VIABILITY);
        return;
    }
    AI_THINKING_STRUCT->aiFlags = gTrainers[gTrainerBattleOpponent_A].aiFlags;
}

u8 BattleAI_ChooseMoveOrAction(void)
{
    u8 currentMoveArray[MAX_MON_MOVES];
    u8 consideredMoveArray[MAX_MON_MOVES];
    u8 numOfBestMoves;
    s32 i;

    RecordLastUsedMoveByTarget();

    // Smart switching: evaluate before move scoring.
    // If the trainer has AI_SCRIPT_SMART_SWITCHING and a better benched mon
    // exists for the current matchup, switch now instead of using a move.
    if (AI_THINKING_STRUCT->aiFlags & AI_SCRIPT_SMART_SWITCHING)
    {
        u8 switchSlot = AI_EvaluateSwitch(gBattlerAttacker, gBattlerTarget);
        if (switchSlot != PARTY_SIZE)
        {
            *(gBattleStruct->monToSwitchIntoId + gBattlerAttacker) = switchSlot;
            return B_ACTION_SWITCH;
        }
    }

    while (AI_THINKING_STRUCT->aiFlags != 0)
    {
        if (AI_THINKING_STRUCT->aiFlags & 1)
        {
            AI_THINKING_STRUCT->aiState = AIState_SettingUp;
            BattleAI_DoAIProcessing();
        }
        AI_THINKING_STRUCT->aiFlags >>= 1;
        AI_THINKING_STRUCT->aiLogicId++;
        AI_THINKING_STRUCT->movesetIndex = 0;
    }

    // special flee or watch cases for safari.
    if (AI_THINKING_STRUCT->aiAction & AI_ACTION_FLEE)
        return AI_CHOICE_FLEE;
    if (AI_THINKING_STRUCT->aiAction & AI_ACTION_WATCH)
        return AI_CHOICE_WATCH;

    numOfBestMoves = 1;
    currentMoveArray[0] = AI_THINKING_STRUCT->score[0];
    consideredMoveArray[0] = 0;

    for (i = 1; i < MAX_MON_MOVES; i++)
    {
        if (currentMoveArray[0] < AI_THINKING_STRUCT->score[i])
        {
            numOfBestMoves = 1;
            currentMoveArray[0] = AI_THINKING_STRUCT->score[i];
            consideredMoveArray[0] = i;
        }
        if (currentMoveArray[0] == AI_THINKING_STRUCT->score[i])
        {
            currentMoveArray[numOfBestMoves] = AI_THINKING_STRUCT->score[i];
            consideredMoveArray[numOfBestMoves++] = i;
        }
    }

    return consideredMoveArray[Random() % numOfBestMoves]; // break any ties that exist.
}

// BattleAI_DoAIProcessing: replaces the ASM bytecode VM state machine.
// Called once per set AI flag bit from BattleAI_ChooseMoveOrAction.
// Evaluates all moves by invoking the C function for the current flag,
// and updates scores in AI_THINKING_STRUCT.
static void BattleAI_DoAIProcessing(void)
{
    u8 flagIdx = AI_THINKING_STRUCT->aiLogicId;
    u8 i;

    if (flagIdx >= gAIFunctionTableSize || gAIFunctionTable[flagIdx] == NULL)
        return;

    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        u16 move = gBattleMons[gBattlerAttacker].moves[i];

        // Skip moves the AI cannot use (already zeroed by BattleAI_SetupAIData).
        if (AI_THINKING_STRUCT->score[i] == 0)
            continue;
        if (move == MOVE_NONE || gBattleMons[gBattlerAttacker].pp[i] == 0)
            continue;

        AI_THINKING_STRUCT->score[i] = gAIFunctionTable[flagIdx](
            gBattlerAttacker, gBattlerTarget, move, AI_THINKING_STRUCT->score[i]);

        // Scores must not go negative.
        if (AI_THINKING_STRUCT->score[i] < 0)
            AI_THINKING_STRUCT->score[i] = 0;
    }
}

static void RecordLastUsedMoveByTarget(void)
{
    s32 i;

    for (i = 0; i < 8; i++)
    {
        if (BATTLE_HISTORY->usedMoves[gBattlerTarget >> 1][i] == 0)
        {
            BATTLE_HISTORY->usedMoves[gBattlerTarget >> 1][i] = gLastMoves[gBattlerTarget];
            return;
        }
    }
}

// not used
static void ClearBattlerMoveHistory(u8 battlerId)
{
    s32 i;

    for (i = 0; i < 8; i++)
        BATTLE_HISTORY->usedMoves[battlerId / 2][i] = MOVE_NONE;
}

void RecordAbilityBattle(u8 battlerId, u8 abilityId)
{
    if (GetBattlerSide(battlerId) == 0)
        BATTLE_HISTORY->abilities[GET_BATTLER_SIDE(battlerId)] = abilityId;
}

void RecordItemEffectBattle(u8 battlerId, u8 itemEffect)
{
    if (GetBattlerSide(battlerId) == 0)
        BATTLE_HISTORY->itemEffects[GET_BATTLER_SIDE(battlerId)] = itemEffect;
}

