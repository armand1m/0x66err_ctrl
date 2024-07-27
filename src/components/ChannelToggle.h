#ifndef CHANNEL_TOGGLE_H
#define CHANNEL_TOGGLE_H

#include "../context/GuiContext.h"
#include "../references/UIGlobalRefs.h"
#include "../state/UIState.h"
#include "Button.h"

typedef struct ChannelToggleProps {
    GuiContext context;
    int16_t channelid_1;
    int16_t channelid_2;
    int16_t channelid_3;
    int16_t channelid_4;
} ChannelToggleProps;

bool on_channel_toggle(void* gui_pointer, void* element_ref_pointer, gslc_teTouch touch_event,
    int16_t _touch_x, int16_t _touch_y)
{
    gslc_tsGui* gui = (gslc_tsGui*)(gui_pointer);
    gslc_tsElemRef* element_ref = (gslc_tsElemRef*)(element_ref_pointer);
    gslc_tsElem* element = gslc_GetElemFromRef(gui, element_ref);

    if (touch_event == GSLC_TOUCH_UP_IN) {
        active_channel_state.channel = get_channel_number_by_element_id(element->nId);

        // deactivate old channel button
        toggle_button_active({
            .context = { .gui = gui },
            .element = active_channel_state.active_element,
            .active = false,
        });

        // replace active element with new channel button
        active_channel_state.active_element = element_ref;

        // activate new channel button
        toggle_button_active({
            .context = { .gui = gui },
            .element = element_ref,
            .active = true,
        });
    }

    return true;
}

#define channel_button(index, channel_label)                   \
    createButton({ .context = props.context,                   \
        .id = CONCAT(props.channelid_, index),                 \
        .position = { 50 + (100 * (index - 1)), 295, 80, 20 }, \
        .text = channel_label,                                 \
        .on_press = &on_channel_toggle,                        \
        .is_active = active_channel_state.channel == index });

void render_channel_toggle(ChannelToggleProps props)
{
    gslc_tsElemRef* channel_1 = channel_button(1, "Channel 1");

    if (active_channel_state.channel < 1) {
        active_channel_state.channel = 1;
    }

    if (active_channel_state.active_element == NULL) {
        active_channel_state.active_element = channel_1;
    }

    channel_button(2, "Channel 2");
    channel_button(3, "Channel 3");
    channel_button(4, "Channel 4");
}

#endif // CHANNEL_TOGGLE_H