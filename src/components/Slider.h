#ifndef SLIDER_H
#define SLIDER_H

#include "../context/GuiContext.h"
#include "../enums/FontEnums.h"
#include "GUIslice.h"
#include "Text.h"
#include "elem/XSlider.h"

typedef struct SliderProps {
    GuiContext context;
    int16_t id;
    gslc_tsRect position;
    char* label;
    int16_t label_id;
    gslc_tsXSlider* state;
    GSLC_CB_XSLIDER_POS on_change;
} SliderProps;

typedef struct SliderElements {
    gslc_tsElemRef* slider;
    gslc_tsElemRef* label;
} SliderElements;

SliderElements createSlider(SliderProps props)
{
    gslc_tsGui* gui = props.context.gui;

    gslc_tsElemRef* instance = gslc_ElemXSliderCreate(gui, props.id, props.context.page, props.state,
        props.position, 0, 100, 50, 5, true);

    gslc_ElemXSliderSetStyle(gui, instance, false, GSLC_COL_BLUE, 10, 5,
        GSLC_COL_RED_DK1);
    gslc_ElemXSliderSetPosFunc(gui, instance, props.on_change);

    SliderElements elements = {
        .slider = instance,
        .label = createText({
            .context = props.context,
            .id = props.label_id,
            .position = {
                .x = props.position.x,
                .y = props.position.y + 144,
                .w = 30,
                .h = 8,
            },
            .text = props.label,
        }),
    };

    return elements;
}

typedef struct UpdateSliderProps {
    gslc_tsGui* gui;
    gslc_tsElemRef* element;
    long value;
} UpdateSliderProps;

void update_slider(UpdateSliderProps props)
{
    int slider_value = map(props.value, 0, 127, 100, 0);
    gslc_ElemXSliderSetPos(props.gui, props.element, slider_value);
}

#endif // SLIDER_H