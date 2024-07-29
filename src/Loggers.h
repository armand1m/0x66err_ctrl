#ifndef LOGGERS_H
#define LOGGERS_H

static void infolog(const String& message)
{
#ifndef HIDUINO
    if (message.equals("\n")) {
        Serial.println("");
    } else {
        Serial.print(message);
    }
#endif
}

#endif // LOGGERS_H