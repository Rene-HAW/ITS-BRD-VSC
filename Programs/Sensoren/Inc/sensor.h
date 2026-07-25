#ifndef _SENSOR_H
#define _SENSOR_H

#include <stdint.h>

#define REDO_SEARCH 1
#define TEMP_FACTOR 0.0625

// ROM Commands
#define SEARCH_ROM   0xF0
#define READ_ROM     0x33
#define MATCH_ROM    0x55
#define SKIP_ROM     0xCC
#define ALARM_SEARCH 0xEC

// DS18B/S20 Function Commands
#define CONVERT_T         0x44
#define WRITE_SCRATCHPAD  0x4E
#define READ_SCRATCHPAD   0xBE
#define COPY_SCRATCHPAD   0x48
#define RECALL_E2         0xB8
#define READ_POWER_SUPPLY 0xB4

// Store Structure
#define SIZE_PAD 9
#define SIZE_ROM 8
#define SIZE_FAM 8

#define PRESENT 'P'    // Valid sensor data
#define EMPTY   'E'    // Invalid sensor data
#define ADDED   'A'    // New Sensor found after last ROM search
#define REMOVED 'R'    // Known Sensor not found after last ROM search

typedef struct {
    uint8_t rom[SIZE_ROM];
    char family[SIZE_FAM];
    char state;
} ThermalSensor;

/**
 *  @brief Sends a reset pulse and checks for a presence pulse from any slave
 *  @param None
 *  @retval 0 if no slaves present, 1 otherwise
 */
uint8_t snsResetPulse(void);

/**
 *  @brief Writes a whole byte of data to the 1-wire bus
 *  @param val  The (command) byte to write
 *  @retval None
 */
void snsWriteByte(uint8_t val);

/**
 *  @brief Reads and returns a whole byte of data from the 1-wire bus
 *  @param None
 *  @retval The received byte
 */
uint8_t snsReadByte(void);

/**
 *  @brief Reads and stores ROMs into an array for all present sensors
 *  @param sensors[] - Array of store structures
 *  @param arraySize - Count of elements in sensors[]
 *  @retval NOK if no slaves present, REDO_SEARCH if search cancelled, EOK otherwise
 */
int snsSearchROMs(ThermalSensor sensors[], int arraySize);

/**
 *  @brief Reads and stores ROM for a single sensor,
 *         don't use with more than one on the bus!
 *  @param *sensor - Pointer to a store structure
 *  @retval NOK on error, EOK otherwise
 */
int snsReadROM(ThermalSensor *sensor);

#endif /* _SENSOR_H */
// EOF
