//<App !Start!>
// FILE: [GUISliceProjects.ino]
// Created by GUIslice Builder version: [0.17.b24]
//
// GUIslice Builder Generated File
//
// For the latest guides, updates and support view:
// https://github.com/ImpulseAdventure/GUIslice
//
//<App !End!>

// ------------------------------------------------
// Headers to include
// ------------------------------------------------
#include "GUISliceProjects_GSLC.h"


// ------------------------------------------------
// Program Globals
// ------------------------------------------------

// Save some element references for direct access
//<Save_References !Start!>
gslc_tsElemRef* AppHeader         = NULL;
gslc_tsElemRef* BackHomeButton    = NULL;
gslc_tsElemRef* KnobGauge1        = NULL;
gslc_tsElemRef* KnobGauge2        = NULL;
gslc_tsElemRef* KnobGauge3        = NULL;
gslc_tsElemRef* KnobGauge4        = NULL;
gslc_tsElemRef* KnobGaugeText1    = NULL;
gslc_tsElemRef* KnobGaugeText2    = NULL;
gslc_tsElemRef* KnobGaugeText3    = NULL;
gslc_tsElemRef* KnobGaugeText4    = NULL;
gslc_tsElemRef* SendXMidiMsg      = NULL;
gslc_tsElemRef* SendYMidiMsg      = NULL;
gslc_tsElemRef* Toggle1Text       = NULL;
gslc_tsElemRef* Toggle2Text       = NULL;
gslc_tsElemRef* Toggle3Text       = NULL;
gslc_tsElemRef* Toggle4Text       = NULL;
gslc_tsElemRef* XyMapBox          = NULL;
gslc_tsElemRef* XyMapButton       = NULL;
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
gslc_tsElemRef* m_pElemToggle4    = NULL;
//<Save_References !End!>

// Define debug message function
static int16_t DebugOut(char ch) { if (ch == (char)'\n') Serial.println(""); else Serial.write(ch); return 0; }

// ------------------------------------------------
// Callback Methods
// ------------------------------------------------
// Common Button callback
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
          ;
        }
        break;
      case E_ELEM_TOGGLE2:
        // TODO Add code for Toggle button ON/OFF state
        if (gslc_ElemXTogglebtnGetState(&m_gui, m_pElemToggle2)) {
          ;
        }
        break;
      case E_ELEM_TOGGLE3:
        // TODO Add code for Toggle button ON/OFF state
        if (gslc_ElemXTogglebtnGetState(&m_gui, m_pElemToggle3)) {
          ;
        }
        break;
      case E_ELEM_TOGGLE4:
        // TODO Add code for Toggle button ON/OFF state
        if (gslc_ElemXTogglebtnGetState(&m_gui, m_pElemToggle4)) {
          ;
        }
        break;
      case E_ELEM_XYMAP_BTN:
        gslc_SetPageCur(&m_gui, E_PG_XYMAP);
        break;
      case E_ELEM_BTN_BACKHOME:
        gslc_SetPageCur(&m_gui, E_PG_MAIN);
        break;
      case E_ELEM_BOX1:
        break;
      case E_ELEM_BTN_SEND_X_MSG:
        gslc_SetPageCur(&m_gui, E_PG_MAIN);
        break;
      case E_ELEM_BTN_SEND_Y_MSG:
        gslc_SetPageCur(&m_gui, E_PG_MAIN);
        break;
//<Button Enums !End!>
      default:
        break;
    }
  }
  return true;
}
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

// Callback function for when a slider's position has been updated
bool CbSlidePos(void* pvGui,void* pvElemRef,int16_t nPos)
{
  gslc_tsGui*     pGui     = (gslc_tsGui*)(pvGui);
  gslc_tsElemRef* pElemRef = (gslc_tsElemRef*)(pvElemRef);
  gslc_tsElem*    pElem    = gslc_GetElemFromRef(pGui,pElemRef);
  int16_t         nVal;

  // From the element's ID we can determine which slider was updated.
  switch (pElem->nId) {
//<Slider Enums !Start!>
    case E_ELEM_SLIDER1:
      // Fetch the slider position
      nVal = gslc_ElemXSliderGetPos(pGui,m_pElemSlider1);
      break;
    case E_ELEM_SLIDER2:
      // Fetch the slider position
      nVal = gslc_ElemXSliderGetPos(pGui,m_pElemSlider1_2);
      break;
    case E_ELEM_SLIDER3:
      // Fetch the slider position
      nVal = gslc_ElemXSliderGetPos(pGui,m_pElemSlider1_3);
      break;
    case E_ELEM_SLIDER4:
      // Fetch the slider position
      nVal = gslc_ElemXSliderGetPos(pGui,m_pElemSlider1_4);
      break;
    case E_ELEM_SLIDER5:
      // Fetch the slider position
      nVal = gslc_ElemXSliderGetPos(pGui,m_pElemSlider1_5);
      break;
    case E_ELEM_SLIDER6:
      // Fetch the slider position
      nVal = gslc_ElemXSliderGetPos(pGui,m_pElemSlider1_6);
      break;
    case E_ELEM_SLIDER7:
      // Fetch the slider position
      nVal = gslc_ElemXSliderGetPos(pGui,m_pElemSlider1_7);
      break;

//<Slider Enums !End!>
    default:
      break;
  }

  return true;
}

bool CbTickScanner(void* pvGui,void* pvScope)
{
  gslc_tsGui*     pGui      = (gslc_tsGui*)(pvGui);
  gslc_tsElemRef* pElemRef  = (gslc_tsElemRef*)(pvScope);
  gslc_tsElem*    pElem     = gslc_GetElemFromRef(pGui,pElemRef);

  //TODO add your custom code here 

  return true;
}

void setup()
{
  // ------------------------------------------------
  // Initialize
  // ------------------------------------------------
  Serial.begin(9600);
  // Wait for USB Serial 
  //delay(1000);  // NOTE: Some devices require a delay after Serial.begin() before serial port can be used

  gslc_InitDebug(&DebugOut);

  // ------------------------------------------------
  // Create graphic elements
  // ------------------------------------------------
  InitGUIslice_gen();

}

// -----------------------------------
// Main event loop
// -----------------------------------
void loop()
{

  // ------------------------------------------------
  // Update GUI Elements
  // ------------------------------------------------
  
  //TODO - Add update code for any text, gauges, or sliders
  
  // ------------------------------------------------
  // Periodically call GUIslice update function
  // ------------------------------------------------
  gslc_Update(&m_gui);
    
}
