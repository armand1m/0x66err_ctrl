#ifndef MIDI_TRANSPORT_H
#define MIDI_TRANSPORT_H
#include "../Loggers.h"
#include "../components/RingGauge.h"
#include "../components/Slider.h"
#include "../components/Toggle.h"
#include "../references/UIGlobalRefs.h"
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
    gslc_tsElemRef* toggle = get_toggle_by_cc_number(number);

    if (toggle != NULL) {
        set_toggle_state({
            .gui = &gui_global,
            .element = toggle,
            .value = value > 0,
        });
        return;
    }

    gslc_tsElemRef* slider = get_slider_by_cc_number(number);

    if (slider != NULL) {
        return update_slider({
            .gui = &gui_global,
            .element = slider,
            .value = value,
        });
    }

    gslc_tsElemRef* gauge = get_gauge_by_cc_number(number);

    if (gauge != NULL) {
        EncoderButton encoder = get_encoder_by_cc_number(number);
        encoder.resetPosition(value);
        return update_ring_gauge({
            .gui = &gui_global,
            .element = gauge,
            .value = value,
        });
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

void send_midi_cc(int controlNumber, int controlValue, int channel)
{
    log_midi_cc(controlNumber, controlValue, channel);
    midiSerial.sendControlChange(controlNumber, controlValue, channel);
}

#endif // MIDI_TRANSPORT_H