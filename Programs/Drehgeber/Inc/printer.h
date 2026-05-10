#ifndef PRINTER_H
#define PRINTER_H

#define PRINT_SIZE 15  // Displayed string size + '\0'
#define INIT_ANGLE "0.0           "
#define INIT_SPEED "0.00          "

void initDisplay(void);

int printAngle(char c, int offset);

int printSpeed(char c, int offset);

void resetDisplayValues(void);

#endif /* PRINTER_H */
// EOF
