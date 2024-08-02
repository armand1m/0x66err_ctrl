#ifndef MIDI_TRANSPORT_H
#define MIDI_TRANSPORT_H
#include "../Loggers.h"
#include "../components/RingGauge.h"
#include "../components/Slider.h"
#include "../components/Toggle.h"
#include "../enums/ComponentEnums.h"
#include "../references/UIGlobalRefs.h"
#include "../state/EEPROMState.h"
#include "../state/UIState.h"
#include <MIDI.h>

#ifdef HIDUINO
MIDI_CREATE_INSTANCE(HardwareSerial, Serial, midiSerial);
#else
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, midiSerial);
#endif

const byte sysexRequest[] = { 0xF0, 0x00, 0x01, 0x05, 0x7F, 0xF7 }; // Example SysEx request

void handle_control_change(byte channel, byte number, byte value)
{
    ChannelState* state = __eeprom_get_channel_state(channel);
    gslc_tsElemRef* toggle = get_toggle_by_cc_number(number);

    if (toggle != NULL) {
        bool new_value = value > 0;
        gslc_tsElem* element = gslc_GetElemFromRef(&gui_global, toggle);
        __eeprom_set_toggle_state(channel, element->nId, new_value);

        if (mainpage_channel_state.channel == channel) {
            set_toggle_state({
                .gui = &gui_global,
                .element = toggle,
                .value = new_value,
            });
        }
    }

    gslc_tsElemRef* slider = get_slider_by_cc_number(number);

    if (slider != NULL) {
        gslc_tsElem* element = gslc_GetElemFromRef(&gui_global, slider);
        __eeprom_set_slider_state(channel, element->nId, value);

        if (mainpage_channel_state.channel == channel) {
            update_slider({
                .gui = &gui_global,
                .element = slider,
                .value = value,
            });
        }
    }

    gslc_tsElemRef* gauge = get_gauge_by_cc_number(number);

    if (gauge != NULL) {
        gslc_tsElem* element = gslc_GetElemFromRef(&gui_global, gauge);
        __eeprom_set_knob_state(channel, element->nId, value);

        if (mainpage_channel_state.channel == channel) {
            EncoderButton encoder = get_encoder_by_cc_number(number);
            encoder.resetPosition(value);
            update_ring_gauge({
                .gui = &gui_global,
                .element = gauge,
                .value = value,
            });
        }
    }

    if (number == XY_MAP_CC_X) {
        state->xymap_x = map(value, 0, 127, bounds.x_start, bounds.x_end);
    }

    if (number == XY_MAP_CC_Y) {
        state->xymap_y = map(value, 0, 127, bounds.y_end, bounds.y_start);
    }

    if (gslc_GetPageCur(&gui_global) == xymap_page_context.page && xymap_channel_state.channel == channel) {
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

void sendSysExRequest()
{
    midiSerial.sendSysEx(sizeof(sysexRequest), sysexRequest, true);
}

void handleSysEx(byte* data, unsigned length)
{
    char receivedMessage[256] = { 0 };
    snprintf(receivedMessage, sizeof(receivedMessage), "Received SysEx: ");

    for (unsigned i = 0; i < length; ++i) {
        char byteStr[5];
        snprintf(byteStr, sizeof(byteStr), "%02X ", data[i]);
        strcat(receivedMessage, byteStr);
    }
}

void setup_midi_handlers()
{
    midiSerial.setHandleControlChange(handle_control_change);
    midiSerial.setHandleSystemExclusive(handleSysEx);

    // Send SysEx request
    sendSysExRequest();
}

void midi_transport_begin()
{
#ifdef HIDUINO
    Serial.begin(31250);
#else
    Serial.begin(115200);
    Serial1.begin(31250);
#endif

    midiSerial.begin(MIDI_CHANNEL_OMNI);
    setup_midi_handlers();
}

#ifndef HIDUINO
static void log_midi_cc(int controlNumber, int controlValue, int channel)
{
    infolog("Control Change: ");
    infolog(String(controlNumber));
    infolog(", ");
    infolog(String(controlValue));
    infolog(", ");
    infolog(String(channel));
    infolog("\n");
}
#endif

void __midi_send_cc(int controlNumber, int controlValue, int channel)
{
#ifndef HIDUINO
    log_midi_cc(controlNumber, controlValue, channel);
#endif
    midiSerial.sendControlChange(controlNumber, controlValue, channel);
}

#endif // MIDI_TRANSPORT_H