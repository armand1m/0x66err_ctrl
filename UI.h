//<File !Start!>
// FILE: [GUISliceProjects_GSLC.h]
// Created by GUIslice Builder version: [0.17.b24]
//
// GUIslice Builder Generated GUI Framework File
//
// For the latest guides, updates and support view:
// https://github.com/ImpulseAdventure/GUIslice
//
//<File !End!>

#ifndef _GUISLICE_GEN_H
#define _GUISLICE_GEN_H

// ------------------------------------------------
// Headers to include
// ------------------------------------------------
#include "GUIslice.h"
#include "GUIslice_drv.h"

// Include any extended elements
//<Includes !Start!>
// Include extended elements
#include "elem/XRingGauge.h"
#include "elem/XSlider.h"
#include "elem/XTogglebtn.h"
//<Includes !End!>

// ------------------------------------------------
// Headers and Defines for fonts
// Note that font files are located within the Adafruit-GFX library folder:
// ------------------------------------------------
//<Fonts !Start!>
#if defined(DRV_DISP_TFT_ESPI)
#error E_PROJECT_OPTIONS tab->Graphics Library should be TFT_eSPI
#endif
#include <Adafruit_GFX.h>
//<Fonts !End!>

// ------------------------------------------------
// Defines for resources
// ------------------------------------------------
//<Resources !Start!>
//<Resources !End!>

// ------------------------------------------------
// Enumerations for pages, elements, fonts, images
// ------------------------------------------------
//<Enum !Start!>
enum { E_PG_MAIN, E_PG2 };
enum {
  E_ELEM_APPHEADER,
  E_ELEM_KNOB_1,
  E_ELEM_KNOB_2,
  E_ELEM_KNOB_3,
  E_ELEM_KNOB_4,
  E_ELEM_RINGGAUGE1,
  E_ELEM_RINGGAUGE2,
  E_ELEM_RINGGAUGE3,
  E_ELEM_RINGGAUGE4,
  E_ELEM_SLIDER1,
  E_ELEM_SLIDER2,
  E_ELEM_SLIDER3,
  E_ELEM_SLIDER4,
  E_ELEM_SLIDER5,
  E_ELEM_SLIDER6,
  E_ELEM_SLIDER7,
  E_ELEM_TEXT10,
  E_ELEM_TEXT11,
  E_ELEM_TEXT12,
  E_ELEM_TEXT13,
  E_ELEM_TEXT14,
  E_ELEM_TEXT15,
  E_ELEM_TEXT17,
  E_ELEM_TEXT18,
  E_ELEM_TEXT19,
  E_ELEM_TEXT20,
  E_ELEM_TEXT21,
  E_ELEM_TEXT22,
  E_ELEM_TEXT23,
  E_ELEM_TEXT9,
  E_ELEM_TOGGLE1,
  E_ELEM_TOGGLE2,
  E_ELEM_TOGGLE3,
  E_ELEM_TOGGLE4,
  E_ELEM_TOGGLE_TEXT_1,
  E_ELEM_TOGGLE_TEXT_2,
  E_ELEM_TOGGLE_TEXT_3,
  E_ELEM_TOGGLE_TEXT_4
};
// Must use separate enum for fonts with MAX_FONT at end to use gslc_FontSet.
enum { E_BUILTIN15X24, E_BUILTIN20X32, E_BUILTIN5X8, MAX_FONT };
//<Enum !End!>

// ------------------------------------------------
// Instantiate the GUI
// ------------------------------------------------

// ------------------------------------------------
// Define the maximum number of elements and pages
// ------------------------------------------------
//<ElementDefines !Start!>
#define MAX_PAGE 2

#define MAX_ELEM_PG_MAIN 37                   // # Elems total on page
#define MAX_ELEM_PG_MAIN_RAM MAX_ELEM_PG_MAIN // # Elems in RAM

#define MAX_ELEM_PG2 1                // # Elems total on page
#define MAX_ELEM_PG2_RAM MAX_ELEM_PG2 // # Elems in RAM
//<ElementDefines !End!>

// ------------------------------------------------
// Create element storage
// ------------------------------------------------
gslc_tsGui m_gui;
gslc_tsDriver m_drv;
gslc_tsFont m_asFont[MAX_FONT];
gslc_tsPage m_asPage[MAX_PAGE];

