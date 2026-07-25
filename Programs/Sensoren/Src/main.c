/**
  *****************************************************************************
  * @file    main.c
  * @author  Rene Rudzki
  * @brief   Programm zum Lesen und Anzeigen von gemessenen Temperaturen
  *****************************************************************************
*/

/* Includes -----------------------------------------------------------------*/
#include "init.h"
#include "one_wire.h"
#include "lcd_print.h"
#include "errorhandler.h"
#include "sensor.h"
#include "gpio.h"
#include <stdint.h>

#define RESET_BUTTON 0
#define TEMP_INDEX   8

int main(void) {
	initITSboard();    // Initialisierung des ITS-Boards
	initDisplay();     // Initialisierung des LCD-Bildschirms
	initOneWire();     // Initialisierung des 1-Wire Protokolls

	ThermalSensor sensors[MAX_ENTRIES];
	for (int i=0; i < MAX_ENTRIES; i++)
		sensors[i].state = EMPTY;
    uint8_t scratchpad[SIZE_PAD];
	int state = EOK;

	// Test in Endlosschleife
	while(1) {
		do {
            state = snsSearchROMs(sensors, MAX_ENTRIES);
            if (state == NOK) {
                waitForInput(RESET_BUTTON);
                clearList();
                for (int i=0; i < MAX_ENTRIES; i++)
                    sensors[i].state = EMPTY;
                state = REDO_SEARCH;
            }
        } while (state == REDO_SEARCH);

		for (int i=0; i < MAX_ENTRIES; i++) {
			if (sensors[i].state == ADDED) {
				printSensorInfo(&sensors[i], i);
				sensors[i].state = PRESENT;
			}
			if (sensors[i].state == REMOVED) {
				clearEntry(i);
				sensors[i].state = EMPTY;
			}
		}
        snsResetPulse();
        snsWriteByte(SKIP_ROM);
        snsWriteByte(CONVERT_T);
        busProvideVoltage(800);

        for (int i=0; i < MAX_ENTRIES; i++) if (sensors[i].state == PRESENT) {
            snsResetPulse();
            snsWriteByte(MATCH_ROM);
            for (int j=SIZE_ROM-1; j >= 0; j--)
                snsWriteByte(sensors[i].rom[j]);

            snsWriteByte(READ_SCRATCHPAD);
            for (int j=SIZE_PAD-1; j >= 0; j--)
                scratchpad[j] = snsReadByte();

            int16_t tempData = (scratchpad[TEMP_INDEX-1] << 8) + scratchpad[TEMP_INDEX];
            printTemperature(tempData * TEMP_FACTOR, i);
        }
	}
}

// EOF
