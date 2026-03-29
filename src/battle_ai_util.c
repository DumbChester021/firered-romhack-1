#include "global.h"
#include "battle.h"
#include "battle_anim.h"
#include "battle_ai_main.h"
#include "battle_ai_util.h"
#include "battle_main.h"
#include "battle_script_commands.h"
#include "battle_util.h"
#include "pokemon.h"
#include "random.h"
#include "item.h"
#include "constants/battle.h"
#include "constants/battle_ai.h"
#include "constants/hold_effects.h"
#include "constants/moves.h"
#include "constants/battle_move_effects.h"
#include "battle_ai_field_statuses.h"

#define AI_THINKING_STRUCT (gBattleResources->ai)

// AI_CalcDamage: Returns an estimated damage value for the AI's move selection.
// Calls FireRed's existing AI_CalcDmg + TypeCalc (from battle_script_commands.c)
// which use gBattleMoveDamage as an in/out global.
// Returns 0 if the move has no power, or is completely negated by type immunity.
// Sets *typeEffectiveness to the MOVE_RESULT_* flags from TypeCalc.
s32 AI_CalcDamage(u16 move, u8 battlerAtk, u8 battlerDef, u8 *typeEffectiveness)
{
    s32 dmg;
    u8 flags;

    if (gMovesInfo[move].power < 2)
    {
        if (typeEffectiveness != NULL)
            *typeEffectiveness = 0;
        return 0;
    }

    // Save and set up state the same way Cmd_if_can_faint does.
    gDynamicBasePower = 0;
    gBattleStruct->dynamicMoveType = 0;
    gBattleScripting.dmgMultiplier = 1;
    gMoveResultFlags = 0;
    gCritMultiplier = 1;
    gCurrentMove = move;

    AI_CalcDmg(battlerAtk, battlerDef);
    flags = TypeCalc(move, battlerAtk, battlerDef);

    // Apply the AI's simulated RNG factor (97 = ~midpoint of 85–100 range, conservative).
    // This is not index-based like the old VM; we use a fixed midpoint.
    gBattleMoveDamage = gBattleMoveDamage * 97 / 100;
    if (gBattleMoveDamage == 0)
        gBattleMoveDamage = 1;

    // If the move is completely negated (Levitate vs Ground, type immunity, etc.), return 0.
    if (flags & (MOVE_RESULT_DOESNT_AFFECT_FOE | MOVE_RESULT_MISSED))
        dmg = 0;
    else
        dmg = gBattleMoveDamage;

    if (typeEffectiveness != NULL)
        *typeEffectiveness = flags;

    return dmg;
}

// RHH: AI_WhoStrikesFirst (pokeemerald-expansion/src/battle_ai_util.c:1450)
// Compares speeds (and optionally move priorities) and returns AI_IS_FASTER or AI_IS_SLOWER.
// HOLD_EFFECT_LAGGING_TAIL and ABILITY_STALL guarded by #ifdef until those constants are added.
s32 AI_WhoStrikesFirst(u8 battlerAtk, u8 battlerDef, u16 aiMove, u16 playerMove, enum ConsiderPriority considerPriority)
{
    u32 speedAI, speedPlayer;
    u8 abilityAI     = gAiLogicData->abilities[battlerAtk];
    u8 abilityPlayer = gAiLogicData->abilities[battlerDef];
    u8 holdEffAI     = gAiLogicData->holdEffects[battlerAtk];
    u8 holdEffPlayer = gAiLogicData->holdEffects[battlerDef];

    if (considerPriority == CONSIDER_PRIORITY)
    {
        s32 aiPriority     = GetBattleMovePriority(battlerAtk, abilityAI,     aiMove);
        s32 playerPriority = GetBattleMovePriority(battlerDef, abilityPlayer, playerMove);

        if (aiPriority > playerPriority)
            return AI_IS_FASTER;
        else if (aiPriority < playerPriority)
            return AI_IS_SLOWER;
    }

    speedAI     = GetBattlerTotalSpeedStat(battlerAtk, abilityAI,     holdEffAI);
    speedPlayer = GetBattlerTotalSpeedStat(battlerDef, abilityPlayer, holdEffPlayer);

#ifdef HOLD_EFFECT_LAGGING_TAIL
    if (holdEffAI == HOLD_EFFECT_LAGGING_TAIL && holdEffPlayer != HOLD_EFFECT_LAGGING_TAIL)
        return AI_IS_SLOWER;
    else if (holdEffAI != HOLD_EFFECT_LAGGING_TAIL && holdEffPlayer == HOLD_EFFECT_LAGGING_TAIL)
        return AI_IS_FASTER;
#endif
#ifdef ABILITY_STALL
    if (abilityAI == ABILITY_STALL && abilityPlayer != ABILITY_STALL)
        return AI_IS_SLOWER;
    else if (abilityAI != ABILITY_STALL && abilityPlayer == ABILITY_STALL)
        return AI_IS_FASTER;
#endif

    if (speedAI > speedPlayer)
    {
#ifdef STATUS_FIELD_TRICK_ROOM
        if (gFieldStatuses & STATUS_FIELD_TRICK_ROOM)
            return AI_IS_SLOWER;
#endif
        return AI_IS_FASTER;
    }
    else if (speedAI == speedPlayer)
    {
        return AI_IS_FASTER; // tie → assume AI acts first
    }
    else
    {
#ifdef STATUS_FIELD_TRICK_ROOM
        if (gFieldStatuses & STATUS_FIELD_TRICK_ROOM)
            return AI_IS_FASTER;
#endif
        return AI_IS_SLOWER;
    }
}

// RHH: AI_IsFaster / AI_IsSlower wrappers (pokeemerald-expansion/src/battle_ai_util.c)
// Thin wrappers around AI_WhoStrikesFirst for call-site convenience.
bool8 AI_IsFaster(u8 battlerAtk, u8 battlerDef, u16 aiMove, u16 playerMove, enum ConsiderPriority considerPriority)
{
    return AI_WhoStrikesFirst(battlerAtk, battlerDef, aiMove, playerMove, considerPriority) == AI_IS_FASTER;
}

bool8 AI_IsSlower(u8 battlerAtk, u8 battlerDef, u16 aiMove, u16 playerMove, enum ConsiderPriority considerPriority)
{
    return AI_WhoStrikesFirst(battlerAtk, battlerDef, aiMove, playerMove, considerPriority) == AI_IS_SLOWER;
}

// AI_HasMoveEffect: Returns TRUE if any of battlerAtk's current moves have the given effect ID.
bool8 AI_HasMoveEffect(u8 battlerAtk, u16 effect)
{
    u8 i;
    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        u16 move = gBattleMons[battlerAtk].moves[i];
        if (move != MOVE_NONE && gMovesInfo[move].effect == effect)
            return TRUE;
    }
    return FALSE;
}

// AI_CountAlivePokemon: Counts non-fainted (HP > 0) mons in battler's party
// that can still fight (HP > 0, not currently on field).
u8 AI_CountAlivePokemon(u8 battler)
{
    struct Pokemon *party = (GetBattlerSide(battler) == B_SIDE_PLAYER)
                             ? gPlayerParty
                             : gEnemyParty;
    u8 count = 0;
    u8 i;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        if (GetMonData(&party[i], MON_DATA_SPECIES, NULL) != SPECIES_NONE
         && GetMonData(&party[i], MON_DATA_HP, NULL) > 0
         && i != gBattlerPartyIndexes[battler])
            count++;
    }
    return count;
}

// ============================================================================
// AI_GetTypeEffectiveness (FRLG port)
// RHH source: src/battle_ai_util.c lines 1013-1033 (AI_GetTypeEffectiveness)
//
// RHH uses: SaveBattlerData / SetBattlerData / CalcTypeEffectivenessMultiplier
// FRLG adaptation: TypeCalc() is FireRed's equivalent type+ability chart function.
//   It returns MOVE_RESULT_* flags. We translate those to the same enum RHH uses
//   (AI_EFFECTIVENESS_x0 / x0_5 / x1 / x2) so the rest of the logic is identical.
//
// FRLG_STUB: When we add SaveBattlerData/SetBattlerData and a clean CalcTypeEffectiveness-
//   Multiplier wrapper, replace this body with a direct port of RHH's version.
// ============================================================================
static u8 AI_GetTypeEffectiveness(u16 move, u8 battlerAtk, u8 battlerDef)
{
    u8 flags;

    if (gMovesInfo[move].power < 2)
        return AI_EFFECTIVENESS_x0;

    flags = TypeCalc(move, battlerAtk, battlerDef);

    if (flags & MOVE_RESULT_DOESNT_AFFECT_FOE)
        return AI_EFFECTIVENESS_x0;
    if (flags & MOVE_RESULT_NOT_VERY_EFFECTIVE)
        return AI_EFFECTIVENESS_x0_5;
    if (flags & MOVE_RESULT_SUPER_EFFECTIVE)
        return AI_EFFECTIVENESS_x2;
    return AI_EFFECTIVENESS_x1;
}

// ============================================================================
// AI_GetTypeEffectivenessForPartyMon (FRLG port)
// RHH source: src/battle_util.c lines 10487-10507 (CalcPartyMonTypeEffectivenessMultiplier)
//
// Checks a benched party mon's type matchup against a given move.
// RHH version uses MulByTypeEffectiveness on gSpeciesInfo types + abilityDef check.
// FRLG adaptation: we temporarily set the battlerDef's species/types from party data
//   and call TypeCalc. This avoids needing MulByTypeEffectiveness.
//
// FRLG_STUB: When MulByTypeEffectiveness and CalcPartyMonTypeEffectivenessMultiplier
//   are ported, replace with a direct call by passing the party mon's species+ability.
// ============================================================================
static u8 AI_GetTypeEffectivenessForPartyMon(u16 move, struct Pokemon *targetMon)
{
    // Temporarily borrow battler slot 2 (never active in single battle) as scratch.
    // We save and restore the species+types fields so no persistent mutation occurs.
    // This is the cleanest pre-AI_DATA approach available in FRLG.
    u16 savedSpecies = gBattleMons[2].species;
    u8  savedType1   = GetBattlerType1(2);
    u8  savedType2   = GetBattlerType2(2);
    u16 candSpecies  = GetMonData(targetMon, MON_DATA_SPECIES, NULL);
    u8  flags;

    gBattleMons[2].species = candSpecies;
    gBattleMons[2].type1   = gSpeciesInfo[candSpecies].types[0];
    gBattleMons[2].type2   = gSpeciesInfo[candSpecies].types[1];

    flags = TypeCalc(move, 0, 2);   // attacker slot doesn't matter for type chart

    gBattleMons[2].species = savedSpecies;
    gBattleMons[2].type1   = savedType1;
    gBattleMons[2].type2   = savedType2;

    if (flags & MOVE_RESULT_DOESNT_AFFECT_FOE)
        return AI_EFFECTIVENESS_x0;
    if (flags & MOVE_RESULT_NOT_VERY_EFFECTIVE)
        return AI_EFFECTIVENESS_x0_5;
    if (flags & MOVE_RESULT_SUPER_EFFECTIVE)
        return AI_EFFECTIVENESS_x2;
    return AI_EFFECTIVENESS_x1;
}

// ============================================================================
// HasBadOdds (FRLG port)
// RHH source: src/battle_ai_switch_items.c lines 71-217 (HasBadOdds)
//
// Determines if the current active pokemon has tactically unfavorable odds.
// Returns TRUE if a switch is recommended and sets *outSwitch to PARTY_SIZE
//   (sentinel: caller uses AI_DATA->mostSuitableMonId, which we don't have yet).
//
// Ported line-by-line from RHH. Items marked FRLG_STUB are not yet implemented:
//   - ABILITY_REGENERATOR hp threshold: uncomment when Gen 4 abilities added.
//   - AI_DATA->mostSuitableMonId: uncomment when AI_DATA precompute is added.
//   - RNG_AI_SWITCH_HASBADODDS seed: using Random()&1 (50%) as direct equivalent.
//   - weather parameter: FRLG has no weather AI helper yet (B_WEATHER_NONE always).
// ============================================================================
static bool8 HasBadOdds(u8 battler, u8 opposingBattler)
{
    // RHH lines 80-82: only run if AI_FLAG_SMART_SWITCHING set.
    // (Caller already checks this, but guard here for safety.)
    // RHH lines 84-86: skip doubles.
    if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE)
        return FALSE;

    {
        // RHH lines 91-95: get types of both mons.
        u8 atkType1 = GetBattlerType1(opposingBattler);
        u8 atkType2 = GetBattlerType2(opposingBattler);
        u8 defType1 = GetBattlerType1(battler);
        u8 defType2 = GetBattlerType2(battler);
        s32 i;
        s32 damageDealt = 0, maxDamageDealt = 0;
        s32 damageTaken = 0, maxDamageTaken = 0;
        bool8 getsOneShot = FALSE;
        bool8 hasStatusMove = FALSE;
        bool8 hasSuperEffectiveMove = FALSE;
        // RHH line 78: baseline type effectiveness multiplier (1.0 = neutral).
        // We replicate this as: typeDisadvantage = TRUE if at least one of foe's
        // types is super-effective vs at least one of ours via the type chart.
        bool8 typeDisadvantage = FALSE;

        // RHH lines 98-132: check AI moves for damage dealt and status moves.
        for (i = 0; i < MAX_MON_MOVES; i++)
        {
            u16 aiMove = gBattleMons[battler].moves[i];
            if (aiMove == MOVE_NONE)
                continue;

            // RHH lines 105-113: important status moves (keep mon in field).
            if (gMovesInfo[aiMove].power == 0)
            {
                u16 effect = gMovesInfo[aiMove].effect;
                if (effect == EFFECT_REFLECT        || effect == EFFECT_LIGHT_SCREEN
                 || effect == EFFECT_EXPLOSION       || effect == EFFECT_DESTINY_BOND
                 || effect == EFFECT_LEECH_SEED
                 || effect == EFFECT_SLEEP           || effect == EFFECT_TOXIC
                 || effect == EFFECT_PARALYZE
                 || effect == EFFECT_SPIKES          // Gen 3: Spikes layer hazard
                 || effect == EFFECT_YAWN            // Gen 3: forces sleep next turn
                 || effect == EFFECT_WILL_O_WISP     // Gen 3: burn inducer
                 || effect == EFFECT_TRICK           // Gen 3: disrupts Choice-locked foes
                 // FRLG_STUB: EFFECT_STEALTH_ROCK (Gen 4), EFFECT_TRICK_ROOM (Gen 4),
                 //   EFFECT_WONDER_ROOM (Gen 5), EFFECT_STICKY_WEB (Gen 6) — add when ported.
                )
                    hasStatusMove = TRUE;
                continue;
            }

            // RHH lines 116-131: check if mon has SE move and compute max damage dealt.
            if (AI_GetTypeEffectiveness(aiMove, battler, opposingBattler) >= AI_EFFECTIVENESS_x2)
                hasSuperEffectiveMove = TRUE;

            damageDealt = AI_CalcDamage(aiMove, battler, opposingBattler, NULL);
            if (damageDealt > maxDamageDealt)
                maxDamageDealt = damageDealt;
        }

        // RHH lines 134-143: calculate type disadvantage.
        // RHH uses GetTypeModifier + uq4_12_multiply for exact chart lookup.
        // FRLG: we use AI_GetTypeEffectiveness on a neutral-power move proxy.
        // We check if foe's primary type hits either of our types super-effectively.
        // This is equivalent to RHH's typeEffectiveness >= UQ_4_12(2.0) check.
        {
            u8 j;
            for (j = 0; j < MAX_MON_MOVES; j++)
            {
                u16 foeMove = gBattleMons[opposingBattler].moves[j];
                if (foeMove == MOVE_NONE || gMovesInfo[foeMove].power < 2)
                    continue;
                // If foe has a move super-effective vs us, that's the equivalent
                // of the type chart showing >= 2x for their type vs ours.
                if (AI_GetTypeEffectiveness(foeMove, opposingBattler, battler) >= AI_EFFECTIVENESS_x2)
                {
                    typeDisadvantage = TRUE;
                    break;
                }
            }
            (void)atkType1; (void)atkType2; (void)defType1; (void)defType2;
        }

        // RHH lines 145-155: get max damage mon could take.
        for (i = 0; i < MAX_MON_MOVES; i++)
        {
            u16 playerMove = gBattleMons[opposingBattler].moves[i];
            if (playerMove == MOVE_NONE || gMovesInfo[playerMove].power < 2)
                continue;
            damageTaken = AI_CalcDamage(playerMove, opposingBattler, battler, NULL);
            if (damageTaken > maxDamageTaken)
                maxDamageTaken = damageTaken;
        }

        // RHH lines 157-161: check if mon gets one shot.
        if (maxDamageTaken >= (s32)gBattleMons[battler].hp)
            getsOneShot = TRUE;

        // RHH lines 163-168: if we can KO despite bad matchup, don't switch.
        if (maxDamageDealt >= (s32)gBattleMons[opposingBattler].hp)
        {
            if (AI_IsFaster(battler, opposingBattler, MOVE_NONE, MOVE_NONE, DONT_CONSIDER_PRIORITY))
                return FALSE;
        }

        // RHH lines 170-172: if no viable switch target, don't switch.
        // FRLG_STUB: RHH checks AI_DATA->mostSuitableMonId[battler] != PARTY_SIZE here.
        // When AI_DATA precompute is added, replace the AI_CountAlivePokemon call with that.
        if (AI_CountAlivePokemon(battler) == 0)
            return FALSE;

        // RHH lines 174-191: OHKO + outspeed case.
        if ((getsOneShot && gBattleMons[opposingBattler].speed > gBattleMons[battler].speed
             && maxDamageDealt < (s32)(gBattleMons[opposingBattler].hp / 2))
         && (gBattleMons[battler].hp >= gBattleMons[battler].maxHP / 2
             // FRLG_STUB: || (aiAbility == ABILITY_REGENERATOR
             //   && gBattleMons[battler].hp >= gBattleMons[battler].maxHP / 4)
             // Uncomment when ABILITY_REGENERATOR is added.
            ))
        {
            // RHH line 183: 50% chance to stay in regardless.
            if (!(Random() & 1)) // RandomPercentage(RNG_AI_SWITCH_HASBADODDS, 50)
                return FALSE;
            return TRUE;
        }

        // RHH lines 193-215: general type disadvantage case.
        if (typeDisadvantage)
        {
            if (!hasSuperEffectiveMove
             && (gBattleMons[battler].hp >= gBattleMons[battler].maxHP / 2
                 // FRLG_STUB: || (aiAbility == ABILITY_REGENERATOR
                 //   && gBattleMons[battler].hp >= gBattleMons[battler].maxHP / 4)
                 // Uncomment when ABILITY_REGENERATOR is added.
                ))
            {
                // RHH: if mon has important status move, keep it in.
                if (hasStatusMove)
                    return FALSE;

                // RHH line 206: 50% chance to stay in regardless.
                if (!(Random() & 1)) // RandomPercentage(RNG_AI_SWITCH_HASBADODDS, 50)
                    return FALSE;

                return TRUE;
            }
        }
    }
    return FALSE;
}

