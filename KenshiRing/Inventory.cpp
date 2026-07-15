#include "HookKR.h"


//-------------------------------------------------------------------------------------------------------------------------------------------------------------------

InventorySection* (*getSectionOfType_orig)(Inventory* thisptr, AttachSlot type) = nullptr;
InventorySection* getSectionOfType_hook(Inventory* thisptr, AttachSlot type)
{
    KR_DEBUG_LOG_L2("Call - getSectionOfType_hook FOR ATTACH - " + SuppKR::toStringV100(type));
    
    InventorySection* approvedSection = nullptr;

    // thisptr->getSection(""); должен указывать на самую большую секцию (x*y), если секций >1 для типа AttachSlot
    // сделать этот метод автономным будет стоить оргромной потере производительности из-за 100+ вызовов в секунду, поэтому добавтье вручную

    switch (type)
    {
    //case ATTACH_LEFT_ARM:
    //case ATTACH_LEFT_LEG:  
    //case ATTACH_RIGHT_ARM: 
    //case ATTACH_RIGHT_LEG: 
    
    //case ATTACH_BODY:
    //    approvedSection = thisptr->getSection("armour");
    //    break;
    //case ATTACH_NONE:
    //    approvedSection = thisptr->getSection("main");
    //    break;
    //case ATTACH_BACKPACK:
    //    approvedSection = thisptr->getSection("backpack_attach");
    //    break;
    case ATTACH_WEAPON:
        approvedSection = thisptr->getSection("back");
        break;
    case ATTACH_BACK:
        approvedSection = thisptr->getSection("KR_shoulders");
        break;
    case ATTACH_HAIR:
        approvedSection = thisptr->getSection("KR_ears");
        break;
    case ATTACH_HAT:
        approvedSection = thisptr->getSection("head");
        break;
    case ATTACH_EYES:
        approvedSection = thisptr->getSection("EIS_eyes_eyes");
        break;
    case ATTACH_LEGS:
        approvedSection = thisptr->getSection("legs");
        break;
    case ATTACH_SHIRT:
        approvedSection = thisptr->getSection("shirt");
        break;
    case ATTACH_BOOTS:
        approvedSection = thisptr->getSection("boots");
        break;
    case ATTACH_GLOVES:
        approvedSection = thisptr->getSection("KR_forearm");
        break;
    case ATTACH_NECK:
        approvedSection = thisptr->getSection("EIS_neck");
        break;
    case ATTACH_BEARD:
        approvedSection = thisptr->getSection("KR_fingers");
        break;
    case ATTACH_BELT:
        approvedSection = thisptr->getSection("belt");
        break;
    }
    KR_DEBUG_LOG_L2("exit - getSectionOfType_hook");

    return approvedSection ? approvedSection : getSectionOfType_orig(thisptr, type);
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------