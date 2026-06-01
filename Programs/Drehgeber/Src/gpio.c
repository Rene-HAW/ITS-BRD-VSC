#include "gpio.h"
#include "main.h"
#include <stdint.h>

#define MIN_GPIO_PIN 0
#define MAX_GPIO_PIN 15

int readGPIOpin(GPIO_TypeDef *GPIOx, int pin) {
    if ( (pin < MIN_GPIO_PIN) || (pin > MAX_GPIO_PIN) ) {
        return INTERNAL_ERR;
    }
    return ( (0x01U << pin) != (GPIOx->IDR & (0x01U << pin)) );
}

int setGPIOpin(GPIO_TypeDef *GPIOx, int pin, bool on) {
    if ( (pin < MIN_GPIO_PIN) || (pin > MAX_GPIO_PIN) ) {
        return INTERNAL_ERR;
    }
    int offset = (on) ? 0 : 16;

    GPIOx->BSRR = (0x01U << (pin + offset));
    return EOK;
}

static void setGPIOpinMask(GPIO_TypeDef *GPIOx, uint16_t mask) {
    GPIOx->BSRR = (uint32_t)(~mask << 16);
    GPIOx->BSRR = mask;
}

void setLEDstate(int move) {
    switch(move) {
        case FORWARD:
            setGPIOpin(OUT_STATE, D23, true);
            setGPIOpin(OUT_STATE, D22, false);
            setGPIOpin(OUT_STATE, D21, false);
            break;
        case BACKWARD:
            setGPIOpin(OUT_STATE, D23, false);
            setGPIOpin(OUT_STATE, D22, true);
            setGPIOpin(OUT_STATE, D21, false);
            break;
        case INTERNAL_ERR:
            setGPIOpin(OUT_STATE, D23, false);
            setGPIOpin(OUT_STATE, D22, false);
            setGPIOpin(OUT_STATE, D21, true);
    }
}

void setLEDcounter(int steps) {
    if (steps < 0) steps = -steps;
    uint16_t stepsDisplayed = (steps < UINT8_MAX) ? steps : UINT8_MAX;
    setGPIOpinMask(OUT_COUNT, stepsDisplayed);
}

void resetLED(void) {
    setGPIOpin(OUT_STATE, D23, false);
    setGPIOpin(OUT_STATE, D22, false);
    setGPIOpin(OUT_STATE, D21, false);
    setGPIOpinMask(OUT_COUNT, 0x00U);
}

// EOF
