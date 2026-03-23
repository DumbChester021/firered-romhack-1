#include "global.h"
#include "battle.h"
#include "battle_anim.h"
#include "battle_ai_main.h"
#include "battle_ai_util.h"
#include "battle_script_commands.h"
#include "pokemon.h"
#include "random.h"
#include "constants/abilities.h"
#include "constants/battle.h"
#include "constants/battle_ai.h"
#include "constants/battle_move_effects.h"
#include "constants/items.h"
#include "constants/moves.h"
#include "constants/pokemon.h"

// Forward declarations for all AI flag functions.
static s32 AI_CheckBadMove(u8 battlerAtk, u8 battlerDef, u16 move, s32 score);
static s32 AI_CheckViability(u8 battlerAtk, u8 battlerDef, u16 move, s32 score);
static s32 AI_TryToFaint(u8 battlerAtk, u8 battlerDef, u16 move, s32 score);
static s32 AI_SetupFirstTurn(u8 battlerAtk, u8 battlerDef, u16 move, s32 score);
static s32 AI_Risky(u8 battlerAtk, u8 battlerDef, u16 move, s32 score);
static s32 AI_PreferStrongestMove(u8 battlerAtk, u8 battlerDef, u16 move, s32 score);
static s32 AI_PreferBatonPass(u8 battlerAtk, u8 battlerDef, u16 move, s32 score);
static s32 AI_DoubleBattle(u8 battlerAtk, u8 battlerDef, u16 move, s32 score);
static s32 AI_HPAware(u8 battlerAtk, u8 battlerDef, u16 move, s32 score);
static s32 AI_SmartSwitching(u8 battlerAtk, u8 battlerDef, u16 move, s32 score);
static s32 AI_Roaming(u8 battlerAtk, u8 battlerDef, u16 move, s32 score);
static s32 AI_Safari(u8 battlerAtk, u8 battlerDef, u16 move, s32 score);
static s32 AI_FirstBattle(u8 battlerAtk, u8 battlerDef, u16 move, s32 score);

// Maps AI flag bit index to handler function.
// Indices 9-19 are NULL (reserved/unused in FRLG).
const AIFunc gAIFunctionTable[] = {
    [0]  = AI_CheckBadMove,
    [1]  = AI_CheckViability,
    [2]  = AI_TryToFaint,
    [3]  = AI_SetupFirstTurn,
    [4]  = AI_Risky,
    [5]  = AI_PreferStrongestMove,
    [6]  = AI_PreferBatonPass,
    [7]  = AI_DoubleBattle,
    [8]  = AI_HPAware,
    [9]  = AI_SmartSwitching,  // No-op scoring slot; switch logic runs in BattleAI_ChooseMoveOrAction
    // [10-19] = NULL (implicitly)
    [20] = AI_Roaming,
    [21] = AI_Safari,
    [22] = AI_FirstBattle,
};

const u32 gAIFunctionTableSize = ARRAY_COUNT(gAIFunctionTable);

// ============================================================================
// Helpers shared across AI flags
// ============================================================================

static bool8 IsMoveTypeMatchingAbsorb(u16 move, u8 ability)
{
    u8 moveType = gBattleMoves[move].type;
    switch (ability)
    {
    case ABILITY_VOLT_ABSORB:  return moveType == TYPE_ELECTRIC;
    case ABILITY_WATER_ABSORB: return moveType == TYPE_WATER;
    case ABILITY_FLASH_FIRE:   return moveType == TYPE_FIRE;
    default:                   return FALSE;
    }
}

