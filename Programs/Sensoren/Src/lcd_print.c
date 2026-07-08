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

void clearList(void) {
    lcdGotoXY(X_FAM, Y_LIST);
    for (int i=0; i < MAX_ENTRIES; i++)
        lcdPrintlnS(" ");
}

void clearEntry(int entry) {
    uint8_t line = Y_LIST + entry;
    lcdGotoXY(X_FAM, line);
    lcdPrintS(" ");
}

void printSensorInfo(ThermalSensor *sensor, int entry) {
    char stringBuf[SIZE_ROM_STRING];
    char *pointer = stringBuf;
    
    pointer += sprintf(pointer, "0x");
    for (int i=0; i < SIZE_ROM; i++)
        pointer += sprintf(pointer, "%02X", sensor->rom[i]);

    uint8_t line = Y_LIST + entry;
    lcdGotoXY(X_FAM, line);
    lcdPrintS(sensor->family);
    lcdGotoXY(X_ROM, line);
    lcdPrintS(stringBuf);
}

void printTemperature(char *temp, int entry) {
    uint8_t line = Y_LIST + entry;
    lcdGotoXY(X_TEMP, line);
    lcdPrintS(temp);
}


#define DUMMY "DS18S20 0x0102030405060708 20.500000"

void dummyprint(void) {
    ThermalSensor test = {
        {1,14,52,168,255,45,78,95},
        "TestTes", PRESENT
    };
    printSensorInfo(&test, 0);
    printTemperature("24.lol", 0);

    lcdGotoXY(X_FAM, Y_LIST+2);
    for (int i=2; i < MAX_ENTRIES; i++)
        lcdPrintlnS(DUMMY);
}

// EOF
