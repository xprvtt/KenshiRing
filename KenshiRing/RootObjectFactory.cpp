#include "HookKR.h"
#include <kenshi/RaceData.h>
#include <kenshi/GameData.h>

//-----------------------------------------------------------------------------------------------------------------------------------------------------------

struct secondInfoCloth
{
    ConfigIKR::Size2D m_size;
    int m_quantity;
    int m_chance;

    secondInfoCloth() : m_quantity(0), m_chance(0) {};
    secondInfoCloth(int q, int c, int width, int height) : m_quantity(q), m_chance(c), m_size(width, height) {};
};

//-----------------------------------------------------------------------------------------------------------------------------------------------------------

std::unordered_map<std::string, std::unordered_map<GameDataReference*, secondInfoCloth*> >selectSuitableClothesForSections(const std::unordered_map<GameDataReference*, secondInfoCloth>& validItemPull, const std::set<ConfigIKR::PropertySectionKR>& sortSectionsType, const RaceData* race);
void fillSections(lektor<GameData*>& lekGearOutput, std::unordered_map<std::string, std::unordered_map<GameDataReference*, secondInfoCloth*> >& clothesForAllSection, const std::set<ConfigIKR::PropertySectionKR>& sortSectionsType);

//-----------------------------------------------------------------------------------------------------------------------------------------------------------

