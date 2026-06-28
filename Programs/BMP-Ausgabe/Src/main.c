/**
  *****************************************************************************
  * @file    main.c
  * @author  Franz Korf
  * @brief   Kleines Testprogramm fuer neu erstelle Fonts.
  *****************************************************************************
*/

/* Includes -----------------------------------------------------------------*/
#include "LCD_general.h"
#include "colors.h"
#include "init.h"
#include "errorhandler.h"
#include "BMP_types.h"
#include "display_bitmap.h"
#include "input.h"
#include "gpio.h"

#include "lcd.h"
#include "LCD_GUI.h"
#include "LCD_general.h"
#include <stdbool.h>

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

		RGBTRIPLE color = {191, 0, 188};
		Coordinate a = {0, LCD_HEIGHT-101};
		Coordinate b = {150, LCD_HEIGHT-1};
		GUI_drawRectangle(a, b, getLCDcolor(color), true, DOT_PIXEL_1X1);
	}
}

// EOF
