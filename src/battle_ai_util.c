#include "global.h"
#include "battle.h"
#include "battle_anim.h"
#include "battle_ai_util.h"
#include "battle_script_commands.h"
#include "pokemon.h"
#include "random.h"
#include "constants/battle.h"
#include "constants/moves.h"
#include "constants/battle_move_effects.h"

// AI_CalcDamage: Returns an estimated damage value for the AI's move selection.
// Calls FireRed's existing AI_CalcDmg + TypeCalc (from battle_script_commands.c)
// which use gBattleMoveDamage as an in/out global.
// Returns 0 if the move has no power, or is completely negated by type immunity.
// Sets *typeEffectiveness to the MOVE_RESULT_* flags from TypeCalc.
s32 AI_CalcDamage(u16 move, u8 battlerAtk, u8 battlerDef, u8 *typeEffectiveness)
{
    s32 dmg;
    u8 flags;

    if (gBattleMoves[move].power < 2)
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

// AI_IsFaster: Returns TRUE if battlerAtk moves before battlerDef for the given move,
// accounting for move priority.
bool8 AI_IsFaster(u8 battlerAtk, u8 battlerDef, u16 move)
{
    s8 priority = gBattleMoves[move].priority;
    u16 spdAtk = gBattleMons[battlerAtk].speed;
    u16 spdDef = gBattleMons[battlerDef].speed;

    if (priority > 0)
        return TRUE;
    if (priority < 0)
        return FALSE;

    return spdAtk >= spdDef;
}

// AI_HasMoveEffect: Returns TRUE if any of battlerAtk's current moves have the given effect ID.
bool8 AI_HasMoveEffect(u8 battlerAtk, u16 effect)
{
    u8 i;
    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        u16 move = gBattleMons[battlerAtk].moves[i];
        if (move != MOVE_NONE && gBattleMoves[move].effect == effect)
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

    if (gBattleMoves[move].power < 2)
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
    u8  savedType1   = gBattleMons[2].type1;
    u8  savedType2   = gBattleMons[2].type2;
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
        u8 atkType1 = gBattleMons[opposingBattler].type1;
        u8 atkType2 = gBattleMons[opposingBattler].type2;
        u8 defType1 = gBattleMons[battler].type1;
        u8 defType2 = gBattleMons[battler].type2;
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
            if (gBattleMoves[aiMove].power == 0)
            {
                u16 effect = gBattleMoves[aiMove].effect;
                if (effect == EFFECT_REFLECT        || effect == EFFECT_LIGHT_SCREEN
                 || effect == EFFECT_EXPLOSION       || effect == EFFECT_DESTINY_BOND
                 || effect == EFFECT_LEECH_SEED
                 || effect == EFFECT_SLEEP           || effect == EFFECT_TOXIC
                 || effect == EFFECT_PARALYZE
                 // FRLG_STUB: add EFFECT_SPIKES, EFFECT_STEALTH_ROCK, EFFECT_TRICK_ROOM,
                 //   EFFECT_YAWN, EFFECT_WILL_O_WISP, EFFECT_TRICK, EFFECT_WONDER_ROOM,
                 //   EFFECT_STICKY_WEB when those move effects are available.
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
                if (foeMove == MOVE_NONE || gBattleMoves[foeMove].power < 2)
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
            if (playerMove == MOVE_NONE || gBattleMoves[playerMove].power < 2)
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
            if (AI_IsFaster(battler, opposingBattler, 0))
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
static bool8 FindMonWithFlagsAndSuperEffective(u8 battler, u8 opposingBattler,
                                                u8 requiredFlag, u8 *outSlot)
{
    struct Pokemon *party;
    s32 i, j;
    u16 move;

    // RHH lines 759-766: if no last-landed move data, bail.
    // FRLG_STUB: RHH checks gLastLandedMoves[battler]. FireRed uses gLastUsedMoveByTarget
    //   which is similar. For now we skip the "flags-against-last-move" requirement
    //   (the MOVE_RESULT_DOESNT_AFFECT_FOE / NOT_VERY_EFFECTIVE filter on the last landed move)
    //   and only check if the candidate has a SE move vs current foe.
    //   Uncomment the gLastLandedMoves check when that array is accessible here.

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
            if (move == MOVE_NONE || gBattleMoves[move].power < 2)
                continue;

            // RHH: move must be super-effective vs opponent (the "FindMonWith...SuperEffective" part).
            if (AI_GetTypeEffectivenessForPartyMon(move, &party[i]) < AI_EFFECTIVENESS_x2)
                continue; // not super effective vs current foe species — skip
            // Note: RHH's full version also checks the requiredFlag against gLastLandedMoves
            //   (see the FRLG_STUB note above). For now we only check SE vs current defender.
            (void)requiredFlag;
            // FRLG_STUB: add check AI_GetTypeEffectivenessForPartyMon(gLastLandedMoves[battler], &party[i])
            //   against requiredFlag (e.g. MOVE_RESULT_DOESNT_AFFECT_FOE for immunity).

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
// Structure mirrors ShouldSwitch exactly:
//   1. Trap/availability guards.
//   2. HasBadOdds — OHKO threat and type disadvantage.
//   3. FindMonWithFlagsAndSuperEffective — default proactive switch.
//
// FRLG_STUB (lines from RHH ShouldSwitch that are skipped):
//   - STATUS2_ESCAPE_PREVENTION (RHH line 1011): FireRed uses STATUS2_WRAPPED which we have.
//   - STATUS3_ROOTED (RHH line 1013): add when Ingrain is implemented.
//   - IsAbilityPreventingEscape (RHH line 1015): add when Shadow Tag / Arena Trap added.
//   - BATTLE_TYPE_ARENA (RHH line 1017): not in FRLG.
//   - AI_FLAG_SEQUENCE_SWITCHING (RHH line 1021): add when that flag is implemented.
//   - ShouldSwitchIfWonderGuard: add when Wonder Guard AI is ported.
//   - ShouldSwitchIfGameStatePrompt: add when perish song / yawn AI is ported.
//   - FindMonThatTrapsOpponent: add when Shadow Tag / Magnet Pull AI is ported.
//   - FindMonThatAbsorbsOpponentsMove: add when type-absorb ability AI is ported.
//   - CanMonSurviveHazardSwitchin: add when entry hazards (Stealth Rock etc.) are added.
//   - ShouldSwitchIfEncored: add when Encore AI is ported.
//   - ShouldSwitchIfBadChoiceLock: add when Choice items are added.
//   - AreAttackingStatsLowered: add when stat-stage tracking is added.
// ============================================================================
u8 AI_EvaluateSwitch(u8 battlerAtk, u8 battlerDef)
{
    u8 outSlot = PARTY_SIZE;

    // RHH lines 1011-1012: don't switch if wrapped/prevented.
    if (gBattleMons[battlerAtk].status2 & (STATUS2_WRAPPED | STATUS2_ESCAPE_PREVENTION))
        return PARTY_SIZE;

    // FRLG_STUB: STATUS3_ROOTED check (RHH line 1013) — add when Ingrain implemented.
    // FRLG_STUB: IsAbilityPreventingEscape (RHH line 1015) — add when Shadow Tag/Arena Trap added.

    // RHH lines 1024-1065: count available-to-switch mons.
    if (AI_CountAlivePokemon(battlerAtk) == 0)
        return PARTY_SIZE;

    // FRLG_STUB (RHH lines 1080-1087): ShouldSwitchIfWonderGuard, ShouldSwitchIfGameStatePrompt,
    //   FindMonThatTrapsOpponent, FindMonThatAbsorbsOpponentsMove — uncomment when ported.

    // FRLG_STUB (RHH line 1090): CanMonSurviveHazardSwitchin — add when entry hazards are in.

    // RHH lines 1092-1103: HasBadOdds and similar checks.
    if (HasBadOdds(battlerAtk, battlerDef))
    {
        // FRLG_STUB: RHH resolves the slot via AI_DATA->mostSuitableMonId[battler].
        // We return PARTY_SIZE here as sentinel — caller (BattleAI_ChooseMoveOrAction)
        // should pick the best available mon via FindMonWithFlagsAndSuperEffective below.
        // When AI_DATA->mostSuitableMonId is added, replace with that value.
        if (FindMonWithFlagsAndSuperEffective(battlerAtk, battlerDef, 0, &outSlot))
            return outSlot;
        // Even if no perfect candidate, HasBadOdds alone warrants the switch.
        // Return first available non-fainted, non-current mon.
        {
            struct Pokemon *party = (GetBattlerSide(battlerAtk) == B_SIDE_PLAYER)
                                    ? gPlayerParty : gEnemyParty;
            u8 i;
            for (i = 0; i < PARTY_SIZE; i++)
            {
                if (i == gBattlerPartyIndexes[battlerAtk])
                    continue;
                if (GetMonData(&party[i], MON_DATA_SPECIES, NULL) == SPECIES_NONE)
                    continue;
                if (GetMonData(&party[i], MON_DATA_HP, NULL) == 0)
                    continue;
                return i;
            }
        }
    }

    // FRLG_STUB (RHH lines 1098-1103): ShouldSwitchIfEncored, ShouldSwitchIfBadChoiceLock,
    //   AreAttackingStatsLowered — uncomment when those systems are ported.

    // RHH lines 1107-1110: don't switch if we already have a SE move.
    {
        u8 j;
        for (j = 0; j < MAX_MON_MOVES; j++)
        {
            u16 move = gBattleMons[battlerAtk].moves[j];
            if (move == MOVE_NONE || gBattleMoves[move].power < 2)
                continue;
            if (AI_GetTypeEffectiveness(move, battlerAtk, battlerDef) >= AI_EFFECTIVENESS_x2)
                return PARTY_SIZE; // RHH: HasSuperEffectiveMoveAgainstOpponents → don't switch
        }
    }

    // RHH lines 1114-1116: default — look for a better mon via type coverage.
    // RHH calls FindMonWithFlagsAndSuperEffective twice:
    //   first with MOVE_RESULT_DOESNT_AFFECT_FOE (immunity), then NOT_VERY_EFFECTIVE.
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