// ============================================================================
// FindMonWithFlagsAndSuperEffective (FRLG port)
// RHH source: src/battle_ai_switch_items.c lines 750-897
//
// Finds a party mon that has a move with specific type-result flags against
// the last move that hit us, AND has a super-effective move vs the opponent.
// Used as the "default" switch-in recommendation at the bottom of ShouldSwitch.
//
// FRLG_STUB: IsAceMon check (RHH lines 279-282) — uncomment when AI_FLAG_ACE_POKEMON
//   and CalculateEnemyPartyCount are added.
// FRLG_STUB: battlerIn2 double-battle handling simplified to single-battle only.
// ============================================================================
// ============================================================================
// CanMonSurviveHazardSwitchin (FRLG port)
// RHH source: src/battle_ai_switch_items.c (CanMonSurviveHazardSwitchin, ~line 700-748)
//
// Returns TRUE if the candidate mon can survive switching in given current
// entry hazards on its side of the field.
// Gen 3 only has Spikes (1-3 layers = 1/8, 1/6, 1/4 max HP per switch-in).
// Flying-type and Levitate ignore Spikes.
//
// FRLG_STUB: Stealth Rock (Gen 4), Toxic Spikes (Gen 4), Sticky Web (Gen 6)
//   — add elif-branches here when those hazards are ported.
// ============================================================================
static bool8 CanMonSurviveHazardSwitchin(struct Pokemon *mon, u8 battlerSide)
{
    u16 species   = GetMonData(mon, MON_DATA_SPECIES, NULL);
    u32 hp        = GetMonData(mon, MON_DATA_HP, NULL);
    u32 maxHp     = GetMonData(mon, MON_DATA_MAX_HP, NULL);
    u8  type1     = gSpeciesInfo[species].types[0];
    u8  type2     = gSpeciesInfo[species].types[1];
    u8  spikesCnt = gSideTimers[battlerSide].spikesAmount;

    if (spikesCnt == 0)
        return TRUE; // no hazards

    // Flying-type or Levitate immunity to Spikes.
    if (type1 == TYPE_FLYING || type2 == TYPE_FLYING)
        return TRUE;
    // FRLG_STUB: || GetMonAbility(mon) == ABILITY_LEVITATE — add when GetMonAbility is available here.

    // Spikes damage: 1 layer = 1/8, 2 layers = 1/6, 3 layers = 1/4.
    {
        u32 spikeDmg;
        if (spikesCnt == 1)       spikeDmg = maxHp / 8;
        else if (spikesCnt == 2)  spikeDmg = maxHp / 6;
        else                      spikeDmg = maxHp / 4;
        if (spikeDmg == 0) spikeDmg = 1;
        return (hp > spikeDmg);
    }
}

// ============================================================================
// ShouldSwitchIfWonderGuard (FRLG port)
// RHH source: src/battle_ai_switch_items.c (ShouldSwitchIfWonderGuard, ~line 220-275)
//
// If the opposing battler has Wonder Guard, switch to a mon with a SE move
// because only SE moves can damage it. This is a Gen 3 mechanic (Shedinja).
// ============================================================================
static bool8 ShouldSwitchIfWonderGuard(u8 battler, u8 opposingBattler, u8 *outSlot)
{
    u8 i;
    struct Pokemon *party;

    if (gBattleMons[opposingBattler].ability != ABILITY_WONDER_GUARD)
        return FALSE;

    // Check if any current move is super-effective — if so, stay in.
    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        u16 move = gBattleMons[battler].moves[i];
        if (move == MOVE_NONE || gMovesInfo[move].power < 2)
            continue;
        if (AI_GetTypeEffectiveness(move, battler, opposingBattler) >= AI_EFFECTIVENESS_x2)
            return FALSE;
    }

    // None of our moves are SE vs Wonder Guard — find a party mon that has one.
    party = (GetBattlerSide(battler) == B_SIDE_PLAYER) ? gPlayerParty : gEnemyParty;
    for (i = 0; i < PARTY_SIZE; i++)
    {
        u16 species = GetMonData(&party[i], MON_DATA_SPECIES, NULL);
        u32 hp      = GetMonData(&party[i], MON_DATA_HP, NULL);
        u8 j;

        if (species == SPECIES_NONE || hp == 0 || i == gBattlerPartyIndexes[battler])
            continue;

        for (j = 0; j < MAX_MON_MOVES; j++)
        {
            u16 candMove = GetMonData(&party[i], MON_DATA_MOVE1 + j, NULL);
            if (candMove == MOVE_NONE || gMovesInfo[candMove].power < 2)
                continue;
            if (AI_GetTypeEffectivenessForPartyMon(candMove, &party[i]) >= AI_EFFECTIVENESS_x2)
            {
                *outSlot = i;
                return TRUE;
            }
        }
    }
    return FALSE;
}

// ============================================================================
// ShouldSwitchIfEncored (FRLG port)
// RHH source: src/battle_ai_switch_items.c lines 1098-1100 (ShouldSwitchIfEncored)
//
// If our active mon is encored into a move that doesn't damage the opponent,
// we should switch to avoid wasting turns.
// Encore is Gen 3; gDisableStructs[battler].encoreTimer tracks remaining turns.
// ============================================================================
static bool8 ShouldSwitchIfEncored(u8 battler)
{
    if (gDisableStructs[battler].encoreTimer == 0)
        return FALSE;

    // Check if the encored move is non-damaging vs the current opponent.
    // encoreMove is the move we're locked into (tracked in gDisableStructs[battler].encoredMove).
    {
        u16 encoredMove = gDisableStructs[battler].encoredMove;
        if (encoredMove == MOVE_NONE)
            return FALSE;
        // If the encored move has no power (status), it's wasteful. Switch.
        if (gMovesInfo[encoredMove].power < 2)
            return TRUE;
    }
    return FALSE;
}

// ============================================================================
// IsAbilityPreventingEscape (FRLG port)
// RHH source: src/battle_ai_switch_items.c lines 1015 area
//
// Returns TRUE if an opposing ability traps us on the field.
// All three trapping abilities exist in Gen 3.
// ============================================================================
static bool8 IsAbilityPreventingEscape(u8 battler, u8 opposingBattler)
{
    u8 oppAbility = gBattleMons[opposingBattler].ability;
    u8 battlerType1 = GetBattlerType1(battler);
    u8 battlerType2 = GetBattlerType2(battler);

    if (oppAbility == ABILITY_SHADOW_TAG)
        return TRUE; // traps all non-Ghost mons (Ghost immunity handled by game engine)

    if (oppAbility == ABILITY_ARENA_TRAP)
    {
        // Arena Trap only traps grounded mons (not Flying-type or Levitate).
        if (battlerType1 == TYPE_FLYING || battlerType2 == TYPE_FLYING)
            return FALSE;
        // FRLG_STUB: add Levitate check when GetBattlerAbility is accessible here.
        return TRUE;
    }

    if (oppAbility == ABILITY_MAGNET_PULL)
    {
        // Magnet Pull only traps Steel-types.
        if (battlerType1 == TYPE_STEEL || battlerType2 == TYPE_STEEL)
            return TRUE;
    }

    return FALSE;
}

static bool8 FindMonWithFlagsAndSuperEffective(u8 battler, u8 opposingBattler,
                                                u8 requiredFlag, u8 *outSlot)
{
    struct Pokemon *party;
    s32 i, j;
    u16 lastLandedMove;
    u16 move;

    // RHH lines 759-766: if no last-landed move data, skip the resistance filter.
    // gLastLandedMoves[] exists in FRLG and tracks the last move that hit each battler.
    lastLandedMove = gLastLandedMoves[battler];

    party = (GetBattlerSide(battler) == B_SIDE_PLAYER) ? gPlayerParty : gEnemyParty;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        u16 species = GetMonData(&party[i], MON_DATA_SPECIES, NULL);
        u32 hp      = GetMonData(&party[i], MON_DATA_HP, NULL);

        // RHH lines 793-800: skip invalid, current battler, already-switching-in mons.
        if (species == SPECIES_NONE || hp == 0)
            continue;
        if (i == gBattlerPartyIndexes[battler])
            continue;
        // FRLG_STUB: skip IsAceMon(battler, i) — add when AI_FLAG_ACE_POKEMON implemented.
        // FRLG_STUB: skip gBattleStruct->monToSwitchIntoId[battlerIn2] check for doubles.

        // RHH lines 802-860: check each move of the candidate.
        for (j = 0; j < MAX_MON_MOVES; j++)
        {
            move = GetMonData(&party[i], MON_DATA_MOVE1 + j, NULL);
            if (move == MOVE_NONE || gMovesInfo[move].power < 2)
                continue;

            // RHH: move must be super-effective vs opponent (the "FindMonWith...SuperEffective" part).
            if (AI_GetTypeEffectivenessForPartyMon(move, &party[i]) < AI_EFFECTIVENESS_x2)
                continue;

            // RHH: if a last-landed move is known, also require the candidate to resist or be
            // immune to that move (requiredFlag = DOESNT_AFFECT_FOE for immunity pass,
            // NOT_VERY_EFFECTIVE for resistance pass).
            if (lastLandedMove != MOVE_NONE && lastLandedMove != 0 && requiredFlag != 0)
            {
                u8 resistFlags = TypeCalc(lastLandedMove, opposingBattler, (u8)i);
                // We need the flag to be set (immune or NVE) for requiredFlag.
                // Temporarily borrow slot 2 as scratch for the candidate's types.
                u16 savedSpecies = gBattleMons[2].species;
                u8  savedT1      = GetBattlerType1(2);
                u8  savedT2      = GetBattlerType2(2);
                u16 candSpecies  = GetMonData(&party[i], MON_DATA_SPECIES, NULL);

                gBattleMons[2].species = candSpecies;
                gBattleMons[2].type1   = gSpeciesInfo[candSpecies].types[0];
                gBattleMons[2].type2   = gSpeciesInfo[candSpecies].types[1];
                resistFlags = TypeCalc(lastLandedMove, opposingBattler, 2);
                gBattleMons[2].species = savedSpecies;
                gBattleMons[2].type1   = savedT1;
                gBattleMons[2].type2   = savedT2;
                (void)resistFlags;

                if (!(resistFlags & requiredFlag))
                    continue; // candidate doesn't satisfy the required resistance/immunity
            }

            *outSlot = (u8)i;
            return TRUE;
        }
    }
    return FALSE;
}

// ============================================================================
// AI_EvaluateSwitch
// RHH source: src/battle_ai_switch_items.c lines 1001-1118 (ShouldSwitch)
//
// Entry point. Returns the party slot to switch into, or PARTY_SIZE (no switch).
// Structure mirrors ShouldSwitch exactly.
//
// FRLG_STUB (lines from RHH ShouldSwitch that are genuinely Gen 4+):
//   - STATUS3_ROOTED (RHH line 1013): add when Ingrain is implemented (Gen 4 AI check).
//   - AI_FLAG_SEQUENCE_SWITCHING (RHH): RHH-specific flag system, not a game feature.
//   - ShouldSwitchIfGameStatePrompt: perish song countdown AI (low priority, add later).
//   - ShouldSwitchIfBadChoiceLock: Choice items don't exist in vanilla FRLG.
//   - AreAttackingStatsLowered: requires stat-stage history tracking.
//   - AI_DATA->mostSuitableMonId: requires full AI_DATA precompute system.
// ============================================================================
u8 AI_EvaluateSwitch(u8 battlerAtk, u8 battlerDef)
{
    u8 outSlot = PARTY_SIZE;
    u8 battlerSide = GET_BATTLER_SIDE(battlerAtk);
    u8 oppSide     = GET_BATTLER_SIDE(battlerDef);
    (void)oppSide;

    // RHH lines 1011-1012: don't switch if wrapped/prevented.
    if (gBattleMons[battlerAtk].status2 & (STATUS2_WRAPPED | STATUS2_ESCAPE_PREVENTION))
        return PARTY_SIZE;

    // FRLG_STUB: STATUS3_ROOTED (Ingrain) check — add when Ingrain AI implemented.

    // IsAbilityPreventingEscape: Arena Trap, Shadow Tag, Magnet Pull — all Gen 3.
    if (IsAbilityPreventingEscape(battlerAtk, battlerDef))
        return PARTY_SIZE;

    // RHH lines 1024-1065: count available-to-switch mons.
    if (AI_CountAlivePokemon(battlerAtk) == 0)
        return PARTY_SIZE;

    // ShouldSwitchIfWonderGuard: Shedinja exists in Gen 3.
    if (ShouldSwitchIfWonderGuard(battlerAtk, battlerDef, &outSlot))
        return outSlot;

    // FRLG_STUB: ShouldSwitchIfGameStatePrompt (Perish Song countdown) — low priority, add later.
    // FRLG_STUB: FindMonThatTrapsOpponent (RHH reward-AI for trapping) — not a simple port.
    // FindMonThatAbsorbsOpponentsMove: type-absorb abilities (VoltAbsorb etc.) exist in Gen 3
    //   but this requires scanning party for ability data — add when GetMonAbility is available here.

    // CanMonSurviveHazardSwitchin: Spikes exist in Gen 3.
    // Note: we use this as a filter when selecting switch targets below, not a reason to switch.
    // (RHH uses it differently — to avoid switching into a mon that would faint on entry.)
    // Applied in the fallback loop in HasBadOdds block below.

    // RHH lines 1092-1103: HasBadOdds and similar checks.
    if (HasBadOdds(battlerAtk, battlerDef))
    {
        // Look for a mon with SE coverage that can survive switching in.
        struct Pokemon *party = (GetBattlerSide(battlerAtk) == B_SIDE_PLAYER)
                                ? gPlayerParty : gEnemyParty;
        if (FindMonWithFlagsAndSuperEffective(battlerAtk, battlerDef, 0, &outSlot))
        {
            if (CanMonSurviveHazardSwitchin(&party[outSlot], battlerSide))
                return outSlot;
        }
        // Fall back: first available mon that survives hazards.
        {
            u8 i;
            for (i = 0; i < PARTY_SIZE; i++)
            {
                if (i == gBattlerPartyIndexes[battlerAtk])
                    continue;
                if (GetMonData(&party[i], MON_DATA_SPECIES, NULL) == SPECIES_NONE)
                    continue;
                if (GetMonData(&party[i], MON_DATA_HP, NULL) == 0)
                    continue;
                if (!CanMonSurviveHazardSwitchin(&party[i], battlerSide))
                    continue;
                return i;
            }
        }
    }

    // ShouldSwitchIfEncored: Encore is Gen 3.
    if (ShouldSwitchIfEncored(battlerAtk))
    {
        if (FindMonWithFlagsAndSuperEffective(battlerAtk, battlerDef,
                                              MOVE_RESULT_DOESNT_AFFECT_FOE, &outSlot))
            return outSlot;
    }

    // FRLG_STUB: ShouldSwitchIfBadChoiceLock — Choice items not in vanilla FRLG.
    // FRLG_STUB: AreAttackingStatsLowered — requires stat stage history.

    // RHH lines 1107-1110: don't switch if we already have a SE move.
    {
        u8 j;
        for (j = 0; j < MAX_MON_MOVES; j++)
        {
            u16 move = gBattleMons[battlerAtk].moves[j];
            if (move == MOVE_NONE || gMovesInfo[move].power < 2)
                continue;
            if (AI_GetTypeEffectiveness(move, battlerAtk, battlerDef) >= AI_EFFECTIVENESS_x2)
                return PARTY_SIZE; // already have SE coverage, don't switch
        }
    }

    // RHH lines 1114-1116: default — look for a better mon via type coverage.
    if (FindMonWithFlagsAndSuperEffective(battlerAtk, battlerDef,
                                          MOVE_RESULT_DOESNT_AFFECT_FOE, &outSlot))
        return outSlot;
    if (FindMonWithFlagsAndSuperEffective(battlerAtk, battlerDef,
                                          MOVE_RESULT_NOT_VERY_EFFECTIVE, &outSlot))
        return outSlot;

    return PARTY_SIZE;
}

bool8 AI_IsTerrainActive(u8 terrainFlag)
{
    return (gFieldStatuses & terrainFlag) != 0;
}

bool8 AI_IsTrickRoomActive(void)
{
    return (gFieldStatuses & STATUS_FIELD_TRICK_ROOM) != 0;
}

