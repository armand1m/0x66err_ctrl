#ifndef XYMAPPAGE_H
#define XYMAPPAGE_H

#include "../components/Button.h"
#include "../components/ChannelToggle.h"
#include "../components/XYMap.h"
#include "../context/PagesContext.h"
#include "../enums/ComponentEnums.h"
#include "../enums/PageEnums.h"
#include "../midi/CCMaps.h"
#include "../midi/Transport.h"
#include "../references/ExternComponents.h"
#include "../state/UIState.h"
#include "../utils/clamp.h"
#include "PageHandlers.h"

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
    __midi_send_cc(XY_MAP_CC_X, map_x_to_midi_cc(XyMapRenderedState.x), xymap_channel_state.channel);
    return true;
}

bool on_sendy_press(void* gui_pointer, void* element_ref_pointer, gslc_teTouch touch_event,
    int16_t _touch_x, int16_t _touch_y)
{
    __on_touch_only();
    __midi_send_cc(XY_MAP_CC_Y, map_y_to_midi_cc(XyMapRenderedState.y), xymap_channel_state.channel);
    return true;
}

bool on_xymap_touch(void* gui_pointer, void* element_ref_pointer, gslc_teTouch touch_event,
    int16_t touch_x, int16_t touch_y)
{
    bool should_capture_event = touch_event == GSLC_TOUCH_DOWN_IN
        || touch_event == GSLC_TOUCH_MOVE_IN
        || touch_event == GSLC_TOUCH_UP_IN;

    if (!should_capture_event) {
        return true;
    }

    ChannelState* state = __eeprom_get_channel_state(xymap_channel_state.channel);

    render_xymap_lines({ .context = xymap_page_context,
        .bounds = xymap_position,
        .color = GSLC_COL_GRAY_LT2,
        .border_color = GSLC_COL_GRAY_DK2,
        .state = XyMapRenderedState,
        .erase = true });

    XyMapRenderedState.x = touch_x;
    XyMapRenderedState.y = touch_y;
    state->xymap_x = touch_x;
    state->xymap_y = touch_y;

    render_xymap_lines({ .context = xymap_page_context,
        .bounds = xymap_position,
        .color = GSLC_COL_GRAY_LT2,
        .border_color = GSLC_COL_GRAY_DK2,
        .state = XyMapRenderedState,
        .erase = false });

    int16_t clamped_x = clamp(XyMapRenderedState.x, bounds.x_start, bounds.x_end);
    int16_t clamped_y = clamp(XyMapRenderedState.y, bounds.y_start, bounds.y_end);

    __midi_send_cc(XY_MAP_CC_X, map_x_to_midi_cc(clamped_x), xymap_channel_state.channel);
    __midi_send_cc(XY_MAP_CC_Y, map_y_to_midi_cc(clamped_y), xymap_channel_state.channel);

    __eeprom_save();

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

    __eeprom_render_xymap_values(xymap_channel_state.channel);
    return true;
}

void render_xymap_channel_selectors()
{
    xymap_channel_state = render_channel_toggle({
        .context = xymap_page_context,
        .state = xymap_channel_state,
        .on_toggle = &on_xymap_channel_toggle,
        .channelid_1 = E_ELEM_XYMAP_BTN_CHANNEL_1,
        .channelid_2 = E_ELEM_XYMAP_BTN_CHANNEL_2,
        .channelid_3 = E_ELEM_XYMAP_BTN_CHANNEL_3,
        .channelid_4 = E_ELEM_XYMAP_BTN_CHANNEL_4,
    });
}

void render_top_buttons()
{
    gslc_ElemCreateBtnTxt_P(&gui_global, E_ELEM_BTN_BACKHOME, E_PG_XYMAP, 10, 10, 80, 20, "Back", &FontStore[Fonts::E_BUILTIN5X8], GSLC_COL_WHITE, GSLC_COL_GRAY_DK2, GSLC_COL_GRAY_DK4, GSLC_COL_GRAY_DK2, GSLC_COL_GRAY_DK1, GSLC_ALIGN_MID_MID, true, true, &on_back_press, NULL);
    gslc_ElemCreateBtnTxt_P(&gui_global, E_ELEM_BTN_SEND_X_MSG, E_PG_XYMAP, 300, 10, 80, 20, "Send X", &FontStore[Fonts::E_BUILTIN5X8], GSLC_COL_WHITE, GSLC_COL_GRAY_DK2, GSLC_COL_GRAY_DK4, GSLC_COL_GRAY_DK2, GSLC_COL_GRAY_DK1, GSLC_ALIGN_MID_MID, true, true, &on_sendx_press, NULL);
    gslc_ElemCreateBtnTxt_P(&gui_global, E_ELEM_BTN_SEND_Y_MSG, E_PG_XYMAP, 390, 10, 80, 20, "Send Y", &FontStore[Fonts::E_BUILTIN5X8], GSLC_COL_WHITE, GSLC_COL_GRAY_DK2, GSLC_COL_GRAY_DK4, GSLC_COL_GRAY_DK2, GSLC_COL_GRAY_DK1, GSLC_ALIGN_MID_MID, true, true, &on_sendy_press, NULL);
}

bool render_lines(void* pvGui, void* pvElemRef, gslc_teRedrawType eRedraw)
{
    render_xymap_lines({ .context = xymap_page_context,
        .bounds = xymap_position,
        .color = GSLC_COL_GRAY_LT2,
        .border_color = GSLC_COL_GRAY_DK2,
        .state = XyMapRenderedState,
        .erase = false });

    return true;
}

void render_xymap()
{
    ChannelState* state = __eeprom_get_channel_state(xymap_channel_state.channel);
    XyMapRenderedState.x = state->xymap_x;
    XyMapRenderedState.y = state->xymap_y;
    createXYMap({
        .context = xymap_page_context,
        .id = E_ELEM_XYMAP_BOX,
        .position = xymap_position,
        .on_touch = &on_xymap_touch,
        .on_draw = &render_lines,
    });
}

void render_xymap_page()
{
    render_xymap_channel_selectors();
    render_top_buttons();
    render_xymap();
    __eeprom_render_xymap_values(xymap_channel_state.channel);
}

#endif // XYMAPPAGE_H