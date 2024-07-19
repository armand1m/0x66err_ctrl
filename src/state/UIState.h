#ifndef _UISTATE_H_
#define _UISTATE_H_

#include "GUIslice.h"
#include "GUIslice_drv.h"

#include "../constants/MaxElements.h"
#include "../enums/FontEnums.h"
#include "elem/XRingGauge.h"
#include "elem/XSlider.h"
#include "elem/XTogglebtn.h"

gslc_tsGui m_gui;
gslc_tsDriver m_drv;
gslc_tsFont m_asFont[MAX_FONT];
gslc_tsPage m_asPage[MAX_PAGE];
gslc_tsElem m_asPage1Elem[MAX_ELEM_PG_MAIN_RAM];
gslc_tsElemRef m_asPage1ElemRef[MAX_ELEM_PG_MAIN];
gslc_tsElem m_asPage2Elem[MAX_ELEM_PG_XYMAP_RAM];
gslc_tsElemRef m_asPage2ElemRef[MAX_ELEM_PG_XYMAP];
gslc_tsXRingGauge m_sXRingGauge1;
gslc_tsXRingGauge m_sXRingGauge2;
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

#endif // _UISTATE_H_