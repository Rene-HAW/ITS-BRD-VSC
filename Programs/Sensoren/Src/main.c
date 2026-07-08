/**
  *****************************************************************************
  * @file    main.c
  * @author  Franz Korf
  * @brief   Kleines Testprogramm fuer neu erstelle Fonts.
  *****************************************************************************
*/

/* Includes -----------------------------------------------------------------*/
#include "init.h"
#include "one_wire.h"
#include "lcd_print.h"
#include "errorhandler.h"
#include "sensor.h"

int main(void) {
	initITSboard();    // Initialisierung des ITS-Boards
	initDisplay();     // Initialisierung des LCD-Bildschirms
	initOneWire();     // Initialisierung des 1-Wire Protokolls

	ThermalSensor sensors[MAX_ENTRIES];
	for (int i=0; i < MAX_ENTRIES; i++)
		sensors[i].state = EMPTY;
	int state = EOK;

	// Test in Endlosschleife
	while(1) {
		do state = snsSearchROMs(sensors, MAX_ENTRIES);
		while (state == REDO_SEARCH);

		while (state == NOK) ;

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
	}
}

// EOF
