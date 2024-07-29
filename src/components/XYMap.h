#ifndef XYMAP_H
#define XYMAP_H

#include "../context/GuiContext.h"
#include "../enums/FontEnums.h"
#include "../state/XYMapState.h"
#include "../utils/clamp.h"
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
    XYMapState state;
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
    int16_t adjusted_x = clamp(props.state.x + 20, bounds.x_start, bounds.x_end);
    int16_t adjusted_y = clamp(props.state.y + 30, bounds.y_start, bounds.y_end);

    // horizontal line
    gslc_DrawLine(gui, bounds.x_start, adjusted_y, bounds.x_end, adjusted_y, color);
    // vertical line
    gslc_DrawLine(gui, adjusted_x, bounds.y_start, adjusted_x, bounds.y_end, color);
}

gslc_tsElemRef* createXYMap(XYMapProps props)
{
    return createBox({
        .context = props.context,
        .id = props.id,
        .position = props.position,
        .on_touch = props.on_touch,
    });
}
#endif // XYMAP_H