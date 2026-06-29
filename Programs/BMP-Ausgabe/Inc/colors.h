#ifndef _COLORS_H
#define _COLORS_H

#include "BMP_types.h"
#include "LCD_general.h"

/**
 *  @brief  Setze einen Farbwert an Index i der Palette
 *  @param  i     Farbindex
 *  @param  rgbq  Farbe als RGBQUAD
 *  @retval NOK wenn i außerhalb der Palette
 */
int setPaletteColor(int i, RGBQUAD rgbq);

/**
 *  @brief  Erhalte den Farbwert an Index i der Palette
 *  @param  i         Farbindex
 *  @param  *rgbqOut  Schreibbuffer für die Farbe als RGBTRIPLE
 *  @retval NOK wenn i außerhalb der Palette
 */
int getPaletteColor(int i, RGBTRIPLE *rgbOut);

/**
 *  @brief  Konvertiere ein RGBTRIPLE in einen COLOR Wert
            zur Ausgabe auf dem LCD Bildschirm
    @param  rgb  Farbe als RGBTRIPLE
    @retval LCD Farbe
 */
COLOR getLCDcolor(RGBTRIPLE rgb);

#endif /* _COLORS_H */
// EOF
