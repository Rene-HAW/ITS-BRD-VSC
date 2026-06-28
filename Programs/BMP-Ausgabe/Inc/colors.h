#ifndef _COLORS_H
#define _COLORS_H

#include "BMP_types.h"
#include "LCD_general.h"

int setPaletteColor(int i, RGBQUAD rgbq);

int getPaletteColor(int i, RGBTRIPLE *rgbOut);

COLOR getLCDcolor(RGBTRIPLE rgb);

#endif /* _COLORS_H */
// EOF