// ============================================================================
// AI_CheckBadMove (flag bit 0)
// Penalizes moves that are pointless or harmful to use.
// Direct C translation of data/battle_ai_scripts.s lines 52–631.
// Includes 6 Emerald improvements (marked EMERALD).
// ============================================================================
static s32 AI_CheckBadMove(u8 battlerAtk, u8 battlerDef, u16 move, s32 score)
{
    u16 effect = gBattleMoves[move].effect;
    u8 atkAbility = gBattleMons[battlerAtk].ability;
    u8 defAbility = gBattleMons[battlerDef].ability;
    u8 moveType = gBattleMoves[move].type;
    u8 defStatus = gBattleMons[battlerDef].status1;
    u8 atkStatus = gBattleMons[battlerAtk].status1;
    u8 typeFlags;

    // --- Type effectiveness check (skip for OHKO moves handled separately) ---
    typeFlags = TypeCalc(move, battlerAtk, battlerDef);
    // Reset after check since TypeCalc modifies gBattleMoveDamage in place.

    if ((typeFlags & MOVE_RESULT_DOESNT_AFFECT_FOE) && effect != EFFECT_OHKO)
        return score - 10;

    // --- Ability-based immunity checks ---
    if ((defAbility == ABILITY_VOLT_ABSORB || defAbility == ABILITY_WATER_ABSORB || defAbility == ABILITY_FLASH_FIRE)
      && IsMoveTypeMatchingAbsorb(move, defAbility))
        return score - 12;

    if (defAbility == ABILITY_WONDER_GUARD && !(typeFlags & MOVE_RESULT_SUPER_EFFECTIVE))
        return score - 10;

    if (defAbility == ABILITY_LEVITATE && moveType == TYPE_GROUND)
        return score - 10;

    // --- Soundproof ---
    if (defAbility == ABILITY_SOUNDPROOF)
    {
        static const u16 sSoundMoves[] = {
            MOVE_GROWL, MOVE_ROAR, MOVE_SING, MOVE_SUPERSONIC, MOVE_SCREECH,
            MOVE_SNORE, MOVE_UPROAR, MOVE_METAL_SOUND, MOVE_GRASS_WHISTLE, MOVE_NONE
        };
        u8 i;
        for (i = 0; sSoundMoves[i] != MOVE_NONE; i++)
        {
            if (move == sSoundMoves[i])
                return score - 10;
        }
    }

    // --- Effect-specific checks ---
    switch (effect)
    {
    case EFFECT_SLEEP:
        if (defAbility == ABILITY_INSOMNIA || defAbility == ABILITY_VITAL_SPIRIT)
            return score - 10;
        if (defStatus & STATUS1_ANY)
            return score - 10;
        // EMERALD: also penalize if Safeguard is on the target's side
        if (gSideStatuses[GET_BATTLER_SIDE(battlerDef)] & SIDE_STATUS_SAFEGUARD)
            return score - 10;
        break;

    case EFFECT_EXPLOSION:
        if (typeFlags & MOVE_RESULT_DOESNT_AFFECT_FOE)
            return score - 10;
        if (defAbility == ABILITY_DAMP)
            return score - 10;
        // Only worthwhile if we have no other alive mons and opponent does
        if (AI_CountAlivePokemon(battlerAtk) != 0)
            break;
        if (AI_CountAlivePokemon(battlerDef) != 0)
            return score - 10;
        return score - 1;

    case EFFECT_DREAM_EATER:
        if (!(defStatus & STATUS1_SLEEP))
            return score - 8;
        if (typeFlags & MOVE_RESULT_DOESNT_AFFECT_FOE)
            return score - 10;
        break;

    case EFFECT_ATTACK_UP:
    case EFFECT_ATTACK_UP_2:
    case EFFECT_BELLY_DRUM: // belly drum also checks HP <= 50%
        if (effect == EFFECT_BELLY_DRUM && gBattleMons[battlerAtk].hp * 100 / gBattleMons[battlerAtk].maxHP <= 50)
            return score - 10;
        if (gBattleMons[battlerAtk].statStages[STAT_ATK] == MAX_STAT_STAGE)
            return score - 10;
        break;

    case EFFECT_DEFENSE_UP:
    case EFFECT_DEFENSE_UP_2:
    case EFFECT_DEFENSE_CURL:
        if (gBattleMons[battlerAtk].statStages[STAT_DEF] == MAX_STAT_STAGE)
            return score - 10;
        break;

    case EFFECT_SPEED_UP:
    case EFFECT_SPEED_UP_2:
        if (gBattleMons[battlerAtk].statStages[STAT_SPEED] == MAX_STAT_STAGE)
            return score - 10;
        break;

    case EFFECT_SPECIAL_ATTACK_UP:
    case EFFECT_SPECIAL_ATTACK_UP_2:
        if (gBattleMons[battlerAtk].statStages[STAT_SPATK] == MAX_STAT_STAGE)
            return score - 10;
        break;

    case EFFECT_SPECIAL_DEFENSE_UP:
    case EFFECT_SPECIAL_DEFENSE_UP_2:
        if (gBattleMons[battlerAtk].statStages[STAT_SPDEF] == MAX_STAT_STAGE)
            return score - 10;
        break;

    case EFFECT_ACCURACY_UP:
    case EFFECT_ACCURACY_UP_2:
        if (gBattleMons[battlerAtk].statStages[STAT_ACC] == MAX_STAT_STAGE)
            return score - 10;
        break;

    case EFFECT_EVASION_UP:
    case EFFECT_EVASION_UP_2:
    case EFFECT_MINIMIZE:
        if (gBattleMons[battlerAtk].statStages[STAT_EVASION] == MAX_STAT_STAGE)
            return score - 10;
        break;

    case EFFECT_ATTACK_DOWN:
    case EFFECT_ATTACK_DOWN_2:
        if (gBattleMons[battlerDef].statStages[STAT_ATK] == MIN_STAT_STAGE)
            return score - 10;
        if (defAbility == ABILITY_HYPER_CUTTER)
            return score - 10;
        if (defAbility == ABILITY_CLEAR_BODY || defAbility == ABILITY_WHITE_SMOKE)
            return score - 10;
        break;

    case EFFECT_DEFENSE_DOWN:
    case EFFECT_DEFENSE_DOWN_2:
        if (gBattleMons[battlerDef].statStages[STAT_DEF] == MIN_STAT_STAGE)
            return score - 10;
        if (defAbility == ABILITY_CLEAR_BODY || defAbility == ABILITY_WHITE_SMOKE)
            return score - 10;
        break;

    case EFFECT_SPEED_DOWN:
    case EFFECT_SPEED_DOWN_2:
        if (gBattleMons[battlerDef].statStages[STAT_SPEED] == MIN_STAT_STAGE)
            return score - 10;
        // EMERALD: Speed Boost makes lowering speed pointless
        if (defAbility == ABILITY_SPEED_BOOST)
            return score - 10;
        if (defAbility == ABILITY_CLEAR_BODY || defAbility == ABILITY_WHITE_SMOKE)
            return score - 10;
        break;

    case EFFECT_SPECIAL_ATTACK_DOWN:
    case EFFECT_SPECIAL_ATTACK_DOWN_2:
        if (gBattleMons[battlerDef].statStages[STAT_SPATK] == MIN_STAT_STAGE)
            return score - 10;
        if (defAbility == ABILITY_CLEAR_BODY || defAbility == ABILITY_WHITE_SMOKE)
            return score - 10;
        break;

    case EFFECT_SPECIAL_DEFENSE_DOWN:
    case EFFECT_SPECIAL_DEFENSE_DOWN_2:
        if (gBattleMons[battlerDef].statStages[STAT_SPDEF] == MIN_STAT_STAGE)
            return score - 10;
        if (defAbility == ABILITY_CLEAR_BODY || defAbility == ABILITY_WHITE_SMOKE)
            return score - 10;
        break;

    case EFFECT_ACCURACY_DOWN:
    case EFFECT_ACCURACY_DOWN_2:
        if (gBattleMons[battlerDef].statStages[STAT_ACC] == MIN_STAT_STAGE)
            return score - 10;
        if (defAbility == ABILITY_KEEN_EYE)
            return score - 10;
        if (defAbility == ABILITY_CLEAR_BODY || defAbility == ABILITY_WHITE_SMOKE)
            return score - 10;
        break;

    case EFFECT_EVASION_DOWN:
    case EFFECT_EVASION_DOWN_2:
        if (gBattleMons[battlerDef].statStages[STAT_EVASION] == MIN_STAT_STAGE)
            return score - 10;
        if (defAbility == ABILITY_CLEAR_BODY || defAbility == ABILITY_WHITE_SMOKE)
            return score - 10;
        break;

    case EFFECT_HAZE:
    case EFFECT_PSYCH_UP:
    {
        // Penalize if user's stats are all normal and target has no boosts
        bool8 userBoosted = FALSE;
        bool8 targetBoosted = FALSE;
        u8 s;
        for (s = STAT_ATK; s <= STAT_EVASION; s++)
        {
            if (gBattleMons[battlerAtk].statStages[s] != DEFAULT_STAT_STAGE) userBoosted = TRUE;
            if (gBattleMons[battlerDef].statStages[s] != DEFAULT_STAT_STAGE) targetBoosted = TRUE;
        }
        if (!userBoosted && !targetBoosted)
            return score - 10;
        break;
    }

    case EFFECT_ROAR:
        if (AI_CountAlivePokemon(battlerDef) == 0)
            return score - 10;
        if (defAbility == ABILITY_SUCTION_CUPS)
            return score - 10;
        break;

    case EFFECT_TOXIC:
    case EFFECT_POISON:
    {
        u8 type1 = gBattleMons[battlerDef].type1;
        u8 type2 = gBattleMons[battlerDef].type2;
        if (type1 == TYPE_STEEL || type1 == TYPE_POISON || type2 == TYPE_STEEL || type2 == TYPE_POISON)
            return score - 10;
        if (defAbility == ABILITY_IMMUNITY)
            return score - 10;
        if (defStatus & STATUS1_ANY)
            return score - 10;
        // EMERALD: Safeguard
        if (gSideStatuses[GET_BATTLER_SIDE(battlerDef)] & SIDE_STATUS_SAFEGUARD)
            return score - 10;
        break;
    }

    case EFFECT_LIGHT_SCREEN:
        if (gSideStatuses[GET_BATTLER_SIDE(battlerAtk)] & SIDE_STATUS_LIGHTSCREEN)
            return score - 8;
        break;

    case EFFECT_OHKO:
        if (typeFlags & MOVE_RESULT_DOESNT_AFFECT_FOE)
            return score - 10;
        if (defAbility == ABILITY_STURDY)
            return score - 10;
        // Penalize if target's level is higher than user's
        if (gBattleMons[battlerDef].level > gBattleMons[battlerAtk].level)
            return score - 10;
        break;

    case EFFECT_MAGNITUDE:
        if (defAbility == ABILITY_LEVITATE)
            return score - 10;
        // Fall through to HighRiskForDamage
        if (typeFlags & MOVE_RESULT_DOESNT_AFFECT_FOE)
            return score - 10;
        if (defAbility == ABILITY_WONDER_GUARD && !(typeFlags & MOVE_RESULT_SUPER_EFFECTIVE))
            return score - 10;
        break;

    // HighRiskForDamage group: just check type effectiveness
    case EFFECT_BIDE:
    case EFFECT_RAZOR_WIND:
    case EFFECT_SUPER_FANG:
    case EFFECT_LEVEL_DAMAGE:
    case EFFECT_PSYWAVE:
    case EFFECT_COUNTER:
    case EFFECT_FLAIL:
    case EFFECT_RETURN:
    case EFFECT_PRESENT:
    case EFFECT_FRUSTRATION:
    case EFFECT_SONICBOOM:
    case EFFECT_MIRROR_COAT:
    case EFFECT_SKULL_BASH:
    case EFFECT_LOW_KICK:
    case EFFECT_RECHARGE:
    case EFFECT_FOCUS_PUNCH:
    case EFFECT_SUPERPOWER:
    case EFFECT_ENDEAVOR:
        if (typeFlags & MOVE_RESULT_DOESNT_AFFECT_FOE)
            return score - 10;
        if (defAbility == ABILITY_WONDER_GUARD && !(typeFlags & MOVE_RESULT_SUPER_EFFECTIVE))
            return score - 10;
        break;

    case EFFECT_MIST:
        if (gSideStatuses[GET_BATTLER_SIDE(battlerAtk)] & SIDE_STATUS_MIST)
            return score - 8;
        break;

    case EFFECT_FOCUS_ENERGY:
        if (gBattleMons[battlerAtk].status2 & STATUS2_FOCUS_ENERGY)
            return score - 10;
        break;

    case EFFECT_CONFUSE:
    case EFFECT_SWAGGER:
    case EFFECT_FLATTER:
        if (gBattleMons[battlerDef].status2 & STATUS2_CONFUSION)
            return score - 5;
        if (defAbility == ABILITY_OWN_TEMPO)
            return score - 10;
        // EMERALD: Safeguard
        if (gSideStatuses[GET_BATTLER_SIDE(battlerDef)] & SIDE_STATUS_SAFEGUARD)
            return score - 10;
        break;

    case EFFECT_REFLECT:
        if (gSideStatuses[GET_BATTLER_SIDE(battlerAtk)] & SIDE_STATUS_REFLECT)
            return score - 8;
        break;

    case EFFECT_PARALYZE:
        if (typeFlags & MOVE_RESULT_DOESNT_AFFECT_FOE)
            return score - 10;
        if (defAbility == ABILITY_LIMBER)
            return score - 10;
        if (defStatus & STATUS1_ANY)
            return score - 10;
        // EMERALD: Safeguard
        if (gSideStatuses[GET_BATTLER_SIDE(battlerDef)] & SIDE_STATUS_SAFEGUARD)
            return score - 10;
        break;

    case EFFECT_SUBSTITUTE:
        if (gBattleMons[battlerAtk].status2 & STATUS2_SUBSTITUTE)
            return score - 8;
        if (gBattleMons[battlerAtk].hp * 100 / gBattleMons[battlerAtk].maxHP <= 25)
            return score - 10;
        break;

    case EFFECT_LEECH_SEED:
        if (gStatuses3[battlerDef] & STATUS3_LEECHSEED)
            return score - 10;
        if (gBattleMons[battlerDef].type1 == TYPE_GRASS || gBattleMons[battlerDef].type2 == TYPE_GRASS)
            return score - 10;
        break;

    case EFFECT_DISABLE:
        if (gDisableStructs[battlerDef].disabledMove != MOVE_NONE)
            return score - 8;
        break;

    case EFFECT_ENCORE:
        if (gDisableStructs[battlerDef].encoredMove != MOVE_NONE)
            return score - 8;
        break;

    case EFFECT_SNORE:
    case EFFECT_SLEEP_TALK:
        if (!(atkStatus & STATUS1_SLEEP))
            return score - 8;
        break;

    case EFFECT_MEAN_LOOK:
        if (gBattleMons[battlerDef].status2 & STATUS2_ESCAPE_PREVENTION)
            return score - 10;
        break;

    case EFFECT_NIGHTMARE:
        if (gBattleMons[battlerDef].status2 & STATUS2_NIGHTMARE)
            return score - 10;
        if (!(defStatus & STATUS1_SLEEP))
            return score - 8;
        break;

    case EFFECT_CURSE:
        if (gBattleMons[battlerAtk].statStages[STAT_ATK] == MAX_STAT_STAGE)
            return score - 10;
        if (gBattleMons[battlerAtk].statStages[STAT_DEF] == MAX_STAT_STAGE)
            return score - 8;
        break;

    case EFFECT_SPIKES:
        if (gSideStatuses[GET_BATTLER_SIDE(battlerDef)] & SIDE_STATUS_SPIKES)
            return score - 10;
        break;

    case EFFECT_FORESIGHT:
        if (gBattleMons[battlerDef].status2 & STATUS2_FORESIGHT)
            return score - 10;
        break;

    case EFFECT_PERISH_SONG:
        if (gStatuses3[battlerDef] & STATUS3_PERISH_SONG)
            return score - 10;
        break;

    case EFFECT_SANDSTORM:
        if (gBattleWeather & B_WEATHER_SANDSTORM)
            return score - 8;
        break;

    case EFFECT_ATTRACT:
        if (gBattleMons[battlerDef].status2 & STATUS2_INFATUATION)
            return score - 10;
        if (defAbility == ABILITY_OBLIVIOUS)
            return score - 10;
        {
            u8 genderAtk = GetGenderFromSpeciesAndPersonality(gBattleMons[battlerAtk].species, gBattleMons[battlerAtk].personality);
            u8 genderDef = GetGenderFromSpeciesAndPersonality(gBattleMons[battlerDef].species, gBattleMons[battlerDef].personality);
            if (genderAtk == MON_GENDERLESS || genderDef == MON_GENDERLESS)
                return score - 10;
            if (genderAtk == genderDef)
                return score - 10;
        }
        break;

    case EFFECT_SAFEGUARD:
        if (gSideStatuses[GET_BATTLER_SIDE(battlerAtk)] & SIDE_STATUS_SAFEGUARD)
            return score - 8;
        break;

    case EFFECT_MEMENTO:
        if (gBattleMons[battlerDef].statStages[STAT_ATK] == MIN_STAT_STAGE)
            return score - 10;
        if (gBattleMons[battlerDef].statStages[STAT_SPATK] == MIN_STAT_STAGE)
            return score - 8;
        break;

    case EFFECT_BATON_PASS:
        if (AI_CountAlivePokemon(battlerAtk) == 0)
            return score - 10;
        break;

    case EFFECT_RAIN_DANCE:
        if (gBattleWeather & B_WEATHER_RAIN)
            return score - 8;
        break;

    case EFFECT_SUNNY_DAY:
        if (gBattleWeather & B_WEATHER_SUN)
            return score - 8;
        break;

    case EFFECT_FUTURE_SIGHT:
        // EMERALD: also penalize if our side already has a future attack pending
        if (gSideStatuses[GET_BATTLER_SIDE(battlerDef)] & SIDE_STATUS_FUTUREATTACK)
            return score - 10;
        if (gSideStatuses[GET_BATTLER_SIDE(battlerAtk)] & SIDE_STATUS_FUTUREATTACK)
            return score - 12;
        break;

    case EFFECT_TELEPORT:
        return score - 10;

    case EFFECT_FAKE_OUT:
        if (!gDisableStructs[battlerAtk].isFirstTurn)
            return score - 10;
        break;

    case EFFECT_STOCKPILE:
        if (gDisableStructs[battlerAtk].stockpileCounter >= 3)
            return score - 10;
        break;

    case EFFECT_SPIT_UP:
    case EFFECT_SWALLOW:
        if (typeFlags & MOVE_RESULT_DOESNT_AFFECT_FOE)
            return score - 10;
        if (gDisableStructs[battlerAtk].stockpileCounter == 0)
            return score - 10;
        break;

    case EFFECT_HAIL:
        if (gBattleWeather & B_WEATHER_HAIL)
            return score - 8;
        break;

    case EFFECT_TORMENT:
        if (gBattleMons[battlerDef].status2 & STATUS2_TORMENT)
            return score - 10;
        break;

    case EFFECT_WILL_O_WISP:
        if (defAbility == ABILITY_WATER_VEIL)
            return score - 10;
        if (defStatus & STATUS1_ANY)
            return score - 10;
        if (typeFlags & (MOVE_RESULT_DOESNT_AFFECT_FOE | MOVE_RESULT_NOT_VERY_EFFECTIVE))
            return score - 10;
        // EMERALD: Safeguard
        if (gSideStatuses[GET_BATTLER_SIDE(battlerDef)] & SIDE_STATUS_SAFEGUARD)
            return score - 10;
        break;

    case EFFECT_HELPING_HAND:
        if (!(gBattleTypeFlags & BATTLE_TYPE_DOUBLE))
            return score - 10;
        break;

    case EFFECT_TRICK:
    case EFFECT_KNOCK_OFF:
        if (defAbility == ABILITY_STICKY_HOLD)
            return score - 10;
        break;

    case EFFECT_INGRAIN:
        if (gStatuses3[battlerAtk] & STATUS3_ROOTED)
            return score - 10;
        break;

    case EFFECT_RECYCLE:
        // Penalize if no used held item
        if (gBattleMons[battlerAtk].item != ITEM_NONE)
            return score - 10;
        break;

    case EFFECT_IMPRISON:
        if (gStatuses3[battlerAtk] & STATUS3_IMPRISONED_OTHERS)
            return score - 10;
        break;

    case EFFECT_REFRESH:
        if (!(atkStatus & (STATUS1_POISON | STATUS1_BURN | STATUS1_PARALYSIS | STATUS1_TOXIC_POISON)))
            return score - 10;
        break;

    case EFFECT_MUD_SPORT:
        if (gStatuses3[battlerAtk] & STATUS3_MUDSPORT)
            return score - 10;
        break;

    case EFFECT_TICKLE:
        if (gBattleMons[battlerDef].statStages[STAT_ATK] == MIN_STAT_STAGE)
            return score - 10;
        if (gBattleMons[battlerDef].statStages[STAT_DEF] == MIN_STAT_STAGE)
            return score - 8;
        break;

    case EFFECT_COSMIC_POWER:
        if (gBattleMons[battlerAtk].statStages[STAT_DEF] == MAX_STAT_STAGE)
            return score - 10;
        if (gBattleMons[battlerAtk].statStages[STAT_SPDEF] == MAX_STAT_STAGE)
            return score - 8;
        break;

    case EFFECT_BULK_UP:
        if (gBattleMons[battlerAtk].statStages[STAT_ATK] == MAX_STAT_STAGE)
            return score - 10;
        if (gBattleMons[battlerAtk].statStages[STAT_DEF] == MAX_STAT_STAGE)
            return score - 8;
        break;

    case EFFECT_WATER_SPORT:
        if (gStatuses3[battlerAtk] & STATUS3_WATERSPORT)
            return score - 10;
        break;

    case EFFECT_CALM_MIND:
        if (gBattleMons[battlerAtk].statStages[STAT_SPATK] == MAX_STAT_STAGE)
            return score - 10;
        if (gBattleMons[battlerAtk].statStages[STAT_SPDEF] == MAX_STAT_STAGE)
            return score - 8;
        break;

    case EFFECT_DRAGON_DANCE:
        if (gBattleMons[battlerAtk].statStages[STAT_ATK] == MAX_STAT_STAGE)
            return score - 10;
        if (gBattleMons[battlerAtk].statStages[STAT_SPEED] == MAX_STAT_STAGE)
            return score - 8;
        break;
    }

    return score;
}

