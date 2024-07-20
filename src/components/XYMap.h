#ifndef XYMAP_H
#define XYMAP_H

#include "../context/GuiContext.h"
#include "../enums/FontEnums.h"
#include "../state/UIState.h"
#include "Box.h"

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

void render_xymap_lines(XYMapLinesProps props)
{
    gslc_tsGui* gui = props.context.gui;

    int16_t x_start_limit = props.bounds.x + 2;
    int16_t x_end_limit = props.bounds.w + 8;
    int16_t y_start_limit = props.bounds.y + 2;
    int16_t y_end_limit = props.bounds.h + 38;

    gslc_tsColor color = props.erase ? GSLC_COL_BLACK : props.color;

    gslc_DrawLine(gui, x_start_limit, XyMapState1.y, x_end_limit, XyMapState1.y, color);
    gslc_DrawLine(gui, XyMapState1.x, y_start_limit, XyMapState1.x, y_end_limit, color);
}

gslc_tsElemRef* createXYMap(XYMapProps props)
{
    gslc_tsGui* gui = props.context.gui;

    gslc_tsElemRef* instance = createBox({
        .context = props.context,
        .id = props.id,
        .position = props.position,
        .on_touch = props.on_touch,
    });

    render_xymap_lines({
        .context = props.context,
        .bounds = props.position,
        .color = props.color,
        .erase = false,
    });

    return instance;
}

#endif // XYMAP_H