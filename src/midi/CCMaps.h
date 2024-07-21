#ifndef MIDI_CCMAPS_H
#define MIDI_CCMAPS_H

// reference: https://anotherproducer.com/online-tools-for-musicians/midi-cc-list/
#define KNOB_CC_1 16
#define KNOB_CC_2 17
#define KNOB_CC_3 18
#define KNOB_CC_4 19
#define SLIDER_CC_1 20
#define SLIDER_CC_2 21
#define SLIDER_CC_3 22
#define SLIDER_CC_4 23
#define SLIDER_CC_5 24
#define SLIDER_CC_6 25
#define SLIDER_CC_7 26
#define TOGGLE_CC_1 28
#define TOGGLE_CC_2 29
#define TOGGLE_CC_3 30
#define TOGGLE_CC_4 31
#define XY_MAP_CC_X 11
#define XY_MAP_CC_Y 86

byte knob_midi_cc[4] = { KNOB_CC_1, KNOB_CC_2, KNOB_CC_3, KNOB_CC_4 };
byte slider_midi_cc[7] = { SLIDER_CC_1, SLIDER_CC_2, SLIDER_CC_3, SLIDER_CC_4, SLIDER_CC_5, SLIDER_CC_6, SLIDER_CC_7 };
byte toggle_midi_cc[4] = { TOGGLE_CC_1, TOGGLE_CC_2, TOGGLE_CC_3, TOGGLE_CC_4 };
byte xy_map_midi_cc[2] = { XY_MAP_CC_X, XY_MAP_CC_Y };

#endif // MIDI_CCMAPS_H