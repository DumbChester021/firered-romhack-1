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
#include "constants/moves.h"
#include "constants/battle_move_effects.h"

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

// ============================================================================
// Gen 4+ Stubs — return safe neutral values.
// Replace stub bodies when implementing the corresponding mechanics.
// ============================================================================

// GEN4_STUB
s32 AI_GetAbilityRating(u8 ability)
{
    (void)ability;
    return 0;
}

// GEN4_STUB
bool8 AI_IsTerrainActive(u8 terrainFlag)
{
    (void)terrainFlag;
    return FALSE;
}

// GEN4_STUB
bool8 AI_IsTrickRoomActive(void)
{
    return FALSE;
}

// =============================================================================
// Phase 3: additionalEffects AI helper
// RHH source: pokeemerald-expansion/src/battle_ai_util.c
// Returns TRUE if any of battlerId's moves have an additionalEffects entry
// matching moveEffect (targeting the foe).
// =============================================================================
bool8 HasMoveWithAdditionalEffect(u8 battlerId, u16 moveEffect)
{
    u8 i;
    for (i = 0; i < MAX_MON_MOVES; i++)
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
// Returns TRUE if the AI_FLAG_PREDICT_MOVE flag is set for any battler.
bool32 CanAiPredictMove(u8 battlerId)
{
#ifdef AI_FLAG_PREDICT_MOVE
    if (IsAiFlagPresent(AI_FLAG_PREDICT_MOVE))
        return TRUE;
#endif
    (void)battlerId;
    return FALSE;
}

// RHH: IsBattlerPredictedToSwitch (pokeemerald-expansion/src/battle_ai_util.c:190)
// Returns TRUE if the AI predicts the given battler will switch this turn.
// RHH checks per-battler aiFlags[battlerIndex]. FireRed has a single aiFlags — use
// AI_FLAG_PREDICT_SWITCH when that constant is added; until then always returns FALSE.
bool32 IsBattlerPredictedToSwitch(u8 battler)
{
#ifdef AI_FLAG_PREDICT_SWITCH
    if (IsAiFlagPresent(AI_FLAG_PREDICT_SWITCH))
    {
        if (gAiLogicData->predictingSwitch && gAiLogicData->shouldSwitch & (1u << battler))
            return TRUE;
    }
#else
    (void)battler;
#endif
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
}
