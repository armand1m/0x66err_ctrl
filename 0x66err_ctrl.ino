// Define this flag when building the firmware before flashing HIDUINO
#define HIDUINO 1
#define GSLC_USE_PROGMEM 1

#include "src/Loggers.h"
#include "src/UI.h"
#include "src/midi/CCMaps.h"
#include "src/midi/Transport.h"
#include "src/peripherals/RotaryEncoderHandlers.h"
#include "src/peripherals/RotaryEncoders.h"
#include "src/references/UIGlobalRefs.h"
#include "src/utils/mem.h"

void setup()
{
    midi_transport_begin();
    setup_eeprom();
    debug_user_interface();
    setup_user_interface();
    setup_encoders(encoders, on_encoder_spin, on_encoder_click);
    log_free_memory();
}

void loop()
{
    midiSerial.read();
    update_user_interface();
    update_encoders(encoders);
    __eeprom_loop();
}