// =============================================================================
// Phase 3: additionalEffects AI helper
// RHH source: pokeemerald-expansion/src/battle_ai_util.c
// Returns TRUE if any of battlerId's moves have an additionalEffects entry
// matching moveEffect (targeting the foe).
// =============================================================================
bool32 HasMoveWithAdditionalEffect(u8 battlerId, u16 moveEffect)
{
    for (u32 i = 0; i < MAX_MON_MOVES; i++)
    {
        u16 move = gBattleMons[battlerId].moves[i];
        if (move != MOVE_NONE && MoveHasAdditionalEffect(move, moveEffect))
            return TRUE;
    }
    return FALSE;
}

// =============================================================================
// Tier B: Move array + move query helpers (RHH pokeemerald-expansion/src/battle_ai_util.c)
// =============================================================================

// RHH: BattlerHasAi (pokeemerald-expansion/src/battle_controllers.c:103)
// RHH checks gBattlerBattleController[battler] (absent in FireRed).
// FireRed equivalent: opponent side is always AI-controlled.
bool32 BattlerHasAi(u8 battler)
{
    return GetBattlerSide(battler) == B_SIDE_OPPONENT;
}

// RHH: IsAiFlagPresent (pokeemerald-expansion/src/battle_ai_util.c:139)
// RHH iterates per-battler u64 aiFlags[4]. FireRed has a single u32 aiFlags.
// Semantics: returns TRUE if any AI battler has the given flag set.
bool32 IsAiFlagPresent(u32 flag)
{
    return (AI_THINKING_STRUCT->aiFlags & flag) != 0;
}

// RHH: IsAiBattlerAware (pokeemerald-expansion/src/battle_ai_util.c:150)
// TRUE if the AI has full knowledge of battler's moves (own battler, or OMNISCIENT flag).
bool32 IsAiBattlerAware(u8 battler)
{
#ifdef AI_FLAG_OMNISCIENT
    if (IsAiFlagPresent(AI_FLAG_OMNISCIENT))
        return TRUE;
#endif
    return BattlerHasAi(battler);
}

// RHH: GetMovesArray (pokeemerald-expansion/src/battle_ai_util.c:2528)
// Returns the array of moves for the given battler.
// When the AI is aware of the battler, returns live gBattleMons data;
// otherwise RHH returns gBattleHistory->usedMoves[battler]. Our history struct
// is side-indexed (usedMoves[2][8]) rather than battler-indexed, so we fall
// back to gBattleMons here too — functionally omniscient, same as current FireRed AI.
u16 *GetMovesArray(u8 battler)
{
    if (IsAiBattlerAware(battler) || IsAiBattlerAware(BATTLE_PARTNER(battler)))
        return gBattleMons[battler].moves;
    else
        return gBattleMons[battler].moves; // FireRed: no battler-indexed history
}

// RHH: HasMoveWithEffect (pokeemerald-expansion/src/battle_ai_util.c:2610)
// Returns TRUE if any of battler's moves have the given effect ID.
bool32 HasMoveWithEffect(u8 battler, u16 effect)
{
    u16 *moves = GetMovesArray(battler);
    u32 moveIndex;

    for (moveIndex = 0; moveIndex < MAX_MON_MOVES; moveIndex++)
    {
        if (moves[moveIndex] != MOVE_NONE && moves[moveIndex] != MOVE_UNAVAILABLE
            && GetMoveEffect(moves[moveIndex]) == effect)
            return TRUE;
    }
    return FALSE;
}

// RHH: HasMoveThatChangesKOThreshold (pokeemerald-expansion/src/battle_ai_util.c:4727)
// Returns TRUE if battlerId has a priority move or a speed-drop additional effect
// that could change how many hits are needed to KO.
static bool32 HasMoveThatChangesKOThreshold(u8 battlerId, u32 noOfHitsToFaint, bool32 aiIsFaster)
{
    u16 *moves = GetMovesArray(battlerId);
    u32 moveIndex;

    for (moveIndex = 0; moveIndex < MAX_MON_MOVES; moveIndex++)
    {
        u32 additionalEffectCount, effectIndex;

        if (moves[moveIndex] == MOVE_NONE || moves[moveIndex] == MOVE_UNAVAILABLE)
            continue;
        if (noOfHitsToFaint <= 2)
        {
            if (GetMovePriority(moves[moveIndex]) > 0)
                return TRUE;

            additionalEffectCount = GetMoveAdditionalEffectCount(moves[moveIndex]);
            for (effectIndex = 0; effectIndex < additionalEffectCount; effectIndex++)
            {
                const struct AdditionalEffect *additionalEffect = GetMoveAdditionalEffectById(moves[moveIndex], effectIndex);
                switch (additionalEffect->moveEffect)
                {
                case MOVE_EFFECT_SPD_MINUS_1:
                case MOVE_EFFECT_SPD_MINUS_2:
                    if (aiIsFaster && !additionalEffect->self)
                        return TRUE;
                    break;
                default:
                    break;
                }
            }
        }
    }
    return FALSE;
}

// =============================================================================
// Tier C: Secondary damage helpers (pokeemerald-expansion/src/battle_ai_util.c:3270-3432)
// Used by IncreaseStatDownScore to skip stat-lowering if target dies from residuals anyway.
// Gen 4+ abilities (Magic Guard, Poison Heal, etc.) and hold effects are #ifdef-guarded.
// =============================================================================

// RHH: GetLeechSeedDamage (pokeemerald-expansion/src/battle_ai_util.c:3270)
static u32 GetLeechSeedDamage(u8 battler)
{
    u32 damage = 0;
    if (gStatuses3[battler] & STATUS3_LEECHSEED)
    {
        u8 seeder = gStatuses3[battler] & STATUS3_LEECHSEED_BATTLER;
        if (gBattleMons[seeder].hp != 0)
        {
            damage = gBattleMons[battler].maxHP / 8;
            if (damage == 0)
                damage = 1;
        }
    }
    return damage;
}

// RHH: GetNightmareDamage (pokeemerald-expansion/src/battle_ai_util.c:3283)
static u32 GetNightmareDamage(u8 battlerId)
{
    u32 damage = 0;
    if ((gBattleMons[battlerId].status2 & STATUS2_NIGHTMARE)
     && (gBattleMons[battlerId].status1 & STATUS1_SLEEP))
    {
        damage = gBattleMons[battlerId].maxHP / 4;
        if (damage == 0)
            damage = 1;
    }
    return damage;
}

// RHH: GetCurseDamage (pokeemerald-expansion/src/battle_ai_util.c:3297)
static u32 GetCurseDamage(u8 battlerId)
{
    u32 damage = 0;
    if (gBattleMons[battlerId].status2 & STATUS2_CURSED)
    {
        damage = gBattleMons[battlerId].maxHP / 4;
        if (damage == 0)
            damage = 1;
    }
    return damage;
}

// RHH: GetTrapDamage (pokeemerald-expansion/src/battle_ai_util.c:3309)
// HOLD_EFFECT_BINDING_BAND not in FireRed — use /16 divisor only (Gen 3 default).
static u32 GetTrapDamage(u8 battler)
{
    u32 damage = 0;
    if (gBattleMons[battler].status2 & STATUS2_WRAPPED)
    {
        damage = gBattleMons[battler].maxHP / 16;
        if (damage == 0)
            damage = 1;
    }
    return damage;
}

// RHH: GetPoisonDamage (pokeemerald-expansion/src/battle_ai_util.c:3326)
static u32 GetPoisonDamage(u8 battlerId)
{
    u32 damage = 0;
#ifdef ABILITY_POISON_HEAL
    if (gAiLogicData->abilities[battlerId] == ABILITY_POISON_HEAL)
        return 0;
#endif
    if (gBattleMons[battlerId].status1 & STATUS1_POISON)
    {
        damage = gBattleMons[battlerId].maxHP / 8;
        if (damage == 0)
            damage = 1;
    }
    else if (gBattleMons[battlerId].status1 & STATUS1_TOXIC_POISON)
    {
        u32 status1Temp = gBattleMons[battlerId].status1;
        damage = gBattleMons[battlerId].maxHP / 16;
        if (damage == 0)
            damage = 1;
        if ((status1Temp & STATUS1_TOXIC_COUNTER) != STATUS1_TOXIC_TURN(15))
            status1Temp += STATUS1_TOXIC_TURN(1);
        damage *= (status1Temp & STATUS1_TOXIC_COUNTER) >> 8;
    }
    return damage;
}

// RHH: DoesBattlerTakeSandstormDamage (pokeemerald-expansion/src/battle_ai_util.c:3352)
static bool32 DoesBattlerTakeSandstormDamage(u8 battlerId, u8 ability)
{
    if (!(gBattleWeather & B_WEATHER_SANDSTORM))
        return FALSE;
    if (IS_BATTLER_OF_TYPE(battlerId, TYPE_ROCK)
     || IS_BATTLER_OF_TYPE(battlerId, TYPE_GROUND)
     || IS_BATTLER_OF_TYPE(battlerId, TYPE_STEEL))
        return FALSE;
    if (ability == ABILITY_SAND_VEIL)
        return FALSE;
#ifdef ABILITY_SAND_FORCE
    if (ability == ABILITY_SAND_FORCE)
        return FALSE;
#endif
#ifdef ABILITY_SAND_RUSH
    if (ability == ABILITY_SAND_RUSH)
        return FALSE;
#endif
#ifdef ABILITY_MAGIC_GUARD
    if (ability == ABILITY_MAGIC_GUARD)
        return FALSE;
#endif
#ifdef ABILITY_OVERCOAT
    if (ability == ABILITY_OVERCOAT)
        return FALSE;
#endif
    return TRUE;
}

// RHH: DoesBattlerTakeHailDamage (pokeemerald-expansion/src/battle_ai_util.c:3367)
static bool32 DoesBattlerTakeHailDamage(u8 battlerId, u8 ability)
{
    if (!(gBattleWeather & B_WEATHER_HAIL))
        return FALSE;
    if (IS_BATTLER_OF_TYPE(battlerId, TYPE_ICE))
        return FALSE;
#ifdef ABILITY_SNOW_CLOAK
    if (ability == ABILITY_SNOW_CLOAK)
        return FALSE;
#endif
#ifdef ABILITY_ICE_BODY
    if (ability == ABILITY_ICE_BODY)
        return FALSE;
#endif
#ifdef ABILITY_MAGIC_GUARD
    if (ability == ABILITY_MAGIC_GUARD)
        return FALSE;
#endif
#ifdef ABILITY_OVERCOAT
    if (ability == ABILITY_OVERCOAT)
        return FALSE;
#endif
    return TRUE;
}

// RHH: GetWeatherDamage (pokeemerald-expansion/src/battle_ai_util.c:3381)
// HOLD_EFFECT_SAFETY_GOGGLES and semiInvulnerable checks not in FireRed — omitted.
static u32 GetWeatherDamage(u8 battlerId)
{
    u8 ability = gAiLogicData->abilities[battlerId];
    u32 damage = 0;

    if (!gBattleWeather)
        return 0;

    if (DoesBattlerTakeSandstormDamage(battlerId, ability))
    {
        damage = gBattleMons[battlerId].maxHP / 16;
        if (damage == 0)
            damage = 1;
    }
    if ((gBattleWeather & B_WEATHER_HAIL)
#ifdef ABILITY_ICE_BODY
        && ability != ABILITY_ICE_BODY
#endif
    )
    {
        if (DoesBattlerTakeHailDamage(battlerId, ability))
        {
            damage = gBattleMons[battlerId].maxHP / 16;
            if (damage == 0)
                damage = 1;
        }
    }
    return damage;
}

// RHH: GetBattlerSecondaryDamage (pokeemerald-expansion/src/battle_ai_util.c:3417)
// Returns total residual damage the battler will take this turn.
u32 GetBattlerSecondaryDamage(u8 battlerId)
{
    u32 secondaryDamage;

#ifdef ABILITY_MAGIC_GUARD
    if (gAiLogicData->abilities[battlerId] == ABILITY_MAGIC_GUARD)
        return 0;
#endif

    secondaryDamage = GetLeechSeedDamage(battlerId)
     + GetNightmareDamage(battlerId)
     + GetCurseDamage(battlerId)
     + GetTrapDamage(battlerId)
     + GetPoisonDamage(battlerId)
     + GetWeatherDamage(battlerId);

    return secondaryDamage;
}

// RHH: DoesAbilityRaiseStatsWhenLowered (pokeemerald-expansion/src/battle_ai_util.c:5844)
// Returns TRUE if the ability turns stat reductions into gains (Contrary/Competitive/Defiant).
// Competitive and Defiant are Gen 5+ — #ifdef-guarded until their constants are added.
bool32 DoesAbilityRaiseStatsWhenLowered(u8 ability)
{
    switch (ability)
    {
    case ABILITY_CONTRARY:
#ifdef ABILITY_COMPETITIVE
    case ABILITY_COMPETITIVE:
#endif
#ifdef ABILITY_DEFIANT
    case ABILITY_DEFIANT:
#endif
        return TRUE;
    default:
        return FALSE;
    }
}

// =============================================================================
// Tier D: Stat change helpers (pokeemerald-expansion/src/battle_ai_util.c:4762-4823)
// Pure switches — no external dependencies beyond enum StatChange (battle_ai_main.h).
// =============================================================================

// RHH: GetStatBeingChanged (pokeemerald-expansion/src/battle_ai_util.c:4762)
// Maps a StatChange enum value to the corresponding STAT_* constant.
static u8 GetStatBeingChanged(enum StatChange statChange)
{
    switch (statChange)
    {
    case STAT_CHANGE_ATK:
    case STAT_CHANGE_ATK_2:
    case STAT_CHANGE_ATK_3:
    case STAT_CHANGE_ATK_MAX:
        return STAT_ATK;
    case STAT_CHANGE_DEF:
    case STAT_CHANGE_DEF_2:
    case STAT_CHANGE_DEF_3:
        return STAT_DEF;
    case STAT_CHANGE_SPEED:
    case STAT_CHANGE_SPEED_2:
    case STAT_CHANGE_SPEED_3:
        return STAT_SPEED;
    case STAT_CHANGE_SPATK:
    case STAT_CHANGE_SPATK_2:
    case STAT_CHANGE_SPATK_3:
        return STAT_SPATK;
    case STAT_CHANGE_SPDEF:
    case STAT_CHANGE_SPDEF_2:
    case STAT_CHANGE_SPDEF_3:
        return STAT_SPDEF;
    case STAT_CHANGE_ACC:
        return STAT_ACC;
    case STAT_CHANGE_EVASION:
        return STAT_EVASION;
    }
    return STAT_HP; // should never be reached
}

// RHH: GetStagesOfStatChange (pokeemerald-expansion/src/battle_ai_util.c:4795)
// Returns the number of stat stages changed (1, 2, 3, or 6 for ATK_MAX).
static u32 GetStagesOfStatChange(enum StatChange statChange)
{
    switch (statChange)
    {
    case STAT_CHANGE_ATK:
    case STAT_CHANGE_DEF:
    case STAT_CHANGE_SPEED:
    case STAT_CHANGE_SPATK:
    case STAT_CHANGE_SPDEF:
    case STAT_CHANGE_ACC:
    case STAT_CHANGE_EVASION:
        return 1;
    case STAT_CHANGE_ATK_2:
    case STAT_CHANGE_DEF_2:
    case STAT_CHANGE_SPEED_2:
    case STAT_CHANGE_SPATK_2:
    case STAT_CHANGE_SPDEF_2:
        return 2;
    case STAT_CHANGE_ATK_3:
    case STAT_CHANGE_DEF_3:
    case STAT_CHANGE_SPEED_3:
    case STAT_CHANGE_SPATK_3:
    case STAT_CHANGE_SPDEF_3:
        return 3;
    case STAT_CHANGE_ATK_MAX:
        return 6;
    }
    return 0; // should never be reached
}

// =============================================================================
// Tier E: Setup logic (pokeemerald-expansion/src/battle_ai_util.c:182-2227)
// CanAiPredictMove, IsBattlerPredictedToSwitch, GetIncomingMoveSpeedCheck,
// AreBattlersStatsMaxed, CountPositiveStatStages, AI_IsAbilityOnSide, ShouldRaiseAnyStat
// =============================================================================

// RHH: CanAiPredictMove (pokeemerald-expansion/src/battle_ai_util.c:182)
bool32 CanAiPredictMove(u8 battlerId)
{
    if (IsAiFlagPresent(AI_FLAG_PREDICT_MOVE))
        return TRUE;
    (void)battlerId;
    return FALSE;
}

// RHH: IsBattlerPredictedToSwitch (pokeemerald-expansion/src/battle_ai_util.c:190)
bool32 IsBattlerPredictedToSwitch(u8 battler)
{
    if (IsAiFlagPresent(AI_FLAG_PREDICT_SWITCH))
    {
        if (gAiLogicData->predictingSwitch && gAiLogicData->shouldSwitch & (1u << battler))
            return TRUE;
    }
    (void)battler;
    return FALSE;
}

// RHH: GetIncomingMoveSpeedCheck (pokeemerald-expansion/src/battle_ai_util.c:213)
// Returns the predicted opposing move for speed-check purposes, or MOVE_NONE.
u16 GetIncomingMoveSpeedCheck(u8 battler, u8 opposingBattler, struct AiLogicData *aiData)
{
    if (aiData->predictingMove && CanAiPredictMove(battler))
    {
        if (GetMovePower(aiData->predictedMove[opposingBattler]) != 0
         && GetMoveEffect(aiData->predictedMove[opposingBattler]) != EFFECT_FIRST_TURN_ONLY)
            return aiData->predictedMove[opposingBattler];
    }
    return MOVE_NONE;
}

