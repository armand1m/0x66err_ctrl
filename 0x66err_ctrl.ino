// Define this flag when building the firmware before flashing HIDUINO
#define HIDUINO

#include "Loggers.h"
#include "MidiCCMaps.h"
#include "RotaryEncoders.h"
#include "UI.h"
#include "UIReferences.h"
#include <MIDI.h>

#ifdef HIDUINO
MIDI_CREATE_INSTANCE(HardwareSerial, Serial, midiSerial);
#else
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, midiSerial);
#endif

void setup() {
#ifdef HIDUINO
  Serial.begin(31250);
#else
  Serial.begin(115200);
  Serial1.begin(31250);
#endif

  midiSerial.begin(MIDI_CHANNEL_OMNI);
  gslc_InitDebug(&DebugOut);
  InitGUIslice_gen();
  setupEncoders(encoders, onEncoderSpin, onEncoderClick);
}

void loop() {
  gslc_Update(&m_gui);
  updateEncoders(encoders);
}

void sendCC(int controlNumber, int controlValue, int channel) {
  logControlChange(controlNumber, controlValue, channel);
  midiSerial.sendControlChange(controlNumber, controlValue, channel);
}

void onEncoderClick(EncoderButton &encoder) {
  int index = encoder.userId();
  gslc_tsElemRef *toggleElementReference = getElemRefForToggle(index);

  bool state = !gslc_ElemXTogglebtnGetState(&m_gui, toggleElementReference);
  gslc_ElemXTogglebtnSetState(&m_gui, toggleElementReference, state);

  if (state) {
    sendCC(toggle_midi_cc[index], 127, 1);
  } else {
    sendCC(toggle_midi_cc[index], 0, 1);
  }
}

void onEncoderSpin(EncoderButton &encoder) {
  if (encoder.position() <= 0) {
    encoder.resetPosition(0);
  }

  if (encoder.position() >= 127) {
    encoder.resetPosition(127);
  }

  int controlValue = encoder.position();
  int controlNumber = knob_midi_cc[encoder.userId()];
  int channel = 1;

  sendCC(controlNumber, controlValue, channel);

  char knobGaugeString[10];
  gslc_tsElemRef *knobGaugeElementReference =
      getElemRefForEncoderKnobGauge(encoder.userId());
  long renderedPosition = map(encoder.position(), 0, 127, 0, 100);

  gslc_ElemXRingGaugeSetVal(&m_gui, knobGaugeElementReference,
                            renderedPosition);
  snprintf(knobGaugeString, 10, "%d", renderedPosition);
  gslc_ElemSetTxtStr(&m_gui, knobGaugeElementReference, knobGaugeString);
}

bool CbBtnCommon(void *pvGui, void *pvElemRef, gslc_teTouch eTouch, int16_t nX,
                 int16_t nY) {
  gslc_tsGui *pGui = (gslc_tsGui *)(pvGui);
  gslc_tsElemRef *pElemRef = (gslc_tsElemRef *)(pvElemRef);
  gslc_tsElem *pElem = gslc_GetElemFromRef(pGui, pElemRef);
  int index = getElemRefCCIndexById(pElem->nId);

  if (eTouch == GSLC_TOUCH_UP_IN) {
    if (gslc_ElemXTogglebtnGetState(&m_gui, pElemRef)) {
      sendCC(toggle_midi_cc[index], 127, 1);
    } else {
      sendCC(toggle_midi_cc[index], 0, 1);
    }
  }

  return true;
}

/**
 * This is the callback for the EQ sliders.
 * This function primarily identifies which slider was moved and sends the
 * corresponding MIDI CC message.
 */
bool CbSlidePos(void *pvGui, void *pvElemRef, int16_t nPos) {
  gslc_tsGui *pGui = (gslc_tsGui *)(pvGui);
  gslc_tsElemRef *pElemRef = (gslc_tsElemRef *)(pvElemRef);
  gslc_tsElem *pElem = gslc_GetElemFromRef(pGui, pElemRef);
  int16_t nVal = gslc_ElemXSliderGetPos(pGui, pElemRef);
  int index = getElemRefCCIndexById(pElem->nId);

  int controlNumber = slider_midi_cc[index];
  int controlValue = map(nVal, 0, 100, 127, 0);
  int channel = 1;

  sendCC(controlNumber, controlValue, channel);

  return true;
}
