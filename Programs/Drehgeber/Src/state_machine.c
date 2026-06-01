#include "state_machine.h"
#include "main.h"

static char currentPhase = 's';

static int fsm(char newPhase) {
    switch (currentPhase) {
        case 'a':
            switch (newPhase) {
                case 'a':
                    return STANDSTILL;
                case 'b':
                    currentPhase = newPhase;
                    return FORWARD;
                case 'd':
                    currentPhase = newPhase;
                    return BACKWARD;
                default:
                    currentPhase = 'e';
                    return INTERNAL_ERR;
            }

        case 'b':
            switch (newPhase) {
                case 'a':
                    currentPhase = newPhase;
                    return BACKWARD;
                case 'b':
                    return STANDSTILL;
                case 'c':
                    currentPhase = newPhase;
                    return FORWARD;
                default:
                    currentPhase = 'e';
                    return INTERNAL_ERR;
            }

        case 'c':
            switch (newPhase) {
                case 'b':
                    currentPhase = newPhase;
                    return BACKWARD;
                case 'c':
                    return STANDSTILL;
                case 'd':
                    currentPhase = newPhase;
                    return FORWARD;
                default:
                    currentPhase = 'e';
                    return INTERNAL_ERR;
            }

        case 'd':
            switch (newPhase) {
                case 'a':
                    currentPhase = newPhase;
                    return FORWARD;
                case 'c':
                    currentPhase = newPhase;
                    return BACKWARD;
                case 'd':
                    return STANDSTILL;
                default:
                    currentPhase = 'e';
                    return INTERNAL_ERR;
            }

        case 's':
            switch (newPhase) {
                case 'a': case 'b': case 'c': case 'd':
                    currentPhase = newPhase;
                    return STANDSTILL;
                default:
                    currentPhase = 'e';
                    return INTERNAL_ERR;
            }
        
        default:
            currentPhase = 'e';
            return INTERNAL_ERR;
    }
}

int encodeInput(int in1State, int in0State, int *move, int *steps) {
    char phase;
    if (in1State) {
        phase = (in0State) ? 'c' : 'b';
    } else /* !in1State */ {
        phase = (in0State) ? 'd' : 'a';
    }
    switch ( fsm(phase) ) {
        case FORWARD:
            *move = FORWARD;
            *steps += 1;
            return EOK;
        case BACKWARD:
            *move = BACKWARD;
            *steps -= 1;
            return EOK;
        case STANDSTILL:
            *move = STANDSTILL;
            return EOK;
    }
    return INTERNAL_ERR;
}

void resetMachine(void) {
    currentPhase = 's';
}

// EOF
