#ifndef UIGLOBALREFS_H
#define UIGLOBALREFS_H

#include "../enums/ComponentEnums.h"
#include "../midi/CCMaps.h"
#include "../peripherals/RotaryEncoders.h"
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
gslc_tsElemRef* DebugText = NULL;

EncoderButton get_encoder_by_cc_number(int cc_number)
{
    switch (cc_number) {
    case KNOB_CC_1:
        return encoders[0];
    case KNOB_CC_2:
        return encoders[1];
    case KNOB_CC_3:
        return encoders[2];
    case KNOB_CC_4:
        return encoders[3];
    default:
        return NULL;
    }
}
gslc_tsElemRef* get_toggle_by_cc_number(int cc_number)
{
    switch (cc_number) {
    case TOGGLE_CC_1:
        return Toggle1;
    case TOGGLE_CC_2:
        return Toggle2;
    case TOGGLE_CC_3:
        return Toggle3;
    case TOGGLE_CC_4:
        return Toggle4;
    default:
        return NULL;
    }
}

gslc_tsElemRef* get_slider_by_cc_number(int cc_number)
{
    switch (cc_number) {
    case SLIDER_CC_1:
        return EqSlider1;
    case SLIDER_CC_2:
        return EqSlider2;
    case SLIDER_CC_3:
        return EqSlider3;
    case SLIDER_CC_4:
        return EqSlider4;
    case SLIDER_CC_5:
        return EqSlider5;
    case SLIDER_CC_6:
        return EqSlider6;
    case SLIDER_CC_7:
        return EqSlider7;
    default:
        return NULL;
    }
}

gslc_tsElemRef* get_gauge_by_cc_number(int cc_number)
{
    switch (cc_number) {
    case KNOB_CC_1:
        return KnobGauge1;
    case KNOB_CC_2:
        return KnobGauge2;
    case KNOB_CC_3:
        return KnobGauge3;
    case KNOB_CC_4:
        return KnobGauge4;
    default:
        return NULL;
    }
}

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