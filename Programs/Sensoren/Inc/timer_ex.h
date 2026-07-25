#ifndef _TIMER_EX_H
#define _TIMER_EX_H

#include <stdint.h>

/**
 *  @brief Get the amount of micro seconds between two time stamps
 *  @param start - Opening stamp of the time frame
 *  @param end   - Closing stamp of the time frame
 *  @retval Micro seconds with double precision
 */
double getTimeFrame(uint32_t start, uint32_t end);

/**
 *  @brief Pause the running process for a specific amount of time
 *  @param us - Time to wait in micro seconds
 *  @retval None
 */
void sleep(double us);

#endif /* _TIMER_EX_H */
// EOF
