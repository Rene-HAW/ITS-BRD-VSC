#include "display_bitmap.h"
#include "errorhandler.h"
#include "MS_basetypes.h"
#include "BMP_types.h"
#include "LCD_general.h"
#include "LCD_GUI.h"
#include "lcd.h"
#include "input.h"
#include "colors.h"
#include <stdbool.h>
#include <stdint.h>

void initBMPdisplay(void) {
  GUI_init(DEFAULT_BRIGHTNESS);
  lcdPrintlnS("Waiting on Connect from programm...");
  initInput();
  lcdPrintlnS("");
  lcdPrintlnS("Connected! Use S0 to display your images.");
}

int storePalette(DWORD biClrUsed) {
  int size = ( (0 < biClrUsed) && (biClrUsed < MAX_COLOR_TABLE_SIZE) ) ?
              (int)biClrUsed : MAX_COLOR_TABLE_SIZE;
  RGBQUAD color;
  
  for (int i=0; i < size; i++) {
    RETURN_NOK_ON_ERR (
      1 != COMread((char*) &color, sizeof(RGBQUAD), 1),
      "readPalette: Error during read." )
    setPaletteColor(i, color);
  }
  return EOK;
}

static COLOR getPaletteLCDcolor(int i) {
  RGBTRIPLE rgbColor;
  getPaletteColor(i, &rgbColor);
  return getLCDcolor(rgbColor);
}

static void printDelta (POINT setX, POINT lines, Coordinate *coord, COLOR *colors) {
  if (setX > LCD_WIDTH) setX = LCD_WIDTH;
  if (lines > coord->y) lines = coord->y;
  
  if (lines == 0) {
    for (POINT i=coord->x; i < setX; i++) {colors[i] = LCD_BACKGROUND;}
  } else {
    for (POINT i=coord->x; i < LCD_WIDTH; i++) {colors[i] = LCD_BACKGROUND;}
    coord->y--;
    GUI_WriteLine((Coordinate){0,coord->y}, LCD_WIDTH, colors);
    
    POINT limit = ( (lines == 1) && (setX < coord->x) ) ? setX : coord->x;

    for (POINT i=0; i < limit; i++) {colors[i] = LCD_BACKGROUND;}
    for (POINT i=1; i < lines; i++) {
      coord->y--;
      GUI_WriteLine((Coordinate){0,coord->y}, LCD_WIDTH, colors);
    }
  }
  coord->x = setX;
}

int printCompressedImg(void) {
  Coordinate coord = {0, LCD_HEIGHT};
  COLOR lineColors[LCD_WIDTH];
  while (coord.y > 0) {
    uint8_t i = 0;
    int firstByte = nextChar();
    int secondByte = nextChar();
    RETURN_NOK_ON_ERR (
      (firstByte == NOK) || (secondByte == NOK),
      "readImage: Error during read." )
    
    if (firstByte > 0) {    // Count-Index Pair
      COLOR lcdColor = getPaletteLCDcolor(secondByte);
      while ( (coord.x < LCD_WIDTH) && (i < firstByte) ) {
        lineColors[coord.x] = lcdColor;
        coord.x++; i++;
      }
    } else {
      if (secondByte > 2) {    // Absolute Mode
        uint16_t size = ((secondByte % 2) == 1) ? secondByte+1 : secondByte;
        uint8_t indexBytes[size];
        COMread((char*) indexBytes, size, 1);
        while ( (coord.x < LCD_WIDTH) && (i < secondByte) ) {
          lineColors[coord.x] = getPaletteLCDcolor(indexBytes[i]);
          coord.x++; i++;
        }
      } else {    // Encoded Mode
        uint8_t offsetX, offsetY;
        switch (secondByte) {
          case 2:    // Delta
            offsetX = nextChar();
            offsetY = nextChar();
            printDelta((coord.x + offsetX), offsetY, &coord, lineColors);
            break;
          case 1:    // End of bitmap
            printDelta(0, coord.y, &coord, lineColors);
            break;
          case 0:    // End of line
            printDelta(0, 1, &coord, lineColors);
        }
      }
    }
  }
  return EOK;
}

int printUncompressedImg(BITMAPINFOHEADER *infoHeader) {
  
  return EOK;
}
