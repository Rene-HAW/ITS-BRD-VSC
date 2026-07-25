#include "lcd_print.h"
#include "LCD_GUI.h"
#include "lcd.h"
#include "errorhandler.h"

#define INIT_ANGLE "Winkel          : 0.0            Grad"
#define INIT_SPEED "Geschwindigkeit : 0.00           Grad/s"
#define Y_ANGLE    2
#define Y_SPEED    4
#define X_TEXT     2
#define X_VALUE    20

void initDisplay(void) {
    GUI_init(DEFAULT_BRIGHTNESS);
    lcdGotoXY(X_TEXT, Y_ANGLE);
    lcdPrintS(INIT_ANGLE);
    lcdGotoXY(X_TEXT, Y_SPEED);
    lcdPrintS(INIT_SPEED);
}

int printAngle(char c, int index) {
    if ( (index < 0) || (index >= PRINT_SIZE) ) {
        return NOK;
    }
    lcdGotoXY( (X_VALUE + index), Y_ANGLE );
    lcdPrintC(c);
    return EOK;
}

int printSpeed(char c, int index) {
    if ( (index < 0) || (index >= PRINT_SIZE) ) {
        return NOK;
    }
    lcdGotoXY( (X_VALUE + index), Y_SPEED );
    lcdPrintC(c);
    return EOK;
}

void resetDisplayValues(void) {
    GUI_clear(LCD_BACKGROUND);
    lcdGotoXY(X_TEXT, Y_ANGLE);
    lcdPrintS(INIT_ANGLE);
    lcdGotoXY(X_TEXT, Y_SPEED);
    lcdPrintS(INIT_SPEED);
}

// EOF
