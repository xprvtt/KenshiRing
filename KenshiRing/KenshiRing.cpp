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
    if (KenshiLib::SUCCESS != KenshiLib::AddHook(KenshiLib::GetRealAddress(&Character::_NV_init), &NVInitHook, &NVInitOrig))
    {
        KR_ERROR_LOG("Failure hooking Character::_NV_init.");
    }
    KR_DEBUG_LOG_L1("Success load hook -> Character::_NV_init");
    #endif // CHARACTER_NV_INIT

    //=================================================

    #ifdef ROOTOBJECTFACTORY_CHOOSEMYCLOTHING
    if (KenshiLib::SUCCESS != KenshiLib::AddHook(KenshiLib::GetRealAddress(&RootObjectFactory::chooseMyClothing), &chooseMyClothingHook, &chooseMyClothingOrig))
    {
        KR_ERROR_LOG("Failure hooking RootObjectFactory::chooseMyClothing.");
    }
    KR_DEBUG_LOG_L1("Success load hook -> RootObjectFactory::chooseMyClothing");
    #endif // ROOTOBJECTFACTORY_CHOOSEMYCLOTHING

    //=================================================

    #ifdef ROOTOBJECTFACTORY_CHOOSECLOTHINGITEMFROMLIST
    if (KenshiLib::SUCCESS != KenshiLib::AddHook(KenshiLib::GetRealAddress(&RootObjectFactory::_chooseClothingItemFromList), &chooseClothingItemFromListHook, &chooseClothingItemFromListOrig))
    {
        KR_ERROR_LOG("Failure hooking RootObjectFactory::_chooseClothingItemFromList.");
    }
    KR_DEBUG_LOG_L1("Success load hook -> RootObjectFactory::_chooseClothingItemFromList");
    #endif // ROOTOBJECTFACTORY_CHOOSECLOTHINGITEMFROMLIST

    //=================================================

    #ifdef INVENTORY_GETSECTIONOFTYPE
    if (KenshiLib::SUCCESS != KenshiLib::AddHook(KenshiLib::GetRealAddress(&Inventory::getSectionOfType), &getSectionOfTypeHook, &getSectionOfTypeOrig))
    {
        KR_ERROR_LOG("Failure hooking Inventory::getSectionOfType.");
    }
    KR_DEBUG_LOG_L1("Success load hook -> Inventory::getSectionOfType");
    #endif // INVENTORY_GETSECTIONOFTYPE

    //=================================================

    #ifdef CHARACTER_NV_HITBYMELEEATTACK
    if (KenshiLib::SUCCESS != KenshiLib::AddHook(KenshiLib::GetRealAddress(&Character::_NV_hitByMeleeAttack), &NVHitByMeleeAttackHook, &NVHitByMeleeAttackOrig))
    {
        KR_ERROR_LOG("Failure hooking Character::_NV_hitByMeleeAttack.");
    }
    KR_DEBUG_LOG_L1("Success load hook -> Character::_NV_hitByMeleeAttack");
    #endif // CHARACTER_NV_HITBYMELEEATTACK

    //=================================================

    #ifdef CHARACTER_NV_GETTINGEATEN
    if (KenshiLib::SUCCESS != KenshiLib::AddHook(KenshiLib::GetRealAddress(&Character::_NV_gettingEaten), &NVGettingEatenHook, &NVGettingEatenOrig))
    {
        KR_ERROR_LOG("Failure hooking Character::_NV_gettingEaten.");
    }
    KR_DEBUG_LOG_L1("Success load hook -> Character::_NV_gettingEaten");
    #endif // CHARACTER_NV_GETTINGEATEN

    //=================================================

    #ifdef CHARACTER_ATTACKTARGET
    if (KenshiLib::SUCCESS != KenshiLib::AddHook(KenshiLib::GetRealAddress(&Character::attackTarget), &attackTargetHook, &attackTargetOrig))
    {
        KR_ERROR_LOG("Failure hooking Character::attackTarget.");
    }
    KR_DEBUG_LOG_L1("Success load hook -> Character::attackTarget");
    #endif // CHARACTER_ATTACKTARGET

    //=================================================

    #ifdef MEDICALSYSTEM_APPLYFIRSTAID
    if (KenshiLib::SUCCESS != KenshiLib::AddHook(KenshiLib::GetRealAddress(&MedicalSystem::applyFirstAid), &applyFirstAidHook, &applyFirstAidOrig))
    {
        KR_ERROR_LOG("Failure hooking MedicalSystem::applyFirstAid.");
    }
    KR_DEBUG_LOG_L1("Success load hook -> MedicalSystem::applyFirstAid");
    #endif // MEDICALSYSTEM_APPLYFIRSTAID

    //=================================================

    #ifdef MEDICALSYSTEM_APPLYDOCTORING
    if (KenshiLib::SUCCESS != KenshiLib::AddHook(KenshiLib::GetRealAddress(&MedicalSystem::applyDoctoring), &applyDoctoringHook, &applyDoctoringOrig))
    {
        KR_ERROR_LOG("Failure hooking MedicalSystem::applyDoctoring.");
    }
    KR_DEBUG_LOG_L1("Success load hook -> MedicalSystem::applyDoctoring");
    #endif // MEDICALSYSTEM_APPLYDOCTORING

    //=================================================

    #ifdef MEDICALSYSTEM_APPLYRIGGING
    if (KenshiLib::SUCCESS != KenshiLib::AddHook(KenshiLib::GetRealAddress(&MedicalSystem::applyRigging), &applyRiggingHook, &applyRiggingOrig))
    {
        KR_ERROR_LOG("Failure hooking MedicalSystem::applyRigging.");
    }
    KR_DEBUG_LOG_L1("Success load hook -> MedicalSystem::applyRigging");
    #endif // MEDICALSYSTEM_APPLYRIGGING

    //=================================================

    #ifdef MEDICALSYSTEM_NV_PERIODICUPDATE
    if (KenshiLib::SUCCESS != KenshiLib::AddHook(KenshiLib::GetRealAddress(&MedicalSystem::_NV_periodicUpdate), &NVPeriodicUpdateHook, &NVPeriodicUpdateOrig))
    {
        KR_ERROR_LOG("Failure hooking MedicalSystem::_NV_periodicUpdate.");
    }
    KR_DEBUG_LOG_L1("Success load hook -> MedicalSystem::_NV_periodicUpdate");
    #endif // MEDICALSYSTEM_NV_PERIODICUPDATE

    //=================================================

    #ifdef CHARACTER_NV_UPDATE
    if (KenshiLib::SUCCESS != KenshiLib::AddHook(KenshiLib::GetRealAddress(&Character::_NV_update), &NVUpdateHook, &NVUpdateOrig))
    {
        KR_ERROR_LOG("Failure hooking Character::_NV_update.");
    }
    KR_DEBUG_LOG_L1("Success load hook -> Character::_NV_update");
    #endif // CHARACTER_NV_UPDATE

    //=================================================

    #ifdef CHARACTER_ISHOTYOU
    if (KenshiLib::SUCCESS != KenshiLib::AddHook(KenshiLib::GetRealAddress(&Character::iShotYou), &iShotYouHook, &iShotYouOrig))
    {
        KR_ERROR_LOG("Failure hooking Character::iShotYou.");
    }
    KR_DEBUG_LOG_L1("Success load hook -> Character::iShotYou");
    #endif // CHARACTER_ISHOTYOU

    //=================================================
    //InventoryLayout(const std::string & file);

    #ifdef INVENTORYLAYOUT_CONSTRUCTOR
    if (KenshiLib::SUCCESS != KenshiLib::AddHook(KenshiLib::GetRealAddress(&InventoryLayout::_CONSTRUCTOR), &constructorHook, &constructorOrig))
    {
        KR_ERROR_LOG("Failure hooking &InventoryLayout::_CONSTRUCTOR");
    }
    KR_DEBUG_LOG_L1("Success load hook -> &InventoryLayout::_CONSTRUCTOR");
    #endif // INVENTORYLAYOUT_CONSTRUCTOR

    //=================================================

    ////void _NV_setupCharacterEntityTexture(Ogre::Entity * ent, const boost::unordered::unordered_map<std::string, std::string, boost::hash<std::string >, std::equal_to<std::string >, Ogre::STLAllocator<std::pair<std::string const, std::string >, Ogre::GeneralAllocPolicy > >&textureLayers, Ogre::ColourValue * colour);// protected RVA = 0x52B340 vtable offset = 0x60

    //KenshiLib::AddHook(KenshiLib::GetRealAddress(&AppearanceHuman::_NV_setupCharacterEntityTexture), &constructorHook, &constructorOrig)

}