// ============================================================================
// AI_CheckViability (flag bit 1)
// Fine-grained scoring for move viability. Direct C port of ASM table
// (battle_ai_scripts.s lines 653–2766).
// ============================================================================
static s32 AI_CheckViability(u8 battlerAtk, u8 battlerDef, u16 move, s32 score)
{
    u16 effect      = gBattleMoves[move].effect;
    u8 atkHpPct    = gBattleMons[battlerAtk].hp * 100 / gBattleMons[battlerAtk].maxHP;
    u8 defHpPct    = gBattleMons[battlerDef].hp * 100 / gBattleMons[battlerDef].maxHP;
    u8 atkAbility  = gBattleMons[battlerAtk].ability;
    u8 atkStgAtk   = gBattleMons[battlerAtk].statStages[STAT_ATK];
    u8 atkStgDef   = gBattleMons[battlerAtk].statStages[STAT_DEF];
    u8 atkStgSpAtk = gBattleMons[battlerAtk].statStages[STAT_SPATK];
    u8 atkStgSpDef = gBattleMons[battlerAtk].statStages[STAT_SPDEF];
    u8 atkStgSpd   = gBattleMons[battlerAtk].statStages[STAT_SPEED];
    u8 atkStgEva   = gBattleMons[battlerAtk].statStages[STAT_EVASION];
    u8 defStgAtk   = gBattleMons[battlerDef].statStages[STAT_ATK];
    u8 defStgSpAtk = gBattleMons[battlerDef].statStages[STAT_SPATK];
    u8 defStgEva   = gBattleMons[battlerDef].statStages[STAT_EVASION];
    u8 defStatus1  = gBattleMons[battlerDef].status1;
    u8 defStatus2  = gBattleMons[battlerDef].status2;
    u8 atkStatus1  = gBattleMons[battlerAtk].status1;
    u8 atkStatus2  = gBattleMons[battlerAtk].status2;
    u8 defType1    = gBattleMons[battlerDef].type1;
    u8 defType2    = gBattleMons[battlerDef].type2;
    u8 atkType1    = gBattleMons[battlerAtk].type1;
    u8 atkType2    = gBattleMons[battlerAtk].type2;
    bool8 faster   = AI_IsFaster(battlerAtk, battlerDef, move);
    u8 typeFlags   = TypeCalc(move, battlerAtk, battlerDef);
    bool8 superEff = (typeFlags & MOVE_RESULT_SUPER_EFFECTIVE) != 0;
    bool8 notVeryEff = (typeFlags & MOVE_RESULT_NOT_VERY_EFFECTIVE) != 0;

    switch (effect)
    {
    // ---- Stat boosts for user ----
    case EFFECT_ATTACK_UP:
    case EFFECT_ATTACK_UP_2:
        if (atkStgAtk >= 10)
        { if ((Random() % 100) >= 100) score -= 1; }
        else if (atkHpPct == 100 && (Random() % 256) >= 128)
            score += 2;
        if (atkHpPct <= 70)
        {
            if (atkHpPct <= 40) score -= 2;
            else if ((Random() % 100) >= 40) score -= 0;
        }
        break;

    case EFFECT_DEFENSE_UP:
    case EFFECT_DEFENSE_UP_2:
        if (atkStgDef >= 10)
        { if ((Random() % 100) >= 100) score -= 1; }
        else if (atkHpPct == 100 && (Random() % 256) >= 128)
            score += 2;
        if (atkHpPct < 70)
        {
            if (atkHpPct < 40) score -= 2;
        }
        break;

    case EFFECT_SPEED_UP:
    case EFFECT_SPEED_UP_2:
        if (!faster) score -= 3;
        else if ((Random() % 100) >= 70) score += 3;
        break;

    case EFFECT_SPECIAL_ATTACK_UP:
    case EFFECT_SPECIAL_ATTACK_UP_2:
        if (atkStgSpAtk >= 10)
        { if ((Random() % 100) >= 100) score -= 1; }
        else if (atkHpPct == 100 && (Random() % 256) >= 128)
            score += 2;
        if (atkHpPct <= 70)
        {
            if (atkHpPct <= 40) score -= 2;
            else if ((Random() % 100) >= 70) score -= 0;
        }
        break;

    case EFFECT_SPECIAL_DEFENSE_UP:
    case EFFECT_SPECIAL_DEFENSE_UP_2:
        if (atkStgSpDef >= 10)
        { if ((Random() % 100) >= 100) score -= 1; }
        else if (atkHpPct == 100 && (Random() % 256) >= 128)
            score += 2;
        if (atkHpPct < 70)
        {
            if (atkHpPct < 40) score -= 2;
        }
        break;

    case EFFECT_ACCURACY_UP:
    case EFFECT_ACCURACY_UP_2:
        if (gBattleMons[battlerAtk].statStages[STAT_ACC] >= 10
            && (Random() % 256) >= 50)
            score -= 2;
        if (atkHpPct <= 70)
            score -= 2;
        break;

    case EFFECT_EVASION_UP:
    case EFFECT_EVASION_UP_2:
    case EFFECT_MINIMIZE:
        if (atkHpPct >= 90 && (Random() % 100) >= 100)
            score += 3;
        if (atkStgEva >= 10 && (Random() % 256) >= 128)
            score -= 1;
        if (defStatus1 & STATUS1_TOXIC_POISON)
        {
            if (atkHpPct > 50 || (Random() % 256) >= 80)
            { if ((Random() % 256) >= 50) score += 3; }
            else score += 3;
        }
        if (gStatuses3[battlerDef] & STATUS3_LEECHSEED && (Random() % 100) >= 70)
            score += 3;
        if (gStatuses3[battlerAtk] & STATUS3_ROOTED && (Random() % 256) >= 128)
            score += 2;
        if (defStatus2 & STATUS2_CURSED && (Random() % 100) >= 70)
            score += 3;
        if (atkHpPct <= 70 && atkStgEva != DEFAULT_STAT_STAGE
            && atkHpPct > 40 && defHpPct > 40
            && (Random() % 100) >= 70)
            score -= 2;
        break;

    // ---- Stat drops for target ----
    case EFFECT_ATTACK_DOWN:
    case EFFECT_ATTACK_DOWN_2:
        // Penalize if target is not a physical attacker
        if (defStgAtk == DEFAULT_STAT_STAGE)
            score -= 1;
        if (atkHpPct >= 90)
            score -= 1;
        if (defStgAtk <= 4 && (Random() % 256) >= 50)
            score -= 2;
        if (defHpPct <= 70)
            score -= 2;
        if (defType1 != TYPE_NORMAL && defType1 != TYPE_FIGHTING &&
            defType1 != TYPE_GROUND && defType1 != TYPE_ROCK &&
            defType1 != TYPE_BUG    && defType1 != TYPE_STEEL &&
            defType2 != TYPE_NORMAL && defType2 != TYPE_FIGHTING &&
            defType2 != TYPE_GROUND && defType2 != TYPE_ROCK &&
            defType2 != TYPE_BUG    && defType2 != TYPE_STEEL &&
            (Random() % 256) >= 50)
            score -= 2;
        break;

    case EFFECT_DEFENSE_DOWN:
    case EFFECT_DEFENSE_DOWN_2:
        if (atkHpPct >= 70 && gBattleMons[battlerDef].statStages[STAT_DEF] <= 4)
        {
            if ((Random() % 256) >= 50) score -= 2;
        }
        else if ((Random() % 256) >= 50)
            score -= 2;
        if (defHpPct <= 70)
            score -= 2;
        break;

    case EFFECT_SPEED_DOWN:
    case EFFECT_SPEED_DOWN_2:
        if (faster) score -= 3;
        else if ((Random() % 100) >= 70) score += 2;
        break;

    case EFFECT_SPECIAL_ATTACK_DOWN:
    case EFFECT_SPECIAL_ATTACK_DOWN_2:
        if (defStgSpAtk == DEFAULT_STAT_STAGE)
            score -= 1;
        if (atkHpPct >= 90)
            score -= 1;
        if (defStgSpAtk <= 4 && (Random() % 256) >= 50)
            score -= 2;
        if (defHpPct <= 70)
            score -= 2;
        if (defType1 != TYPE_FIRE  && defType1 != TYPE_WATER &&
            defType1 != TYPE_GRASS && defType1 != TYPE_ELECTRIC &&
            defType1 != TYPE_PSYCHIC && defType1 != TYPE_ICE &&
            defType1 != TYPE_DRAGON && defType1 != TYPE_DARK &&
            defType2 != TYPE_FIRE  && defType2 != TYPE_WATER &&
            defType2 != TYPE_GRASS && defType2 != TYPE_ELECTRIC &&
            defType2 != TYPE_PSYCHIC && defType2 != TYPE_ICE &&
            defType2 != TYPE_DRAGON && defType2 != TYPE_DARK &&
            (Random() % 256) >= 50)
            score -= 2;
        break;

    case EFFECT_SPECIAL_DEFENSE_DOWN:
    case EFFECT_SPECIAL_DEFENSE_DOWN_2:
        if (atkHpPct >= 70 && gBattleMons[battlerDef].statStages[STAT_SPDEF] <= 4)
        {
            if ((Random() % 256) >= 50) score -= 2;
        }
        else if ((Random() % 256) >= 50)
            score -= 2;
        if (defHpPct <= 70)
            score -= 2;
        break;

    case EFFECT_ACCURACY_DOWN:
    case EFFECT_ACCURACY_DOWN_2:
        if (atkHpPct < 70 || defHpPct <= 70)
        {
            if ((Random() % 100) >= 100) score -= 1;
        }
        if (gBattleMons[battlerAtk].statStages[STAT_ACC] <= 5
            && (Random() % 256) >= 80)
            score -= 2;
        if (defStatus1 & STATUS1_TOXIC_POISON && (Random() % 100) >= 70)
            score += 2;
        if (gStatuses3[battlerDef] & STATUS3_LEECHSEED && (Random() % 100) >= 70)
            score += 2;
        if (gStatuses3[battlerAtk] & STATUS3_ROOTED && (Random() % 256) >= 128)
            score += 1;
        if (defStatus2 & STATUS2_CURSED && (Random() % 100) >= 70)
            score += 2;
        if (atkHpPct <= 70 && gBattleMons[battlerDef].statStages[STAT_ACC] != DEFAULT_STAT_STAGE
            && atkHpPct > 40 && defHpPct > 40
            && (Random() % 100) >= 70)
            score -= 2;
        break;

    case EFFECT_EVASION_DOWN:
    case EFFECT_EVASION_DOWN_2:
        if (atkHpPct >= 70 && defStgEva <= 4)
        {
            if ((Random() % 256) >= 50) score -= 2;
        }
        else if ((Random() % 256) >= 50)
            score -= 2;
        if (defHpPct <= 70)
            score -= 2;
        break;

    // ---- Screens ----
    case EFFECT_LIGHT_SCREEN:
        if (atkHpPct < 50) score -= 2;
        else if (defType1 == TYPE_FIRE || defType1 == TYPE_WATER ||
                 defType1 == TYPE_GRASS || defType1 == TYPE_ELECTRIC ||
                 defType1 == TYPE_PSYCHIC || defType1 == TYPE_ICE ||
                 defType1 == TYPE_DRAGON || defType1 == TYPE_DARK ||
                 defType2 == TYPE_FIRE || defType2 == TYPE_WATER ||
                 defType2 == TYPE_GRASS || defType2 == TYPE_ELECTRIC ||
                 defType2 == TYPE_PSYCHIC || defType2 == TYPE_ICE ||
                 defType2 == TYPE_DRAGON || defType2 == TYPE_DARK)
            { /* good move, no score change */ }
        else if ((Random() % 256) >= 50)
            score -= 2;
        break;

    case EFFECT_REFLECT:
        if (atkHpPct < 50) score -= 2;
        else if (defType1 == TYPE_NORMAL || defType1 == TYPE_FIGHTING ||
                 defType1 == TYPE_FLYING || defType1 == TYPE_POISON ||
                 defType1 == TYPE_GROUND || defType1 == TYPE_ROCK ||
                 defType1 == TYPE_BUG    || defType1 == TYPE_GHOST ||
                 defType1 == TYPE_STEEL  ||
                 defType2 == TYPE_NORMAL || defType2 == TYPE_FIGHTING ||
                 defType2 == TYPE_FLYING || defType2 == TYPE_POISON ||
                 defType2 == TYPE_GROUND || defType2 == TYPE_ROCK ||
                 defType2 == TYPE_BUG    || defType2 == TYPE_GHOST ||
                 defType2 == TYPE_STEEL)
            { /* good move */ }
        else if ((Random() % 256) >= 50)
            score -= 2;
        break;

    // ---- Status conditions ----
    case EFFECT_POISON:
        if (atkHpPct < 50 || defHpPct <= 50)
            score -= 1;
        break;

    case EFFECT_PARALYZE:
        if (!faster)
        {
            if ((Random() % 256) >= 20) score += 3;
        }
        else if (atkHpPct <= 70)
            score -= 1;
        break;

    case EFFECT_SLEEP:
    case EFFECT_TOXIC:
        // Covered by AI_CheckBadMove; CheckViability only adjusts for combos
        if (AI_HasMoveEffect(battlerAtk, EFFECT_SPECIAL_DEFENSE_UP)
            || AI_HasMoveEffect(battlerAtk, EFFECT_PROTECT))
        {
            if ((Random() % 100) >= 60) score += 2;
        }
        break;

    // ---- Recovery ----
    case EFFECT_RESTORE_HP:
    case EFFECT_MORNING_SUN:
    case EFFECT_SYNTHESIS:
    case EFFECT_MOONLIGHT:
    case EFFECT_SOFTBOILED:
        // Bad if: weather hurts, full HP, or slower than target
        if (gBattleWeather & (B_WEATHER_HAIL | B_WEATHER_RAIN | B_WEATHER_SANDSTORM))
            score -= 2;
        if (atkHpPct == 100) score -= 3;
        else if (!faster)
        {
            if (atkHpPct >= 70 && (Random() % 256) >= 30) score -= 3;
            else if (atkHpPct >= 70) score = score;
            else if (atkHpPct < 70)
            {
                // Check if target has Snatch
                if (AI_HasMoveEffect(battlerDef, EFFECT_SNATCH) && (Random() % 100) >= 100)
                    score = score;
                else if ((Random() % 256) >= 20) score += 2;
            }
        }
        else
        {
            if (atkHpPct >= 70 && (Random() % 256) >= 30) score -= 3;
            else if (atkHpPct < 70) score = score;
        }
        break;

    case EFFECT_REST:
        if (!faster)
        {
            if (atkHpPct == 100) { score -= 8; break; }
            if (atkHpPct >= 60 && (Random() % 256) >= 50) { score -= 3; break; }
        }
        else
        {
            if (atkHpPct < 60 || (Random() % 256) >= 50)
            {
                if (atkHpPct >= 70 && (Random() % 256) >= 30) { score -= 3; break; }
            }
        }
        if (AI_HasMoveEffect(battlerDef, EFFECT_SNATCH) && (Random() % 256) >= 50)
            break;
        if ((Random() % 256) >= 10) score += 3;
        break;

    // ---- Combo / misc ----
    case EFFECT_BELLY_DRUM:
        if (atkHpPct < 90) score -= 2;
        break;

    case EFFECT_BATON_PASS:
        // Encourage if any stat is boosted high
        if (atkStgAtk > 8 || atkStgDef > 8 || atkStgSpAtk > 8 || atkStgSpDef > 8 || atkStgEva > 8)
        {
            if (!faster)
            {
                if (atkHpPct > 60 || (Random() % 256) >= 80) score += 2;
            }
            else
            {
                if (atkHpPct < 70 || (Random() % 256) >= 80) score += 2;
            }
        }
        else if (atkStgAtk > 7 || atkStgDef > 7 || atkStgSpAtk > 7 || atkStgSpDef > 7 || atkStgEva > 7)
        {
            // Discourage if not fast and low HP
            if (!faster)
            {
                if (atkHpPct > 60) score -= 2;
            }
            else if (atkHpPct < 70)
                score -= 2;
        }
        else
            score -= 2;
        break;

    case EFFECT_SUBSTITUTE:
        // Score down progressively with lower HP
        if (atkHpPct <= 50) score -= 1;
        if (atkHpPct <= 70) score -= 1;
        if (atkHpPct <= 90) score -= 1;
        // Encourage if target's last move is a status
        if (!faster)
        {
            u16 lastMove = gLastMoves[battlerDef];
            if (lastMove != MOVE_NONE)
            {
                u16 lastEffect = gBattleMoves[lastMove].effect;
                if (lastEffect == EFFECT_SLEEP || lastEffect == EFFECT_TOXIC ||
                    lastEffect == EFFECT_POISON || lastEffect == EFFECT_PARALYZE ||
                    lastEffect == EFFECT_WILL_O_WISP)
                {
                    if (!(defStatus1 & STATUS1_ANY) && (Random() % 100) >= 100)
                        score += 1;
                }
                if (lastEffect == EFFECT_CONFUSE && !(defStatus2 & STATUS2_CONFUSION)
                    && (Random() % 100) >= 100)
                    score += 1;
                if (lastEffect == EFFECT_LEECH_SEED && !(gStatuses3[battlerDef] & STATUS3_LEECHSEED)
                    && (Random() % 100) >= 100)
                    score += 1;
            }
        }
        break;

    case EFFECT_DREAM_EATER:
        if (notVeryEff) score -= 1;
        break;

    case EFFECT_FLAIL:
    // EFFECT_REVERSAL shares the same constant as EFFECT_FLAIL in FireRed
        if (!faster)
        {
            if (atkHpPct > 33) score -= 1;
            else if (atkHpPct > 20) break;
            else if (atkHpPct < 8) score += 1;
            if ((Random() % 100) >= 100) score += 1;
        }
        else
        {
            if (atkHpPct > 60) score -= 1;
            else if (atkHpPct > 40) break;
            if ((Random() % 100) >= 100) score += 1;
        }
        break;

    case EFFECT_DESTINY_BOND:
        score -= 1;
        if (!faster && atkHpPct <= 70)
        {
            if ((Random() % 256) >= 128) score += 1;
            if (atkHpPct <= 50 && (Random() % 256) >= 128) score += 1;
            if (atkHpPct <= 30 && (Random() % 100) >= 100) score += 2;
        }
        break;

    case EFFECT_HIGH_CRITICAL:
        if (!superEff && !notVeryEff && (Random() % 256) >= 128)
            score += 1;
        else if ((superEff) && (Random() % 256) >= 128)
            score += 1;
        break;

    case EFFECT_CONFUSE:
    case EFFECT_FLATTER:
        // Flatter adds small random bonus
        if (effect == EFFECT_FLATTER && (Random() % 256) >= 128)
            score += 1;
        if (defHpPct <= 70)
        {
            if ((Random() % 256) >= 128) score -= 1;
            if (defHpPct <= 50) score -= 1;
            if (defHpPct <= 30) score -= 1;
        }
        break;

    case EFFECT_ROAR:
        // Encourage if target has boosted stats
        if (defStgAtk > 8 || gBattleMons[battlerDef].statStages[STAT_DEF] > 8 ||
            defStgSpAtk > 8 || gBattleMons[battlerDef].statStages[STAT_SPDEF] > 8 ||
            defStgEva > 8)
        {
            if ((Random() % 256) >= 128) score += 2;
        }
        else
            score -= 3;
        break;

    case EFFECT_HAZE:
        // Encourage if user has boosts or target has boosts the other way
        if (atkStgAtk > 8 || atkStgDef > 8 || atkStgSpAtk > 8 ||
            atkStgSpDef > 8 || atkStgEva > 8 ||
            defStgAtk < 4 || gBattleMons[battlerDef].statStages[STAT_DEF] < 4 ||
            defStgSpAtk < 4 || gBattleMons[battlerDef].statStages[STAT_SPDEF] < 4 ||
            gBattleMons[battlerDef].statStages[STAT_ACC] < 4)
        {
            if ((Random() % 256) >= 50) score -= 3;
        }
        if (defStgAtk > 8 || gBattleMons[battlerDef].statStages[STAT_DEF] > 8 ||
            defStgSpAtk > 8 || gBattleMons[battlerDef].statStages[STAT_SPDEF] > 8 ||
            defStgEva > 8 ||
            atkStgAtk < 4 || atkStgDef < 4 || atkStgSpAtk < 4 ||
            atkStgSpDef < 4 || gBattleMons[battlerAtk].statStages[STAT_ACC] < 4)
        {
            if ((Random() % 256) >= 50) score += 3;
        }
        else
        {
            if ((Random() % 256) >= 50) score -= 1;
        }
        break;

    case EFFECT_RECHARGE:
        if (notVeryEff) score -= 1;
        if (!faster)
        {
            if (atkHpPct <= 40) break;
            score -= 1;
        }
        else if (atkHpPct >= 60)
            score -= 1;
        break;

    case EFFECT_DISABLE:
        if (!faster)
        {
            u16 lastMove = gLastMoves[battlerDef];
            if (lastMove != MOVE_NONE && gBattleMoves[lastMove].power > 0)
                score += 1;
            else if ((Random() % 100) >= 100)
                score -= 1;
        }
        break;

    case EFFECT_ENCORE:
        {
            u16 lastMove = gLastMoves[battlerDef];
            u8 lastEffect = (lastMove != MOVE_NONE) ? gBattleMoves[lastMove].effect : 0xFF;
            // Check encouraged effects to encore
            if (gDisableStructs[battlerDef].disabledMove != MOVE_NONE ||
                (!faster && (lastEffect == EFFECT_ATTACK_UP || lastEffect == EFFECT_DEFENSE_UP ||
                             lastEffect == EFFECT_SPEED_UP  || lastEffect == EFFECT_SPECIAL_ATTACK_UP ||
                             lastEffect == EFFECT_HAZE || lastEffect == EFFECT_PROTECT ||
                             lastEffect == EFFECT_REST || lastEffect == EFFECT_TOXIC ||
                             lastEffect == EFFECT_SLEEP || lastEffect == EFFECT_SPLASH)))
            {
                if ((Random() % 256) >= 30) score += 3;
            }
            else
                score -= 2;
        }
        break;

    case EFFECT_SNORE:
    case EFFECT_SLEEP_TALK:
        score += 2;
        break;

    case EFFECT_PAIN_SPLIT:
        if (defHpPct >= 80)
        {
            if (!faster && atkHpPct <= 40) score += 1;
            else if (faster && atkHpPct <= 60) score -= 1;
            else score -= 1;
        }
        else
            score -= 1;
        break;

    case EFFECT_LOCK_ON:
        if ((Random() % 256) >= 128) score += 2;
        break;

    case EFFECT_PROTECT:
    case EFFECT_ENDURE:
        if (gDisableStructs[battlerAtk].protectUses > 1) { score -= 2; break; }
        if (atkStatus2 & STATUS2_CURSED || gStatuses3[battlerAtk] & STATUS3_LEECHSEED ||
            atkStatus2 & STATUS2_INFATUATION || gStatuses3[battlerAtk] & STATUS3_YAWN ||
            atkStatus1 & STATUS1_TOXIC_POISON || gStatuses3[battlerAtk] & STATUS3_PERISH_SONG)
        {
            score += 2;
        }
        if (defStatus2 & STATUS2_CURSED || gStatuses3[battlerDef] & STATUS3_LEECHSEED ||
            defStatus2 & STATUS2_INFATUATION || gStatuses3[battlerDef] & STATUS3_YAWN ||
            defStatus1 & STATUS1_TOXIC_POISON || gStatuses3[battlerDef] & STATUS3_PERISH_SONG)
        {
            score += 2;
        }
        if (gDisableStructs[battlerAtk].protectUses > 0) score -= 1;
        if (gDisableStructs[battlerAtk].protectUses > 0 && (Random() % 256) >= 128) score -= 1;
        break;

    case EFFECT_BIDE:
        if (atkHpPct <= 90) score -= 2;
        break;

    case EFFECT_SUPER_FANG:
        if (defHpPct <= 50) score -= 1;
        break;

    case EFFECT_TRAP:
        if (defStatus1 & STATUS1_TOXIC_POISON || defStatus2 & STATUS2_CURSED ||
            gStatuses3[battlerDef] & STATUS3_PERISH_SONG || defStatus2 & STATUS2_INFATUATION)
        {
            if ((Random() % 256) >= 128) score += 1;
        }
        break;

    case EFFECT_OHKO:
        // neutral score — AI_CheckBadMove already filtered impossible cases
        break;

    case EFFECT_HEAL_BELL:
    // EFFECT_AROMATHERAPY maps to EFFECT_HEAL_BELL in FireRed
        // Only good if someone is statused
        if (!(defStatus1 & STATUS1_ANY))
            score -= 5;
        break;

    case EFFECT_CURSE:
        if (atkType1 == TYPE_GHOST || atkType2 == TYPE_GHOST)
        {
            if (atkHpPct <= 80) score -= 1;
        }
        else
        {
            if (atkStgDef <= 9 && (Random() % 256) >= 128) score += 1;
            if (atkStgDef <= 7 && (Random() % 256) >= 128) score += 1;
            if (atkStgDef <= 6 && (Random() % 256) >= 128) score += 1;
        }
        break;

    case EFFECT_FOCUS_ENERGY:
        score += 0; // handled by CheckBadMove; viability is neutral
        break;

    // EFFECT_SOLAR_BEAM and EFFECT_SKULL_BASH are used for two-turn moves.
    case EFFECT_SOLAR_BEAM:
    case EFFECT_SKULL_BASH:
        if (notVeryEff) score -= 2;
        if (AI_HasMoveEffect(battlerDef, EFFECT_PROTECT)) score -= 2;
        if (atkHpPct <= 38) score -= 1;
        break;

    case EFFECT_SEMI_INVULNERABLE:
        if (AI_HasMoveEffect(battlerDef, EFFECT_PROTECT)) { score -= 1; break; }
        if (defStatus1 & STATUS1_TOXIC_POISON || defStatus2 & STATUS2_CURSED ||
            gStatuses3[battlerDef] & STATUS3_LEECHSEED)
        {
            if ((Random() % 256) >= 80) score += 1;
        }
        break;

    case EFFECT_FAKE_OUT:
        score += 2;
        break;

    case EFFECT_SPIT_UP:
        if (gDisableStructs[battlerAtk].stockpileCounter >= 2 && (Random() % 256) >= 80)
            score += 2;
        break;

    case EFFECT_RAIN_DANCE:
        if (atkHpPct < 40) score -= 1;
        else if (gBattleWeather & (B_WEATHER_HAIL | B_WEATHER_SUN | B_WEATHER_SANDSTORM))
            score += 1;
        else if (atkAbility == ABILITY_SWIFT_SWIM || atkAbility == ABILITY_RAIN_DISH)
            score += 1;
        break;

    case EFFECT_SUNNY_DAY:
        if (atkHpPct < 40) score -= 1;
        else if (gBattleWeather & (B_WEATHER_HAIL | B_WEATHER_RAIN | B_WEATHER_SANDSTORM))
            score += 1;
        break;

    case EFFECT_HAIL:
        if (atkHpPct < 40) score -= 1;
        else if (gBattleWeather & (B_WEATHER_SUN | B_WEATHER_RAIN | B_WEATHER_SANDSTORM))
            score += 1;
        break;

    case EFFECT_DRAGON_DANCE:
        if (!faster)
        {
            if (atkHpPct > 50) score -= 1;
        }
        else if ((Random() % 256) >= 128)
            score += 1;
        break;

    case EFFECT_BULK_UP:
    case EFFECT_CALM_MIND:
    case EFFECT_COSMIC_POWER:
        // Already handled by CheckBadMove — these are neutral in Viability
        break;

    case EFFECT_FACADE:
        // BUG in original: checks target status, should be user status
        // We port it faithfully (target)
        if (defStatus1 & (STATUS1_POISON | STATUS1_BURN | STATUS1_PARALYSIS | STATUS1_TOXIC_POISON))
            score += 1;
        break;

    case EFFECT_FOCUS_PUNCH:
        if (notVeryEff) score -= 1;
        else if ((defStatus1 & STATUS1_SLEEP) || (defStatus2 & STATUS2_INFATUATION) ||
                 (defStatus2 & STATUS2_CONFUSION))
        {
            if ((Random() % 100) >= 100) score += 1;
        }
        else
        {
            if (!gDisableStructs[battlerAtk].isFirstTurn && (Random() % 100) >= 100)
                score += 1;
        }
        break;

    case EFFECT_SUPERPOWER:
        if (notVeryEff || atkStgAtk <= 6) score -= 1;
        else if (!faster && atkHpPct <= 40) score += 0;
        else if (faster && atkHpPct < 60) break;
        else score -= 1;
        break;

    case EFFECT_COUNTER:
        if ((defStatus1 & STATUS1_SLEEP) || (defStatus2 & STATUS2_INFATUATION) ||
            (defStatus2 & STATUS2_CONFUSION))
        {
            score -= 1; break;
        }
        if (atkHpPct <= 30 || (Random() % 256) >= 10) score -= 1;
        if (atkHpPct <= 50 && (Random() % 100) >= 100) score -= 1;
        break;

    case EFFECT_MIRROR_COAT:
        if ((defStatus1 & STATUS1_SLEEP) || (defStatus2 & STATUS2_INFATUATION) ||
            (defStatus2 & STATUS2_CONFUSION))
        {
            score -= 1; break;
        }
        if (atkHpPct <= 30 || (Random() % 256) >= 10) score -= 1;
        if (atkHpPct <= 50 && (Random() % 100) >= 100) score -= 1;
        break;

    case EFFECT_ENDEAVOR:
        if (defHpPct >= 70) score -= 1;
        else if (!faster && atkHpPct <= 40) score += 1;
        else if (faster && atkHpPct <= 50) score += 1;
        else score -= 1;
        break;

    case EFFECT_ERUPTION:
    // EFFECT_WATER_SPOUT maps to EFFECT_ERUPTION in FireRed
        if (notVeryEff) score -= 1;
        else if (!faster && defHpPct <= 50) score -= 1;
        else if (faster && defHpPct <= 70) score -= 1;
        break;

    case EFFECT_IMPRISON:
        if (!gDisableStructs[battlerAtk].isFirstTurn && (Random() % 100) >= 100)
            score += 2;
        break;

    case EFFECT_REFRESH:
        if (defHpPct < 50) score -= 1;
        break;

    case EFFECT_MUD_SPORT:
        if (atkHpPct >= 50 && (defType1 == TYPE_ELECTRIC || defType2 == TYPE_ELECTRIC))
            score += 1;
        else
            score -= 1;
        break;

    case EFFECT_WATER_SPORT:
        if (atkHpPct >= 50 && (defType1 == TYPE_FIRE || defType2 == TYPE_FIRE))
            score += 1;
        else
            score -= 1;
        break;
    }

    return score;
}

