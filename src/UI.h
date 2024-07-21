#ifndef UI_H
#define UI_H

#include "GUIslice.h"
#include "GUIslice_drv.h"

#if defined(DRV_DISP_TFT_ESPI)
#error E_PROJECT_OPTIONS tab->Graphics Library should be TFT_eSPI
#endif

#include <Adafruit_GFX.h>

#define CONCAT(base, arg) base##arg
#define CONCAT3(base, arg1, arg2) base##arg1##arg2

#include "pages/DebugPage.h"
#include "pages/MainPage.h"
#include "pages/XYMapPage.h"

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

bool initialize()
{
    return gslc_Init(&gui_global, &gui_driver, PageStore, MAX_PAGE, FontStore, MAX_FONT);
}

bool setup_fonts()
{
    bool builtin20x32_font_loaded = gslc_FontSet(&gui_global, E_BUILTIN20X32, GSLC_FONTREF_PTR, NULL, 4);
    bool builtin5x8_font_loaded = gslc_FontSet(&gui_global, E_BUILTIN5X8, GSLC_FONTREF_PTR, NULL, 1);

    return builtin20x32_font_loaded && builtin5x8_font_loaded;
}

#define register_page(page_id, ref)           \
    gslc_PageAdd(&gui_global,                 \
        CONCAT(E_PG_, page_id),               \
        CONCAT(ref, Elem),                    \
        CONCAT3(MAX_ELEM_PG_, page_id, _RAM), \
        CONCAT(ref, ElemRef),                 \
        CONCAT(MAX_ELEM_PG_, page_id));

void register_pages()
{
    register_page(MAIN, MainPage);
    register_page(XYMAP, XYMapPage);
    register_page(DEBUG, DebugPage);
}

void set_main_page(int16_t page_id) { gslc_SetPageCur(&gui_global, page_id); }
void set_background_color(gslc_tsColor color)
{
    gslc_SetBkgndColor(&gui_global, color);
}

void render()
{
    if (!initialize() || !setup_fonts()) {
        return;
    }

    register_pages();
    set_main_page(E_PG_MAIN);
    set_background_color(GSLC_COL_BLACK);
    render_main_page();
    render_xy_map_page();
    render_debug_page();
}

#endif // end UI_H