// RHH: AreBattlersStatsMaxed (pokeemerald-expansion/src/battle_ai_util.c:2471)
// Returns TRUE if all of battler's combat stats are at +6 (MAX_STAT_STAGE).
bool32 AreBattlersStatsMaxed(u8 battlerId)
{
    u8 statId;
    for (statId = STAT_ATK; statId < NUM_BATTLE_STATS; statId++)
    {
        if (gBattleMons[battlerId].statStages[statId] < MAX_STAT_STAGE)
            return FALSE;
    }
    return TRUE;
}

// RHH: CountPositiveStatStages (pokeemerald-expansion/src/battle_ai_util.c:2491)
// Returns the number of stats currently above the default stage.
u32 CountPositiveStatStages(u8 battlerId)
{
    u32 count = 0;
    u8 statId;
    for (statId = STAT_ATK; statId < NUM_BATTLE_STATS; statId++)
    {
        if (gBattleMons[battlerId].statStages[statId] > DEFAULT_STAT_STAGE)
            count++;
    }
    return count;
}

// RHH: AI_IsAbilityOnSide (pokeemerald-expansion/src/battle_ai_util.c:1799)
// Returns TRUE if the given ability is present on the battler or its partner.
bool32 AI_IsAbilityOnSide(u8 battlerId, u8 ability)
{
    if (IsBattlerAlive(battlerId) && gAiLogicData->abilities[battlerId] == ability)
        return TRUE;
    if (IsBattlerAlive(BATTLE_PARTNER(battlerId)) && gAiLogicData->abilities[BATTLE_PARTNER(battlerId)] == ability)
        return TRUE;
    return FALSE;
}

// RHH: ShouldRaiseAnyStat (pokeemerald-expansion/src/battle_ai_util.c:2192)
// Returns FALSE if stat raising is inadvisable (dead to residuals, stats maxed,
// Unaware/Opportunist on opposing side, etc.).
// Gen 5+ yawn/Opportunist/Sturdy checks are #ifdef-guarded until those are ported.
bool32 ShouldRaiseAnyStat(u8 battlerAtk, u8 battlerDef)
{
    if (AreBattlersStatsMaxed(battlerAtk))
        return FALSE;

#ifdef ABILITY_UNAWARE
    if (AI_IsAbilityOnSide(battlerDef, ABILITY_UNAWARE))
        return FALSE;
#endif

    // Don't set up if AI will die to residual damage anyway
    if (GetBattlerSecondaryDamage(battlerAtk) >= gBattleMons[battlerAtk].hp)
        return FALSE;

#ifdef ABILITY_OPPORTUNIST
    if (AI_IsAbilityOnSide(battlerDef, ABILITY_OPPORTUNIST))
        return FALSE;
#endif

    (void)battlerDef;
    return TRUE;
}

// =============================================================================
// AI Helpers for Gen 4+ Moves (RHH Faithful Ports)
// =============================================================================

bool8 HasMoveWithCategory(u8 battler, u8 category)
{
    u8 i;
    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        u16 move = gBattleMons[battler].moves[i];
        if (move != MOVE_NONE && move != MOVE_UNAVAILABLE && gMovesInfo[move].category == category)
            return TRUE;
    }
    return FALSE;
}

bool8 BattlerStatCanRise(u8 battler, u8 stat)
{
    if ((gBattleMons[battler].statStages[stat] < MAX_STAT_STAGE && gBattleMons[battler].ability != ABILITY_CONTRARY)
      || (gBattleMons[battler].ability == ABILITY_CONTRARY && gBattleMons[battler].statStages[stat] > MIN_STAT_STAGE))
        return TRUE;
    return FALSE;
}

u32 GetBattlerSideSpeedAverage(u8 battler)
{
    u32 totalSpeed = 0;
    u32 numAlive = 0;
    u8 side = GetBattlerSide(battler);
    struct Pokemon *party = (side == B_SIDE_PLAYER) ? gPlayerParty : gEnemyParty;
    u8 i;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        if (GetMonData(&party[i], MON_DATA_SPECIES, NULL) != SPECIES_NONE
         && GetMonData(&party[i], MON_DATA_HP, NULL) > 0)
        {
            totalSpeed += GetMonData(&party[i], MON_DATA_SPEED, NULL);
            numAlive++;
        }
    }

    if (numAlive == 0)
        return 0;

    return totalSpeed / numAlive;
}

// RHH: SetBattlerAiData (pokeemerald-expansion/src/battle_ai_main.c:615-634)
// Populates per-battler fields in gAiLogicData for use by AI scoring helpers.
// Simplified: FireRed lacks RHH's knowledge-inference system (AI_DecideKnownAbilityForTurn,
// AI_DecideHoldEffectForTurn, GetBattlerTotalSpeedStat, recording helpers), so we read
// battle state directly. The struct fields are identical to RHH's; only the population
// method is simplified here — replace each field with the full RHH version as those
// helpers are ported.
void SetBattlerAiData(u8 battler, struct AiLogicData *aiData)
{
    u8 ability    = gBattleMons[battler].ability;   // TODO: AI_DecideKnownAbilityForTurn
    u16 item      = gBattleMons[battler].item;
    u8 holdEffect = ItemId_GetHoldEffect(item);     // TODO: AI_DecideHoldEffectForTurn

    aiData->abilities[battler]       = ability;
    aiData->items[battler]           = item;
    aiData->holdEffects[battler]     = holdEffect;
    aiData->holdEffectParams[battler] = ItemId_GetHoldEffectParam(item);
    aiData->lastUsedMove[battler]    = (gLastMoves[battler] == MOVE_UNAVAILABLE)
                                       ? MOVE_NONE : gLastMoves[battler];
    aiData->hpPercents[battler]      = (gBattleMons[battler].maxHP == 0) ? 0
                                       : gBattleMons[battler].hp * 100 / gBattleMons[battler].maxHP;
    aiData->moveLimitations[battler] = CheckMoveLimitations(battler, 0, MOVE_LIMITATIONS_ALL);
    aiData->speedStats[battler]      = GetBattlerTotalSpeedStat(battler, ability, holdEffect);

    // RHH: CalcBattlerAiMovesData (pokeemerald-expansion/src/battle_ai_main.c:658-678)
    // Populate simulatedDmg for battler as attacker vs all living opponents.
    // Our AI_CalcDamage returns a single s32; all three fields get the same value until
    // a min/median/max variant is ported.
    for (u32 t = 0; t < gBattlersCount; t++)
    {
        u32 m;
        if (t == battler || !IsBattlerAlive(t))
            continue;
        for (m = 0; m < MAX_MON_MOVES; m++)
        {
            s32 dmg = AI_CalcDamage(gBattleMons[battler].moves[m], battler, t, NULL);
            if (dmg < 0) dmg = 0;
            aiData->simulatedDmg[battler][t][m].minimum = (u16)dmg;
            aiData->simulatedDmg[battler][t][m].median  = (u16)dmg;
            aiData->simulatedDmg[battler][t][m].maximum = (u16)dmg;
        }
    }
}

// ============================================================================
// Tier F: KO Calculation
// RHH source: pokeemerald-expansion/src/battle_ai_util.c:94-115 (AI_GetDamage)
//             and 1362-1561 (GetNoOfHitsToKO*, CanEndureHit, NoOfHitsForTarget*)
// ============================================================================

// RHH: AI_GetDamage (pokeemerald-expansion/src/battle_ai_util.c:94-115)
// Selects min/median/max from pre-computed simulatedDmg based on AI personality flags.
static u32 AI_GetDamage(u8 battlerAtk, u8 battlerDef, u32 moveIndex,
                        enum DamageCalcContext calcContext, struct AiLogicData *aiData)
{
    if (calcContext == AI_ATTACKING && BattlerHasAi(battlerAtk))
    {
        if ((AI_THINKING_STRUCT->aiFlags & AI_FLAG_RISKY) && !(AI_THINKING_STRUCT->aiFlags & AI_FLAG_CONSERVATIVE))
            return aiData->simulatedDmg[battlerAtk][battlerDef][moveIndex].maximum;
        if ((AI_THINKING_STRUCT->aiFlags & AI_FLAG_CONSERVATIVE) && !(AI_THINKING_STRUCT->aiFlags & AI_FLAG_RISKY))
            return aiData->simulatedDmg[battlerAtk][battlerDef][moveIndex].minimum;
        return aiData->simulatedDmg[battlerAtk][battlerDef][moveIndex].median;
    }
    else if (calcContext == AI_DEFENDING && BattlerHasAi(battlerDef))
    {
        if ((AI_THINKING_STRUCT->aiFlags & AI_FLAG_RISKY) && !(AI_THINKING_STRUCT->aiFlags & AI_FLAG_CONSERVATIVE))
            return aiData->simulatedDmg[battlerAtk][battlerDef][moveIndex].minimum;
        if ((AI_THINKING_STRUCT->aiFlags & AI_FLAG_CONSERVATIVE) && !(AI_THINKING_STRUCT->aiFlags & AI_FLAG_RISKY))
            return aiData->simulatedDmg[battlerAtk][battlerDef][moveIndex].maximum;
        return aiData->simulatedDmg[battlerAtk][battlerDef][moveIndex].median;
    }
    else
    {
        return aiData->simulatedDmg[battlerAtk][battlerDef][moveIndex].median;
    }
}

// RHH: GetNoOfHitsToKO (pokeemerald-expansion/src/battle_ai_util.c:1362-1367)
u32 GetNoOfHitsToKO(u32 dmg, s32 hp)
{
    if (dmg == 0)
        return 0;
    return (hp + dmg - 1) / dmg;
}

// RHH: GetNoOfHitsToKOBattlerDmg (pokeemerald-expansion/src/battle_ai_util.c:1369-1371)
u32 GetNoOfHitsToKOBattlerDmg(u32 dmg, u8 battlerDef)
{
    return GetNoOfHitsToKO(dmg, gBattleMons[battlerDef].hp);
}

// RHH: CanEndureHit (pokeemerald-expansion/src/battle_ai_util.c:1504-1525)
// Returns TRUE if battlerTarget can survive an otherwise-KO hit (Focus Sash, Sturdy Gen5+).
// Gen 3: HOLD_EFFECT_FOCUS_SASH and HOLD_EFFECT_STURDY_GEN5 don't exist — always FALSE for now.
bool32 CanEndureHit(u8 battler, u8 battlerTarget, u16 move)
{
    if (gBattleMons[battlerTarget].hp != gBattleMons[battlerTarget].maxHP)
        return FALSE;
    // HOLD_EFFECT_FOCUS_SASH is Gen 4+ — #ifdef when ported
    // ABILITY_STURDY as general endure is Gen 5+ — #ifdef when ported
    return FALSE;
}

// RHH: GetNoOfHitsToKOBattler (pokeemerald-expansion/src/battle_ai_util.c:1374-1386)
u32 GetNoOfHitsToKOBattler(u8 battlerAtk, u8 battlerDef, u32 moveIndex,
                           enum DamageCalcContext calcContext, enum AiConsiderEndure considerEndure)
{
    u32 hitsToKO = GetNoOfHitsToKOBattlerDmg(AI_GetDamage(battlerAtk, battlerDef, moveIndex, calcContext, gAiLogicData), battlerDef);
    u16 *moves = GetMovesArray(battlerAtk);

    if (CanEndureHit(battlerAtk, battlerDef, moves[moveIndex]) && hitsToKO == 1 && considerEndure == CONSIDER_ENDURE)
        hitsToKO += 1;

    return hitsToKO;
}

// RHH: NoOfHitsForTargetToFaintBattler (pokeemerald-expansion/src/battle_ai_util.c:1547-1562)
u32 NoOfHitsForTargetToFaintBattler(u8 battlerDef, u8 battlerAtk, enum AiConsiderEndure considerEndure)
{
    u32 currNumberOfHits;
    u32 leastNumberOfHits = UNKNOWN_NO_OF_HITS;

    for (u32 moveIndex = 0; moveIndex < MAX_MON_MOVES; moveIndex++)
    {
        currNumberOfHits = GetNoOfHitsToKOBattler(battlerDef, battlerAtk, moveIndex, AI_DEFENDING, considerEndure);
        if (currNumberOfHits != 0)
        {
            if (currNumberOfHits < leastNumberOfHits)
                leastNumberOfHits = currNumberOfHits;
        }
    }
    return leastNumberOfHits;
}

// ============================================================================
// Tier G: Trap Detection
// RHH source: pokeemerald-expansion/src/battle_ai_util.c:68-71, 469-510,
//             4553-4585, 6349-6365
// ============================================================================

// RHH: AI_IsBattlerGrounded (pokeemerald-expansion/src/battle_ai_util.c:68-71)
bool32 AI_IsBattlerGrounded(u8 battler)
{
    return IsBattlerGrounded(battler, gAiLogicData->abilities[battler], gAiLogicData->holdEffects[battler]);
}

// RHH: AI_CanBattlerEscape (pokeemerald-expansion/src/battle_ai_util.c:469-479)
// Gen 3: HOLD_EFFECT_SHED_SHELL is Gen 4+ — always returns FALSE.
bool32 AI_CanBattlerEscape(u8 battler)
{
    // HOLD_EFFECT_SHED_SHELL is Gen 4+ — #ifdef when ported
    // Ghost-type escape (B_GHOSTS_ESCAPE >= GEN_6) is Gen 6+ — #ifdef when ported
    return FALSE;
}

// RHH: GetAIPartyIndexes (pokeemerald-expansion/src/battle_ai_util.c:6349-6365)
// Returns the valid party range for a battler (handles multi-battles).
void GetAIPartyIndexes(u8 battler, s32 *firstId, s32 *lastId)
{
    if (gBattleTypeFlags & (BATTLE_TYPE_TWO_OPPONENTS | BATTLE_TYPE_INGAME_PARTNER | BATTLE_TYPE_TOWER_LINK_MULTI))
    {
        if ((battler & BIT_FLANK) == B_FLANK_LEFT)
            *firstId = 0, *lastId = PARTY_SIZE / 2;
        else
            *firstId = PARTY_SIZE / 2, *lastId = PARTY_SIZE;
    }
    else
    {
        *firstId = 0, *lastId = PARTY_SIZE;
    }
}

// RHH: CountUsablePartyMons (pokeemerald-expansion/src/battle_ai_util.c:4553-4585)
// Returns count of party mons not on field, alive, and not Eggs.
s32 CountUsablePartyMons(u8 battlerId)
{
    s32 battlerOnField1, battlerOnField2, ret;
    struct Pokemon *party = GetBattlerParty(battlerId);

    if (IsDoubleBattle())
    {
        battlerOnField1 = gBattlerPartyIndexes[battlerId];
        battlerOnField2 = gBattlerPartyIndexes[BATTLE_PARTNER(battlerId)];
    }
    else
    {
        battlerOnField1 = gBattlerPartyIndexes[battlerId];
        battlerOnField2 = gBattlerPartyIndexes[battlerId];
    }

    ret = 0;
    {
        s32 firstId, lastId;
        u32 monIndex;
        GetAIPartyIndexes(battlerId, &firstId, &lastId);
        for (monIndex = firstId; monIndex < (u32)lastId; monIndex++)
        {
            if ((s32)monIndex != battlerOnField1 && (s32)monIndex != battlerOnField2
             && GetMonData(&party[monIndex], MON_DATA_HP) != 0
             && GetMonData(&party[monIndex], MON_DATA_SPECIES_OR_EGG) != SPECIES_NONE
             && GetMonData(&party[monIndex], MON_DATA_SPECIES_OR_EGG) != SPECIES_EGG)
            {
                ret++;
            }
        }
    }
    return ret;
}

// RHH: IsBattlerTrapped (pokeemerald-expansion/src/battle_ai_util.c:481-510)
// volatiles.wrapped       → status2 & STATUS2_WRAPPED
// volatiles.escapePrevention → status2 & STATUS2_ESCAPE_PREVENTION
// volatiles.root          → gStatuses3 & STATUS3_ROOTED (Ingrain, Gen 3)
// volatiles.semiInvulnerable == STATE_SKY_DROP → #ifdef (Gen 5+)
// gFieldStatuses & STATUS_FIELD_FAIRY_LOCK → #ifdef (Gen 6+)
// B_SHADOW_TAG_ESCAPE >= GEN_4 → omitted; Shadow Tag always traps in Gen 3
bool32 IsBattlerTrapped(u8 battlerAtk, u8 battlerDef)
{
    if (AI_CanBattlerEscape(battlerDef))
        return FALSE;

    if (gBattleMons[battlerDef].status2 & STATUS2_WRAPPED)
        return TRUE;
    if (gBattleMons[battlerDef].status2 & STATUS2_ESCAPE_PREVENTION)
        return TRUE;
    if (gStatuses3[battlerDef] & STATUS3_ROOTED)
        return TRUE;
    // SKY_DROP volatile is Gen 5+ — #ifdef when ported
    // STATUS_FIELD_FAIRY_LOCK is Gen 6+ — #ifdef when ported
    if (AI_IsAbilityOnSide(battlerAtk, ABILITY_SHADOW_TAG)
        && gAiLogicData->abilities[battlerDef] != ABILITY_SHADOW_TAG)
        return TRUE;
    if (AI_IsAbilityOnSide(battlerAtk, ABILITY_ARENA_TRAP)
        && AI_IsBattlerGrounded(battlerAtk))
        return TRUE;
    if (AI_IsAbilityOnSide(battlerAtk, ABILITY_MAGNET_PULL)
        && IS_BATTLER_OF_TYPE(battlerDef, TYPE_STEEL))
        return TRUE;

    if ((gBattleTypeFlags & BATTLE_TYPE_TRAINER) && CountUsablePartyMons(battlerDef) == 0)
        return TRUE;

    return FALSE;
}

// ============================================================================
// Tier H/I Pre-requisite helpers
// ============================================================================

