/**
  *****************************************************************************
  * @file    main.c
  * @author  Franz Korf
  * @brief   Kleines Testprogramm fuer neu erstelle Fonts.
  *****************************************************************************
*/

/* Includes -----------------------------------------------------------------*/
#include "init.h"
#include "stm32f429xx.h"
#include "errorhandler.h"
#include "BMP_types.h"
#include "display_bitmap.h"
#include "input.h"

#define INPUT        GPIOF
#define S0           0
#define MIN_GPIO_PIN 0
#define MAX_GPIO_PIN 15

static int readGPIOpin(GPIO_TypeDef *GPIOx, int pin) {
    if ( (pin < MIN_GPIO_PIN) || (pin > MAX_GPIO_PIN) ) {
        return NOK;
    }
    return ( (0x01U << pin) != (GPIOx->IDR & (0x01U << pin)) );
}
 
int main(void) {
	initITSboard();    // Initialisierung des ITS Boards

	BITMAPFILEHEADER fileHeader;
	BITMAPINFOHEADER infoHeader;
	initBMPdisplay();    // Initialisierung der Bitmap-Verarbeitung

	// Beginn der Endlosschleife
	while(1) {
		int s0Pressed = 0;
		while(s0Pressed != 1) s0Pressed = readGPIOpin(INPUT, S0);
	}
}

// EOF
