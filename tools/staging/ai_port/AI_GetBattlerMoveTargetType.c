// Extracted from RHH src/battle_ai_util.c:80-91
// 12 lines
// Dependencies: AI_CanBattlerHitBothFoesInTerrain, AI_GetBattlerMoveTargetType, GetMoveEffect, GetMoveTarget

enum MoveTarget AI_GetBattlerMoveTargetType(enum BattlerId battler, enum Move move)
{
    enum BattleMoveEffects effect = GetMoveEffect(move);
    if (effect == EFFECT_CURSE && !IS_BATTLER_OF_TYPE(battler, TYPE_GHOST))
        return TARGET_USER;
    if (AI_CanBattlerHitBothFoesInTerrain(battler, move, effect))
        return TARGET_BOTH;
    if (effect == EFFECT_TERA_STARSTORM && gBattleMons[battler].species == SPECIES_TERAPAGOS_STELLAR)
        return TARGET_BOTH;

    return GetMoveTarget(move);
}
