// === RHH AI Scoring Functions — Extracted for Porting ===
// Functions: ShouldTryToFlinch
// Total extracted: 21 lines


// --- ShouldTryToFlinch (src/battle_ai_util.c:3754-3774) ---
bool32 ShouldTryToFlinch(enum BattlerId battlerAtk, enum BattlerId battlerDef, enum Ability atkAbility, enum Ability defAbility, enum Move move)
{
    enum Move predictedMoveSpeedCheck = GetIncomingMoveSpeedCheck(battlerAtk, battlerDef, gAiLogicData);
    if (((!IsMoldBreakerTypeAbility(battlerAtk, gAiLogicData->abilities[battlerAtk]) && (defAbility == ABILITY_SHIELD_DUST || defAbility == ABILITY_INNER_FOCUS))
      || gAiLogicData->holdEffects[battlerDef] == HOLD_EFFECT_COVERT_CLOAK
      || DoesSubstituteBlockMove(battlerAtk, battlerDef, move)
      || AI_IsSlower(battlerAtk, battlerDef, move, predictedMoveSpeedCheck, CONSIDER_PRIORITY))) // Opponent goes first
    {
        return FALSE;
    }
    else if ((atkAbility == ABILITY_SERENE_GRACE
      || gBattleMons[battlerDef].status1 & STATUS1_PARALYSIS
      || gBattleMons[battlerDef].volatiles.infatuation
      || gBattleMons[battlerDef].volatiles.confusionTurns > 0)
      || ((AI_IsFaster(battlerAtk, battlerDef, move, predictedMoveSpeedCheck, CONSIDER_PRIORITY)) && CanTargetFaintAi(battlerDef, battlerAtk)))
    {
        return TRUE;   // good idea to flinch
    }

    return FALSE;   // don't try to flinch
}
