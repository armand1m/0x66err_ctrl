#ifndef MAIN_PAGE_H
#define MAIN_PAGE_H

#include "../components/Button.h"
#include "../components/RingGauge.h"
#include "../components/Slider.h"
#include "../components/Text.h"
#include "../components/Toggle.h"
#include "../context/GuiContext.h"
#include "../enums/ComponentEnums.h"
#include "../enums/PageEnums.h"
#include "../midi/CCMaps.h"
#include "../midi/Transport.h"
#include "../references/ExternComponents.h"
#include "../references/UIGlobalRefs.h"
#include "../state/UIState.h"

GuiContext mainpage_context = { .gui = &m_gui, .page = E_PG_MAIN };

bool on_xymap_button_press(void* gui_pointer, void* element_ref_pointer, gslc_teTouch touch_event,
    int16_t nX, int16_t nY)
{
    gslc_SetPageCur(&m_gui, E_PG_XYMAP);
    return true;
}

bool on_toggle_press(void* gui_pointer, void* element_ref_pointer, gslc_teTouch touch_event,
    int16_t nX, int16_t nY)
{
    gslc_tsGui* gui = (gslc_tsGui*)(gui_pointer);
    gslc_tsElemRef* element_ref = (gslc_tsElemRef*)(element_ref_pointer);
    gslc_tsElem* element = gslc_GetElemFromRef(gui, element_ref);

    int index = get_cc_index_by_element_id(element->nId);

    if (touch_event == GSLC_TOUCH_UP_IN) {
        if (gslc_ElemXTogglebtnGetState(&m_gui, element_ref)) {
            send_midi_cc(toggle_midi_cc[index], 127, 1);
        } else {
            send_midi_cc(toggle_midi_cc[index], 0, 1);
        }
    }

    return true;
}

bool on_slide_change(void* gui_pointer, void* element_ref_pointer, int16_t slider_position)
{
    gslc_tsGui* gui = (gslc_tsGui*)(gui_pointer);
    gslc_tsElemRef* element_ref = (gslc_tsElemRef*)(element_ref_pointer);
    gslc_tsElem* element = gslc_GetElemFromRef(gui, element_ref);
    int index = get_cc_index_by_element_id(element->nId);

    int controlNumber = slider_midi_cc[index];
    int controlValue = map(slider_position, 0, 100, 127, 0);
    int channel = 1;

    send_midi_cc(controlNumber, controlValue, channel);

    return true;
}

void render_bmth_quote()
{
    createText({ .context = mainpage_context,
        .id = E_ELEM_TEXT17,
        .position = { 250, 50, 210, 8 },
        .text = "Cause everyone's too scared to heal" });

    createText({ .context = mainpage_context,
        .id = E_ELEM_TEXT18,
        .position = { 250, 60, 216, 8 },
        .text = "They don't give a fuck how they feel" });

    createText({ .context = mainpage_context,
        .id = E_ELEM_TEXT19,
        .position = { 250, 70, 216, 8 },
        .text = "And I don't know how to deal anymore" });

    createText({
        .context = mainpage_context,
        .id = E_ELEM_TEXT20,
        .position = { 250, 80, 174, 8 },
        .text = "Well maybe the damage is done",
        .font = NULL,
        .align = TextAlign::CENTER,
        .color = &GSLC_COL_RED_DK1,
    });

    createText({
        .context = mainpage_context,
        .id = E_ELEM_TEXT21,
        .position = { 250, 90, 156, 8 },
        .text = "Maybe the darkness has won",
        .font = NULL,
        .align = TextAlign::CENTER,
        .color = &GSLC_COL_RED_DK2,
    });

    createText({
        .context = mainpage_context,
        .id = E_ELEM_TEXT22,
        .position = { 250, 100, 222, 8 },
        .text = "And we were programmed just to suffer",
    });
}

void render_header()
{
    int16_t big_text = E_BUILTIN20X32;

    AppHeader = createText({ .context = mainpage_context,
        .id = E_ELEM_APPHEADER,
        .position = { 190, 10, 285, 32 },
        .text = "0x66err_ctrl",
        .font = &big_text });

    XyMapButton = createButton({
        .context = mainpage_context,
        .id = E_ELEM_XYMAP_BTN,
        .position = { 15, 15, 80, 20 },
        .text = "XY MAP",
        .callback = &on_xymap_button_press,
    });

    render_bmth_quote();
}

void render_ring_gauges()
{
    RingGaugeElements ring_gauge_1 = createRingGauge({ .context = mainpage_context,
        .id = E_ELEM_RINGGAUGE1,
        .position = { 14, 54, 45, 45 },
        .ring_text = "0",
        .label = "Gain",
        .label_id = E_ELEM_KNOB_1,
        .state = &m_sXRingGauge1 });

    KnobGauge1 = ring_gauge_1.ring_gauge;
    KnobGaugeText1 = ring_gauge_1.label;

    RingGaugeElements ring_gauge_2 = createRingGauge({ .context = mainpage_context,
        .id = E_ELEM_RINGGAUGE2,
        .position = { 73, 54, 45, 45 },
        .ring_text = "0",
        .label = "Low",
        .label_id = E_ELEM_KNOB_2,
        .state = &m_sXRingGauge2 });

    KnobGauge2 = ring_gauge_2.ring_gauge;
    KnobGaugeText2 = ring_gauge_2.label;

    RingGaugeElements ring_gauge_3 = createRingGauge({ .context = mainpage_context,
        .id = E_ELEM_RINGGAUGE3,
        .position = { 132, 54, 45, 45 },
        .ring_text = "0",
        .label = "Mid",
        .label_id = E_ELEM_KNOB_3,
        .state = &m_sXRingGauge3 });

    KnobGauge3 = ring_gauge_3.ring_gauge;
    KnobGaugeText3 = ring_gauge_3.label;

    RingGaugeElements ring_gauge_4 = createRingGauge({ .context = mainpage_context,
        .id = E_ELEM_RINGGAUGE4,
        .position = { 191, 54, 45, 45 },
        .ring_text = "0",
        .label = "High",
        .label_id = E_ELEM_KNOB_4,
        .state = &m_sXRingGauge4 });

    KnobGauge4 = ring_gauge_4.ring_gauge;
    KnobGaugeText4 = ring_gauge_4.label;
}

