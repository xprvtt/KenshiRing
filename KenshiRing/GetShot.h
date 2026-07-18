
/*
* iShotYouHook
*/

#pragma once
#include "ConfigHookExtension.h"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#define ADD_LOGIC_GS(__NAME_EFFECT__, __FUNCT__, __NAME_COLOR__, __CHANCE__, __AUTO_MODIFICATOR__,__AUTO_ITEM__,  __SELF__, __ATTAKCER__, __HARPOON__, __ON_PURPOSE__, __HIT_TARGET__) \
if(HookExtension::fastRandom100() <= __CHANCE__ && HookExtension::compareStringForEffect(__NAME_EFFECT__, __NAME_COLOR__)) \
{ \
    KR_DEBUG_LOG_L9("TRIGGER: " + __AUTO_ITEM__->getName() + " NAME: " + __NAME_EFFECT__)\
    KR_DEBUG_LOG_L9("SELF CHARACTER:" + (__SELF__).myRace->data->name + " OTHER CHARACTER: " + (__ATTAKCER__).myRace->data->name)\
    KR_LOG_CHECKPOINT;\
    __FUNCT__(__AUTO_MODIFICATOR__,__AUTO_ITEM__,  __SELF__, __ATTAKCER__, __HARPOON__, __ON_PURPOSE__, __HIT_TARGET__); \
    KR_LOG_CHECKPOINT;\
    continue; \
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#define MAIN_MACROS_AFTER_GET_SHOT(__NAME_COLOR__, __CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, __SELF__, __ATTAKCER__, __HARPOON__, __ON_PURPOSE__, __HIT_TARGET__) \
    ADD_LOGIC_GS("#Bulletproof", Bulletproof, __NAME_COLOR__, __CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, __SELF__, __ATTAKCER__, __HARPOON__, __ON_PURPOSE__, __HIT_TARGET__) \

//may be useless
// __HARPOON__ - already used
// __ON_PURPOSE__ - already used
// __HIT_TARGET__ - result shot

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// fix? Harpoon
inline void Bulletproof(const float modificatorEffect, Item * itemThatCaused, Character& me, Character& attacker, Harpoon& poon, bool& onPurpose, const bool isHitTarget)
{
    if (isHitTarget)
    {
        auto& anatomy = me.medical.anatomy;
        for (uint32_t i = 0; i < anatomy.size(); i++)
        {
            anatomy[i]->fleshStun -= 20.f * modificatorEffect;
            anatomy[i]->flesh += anatomy[i]->_maxHealth * modificatorEffect;
        }
    }
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
