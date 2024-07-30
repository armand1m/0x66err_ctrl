#ifndef ROTARY_ENCODER_HANDLERS_H
#define ROTARY_ENCODER_HANDLERS_H

#include "../components/RingGauge.h"
#include "../components/Toggle.h"
#include "../midi/CCMaps.h"
#include "../midi/Transport.h"
#include "../references/UIGlobalRefs.h"
#include "../state/UIState.h"
#include "RotaryEncoders.h"

void on_encoder_click(EncoderButton& encoder)
{
    int id = encoder.userId();
    int control_value = switch_toggle_state({ .gui = &gui_global,
                            .element = get_toggle_ref_by_encoder_id(id) })
        ? 127
        : 0;

    return send_midi_cc(toggle_midi_cc[id], control_value, mainpage_channel_state.channel);
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

    return send_midi_cc(control_number, control_value, mainpage_channel_state.channel);
}

#endif // ROTARY_ENCODER_HANDLERS_H