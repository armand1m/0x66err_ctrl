#ifndef MAIN_PAGE_H
#define MAIN_PAGE_H

#define CONCAT(arg1, arg2) arg1##arg2

#include "../components/Button.h"
#include "../components/ChannelToggle.h"
#include "../components/RingGauge.h"
#include "../components/Toggle.h"
#include "../context/GuiContext.h"
#include "../context/PagesContext.h"
#include "../enums/ComponentEnums.h"
#include "../enums/PageEnums.h"
#include "../midi/CCMaps.h"
#include "../midi/Transport.h"
#include "../references/ExternComponents.h"
#include "../references/UIGlobalRefs.h"
#include "../state/EEPROMState.h"
#include "../state/UIState.h"
#include "PageHandlers.h"

bool on_xymap_button_press(void* gui_pointer, void* element_ref_pointer, gslc_teTouch touch_event,
    int16_t _touch_x, int16_t _touch_y)
{
    __on_touch_only();
    set_current_page(E_PG_XYMAP);
    return true;
}

bool on_toggle_press(void* gui_pointer, void* element_ref_pointer, gslc_teTouch touch_event,
    int16_t _touch_x, int16_t _touch_y)
{
    __on_touch_only();
    __resolve_gui_context();
    int index = get_cc_index_by_element_id(element_id);
    bool new_value = get_toggle_state(element_ref);
    int control_number = toggle_midi_cc[index];
    int control_value = new_value ? 127 : 0;
    __midi_send_cc(control_number, control_value, mainpage_channel_state.channel);

    ChannelState* state = __eeprom_get_channel_state(mainpage_channel_state.channel);
    __eeprom_update_toggle_state(state, element_id, new_value);
    __eeprom_save();

    return true;
}

bool on_slide_change(void* gui_pointer, void* element_ref_pointer, int16_t slider_position)
{
    __resolve_gui_context();
    int index = get_cc_index_by_element_id(element_id);
    int control_number = slider_midi_cc[index];
    int control_value = map(slider_position, 0, 100, 127, 0);
    __midi_send_cc(control_number, control_value, mainpage_channel_state.channel);

    ChannelState* state = __eeprom_get_channel_state(mainpage_channel_state.channel);
    __eeprom_update_slider_state(state, element_id, slider_position);
    __eeprom_save();

    return true;
}

bool on_main_channel_toggle(void* gui_pointer, void* element_ref_pointer, gslc_teTouch touch_event,
    int16_t _touch_x, int16_t _touch_y)
{
    __on_touch_only();
    __resolve_gui_context();

    mainpage_channel_state.channel = get_channel_number_by_element_id(element_id);

    // deactivate old channel button
    toggle_button_active({
        .context = mainpage_context,
        .element = mainpage_channel_state.active_element,
        .active = false,
    });

    // replace active element with new channel button
    mainpage_channel_state.active_element = element_ref;

    // activate new channel button
    toggle_button_active({
        .context = mainpage_context,
        .element = mainpage_channel_state.active_element,
        .active = true,
    });

    __eeprom_update_component_values(mainpage_channel_state.channel);

    return true;
}

#define gauge(index, gauge_label)                                                     \
    static char CONCAT(ring_gauge_text_, index)[XRING_STR_MAX] = "0";                 \
    RingGaugeElements CONCAT(ring_gauge_, index) = createRingGauge((RingGaugeProps) { \
        .context = mainpage_context,                                                  \
        .id = CONCAT(E_ELEM_RINGGAUGE, index),                                        \
        .position = { 15 + (60 * (index - 1)), 50, 45, 45 },                          \
        .ring_text = CONCAT(ring_gauge_text_, index),                                 \
        .label = gauge_label,                                                         \
        .label_id = CONCAT(E_ELEM_KNOB_LABEL_, index),                                \
        .state = CONCAT(&RingGaugeState, index) });                                   \
    CONCAT(KnobGauge, index) = CONCAT(ring_gauge_, index).ring_gauge;

