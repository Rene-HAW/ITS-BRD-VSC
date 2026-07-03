#include "gpio.h"
#include "stm32f429xx.h"
#include "errorhandler.h"
#include <stdbool.h>

#define MIN_GPIO_PIN 0
#define MAX_GPIO_PIN 15

int readGPIOpin(GPIO_TypeDef *GPIOx, int pin) {
    if ( (pin < MIN_GPIO_PIN) || (pin > MAX_GPIO_PIN) ) {
        return NOK;
    }
    return ( (0x01U << pin) != (GPIOx->IDR & (0x01U << pin)) );
}

int setGPIOpin(GPIO_TypeDef *GPIOx, int pin, bool high) {
    if ( (pin < MIN_GPIO_PIN) || (pin > MAX_GPIO_PIN) ) {
        return NOK;
    }
    int offset = (high) ? 0 : 16;
    GPIOx->BSRR = (0x01U << (pin + offset));
    return EOK;
}

int setGPIOpinMode(GPIO_TypeDef *GPIOx, int pin, int mode) {
    if ( (pin < MIN_GPIO_PIN) || (pin > MAX_GPIO_PIN) ) {
        return NOK;
    }
    switch (mode) {
        case PUSH_PULL: GPIOx->OTYPER &= ~(0x01U << pin); break;
        case OPEN_DRAIN: GPIOx->OTYPER |= (0x01U << pin);
    }
    return EOK;
}

// EOF
