#ifndef GPIO_H
#define GPIO_H

#include "stm32f429xx.h"
#include <stdbool.h>

int readGPIOpin(GPIO_TypeDef *GPIOx, int pin);

int setGPIOpin(GPIO_TypeDef *GPIOx, int pin, bool on);

void setLEDstate(int move);

void setLEDcounter(int steps);

void resetLED(void);

#endif /* GPIO_H */
