#ifndef _LCD_PRINT_H
#define _LCD_PRINT_H

#include "sensor.h"

#define MAX_ENTRIES 16

void initDisplay(void);

void resetDisplay(void);

void printSensorInfo(Sensor *sensor);

void printTemperature(Sensor *sensor);

void dummyprint(void);

#endif /* _LCD_PRINT_H */
// EOF
