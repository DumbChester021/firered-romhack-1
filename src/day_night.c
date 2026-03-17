#include "global.h"
#include "gflib.h"
#include "day_night.h"
#include "overworld.h"
#include "field_weather.h"
#include "constants/day_night.h"
#include "constants/field_weather.h"

struct DayNightState
{
    u8 currentHour;
    u8 currentMinute;
    u8 currentTimeOfDay;
    u8 previousTimeOfDay;
    struct DnTintColor currentTint;
    struct DnTintColor targetTint;
    u16 transitionWeight;
    u8 transitionDelayCounter;
    bool8 initialized;
};

static EWRAM_DATA struct DayNightState sDayNight = {};

static const struct DnTintColor sTimeOfDayTints[TIME_OF_DAY_COUNT] = {
    [TIME_OF_DAY_MORNING] = { DN_TINT_MORNING_R, DN_TINT_MORNING_G, DN_TINT_MORNING_B },
    [TIME_OF_DAY_DAY]     = { DN_TINT_DAY_R,     DN_TINT_DAY_G,     DN_TINT_DAY_B },
    [TIME_OF_DAY_EVENING] = { DN_TINT_EVENING_R, DN_TINT_EVENING_G, DN_TINT_EVENING_B },
    [TIME_OF_DAY_NIGHT]   = { DN_TINT_NIGHT_R,   DN_TINT_NIGHT_G,   DN_TINT_NIGHT_B },
};

static u8 ResolveTimeOfDay(u8 hour)
{
    if (hour >= DN_HOUR_NIGHT || hour < DN_HOUR_MORNING)
        return TIME_OF_DAY_NIGHT;
    if (hour >= DN_HOUR_EVENING)
        return TIME_OF_DAY_EVENING;
    if (hour >= DN_HOUR_DAY)
        return TIME_OF_DAY_DAY;
    return TIME_OF_DAY_MORNING;
}

static void ComputeClockFromPlayTime(void)
{
    u32 totalPlayMinutes;
    u32 totalInGameMinutes;

    totalPlayMinutes = (u32)gSaveBlock2Ptr->playTimeHours * 60
                     + (u32)gSaveBlock2Ptr->playTimeMinutes;

#if DN_MINUTES_PER_INGAME_HOUR > 0
    totalInGameMinutes = totalPlayMinutes / DN_MINUTES_PER_INGAME_HOUR;
#else
    totalInGameMinutes = totalPlayMinutes * 60
                       + (u32)gSaveBlock2Ptr->playTimeSeconds;
#endif

    sDayNight.currentHour   = (totalInGameMinutes / 60) % 24;
    sDayNight.currentMinute = totalInGameMinutes % 60;
}

static struct DnTintColor LerpTint(const struct DnTintColor *old, const struct DnTintColor *tgt, u16 weight)
{
    struct DnTintColor result;
    result.r = old->r + (((s32)(tgt->r - old->r) * weight) >> 8);
    result.g = old->g + (((s32)(tgt->g - old->g) * weight) >> 8);
    result.b = old->b + (((s32)(tgt->b - old->b) * weight) >> 8);
    return result;
}

void DayNight_Init(void)
{
#if !DN_ENABLED
    return;
#endif
    ComputeClockFromPlayTime();
    sDayNight.currentTimeOfDay  = ResolveTimeOfDay(sDayNight.currentHour);
    sDayNight.previousTimeOfDay = sDayNight.currentTimeOfDay;
    sDayNight.currentTint = sTimeOfDayTints[sDayNight.currentTimeOfDay];
    sDayNight.targetTint  = sDayNight.currentTint;
    sDayNight.transitionWeight = DN_WEIGHT_MAX;
    sDayNight.transitionDelayCounter = 0;
    sDayNight.initialized = TRUE;
}

void DayNight_UpdateClock(void)
{
    u8 newTimeOfDay;

#if !DN_ENABLED
    return;
#endif

    if (!sDayNight.initialized)
        DayNight_Init();

    ComputeClockFromPlayTime();
    newTimeOfDay = ResolveTimeOfDay(sDayNight.currentHour);

    if (newTimeOfDay != sDayNight.currentTimeOfDay)
    {
        sDayNight.previousTimeOfDay = sDayNight.currentTimeOfDay;
        sDayNight.currentTimeOfDay  = newTimeOfDay;
        sDayNight.targetTint  = sTimeOfDayTints[newTimeOfDay];
        sDayNight.transitionWeight = 0;
        sDayNight.transitionDelayCounter = 0;
    }

    if (sDayNight.transitionWeight < DN_WEIGHT_MAX)
    {
        if (++sDayNight.transitionDelayCounter >= DN_TRANSITION_STEP_DELAY)
        {
            sDayNight.transitionDelayCounter = 0;
            sDayNight.transitionWeight += 4;
            if (sDayNight.transitionWeight > DN_WEIGHT_MAX)
                sDayNight.transitionWeight = DN_WEIGHT_MAX;
            if (sDayNight.transitionWeight == DN_WEIGHT_MAX)
                sDayNight.currentTint = sDayNight.targetTint;
        }
    }
}

u8 DayNight_GetTimeOfDay(void)
{
    return sDayNight.currentTimeOfDay;
}

u8 DayNight_GetCurrentHour(void)
{
    return sDayNight.currentHour;
}

