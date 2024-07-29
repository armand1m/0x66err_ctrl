#ifndef ACTIVE_CHANNEL_STATE_H
#define ACTIVE_CHANNEL_STATE_H

#include <GUIslice.h>

typedef struct ActiveChannelState {
    int channel;
    gslc_tsElemRef* active_element;
} ActiveChannelState;

#endif // ACTIVE_CHANNEL_STATE_H