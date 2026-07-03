#include "one_wire.h"
#include "errorhandler.h"
#include "timer_ex.h"
#include "gpio.h"
#include "sensor.h"
#include <stdbool.h>
#include <stdint.h>

static void write(uint16_t s1, uint16_t s2) {
    setGPIOpin(OUT, PD0, false);
    sleep(s1);
    setGPIOpin(OUT, PD0, true);
    sleep(s2);
}

static uint8_t read(uint16_t s1, uint16_t s2, uint16_t s3) {
    setGPIOpin(OUT, PD0, false);
    sleep(s1);
    setGPIOpin(OUT, PD0, true);
    sleep(s2);
    uint8_t bit = readGPIOpin(OUT, PD0);
    sleep(s3);
    return bit;
}

#define writeZero() write(60,10)
#define writeOne()  write(6,64)
#define readBit()    read(6,9,55)
#define reset()      read(480,70,410)

static void sendByte(uint8_t val) {
    for (uint8_t i=0; i < 8; i++) {
        if ( val & (0x01 << i) ) writeOne();
        else writeZero();
    }
}

static uint8_t readByte(void) {
    uint8_t byte = 0;
    for (uint8_t i=0; i < 8; i++)
        byte += (readBit() << i);
    return byte;
}

int readROM(Sensor *sensor) {
    RETURN_NOK_ON_ERR ( 0 != reset(),
        "resetError: No responses from any sensors." )
    sendByte(READ_ROM);
    for (uint8_t i=SIZE_ROM-1; i >= 0; i--)
        sensor->rom[i] = readByte();
    return EOK;
}
