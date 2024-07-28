#ifndef XYMAPPAGE_H
#define XYMAPPAGE_H

#include "../components/Button.h"
#include "../components/ChannelToggle.h"
#include "../components/XYMap.h"
#include "../enums/ComponentEnums.h"
#include "../enums/PageEnums.h"
#include "../midi/CCMaps.h"
#include "../midi/Transport.h"
#include "../references/ExternComponents.h"
#include "../state/UIState.h"
#include "../utils/clamp.h"
#include "PageHandlers.h"

GuiContext xymap_page_context = { .gui = &gui_global, .page = E_PG_XYMAP };
gslc_tsRect xymap_position = { 10, 40, 460, 230 };
XYMapLineBounds bounds = create_xymap_line_bounds(xymap_position);

#define map_x_to_midi_cc(x) map(x, bounds.x_start, bounds.x_end, 0, 133)
#define map_y_to_midi_cc(y) map(y, bounds.y_start, bounds.y_end, 125, -21)

#define on_touch_only()                    \
    if (touch_event != GSLC_TOUCH_UP_IN) { \
        return true;                       \
    }

bool on_back_press(void* gui_pointer, void* element_ref_pointer, gslc_teTouch touch_event,
    int16_t _touch_x, int16_t _touch_y)
{
    on_touch_only();
    set_current_page(E_PG_MAIN);

    return true;
}

bool on_sendx_press(void* gui_pointer, void* element_ref_pointer, gslc_teTouch touch_event,
    int16_t _touch_x, int16_t _touch_y)
{
    on_touch_only();
    send_midi_cc(XY_MAP_CC_X, map_x_to_midi_cc(XyMapState1.x), xymap_channel_state.channel);
    return true;
}

bool on_sendy_press(void* gui_pointer, void* element_ref_pointer, gslc_teTouch touch_event,
    int16_t _touch_x, int16_t _touch_y)
{
    on_touch_only();
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

    XyMapState1.x = clamp(touch_x, bounds.x_start, bounds.x_end);
    XyMapState1.y = clamp(touch_y, bounds.y_start, bounds.y_end);

    render_xymap_lines({ .context = xymap_page_context,
        .bounds = xymap_position,
        .color = GSLC_COL_GRAY_LT2,
        .state = XyMapState1,
        .erase = false });

    send_midi_cc(XY_MAP_CC_X, map_x_to_midi_cc(XyMapState1.x), xymap_channel_state.channel);
    send_midi_cc(XY_MAP_CC_Y, map_y_to_midi_cc(XyMapState1.y), xymap_channel_state.channel);

    return true;
}

bool on_xymap_channel_toggle(void* gui_pointer, void* element_ref_pointer, gslc_teTouch touch_event,
    int16_t _touch_x, int16_t _touch_y)
{
    on_touch_only();

    gslc_tsGui* gui = (gslc_tsGui*)(gui_pointer);
    gslc_tsElemRef* element_ref = (gslc_tsElemRef*)(element_ref_pointer);
    gslc_tsElem* element = gslc_GetElemFromRef(gui, element_ref);

    xymap_channel_state.channel = get_channel_number_by_element_id(element->nId);

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

void render_xy_map_page()
{
    // xymap_channel_state = render_channel_toggle({
    //     .context = xymap_page_context,
    //     .state = xymap_channel_state,
    //     .on_toggle = &on_xymap_channel_toggle,
    //     .channelid_1 = E_ELEM_XYMAP_BTN_CHANNEL_1,
    //     .channelid_2 = E_ELEM_XYMAP_BTN_CHANNEL_2,
    //     .channelid_3 = E_ELEM_XYMAP_BTN_CHANNEL_3,
    //     .channelid_4 = E_ELEM_XYMAP_BTN_CHANNEL_4,
    // });

    createButton({
        .context = xymap_page_context,
        .id = E_ELEM_BTN_BACKHOME,
        .position = { 10, 10, 80, 20 },
        .text = "Back",
        .on_press = &on_back_press,
        .is_active = false,
    });

    // createButton({
    //     .context = xymap_page_context,
    //     .id = E_ELEM_BTN_SEND_X_MSG,
    //     .position = { 300, 10, 80, 20 },
    //     .text = "Send X",
    //     .on_press = &on_sendx_press,
    //     .is_active = false,
    // });

    // createButton({
    //     .context = xymap_page_context,
    //     .id = E_ELEM_BTN_SEND_Y_MSG,
    //     .position = { 390, 10, 80, 20 },
    //     .text = "Send Y",
    //     .on_press = &on_sendy_press,
    //     .is_active = false,
    // });

    createXYMap({
        .context = xymap_page_context,
        .id = E_ELEM_XYMAP_BOX,
        .position = xymap_position,
        .on_touch = &on_xymap_touch,
        .color = GSLC_COL_GRAY_LT2,
    });
}

#endif // XYMAPPAGE_H