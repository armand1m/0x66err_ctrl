#ifndef ROTARY_ENCODER_HANDLERS_H
#define ROTARY_ENCODER_HANDLERS_H

#include "../components/RingGauge.h"
#include "../components/Toggle.h"
#include "../midi/CCMaps.h"
#include "../midi/Transport.h"
#include "../references/UIGlobalRefs.h"
#include "../state/UIState.h"
#include "RotaryEncoders.h"
#include <EncoderButton.h>

void on_encoder_click(EncoderButton& encoder)
{
    int index = encoder.userId();
    gslc_tsElemRef* element = get_toggle_ref_by_encoder_id(index);

    if (switch_toggle_state({ .gui = &m_gui, .element = element })) {
        return send_midi_cc(toggle_midi_cc[index], 127, 1);
    }

    send_midi_cc(toggle_midi_cc[index], 0, 1);
}

void on_encoder_spin(EncoderButton& encoder)
{
    limit_encoder_positions(encoder);

    gslc_tsElemRef* element = get_gauge_ref_by_encoder_id(encoder.userId());

    update_ring_gauge({
        .gui = &m_gui,
        .element = element,
        .value = encoder.position(),
    });

    int control_value = encoder.position();
    int control_number = knob_midi_cc[encoder.userId()];
    int channel = 1;

    send_midi_cc(control_number, control_value, channel);
}

#endif // ROTARY_ENCODER_HANDLERS_H