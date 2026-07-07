#include "sensor.h"
#include "one_wire.h"
#include "errorhandler.h"
#include <stdint.h>
#include <string.h>

#define writeOne()  busWrite(4,66)
#define writeZero() busWrite(60,10)
#define readBit()   busRead(4,6,60)

uint8_t snsResetPulse(void) { return busRead(480,70,410); }

void snsWriteByte(uint8_t val) {
    for (uint8_t i=0; i < 8; i++) {
        if ( val & (0x01U << i) ) writeOne();
        else writeZero();
    }
}

uint8_t snsReadByte(void) {
    uint8_t byte = 0;
    for (uint8_t i=0; i < 8; i++)
        byte += (readBit() << i);
    return byte;
}


#define CRC_INDEX  0
#define FAMC_INDEX 7

static void snsCalcCRC(uint8_t *crc, uint8_t input) {
    uint8_t lsBit = *crc & 0x01;
    *crc >>= 1;
    if (lsBit != input) *crc ^= 0b10001100;
}

int snsReadSingleROM(ThermalSensor *sensor) {
    RETURN_NOK_ON_ERR ( 0 != snsResetPulse(),
        "resetError: No responses from any sensors." )
    
    snsWriteByte(READ_ROM);
    uint8_t crcVal = 0;

    for (int i=SIZE_ROM-1; i > CRC_INDEX; i--) {
        sensor->rom[i] = 0;
        for (uint8_t offset=0; offset < 8; offset++) {
            uint8_t bit = readBit();
            sensor->rom[i] += (bit << offset);
            snsCalcCRC(&crcVal, bit);
        }
    }
    sensor->rom[CRC_INDEX] = snsReadByte();
    RETURN_NOK_ON_ERR ( crcVal != sensor->rom[CRC_INDEX],
        "crcError: CRC validation failed." )

    switch (sensor->rom[FAMC_INDEX]) {
        case 0x28: strcpy(sensor->family, "DS18B20"); break;
        case 0x10: strcpy(sensor->family, "DS18S20");
    }
    sensor->index = 0;
    return EOK;
}

// EOF