bool8 DayNight_IsTintActive(void)
{
#if !DN_ENABLED
    return FALSE;
#endif
    if (!sDayNight.initialized)
        return FALSE;
    if (sDayNight.currentTint.r == 256 && sDayNight.currentTint.g == 256 && sDayNight.currentTint.b == 256
        && sDayNight.targetTint.r == 256 && sDayNight.targetTint.g == 256 && sDayNight.targetTint.b == 256)
        return FALSE;
    return TRUE;
}

// Composited day/night tint + screen fade application.
//
// Modeled after RHH's TIME_OF_DAY_FADE: tint and fade are computed
// together in a single pass to prevent any frame where untinted
// colors are visible.
//
// Pipeline per pixel:
//   1. Read from gPlttBufferUnfaded (always — prevents compounding)
//   2. Apply multiplicative time-of-day tint
//   3. If NORMAL_FADE active for this palette, blend toward
//      fade's target color at its current coefficient
//   4. Write to gPlttBufferFaded
//
// Hardware fades (BLDCNT/BLDY) are handled by the hardware on top
// of whatever we write to gPlttBufferFaded, so we just write tinted
// values and the hardware darkens/lightens them correctly.
void DayNight_ApplyTintToFadedPalettes(void)
{
    u32 selectedPalettes;
    u16 palOffset;
    u32 palIndex;
    struct DnTintColor tint;
    bool8 normalFadeActive;
    u32 fadePalettes;
    u8 fadeCoeff;
    s32 fadeR, fadeG, fadeB;

#if !DN_ENABLED
    return;
#endif

    if (!sDayNight.initialized)
        return;

    if (!IsMapTypeOutdoors(gMapHeader.mapType))
        return;

    // After a fade-to-black/white completes, active=FALSE but y stays
    // at targetY (e.g. 16). The screen should remain fully faded until
    // the next fade begins. Don't overwrite with tinted colors.
    if (!gPaletteFade.active && gPaletteFade.y > 0)
        return;

    if (sDayNight.transitionWeight >= DN_WEIGHT_MAX)
        tint = sDayNight.currentTint;
    else
        tint = LerpTint(&sDayNight.currentTint, &sDayNight.targetTint, sDayNight.transitionWeight);

    if (tint.r == 256 && tint.g == 256 && tint.b == 256)
        return;

    // Check for active NORMAL software fade.
    // NORMAL_FADE uses BlendPalette (unfaded → faded) which we must
    // composite with, otherwise the fade overwrites or is overwritten.
    // HARDWARE_FADE uses BLDY registers — our tinted gPlttBufferFaded
    // is darkened/lightened by hardware, no conflict.
    // FAST_FADE modifies faded incrementally — we skip compositing for
    // it since it's brief full-screen transitions.
    normalFadeActive = (gPaletteFade.active && gPaletteFade.mode == 0); // 0 = NORMAL_FADE (private enum in palette.c)
    if (normalFadeActive)
    {
        fadePalettes = gPaletteFade_selectedPalettes;
        fadeCoeff = gPaletteFade.y;
        fadeR = (gPaletteFade.blendColor >> 0) & 0x1F;
        fadeG = (gPaletteFade.blendColor >> 5) & 0x1F;
        fadeB = (gPaletteFade.blendColor >> 10) & 0x1F;
    }
    else
    {
        fadePalettes = 0;
        fadeCoeff = 0;
        fadeR = fadeG = fadeB = 0;
    }

    selectedPalettes = DN_TINTABLE_MASK;

    for (palIndex = 0, palOffset = 0; selectedPalettes != 0; palIndex++, palOffset += 16)
    {
        if (selectedPalettes & 1)
        {
            u16 i;
            bool8 fadeThisPal = normalFadeActive && (fadePalettes & (1u << palIndex));

            for (i = 0; i < 16; i++)
            {
                u16 srcColor = gPlttBufferUnfaded[palOffset + i];
                s32 r = (srcColor >>  0) & 0x1F;
                s32 g = (srcColor >>  5) & 0x1F;
                s32 b = (srcColor >> 10) & 0x1F;

                // Step 1: Multiplicative tint
                r = (r * tint.r) >> 8;
                g = (g * tint.g) >> 8;
                b = (b * tint.b) >> 8;

                // Step 2: Compose with screen fade blend if active
                // Formula: result = tinted + ((fadeColor - tinted) * coeff) / 16
                if (fadeThisPal)
                {
                    r += ((fadeR - r) * fadeCoeff) >> 4;
                    g += ((fadeG - g) * fadeCoeff) >> 4;
                    b += ((fadeB - b) * fadeCoeff) >> 4;
                }

                if (r > 31) r = 31;
                if (g > 31) g = 31;
                if (b > 31) b = 31;
                if (r < 0) r = 0;
                if (g < 0) g = 0;
                if (b < 0) b = 0;

                gPlttBufferFaded[palOffset + i] = (u16)(r | (g << 5) | (b << 10));
            }
        }
        selectedPalettes >>= 1;
    }
}

void DayNight_SetTintImmediate(u8 timeOfDay)
{
#if !DN_ENABLED
    return;
#endif
    if (timeOfDay >= TIME_OF_DAY_COUNT)
        timeOfDay = TIME_OF_DAY_DAY;
    sDayNight.currentTimeOfDay  = timeOfDay;
    sDayNight.previousTimeOfDay = timeOfDay;
    sDayNight.currentTint = sTimeOfDayTints[timeOfDay];
    sDayNight.targetTint  = sDayNight.currentTint;
    sDayNight.transitionWeight = DN_WEIGHT_MAX;
}
