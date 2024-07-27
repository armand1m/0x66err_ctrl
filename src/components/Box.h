#ifndef BOX_H
#define BOX_H

#include "../context/GuiContext.h"

typedef struct BoxProps {
    GuiContext context;
    int16_t id;
    gslc_tsRect position;
    GSLC_CB_TOUCH on_touch;
} BoxProps;

gslc_tsElemRef* createBox(BoxProps props)
{
    gslc_tsGui* gui = props.context.gui;
    gslc_tsElemRef* instance = gslc_ElemCreateBox(gui, props.id, props.context.page, props.position);
    gslc_ElemSetClickEn(gui, instance, true);
    gslc_ElemSetTouchFunc(gui, instance, props.on_touch);

    return instance;
}

#endif // BUTTON_H