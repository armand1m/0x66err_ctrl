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

#endif // BUTTON_H