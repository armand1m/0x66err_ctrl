#include <EncoderButton.h>

#define ENCODER_COUNT 4

typedef void (*EncoderButtonCallbackFunction)(EncoderButton &);

void debugClick(EncoderButton &encoder) {
  Serial.print("Encoder with Id ");
  Serial.print(encoder.userId());
  Serial.print(" clickCount is: ");
  Serial.println(encoder.clickCount());
}

void debugRotary(EncoderButton &encoder) {
  Serial.print("Encoder with Id ");
  Serial.print(encoder.userId());
  Serial.print(" incremented by ");
  Serial.println(encoder.increment());

  Serial.print("Encoder with Id ");
  Serial.print(encoder.userId());
  Serial.print(" position is: ");
  Serial.println(encoder.position());
}

void updateEncoders(EncoderButton encoders[]) {
  for (uint8_t index = 0; index < ENCODER_COUNT; index++) {
    encoders[index].update();
  }
}

void setupEncoders(EncoderButton encoders[],
                   EncoderButtonCallbackFunction onEncoderSpin,
                   EncoderButtonCallbackFunction onEncoderClick) {
  for (uint8_t index = 0; index < ENCODER_COUNT; index++) {
    encoders[index].setUserId(index);
    encoders[index].setClickHandler(onEncoderClick);
    encoders[index].setEncoderHandler(onEncoderSpin);
  }
}

EncoderButton encoders[ENCODER_COUNT] = {
    EncoderButton(44, 42, 46),
    EncoderButton(45, 43, 47),
    EncoderButton(50, 48, 52),
    EncoderButton(51, 49, 53),
};