#include "../components/XYMap.h"
#include "../state/UIState.h"
#include "GuiContext.h"
#ifndef PAGES_CONTEXT_H
#define PAGES_CONTEXT_H

GuiContext mainpage_context = { .gui = &gui_global, .page = Pages::E_PG_MAIN };

GuiContext xymap_page_context = { .gui = &gui_global, .page = Pages::E_PG_XYMAP };
gslc_tsRect xymap_position = { 10, 40, 460, 235 };
XYMapLineBounds bounds = create_xymap_line_bounds(xymap_position);

#endif // PAGES_CONTEXT_H