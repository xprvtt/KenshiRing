//------------------------------------------------------
//
// Макросы для упрощения работы и безопасной инициализации мода
// 
//------------------------------------------------------

#include "InventoryKR.h"

//------------------------------------------------------
// 
//	Kenshi Ring Inventory
//
//------------------------------------------------------
 
// добавление новой секции инвентаря 
// __PROPERTY_SECTION_KR__ = ConfigIKR::PropertySectionKR
#define KRI_ADD_SECTION(__PROPERTY_SECTION_KR__) InventoryKR::instance().manualAddSection(__PROPERTY_SECTION_KR__);

//__PROPERTY_SECTION_KR__ = ConfigIKR::PropertySectionKR
#define KRI_SET_EXIST_GAME_SECTION(__PROPERTY_SECTION_KR__) InventoryKR::instance().setGameSection(__PROPERTY_SECTION_KR__)

#define KRI_GET_INSTANCE InventoryKR::instance()

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
