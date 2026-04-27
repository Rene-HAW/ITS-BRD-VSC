#ifndef CODE_NUM_H
#define CODE_NUM_H

// Non-Errors:
#define EOK              0  // Everything OK, Funktion erfolgreich ausgeführt
#define STACK_EMPTY      1  // Peek auf leeren Stack

// Errors:
#define OVERFLOW_ERR    -1  // Stack Overflow Fehler
#define UNDERFLOW_ERR   -2  // Stack Underflow Fehler
#define ARITHMETIC_ERR  -3  // Arithmetic Overflow Fehler
#define DIVIDE_0_ERR    -4  // Geteilt durch 0 Fehler
#define INPUT_ERR       -5  // Undefinierter Input Fehler

#endif /* CODE_NUM_H */
//EOF
