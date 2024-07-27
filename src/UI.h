#ifndef UI_H
#define UI_H

#include "GUIslice.h"
#include "GUIslice_drv.h"

#if defined(DRV_DISP_TFT_ESPI)
#error E_PROJECT_OPTIONS tab->Graphics Library should be TFT_eSPI
#endif

#include <Adafruit_GFX.h>

#include "pages/Pages.h"

#define update_user_interface() gslc_Update(&gui_global);
#define debug_user_interface() gslc_InitDebug(&DebugOut);
#define initialize() gslc_Init(&gui_global, &gui_driver, PageStore, MAX_PAGE, FontStore, MAX_FONT)

// GUIslice debug function definition
static int16_t DebugOut(char ch)
{
#ifndef HIDUINO
    if (ch == (char)'\n')
        Serial.println("");
    else
        Serial.write(ch);
#endif

    return 0;
}

bool setup_fonts()
{
    bool builtin20x32_font_loaded = gslc_FontSet(&gui_global, E_BUILTIN20X32, GSLC_FONTREF_PTR, NULL, 4);
    bool builtin5x8_font_loaded = gslc_FontSet(&gui_global, E_BUILTIN5X8, GSLC_FONTREF_PTR, NULL, 1);

    return builtin20x32_font_loaded && builtin5x8_font_loaded;
}

void setup_user_interface()
{
    if (!initialize() || !setup_fonts()) {
        return;
    }

    setup_pages();
}

#endif // end UI_H
