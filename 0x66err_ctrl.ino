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

/**
 * This is the callback for the toggles on the screen only.
 * This function primarily identifies which toggle was pressed and sends the
 * corresponding MIDI CC message.
 */
bool CbBtnCommon(void *pvGui, void *pvElemRef, gslc_teTouch eTouch, int16_t nX,
                 int16_t nY) {
  gslc_tsGui *pGui = (gslc_tsGui *)(pvGui);
  gslc_tsElemRef *pElemRef = (gslc_tsElemRef *)(pvElemRef);
  gslc_tsElem *pElem = gslc_GetElemFromRef(pGui, pElemRef);

  switch (pElem->nId) {
  case E_ELEM_XYMAP_BTN:
    gslc_SetPageCur(&m_gui, E_PG_XYMAP);
    return true;

  case E_ELEM_BTN_BACKHOME:
    gslc_SetPageCur(&m_gui, E_PG_MAIN);
    return true;
  
  case E_ELEM_BTN_SEND_X_MSG:
    sendCC(xy_map_midi_cc[0], map(xyMapCurrentX, 12, 468, 0, 127), 1);
    return true;

  case E_ELEM_BTN_SEND_Y_MSG:
    sendCC(xy_map_midi_cc[1], map(xyMapCurrentY, 42, 308, 127, 0), 1);
    return true;
  }

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

bool CbTickScanner(void *pvGui, void *pvScope) {
  gslc_tsGui *pGui = (gslc_tsGui *)(pvGui);
  gslc_tsElemRef *pElemRef = (gslc_tsElemRef *)(pvScope);
  gslc_tsElem *pElem = gslc_GetElemFromRef(pGui, pElemRef);

  // TODO add your custom code here

  return true;
}
// Example logarithmic mapping function
float mapLog(float x, float in_min, float in_max, float out_min, float out_max) {
  return out_min + (out_max - out_min) * ((log(x) - log(in_min)) / (log(in_max) - log(in_min)));
}
// Touch event callback function
bool CbTouch(void *pvGui, void *pvElemRef, gslc_teTouch eTouch, int16_t nX,
             int16_t nY) {
  if (eTouch == GSLC_TOUCH_DOWN_IN || eTouch == GSLC_TOUCH_MOVE_IN ||
      eTouch == GSLC_TOUCH_UP_IN) {

    // Limit the touch coordinates to the box boundaries
    if (nX < 12)
      nX = 12;

    if (nX > 468)
      nX = 468;

    if (nY < 42)
      nY = 42;

    if (nY > 308)
      nY = 308;

    // Erase previous lines
    renderXYMap(GSLC_COL_BLACK);

    // Update current line positions
    xyMapCurrentX = nX;
    xyMapCurrentY = nY;

    // Draw new lines at the touch coordinates
    renderXYMap(GSLC_COL_GRAY_LT2);

    // Send midi codes
    sendCC(xy_map_midi_cc[0], mapLog(xyMapCurrentX, 12, 468, 0, 127), 1);
    sendCC(xy_map_midi_cc[1], map(xyMapCurrentY, 42, 308, 125, -21), 1);
  }

  return true;
}