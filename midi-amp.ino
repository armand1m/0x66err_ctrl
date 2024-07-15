#include "RotaryEncoders.h"
#include "MainUI.h"
#include <MIDI.h>

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, midiSerial);

EncoderButton encoders[ENCODER_COUNT] = {
  EncoderButton(44, 42, 46),
  EncoderButton(45, 43, 47),
  EncoderButton(50, 48, 52),
  EncoderButton(51, 49, 53),
};

gslc_tsElemRef *AppHeader = NULL;
gslc_tsElemRef *KnobGauge1 = NULL;
gslc_tsElemRef *KnobGauge2 = NULL;
gslc_tsElemRef *KnobGauge3 = NULL;
gslc_tsElemRef *KnobGauge4 = NULL;
gslc_tsElemRef *KnobGauge5 = NULL;
gslc_tsElemRef *KnobGauge6 = NULL;
gslc_tsElemRef *KnobGauge7 = NULL;
gslc_tsElemRef *KnobGauge8 = NULL;
gslc_tsElemRef *KnobGaugeText1 = NULL;
gslc_tsElemRef *KnobGaugeText2 = NULL;

static int16_t DebugOut(char ch)
{
  if (ch == (char)'\n')
    Serial.println("");
  else
    Serial.write(ch);
  return 0;
}

void setup()
{
  Serial.begin(115200);
  gslc_InitDebug(&DebugOut);
  initializeGUI();
  setupEncoders(encoders, onEncoderSpin);

  Serial.println("Starting MIDI interface..");
  Serial1.begin(31250);
  midiSerial.begin(MIDI_CHANNEL_OMNI);
  Serial.println("MIDI interface initialized.");
}

void loop()
{
  gslc_Update(&m_gui);
  updateEncoders(encoders);
}

gslc_tsElemRef * getElemRefForEncoderKnobGauge(int encoderId) {
  switch (encoderId) {
    case 0: return KnobGauge1;
    case 1: return KnobGauge2;
    case 2: return KnobGauge3;
    case 3: return KnobGauge4;
    case 4: return KnobGauge5;
    case 5: return KnobGauge6;
    case 6: return KnobGauge7;
    case 7: return KnobGauge8;
    default: return NULL;
  }
}

void onEncoderSpin(EncoderButton &encoder)
{
  Serial.print("Sending control change: ");
  Serial.print(encoder.userId());
  Serial.print(", ");
  Serial.println(encoder.position());

  unsigned char controlNumber = static_cast<unsigned char>(encoder.userId());
  unsigned char controlValue = static_cast<unsigned char>(encoder.position());
  unsigned char channel = static_cast<unsigned char>(1);

  midiSerial.sendControlChange(controlNumber, controlValue, channel);
  Serial.println("Sent.");

  char knobGaugeString[10]; 
  gslc_tsElemRef* knobGaugeElementReference = getElemRefForEncoderKnobGauge(encoder.userId());
  long position = encoder.position();

  gslc_ElemXRingGaugeSetVal(&m_gui, knobGaugeElementReference, position);
  snprintf(knobGaugeString, 10, "%d", position);
  gslc_ElemSetTxtStr(&m_gui, knobGaugeElementReference, knobGaugeString);
}