// ============================================================================
// AI_TryToFaint (flag bit 2)
// Boosts score of moves that can KO the target this turn.
// Uses AI_CalcDamage for full damage estimation.
// ============================================================================
static s32 AI_TryToFaint(u8 battlerAtk, u8 battlerDef, u16 move, s32 score)
{
    u8 typeFlags;
    s32 dmg;

    if (gBattleMoves[move].power < 2)
        return score;

    dmg = AI_CalcDamage(move, battlerAtk, battlerDef, &typeFlags);

    if (dmg == 0)
        return score;

    // Can we KO?
    if (gBattleMons[battlerDef].hp <= dmg)
    {
        // Prefer priority move if we'd be outsped (it gets the kill safely)
        if (gBattleMoves[move].priority > 0 && !AI_IsFaster(battlerAtk, battlerDef, move))
            return score + 7;
        return score + 5;
    }

    return score;
}

// ============================================================================
// AI_SetupFirstTurn (flag bit 3)
// On turn 0 only: encourage stat-altering setup moves.
// Direct port of AI_SetupFirstTurn (lines 2791-2858).
// ============================================================================
static s32 AI_SetupFirstTurn(u8 battlerAtk, u8 battlerDef, u16 move, s32 score)
{
    static const u16 sSetupEffects[] = {
        EFFECT_ATTACK_UP, EFFECT_DEFENSE_UP, EFFECT_SPEED_UP,
        EFFECT_SPECIAL_ATTACK_UP, EFFECT_SPECIAL_DEFENSE_UP,
        EFFECT_ACCURACY_UP, EFFECT_EVASION_UP,
        EFFECT_ATTACK_DOWN, EFFECT_DEFENSE_DOWN, EFFECT_SPEED_DOWN,
        EFFECT_SPECIAL_ATTACK_DOWN, EFFECT_SPECIAL_DEFENSE_DOWN,
        EFFECT_ACCURACY_DOWN, EFFECT_EVASION_DOWN,
        EFFECT_CONVERSION, EFFECT_LIGHT_SCREEN,
        EFFECT_SPECIAL_DEFENSE_UP_2, EFFECT_FOCUS_ENERGY, EFFECT_CONFUSE,
        EFFECT_ATTACK_UP_2, EFFECT_DEFENSE_UP_2, EFFECT_SPEED_UP_2,
        EFFECT_SPECIAL_ATTACK_UP_2, EFFECT_ACCURACY_UP_2, EFFECT_EVASION_UP_2,
        EFFECT_ATTACK_DOWN_2, EFFECT_DEFENSE_DOWN_2, EFFECT_SPEED_DOWN_2,
        EFFECT_SPECIAL_ATTACK_DOWN_2, EFFECT_SPECIAL_DEFENSE_DOWN_2,
        EFFECT_ACCURACY_DOWN_2, EFFECT_EVASION_DOWN_2,
        EFFECT_REFLECT, EFFECT_POISON, EFFECT_PARALYZE, EFFECT_SUBSTITUTE,
        EFFECT_LEECH_SEED, EFFECT_MINIMIZE, EFFECT_CURSE,
        EFFECT_SWAGGER, EFFECT_YAWN, EFFECT_DEFENSE_CURL,
        EFFECT_TORMENT, EFFECT_FLATTER, EFFECT_WILL_O_WISP, EFFECT_INGRAIN,
        EFFECT_IMPRISON, EFFECT_TEETER_DANCE, EFFECT_TICKLE,
        EFFECT_COSMIC_POWER, EFFECT_BULK_UP, EFFECT_CALM_MIND, EFFECT_CAMOUFLAGE,
        EFFECT_DRAGON_DANCE, 0xFFFF
    };
    u16 effect = gBattleMoves[move].effect;
    u8 i;

    if (gBattleResults.battleTurnCounter != 0)
        return score;

    for (i = 0; sSetupEffects[i] != 0xFFFF; i++)
    {
        if (effect == sSetupEffects[i])
        {
            if ((Random() % 256) >= 80)
                score += 2;
            return score;
        }
    }
    return score;
}

