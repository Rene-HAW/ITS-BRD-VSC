/**
  * @file   operations.c
  * @author René Rudzki, Sajad Nazari
  * @brief  Implementierung der Operationen des Taschenrechners
  */

#include "operations.h"
#include "stack.h"
#include "limits.h"
#include "token.h"
#include "err_num.h"
#include "msg_handler.h"

static int add(int num_a, int num_b) {
    if  (  (num_a > 0) && (num_b > 0) && (num_b > INT_MAX - num_a)
        || (num_a < 0) && (num_b < 0) && (num_b < INT_MIN - num_a)
        ) {
            return ARITHMETIC_ERR;
        }
    int result = num_a + num_b;
    stackPush(result);
    return EOK;
}

static int subtract(int num_a, int num_b) {
    if  (  (num_a < 0) && (num_b > -1) && (num_b > INT_MAX + num_a)
        || (num_a > 0) && (num_b < -1) && (num_b < INT_MIN + num_a)
        ) {
            return ARITHMETIC_ERR;
        }
    int result = num_b - num_a;
    stackPush(result);
    return EOK;
}

static int multiply(int num_a, int num_b) {
    if  (  (num_a > 1) && (num_b > 1) && (num_b > INT_MAX / num_a)
        || (num_a < 0) && (num_b < 0) && (num_b < INT_MAX / num_a)    // > wird zu < wegen Teilung durch Minuszahl

        || (num_a > 1) && (num_b < 0) && (num_b < INT_MIN / num_a)
        || (num_a < 0) && (num_b > 1) && (num_b > INT_MIN / num_a)    // < wird zu > wegen Teilung durch Minuszahl
        ) {
            return ARITHMETIC_ERR;
        }
    int result = num_a * num_b;
    stackPush(result);
    return EOK;
}

static int divide(int num_a, int num_b) {
    if (num_a == 0) {
        return DIVIDE0_ERR;
    }
    if ( (num_b == INT_MIN) && (num_a == -1) ) {
        return ARITHMETIC_ERR;
    }
    int result = num_b / num_a;
    stackPush(result);
    return EOK;
}

int calculate(char token) {
    int num_a; int num_b;
    int state;

    state = stackPop(&num_a);
    if (state != EOK) { return state; }
    state = stackPop(&num_b);
    if (state != EOK) { return state; }

    switch (token) {
        case PLUS:
            state = add(num_a, num_b); break;
        case MINUS:
            state = subtract(num_a, num_b); break;
        case MULT:
            state = multiply(num_a, num_b); break;
        case DIV:
            state = divide(num_a, num_b); break;
        case SWAP:
            stackPush(num_a);
            stackPush(num_b);
            break;
        default:
            state = UNEX_INPUT_ERR;
    }
    return state;
}

int duplicate(void) {
    int num_a;
    int state;

    state = stackPop(&num_a);
    if (state != EOK) { return state; }

    stackPush(num_a);
    stackPush(num_a);
    return EOK;
}

void printOps(char token) {
    int num_a; int num_b;
    int state;
    int depth = 0;
    
    state = stackPeek(&num_a, depth);
    if (state == STACK_EMPTY) { printMessage(state); return; }

    printNumber(num_a);
    
    if (token == PRT_ALL) {
        depth++;
        state = stackPeek(&num_a, depth);

        while (state == EOK) {
            printNumber(num_a);
            depth++;
            state = stackPeek(&num_a, depth);
        }
    }
}

//EOF
