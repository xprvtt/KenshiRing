/*
* NAME
* Character.cpp - _NV_hitByMeleeAttack_hook 
* 
* DEFINE
* Character_NV_hitByMeleeAttack
* 
* How do I use it ?
* 
* 1. создайсте свою функцию с параметрами "inline void yourNameFunction(Character& victim, CutDirection& dir, Damages& damage, Character& attacking, CombatTechniqueData& attackTech, int& comboID)"
* 
* 2. измените входящие данные, которые вы выхотите
* 
* 3. придумайте название эффекту например "#yourNameEffect"
* 
* 4. добавьте свою функцию через макрос ADD_LOGIC_BEFORE_THIT_NVBMA("#yourNameEffect", yourNameFunction ..... ), в макрос MAIN_MACROS_BEFORE_NV_HIT_BY_MELEE_ATTACK
*    пример :
*
*    #define MAIN_MACROS_BEFORE_THIT_NV_HIT_BY_MELEE_ATTACK(__NAME_COLOR__, __CHANCE__, __SELF__, __DIR__, __DAMAGE__, __WHO__, __COMBAT_TECH__, __COMBO_ID__, __AUTO_MODIFICATOR__) \
*                ADD_LOGIC_BEFORE_THIT_NVBMA(....) \
*                ADD_LOGIC_BEFORE_THIT_NVBMA(....) \
*        here -> ADD_LOGIC_BEFORE_THIT_NVBMA("yourNameEffect", yourNameFunction, __NAME_COLOR__, __CHANCE__, __SELF__, __DIR__, __DAMAGE__, __WHO__, __COMBAT_TECH__, __COMBO_ID__, __AUTO_MODIFICATOR__) \
*                ADD_LOGIC_BEFORE_THIT_NVBMA(....) \
*                ADD_LOGIC_BEFORE_THIT_NVBMA(....) 
*       or here->ADD_LOGIC_BEFORE_THIT_NVBMA("yourNameEffect", yourNameFunction,  __NAME_COLOR__, __CHANCE__, __SELF__, __DIR__, __DAMAGE__, __WHO__, __COMBAT_TECH__, __COMBO_ID__, __AUTO_MODIFICATOR__) )
*     
* 5. учитывайте символ \ после ADD_LOGIC_BEFORE_THIT_NVBMA(), он определяет перенос строки это обеспечивает удобство
* 
* 6. в каждом макросе вы встетите параметр __AUTO_MODIFICATOR__ который передается как const int modificatorEffect это модификатор который вы можете использовать по своему усмотрению
*    например для усиления или остабления свого эффекта из FSC добавив несколько вариаций своего эффекта
* 
* 7. в каждом макросе вы так же встретите параметр __AUTO_ITEM__ который передается как Item* itemThatCaused это предмет ставший причиной вызова, который вы можете использовать по своему усмотрению
*    например для удаления после вызова.  __AUTO_ITEM__ != nullptr
* 
* 8. оптимизация. Eсли вы добавляете "часто вызываемую" функцию(effect) добавьте ее выше остальных, если же она реже всех то ниже
*    пример: "#yourNameEffect" наложен на огромное колличество предметов, для оптимизации использован if( foo(); continue;) подход вместо vector<pair<string, function>>
*    изходя из этого чем выше находится частоиспользуемая функция тем меньше затрат на прохождение цепочки if-if-if-if-if ....
*/

#pragma once
#include "ConfigHookExtension.h"


