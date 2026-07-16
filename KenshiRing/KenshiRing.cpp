#include "HookKR.h"

// управление хуками расположено в CoreMacrosHelper.h

__declspec(dllexport) void startPlugin()
{
    //=================================================
    // главная функция инициализации проекта
    // Если вы захотите изменить конфигурацию мода, то скорее всего вам в setup()

    setup();

    KR_DEBUG_LOG_L1("MOD CONFIGURATION INITIALIZED");

    //=================================================

    #ifdef CHARACTER_NV_INIT
    if (KenshiLib::SUCCESS != KenshiLib::AddHook(KenshiLib::GetRealAddress(&Character::_NV_init), &_NV_init_hook, &Character_NV_init_orig))
    {
        KR_ERROR_LOG("Failure hooking Character::_NV_init.");
    }
    KR_DEBUG_LOG_L1("Success load hook -> Character::_NV_init");
    #endif // CHARACTER_NV_INIT

    //=================================================

    #ifdef ROOTOBJECTFACTORY_CHOOSEMYCLOTHING
    if (KenshiLib::SUCCESS != KenshiLib::AddHook(KenshiLib::GetRealAddress(&RootObjectFactory::chooseMyClothing), &chooseMyClothing_hook, &chooseMyClothing_orig))
    {
        KR_ERROR_LOG("Failure hooking RootObjectFactory::chooseMyClothing.");
    }
    KR_DEBUG_LOG_L1("Success load hook -> RootObjectFactory::chooseMyClothing");
    #endif // ROOTOBJECTFACTORY_CHOOSEMYCLOTHING

    //=================================================

    #ifdef ROOTOBJECTFACTORY_CHOOSECLOTHINGITEMFROMLIST
    if (KenshiLib::SUCCESS != KenshiLib::AddHook(KenshiLib::GetRealAddress(&RootObjectFactory::_chooseClothingItemFromList), &_chooseClothingItemFromList_hook, &_chooseClothingItemFromList_orig))
    {
        KR_ERROR_LOG("Failure hooking RootObjectFactory::_chooseClothingItemFromList.");
    }
    KR_DEBUG_LOG_L1("Success load hook -> RootObjectFactory::_chooseClothingItemFromList");
    #endif // ROOTOBJECTFACTORY_CHOOSECLOTHINGITEMFROMLIST

    //=================================================

    #ifdef INVENTORY_GETSECTIONOFTYPE
    if (KenshiLib::SUCCESS != KenshiLib::AddHook(KenshiLib::GetRealAddress(&Inventory::getSectionOfType), &getSectionOfType_hook, &getSectionOfType_orig))
    {
        KR_ERROR_LOG("Failure hooking Inventory::getSectionOfType.");
    }
    KR_DEBUG_LOG_L1("Success load hook -> Inventory::getSectionOfType");
    #endif // INVENTORY_GETSECTIONOFTYPE

    //=================================================

    #ifdef CHARACTER_NV_HITBYMELEEATTACK
    if (KenshiLib::SUCCESS != KenshiLib::AddHook(KenshiLib::GetRealAddress(&Character::_NV_hitByMeleeAttack), &_NV_hitByMeleeAttack_hook, &_NV_hitByMeleeAttack_orig))
    {
        KR_ERROR_LOG("Failure hooking Character::_NV_hitByMeleeAttack.");
    }
    KR_DEBUG_LOG_L1("Success load hook -> Character::_NV_hitByMeleeAttack");
    #endif // CHARACTER_NV_HITBYMELEEATTACK

    //=================================================

    #ifdef CHARACTER_NV_GETTINGEATEN
    if (KenshiLib::SUCCESS != KenshiLib::AddHook(KenshiLib::GetRealAddress(&Character::_NV_gettingEaten), &_NV_gettingEaten_hook, &_NV_gettingEaten_orig))
    {
        KR_ERROR_LOG("Failure hooking Character::_NV_gettingEaten.");
    }
    KR_DEBUG_LOG_L1("Success load hook -> Character::_NV_gettingEaten");
    #endif // CHARACTER_NV_GETTINGEATEN

    //=================================================

    #ifdef CHARACTER_ATTACKTARGET
    if (KenshiLib::SUCCESS != KenshiLib::AddHook(KenshiLib::GetRealAddress(&Character::attackTarget), &attackTarget_hook, &attackTarget_orig))
    {
        KR_ERROR_LOG("Failure hooking Character::attackTarget.");
    }
    KR_DEBUG_LOG_L1("Success load hook -> Character::attackTarget");
    #endif // CHARACTER_ATTACKTARGET

    //=================================================

    #ifdef MEDICALSYSTEM_APPLYFIRSTAID
    if (KenshiLib::SUCCESS != KenshiLib::AddHook(KenshiLib::GetRealAddress(&MedicalSystem::applyFirstAid), &applyFirstAid_hook, &applyFirstAid_orig))
    {
        KR_ERROR_LOG("Failure hooking MedicalSystem::applyFirstAid.");
    }
    KR_DEBUG_LOG_L1("Success load hook -> MedicalSystem::applyFirstAid");
    #endif // MEDICALSYSTEM_APPLYFIRSTAID

    //=================================================

    #ifdef MEDICALSYSTEM_APPLYDOCTORING
    if (KenshiLib::SUCCESS != KenshiLib::AddHook(KenshiLib::GetRealAddress(&MedicalSystem::applyDoctoring), &applyDoctoring_hook, &applyDoctoring_orig))
    {
        KR_ERROR_LOG("Failure hooking MedicalSystem::applyDoctoring.");
    }
    KR_DEBUG_LOG_L1("Success load hook -> MedicalSystem::applyDoctoring");
    #endif // MEDICALSYSTEM_APPLYDOCTORING

    //=================================================

    #ifdef MEDICALSYSTEM_APPLYRIGGING
    if (KenshiLib::SUCCESS != KenshiLib::AddHook(KenshiLib::GetRealAddress(&MedicalSystem::applyRigging), &applyRigging_hook, &applyRigging_orig))
    {
        KR_ERROR_LOG("Failure hooking MedicalSystem::applyRigging.");
    }
    KR_DEBUG_LOG_L1("Success load hook -> MedicalSystem::applyRigging");
    #endif // MEDICALSYSTEM_APPLYRIGGING

    //=================================================

    #ifdef MEDICALSYSTEM_NV_PERIODICUPDATE
    if (KenshiLib::SUCCESS != KenshiLib::AddHook(KenshiLib::GetRealAddress(&MedicalSystem::_NV_periodicUpdate), &_NV_periodicUpdate_hook, &_NV_periodicUpdate_orig))
    {
        KR_ERROR_LOG("Failure hooking MedicalSystem::_NV_periodicUpdate.");
    }
    KR_DEBUG_LOG_L1("Success load hook -> MedicalSystem::_NV_periodicUpdate");
    #endif // MEDICALSYSTEM_NV_PERIODICUPDATE

    //=================================================

    #ifdef CHARACTER_NV_UPDATE
    if (KenshiLib::SUCCESS != KenshiLib::AddHook(KenshiLib::GetRealAddress(&Character::_NV_update), &_NV_update_hook, &_NV_update_orig))
    {
        KR_ERROR_LOG("Failure hooking Character::_NV_update.");
    }
    KR_DEBUG_LOG_L1("Success load hook -> Character::_NV_update");
    #endif // CHARACTER_NV_UPDATE

    //=================================================

    #ifdef CHARACTER_ISHOTYOU
    if (KenshiLib::SUCCESS != KenshiLib::AddHook(KenshiLib::GetRealAddress(&Character::iShotYou), &_iShotYou_hook, &iShotYou_orig))
    {
        KR_ERROR_LOG("Failure hooking Character::_NV_update.");
    }
    KR_DEBUG_LOG_L1("Success load hook -> Character::_NV_update");
    #endif // CHARACTER_ISHOTYOU

    //=================================================

}


