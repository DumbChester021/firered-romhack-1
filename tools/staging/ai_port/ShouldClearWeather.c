// Extracted from RHH src/battle_ai_util.c:2237-2240
// 4 lines
// Dependencies: ShouldClearWeather, WeatherChecker

bool32 ShouldClearWeather(enum BattlerId battler, u32 weather)
{
    return WeatherChecker(battler, weather, FIELD_EFFECT_NEGATIVE);
}
