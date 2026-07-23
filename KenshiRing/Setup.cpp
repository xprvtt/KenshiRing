#include "SetupMacrosHelper.h"

//-----------------------------------------------------------------------------------------------------------------------------------------------------------
// TODO: move to config.json?
void setup()
{
	KR_DEBUG_LOG_L8("Start of mod configuration");

	KR_DEBUG_LOG_L8("Add new slots");

	{ // place a new inventory section in Character

		// для безопасного добавление секций используйте макрос KRI_ADD_SECTION
		// Вы можете сколько угодно добавлять таким путем слоты 
		
		//чтобы держать совместимость с уже существующими модами, которые использовали EIS
		KRI_ADD_SECTION(ConfigIKR::PropertySectionKR("eyes_hats",     ConfigIKR::Size2D(3, 1), AttachSlot::ATTACH_HAT, true, false, true, 1));
		KRI_ADD_SECTION(ConfigIKR::PropertySectionKR("eyes_eyes",     ConfigIKR::Size2D(3, 1), AttachSlot::ATTACH_EYES,    true, false, true, 1));
		KRI_ADD_SECTION(ConfigIKR::PropertySectionKR("eyes_belts",    ConfigIKR::Size2D(3, 1), AttachSlot::ATTACH_BELT,    true, false, true, 1));
		KRI_ADD_SECTION(ConfigIKR::PropertySectionKR("neck",          ConfigIKR::Size2D(2, 2), AttachSlot::ATTACH_NECK,    true, false, true, 1));
		KRI_ADD_SECTION(ConfigIKR::PropertySectionKR("gloves",        ConfigIKR::Size2D(2, 2), AttachSlot::ATTACH_GLOVES,  true, false, true, 4));

		// Kenshi ring
		KRI_ADD_SECTION(ConfigIKR::PropertySectionKR("KR_hip",        ConfigIKR::Size2D(2, 2), AttachSlot::ATTACH_LEGS, true, false, true, 1));
		KRI_ADD_SECTION(ConfigIKR::PropertySectionKR("KR_lowerleg",   ConfigIKR::Size2D(2, 3), AttachSlot::ATTACH_BOOTS, true, false, true, 1));

		//KRI_ADD_SECTION(ConfigIKR::PropertySectionKR("KR_dagger",   ConfigIKR::Size2D(3, 1), AttachSlot::ATTACH_WEAPON, true, false, false, 1)); // нужно овверайднуть логику экипировки оружия
		KRI_ADD_SECTION(ConfigIKR::PropertySectionKR("KR_ears",       ConfigIKR::Size2D(3, 1), AttachSlot::ATTACH_HAIR, true, false, true, 1));
		KRI_ADD_SECTION(ConfigIKR::PropertySectionKR("KR_chain",      ConfigIKR::Size2D(3, 1), AttachSlot::ATTACH_NECK, true, false, true, 1));

		KRI_ADD_SECTION(ConfigIKR::PropertySectionKR("KR_shoulders",  ConfigIKR::Size2D(4, 3), AttachSlot::ATTACH_BACK, true, false, true, 1));
		KRI_ADD_SECTION(ConfigIKR::PropertySectionKR("KR_forearm",    ConfigIKR::Size2D(4, 2), AttachSlot::ATTACH_GLOVES, true, false, true, 1));
		KRI_ADD_SECTION(ConfigIKR::PropertySectionKR("KR_fingers",    ConfigIKR::Size2D(4, 2), AttachSlot::ATTACH_BEARD, true, false, true, 2));
		KRI_ADD_SECTION(ConfigIKR::PropertySectionKR("KR_toes",       ConfigIKR::Size2D(4, 2), AttachSlot::ATTACH_BEARD, true, false, true, 2));

		KRI_ADD_SECTION(ConfigIKR::PropertySectionKR("KR_pocket",     ConfigIKR::Size2D(2, 4), AttachSlot::ATTACH_NONE, false, true, true, 8));
	}
	
	//
	// для добавления своих эффектов предметов перейдите в Setup -> CustomEffects -> HookExtension.h
	// HookExtension.h содержит подробную инструкцию по добавлению
	//
	
	{ // CRITICALLY IMPORTANT SETTING - Please do not make changes if you don't know what you are doing.
		
		//armour
		KRI_SET_EXIST_GAME_SECTION(ConfigIKR::PropertySectionKR("head",  ConfigIKR::Size2D(4, 3), AttachSlot::ATTACH_HAT,   true, false, true, 1));
		KRI_SET_EXIST_GAME_SECTION(ConfigIKR::PropertySectionKR("armour",ConfigIKR::Size2D(4, 6), AttachSlot::ATTACH_BODY,  true, false, true, 1));
		KRI_SET_EXIST_GAME_SECTION(ConfigIKR::PropertySectionKR("legs",  ConfigIKR::Size2D(4, 5), AttachSlot::ATTACH_LEGS,  true, false, true, 1));
		KRI_SET_EXIST_GAME_SECTION(ConfigIKR::PropertySectionKR("boots", ConfigIKR::Size2D(4, 2), AttachSlot::ATTACH_BOOTS, true, false, true, 1));
		KRI_SET_EXIST_GAME_SECTION(ConfigIKR::PropertySectionKR("belt",  ConfigIKR::Size2D(2, 2), AttachSlot::ATTACH_BELT,  true, false, true, 1));
		KRI_SET_EXIST_GAME_SECTION(ConfigIKR::PropertySectionKR("shirt", ConfigIKR::Size2D(4, 2), AttachSlot::ATTACH_SHIRT, true, false, true, 1));

		//KRI_SET_EXIST_GAME_SECTION(ConfigIKR::PropertySectionKR("back", 
		//KRI_SET_EXIST_GAME_SECTION(ConfigIKR::PropertySectionKR("hip", 
		//KRI_SET_EXIST_GAME_SECTION(ConfigIKR::PropertySectionKR("backpacks_attach", 
		//KRI_SET_EXIST_GAME_SECTION(ConfigIKR::PropertySectionKR("main", 

		// вызовем геттеры чтобы заморозить конфигурацию инвентаря
		KR_RELEASE_LOG("Total new slots: " + SuppKR::toStringV100(KRI_GET_INSTANCE.getNewSections().size()));
		KR_RELEASE_LOG("Total game slots: " + SuppKR::toStringV100(KRI_GET_INSTANCE.getGameSections().size()));
		KRI_GET_INSTANCE.sortSections(); // необходимый костыль для формирования общего инвентаря

		KR_RELEASE_LOG("KenshiRing - BUILD DATE: " + std::string(__DATE__) + ", TIME: " + std::string(__TIME__))
	}

	KR_DEBUG_LOG_L8("End of mod configuration");
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------
