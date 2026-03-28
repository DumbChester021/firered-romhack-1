#ifndef GUARD_CONSTANTS_BATTLE_AI_H
#define GUARD_CONSTANTS_BATTLE_AI_H

// battlers
#define AI_TARGET 0
#define AI_USER 1
#define AI_TARGET_PARTNER 2
#define AI_USER_PARTNER 3

// get_type command
#define AI_TYPE1_TARGET 0
#define AI_TYPE1_USER 1
#define AI_TYPE2_TARGET 2
#define AI_TYPE2_USER 3
#define AI_TYPE_MOVE 4

// type effectiveness multipliers moved to battle_ai_util.h

// ai weather
#define AI_WEATHER_SUN       0
#define AI_WEATHER_RAIN      1
#define AI_WEATHER_SANDSTORM 2
#define AI_WEATHER_HAIL      3

// get_how_powerful_move_is
#define MOVE_POWER_DISCOURAGED  0
#define MOVE_NOT_MOST_POWERFUL  1
#define MOVE_MOST_POWERFUL      2

// script's table id to bit (legacy FRLG names — converging to AI_FLAG_* from RHH)
#define AI_SCRIPT_CHECK_BAD_MOVE (1 << 0)
#define AI_SCRIPT_CHECK_VIABILITY (1 << 1)
#define AI_SCRIPT_TRY_TO_FAINT (1 << 2)
#define AI_SCRIPT_SETUP_FIRST_TURN (1 << 3)
#define AI_SCRIPT_RISKY (1 << 4)
#define AI_SCRIPT_PREFER_STRONGEST_MOVE (1 << 5)
#define AI_SCRIPT_PREFER_BATON_PASS (1 << 6)
#define AI_SCRIPT_DOUBLE_BATTLE (1 << 7)
#define AI_SCRIPT_HP_AWARE (1 << 8)
#define AI_SCRIPT_SMART_SWITCHING (1 << 9)  // Voluntary mid-battle switch evaluation
// 10 - 28 are not used
#define AI_SCRIPT_ROAMING (1 << 29)
#define AI_SCRIPT_SAFARI (1 << 30)
#define AI_SCRIPT_FIRST_BATTLE (1 << 31)

// RHH: AI_FLAG_* constants (pokeemerald-expansion/include/constants/battle_ai.h)
// RHH uses u64 AI_FLAG(x) = (u64)1 << x; we use u32 since aiFlags is u32.
// Bits 0-19 match AI_SCRIPT_* values above. New flags use bits that fit in u32.
// TODO: Rename all AI_SCRIPT_* usages to AI_FLAG_* to fully converge with RHH.
#define AI_FLAG_CHECK_BAD_MOVE          (1 << 0)
#define AI_FLAG_TRY_TO_FAINT            (1 << 1)
#define AI_FLAG_CHECK_VIABILITY         (1 << 2)
#define AI_FLAG_FORCE_SETUP_FIRST_TURN  (1 << 3)
#define AI_FLAG_RISKY                   (1 << 4)
#define AI_FLAG_TRY_TO_2HKO             (1 << 5)
#define AI_FLAG_PREFER_BATON_PASS       (1 << 6)
#define AI_FLAG_DOUBLE_BATTLE           (1 << 7)
#define AI_FLAG_HP_AWARE                (1 << 8)
#define AI_FLAG_POWERFUL_STATUS         (1 << 9)
#define AI_FLAG_NEGATE_UNAWARE          (1 << 10)
#define AI_FLAG_WILL_SUICIDE            (1 << 11)
#define AI_FLAG_PREFER_STATUS_MOVES     (1 << 12)
#define AI_FLAG_STALL                   (1 << 13)
#define AI_FLAG_SMART_SWITCHING         (1 << 14)
#define AI_FLAG_ACE_POKEMON             (1 << 15)
#define AI_FLAG_OMNISCIENT              (1 << 16)
#define AI_FLAG_SMART_MON_CHOICES       (1 << 17)
#define AI_FLAG_CONSERVATIVE            (1 << 18)
#define AI_FLAG_SEQUENCE_SWITCHING      (1 << 19)
// Bits 20-28 are RHH Gen 8+ flags — add when needed
#define AI_FLAG_PREDICT_SWITCH          (1 << 23)
#define AI_FLAG_PREDICT_MOVE            (1 << 26)

#endif // GUARD_CONSTANTS_BATTLE_AI_H
