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

GuiContext xymap_page_context = { .gui = &m_gui, .page = E_PG_XYMAP };
gslc_tsRect xymap_position = { 10, 40, 460, 270 };

int16_t x_start_limit = xymap_position.x + 2;
int16_t x_end_limit = xymap_position.w + 8;
int16_t y_start_limit = xymap_position.y + 2;
int16_t y_end_limit = xymap_position.h + 38;

long map_x_to_midi_cc(int16_t x)
{
    return map(x, x_start_limit, x_end_limit, 0, 136);
}

long map_y_to_midi_cc(int16_t y)
{
    return map(y, y_start_limit, y_end_limit, 125, -21);
}

bool on_back_press(void* pvGui, void* pvElemRef, gslc_teTouch eTouch,
    int16_t nX, int16_t nY)
{
    gslc_SetPageCur(&m_gui, E_PG_MAIN);
    return true;
}

bool on_sendx_press(void* pvGui, void* pvElemRef, gslc_teTouch eTouch,
    int16_t nX, int16_t nY)
{
    send_midi_cc(xy_map_midi_cc[0], map_x_to_midi_cc(xyMapCurrentX), 1);
    return true;
}

bool on_sendy_press(void* pvGui, void* pvElemRef, gslc_teTouch eTouch,
    int16_t nX, int16_t nY)
{
    send_midi_cc(xy_map_midi_cc[1], map_y_to_midi_cc(xyMapCurrentY), 1);
    return true;
}

bool on_xymap_touch(void* pvGui, void* pvElemRef, gslc_teTouch eTouch,
    int16_t nX, int16_t nY)
{

    bool is_touch_event = eTouch == GSLC_TOUCH_DOWN_IN || eTouch == GSLC_TOUCH_MOVE_IN || eTouch == GSLC_TOUCH_UP_IN;

    if (is_touch_event) {
        // Limit the touch coordinates to the box boundaries
        if (nX < x_start_limit) {
            nX = x_start_limit;
        }

        if (nX > x_end_limit) {
            nX = x_end_limit;
        }

        if (nY < y_start_limit) {
            nY = y_start_limit;
        }

        if (nY > y_end_limit) {
            nY = y_end_limit;
        }

        // Erase previous lines
        renderXYMapLines({ .context = xymap_page_context,
            .bounds = xymap_position,
            .color = GSLC_COL_GRAY_LT2,
            .erase = true });

        // Update current line positions
        xyMapCurrentX = nX;
        xyMapCurrentY = nY;

        // Draw new lines at the touch coordinates
        renderXYMapLines({ .context = xymap_page_context,
            .bounds = xymap_position,
            .color = GSLC_COL_GRAY_LT2,
            .erase = false });

        // Send midi codes
        send_midi_cc(xy_map_midi_cc[0], map_x_to_midi_cc(xyMapCurrentX), 1);
        send_midi_cc(xy_map_midi_cc[1], map_y_to_midi_cc(xyMapCurrentY), 1);
    }

    return true;
}

void render_xy_map_page()
{
    BackHomeButton = createButton({
        .context = xymap_page_context,
        .id = E_ELEM_BTN_BACKHOME,
        .position = { 10, 10, 80, 20 },
        .text = "Back",
        .callback = &on_back_press,
    });

    XyMapBox = createXYMap({
        .context = xymap_page_context,
        .id = E_ELEM_BOX1,
        .position = xymap_position,
        .on_touch = &on_xymap_touch,
        .color = GSLC_COL_GRAY_LT2,
    });

    SendXMidiMsg = createButton({
        .context = xymap_page_context,
        .id = E_ELEM_BTN_SEND_X_MSG,
        .position = { 300, 10, 80, 20 },
        .text = "Send X",
        .callback = &on_sendx_press,
    });

    SendYMidiMsg = createButton({
        .context = xymap_page_context,
        .id = E_ELEM_BTN_SEND_Y_MSG,
        .position = { 390, 10, 80, 20 },
        .text = "Send Y",
        .callback = &on_sendy_press,
    });
}
#endif // XYMAPPAGE_H