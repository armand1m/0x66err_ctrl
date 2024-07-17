static int16_t DebugOut(char ch) {
#ifdef HIDUINO
  // noop
#else
  if (ch == (char)'\n')
    Serial.println("");
  else
    Serial.write(ch);
#endif

  return 0;
}

static void log(const String &message) {
#ifdef HIDUINO
  // noop
#else
  if (message.equals("\n")) {
    Serial.println("");
  } else {
    Serial.print(message);
  }
#endif
}

static void logControlChange(int controlNumber, int controlValue, int channel) {
  log("Control Change: ");
  log(String(controlNumber));
  log(", ");
  log(String(controlValue));
  log(", ");
  log(String(channel));
  log("\n");
}
