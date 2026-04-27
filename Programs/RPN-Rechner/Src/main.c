/**
  ******************************************************************************
  * @file    main.c
  * @author  René Rudzki
  * @brief   Implementierung eines RPN Taschenrechners
  *			 über Touch-Display des ITS-Boards.
  ******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "init.h"
#include "operations.h"
#include "output.h"
#include "scanner.h"
#include "token.h"
#include "code_num.h"

int main(void) {
	initITSboard();    // Initialisierung des ITS-Boards	
	initOutput();      // Initialisierung des Displays

	int state = EOK;
	T_token input;
	
	// Ausführung in Endlosschleife
	while(1) {
		input = nextToken();

		switch (input.tok) {
			case NUMBER:
				state = rpn_enterNumber(input.val); break;
			
			case OVERFLOW:
				state = OVERFLOW_ERR; break;
			
			case PLUS: case MINUS: case MULT: case DIV: case SWAP:
				state = rpn_binaryOperations(input.tok); break;
			
			case DOUBLE:
				state = rpn_duplicate(); break;

			case PRT: case PRT_ALL:
				rpn_printOperations(input.tok); break;

			case CLEAR:
				clearOutput();
				rpn_clearMemory(); break;

			case UNEXPECTED:
				state = INPUT_ERR;
		}

		if (state < EOK) {
			printError(state);
			rpn_clearMemory();
		}
	}
}

// EOF
