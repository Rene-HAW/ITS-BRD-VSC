#ifndef RPN_OUTPUT_H
#define RPN_OUTPUT_H

/**
 *
 */
void initOutput(void);

/**
 *
 */
void clearOutput(void);

/*
 ****************************************************************************************
 *  @brief      Gibt einen Integer auf den Bildschrim aus
 *
 *  @param      value => Der auszugebende Wert
 *
 *  @return     void
 ****************************************************************************************/
void printNumber(int value);

/*
 ****************************************************************************************
 *  @brief      Gibt vordefinierte Nachrichten anhand einer Codenummer aus
 *
 *  @param      code => Codenummer
 *
 *  @return     void
 ****************************************************************************************/
void printMessage(int code);

/**
 *
 */
void printError(int code);

#endif /* RPN_OUTPUT_H */
// EOF
