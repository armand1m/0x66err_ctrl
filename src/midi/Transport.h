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
    ChannelState* state = get_channel_state(mainpage_channel_state.channel);
    gslc_tsElemRef* toggle = get_toggle_by_cc_number(number);

    bool new_value = value > 0;
    if (toggle != NULL) {
        gslc_tsElem* element = gslc_GetElemFromRef(&gui_global, toggle);
        set_toggle_state({
            .gui = &gui_global,
            .element = toggle,
            .value = new_value,
        });

        switch (element->nId) {
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

    gslc_tsElemRef* slider = get_slider_by_cc_number(number);

    if (slider != NULL) {
        gslc_tsElem* element = gslc_GetElemFromRef(&gui_global, slider);

        update_slider({
            .gui = &gui_global,
            .element = slider,
            .value = value,
        });

        switch (element->nId) {
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

    gslc_tsElemRef* gauge = get_gauge_by_cc_number(number);

    if (gauge != NULL) {
        gslc_tsElem* element = gslc_GetElemFromRef(&gui_global, gauge);
        EncoderButton encoder = get_encoder_by_cc_number(number);
        encoder.resetPosition(value);
        update_ring_gauge({
            .gui = &gui_global,
            .element = gauge,
            .value = value,
        });

        switch (element->nId) {
        case E_ELEM_KNOB_1:
            state->ring_gauge1 = value;
            break;

        case E_ELEM_KNOB_2:
            state->ring_gauge2 = value;
            break;

        case E_ELEM_KNOB_3:
            state->ring_gauge3 = value;
            break;

        case E_ELEM_KNOB_4:
            state->ring_gauge4 = value;
            break;
        }
    }

    save_state_to_eeprom();

    // TODO: track XYMap and save to eeprom as well
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

void send_midi_cc(int controlNumber, int controlValue, int channel)
{
#ifndef HIDUINO
    log_midi_cc(controlNumber, controlValue, channel);
#endif
    midiSerial.sendControlChange(controlNumber, controlValue, channel);
}

#endif // MIDI_TRANSPORT_H