#pragma once

#include "CoreKenshiRing.h"
#include "HookExtension.h"
#include "SetupMacrosHelper.h"

//-----------------------------------------------------------------------------------------------------------------------------------------------

void NVInitHook(Character* self);
extern void (*NVInitOrig)(Character* self);


//-----------------------------------------------------------------------------------------------------------------------------------------------

GameData* chooseClothingItemFromListHook(GameData* dataList, const std::string& listName, AttachSlot sectionAttach, RaceData* race);
extern GameData* (*chooseClothingItemFromListOrig)(GameData* dataList, const std::string& listName, AttachSlot sectionAttach, RaceData* race);

//-----------------------------------------------------------------------------------------------------------------------------------------------
 
void chooseMyClothingHook(lektor<GameData*>& gear, GameData* dataList, const std::string& listName, RaceData* race, bool noShoes);
extern void (*chooseMyClothingOrig)(lektor<GameData*>& gear, GameData* dataList, const std::string& listName, RaceData* race, bool noShoes);

//-----------------------------------------------------------------------------------------------------------------------------------------------

InventorySection* getSectionOfTypeHook(Inventory* self, AttachSlot type);
extern InventorySection* (*getSectionOfTypeOrig)(Inventory* self, AttachSlot type);

//-----------------------------------------------------------------------------------------------------------------------------------------------

HitMaterialType NVHitByMeleeAttackHook(Character* self, CutDirection dir, Damages& damage, Character* who, CombatTechniqueData* attack, int comboID);
extern HitMaterialType (*NVHitByMeleeAttackOrig)(Character* self, CutDirection dir, Damages& damage, Character* who, CombatTechniqueData* attack, int comboID);

//-----------------------------------------------------------------------------------------------------------------------------------------------

bool NVGettingEatenHook(Character* self, float amount, Character* eater);
extern bool (*NVGettingEatenOrig)(Character* self, float amount, Character* eater);

//-----------------------------------------------------------------------------------------------------------------------------------------------

void attackTargetHook(Character* self, Character* who);
extern void (*attackTargetOrig)(Character* self, Character* who);

//-----------------------------------------------------------------------------------------------------------------------------------------------

bool applyFirstAidHook(MedicalSystem* self, float skill, Item* equipment, float frameTime, Character* who);
extern bool (*applyFirstAidOrig)(MedicalSystem*, float, Item*, float, Character*);

//-----------------------------------------------------------------------------------------------------------------------------------------------

bool applyDoctoringHook(MedicalSystem* self, float skill, Item* equipment, float frameTIME, Character* who);
extern bool (*applyDoctoringOrig)(MedicalSystem*, float, Item*, float, Character*);

//-----------------------------------------------------------------------------------------------------------------------------------------------

bool applyRiggingHook(MedicalSystem* self, float skill, Item* equipment, float frameTIME);
extern bool (*applyRiggingOrig)(MedicalSystem*, float, Item*, float);

//-----------------------------------------------------------------------------------------------------------------------------------------------

void NVPeriodicUpdateHook(MedicalSystem* self);
extern void (*NVPeriodicUpdateOrig)(MedicalSystem*);

//-----------------------------------------------------------------------------------------------------------------------------------------------

extern void (*NVUpdateOrig)(Character* self);
void NVUpdateHook(Character* self);

//-----------------------------------------------------------------------------------------------------------------------------------------------

extern bool (*iShotYouOrig)(Character* self, Character* attacker, Harpoon* poon, bool onPurpose);
bool iShotYouHook(Character* self, Character* attacker, Harpoon* poon, bool onPurpose);

//-----------------------------------------------------------------------------------------------------------------------------------------------

extern void (*constructorOrig)(InventoryLayout* self, const std::string& file);
void constructorHook(InventoryLayout* self, const std::string& file);

//-----------------------------------------------------------------------------------------------------------------------------------------------
