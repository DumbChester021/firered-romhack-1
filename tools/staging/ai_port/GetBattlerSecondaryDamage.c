// Extracted from RHH src/battle_ai_util.c:3417-3432
// 16 lines
// Dependencies: GetBattlerSecondaryDamage, GetCurseDamage, GetLeechSeedDamage, GetNightmareDamage, GetPoisonDamage, GetTrapDamage, GetWeatherDamage

u32 GetBattlerSecondaryDamage(enum BattlerId battlerId)
{
    u32 secondaryDamage;

    if (gAiLogicData->abilities[battlerId] == ABILITY_MAGIC_GUARD)
        return FALSE;

    secondaryDamage = GetLeechSeedDamage(battlerId)
     + GetNightmareDamage(battlerId)
     + GetCurseDamage(battlerId)
     + GetTrapDamage(battlerId)
     + GetPoisonDamage(battlerId)
     + GetWeatherDamage(battlerId);

    return secondaryDamage;
}
