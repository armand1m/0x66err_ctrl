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
enum {E_PG_MAIN};
enum {E_ELEM_RINGGAUGE1,E_ELEM_RINGGAUGE2,E_ELEM_RINGGAUGE3
      ,E_ELEM_RINGGAUGE4,E_ELEM_RINGGAUGE5,E_ELEM_RINGGAUGE6
      ,E_ELEM_RINGGAUGE7,E_ELEM_RINGGAUGE8,E_ELEM_TEXT1,E_ELEM_TEXT2
      ,E_ELEM_TEXT3};
// Must use separate enum for fonts with MAX_FONT at end to use gslc_FontSet.
enum {E_BUILTIN20X32,E_BUILTIN5X8,MAX_FONT};
//<Enum !End!>

// ------------------------------------------------
// Instantiate the GUI
// ------------------------------------------------

// ------------------------------------------------
// Define the maximum number of elements and pages
// ------------------------------------------------
//<ElementDefines !Start!>
#define MAX_PAGE                1

#define MAX_ELEM_PG_MAIN 11 // # Elems total on page
#define MAX_ELEM_PG_MAIN_RAM MAX_ELEM_PG_MAIN // # Elems in RAM
//<ElementDefines !End!>

// ------------------------------------------------
// Create element storage
// ------------------------------------------------
gslc_tsGui                      m_gui;
gslc_tsDriver                   m_drv;
gslc_tsFont                     m_asFont[MAX_FONT];
gslc_tsPage                     m_asPage[MAX_PAGE];

//<GUI_Extra_Elements !Start!>
gslc_tsElem                     m_asPage1Elem[MAX_ELEM_PG_MAIN_RAM];
gslc_tsElemRef                  m_asPage1ElemRef[MAX_ELEM_PG_MAIN];
gslc_tsXRingGauge               m_sXRingGauge1;
gslc_tsXRingGauge               m_sXRingGauge2;
gslc_tsXRingGauge               m_sXRingGauge3;
gslc_tsXRingGauge               m_sXRingGauge4;
gslc_tsXRingGauge               m_sXRingGauge5;
gslc_tsXRingGauge               m_sXRingGauge6;
gslc_tsXRingGauge               m_sXRingGauge7;
gslc_tsXRingGauge               m_sXRingGauge8;

#define MAX_STR                 100

//<GUI_Extra_Elements !End!>

// ------------------------------------------------
// Program Globals
// ------------------------------------------------

// Element References for direct access
//<Extern_References !Start!>
extern gslc_tsElemRef* AppHeader;
extern gslc_tsElemRef* KnobGauge1;
extern gslc_tsElemRef* KnobGauge2;
extern gslc_tsElemRef* KnobGauge3;
extern gslc_tsElemRef* KnobGauge4;
extern gslc_tsElemRef* KnobGauge5;
extern gslc_tsElemRef* KnobGauge6;
extern gslc_tsElemRef* KnobGauge7;
extern gslc_tsElemRef* KnobGauge8;
extern gslc_tsElemRef* KnobGaugeText1;
extern gslc_tsElemRef* KnobGaugeText2;
//<Extern_References !End!>

// Define debug message function
static int16_t DebugOut(char ch);


