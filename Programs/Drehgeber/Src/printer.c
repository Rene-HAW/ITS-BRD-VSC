#include "printer.h"
#include "LCD_GUI.h"
#include "general_def.h"
#include "lcd.h"

#define INIT_TEXT1  "Winkel          :                Grad"
#define INIT_TEXT2  "Geschwindigkeit :                Grad/s"
#define Y_ANGLE     2
#define Y_SPEED     4
#define X_TEXT      2
#define X_VALUE     (X_TEXT + 18)

void initDisplay(void) {
    GUI_init(DEFAULT_BRIGHTNESS);
    lcdGotoXY(X_TEXT, Y_ANGLE);
    lcdPrintS(INIT_TEXT1);
    lcdGotoXY(X_TEXT, Y_SPEED);
    lcdPrintS(INIT_TEXT2);
    resetDisplayValues();
}

int printAngle(char c, int offset) {
    if ( (offset < 0) || (offset >= PRINT_SIZE) ) {
        return INTERNAL_ERR;
    }
    lcdGotoXY( (X_VALUE + offset), Y_ANGLE );
    lcdPrintC(c);
    return EOK;
}

int printSpeed(char c, int offset) {
    if ( (offset < 0) || (offset >= PRINT_SIZE) ) {
        return INTERNAL_ERR;
    }
    lcdGotoXY( (X_VALUE + offset), Y_SPEED );
    lcdPrintC(c);
    return EOK;
}

void resetDisplayValues(void) {
    lcdGotoXY(X_VALUE, Y_ANGLE);
    lcdPrintReplS(INIT_ANGLE);
    lcdGotoXY(X_VALUE, Y_SPEED);
    lcdPrintReplS(INIT_SPEED);
}

// EOF
