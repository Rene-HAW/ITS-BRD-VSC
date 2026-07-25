#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

// Definieren von Zuständen
#define FORWARD     2
#define BACKWARD    1
#define STANDSTILL  0
#define UNKNOWN    -1

int encodeInput(int in1State, int in0State, int *move, int *steps);

void resetMachine(void);

#endif /* STATE_MACHINE_H */
// EOF