void render_toggles()
{
    ToggleElements toggle_1 = createToggle({ .context = mainpage_context,
        .id = E_ELEM_TOGGLE1,
        .position = { 20, 141, 35, 20 },
        .label = "Octaver",
        .label_id = E_ELEM_TOGGLE_TEXT_1,
        .state = &m_asXToggle1,
        .on_touch = &on_toggle_press });

    m_pElemToggle1 = toggle_1.toggle;
    Toggle1Text = toggle_1.label;

    ToggleElements toggle_2 = createToggle({ .context = mainpage_context,
        .id = E_ELEM_TOGGLE2,
        .position = { 20, 181, 35, 20 },
        .label = "Overdrive",
        .label_id = E_ELEM_TOGGLE_TEXT_2,
        .state = &m_asXToggle2,
        .on_touch = &on_toggle_press });

    m_pElemToggle2 = toggle_2.toggle;
    Toggle2Text = toggle_2.label;

    ToggleElements toggle_3 = createToggle({ .context = mainpage_context,
        .id = E_ELEM_TOGGLE3,
        .position = { 20, 221, 35, 20 },
        .label = "Distortion",
        .label_id = E_ELEM_TOGGLE_TEXT_3,
        .state = &m_asXToggle3,
        .on_touch = &on_toggle_press });

    m_pElemToggle3 = toggle_3.toggle;
    Toggle3Text = toggle_3.label;

    ToggleElements toggle_4 = createToggle({ .context = mainpage_context,
        .id = E_ELEM_TOGGLE4,
        .position = { 20, 262, 35, 20 },
        .label = "Custom",
        .label_id = E_ELEM_TOGGLE_TEXT_4,
        .state = &m_asXToggle4,
        .on_touch = &on_toggle_press });

    m_pElemToggle4 = toggle_4.toggle;
    Toggle4Text = toggle_4.label;
}

void render_equalizer()
{
    SliderElements slider_1 = createSlider({ .context = mainpage_context,
        .id = E_ELEM_SLIDER1,
        .position = { 140, 130, 20, 160 },
        .label = "65hz",
        .label_id = E_ELEM_TEXT9,
        .state = &m_sXSlider1,
        .on_change = &on_slide_change });

    m_pElemSlider1 = slider_1.slider;

    SliderElements slider_2 = createSlider({ .context = mainpage_context,
        .id = E_ELEM_SLIDER2,
        .position = { 190, 130, 20, 160 },
        .label = "125hz",
        .label_id = E_ELEM_TEXT10,
        .state = &m_sXSlider2,
        .on_change = &on_slide_change });

    m_pElemSlider1_2 = slider_2.slider;

    SliderElements slider_3 = createSlider({ .context = mainpage_context,
        .id = E_ELEM_SLIDER3,
        .position = { 240, 130, 20, 160 },
        .label = "250hz",
        .label_id = E_ELEM_TEXT11,
        .state = &m_sXSlider3,
        .on_change = &on_slide_change });

    m_pElemSlider1_3 = slider_3.slider;

    SliderElements slider_4 = createSlider({ .context = mainpage_context,
        .id = E_ELEM_SLIDER4,
        .position = { 290, 130, 20, 160 },
        .label = "500hz",
        .label_id = E_ELEM_TEXT12,
        .state = &m_sXSlider4,
        .on_change = &on_slide_change });

    m_pElemSlider1_4 = slider_4.slider;

    SliderElements slider_5 = createSlider({ .context = mainpage_context,
        .id = E_ELEM_SLIDER5,
        .position = { 340, 130, 20, 160 },
        .label = "1kHz",
        .label_id = E_ELEM_TEXT13,
        .state = &m_sXSlider5,
        .on_change = &on_slide_change });

    m_pElemSlider1_5 = slider_5.slider;

    SliderElements slider_6 = createSlider({ .context = mainpage_context,
        .id = E_ELEM_SLIDER6,
        .position = { 390, 130, 20, 160 },
        .label = "2kHz",
        .label_id = E_ELEM_TEXT14,
        .state = &m_sXSlider6,
        .on_change = &on_slide_change });

    m_pElemSlider1_6 = slider_6.slider;

    SliderElements slider_7 = createSlider({ .context = mainpage_context,
        .id = E_ELEM_SLIDER7,
        .position = { 440, 130, 20, 160 },
        .label = "4kHz",
        .label_id = E_ELEM_TEXT15,
        .state = &m_sXSlider7,
        .on_change = &on_slide_change });

    m_pElemSlider1_7 = slider_7.slider;
}

void render_main_page()
{
    render_header();
    render_ring_gauges();
    render_toggles();
    render_equalizer();
}

#endif // MAIN_PAGE_H