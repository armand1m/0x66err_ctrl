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

    __midi_send_cc(toggle_midi_cc[id], control_value, mainpage_channel_state.channel);

    gslc_tsElemRef* element_ref = get_toggle_ref_by_encoder_id(id);
    gslc_tsElem* element = gslc_GetElemFromRef(&gui_global, element_ref);
    __eeprom_set_toggle_state(mainpage_channel_state.channel, element->nId, new_value);
}

void on_encoder_spin(EncoderButton& encoder)
{
    int id = encoder.userId();
    gslc_tsElemRef* element_ref = get_gauge_ref_by_encoder_id(id);
    gslc_tsElem* element = gslc_GetElemFromRef(&gui_global, element_ref);

    limit_encoder_positions(encoder);

    int control_number = knob_midi_cc[id];
    int control_value = encoder.position();

    update_ring_gauge({
        .gui = &gui_global,
        .element = element_ref,
        .value = control_value,
    });

    __eeprom_set_knob_state(mainpage_channel_state.channel, element->nId, control_value);
    __midi_send_cc(control_number, control_value, mainpage_channel_state.channel);
}

#endif // ROTARY_ENCODER_HANDLERS_H