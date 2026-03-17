#ifndef GUARD_CONSTANTS_DAY_NIGHT_H
#define GUARD_CONSTANTS_DAY_NIGHT_H

#include "constants/rgb.h"

// Time-of-day periods
#define TIME_OF_DAY_MORNING   0  // DN_HOUR_MORNING to DN_HOUR_DAY - 1
#define TIME_OF_DAY_DAY       1  // DN_HOUR_DAY     to DN_HOUR_EVENING - 1
#define TIME_OF_DAY_EVENING   2  // DN_HOUR_EVENING  to DN_HOUR_NIGHT - 1
#define TIME_OF_DAY_NIGHT     3  // DN_HOUR_NIGHT    to DN_HOUR_MORNING - 1
#define TIME_OF_DAY_COUNT     4

// Hour boundaries for each period (24-hour format)
#define DN_HOUR_MORNING    6
#define DN_HOUR_DAY       10
#define DN_HOUR_EVENING   17
#define DN_HOUR_NIGHT     20

// Palette slot masks
// BG palettes 0-12 (tileset/map), skip 13-15 (UI/textbox)
#define DN_TINTABLE_BG_MASK   0x00001FFF
// OBJ palettes 16-27 (overworld sprites), skip 28-31 (UI sprites)
#define DN_TINTABLE_OBJ_MASK  0x0FFF0000
#define DN_TINTABLE_MASK      (DN_TINTABLE_BG_MASK | DN_TINTABLE_OBJ_MASK)

// Multiplicative tint colors per time-of-day.
// These are Q8.8 fixed-point scale factors per channel (256 = 1.0 = no change).
// The tint is applied as: outColor = (srcColor * tintFactor) >> 8
// Lower values = darker. Values > 256 would brighten (not used).
//
// Morning: warm amber glow — slightly reduce blue, boost red warmth
#define DN_TINT_MORNING_R  248   // ~0.97
#define DN_TINT_MORNING_G  220   // ~0.86
#define DN_TINT_MORNING_B  180   // ~0.70

// Day: identity — no tinting
#define DN_TINT_DAY_R      256   // 1.0
#define DN_TINT_DAY_G      256   // 1.0
#define DN_TINT_DAY_B      256   // 1.0

// Evening: warm orange sunset
#define DN_TINT_EVENING_R  245   // ~0.96
#define DN_TINT_EVENING_G  200   // ~0.78
#define DN_TINT_EVENING_B  160   // ~0.63

// Night: cool blue moonlight (matches RHH's Q_8_8 values)
#define DN_TINT_NIGHT_R    117   // ~0.456 (Q_8_8(0.456))
#define DN_TINT_NIGHT_G    117   // ~0.456
#define DN_TINT_NIGHT_B    157   // ~0.615

// Transition: frames between blend weight steps (higher = slower transition)
#define DN_TRANSITION_STEP_DELAY  2

// Transition weight range: 0 = fully old tint, 256 = fully new tint
#define DN_WEIGHT_MAX  256

#endif // GUARD_CONSTANTS_DAY_NIGHT_H
