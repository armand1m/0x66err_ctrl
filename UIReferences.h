#include "UI.h"

gslc_tsElemRef *AppHeader = NULL;
gslc_tsElemRef *KnobGauge1 = NULL;
gslc_tsElemRef *KnobGauge2 = NULL;
gslc_tsElemRef *KnobGauge3 = NULL;
gslc_tsElemRef *KnobGauge4 = NULL;
gslc_tsElemRef *KnobGaugeText1 = NULL;
gslc_tsElemRef *KnobGaugeText2 = NULL;
gslc_tsElemRef *KnobGaugeText3 = NULL;
gslc_tsElemRef *KnobGaugeText4 = NULL;
gslc_tsElemRef *Toggle1Text = NULL;
gslc_tsElemRef *Toggle2Text = NULL;
gslc_tsElemRef *Toggle3Text = NULL;
gslc_tsElemRef *Toggle4Text = NULL;
gslc_tsElemRef *m_pElemSlider1 = NULL;
gslc_tsElemRef *m_pElemSlider1_2 = NULL;
gslc_tsElemRef *m_pElemSlider1_3 = NULL;
gslc_tsElemRef *m_pElemSlider1_4 = NULL;
gslc_tsElemRef *m_pElemSlider1_5 = NULL;
gslc_tsElemRef *m_pElemSlider1_6 = NULL;
gslc_tsElemRef *m_pElemSlider1_7 = NULL;
gslc_tsElemRef *m_pElemToggle1 = NULL;
gslc_tsElemRef *m_pElemToggle2 = NULL;
gslc_tsElemRef *m_pElemToggle3 = NULL;
gslc_tsElemRef *m_pElemToggle4 = NULL;

gslc_tsElemRef *getElemRefForEncoderKnobGauge(int encoderId) {
  switch (encoderId) {
  case 0:
    return KnobGauge1;
  case 1:
    return KnobGauge2;
  case 2:
    return KnobGauge3;
  case 3:
    return KnobGauge4;
  default:
    return NULL;
  }
}

gslc_tsElemRef *getElemRefForToggle(int encoderId) {
  switch (encoderId) {
  case 0:
    return m_pElemToggle1;
  case 1:
    return m_pElemToggle2;
  case 2:
    return m_pElemToggle3;
  case 3:
    return m_pElemToggle4;
  default:
    return NULL;
  }
}

gslc_tsElemRef *getElemRefById(int16_t id) {
  switch (id) {
  case E_ELEM_TOGGLE1:
    return m_pElemToggle1;
  case E_ELEM_TOGGLE2:
    return m_pElemToggle2;
  case E_ELEM_TOGGLE3:
    return m_pElemToggle3;
  case E_ELEM_TOGGLE4:
    return m_pElemToggle4;
  case E_ELEM_SLIDER1:
    return m_pElemSlider1;
  case E_ELEM_SLIDER2:
    return m_pElemSlider1_2;
  case E_ELEM_SLIDER3:
    return m_pElemSlider1_3;
  case E_ELEM_SLIDER4:
    return m_pElemSlider1_4;
  case E_ELEM_SLIDER5:
    return m_pElemSlider1_5;
  case E_ELEM_SLIDER6:
    return m_pElemSlider1_6;
  case E_ELEM_SLIDER7:
    return m_pElemSlider1_7;
  default:
    return NULL;
  }
}

int getElemRefCCIndexById(int16_t id) {
  switch (id) {
  // toggle_midi_cc
  case E_ELEM_TOGGLE1:
    return 0;
  case E_ELEM_TOGGLE2:
    return 1;
  case E_ELEM_TOGGLE3:
    return 2;
  case E_ELEM_TOGGLE4:
    return 3;

  // slider_midi_cc
  case E_ELEM_SLIDER1:
    return 0;
  case E_ELEM_SLIDER2:
    return 1;
  case E_ELEM_SLIDER3:
    return 2;
  case E_ELEM_SLIDER4:
    return 3;
  case E_ELEM_SLIDER5:
    return 4;
  case E_ELEM_SLIDER6:
    return 5;
  case E_ELEM_SLIDER7:
    return 6;
  default:
    return -1;
  }
}
