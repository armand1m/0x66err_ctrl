#ifndef ROTARY_ENCODER_HANDLERS_H
#define ROTARY_ENCODER_HANDLERS_H

#include "../components/RingGauge.h"
#include "../components/Toggle.h"
#include "../midi/CCMaps.h"
#include "../midi/Transport.h"
#include "../references/UIGlobalRefs.h"
#include "../state/EEPROMState.h"
#include "../state/UIState.h"
#include "RotaryEncoders.h"

void on_encoder_click(EncoderButton& encoder)
{
    int id = encoder.userId();
    int new_value = switch_toggle_state({ .gui = &gui_global,
        .element = get_toggle_ref_by_encoder_id(id) });
    int control_value = new_value ? 127 : 0;

    send_midi_cc(toggle_midi_cc[id], control_value, mainpage_channel_state.channel);

    ChannelState* state = get_channel_state(mainpage_channel_state.channel);

    switch (id) {
    case 0:
        state->toggle1 = new_value;
        break;

    case 1:
        state->toggle2 = new_value;
        break;

    case 2:
        state->toggle3 = new_value;
        break;

    case 3:
        state->toggle4 = new_value;
        break;
    }

    return save_state_to_eeprom();
}

void on_encoder_spin(EncoderButton& encoder)
{
    int id = encoder.userId();
    gslc_tsElemRef* element = get_gauge_ref_by_encoder_id(id);

    limit_encoder_positions(encoder);

    int control_value = encoder.position();

    update_ring_gauge({
        .gui = &gui_global,
        .element = element,
        .value = control_value,
    });

    int control_number = knob_midi_cc[id];

    send_midi_cc(control_number, control_value, mainpage_channel_state.channel);

    ChannelState* state = get_channel_state(mainpage_channel_state.channel);

    switch (id) {
    case 0:
        state->ringGauge1 = control_value;
        break;

    case 1:
        state->ringGauge2 = control_value;
        break;

    case 2:
        state->ringGauge3 = control_value;
        break;

    case 3:
        state->ringGauge4 = control_value;
        break;
    }

    return save_state_to_eeprom();
}

#endif // ROTARY_ENCODER_HANDLERS_H