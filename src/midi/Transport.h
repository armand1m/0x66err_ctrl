#ifndef MIDI_TRANSPORT_H
#define MIDI_TRANSPORT_H
#include "../Loggers.h"
#include "../components/RingGauge.h"
#include "../components/Slider.h"
#include "../components/Toggle.h"
#include "../enums/ComponentEnums.h"
#include "../references/UIGlobalRefs.h"
#include "../state/EEPROMState.h"
#include "../state/UIState.h"
#include <MIDI.h>

#ifdef HIDUINO
MIDI_CREATE_INSTANCE(HardwareSerial, Serial, midiSerial);
#else
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, midiSerial);
#endif

const byte sysex_request[] = { 0xF0, 0x00, 0x01, 0x05, 0x7F, 0xF7 }; // Example SysEx request

void handle_control_change(byte channel, byte number, byte value)
{
    ChannelState* state = __eeprom_get_channel_state(channel);
    gslc_tsElemRef* toggle = get_toggle_by_cc_number(number);

    if (toggle != NULL) {
        bool new_value = value > 0;
        gslc_tsElem* element = gslc_GetElemFromRef(&gui_global, toggle);
        __eeprom_set_toggle_state(channel, element->nId, new_value);

        if (mainpage_channel_state.channel == channel) {
            set_toggle_state({
                .gui = &gui_global,
                .element = toggle,
                .value = new_value,
            });
        }
    }

    gslc_tsElemRef* slider = get_slider_by_cc_number(number);

    if (slider != NULL) {
        gslc_tsElem* element = gslc_GetElemFromRef(&gui_global, slider);
        __eeprom_set_slider_state(channel, element->nId, value);

        if (mainpage_channel_state.channel == channel) {
            update_slider({
                .gui = &gui_global,
                .element = slider,
                .value = value,
            });
        }
    }

    gslc_tsElemRef* gauge = get_gauge_by_cc_number(number);

    if (gauge != NULL) {
        gslc_tsElem* element = gslc_GetElemFromRef(&gui_global, gauge);
        __eeprom_set_knob_state(channel, element->nId, value);

        if (mainpage_channel_state.channel == channel) {
            EncoderButton encoder = get_encoder_by_cc_number(number);
            encoder.resetPosition(value);
            update_ring_gauge({
                .gui = &gui_global,
                .element = gauge,
                .value = value, // update_ring_gauge will map this to 0-100
            });
        }
    }

    if (number == XY_MAP_CC_X) {
        state->xymap_x = map(value, 0, 127, bounds.x_start, bounds.x_end);
    }

    if (number == XY_MAP_CC_Y) {
        state->xymap_y = map(value, 0, 127, bounds.y_end, bounds.y_start);
    }

    if (gslc_GetPageCur(&gui_global) == xymap_page_context.page && xymap_channel_state.channel == channel) {
        render_xymap_lines({ .context = xymap_page_context,
            .bounds = xymap_position,
            .color = GSLC_COL_GRAY_LT2,
            .border_color = GSLC_COL_GRAY_DK2,
            .state = XyMapRenderedState,
            .erase = true });

        XyMapRenderedState.x = state->xymap_x;
        XyMapRenderedState.y = state->xymap_y;

        render_xymap_lines({ .context = xymap_page_context,
            .bounds = xymap_position,
            .color = GSLC_COL_GRAY_LT2,
            .border_color = GSLC_COL_GRAY_DK2,
            .state = XyMapRenderedState,
            .erase = false });
    }
}

#ifndef HIDUINO
void parse_midi_serial_message(String message)
{
    message.trim();

    if (!message.startsWith("midi: ")) {
        infolog("Invalid message prefix.");
        return;
    }

    // Remove "midi: " prefix
    message = message.substring(6);

    int first_comma = message.indexOf(',');
    int second_comma = message.indexOf(',', first_comma + 1);

    if (first_comma == -1 || second_comma == -1) {
        infolog("Invalid message format. Could not find two commas.");
        return;
    }

    int cc_number = message.substring(0, first_comma).toInt();
    int cc_value = message.substring(first_comma + 1, second_comma).toInt();
    int channel = message.substring(second_comma + 1).toInt();

    handle_control_change((byte)channel, (byte)cc_number, (byte)cc_value);
}
#endif

void midi_transport_loop()
{
#ifndef HIDUINO
    static String input_string = "";
    static bool string_complete = false;

    // read all characters in the buffer
    // until a line break comes in.
    // make sure to set the line ending to be LF
    // in the serial monitor configuration.
    while (Serial.available()) {
        char input_char = (char)Serial.read();
        input_string += input_char;
        if (input_char == '\n') {
            string_complete = true;
        }
    }

    if (string_complete) {
        parse_midi_serial_message(input_string);
        input_string = "";
        string_complete = false;
    }
#endif
}

void setup_midi_handlers()
{
    midiSerial.setHandleControlChange(handle_control_change);
    midiSerial.turnThruOff();
}

void midi_transport_begin()
{
#ifdef HIDUINO
    Serial.begin(31250);
#else
    Serial.begin(115200);
    Serial1.begin(31250);
#endif

    midiSerial.begin(MIDI_CHANNEL_OMNI);
    setup_midi_handlers();
}

#ifndef HIDUINO
static void log_midi_cc(int control_number, int control_value, int channel)
{
    infolog("Control Change: ");
    infolog(String(control_number));
    infolog(", ");
    infolog(String(control_value));
    infolog(", ");
    infolog(String(channel));
    infolog("\n");
}
#endif

void __midi_send_cc(int control_number, int control_value, int channel)
{
#ifndef HIDUINO
    log_midi_cc(control_number, control_value, channel);
#endif
    midiSerial.sendControlChange(control_number, control_value, channel);
}

#endif // MIDI_TRANSPORT_H