#include "RotaryEncoders.h"
#include "MainUI.h"
#include <MIDI.h>

#define HIDUINO

#ifdef HIDUINO
MIDI_CREATE_INSTANCE(HardwareSerial, Serial, midiSerial);
#else
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, midiSerial);
#endif

EncoderButton encoders[ENCODER_COUNT] = {
  EncoderButton(44, 42, 46),
  EncoderButton(45, 43, 47),
  EncoderButton(50, 48, 52),
  EncoderButton(51, 49, 53),
};

// https://anotherproducer.com/online-tools-for-musicians/midi-cc-list/
byte knob_midi_cc[] = {16, 17, 18, 19};
byte slider_midi_cc[] = {20, 21, 22, 23, 24, 25, 26};
byte toggle_midi_cc[] = {28, 29, 30};

gslc_tsElemRef* AppHeader         = NULL;
gslc_tsElemRef* KnobGauge1        = NULL;
gslc_tsElemRef* KnobGauge2        = NULL;
gslc_tsElemRef* KnobGauge3        = NULL;
gslc_tsElemRef* KnobGauge4        = NULL;
gslc_tsElemRef* KnobGaugeText1    = NULL;
gslc_tsElemRef* KnobGaugeText2    = NULL;
gslc_tsElemRef* KnobGaugeText3    = NULL;
gslc_tsElemRef* KnobGaugeText4    = NULL;
gslc_tsElemRef* m_pElemSlider1    = NULL;
gslc_tsElemRef* m_pElemSlider1_2  = NULL;
gslc_tsElemRef* m_pElemSlider1_3  = NULL;
gslc_tsElemRef* m_pElemSlider1_4  = NULL;
gslc_tsElemRef* m_pElemSlider1_5  = NULL;
gslc_tsElemRef* m_pElemSlider1_6  = NULL;
gslc_tsElemRef* m_pElemSlider1_7  = NULL;
gslc_tsElemRef* m_pElemToggle1    = NULL;
gslc_tsElemRef* m_pElemToggle2    = NULL;
gslc_tsElemRef* m_pElemToggle3    = NULL;

// TODO: attribute midi CC values to toggles
bool CbBtnCommon(void* pvGui,void *pvElemRef,gslc_teTouch eTouch,int16_t nX,int16_t nY)
{
  // Typecast the parameters to match the GUI and element types
  gslc_tsGui*     pGui     = (gslc_tsGui*)(pvGui);
  gslc_tsElemRef* pElemRef = (gslc_tsElemRef*)(pvElemRef);
  gslc_tsElem*    pElem    = gslc_GetElemFromRef(pGui,pElemRef);

  if ( eTouch == GSLC_TOUCH_UP_IN ) {
    // From the element's ID we can determine which button was pressed.
    switch (pElem->nId) {
//<Button Enums !Start!>
      case E_ELEM_TOGGLE1:
        // TODO Add code for Toggle button ON/OFF state
        if (gslc_ElemXTogglebtnGetState(&m_gui, m_pElemToggle1)) {
          midiSerial.sendControlChange(toggle_midi_cc[0], 127, 1);
        } else {
          midiSerial.sendControlChange(toggle_midi_cc[0], 0, 1);
        }
        break;
      case E_ELEM_TOGGLE2:
        // TODO Add code for Toggle button ON/OFF state
        if (gslc_ElemXTogglebtnGetState(&m_gui, m_pElemToggle2)) {
          midiSerial.sendControlChange(toggle_midi_cc[1], 127, 1);
        } else {
          midiSerial.sendControlChange(toggle_midi_cc[1], 0, 1);
        }
        break;
      case E_ELEM_TOGGLE3:
        // TODO Add code for Toggle button ON/OFF state
        if (gslc_ElemXTogglebtnGetState(&m_gui, m_pElemToggle3)) {
          midiSerial.sendControlChange(toggle_midi_cc[2], 127, 1);
        } else {
          midiSerial.sendControlChange(toggle_midi_cc[2], 0, 1);
        }
        break;
//<Button Enums !End!>
      default:
        break;
    }
  }
  return true;
}

