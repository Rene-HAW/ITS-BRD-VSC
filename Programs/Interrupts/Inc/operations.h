#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "lcd_print.h"
#include <stdint.h>

#define NO_PRINT -1
typedef struct {
    char string[PRINT_SIZE];
    int printIndex[PRINT_SIZE];
    int next;
} PrintBuffer;

PrintBuffer newBuffer(void);

double calcTimeFrame(uint32_t start, uint32_t end);

void calcAngle(char out[], int steps);

void calcSpeed(char out[], int steps, double timeFrame);

void updateBuffer(PrintBuffer *buffer, char newString[PRINT_SIZE]);

void setLEDcounter(int steps);

void setLEDstate(int move);

void resetLED(void);

#endif /* OPERATIONS_H */
// EOF
