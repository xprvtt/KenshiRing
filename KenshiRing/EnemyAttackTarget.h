
/* 
* Character_attackTarget - off
*/

#pragma once
#include "ConfigHookExtension.h"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#define ADD_LOGIC_BEFORE_A_TAR(__NAME_EFFECT__, __FUNCT__, __NAME_COLOR__, __CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, __SELF__, __ME__) \
if(HookExtension::fastRandom100() <= __CHANCE__ && HookExtension::compareStringForEffect(__NAME_EFFECT__, __NAME_COLOR__)) \
{ \
    __FUNCT__(__AUTO_MODIFICATOR__,__AUTO_ITEM__, __SELF__, __ME__); \
    continue; \
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#define MAIN_MACROS_BEFORE_ATTACK_TARGET(__NAME_COLOR__, __CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, __SELF__, __ME__) \
    ADD_LOGIC_BEFORE_A_TAR("#DeathGaze", DeathGaze, __NAME_COLOR__, __CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, __SELF__, __ME__) \

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

inline void DeathGaze(const float modificatorEffect, Item * itemThatCaused, Character& attacker, Character& me)
{
    auto& anatomy = attacker.medical.anatomy;
    for (uint32_t i = 0; i < anatomy.size(); i++)
    {
        anatomy[i]->flesh -= 1.f * modificatorEffect;
    }
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
