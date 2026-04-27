/**
  * @file   stack.c
  * @author René Rudzki
  * @brief  Implementierung eines Stacks (LIFO Queue)
  *         als Speicher für den Taschenrechner
*/

#include "stack.h"
#include "code_num.h"
#include <stdbool.h>

#define MAX_SIZE 100

typedef struct {
    int array[MAX_SIZE];
    int top;
} Int_Stack;

static Int_Stack stack = {.top = -1};

static bool isEmpty(void) {
    return stack.top == -1;
}

static bool isFull(void) {
    return stack.top == (MAX_SIZE - 1);
}

int stackPush(int value) {
    if (isFull()) { return OVERFLOW_ERR; }

    stack.top++;
    stack.array[stack.top] = value;
    return EOK;
}

int stackPop(int *value) {
    if (isEmpty()) { return UNDERFLOW_ERR; }

    *value = stack.array[stack.top];
    stack.top--;
    return EOK;
}

int stackPeek(int *value, int depth) {
    if (isEmpty()) { return STACK_EMPTY; }

    int index = stack.top - depth;
    if ( (index < 0) || (stack.top < index) ) { return INPUT_ERR; }

    *value = stack.array[index];
    return EOK;
}

void clearStack(void) {
    stack.top = -1;
}

// EOF
