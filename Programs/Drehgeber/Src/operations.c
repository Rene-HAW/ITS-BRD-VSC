#include "operations.h"
#include "timer.h"
#include <stdio.h>

#define STEPS_PER_CYCLE 1200  // Phasenwechsel pro 360° Umdrehung

double calcTimeFrame(uint32_t start, uint32_t end) {
    double frame;
    if (start > end) {  /* Register Overflow */
        frame = UINT32_MAX - start + end;
    } else {
        frame = end - start;
    }
    return (frame / TICKS_PER_US) / 1000;  /* us zu ms */
}

void calcAngle(char out[], int steps) {
    double angle = steps * (360.0 / STEPS_PER_CYCLE);
    sprintf(out, "%-*.1lf", (PRINT_SIZE-1), angle);
}

void calcSpeed(char out[], int steps, double timeFrame) {
    static double lastAngle = 0.0;
    double newAngle = steps * (360.0 / STEPS_PER_CYCLE);
    double angleOfFrame = newAngle - lastAngle;
    lastAngle = newAngle;
    if (angleOfFrame < 0) angleOfFrame = -angleOfFrame;

    double speed = (angleOfFrame / timeFrame) * 1000;  /* Grad/ms zu Grad/s */
    sprintf(out, "%-*.2lf", (PRINT_SIZE-1), speed);
}

void updateBuffer(PrintBuffer *buffer, char newString[PRINT_SIZE]) {
    int printCounter = 0;
    for (int i = 0; i < (PRINT_SIZE-1); i++) {
        if (buffer->string[i] != newString[i]) {
            buffer->string[i] = newString[i];
            buffer->printIndex[printCounter] = i;
            printCounter++;
        }
    }
    buffer->printIndex[printCounter] = NO_PRINT;
    buffer->next = 0;
}

PrintBuffer newBuffer(void) {
    PrintBuffer buffer;
    buffer.printIndex[0] = NO_PRINT;
    buffer.next = 0;
    return buffer;
}

// EOF
