#include "HookKR.h"

#define EMPLACE_SECTION_KR(__SECTION_KR__) \
    (__SECTION_KR__).name.c_str(), \
    (__SECTION_KR__).sizeSection.width, \
    (__SECTION_KR__).sizeSection.height, \
    (__SECTION_KR__).sectionAttach, \
    (__SECTION_KR__).equipCallbacks, \
    (__SECTION_KR__).isContainerSection, \
    (__SECTION_KR__).enabled, \
    (__SECTION_KR__).limit

void (*Character_NV_init_orig)(Character* thisptr) = nullptr;
void ensureExtraInventorySections(Inventory* inv, std::vector<ConfigIKR::PropertySectionKR> newSlots);

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------

void Character_NV_init_hook(Character* thisptr)
{
    Character_NV_init_orig(thisptr);
    ensureExtraInventorySections(thisptr->inventory, InventoryKR::instance().getNewSlots());
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------

// This function checks for the existence of our extra inventory sections and creates them if they don't already exist.
void ensureExtraInventorySections(Inventory* inv, std::vector<ConfigIKR::PropertySectionKR> newSlots)
{
    if (!inv)
    {
        ErrorLog("ensureExtraInventorySections: Inventory pointer missing or null");
        return;
    }

    // (!) MOVED TO Setup.cpp
    // 
    // hardcoded section info for our extra inventory sections
    //static const PropertySectionKR sections[] = {
    //    {"eyes_eyes",  3, 1, ATTACH_EYES,   true, false, true, 1},
    //    {"eyes_belts", 3, 1, ATTACH_BELT,   true, false, true, 1},
    //    {"eyes_hats",  3, 1, ATTACH_HAT,    true, false, true, 1},
    //    {"neck",       2, 2, ATTACH_NECK,   true, false, true, 1},
    //    {"gloves",     2, 2, ATTACH_GLOVES, true, false, true, 4}
    //};

    for (int it = 0; it < newSlots.size(); it++)
    {
        auto currentSlot = newSlots[it];

        if (!inv->getSection(currentSlot.name))
        {
            // store returned pointer so we can validate and correct sizes if necessary
            // Сохраняем возвращенный указатель, чтобы при необходимости проверить и скорректировать размеры. // нам это необходимо?
            InventorySection* newSection = inv->_NV_initialiseNewSection(EMPLACE_SECTION_KR(currentSlot));

            if (!newSection)
            {
                std::string sectionNameStr = "ensureExtraInventorySections: failed to create section " + std::string(currentSlot.name);
                ErrorLog(sectionNameStr.c_str());
                continue;
            }

            // If the created section does not match expected dims, resize it.
            // This avoids Array2d out-of-range access if constructor used swapped dims or other mismatch.
            if (newSection->width != currentSlot.sizeSection.width || newSection->height != currentSlot.sizeSection.height)
            {
                std::ostringstream oss;
                oss << "ensureExtraInventorySections: section '" << currentSlot.name
                    << "' created with unexpected size (got " << newSection->width << " x " << newSection->height
                    << ", expected " << currentSlot.sizeSection.width << " x " << currentSlot.sizeSection.height << "). Resizing.";
                ErrorLog(oss.str());

                inv->resizeSection(newSection, currentSlot.sizeSection.width, currentSlot.sizeSection.height, true);
            }
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------
