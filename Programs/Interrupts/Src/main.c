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
#include "timer.h"
#include "state_machine.h"
#include "operations.h"
#include "lcd_print.h"
#include "errorhandler.h"
#include <stdint.h>

#define MIN_TIME 250  // ms
#define MAX_TIME 500  // ms

int main(void) {
  // Initialisierung ITS Board und interne Variabeln
  initITSboard();
  int move = STANDSTILL;
  int steps = 0;
  int state;

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
    int in0State = readGPIOpin(INPUT, IN0);
    int in1State = readGPIOpin(INPUT, IN1);

    // ------------------------------------------------------------------------
    // Update des Zustands
    state = encodeInput(in1State, in0State, &move, &steps);

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
    if (state == EOK) {
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
      setLEDcounter(steps);
    }
    setLEDstate(move);
    
    // ------------------------------------------------------------------------
    // Error Handling
    if (state == NOK) {
      waitForInput(S6);

      resetLED();
      resetMachine();
      resetDisplayValues();

      move = STANDSTILL;
      steps = 0;
      bufAngle = newBuffer();
      bufSpeed = newBuffer();
      frameStart = getTimeStamp();
    }
	}
}

// EOF
