#ifndef GUARD_BATTLE_AI_FIELD_STATUSES_H
#define GUARD_BATTLE_AI_FIELD_STATUSES_H

// RHH source: pokeemerald-expansion/include/battle_ai_field_statuses.h

#include "battle_ai_main.h"
#include "battle_ai_util.h"

// RHH: enum FieldEffectOutcome (pokeemerald-expansion/include/battle_ai_field_statuses.h)
enum FieldEffectOutcome
{
    FIELD_EFFECT_POSITIVE,
    FIELD_EFFECT_NEUTRAL,
    FIELD_EFFECT_NEGATIVE,
    FIELD_EFFECT_BLOCKED,
};

bool32 WeatherChecker(u8 battler, u32 weather, enum FieldEffectOutcome desiredResult);
bool32 FieldStatusChecker(u8 battler, u32 fieldStatus, enum FieldEffectOutcome desiredResult);
s32 CalcWeatherScore(u8 battlerAtk, u8 battlerDef, u16 move, struct AiLogicData *aiData);

#endif // GUARD_BATTLE_AI_FIELD_STATUSES_H
