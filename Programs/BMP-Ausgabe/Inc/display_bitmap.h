#ifndef _DISPLAY_BITMAP_H
#define _DISPLAY_BITMAP_H

#include "BMP_types.h"

void initBMPdisplay(void);

void storePalette(int size);

void printCompressedImg(BITMAPINFOHEADER *infoHeader);

void printUncompressedImg(BITMAPINFOHEADER *infoHeader);

#endif /* _DISPLAY_BITMAP_H */
// EOF
