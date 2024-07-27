#ifndef PAGE_HANDLERS_H
#define PAGE_HANDLERS_H

#define CONCAT(base, arg) base##arg
#define CONCAT3(base, arg1, arg2) base##arg1##arg2

#define set_current_page(page_id) gslc_SetPageCur(&gui_global, page_id);
#define set_background_color(color) gslc_SetBkgndColor(&gui_global, color);
#define register_page(page_id, ref)           \
    gslc_PageAdd(&gui_global,                 \
        CONCAT(E_PG_, page_id),               \
        CONCAT(ref, Elem),                    \
        CONCAT3(MAX_ELEM_PG_, page_id, _RAM), \
        CONCAT(ref, ElemRef),                 \
        CONCAT(MAX_ELEM_PG_, page_id));

#endif // PAGE_HANDLERS_H