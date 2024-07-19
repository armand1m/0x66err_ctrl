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

bool on_xymap_button_press(void* pvGui, void* pvElemRef, gslc_teTouch eTouch,
    int16_t nX, int16_t nY)
{
    gslc_SetPageCur(&m_gui, E_PG_XYMAP);
    return true;
}

bool on_toggle_press(void* pvGui, void* pvElemRef, gslc_teTouch eTouch,
    int16_t nX, int16_t nY)
{
    gslc_tsGui* pGui = (gslc_tsGui*)(pvGui);
    gslc_tsElemRef* pElemRef = (gslc_tsElemRef*)(pvElemRef);
    gslc_tsElem* pElem = gslc_GetElemFromRef(pGui, pElemRef);

    int index = get_cc_index_by_element_id(pElem->nId);

    if (eTouch == GSLC_TOUCH_UP_IN) {
        if (gslc_ElemXTogglebtnGetState(&m_gui, pElemRef)) {
            send_midi_cc(toggle_midi_cc[index], 127, 1);
        } else {
            send_midi_cc(toggle_midi_cc[index], 0, 1);
        }
    }

    return true;
}

/**
 * This is the callback for the EQ sliders.
 * This function primarily identifies which slider was moved and sends the
 * corresponding MIDI CC message.
 */
bool on_slide_change(void* pvGui, void* pvElemRef, int16_t nPos)
{
    gslc_tsGui* pGui = (gslc_tsGui*)(pvGui);
    gslc_tsElemRef* pElemRef = (gslc_tsElemRef*)(pvElemRef);
    gslc_tsElem* pElem = gslc_GetElemFromRef(pGui, pElemRef);
    int16_t nVal = gslc_ElemXSliderGetPos(pGui, pElemRef);
    int index = get_cc_index_by_element_id(pElem->nId);

    int controlNumber = slider_midi_cc[index];
    int controlValue = map(nVal, 0, 100, 127, 0);
    int channel = 1;

    send_midi_cc(controlNumber, controlValue, channel);

    return true;
}

