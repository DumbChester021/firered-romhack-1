// RHH source: pokeemerald-expansion/src/battle_ai_field_statuses.c
// Port of WeatherChecker/FieldStatusChecker AI infrastructure.
// Gen3 adaptations:
//   - B_WEATHER_ICY_ANY  = B_WEATHER_HAIL (no snow in Gen3)
//   - B_WEATHER_PRIMAL_ANY = 0 (no primal weather)
//   - Terrain (Gen6+): BenefitsFrom*Terrain stubs pending struct Volatiles migration (.yawn)
//   - HOLD_EFFECT_UTILITY_UMBRELLA (Gen8+): #ifdef'd
//   - HOLD_EFFECT_SAFETY_GOGGLES (Gen4+): #ifdef'd
//   - Gen4+ abilities (SWIFT_SWIM, CHLOROPHYLL, etc.): all defined in our abilities.h
//   - IS_BATTLER_ANY_TYPE → three separate IS_BATTLER_OF_TYPE checks

#include "global.h"
#include "battle.h"
#include "battle_ai_field_statuses.h"
#include "battle_ai_util.h"
#include "battle_ai_main.h"
#include "pokemon.h"
#include "constants/abilities.h"
#include "constants/battle_ai.h"
#include "constants/battle_move_effects.h"
#include "constants/moves.h"

// Forward declarations for static helpers
static enum FieldEffectOutcome BenefitsFromSun(u8 battler);
static enum FieldEffectOutcome BenefitsFromSandstorm(u8 battler);
static enum FieldEffectOutcome BenefitsFromHailOrSnow(u8 battler, u32 weather);
static enum FieldEffectOutcome BenefitsFromRain(u8 battler);
static enum FieldEffectOutcome BenefitsFromElectricTerrain(u8 battler);
static enum FieldEffectOutcome BenefitsFromGrassyTerrain(u8 battler);
static enum FieldEffectOutcome BenefitsFromMistyTerrain(u8 battler);
static enum FieldEffectOutcome BenefitsFromPsychicTerrain(u8 battler);
static enum FieldEffectOutcome BenefitsFromGravity(u8 battler);
static enum FieldEffectOutcome BenefitsFromTrickRoom(u8 battler);
static bool32 DoesAbilityBenefitFromWeather(u8 ability, u32 weather);
static bool32 IsLightSensitiveMove(u16 move);
static bool32 HasLightSensitiveMove(u8 battler);

// RHH: WeatherChecker (src/battle_ai_field_statuses.c:65-101)
// Checks if a battler (and optionally its double battle partner) benefit from the given weather.
// Gen3: B_WEATHER_PRIMAL_ANY = 0, so IsWeatherActive(0) is always WEATHER_INACTIVE.
bool32 WeatherChecker(u8 battler, u32 weather, enum FieldEffectOutcome desiredResult)
{
    if (IsWeatherActive(B_WEATHER_PRIMAL_ANY) != WEATHER_INACTIVE)
        return (FIELD_EFFECT_BLOCKED == desiredResult);

    enum FieldEffectOutcome result = FIELD_EFFECT_NEUTRAL;
    enum FieldEffectOutcome firstResult = FIELD_EFFECT_NEUTRAL;

    u32 battlersOnSide = 1;
    if (HasPartner(battler))
        battlersOnSide = 2;

    for (u32 battlerIndex = 0; battlerIndex < battlersOnSide; battlerIndex++)
    {
        if (weather & B_WEATHER_RAIN)
            result = BenefitsFromRain(battler);
        else if (weather & B_WEATHER_SUN)
            result = BenefitsFromSun(battler);
        else if (weather & B_WEATHER_SANDSTORM)
            result = BenefitsFromSandstorm(battler);
        else if (weather & B_WEATHER_ICY_ANY)
            result = BenefitsFromHailOrSnow(battler, weather);

        battler = BATTLE_PARTNER(battler);

        if (result != FIELD_EFFECT_NEUTRAL)
        {
            if ((weather & B_WEATHER_DAMAGING_ANY) && battlerIndex == 0 && battlersOnSide == 2)
                firstResult = result;
        }
    }
    if (firstResult != FIELD_EFFECT_NEUTRAL)
        return (firstResult == result) && (result == desiredResult);
    return (result == desiredResult);
}

