#ifndef RINGGAUGEPROPS_H // Check if RINGGAUGEPROPS_H is not defined
#define RINGGAUGEPROPS_H // Define RINGGAUGEPROPS_H

#include "../context/GuiContext.h"
#include "../enums/FontEnums.h"
#include "../references/UIGlobalRefs.h"
#include "GUIslice.h"
#include "Text.h"
#include "elem/XRingGauge.h"

typedef struct RingGaugeProps {
    GuiContext context;
    int16_t id;
    gslc_tsRect position;
    char* ring_text;
    char* label;
    int16_t label_id;
    gslc_tsXRingGauge* state;
} RingGaugeProps;

typedef struct RingGaugeElements {
    gslc_tsElemRef* ring_gauge;
    gslc_tsElemRef* label;
} RingGaugeElements;

RingGaugeElements createRingGauge(RingGaugeProps props)
{
    gslc_tsGui* gui = props.context.gui;
    gslc_tsElemRef* instance = gslc_ElemXRingGaugeCreate(
        gui, props.id, props.context.page, props.state, props.position,
        props.ring_text, XRING_STR_MAX, E_BUILTIN5X8);

    gslc_ElemXRingGaugeSetValRange(gui, instance, 0, 100);
    gslc_ElemXRingGaugeSetVal(gui, instance, 0);
    gslc_ElemXRingGaugeSetAngleRange(gui, instance, 0, 360, 0);
    gslc_ElemXRingGaugeSetColorActiveFlat(gui, instance, GSLC_COL_RED_DK1);
    gslc_ElemXRingGaugeSetColorInactive(gui, instance, GSLC_COL_GRAY);
    // gslc_ElemXRingGaugeSetQuality(gui, instance, 360);
    // gslc_ElemXRingGaugeSetThickness(gui, instance, 10);
    gslc_ElemSetTxtCol(gui, instance, GSLC_COL_WHITE);

    RingGaugeElements elements = {
        .ring_gauge = instance,
        .label = createText({
            .context = props.context,
            .id = props.label_id,
            .position = (gslc_tsRect) { props.position.x, props.position.y + 50, 50, 10 },
            .text = props.label,
            .font = NULL,
            .align = TextAlign::CENTER,
        }),
    };

    return elements;
}

typedef struct UpdateRingGaugeProps {
    gslc_tsGui* gui;
    gslc_tsElemRef* element;
    long value;
} UpdateRingGaugeProps;

void update_ring_gauge(UpdateRingGaugeProps props)
{
    char ring_text[XRING_STR_MAX];
    long rendered_position = map(props.value, 0, 127, 0, 100);
    snprintf(ring_text, XRING_STR_MAX, "%ld", rendered_position);
    gslc_ElemXRingGaugeSetVal(props.gui, props.element, rendered_position);
    gslc_ElemSetTxtStr(props.gui, props.element, ring_text);
}

#endif // RINGGAUGEPROPS_H