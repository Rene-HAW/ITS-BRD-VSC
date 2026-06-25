/**
  *****************************************************************************
  * @file    main.c
  * @author  Franz Korf
  * @brief   Kleines Testprogramm fuer neu erstelle Fonts.
  *****************************************************************************
*/

/* Includes -----------------------------------------------------------------*/
#include "init.h"
#include "errorhandler.h"
#include "BMP_types.h"
#include "display_bitmap.h"
#include "input.h"
#include "gpio.h"

#include "lcd.h"

int main(void) {
	initITSboard();    // Initialisierung des ITS Boards

	BITMAPFILEHEADER fileHeader;
	BITMAPINFOHEADER infoHeader;
	initBMPdisplay();    // Initialisierung der Bitmap-Verarbeitung

	// Beginn der Endlosschleife
	while(1) {
		waitForButton(S0);
        char* txt = (0x1F < 255) ? "true" : "false";
        lcdPrintlnS(txt);
	}
}

// EOF
