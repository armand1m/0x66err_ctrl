// Define this flag when building the firmware before flashing HIDUINO
// #define HIDUINO

#include "src/Loggers.h"
#include "src/UI.h"
#include "src/midi/CCMaps.h"
#include "src/midi/Transport.h"
#include "src/peripherals/RotaryEncoderHandlers.h"
#include "src/peripherals/RotaryEncoders.h"
#include "src/references/UIGlobalRefs.h"

void setup()
{
#ifndef HIDUINO
    gslc_InitDebug(&DebugOut);
#endif

    midi_transport_begin();
    render();
    setup_encoders(encoders, on_encoder_spin, on_encoder_click);
}

void loop()
{
    gslc_Update(&m_gui);
    update_encoders(encoders);
}
