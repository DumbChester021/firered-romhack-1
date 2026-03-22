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
    // [9-19] = NULL (implicitly, since C zero-initializes)
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
    u8 effect = gBattleMoves[move].effect;
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
// AI_CheckViability (flag bit 1) — STUB, Phase 4 next
// ============================================================================
static s32 AI_CheckViability(u8 battlerAtk, u8 battlerDef, u16 move, s32 score)
{
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
// AI_SetupFirstTurn (flag bit 3) — STUB
// ============================================================================
static s32 AI_SetupFirstTurn(u8 battlerAtk, u8 battlerDef, u16 move, s32 score)
{
    return score;
}

// ============================================================================
// AI_Risky (flag bit 4) — STUB
// ============================================================================
static s32 AI_Risky(u8 battlerAtk, u8 battlerDef, u16 move, s32 score)
{
    return score;
}

// ============================================================================
// AI_PreferStrongestMove (flag bit 5) — STUB
// ============================================================================
static s32 AI_PreferStrongestMove(u8 battlerAtk, u8 battlerDef, u16 move, s32 score)
{
    return score;
}

// ============================================================================
// AI_PreferBatonPass (flag bit 6) — STUB
// ============================================================================
static s32 AI_PreferBatonPass(u8 battlerAtk, u8 battlerDef, u16 move, s32 score)
{
    return score;
}

// ============================================================================
// AI_DoubleBattle (flag bit 7) — STUB
// ============================================================================
static s32 AI_DoubleBattle(u8 battlerAtk, u8 battlerDef, u16 move, s32 score)
{
    return score;
}

// ============================================================================
// AI_HPAware (flag bit 8) — STUB
// ============================================================================
static s32 AI_HPAware(u8 battlerAtk, u8 battlerDef, u16 move, s32 score)
{
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
