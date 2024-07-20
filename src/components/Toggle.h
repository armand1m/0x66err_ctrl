#ifndef TOGGLE_H
#define TOGGLE_H

#include "../context/GuiContext.h"
#include "../enums/FontEnums.h"
#include "../references/UIGlobalRefs.h"
#include "GUIslice.h"
#include "Text.h"
#include "elem/XTogglebtn.h"

typedef struct ToggleProps {
    GuiContext context;
    int16_t id;
    gslc_tsRect position;
    char* label;
    int16_t label_id;
    gslc_tsXTogglebtn* state;
    GSLC_CB_TOUCH on_touch;
} ToggleProps;

typedef struct ToggleElements {
    gslc_tsElemRef* toggle;
    gslc_tsElemRef* label;
} ToggleElements;

ToggleElements createToggle(ToggleProps props)
{
    gslc_tsElemRef* toggle = gslc_ElemXTogglebtnCreate(
        props.context.gui, props.id, props.context.page, props.state,
        props.position, GSLC_COL_GRAY, GSLC_COL_RED_DK1, GSLC_COL_GRAY_LT3, true,
        false, props.on_touch);

    ToggleElements elements = {
        .toggle = toggle,
        .label = createText({
            .context = props.context,
            .id = props.label_id,
            .position = {
                .x = props.position.x + 40,
                .y = props.position.y + 7,
                .w = props.position.w + 7,
                .h = props.position.h - 12,
            },
            .text = props.label,
            .font = NULL,
            .align = TextAlign::LEFT,
        }),
    };

    return elements;
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