// RHH: FieldStatusChecker (src/battle_ai_field_statuses.c:102-142)
// Gen3: all terrain/gravity/trick-room BenefitsFrom* stubs return FIELD_EFFECT_NEUTRAL.
bool32 FieldStatusChecker(u8 battler, u32 fieldStatus, enum FieldEffectOutcome desiredResult)
{
    enum FieldEffectOutcome result = FIELD_EFFECT_NEUTRAL;
    enum FieldEffectOutcome firstResult = FIELD_EFFECT_NEUTRAL;

    u32 battlersOnSide = 1;
    if (HasPartner(battler))
        battlersOnSide = 2;

    for (u32 battlerIndex = 0; battlerIndex < battlersOnSide; battlerIndex++)
    {
        if (fieldStatus & STATUS_FIELD_ELECTRIC_TERRAIN)
            result = BenefitsFromElectricTerrain(battler);
        if (fieldStatus & STATUS_FIELD_GRASSY_TERRAIN)
            result = BenefitsFromGrassyTerrain(battler);
        if (fieldStatus & STATUS_FIELD_MISTY_TERRAIN)
            result = BenefitsFromMistyTerrain(battler);
        if (fieldStatus & STATUS_FIELD_PSYCHIC_TERRAIN)
            result = BenefitsFromPsychicTerrain(battler);
        if (fieldStatus & STATUS_FIELD_GRAVITY)
            result = BenefitsFromGravity(battler);
        if (fieldStatus & STATUS_FIELD_TRICK_ROOM)
            result = BenefitsFromTrickRoom(battler);

        battler = BATTLE_PARTNER(battler);

        if (result != FIELD_EFFECT_NEUTRAL)
        {
            if ((fieldStatus & STATUS_FIELD_TRICK_ROOM) && battlerIndex == 0 && battlersOnSide == 2)
                firstResult = result;
        }
    }
    if (firstResult != FIELD_EFFECT_NEUTRAL)
        return (firstResult == result) && (result == desiredResult);
    return (result == desiredResult);
}

// RHH: DoesAbilityBenefitFromWeather (src/battle_ai_field_statuses.c:144-182, static)
// Gen4+ abilities included — all defined in our abilities.h.
static bool32 DoesAbilityBenefitFromWeather(u8 ability, u32 weather)
{
    switch (ability)
    {
    case ABILITY_FORECAST:
        return (weather & (B_WEATHER_RAIN | B_WEATHER_SUN | B_WEATHER_ICY_ANY)) != 0;
    case ABILITY_SAND_VEIL:
        return (weather & B_WEATHER_SANDSTORM) != 0;
    case ABILITY_SWIFT_SWIM:
        return (weather & B_WEATHER_RAIN) != 0;
    case ABILITY_CHLOROPHYLL:
        return (weather & B_WEATHER_SUN) != 0;
    case ABILITY_SOLAR_POWER:
        return (weather & B_WEATHER_SUN) != 0;
    default:
        break;
    }
    // Gen4+ abilities (#ifdef'd until ported)
#ifdef ABILITY_MAGIC_GUARD
    if (ability == ABILITY_MAGIC_GUARD || ability == ABILITY_OVERCOAT)
        return (weather & B_WEATHER_DAMAGING_ANY) != 0;
#endif
#ifdef ABILITY_SAND_FORCE
    if (ability == ABILITY_SAND_FORCE || ability == ABILITY_SAND_RUSH)
        return (weather & B_WEATHER_SANDSTORM) != 0;
#endif
#ifdef ABILITY_ICE_BODY
    if (ability == ABILITY_ICE_BODY || ability == ABILITY_SNOW_CLOAK)
        return (weather & B_WEATHER_ICY_ANY) != 0;
#endif
#ifdef ABILITY_DRY_SKIN
    if (ability == ABILITY_DRY_SKIN || ability == ABILITY_HYDRATION || ability == ABILITY_RAIN_DISH)
        return (weather & B_WEATHER_RAIN) != 0;
#endif
#ifdef ABILITY_FLOWER_GIFT
    if (ability == ABILITY_FLOWER_GIFT || ability == ABILITY_HARVEST || ability == ABILITY_LEAF_GUARD)
        return (weather & B_WEATHER_SUN) != 0;
#endif
    return FALSE;
}

