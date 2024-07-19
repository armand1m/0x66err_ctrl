#ifndef GUICONTEXT_H
#define GUICONTEXT_H

#include <GUIslice.h>

typedef struct GuiContext {
    gslc_tsGui* gui;
    int16_t page;
} GuiContext;

#endif // GUICONTEXT_H