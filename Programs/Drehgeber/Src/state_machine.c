#include "state_machine.h"
#include "general_def.h"

static char bufPhase = 's';

static int fsm(char newPhase) {
    switch (bufPhase) {

        case 'a':
            switch (newPhase) {
                case 'a':
                    return STANDSTILL;
                
                case 'b':
                    bufPhase = newPhase;
                    return FORWARD;
                
                case 'd':
                    bufPhase = newPhase;
                    return BACKWARD;
                
                default:
                    bufPhase = 'e';
                    return INTERNAL_ERR;
            }

        case 'b':
            switch (newPhase) {
                case 'a':
                    bufPhase = newPhase;
                    return BACKWARD;
                
                case 'b':
                    return STANDSTILL;
                
                case 'c':
                    bufPhase = newPhase;
                    return FORWARD;
                
                default:
                    bufPhase = 'e';
                    return INTERNAL_ERR;
            }

        case 'c':
            switch (newPhase) {
                case 'b':
                    bufPhase = newPhase;
                    return BACKWARD;
                
                case 'c':
                    return STANDSTILL;
                
                case 'd':
                    bufPhase = newPhase;
                    return FORWARD;
                
                default:
                    bufPhase = 'e';
                    return INTERNAL_ERR;
            }

        case 'd':
            switch (newPhase) {
                case 'a':
                    bufPhase = newPhase;
                    return FORWARD;
                
                case 'c':
                    bufPhase = newPhase;
                    return BACKWARD;
                
                case 'd':
                    return STANDSTILL;
                
                default:
                    bufPhase = 'e';
                    return INTERNAL_ERR;
            }

        case 's':
            switch (newPhase) {
                case 'a': case 'b': case 'c': case 'd':
                    bufPhase = newPhase;
                    return STANDSTILL;
                
                default:
                    bufPhase = 'e';
                    return INTERNAL_ERR;
            }
        
        default:
            return INTERNAL_ERR;
    }
}

int encodeState(int in1State, int in0State) {
    char phase;
    if (in1State) {
        phase = (in0State) ? 'c' : 'b';
    } else /* !in1State */ {
        phase = (in0State) ? 'd' : 'a';
    }
    return fsm(phase);
}

void resetMachine(void) {
    bufPhase = 's';
}

// EOF