// RHH: IsLightSensitiveMove (src/battle_ai_field_statuses.c:203-217, static)
// Moves boosted by sun or weakened by low light.
static bool32 IsLightSensitiveMove(u16 move)
{
    switch (GetMoveEffect(move))
    {
    case EFFECT_SOLAR_BEAM:
    case EFFECT_MORNING_SUN:
    case EFFECT_SYNTHESIS:
    case EFFECT_MOONLIGHT:
    case EFFECT_GROWTH:
        return TRUE;
    default:
        return FALSE;
    }
}

// RHH: HasLightSensitiveMove (src/battle_ai_field_statuses.c:218-228, static)
static bool32 HasLightSensitiveMove(u8 battler)
{
    u16 *moves = GetMovesArray(battler);

    for (u32 moveIndex = 0; moveIndex < MAX_MON_MOVES; moveIndex++)
    {
        if (moves[moveIndex] != MOVE_NONE && moves[moveIndex] != MOVE_UNAVAILABLE
         && IsLightSensitiveMove(moves[moveIndex]))
            return TRUE;
    }
    return FALSE;
}

// RHH: BenefitsFromSun (src/battle_ai_field_statuses.c:231-252, static)
// Gen3: HOLD_EFFECT_UTILITY_UMBRELLA #ifdef'd; EFFECT_HYDRO_STEAM Gen8+ #ifdef'd.
static enum FieldEffectOutcome BenefitsFromSun(u8 battler)
{
    u8 ability = gAiLogicData->abilities[battler];

#ifdef HOLD_EFFECT_UTILITY_UMBRELLA
    if (gAiLogicData->holdEffects[battler] == HOLD_EFFECT_UTILITY_UMBRELLA)
        return FIELD_EFFECT_NEUTRAL;
#endif

    if (DoesAbilityBenefitFromWeather(ability, B_WEATHER_SUN)
     || HasLightSensitiveMove(battler)
     || HasDamagingMoveOfType(battler, TYPE_FIRE))
        return FIELD_EFFECT_POSITIVE;

    if (HasMoveWithFlag(battler, MoveHas50AccuracyInSun)
     || HasDamagingMoveOfType(battler, TYPE_WATER))
        return FIELD_EFFECT_NEGATIVE;

    return FIELD_EFFECT_NEUTRAL;
}

// RHH: BenefitsFromSandstorm (src/battle_ai_field_statuses.c:254-272, static)
// Gen3: HOLD_EFFECT_SAFETY_GOGGLES #ifdef'd;
// IS_BATTLER_ANY_TYPE → three separate IS_BATTLER_OF_TYPE checks.
static enum FieldEffectOutcome BenefitsFromSandstorm(u8 battler)
{
    u8 leftFoe = LEFT_FOE(battler);

    if (DoesAbilityBenefitFromWeather(gAiLogicData->abilities[battler], B_WEATHER_SANDSTORM)
     || IS_BATTLER_OF_TYPE(battler, TYPE_ROCK))
        return FIELD_EFFECT_POSITIVE;

    if (IS_BATTLER_OF_TYPE(battler, TYPE_ROCK)
     || IS_BATTLER_OF_TYPE(battler, TYPE_GROUND)
     || IS_BATTLER_OF_TYPE(battler, TYPE_STEEL)
#ifdef HOLD_EFFECT_SAFETY_GOGGLES
     || gAiLogicData->holdEffects[battler] == HOLD_EFFECT_SAFETY_GOGGLES
#endif
    )
    {
        // We're immune — see if foe also is
        if (!(IS_BATTLER_OF_TYPE(leftFoe, TYPE_ROCK)
           || IS_BATTLER_OF_TYPE(leftFoe, TYPE_GROUND)
           || IS_BATTLER_OF_TYPE(leftFoe, TYPE_STEEL))
         || DoesAbilityBenefitFromWeather(gAiLogicData->abilities[leftFoe], B_WEATHER_SANDSTORM)
#ifdef HOLD_EFFECT_SAFETY_GOGGLES
         || gAiLogicData->holdEffects[leftFoe] == HOLD_EFFECT_SAFETY_GOGGLES
#endif
        )
            return FIELD_EFFECT_POSITIVE;
        else
            return FIELD_EFFECT_NEUTRAL;
    }

    return FIELD_EFFECT_NEGATIVE;
}

