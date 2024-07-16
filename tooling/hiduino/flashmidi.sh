dfu-programmer atmega16u2 erase;
dfu-programmer atmega16u2 erase --force; 
dfu-programmer atmega16u2 flash ./compiled_firmwares/arduino_midi.hex &&
dfu-programmer atmega16u2 reset
