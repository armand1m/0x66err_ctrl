#ifndef EEPROM_STATE_H
#define EEPROM_STATE_H
#include "../Loggers.h"
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

EEPROMState __eeprom_current_state;
EEPROMState __eeprom_previous_state;
unsigned long last_write_time = 0;
const unsigned long write_interval = 60000; // 1 minute interval between writes

bool __eeprom_has_state_changes(const EEPROMState& currentState, const EEPROMState& previousState)
{
    return memcmp(&currentState, &previousState, sizeof(EEPROMState)) != 0;
}

void __eeprom_save()
{
    EEPROM.put(EEPROM_STATE_ADDR, __eeprom_current_state);
}

void __eeprom_loop()
{
    unsigned long current_time = millis();
    bool should_write = __eeprom_has_state_changes(__eeprom_current_state, __eeprom_previous_state)
        && (current_time - last_write_time > write_interval);
    if (should_write) {
        infolog("Writing EEPROM state");
        __eeprom_save();
        __eeprom_previous_state = __eeprom_current_state; // Update the previous state
        last_write_time = current_time; // Update the last write time
    }
}

void __eeprom_read(EEPROMState& state)
{
    EEPROM.get(EEPROM_STATE_ADDR, state);
}

ChannelState* __eeprom_get_channel_state(int channel_number)
{
    return &__eeprom_current_state.channel_states[channel_number - 1];
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

#define __eeprom_update_knob(elem, enc, val) \
    update_ring_gauge({                      \
        .gui = &gui_global,                  \
        .element = elem,                     \
        .value = val,                        \
    });                                      \
    enc.resetPosition(val);

#define __eeprom_update_toggle(elem, val) set_toggle_state({ .gui = &gui_global, .element = elem, .value = static_cast<bool>(val) })
#define __eeprom_update_slider(elem, val) update_slider({ .gui = &gui_global, .element = elem, .value = val })

void __eeprom_render_updated_components(int channel_number)
{
    if (channel_number < 1 || channel_number > 4) {
        return;
    }

    ChannelState* state = __eeprom_get_channel_state(channel_number);
    ChannelState* previous_state = &__eeprom_previous_state.channel_states[channel_number - 1];

    int& gauge1 = state->ring_gauge1;
    int& gauge2 = state->ring_gauge2;
    int& gauge3 = state->ring_gauge3;
    int& gauge4 = state->ring_gauge4;
    int& toggle1 = state->toggle1;
    int& toggle2 = state->toggle2;
    int& toggle3 = state->toggle3;
    int& toggle4 = state->toggle4;
    int& slider1 = state->slider1;
    int& slider2 = state->slider2;
    int& slider3 = state->slider3;
    int& slider4 = state->slider4;
    int& slider5 = state->slider5;
    int& slider6 = state->slider6;
    int& slider7 = state->slider7;

    int& prev_gauge1 = previous_state->ring_gauge1;
    int& prev_gauge2 = previous_state->ring_gauge2;
    int& prev_gauge3 = previous_state->ring_gauge3;
    int& prev_gauge4 = previous_state->ring_gauge4;
    int& prev_toggle1 = previous_state->toggle1;
    int& prev_toggle2 = previous_state->toggle2;
    int& prev_toggle3 = previous_state->toggle3;
    int& prev_toggle4 = previous_state->toggle4;
    int& prev_slider1 = previous_state->slider1;
    int& prev_slider2 = previous_state->slider2;
    int& prev_slider3 = previous_state->slider3;
    int& prev_slider4 = previous_state->slider4;
    int& prev_slider5 = previous_state->slider5;
    int& prev_slider6 = previous_state->slider6;
    int& prev_slider7 = previous_state->slider7;

    if (gauge1 != prev_gauge1) {
        __eeprom_update_knob(KnobGauge1, encoders[0], gauge1);
    }
    if (gauge2 != prev_gauge2) {
        __eeprom_update_knob(KnobGauge2, encoders[1], gauge2);
    }
    if (gauge3 != prev_gauge3) {
        __eeprom_update_knob(KnobGauge3, encoders[2], gauge3);
    }
    if (gauge4 != prev_gauge4) {
        __eeprom_update_knob(KnobGauge4, encoders[3], gauge4);
    }
    if (toggle1 != prev_toggle1) {
        __eeprom_update_toggle(Toggle1, toggle1);
    }
    if (toggle2 != prev_toggle2) {
        __eeprom_update_toggle(Toggle2, toggle2);
    }
    if (toggle3 != prev_toggle3) {
        __eeprom_update_toggle(Toggle3, toggle3);
    }
    if (toggle4 != prev_toggle4) {
        __eeprom_update_toggle(Toggle4, toggle4);
    }
    if (slider1 != prev_slider1) {
        __eeprom_update_slider(EqSlider1, slider1);
    }
    if (slider2 != prev_slider2) {
        __eeprom_update_slider(EqSlider2, slider2);
    }
    if (slider3 != prev_slider3) {
        __eeprom_update_slider(EqSlider3, slider3);
    }
    if (slider4 != prev_slider4) {
        __eeprom_update_slider(EqSlider4, slider4);
    }
    if (slider5 != prev_slider5) {
        __eeprom_update_slider(EqSlider5, slider5);
    }
    if (slider6 != prev_slider6) {
        __eeprom_update_slider(EqSlider6, slider6);
    }
    if (slider7 != prev_slider7) {
        __eeprom_update_slider(EqSlider7, slider7);
    }
}

/**
 * Initialize the data in EEPROM
 */
void __eeprom_set_default_values()
{
    for (int i = 0; i < 4; ++i) {
        ChannelState* state = &__eeprom_current_state.channel_states[i];
        state->ring_gauge1 = 0;
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
    EEPROM.put(EEPROM_STATE_ADDR, __eeprom_current_state);
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
        __eeprom_read(__eeprom_current_state);
    }
}

void __eeprom_set_toggle_state(int channel_number, int element_id, bool new_value)
{
    ChannelState* state = __eeprom_get_channel_state(channel_number);
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

void __eeprom_set_slider_state(int channel_number, int element_id, int value)
{
    ChannelState* state = __eeprom_get_channel_state(channel_number);
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

void __eeprom_set_knob_state(int channel_number, int element_id, int value)
{
    ChannelState* state = __eeprom_get_channel_state(channel_number);
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