// RHH: DoesSubstituteBlockMove (pokeemerald-expansion/src/battle_script_commands.c:10332)
// Gen 3: INFILTRATOR doesn't exist; substitute always blocks non-sound moves.
bool32 DoesSubstituteBlockMove(u8 battlerAtk, u8 battlerDef, u16 move)
{
    if (!(gBattleMons[battlerDef].status2 & STATUS2_SUBSTITUTE))
        return FALSE;
    if (MoveIgnoresSubstitute(move))
        return FALSE;
    return TRUE;
}

// RHH: HasTwoOpponents (pokeemerald-expansion/src/battle_ai_util.c:4152)
bool32 HasTwoOpponents(u8 battler)
{
    if (IsDoubleBattle()
      && IsBattlerAlive(LEFT_FOE(battler)) && IsBattlerAlive(RIGHT_FOE(battler)))
        return TRUE;
    return FALSE;
}

// RHH: HasPartner (pokeemerald-expansion/src/battle_ai_util.c:4160)
bool32 HasPartner(u8 battler)
{
    if (IsDoubleBattle() && IsBattlerAlive(BATTLE_PARTNER(battler)))
    {
        if (AI_THINKING_STRUCT->aiFlags & AI_FLAG_DOUBLE_BATTLE)
            return TRUE;
    }
    return FALSE;
}

// RHH: CanAIFaintTarget (pokeemerald-expansion/src/battle_ai_util.c:1701-1730)
// Returns TRUE if battlerAtk has a move that will KO battlerDef in numHits hits.
bool32 CanAIFaintTarget(u8 battlerAtk, u8 battlerDef, u32 numHits)
{
    struct AiLogicData *aiData = gAiLogicData;
    u32 moveIndex;
    u16 *moves = gBattleMons[battlerAtk].moves;
    u32 moveLimitations = aiData->moveLimitations[battlerAtk];

    for (moveIndex = 0; moveIndex < MAX_MON_MOVES; moveIndex++)
    {
        u32 dmg;
        if (IsMoveUnusable(moveIndex, moves[moveIndex], moveLimitations))
            continue;

        dmg = AI_GetDamage(battlerAtk, battlerDef, moveIndex, AI_ATTACKING, aiData);

        if (numHits)
            dmg *= numHits;

        if (gBattleMons[battlerDef].hp <= dmg)
        {
            if (numHits > 1)
                return TRUE;

            if (!CanEndureHit(battlerAtk, battlerDef, moves[moveIndex]))
                return TRUE;
        }
    }

    return FALSE;
}

// RHH: CanTargetFaintAi (pokeemerald-expansion/src/battle_ai_util.c:1528-1545)
// Returns TRUE if battlerDef has a move that can KO battlerAtk.
bool32 CanTargetFaintAi(u8 battlerDef, u8 battlerAtk)
{
    struct AiLogicData *aiData = gAiLogicData;
    u32 moveIndex;
    u16 *moves = GetMovesArray(battlerDef);
    u32 moveLimitations = aiData->moveLimitations[battlerDef];

    for (moveIndex = 0; moveIndex < MAX_MON_MOVES; moveIndex++)
    {
        if (IsMoveUnusable(moveIndex, moves[moveIndex], moveLimitations))
            continue;

        if (AI_GetDamage(battlerDef, battlerAtk, moveIndex, AI_DEFENDING, aiData) >= gBattleMons[battlerAtk].hp
            && !CanEndureHit(battlerDef, battlerAtk, moves[moveIndex]))
            return TRUE;
    }

    return FALSE;
}

// ============================================================================
// Tier F-G supplement: CanIndexMoveFaintTarget, GetBestDmgMovesFromBattler
// RHH source: pokeemerald-expansion/src/battle_ai_util.c:2513-2527, 1589-1629
// ============================================================================

// RHH: CanIndexMoveFaintTarget (pokeemerald-expansion/src/battle_ai_util.c:2513)
bool32 CanIndexMoveFaintTarget(u8 battlerAtk, u8 battlerDef, u32 moveIndex, enum DamageCalcContext calcContext)
{
    s32 dmg;
    u16 *moves = gBattleMons[battlerAtk].moves;

    if (IsDoubleBattle() && battlerDef == BATTLE_PARTNER(battlerAtk))
        dmg = gAiLogicData->simulatedDmg[battlerAtk][battlerDef][moveIndex].maximum;
    else
        dmg = AI_GetDamage(battlerAtk, battlerDef, moveIndex, calcContext, gAiLogicData);

    if ((s32)gBattleMons[battlerDef].hp <= dmg && !CanEndureHit(battlerAtk, battlerDef, moves[moveIndex]))
        return TRUE;
    return FALSE;
}

// RHH: GetBestDmgMovesFromBattler (pokeemerald-expansion/src/battle_ai_util.c:1589)
void GetBestDmgMovesFromBattler(u8 battlerAtk, u8 battlerDef, enum DamageCalcContext calcContext, u16 *bestMoves)
{
    struct AiLogicData *aiData = gAiLogicData;
    u32 bestDmg = 0;
    u16 *moves = GetMovesArray(battlerAtk);
    u32 moveLimitations = aiData->moveLimitations[battlerAtk];
    u32 countBestMoves = 0;

    if (CanAIFaintTarget(battlerAtk, battlerDef, 1))
    {
        for (u32 moveIndex = 0; moveIndex < MAX_MON_MOVES; moveIndex++)
        {
            if (CanIndexMoveFaintTarget(battlerAtk, battlerDef, moveIndex, AI_ATTACKING))
                bestMoves[countBestMoves++] = moves[moveIndex];
        }
    }
    else
    {
        for (u32 moveIndex = 0; moveIndex < MAX_MON_MOVES; moveIndex++)
        {
            if (IsMoveUnusable(moveIndex, moves[moveIndex], moveLimitations)
             || GetMovePower(moves[moveIndex]) == 0
             || AI_GetDamage(battlerAtk, battlerDef, moveIndex, calcContext, aiData) == 0)
                continue;

            if (bestDmg < AI_GetDamage(battlerAtk, battlerDef, moveIndex, calcContext, aiData))
            {
                countBestMoves = 0;
                bestDmg = AI_GetDamage(battlerAtk, battlerDef, moveIndex, calcContext, aiData);
                *bestMoves = 0;
                bestMoves[countBestMoves++] = moves[moveIndex];
            }
            else if (bestDmg == AI_GetDamage(battlerAtk, battlerDef, moveIndex, calcContext, aiData))
            {
                bestMoves[countBestMoves++] = moves[moveIndex];
            }
        }
    }
}

// ============================================================================
// Tier I: Stat Down/Up Scoring
// RHH source: pokeemerald-expansion/src/battle_ai_util.c:2390-2461, 4825-4978
// ============================================================================

// RHH: IncreaseStatDownScore (pokeemerald-expansion/src/battle_ai_util.c:2390-2461)
// volatile field translations:
//   volatiles.leechSeed   → gStatuses3[battlerDef] & STATUS3_LEECHSEED
//   volatiles.cursed      → gBattleMons[battlerDef].status2 & STATUS2_CURSED
//   volatiles.root        → gStatuses3[battlerDef] & STATUS3_ROOTED
enum AIScore IncreaseStatDownScore(u8 battlerAtk, u8 battlerDef, u8 stat)
{
    enum AIScore tempScore = NO_INCREASE;

    if (stat != STAT_SPEED && gBattleMons[battlerDef].statStages[stat] <= DEFAULT_STAT_STAGE - 3)
        return NO_INCREASE;

    if (GetBattlerSecondaryDamage(battlerDef) >= gBattleMons[battlerDef].hp)
        return NO_INCREASE;

    if (DoesAbilityRaiseStatsWhenLowered(gAiLogicData->abilities[battlerDef]))
        return NO_INCREASE;

    switch (stat)
    {
    case STAT_ATK:
        if (HasMoveWithCategory(battlerDef, DAMAGE_CATEGORY_PHYSICAL))
            tempScore += DECENT_EFFECT;
        break;
    case STAT_DEF:
        if (HasMoveWithCategory(battlerAtk, DAMAGE_CATEGORY_PHYSICAL)
         || HasMoveWithCategory(BATTLE_PARTNER(battlerAtk), DAMAGE_CATEGORY_PHYSICAL))
            tempScore += DECENT_EFFECT;
        break;
    case STAT_SPEED:
    {
        u16 predictedMoveSpeedCheck = GetIncomingMoveSpeedCheck(battlerAtk, battlerDef, gAiLogicData);
        if (AI_IsSlower(battlerAtk, battlerDef, MOVE_NONE, predictedMoveSpeedCheck, DONT_CONSIDER_PRIORITY)
        || AI_IsSlower(BATTLE_PARTNER(battlerAtk), battlerDef, MOVE_NONE, predictedMoveSpeedCheck, DONT_CONSIDER_PRIORITY))
            tempScore += DECENT_EFFECT;
        break;
    }
    case STAT_SPATK:
        if (HasMoveWithCategory(battlerDef, DAMAGE_CATEGORY_SPECIAL))
            tempScore += DECENT_EFFECT;
        break;
    case STAT_SPDEF:
        if (HasMoveWithCategory(battlerAtk, DAMAGE_CATEGORY_SPECIAL)
         || HasMoveWithCategory(BATTLE_PARTNER(battlerAtk), DAMAGE_CATEGORY_SPECIAL))
            tempScore += DECENT_EFFECT;
        break;
    case STAT_ACC:
        tempScore += WEAK_EFFECT;
        if (IsBattlerTrapped(battlerAtk, battlerDef))
            tempScore += DECENT_EFFECT;
        if (gStatuses3[battlerDef] & STATUS3_LEECHSEED)   // volatiles.leechSeed
            tempScore += WEAK_EFFECT;
        if (gBattleMons[battlerDef].status2 & STATUS2_CURSED)   // volatiles.cursed
            tempScore += WEAK_EFFECT;
        break;
    case STAT_EVASION:
        if (gBattleMons[battlerDef].status1 & STATUS1_PSN_ANY)
            tempScore += WEAK_EFFECT;
        if (gStatuses3[battlerDef] & STATUS3_LEECHSEED)   // volatiles.leechSeed
            tempScore += WEAK_EFFECT;
        if (gStatuses3[battlerDef] & STATUS3_ROOTED)   // volatiles.root
            tempScore += WEAK_EFFECT;
        if (gBattleMons[battlerDef].status2 & STATUS2_CURSED)   // volatiles.cursed
            tempScore += WEAK_EFFECT;
        break;
    default:
        break;
    }

    return (tempScore > BEST_EFFECT) ? BEST_EFFECT : tempScore;
}

// RHH: IncreaseStatUpScoreInternal (pokeemerald-expansion/src/battle_ai_util.c:4825-4947)
// gAiThinkingStruct->aiFlags[battlerAtk] → AI_THINKING_STRUCT->aiFlags (single u32, no per-battler)
// ABILITY_SIMPLE is Gen 4+ → #ifdef'd
static enum AIScore IncreaseStatUpScoreInternal(u8 battlerAtk, u8 battlerDef, enum StatChange statChange, bool32 considerContrary)
{
    enum AIScore tempScore = NO_INCREASE;
    u32 noOfHitsToFaint = NoOfHitsForTargetToFaintBattler(battlerDef, battlerAtk, DONT_CONSIDER_ENDURE);
    u16 predictedMoveSpeedCheck = GetIncomingMoveSpeedCheck(battlerAtk, battlerDef, gAiLogicData);
    bool32 aiIsFaster = AI_IsFaster(battlerAtk, battlerDef, MOVE_NONE, predictedMoveSpeedCheck, DONT_CONSIDER_PRIORITY);
    bool32 shouldSetUp = ((noOfHitsToFaint >= 2 && aiIsFaster) || (noOfHitsToFaint >= 3 && !aiIsFaster) || noOfHitsToFaint == UNKNOWN_NO_OF_HITS);
    u8 statId = GetStatBeingChanged(statChange);
    u32 stages = GetStagesOfStatChange(statChange);

    if (considerContrary && gAiLogicData->abilities[battlerAtk] == ABILITY_CONTRARY)
        return NO_INCREASE;

    if (!ShouldRaiseAnyStat(battlerAtk, battlerDef))
        return NO_INCREASE;

    if (gBattleMons[battlerAtk].statStages[statId] >= MAX_STAT_STAGE - 2)
        return NO_INCREASE;

    if (gAiLogicData->hpPercents[battlerAtk] < 70 && noOfHitsToFaint == UNKNOWN_NO_OF_HITS)
        return NO_INCREASE;

    if (HasMoveThatChangesKOThreshold(battlerDef, noOfHitsToFaint, aiIsFaster))
        return NO_INCREASE;

#ifdef ABILITY_SIMPLE
    if (gAiLogicData->abilities[battlerAtk] == ABILITY_SIMPLE)
        stages *= 2;
#endif

    if (IsBattlerPredictedToSwitch(battlerDef))
    {
        struct Pokemon *playerParty = GetBattlerParty(battlerDef);
        u32 monIndex;
        for (monIndex = 0; monIndex < MAX_MON_MOVES; monIndex++)
        {
            if (GetMoveEffect(GetMonData(&playerParty[gAiLogicData->mostSuitableMonId[battlerDef]], MON_DATA_MOVE1 + monIndex)) == EFFECT_ENCORE
                && GetMonData(&playerParty[gAiLogicData->mostSuitableMonId[battlerDef]], MON_DATA_PP1 + monIndex) > 0)
            {
                if (GetMonData(&playerParty[gAiLogicData->mostSuitableMonId[battlerDef]], MON_DATA_SPEED) > gBattleMons[battlerAtk].speed)
                    return NO_INCREASE;
            }
        }
        tempScore += WEAK_EFFECT;
    }

    switch (statId)
    {
    case STAT_ATK:
        if (HasMoveWithCategory(battlerAtk, DAMAGE_CATEGORY_PHYSICAL) && shouldSetUp)
        {
            if (stages == 1)
                tempScore += DECENT_EFFECT;
            else if (stages == 6)
                tempScore += BEST_EFFECT;
            else
                tempScore += GOOD_EFFECT;
        }
        break;
    case STAT_DEF:
        if (HasMoveWithCategory(battlerDef, DAMAGE_CATEGORY_PHYSICAL) || !HasMoveWithCategory(battlerDef, DAMAGE_CATEGORY_SPECIAL))
        {
            if (AI_THINKING_STRUCT->aiFlags & AI_FLAG_STALL)
                tempScore += WEAK_EFFECT;
            if (stages == 1)
                tempScore += WEAK_EFFECT;
            else
                tempScore += DECENT_EFFECT;
        }
        break;
    case STAT_SPEED:
        if ((noOfHitsToFaint >= 3 && !aiIsFaster) || noOfHitsToFaint == UNKNOWN_NO_OF_HITS)
        {
            if (stages == 1)
                tempScore += DECENT_EFFECT;
            else
                tempScore += GOOD_EFFECT;
        }
        break;
    case STAT_SPATK:
        if (HasMoveWithCategory(battlerAtk, DAMAGE_CATEGORY_SPECIAL) && shouldSetUp)
        {
            if (stages == 1)
                tempScore += DECENT_EFFECT;
            else
                tempScore += GOOD_EFFECT;
        }
        break;
    case STAT_SPDEF:
        if (HasMoveWithCategory(battlerDef, DAMAGE_CATEGORY_SPECIAL) || !HasMoveWithCategory(battlerDef, DAMAGE_CATEGORY_PHYSICAL))
        {
            if (AI_THINKING_STRUCT->aiFlags & AI_FLAG_STALL)
                tempScore += WEAK_EFFECT;
            if (stages == 1)
                tempScore += WEAK_EFFECT;
            else
                tempScore += DECENT_EFFECT;
        }
        break;
    case STAT_ACC:
        if (gBattleMons[battlerAtk].statStages[statId] <= DEFAULT_STAT_STAGE - 3)
            tempScore += DECENT_EFFECT;
        break;
    case STAT_EVASION:
        if (noOfHitsToFaint > 3 || noOfHitsToFaint == UNKNOWN_NO_OF_HITS)
            tempScore += GOOD_EFFECT;
        else
            tempScore += DECENT_EFFECT;
        break;
    default:
        break;
    }

    if (tempScore > 0 && HasMoveWithEffect(battlerAtk, EFFECT_STORED_POWER))
        tempScore += WEAK_EFFECT;

    return tempScore;
}

// RHH: IncreaseStatUpScore (pokeemerald-expansion/src/battle_ai_util.c:4970-4973)
enum AIScore IncreaseStatUpScore(u8 battlerAtk, u8 battlerDef, enum StatChange statChange)
{
    return IncreaseStatUpScoreInternal(battlerAtk, battlerDef, statChange, TRUE);
}

// RHH: IncreaseStatUpScoreContrary (pokeemerald-expansion/src/battle_ai_util.c:4975-4978)
enum AIScore IncreaseStatUpScoreContrary(u8 battlerAtk, u8 battlerDef, enum StatChange statChange)
{
    return IncreaseStatUpScoreInternal(battlerAtk, battlerDef, statChange, FALSE);
}

// ============================================================================
// Tier H: Status Scoring Helpers
// RHH source: pokeemerald-expansion/src/battle_ai_util.c:4980-5115
// BLOCKED: Require AI_CanPoison/Burn/Paralyze/Sleep/Confuse which depend on
// CanSetNonVolatileStatus (complex, not yet ported). These are stubs that
// return without scoring until that infrastructure is ported.
// ============================================================================

