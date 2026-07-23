/* 
* MedicalSystem_applyDoctoring
*/



#pragma once
#include "ConfigHookExtension.h"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#define ADD_LOGIC_BEFORE_AD(__NAME_EFFECT__, __FUNCT__, __NAME_COLOR__, __CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, __SELF__, __SKILL__, __EQUIPMENT__, __FRAME_TIME__, __WHO__) \
if(HookExtension::fastRandom100() <= __CHANCE__ && HookExtension::compareStringForEffect(__NAME_EFFECT__, __NAME_COLOR__)) \
{ \
    KR_DEBUG_LOG_L9("TRIGGER: " + __AUTO_ITEM__->getName() + " NAME: " + __NAME_EFFECT__)\
    KR_DEBUG_LOG_L9("SELF CHARACTER:" + (__SELF__).myRace->data->name + " OTHER CHARACTER: " + (__WHO__).myRace->data->name)\
    KR_LOGD_CHECKPOINT;\
    __FUNCT__(__AUTO_MODIFICATOR__, __AUTO_ITEM__, __SELF__, __SKILL__, __EQUIPMENT__, __FRAME_TIME__, __WHO__); \
    KR_LOGD_CHECKPOINT;\
    continue; \
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#define MAIN_MACROS_LOGIC_BEFORE_APLY__DOCTORING(__NAME_COLOR__, __CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, __SELF__, __SKILL__, __EQUIPMENT__, __FRAME_TIME__, __WHO__) \
    ADD_LOGIC_BEFORE_AD("#DivineHealing", divineHealing, __NAME_COLOR__, __CHANCE__, __AUTO_MODIFICATOR__,__AUTO_ITEM__, __SELF__, __SKILL__, __EQUIPMENT__, __FRAME_TIME__, __WHO__) \
    ADD_LOGIC_BEFORE_AD("#SoulDeadMedic", soulDeadMedic, __NAME_COLOR__, __CHANCE__, __AUTO_MODIFICATOR__,__AUTO_ITEM__, __SELF__, __SKILL__, __EQUIPMENT__, __FRAME_TIME__, __WHO__) \
    ADD_LOGIC_BEFORE_AD("#BloodTransfusion", bloodTransfusion, __NAME_COLOR__, __CHANCE__, __AUTO_MODIFICATOR__,__AUTO_ITEM__, __SELF__, __SKILL__, __EQUIPMENT__, __FRAME_TIME__, __WHO__) \
    ADD_LOGIC_BEFORE_AD("#Bloodsucker", bloodsucker, __NAME_COLOR__, __CHANCE__, __AUTO_MODIFICATOR__,__AUTO_ITEM__, __SELF__, __SKILL__, __EQUIPMENT__, __FRAME_TIME__, __WHO__) \
    ADD_LOGIC_BEFORE_AD("#Nanites", Nanites, __NAME_COLOR__, __CHANCE__, __AUTO_MODIFICATOR__,__AUTO_ITEM__, __SELF__, __SKILL__, __EQUIPMENT__, __FRAME_TIME__, __WHO__) \


//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// когда лечите, шанс излечить полностью пациента
inline void divineHealing(const float modificatorEffect, Item * itemThatCaused, Character& wounded, float& skill, Item& equipment, float& frameTIME, Character& whoDoctoring)
{
    if (SuppKR::fastRandom(10000000) <= 100.f * modificatorEffect) // масштабирование шанса, иначе за 100 вызовов он почти гарантированно срабатывает что уже не составляет стандартный процент
    {
        wounded.healCompletely();
    }
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// бафф медика
inline void soulDeadMedic(const float modificatorEffect, Item* itemThatCaused, Character& wounded, float& skill, Item& equipment, float& frameTIME, Character& whoDoctoring)
{
    skill = 100.f * modificatorEffect + skill;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

inline void bloodTransfusion(const float modificatorEffect, Item* itemThatCaused, Character& wounded, float& skill, Item& equipment, float& frameTIME, Character& whoDoctoring)
{
    auto& an1 = whoDoctoring.medical.anatomy;
    for (uint32_t i = 0; i < an1.size(); i++)
    {
        an1[i]->flesh -= 0.01f;
    }
    auto& an2 = wounded.medical.anatomy;
    for (uint32_t i = 0; i < an2.size(); i++)
    {
        auto& fl = an2[i]->flesh;
        auto& flS = an2[i]->fleshStun;

        if (fl < an2[i]->_maxHealth)
        {
            fl += (115.f * modificatorEffect) / 1000.f;
        }
        if (flS > 0.f)
        {
            flS -= (115.f * modificatorEffect) / 1000.f;
        }
    }
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

inline void bloodsucker(const float modificatorEffect, Item* itemThatCaused, Character& wounded, float& skill, Item& equipment, float& frameTIME, Character& whoDoctoring)
{
    auto& an1 = whoDoctoring.medical.anatomy;
    for (uint32_t i = 0; i < an1.size(); i++)
    {
        an1[i]->flesh += (100.f * modificatorEffect) / 10000.f;
        an1[i]->fleshStun -= (100.f * modificatorEffect) / 10000.f;
    }
    auto& an2 = wounded.medical.anatomy;
    for (uint32_t i = 0; i < an2.size(); i++)
    {
        an2[i]->flesh -= 0.07f;
    }
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

inline void Nanites(const float modificatorEffect, Item* itemThatCaused, Character& wounded, float& skill, Item& equipment, float& frameTIME, Character& whoDoctoring)
{
    auto& an2 = wounded.medical.anatomy;
    for (uint32_t i = 0; i < an2.size(); i++)
    {
        auto& limb = an2[i];
        if (limb->isRobotic() && limb->wearDamage > 0.f)
        {
            limb->wearDamage -= 0.01f + (130.f * modificatorEffect) / 10000.f;
        }
    }
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------