// RHH: BenefitsFromHailOrSnow (src/battle_ai_field_statuses.c:274-294, static)
// Gen3: HOLD_EFFECT_SAFETY_GOGGLES #ifdef'd.
static enum FieldEffectOutcome BenefitsFromHailOrSnow(u8 battler, u32 weather)
{
    u8 leftFoe = LEFT_FOE(battler);

    if (DoesAbilityBenefitFromWeather(gAiLogicData->abilities[battler], weather)
     || IS_BATTLER_OF_TYPE(battler, TYPE_ICE)
     || HasMoveWithFlag(battler, MoveAlwaysHitsInHailSnow)
     || HasBattlerSideMoveWithEffect(battler, EFFECT_AURORA_VEIL))
        return FIELD_EFFECT_POSITIVE;

    if ((weather & B_WEATHER_DAMAGING_ANY)
#ifdef HOLD_EFFECT_SAFETY_GOGGLES
     && gAiLogicData->holdEffects[battler] != HOLD_EFFECT_SAFETY_GOGGLES
#endif
    )
        return FIELD_EFFECT_NEGATIVE;

    if (HasLightSensitiveMove(battler))
        return FIELD_EFFECT_NEGATIVE;

    if (HasMoveWithFlag(leftFoe, MoveAlwaysHitsInHailSnow))
        return FIELD_EFFECT_NEGATIVE;

    return FIELD_EFFECT_NEUTRAL;
}

// RHH: BenefitsFromRain (src/battle_ai_field_statuses.c:296-313, static)
// Gen3: HOLD_EFFECT_UTILITY_UMBRELLA #ifdef'd.
static enum FieldEffectOutcome BenefitsFromRain(u8 battler)
{
    u8 leftFoe = LEFT_FOE(battler);

#ifdef HOLD_EFFECT_UTILITY_UMBRELLA
    if (gAiLogicData->holdEffects[battler] == HOLD_EFFECT_UTILITY_UMBRELLA)
        return FIELD_EFFECT_NEUTRAL;
#endif

    if (DoesAbilityBenefitFromWeather(gAiLogicData->abilities[battler], B_WEATHER_RAIN)
     || HasMoveWithFlag(battler, MoveAlwaysHitsInRain)
     || HasDamagingMoveOfType(battler, TYPE_WATER))
        return FIELD_EFFECT_POSITIVE;

    if (HasLightSensitiveMove(battler) || HasDamagingMoveOfType(battler, TYPE_FIRE))
        return FIELD_EFFECT_NEGATIVE;

    if (HasMoveWithFlag(leftFoe, MoveAlwaysHitsInRain))
        return FIELD_EFFECT_NEGATIVE;

    return FIELD_EFFECT_NEUTRAL;
}

// ============================================================================
// Terrain/field status stubs — Gen6+ features, return FIELD_EFFECT_NEUTRAL.
// Full port deferred until terrain system is implemented.
// ============================================================================

// RHH: BenefitsFromElectricTerrain (src/battle_ai_field_statuses.c:315-349, static)
static enum FieldEffectOutcome BenefitsFromElectricTerrain(u8 battler)
{
    (void)battler;
    return FIELD_EFFECT_NEUTRAL;  // Terrain Gen6+ — deferred
}

// RHH: BenefitsFromGrassyTerrain (src/battle_ai_field_statuses.c:351-374, static)
static enum FieldEffectOutcome BenefitsFromGrassyTerrain(u8 battler)
{
    (void)battler;
    return FIELD_EFFECT_NEUTRAL;  // Terrain Gen6+ — deferred
}

// RHH: BenefitsFromMistyTerrain (src/battle_ai_field_statuses.c:376-413, static)
static enum FieldEffectOutcome BenefitsFromMistyTerrain(u8 battler)
{
    (void)battler;
    return FIELD_EFFECT_NEUTRAL;  // Terrain Gen6+ — deferred
}

// RHH: BenefitsFromPsychicTerrain (src/battle_ai_field_statuses.c:415-448, static)
static enum FieldEffectOutcome BenefitsFromPsychicTerrain(u8 battler)
{
    (void)battler;
    return FIELD_EFFECT_NEUTRAL;  // Terrain Gen6+ — deferred
}

