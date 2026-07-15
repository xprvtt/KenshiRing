
/* 
* Character_NV_hitByMeleeAttack
*/

#pragma once
#include "ConfigHookExtension.h"


//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#define ADD_LOGIC_BEFORE_ATTACKING_NVBMA(__NAME_EFFECT__, __FUNCT__, __NAME_COLOR__, __CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, __SELF__, __DIR__, __DAMAGE__, __VICTIM__, __COMBAT_TECH__, __COMBO_ID__) \
if(HookExtension::fastRandom100() <= __CHANCE__ && HookExtension::compareStringForEffect(__NAME_EFFECT__, __NAME_COLOR__)) \
{ \
    __FUNCT__(__AUTO_MODIFICATOR__,__AUTO_ITEM__, __SELF__, __DIR__, __DAMAGE__, __VICTIM__, __COMBAT_TECH__, __COMBO_ID__); \
    continue; \
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#define MAIN_MACROS_BEFORE_ATTACING_NV_HIT_BY_MELEE_ATTACK(__NAME_COLOR__, __CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, __SELF__, __DIR__, __DAMAGE__, __VICTIM__, __COMBAT_TECH__, __COMBO_ID__) \
    ADD_LOGIC_BEFORE_ATTACKING_NVBMA("#Vampir", vampir, __NAME_COLOR__, __CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, __SELF__, __DIR__, __DAMAGE__, __VICTIM__, __COMBAT_TECH__, __COMBO_ID__) \
    ADD_LOGIC_BEFORE_ATTACKING_NVBMA("#AbsolutePenetration", absolutePenetration, __NAME_COLOR__, __CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, __SELF__, __DIR__, __DAMAGE__, __VICTIM__, __COMBAT_TECH__, __COMBO_ID__)\
    ADD_LOGIC_BEFORE_ATTACKING_NVBMA("#DivineStrike", divineStrike, __NAME_COLOR__, __CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, __SELF__, __DIR__, __DAMAGE__, __VICTIM__, __COMBAT_TECH__, __COMBO_ID__)\
    ADD_LOGIC_BEFORE_ATTACKING_NVBMA("#AreaDamage", areaDamage, __NAME_COLOR__, __CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, __SELF__, __DIR__, __DAMAGE__, __VICTIM__, __COMBAT_TECH__, __COMBO_ID__)\
    ADD_LOGIC_BEFORE_ATTACKING_NVBMA("#Disarmament", disarmament, __NAME_COLOR__, __CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, __SELF__, __DIR__, __DAMAGE__, __VICTIM__, __COMBAT_TECH__, __COMBO_ID__)\
    ADD_LOGIC_BEFORE_ATTACKING_NVBMA("#ArmorStrip", ArmorStrip, __NAME_COLOR__, __CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, __SELF__, __DIR__, __DAMAGE__, __VICTIM__, __COMBAT_TECH__, __COMBO_ID__)\
    ADD_LOGIC_BEFORE_ATTACKING_NVBMA("#Amputator", Amputator,   __NAME_COLOR__, __CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, __SELF__, __DIR__, __DAMAGE__, __VICTIM__, __COMBAT_TECH__, __COMBO_ID__)\
    ADD_LOGIC_BEFORE_ATTACKING_NVBMA("#LimbRipper", LimbRipper, __NAME_COLOR__, __CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, __SELF__, __DIR__, __DAMAGE__, __VICTIM__, __COMBAT_TECH__, __COMBO_ID__)\

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// атаки восстанавливают хп
inline void vampir(const float modificatorEffect, Item * itemThatCaused, Character& me, CutDirection& dir, Damages& damage, Character& victim, CombatTechniqueData& attackTech, int& comboID)
{
    auto& anatomy = me.medical.anatomy;

    MedicalSystem::HealthPartStatus* selected = nullptr;
    uint32_t count = 0;

    for (uint32_t i = 0; i < anatomy.size(); i++)
    {
        auto* limb = anatomy[i];
        if (limb->fleshStun > 0 || selected->flesh < selected->_maxHealth)
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
    auto& anatomy = victim.medical.anatomy;
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
    int level = std::min(5, static_cast<int>(modificatorEffect * 100.0f) / 50 + 1);

    auto& allSec = victim.inventory->sections;
    for (auto i = allSec.begin(); i != allSec.end(); i++)
    {
        if (i->second->limitedSlot == AttachSlot::ATTACH_WEAPON)
        {
            auto& items = i->second->items;
            for (size_t it = 0; it < items.size(); it++)
            {
                InventorySection::SectionItem& item = items[it];
                victim.inventory->dropItem(item.item);
            }
            level--;
            if (!level)
            {
                return;
            }
        }
    }
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


// снять 1 броню
inline void ArmorStrip(const float modificatorEffect, Item* itemThatCaused, Character& me, CutDirection& dir, Damages& damage, Character& victim, CombatTechniqueData& attackTech, int& comboID)
{
    int count = static_cast<int>(modificatorEffect * 2.0f) + 1;
    if (count > 5)
    {
        count = 5;
    }
    for (size_t i = 0; i < count; i++)
    {
        lektor<Item*> allIt;
        victim.inventory->getEquippedArmour(allIt);
        if (allIt.size() == 0)
        {
            break;
        }
        Item* item = allIt[SuppKR::fastRandom(allIt.size() - 1)];
        victim.inventory->dropItem(item);
    }
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

inline void LimbRipper(const float modificatorEffect, Item* itemThatCaused, Character& me, CutDirection& dir, Damages& damage, Character& victim, CombatTechniqueData& attackTech, int& comboID)
{
    victim.medical.amputate(HookExtension::amputateList[SuppKR::fastRandom(HookExtension::sizeAmputateList)], true, Ogre::Vector3(1.f, 1.f, 1.f));
    if (modificatorEffect >= 1.f)
    {
        victim.medical.amputate(HookExtension::amputateList[SuppKR::fastRandom(HookExtension::sizeAmputateList)], true, Ogre::Vector3(1.f, 1.f, 1.f));
        if (modificatorEffect >= 1.5f)
        {
            victim.medical.amputate(HookExtension::amputateList[SuppKR::fastRandom(HookExtension::sizeAmputateList)], true, Ogre::Vector3(1.f, 1.f, 1.f));
            if (modificatorEffect >= 2.f)
            {
                victim.medical.amputate(HookExtension::amputateList[SuppKR::fastRandom(HookExtension::sizeAmputateList)], true, Ogre::Vector3(1.f, 1.f, 1.f));
            }
        }
    }
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

inline void Amputator(const float modificatorEffect, Item* itemThatCaused, Character& me, CutDirection& dir, Damages& damage, Character& victim, CombatTechniqueData& attackTech, int& comboID)
{
    victim.medical.amputate(RobotLimbs::Limb::LEFT_ARM, true, Ogre::Vector3(1.f, 1.f, 1.f));
    victim.medical.amputate(RobotLimbs::Limb::LEFT_LEG, true, Ogre::Vector3(1.f, 1.f, 1.f));
    victim.medical.amputate(RobotLimbs::Limb::RIGHT_ARM, true, Ogre::Vector3(1.f, 1.f, 1.f));
    victim.medical.amputate(RobotLimbs::Limb::RIGHT_LEG, true, Ogre::Vector3(1.f, 1.f, 1.f));
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


