// Extracted from RHH src/battle_ai_util.c:481-510
// 30 lines
// Dependencies: AI_CanBattlerEscape, AI_IsAbilityOnSide, AI_IsBattlerGrounded, CountUsablePartyMons, IsBattlerTrapped

bool32 IsBattlerTrapped(enum BattlerId battlerAtk, enum BattlerId battlerDef)
{
    if (AI_CanBattlerEscape(battlerDef))
        return FALSE;

    if (gBattleMons[battlerDef].volatiles.wrapped)
        return TRUE;
    if (gBattleMons[battlerDef].volatiles.escapePrevention)
        return TRUE;
    if (gBattleMons[battlerDef].volatiles.semiInvulnerable == STATE_SKY_DROP)
        return TRUE;
    if (gBattleMons[battlerDef].volatiles.root)
        return TRUE;
    if (gFieldStatuses & STATUS_FIELD_FAIRY_LOCK)
        return TRUE;
    if (AI_IsAbilityOnSide(battlerAtk, ABILITY_SHADOW_TAG)
        && (B_SHADOW_TAG_ESCAPE >= GEN_4 && gAiLogicData->abilities[battlerDef] != ABILITY_SHADOW_TAG))
        return TRUE;
    if (AI_IsAbilityOnSide(battlerAtk, ABILITY_ARENA_TRAP)
        && AI_IsBattlerGrounded(battlerAtk))
        return TRUE;
    if (AI_IsAbilityOnSide(battlerAtk, ABILITY_MAGNET_PULL)
        && IS_BATTLER_OF_TYPE(battlerAtk, TYPE_STEEL))
        return TRUE;

    if (gBattleTypeFlags & BATTLE_TYPE_TRAINER && CountUsablePartyMons(battlerDef) == 0)
        return TRUE;

    return FALSE;
}
