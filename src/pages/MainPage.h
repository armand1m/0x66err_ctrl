#ifndef MAIN_PAGE_H
#define MAIN_PAGE_H

#define CONCAT(arg1, arg2) arg1##arg2

#include "../components/Button.h"
#include "../components/ChannelToggle.h"
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
#include "PageHandlers.h"

GuiContext mainpage_context = { .gui = &gui_global, .page = E_PG_MAIN };

bool on_xymap_button_press(void* gui_pointer, void* element_ref_pointer, gslc_teTouch touch_event,
    int16_t _touch_x, int16_t _touch_y)
{
    if (touch_event != gslc_teTouch::GSLC_TOUCH_UP_IN) {
        return true;
    }

    set_current_page(E_PG_XYMAP);
    return true;
}

bool on_toggle_press(void* gui_pointer, void* element_ref_pointer, gslc_teTouch touch_event,
    int16_t _touch_x, int16_t _touch_y)
{
    gslc_tsGui* gui = (gslc_tsGui*)(gui_pointer);
    gslc_tsElemRef* element_ref = (gslc_tsElemRef*)(element_ref_pointer);
    gslc_tsElem* element = gslc_GetElemFromRef(gui, element_ref);
    int index = get_cc_index_by_element_id(element->nId);

    if (touch_event == GSLC_TOUCH_UP_IN) {
        int value = get_toggle_state(element_ref) ? 127 : 0;
        send_midi_cc(toggle_midi_cc[index], value, mainpage_channel_state.channel);
    }

    return true;
}

bool on_slide_change(void* gui_pointer, void* element_ref_pointer, int16_t slider_position)
{
    gslc_tsGui* gui = (gslc_tsGui*)(gui_pointer);
    gslc_tsElemRef* element_ref = (gslc_tsElemRef*)(element_ref_pointer);
    gslc_tsElem* element = gslc_GetElemFromRef(gui, element_ref);
    int index = get_cc_index_by_element_id(element->nId);

    int control_number = slider_midi_cc[index];
    int control_value = map(slider_position, 0, 100, 127, 0);

    send_midi_cc(control_number, control_value, mainpage_channel_state.channel);

    return true;
}

bool on_main_channel_toggle(void* gui_pointer, void* element_ref_pointer, gslc_teTouch touch_event,
    int16_t _touch_x, int16_t _touch_y)
{
    gslc_tsGui* gui = (gslc_tsGui*)(gui_pointer);
    gslc_tsElemRef* element_ref = (gslc_tsElemRef*)(element_ref_pointer);
    gslc_tsElem* element = gslc_GetElemFromRef(gui, element_ref);

    if (touch_event == GSLC_TOUCH_UP_IN) {
        mainpage_channel_state.channel = get_channel_number_by_element_id(element->nId);

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
    }

    return true;
}

#define quote(index, txt, col)                                \
    createText((TextProps) {                                  \
        .context = mainpage_context,                          \
        .id = CONCAT(QUOTE_TEXT_, index),                     \
        .position = { 250, 50 + (10 * (index - 1)), 210, 8 }, \
        .text = txt,                                          \
        .font = NULL,                                         \
        .align = TextAlign::LEFT,                             \
        .color = col })

#define gauge(index, gauge_label)                                                     \
    static char CONCAT(ring_gauge_text_, index)[XRING_STR_MAX] = "0";                 \
    RingGaugeElements CONCAT(ring_gauge_, index) = createRingGauge((RingGaugeProps) { \
        .context = mainpage_context,                                                  \
        .id = CONCAT(E_ELEM_RINGGAUGE, index),                                        \
        .position = { 15 + (60 * (index - 1)), 50, 45, 45 },                          \
        .ring_text = CONCAT(ring_gauge_text_, index),                                 \
        .label = gauge_label,                                                         \
        .label_id = CONCAT(E_ELEM_KNOB_, index),                                      \
        .state = CONCAT(&RingGaugeState, index) });                                   \
    CONCAT(KnobGauge, index) = CONCAT(ring_gauge_, index).ring_gauge;

#define toggle(index, toggle_label)                                                     \
    ToggleElements CONCAT(toggle_, index) = createToggle({ .context = mainpage_context, \
        .id = CONCAT(E_ELEM_TOGGLE, index),                                             \
        .position = { 15, 140 + (40 * (index - 1)), 35, 20 },                           \
        .label = toggle_label,                                                          \
        .label_id = CONCAT(E_ELEM_TOGGLE_TEXT_, index),                                 \
        .state = CONCAT(&ToggleState, index),                                           \
        .on_touch = &on_toggle_press });                                                \
    CONCAT(Toggle, index) = CONCAT(toggle_, index).toggle;

#define slider(index, slider_label)                                                     \
    SliderElements CONCAT(slider_, index) = createSlider({ .context = mainpage_context, \
        .id = CONCAT(E_ELEM_SLIDER, index),                                             \
        .position = { 140 + (50 * (index - 1)), 130, 20, 140 },                         \
        .label = slider_label,                                                          \
        .label_id = CONCAT(EQ_SLIDER_TEXT_, index),                                     \
        .state = CONCAT(&SliderState, index),                                           \
        .on_change = &on_slide_change });                                               \
    CONCAT(EqSlider, index) = CONCAT(slider_, index).slider;

void render_header()
{
    int16_t big_text = E_BUILTIN20X32;

    createText({ .context = mainpage_context,
        .id = E_ELEM_APPHEADER,
        .position = { 190, 10, 285, 32 },
        .text = "0x66err_ctrl",
        .font = &big_text });

    createButton({ .context = mainpage_context,
        .id = E_ELEM_XYMAP_BTN,
        .position = { 15, 10, 80, 20 },
        .text = "XY MAP",
        .on_press = &on_xymap_button_press,
        .is_active = false });

    quote(1, "Cause everyone's too scared to heal", &GSLC_COL_WHITE);
    quote(2, "They don't give a fuck how they feel", &GSLC_COL_WHITE);
    quote(3, "And I don't know how to deal anymore", &GSLC_COL_WHITE);
    quote(4, "Well maybe the damage is done", &GSLC_COL_RED_DK1);
    quote(5, "Maybe the darkness has won", &GSLC_COL_RED_DK2);
    quote(6, "And we were programmed just to suffer", &GSLC_COL_WHITE);
}

void render_main_page()
{
    render_header();

    mainpage_channel_state = render_channel_toggle({
        .context = mainpage_context,
        .state = mainpage_channel_state,
        .on_toggle = &on_main_channel_toggle,
        .channelid_1 = E_ELEM_BTN_CHANNEL_1,
        .channelid_2 = E_ELEM_BTN_CHANNEL_2,
        .channelid_3 = E_ELEM_BTN_CHANNEL_3,
        .channelid_4 = E_ELEM_BTN_CHANNEL_4,
    });

    gauge(1, "Gain");
    gauge(2, "Low");
    gauge(3, "Mid");
    gauge(4, "High");

    toggle(1, "Octaver");
    toggle(2, "Overdrive");
    toggle(3, "Distortion");
    toggle(4, "Custom");

    slider(1, "65hz");
    slider(2, "125hz");
    slider(3, "250hz");
    slider(4, "500hz");
    slider(5, "1kHz");
    slider(6, "2kHz");
    slider(7, "4kHz");
}

#endif // MAIN_PAGE_H