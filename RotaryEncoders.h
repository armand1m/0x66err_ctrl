#include <EncoderButton.h>
#define ENCODER_COUNT 3

typedef void (*EncoderButtonCallbackFunction)(EncoderButton &);

void debugClick(EncoderButton& encoder) {
  Serial.print("Encoder with Id ");
  Serial.print(encoder.userId());
  Serial.print(" clickCount is: ");
  Serial.println(encoder.clickCount());
}

void debugRotary(EncoderButton& encoder) {
  Serial.print("Encoder with Id ");
  Serial.print(encoder.userId());
  Serial.print(" incremented by ");
  Serial.println(encoder.increment());

  Serial.print("Encoder with Id ");
  Serial.print(encoder.userId());
  Serial.print(" position is: ");
  Serial.println(encoder.position());
}

void onEncoderButtonClick(EncoderButton& encoder) {
  debugClick(encoder);
}

void updateEncoders(EncoderButton encoders[]) {
  for (uint8_t index = 0; index < ENCODER_COUNT; index++) {
    encoders[index].update();
  }
}

void setupEncoders(EncoderButton encoders[], EncoderButtonCallbackFunction onEncoderSpin) {
  for (uint8_t index = 0; index < ENCODER_COUNT; index++) {
    encoders[index].setUserId(index);
    encoders[index].setClickHandler(onEncoderButtonClick);
    encoders[index].setEncoderHandler(onEncoderSpin);
  }
}
