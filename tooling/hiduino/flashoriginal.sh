dfu-programmer atmega16u2 erase;
dfu-programmer atmega16u2 erase --force; 
dfu-programmer atmega16u2 flash --suppress-bootloader-mem ./compiled_firmwares/usbserial_mega_16u2.hex &&
dfu-programmer atmega16u2 reset
