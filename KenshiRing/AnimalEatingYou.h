
/*
* Character_NV_gettingEaten
*/

#pragma once
#include "ConfigHookExtension.h"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#define ADD_LOGIC_BEFORE_GETTING_EATEN(__NAME_EFFECT__, __FUNCT__, __NAME_COLOR__, __CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, __SELF__, __DAMAGE__, __WHO__) \
if(HookExtension::fastRandom100() <= __CHANCE__ && HookExtension::compareStringForEffect(__NAME_EFFECT__, __NAME_COLOR__)) \
{ \
    __FUNCT__(__AUTO_MODIFICATOR__,__AUTO_ITEM__, __SELF__, __DAMAGE__, __WHO__); \
    continue; \
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#define MAIN_MACROS_BEFORE_GETTING_EATEN(__NAME_COLOR__, __CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, __SELF__, __DAMAGE__, __WHO__) \
    ADD_LOGIC_BEFORE_GETTING_EATEN("#Poisonous", poisonous,       __NAME_COLOR__, __CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, __SELF__, __DAMAGE__, __WHO__) \
    ADD_LOGIC_BEFORE_GETTING_EATEN("#Paralysis", paralysis,       __NAME_COLOR__, __CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, __SELF__, __DAMAGE__, __WHO__) \
    ADD_LOGIC_BEFORE_GETTING_EATEN("#IronSkin", ironSkin,         __NAME_COLOR__, __CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, __SELF__, __DAMAGE__, __WHO__) \
    ADD_LOGIC_BEFORE_GETTING_EATEN("#BeastRevival", BeastRevival, __NAME_COLOR__, __CHANCE__, __AUTO_MODIFICATOR__,__AUTO_ITEM__,  __SELF__, __DAMAGE__, __WHO__) \

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// отражение урона
inline void poisonous(const float modificatorEffect, Item * itemThatCaused, Character& me, float& amount, Character& devouring)
{
    auto& an1 = devouring.medical.anatomy;
    for (uint32_t i = 0; i < an1.size(); i++)
    {
        an1[i]->fleshStun += (10.f * modificatorEffect) / 100.f;
    }
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// паралич
inline void paralysis(const float modificatorEffect, Item* itemThatCaused, Character& me, float& amount, Character& devouring)
{
    devouring.medical.nextKOTime = 1000.f * modificatorEffect;
    devouring.medical.startKnockoutTimer();
    amount *= 10.f;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

inline void ironSkin(const float modificatorEffect, Item* itemThatCaused, Character& me, float& amount, Character& devouring)
{
    amount *= (1.0f - std::max(modificatorEffect, 1.f));
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// паралич
inline void BeastRevival(const float modificatorEffect, Item* itemThatCaused, Character& me, float& amount, Character& devouring)
{
    auto& an1 = me.medical.anatomy;
    if (an1.size() && an1[0]->fatal)
    {
        for (uint32_t i = 0; i < an1.size(); i++)
        {
            an1[i]->applyDamage(Damages(100.f, 100.f, 100.f, 100.f, 100.f));
        }
        devouring.separateIntoMyOwnSquad(true);
        devouring.setFaction(me.getFaction(), me.getPlatoon());

        const auto& sect = me.inventory->getSection(itemThatCaused->inventorySection);
        sect->removeItem(itemThatCaused);
    }
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
