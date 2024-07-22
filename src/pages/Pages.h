#ifndef PAGES_H
#define PAGES_H

#define CONCAT(base, arg) base##arg
#define CONCAT3(base, arg1, arg2) base##arg1##arg2

#include "DebugPage.h"
#include "MainPage.h"
#include "XYMapPage.h"

#define set_main_page(page_id) gslc_SetPageCur(&gui_global, page_id);
#define set_background_color(color) gslc_SetBkgndColor(&gui_global, color);
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

void setup_page_defaults()
{
    register_pages();
    set_main_page(E_PG_MAIN);
    set_background_color(GSLC_COL_BLACK);
}

void setup_pages()
{
    setup_page_defaults();
    render_main_page();
    render_xy_map_page();
    render_debug_page();
}

#endif // PAGES_H