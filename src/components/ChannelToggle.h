#ifndef CHANNEL_TOGGLE_H
#define CHANNEL_TOGGLE_H

#include "../context/GuiContext.h"
#include "../references/UIGlobalRefs.h"
#include "../state/UIState.h"
#include "Button.h"

typedef struct ChannelToggleProps {
    GuiContext context;
    ActiveChannelState state;
    GSLC_CB_TOUCH on_toggle;
    int16_t channelid_1;
    int16_t channelid_2;
    int16_t channelid_3;
    int16_t channelid_4;
} ChannelToggleProps;

#define channel_button(index, channel_label)                   \
    createButton({ .context = props.context,                   \
        .id = CONCAT(props.channelid_, index),                 \
        .position = { 50 + (100 * (index - 1)), 288, 80, 20 }, \
        .text = channel_label,                                 \
        .on_press = props.on_toggle,                           \
        .is_active = props.state.channel == index });

ActiveChannelState render_channel_toggle(ChannelToggleProps props)
{
    props.state.channel = 1;
    props.state.active_element = channel_button(1, "Channel 1");

    channel_button(2, "Channel 2");
    channel_button(3, "Channel 3");
    channel_button(4, "Channel 4");

    return props.state;
}

#endif // CHANNEL_TOGGLE_H