// RHH: BenefitsFromGravity (src/battle_ai_field_statuses.c:449-475)
static enum FieldEffectOutcome BenefitsFromGravity(u8 battler)
{
    if (!AI_IsBattlerGrounded(battler))
        return FIELD_EFFECT_NEGATIVE;

    if (AI_IsAbilityOnSide(battler, ABILITY_HUSTLE))
        return FIELD_EFFECT_POSITIVE;

    if (HasMoveWithFlag(battler, IsMoveGravityBanned))
        return FIELD_EFFECT_NEGATIVE;

    if (IsBattlerAlive(LEFT_FOE(battler)))
    {
        if (HasMoveWithLowAccuracy(battler, LEFT_FOE(battler), LOW_ACCURACY_THRESHOLD, FALSE)
         || (!AI_IsBattlerGrounded(LEFT_FOE(battler)) && HasDamagingMoveOfType(battler, TYPE_GROUND)))
            return FIELD_EFFECT_POSITIVE;
    }

    if (IsBattlerAlive(RIGHT_FOE(battler)))
    {
        if (HasMoveWithLowAccuracy(battler, RIGHT_FOE(battler), LOW_ACCURACY_THRESHOLD, FALSE)
         || (!AI_IsBattlerGrounded(RIGHT_FOE(battler)) && HasDamagingMoveOfType(battler, TYPE_GROUND)))
            return FIELD_EFFECT_POSITIVE;
    }

    return FIELD_EFFECT_NEUTRAL;
}

// RHH: BenefitsFromTrickRoom (src/battle_ai_field_statuses.c:477-510)
static enum FieldEffectOutcome BenefitsFromTrickRoom(u8 battler)
{
    if (IsBattle1v1())
    {
        if (gAiLogicData->speedStats[battler] < gAiLogicData->speedStats[LEFT_FOE(battler)])
            return FIELD_EFFECT_POSITIVE;
        else if (gAiLogicData->speedStats[battler] == gAiLogicData->speedStats[LEFT_FOE(battler)])
            return FIELD_EFFECT_NEUTRAL;
        else
            return FIELD_EFFECT_NEGATIVE;
    }

    if (!(gFieldStatuses & STATUS_FIELD_PSYCHIC_TERRAIN))
    {
        u16 *aiMoves = GetMovesArray(battler);
        u32 moveIndex;
        for (moveIndex = 0; moveIndex < MAX_MON_MOVES; moveIndex++)
        {
            u16 move = aiMoves[moveIndex];
            if (GetBattleMovePriority(battler, gAiLogicData->abilities[battler], move) > 0
             && !(GetMovePriority(move) > 0 && IsBattleMoveStatus(move)))
                return FIELD_EFFECT_POSITIVE;
        }
    }

    if ((gAiLogicData->speedStats[battler] >= gAiLogicData->speedStats[LEFT_FOE(battler)])
     || (gAiLogicData->speedStats[battler] >= gAiLogicData->speedStats[RIGHT_FOE(battler)]))
        return FIELD_EFFECT_NEGATIVE;

    return FIELD_EFFECT_POSITIVE;
}

