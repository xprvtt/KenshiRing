#include "HookKR.h"

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------

//не использован
bool (*applyFirstAidOrig)(MedicalSystem*, float, Item*, float, Character*) = nullptr;
bool applyFirstAidHook(MedicalSystem* self, float skill, Item* equipment, float frameTime, Character* who)
{
    //KR_DEBUG_LOG_L3_1("Call - applyFirstAidHook");

    auto ret = applyFirstAidOrig(self, skill, equipment, frameTime, who);

    //KR_DEBUG_LOG_L3_1("Exit - applyFirstAidHook");
    return ret;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool (*applyDoctoringOrig)(MedicalSystem*, float, Item*, float, Character*) = nullptr;
bool applyDoctoringHook(MedicalSystem* self, float skill, Item* equipment, float frameTime, Character* who)
{
    KR_DEBUG_LOG_L3_1("Call - applyDoctoringHook");
    KR_DEBUG_LOG_L3_1("------------------------------------------------");

    // проход по предметам того КТО хилить
    FOR_EACH_COLOR(who, MAIN_MACROS_LOGIC_BEFORE_APLY__DOCTORING(__AUTO_NAME__, __AUTO_CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, *self->me, skill, *equipment, frameTime, *who));

    KR_DEBUG_LOG_L3_1("======");

    // проход по предметам того КОГО хилят
    FOR_EACH_COLOR(self->me, MAIN_MACROS_LOGIC_BEFORE_RECIEVED_APLY_DOCTORING(__AUTO_NAME__, __AUTO_CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, *self->me, skill, *equipment, frameTime, *who));

    KR_DEBUG_LOG_L3_1("------------------------------------------------");
    KR_DEBUG_LOG_L3_1("Exit - applyDoctoringHook");
    return  applyDoctoringOrig(self, skill, equipment, frameTime, who);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------

//не использован
bool (*applyRiggingOrig)(MedicalSystem*, float, Item*, float) = nullptr;
bool applyRiggingHook(MedicalSystem* self, float skill, Item* equipment, float frameTime)
{
    KR_DEBUG_LOG_L3_2("Call - applyRiggingHook");

    // проход по предметам того КОГО хилят
    FOR_EACH_COLOR(self->me, MAIN_MACROS_LOGIC_BEFORE_APLY_RIGGING(__AUTO_NAME__, __AUTO_CHANCE__, __AUTO_MODIFICATOR__, __AUTO_ITEM__, *self->me, skill, *equipment, frameTime));
 

    KR_DEBUG_LOG_L3_2("Exit - applyRiggingHook");
    return applyRiggingOrig(self, skill, equipment, frameTime);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------

//не использован
void (*NVPeriodicUpdateOrig)(MedicalSystem*) = nullptr;
void NVPeriodicUpdateHook(MedicalSystem* self)
{
    //KR_DEBUG_LOG_L3_1("Call - NVPeriodicUpdateHook");


    NVPeriodicUpdateOrig(self);

    //KR_DEBUG_LOG_L3_1("Exit - NVPeriodicUpdateHook");
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------
