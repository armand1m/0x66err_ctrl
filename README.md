# 0x66err_ctrl

0x66err_ctrl is a DIY MIDI Controller on top of Arduino Mega 2560 R3.

In the current prototype, it features a LCD 3.5" 480x320 touchscreen and 4 rotary encoders.

![Initial prototype](https://github.com/armand1m/0x66err_ctrl/blob/main/assets/ctrl.jpeg)

https://github.com/armand1m/0x66err_ctrl/raw/main/assets/xymap.mp4

## Features:

- [x] 7-band EQ on Touchscreen
    - [x] on touch enabled
    - [x] on software change enabled
- [x] 3 toggles
    - [x] on touch enabled
    - [x] on knob click enabled
    - [x] on software change enabled
- [x] 4 rotary encoders for knob control 
    - [ ] on touch enabled
    - [x] on knob position change enabled
    - [x] on software change enabled
- [x] Multi Page Control
    - Having a navigation system means it gets easier to add new features.
- [x] Touchscreen XY map  _(x being frequency and y being resonance)_
    - Useful for certain things like Ableton's Autofilter _(map X to the Frequency knob, and Y to the Resonance)_
- [x] Sync MIDI messages from software to hardware
    - Changing mapped properties in Ableton will change them in the device as well.
- [x] 4 Channel Selection for both Amp page and XYMap page
    - You can switch between 4 midi channels individually on each page for each device.
- [x] Storing settings and selections on EEPROM
- [x] Syncing from DAW into EEPROM

### Next in line:

- [ ] 8 rotary encoders
- [ ] Preset selection screen
- [ ] 4x4 drumpad physical module

### Future:

- [ ] 7-band EQ physical module
- [ ] Momentary gates _(to enable things like killswitches)_

## Hardware

- [TFT-LCD 3.5" 480x320 display, ILI9486 driver](https://www.amazon.nl/dp/B07Y6179LG)
- [4 Rotary encoders](https://www.amazon.nl/WayinTop-Roterende-Encoder-Module-Drukknop/dp/B07T3672VK)
- [Arduino Mega 2560 R3](https://store.arduino.cc/products/arduino-mega-2560-rev3)

## Building

This project comes with a `Makefile` that helps a lot with managing and building the firmware. 

### Setup 

**Important:** Make sure you have `clang-format` and `arduino-cli` installed in the host.

You probably will need to change the `PORT` in the `Makefile` to match the device in your host. 

You can use `make list_boards` to list the available connected ports.

Once that is all in place, you can use the commands:

```sh
# will build the firmware
make build

# will upload the firmware
make upload

# will do both by default
make
```

It also offers other utilities

```sh
# will format the whole code
make format

# will install all external dependencies
make install_libs

# will clean the build folder
make clean

# will connect and render serial messages (make sure to set the correct PORT and BAUD rate)
make serial

# disconnect from serial
make stop_serial

# flashes the hiduino firwmare onto atmega16u2
make flash_hiduino

# flashes the original firwmare onto atmega16u2
make flash_original
```

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

![Project](https://github.com/armand1m/0x66err_ctrl/blob/main/assets/uiproject.png)

#### Code Generation

The GUISliceBuilder features code generation and that can be used to get positions and all of that.

However, the code structure in the project is wrapped into my own "react-like" abstraction so I have an easier time updating and implementing new features. You'll probably have to convert some of that and make it match.

#### Fork

GUIslice is forked into this repo under the `libraries/GUIslice` because it demans a selected `GUIslice_config.h` to be enabled for a build. Since I made this for my own, I forked it into the repo and added my TFT config hardcoded. 

I might extract that into a different file for easy toggling, but not a priority.

It also has the following flags commented which are fairly handy for debugging issues:

```c
#define DEBUG_ERR     2   // 1,2 to enable, 0 to disable
#define DBG_LOG           // Enable debugging log output
#define DBG_TOUCH         // Enable debugging of touch-presses
#define DBG_FRAME_RATE    // Enable diagnostic frame rate reporting
#define DBG_DRAW_IMM      // Enable immediate rendering of drawing primitives
#define DBG_DRIVER        // Enable graphics driver debug reporting
```

As well as an enabled PROGMEM flag which enables rendering elements into flash memory instead of RAM, thus making the most out of such a small device as an arduino.

Unfortunately, rendering those elements demands me to use the macros GUIslice made available in a static matter, so the code might not be the easiest or the most readable, but it certainly is the most performatic and memory-saving one.

### Rotary Encoders

Rotary Encoders are powered by the `EncoderButton` library: https://github.com/Stutchbury/EncoderButton

EncoderButton offers an event-based API for using rotary encoders. It manages all the rotary states and it triggers given callbacks for specific events.
It already gives you support to attribute identifiers to every rotary encoder, which comes in handy.

The library is thin-wrapper built on top of the well-known Encoder library.
It adds button click support with clickCount by using the `Bounce2` library.

#### Fork

I did fork the `EncoderButton` library under `libraries/EncoderButton` in this repository.

The main reasoning was that the `EncoderButton::resetPosition` didn't reset the position in the actual encoder. My fork does that.
This was necessary as I'm reading MIDI messages from the DAW and syncing them with the device. 

### MIDI support

MIDI is powered by the <MIDI.h> standard library.

Most MIDI events are sent as Control Change events over channel 1.

MIDI events can be debugged during development using the Serial Monitor on 115200 baud.

#### MIDI CC Messages

| Device ID     | CC Value |
|---------------|----------|
| KNOB_CC_1     | 16       |
| KNOB_CC_2     | 17       |
| KNOB_CC_3     | 18       |
| KNOB_CC_4     | 19       |
| SLIDER_CC_1   | 20       |
| SLIDER_CC_2   | 21       |
| SLIDER_CC_3   | 22       |
| SLIDER_CC_4   | 23       |
| SLIDER_CC_5   | 24       |
| SLIDER_CC_6   | 25       |
| SLIDER_CC_7   | 26       |
| TOGGLE_CC_1   | 28       |
| TOGGLE_CC_2   | 29       |
| TOGGLE_CC_3   | 30       |
| TOGGLE_CC_4   | 31       |
| XY_MAP_CC_X   | 11       |
| XY_MAP_CC_Y   | 86       |

### MIDI over USB

Since Arduino Mega 2560 R3 doesn't support MIDI over USB out of the box, you need to flash HIDUINO in the board atmega16u2.

You can find the scripts and built firmware needed to switch between HIDUINO and the default USBSerial firmwares on this repo.

#### Flashing into atmega16u2

- Uncomment the `#define HIDUINO 1` in the main project file.
- Flash it into the Arduino Mega 2560 as you'd normally do.
- Short the RESET and GND pins close to the `atmega16u2` to get it into flash mode.
- Run `make flash_hiduino`
- Disconnect device and connect again.

If you need to make changes to the firmware, you will need to flash the original firmware back into the `atmega16u2`

- Short the RESET and GND pins close to the `atmega16u2` to get it into flash mode.
- Run `make flash_original`