// ============================================================================
// AI_Risky (flag bit 4)
// Randomly encourages chaotic / high-risk moves.
// Direct port of AI_Risky (lines 2869-2898).
// ============================================================================
static s32 AI_Risky(u8 battlerAtk, u8 battlerDef, u16 move, s32 score)
{
    static const u16 sRiskyEffects[] = {
        EFFECT_SLEEP, EFFECT_EXPLOSION, EFFECT_MIRROR_MOVE, EFFECT_OHKO,
        EFFECT_HIGH_CRITICAL, EFFECT_CONFUSE, EFFECT_METRONOME,
        EFFECT_PSYWAVE, EFFECT_COUNTER, EFFECT_DESTINY_BOND,
        EFFECT_SWAGGER, EFFECT_ATTRACT, EFFECT_PRESENT,
        EFFECT_ALL_STATS_UP_HIT, EFFECT_BELLY_DRUM, EFFECT_MIRROR_COAT,
        EFFECT_FOCUS_PUNCH, EFFECT_REVENGE, EFFECT_TEETER_DANCE, 0xFFFF
    };
    u16 effect = gBattleMoves[move].effect;
    u8 i;

    for (i = 0; sRiskyEffects[i] != 0xFFFF; i++)
    {
        if (effect == sRiskyEffects[i])
        {
            if ((Random() % 256) >= 128)
                score += 2;
            return score;
        }
    }
    return score;
}