// RHH: CalcWeatherScore (src/battle_ai_field_statuses.c:512-603)
// Scores a weather-setting move for AI viability.
// Gen3: HOLD_EFFECT_DAMP_ROCK/HEAT_ROCK/SMOOTH_ROCK/ICY_ROCK #ifdef'd.
// BATTLE_WEATHER_SNOW merged with BATTLE_WEATHER_HAIL case.
// GetMoveWeatherType simplified: uses move effect mapping.
s32 CalcWeatherScore(u8 battlerAtk, u8 battlerDef, u16 move, struct AiLogicData *aiData)
{
    s32 score = 0;
    u16 effect = GetMoveEffect(move);
    u32 weatherType;

    // Map move effect to BATTLE_WEATHER type (Gen3 subset)
    switch (effect)
    {
    case EFFECT_RAIN_DANCE:          weatherType = BATTLE_WEATHER_RAIN;      break;
    case EFFECT_SUNNY_DAY:           weatherType = BATTLE_WEATHER_SUN;       break;
    case EFFECT_SANDSTORM:           weatherType = BATTLE_WEATHER_SANDSTORM; break;
    case EFFECT_HAIL:                weatherType = BATTLE_WEATHER_HAIL;      break;
    default:                         return score;
    }

    switch (weatherType)
    {
    case BATTLE_WEATHER_RAIN:
        if (ShouldSetWeather(battlerAtk, B_WEATHER_RAIN))
        {
            score += DECENT_EFFECT;

            if (HasBattlerSideMoveWithEffect(battlerAtk, EFFECT_WEATHER_BALL))
                score += WEAK_EFFECT;
#ifdef HOLD_EFFECT_DAMP_ROCK
            if (aiData->holdEffects[battlerAtk] == HOLD_EFFECT_DAMP_ROCK)
                score += WEAK_EFFECT;
#endif
            if (HasBattlerSideMoveWithEffect(battlerDef, EFFECT_MORNING_SUN)
             || HasBattlerSideMoveWithEffect(battlerDef, EFFECT_SYNTHESIS)
             || HasBattlerSideMoveWithEffect(battlerDef, EFFECT_SOLAR_BEAM)
             || HasBattlerSideMoveWithEffect(battlerDef, EFFECT_MOONLIGHT))
                score += WEAK_EFFECT;
            if (HasDamagingMoveOfType(battlerDef, TYPE_FIRE)
             || HasDamagingMoveOfType(BATTLE_PARTNER(battlerDef), TYPE_FIRE))
                score += WEAK_EFFECT;
        }
        break;
    case BATTLE_WEATHER_SUN:
        if (ShouldSetWeather(battlerAtk, B_WEATHER_SUN))
        {
            score += DECENT_EFFECT;

            if (HasBattlerSideMoveWithEffect(battlerAtk, EFFECT_WEATHER_BALL))
                score += WEAK_EFFECT;
#ifdef HOLD_EFFECT_HEAT_ROCK
            if (aiData->holdEffects[battlerAtk] == HOLD_EFFECT_HEAT_ROCK)
                score += WEAK_EFFECT;
#endif
            if (HasDamagingMoveOfType(battlerDef, TYPE_WATER)
             || HasDamagingMoveOfType(BATTLE_PARTNER(battlerDef), TYPE_WATER))
                score += WEAK_EFFECT;
            if (HasMoveWithFlag(battlerDef, MoveHas50AccuracyInSun)
             || HasMoveWithFlag(BATTLE_PARTNER(battlerDef), MoveHas50AccuracyInSun))
                score += WEAK_EFFECT;
        }
        break;
    case BATTLE_WEATHER_SANDSTORM:
        if (ShouldSetWeather(battlerAtk, B_WEATHER_SANDSTORM))
        {
            score += DECENT_EFFECT;

            if (HasBattlerSideMoveWithEffect(battlerAtk, EFFECT_WEATHER_BALL))
                score += WEAK_EFFECT;
#ifdef HOLD_EFFECT_SMOOTH_ROCK
            if (aiData->holdEffects[battlerAtk] == HOLD_EFFECT_SMOOTH_ROCK)
                score += WEAK_EFFECT;
#endif
            if (HasMoveWithEffect(battlerDef, EFFECT_MORNING_SUN)
             || HasMoveWithEffect(battlerDef, EFFECT_SYNTHESIS)
             || HasMoveWithEffect(battlerDef, EFFECT_MOONLIGHT))
                score += WEAK_EFFECT;
        }
        break;
    case BATTLE_WEATHER_HAIL:
        if (ShouldSetWeather(battlerAtk, B_WEATHER_HAIL))
        {
            score += DECENT_EFFECT;

            if (HasBattlerSideMoveWithEffect(battlerAtk, EFFECT_AURORA_VEIL)
             && ShouldSetScreen(battlerAtk, battlerDef, EFFECT_AURORA_VEIL))
                score += GOOD_EFFECT;
            if (HasBattlerSideMoveWithEffect(battlerAtk, EFFECT_WEATHER_BALL))
                score += WEAK_EFFECT;
#ifdef HOLD_EFFECT_ICY_ROCK
            if (aiData->holdEffects[battlerAtk] == HOLD_EFFECT_ICY_ROCK)
                score += WEAK_EFFECT;
#endif
            if (HasMoveWithEffect(battlerDef, EFFECT_MORNING_SUN)
             || HasMoveWithEffect(battlerDef, EFFECT_SYNTHESIS)
             || HasMoveWithEffect(battlerDef, EFFECT_MOONLIGHT))
                score += WEAK_EFFECT;
        }
        break;
    }

    return score;
}
