#include "lcd_print.h"
#include "LCD_GUI.h"
#include "lcd.h"
#include "sensor.h"
#include <stdint.h>
#include <stdio.h>

#define HEADER "Sensor  PDROM              Temp. [C]"
#define SIZE_ROM_STRING (SIZE_ROM * 2 + 3)

#define X_FAM   1
#define X_ROM  (X_FAM + SIZE_FAM)
#define X_TEMP (X_ROM + SIZE_ROM_STRING)

#define Y_INIT  1
#define Y_LIST (Y_INIT + 2)

void initDisplay(void) {
    GUI_init(DEFAULT_BRIGHTNESS);
    lcdGotoXY(X_FAM, Y_INIT);
    lcdPrintS(HEADER);
}

void printSensorInfo(ThermalSensor *sensor, int entry) {
    char stringBuffer[SIZE_ROM_STRING];
    char *pointer = stringBuffer;
    
    pointer += sprintf(pointer, "0x");
    for (int i=0; i < SIZE_ROM; i++)
        pointer += sprintf(pointer, "%02X", sensor->rom[i]);

    uint8_t line = Y_LIST + entry;
    lcdGotoXY(X_FAM, line);
    lcdPrintS(sensor->family);
    lcdGotoXY(X_ROM, line);
    lcdPrintS(stringBuffer);
}

void printTemperature(double temp, int entry) {
    char stringBuffer[11];
    sprintf(stringBuffer, "%+9.4f", temp);

    uint8_t line = Y_LIST + entry;
    lcdGotoXY(X_TEMP, line);
    lcdPrintS(stringBuffer);
}

void clearEntry(int entry) {
    uint8_t line = Y_LIST + entry;
    lcdGotoXY(X_FAM, line);
    lcdPrintS(" ");
}

void clearList(void) {
    GUI_clear(LCD_BACKGROUND);
    lcdGotoXY(X_FAM, Y_INIT);
    lcdPrintS(HEADER);
}

// EOF
