#include "state_machine.h"
#include "errorhandler.h"

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
                    return UNKNOWN;
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
                    return UNKNOWN;
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
                    return UNKNOWN;
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
                    return UNKNOWN;
            }

        case 's':
            switch (newPhase) {
                case 'a': case 'b': case 'c': case 'd':
                    currentPhase = newPhase;
                    return STANDSTILL;
                default:
                    currentPhase = 'e';
                    return UNKNOWN;
            }
        
        default:
            currentPhase = 'e';
            return UNKNOWN;
    }
}

int encodeInput(int in1State, int in0State, int *move, int *steps) {
    char phase;
    if (in1State) {
        phase = (in0State) ? 'c' : 'b';
    } else /* !in1State */ {
        phase = (in0State) ? 'd' : 'a';
    }
    *move = fsm(phase);

    RETURN_NOK_ON_ERR( *move == UNKNOWN,
        "phaseError: Move direction of encoder could not be determined." )
    
    switch (*move) {
        case FORWARD:  *steps += 1; break;
        case BACKWARD: *steps -= 1;
    }
    return EOK;
}

void resetMachine(void) {
    currentPhase = 's';
}

// EOF
