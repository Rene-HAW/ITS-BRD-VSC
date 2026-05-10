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
    return (frame / TICKS_PER_US) / 1000;  /* US zu MS */
}

void calcAngle(double steps, char out[]) {
    double angle = steps * (360.0 / STEPS_PER_CYCLE);
    sprintf(out, "%-*.1lf", (PRINT_SIZE - 1), angle);
}

void calcSpeed(double stepsOfFrame, double timeFrame, char out[]) {
    if (stepsOfFrame < 0) {
        stepsOfFrame = -stepsOfFrame;
    }
    double angleOfFrame = stepsOfFrame * (360.0 / STEPS_PER_CYCLE);
    double speed = (angleOfFrame / timeFrame) * 1000;  /* Grad/ms zu Grad/s */
    sprintf(out, "%-*.2lf", (PRINT_SIZE - 1), speed);
}


void updateBuffer(PrintBuffer *buffer, char newString[]) {
    char *oldString = buffer->string;
    int printCounter = 0;

    for (int i = 0; i < (PRINT_SIZE - 1); i++) {
        if (oldString[i] != newString[i]) {
            oldString[i] = newString[i];
            buffer->printIndex[printCounter] = i;
            printCounter++;
        }
    }
    buffer->printIndex[printCounter] = NO_PRINT;
    buffer->next = 0;
}

PrintBuffer newBuffer(char initString[]) {
    PrintBuffer buffer;
    for (int i = 0; i < PRINT_SIZE; i++) {
        buffer.string[i] = initString[i];
    }
    buffer.printIndex[0] = NO_PRINT;
    buffer.next = 0;
    return buffer;
}

// EOF