// ============================================================================
// AI_PreferStrongestMove (flag bit 5)
// Randomly boosts discouraged (underpower) moves.
// Port of AI_PreferStrongestMove (lines 2860-2867).
// ============================================================================
static s32 AI_PreferStrongestMove(u8 battlerAtk, u8 battlerDef, u16 move, s32 score)
{
    // "MOVE_POWER_DISCOURAGED" in the ASM means the move has no power (power == 0)
    // and the AI would not normally prefer it.
    // The script checks get_how_powerful_move_is == MOVE_POWER_DISCOURAGED
    // then randomly adds +2. We mirror that: if non-damaging, randomly boost.
    if (gBattleMoves[move].power == 0 && (Random() % 100) >= 100)
        score += 2;
    return score;
}

// ============================================================================
// AI_PreferBatonPass (flag bit 6)
// Encourages setup moves when the user also has Baton Pass.
// Port of AI_PreferBatonPass (lines 2900-2947).
// ============================================================================
static s32 AI_PreferBatonPass(u8 battlerAtk, u8 battlerDef, u16 move, s32 score)
{
    if (AI_CountAlivePokemon(battlerAtk) == 0)
        return score;

    // Only applies to non-damaging (setup) moves
    if (gBattleMoves[move].power > 0)
        return score;

    // If user has Baton Pass, randomly boost setup moves
    if (AI_HasMoveEffect(battlerAtk, EFFECT_BATON_PASS))
    {
        if ((Random() % 256) >= 20)
            score += 3;
    }
    else
    {
        if ((Random() % 256) >= 80)
            score = score; // no change, just mirrors ASM fallthrough
    }
    return score;
}

