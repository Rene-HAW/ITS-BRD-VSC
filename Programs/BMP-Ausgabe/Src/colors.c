#include "colors.h"
#include "errorhandler.h"
#include "BMP_types.h"
#include "LCD_general.h"
#include <stdint.h>
#include <math.h>

static RGBTRIPLE palette[MAX_COLOR_TABLE_SIZE];

int setPaletteColor(int i, RGBQUAD rgbq) {
    if ( (i < 0) || (MAX_COLOR_TABLE_SIZE <= i) ) return NOK;

    palette[i].rgbtRed   = rgbq.rgbRed;
    palette[i].rgbtGreen = rgbq.rgbGreen;
    palette[i].rgbtBlue  = rgbq.rgbBlue;
    return EOK;
}

int getPaletteColor(int i, RGBTRIPLE *rgbOut) {
    if ( (i < 0) || (MAX_COLOR_TABLE_SIZE <= i) ) return NOK;

    *rgbOut = palette[i];
    return EOK;
}

#define SIZE_R 0x1F
#define SIZE_G 0x3F
#define SIZE_B 0x1F

#define OFFSET_R 11
#define OFFSET_G 5

COLOR getLCDcolor(RGBTRIPLE rgb) {
    double rgbMax = UINT8_MAX;
    COLOR red   = round( SIZE_R * (rgb.rgbtRed   / rgbMax) );
    COLOR green = round( SIZE_G * (rgb.rgbtGreen / rgbMax) );
    COLOR blue  = round( SIZE_B * (rgb.rgbtBlue  / rgbMax) );
    return ( (red << OFFSET_R) + (green << OFFSET_G) + blue );
}

// EOF
