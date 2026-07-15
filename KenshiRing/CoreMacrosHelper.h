/* 
* 
* Макросы для упрощения работы с хуками
* 
*/

#pragma once

//---------------------------------------------------------------------------------------------------------------

// управление отладочной информацией
#define DEBUG 

//---------------------------------------------------------------------------------------------------------------

// TODO: move to config.json?
// HOOK enabled

//========================================

#define CHARACTER_NV_INIT
//#define CHARACTER_NV_UPDATE // производительность?
#define CHARACTER_NV_HITBYMELEEATTACK
#define CHARACTER_NV_GETTINGEATEN
//#define CHARACTER_ATTACKTARGET
#define CHARACTER_ISHOTYOU

//========================================

#define ROOTOBJECTFACTORY_CHOOSEMYCLOTHING
//#define ROOTOBJECTFACTORY_CHOOSECLOTHINGITEMFROMLIST // obsolete 

//========================================

#define INVENTORY_GETSECTIONOFTYPE

//========================================

//#define MEDICALSYSTEM_APPLYFIRSTAID 
#define MEDICALSYSTEM_APPLYDOCTORING
//#define MEDICALSYSTEM_APPLYRIGGING
//#define MEDICALSYSTEM_NV_PERIODICUPDATE  // производительность?

//========================================

//#define BASELAYOUT_INITIALISE

//========================================


//---------------------------------------------------------------------------------------------------------------

#define KR_RELEASE_LOG(__STRING_MESSAGE__) DebugLog(__STRING_MESSAGE__);
#define KR_ERROR_LOG(__STRING_MESSAGE__) ErrorLog(__STRING_MESSAGE__);

#ifdef DEBUG
	#define KR_DEBUG_LOG_L1(__STRING_MESSAGE__)    DebugLog(__STRING_MESSAGE__) // KenshiRing.cpp
	#define KR_DEBUG_LOG_L2(__STRING_MESSAGE__)    DebugLog(__STRING_MESSAGE__) // Inventory.cpp
	#define KR_DEBUG_LOG_L3_1(__STRING_MESSAGE__)  DebugLog(__STRING_MESSAGE__) // MedicalSystem.cpp
	#define KR_DEBUG_LOG_L3_2(__STRING_MESSAGE__)  DebugLog(__STRING_MESSAGE__) // MedicalSystem.cpp
	#define KR_DEBUG_LOG_L4(__STRING_MESSAGE__)    DebugLog(__STRING_MESSAGE__) // RootObjectFactory.cpp
	#define KR_DEBUG_CODE_L4(__DEBUG_CODE__)       __DEBUG_CODE__;              // RootObjectFactory.cpp
	#define KR_DEBUG_LOG_L5(__STRING_MESSAGE__)    DebugLog(__STRING_MESSAGE__) // Character.cpp
	#define KR_DEBUG_LOG_L5_1(__STRING_MESSAGE__)  DebugLog(__STRING_MESSAGE__) // Character.cpp
	#define KR_DEBUG_LOG_L5_2(__STRING_MESSAGE__)  DebugLog(__STRING_MESSAGE__) // Character.cpp
	#define KR_DEBUG_LOG_L5_3(__STRING_MESSAGE__)  DebugLog(__STRING_MESSAGE__) // Character.cpp
	#define KR_DEBUG_LOG_L5_4(__STRING_MESSAGE__)  DebugLog(__STRING_MESSAGE__) // Character.cpp
	#define KR_DEBUG_LOG_L6(__STRING_MESSAGE__)    DebugLog(__STRING_MESSAGE__) // BaseLayout.cpp
	#define KR_DEBUG_LOG_L7(__STRING_MESSAGE__)    DebugLog(__STRING_MESSAGE__) // InventoryKR.h
	#define KR_DEBUG_LOG_L8(__STRING_MESSAGE__)    DebugLog(__STRING_MESSAGE__) // Setup.cpp
	#define KR_DEBUG_LOG_L9(__STRING_MESSAGE__)    DebugLog(__STRING_MESSAGE__) // HookExtension.h
	#define KR_DEBUG_LOG_L10(__STRING_MESSAGE__)   DebugLog(__STRING_MESSAGE__) // ConfigHookExtension.h
	#define KR_DEBUG_CODE_L10(__DEBUG_CODE__);      __DEBUG_CODE__;             // ConfigHookExtension.h
	#define KR_DEBUG_LOG_L11(__STRING_MESSAGE__)   DebugLog(__STRING_MESSAGE__) // available
	#define KR_DEBUG_LOG_L12(__STRING_MESSAGE__)   DebugLog(__STRING_MESSAGE__) // available