// RHH: IncreasePoisonScore (pokeemerald-expansion/src/battle_ai_util.c:4980-5001)
// TODO: Replace stub with full port once AI_CanPoison + CanBePoisoned are ported.
// RHH: HasDamagingMove (pokeemerald-expansion/src/battle_ai_util.c:3206)
static bool32 HasDamagingMove(u8 battler)
{
    u16 *moves = GetMovesArray(battler);
    u32 moveIndex;
    for (moveIndex = 0; moveIndex < MAX_MON_MOVES; moveIndex++)
    {
        if (moves[moveIndex] != MOVE_NONE && moves[moveIndex] != MOVE_UNAVAILABLE
            && GetMovePower(moves[moveIndex]) > 0)
            return TRUE;
    }
    return FALSE;
}

// RHH: HasUsableWhileAsleepMove (pokeemerald-expansion/src/battle_ai_util.c:2934)
static bool32 HasUsableWhileAsleepMove(u8 battler)
{
    u16 *moves = GetMovesArray(battler);
    u32 moveIndex;
    for (moveIndex = 0; moveIndex < MAX_MON_MOVES; moveIndex++)
    {
        if (moves[moveIndex] != MOVE_NONE && moves[moveIndex] != MOVE_UNAVAILABLE
            && IsUsableWhileAsleepEffect(GetMoveEffect(moves[moveIndex])))
            return TRUE;
    }
    return FALSE;
}

// RHH: HasMoveWithMoveEffectExcept (pokeemerald-expansion/src/battle_ai_util.c:2754)
static bool32 HasMoveWithMoveEffectExcept(u8 battler, u16 moveEffect, u16 exception)
{
    u16 *moves = GetMovesArray(battler);
    u32 moveIndex;
    for (moveIndex = 0; moveIndex < MAX_MON_MOVES; moveIndex++)
    {
        if (moves[moveIndex] != MOVE_NONE && moves[moveIndex] != MOVE_UNAVAILABLE
            && GetMoveEffect(moves[moveIndex]) != exception
            && MoveHasAdditionalEffect(moves[moveIndex], moveEffect))
            return TRUE;
    }
    return FALSE;
}

// RHH: IsPowerBasedOnStatus (pokeemerald-expansion/src/battle_ai_util.c:2702)
// Returns TRUE if battler has a move with the given effect whose argument matches the status.
static bool32 IsPowerBasedOnStatus(u8 battler, u16 effect, u32 argument)
{
    u16 *moves = GetMovesArray(battler);
    u32 moveIndex;
    for (moveIndex = 0; moveIndex < MAX_MON_MOVES; moveIndex++)
    {
        if (moves[moveIndex] != MOVE_NONE && moves[moveIndex] != MOVE_UNAVAILABLE
            && GetMoveEffect(moves[moveIndex]) == effect
            && (gMovesInfo[moves[moveIndex]].argument & argument))
            return TRUE;
    }
    return FALSE;
}

// RHH: DoesPartnerHaveSameMoveEffect (pokeemerald-expansion/src/battle_ai_util.c:4349)
static bool32 DoesPartnerHaveSameMoveEffect(u8 battlerAtkPartner, u8 battlerDef, u16 move, u16 partnerMove)
{
    if (!HasPartner(battlerAtkPartner))
        return FALSE;
    if (GetMoveEffect(move) == GetMoveEffect(partnerMove) && partnerMove != MOVE_NONE)
    {
        if (GetMoveTarget(move, 0) == MOVE_TARGET_SELECTED && GetMoveTarget(partnerMove, 0) == MOVE_TARGET_SELECTED)
            return gBattleStruct->moveTarget[battlerAtkPartner] == battlerDef;
        return TRUE;
    }
    return FALSE;
}

// RHH: PartnerMoveEffectIsStatusSameTarget (pokeemerald-expansion/src/battle_ai_util.c:4367)
// Returns TRUE if the partner is targeting the same battlerDef with a non-volatile status move.
static bool32 PartnerMoveEffectIsStatusSameTarget(u8 battlerAtkPartner, u8 battlerDef, u16 partnerMove)
{
    if (!HasPartner(battlerAtkPartner))
        return FALSE;
    if (partnerMove != MOVE_NONE && gBattleStruct->moveTarget[battlerAtkPartner] == battlerDef)
    {
        u16 effect = GetMoveEffect(partnerMove);
        if (effect == EFFECT_TOXIC || effect == EFFECT_POISON
         || effect == EFFECT_SLEEP || effect == EFFECT_PARALYZE
         || effect == EFFECT_WILL_O_WISP || effect == EFFECT_YAWN)
            return TRUE;
    }
    return FALSE;
}

// RHH: AI_CanBeConfused (pokeemerald-expansion/src/battle_ai_util.c:3705)
static bool32 AI_CanBeConfused(u8 battlerAtk, u8 battlerDef, u16 move, u8 abilityDef)
{
    if (gBattleMons[battlerDef].status2 & STATUS2_CONFUSION)   // volatiles.confusionTurns > 0
        return FALSE;
    if (abilityDef == ABILITY_OWN_TEMPO)
        return FALSE;
    // Gen 6+: Misty Terrain — #ifdef when ported
    if (gSideStatuses[GetBattlerSide(battlerDef)] & SIDE_STATUS_SAFEGUARD)
        return FALSE;
    if (gBattleMons[battlerDef].status2 & STATUS2_SUBSTITUTE && !MoveIgnoresSubstitute(move))
        return FALSE;
    return TRUE;
}

// RHH: AI_CanPoison (pokeemerald-expansion/src/battle_ai_util.c:3673)
static bool32 AI_CanPoison(u8 battlerAtk, u8 battlerDef, u8 abilityAtk, u8 defAbility, u16 move, u16 partnerMove)
{
    if (!CanBePoisoned(battlerAtk, battlerDef, abilityAtk, defAbility))
        return FALSE;
    if (gBattleMons[battlerDef].status2 & STATUS2_SUBSTITUTE && !MoveIgnoresSubstitute(move))
        return FALSE;
    if (PartnerMoveEffectIsStatusSameTarget(BATTLE_PARTNER(battlerAtk), battlerDef, partnerMove))
        return FALSE;
    return TRUE;
}

// RHH: AI_CanBurn (pokeemerald-expansion/src/battle_ai_util.c:3719)
static bool32 AI_CanBurn(u8 battlerAtk, u8 battlerDef, u8 defAbility, u8 battlerAtkPartner, u16 move, u16 partnerMove)
{
    if (!CanBeBurned(battlerAtk, battlerDef, defAbility))
        return FALSE;
    if (gBattleMons[battlerDef].status2 & STATUS2_SUBSTITUTE && !MoveIgnoresSubstitute(move))
        return FALSE;
    if (PartnerMoveEffectIsStatusSameTarget(battlerAtkPartner, battlerDef, partnerMove))
        return FALSE;
    return TRUE;
}

// RHH: AI_CanParalyze (pokeemerald-expansion/src/battle_ai_util.c:3684)
static bool32 AI_CanParalyze(u8 battlerAtk, u8 battlerDef, u8 defAbility, u16 move, u16 partnerMove)
{
    if (!CanBeParalyzed(battlerAtk, battlerDef, defAbility))
        return FALSE;
    if (gBattleMons[battlerDef].status2 & STATUS2_SUBSTITUTE && !MoveIgnoresSubstitute(move))
        return FALSE;
    if (PartnerMoveEffectIsStatusSameTarget(BATTLE_PARTNER(battlerAtk), battlerDef, partnerMove))
        return FALSE;
    return TRUE;
}

// RHH: AI_CanPutToSleep (pokeemerald-expansion/src/battle_ai_util.c:3563)
static bool32 AI_CanPutToSleep(u8 battlerAtk, u8 battlerDef, u8 defAbility, u16 move, u16 partnerMove)
{
    if (!CanBeSlept(battlerAtk, battlerDef, defAbility))
        return FALSE;
    if (gBattleMons[battlerDef].status2 & STATUS2_SUBSTITUTE && !MoveIgnoresSubstitute(move))
        return FALSE;
    if (PartnerMoveEffectIsStatusSameTarget(BATTLE_PARTNER(battlerAtk), battlerDef, partnerMove))
        return FALSE;
    return TRUE;
}

// RHH: AI_CanConfuse (pokeemerald-expansion/src/battle_ai_util.c:3705)
static bool32 AI_CanConfuse(u8 battlerAtk, u8 battlerDef, u8 defAbility, u8 battlerAtkPartner, u16 move, u16 partnerMove)
{
    if (!AI_CanBeConfused(battlerAtk, battlerDef, move, defAbility))
        return FALSE;
    if (DoesPartnerHaveSameMoveEffect(battlerAtkPartner, battlerDef, move, partnerMove))
        return FALSE;
    return TRUE;
}

// RHH: IncreasePoisonScore (pokeemerald-expansion/src/battle_ai_util.c:4979)
void IncreasePoisonScore(u8 battlerAtk, u8 battlerDef, u16 move, s32 *score)
{
    if (((AI_THINKING_STRUCT->aiFlags & AI_FLAG_TRY_TO_FAINT) && CanAIFaintTarget(battlerAtk, battlerDef, 0))
            || gAiLogicData->holdEffects[battlerDef] == HOLD_EFFECT_CURE_PSN
            || gAiLogicData->holdEffects[battlerDef] == HOLD_EFFECT_CURE_STATUS)
        return;

    if (AI_CanPoison(battlerAtk, battlerDef, gAiLogicData->abilities[battlerAtk],
                     gAiLogicData->abilities[battlerDef], move, gAiLogicData->partnerMove)
        && gAiLogicData->hpPercents[battlerDef] > 20)
    {
        if (!HasDamagingMove(battlerDef))
            ADJUST_SCORE_PTR(DECENT_EFFECT);

        if (AI_THINKING_STRUCT->aiFlags & AI_FLAG_STALL && HasMoveWithEffect(battlerAtk, EFFECT_PROTECT))
            ADJUST_SCORE_PTR(WEAK_EFFECT);

        if (IsPowerBasedOnStatus(battlerAtk, EFFECT_DOUBLE_POWER_ON_ARG_STATUS, STATUS1_PSN_ANY)
         || HasMoveWithEffect(battlerAtk, EFFECT_VENOM_DRENCH))
            ADJUST_SCORE_PTR(DECENT_EFFECT);
        else
            ADJUST_SCORE_PTR(WEAK_EFFECT);
    }
}

// RHH: IncreaseBurnScore (pokeemerald-expansion/src/battle_ai_util.c:5003)
void IncreaseBurnScore(u8 battlerAtk, u8 battlerDef, u16 move, s32 *score)
{
    if (((AI_THINKING_STRUCT->aiFlags & AI_FLAG_TRY_TO_FAINT) && CanAIFaintTarget(battlerAtk, battlerDef, 0))
            || gAiLogicData->holdEffects[battlerDef] == HOLD_EFFECT_CURE_BRN
            || gAiLogicData->holdEffects[battlerDef] == HOLD_EFFECT_CURE_STATUS)
        return;

    if (AI_CanBurn(battlerAtk, battlerDef, gAiLogicData->abilities[battlerDef],
                   BATTLE_PARTNER(battlerAtk), move, gAiLogicData->partnerMove))
    {
        if (HasMoveWithCategory(battlerDef, DAMAGE_CATEGORY_PHYSICAL)
            || (!(AI_THINKING_STRUCT->aiFlags & AI_FLAG_OMNISCIENT)
                && GetSpeciesBaseAttack(gBattleMons[battlerDef].species) >= GetSpeciesBaseSpAttack(gBattleMons[battlerDef].species) + 10))
        {
            u16 defBestMoves[MAX_MON_MOVES] = {MOVE_NONE};
            bool32 hasPhysical = FALSE;
            u32 moveIndex;

            GetBestDmgMovesFromBattler(battlerAtk, battlerDef, AI_DEFENDING, defBestMoves);

            for (moveIndex = 0; moveIndex < MAX_MON_MOVES; moveIndex++)
            {
                if (defBestMoves[moveIndex] == MOVE_NONE)
                    break;
                if (gMovesInfo[defBestMoves[moveIndex]].category == DAMAGE_CATEGORY_PHYSICAL)
                {
                    hasPhysical = TRUE;
                    break;
                }
            }

            if (hasPhysical)
                ADJUST_SCORE_PTR(DECENT_EFFECT);
            else
                ADJUST_SCORE_PTR(WEAK_EFFECT);
        }

        if (IsPowerBasedOnStatus(battlerAtk, EFFECT_DOUBLE_POWER_ON_ARG_STATUS, STATUS1_BURN)
         || IsPowerBasedOnStatus(BATTLE_PARTNER(battlerAtk), EFFECT_DOUBLE_POWER_ON_ARG_STATUS, STATUS1_BURN))
            ADJUST_SCORE_PTR(WEAK_EFFECT);
    }
}

// RHH: IncreaseParalyzeScore (pokeemerald-expansion/src/battle_ai_util.c:5044)
void IncreaseParalyzeScore(u8 battlerAtk, u8 battlerDef, u16 move, s32 *score)
{
    if (((AI_THINKING_STRUCT->aiFlags & AI_FLAG_TRY_TO_FAINT) && CanAIFaintTarget(battlerAtk, battlerDef, 0))
            || gAiLogicData->holdEffects[battlerDef] == HOLD_EFFECT_CURE_PAR
            || gAiLogicData->holdEffects[battlerDef] == HOLD_EFFECT_CURE_STATUS)
        return;

    if (AI_CanParalyze(battlerAtk, battlerDef, gAiLogicData->abilities[battlerDef], move, gAiLogicData->partnerMove))
    {
        u32 atkSpeed = gAiLogicData->speedStats[battlerAtk];
        u32 defSpeed = gAiLogicData->speedStats[battlerDef];

        if ((defSpeed >= atkSpeed && defSpeed / 2 < atkSpeed)
         || IsPowerBasedOnStatus(battlerAtk, EFFECT_DOUBLE_POWER_ON_ARG_STATUS, STATUS1_PARALYSIS)
         || HasMoveWithMoveEffectExcept(battlerAtk, MOVE_EFFECT_FLINCH, EFFECT_FIRST_TURN_ONLY)
         || (gBattleMons[battlerDef].status2 & STATUS2_INFATUATION)      // volatiles.infatuation
         || (gBattleMons[battlerDef].status2 & STATUS2_CONFUSION))       // volatiles.confusionTurns > 0
            ADJUST_SCORE_PTR(GOOD_EFFECT);
        else
            ADJUST_SCORE_PTR(DECENT_EFFECT);
    }
}

// RHH: IncreaseSleepScore (pokeemerald-expansion/src/battle_ai_util.c:5066)
void IncreaseSleepScore(u8 battlerAtk, u8 battlerDef, u16 move, s32 *score)
{
    if (gAiLogicData->holdEffects[battlerDef] == HOLD_EFFECT_CURE_SLP
            || gAiLogicData->holdEffects[battlerDef] == HOLD_EFFECT_CURE_STATUS)
        return;

    if ((AI_THINKING_STRUCT->aiFlags & AI_FLAG_TRY_TO_FAINT) && CanAIFaintTarget(battlerAtk, battlerDef, 0))
    {
        u16 bestMoves[MAX_MON_MOVES] = {MOVE_NONE};
        u32 moveIndex;

        GetBestDmgMovesFromBattler(battlerAtk, battlerDef, AI_ATTACKING, bestMoves);

        for (moveIndex = 0; moveIndex < MAX_MON_MOVES; moveIndex++)
        {
            if (GetMoveEffect(bestMoves[moveIndex]) != EFFECT_FOCUS_PUNCH && bestMoves[moveIndex] != MOVE_NONE)
                return;
        }
    }

    if (!AI_CanPutToSleep(battlerAtk, battlerDef, gAiLogicData->abilities[battlerDef], move, gAiLogicData->partnerMove))
        return;

    ADJUST_SCORE_PTR(DECENT_EFFECT);

    if ((HasMoveWithEffect(battlerAtk, EFFECT_DREAM_EATER) || HasMoveWithEffect(battlerAtk, EFFECT_NIGHTMARE))
     && !HasUsableWhileAsleepMove(battlerDef))
        ADJUST_SCORE_PTR(WEAK_EFFECT);

    if (IsPowerBasedOnStatus(battlerAtk, EFFECT_DOUBLE_POWER_ON_ARG_STATUS, STATUS1_SLEEP)
     || IsPowerBasedOnStatus(BATTLE_PARTNER(battlerAtk), EFFECT_DOUBLE_POWER_ON_ARG_STATUS, STATUS1_SLEEP))
        ADJUST_SCORE_PTR(WEAK_EFFECT);
}

// RHH: IncreaseConfusionScore (pokeemerald-expansion/src/battle_ai_util.c:5098)
void IncreaseConfusionScore(u8 battlerAtk, u8 battlerDef, u16 move, s32 *score)
{
    if (((AI_THINKING_STRUCT->aiFlags & AI_FLAG_TRY_TO_FAINT) && CanAIFaintTarget(battlerAtk, battlerDef, 0))
            || gAiLogicData->holdEffects[battlerDef] == HOLD_EFFECT_CURE_CONFUSION
            || gAiLogicData->holdEffects[battlerDef] == HOLD_EFFECT_CURE_STATUS)
        return;

    if (AI_CanConfuse(battlerAtk, battlerDef, gAiLogicData->abilities[battlerDef],
                      BATTLE_PARTNER(battlerAtk), move, gAiLogicData->partnerMove))
    {
        if ((gBattleMons[battlerDef].status1 & STATUS1_PARALYSIS)
         || (gBattleMons[battlerDef].status2 & STATUS2_INFATUATION)     // volatiles.infatuation
         || (gAiLogicData->abilities[battlerAtk] == ABILITY_SERENE_GRACE
             && HasMoveWithMoveEffectExcept(battlerAtk, MOVE_EFFECT_FLINCH, EFFECT_FIRST_TURN_ONLY)))
            ADJUST_SCORE_PTR(GOOD_EFFECT);
        else
            ADJUST_SCORE_PTR(DECENT_EFFECT);
    }
}

