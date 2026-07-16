#include "HookKR.h"

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------

//не использован
bool (*applyFirstAid_orig)(MedicalSystem*, float, Item*, float, Character*) = nullptr;
bool applyFirstAid_hook(MedicalSystem* thsptr, float skill, Item* equipment, float frameTIME, Character* who)
{
    //KR_DEBUG_LOG_L3_1("Call - applyFirstAid_hook");

    auto ret = applyFirstAid_orig(thsptr, skill, equipment, frameTIME, who);

    //KR_DEBUG_LOG_L3_1("Exit - applyFirstAid_hook");
    return ret;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool (*applyDoctoring_orig)(MedicalSystem*, float, Item*, float, Character*) = nullptr;
bool applyDoctoring_hook(MedicalSystem* thsptr, float skill, Item* equipment, float frameTIME, Character* who)
{
    KR_DEBUG_LOG_L3_1("Call - applyDoctoring_hook");
    KR_DEBUG_LOG_L3_1("------------------------------------------------");

    // проход по предметам того КТО хилить
    FOR_EACH_COLOR(who, MAIN_MACROS_LOGIC_BEFORE_APLY__DOCTORING(__AUTO_NAME__, __AUTO_CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, *thsptr->me, skill, *equipment, frameTIME, *who));

    KR_DEBUG_LOG_L3_1("======");

    // проход по предметам того КОГО хилят
    FOR_EACH_COLOR(thsptr->me, MAIN_MACROS_LOGIC_BEFORE_RECIEVED_APLY_DOCTORING(__AUTO_NAME__, __AUTO_CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, *thsptr->me, skill, *equipment, frameTIME, *who));

    KR_DEBUG_LOG_L3_1("------------------------------------------------");
    KR_DEBUG_LOG_L3_1("Exit - applyDoctoring_hook");
    return  applyDoctoring_orig(thsptr, skill, equipment, frameTIME, who);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------

//не использован
bool (*applyRigging_orig)(MedicalSystem*, float, Item*, float) = nullptr;
bool applyRigging_hook(MedicalSystem* thsptr, float skill, Item* equipment, float frameTIME)
{
    KR_DEBUG_LOG_L3_2("Call - applyRigging_hook");

    // проход по предметам того КОГО хилят
    FOR_EACH_COLOR(thsptr->me, MAIN_MACROS_LOGIC_BEFORE_APLY_RIGGING(__AUTO_NAME__, __AUTO_CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, *thsptr->me, skill, *equipment, frameTIME));
 

    KR_DEBUG_LOG_L3_2("Exit - applyRigging_hook");
    return applyRigging_orig(thsptr, skill, equipment, frameTIME);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------

//не использован
void (*_NV_periodicUpdate_orig)(MedicalSystem*) = nullptr;
void _NV_periodicUpdate_hook(MedicalSystem* thsptr)
{
    //KR_DEBUG_LOG_L3_1("Call - _NV_periodicUpdate_hook");


    _NV_periodicUpdate_orig(thsptr);

    //KR_DEBUG_LOG_L3_1("Exit - _NV_periodicUpdate_hook");
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------