//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#define ADD_LOGIC_BEFORE_THIT_NVBMA(__NAME_EFFECT__, __FUNCT__, __NAME_COLOR__, __CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, __SELF__, __DIR__, __DAMAGE__, __WHO__, __COMBAT_TECH__, __COMBO_ID__) \
if(HookExtension::fastRandom100() <= __CHANCE__ && HookExtension::compareStringForEffect(__NAME_EFFECT__, __NAME_COLOR__)) \
{ \
    __FUNCT__(__AUTO_MODIFICATOR__, __AUTO_ITEM__ , __SELF__, __DIR__, __DAMAGE__, __WHO__, __COMBAT_TECH__, __COMBO_ID__); \
    continue; \
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#define MAIN_MACROS_BEFORE_THIT_NV_HIT_BY_MELEE_ATTACK(__NAME_COLOR__, __CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, __SELF__, __DIR__, __DAMAGE__, __WHO__, __COMBAT_TECH__, __COMBO_ID__) \
    ADD_LOGIC_BEFORE_THIT_NVBMA("#BladeMail", bladeMail, __NAME_COLOR__, __CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, __SELF__, __DIR__, __DAMAGE__, __WHO__, __COMBAT_TECH__, __COMBO_ID__) \
    ADD_LOGIC_BEFORE_THIT_NVBMA("#DamageNullification", damageNullification, __NAME_COLOR__, __CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, __SELF__, __DIR__, __DAMAGE__, __WHO__, __COMBAT_TECH__, __COMBO_ID__) \
    ADD_LOGIC_BEFORE_THIT_NVBMA("#ClutchSurvival", сlutchSurvival, __NAME_COLOR__, __CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, __SELF__, __DIR__, __DAMAGE__, __WHO__, __COMBAT_TECH__, __COMBO_ID__) \
    ADD_LOGIC_BEFORE_THIT_NVBMA("#UntouchableSoul", UntouchableSoul, __NAME_COLOR__, __CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, __SELF__, __DIR__, __DAMAGE__, __WHO__, __COMBAT_TECH__, __COMBO_ID__) \

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// отражение урона
inline void bladeMail(const float modificatorEffect, Item* itemThatCaused, Character& me, CutDirection& dir, Damages& damage, Character& attacking, CombatTechniqueData& attackTech, int& comboID)
{
    Damages newDamage = damage;
    newDamage.bleedMult         *= modificatorEffect;
    newDamage.blunt             *= modificatorEffect;
    newDamage.cut               *= modificatorEffect;
    newDamage.extraStun         *= modificatorEffect;
    newDamage.pierce            *= modificatorEffect;
    newDamage.armourPenetration *= modificatorEffect;

    auto& anatomy = attacking.medical.anatomy;
    anatomy[SuppKR::fastRandom(anatomy.size() - 1)]->applyDamage(newDamage);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// зануление урона
inline void damageNullification(const float modificatorEffect, Item* itemThatCaused, Character& me, CutDirection& dir, Damages& damage, Character& attacking, CombatTechniqueData& attackTech, int& comboID)
{
    float null = std::max(1.0f - modificatorEffect, 0.f);
    
    damage.bleedMult *= null;
    damage.blunt *= null;
    damage.cut *= null;
    damage.extraStun *= null;
    damage.pierce *= null;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// конечности не могут быть повреждены во время атаки
inline void сlutchSurvival(const float modificatorEffect, Item* itemThatCaused, Character& me, CutDirection& dir, Damages& damage, Character& attacking, CombatTechniqueData& attackTech, int& comboID)
{
    damage.armourPenetration *= modificatorEffect;
    damage.bleedMult *= modificatorEffect;
    damage.blunt *= modificatorEffect;
    damage.cut *= modificatorEffect;
    damage.extraStun *= modificatorEffect;
    damage.pierce *= modificatorEffect;

    auto& anatomy = me.medical.anatomy;
    for (uint32_t i = 3; i < anatomy.size(); i++)
    {
        auto& limb = anatomy[i];

        //Head - 
        //Stomach - 
        //Chest -
        //Left Arm +
        //Right Arm +
        //Left Leg +
        //Right Leg +
        if (limb->data->name.compare(0, 4, "Left") == 0 || limb->data->name.compare(0, 5, "Right") == 0)
        {
            limb->fleshStun = 0.f;
            limb->bandaging = 0.f;
            limb->flesh = limb->_maxHealth;
        }
    }
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

inline void UntouchableSoul(const float modificatorEffect, Item* itemThatCaused, Character& me, CutDirection& dir, Damages& damage, Character& attacking, CombatTechniqueData& attackTech, int& comboID)
{
    attacking.separateIntoMyOwnSquad(true);
    attacking.setFaction(me.getFaction(), me.getPlatoon());

    auto& anatomy = me.medical.anatomy;
    for (uint32_t i = 0; i < anatomy.size(); i++)
    {
        anatomy[i]->applyDamage(Damages(100.f, 100.f, 100.f, 100.f, 100.f));
    }

}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
