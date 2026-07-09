#ifndef _LCD_PRINT_H
#define _LCD_PRINT_H

#include "sensor.h"

#define MAX_ENTRIES 16

void initDisplay(void);

void printSensorInfo(ThermalSensor *sensor, int entry);

void printTemperature(double temp, int entry);

void clearEntry(int entry);

void clearList(void);

void dummyprint(void);

#endif /* _LCD_PRINT_H */
// EOF