// TODO: setup midi CC channels for the EQ
// Callback function for when a slider's position has been updated
bool CbSlidePos(void* pvGui,void* pvElemRef,int16_t nPos)
{
  gslc_tsGui*     pGui     = (gslc_tsGui*)(pvGui);
  gslc_tsElemRef* pElemRef = (gslc_tsElemRef*)(pvElemRef);
  gslc_tsElem*    pElem    = gslc_GetElemFromRef(pGui,pElemRef);
  int16_t         nVal;
  int             sliderIndex = 0;

  // From the element's ID we can determine which slider was updated.
  switch (pElem->nId) {
//<Slider Enums !Start!>
    case E_ELEM_SLIDER1:
      // Fetch the slider position
      nVal = gslc_ElemXSliderGetPos(pGui,m_pElemSlider1);
      sliderIndex = 0;
      break;
    case E_ELEM_SLIDER2:
      // Fetch the slider position
      nVal = gslc_ElemXSliderGetPos(pGui,m_pElemSlider1_2);
      sliderIndex = 1;
      break;
    case E_ELEM_SLIDER3:
      // Fetch the slider position
      nVal = gslc_ElemXSliderGetPos(pGui,m_pElemSlider1_3);
      sliderIndex = 2;
      break;
    case E_ELEM_SLIDER4:
      // Fetch the slider position
      nVal = gslc_ElemXSliderGetPos(pGui,m_pElemSlider1_4);
      sliderIndex = 3;
      break;
    case E_ELEM_SLIDER5:
      // Fetch the slider position
      nVal = gslc_ElemXSliderGetPos(pGui,m_pElemSlider1_5);
      sliderIndex = 4;
      break;
    case E_ELEM_SLIDER6:
      // Fetch the slider position
      nVal = gslc_ElemXSliderGetPos(pGui,m_pElemSlider1_6);
      sliderIndex = 5;
      break;
    case E_ELEM_SLIDER7:
      // Fetch the slider position
      nVal = gslc_ElemXSliderGetPos(pGui,m_pElemSlider1_7);
      sliderIndex = 6;
      break;

//<Slider Enums !End!>
    default:
      break;
  }

  midiSerial.sendControlChange(slider_midi_cc[sliderIndex], map(nVal, 0, 100, 0, 127), 1);

  return true;
}

static int16_t DebugOut(char ch)
{
  #ifdef HIDUINO
    // noop
  #else
    if (ch == (char)'\n')
      Serial.println("");
    else
      Serial.write(ch);
  #endif
  
  return 0;
}

static void log(const String &message)
{
  #ifdef HIDUINO
    // noop
  #else
    if (message.equals("\n")) {
      Serial.println("");
    } else {
      Serial.print(message);
    }
  #endif
}

void setup()
{
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
    default: return NULL;
  }
}

void onEncoderClick(EncoderButton &encoder)
{
  // TODO: map clicks to activate the toggles in the screen
}

void onEncoderSpin(EncoderButton &encoder)
{
  if (encoder.position() <= 0) {
    encoder.resetPosition(0);
  }

  if (encoder.position() >= 127) {
    encoder.resetPosition(127);
  }
  
  int controlValue = encoder.position();
  int controlNumber = knob_midi_cc[encoder.userId()];
  int channel = 1;

  log("Sending Control Change: ");
  log(String(controlNumber));
  log(", ");
  log(String(controlValue));
  log(", ");
  log(String(channel));
  log("\n");

  midiSerial.sendControlChange(controlNumber, controlValue, channel);

  char knobGaugeString[10];
  gslc_tsElemRef* knobGaugeElementReference = getElemRefForEncoderKnobGauge(encoder.userId());
  long renderedPosition = map(encoder.position(), 0, 127, 0, 100);

  gslc_ElemXRingGaugeSetVal(&m_gui, knobGaugeElementReference, renderedPosition);
  snprintf(knobGaugeString, 10, "%d", renderedPosition);
  gslc_ElemSetTxtStr(&m_gui, knobGaugeElementReference, knobGaugeString);
}