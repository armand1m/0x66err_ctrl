# 0x66err_ctrl

> this is a project in progress. consider this very unstable and quirky.

![Initial prototype](https://github.com/armand1m/0x66err_ctrl/blob/main/assets/ctrl.jpeg)

0x66err_ctrl is a homemade midi controller on top of Arduino Mega 2560 R3.

It features a LCD 3.5" 480x320 touchscreen and 4 rotary encoders (with 8 being planned in the future).
In the future, it might include some drumpads as well based on Adafruit Trellis.

## Features:

- [x] 7-band EQ on Touchscreen
- [x] 3 toggles (working both on touchscreen and on knob press)
- [x] 4 rotary encoders for knob control 
- [x] single page control

### Future:

- [ ] Multipage control
- [ ] 8 rotary encoders
- [ ] 9-band EQ on Touchscreen
- [ ] 9-band EQ physical module
- [ ] Touchscreen XY map for Autofilter control _(x being frequency and y being resonance)_
- [ ] Momentary gates _(to enable things like killswitches)_
- [ ] 4x4 drumpad physical module
- [ ] Preset selection screen

## Hardware

- [TFT-LCD 3.5" 480x320 display, ILI9486 driver](https://www.amazon.nl/dp/B07Y6179LG)
- [4 Rotary encoders](https://www.amazon.nl/WayinTop-Roterende-Encoder-Module-Drukknop/dp/B07T3672VK)
- [Arduino Mega 2560 R3](https://store.arduino.cc/products/arduino-mega-2560-rev3)

## Libraries

### UI and Touchscreen Events

UI is powered by GUISlice: https://github.com/ImpulseAdventure/GUIslice

GUISlice offers not only touch-compatible components out of the box
and it also provides LCD and touchscreen setup and configuration examples.

It is super well documented and works perfectly with the hardware chosen here.

The UI is built using the GUISlice Builder, with some extra twirks directly in code.

You can start the GUISliceBuilder app using the following command:

```sh
cd ./tooling/GUIsliceBuilder
./GUIslice.sh
```

Then you can open the project at `tooling/GUISliceProjects/GUISliceProject.prj`

![Project](https://github.com/armand1m/0x66err_ctrl/blob/main/assets/uiproject.jpeg)

#### Code Generation

The GUISliceBuilder features code generation.

Once generated, do the following:

- Copy the contents of `tooling/GUISliceProjects/GUISliceProjects_GSLC.h` into `UI.h` and save it.
- Copy the Program Globals in `tooling/GUISliceProjects/GUISliceProjects.ino` into `UIReferences.h`. Replace the previous ones.

I might work on some better structure to allow for more dynamic updates of the UI without so much hassle.

### Rotary Encoders

Rotary Encoders are powered by the `EncoderButton` library: https://github.com/Stutchbury/EncoderButton

EncoderButton offers an event-based API for using rotary encoders. It manages all the rotary states and it triggers given callbacks for specific events.
It already gives you support to attribute identifiers to every rotary encoder, which comes in handy.

The library is thin-wrapper built on top of the well-known Encoder library.
It adds button click support with clickCount by using the `Bounce2` library.

### MIDI support

MIDI is powered by the <MIDI.h> standard library.

Most MIDI events are sent as Control Change events over channel 1.

MIDI events can be debugged during development using the Serial Monitor on 115200 baud.

### MIDI over USB

Since Arduino Mega 2560 R3 doesn't support MIDI over USB out of the box, you need to flash HIDUINO in the board atmega16u2.

You can find the scripts and built firmware needed to switch between HIDUINO and the default USBSerial firmwares on this repo.

#### Flashing into atmega16u2

- Uncomment the `#define HIDUINO` in the main project file.
- Flash it into the Arduino Mega 2560 as you'd normally do.
- Short the RESET and GND pins close to the `atmega16u2` to get it into flash mode.
- Run `./tooling/hiduino/flashmidi.sh` to flash HIDUINO firmware _(customized for this specific build. device will show up as `0x66err_ctrl`)_.
- Disconnect device and connect again.

If you need to make changes to the firmware, you will need to flash the original firmware back into the `atmega16u2`

- Short the RESET and GND pins close to the `atmega16u2` to get it into flash mode.
- Run `./tooling/hiduino/flashoriginal.sh` to flash back the Arduino Mega 2560 R3 default USBSerial firmware.
