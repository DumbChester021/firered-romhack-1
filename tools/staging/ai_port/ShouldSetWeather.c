// Extracted from RHH src/battle_ai_util.c:2229-2235
// 7 lines
// Dependencies: AI_GetWeather, ShouldSetWeather, WeatherChecker

bool32 ShouldSetWeather(enum BattlerId battler, u32 weather)
{
    if (AI_GetWeather() & weather)
        return FALSE;

    return WeatherChecker(battler, weather, FIELD_EFFECT_POSITIVE);
}
