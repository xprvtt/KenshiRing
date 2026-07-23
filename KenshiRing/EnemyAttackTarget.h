
/* 
* Character_attackTarget - off
*/

#pragma once
#include "ConfigHookExtension.h"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#define ADD_LOGIC_BEFORE_A_TAR(__NAME_EFFECT__, __FUNCT__, __NAME_COLOR__, __CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, __SELF__, __ME__) \
if(HookExtension::fastRandom100() <= __CHANCE__ && HookExtension::compareStringForEffect(__NAME_EFFECT__, __NAME_COLOR__)) \
{ \
    KR_DEBUG_LOG_L9("TRIGGER: " + __AUTO_ITEM__->getName() + " NAME: " + __NAME_EFFECT__)\
    KR_DEBUG_LOG_L9("SELF CHARACTER:" + (__SELF__).myRace->data->name + " OTHER CHARACTER: " + (__ME__).myRace->data->name)\
    KR_LOGD_CHECKPOINT;\
    __FUNCT__(__AUTO_MODIFICATOR__,__AUTO_ITEM__, __SELF__, __ME__); \
    KR_LOGD_CHECKPOINT;\
    continue; \
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#define MAIN_MACROS_BEFORE_ATTACK_TARGET(__NAME_COLOR__, __CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, __SELF__, __ME__) \
    ADD_LOGIC_BEFORE_A_TAR("#DeathGaze", DeathGaze, __NAME_COLOR__, __CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, __SELF__, __ME__) \

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

inline void DeathGaze(const float modificatorEffect, Item * itemThatCaused, Character& attacker, Character& me)
{
    const auto& anatomy = attacker.medical.anatomy;
    for (uint32_t i = 0; i < anatomy.size(); ++i)
    {
        anatomy[i]->flesh -= 1.f * modificatorEffect;
    }
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