// ============================================================================
// AI_DoubleBattle (flag bit 7)
// Empty in FRLG — expanded logic exists only in Emerald.
// ============================================================================
static s32 AI_DoubleBattle(u8 battlerAtk, u8 battlerDef, u16 move, s32 score)
{
    return score;
}

// ============================================================================
// AI_HPAware (flag bit 8)
// Penalizes setup moves based on user/target HP percentage.
// Direct port of AI_HPAware (lines 2953-3260).
// ============================================================================
static s32 AI_HPAware(u8 battlerAtk, u8 battlerDef, u16 move, s32 score)
{
    u16 effect = gBattleMoves[move].effect;
    u8 atkHpPct = gBattleMons[battlerAtk].hp * 100 / gBattleMons[battlerAtk].maxHP;
    u8 defHpPct = gBattleMons[battlerDef].hp * 100 / gBattleMons[battlerDef].maxHP;

    static const u8 sHighHPDiscouraged[] = {
        EFFECT_EXPLOSION, EFFECT_RESTORE_HP, EFFECT_REST, EFFECT_DESTINY_BOND,
        EFFECT_FLAIL, EFFECT_ENDURE, EFFECT_MORNING_SUN, EFFECT_SYNTHESIS,
        EFFECT_MOONLIGHT, EFFECT_SOFTBOILED, EFFECT_MEMENTO, EFFECT_GRUDGE,
        EFFECT_OVERHEAT, 0xFF
    };
    static const u8 sMediumHPDiscouraged[] = {
        EFFECT_EXPLOSION,
        EFFECT_ATTACK_UP, EFFECT_DEFENSE_UP, EFFECT_SPEED_UP,
        EFFECT_SPECIAL_ATTACK_UP, EFFECT_SPECIAL_DEFENSE_UP,
        EFFECT_ACCURACY_UP, EFFECT_EVASION_UP,
        EFFECT_ATTACK_DOWN, EFFECT_DEFENSE_DOWN, EFFECT_SPEED_DOWN,
        EFFECT_SPECIAL_ATTACK_DOWN, EFFECT_SPECIAL_DEFENSE_DOWN,
        EFFECT_ACCURACY_DOWN, EFFECT_EVASION_DOWN,
        EFFECT_BIDE, EFFECT_CONVERSION, EFFECT_LIGHT_SCREEN, EFFECT_MIST,
        EFFECT_FOCUS_ENERGY,
        EFFECT_ATTACK_UP_2, EFFECT_DEFENSE_UP_2, EFFECT_SPEED_UP_2,
        EFFECT_SPECIAL_ATTACK_UP_2, EFFECT_SPECIAL_DEFENSE_UP_2,
        EFFECT_ACCURACY_UP_2, EFFECT_EVASION_UP_2,
        EFFECT_ATTACK_DOWN_2, EFFECT_DEFENSE_DOWN_2, EFFECT_SPEED_DOWN_2,
        EFFECT_SPECIAL_ATTACK_DOWN_2, EFFECT_SPECIAL_DEFENSE_DOWN_2,
        EFFECT_ACCURACY_DOWN_2, EFFECT_EVASION_DOWN_2,
        EFFECT_CONVERSION_2, EFFECT_SAFEGUARD, EFFECT_BELLY_DRUM,
        EFFECT_TICKLE, EFFECT_COSMIC_POWER, EFFECT_BULK_UP,
        EFFECT_CALM_MIND, EFFECT_DRAGON_DANCE, 0xFF
    };
    static const u8 sLowHPDiscouraged[] = {
        EFFECT_ATTACK_UP, EFFECT_DEFENSE_UP, EFFECT_SPEED_UP,
        EFFECT_SPECIAL_ATTACK_UP, EFFECT_SPECIAL_DEFENSE_UP,
        EFFECT_ACCURACY_UP, EFFECT_EVASION_UP,
        EFFECT_ATTACK_DOWN, EFFECT_DEFENSE_DOWN, EFFECT_SPEED_DOWN,
        EFFECT_SPECIAL_ATTACK_DOWN, EFFECT_SPECIAL_DEFENSE_DOWN,
        EFFECT_ACCURACY_DOWN, EFFECT_EVASION_DOWN,
        EFFECT_BIDE, EFFECT_CONVERSION, EFFECT_LIGHT_SCREEN, EFFECT_MIST,
        EFFECT_FOCUS_ENERGY,
        EFFECT_ATTACK_UP_2, EFFECT_DEFENSE_UP_2, EFFECT_SPEED_UP_2,
        EFFECT_SPECIAL_ATTACK_UP_2, EFFECT_SPECIAL_DEFENSE_UP_2,
        EFFECT_ACCURACY_UP_2, EFFECT_EVASION_UP_2,
        EFFECT_ATTACK_DOWN_2, EFFECT_DEFENSE_DOWN_2, EFFECT_SPEED_DOWN_2,
        EFFECT_SPECIAL_ATTACK_DOWN_2, EFFECT_SPECIAL_DEFENSE_DOWN_2,
        EFFECT_ACCURACY_DOWN_2, EFFECT_EVASION_DOWN_2,
        EFFECT_RAGE, EFFECT_CONVERSION_2, EFFECT_LOCK_ON,
        EFFECT_SAFEGUARD, EFFECT_BELLY_DRUM, EFFECT_PSYCH_UP,
        EFFECT_MIRROR_COAT, EFFECT_SOLAR_BEAM, EFFECT_ERUPTION,
        EFFECT_TICKLE, EFFECT_COSMIC_POWER, EFFECT_BULK_UP,
        EFFECT_CALM_MIND, EFFECT_DRAGON_DANCE, 0xFF
    };
    static const u8 sTargetMediumHPDiscouraged[] = {
        EFFECT_ATTACK_UP, EFFECT_DEFENSE_UP, EFFECT_SPEED_UP,
        EFFECT_SPECIAL_ATTACK_UP, EFFECT_SPECIAL_DEFENSE_UP,
        EFFECT_ACCURACY_UP, EFFECT_EVASION_UP,
        EFFECT_ATTACK_DOWN, EFFECT_DEFENSE_DOWN, EFFECT_SPEED_DOWN,
        EFFECT_SPECIAL_ATTACK_DOWN, EFFECT_SPECIAL_DEFENSE_DOWN,
        EFFECT_ACCURACY_DOWN, EFFECT_EVASION_DOWN,
        EFFECT_MIST, EFFECT_FOCUS_ENERGY,
        EFFECT_ATTACK_UP_2, EFFECT_DEFENSE_UP_2, EFFECT_SPEED_UP_2,
        EFFECT_SPECIAL_ATTACK_UP_2, EFFECT_SPECIAL_DEFENSE_UP_2,
        EFFECT_ACCURACY_UP_2, EFFECT_EVASION_UP_2,
        EFFECT_ATTACK_DOWN_2, EFFECT_DEFENSE_DOWN_2, EFFECT_SPEED_DOWN_2,
        EFFECT_SPECIAL_ATTACK_DOWN_2, EFFECT_SPECIAL_DEFENSE_DOWN_2,
        EFFECT_ACCURACY_DOWN_2, EFFECT_EVASION_DOWN_2,
        EFFECT_POISON, EFFECT_PAIN_SPLIT, EFFECT_PERISH_SONG, EFFECT_SAFEGUARD,
        EFFECT_TICKLE, EFFECT_COSMIC_POWER, EFFECT_BULK_UP,
        EFFECT_CALM_MIND, EFFECT_DRAGON_DANCE, 0xFF
    };
    static const u8 sTargetLowHPDiscouraged[] = {
        EFFECT_SLEEP, EFFECT_EXPLOSION,
        EFFECT_ATTACK_UP, EFFECT_DEFENSE_UP, EFFECT_SPEED_UP,
        EFFECT_SPECIAL_ATTACK_UP, EFFECT_SPECIAL_DEFENSE_UP,
        EFFECT_ACCURACY_UP, EFFECT_EVASION_UP,
        EFFECT_ATTACK_DOWN, EFFECT_DEFENSE_DOWN, EFFECT_SPEED_DOWN,
        EFFECT_SPECIAL_ATTACK_DOWN, EFFECT_SPECIAL_DEFENSE_DOWN,
        EFFECT_ACCURACY_DOWN, EFFECT_EVASION_DOWN,
        EFFECT_BIDE, EFFECT_CONVERSION, EFFECT_TOXIC, EFFECT_LIGHT_SCREEN,
        EFFECT_OHKO, EFFECT_SUPER_FANG, EFFECT_MIST, EFFECT_FOCUS_ENERGY,
        EFFECT_CONFUSE,
        EFFECT_ATTACK_UP_2, EFFECT_DEFENSE_UP_2, EFFECT_SPEED_UP_2,
        EFFECT_SPECIAL_ATTACK_UP_2, EFFECT_SPECIAL_DEFENSE_UP_2,
        EFFECT_ACCURACY_UP_2, EFFECT_EVASION_UP_2,
        EFFECT_ATTACK_DOWN_2, EFFECT_DEFENSE_DOWN_2, EFFECT_SPEED_DOWN_2,
        EFFECT_SPECIAL_ATTACK_DOWN_2, EFFECT_SPECIAL_DEFENSE_DOWN_2,
        EFFECT_ACCURACY_DOWN_2, EFFECT_EVASION_DOWN_2,
        EFFECT_POISON, EFFECT_PARALYZE, EFFECT_PAIN_SPLIT,
        EFFECT_CONVERSION_2, EFFECT_LOCK_ON, EFFECT_SAFEGUARD,
        EFFECT_TICKLE, EFFECT_COSMIC_POWER, EFFECT_BULK_UP,
        EFFECT_CALM_MIND, EFFECT_DRAGON_DANCE, 0xFF
    };

    const u8 *userList;
    const u8 *targetList;
    u8 i;

    // Select user HP bracket list
    if (atkHpPct > 70)      userList = sHighHPDiscouraged;
    else if (atkHpPct > 30) userList = sMediumHPDiscouraged;
    else                    userList = sLowHPDiscouraged;

    for (i = 0; userList[i] != 0xFF; i++)
    {
        if (effect == userList[i])
        {
            if ((Random() % 256) >= 50)
                score -= 2;
            break;
        }
    }

    // Select target HP bracket list
    if (defHpPct > 70)      targetList = NULL; // sTargetHighHPDiscouraged is empty in FRLG
    else if (defHpPct > 30) targetList = sTargetMediumHPDiscouraged;
    else                    targetList = sTargetLowHPDiscouraged;

    if (targetList != NULL)
    {
        for (i = 0; targetList[i] != 0xFF; i++)
        {
            if (effect == targetList[i])
            {
                if ((Random() % 256) >= 50)
                    score -= 2;
                break;
            }
        }
    }

    return score;
}

// ============================================================================
// AI_SmartSwitching (flag bit 9)
// This is a scoring-loop no-op. The actual switch decision happens in
// BattleAI_ChooseMoveOrAction() BEFORE move scoring begins. If the switch
// fires there, we return B_ACTION_SWITCH immediately and never reach here.
// This slot exists only to prevent a null-pointer call if the flag bit
// somehow survives into the scoring loop iteration.
// ============================================================================
static s32 AI_SmartSwitching(u8 battlerAtk, u8 battlerDef, u16 move, s32 score)
{
    (void)battlerAtk; (void)battlerDef; (void)move;
    return score;
}

// ============================================================================
// AI_Roaming / AI_Safari / AI_FirstBattle (flags 20-22)
// These apply to wild battles only. No move scoring is done.
// ============================================================================
static s32 AI_Roaming(u8 battlerAtk, u8 battlerDef, u16 move, s32 score)
{
    return score;
}

static s32 AI_Safari(u8 battlerAtk, u8 battlerDef, u16 move, s32 score)
{
    return score;
}

static s32 AI_FirstBattle(u8 battlerAtk, u8 battlerDef, u16 move, s32 score)
{
    return score;
}
