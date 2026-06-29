#ifndef _DISPLAY_BITMAP_H
#define _DISPLAY_BITMAP_H

#include "MS_basetypes.h"
#include "BMP_types.h"

/**
 *  @brief  Initialisere LCD Bildschirm und baue eine Verbindung
            zur Python GUI auf
 *  @param  None
 *  @retval None
 */
void initBMPdisplay(void);

/**
 *  @brief  Speicher die Palette der derzeitigen Datei
 *  @param  biClrUsed  Anzahl der Farbindezes nach Angabe des Info Headers
 *  @retval NOK wenn Fehler beim Lesen der Datei
 */
int storePalette(DWORD biClrUsed);

/**
 *  @brief  Gebe eine komprimierte BL_RLE8 Bitmap Datei auf dem LCD Bildschirm aus
 *  @param  None
 *  @retval NOK wenn Fehler beim Lesen der Datei
 */
int printCompressedImg(void);

/**
 *  @brief  Gebe eine unkomprimierte BL_RGB Bitmap Datei auf dem LCD Bildschirm aus
 *  @param  *info  Der Info Header der zugehörigen Bitmap Datei
 *  @retval NOK wenn Fehler beim Lesen der Datei
 */
int printUncompressedImg(BITMAPINFOHEADER *info);

#endif /* _DISPLAY_BITMAP_H */
// EOF
