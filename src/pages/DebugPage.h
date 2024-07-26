#ifndef DEBUG_PAGE_H
#define DEBUG_PAGE_H

#include "../components/Button.h"
#include "../components/Text.h"
#include "../context/GuiContext.h"
#include "../enums/ComponentEnums.h"
#include "../enums/PageEnums.h"
#include "../references/ExternComponents.h"
#include "../state/UIState.h"

GuiContext debug_page_context = { .gui = &gui_global, .page = E_PG_DEBUG };

bool on_backhome_press(void* gui_pointer, void* element_ref_pointer, gslc_teTouch touch_event,
    int16_t _touch_x, int16_t _touch_y)
{
    gslc_SetPageCur(&gui_global, E_PG_MAIN);
    return true;
}

void render_debug_page()
{
    DebugText = createText({ .context = debug_page_context,
        .id = E_ELEM_DEBUG_TXT,
        .position = { 30, 30, 300, 300 },
        .text = "debug text goes here" });

    createButton({ .context = debug_page_context,
        .id = E_ELEM_BTN_BACKHOME_DEBUG,
        .position = { 10, 10, 80, 20 },
        .text = "Back",
        .on_press = &on_backhome_press,
        .is_active = false });
}

#endif // DEBUG_PAGE_H