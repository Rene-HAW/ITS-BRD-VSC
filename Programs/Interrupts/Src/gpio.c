#include "gpio.h"
#include "errorhandler.h"
#include "stm32f429xx.h"
#include <stdbool.h>
#include <stdint.h>

#define MIN_GPIO_PIN 0
#define MAX_GPIO_PIN 15
#define MASK(pin) (0x01U << (pin))

int readGPIOpin(GPIO_TypeDef *GPIOx, int pin) {
    if ( (pin < MIN_GPIO_PIN) || (pin > MAX_GPIO_PIN) ) {
        return NOK;
    }
    return ( MASK(pin) == (GPIOx->IDR & MASK(pin)) );
}

int setGPIOpin(GPIO_TypeDef *GPIOx, int pin, bool high) {
    if ( (pin < MIN_GPIO_PIN) || (pin > MAX_GPIO_PIN) ) {
        return NOK;
    }
    int offset = (high) ? 0 : 16;
    GPIOx->BSRR = MASK(pin+offset);
    return EOK;
}

void setGPIOpinMask(GPIO_TypeDef *GPIOx, uint16_t mask) {
    GPIOx->BSRR = (uint32_t)(~mask << 16);
    GPIOx->BSRR = mask;
}

void waitForInput(int button) {
    LOOP_ON_ERR( NOK == readGPIOpin(GPIOF, button),
        "readGPIOpin: Given pin out of range." );
    int sxHeld = 0;
    int sxPressed = 0;
    while( !sxPressed || sxHeld ) {
        sxHeld = !readGPIOpin(GPIOF, button);
        if( !sxPressed && sxHeld ) sxPressed = 1;
    }
}

// EOF
