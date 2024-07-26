#ifndef BUTTON_H
#define BUTTON_H

#include "../context/GuiContext.h"
#include "../enums/FontEnums.h"

#include "GUIslice.h"

typedef struct ToggleButtonActiveProps {
    GuiContext context;
    gslc_tsElemRef* element;
    bool active;
} SetButtonActiveProps;

void toggle_button_active(ToggleButtonActiveProps props)
{
    if (props.active) {
        return gslc_ElemSetCol(props.context.gui, props.element, GSLC_COL_RED_DK3, GSLC_COL_RED_DK1,
            GSLC_COL_RED_DK1);
    }

    return gslc_ElemSetCol(props.context.gui, props.element, GSLC_COL_GRAY, GSLC_COL_GRAY_DK1,
        GSLC_COL_GRAY);
}

typedef struct ButtonProps {
    GuiContext context;
    int16_t id;
    gslc_tsRect position;
    char* text;
    GSLC_CB_TOUCH on_press;
    bool is_active;
} ButtonProps;

gslc_tsElemRef* createButton(ButtonProps props)
{
    gslc_tsGui* gui = props.context.gui;
    gslc_tsElemRef* instance = gslc_ElemCreateBtnTxt(gui, props.id, props.context.page, props.position,
        props.text, 0, E_BUILTIN5X8, props.on_press);

    toggle_button_active({
        .context = props.context,
        .element = instance,
        .active = props.is_active,
    });

    return instance;
}

#endif // BUTTON_H