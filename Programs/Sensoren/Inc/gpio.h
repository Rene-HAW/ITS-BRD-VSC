#ifndef _GPIO_H
#define _GPIO_H

#include "stm32f429xx.h"
#include <stdbool.h>

#define PUSH_PULL  0
#define OPEN_DRAIN 1

int readGPIOpin(GPIO_TypeDef *GPIOx, int pin);

int setGPIOpin(GPIO_TypeDef *GPIOx, int pin, bool high);

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
