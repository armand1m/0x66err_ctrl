#ifndef PAGES_H
#define PAGES_H

#include "MainPage.h"
#include "PageHandlers.h"
#include "XYMapPage.h"

void register_pages()
{
    register_page(MAIN, MainPage);
    register_page(XYMAP, XYMapPage);
}

void setup_page_defaults()
{
    set_current_page(Pages::E_PG_MAIN);
    set_background_color(GSLC_COL_BLACK);
}

void setup_pages()
{
    register_pages();
    setup_page_defaults();
    render_main_page();
    render_xymap_page();
}

#endif // PAGES_H