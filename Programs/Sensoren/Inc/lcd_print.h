#ifndef _LCD_PRINT_H
#define _LCD_PRINT_H

#include "sensor.h"

#define MAX_ENTRIES 16

/**
 *  @brief Initialize LCD and print one-time strings
 *  @param None
 *  @retval None
 */
void initDisplay(void);

/**
 *  @brief Print family name and ROM number of a given sensor
 *  @param *sensor - Pointer to the sensor's store structure
 *  @param entry   - Position in the list on the LCD
 *  @retval None
 */
void printSensorInfo(ThermalSensor *sensor, int entry);

/**
 *  @brief Print given temperature of a sensor
 *  @param temp  - value of temperature
 *  @param entry - Position in the list on the LCD
 *  @retval None
 */
void printTemperature(double temp, int entry);

/**
 *  @brief Clear a given line from the sensors list
 *  @param entry - Position in the list on the LCD
 *  @retval None
 */
void clearEntry(int entry);

/**
 *  @brief Reset the whole screen to its init state
 *  @param None
 *  @retval None
 */
void clearList(void);

#endif /* _LCD_PRINT_H */
// EOF
