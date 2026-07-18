
/*
* MedicalSystem_applyRigging - off
*/


#pragma once
#include "ConfigHookExtension.h"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#define ADD_LOGIC_BEFORE_AR(__NAME_EFFECT__, __FUNCT__, __NAME_COLOR__, __CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, __SELF__, __SKILL__, __EQUIPMENT__, __FRAME_TIME__) \
if(HookExtension::fastRandom100() <= __CHANCE__ && HookExtension::compareStringForEffect(__NAME_EFFECT__, __NAME_COLOR__)) \
{ \
    KR_DEBUG_LOG_L9("TRIGGER: " + __AUTO_ITEM__->getName() + " NAME: " + __NAME_EFFECT__)\
    KR_LOG_CHECKPOINT;\
    __FUNCT__(__AUTO_MODIFICATOR__,__AUTO_ITEM__,  __SELF__, __SKILL__, __EQUIPMENT__, __FRAME_TIME__); \
    KR_LOG_CHECKPOINT;\
    continue; \
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#define MAIN_MACROS_LOGIC_BEFORE_APLY_RIGGING(__NAME_COLOR__, __CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, __SELF__, __SKILL__, __EQUIPMENT__, __FRAME_TIME__) \
    ADD_LOGIC_BEFORE_AR("#DivineRigging", divineRigging, __NAME_COLOR__, __CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, __SELF__, __SKILL__, __EQUIPMENT__, __FRAME_TIME__) \

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// убрать износ
inline void divineRigging(const float modificatorEffect, Item * itemThatCaused, Character& wounded, float& skill, Item& equipment, float& frameTIME)
{
    auto& an = wounded.medical.anatomy;

    for (uint32_t i = 0; i < an.size(); i++)
    {
        auto& limb = an[i];
        if (limb->isRobotic())
        {
            KR_RELEASE_LOG(SuppKR::toStringV100(limb->wearDamage));
            KR_RELEASE_LOG(SuppKR::toStringV100(limb->juryRigging));
        }
    }
    
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
