#include <EEPROM.h>

void clearEEPROM() {
  for (int i = 0; i < EEPROM.length(); i++) {
    EEPROM.write(i, 0xFF); // Write 0xFF to each byte
  }
}

void setup() {
  Serial.begin(9600);
  Serial.println("Clearing EEPROM...");
  clearEEPROM();
  Serial.println("EEPROM cleared.");
}

void loop() {
  // Do nothing here
}
