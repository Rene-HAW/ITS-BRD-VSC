#include "lcd_print.h"
#include "LCD_GUI.h"
#include "lcd.h"
#include "main.h"

#define INIT_ANGLE "Winkel          :                Grad"
#define INIT_SPEED "Geschwindigkeit :                Grad/s"
#define INIT_VAL_A "0.0           "
#define INIT_VAL_S "0.00          "
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
    resetDisplayValues();
}

int printAngle(char c, int index) {
    if ( (index < 0) || (index >= PRINT_SIZE) ) {
        return INTERNAL_ERR;
    }
    lcdGotoXY( (X_VALUE + index), Y_ANGLE );
    lcdPrintC(c);
    return EOK;
}

int printSpeed(char c, int index) {
    if ( (index < 0) || (index >= PRINT_SIZE) ) {
        return INTERNAL_ERR;
    }
    lcdGotoXY( (X_VALUE + index), Y_SPEED );
    lcdPrintC(c);
    return EOK;
}

void resetDisplayValues(void) {
    lcdGotoXY(X_VALUE, Y_ANGLE);
    lcdPrintReplS(INIT_VAL_A);
    lcdGotoXY(X_VALUE, Y_SPEED);
    lcdPrintReplS(INIT_VAL_S);
}

// EOF
