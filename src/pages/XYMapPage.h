#ifndef XYMAPPAGE_H
#define XYMAPPAGE_H

#include "../components/Button.h"
#include "../components/XYMap.h"
#include "../enums/ComponentEnums.h"
#include "../enums/PageEnums.h"
#include "../midi/CCMaps.h"
#include "../midi/Transport.h"
#include "../references/ExternComponents.h"
#include "../state/UIState.h"
#include "../utils/clamp.h"
#include "../utils/mem.h"
#include "PageHandlers.h"

GuiContext xymap_page_context = { .gui = &gui_global, .page = Pages::E_PG_XYMAP };
gslc_tsRect xymap_position = { 10, 40, 460, 230 };
XYMapLineBounds bounds = create_xymap_line_bounds(xymap_position);

#define map_x_to_midi_cc(x) map(x, bounds.x_start, bounds.x_end, 0, 129)
#define map_y_to_midi_cc(y) map(y, bounds.y_start, bounds.y_end, 127, -21)

bool on_back_press(void* gui_pointer, void* element_ref_pointer, gslc_teTouch touch_event,
    int16_t _touch_x, int16_t _touch_y)
{
    __on_touch_only();
    set_current_page(Pages::E_PG_MAIN);
    return true;
}

bool on_sendx_press(void* gui_pointer, void* element_ref_pointer, gslc_teTouch touch_event,
    int16_t _touch_x, int16_t _touch_y)
{
    __on_touch_only();
    send_midi_cc(XY_MAP_CC_X, map_x_to_midi_cc(XyMapState1.x), xymap_channel_state.channel);
    return true;
}

bool on_sendy_press(void* gui_pointer, void* element_ref_pointer, gslc_teTouch touch_event,
    int16_t _touch_x, int16_t _touch_y)
{
    __on_touch_only();
    send_midi_cc(XY_MAP_CC_Y, map_y_to_midi_cc(XyMapState1.y), xymap_channel_state.channel);
    return true;
}

bool on_xymap_touch(void* gui_pointer, void* element_ref_pointer, gslc_teTouch touch_event,
    int16_t touch_x, int16_t touch_y)
{
    bool should_capture_event = touch_event == GSLC_TOUCH_DOWN_IN || touch_event == GSLC_TOUCH_MOVE_IN || touch_event == GSLC_TOUCH_UP_IN;

    if (!should_capture_event) {
        return true;
    }

    render_xymap_lines({ .context = xymap_page_context,
        .bounds = xymap_position,
        .color = GSLC_COL_GRAY_LT2,
        .state = XyMapState1,
        .erase = true });

    XyMapState1.x = touch_x;
    XyMapState1.y = touch_y;

    render_xymap_lines({ .context = xymap_page_context,
        .bounds = xymap_position,
        .color = GSLC_COL_GRAY_LT2,
        .state = XyMapState1,
        .erase = false });

    int16_t clamped_x = clamp(XyMapState1.x, bounds.x_start, bounds.x_end);
    int16_t clamped_y = clamp(XyMapState1.y, bounds.y_start, bounds.y_end);

    send_midi_cc(XY_MAP_CC_X, map_x_to_midi_cc(clamped_x), xymap_channel_state.channel);
    send_midi_cc(XY_MAP_CC_Y, map_y_to_midi_cc(clamped_y), xymap_channel_state.channel);

    return true;
}

bool on_xymap_channel_toggle(void* gui_pointer, void* element_ref_pointer, gslc_teTouch touch_event,
    int16_t _touch_x, int16_t _touch_y)
{
    __on_touch_only();
    __resolve_gui_context();

    xymap_channel_state.channel = get_channel_number_by_element_id(element_id);

    // deactivate old channel button
    toggle_button_active({
        .context = xymap_page_context,
        .element = xymap_channel_state.active_element,
        .active = false,
    });

    // replace active element with new channel button
    xymap_channel_state.active_element = element_ref;

    // activate new channel button
    toggle_button_active({
        .context = xymap_page_context,
        .element = xymap_channel_state.active_element,
        .active = true,
    });

    return true;
}

