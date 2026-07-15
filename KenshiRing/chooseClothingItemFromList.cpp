#include "HookKR.h"

GameData* (*_chooseClothingItemFromList_orig)(GameData* dataList, const std::string& listName, AttachSlot sectionAttach, RaceData* race) = nullptr;

//-----------------------------------------------------------------------------------------------------------------------------------------------------------

GameData* _chooseClothingItemFromList_hook(GameData* dataList, const std::string& listName, AttachSlot sectionAttach, RaceData* race)
{
    return _chooseClothingItemFromList_orig(dataList, listName, sectionAttach, race);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------
