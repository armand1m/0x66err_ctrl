#ifndef MIDI_TRANSPORT_H
#define MIDI_TRANSPORT_H
#include "../Loggers.h"
#include <MIDI.h>

#ifdef HIDUINO
MIDI_CREATE_INSTANCE(HardwareSerial, Serial, midiSerial);
#else
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, midiSerial);
#endif

void midi_transport_begin()
{
#ifdef HIDUINO
    Serial.begin(31250);
#else
    Serial.begin(115200);
    Serial1.begin(31250);
#endif

    midiSerial.begin(MIDI_CHANNEL_OMNI);
}

static void log_midi_cc(int controlNumber, int controlValue, int channel)
{
    log("Control Change: ");
    log(String(controlNumber));
    log(", ");
    log(String(controlValue));
    log(", ");
    log(String(channel));
    log("\n");
}

void send_midi_cc(int controlNumber, int controlValue, int channel)
{
    log_midi_cc(controlNumber, controlValue, channel);
    midiSerial.sendControlChange(controlNumber, controlValue, channel);
}
#endif // MIDI_TRANSPORT_H