//<GUI_Extra_Elements !Start!>
gslc_tsElem m_asPage1Elem[MAX_ELEM_PG_MAIN_RAM];
gslc_tsElemRef m_asPage1ElemRef[MAX_ELEM_PG_MAIN];
gslc_tsElem m_asPage2Elem[MAX_ELEM_PG2_RAM];
gslc_tsElemRef m_asPage2ElemRef[MAX_ELEM_PG2];
gslc_tsXRingGauge m_sXRingGauge2;
gslc_tsXRingGauge m_sXRingGauge1;
gslc_tsXRingGauge m_sXRingGauge3;
gslc_tsXRingGauge m_sXRingGauge4;
gslc_tsXTogglebtn m_asXToggle1;
gslc_tsXTogglebtn m_asXToggle2;
gslc_tsXTogglebtn m_asXToggle3;
gslc_tsXTogglebtn m_asXToggle4;
gslc_tsXSlider m_sXSlider1;
gslc_tsXSlider m_sXSlider2;
gslc_tsXSlider m_sXSlider3;
gslc_tsXSlider m_sXSlider4;
gslc_tsXSlider m_sXSlider5;
gslc_tsXSlider m_sXSlider6;
gslc_tsXSlider m_sXSlider7;

#define MAX_STR 100

//<GUI_Extra_Elements !End!>

// ------------------------------------------------
// Program Globals
// ------------------------------------------------

// Element References for direct access
//<Extern_References !Start!>
extern gslc_tsElemRef *AppHeader;
extern gslc_tsElemRef *KnobGauge1;
extern gslc_tsElemRef *KnobGauge2;
extern gslc_tsElemRef *KnobGauge3;
extern gslc_tsElemRef *KnobGauge4;
extern gslc_tsElemRef *KnobGaugeText1;
extern gslc_tsElemRef *KnobGaugeText2;
extern gslc_tsElemRef *KnobGaugeText3;
extern gslc_tsElemRef *KnobGaugeText4;
extern gslc_tsElemRef *Toggle1Text;
extern gslc_tsElemRef *Toggle2Text;
extern gslc_tsElemRef *Toggle3Text;
extern gslc_tsElemRef *Toggle4Text;
extern gslc_tsElemRef *m_pElemSlider1;
extern gslc_tsElemRef *m_pElemSlider1_2;
extern gslc_tsElemRef *m_pElemSlider1_3;
extern gslc_tsElemRef *m_pElemSlider1_4;
extern gslc_tsElemRef *m_pElemSlider1_5;
extern gslc_tsElemRef *m_pElemSlider1_6;
extern gslc_tsElemRef *m_pElemSlider1_7;
extern gslc_tsElemRef *m_pElemToggle1;
extern gslc_tsElemRef *m_pElemToggle2;
extern gslc_tsElemRef *m_pElemToggle3;
extern gslc_tsElemRef *m_pElemToggle4;
//<Extern_References !End!>

// Define debug message function
static int16_t DebugOut(char ch);

// ------------------------------------------------
// Callback Methods
// ------------------------------------------------
bool CbBtnCommon(void *pvGui, void *pvElemRef, gslc_teTouch eTouch, int16_t nX,
                 int16_t nY);
bool CbCheckbox(void *pvGui, void *pvElemRef, int16_t nSelId, bool bState);
bool CbDrawScanner(void *pvGui, void *pvElemRef, gslc_teRedrawType eRedraw);
bool CbKeypad(void *pvGui, void *pvElemRef, int16_t nState, void *pvData);
bool CbListbox(void *pvGui, void *pvElemRef, int16_t nSelId);
bool CbSlidePos(void *pvGui, void *pvElemRef, int16_t nPos);
bool CbSpinner(void *pvGui, void *pvElemRef, int16_t nState, void *pvData);
bool CbTickScanner(void *pvGui, void *pvScope);

