#include "colors.h"
#include "errorhandler.h"
#include "BMP_types.h"

static RGBTRIPLE palette[MAX_COLOR_TABLE_SIZE];

int setPaletteColor(int i, RGBQUAD color) {
    if ( (i < 0) || (MAX_COLOR_TABLE_SIZE <= i) ) return NOK;

    palette[i].rgbtRed   = color.rgbRed;
    palette[i].rgbtGreen = color.rgbGreen;
    palette[i].rgbtBlue  = color.rgbBlue;
    return EOK;
}

int getPaletteColor(int i, RGBTRIPLE *color) {
    if ( (i < 0) || (MAX_COLOR_TABLE_SIZE <= i) ) return NOK;

    *color = palette[i];
    return EOK;
}
