#include "HookKR.h"

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------

//не использован
bool (*MedicalSystem_applyFirstAid_orig)(MedicalSystem*, float, Item*, float, Character*) = nullptr;
bool MedicalSystem_applyFirstAid_hook(MedicalSystem* thsptr, float skill, Item* equipment, float frameTIME, Character* who)
{
    //KR_DEBUG_LOG_L3_1("Call - MedicalSystem_applyFirstAid_hook");

    auto ret = MedicalSystem_applyFirstAid_orig(thsptr, skill, equipment, frameTIME, who);

    //KR_DEBUG_LOG_L3_1("Exit - MedicalSystem_applyFirstAid_hook");
    return ret;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool (*MedicalSystem_applyDoctoring_orig)(MedicalSystem*, float, Item*, float, Character*) = nullptr;
bool MedicalSystem_applyDoctoring_hook(MedicalSystem* thsptr, float skill, Item* equipment, float frameTIME, Character* who)
{
    KR_DEBUG_LOG_L3_1("Call - MedicalSystem_applyDoctoring_hook");
    KR_DEBUG_LOG_L3_1("------------------------------------------------");

    // проход по предметам того КТО хилить
    FOR_EACH_COLOR(who, MAIN_MACROS_LOGIC_BEFORE_APLY__DOCTORING(__AUTO_NAME__, __AUTO_CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, *thsptr->me, skill, *equipment, frameTIME, *who));

    KR_DEBUG_LOG_L3_1("======");

    // проход по предметам того КОГО хилят
    FOR_EACH_COLOR(thsptr->me, MAIN_MACROS_LOGIC_BEFORE_RECIEVED_APLY_DOCTORING(__AUTO_NAME__, __AUTO_CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, *thsptr->me, skill, *equipment, frameTIME, *who));

    KR_DEBUG_LOG_L3_1("------------------------------------------------");
    KR_DEBUG_LOG_L3_1("Exit - MedicalSystem_applyDoctoring_hook");
    return  MedicalSystem_applyDoctoring_orig(thsptr, skill, equipment, frameTIME, who);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------

//не использован
bool (*MedicalSystem_applyRigging_orig)(MedicalSystem*, float, Item*, float) = nullptr;
bool MedicalSystem_applyRigging_hook(MedicalSystem* thsptr, float skill, Item* equipment, float frameTIME)
{
    KR_DEBUG_LOG_L3_2("Call - MedicalSystem_applyRigging_hook");

    // проход по предметам того КОГО хилят
    FOR_EACH_COLOR(thsptr->me, MAIN_MACROS_LOGIC_BEFORE_APLY_RIGGING(__AUTO_NAME__, __AUTO_CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, *thsptr->me, skill, *equipment, frameTIME));
 

    KR_DEBUG_LOG_L3_2("Exit - MedicalSystem_applyRigging_hook");
    return MedicalSystem_applyRigging_orig(thsptr, skill, equipment, frameTIME);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------

//не использован
void (*MedicalSystem_NV_periodicUpdate_orig)(MedicalSystem*) = nullptr;
void MedicalSystem_NV_periodicUpdate_hook(MedicalSystem* thsptr)
{
    //KR_DEBUG_LOG_L3_1("Call - MedicalSystem_NV_periodicUpdate_hook");


    MedicalSystem_NV_periodicUpdate_orig(thsptr);

    //KR_DEBUG_LOG_L3_1("Exit - MedicalSystem_NV_periodicUpdate_hook");
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------