#define toggle(index, toggle_label)                                                     \
    ToggleElements CONCAT(toggle_, index) = createToggle({ .context = mainpage_context, \
        .id = CONCAT(E_ELEM_TOGGLE, index),                                             \
        .position = { 15, 125 + (40 * (index - 1)), 35, 20 },                           \
        .label = toggle_label,                                                          \
        .label_id = CONCAT(E_ELEM_TOGGLE_TEXT_, index),                                 \
        .state = CONCAT(&ToggleState, index),                                           \
        .on_touch = &on_toggle_press });                                                \
    CONCAT(Toggle, index) = CONCAT(toggle_, index).toggle;

void render_header()
{
    gslc_ElemCreateTxt_P(&gui_global, E_ELEM_APPHEADER, E_PG_MAIN, 190, 10, 285, 32, "0x66err_ctrl", &FontStore[Fonts::E_BUILTIN20X32], GSLC_COL_WHITE, GSLC_COL_BLACK, GSLC_COL_BLACK, GSLC_ALIGN_MID_LEFT, false, true);
    gslc_ElemCreateBtnTxt_P(&gui_global, E_ELEM_XYMAP_BTN, E_PG_MAIN, 15, 10, 80, 20, "XY MAP", &FontStore[Fonts::E_BUILTIN5X8], GSLC_COL_WHITE, GSLC_COL_GRAY_DK2, GSLC_COL_GRAY_DK4, GSLC_COL_GRAY_DK2, GSLC_COL_GRAY_DK1, GSLC_ALIGN_MID_MID, true, true, &on_xymap_button_press, NULL);
}

void render_quote()
{
    gslc_ElemCreateTxt_P(&gui_global, QUOTE_TEXT_1, E_PG_MAIN, 250, 50, 210, 8, "Cause everyone's too scared to heal", &FontStore[Fonts::E_BUILTIN5X8], GSLC_COL_WHITE, GSLC_COL_BLACK, GSLC_COL_BLACK, GSLC_ALIGN_MID_LEFT, false, true);
    gslc_ElemCreateTxt_P(&gui_global, QUOTE_TEXT_2, E_PG_MAIN, 250, 60, 210, 8, "They don't give a fuck how they feel", &FontStore[Fonts::E_BUILTIN5X8], GSLC_COL_WHITE, GSLC_COL_BLACK, GSLC_COL_BLACK, GSLC_ALIGN_MID_LEFT, false, true);
    gslc_ElemCreateTxt_P(&gui_global, QUOTE_TEXT_3, E_PG_MAIN, 250, 70, 210, 8, "And I don't know how to deal anymore", &FontStore[Fonts::E_BUILTIN5X8], GSLC_COL_WHITE, GSLC_COL_BLACK, GSLC_COL_BLACK, GSLC_ALIGN_MID_LEFT, false, true);
    gslc_ElemCreateTxt_P(&gui_global, QUOTE_TEXT_4, E_PG_MAIN, 250, 80, 210, 8, "Well maybe the damage is done", &FontStore[Fonts::E_BUILTIN5X8], GSLC_COL_RED_DK1, GSLC_COL_BLACK, GSLC_COL_BLACK, GSLC_ALIGN_MID_LEFT, false, true);
    gslc_ElemCreateTxt_P(&gui_global, QUOTE_TEXT_5, E_PG_MAIN, 250, 90, 210, 8, "Maybe the darkness has won", &FontStore[Fonts::E_BUILTIN5X8], GSLC_COL_RED_DK2, GSLC_COL_BLACK, GSLC_COL_BLACK, GSLC_ALIGN_MID_LEFT, false, true);
    gslc_ElemCreateTxt_P(&gui_global, QUOTE_TEXT_6, E_PG_MAIN, 250, 100, 210, 8, "And we were programmed just to suffer", &FontStore[Fonts::E_BUILTIN5X8], GSLC_COL_WHITE, GSLC_COL_BLACK, GSLC_COL_BLACK, GSLC_ALIGN_MID_LEFT, false, true);
}

