#include "display_bitmap.h"
#include "errorhandler.h"
#include "BMP_types.h"
#include "LCD_GUI.h"
#include "lcd.h"
#include "input.h"
#include "colors.h"

void initBMPdisplay(void) {
    GUI_init(DEFAULT_BRIGHTNESS);
    lcdPrintlnS("Waiting on Connect from programm...");
    initInput();
    lcdPrintlnS("");
    lcdPrintlnS("Connected! Use S0 to display your images.");
}
