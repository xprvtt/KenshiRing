#include "HookKR.h"

void (*constructorOrig)(InventoryLayout* self, const std::string& file) = nullptr;
void constructorHook(InventoryLayout* self, const std::string& file)
{
    KR_DEBUG_LOG_L11("Call - constructorHook");

    file == "Kenshi_InventoryCharacterWindow.layout" ? constructorOrig(self, "KenshiRing_InventoryCharacterWindow.layout") : constructorOrig(self, file);

    KR_DEBUG_LOG_L11("Exit - constructorHook");
}