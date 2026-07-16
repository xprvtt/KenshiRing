#include "HookKR.h"

#define EMPLACE_SECTION_KR(__SECTION_KR__) \
    (__SECTION_KR__).m_name.c_str(), \
    (__SECTION_KR__).m_sizeSection.m_width, \
    (__SECTION_KR__).m_sizeSection.m_height, \
    (__SECTION_KR__).m_sectionAttach, \
    (__SECTION_KR__).m_equipCallbacks, \
    (__SECTION_KR__).m_isContainerSection, \
    (__SECTION_KR__).m_enabled, \
    (__SECTION_KR__).m_limit

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------

void (*Character_NV_init_orig)(Character* thisptr) = nullptr;
void _NV_init_hook(Character* thisptr)
{
    KR_DEBUG_LOG_L5("Call - _NV_init_hook");

    Character_NV_init_orig(thisptr);
    if (!thisptr->inventory)
    {
        return;
    }
    const auto& newSec = KRI_GET_INSTANCE.getNewSections();
    for (int it = 0; it < newSec.size(); it++)
    {
        auto currentSlot = newSec[it];
        if (!thisptr->inventory->getSection(currentSlot.m_name))
        {
            if (!thisptr->inventory->_NV_initialiseNewSection(EMPLACE_SECTION_KR(currentSlot)))
            {
                KR_ERROR_LOG("\t\failed to create section " + currentSlot.m_name);
                continue;
            }
        }
    }
    KR_DEBUG_LOG_L5("Exit - _NV_init_hook");
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------

// This function checks for the existence of our extra inventory sections and creates them if they don't already exist.
void ensureExtraInventorySections(Inventory* inv, std::vector<ConfigIKR::PropertySectionKR> newSlots)
{
    KR_DEBUG_LOG_L5("Call - ensureExtraInventorySections");


    KR_DEBUG_LOG_L5("Exit - ensureExtraInventorySections");
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool (*_NV_gettingEaten_orig)(Character* thsptr, float amount, Character* eater) = nullptr;
bool _NV_gettingEaten_hook(Character* thsptr, float amount, Character* eater)
{
    KR_DEBUG_LOG_L5("Call - _NV_gettingEaten_hook");

    // проход по бафам того кто нас ест
    FOR_EACH_COLOR(thsptr, MAIN_MACROS_BEFORE_GETTING_EATEN(__AUTO_NAME__, __AUTO_CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, *thsptr, amount, *eater));

    KR_DEBUG_LOG_L5("Exit - _NV_gettingEaten_hook");
	return _NV_gettingEaten_orig(thsptr, amount, eater);;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------
HitMaterialType(*_NV_hitByMeleeAttack_orig)(Character* thsptr, CutDirection dir, Damages& damage, Character* who, CombatTechniqueData* attack, int comboID) = nullptr;
HitMaterialType _NV_hitByMeleeAttack_hook(Character* thsptr, CutDirection dir, Damages& damage, Character* who, CombatTechniqueData* attack, int comboID)
{
    KR_DEBUG_LOG_L5_1("Call - _NV_hitByMeleeAttack_hook");
    KR_DEBUG_LOG_L5_1("--------------------------------------------------------");

    KR_DEBUG_LOG_L5_1(" ");

    KR_DEBUG_LOG_L5_1("attacking");

    // проход по бафам атакующего
    FOR_EACH_COLOR(who, MAIN_MACROS_BEFORE_ATTACING_NV_HIT_BY_MELEE_ATTACK(__AUTO_NAME__, __AUTO_CHANCE__ , __AUTO_MODIFICATOR__ , __AUTO_ITEM__, *who, dir, damage, *thsptr, *attack, comboID));

    KR_DEBUG_LOG_L5_1(" ");

    KR_DEBUG_LOG_L5_1("victim");

    // проход по бафам пострадавшего
    FOR_EACH_COLOR(thsptr, MAIN_MACROS_BEFORE_THIT_NV_HIT_BY_MELEE_ATTACK(__AUTO_NAME__, __AUTO_CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, *thsptr, dir, damage, *who, *attack, comboID));

    HitMaterialType returnVal = _NV_hitByMeleeAttack_orig(thsptr, dir, damage, who, attack, comboID);

    KR_DEBUG_LOG_L5_1(" ");

    KR_DEBUG_LOG_L5_1("--------------------------------------------------------");
    KR_DEBUG_LOG_L5_1("Exit - _NV_hitByMeleeAttack_hook");
    return returnVal;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------

void (*attackTarget_orig)(Character*, Character*) = nullptr;
void attackTarget_hook(Character* thsptr, Character* who)
{
    KR_DEBUG_LOG_L5_4("Call - attackTarget_hook");

    FOR_EACH_COLOR(who, MAIN_MACROS_BEFORE_ATTACK_TARGET(__AUTO_NAME__, __AUTO_CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, *thsptr, *who));

    KR_DEBUG_LOG_L5_4("Exit - attackTarget_hook");
    attackTarget_orig(thsptr, who);;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------

// не используется
void (*_NV_update_orig)(Character*) = nullptr;
void _NV_update_hook(Character* thsptr)
{
    _NV_update_orig(thsptr);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool (*iShotYou_orig)(Character* thsptr, Character* attacker, Harpoon* poon, bool onPurpose) = nullptr;
bool _iShotYou_hook(Character* thsptr, Character* attacker, Harpoon* poon, bool onPurpose)
{
    KR_DEBUG_LOG_L5_3("Call - _iShotYou_hook");

    auto res =  iShotYou_orig(thsptr, attacker, poon, onPurpose);

    // проход по тому КТО выстрелил
    FOR_EACH_COLOR(attacker, MAIN_MACROS_AFTER_SHOT(__AUTO_NAME__, __AUTO_CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, *thsptr, *attacker, *poon, onPurpose, res));
    
    // проход по тому КТО получил пулю
    FOR_EACH_COLOR(thsptr, MAIN_MACROS_AFTER_GET_SHOT(__AUTO_NAME__, __AUTO_CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, *thsptr, *attacker, *poon, onPurpose, res));

    KR_DEBUG_LOG_L5_3("Exit - _iShotYou_hook === " + SuppKR::toStringV100(res));
    return res;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------
