#pragma once

#include "CoreKenshiRing.h"
#include "HookExtension.h"
#include "SetupMacrosHelper.h"

//-----------------------------------------------------------------------------------------------------------------------------------------------

// We hook the Character::_NV_init function to ensure our extra inventory sections are created early enough to be available for all characters.
void Character_NV_init_hook(Character* thisptr);
extern void (*Character_NV_init_orig)(Character* thisptr);

//-----------------------------------------------------------------------------------------------------------------------------------------------

// We include this hook to ensure that we have a pointer to the original _chooseClothingItemFromList function, which we need to call from our chooseMyClothing_hook function.
//GameData* _chooseClothingItemFromList_hook(GameData* dataList, const std::string& listName, AttachSlot sectionAttach, RaceData* race);
//extern GameData* (*_chooseClothingItemFromList_orig)(GameData* dataList, const std::string& listName, AttachSlot sectionAttach, RaceData* race);

//-----------------------------------------------------------------------------------------------------------------------------------------------
 
// Мы перехватываем функцию chooseMyClothing, чтобы добавить предметы из наших дополнительных секций инвентаря в тот момент, когда игра генерирует одежду для персонажа.
// Стандартная игра ищет только те предметы одежды, которые относятся к слотам ATTACH_HAT, ATTACH_BELT, ATTACH_BODY, ATTACH_LEGS и ATTACH_SHIRT + ATTACH_BOOTS.
// Перехват этой функции позволяет нам также находить предметы для слотов
// и включать их в список одежды персонажа.
void chooseMyClothing_hook(lektor<GameData*>& gear, GameData* dataList, const std::string& listName, RaceData* race, bool noShoes);
extern void (*chooseMyClothing_orig)(lektor<GameData*>& gear, GameData* dataList, const std::string& listName, RaceData* race, bool noShoes);

//-----------------------------------------------------------------------------------------------------------------------------------------------

// We hook the Inventory::getSectionOfType function because the game uses that function to determine which inventory section to use for equipping items.
// Basically the game will try and equip items that won't fit in our new sections and this causes an issue with Array2d out-of-range errors and crashes.
// 
// Мы перехватываем функцию Inventory::getSectionOfType, так как игра использует её для определения того, какой раздел инвентаря задействовать при экипировке предметов.
// По сути, игра пытается экипировать предметы, которые не помещаются в наши новые разделы, что приводит к ошибкам выхода за границы массива (Array2d) и аварийному завершению работы.
InventorySection* getSectionOfType_hook(Inventory* thisptr, AttachSlot type);
extern InventorySection* (*getSectionOfType_orig)(Inventory* thisptr, AttachSlot type);

//-----------------------------------------------------------------------------------------------------------------------------------------------

// There are a few different ways we can create the MyGUI widgets needed for our extra inventory sections, but this is the one that I found to be the most reliable.
// Other methods put your layout file at risk of being overwritten by the game or other mods (specifically UI mods) and that always leads to the game crashing.
// You can tell the user to place the mod in a specific load order position to avoid this, but that isn't ideal, especially with some users having 200+ mods.
// 
// Существует несколько способов создания виджетов MyGUI, необходимых для дополнительных разделов инвентаря, но этот вариант оказался самым надежным.
// При использовании других методов возникает риск перезаписи вашего файла разметки самой игрой или другими модами (в частности, модификациями интерфейса), что неизбежно приводит к вылету игры.
// Конечно, можно попросить пользователя разместить мод на определенной позиции в порядке загрузки, чтобы избежать этой проблемы, 
// но такой подход нельзя назвать идеальным — особенно учитывая, что у некоторых игроков установлено более 200 модов.
static void baseLayout_initialise_hook(wraps::BaseLayout* thisptr, const std::string& layout, MyGUI::Widget* parent, bool _throw, bool _createFakeWidgets);
extern void (*BaseLayout_initialise_orig)(wraps::BaseLayout*, const std::string&, MyGUI::Widget*, bool, bool);

//-----------------------------------------------------------------------------------------------------------------------------------------------

HitMaterialType _NV_hitByMeleeAttack_hook(Character* thsptr, CutDirection dir, Damages& damage, Character* who, CombatTechniqueData* attack, int comboID);
extern HitMaterialType (*_NV_hitByMeleeAttack_orig)(Character* thsptr, CutDirection dir, Damages& damage, Character* who, CombatTechniqueData* attack, int comboID);

//-----------------------------------------------------------------------------------------------------------------------------------------------

bool Character_NV_gettingEaten_hook(Character* thsptr, float amount, Character* eater);
extern bool (*Character_NV_gettingEaten_orig)(Character* thsptr, float amount, Character* eater);

//-----------------------------------------------------------------------------------------------------------------------------------------------

void Character_attackTarget_hook(Character* thsptr, Character* who);
extern void (*Character_attackTarget_orig)(Character* thsptr, Character* who);

//-----------------------------------------------------------------------------------------------------------------------------------------------

bool MedicalSystem_applyFirstAid_hook(MedicalSystem* thsptr, float skill, Item* equipment, float frameTIME, Character* who);
extern bool (*MedicalSystem_applyFirstAid_orig)(MedicalSystem*, float, Item*, float, Character*);

//-----------------------------------------------------------------------------------------------------------------------------------------------

bool MedicalSystem_applyDoctoring_hook(MedicalSystem* thsptr, float skill, Item* equipment, float frameTIME, Character* who);
extern bool (*MedicalSystem_applyDoctoring_orig)(MedicalSystem*, float, Item*, float, Character*);

//-----------------------------------------------------------------------------------------------------------------------------------------------

bool MedicalSystem_applyRigging_hook(MedicalSystem* thsptr, float skill, Item* equipment, float frameTIME);
extern bool (*MedicalSystem_applyRigging_orig)(MedicalSystem*, float, Item*, float);

//-----------------------------------------------------------------------------------------------------------------------------------------------

void MedicalSystem_NV_periodicUpdate_hook(MedicalSystem* thsptr);
extern void (*MedicalSystem_NV_periodicUpdate_orig)(MedicalSystem*);

//-----------------------------------------------------------------------------------------------------------------------------------------------

extern void (*Character_NV_update_orig)(Character*);
void Character_NV_update_hook(Character* thsptr);

//-----------------------------------------------------------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------------------------------------------------------
extern bool (*Character_iShotYou_orig)(Character* thsptr, Character* attacker, Harpoon* poon, bool onPurpose);
bool Character_iShotYou_hook(Character* thsptr, Character* attacker, Harpoon* poon, bool onPurpose);