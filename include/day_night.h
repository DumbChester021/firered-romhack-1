#ifndef GUARD_DAY_NIGHT_H
#define GUARD_DAY_NIGHT_H

#include "constants/day_night.h"

struct DnTintColor
{
    u16 r;
    u16 g;
    u16 b;
};

void DayNight_Init(void);
void DayNight_UpdateClock(void);
u8   DayNight_GetTimeOfDay(void);
u8   DayNight_GetCurrentHour(void);
void DayNight_ApplyTintToFadedPalettes(void);
void DayNight_SetTintImmediate(u8 timeOfDay);
bool8 DayNight_IsTintActive(void);

#endif // GUARD_DAY_NIGHT_H
