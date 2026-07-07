#include "one_wire.h"
#include "gpio.h"
#include "timer.h"
#include "timer_ex.h"
#include <stdbool.h>
#include <stdint.h>

#define OUT GPIOD
#define PD0 0
#define PD1 1

void initOneWire(void) {
    setGPIOpinMode(OUT, PD0, OPEN_DRAIN);
	setGPIOpin(OUT, PD0, true);
    setGPIOpin(OUT, PD1, true);
    initTimer();
}

void busWrite(int s1, int s2) {
    setGPIOpin(OUT, PD0, false);
    sleep(s1);
    setGPIOpin(OUT, PD0, true);
    sleep(s2);
}

uint8_t busRead(int s1, int s2, int s3) {
    setGPIOpin(OUT, PD0, false);
    sleep(s1);
    setGPIOpin(OUT, PD0, true);
    sleep(s2);
    uint8_t bit = readGPIOpin(OUT, PD0);
    sleep(s3);
    return bit;
}

void busProvideVoltage(int ms) {
    setGPIOpinMode(OUT, PD0, PUSH_PULL);
    sleep(ms * 1000);
    setGPIOpinMode(OUT, PD0, OPEN_DRAIN);
}

// EOF
