#include "HookKR.h"


//-------------------------------------------------------------------------------------------------------------------------------------------------------------------

InventorySection* (*getSectionOfTypeOrig)(Inventory* self, AttachSlot type) = nullptr;
InventorySection* getSectionOfTypeHook(Inventory* self, AttachSlot type)
{
    KR_DEBUG_LOG_L2("Call - getSectionOfTypeHook FOR ATTACH - " + SuppKR::toStringV100(type));
    
    InventorySection* approvedSection = nullptr;

    // self->getSection(""); должен указывать на самую большую секцию (x*y), если секций >1 для типа AttachSlot
    // сделать этот метод автономным будет стоить оргромной потере производительности из-за 100+ вызовов в секунду, поэтому добавте вручную

    switch (type)
    {
    //case ATTACH_LEFT_ARM:
    //case ATTACH_LEFT_LEG:  
    //case ATTACH_RIGHT_ARM: 
    //case ATTACH_RIGHT_LEG: 
    
    //case ATTACH_BODY:
    //    approvedSection = self->getSection("armour");
    //    break;
    //case ATTACH_NONE:
    //    approvedSection = self->getSection("main");
    //    break;
    //case ATTACH_BACKPACK:
    //    approvedSection = self->getSection("backpack_attach");
    //    break;
    case ATTACH_WEAPON:
        approvedSection = self->getSection("back");
        break;
    case ATTACH_BACK:
        approvedSection = self->getSection("KR_shoulders");
        break;
    case ATTACH_HAIR:
        approvedSection = self->getSection("KR_ears");
        break;
    case ATTACH_HAT:
        approvedSection = self->getSection("head");
        break;
    case ATTACH_EYES:
        approvedSection = self->getSection("EIS_eyes_eyes");
        break;
    case ATTACH_LEGS:
        approvedSection = self->getSection("legs");
        break;
    case ATTACH_SHIRT:
        approvedSection = self->getSection("shirt");
        break;
    case ATTACH_BOOTS:
        approvedSection = self->getSection("boots");
        break;
    case ATTACH_GLOVES:
        approvedSection = self->getSection("KR_forearm");
        break;
    case ATTACH_NECK:
        approvedSection = self->getSection("EIS_neck");
        break;
    case ATTACH_BEARD:
        approvedSection = self->getSection("KR_fingers");
        break;
    case ATTACH_BELT:
        approvedSection = self->getSection("belt");
        break;
    }
    KR_DEBUG_LOG_L2("exit - getSectionOfTypeHook");

    return approvedSection ? approvedSection : getSectionOfTypeOrig(self, type);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------