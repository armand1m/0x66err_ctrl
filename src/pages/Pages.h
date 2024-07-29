#ifndef PAGES_H
#define PAGES_H

#include "../utils/mem.h"
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

    infolog("Memory before main page:");
    log_free_memory();
    render_main_page();
    infolog("Memory after main page:");
    log_free_memory();

    infolog("Memory before xymap page:");
    log_free_memory();
    render_xy_map_page();
    infolog("Memory after xymap page:");
    log_free_memory();
}

#endif // PAGES_H