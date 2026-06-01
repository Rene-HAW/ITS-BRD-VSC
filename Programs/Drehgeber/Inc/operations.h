#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <stdint.h>

double calcTimeFrame(uint32_t start, uint32_t end);

void calcAngle(char out[], int steps);

void calcSpeed(char out[], int steps, double timeFrame);

#endif /* OPERATIONS_H */
// EOF
