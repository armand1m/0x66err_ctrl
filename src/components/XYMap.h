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

typedef struct XYMapLineBounds {
    int16_t x_start;
    int16_t x_end;
    int16_t y_start;
    int16_t y_end;
} XYMapLineBounds;

XYMapLineBounds create_xymap_line_bounds(gslc_tsRect rect)
{
    return {
        .x_start = rect.x + 2,
        .x_end = rect.w + 8,
        .y_start = rect.y + 2,
        .y_end = rect.h + 38,
    };
}

void render_xymap_lines(XYMapLinesProps props)
{
    gslc_tsGui* gui = props.context.gui;
    gslc_tsColor color = props.erase ? GSLC_COL_BLACK : props.color;
    XYMapLineBounds bounds = create_xymap_line_bounds(props.bounds);

    gslc_DrawLine(gui, bounds.x_start, XyMapState1.y, bounds.x_end, XyMapState1.y, color);
    gslc_DrawLine(gui, XyMapState1.x, bounds.y_start, XyMapState1.x, bounds.y_end, color);
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