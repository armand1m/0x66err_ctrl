#ifndef EEPROM_STATE_H
#define EEPROM_STATE_H
#include "../components/RingGauge.h"
#include "../components/Slider.h"
#include "../components/Toggle.h"
#include "../peripherals/RotaryEncoders.h"
#include "../references/ExternComponents.h"
#include "UIState.h"
#include <EEPROM.h>
#include <elem/XRingGauge.h>

#define EEPROM_SIGNATURE_ADDR 0
#define EEPROM_SIGNATURE_VALUE 0xDEADBEEF
#define EEPROM_STATE_ADDR (EEPROM_SIGNATURE_ADDR + sizeof(unsigned long))

typedef struct ChannelState {
    int ringGauge1;
    int ringGauge2;
    int ringGauge3;
    int ringGauge4;
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

void apply_eeprom_values_to_components(int channel)
{
    if (channel < 0 || channel >= 4)
        return; // Ensure channel is valid
    ChannelState* state = &eepromState.channel_states[channel];

    update_ring_gauge({
        .gui = &gui_global,
        .element = KnobGauge1,
        .value = state->ringGauge1,
    });
    encoders[0].resetPosition(state->ringGauge1);

    update_ring_gauge({
        .gui = &gui_global,
        .element = KnobGauge2,
        .value = state->ringGauge2,
    });
    encoders[1].resetPosition(state->ringGauge2);

    update_ring_gauge({
        .gui = &gui_global,
        .element = KnobGauge3,
        .value = state->ringGauge3,
    });
    encoders[2].resetPosition(state->ringGauge3);

    update_ring_gauge({
        .gui = &gui_global,
        .element = KnobGauge4,
        .value = state->ringGauge4,
    });
    encoders[3].resetPosition(state->ringGauge4);

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

void setup_eeprom()
{
    unsigned long signature;
    EEPROM.get(EEPROM_SIGNATURE_ADDR, signature);

    if (signature != EEPROM_SIGNATURE_VALUE) {
        // Signature not present, initialize EEPROM with default values
        for (int i = 0; i < 4; ++i) {
            ChannelState* state = &eepromState.channel_states[i];
            state->ringGauge1 = 0; // Set default values as needed
            state->ringGauge2 = 0;
            state->ringGauge3 = 0;
            state->ringGauge4 = 0;
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
        }
        EEPROM.put(EEPROM_STATE_ADDR, eepromState);
        EEPROM.put(EEPROM_SIGNATURE_ADDR, EEPROM_SIGNATURE_VALUE);
    } else {
        // Load the existing state
        load_state_from_eeprom();
    }
}
#endif // EEPROM_STATE_H