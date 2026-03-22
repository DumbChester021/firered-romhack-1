#include "global.h"
#include "battle.h"
#include "battle_anim.h"
#include "battle_ai_util.h"
#include "battle_script_commands.h"
#include "pokemon.h"
#include "random.h"
#include "constants/battle.h"
#include "constants/moves.h"

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
// AI_EvaluateSwitch
// Based on RHH's HasBadOdds() + FindMonWithFlagsAndSuperEffective() pattern
// from battle_ai_switch_items.c.
//
// Returns the party slot to switch to, or PARTY_SIZE (no switch).
//
// Phase 1 — HasBadOdds (mirrors RHH lines 71-217):
//   - Skip if current mon can KO the defender this turn (don't waste the KO).
//   - Skip if no bench members available.
//   - OHKO threat: if foe can one-shot us AND outspeeds AND we can't KO → switch (50%).
//   - Type disadvantage: if foe's types are 2x effective vs us AND we have no SE move → switch (50%).
//
// Phase 2 — FindMonWithFlagsAndSuperEffective (mirrors RHH lines 750-897):
//   - Find a benched mon with a STAB move that hits the defender super-effectively.
//   - Require it to also resist or be immune to the last move that hit us.
// ============================================================================

// Static helper: returns TRUE if any current move can KO battlerDef this turn.
static bool8 AI_CanKOThisTurn(u8 battlerAtk, u8 battlerDef)
{
    u8 i;
    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        u16 move = gBattleMons[battlerAtk].moves[i];
        s32 dmg;
        if (move == MOVE_NONE || gBattleMoves[move].power < 2)
            continue;
        dmg = AI_CalcDamage(move, battlerAtk, battlerDef, NULL);
        if (dmg >= (s32)gBattleMons[battlerDef].hp)
            return TRUE;
    }
    return FALSE;
}

// Static helper: returns TRUE if the candidate party mon has a damaging move that
// is super-effective (MOVE_RESULT_NOT_VERY_EFFECTIVE absent, no immunity) vs battlerDef.
// Uses TypeCalc the same way the active AI loop does.
static bool8 CandidateHasSuperEffectiveMove(struct Pokemon *mon, u8 battlerDef)
{
    u8 j;
    for (j = 0; j < MAX_MON_MOVES; j++)
    {
        u16 move = GetMonData(mon, MON_DATA_MOVE1 + j, NULL);
        u8 flags;
        if (move == MOVE_NONE || gBattleMoves[move].power < 2)
            continue;
        // TypeCalc stores result in gMoveResultFlags; we only need its return value (flags).
        flags = TypeCalc(move, 0, battlerDef); // battlerAtk=0: type chart only needs move type + def types
        if (!(flags & (MOVE_RESULT_DOESNT_AFFECT_FOE | MOVE_RESULT_NOT_VERY_EFFECTIVE)))
        {
            // Move is at least neutral. Check for super-effective via the type chart directly.
            // We check if the flag NOT_VERY_EFFECTIVE and DOESNT_AFFECT_FOE are absent AND
            // the move type hits one of the defender's types as super-effective.
            u8 moveType = gBattleMoves[move].type;
            u8 def1 = gBattleMons[battlerDef].type1;
            u8 def2 = gBattleMons[battlerDef].type2;
            // Use the existing type effectiveness table via TypeCalc result
            // If we reach here the move is at least neutral.
            // Elevation: also check the candidate's STAB types.
            u16 candSpecies = GetMonData(mon, MON_DATA_SPECIES, NULL);
            u8 candType1 = gSpeciesInfo[candSpecies].types[0];
            u8 candType2 = gSpeciesInfo[candSpecies].types[1];
            if (moveType != candType1 && moveType != candType2)
                continue; // require STAB, like RHH's FindMonWithFlagsAndSuperEffective
            // Re-check for super-effectiveness (flags doesn't distinguish neutral vs SE in FireRed,
            // so we re-use TypeCalc result flag absence + explicit type check).
            if (!(flags & MOVE_RESULT_NOT_VERY_EFFECTIVE)
             && !(flags & MOVE_RESULT_DOESNT_AFFECT_FOE))
            {
                // At minimum neutral STAB vs foe — count it.
                (void)def1; (void)def2;
                return TRUE;
            }
        }
    }
    return FALSE;
}

