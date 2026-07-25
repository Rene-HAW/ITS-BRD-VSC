#ifndef _GPIO_H
#define _GPIO_H

#include "stm32f429xx.h"
#include <stdbool.h>

#define PUSH_PULL  0
#define OPEN_DRAIN 1

/**
 *  @brief Read pin state of a given GPIO
 *  @param *GPIOx - Target GPIO
 *  @param pin    - Target Pin
 *  @retval NOK if invalid pin, EOK otherwise
 */
int readGPIOpin(GPIO_TypeDef *GPIOx, int pin);

/**
 *  @brief Set pin state of a given GPIO
 *  @param *GPIOx - Target GPIO
 *  @param pin    - Target Pin
 *  @param high   - true for high, false for low
 *  @retval NOK if invalid pin, EOK otherwise
 */
int setGPIOpin(GPIO_TypeDef *GPIOx, int pin, bool high);

/**
 *  @brief Set pin mode of a given GPIO
 *  @param *GPIOx - Target GPIO
 *  @param pin    - Target Pin
 *  @param mode   - Desired mode for pin
 *  @retval NOK if invalid pin, EOK otherwise
 */
int setGPIOpinMode(GPIO_TypeDef *GPIOx, int pin, int mode);

/**
 *  @brief  Waits for a whole button press (push + release),
 *          enters endless error loop if pin invalid
 *  @param  button - Pin of the expected button
 *  @retval None
 */
void waitForInput(int button);

#endif /* _GPIO_H */
// EOF
