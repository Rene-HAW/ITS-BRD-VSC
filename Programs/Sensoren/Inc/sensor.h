#ifndef _SENSOR_H
#define _SENSOR_H

#include <stdint.h>

#define READ_ROM 0x33

#define SIZE_ROM  8
#define SIZE_FAM  8
#define SIZE_TEMP 10

typedef struct {
    uint8_t rom[SIZE_ROM];
    char family[SIZE_FAM];
    char temperature[SIZE_TEMP];
    uint8_t index;
} Sensor;

#endif /* _SENSOR_H */
// EOF
