#ifndef _GPIO_H
#define _GPIO_H

#include "stm32f429xx.h"
#include <stdbool.h>

#define OUT GPIOD
#define PD0 0
#define PD1 1

#define PUSH_PULL  0
#define OPEN_DRAIN 1

int readGPIOpin(GPIO_TypeDef *GPIOx, int pin);

int setGPIOpin(GPIO_TypeDef *GPIOx, int pin, bool high);

int setGPIOpinMode(GPIO_TypeDef *GPIOx, int pin, int mode);

#endif /* _GPIO_H */
// EOF
