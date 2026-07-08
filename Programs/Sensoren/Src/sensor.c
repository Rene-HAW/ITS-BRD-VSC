#include "sensor.h"
#include "one_wire.h"
#include "errorhandler.h"
#include <stdint.h>
#include <string.h>

#define writeZero() busWrite(60,10)
#define writeOne()  busWrite(4,66)
#define readBit()   busRead(4,6,60)

uint8_t snsResetPulse(void) { return busRead(480,70,410); }

void snsWriteByte(uint8_t val) {
    for (uint8_t i=0; i < 8; i++) {
        if ( (val >> i) & 0x01 ) writeOne();
        else writeZero();
    }
}

uint8_t snsReadByte(void) {
    uint8_t byte = 0;
    for (uint8_t i=0; i < 8; i++)
        byte += (readBit() << i);
    return byte;
}


#define CRC_STEPS  56
#define CRC_INDEX  0
#define FAMC_INDEX 7

typedef struct {
    uint8_t depth;
    uint8_t lastZero;
    uint8_t lastDiscrepancy;
} SearchVariables;

static uint8_t resolveSearch(SearchVariables *search, uint8_t romBuffer[SIZE_ROM]) { 
    uint8_t bit = readBit();
    uint8_t bitComp = readBit();
    uint8_t direction;

    if ( (bit == bitComp) && (bit == 1) ) {
        search->depth = UINT8_MAX;
        direction = UINT8_MAX;
    }
    else {
        uint8_t bufIndex  = SIZE_ROM - (search->depth / 8) - 1;
        uint8_t bufOffset = search->depth % 8;
        search->depth++;

        if (bit != bitComp) {
            direction = bit;
        } else {
            if (search->depth < search->lastDiscrepancy)
                direction = (romBuffer[bufIndex] >> bufOffset) & 0x01;
            else
                direction = (search->depth == search->lastDiscrepancy);
        
            if (direction == 0) search->lastZero = search->depth;
        }
        if (direction == 0) {
            romBuffer[bufIndex] &= ~(0x01 << bufOffset);
            writeZero();
        } else {
            romBuffer[bufIndex] |= (0x01 << bufOffset);
            writeOne();
        }
    }
    return direction;
}

static void calcCRC(uint8_t *crc, uint8_t input) {
    uint8_t lsBit = *crc & 0x01;
    *crc >>= 1;
    if (lsBit != input) *crc ^= 0b10001100;
}

int snsSearchROMs(ThermalSensor sensors[], int arraySize) {
    int emptySlot = 0;
    for (int i=0; i < arraySize; i++)
        if (sensors[i].state == PRESENT) {
            sensors[i].state = CHECKUP;
            if (emptySlot == i) emptySlot++;
        }
    SearchVariables search = {0,0,0};
    uint8_t romBuffer[SIZE_ROM];
    uint8_t state = EOK;
    
    do {
        RETURN_NOK_ON_ERR ( 0 != snsResetPulse(),
            "resetError: No responses from any sensors." )
        
        snsWriteByte(SEARCH_ROM);
        uint8_t crcVal = 0;
        while (search.depth < SIZE_ROM*8) {
            uint8_t bit = resolveSearch(&search, romBuffer);
            if (search.depth <= CRC_STEPS) calcCRC(&crcVal, bit);
        }
        if ( (search.depth == UINT8_MAX) || (crcVal != romBuffer[CRC_INDEX]) ) {
            search.lastDiscrepancy = 0;
            state = REDO_SEARCH;
        } else {
            int compare = 1;
            for (int i=0; i < arraySize; i++)
                if (sensors[i].state == CHECKUP) {
                    compare = memcmp(sensors[i].rom, romBuffer, SIZE_ROM);
                    if (compare == 0) { 
                        sensors[i].state = PRESENT;
                        i = arraySize;
                    }
                }
            if ( (compare != 0) && (emptySlot < arraySize) ) {
                sensors[emptySlot].state = ADDED;
                memcpy(sensors[emptySlot].rom, romBuffer, SIZE_ROM);
                switch (romBuffer[FAMC_INDEX]) {
                    case 0x28: strcpy(sensors[emptySlot].family, "DS18B20"); break;
                    case 0x10: strcpy(sensors[emptySlot].family, "DS18S20");
                }
                while ( (emptySlot < arraySize) && (sensors[emptySlot].state != EMPTY) )
                    emptySlot++;
            }
            search.lastDiscrepancy = search.lastZero;
            search.lastZero = 0;
            search.depth = 0;
        }
    } while (search.lastDiscrepancy > 0);
    
    for (int i=0; i < arraySize; i++) {
        if (state == REDO_SEARCH) {
            if (sensors[i].state == ADDED) sensors[i].state = EMPTY;
            if (sensors[i].state == CHECKUP) sensors[i].state = PRESENT;
        } else /* state == EOK */ {
            if (sensors[i].state == CHECKUP) sensors[i].state = REMOVED;
        }
    }
    return state;
}


int snsReadROM(ThermalSensor *sensor) {
    RETURN_NOK_ON_ERR ( 0 != snsResetPulse(),
        "resetError: No responses from any sensors." )
    
    snsWriteByte(READ_ROM);
    uint8_t crcVal = 0;

    for (int i=SIZE_ROM-1; i > CRC_INDEX; i--) {
        sensor->rom[i] = 0;
        for (uint8_t offset=0; offset < 8; offset++) {
            uint8_t bit = readBit();
            sensor->rom[i] += (bit << offset);
            calcCRC(&crcVal, bit);
        }
    }
    sensor->rom[CRC_INDEX] = snsReadByte();
    RETURN_NOK_ON_ERR ( crcVal != sensor->rom[CRC_INDEX],
        "crcError: CRC validation failed." )

    switch (sensor->rom[FAMC_INDEX]) {
        case 0x28: strcpy(sensor->family, "DS18B20"); break;
        case 0x10: strcpy(sensor->family, "DS18S20");
    }
    return EOK;
}

// EOF
