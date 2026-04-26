/**
  * @file   msg_handler.c
  * @author René Rudzki, Sajad Nazari
  * @brief  Modul zur Ausgabe von Nachrichten auf den Bildschirm
  */

#include "msg_handler.h"
#include "display.h"
#include "limits.h"
#include "token.h"
#include "err_num.h"
#include "scanner.h"

static int sizeofInt(int value) {
    int count = 2;    // Allocate for '\n' + '\0'
    if (value <= 0) { count++; }    // Allocate for '0' || '-'
    while (value != 0) {
        count++;
        value = value / 10;
    }
    return count;
}

void printNumber(int value) {
    int i = sizeofInt(value);
    char str[i]; i--;

    str[i] = '\0'; i--;
    str[i] = '\n'; i--;

    if (value == 0) { str[0] = '0'; }
    else {
        if (value < 0) {
            if (value == INT_MIN) {
                str[i] = '8';
                value = value / 10;
                i--;
            }
            str[0] = '-';
            value = -value;
        }
        
        while (value > 0) {
            str[i] = value % 10 + '0';
            value = value / 10;
            i--;
        }
    }
    
    if (isBottomLine()) {
        printStdout("Mit P fortfahren...");
        T_token input = nextToken();
        while (input.tok != PRT_ALL) { input = nextToken(); }
        clearStdout();
    }
    printStdout(str);
}

void printMessage(int num) {
    switch (num) {
        case STACK_EMPTY:
            printStdout("Stack leer."); break;
        case OVERFLOW_ERR:
            printStdout("Stack Overflow!\n(Reset mit C)"); break;
        case UNDERFLOW_ERR:
            printStdout("Stack Underflow!\n(Reset mit C)"); break;
        case ARITHMETIC_ERR:
            printStdout("Arithmetic Overflow!\n(Reset mit C)"); break;
        case DIVIDE0_ERR:
            printStdout("Durch 0 geteilt!\n(So moege Sie der\nBlitz treffen.)"); break;
        case UNEX_INPUT_ERR:
            printStdout("Unexpected Input!\n(Reset mit C)");
    }
}

//EOF
