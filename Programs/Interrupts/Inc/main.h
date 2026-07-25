#ifndef MAIN_H
#define MAIN_H

// Definieren von GPIO Makros
#define INPUT     GPIOF
#define IN0       0
#define IN1       1
#define S6        6

#define OUT_COUNT GPIOD

#define OUT_STATE GPIOE
#define MASK_FORW (0x01U << 7)
#define MASK_BACK (0x01U << 6)
#define MASK_NOK  (0x01U << 5)

#define OUT10     2
#define OUT11     3

#endif /* MAIN_H */
// EOF
