#ifndef MEM_H
#define MEM_H
#include "../Loggers.h"

// Function to calculate free memory
int availableMemory()
{
    int size = 8192;
    byte* buf;

    while ((buf = (byte*)malloc(--size)) == NULL)
        ;

    free(buf);

    return size;
}

void log_free_memory()
{
#ifndef HIDUINO
    infolog("Free memory:");
    Serial.println(availableMemory());
#endif
}

#endif // MEM_H