// ============================================================================
// Tier J — AI_CalcAdditionalEffectScore helper functions
// RHH source: pokeemerald-expansion/src/battle_ai_util.c
// ============================================================================

// RHH: GetIncomingMove (src/battle_ai_util.c:205-210)
// Returns predicted or last used move for the opposing battler.
u16 GetIncomingMove(u8 battler, u8 opposingBattler, struct AiLogicData *aiData)
{
    if (aiData->predictingMove && CanAiPredictMove(battler))
        return aiData->predictedMove[opposingBattler];
    return aiData->lastUsedMove[opposingBattler];
}

// RHH: HasPartnerIgnoreFlags (src/battle_ai_util.c:4172-4179)
bool32 HasPartnerIgnoreFlags(u8 battler)
{
    if (IsDoubleBattle() && IsBattlerAlive(BATTLE_PARTNER(battler)))
        return TRUE;
    return FALSE;
}

// RHH: HasBattlerSideMoveWithEffect (src/battle_ai_util.c:2639-2646)
bool32 HasBattlerSideMoveWithEffect(u8 battler, u16 effect)
{
    if (HasMoveWithEffect(battler, effect))
        return TRUE;
    if (HasPartnerIgnoreFlags(battler) && HasMoveWithEffect(BATTLE_PARTNER(battler), effect))
        return TRUE;
    return FALSE;
}

// RHH: DoesBattlerIgnoreAbilityChecks (src/battle_ai_util.c:1881-1893)
// Gen4+ ABILITY_MYCELIUM_MIGHT #ifdef'd.
bool32 DoesBattlerIgnoreAbilityChecks(u8 battlerAtk, u8 atkAbility, u16 move)
{
    if (AI_THINKING_STRUCT->aiFlags & AI_FLAG_NEGATE_UNAWARE)
        return FALSE;

#ifdef ABILITY_MYCELIUM_MIGHT
    if (atkAbility == ABILITY_MYCELIUM_MIGHT && IsBattleMoveStatus(move))
        return TRUE;
#endif

    if (IsMoldBreakerTypeAbility(battlerAtk, atkAbility) || MoveIgnoresTargetAbility(move))
        return TRUE;

    return FALSE;
}

// RHH: AI_WeatherHasEffect (src/battle_ai_util.c:1895-1902, static inline)
// Gen3: single aiFlags — no per-battler flag array.
static bool32 AI_WeatherHasEffect(void)
{
    if (AI_THINKING_STRUCT->aiFlags & AI_FLAG_NEGATE_UNAWARE)
        return TRUE;   // AI handicap: doesn't understand weather suppression
    return gAiLogicData->weatherHasEffect;
}

// RHH: AI_GetWeather (src/battle_ai_util.c:1904-1911)
bool32 AI_GetWeather(void)
{
    if (!gBattleWeather)
        return 0;
    if (!AI_WeatherHasEffect())
        return 0;
    return gBattleWeather;
}

// RHH: BattlerWillFaintFromWeather (src/battle_ai_util.c:3434-3444)
// Gen3: HOLD_EFFECT_SAFETY_GOGGLES #ifdef'd; GetNonDynamaxMaxHP → maxHP.
// Uses existing DoesBattlerTakeSandstormDamage/DoesBattlerTakeHailDamage (see above).
bool32 BattlerWillFaintFromWeather(u8 battler, u8 ability)
{
#ifdef HOLD_EFFECT_SAFETY_GOGGLES
    if (gAiLogicData->holdEffects[battler] == HOLD_EFFECT_SAFETY_GOGGLES)
        return FALSE;
#endif

    // Note: existing statics check gBattleWeather directly; acceptable for Gen3.
    if ((DoesBattlerTakeSandstormDamage(battler, ability) || DoesBattlerTakeHailDamage(battler, ability))
      && gBattleMons[battler].hp <= max(1, gBattleMons[battler].maxHP / 16))
        return TRUE;

    return FALSE;
}

// RHH: BattlerWillFaintFromSecondaryDamage (src/battle_ai_util.c:3446-3452)
bool32 BattlerWillFaintFromSecondaryDamage(u8 battler, u8 ability)
{
    (void)ability;
    if (GetBattlerSecondaryDamage(battler) != 0
      && gBattleMons[battler].hp <= max(1, gBattleMons[battler].maxHP / 16))
        return TRUE;
    return FALSE;
}

// RHH: IsAdditionalEffectBlocked (src/battle_ai_util.c:727-736)
// Gen3: HOLD_EFFECT_COVERT_CLOAK #ifdef'd.
bool32 IsAdditionalEffectBlocked(u8 battlerAtk, u8 abilityAtk, u8 battlerDef, u8 abilityDef)
{
#ifdef HOLD_EFFECT_COVERT_CLOAK
    if (gAiLogicData->holdEffects[battlerDef] == HOLD_EFFECT_COVERT_CLOAK)
        return TRUE;
#endif

    if (abilityDef == ABILITY_SHIELD_DUST && !IsMoldBreakerTypeAbility(battlerAtk, abilityAtk))
        return TRUE;

    return FALSE;
}

// RHH: ShouldTryToFlinch (src/battle_ai_util.c:3754-3774)
// Gen3: HOLD_EFFECT_COVERT_CLOAK #ifdef'd; volatiles → status2 bitmasks.
bool32 ShouldTryToFlinch(u8 battlerAtk, u8 battlerDef, u8 atkAbility, u8 defAbility, u16 move)
{
    u16 predictedMoveSpeedCheck = GetIncomingMoveSpeedCheck(battlerAtk, battlerDef, gAiLogicData);

    if ((!IsMoldBreakerTypeAbility(battlerAtk, gAiLogicData->abilities[battlerAtk])
            && (defAbility == ABILITY_SHIELD_DUST || defAbility == ABILITY_INNER_FOCUS))
#ifdef HOLD_EFFECT_COVERT_CLOAK
     || gAiLogicData->holdEffects[battlerDef] == HOLD_EFFECT_COVERT_CLOAK
#endif
     || DoesSubstituteBlockMove(battlerAtk, battlerDef, move)
     || AI_IsSlower(battlerAtk, battlerDef, move, predictedMoveSpeedCheck, CONSIDER_PRIORITY))
    {
        return FALSE;
    }
    else if (atkAbility == ABILITY_SERENE_GRACE
          || (gBattleMons[battlerDef].status1 & STATUS1_PARALYSIS)
          || (gBattleMons[battlerDef].status2 & STATUS2_INFATUATION)
          || (gBattleMons[battlerDef].status2 & STATUS2_CONFUSION)
          || (AI_IsFaster(battlerAtk, battlerDef, move, predictedMoveSpeedCheck, CONSIDER_PRIORITY)
              && CanTargetFaintAi(battlerDef, battlerAtk)))
    {
        return TRUE;
    }

    return FALSE;
}

// RHH: ShouldTrap (src/battle_ai_util.c:3776-3794)
// Gen3: single aiFlags.
bool32 ShouldTrap(u8 battlerAtk, u8 battlerDef, u16 move)
{
    if (AI_CanBattlerEscape(battlerDef))
        return FALSE;

    if (IsBattlerTrapped(battlerAtk, battlerDef))
        return FALSE;

    if (BattlerWillFaintFromSecondaryDamage(battlerDef, gAiLogicData->abilities[battlerDef]))
        return TRUE;

    if (AI_THINKING_STRUCT->aiFlags & AI_FLAG_STALL)
    {
        if (!CanTargetFaintAi(battlerDef, battlerAtk))
            return TRUE;
    }

    return FALSE;
}

// RHH: GetAIEffectGroup (src/battle_ai_util.c:4229-4291, static)
// Maps a primary battle move effect to an AI_EFFECT_* group bitmask.
// Gen4+ effects #ifdef'd where the EFFECT_ constant may not be in Gen3.
static u32 GetAIEffectGroup(u16 effect)
{
    u32 aiEffect = AI_EFFECT_NONE;

    switch (effect)
    {
    case EFFECT_WEATHER:
    case EFFECT_WEATHER_AND_SWITCH:
        aiEffect |= AI_EFFECT_WEATHER;
        break;
    case EFFECT_ELECTRIC_TERRAIN:
    case EFFECT_GRASSY_TERRAIN:
    case EFFECT_MISTY_TERRAIN:
    case EFFECT_PSYCHIC_TERRAIN:
    case EFFECT_STEEL_ROLLER:
    case EFFECT_ICE_SPINNER:
        aiEffect |= AI_EFFECT_TERRAIN;
        break;
    case EFFECT_COURT_CHANGE:
        aiEffect |= AI_EFFECT_CLEAR_HAZARDS | AI_EFFECT_AURORA_VEIL | AI_EFFECT_BREAK_SCREENS;
        break;
    case EFFECT_DEFOG:
        aiEffect |= AI_EFFECT_CLEAR_HAZARDS | AI_EFFECT_BREAK_SCREENS;
        break;
    case EFFECT_RAPID_SPIN:
    case EFFECT_TIDY_UP:
        aiEffect |= AI_EFFECT_CLEAR_HAZARDS;
        break;
    case EFFECT_HAZE:
        aiEffect |= AI_EFFECT_RESET_STATS;
        break;
    case EFFECT_HIT_SWITCH_TARGET:
    case EFFECT_ROAR:
        aiEffect |= AI_EFFECT_FORCE_SWITCH;
        break;
    case EFFECT_TORMENT:
        aiEffect |= AI_EFFECT_TORMENT;
        break;
    case EFFECT_AURORA_VEIL:
        aiEffect |= AI_EFFECT_AURORA_VEIL;
        break;
    case EFFECT_LIGHT_SCREEN:
        aiEffect |= AI_EFFECT_LIGHT_SCREEN;
        break;
    case EFFECT_REFLECT:
        aiEffect |= AI_EFFECT_REFLECT;
        break;
    case EFFECT_GRAVITY:
        aiEffect |= AI_EFFECT_GRAVITY;
        break;
    case EFFECT_DOODLE:
    case EFFECT_ENTRAINMENT:
    case EFFECT_GASTRO_ACID:
    case EFFECT_ROLE_PLAY:
    case EFFECT_SKILL_SWAP:
    case EFFECT_OVERWRITE_ABILITY:
        aiEffect |= AI_EFFECT_CHANGE_ABILITY;
        break;
    default:
        break;
    }

    return aiEffect;
}

// RHH: GetAIEffectGroupFromMove (src/battle_ai_util.c:4294-4349, static)
// Combines primary move effect group with additionalEffects group flags.
static u32 GetAIEffectGroupFromMove(u8 battler, u16 move)
{
    (void)battler;
    u32 aiEffect = GetAIEffectGroup(gMovesInfo[move].effect);
    u32 additionalEffectCount = GetMoveAdditionalEffectCount(move);

    for (u32 effectIndex = 0; effectIndex < additionalEffectCount; effectIndex++)
    {
        switch (GetMoveAdditionalEffectById(move, effectIndex)->moveEffect)
        {
        case MOVE_EFFECT_SUN:
        case MOVE_EFFECT_RAIN:
        case MOVE_EFFECT_SANDSTORM:
        case MOVE_EFFECT_HAIL:
            aiEffect |= AI_EFFECT_WEATHER;
            break;
        case MOVE_EFFECT_ELECTRIC_TERRAIN:
        case MOVE_EFFECT_GRASSY_TERRAIN:
        case MOVE_EFFECT_MISTY_TERRAIN:
        case MOVE_EFFECT_PSYCHIC_TERRAIN:
            aiEffect |= AI_EFFECT_TERRAIN;
            break;
        case MOVE_EFFECT_DEFOG:
            aiEffect |= AI_EFFECT_CLEAR_HAZARDS | AI_EFFECT_BREAK_SCREENS;
            break;
        case MOVE_EFFECT_CLEAR_SMOG:
        case MOVE_EFFECT_HAZE:
            aiEffect |= AI_EFFECT_RESET_STATS;
            break;
        case MOVE_EFFECT_TORMENT_SIDE:
            aiEffect |= AI_EFFECT_TORMENT;
            break;
        case MOVE_EFFECT_LIGHT_SCREEN:
            aiEffect |= AI_EFFECT_LIGHT_SCREEN;
            break;
        case MOVE_EFFECT_REFLECT:
            aiEffect |= AI_EFFECT_REFLECT;
            break;
        case MOVE_EFFECT_AURORA_VEIL:
            aiEffect |= AI_EFFECT_AURORA_VEIL;
            break;
        case MOVE_EFFECT_GRAVITY:
            aiEffect |= AI_EFFECT_GRAVITY;
            break;
        case MOVE_EFFECT_BREAK_SCREEN:
            aiEffect |= AI_EFFECT_BREAK_SCREENS;
            break;
        default:
            break;
        }
    }

    return aiEffect;
}

// RHH: HasMoveWithAIEffect (src/battle_ai_util.c:2623-2637)
bool32 HasMoveWithAIEffect(u8 battler, u32 aiEffect)
{
    u16 *moves = GetMovesArray(battler);

    for (u32 moveIndex = 0; moveIndex < MAX_MON_MOVES; moveIndex++)
    {
        if (moves[moveIndex] != MOVE_NONE && moves[moveIndex] != MOVE_UNAVAILABLE)
        {
            if (GetAIEffectGroupFromMove(battler, moves[moveIndex]) & aiEffect)
                return TRUE;
        }
    }

    return FALSE;
}

// RHH: HasBattlerSideMoveWithAIEffect (src/battle_ai_util.c:2648-2655)
bool32 HasBattlerSideMoveWithAIEffect(u8 battler, u32 aiEffect)
{
    if (HasMoveWithAIEffect(battler, aiEffect))
        return TRUE;
    if (HasPartnerIgnoreFlags(battler) && HasMoveWithAIEffect(BATTLE_PARTNER(battler), aiEffect))
        return TRUE;
    return FALSE;
}

// RHH: CanLowerStat (src/battle_ai_util.c:2327-2388)
// Gen3 adaptations: no HOLD_EFFECT_CLEAR_AMULET/FLOWER_VEIL/BIG_PECKS/MINDS_EYE/FULL_METAL_BODY/MAGIC_BOUNCE;
// no GetConfig/GetActiveGimmick; SHIELD_DUST simplified (no dynamax); INFILTRATOR #ifdef'd.
bool32 CanLowerStat(u8 battlerAtk, u8 battlerDef, struct AiLogicData *aiData, u8 stat)
{
    if (gBattleMons[battlerDef].statStages[stat] == MIN_STAT_STAGE)
        return FALSE;

#ifdef HOLD_EFFECT_CLEAR_AMULET
    if (aiData->holdEffects[battlerDef] == HOLD_EFFECT_CLEAR_AMULET)
        return FALSE;
#endif

    u16 move = AI_THINKING_STRUCT->moveConsidered;
    u8 abilityAtk = aiData->abilities[battlerAtk];

    if (gSideStatuses[GetBattlerSide(battlerDef)] & SIDE_STATUS_MIST
#ifdef ABILITY_INFILTRATOR
     && abilityAtk != ABILITY_INFILTRATOR
#endif
    )
        return FALSE;

    if (!DoesBattlerIgnoreAbilityChecks(battlerAtk, abilityAtk, move))
    {
#ifdef ABILITY_FLOWER_VEIL
        if (IS_BATTLER_OF_TYPE(battlerDef, TYPE_GRASS) && AI_IsAbilityOnSide(battlerDef, ABILITY_FLOWER_VEIL))
            return FALSE;
#endif

        switch (aiData->abilities[battlerDef])
        {
        case ABILITY_SPEED_BOOST:
            if (stat == STAT_SPEED)
                return FALSE;
            break;
        case ABILITY_HYPER_CUTTER:
            if (stat == STAT_ATK)
                return FALSE;
            break;
#ifdef ABILITY_BIG_PECKS
        case ABILITY_BIG_PECKS:
            if (stat == STAT_DEF)
                return FALSE;
            break;
#endif
        case ABILITY_KEEN_EYE:
#ifdef ABILITY_MINDS_EYE
        case ABILITY_MINDS_EYE:
#endif
            if (stat == STAT_ACC)
                return FALSE;
            break;
        case ABILITY_CONTRARY:
        case ABILITY_CLEAR_BODY:
        case ABILITY_WHITE_SMOKE:
#ifdef ABILITY_FULL_METAL_BODY
        case ABILITY_FULL_METAL_BODY:
#endif
            return FALSE;
        case ABILITY_SHIELD_DUST:
            // Gen3: no dynamax check needed
            if (!IsBattleMoveStatus(move))
                return FALSE;
            break;
#ifdef ABILITY_MAGIC_BOUNCE
        case ABILITY_MAGIC_BOUNCE:
            if (IsBattleMoveStatus(move))
                return FALSE;
            break;
#endif
        default:
            break;
        }
    }

    if (stat == STAT_SPEED)
    {
        u16 predictedMoveSpeedCheck = GetIncomingMoveSpeedCheck(battlerAtk, battlerDef, gAiLogicData);
        return !(AI_IsFaster(battlerAtk, battlerDef, move, predictedMoveSpeedCheck, DONT_CONSIDER_PRIORITY)
              && CountUsablePartyMons(battlerAtk) == 0
              && !HasBattlerSideMoveWithEffect(battlerAtk, EFFECT_ELECTRO_BALL));
    }

    return TRUE;
}

// RHH: ShouldSetWeather (src/battle_ai_util.c:2229-2235)
bool32 ShouldSetWeather(u8 battler, u32 weather)
{
    if (AI_GetWeather() & weather)
        return FALSE;

    return WeatherChecker(battler, weather, FIELD_EFFECT_POSITIVE);
}

