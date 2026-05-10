/**
 *  @file   operations.c
 *  @author René Rudzki
 *  @brief  Implementierung der Operationen des Taschenrechners
*/

#include "operations.h"
#include "stack.h"
#include "output.h"
#include "limits.h"
#include "token.h"
#include "code_num.h"

static int add(int num_a, int num_b) {
    if  (  ( (num_a > 0) && (num_b > 0) && (num_a > INT_MAX - num_b) )
        || ( (num_a < 0) && (num_b < 0) && (num_a < INT_MIN - num_b) )
        ) {
            return ARITHMETIC_ERR;
        }
    int result = num_a + num_b;
    return stackPush(result);
}

static int subtract(int num_a, int num_b) {
    if  (  ( (num_a < -1) && (num_b > 0) && (num_a < INT_MIN + num_b) )
        || ( (num_a > -1) && (num_b < 0) && (num_a > INT_MAX + num_b) )
        ) {
            return ARITHMETIC_ERR;
        }
    int result = num_a - num_b;
    return stackPush(result);
}

static int multiply(int num_a, int num_b) {
    if  (  ( (num_a > 1) && (num_b > 1) && (num_a > INT_MAX / num_b) )
        || ( (num_a < 0) && (num_b < 0) && (num_a < INT_MAX / num_b) )

        || ( (num_a > 1) && (num_b < 0) && (num_a > INT_MIN / num_b) )
        || ( (num_a < 0) && (num_b > 1) && (num_a < INT_MIN / num_b) )
        ) {
            return ARITHMETIC_ERR;
        }
    int result = num_a * num_b;
    return stackPush(result);
}

static int divide(int num_a, int num_b) {
    if (num_b == 0) {
        return DIVIDE_0_ERR;
    }
    if ( (num_a == INT_MIN) && (num_b == -1) ) {
        return ARITHMETIC_ERR;
    }
    int result = num_a / num_b;
    return stackPush(result);
}

static int peekTop(int *value) {
    int state = stackPeek(value, 0);
    if (state == STACK_EMPTY) { 
        clearOutput();
        printMessage(state);
    }
    return state;
}

//-----------------------------------------------------------------------------

int rpn_enterNumber(int num) {
    return stackPush(num);
}

int rpn_binaryOperations(char token) {
    int num_a; int num_b;
    int state;

    state = stackPop(&num_b);
    if (state != EOK) { return state; }
    state = stackPop(&num_a);
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
            stackPush(num_b);
            stackPush(num_a); break;
        default:
            state = INPUT_ERR;
    }
    return state;
}

int rpn_duplicate(void) {
    int num;
    int state = peekTop(&num);
    if (state == EOK) { state = stackPush(num); }
    return state;
}

void rpn_printOperations(char token) {
    int num;
    int state = peekTop(&num);
    if (state == EOK) {
        clearOutput();
        printNumber(num);

        if (token == PRT_ALL) {
            int depth = 1;
            state = stackPeek(&num, depth);
            while (state == EOK) {
                printNumber(num);
                depth++;
                state = stackPeek(&num, depth);
            } //while
        } //PRT_ALL
    } //EOK
} //func

void rpn_clearMemory(void) {
    clearStack();
}

//EOF