void render_xymap_channel_selectors()
{
    xymap_channel_state.channel = 1;
    gslc_ElemCreateBtnTxt_P(&gui_global, E_ELEM_XYMAP_BTN_CHANNEL_1, E_PG_XYMAP, 50, 295, 80, 20, "Channel 1", &FontStore[Fonts::E_BUILTIN5X8], GSLC_COL_WHITE, GSLC_COL_GRAY_DK2, GSLC_COL_GRAY_DK4, GSLC_COL_GRAY_DK2, GSLC_COL_GRAY_DK1, GSLC_ALIGN_MID_MID, true, true, &on_xymap_channel_toggle, NULL);
    xymap_channel_state.active_element = gslc_PageFindElemById(&gui_global, E_PG_XYMAP, E_ELEM_XYMAP_BTN_CHANNEL_1);
    gslc_ElemCreateBtnTxt_P(&gui_global, E_ELEM_XYMAP_BTN_CHANNEL_2, E_PG_XYMAP, 150, 295, 80, 20, "Channel 2", &FontStore[Fonts::E_BUILTIN5X8], GSLC_COL_WHITE, GSLC_COL_GRAY_DK2, GSLC_COL_GRAY_DK4, GSLC_COL_GRAY_DK2, GSLC_COL_GRAY_DK1, GSLC_ALIGN_MID_MID, true, true, &on_xymap_channel_toggle, NULL);
    gslc_ElemCreateBtnTxt_P(&gui_global, E_ELEM_XYMAP_BTN_CHANNEL_3, E_PG_XYMAP, 250, 295, 80, 20, "Channel 3", &FontStore[Fonts::E_BUILTIN5X8], GSLC_COL_WHITE, GSLC_COL_GRAY_DK2, GSLC_COL_GRAY_DK4, GSLC_COL_GRAY_DK2, GSLC_COL_GRAY_DK1, GSLC_ALIGN_MID_MID, true, true, &on_xymap_channel_toggle, NULL);
    gslc_ElemCreateBtnTxt_P(&gui_global, E_ELEM_XYMAP_BTN_CHANNEL_4, E_PG_XYMAP, 350, 295, 80, 20, "Channel 4", &FontStore[Fonts::E_BUILTIN5X8], GSLC_COL_WHITE, GSLC_COL_GRAY_DK2, GSLC_COL_GRAY_DK4, GSLC_COL_GRAY_DK2, GSLC_COL_GRAY_DK1, GSLC_ALIGN_MID_MID, true, true, &on_xymap_channel_toggle, NULL);
}

void render_xy_map_page()
{
    log_free_memory();

    render_xymap_channel_selectors();
    gslc_ElemCreateBtnTxt_P(&gui_global, E_ELEM_BTN_BACKHOME, E_PG_XYMAP, 10, 10, 80, 20, "Back", &FontStore[Fonts::E_BUILTIN5X8], GSLC_COL_WHITE, GSLC_COL_GRAY_DK2, GSLC_COL_GRAY_DK4, GSLC_COL_GRAY_DK2, GSLC_COL_GRAY_DK1, GSLC_ALIGN_MID_MID, true, true, &on_back_press, NULL);
    gslc_ElemCreateBtnTxt_P(&gui_global, E_ELEM_BTN_SEND_X_MSG, E_PG_XYMAP, 300, 10, 80, 20, "Send X", &FontStore[Fonts::E_BUILTIN5X8], GSLC_COL_WHITE, GSLC_COL_GRAY_DK2, GSLC_COL_GRAY_DK4, GSLC_COL_GRAY_DK2, GSLC_COL_GRAY_DK1, GSLC_ALIGN_MID_MID, true, true, &on_sendx_press, NULL);
    gslc_ElemCreateBtnTxt_P(&gui_global, E_ELEM_BTN_SEND_Y_MSG, E_PG_XYMAP, 390, 10, 80, 20, "Send Y", &FontStore[Fonts::E_BUILTIN5X8], GSLC_COL_WHITE, GSLC_COL_GRAY_DK2, GSLC_COL_GRAY_DK4, GSLC_COL_GRAY_DK2, GSLC_COL_GRAY_DK1, GSLC_ALIGN_MID_MID, true, true, &on_sendy_press, NULL);

    gslc_ElemCreateBox_P(
        &gui_global,
        E_ELEM_XYMAP_BOX,
        Pages::E_PG_XYMAP,
        10,
        40,
        460,
        230,
        GSLC_COL_GRAY_LT2,
        GSLC_COL_BLACK,
        true,
        true,
        NULL,
        NULL);

    gslc_tsElemRef* xymap_instance = gslc_PageFindElemById(&gui_global, E_PG_XYMAP, E_ELEM_XYMAP_BOX);
    gslc_ElemSetClickEn(&gui_global, xymap_instance, true);
    gslc_ElemSetTouchFunc(&gui_global, xymap_instance, &on_xymap_touch);

    log_free_memory();
}

#endif // XYMAPPAGE_H