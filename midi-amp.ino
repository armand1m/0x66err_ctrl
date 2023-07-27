#include "RotaryEncoders.h"
#include "GUISliceProjects_GSLC.h"

EncoderButton encoders[ENCODER_COUNT] = {
  EncoderButton(51, 49, 53),
  EncoderButton(50, 48, 52),
  EncoderButton(44, 42, 46),
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

// Define debug message function
static int16_t DebugOut(char ch)
{
  if (ch == (char)'\n')
    Serial.println("");
  else
    Serial.write(ch);
  return 0;
}

// ------------------------------------------------
// Callback Methods
// ------------------------------------------------
//<Button Callback !Start!>
//<Button Callback !End!>
//<Checkbox Callback !Start!>
//<Checkbox Callback !End!>
//<Keypad Callback !Start!>
//<Keypad Callback !End!>
//<Spinner Callback !Start!>
//<Spinner Callback !End!>
//<Listbox Callback !Start!>
//<Listbox Callback !End!>
//<Draw Callback !Start!>
//<Draw Callback !End!>
//<Slider Callback !Start!>
//<Slider Callback !End!>
//<Tick Callback !Start!>
//<Tick Callback !End!>

void setup()
{
  Serial.begin(115200);
  gslc_InitDebug(&DebugOut);
  InitGUIslice_gen();
  setupEncoders(encoders, onEncoderSpin);
}

void loop()
{
  // TODO - Add update code for any text, gauges, or sliders

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
  // debugRotary(encoder);
  char knobGaugeString[10];
  gslc_tsElemRef* knobGaugeElementReference = getElemRefForEncoderKnobGauge(encoder.userId());
  long position = encoder.position();

  gslc_ElemXRingGaugeSetVal(&m_gui, knobGaugeElementReference, position);
  snprintf(knobGaugeString, 10, "%d", position);
  gslc_ElemSetTxtStr(&m_gui, knobGaugeElementReference, knobGaugeString);
}