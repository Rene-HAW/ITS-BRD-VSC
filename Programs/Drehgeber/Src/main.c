/**
  ******************************************************************************
  * @file    main.c
  * @author  René Rudzki
  * @brief   Ermittlung von Winkel und Geschwindigkeit anhand eines Drehgebers
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/

#include "init.h"
#include "general_def.h"
#include "gpio.h"
#include "state_machine.h"
#include "operations.h"
#include "printer.h"
#include "timer.h"
#include <stdbool.h>
#include <stdint.h>

#define MIN_TIME 250  // ms
#define MAX_TIME 500  // ms

bool errorHandler(void) {
  setLEDstate(INTERNAL_ERR);
  int s6Pressed = 0;

  while(s6Pressed != 1) {
    s6Pressed = readGPIOpin(INPUT, S6);
  }

  resetLED();
  resetMachine();
  resetDisplayValues();
  return false;
}


int main(void) {
  // Initialisierung ITS Board und interne Variabeln
  initITSboard();
  bool error = false;
  int state = EOK;
  int steps = 0;
  int stepsOfFrame = 0;

  // Initialisierung LCD mit Text und Ausgabe-Buffern
  initDisplay();
  PrintBuffer bufAngle = newBuffer(INIT_ANGLE);
  PrintBuffer bufSpeed = newBuffer(INIT_SPEED);

  // Initialisierung Timer und Zeitfenster direkt vor super-loop öffnen
  initTimer();
	uint32_t frameStart = getTimeStamp();
	

  // Beginn der super-loop
	while(1) {
    //setGPIOpin(OUTPUT_STATE, OUT10, true);  // Zeitmessung: super-loop (start)

		// Eingabe - Einlesen der Sensoren
    int in0State = readGPIOpin(INPUT, IN0);
    int in1State = readGPIOpin(INPUT, IN1);
    uint32_t frameEnd = getTimeStamp();


    // Update des Zustands
    state = encodeState(in1State, in0State);
    error = (state == INTERNAL_ERR) || (in0State == INTERNAL_ERR) || (in1State == INTERNAL_ERR);
    
    switch(state) {
      case FORWARD:
        steps++;
        stepsOfFrame++;
        break;
      case BACKWARD:
        steps--;
        stepsOfFrame--;
        break;
    }


    // Berechnung der neuen Werte fuer die Aktoren
    double timeFrame = calcTimeFrame(frameStart, frameEnd);

    if (timeFrame >= MIN_TIME) {
      if ( (state == FORWARD) || (state == BACKWARD) || (timeFrame >= MAX_TIME) ) {
        
        char bufOutput[PRINT_SIZE];

        calcAngle(steps, bufOutput);
        updateBuffer(&bufAngle, bufOutput);

        calcSpeed(stepsOfFrame, timeFrame, bufOutput);
        updateBuffer(&bufSpeed, bufOutput);

        stepsOfFrame = 0;
        frameStart = frameEnd;
      }
    }


    // Ausgabe - Treiben der Aktoren
    setLEDstate(state);
    setLEDcounter(steps);
    
    //setGPIOpin(OUTPUT_STATE, OUT11, true);  // Zeitmessung: LCD Ausgabe (start)

    int index = bufAngle.printIndex[bufAngle.next];
    if (index != NO_PRINT) {
      
      state = printAngle(bufAngle.string[index], index);
      error = error || (state == INTERNAL_ERR);
      bufAngle.next++;
    }

    index = bufSpeed.printIndex[bufSpeed.next];
    if (index != NO_PRINT) {
      
      state = printSpeed(bufSpeed.string[index], index);
      error = error || (state == INTERNAL_ERR);
      bufSpeed.next++;
    }

    //setGPIOpin(OUTPUT_STATE, OUT11, false);  // Zeitmessung: LCD Ausgabe (ende)
    //setGPIOpin(OUTPUT_STATE, OUT10, false);  // Zeitmessung: super-loop (ende)


    // Error Handling
    if (error) {
      error = errorHandler();
      state = EOK;
      steps = 0;
      stepsOfFrame = 0;
      bufAngle = newBuffer(INIT_ANGLE);
      bufSpeed = newBuffer(INIT_SPEED);
      frameStart = getTimeStamp();
    }
	}
}

// EOF
