#ifndef _COLORS_H
#define _COLORS_H

#include "BMP_types.h"
#include <stdint.h>

int setPaletteColor(int i, RGBQUAD color);

int getPaletteColor(int i, RGBTRIPLE *color);

uint16_t getLCDcolor(RGBTRIPLE color);

#endif /* _COLORS_H */
// EOF
