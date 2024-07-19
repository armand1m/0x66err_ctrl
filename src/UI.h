#ifndef UI_H
#define UI_H

#include "GUIslice.h"
#include "GUIslice_drv.h"

#if defined(DRV_DISP_TFT_ESPI)
#error E_PROJECT_OPTIONS tab->Graphics Library should be TFT_eSPI
#endif

#include <Adafruit_GFX.h>

#include "pages/MainPage.h"
#include "pages/XyMapPage.h"

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
    return gslc_Init(&m_gui, &m_drv, m_asPage, MAX_PAGE, m_asFont, MAX_FONT);
}

bool setup_fonts()
{
    bool builtin20x32_font_loaded = gslc_FontSet(&m_gui, E_BUILTIN20X32, GSLC_FONTREF_PTR, NULL, 4);
    bool builtin5x8_font_loaded = gslc_FontSet(&m_gui, E_BUILTIN5X8, GSLC_FONTREF_PTR, NULL, 1);

    return builtin20x32_font_loaded && builtin5x8_font_loaded;
}

void register_pages()
{
    gslc_PageAdd(&m_gui, E_PG_MAIN, m_asPage1Elem, MAX_ELEM_PG_MAIN_RAM,
        m_asPage1ElemRef, MAX_ELEM_PG_MAIN);
    gslc_PageAdd(&m_gui, E_PG_XYMAP, m_asPage2Elem, MAX_ELEM_PG_XYMAP_RAM,
        m_asPage2ElemRef, MAX_ELEM_PG_XYMAP);
}

void set_main_page(int16_t page_id) { gslc_SetPageCur(&m_gui, page_id); }
void set_background_color(gslc_tsColor color)
{
    gslc_SetBkgndColor(&m_gui, color);
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
}

#endif // end UI_H
