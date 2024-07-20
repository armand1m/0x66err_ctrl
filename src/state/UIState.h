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

gslc_tsXRingGauge RingGaugeState1;
gslc_tsXRingGauge RingGaugeState2;
gslc_tsXRingGauge RingGaugeState3;
gslc_tsXRingGauge RingGaugeState4;
gslc_tsXTogglebtn ToggleState1;
gslc_tsXTogglebtn ToggleState2;
gslc_tsXTogglebtn ToggleState3;
gslc_tsXTogglebtn ToggleState4;
gslc_tsXSlider SliderState1;
gslc_tsXSlider SliderState2;
gslc_tsXSlider SliderState3;
gslc_tsXSlider SliderState4;
gslc_tsXSlider SliderState5;
gslc_tsXSlider SliderState6;
gslc_tsXSlider SliderState7;

int16_t xyMapCurrentX = 240;
int16_t xyMapCurrentY = 175;

#endif // _UISTATE_H_