void render_main_page()
{
    GuiContext context = { .gui = &m_gui, .page = E_PG_MAIN };

    int16_t big_text = E_BUILTIN20X32;

    AppHeader = createText({ .context = context,
        .id = E_ELEM_APPHEADER,
        .position = { 190, 10, 285, 32 },
        .text = "0x66err_ctrl",
        .font = &big_text });

    KnobGauge1 = createRingGauge({ .context = context,
        .id = E_ELEM_RINGGAUGE1,
        .position = { 14, 54, 45, 45 },
        .ring_text = "0",
        .state = &m_sXRingGauge1 });

    KnobGauge2 = createRingGauge({ .context = context,
        .id = E_ELEM_RINGGAUGE2,
        .position = { 73, 54, 45, 45 },
        .ring_text = "0",
        .state = &m_sXRingGauge2 });

    KnobGauge3 = createRingGauge({ .context = context,
        .id = E_ELEM_RINGGAUGE3,
        .position = { 132, 54, 45, 45 },
        .ring_text = "0",
        .state = &m_sXRingGauge3 });

    KnobGauge4 = createRingGauge({ .context = context,
        .id = E_ELEM_RINGGAUGE4,
        .position = { 191, 54, 45, 45 },
        .ring_text = "0",
        .state = &m_sXRingGauge4 });

    KnobGaugeText1 = createText({ .context = context,
        .id = E_ELEM_KNOB_1,
        .position = { 23, 102, 24, 8 },
        .text = "Gain" });

    KnobGaugeText2 = createText({ .context = context,
        .id = E_ELEM_KNOB_2,
        .position = { 73, 102, 45, 8 },
        .text = "Low" });

    KnobGaugeText3 = createText({ .context = context,
        .id = E_ELEM_KNOB_3,
        .position = { 143, 102, 18, 8 },
        .text = "Mid" });

    KnobGaugeText4 = createText({ .context = context,
        .id = E_ELEM_KNOB_4,
        .position = { 203, 102, 24, 8 },
        .text = "High" });

    m_pElemToggle1 = createToggle({ .context = context,
        .id = E_ELEM_TOGGLE1,
        .position = { 20, 141, 35, 20 },
        .text = "Octaver",
        .state = &m_asXToggle1,
        .callback = &on_toggle_press });

    m_pElemToggle2 = createToggle({ .context = context,
        .id = E_ELEM_TOGGLE2,
        .position = { 20, 181, 35, 20 },
        .text = "Overdrive",
        .state = &m_asXToggle2,
        .callback = &on_toggle_press });

    m_pElemToggle3 = createToggle({ .context = context,
        .id = E_ELEM_TOGGLE3,
        .position = { 20, 221, 35, 20 },
        .text = "Distortion",
        .state = &m_asXToggle3,
        .callback = &on_toggle_press });

    m_pElemToggle4 = createToggle({ .context = context,
        .id = E_ELEM_TOGGLE4,
        .position = { 20, 262, 35, 20 },
        .text = "Custom",
        .state = &m_asXToggle4,
        .callback = &on_toggle_press });

    Toggle1Text = createText({ .context = context,
        .id = E_ELEM_TOGGLE_TEXT_1,
        .position = { 60, 151, 42, 8 },
        .text = "Octaver" });

    Toggle2Text = createText({ .context = context,
        .id = E_ELEM_TOGGLE_TEXT_2,
        .position = { 60, 191, 54, 8 },
        .text = "Overdrive" });

    Toggle3Text = createText({ .context = context,
        .id = E_ELEM_TOGGLE_TEXT_3,
        .position = { 60, 231, 60, 8 },
        .text = "Distortion" });

    Toggle4Text = createText({ .context = context,
        .id = E_ELEM_TOGGLE_TEXT_4,
        .position = { 60, 272, 36, 8 },
        .text = "Custom" });

    m_pElemSlider1 = createSlider({ .context = context,
        .id = E_ELEM_SLIDER1,
        .position = { 140, 130, 20, 160 },
        .state = &m_sXSlider1,
        .callback = &on_slide_change });

    m_pElemSlider1_2 = createSlider({ .context = context,
        .id = E_ELEM_SLIDER2,
        .position = { 190, 130, 20, 160 },
        .state = &m_sXSlider2,
        .callback = &on_slide_change });

    m_pElemSlider1_3 = createSlider({ .context = context,
        .id = E_ELEM_SLIDER3,
        .position = { 240, 130, 20, 160 },
        .state = &m_sXSlider3,
        .callback = &on_slide_change });

    m_pElemSlider1_4 = createSlider({ .context = context,
        .id = E_ELEM_SLIDER4,
        .position = { 290, 130, 20, 160 },
        .state = &m_sXSlider4,
        .callback = &on_slide_change });

    m_pElemSlider1_5 = createSlider({ .context = context,
        .id = E_ELEM_SLIDER5,
        .position = { 340, 130, 20, 160 },
        .state = &m_sXSlider5,
        .callback = &on_slide_change });

    m_pElemSlider1_6 = createSlider({ .context = context,
        .id = E_ELEM_SLIDER6,
        .position = { 390, 130, 20, 160 },
        .state = &m_sXSlider6,
        .callback = &on_slide_change });

    m_pElemSlider1_7 = createSlider({ .context = context,
        .id = E_ELEM_SLIDER7,
        .position = { 440, 130, 20, 160 },
        .state = &m_sXSlider7,
        .callback = &on_slide_change });

    createText({ .context = context,
        .id = E_ELEM_TEXT9,
        .position = { 141, 295, 30, 8 },
        .text = "65hz" });

    createText({ .context = context,
        .id = E_ELEM_TEXT10,
        .position = { 181, 295, 30, 8 },
        .text = "125hz" });

    createText({ .context = context,
        .id = E_ELEM_TEXT11,
        .position = { 231, 295, 30, 8 },
        .text = "250hz" });

    createText({ .context = context,
        .id = E_ELEM_TEXT12,
        .position = { 281, 295, 30, 8 },
        .text = "500hz" });

    createText({ .context = context,
        .id = E_ELEM_TEXT13,
        .position = { 331, 295, 30, 8 },
        .text = "1kHz" });

    createText({ .context = context,
        .id = E_ELEM_TEXT14,
        .position = { 381, 295, 30, 8 },
        .text = "2kHz" });

    createText({ .context = context,
        .id = E_ELEM_TEXT15,
        .position = { 431, 295, 30, 8 },
        .text = "4kHz" });

    createText({ .context = context,
        .id = E_ELEM_TEXT17,
        .position = { 250, 50, 210, 8 },
        .text = "Cause everyone's too scared to heal" });

    createText({ .context = context,
        .id = E_ELEM_TEXT18,
        .position = { 250, 60, 216, 8 },
        .text = "They don't give a fuck how they feel" });

    createText({ .context = context,
        .id = E_ELEM_TEXT19,
        .position = { 250, 70, 216, 8 },
        .text = "And I don't know how to deal anymore" });

    createText({
        .context = context,
        .id = E_ELEM_TEXT20,
        .position = { 250, 80, 174, 8 },
        .text = "Well maybe the damage is done",
        .font = NULL,
        .color = &GSLC_COL_RED_DK1,
    });

    createText({
        .context = context,
        .id = E_ELEM_TEXT21,
        .position = { 250, 90, 156, 8 },
        .text = "Maybe the darkness has won",
        .font = NULL,
        .color = &GSLC_COL_RED_DK2,
    });

    createText({
        .context = context,
        .id = E_ELEM_TEXT22,
        .position = { 250, 100, 222, 8 },
        .text = "And we were programmed just to suffer",
    });

    XyMapButton = createButton({
        .context = context,
        .id = E_ELEM_XYMAP_BTN,
        .position = { 15, 15, 80, 20 },
        .text = "XY MAP",
        .callback = &on_xymap_button_press,
    });
}
#endif // MAIN_PAGE_H