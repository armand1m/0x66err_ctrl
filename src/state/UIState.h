#ifndef _UISTATE_H_
#define _UISTATE_H_

#include "GUIslice.h"
#include "GUIslice_drv.h"

#include "../constants/MaxElements.h"
#include "../enums/FontEnums.h"
#include "ActiveChannelState.h"
#include "XYMapState.h"
#include "elem/XRingGauge.h"
#include "elem/XSlider.h"
#include "elem/XTogglebtn.h"

#define CONCAT(base, arg) base##arg
#define CONCAT3(base, arg1, arg2) base##arg1##arg2

#define CREATE_PAGE_REFS(page_id, ref)                                       \
    gslc_tsElem CONCAT(ref, PageElem)[CONCAT3(MAX_ELEM_PG_, page_id, _RAM)]; \
    gslc_tsElemRef CONCAT(ref, PageElemRef)[CONCAT(MAX_ELEM_PG_, page_id)];

gslc_tsGui gui_global;
gslc_tsDriver gui_driver;
gslc_tsFont FontStore[MAX_FONT];
gslc_tsPage PageStore[MAX_PAGE];

CREATE_PAGE_REFS(MAIN, Main);
CREATE_PAGE_REFS(XYMAP, XYMap);

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
XYMapState XyMapState1 = {
    .x = 240,
    .y = 175,
};
ActiveChannelState mainpage_channel_state;
ActiveChannelState xymap_channel_state;

#endif // _UISTATE_H_