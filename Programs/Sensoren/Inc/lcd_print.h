#ifndef _LCD_PRINT_H
#define _LCD_PRINT_H

#include "sensor.h"

#define MAX_ENTRIES 16

void initDisplay(void);

void clearList(void);

void clearEntry(int entry);

void printSensorInfo(ThermalSensor *sensor, int entry);

void printTemperature(char *temp, int entry);

void dummyprint(void);

#endif /* _LCD_PRINT_H */
// EOF
