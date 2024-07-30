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

void save_state_to_eeprom()
{
    EEPROM.put(EEPROM_STATE_ADDR, eepromState);
}

void load_state_from_eeprom()
{
    EEPROM.get(EEPROM_STATE_ADDR, eepromState);
}

void apply_eeprom_xymap_values(int channel_state_id)
{
    if (channel_state_id < 0 || channel_state_id >= 4) {
        // Ensure channel is valid
        return;
    }

    ChannelState* state = &eepromState.channel_states[channel_state_id];

    if (gslc_GetPageCur(&gui_global) == xymap_page_context.page) {
        render_xymap_lines({ .context = xymap_page_context,
            .bounds = xymap_position,
            .color = GSLC_COL_GRAY_LT2,
            .state = XyMapState1,
            .erase = true });

        XyMapState1.x = state->xymap_x;
        XyMapState1.y = state->xymap_y;

        render_xymap_lines({ .context = xymap_page_context,
            .bounds = xymap_position,
            .color = GSLC_COL_GRAY_LT2,
            .state = XyMapState1,
            .erase = false });
    }
}

void apply_eeprom_values_to_components(int channel_state_id)
{
    if (channel_state_id < 0 || channel_state_id >= 4) {
        // Ensure channel is valid
        return;
    }

    ChannelState* state = &eepromState.channel_states[channel_state_id];

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

ChannelState* get_channel_state(int channel_id)
{
    return &eepromState.channel_states[channel_id - 1];
}

void __initialize_eeprom_state()
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
        __initialize_eeprom_state();
    } else {
        // Load the existing state
        load_state_from_eeprom();
    }
}
#endif // EEPROM_STATE_H