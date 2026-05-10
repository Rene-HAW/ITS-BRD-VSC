#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "printer.h"
#include <stdint.h>

#define NO_PRINT -1

typedef struct {
    char string[PRINT_SIZE];
    int printIndex[PRINT_SIZE];
    int next;
} PrintBuffer;

double calcTimeFrame(uint32_t start, uint32_t end);

void calcAngle(double steps, char out[]);

void calcSpeed(double stepsOfFrame, double timeFrame, char out[]);

void updateBuffer(PrintBuffer *buffer, char newString[]);

PrintBuffer newBuffer(char initString[]);

#endif /* OPERATIONS_H */
// EOF
