#ifndef ROTARY_ENCODERS_H
#define ROTARY_ENCODERS_H

#include <EncoderButton.h>
#define ENCODER_COUNT 4

EncoderButton encoders[ENCODER_COUNT] = {
    EncoderButton(44, 42, 46),
    EncoderButton(45, 43, 47),
    EncoderButton(50, 48, 52),
    EncoderButton(51, 49, 53),
};

typedef void (*EncoderButtonCallbackFunction)(EncoderButton&);

void update_encoders(EncoderButton encoders[])
{
    for (uint8_t index = 0; index < ENCODER_COUNT; index++) {
        encoders[index].update();
    }
}

void setup_encoders(EncoderButton encoders[],
    EncoderButtonCallbackFunction on_encoder_spin,
    EncoderButtonCallbackFunction on_encoder_click)
{
    for (uint8_t index = 0; index < ENCODER_COUNT; index++) {
        encoders[index].setUserId(index);
        encoders[index].setClickHandler(on_encoder_click);
        encoders[index].setEncoderHandler(on_encoder_spin);
    }
}

void limit_encoder_positions(EncoderButton& encoder)
{
    if (encoder.position() <= 0) {
        encoder.resetPosition(0);
    }

    if (encoder.position() >= 127) {
        encoder.resetPosition(127);
    }
}

#endif // ROTARY_ENCODERS_H