#ifndef UIGLOBALREFS_H
#define UIGLOBALREFS_H

#include "../enums/ComponentEnums.h"
#include "ExternComponents.h"

gslc_tsElemRef* AppHeader = NULL;
gslc_tsElemRef* BackHomeButton = NULL;
gslc_tsElemRef* KnobGauge1 = NULL;
gslc_tsElemRef* KnobGauge2 = NULL;
gslc_tsElemRef* KnobGauge3 = NULL;
gslc_tsElemRef* KnobGauge4 = NULL;
gslc_tsElemRef* KnobGaugeText1 = NULL;
gslc_tsElemRef* KnobGaugeText2 = NULL;
gslc_tsElemRef* KnobGaugeText3 = NULL;
gslc_tsElemRef* KnobGaugeText4 = NULL;
gslc_tsElemRef* ToggleText1 = NULL;
gslc_tsElemRef* ToggleText2 = NULL;
gslc_tsElemRef* ToggleText3 = NULL;
gslc_tsElemRef* ToggleText4 = NULL;
gslc_tsElemRef* XyMapBox = NULL;
gslc_tsElemRef* XyMapButton = NULL;
gslc_tsElemRef* EqSlider1 = NULL;
gslc_tsElemRef* EqSlider2 = NULL;
gslc_tsElemRef* EqSlider3 = NULL;
gslc_tsElemRef* EqSlider4 = NULL;
gslc_tsElemRef* EqSlider5 = NULL;
gslc_tsElemRef* EqSlider6 = NULL;
gslc_tsElemRef* EqSlider7 = NULL;
gslc_tsElemRef* Toggle1 = NULL;
gslc_tsElemRef* Toggle2 = NULL;
gslc_tsElemRef* Toggle3 = NULL;
gslc_tsElemRef* Toggle4 = NULL;
gslc_tsElemRef* SendXMidiMsg = NULL;
gslc_tsElemRef* SendYMidiMsg = NULL;

gslc_tsElemRef* get_gauge_ref_by_encoder_id(int encoderId)
{
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

gslc_tsElemRef* get_toggle_ref_by_encoder_id(int encoderId)
{
    switch (encoderId) {
    case 0:
        return Toggle1;
    case 1:
        return Toggle2;
    case 2:
        return Toggle3;
    case 3:
        return Toggle4;
    default:
        return NULL;
    }
}

int get_cc_index_by_element_id(int16_t id)
{
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

#endif // UIGLOBALREFS_H