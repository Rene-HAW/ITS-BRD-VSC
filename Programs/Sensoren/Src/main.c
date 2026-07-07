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

	ThermalSensor onlyOne;
	int state = snsReadSingleROM(&onlyOne);
	if (state == EOK) printSensorInfo(&onlyOne);

	// Test in Endlosschleife
	while(1) {
		
	}
}

// EOF
