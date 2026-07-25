#ifndef GPIO_H
#define GPIO_H

#include "stm32f429xx.h"
#include <stdbool.h>
#include <stdint.h>

int readGPIOpin(GPIO_TypeDef *GPIOx, int pin);

int setGPIOpin(GPIO_TypeDef *GPIOx, int pin, bool high);

void setGPIOpinMask(GPIO_TypeDef *GPIOx, uint16_t mask);

void waitForInput(int button);

#endif /* GPIO_H */
