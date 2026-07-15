#include "HookKR.h"


template<typename T>
void lektor_push_back(lektor<T>& lek, const T& val);

void (*chooseMyClothing_orig)(lektor<GameData*>& gear, GameData* dataList, const std::string& listName, RaceData* race, bool noShoes) = nullptr;

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------

void chooseMyClothing_hook(lektor<GameData*>& gear, GameData* dataList, const std::string& listName, RaceData* race, bool noShoes)
{
    chooseMyClothing_orig(gear, dataList, listName, race, noShoes);

    if (listName != "clothing")
    {
        return;
    }

    // FIX наших слотов нет
    const AttachSlot extraSlots[] = 
    {
        ATTACH_EYES,   //eyes_eyes
        ATTACH_GLOVES, //gloves
        ATTACH_NECK,   //neck
        //ATTACH_HAT,  //eyes_hats
        //ATTACH_BELT  //eyes_belts
    };

    // This game already chooses clothing for ATTACH_BELT and ATTACH_HAT slots from the "clothing" list, 
    // so we don't need to do anything special for those sections unless we would like the game to be able to populate 
    // both the original head/belt sections and our new ones at the same time, which would require some extra work.
    // 
    // If we want to populate both the original head/belt sections and our new ones, 
    // we would need to add some extra logicRing to determine which item goes in which section. If for example,
    // you have a character template that has a chance of spawning with a helmets and a pair of glasses (both using ATTACH_HAT), 
    // when we "choose" our second ATTACH_HAT item, there's no gurantee it will fit in our new section in which case it will default to the "main" section.
    // So instead of a character spawning with both a helmet and glasses, you might end up with a character that spawns with two helmets and an empty glasses section.
    //
    // 
    // Игра уже подбирает предметы для слотов ATTACH_BELT и ATTACH_HAT из списка «clothing», 
    // поэтому для этих разделов не требуется никаких особых действий — разве что мы захотим, 
    // чтобы игра могла одновременно заполнять как исходные слоты для головных уборов и поясов, 
    // так и наши новые слоты (что потребует дополнительной настройки). 
    // 
    // Если мы хотим задействовать и стандартные, и новые слоты, понадобится дополнительная логика для определения того, 
    // какой предмет в какой слот попадет. Например, допустим, у нас есть шаблон персонажа, 
    // который может появиться в игре одновременно со шлемом и очками (и то, и другое использует слот ATTACH_HAT);
    // 
    // когда мы «выбираем» второй предмет для слота ATTACH_HAT,
    // нет гарантии, что он поместится именно в наш новый слот, — в противном случае он автоматически попадет в «основной» слот.
    // В итоге вместо персонажа со шлемом и очками вы можете получить персонажа с двумя шлемами и пустым слотом для очков.
    const int count = (int)(sizeof(extraSlots) / sizeof(extraSlots[0]));
    for (int i = 0; i < count; ++i)
    {
        GameData* item = _chooseClothingItemFromList_orig(dataList, listName, extraSlots[i], race);

        if (item)
        {
            lektor_push_back(gear, item);
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------

template<typename T>
void lektor_push_back(lektor<T>& lek, const T& val)
{
    if (lek.count >= lek.maxSize)
    {
        uint32_t newMax = lek.maxSize == 0 ? 4 : lek.maxSize * 2;

        T* newStuff = (T*)Ogre::AllocatedObject<
            Ogre::CategorisedAllocPolicy<Ogre::MEMCATEGORY_GENERAL>
        >::operator new(newMax * sizeof(T));

        if (lek.stuff)
        {
            memcpy(newStuff, lek.stuff, lek.count * sizeof(T));
            Ogre::AllocatedObject<
                Ogre::CategorisedAllocPolicy<Ogre::MEMCATEGORY_GENERAL>
            >::operator delete(lek.stuff);
        }

        lek.stuff = newStuff;
        lek.maxSize = newMax;
    }

    lek.stuff[lek.count++] = val;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------