// off
GameData* (*chooseClothingItemFromListOrig)(GameData* dataList, const std::string& listName, AttachSlot sectionAttach, RaceData* race) = nullptr;
GameData* chooseClothingItemFromListHook(GameData* dataList, const std::string& listName, AttachSlot sectionAttach, RaceData* race)
{
    return chooseClothingItemFromListOrig(dataList, listName, sectionAttach, race);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------

void overriddenChooseClothingItemFromList(lektor<GameData*>& gear, GameData* dataList, const std::string& listName, const RaceData* race, AttachSlot valid);

void (*chooseMyClothingOrig)(lektor<GameData*>& gear, GameData* dataList, const std::string& listName, RaceData* race, bool noShoes) = nullptr;
void chooseMyClothingHook(lektor<GameData*>& gear, GameData* dataList, const std::string& listName, RaceData* race, bool noShoes)
{
    KR_DEBUG_LOG_L4("Call - chooseMyClothingHook");

    if (listName != "clothing")
    {
        KR_DEBUG_LOG_L4("Exit - chooseMyClothingHook - listName != clothing : " + listName);
        return;
    }

    // для удобства в сортированном виде
    AttachSlot validSectionsInvertory[12];
    int count = 0;

    validSectionsInvertory[count++] = ATTACH_BACK;
    validSectionsInvertory[count++] = ATTACH_HAIR;
    if (!race || !race->noHats)
    {
        validSectionsInvertory[count++] = ATTACH_HAT;
    }
    validSectionsInvertory[count++] = ATTACH_EYES;
    validSectionsInvertory[count++] = ATTACH_BODY;
    validSectionsInvertory[count++] = ATTACH_LEGS;
    if (!race || !race->noShirts)
    {
        validSectionsInvertory[count++] = ATTACH_SHIRT;
    }
    if (!race || !noShoes && !race->noShoes)
    {
        validSectionsInvertory[count++] = ATTACH_BOOTS;
    }
    validSectionsInvertory[count++] = ATTACH_GLOVES;
    validSectionsInvertory[count++] = ATTACH_NECK;
    validSectionsInvertory[count++] = ATTACH_BEARD;
    validSectionsInvertory[count++] = ATTACH_BELT;

    //ATTACH_NONE,      valid - all item
    //ATTACH_BACKPACK,  no checking
    //ATTACH_WEAPON,    no valid attach
    //ATTACH_LEFT_ARM,  no valid attach
    //ATTACH_RIGHT_ARM, no valid attach
    //ATTACH_LEFT_LEG,  no valid attach
    //ATTACH_RIGHT_LEG, no valid attach

    KR_DEBUG_LOG_L4("SELECTING ITEMS FOR A RACE: " + race->data->name);

    for (int it = 0; it < count; ++it)
    {
        // ванильное игровое поведение
        // GameData* item = chooseClothingItemFromListOrig(dataList, listName, *section, race);
        // if (item)
        // {
        //     SuppKR::lektorPushBack(gear, item);
        // }
        overriddenChooseClothingItemFromList(gear, dataList, listName, race, validSectionsInvertory[it]);
    }

    KR_DEBUG_LOG_L4("GEAR: ");
    KR_DEBUG_CODE_L4
    (
        for (uint32_t i = 0; i < gear.size(); i++)
        {
            KR_DEBUG_LOG_L4(gear[i]->name);
        }
    );
    KR_DEBUG_LOG_L4("Exit - chooseMyClothingHook");
    KR_DEBUG_LOG_L4("----------------------------------------------------------------");
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------

void overriddenChooseClothingItemFromList(lektor<GameData*>& lekGearOutput, GameData* dataList, const std::string& listName, const RaceData* race, AttachSlot attachSlot)
{
    // оптимизация (?)
    if (dataList == nullptr) 
    {
        KR_DEBUG_LOG_L4("Exit - overriddenChooseClothingItemFromList - dataList.empty()");
        return;
    }
    // пулл всех предметов для секций типа AttachSlot
    std::unordered_map<GameDataReference*, secondInfoCloth> validItemPull;

    // добавляем все предметы для слота
    Ogre::vector<GameDataReference>::type& listItem = dataList->objectReferences[listName];


    KR_DEBUG_LOG_L4("\tITEM PULL FOR ATTACH: " + SuppKR::toStringV100(attachSlot));
    for (size_t it = 0; it < listItem.size(); it++)
    {
        GameDataReference& item = listItem[it];

        if (item.ptr == nullptr)
        {
            KR_ERROR_LOG("Item without GameData -> item.ptr == nullptr, Number GameDataReference: " + SuppKR::toStringV100(it) + ", SID: " + item.sid + ", TRIPLE VALUE: " + SuppKR::toStringV100(item.values[0]) + ", " + SuppKR::toStringV100(item.values[1]) + ", " + SuppKR::toStringV100(item.values[2]));
            continue;
        }
        if (item.ptr->idata["slot"] == attachSlot)
        {
            const int quantity = item.values[0];
            const int chance = item.values[1];

            if (quantity < 0)
            {
                // секции типа attachSlot НЕ БУДУТ задействованы в экипировке
                return;
            }
            else if (quantity == 0)
            {
                // ванильное поведение
                continue; // предмет есть в списке, не участвует

                // кастомное
                //quantity = INT_MIN; если включено, то секцию может занять "воздух"
            }
            validItemPull[&item] = secondInfoCloth(quantity, chance, item.ptr->idata["inventory footprint width"], item.ptr->idata["inventory footprint height"]);
        }
    }
    if (validItemPull.empty())
    {
        KR_DEBUG_LOG_L4("Exit - overriddenChooseClothingItemFromList - validItemPull.empty()");
        return;
    }
    // секции типа attachSlot размещены (должны быть)  в порядке возрастания размера
    const auto& sortSectionsType = KRI_GET_INSTANCE.getAllSectionForAttach(attachSlot);
    KR_LOGD_CHECKPOINT;

    // шаг 1. выбираем всю подходящую одежду для каждой секций 
    // секции sortSectionsType должны быть гарантированно размещены в порядке возрастания размера,
    // для того чтобы одежда гарантированно подобралась для всех секций, с которых и начнется заполнение
    auto clothesForAllSection = selectSuitableClothesForSections(validItemPull, sortSectionsType, race);
    KR_LOGD_CHECKPOINT;

    // шаг 2 заполнить секции подходящими предметами
    fillSections(lekGearOutput, clothesForAllSection, sortSectionsType);
    KR_LOGD_CHECKPOINT;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------

std::unordered_map<std::string, std::unordered_map<GameDataReference*, secondInfoCloth*> >selectSuitableClothesForSections( const std::unordered_map<GameDataReference*, secondInfoCloth>& validItemPull, const std::set<ConfigIKR::PropertySectionKR>& sortSectionsType, const RaceData* race)
{
    // оптимизация (?)

    std::unordered_map<std::string, std::unordered_map<GameDataReference*, secondInfoCloth*> > clothesForAllSection;

    KR_DEBUG_LOG_L4("\t\t|_ NUMBER OF SECTIONS FOR ATTACH: " + SuppKR::toStringV100(sortSectionsType.size()));
    for (auto currentSection = sortSectionsType.begin(); currentSection != sortSectionsType.end(); ++currentSection)
    {
        const ConfigIKR::Size2D& sizeSection = currentSection->m_sizeSection;
        const std::string& nameSection = currentSection->m_name;

        KR_DEBUG_LOG_L4("\t\t\t|_ NAME SECTION: " + nameSection + " | SIZE: " + SuppKR::toStringV100(sizeSection.m_width) + " / " + SuppKR::toStringV100(sizeSection.m_height));
        KR_DEBUG_LOG_L4("\t\t\t   SUITABLE ITEMS FOR THE SECTION:");

        for (auto itItem = validItemPull.begin(); itItem != validItemPull.end(); ++itItem)
        {
            GameDataReference* currentItem = itItem->first;
            secondInfoCloth* infoItem = const_cast<secondInfoCloth*>(&itItem->second);

            auto& racesListExclude = currentItem->ptr->objectReferences["races exclude"];
            if (racesListExclude.size() && race && race->data)
            {
                for (auto itRace = racesListExclude.begin(); itRace != racesListExclude.end(); ++itRace)
                {
                    GameDataReference& currentItemRacaExclude = *itRace;
                    if (currentItemRacaExclude.ptr->stringID == race->data->stringID)
                    {
                        continue; // -> next - мы находимся в списке запрещенных рас
                    }
                }
            }
            auto& racesList = currentItem->ptr->objectReferences["races"];
            if (racesList.size() && race && race->data)
            {
                for (auto itRace = racesList.begin(); itRace != racesList.end(); ++itRace)
                {
                    GameDataReference& currentItemRaca = *itRace;
                    if (currentItemRaca.ptr->stringID == race->data->stringID)
                    {
                        if (currentItem->ptr->idata["inventory footprint width"] <= sizeSection.m_width && currentItem->ptr->idata["inventory footprint height"] <= sizeSection.m_height)
                        {
                            clothesForAllSection[nameSection][currentItem] = infoItem;
                            // мы находимся в списке разрешенных рас и можем иметь этот предмет
                        }
                    }
                }
            }
            else
            {
                if (currentItem->ptr->idata["inventory footprint width"] <= sizeSection.m_width && currentItem->ptr->idata["inventory footprint height"] <= sizeSection.m_height)
                {
                    KR_DEBUG_LOG_L4("\t\t\t\t+  " + currentItem->ptr->name + " | Quantity: " + SuppKR::toStringV100(infoItem->m_quantity) + " | Size: " + SuppKR::toStringV100(infoItem->m_size.m_width) + "/" + SuppKR::toStringV100(infoItem->m_size.m_height));
                    clothesForAllSection[nameSection][currentItem] = infoItem;
                }
            }
        }
    }
    return clothesForAllSection;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------

void fillSections(lektor<GameData*>& lekGearOutput, std::unordered_map<std::string, std::unordered_map<GameDataReference*, secondInfoCloth*> >& clothesForAllSection, const std::set<ConfigIKR::PropertySectionKR>& sortSectionsType)
{
    // проход по секциям
    for (std::unordered_map<std::string, std::unordered_map<GameDataReference*, secondInfoCloth*> >::iterator iterSection = clothesForAllSection.begin(); iterSection != clothesForAllSection.end(); ++iterSection)
    {
        auto& currentClothes = iterSection->second;
        auto currentSection = sortSectionsType.begin();

        // костыль, вместо того чтобы не использовать ConfigIKR::PropertySectionKR как ключ к clothesForAllSection
        // гарантированно есть секция иначе бы цикл не начался
        for (; currentSection != sortSectionsType.end(); ++currentSection)
        {
            if (currentSection->m_name == iterSection->first)
            {
                KR_DEBUG_LOG_L4("\t\t\t\t\t|_ FOR SECTION: " + currentSection->m_name + " Limit " + SuppKR::toStringV100(currentSection->m_limit));
                break;
            }
        }
        if (currentSection == sortSectionsType.end())
        {
            continue;
        }
        // на следующем этапе заполняем секцию изходя из лимита
        // и оставшегося размера, а сами предметы уже подобраны
        // не думаю, что стоит усложнять для максимальной компоновки предметов в секцию, ведь это будет убивать некоторый ванильный рандом и производительность

        // оставщийся размер у секции
        ConfigIKR::Container2D remainingSize(currentSection->m_sizeSection);

        // временный пул
        std::vector<GameData*> tmpPull;

        // проход по лимитам на кол-во предметов у секции
        for (int itLimit = 0; itLimit < currentSection->m_limit; ++itLimit)
        {
            // проверка на то, есть ли еще свободное место (?)
            // вероятно оно принесет больше вреда чем пользы, спискок одежды не будет составлять 100+ предметов, вместе с этим и размеры предметов разные
            //if (remainingSize.canPlace(ConfigIKR::Size2D(1,1))) 
            //{
            //    break;
            //}

            int totalWeightChanceForSection = 0;
            for (auto itClo = currentClothes.begin(); itClo != currentClothes.end(); ++itClo)
            {
                if (itClo->second->m_quantity > 0)
                {
                    totalWeightChanceForSection += itClo->second->m_chance;
                }
            }

            // вероятно предметов нет на выбор или же не осталось после выбора для секции
            if (totalWeightChanceForSection <= 0)
            {
                break;
            }

            // если отсутствует(ют) предмет(ы) с начальным m_quantity == 0 (обозначен как INT_MIN), предмет попадет в слот, вне зависимости от того какой у предмета шанс
            // в противном случае, если предметов несколько, предмет будет выбираться изходя из их шансов между ними
            int roll = SuppKR::fastRandom(totalWeightChanceForSection);

            // проход по всем предметам для текущей секции
            for (auto itAllItem = currentClothes.begin(); itAllItem != currentClothes.end(); ++itAllItem)
            {
                KR_DEBUG_LOG_L4("ITEM CURRENT - " + itAllItem->first->ptr->name);

                secondInfoCloth* itemInfo = itAllItem->second;

                if (roll < itemInfo->m_chance)
                {
                    if (itemInfo->m_quantity > 0) // предмет есть в пуле
                    {
                        if (remainingSize.place(itemInfo->m_size))
                        {
                            itemInfo->m_quantity--;
                            tmpPull.push_back(itAllItem->first->ptr);
                            KR_DEBUG_LOG_L4("\t\t\t\t\t\t|_ + " + itAllItem->first->ptr->name + " | Chance : " + SuppKR::toStringV100(itemInfo->m_chance) + " | Remaining quantity:" + SuppKR::toStringV100(itemInfo->m_quantity));
                            break;
                        }
                        //KR_DEBUG_LOG_L4("\t\t\t\t\t\t|_ - (Did not fit -> next) " + itAllItem->first->ptr->name + " | Chance : " + SuppKR::toStringV100(itemInfo->m_chance) + " | Remaining quantity:" + SuppKR::toStringV100(itemInfo->m_quantity));
                        continue; // предмет не поместился
                    }
                    else if (itemInfo->m_quantity == INT_MIN)  // не наступит, на данный момент отключен учет предметов с начальным quantity = 0
                    {
                        // всё же в секции могут находится предметы выбранные ранее, если у секции лимит >1
                        // поэтому нужен временный пул tmpPull + возврат из него
                        for (size_t itTmpPull = 0; itTmpPull < tmpPull.size(); itTmpPull++)
                        {
                            for (auto itReturnItem = currentClothes.begin(); itReturnItem != currentClothes.end(); ++itReturnItem)
                            {
                                if (tmpPull[itTmpPull] == itReturnItem->first->ptr)
                                {
                                    itReturnItem->second->m_quantity++;
                                }
                            }
                            //KR_DEBUG_LOG_L4("\t\t\t\t\t\t|_ - (No Item chance - clear tmp pull - return ITEM: ) " + itAllItem->first->ptr->name + " | Remaining quantity:" + SuppKR::toStringV100(itemInfo->m_quantity));
                        }
                        tmpPull.clear();    
                        itLimit = currentSection->m_limit; // выход из цикла лимитов для секции
                        break;                             // выход из цикла предметов -> переход на след. секцию
                    }                        
                    KR_DEBUG_LOG_L4("Item is not in the pull -> next");
                    continue; // чтобы не попасть в roll -= itemInfo->m_chance;
                }
                KR_DEBUG_CODE_L4(
                else
                {
                    //KR_DEBUG_LOG_L4("The item did not drop -> next");
                }
                )
                // без else иначе бы секция могла оказаться пустой даже если есть предметы под него
                roll -= itemInfo->m_chance;
            }
            // полукостыль, для lekGearOutput на случай если в секции выпадет вариант (itemInfo->m_quantity == INT_MIN),
            // что будет означать, что в секции НЕ ДОЛЖНО быть предметов
            for (size_t itPush = 0; itPush < tmpPull.size(); itPush++)
            {
                SuppKR::lektorPushBack(lekGearOutput, tmpPull[itPush]);
            }
            tmpPull.clear();
        }
    }
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------
