#ifndef RINGGAUGEPROPS_H // Check if RINGGAUGEPROPS_H is not defined
#define RINGGAUGEPROPS_H // Define RINGGAUGEPROPS_H

#include "../context/GuiContext.h"
#include "../enums/FontEnums.h"
#include "../references/UIGlobalRefs.h"
#include "GUIslice.h"
#include "elem/XRingGauge.h"

typedef struct RingGaugeProps {
    GuiContext context;
    int16_t id;
    gslc_tsRect position;
    char* ring_text;
    gslc_tsXRingGauge* state;
} RingGaugeProps;

gslc_tsElemRef* createRingGauge(RingGaugeProps props)
{
    gslc_tsGui* gui = props.context.gui;
    gslc_tsElemRef* instance = gslc_ElemXRingGaugeCreate(
        gui, props.id, props.context.page, props.state, props.position,
        (char*)props.ring_text, 11, E_BUILTIN5X8);

    gslc_ElemXRingGaugeSetValRange(gui, instance, 0, 100);
    gslc_ElemXRingGaugeSetVal(gui, instance, 0);
    gslc_ElemXRingGaugeSetAngleRange(gui, instance, 0, 360, 0);
    gslc_ElemXRingGaugeSetColorActiveFlat(gui, instance, GSLC_COL_RED_DK1);
    gslc_ElemXRingGaugeSetColorInactive(gui, instance, GSLC_COL_GRAY);
    gslc_ElemSetTxtCol(gui, instance, GSLC_COL_WHITE);

    return instance;
}

typedef struct UpdateRingGaugeProps {
    gslc_tsGui* gui;
    gslc_tsElemRef* element;
    long value;
} UpdateRingGaugeProps;

void update_ring_gauge(UpdateRingGaugeProps props)
{
    char knob_gauge_str[10];
    long rendered_position = map(props.value, 0, 127, 0, 100);
    gslc_ElemXRingGaugeSetVal(props.gui, props.element, rendered_position);
    snprintf(knob_gauge_str, 10, "%d", rendered_position);
    gslc_ElemSetTxtStr(props.gui, props.element, knob_gauge_str);
}

#endif // RINGGAUGEPROPS_H