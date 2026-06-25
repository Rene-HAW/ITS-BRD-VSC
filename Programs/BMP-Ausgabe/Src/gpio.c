#include "gpio.h"
#include "stm32f429xx.h"
#include "errorhandler.h"

#define MIN_GPIO_PIN 0
#define MAX_GPIO_PIN 15

int readGPIOpin(GPIO_TypeDef *GPIOx, int pin) {
    if ( (pin < MIN_GPIO_PIN) || (pin > MAX_GPIO_PIN) ) {
        return NOK;
    }
    return ( (0x01U << pin) != (GPIOx->IDR & (0x01U << pin)) );
}

void waitForButton(int button) {
    int sxHeld = 0;
    int sxPressed = 0;
    while( !sxPressed || sxHeld ) {
        sxHeld = readGPIOpin(INPUT, button);
        LOOP_ON_ERR(sxHeld == NOK, "readGPIOpin: Given pin out of range.");
        if( !sxPressed && sxHeld ) sxPressed = 1;
    }
}

// EOF
