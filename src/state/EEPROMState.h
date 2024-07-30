#ifndef EEPROM_STATE_H
#define EEPROM_STATE_H
#include "../components/RingGauge.h"
#include "../components/Slider.h"
#include "../components/Toggle.h"
#include "../components/XYMap.h"
#include "../context/PagesContext.h"
#include "../peripherals/RotaryEncoders.h"
#include "../references/ExternComponents.h"
#include "UIState.h"
#include <EEPROM.h>
#include <elem/XRingGauge.h>

#define EEPROM_SIGNATURE_ADDR 0
#define EEPROM_SIGNATURE_VALUE 0xDEADBEEF
#define EEPROM_STATE_ADDR (EEPROM_SIGNATURE_ADDR + sizeof(unsigned long))

typedef struct ChannelState {
    int ring_gauge1;
    int ring_gauge2;
    int ring_gauge3;
    int ring_gauge4;
    int toggle1;
    int toggle2;
    int toggle3;
    int toggle4;
    int slider1;
    int slider2;
    int slider3;
    int slider4;
    int slider5;
    int slider6;
    int slider7;
    int xymap_x;
    int xymap_y;
} ChannelState;

typedef struct EEPROMState {
    ChannelState channel_states[4];
} EEPROMState;

EEPROMState eepromState;

void __eeprom_save()
{
    EEPROM.put(EEPROM_STATE_ADDR, eepromState);
}

void __eeprom_load()
{
    EEPROM.get(EEPROM_STATE_ADDR, eepromState);
}

ChannelState* __eeprom_get_channel_state(int channel_number)
{
    return &eepromState.channel_states[channel_number - 1];
}

void __eeprom_render_xymap_values(int channel_number)
{
    if (channel_number < 1 || channel_number > 4) {
        return;
    }

    ChannelState* state = __eeprom_get_channel_state(channel_number);

    if (gslc_GetPageCur(&gui_global) == xymap_page_context.page) {
        render_xymap_lines({ .context = xymap_page_context,
            .bounds = xymap_position,
            .color = GSLC_COL_GRAY_LT2,
            .border_color = GSLC_COL_GRAY_DK2,
            .state = XyMapRenderedState,
            .erase = true });

        XyMapRenderedState.x = state->xymap_x;
        XyMapRenderedState.y = state->xymap_y;

        render_xymap_lines({ .context = xymap_page_context,
            .bounds = xymap_position,
            .color = GSLC_COL_GRAY_LT2,
            .border_color = GSLC_COL_GRAY_DK2,
            .state = XyMapRenderedState,
            .erase = false });
    }
}

void __eeprom_update_component_values(int channel_number)
{
    if (channel_number < 1 || channel_number > 4) {
        return;
    }

    ChannelState* state = __eeprom_get_channel_state(channel_number);

    update_ring_gauge({
        .gui = &gui_global,
        .element = KnobGauge1,
        .value = state->ring_gauge1,
    });
    encoders[0].resetPosition(state->ring_gauge1);

    update_ring_gauge({
        .gui = &gui_global,
        .element = KnobGauge2,
        .value = state->ring_gauge2,
    });
    encoders[1].resetPosition(state->ring_gauge2);

    update_ring_gauge({
        .gui = &gui_global,
        .element = KnobGauge3,
        .value = state->ring_gauge3,
    });
    encoders[2].resetPosition(state->ring_gauge3);

    update_ring_gauge({
        .gui = &gui_global,
        .element = KnobGauge4,
        .value = state->ring_gauge4,
    });
    encoders[3].resetPosition(state->ring_gauge4);

    set_toggle_state({
        .gui = &gui_global,
        .element = Toggle1,
        .value = static_cast<bool>(state->toggle1),
    });
    encoders[0].resetPressedPosition(state->toggle1);

    set_toggle_state({
        .gui = &gui_global,
        .element = Toggle2,
        .value = static_cast<bool>(state->toggle2),
    });
    encoders[1].resetPressedPosition(state->toggle2);

    set_toggle_state({
        .gui = &gui_global,
        .element = Toggle3,
        .value = static_cast<bool>(state->toggle3),
    });
    encoders[2].resetPressedPosition(state->toggle3);

    set_toggle_state({
        .gui = &gui_global,
        .element = Toggle4,
        .value = static_cast<bool>(state->toggle4),
    });
    encoders[3].resetPressedPosition(state->toggle4);

    gslc_ElemXSliderSetPos(&gui_global, EqSlider1, state->slider1);
    gslc_ElemXSliderSetPos(&gui_global, EqSlider2, state->slider2);
    gslc_ElemXSliderSetPos(&gui_global, EqSlider3, state->slider3);
    gslc_ElemXSliderSetPos(&gui_global, EqSlider4, state->slider4);
    gslc_ElemXSliderSetPos(&gui_global, EqSlider5, state->slider5);
    gslc_ElemXSliderSetPos(&gui_global, EqSlider6, state->slider6);
    gslc_ElemXSliderSetPos(&gui_global, EqSlider7, state->slider7);
}

