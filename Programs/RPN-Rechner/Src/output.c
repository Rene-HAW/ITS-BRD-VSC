/**
 * @file   output.c
 * @author René Rudzki
 * @brief  Modul zur Ausgabe von Nachrichten auf den Bildschirm
*/

#include "output.h"
#include "display.h"
#include "scanner.h"
#include "token.h"
#include "code_num.h"

#define STRING_SIZE 13    // Sign + Max Stellen eines Integers + \n + \0

void initOutput(void) {
    initDisplay();
}

void clearOutput(void) {
    clearStdout();
}

void printNumber(int value) {
    char str[STRING_SIZE];
    int i = 0;
    int neg = 0;

    // Anpassungen wenn negative Zahl
    if (value < 0) {
        value = -value;
        str[i] = '-';
        i++; neg = 1;
    }

    // Zahl in String konvertieren mit Modulo 10 Strategie
    do {
        str[i] = (char)(value % 10) + '0';
        i++; value /= 10;
    } while (value > 0);

    str[i] = '\n'; i++;
    str[i] = '\0';

    // Gespiegelten String umkehren
    for (int lo=neg, up=(i-2) ; lo<up ; lo++, up--) {
        char temp = str[lo];
        str[lo] = str[up];
        str[up] = temp;
    }
    
    // Ausgabe wenn Platz vorhanden
    if ( isBottomLine() ) {
        printStdout("Mit P fortfahren...");
        T_token input = nextToken();
        while (input.tok != PRT_ALL) { input = nextToken(); }
        clearStdout();
    }
    printStdout(str);
}

void printMessage(int code) {
    switch (code) {
        case STACK_EMPTY:
            printStdout("Stack leer."); break;
        case OVERFLOW_ERR:
            printStdout("Stack Overflow!\n(Reset mit C)"); break;
        case UNDERFLOW_ERR:
            printStdout("Stack Underflow!\n(Reset mit C)"); break;
        case ARITHMETIC_ERR:
            printStdout("Arithmetic Overflow!\n(Reset mit C)"); break;
        case DIVIDE_0_ERR:
            printStdout("Durch 0 geteilt!\n(So moege Sie der\nBlitz treffen.)"); break;
        case INPUT_ERR:
            printStdout("Unexpected Input!\n(Reset mit C)");
    }
}

void printError(int code) {
    setErrMode();
	printMessage(code);
    T_token input = nextToken();
    while (input.tok != PRT_ALL) { input = nextToken(); }
	setNormalMode();
}

//EOF
