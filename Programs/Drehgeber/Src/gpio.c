#include "gpio.h"
#include "general_def.h"
#include <stdint.h>

#define MIN_GPIO_PIN 0
#define MAX_GPIO_PIN 15

int readGPIOpin(GPIO_TypeDef *GPIOx, int pin) {
    if ( (pin < MIN_GPIO_PIN) || (pin > MAX_GPIO_PIN) ) {
        return INTERNAL_ERR;
    }
    return ( (0x01 << pin) != (GPIOx->IDR & (0x01 << pin)) );
}

int setGPIOpin(GPIO_TypeDef *GPIOx, int pin, bool on) {
    if ( (pin < MIN_GPIO_PIN) || (pin > MAX_GPIO_PIN) ) {
        return INTERNAL_ERR;
    }
    int offset = (on) ? 0 : 16;

    GPIOx->BSRR = (0x01 << (pin + offset));
    return EOK;
}

static void setGPIOpinMask(GPIO_TypeDef *GPIOx, uint16_t mask) {
    GPIOx->BSRR = (~mask << 16);
    GPIOx->BSRR = mask;
}

void setLEDstate(int state) {
    switch(state) {
        case FORWARD:
            setGPIOpin(OUTPUT_STATE, D23, true);
            setGPIOpin(OUTPUT_STATE, D22, false);
            setGPIOpin(OUTPUT_STATE, D21, false);
            break;
        case BACKWARD:
            setGPIOpin(OUTPUT_STATE, D23, false);
            setGPIOpin(OUTPUT_STATE, D22, true);
            setGPIOpin(OUTPUT_STATE, D21, false);
            break;
        case INTERNAL_ERR:
            setGPIOpin(OUTPUT_STATE, D23, false);
            setGPIOpin(OUTPUT_STATE, D22, false);
            setGPIOpin(OUTPUT_STATE, D21, true);
            break;
    }
}

void setLEDcounter(int steps) {
    if (steps < 0) {
        steps = -steps;
    }
    uint16_t stepsDisplayed = (steps < UINT8_MAX) ? steps : UINT8_MAX;
    setGPIOpinMask(OUTPUT_COUNT, stepsDisplayed);
}

void resetLED(void) {
    setGPIOpin(OUTPUT_STATE, D23, false);
    setGPIOpin(OUTPUT_STATE, D22, false);
    setGPIOpin(OUTPUT_STATE, D21, false);
    setGPIOpinMask(OUTPUT_COUNT, 0x00);
}

// EOF
