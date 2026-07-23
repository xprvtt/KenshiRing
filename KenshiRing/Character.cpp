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

void (*NVInitOrig)(Character* self) = nullptr;
void NVInitHook(Character* self)
{
    KR_DEBUG_LOG_L5("Call - NVInitHook");
    
    NVInitOrig(self);
    if (!self->inventory)
    {
        return;
    }
    const auto& newSec = KRI_GET_INSTANCE.getNewSections();
    for (int it = 0; it < newSec.size(); it++)
    {
        auto currentSlot = newSec[it];
        if (!self->inventory->getSection(currentSlot.m_name))
        {
            if (!self->inventory->_NV_initialiseNewSection(EMPLACE_SECTION_KR(currentSlot)))
            {
                KR_ERROR_LOG("\t\failed to create section " + currentSlot.m_name);
                continue;
            }
        }
    }
    KR_DEBUG_LOG_L5("Exit - NVInitHook");
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool (*NVGettingEatenOrig)(Character* self, float amount, Character* eater) = nullptr;
bool NVGettingEatenHook(Character* self, float amount, Character* eater)
{
    KR_DEBUG_LOG_L5("Call - NVGettingEatenHook");

    // проход по бафам того кто нас ест
    FOR_EACH_COLOR(self, MAIN_MACROS_BEFORE_GETTING_EATEN(__AUTO_NAME__, __AUTO_CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, *self, amount, *eater));

    KR_DEBUG_LOG_L5("Exit - NVGettingEatenHook");
	return NVGettingEatenOrig(self, amount, eater);;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------
HitMaterialType(*NVHitByMeleeAttackOrig)(Character* self, CutDirection dir, Damages& damage, Character* who, CombatTechniqueData* attack, int comboID) = nullptr;
HitMaterialType NVHitByMeleeAttackHook(Character* self, CutDirection dir, Damages& damage, Character* who, CombatTechniqueData* attack, int comboID)
{
    KR_DEBUG_LOG_L5_1("Call - NVHitByMeleeAttackHook");
    KR_DEBUG_LOG_L5_1("--------------------------------------------------------");

    KR_DEBUG_LOG_L5_1(" ");

    KR_DEBUG_LOG_L5_1("attacking");

    // проход по бафам атакующего
    FOR_EACH_COLOR(who, MAIN_MACROS_BEFORE_ATTACING_NV_HIT_BY_MELEE_ATTACK(__AUTO_NAME__, __AUTO_CHANCE__ , __AUTO_MODIFICATOR__ , __AUTO_ITEM__, *who, dir, damage, *self, *attack, comboID));

    KR_DEBUG_LOG_L5_1(" ");

    KR_DEBUG_LOG_L5_1("victim");

    // проход по бафам пострадавшего
    FOR_EACH_COLOR(self, MAIN_MACROS_BEFORE_THIT_NV_HIT_BY_MELEE_ATTACK(__AUTO_NAME__, __AUTO_CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, *self, dir, damage, *who, *attack, comboID));

    HitMaterialType returnVal = NVHitByMeleeAttackOrig(self, dir, damage, who, attack, comboID);

    KR_DEBUG_LOG_L5_1(" ");

    KR_DEBUG_LOG_L5_1("--------------------------------------------------------");
    KR_DEBUG_LOG_L5_1("Exit - NVHitByMeleeAttackHook");
    return returnVal;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------

void (*attackTargetOrig)(Character*, Character*) = nullptr;
void attackTargetHook(Character* self, Character* who)
{
    KR_DEBUG_LOG_L5_4("Call - attackTargetHook");

    FOR_EACH_COLOR(who, MAIN_MACROS_BEFORE_ATTACK_TARGET(__AUTO_NAME__, __AUTO_CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, *self, *who));

    KR_DEBUG_LOG_L5_4("Exit - attackTargetHook");
    attackTargetOrig(self, who);;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------

// не используется
void (*NVUpdateOrig)(Character*) = nullptr;
void NVUpdateHook(Character* self)
{
    NVUpdateOrig(self);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool (*iShotYouOrig)(Character* self, Character* attacker, Harpoon* poon, bool onPurpose) = nullptr;
bool iShotYouHook(Character* self, Character* attacker, Harpoon* poon, bool onPurpose)
{
    KR_DEBUG_LOG_L5_3("Call - iShotYouHook");

    auto res =  iShotYouOrig(self, attacker, poon, onPurpose);

    // проход по тому КТО выстрелил
    FOR_EACH_COLOR(attacker, MAIN_MACROS_AFTER_SHOT(__AUTO_NAME__, __AUTO_CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, *self, *attacker, *poon, onPurpose, res));
    
    // проход по тому КТО получил пулю
    FOR_EACH_COLOR(self, MAIN_MACROS_AFTER_GET_SHOT(__AUTO_NAME__, __AUTO_CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, *self, *attacker, *poon, onPurpose, res));

    KR_DEBUG_LOG_L5_3("Exit - iShotYouHook === " + SuppKR::toStringV100(res));
    return res;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------
