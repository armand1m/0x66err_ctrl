#ifndef TOGGLE_H
#define TOGGLE_H

#include "../context/GuiContext.h"
#include "../enums/FontEnums.h"
#include "../references/UIGlobalRefs.h"
#include "GUIslice.h"
#include "elem/XTogglebtn.h"

typedef struct ToggleProps {
    GuiContext context;
    int16_t id;
    gslc_tsRect position;
    char* text;
    gslc_tsXTogglebtn* state;
    bool (*callback)(void* pvGui, void* pvElemRef, gslc_teTouch eTouch,
        int16_t nX, int16_t nY);
} ToggleProps;

gslc_tsElemRef* createToggle(ToggleProps props)
{
    gslc_tsElemRef* instance = gslc_ElemXTogglebtnCreate(
        props.context.gui, props.id, props.context.page, props.state,
        props.position, GSLC_COL_GRAY, GSLC_COL_RED_DK1, GSLC_COL_GRAY_LT3, true,
        false, props.callback);

    return instance;
}

typedef struct UpdateToggleStateProps {
    gslc_tsGui* gui;
    gslc_tsElemRef* element;
} UpdateToggleStateProps;

bool switch_toggle_state(UpdateToggleStateProps props)
{
    bool state = !gslc_ElemXTogglebtnGetState(props.gui, props.element);
    gslc_ElemXTogglebtnSetState(props.gui, props.element, state);
    return state;
}

#endif // TOGGLE_H