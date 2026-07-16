#pragma once

#include "CoreKenshiRing.h"
#include "HookExtension.h"
#include "SetupMacrosHelper.h"

//-----------------------------------------------------------------------------------------------------------------------------------------------

void _NV_init_hook(Character* thisptr);
extern void (*Character_NV_init_orig)(Character* thisptr);

//-----------------------------------------------------------------------------------------------------------------------------------------------

GameData* _chooseClothingItemFromList_hook(GameData* dataList, const std::string& listName, AttachSlot sectionAttach, RaceData* race);
extern GameData* (*_chooseClothingItemFromList_orig)(GameData* dataList, const std::string& listName, AttachSlot sectionAttach, RaceData* race);

//-----------------------------------------------------------------------------------------------------------------------------------------------
 
void chooseMyClothing_hook(lektor<GameData*>& gear, GameData* dataList, const std::string& listName, RaceData* race, bool noShoes);
extern void (*chooseMyClothing_orig)(lektor<GameData*>& gear, GameData* dataList, const std::string& listName, RaceData* race, bool noShoes);

//-----------------------------------------------------------------------------------------------------------------------------------------------

InventorySection* getSectionOfType_hook(Inventory* thisptr, AttachSlot type);
extern InventorySection* (*getSectionOfType_orig)(Inventory* thisptr, AttachSlot type);

//-----------------------------------------------------------------------------------------------------------------------------------------------

HitMaterialType _NV_hitByMeleeAttack_hook(Character* thsptr, CutDirection dir, Damages& damage, Character* who, CombatTechniqueData* attack, int comboID);
extern HitMaterialType (*_NV_hitByMeleeAttack_orig)(Character* thsptr, CutDirection dir, Damages& damage, Character* who, CombatTechniqueData* attack, int comboID);

//-----------------------------------------------------------------------------------------------------------------------------------------------

bool _NV_gettingEaten_hook(Character* thsptr, float amount, Character* eater);
extern bool (*_NV_gettingEaten_orig)(Character* thsptr, float amount, Character* eater);

//-----------------------------------------------------------------------------------------------------------------------------------------------

void attackTarget_hook(Character* thsptr, Character* who);
extern void (*attackTarget_orig)(Character* thsptr, Character* who);

//-----------------------------------------------------------------------------------------------------------------------------------------------

bool applyFirstAid_hook(MedicalSystem* thsptr, float skill, Item* equipment, float frameTIME, Character* who);
extern bool (*applyFirstAid_orig)(MedicalSystem*, float, Item*, float, Character*);

//-----------------------------------------------------------------------------------------------------------------------------------------------

bool applyDoctoring_hook(MedicalSystem* thsptr, float skill, Item* equipment, float frameTIME, Character* who);
extern bool (*applyDoctoring_orig)(MedicalSystem*, float, Item*, float, Character*);

//-----------------------------------------------------------------------------------------------------------------------------------------------

bool applyRigging_hook(MedicalSystem* thsptr, float skill, Item* equipment, float frameTIME);
extern bool (*applyRigging_orig)(MedicalSystem*, float, Item*, float);

//-----------------------------------------------------------------------------------------------------------------------------------------------

void _NV_periodicUpdate_hook(MedicalSystem* thsptr);
extern void (*_NV_periodicUpdate_orig)(MedicalSystem*);

//-----------------------------------------------------------------------------------------------------------------------------------------------

extern void (*_NV_update_orig)(Character*);
void _NV_update_hook(Character* thsptr);

//-----------------------------------------------------------------------------------------------------------------------------------------------

extern bool (*iShotYou_orig)(Character* thsptr, Character* attacker, Harpoon* poon, bool onPurpose);
bool _iShotYou_hook(Character* thsptr, Character* attacker, Harpoon* poon, bool onPurpose);

//-----------------------------------------------------------------------------------------------------------------------------------------------
