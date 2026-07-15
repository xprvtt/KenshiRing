#include "HookKR.h"

void (*BaseLayout_initialise_orig)(wraps::BaseLayout*, const std::string&, MyGUI::Widget*, bool, bool) = nullptr;

//-----------------------------------------------------------------------------------------------------------------------------------------------------------

static void baseLayout_initialise_hook(wraps::BaseLayout* thisptr, const std::string& layout, MyGUI::Widget* parent, bool _throw, bool _createFakeWidgets)
{
    if (layout == "Kenshi_InventoryCharacterWindow.layout")
    {
        BaseLayout_initialise_orig(thisptr, "Custom_InventoryCharacterWindow.layout", parent, _throw, _createFakeWidgets);
        return;
    }

    BaseLayout_initialise_orig(thisptr, layout, parent, _throw, _createFakeWidgets);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------
