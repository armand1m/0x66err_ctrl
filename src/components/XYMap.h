#ifndef XYMAP_H
#define XYMAP_H

#include "../context/GuiContext.h"
#include "../enums/FontEnums.h"
#include "../references/ExternComponents.h"

typedef struct XYMapProps {
    GuiContext context;
    int16_t id;
    gslc_tsRect position;
    GSLC_CB_TOUCH on_touch;
    gslc_tsColor color;
} XYMapProps;

typedef struct XYMapLinesProps {
    GuiContext context;
    gslc_tsRect bounds;
    gslc_tsColor color;
    bool erase;
} XYMapLinesProps;

void renderXYMapLines(XYMapLinesProps props)
{
    gslc_tsGui* gui = props.context.gui;

    int16_t x_start_limit = props.bounds.x + 2;
    int16_t x_end_limit = props.bounds.w + 8;
    int16_t y_start_limit = props.bounds.y + 2;
    int16_t y_end_limit = props.bounds.h + 38;

    gslc_tsColor color = props.erase ? GSLC_COL_BLACK : props.color;

    gslc_DrawLine(gui, x_start_limit, xyMapCurrentY, x_end_limit, xyMapCurrentY, color);
    gslc_DrawLine(gui, xyMapCurrentX, y_start_limit, xyMapCurrentX, y_end_limit, color);
}

gslc_tsElemRef* createXYMap(XYMapProps props)
{
    gslc_tsGui* gui = props.context.gui;

    gslc_tsElemRef* instance = gslc_ElemCreateBox(gui, props.id, props.context.page, props.position);
    gslc_ElemSetClickEn(gui, instance, true);
    gslc_ElemSetTouchFunc(gui, instance, props.on_touch);

    renderXYMapLines({
        .context = props.context,
        .bounds = props.position,
        .color = props.color,
        .erase = false,
    });

    return instance;
}

#endif // XYMAP_H