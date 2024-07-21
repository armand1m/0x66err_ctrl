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

GuiContext xymap_page_context = { .gui = &gui_global, .page = E_PG_XYMAP };
gslc_tsRect xymap_position = { 10, 40, 460, 270 };
XYMapLineBounds bounds = create_xymap_line_bounds(xymap_position);

long map_x_to_midi_cc(int16_t x)
{
    return map(x, bounds.x_start, bounds.x_end, 0, 136);
}

long map_y_to_midi_cc(int16_t y)
{
    return map(y, bounds.y_start, bounds.y_end, 125, -21);
}

bool on_back_press(void* gui_pointer, void* element_ref_pointer, gslc_teTouch touch_event,
    int16_t _touch_x, int16_t _touch_y)
{
    gslc_SetPageCur(&gui_global, E_PG_MAIN);
    return true;
}

bool on_sendx_press(void* gui_pointer, void* element_ref_pointer, gslc_teTouch touch_event,
    int16_t _touch_x, int16_t _touch_y)
{
    send_midi_cc(xy_map_midi_cc[0], map_x_to_midi_cc(XyMapState1.x), 1);
    return true;
}

bool on_sendy_press(void* gui_pointer, void* element_ref_pointer, gslc_teTouch touch_event,
    int16_t _touch_x, int16_t _touch_y)
{
    send_midi_cc(xy_map_midi_cc[1], map_y_to_midi_cc(XyMapState1.y), 1);
    return true;
}

bool on_xymap_touch(void* gui_pointer, void* element_ref_pointer, gslc_teTouch touch_event,
    int16_t touch_x, int16_t touch_y)
{
    bool should_capture_event = touch_event == GSLC_TOUCH_DOWN_IN || touch_event == GSLC_TOUCH_MOVE_IN || touch_event == GSLC_TOUCH_UP_IN;

    if (!should_capture_event) {
        return true;
    }

    touch_x = clamp(touch_x, bounds.x_start, bounds.x_end);
    touch_y = clamp(touch_y, bounds.y_start, bounds.y_end);

    render_xymap_lines({ .context = xymap_page_context,
        .bounds = xymap_position,
        .color = GSLC_COL_GRAY_LT2,
        .erase = true });

    XyMapState1.x = touch_x;
    XyMapState1.y = touch_y;

    render_xymap_lines({ .context = xymap_page_context,
        .bounds = xymap_position,
        .color = GSLC_COL_GRAY_LT2,
        .erase = false });

    send_midi_cc(xy_map_midi_cc[0], map_x_to_midi_cc(XyMapState1.x), 1);
    send_midi_cc(xy_map_midi_cc[1], map_y_to_midi_cc(XyMapState1.y), 1);

    return true;
}

void render_xy_map_page()
{
    BackHomeButton = createButton({
        .context = xymap_page_context,
        .id = E_ELEM_BTN_BACKHOME,
        .position = { 15, 10, 80, 20 },
        .text = "Back",
        .on_press = &on_back_press,
    });

    SendXMidiMsg = createButton({
        .context = xymap_page_context,
        .id = E_ELEM_BTN_SEND_X_MSG,
        .position = { 300, 10, 80, 20 },
        .text = "Send X",
        .on_press = &on_sendx_press,
    });

    SendYMidiMsg = createButton({
        .context = xymap_page_context,
        .id = E_ELEM_BTN_SEND_Y_MSG,
        .position = { 390, 10, 80, 20 },
        .text = "Send Y",
        .on_press = &on_sendy_press,
    });

    XyMapBox = createXYMap({
        .context = xymap_page_context,
        .id = E_ELEM_BOX1,
        .position = xymap_position,
        .on_touch = &on_xymap_touch,
        .color = GSLC_COL_GRAY_LT2,
    });
}

#endif // XYMAPPAGE_H