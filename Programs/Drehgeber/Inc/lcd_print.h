#ifndef PRINTER_H
#define PRINTER_H

#define PRINT_SIZE 15  // Displayed string size + '\0'

void initDisplay(void);

int printAngle(char c, int index);

int printSpeed(char c, int index);

void resetDisplayValues(void);

#endif /* PRINTER_H */
// EOF
