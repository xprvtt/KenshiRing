
/* 
* Character_NV_hitByMeleeAttack
*/

#pragma once
#include "ConfigHookExtension.h"


//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#define ADD_LOGIC_BEFORE_ATTACKING_NVBMA(__NAME_EFFECT__, __FUNCT__, __NAME_COLOR__, __CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, __SELF__, __DIR__, __DAMAGE__, __VICTIM__, __COMBAT_TECH__, __COMBO_ID__) \
if(HookExtension::fastRandom100() <= __CHANCE__ && HookExtension::compareStringForEffect(__NAME_EFFECT__, __NAME_COLOR__)) \
{ \
    KR_DEBUG_LOG_L9("TRIGGER: " + __AUTO_ITEM__->getName() + " NAME: " + __NAME_EFFECT__)\
    KR_DEBUG_LOG_L9("SELF CHARACTER:" + (__SELF__).myRace->data->name + " OTHER CHARACTER: " + (__VICTIM__).myRace->data->name)\
    KR_LOGD_CHECKPOINT;\
    __FUNCT__(__AUTO_MODIFICATOR__,__AUTO_ITEM__, __SELF__, __DIR__, __DAMAGE__, __VICTIM__, __COMBAT_TECH__, __COMBO_ID__); \
    KR_LOGD_CHECKPOINT;\
    continue; \
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#define MAIN_MACROS_BEFORE_ATTACING_NV_HIT_BY_MELEE_ATTACK(__NAME_COLOR__, __CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, __SELF__, __DIR__, __DAMAGE__, __VICTIM__, __COMBAT_TECH__, __COMBO_ID__) \
    ADD_LOGIC_BEFORE_ATTACKING_NVBMA("#Vampir", vampir,             __NAME_COLOR__, __CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, __SELF__, __DIR__, __DAMAGE__, __VICTIM__, __COMBAT_TECH__, __COMBO_ID__) \
    ADD_LOGIC_BEFORE_ATTACKING_NVBMA("#AbsolutePenetration", absolutePenetration, __NAME_COLOR__, __CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, __SELF__, __DIR__, __DAMAGE__, __VICTIM__, __COMBAT_TECH__, __COMBO_ID__)\
    ADD_LOGIC_BEFORE_ATTACKING_NVBMA("#DivineStrike", divineStrike, __NAME_COLOR__, __CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, __SELF__, __DIR__, __DAMAGE__, __VICTIM__, __COMBAT_TECH__, __COMBO_ID__)\
    ADD_LOGIC_BEFORE_ATTACKING_NVBMA("#AreaDamage", areaDamage,     __NAME_COLOR__, __CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, __SELF__, __DIR__, __DAMAGE__, __VICTIM__, __COMBAT_TECH__, __COMBO_ID__)\
    ADD_LOGIC_BEFORE_ATTACKING_NVBMA("#Disarmament", disarmament,   __NAME_COLOR__, __CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, __SELF__, __DIR__, __DAMAGE__, __VICTIM__, __COMBAT_TECH__, __COMBO_ID__)\
    ADD_LOGIC_BEFORE_ATTACKING_NVBMA("#ArmorStrip", ArmorStrip,     __NAME_COLOR__, __CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, __SELF__, __DIR__, __DAMAGE__, __VICTIM__, __COMBAT_TECH__, __COMBO_ID__)\
    ADD_LOGIC_BEFORE_ATTACKING_NVBMA("#Amputator", Amputator,       __NAME_COLOR__, __CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, __SELF__, __DIR__, __DAMAGE__, __VICTIM__, __COMBAT_TECH__, __COMBO_ID__)\
    ADD_LOGIC_BEFORE_ATTACKING_NVBMA("#LimbRipper", LimbRipper,     __NAME_COLOR__, __CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, __SELF__, __DIR__, __DAMAGE__, __VICTIM__, __COMBAT_TECH__, __COMBO_ID__)\
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// атаки восстанавливают хп
inline void vampir(const float modificatorEffect, Item * itemThatCaused, Character& me, CutDirection& dir, Damages& damage, Character& victim, CombatTechniqueData& attackTech, int& comboID)
{
    const auto& anatomy = me.medical.anatomy;

    MedicalSystem::HealthPartStatus* selected = nullptr;
    uint32_t count = 0;

    for (uint32_t i = 0; i < anatomy.count; i++)
    {
        auto limb = anatomy[i];
        if (limb->fleshStun > 0 || limb->flesh < limb->_maxHealth)
        {
            if (SuppKR::fastRandom(++count - 1) == 0)
            {
                selected = limb;
            }
        }
    }
    if (selected)
    {
        selected->flesh += ((damage.blunt + damage.cut + damage.pierce) / 5.f) * modificatorEffect;
        if (selected->flesh > selected->_maxHealth)
        {
            selected->flesh = selected->_maxHealth;
        }
        selected->fleshStun -= ((damage.blunt + damage.cut + damage.pierce) / 5.f) * modificatorEffect;
    }
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// абсолютное пробитие
inline void absolutePenetration(const float modificatorEffect, Item* itemThatCaused, Character& me, CutDirection& dir, Damages& damage, Character& victim, CombatTechniqueData& attackTech, int& comboID)
{
    damage.armourPenetration += modificatorEffect;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// урон по телу
inline void divineStrike(const float modificatorEffect, Item* itemThatCaused, Character& me, CutDirection& dir, Damages& damage, Character& victim, CombatTechniqueData& attackTech, int& comboID)
{
    const auto& anatomy = victim.medical.anatomy;
    for (uint32_t i = 0; i < anatomy.size(); i++)
    {
        anatomy[i]->fleshStun += anatomy[i]->_maxHealth * modificatorEffect;
    }
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// атака оружием по всему телу
inline void areaDamage(const float modificatorEffect, Item* itemThatCaused, Character& me, CutDirection& dir, Damages& damage, Character& victim, CombatTechniqueData& attackTech, int& comboID)
{
    damage.armourPenetration *= modificatorEffect;
    damage.extraStun *= modificatorEffect;
    damage.bleedMult *= modificatorEffect;
    damage.pierce *= modificatorEffect;
    damage.blunt *= modificatorEffect;
    damage.cut *= modificatorEffect;

    auto& anatomy = victim.medical.anatomy;
    for (uint32_t i = 0; i < anatomy.size(); i++)
    {
        anatomy[i]->applyDamage(damage);
    }

    damage.armourPenetration = 0.f;
    damage.bleedMult = 0.f;
    damage.extraStun = 0.f;
    damage.pierce = 0.f;
    damage.blunt = 0.f;
    damage.cut = 0.f;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// обезоружить
inline void disarmament(const float modificatorEffect, Item* itemThatCaused, Character& me, CutDirection& dir, Damages& damage, Character& victim, CombatTechniqueData& attackTech, int& comboID)
{
    int level = std::min(5, static_cast<int>(modificatorEffect * 100.f / 50.f) + 1);

    lektor<InventorySection*> allSec;
    victim.inventory->getAllSectionsOfType(allSec, AttachSlot::ATTACH_WEAPON);
    const auto size = allSec.size();

    for (uint32_t itSec = 0; itSec < size; itSec++)
    {
        auto& items = allSec[itSec]->items;
        const auto countItems = items.size();

        for (size_t itItem = 0; itItem < countItems; itItem++)
        {
            victim.inventory->dropItem(items[itItem].item);
        }
        if (!--level)
        {
            return;
        }
    }
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


// снять 1 броню
inline void ArmorStrip(const float modificatorEffect, Item* itemThatCaused, Character& me, CutDirection& dir, Damages& damage, Character& victim, CombatTechniqueData& attackTech, int& comboID)
{
    int countStrip = std::min(static_cast<int>(modificatorEffect * 2.0f) + 1, 5);
    lektor<Item*> allItem;
    for (size_t i = 0; i < countStrip; i++)
    {
        victim.inventory->getEquippedArmour(allItem);
        if (allItem.size() == 0)
        {
            break;
        }
        Item* item = allItem[SuppKR::fastRandom(allItem.size() - 1)];
        victim.inventory->dropItem(item);
        allItem.clear();
    }
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

inline void LimbRipper(const float modificatorEffect, Item* itemThatCaused, Character& me, CutDirection& dir, Damages& damage, Character& victim, CombatTechniqueData& attackTech, int& comboID)
{
    const Ogre::Vector3 force(1.f, 1.f, 1.f);
    victim.medical.amputate(HookExtension::amputateList[SuppKR::fastRandom(HookExtension::sizeAmputateList)], true, force);
    if (modificatorEffect >= 1.f)
    {
        victim.medical.amputate(HookExtension::amputateList[SuppKR::fastRandom(HookExtension::sizeAmputateList)], true, force);
        if (modificatorEffect >= 1.5f)
        {
            victim.medical.amputate(HookExtension::amputateList[SuppKR::fastRandom(HookExtension::sizeAmputateList)], true, force);
            if (modificatorEffect >= 2.f)
            {
                victim.medical.amputate(HookExtension::amputateList[SuppKR::fastRandom(HookExtension::sizeAmputateList)], true, force);
            }
        }
    }
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

inline void Amputator(const float modificatorEffect, Item* itemThatCaused, Character& me, CutDirection& dir, Damages& damage, Character& victim, CombatTechniqueData& attackTech, int& comboID)
{
    const Ogre::Vector3 force(1.f, 1.f, 1.f);
    victim.medical.amputate(RobotLimbs::Limb::LEFT_ARM, true,  force);
    victim.medical.amputate(RobotLimbs::Limb::LEFT_LEG, true,  force);
    victim.medical.amputate(RobotLimbs::Limb::RIGHT_ARM, true, force);
    victim.medical.amputate(RobotLimbs::Limb::RIGHT_LEG, true, force);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


