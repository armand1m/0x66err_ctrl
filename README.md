# MIDI Amp Project

This project is a MIDI controller featuring 8 rotary encoders and 1 TFT LCD 3.5" 320x480 screen.

Hardware:
- TFT-LCD 3.5" 480x320 display, ILI9486 driver: https://www.amazon.nl/dp/B07Y6179LG?ref=ppx_yo2ov_dt_b_product_details&th=1
- Rotary encoders
- Arduino Mega 2560

Libraries:
 - GUISlice: https://github.com/ImpulseAdventure/GUIslice
   - GUISlice offers not only touch-compatible components out of the box,
     but it also provides LCD and touchscreen setup and configuration examples.
     It is super well documented and works perfectly with the hardware chosen here.

 - EncoderButton: https://github.com/Stutchbury/EncoderButton
   - EncoderButton offers an event-based API for using rotary encoders.
     The library is thin-wrapper built on top of the well-known Encoder library.
     It adds button click support with clickCount by using the Bounce2 library.
    
> NOTE: This is the simple version of the example without optimizing for memory consumption.