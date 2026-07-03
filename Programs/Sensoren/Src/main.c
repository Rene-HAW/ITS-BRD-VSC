/**
  *****************************************************************************
  * @file    main.c
  * @author  Franz Korf
  * @brief   Kleines Testprogramm fuer neu erstelle Fonts.
  *****************************************************************************
*/

/* Includes -----------------------------------------------------------------*/
#include "main.h"
#include "init.h"
#include "timer.h"
#include "lcd_print.h"
#include "errorhandler.h"
#include "gpio.h"
#include "sensor.h"
#include "one_wire.h"

int main(void) {
	initITSboard();    // Initialisierung des ITS-Boards
	initDisplay();     // Initialisierung des LCD-Bildschirms
	initTimer();       // Initialisierung des Timers

	setGPIOpin(OUT, PD1, true);
	setGPIOpin(OUT, PD0, true);
	setGPIOpinMode(OUT, PD0, OPEN_DRAIN);

	Sensor onlyOne;
	int state = readROM(&onlyOne);
	if (state == EOK) printSensorInfo(&onlyOne);

	// Test in Endlosschleife
	while(1) {
		
	}
}

// EOF