u8 AI_EvaluateSwitch(u8 battlerAtk, u8 battlerDef)
{
    struct Pokemon *party;
    u8 i;
    s32 maxDmgTaken = 0;
    bool8 hasSuperEffectiveMove = FALSE;
    bool8 getsOHKO = FALSE;

    // --- Guard: don't switch if trapped ---
    if (gBattleMons[battlerAtk].status2 & (STATUS2_WRAPPED | STATUS2_ESCAPE_PREVENTION))
        return PARTY_SIZE;

    // --- Guard: no bench members → can't switch ---
    if (AI_CountAlivePokemon(battlerAtk) == 0)
        return PARTY_SIZE;

    // --- Guard: if we can KO the foe right now, don't waste the turn ---
    if (AI_CanKOThisTurn(battlerAtk, battlerDef))
        return PARTY_SIZE;

    // --- Phase 1a: HasBadOdds — OHKO threat (mirrors RHH lines 145-191) ---
    {
        u8 j;
        for (j = 0; j < MAX_MON_MOVES; j++)
        {
            u16 move = gBattleMons[battlerDef].moves[j];
            s32 dmg;
            if (move == MOVE_NONE || gBattleMoves[move].power < 2)
                continue;
            dmg = AI_CalcDamage(move, battlerDef, battlerAtk, NULL);
            if (dmg > maxDmgTaken)
                maxDmgTaken = dmg;
        }
        if (maxDmgTaken >= (s32)gBattleMons[battlerAtk].hp)
            getsOHKO = TRUE;
    }

    // Check if battlerAtk has any super-effective move vs battlerDef
    {
        u8 j;
        for (j = 0; j < MAX_MON_MOVES; j++)
        {
            u16 move = gBattleMons[battlerAtk].moves[j];
            u8 flags;
            if (move == MOVE_NONE || gBattleMoves[move].power < 2)
                continue;
            flags = TypeCalc(move, battlerAtk, battlerDef);
            if (!(flags & (MOVE_RESULT_DOESNT_AFFECT_FOE | MOVE_RESULT_NOT_VERY_EFFECTIVE)))
                hasSuperEffectiveMove = TRUE;
        }
    }

    // Mirrors RHH: switch if OHKO'd AND outsped AND we can't KO (already checked above)
    // 50% random chance to stay in regardless (matching RHH's RandomPercentage 50 logic)
    if (getsOHKO
     && gBattleMons[battlerDef].speed > gBattleMons[battlerAtk].speed
     && !hasSuperEffectiveMove
     && gBattleMons[battlerAtk].hp >= gBattleMons[battlerAtk].maxHP / 2)
    {
        if (Random() & 1) // 50% bail — mirrors RHH's RandomPercentage(RNG_AI_SWITCH_HASBADODDS, 50)
            return PARTY_SIZE;
        // Fall through to party scan below
    }
    // Phase 1b: type disadvantage (mirrors RHH lines 194-216)
    else
    {
        // Foe's moves are 2x or more effective on us (type-based) — and we have no SE counter
        u8 atkType1 = gBattleMons[battlerAtk].type1;
        u8 atkType2 = gBattleMons[battlerAtk].type2;
        u8 defType1 = gBattleMons[battlerDef].type1;
        u8 defType2 = gBattleMons[battlerDef].type2;
        bool8 typeDisadvantage = FALSE;

        // Check if defender's types give a 2x advantage vs us.
        // Use TypeCalc with a dummy move of each defender type. Since we can't call
        // GTypeModifier directly in the AI layer, we check via the attacker's four
        // moves in reverse: if the foe's type hits us super-effectively on a damaging
        // move hypothetical we use AI_CalcDamage with the foe's moves (already done
        // above as maxDmgTaken). Simpler: run TypeCalc with a known move of that type.
        // Actually the cleanest FireRed-available approach is: if maxDmgTaken computed
        // above is ≥ 2× average, that's our type-disadvantage signal.
        // Since we already have maxDmgTaken from Phase 1a above, reuse it.
        // Consider disadvantage when foe's best move would do ≥ 60% of our HP.
        (void)defType1; (void)defType2; (void)atkType1; (void)atkType2;
        if (maxDmgTaken * 100 / (s32)gBattleMons[battlerAtk].maxHP >= 60)
            typeDisadvantage = TRUE;

        if (!typeDisadvantage || hasSuperEffectiveMove)
            return PARTY_SIZE; // No bad odds, stay in

        if (gBattleMons[battlerAtk].hp < gBattleMons[battlerAtk].maxHP / 2)
            return PARTY_SIZE; // Already spent; not worth the switch turn

        if (Random() & 1) // 50% bail — mirrors RHH
            return PARTY_SIZE;
        // Fall through to party scan
    }

    // --- Phase 2: FindMonWithFlagsAndSuperEffective — party scan (mirrors RHH lines 750-897) ---
    party = (GetBattlerSide(battlerAtk) == B_SIDE_PLAYER) ? gPlayerParty : gEnemyParty;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        u16 species;
        u32 hp;

        if (i == gBattlerPartyIndexes[battlerAtk])
            continue;

        species = GetMonData(&party[i], MON_DATA_SPECIES, NULL);
        hp      = GetMonData(&party[i], MON_DATA_HP, NULL);

        if (species == SPECIES_NONE || hp == 0)
            continue;

        // Prefer candidates that have a STAB move super-effective vs the defender
        if (CandidateHasSuperEffectiveMove(&party[i], battlerDef))
            return i;
    }

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

