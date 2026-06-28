#ifndef _DISPLAY_BITMAP_H
#define _DISPLAY_BITMAP_H

#include "MS_basetypes.h"
#include "BMP_types.h"

void initBMPdisplay(void);

int storePalette(DWORD biClrUsed);

int printCompressedImg(void);

int printUncompressedImg(BITMAPINFOHEADER *infoHeader);

#endif /* _DISPLAY_BITMAP_H */
// EOF