#endif


//---------------------------------------------------------------------------------------------------------------
// define off

#ifndef KR_DEBUG_LOG_L1
#define KR_DEBUG_LOG_L1(__STRING_MESSAGE__)   ((void)0);// KenshiRing.cpp
#endif

#ifndef KR_DEBUG_LOG_L2
#define KR_DEBUG_LOG_L2(__STRING_MESSAGE__)   ((void)0);// Inventory.cpp
#endif

#ifndef KR_DEBUG_LOG_L3_1
#define KR_DEBUG_LOG_L3_1(__STRING_MESSAGE__) ((void)0);// MedicalSystem.cpp
#endif

#ifndef KR_DEBUG_LOG_L3_2
#define KR_DEBUG_LOG_L3_2(__STRING_MESSAGE__) ((void)0);// MedicalSystem.cpp
#endif

#ifndef KR_DEBUG_LOG_L4
#define KR_DEBUG_LOG_L4(__STRING_MESSAGE__)   ((void)0);// RootObjectFactory.cpp
#endif

#ifndef KR_DEBUG_CODE_L4
#define KR_DEBUG_CODE_L4(__DEBUG_CODE__)      ((void)0);// RootObjectFactory.cpp
#endif

#ifndef KR_DEBUG_LOG_L5
#define KR_DEBUG_LOG_L5(__STRING_MESSAGE__)   ((void)0);// Character.cpp
#endif

#ifndef KR_DEBUG_LOG_L5_1
#define KR_DEBUG_LOG_L5_1(__STRING_MESSAGE__) ((void)0);// Character.cpp
#endif

#ifndef KR_DEBUG_LOG_L5_2
#define KR_DEBUG_LOG_L5_2(__STRING_MESSAGE__) ((void)0);// Character.cpp
#endif

#ifndef KR_DEBUG_LOG_L5_3
#define KR_DEBUG_LOG_L5_3(__STRING_MESSAGE__) ((void)0);// Character.cpp
#endif

#ifndef KR_DEBUG_LOG_L5_4
#define KR_DEBUG_LOG_L5_4(__STRING_MESSAGE__) ((void)0);// Character.cpp
#endif

#ifndef KR_DEBUG_LOG_L6
#define KR_DEBUG_LOG_L6(__STRING_MESSAGE__)   ((void)0);// BaseLayout.cpp
#endif

#ifndef KR_DEBUG_LOG_L7
#define KR_DEBUG_LOG_L7(__STRING_MESSAGE__)   ((void)0);// InventoryKR.h
#endif

#ifndef KR_DEBUG_LOG_L8
#define KR_DEBUG_LOG_L8(__STRING_MESSAGE__)   ((void)0);// Setup.cpp
#endif

#ifndef KR_DEBUG_LOG_L9
#define KR_DEBUG_LOG_L9(__STRING_MESSAGE__)   ((void)0);// HookExtension.h
#endif

#ifndef KR_DEBUG_LOG_L10
#define KR_DEBUG_LOG_L10(__STRING_MESSAGE__)  ((void)0);// ConfigHookExtension.h
#endif

#ifndef KR_DEBUG_CODE_L10
#define KR_DEBUG_CODE_L10(__DEBUG_CODE__)     ((void)0);// ConfigHookExtension.h
#endif

#ifndef KR_DEBUG_LOG_L11
#define KR_DEBUG_LOG_L11(__STRING_MESSAGE__)  ((void)0);
#endif

#ifndef KR_DEBUG_LOG_L12
#define KR_DEBUG_LOG_L12(__STRING_MESSAGE__)  ((void)0);
#endif

//---------------------------------------------------------------------------------------------------------------
