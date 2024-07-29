#ifndef PAGE_HANDLERS_H
#define PAGE_HANDLERS_H

#define CONCAT(base, arg) base##arg
#define CONCAT3(base, arg1, arg2) base##arg1##arg2

#define set_current_page(page_id) gslc_SetPageCur(&gui_global, page_id);
#define set_background_color(color) gslc_SetBkgndColor(&gui_global, color);
#define register_page(page_id, ref)           \
    gslc_PageAdd(&gui_global,                 \
        CONCAT(Pages::E_PG_, page_id),        \
        CONCAT(ref, Elem),                    \
        CONCAT3(MAX_ELEM_PG_, page_id, _RAM), \
        CONCAT(ref, ElemRef),                 \
        CONCAT(MAX_ELEM_PG_, page_id));

#define __on_touch_only()                                \
    if (touch_event != gslc_teTouch::GSLC_TOUCH_UP_IN) { \
        return true;                                     \
    }

#define __resolve_gui_context()                                           \
    gslc_tsGui* gui = (gslc_tsGui*)(gui_pointer);                         \
    gslc_tsElemRef* element_ref = (gslc_tsElemRef*)(element_ref_pointer); \
    gslc_tsElem* element = gslc_GetElemFromRef(gui, element_ref);         \
    int16_t element_id = element->nId;

#endif // PAGE_HANDLERS_H