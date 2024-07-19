#ifndef SLIDER_H
#define SLIDER_H

#include "../context/GuiContext.h"
#include "../enums/FontEnums.h"
#include "GUIslice.h"
#include "elem/XSlider.h"

struct SliderProps {
    GuiContext context;
    int16_t id;
    gslc_tsRect position;
    gslc_tsXSlider* state;
    bool (*callback)(void* pvGui, void* pvElemRef, int16_t nPos);
};

gslc_tsElemRef* createSlider(SliderProps props)
{
    gslc_tsGui* gui = props.context.gui;

    gslc_tsElemRef* instance = gslc_ElemXSliderCreate(gui, props.id, props.context.page, props.state,
        props.position, 0, 100, 50, 5, true);

    gslc_ElemXSliderSetStyle(gui, instance, false, GSLC_COL_BLUE, 10, 5,
        GSLC_COL_RED_DK1);
    gslc_ElemXSliderSetPosFunc(gui, instance, props.callback);

    return instance;
}

#endif // SLIDER_H