// ------------------------------------------------
// Create page elements
// ------------------------------------------------
void InitGUIslice_gen() {
  gslc_tsElemRef *pElemRef = NULL;

  if (!gslc_Init(&m_gui, &m_drv, m_asPage, MAX_PAGE, m_asFont, MAX_FONT)) {
    return;
  }

  // ------------------------------------------------
  // Load Fonts
  // ------------------------------------------------
  //<Load_Fonts !Start!>
  if (!gslc_FontSet(&m_gui, E_BUILTIN15X24, GSLC_FONTREF_PTR, NULL, 3)) {
    return;
  }
  if (!gslc_FontSet(&m_gui, E_BUILTIN20X32, GSLC_FONTREF_PTR, NULL, 4)) {
    return;
  }
  if (!gslc_FontSet(&m_gui, E_BUILTIN5X8, GSLC_FONTREF_PTR, NULL, 1)) {
    return;
  }
  //<Load_Fonts !End!>

  //<InitGUI !Start!>
  gslc_PageAdd(&m_gui, E_PG_MAIN, m_asPage1Elem, MAX_ELEM_PG_MAIN_RAM,
               m_asPage1ElemRef, MAX_ELEM_PG_MAIN);
  gslc_PageAdd(&m_gui, E_PG2, m_asPage2Elem, MAX_ELEM_PG2_RAM, m_asPage2ElemRef,
               MAX_ELEM_PG2);

  // NOTE: The current page defaults to the first page added. Here we explicitly
  //       ensure that the main page is the correct page no matter the add
  //       order.
  gslc_SetPageCur(&m_gui, E_PG_MAIN);

  // Set Background to a flat color
  gslc_SetBkgndColor(&m_gui, GSLC_COL_BLACK);

  // -----------------------------------
  // PAGE: E_PG_MAIN

  // Create ring gauge E_ELEM_RINGGAUGE1
  static char m_sRingText2[11] = "0";
  pElemRef = gslc_ElemXRingGaugeCreate(
      &m_gui, E_ELEM_RINGGAUGE1, E_PG_MAIN, &m_sXRingGauge2,
      (gslc_tsRect){14, 54, 45, 45}, (char *)m_sRingText2, 11, E_BUILTIN5X8);
  gslc_ElemXRingGaugeSetValRange(&m_gui, pElemRef, 0, 100);
  gslc_ElemXRingGaugeSetVal(&m_gui, pElemRef, 0); // Set initial value
  gslc_ElemXRingGaugeSetAngleRange(&m_gui, pElemRef, 0, 360, false);
  gslc_ElemXRingGaugeSetColorActiveFlat(&m_gui, pElemRef, GSLC_COL_RED_DK1);
  gslc_ElemXRingGaugeSetColorInactive(&m_gui, pElemRef, GSLC_COL_GRAY);
  gslc_ElemSetTxtCol(&m_gui, pElemRef, GSLC_COL_WHITE);
  KnobGauge1 = pElemRef;

  // Create ring gauge E_ELEM_RINGGAUGE2
  static char m_sRingText1[11] = "0";
  pElemRef = gslc_ElemXRingGaugeCreate(
      &m_gui, E_ELEM_RINGGAUGE2, E_PG_MAIN, &m_sXRingGauge1,
      (gslc_tsRect){73, 54, 45, 45}, (char *)m_sRingText1, 11, E_BUILTIN5X8);
  gslc_ElemXRingGaugeSetValRange(&m_gui, pElemRef, 0, 100);
  gslc_ElemXRingGaugeSetVal(&m_gui, pElemRef, 0); // Set initial value
  gslc_ElemXRingGaugeSetColorActiveFlat(&m_gui, pElemRef, GSLC_COL_RED_DK1);
  gslc_ElemXRingGaugeSetColorInactive(&m_gui, pElemRef, GSLC_COL_GRAY);
  gslc_ElemSetTxtCol(&m_gui, pElemRef, GSLC_COL_WHITE);
  KnobGauge2 = pElemRef;

  // Create ring gauge E_ELEM_RINGGAUGE3
  static char m_sRingText3[11] = "0";
  pElemRef = gslc_ElemXRingGaugeCreate(
      &m_gui, E_ELEM_RINGGAUGE3, E_PG_MAIN, &m_sXRingGauge3,
      (gslc_tsRect){132, 54, 45, 45}, (char *)m_sRingText3, 11, E_BUILTIN5X8);
  gslc_ElemXRingGaugeSetValRange(&m_gui, pElemRef, 0, 127);
  gslc_ElemXRingGaugeSetVal(&m_gui, pElemRef, 0); // Set initial value
  gslc_ElemXRingGaugeSetThickness(&m_gui, pElemRef, 8);
  gslc_ElemXRingGaugeSetColorActiveFlat(&m_gui, pElemRef, GSLC_COL_RED_DK1);
  gslc_ElemXRingGaugeSetColorInactive(&m_gui, pElemRef, GSLC_COL_GRAY);
  gslc_ElemSetTxtCol(&m_gui, pElemRef, GSLC_COL_WHITE);
  KnobGauge3 = pElemRef;

  // Create ring gauge E_ELEM_RINGGAUGE4
  static char m_sRingText4[11] = "0";
  pElemRef = gslc_ElemXRingGaugeCreate(
      &m_gui, E_ELEM_RINGGAUGE4, E_PG_MAIN, &m_sXRingGauge4,
      (gslc_tsRect){191, 54, 45, 45}, (char *)m_sRingText4, 11, E_BUILTIN5X8);
  gslc_ElemXRingGaugeSetValRange(&m_gui, pElemRef, 0, 100);
  gslc_ElemXRingGaugeSetVal(&m_gui, pElemRef, 0); // Set initial value
  gslc_ElemXRingGaugeSetColorActiveFlat(&m_gui, pElemRef, GSLC_COL_RED_DK1);
  gslc_ElemXRingGaugeSetColorInactive(&m_gui, pElemRef, GSLC_COL_GRAY);
  gslc_ElemSetTxtCol(&m_gui, pElemRef, GSLC_COL_WHITE);
  KnobGauge4 = pElemRef;

  // Create E_ELEM_KNOB_1 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui, E_ELEM_KNOB_1, E_PG_MAIN,
                                (gslc_tsRect){23, 102, 24, 8}, (char *)"Gain",
                                0, E_BUILTIN5X8);
  gslc_ElemSetTxtAlign(&m_gui, pElemRef, GSLC_ALIGN_TOP_MID);
  gslc_ElemSetFillEn(&m_gui, pElemRef, false);
  gslc_ElemSetTxtCol(&m_gui, pElemRef, GSLC_COL_WHITE);
  KnobGaugeText1 = pElemRef;

  // Create E_ELEM_KNOB_2 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui, E_ELEM_KNOB_2, E_PG_MAIN,
                                (gslc_tsRect){73, 102, 45, 8}, (char *)"Low", 0,
                                E_BUILTIN5X8);
  gslc_ElemSetTxtAlign(&m_gui, pElemRef, GSLC_ALIGN_TOP_MID);
  gslc_ElemSetFillEn(&m_gui, pElemRef, false);
  gslc_ElemSetTxtCol(&m_gui, pElemRef, GSLC_COL_WHITE);
  KnobGaugeText2 = pElemRef;

  // Create E_ELEM_APPHEADER text label
  pElemRef = gslc_ElemCreateTxt(&m_gui, E_ELEM_APPHEADER, E_PG_MAIN,
                                (gslc_tsRect){190, 10, 285, 32},
                                (char *)"0x66err_ctrl", 0, E_BUILTIN20X32);
  gslc_ElemSetTxtAlign(&m_gui, pElemRef, GSLC_ALIGN_MID_MID);
  gslc_ElemSetFillEn(&m_gui, pElemRef, false);
  gslc_ElemSetTxtCol(&m_gui, pElemRef, GSLC_COL_WHITE);
  AppHeader = pElemRef;

  // Create E_ELEM_KNOB_3 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui, E_ELEM_KNOB_3, E_PG_MAIN,
                                (gslc_tsRect){143, 102, 18, 8}, (char *)"Mid",
                                0, E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui, pElemRef, false);
  gslc_ElemSetTxtCol(&m_gui, pElemRef, GSLC_COL_WHITE);
  KnobGaugeText3 = pElemRef;

  // Create E_ELEM_KNOB_4 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui, E_ELEM_KNOB_4, E_PG_MAIN,
                                (gslc_tsRect){203, 102, 24, 8}, (char *)"High",
                                0, E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui, pElemRef, false);
  gslc_ElemSetTxtCol(&m_gui, pElemRef, GSLC_COL_WHITE);
  KnobGaugeText4 = pElemRef;

  // Create toggle button E_ELEM_TOGGLE1
  pElemRef = gslc_ElemXTogglebtnCreate(
      &m_gui, E_ELEM_TOGGLE1, E_PG_MAIN, &m_asXToggle1,
      (gslc_tsRect){20, 141, 35, 20}, GSLC_COL_GRAY, GSLC_COL_RED_DK1,
      GSLC_COL_GRAY_LT3, true, false, &CbBtnCommon);
  m_pElemToggle1 = pElemRef;

  // Create toggle button E_ELEM_TOGGLE2
  pElemRef = gslc_ElemXTogglebtnCreate(
      &m_gui, E_ELEM_TOGGLE2, E_PG_MAIN, &m_asXToggle2,
      (gslc_tsRect){20, 181, 35, 20}, GSLC_COL_GRAY, GSLC_COL_RED_DK1,
      GSLC_COL_GRAY_LT3, true, false, &CbBtnCommon);
  m_pElemToggle2 = pElemRef;

  // Create toggle button E_ELEM_TOGGLE3
  pElemRef = gslc_ElemXTogglebtnCreate(
      &m_gui, E_ELEM_TOGGLE3, E_PG_MAIN, &m_asXToggle3,
      (gslc_tsRect){20, 221, 35, 20}, GSLC_COL_GRAY, GSLC_COL_RED_DK1,
      GSLC_COL_GRAY_LT3, true, false, &CbBtnCommon);
  m_pElemToggle3 = pElemRef;

  // Create toggle button E_ELEM_TOGGLE4
  pElemRef = gslc_ElemXTogglebtnCreate(
      &m_gui, E_ELEM_TOGGLE4, E_PG_MAIN, &m_asXToggle4,
      (gslc_tsRect){21, 262, 35, 20}, GSLC_COL_GRAY, GSLC_COL_RED_DK1,
      GSLC_COL_GRAY_LT3, true, false, &CbBtnCommon);
  m_pElemToggle4 = pElemRef;

  // Create E_ELEM_TOGGLE_TEXT_1 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui, E_ELEM_TOGGLE_TEXT_1, E_PG_MAIN,
                                (gslc_tsRect){60, 151, 42, 8},
                                (char *)"Octaver", 0, E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui, pElemRef, false);
  gslc_ElemSetTxtCol(&m_gui, pElemRef, GSLC_COL_WHITE);
  Toggle1Text = pElemRef;

  // Create E_ELEM_TOGGLE_TEXT_2 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui, E_ELEM_TOGGLE_TEXT_2, E_PG_MAIN,
                                (gslc_tsRect){60, 191, 54, 8},
                                (char *)"Overdrive", 0, E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui, pElemRef, false);
  gslc_ElemSetTxtCol(&m_gui, pElemRef, GSLC_COL_WHITE);
  Toggle2Text = pElemRef;

  // Create E_ELEM_TOGGLE_TEXT_3 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui, E_ELEM_TOGGLE_TEXT_3, E_PG_MAIN,
                                (gslc_tsRect){60, 231, 60, 8},
                                (char *)"Distortion", 0, E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui, pElemRef, false);
  gslc_ElemSetTxtCol(&m_gui, pElemRef, GSLC_COL_WHITE);
  Toggle3Text = pElemRef;

  // Create E_ELEM_TOGGLE_TEXT_4 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui, E_ELEM_TOGGLE_TEXT_4, E_PG_MAIN,
                                (gslc_tsRect){61, 272, 36, 8}, (char *)"Custom",
                                0, E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui, pElemRef, false);
  gslc_ElemSetTxtCol(&m_gui, pElemRef, GSLC_COL_WHITE);
  Toggle4Text = pElemRef;

  // Create slider E_ELEM_SLIDER1
  pElemRef = gslc_ElemXSliderCreate(
      &m_gui, E_ELEM_SLIDER1, E_PG_MAIN, &m_sXSlider1,
      (gslc_tsRect){140, 130, 20, 160}, 0, 100, 50, 5, true);
  gslc_ElemXSliderSetStyle(&m_gui, pElemRef, false, GSLC_COL_BLUE, 10, 5,
                           GSLC_COL_RED_DK1);
  gslc_ElemXSliderSetPosFunc(&m_gui, pElemRef, &CbSlidePos);
  m_pElemSlider1 = pElemRef;

  // Create slider E_ELEM_SLIDER2
  pElemRef = gslc_ElemXSliderCreate(
      &m_gui, E_ELEM_SLIDER2, E_PG_MAIN, &m_sXSlider2,
      (gslc_tsRect){190, 130, 20, 160}, 0, 100, 50, 5, true);
  gslc_ElemXSliderSetStyle(&m_gui, pElemRef, false, GSLC_COL_BLUE, 10, 5,
                           GSLC_COL_RED_DK1);
  gslc_ElemXSliderSetPosFunc(&m_gui, pElemRef, &CbSlidePos);
  m_pElemSlider1_2 = pElemRef;

  // Create slider E_ELEM_SLIDER3
  pElemRef = gslc_ElemXSliderCreate(
      &m_gui, E_ELEM_SLIDER3, E_PG_MAIN, &m_sXSlider3,
      (gslc_tsRect){240, 130, 20, 160}, 0, 100, 50, 5, true);
  gslc_ElemXSliderSetStyle(&m_gui, pElemRef, false, GSLC_COL_BLUE, 10, 5,
                           GSLC_COL_RED_DK1);
  gslc_ElemXSliderSetPosFunc(&m_gui, pElemRef, &CbSlidePos);
  m_pElemSlider1_3 = pElemRef;

  // Create slider E_ELEM_SLIDER4
  pElemRef = gslc_ElemXSliderCreate(
      &m_gui, E_ELEM_SLIDER4, E_PG_MAIN, &m_sXSlider4,
      (gslc_tsRect){290, 130, 20, 160}, 0, 100, 50, 5, true);
  gslc_ElemXSliderSetStyle(&m_gui, pElemRef, false, GSLC_COL_BLUE, 10, 5,
                           GSLC_COL_RED_DK1);
  gslc_ElemXSliderSetPosFunc(&m_gui, pElemRef, &CbSlidePos);
  m_pElemSlider1_4 = pElemRef;

  // Create slider E_ELEM_SLIDER5
  pElemRef = gslc_ElemXSliderCreate(
      &m_gui, E_ELEM_SLIDER5, E_PG_MAIN, &m_sXSlider5,
      (gslc_tsRect){340, 130, 20, 160}, 0, 100, 50, 5, true);
  gslc_ElemXSliderSetStyle(&m_gui, pElemRef, false, GSLC_COL_BLUE, 10, 5,
                           GSLC_COL_RED_DK1);
  gslc_ElemXSliderSetPosFunc(&m_gui, pElemRef, &CbSlidePos);
  m_pElemSlider1_5 = pElemRef;

  // Create slider E_ELEM_SLIDER6
  pElemRef = gslc_ElemXSliderCreate(
      &m_gui, E_ELEM_SLIDER6, E_PG_MAIN, &m_sXSlider6,
      (gslc_tsRect){390, 130, 20, 160}, 0, 100, 50, 5, true);
  gslc_ElemXSliderSetStyle(&m_gui, pElemRef, false, GSLC_COL_BLUE, 10, 5,
                           GSLC_COL_RED_DK1);
  gslc_ElemXSliderSetPosFunc(&m_gui, pElemRef, &CbSlidePos);
  m_pElemSlider1_6 = pElemRef;

  // Create slider E_ELEM_SLIDER7
  pElemRef = gslc_ElemXSliderCreate(
      &m_gui, E_ELEM_SLIDER7, E_PG_MAIN, &m_sXSlider7,
      (gslc_tsRect){440, 130, 20, 160}, 0, 100, 50, 5, true);
  gslc_ElemXSliderSetStyle(&m_gui, pElemRef, false, GSLC_COL_BLUE, 10, 5,
                           GSLC_COL_RED_DK1);
  gslc_ElemXSliderSetPosFunc(&m_gui, pElemRef, &CbSlidePos);
  m_pElemSlider1_7 = pElemRef;

  // Create E_ELEM_TEXT9 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui, E_ELEM_TEXT9, E_PG_MAIN,
                                (gslc_tsRect){141, 295, 24, 8}, (char *)"65hz",
                                0, E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui, pElemRef, false);
  gslc_ElemSetTxtCol(&m_gui, pElemRef, GSLC_COL_WHITE);

  // Create E_ELEM_TEXT10 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui, E_ELEM_TEXT10, E_PG_MAIN,
                                (gslc_tsRect){181, 295, 30, 8}, (char *)"125hz",
                                0, E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui, pElemRef, false);
  gslc_ElemSetTxtCol(&m_gui, pElemRef, GSLC_COL_WHITE);

  // Create E_ELEM_TEXT11 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui, E_ELEM_TEXT11, E_PG_MAIN,
                                (gslc_tsRect){231, 295, 30, 8}, (char *)"250hz",
                                0, E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui, pElemRef, false);
  gslc_ElemSetTxtCol(&m_gui, pElemRef, GSLC_COL_WHITE);

  // Create E_ELEM_TEXT12 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui, E_ELEM_TEXT12, E_PG_MAIN,
                                (gslc_tsRect){281, 295, 30, 8}, (char *)"500hz",
                                0, E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui, pElemRef, false);
  gslc_ElemSetTxtCol(&m_gui, pElemRef, GSLC_COL_WHITE);

  // Create E_ELEM_TEXT13 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui, E_ELEM_TEXT13, E_PG_MAIN,
                                (gslc_tsRect){331, 295, 24, 8}, (char *)"1kHz",
                                0, E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui, pElemRef, false);
  gslc_ElemSetTxtCol(&m_gui, pElemRef, GSLC_COL_WHITE);

  // Create E_ELEM_TEXT14 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui, E_ELEM_TEXT14, E_PG_MAIN,
                                (gslc_tsRect){381, 295, 24, 8}, (char *)"2kHz",
                                0, E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui, pElemRef, false);
  gslc_ElemSetTxtCol(&m_gui, pElemRef, GSLC_COL_WHITE);

  // Create E_ELEM_TEXT15 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui, E_ELEM_TEXT15, E_PG_MAIN,
                                (gslc_tsRect){431, 295, 24, 8}, (char *)"4kHz",
                                0, E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui, pElemRef, false);
  gslc_ElemSetTxtCol(&m_gui, pElemRef, GSLC_COL_WHITE);

  // Create E_ELEM_TEXT17 text label
  pElemRef = gslc_ElemCreateTxt(
      &m_gui, E_ELEM_TEXT17, E_PG_MAIN, (gslc_tsRect){250, 50, 210, 8},
      (char *)"Cause everyone's too scared to heal", 0, E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui, pElemRef, false);
  gslc_ElemSetTxtCol(&m_gui, pElemRef, GSLC_COL_WHITE);

  // Create E_ELEM_TEXT18 text label
  pElemRef = gslc_ElemCreateTxt(
      &m_gui, E_ELEM_TEXT18, E_PG_MAIN, (gslc_tsRect){250, 60, 216, 8},
      (char *)"They don't give a fuck how they feel", 0, E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui, pElemRef, false);
  gslc_ElemSetTxtCol(&m_gui, pElemRef, GSLC_COL_WHITE);

  // Create E_ELEM_TEXT19 text label
  pElemRef = gslc_ElemCreateTxt(
      &m_gui, E_ELEM_TEXT19, E_PG_MAIN, (gslc_tsRect){250, 70, 216, 8},
      (char *)"And I don't know how to deal anymore", 0, E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui, pElemRef, false);
  gslc_ElemSetTxtCol(&m_gui, pElemRef, GSLC_COL_WHITE);

  // Create E_ELEM_TEXT20 text label
  pElemRef = gslc_ElemCreateTxt(
      &m_gui, E_ELEM_TEXT20, E_PG_MAIN, (gslc_tsRect){250, 80, 174, 8},
      (char *)"Well maybe the damage is done", 0, E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui, pElemRef, false);
  gslc_ElemSetTxtCol(&m_gui, pElemRef, GSLC_COL_RED_DK1);

  // Create E_ELEM_TEXT21 text label
  pElemRef = gslc_ElemCreateTxt(
      &m_gui, E_ELEM_TEXT21, E_PG_MAIN, (gslc_tsRect){250, 90, 156, 8},
      (char *)"Maybe the darkness has won", 0, E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui, pElemRef, false);
  gslc_ElemSetTxtCol(&m_gui, pElemRef, GSLC_COL_RED_DK2);

  // Create E_ELEM_TEXT22 text label
  pElemRef = gslc_ElemCreateTxt(
      &m_gui, E_ELEM_TEXT22, E_PG_MAIN, (gslc_tsRect){250, 100, 222, 8},
      (char *)"And we were programmed just to suffer", 0, E_BUILTIN5X8);
  gslc_ElemSetFillEn(&m_gui, pElemRef, false);
  gslc_ElemSetTxtCol(&m_gui, pElemRef, GSLC_COL_WHITE);

  // -----------------------------------
  // PAGE: E_PG2

  // Create E_ELEM_TEXT23 text label
  pElemRef = gslc_ElemCreateTxt(
      &m_gui, E_ELEM_TEXT23, E_PG2, (gslc_tsRect){10, 140, 468, 24},
      (char *)"This page is not ready yet", 0, E_BUILTIN15X24);
  gslc_ElemSetFillEn(&m_gui, pElemRef, false);
  gslc_ElemSetTxtCol(&m_gui, pElemRef, GSLC_COL_WHITE);
  //<InitGUI !End!>

  //<Startup !Start!>
  //<Startup !End!>
}

#endif // end _GUISLICE_GEN_H
