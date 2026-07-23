/*
* MedicalSystem_applyDoctoring
*/

#pragma once
#include "ConfigHookExtension.h"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#define ADD_LOGIC_BEFORE_RECIEVED_AD(__NAME_EFFECT__, __FUNCT__, __NAME_COLOR__, __CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, __SELF__, __SKILL__, __EQUIPMENT__, __FRAME_TIME__, __WHO__) \
if(HookExtension::fastRandom100() <= __CHANCE__ && HookExtension::compareStringForEffect(__NAME_EFFECT__, __NAME_COLOR__)) \
{ \
    KR_DEBUG_LOG_L9("TRIGGER: " + __AUTO_ITEM__->getName() + " NAME: " + __NAME_EFFECT__)\
    KR_DEBUG_LOG_L9("SELF CHARACTER:" + (__SELF__).myRace->data->name + " OTHER CHARACTER: " + (__WHO__).myRace->data->name)\
    KR_LOGD_CHECKPOINT;\
    __FUNCT__(__AUTO_MODIFICATOR__,__AUTO_ITEM__,  __SELF__, __SKILL__, __EQUIPMENT__, __FRAME_TIME__, __WHO__); \
    KR_LOGD_CHECKPOINT;\
    continue; \
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#define MAIN_MACROS_LOGIC_BEFORE_RECIEVED_APLY_DOCTORING(__NAME_COLOR__, __CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, __SELF__, __SKILL__, __EQUIPMENT__, __FRAME_TIME__, __WHO__) \
    ADD_LOGIC_BEFORE_RECIEVED_AD("#CompliantPatient", compliantPatient, __NAME_COLOR__, __CHANCE__, __AUTO_MODIFICATOR__,__AUTO_ITEM__, __SELF__, __SKILL__, __EQUIPMENT__, __FRAME_TIME__, __WHO__) \
    ADD_LOGIC_BEFORE_RECIEVED_AD("#ViolentPatient", ViolentPatient, __NAME_COLOR__, __CHANCE__, __AUTO_MODIFICATOR__,__AUTO_ITEM__, __SELF__, __SKILL__, __EQUIPMENT__, __FRAME_TIME__, __WHO__) \


//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// когда вас лечат шанс излечиться полностью
inline void compliantPatient(const float modificatorEffect, Item * itemThatCaused, Character& wounded, float& skill, Item& equipment, float& frameTIME, Character& whoDoctoring)
{
    if (SuppKR::fastRandom(10000000) <= 100.f * modificatorEffect) // масштабирование шанса, иначе за 100 вызовов он почти гарантированно срабатывает что уже не составляет стандартный процент
    {
        wounded.healCompletely();
    }
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

inline void ViolentPatient(const float modificatorEffect, Item* itemThatCaused, Character& wounded, float& skill, Item& equipment, float& frameTIME, Character& whoDoctoring)
{
    auto& an1 = wounded.medical.anatomy;
    for (uint32_t i = 0; i < an1.size(); i++)
    {
        an1[i]->flesh += (100.f * modificatorEffect) / 10000.f;
        an1[i]->fleshStun -= (100.f * modificatorEffect) / 10000.f;
    }
    auto& an2 = whoDoctoring.medical.anatomy;
    for (uint32_t i = 0; i < an2.size(); i++)
    {
        an2[i]->flesh -= 0.07f;
    }
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
