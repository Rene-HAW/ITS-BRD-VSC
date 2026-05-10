#ifndef GENERAL_DEF_H
#define GENERAL_DEF_H

// Definieren von GPIO Makros
#define INPUT         GPIOF
#define IN0           0
#define IN1           1
#define S6            6

#define OUTPUT_STATE  GPIOE
#define D21           5
#define D22           6
#define D23           7
#define OUT10         2
#define OUT11         3

#define OUTPUT_COUNT  GPIOD

// Definieren von Zuständen
#define FORWARD       3
#define STANDSTILL    2
#define BACKWARD      1

#define EOK           0
#define INTERNAL_ERR -1

#endif /* GENERAL_DEF_H */
// EOF
