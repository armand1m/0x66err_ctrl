#ifndef SLIDER_H
#define SLIDER_H

#include "../context/GuiContext.h"
#include "../enums/FontEnums.h"
#include "GUIslice.h"
#include "elem/XSlider.h"

typedef struct UpdateSliderProps {
    gslc_tsGui* gui;
    gslc_tsElemRef* element;
    long value;
} UpdateSliderProps;

void update_slider(UpdateSliderProps props)
{
    return gslc_ElemXSliderSetPos(props.gui, props.element, map(props.value, 0, 127, 100, 0));
}

#endif // SLIDER_H