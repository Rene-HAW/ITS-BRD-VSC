/**
  *****************************************************************************
  * @file    main.c
  * @author  René Rudzki
  * @brief   Ermittlung von Winkel und Geschwindigkeit anhand eines Drehgebers
  *****************************************************************************
  */
/* Includes ---------------------------------------------------------------- */

#include "init.h"
#include "main.h"
#include "gpio.h"
#include "state_machine.h"
#include "operations.h"
#include "lcd_print.h"
#include "timer.h"
#include <stdbool.h>
#include <stdint.h>

#define MIN_TIME 250  // ms
#define MAX_TIME 500  // ms

void errorHandler(void) {
  setLEDstate(INTERNAL_ERR);
  int s6Pressed = 0;
  while(s6Pressed != 1) s6Pressed = readGPIOpin(INPUT, S6);

  resetLED();
  resetMachine();
  resetDisplayValues();
}


int main(void) {
  // Initialisierung ITS Board und interne Variabeln
  initITSboard();
  int state = EOK;
  int move = STANDSTILL;
  int steps = 0;

  // Initialisierung LCD mit Text und Ausgabe-Buffern
  initDisplay();
  PrintBuffer bufAngle = newBuffer();
  PrintBuffer bufSpeed = newBuffer();

  // Initialisierung Timer und Zeitfenster direkt vor super-loop öffnen
  initTimer();
	uint32_t frameStart = getTimeStamp();


  // Beginn der super-loop
	while(1) {
    // Eingabe - Einlesen der Sensoren
    //setGPIOpin(OUT_STATE, OUT10, true);  // Zeitmessung: super-loop (start)

    int in0State = readGPIOpin(INPUT, IN0);
    int in1State = readGPIOpin(INPUT, IN1);

    // ------------------------------------------------------------------------
    // Update des Zustands
    if ( (in1State == INTERNAL_ERR) || (in0State == INTERNAL_ERR) )
      state = INTERNAL_ERR;
    else state = encodeInput(in1State, in0State, &move, &steps);

    // ------------------------------------------------------------------------
    // Berechnung der neuen Werte fuer die Aktoren
    uint32_t frameEnd = getTimeStamp();
    double timeFrame = calcTimeFrame(frameStart, frameEnd);

    if (timeFrame >= MIN_TIME) {
      if ( (move > STANDSTILL) || (timeFrame >= MAX_TIME) ) {
        char bufString[PRINT_SIZE];

        calcAngle(bufString, steps);
        updateBuffer(&bufAngle, bufString);

        calcSpeed(bufString, steps, timeFrame);
        updateBuffer(&bufSpeed, bufString);

        frameStart = frameEnd;
      }
    }
    // ------------------------------------------------------------------------
    // Ausgabe - Treiben der Aktoren
    setLEDstate(move);
    setLEDcounter(steps);

    //setGPIOpin(OUT_STATE, OUT11, true);  // Zeitmessung: LCD-Ausgabe (start)

    int index = bufAngle.printIndex[bufAngle.next];
    if (index != NO_PRINT) {
      state = printAngle(bufAngle.string[index], index);
      bufAngle.next++;
    }

    index = bufSpeed.printIndex[bufSpeed.next];
    if (index != NO_PRINT) {
      state = printSpeed(bufSpeed.string[index], index);
      bufSpeed.next++;
    }

    //setGPIOpin(OUT_STATE, OUT11, false);  // Zeitmessung: LCD-Ausgabe (ende)
    //setGPIOpin(OUT_STATE, OUT10, false);  // Zeitmessung: super-loop (ende)

    // ------------------------------------------------------------------------
    // Error Handling
    if (state < EOK) {
      errorHandler();
      state = EOK;
      move = STANDSTILL;
      steps = 0;
      bufAngle = newBuffer();
      bufSpeed = newBuffer();
      frameStart = getTimeStamp();
    }
	}
}

// EOF