void __eeprom_set_default_values()
{
    for (int i = 0; i < 4; ++i) {
        ChannelState* state = &eepromState.channel_states[i];
        state->ring_gauge1 = 0; // Set default values as needed
        state->ring_gauge2 = 0;
        state->ring_gauge3 = 0;
        state->ring_gauge4 = 0;
        state->toggle1 = 0;
        state->toggle2 = 0;
        state->toggle3 = 0;
        state->toggle4 = 0;
        state->slider1 = 50;
        state->slider2 = 50;
        state->slider3 = 50;
        state->slider4 = 50;
        state->slider5 = 50;
        state->slider6 = 50;
        state->slider7 = 50;
        state->xymap_x = 0;
        state->xymap_y = 0;
    }
    EEPROM.put(EEPROM_STATE_ADDR, eepromState);
    EEPROM.put(EEPROM_SIGNATURE_ADDR, EEPROM_SIGNATURE_VALUE);
}

void setup_eeprom()
{
    unsigned long signature;
    EEPROM.get(EEPROM_SIGNATURE_ADDR, signature);

    if (signature != EEPROM_SIGNATURE_VALUE) {
        // Signature not present, initialize EEPROM with default values
        __eeprom_set_default_values();
    } else {
        // Load the existing state
        __eeprom_load();
    }
}

void __eeprom_update_toggle_state(ChannelState* state, int element_id, bool new_value)
{
    switch (element_id) {
    case E_ELEM_TOGGLE1:
        state->toggle1 = new_value;
        break;

    case E_ELEM_TOGGLE2:
        state->toggle2 = new_value;
        break;

    case E_ELEM_TOGGLE3:
        state->toggle3 = new_value;
        break;

    case E_ELEM_TOGGLE4:
        state->toggle4 = new_value;
        break;
    }
}

void __eeprom_update_slider_state(ChannelState* state, int element_id, int value)
{
    switch (element_id) {
    case E_ELEM_SLIDER1:
        state->slider1 = value;
        break;

    case E_ELEM_SLIDER2:
        state->slider2 = value;
        break;

    case E_ELEM_SLIDER3:
        state->slider3 = value;
        break;

    case E_ELEM_SLIDER4:
        state->slider4 = value;
        break;

    case E_ELEM_SLIDER5:
        state->slider5 = value;
        break;

    case E_ELEM_SLIDER6:
        state->slider6 = value;
        break;

    case E_ELEM_SLIDER7:
        state->slider7 = value;
        break;
    }
}

void __eeprom_update_knob_state(ChannelState* state, int element_id, int value)
{
    switch (element_id) {
    case E_ELEM_RINGGAUGE1:
        state->ring_gauge1 = value;
        break;

    case E_ELEM_RINGGAUGE2:
        state->ring_gauge2 = value;
        break;

    case E_ELEM_RINGGAUGE3:
        state->ring_gauge3 = value;
        break;

    case E_ELEM_RINGGAUGE4:
        state->ring_gauge4 = value;
        break;
    }
}
#endif // EEPROM_STATE_H