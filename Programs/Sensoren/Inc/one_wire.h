#ifndef _ONE_WIRE_H
#define _ONE_WIRE_H

#include <stdint.h>

/**
 *  @brief Initialize components for the 1-wire bus protocol
 *  @param None
 *  @retval None
 */
void initOneWire(void);

/**
 *  @brief Send a pulse for writing to slaves on the bus, all timings in us
 *  @param s1 - How long to pull the bus low
 *  @param s2 - After s1, wait how long before exiting function
 *  @retval None
 */
void busWrite(int s1, int s2);

/**
 *  @brief Send a pulse for reading from slaves on the bus, all timings in us
 *  @param s1 - How long to pull the bus low
 *  @param s2 - After s1, wait how long before reading from bus
 *  @param s3 - After s2, wait how long before exiting function
 *  @retval State read from the bus (0 or 1)
 */
uint8_t busRead(int s1, int s2, int s3);

/**
 *  @brief Sets the bus into push-pull mode to provide slaves with extra voltage
 *  @param ms - How long to provide voltage in milliseconds
 *  @retval None
 */
void busProvideVoltage(int ms);

#endif /* _ONE_WIRE_H */
// EOF