// ------------------------------------------------
// Create page elements
// ------------------------------------------------
void initializeGUI()
{
  gslc_tsElemRef* pElemRef = NULL;

  if (!gslc_Init(&m_gui,&m_drv,m_asPage,MAX_PAGE,m_asFont,MAX_FONT)) { return; }

  // ------------------------------------------------
  // Load Fonts
  // ------------------------------------------------
  if (!gslc_FontSet(&m_gui,E_BUILTIN20X32,GSLC_FONTREF_PTR,NULL,4)) { return; }
  if (!gslc_FontSet(&m_gui,E_BUILTIN5X8,GSLC_FONTREF_PTR,NULL,1)) { return; }

  gslc_GuiRotate(&m_gui, 1);
  
  gslc_PageAdd(&m_gui,E_PG_MAIN,m_asPage1Elem,MAX_ELEM_PG_MAIN_RAM,m_asPage1ElemRef,MAX_ELEM_PG_MAIN);

  // NOTE: The current page defaults to the first page added. Here we explicitly
  //       ensure that the main page is the correct page no matter the add order.
  gslc_SetPageCur(&m_gui,E_PG_MAIN);
  
  // Set Background to a flat color
  gslc_SetBkgndColor(&m_gui,GSLC_COL_WHITE);

  // -----------------------------------
  // PAGE: E_PG_MAIN
  
  // Create E_ELEM_TEXT3 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT3,E_PG_MAIN,(gslc_tsRect){100,10,288,32},
    (char*)"MIDI Ampsim", 0, E_BUILTIN20X32);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_MID_MID);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  AppHeader = pElemRef;

  // Create ring gauge E_ELEM_RINGGAUGE1 
  static char m_sRingText1[11] = "0";
  pElemRef = gslc_ElemXRingGaugeCreate(&m_gui,E_ELEM_RINGGAUGE1,E_PG_MAIN,&m_sXRingGauge1,
          (gslc_tsRect){11,52,45,45},
          (char*)m_sRingText1,11,E_BUILTIN5X8);
  gslc_ElemXRingGaugeSetValRange(&m_gui, pElemRef, 0, 100);
  gslc_ElemXRingGaugeSetVal(&m_gui, pElemRef, 0); // Set initial value
  gslc_ElemXRingGaugeSetThickness(&m_gui,pElemRef, 8);
  gslc_ElemXRingGaugeSetColorActiveGradient(&m_gui, pElemRef, GSLC_COL_BLUE, GSLC_COL_RED_LT1);
  gslc_ElemXRingGaugeSetColorInactive(&m_gui,pElemRef, GSLC_COL_BLACK);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_WHITE,GSLC_COL_BLACK);
  KnobGauge1 = pElemRef;

  // Create ring gauge E_ELEM_RINGGAUGE2 
  static char m_sRingText2[11] = "0";
  pElemRef = gslc_ElemXRingGaugeCreate(&m_gui,E_ELEM_RINGGAUGE2,E_PG_MAIN,&m_sXRingGauge2,
          (gslc_tsRect){70,52,45,45},
          (char*)m_sRingText2,11,E_BUILTIN5X8);
  gslc_ElemXRingGaugeSetValRange(&m_gui, pElemRef, 0, 100);
  gslc_ElemXRingGaugeSetVal(&m_gui, pElemRef, 0); // Set initial value

  gslc_ElemXRingGaugeSetThickness(&m_gui,pElemRef, 8);
  gslc_ElemXRingGaugeSetColorActiveGradient(&m_gui, pElemRef, GSLC_COL_BLUE, GSLC_COL_RED_LT1);
  gslc_ElemXRingGaugeSetColorInactive(&m_gui,pElemRef, GSLC_COL_BLACK);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_WHITE,GSLC_COL_BLACK);
  KnobGauge2 = pElemRef;

  // Create ring gauge E_ELEM_RINGGAUGE3 
  static char m_sRingText3[11] = "0";
  pElemRef = gslc_ElemXRingGaugeCreate(&m_gui,E_ELEM_RINGGAUGE3,E_PG_MAIN,&m_sXRingGauge3,
          (gslc_tsRect){129,52,45,45},
          (char*)m_sRingText3,11,E_BUILTIN5X8);
  gslc_ElemXRingGaugeSetValRange(&m_gui, pElemRef, 0, 100);
  gslc_ElemXRingGaugeSetVal(&m_gui, pElemRef, 0); // Set initial value
  gslc_ElemXRingGaugeSetThickness(&m_gui,pElemRef, 8);
  gslc_ElemXRingGaugeSetColorActiveGradient(&m_gui, pElemRef, GSLC_COL_BLUE, GSLC_COL_RED_LT1);
  gslc_ElemXRingGaugeSetColorInactive(&m_gui,pElemRef, GSLC_COL_BLACK);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_WHITE,GSLC_COL_BLACK);
  KnobGauge3 = pElemRef;

  // Create ring gauge E_ELEM_RINGGAUGE4 
  static char m_sRingText4[11] = "0";
  pElemRef = gslc_ElemXRingGaugeCreate(&m_gui,E_ELEM_RINGGAUGE4,E_PG_MAIN,&m_sXRingGauge4,
          (gslc_tsRect){188,52,45,45},
          (char*)m_sRingText4,11,E_BUILTIN5X8);
  gslc_ElemXRingGaugeSetValRange(&m_gui, pElemRef, 0, 100);
  gslc_ElemXRingGaugeSetVal(&m_gui, pElemRef, 0); // Set initial value

  gslc_ElemXRingGaugeSetThickness(&m_gui,pElemRef, 8);
  gslc_ElemXRingGaugeSetColorActiveGradient(&m_gui, pElemRef, GSLC_COL_BLUE, GSLC_COL_RED_LT1);
  gslc_ElemXRingGaugeSetColorInactive(&m_gui,pElemRef, GSLC_COL_BLACK);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_WHITE,GSLC_COL_BLACK);
  KnobGauge4 = pElemRef;

  // Create ring gauge E_ELEM_RINGGAUGE5 
  static char m_sRingText5[11] = "0";
  pElemRef = gslc_ElemXRingGaugeCreate(&m_gui,E_ELEM_RINGGAUGE5,E_PG_MAIN,&m_sXRingGauge5,
          (gslc_tsRect){247,52,45,45},
          (char*)m_sRingText5,11,E_BUILTIN5X8);
  gslc_ElemXRingGaugeSetValRange(&m_gui, pElemRef, 0, 100);
  gslc_ElemXRingGaugeSetVal(&m_gui, pElemRef, 0); // Set initial value

  gslc_ElemXRingGaugeSetThickness(&m_gui,pElemRef, 8);
  gslc_ElemXRingGaugeSetColorActiveGradient(&m_gui, pElemRef, GSLC_COL_BLUE, GSLC_COL_RED_LT1);
  gslc_ElemXRingGaugeSetColorInactive(&m_gui,pElemRef, GSLC_COL_BLACK);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_WHITE,GSLC_COL_BLACK);
  KnobGauge5 = pElemRef;

  // Create ring gauge E_ELEM_RINGGAUGE6 
  static char m_sRingText6[11] = "0";
  pElemRef = gslc_ElemXRingGaugeCreate(&m_gui,E_ELEM_RINGGAUGE6,E_PG_MAIN,&m_sXRingGauge6,
          (gslc_tsRect){306,52,45,45},
          (char*)m_sRingText6,11,E_BUILTIN5X8);
  gslc_ElemXRingGaugeSetValRange(&m_gui, pElemRef, 0, 100);
  gslc_ElemXRingGaugeSetVal(&m_gui, pElemRef, 0); // Set initial value

  gslc_ElemXRingGaugeSetThickness(&m_gui,pElemRef, 8);
  gslc_ElemXRingGaugeSetColorActiveGradient(&m_gui, pElemRef, GSLC_COL_BLUE, GSLC_COL_RED_LT1);
  gslc_ElemXRingGaugeSetColorInactive(&m_gui,pElemRef, GSLC_COL_BLACK);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_WHITE,GSLC_COL_BLACK);
  KnobGauge6 = pElemRef;

  // Create ring gauge E_ELEM_RINGGAUGE7 
  static char m_sRingText7[11] = "0";
  pElemRef = gslc_ElemXRingGaugeCreate(&m_gui,E_ELEM_RINGGAUGE7,E_PG_MAIN,&m_sXRingGauge7,
          (gslc_tsRect){365,52,45,45},
          (char*)m_sRingText7,11,E_BUILTIN5X8);
  gslc_ElemXRingGaugeSetValRange(&m_gui, pElemRef, 0, 100);
  gslc_ElemXRingGaugeSetVal(&m_gui, pElemRef, 0); // Set initial value

  gslc_ElemXRingGaugeSetThickness(&m_gui,pElemRef, 8);
  gslc_ElemXRingGaugeSetColorActiveGradient(&m_gui, pElemRef, GSLC_COL_BLUE, GSLC_COL_RED_LT1);
  gslc_ElemXRingGaugeSetColorInactive(&m_gui,pElemRef, GSLC_COL_BLACK);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_WHITE,GSLC_COL_BLACK);
  KnobGauge7 = pElemRef;

  // Create ring gauge E_ELEM_RINGGAUGE8 
  static char m_sRingText8[11] = "0";
  pElemRef = gslc_ElemXRingGaugeCreate(&m_gui,E_ELEM_RINGGAUGE8,E_PG_MAIN,&m_sXRingGauge8,
          (gslc_tsRect){424,52,45,45},
          (char*)m_sRingText8,11,E_BUILTIN5X8);
  gslc_ElemXRingGaugeSetValRange(&m_gui, pElemRef, 0, 100);
  gslc_ElemXRingGaugeSetVal(&m_gui, pElemRef, 0); // Set initial value

  gslc_ElemXRingGaugeSetThickness(&m_gui,pElemRef, 8);
  gslc_ElemXRingGaugeSetColorActiveGradient(&m_gui, pElemRef, GSLC_COL_BLUE, GSLC_COL_RED_LT1);
  gslc_ElemXRingGaugeSetColorInactive(&m_gui,pElemRef, GSLC_COL_BLACK);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  gslc_ElemSetCol(&m_gui,pElemRef,GSLC_COL_WHITE,GSLC_COL_WHITE,GSLC_COL_BLACK);
  KnobGauge8 = pElemRef;
  
  // Create E_ELEM_TEXT1 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT1,E_PG_MAIN,(gslc_tsRect){10,100,45,8},
    (char*)"Gain",0,E_BUILTIN5X8);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_TOP_MID);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  KnobGaugeText1 = pElemRef;
  
  // Create E_ELEM_TEXT2 text label
  pElemRef = gslc_ElemCreateTxt(&m_gui,E_ELEM_TEXT2,E_PG_MAIN,(gslc_tsRect){70,100,45,8},
    (char*)"Low",0,E_BUILTIN5X8);
  gslc_ElemSetTxtAlign(&m_gui,pElemRef,GSLC_ALIGN_TOP_MID);
  gslc_ElemSetFillEn(&m_gui,pElemRef,false);
  gslc_ElemSetTxtCol(&m_gui,pElemRef,GSLC_COL_BLACK);
  KnobGaugeText2 = pElemRef;
}

#endif