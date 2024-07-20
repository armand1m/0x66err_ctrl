#ifndef BUTTON_H
#define BUTTON_H

#include "../context/GuiContext.h"
#include "../enums/FontEnums.h"
#include "GUIslice.h"

typedef struct ButtonProps {
    GuiContext context;
    int16_t id;
    gslc_tsRect position;
    char* text;
    GSLC_CB_TOUCH on_press;
} ButtonProps;

gslc_tsElemRef* createButton(ButtonProps props)
{
    gslc_tsGui* gui = props.context.gui;
    gslc_tsElemRef* instance = gslc_ElemCreateBtnTxt(gui, props.id, props.context.page, props.position,
        props.text, 0, E_BUILTIN5X8, props.on_press);
    gslc_ElemSetCol(gui, instance, GSLC_COL_GRAY, GSLC_COL_GRAY_DK1,
        GSLC_COL_GRAY);

    return instance;
}

#endif // BUTTON_H