void render_slider()
{
    gslc_ElemXSliderCreate_P(&gui_global, E_ELEM_SLIDER1, E_PG_MAIN, 140, 120, 20, 140, 0, 100, 50, 5, true, GSLC_COL_RED, GSLC_COL_BLACK);
    EqSlider1 = gslc_PageFindElemById(&gui_global, E_PG_MAIN, E_ELEM_SLIDER1);
    gslc_ElemXSliderSetStyle(&gui_global, EqSlider1, true, GSLC_COL_BLUE, 10, 5, GSLC_COL_RED_DK1);
    gslc_ElemXSliderSetPosFunc(&gui_global, EqSlider1, &on_slide_change);
    gslc_ElemCreateTxt_P(&gui_global, EQ_SLIDER_TEXT_1, E_PG_MAIN, 140, 264, 30, 8, "65hz", &FontStore[Fonts::E_BUILTIN5X8], GSLC_COL_WHITE, GSLC_COL_BLACK, GSLC_COL_BLACK, GSLC_ALIGN_MID_LEFT, false, true);

    gslc_ElemXSliderCreate_P(&gui_global, E_ELEM_SLIDER2, E_PG_MAIN, 190, 120, 20, 140, 0, 100, 50, 5, true, GSLC_COL_RED, GSLC_COL_BLACK);
    EqSlider2 = gslc_PageFindElemById(&gui_global, E_PG_MAIN, E_ELEM_SLIDER2);
    gslc_ElemXSliderSetStyle(&gui_global, EqSlider2, true, GSLC_COL_BLUE, 10, 5, GSLC_COL_RED_DK1);
    gslc_ElemXSliderSetPosFunc(&gui_global, EqSlider2, &on_slide_change);
    gslc_ElemCreateTxt_P(&gui_global, EQ_SLIDER_TEXT_2, E_PG_MAIN, 190, 264, 30, 8, "125hz", &FontStore[Fonts::E_BUILTIN5X8], GSLC_COL_WHITE, GSLC_COL_BLACK, GSLC_COL_BLACK, GSLC_ALIGN_MID_LEFT, false, true);

    gslc_ElemXSliderCreate_P(&gui_global, E_ELEM_SLIDER3, E_PG_MAIN, 240, 120, 20, 140, 0, 100, 50, 5, true, GSLC_COL_RED, GSLC_COL_BLACK);
    EqSlider3 = gslc_PageFindElemById(&gui_global, E_PG_MAIN, E_ELEM_SLIDER3);
    gslc_ElemXSliderSetStyle(&gui_global, EqSlider3, true, GSLC_COL_BLUE, 10, 5, GSLC_COL_RED_DK1);
    gslc_ElemXSliderSetPosFunc(&gui_global, EqSlider3, &on_slide_change);
    gslc_ElemCreateTxt_P(&gui_global, EQ_SLIDER_TEXT_3, E_PG_MAIN, 240, 264, 30, 8, "250hz", &FontStore[Fonts::E_BUILTIN5X8], GSLC_COL_WHITE, GSLC_COL_BLACK, GSLC_COL_BLACK, GSLC_ALIGN_MID_LEFT, false, true);

    gslc_ElemXSliderCreate_P(&gui_global, E_ELEM_SLIDER4, E_PG_MAIN, 290, 120, 20, 140, 0, 100, 50, 5, true, GSLC_COL_RED, GSLC_COL_BLACK);
    EqSlider4 = gslc_PageFindElemById(&gui_global, E_PG_MAIN, E_ELEM_SLIDER4);
    gslc_ElemXSliderSetStyle(&gui_global, EqSlider4, true, GSLC_COL_BLUE, 10, 5, GSLC_COL_RED_DK1);
    gslc_ElemXSliderSetPosFunc(&gui_global, EqSlider4, &on_slide_change);
    gslc_ElemCreateTxt_P(&gui_global, EQ_SLIDER_TEXT_4, E_PG_MAIN, 290, 264, 30, 8, "500hz", &FontStore[Fonts::E_BUILTIN5X8], GSLC_COL_WHITE, GSLC_COL_BLACK, GSLC_COL_BLACK, GSLC_ALIGN_MID_LEFT, false, true);

    gslc_ElemXSliderCreate_P(&gui_global, E_ELEM_SLIDER5, E_PG_MAIN, 340, 120, 20, 140, 0, 100, 50, 5, true, GSLC_COL_RED, GSLC_COL_BLACK);
    EqSlider5 = gslc_PageFindElemById(&gui_global, E_PG_MAIN, E_ELEM_SLIDER5);
    gslc_ElemXSliderSetStyle(&gui_global, EqSlider5, true, GSLC_COL_BLUE, 10, 5, GSLC_COL_RED_DK1);
    gslc_ElemXSliderSetPosFunc(&gui_global, EqSlider5, &on_slide_change);
    gslc_ElemCreateTxt_P(&gui_global, EQ_SLIDER_TEXT_5, E_PG_MAIN, 340, 264, 30, 8, "1kHz", &FontStore[Fonts::E_BUILTIN5X8], GSLC_COL_WHITE, GSLC_COL_BLACK, GSLC_COL_BLACK, GSLC_ALIGN_MID_LEFT, false, true);

    gslc_ElemXSliderCreate_P(&gui_global, E_ELEM_SLIDER6, E_PG_MAIN, 390, 120, 20, 140, 0, 100, 50, 5, true, GSLC_COL_RED, GSLC_COL_BLACK);
    EqSlider6 = gslc_PageFindElemById(&gui_global, E_PG_MAIN, E_ELEM_SLIDER6);
    gslc_ElemXSliderSetStyle(&gui_global, EqSlider6, true, GSLC_COL_BLUE, 10, 5, GSLC_COL_RED_DK1);
    gslc_ElemXSliderSetPosFunc(&gui_global, EqSlider6, &on_slide_change);
    gslc_ElemCreateTxt_P(&gui_global, EQ_SLIDER_TEXT_6, E_PG_MAIN, 390, 264, 30, 8, "2kHz", &FontStore[Fonts::E_BUILTIN5X8], GSLC_COL_WHITE, GSLC_COL_BLACK, GSLC_COL_BLACK, GSLC_ALIGN_MID_LEFT, false, true);

    gslc_ElemXSliderCreate_P(&gui_global, E_ELEM_SLIDER7, E_PG_MAIN, 440, 120, 20, 140, 0, 100, 50, 5, true, GSLC_COL_RED, GSLC_COL_BLACK);
    EqSlider7 = gslc_PageFindElemById(&gui_global, E_PG_MAIN, E_ELEM_SLIDER7);
    gslc_ElemXSliderSetStyle(&gui_global, EqSlider7, true, GSLC_COL_BLUE, 10, 5, GSLC_COL_RED_DK1);
    gslc_ElemXSliderSetPosFunc(&gui_global, EqSlider7, &on_slide_change);
    gslc_ElemCreateTxt_P(&gui_global, EQ_SLIDER_TEXT_7, E_PG_MAIN, 440, 264, 30, 8, "4kHz", &FontStore[Fonts::E_BUILTIN5X8], GSLC_COL_WHITE, GSLC_COL_BLACK, GSLC_COL_BLACK, GSLC_ALIGN_MID_LEFT, false, true);
}

void render_toggles()
{
    toggle(1, "Octaver");
    toggle(2, "Overdrive");
    toggle(3, "Distortion");
    toggle(4, "Custom");
}

void render_gauges()
{
    gauge(1, "Gain");
    gauge(2, "Low");
    gauge(3, "Mid");
    gauge(4, "High");
}

void render_channel_selectors()
{
    mainpage_channel_state = render_channel_toggle({
        .context = mainpage_context,
        .state = mainpage_channel_state,
        .on_toggle = &on_main_channel_toggle,
        .channelid_1 = E_ELEM_BTN_CHANNEL_1,
        .channelid_2 = E_ELEM_BTN_CHANNEL_2,
        .channelid_3 = E_ELEM_BTN_CHANNEL_3,
        .channelid_4 = E_ELEM_BTN_CHANNEL_4,
    });
}

void render_main_page()
{
    render_header();
    render_quote();
    render_channel_selectors();
    render_gauges();
    render_toggles();
    render_slider();
    __eeprom_update_component_values(mainpage_channel_state.channel);
}

#endif // MAIN_PAGE_H