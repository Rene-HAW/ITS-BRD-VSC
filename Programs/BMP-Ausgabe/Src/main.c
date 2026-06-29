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
#include "lcd.h"
#include "gpio.h"
#include "input.h"
#include <stdint.h>

static BITMAPFILEHEADER fileHeader;
static BITMAPINFOHEADER infoHeader;

static int basicChecks(void) {
	RETURN_NOK_ON_ERR (
		fileHeader.bfType != BMP_SIGNATURE,
		"checkHeaders: Incorrect file signature." )
	
	RETURN_NOK_ON_ERR (
		(infoHeader.biBitCount != 8) && (infoHeader.biBitCount != 24),
		"checkHeaders: Unsupported bit count." )
	
	RETURN_NOK_ON_ERR (
		(infoHeader.biCompression != BI_RGB) && (infoHeader.biCompression != BI_RLE8),
		"checkHeaders: Unsupported compression." )
	
	if (infoHeader.biCompression == BI_RGB) {
		RETURN_NOK_ON_ERR (
			(unsigned)infoHeader.biWidth > ((UINT32_MAX - 31) / infoHeader.biBitCount),
			"checkHeaders: Width too large." )
	}
	return EOK;
}

int main(void) {
	initITSboard();    // Initialisierung des ITS Boards
	initBMPdisplay();    // Initialisierung der Bitmap-Verarbeitung
    lcdPrintlnS("Use S0 to display your images.");

	// Beginn der Endlosschleife
	while(1) {
		waitForButton(S0);
		lcdPrintS("Opening file...");
		lcdGotoXY(1, 1);
        openNextFile();

		int state = ERR_HANDLER (
			1 != COMread((char*) &fileHeader, sizeof(BITMAPFILEHEADER), 1),
			"readHeaders: Error during read." );

		state = (state == NOK) ? NOK : ERR_HANDLER (
			1 != COMread((char*) &infoHeader, sizeof(BITMAPINFOHEADER), 1),
			"readHeaders: Error during read." );
		
		state = (state == NOK) ? NOK : basicChecks();

		if ( (state == EOK) && (infoHeader.biBitCount == 8) )
			state = storePalette(infoHeader.biClrUsed);
		
		if (state == EOK) {
			if (infoHeader.biCompression == BI_RLE8) printCompressedImg();
			else /* biCompression == BI_RGB */ printUncompressedImg(&infoHeader);
		}
	}
}

// EOF