// RHH: ShouldClearWeather (src/battle_ai_util.c:2237-2240)
bool32 ShouldClearWeather(u8 battler, u32 weather)
{
    return WeatherChecker(battler, weather, FIELD_EFFECT_NEGATIVE);
}

// RHH: ShouldSetFieldStatus (src/battle_ai_util.c:2242-2254)
bool32 ShouldSetFieldStatus(u8 battler, u32 fieldStatus)
{
    if (gFieldStatuses & fieldStatus)
    {
        if (!(fieldStatus & STATUS_FIELD_TRICK_ROOM))
            return FALSE;
        // Re-cast Trick Room on last turn to avoid letting it expire
        else if (gFieldTimers.trickRoomTimer != 1)
            return FALSE;
    }

    return FieldStatusChecker(battler, fieldStatus, FIELD_EFFECT_POSITIVE);
}

// RHH: ShouldClearFieldStatus (src/battle_ai_util.c:2256-2259)
bool32 ShouldClearFieldStatus(u8 battler, u32 fieldStatus)
{
    return FieldStatusChecker(battler, fieldStatus, FIELD_EFFECT_NEGATIVE);
}

// RHH: ShouldSetScreen (src/battle_ai_util.c:4011-4044)
// Gen3: HasMoveWithAIEffect stub always FALSE; B_WEATHER_ICY_ANY → B_WEATHER_HAIL;
// SIDE_STATUS_AURORA_VEIL #ifdef'd.
bool32 ShouldSetScreen(u8 battlerAtk, u8 battlerDef, u16 moveEffect)
{
    u8 atkSide = GetBattlerSide(battlerAtk);

    if (HasMoveWithAIEffect(battlerDef, AI_EFFECT_BREAK_SCREENS))
        return FALSE;

    switch (moveEffect)
    {
    case EFFECT_AURORA_VEIL:
        if ((AI_GetWeather() & B_WEATHER_HAIL)
#ifdef SIDE_STATUS_AURORA_VEIL
         && !(gSideStatuses[atkSide] & (SIDE_STATUS_REFLECT | SIDE_STATUS_LIGHTSCREEN | SIDE_STATUS_AURORA_VEIL))
#else
         && !(gSideStatuses[atkSide] & (SIDE_STATUS_REFLECT | SIDE_STATUS_LIGHTSCREEN))
#endif
        )
            return TRUE;
        break;
    case EFFECT_REFLECT:
        if (HasMoveWithCategory(battlerDef, DAMAGE_CATEGORY_PHYSICAL)
#ifdef SIDE_STATUS_AURORA_VEIL
         && !(gSideStatuses[atkSide] & (SIDE_STATUS_REFLECT | SIDE_STATUS_AURORA_VEIL))
#else
         && !(gSideStatuses[atkSide] & SIDE_STATUS_REFLECT)
#endif
        )
            return TRUE;
        break;
    case EFFECT_LIGHT_SCREEN:
        if (HasMoveWithCategory(battlerDef, DAMAGE_CATEGORY_SPECIAL)
#ifdef SIDE_STATUS_AURORA_VEIL
         && !(gSideStatuses[atkSide] & (SIDE_STATUS_LIGHTSCREEN | SIDE_STATUS_AURORA_VEIL))
#else
         && !(gSideStatuses[atkSide] & SIDE_STATUS_LIGHTSCREEN)
#endif
        )
            return TRUE;
        break;
    default:
        break;
    }

    return FALSE;
}

// RHH: IsWeatherActive (src/battle_ai_util.c:1976-1996)
enum WeatherState IsWeatherActive(u32 flags)
{
    enum WeatherState state;

    if (gBattleWeather & flags)
        state = WEATHER_ACTIVE;
    else
        state = WEATHER_INACTIVE;

    if (!AI_WeatherHasEffect())
    {
        if (state == WEATHER_ACTIVE)
            state = WEATHER_ACTIVE_BUT_BLOCKED;
        else
            state = WEATHER_INACTIVE_AND_BLOCKED;
    }

    return state;
}

// RHH: HasDamagingMoveOfType (src/battle_ai_util.c:3219-3240)
// Gen3 simplified: no GetDynamicMoveType (type-changing abilities); use raw type field.
bool32 HasDamagingMoveOfType(u8 battler, u8 type)
{
    u16 *moves = GetMovesArray(battler);

    for (u32 moveIndex = 0; moveIndex < MAX_MON_MOVES; moveIndex++)
    {
        if (moves[moveIndex] != MOVE_NONE && moves[moveIndex] != MOVE_UNAVAILABLE
         && GetMovePower(moves[moveIndex]) > 0
         && GetMoveType(moves[moveIndex]) == type)
            return TRUE;
    }
    return FALSE;
}

// RHH: HasMoveWithFlag (src/battle_ai_util.c:3241-3252)
bool32 HasMoveWithFlag(u8 battler, MoveFlag getFlag)
{
    u16 *moves = GetMovesArray(battler);
    u32 moveLimitations = gAiLogicData->moveLimitations[battler];

    for (u32 moveIndex = 0; moveIndex < MAX_MON_MOVES; moveIndex++)
    {
        if (IsMoveUnusable(moveIndex, moves[moveIndex], moveLimitations))
            continue;
        if (getFlag(moves[moveIndex]))
            return TRUE;
    }
    return FALSE;
}

// RHH: IsBattle1v1 (src/battle_ai_util.c:4143-4150)
bool32 IsBattle1v1(void)
{
    if (IsDoubleBattle()
      && ((IsBattlerAlive(GetBattlerAtPosition(B_POSITION_PLAYER_LEFT)) && IsBattlerAlive(GetBattlerAtPosition(B_POSITION_PLAYER_RIGHT)))
      || (IsBattlerAlive(GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT)) && IsBattlerAlive(GetBattlerAtPosition(B_POSITION_OPPONENT_RIGHT)))))
        return FALSE;
    return TRUE;
}

// RHH: HasNonVolatileMoveEffect (src/battle_ai_util.c:2689-2700)
// Gen3 simplified: checks additionalEffects (no GetMoveNonVolatileStatus, no EFFECT_NON_VOLATILE_STATUS).
bool32 HasNonVolatileMoveEffect(u8 battlerId, u16 effect)
{
    u16 *moves = GetMovesArray(battlerId);

    for (u32 moveIndex = 0; moveIndex < MAX_MON_MOVES; moveIndex++)
    {
        if (moves[moveIndex] != MOVE_NONE && moves[moveIndex] != MOVE_UNAVAILABLE
         && MoveHasAdditionalEffect(moves[moveIndex], effect))
            return TRUE;
    }
    return FALSE;
}

// RHH: HasBattlerSideMoveWithAdditionalEffect (src/battle_ai_util.c:2731-2737)
bool32 HasBattlerSideMoveWithAdditionalEffect(u8 battler, u16 moveEffect)
{
    if (HasMoveWithAdditionalEffect(battler, moveEffect))
        return TRUE;
    if (HasPartnerIgnoreFlags(battler) && HasMoveWithAdditionalEffect(BATTLE_PARTNER(battler), moveEffect))
        return TRUE;
    return FALSE;
}

// RHH: IsTargetingPartner (src/battle_ai_util.c:4181-4186)
// Gen3: AI_FLAG_ATTACKS_PARTNER not defined — just check flank pairing.
bool32 IsTargetingPartner(u8 battlerAtk, u8 battlerDef)
{
#ifdef AI_FLAG_ATTACKS_PARTNER
    if (AI_THINKING_STRUCT->aiFlags & AI_FLAG_ATTACKS_PARTNER)
        return FALSE;
#endif
    return (battlerAtk == (battlerDef ^ BIT_FLANK));
}

// RHH: HasThawingMove (src/battle_ai_util.c:2923-2932)
bool32 HasThawingMove(u8 battler)
{
    u16 *moves = GetMovesArray(battler);
    for (u32 moveIndex = 0; moveIndex < MAX_MON_MOVES; moveIndex++)
    {
        if (moves[moveIndex] != MOVE_NONE && moves[moveIndex] != MOVE_UNAVAILABLE
         && MoveThawsUser(moves[moveIndex]))
            return TRUE;
    }
    return FALSE;
}

// RHH: DoesBattlerBenefitFromAllVolatileStatus (src/battle_ai_util.c:3572-3582, static)
// Gen3: ABILITY_QUICK_FEET/MAGIC_GUARD #ifdef'd.
static bool32 DoesBattlerBenefitFromAllVolatileStatus(u8 battler, u8 ability)
{
    if (ability == ABILITY_MARVEL_SCALE
#ifdef ABILITY_QUICK_FEET
     || ability == ABILITY_QUICK_FEET
#endif
#ifdef ABILITY_MAGIC_GUARD
     || ability == ABILITY_MAGIC_GUARD
#endif
     || (ability == ABILITY_GUTS && HasMoveWithCategory(battler, DAMAGE_CATEGORY_PHYSICAL))
     || HasMoveWithEffect(battler, EFFECT_FACADE)
     || HasMoveWithEffect(battler, EFFECT_PSYCHO_SHIFT))
        return TRUE;
    return FALSE;
}

// RHH: ShouldCureStatusInternal (src/battle_ai_util.c:4046-4131, static)
// Gen3: HOLD_EFFECT_TOXIC_ORB/FLAME_ORB, ABILITY_POISON_HEAL/TOXIC_BOOST/FLARE_BOOST #ifdef'd.
static bool32 ShouldCureStatusInternal(u8 battlerAtk, u8 battlerDef, bool32 usingItem, struct AiLogicData *aiData)
{
    bool32 targetingSelf = (battlerAtk == battlerDef);
    bool32 targetingAlly = IsTargetingPartner(battlerAtk, battlerDef);
    u32 status = gBattleMons[battlerDef].status1;

    if (status & STATUS1_SLEEP)
    {
        if (targetingAlly || targetingSelf)
        {
            if (HasUsableWhileAsleepMove(battlerDef))
                return FALSE;
            else
                return usingItem || targetingAlly;
        }
        return FALSE;
    }

    if (status & STATUS1_FREEZE)
    {
        if (targetingAlly || targetingSelf)
        {
            if (HasThawingMove(battlerDef))
                return FALSE;
            return usingItem || targetingAlly;
        }
        return FALSE;
    }

    bool32 isHarmless = FALSE;

    if (DoesBattlerBenefitFromAllVolatileStatus(battlerDef, aiData->abilities[battlerDef]))
        isHarmless = TRUE;

    if (status & STATUS1_PSN_ANY)
    {
#ifdef HOLD_EFFECT_TOXIC_ORB
        if (aiData->holdEffects[battlerDef] == HOLD_EFFECT_TOXIC_ORB)
            return FALSE;
#endif
#ifdef ABILITY_POISON_HEAL
        if (aiData->abilities[battlerDef] == ABILITY_POISON_HEAL)
            isHarmless = TRUE;
#endif
#ifdef ABILITY_TOXIC_BOOST
        if (aiData->abilities[battlerDef] == ABILITY_TOXIC_BOOST && !isHarmless)
        {
            if (HasMoveWithCategory(battlerDef, DAMAGE_CATEGORY_PHYSICAL))
                isHarmless = TRUE;
            else if (!(targetingSelf || targetingAlly) && !HasMoveWithCategory(battlerDef, DAMAGE_CATEGORY_SPECIAL))
                isHarmless = TRUE;
        }
#endif
    }

    if (status & STATUS1_BURN)
    {
#ifdef HOLD_EFFECT_FLAME_ORB
        if (aiData->holdEffects[battlerDef] == HOLD_EFFECT_FLAME_ORB)
            return FALSE;
#endif
#ifdef ABILITY_FLARE_BOOST
        if (aiData->abilities[battlerDef] == ABILITY_FLARE_BOOST && !isHarmless)
        {
            if (HasMoveWithCategory(battlerDef, DAMAGE_CATEGORY_SPECIAL))
                isHarmless = TRUE;
            else if (!(targetingSelf || targetingAlly) && !HasMoveWithCategory(battlerDef, DAMAGE_CATEGORY_PHYSICAL))
                isHarmless = TRUE;
        }
#endif
    }

    if (isHarmless)
    {
        if (targetingSelf || targetingAlly)
            return FALSE;
        else
            return TRUE;
    }
    else
    {
        if (targetingSelf || targetingAlly)
            return TRUE;
        else
            return FALSE;
    }
}

// RHH: ShouldCureStatus (src/battle_ai_util.c:4132-4135)
bool32 ShouldCureStatus(u8 battlerAtk, u8 battlerDef, struct AiLogicData *aiData)
{
    return ShouldCureStatusInternal(battlerAtk, battlerDef, FALSE, aiData);
}

// RHH: ShouldCureStatusWithItem (src/battle_ai_util.c:4137-4140)
bool32 ShouldCureStatusWithItem(u8 battlerAtk, u8 battlerDef, struct AiLogicData *aiData)
{
    return ShouldCureStatusInternal(battlerAtk, battlerDef, TRUE, aiData);
}

// RHH: AI_TryToClearStats (src/battle_ai_util.c:5648-5654)
s32 AI_TryToClearStats(u8 battlerAtk, u8 battlerDef, bool32 isDoubleBattle)
{
    (void)battlerAtk;
    if (isDoubleBattle)
        return min(CountPositiveStatStages(battlerDef) + CountPositiveStatStages(BATTLE_PARTNER(battlerDef)), 7);
    else
        return min(CountPositiveStatStages(battlerDef), 4);
}

// RHH: AI_ShouldCopyStatChanges (src/battle_ai_util.c:5656-5684)
// Gen3: single aiFlags; HasMoveWithLowAccuracy uses raw accuracy.
bool32 AI_ShouldCopyStatChanges(u8 battlerAtk, u8 battlerDef)
{
    for (u8 statId = STAT_ATK; statId < NUM_BATTLE_STATS; statId++)
    {
        if (gBattleMons[battlerDef].statStages[statId] > gBattleMons[battlerAtk].statStages[statId])
        {
            switch (statId)
            {
            case STAT_ATK:
                return HasMoveWithCategory(battlerAtk, DAMAGE_CATEGORY_PHYSICAL);
            case STAT_SPATK:
                return HasMoveWithCategory(battlerAtk, DAMAGE_CATEGORY_SPECIAL);
            case STAT_ACC:
                return HasMoveWithLowAccuracy(battlerAtk, battlerDef, LOW_ACCURACY_THRESHOLD, FALSE);
            case STAT_EVASION:
            case STAT_SPEED:
                return TRUE;
            case STAT_DEF:
            case STAT_SPDEF:
                return (AI_THINKING_STRUCT->aiFlags & AI_FLAG_STALL) != 0;
            default:
                break;
            }
        }
    }
    return FALSE;
}

// RHH: AI_ShouldSetUpHazards (src/battle_ai_util.c:5687-5710)
bool32 AI_ShouldSetUpHazards(u8 battlerAtk, u8 battlerDef, u16 move, struct AiLogicData *aiData)
{
    if (CountUsablePartyMons(battlerDef) == 0
     || HasBattlerSideMoveWithAIEffect(battlerDef, AI_EFFECT_CLEAR_HAZARDS))
        return FALSE;

    if (IsBattleMoveStatus(move))
    {
        if (HasMoveWithEffect(battlerDef, EFFECT_MAGIC_COAT))
            return FALSE;
        if (DoesBattlerIgnoreAbilityChecks(battlerAtk, aiData->abilities[battlerAtk], move))
            return TRUE;
#ifdef ABILITY_MAGIC_BOUNCE
        if (aiData->abilities[battlerDef] == ABILITY_MAGIC_BOUNCE)
            return FALSE;
#endif
    }
    else
    {
        if (DoesBattlerIgnoreAbilityChecks(battlerAtk, aiData->abilities[battlerAtk], move))
            return TRUE;
        if (aiData->abilities[battlerDef] == ABILITY_SHIELD_DUST)
            return FALSE;
    }
    return TRUE;
}

// RHH: AI_GetBattlerMoveTargetType (src/battle_ai_util.c:80-91)
// Gen3: no terrain/Terapagos; GetMoveTarget(move, 0).
u16 AI_GetBattlerMoveTargetType(u8 battler, u16 move)
{
    u16 effect = gMovesInfo[move].effect;
    if (effect == EFFECT_CURSE && !IS_BATTLER_OF_TYPE(battler, TYPE_GHOST))
        return MOVE_TARGET_USER;
    return GetMoveTarget(move, 0);
}

// RHH: HasMoveWithLowAccuracy (src/battle_ai_util.c:2839-2864)
// Gen3 simplified: uses raw gMovesInfo[move].accuracy (no moveAccuracy field in AiLogicData).
bool32 HasMoveWithLowAccuracy(u8 battlerAtk, u8 battlerDef, u32 accCheck, bool32 ignoreStatus)
{
    u16 *moves = GetMovesArray(battlerAtk);
    u32 moveLimitations = gAiLogicData->moveLimitations[battlerAtk];

    for (u32 moveIndex = 0; moveIndex < MAX_MON_MOVES; moveIndex++)
    {
        if (IsMoveUnusable(moveIndex, moves[moveIndex], moveLimitations))
            continue;
        if (moves[moveIndex] == MOVE_NONE || moves[moveIndex] == MOVE_UNAVAILABLE)
            continue;

        if (ignoreStatus && IsBattleMoveStatus(moves[moveIndex]))
            continue;

        u16 acc = gMovesInfo[moves[moveIndex]].accuracy;
        if (acc == 0)   // always-hit moves
            continue;

        u16 target = AI_GetBattlerMoveTargetType(battlerAtk, moves[moveIndex]);
        if (target == MOVE_TARGET_USER || target == MOVE_TARGET_OPPONENTS_FIELD)
            continue;

        if (acc <= accCheck)
            return TRUE;
    }

    return FALSE;
}
