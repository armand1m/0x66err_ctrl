#ifndef TEXT_H
#define TEXT_H

#include "../context/GuiContext.h"
#include "../enums/FontEnums.h"
#include "GUIslice.h"

struct TextProps {
    GuiContext context;
    int16_t id;
    gslc_tsRect position;
    char* text;
    int16_t* font;
    gslc_tsColor* color;
};

gslc_tsElemRef* createText(TextProps props)
{
    gslc_tsGui* gui = props.context.gui;

    int16_t font = (props.font != NULL) ? *props.font : E_BUILTIN5X8;
    gslc_tsColor color = (props.color != NULL) ? *props.color : GSLC_COL_WHITE;

    gslc_tsElemRef* instance = gslc_ElemCreateTxt(
        props.context.gui, props.id, props.context.page, props.position,
        props.text, 0, font);

    gslc_ElemSetTxtAlign(gui, instance, GSLC_ALIGN_TOP_MID);
    gslc_ElemSetFillEn(gui, instance, false);
    gslc_ElemSetTxtCol(gui, instance, color);

    return instance;
}

#endif // TEXT_H