#ifndef CLAMP_H
#define CLAMP_H

int16_t clamp(int16_t value, int16_t min, int16_t max)
{
    if (value < min) {
        return min;
    }

    if (value > max) {
        return max;
    }

    return value;
}

#endif // CLAMP_H