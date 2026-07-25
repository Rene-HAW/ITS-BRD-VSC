#ifndef MAIN_H
#define MAIN_H

// Definieren von GPIO Makros
#define INPUT     GPIOF
#define IN0       0
#define IN1       1
#define S6        6

#define OUT_STATE GPIOE
#define D21       5
#define D22       6
#define D23       7
#define OUT10     2
#define OUT11     3

#define OUT_COUNT GPIOD

// Definieren von Zuständen
#define FORWARD       3
#define BACKWARD      2
#define STANDSTILL    1

#define EOK           0
#define INTERNAL_ERR -1

#endif /* MAIN_H */
// EOF
