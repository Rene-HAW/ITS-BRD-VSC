#ifndef _GPIO_H
#define _GPIO_H

#include "stm32f429xx.h"
#define  INPUT  GPIOF
#define  S0     0

int readGPIOpin(GPIO_TypeDef *GPIOx, int pin);

void waitForButton(int button);

#endif /* _GPIO_H */
// EOF
