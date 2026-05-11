#ifndef RPN_OUTPUT_H
#define RPN_OUTPUT_H

/**
 ******************************************************************************
 *  @brief      Initialisiert die Ausgabe-Funktionalität
 *  @return     void
 ******************************************************************************
*/
void initOutput(void);

/**
 ******************************************************************************
 *  @brief      Leert die Bildschirmausgabe
 *  @return     void
 ******************************************************************************
*/
void clearOutput(void);

/**
 ******************************************************************************
 *  @brief      Gibt einen Integer auf den Bildschrim aus
 *  @param      value => Der auszugebende Wert
 *  @return     void
 ******************************************************************************
*/
void printNumber(int value);

/**
 ******************************************************************************
 *  @brief      Gibt vordefinierte Nachrichten anhand einer Codenummer aus
 *  @param      code => Codenummer
 *  @return     void
 ******************************************************************************
*/
void printMessage(int code);

/**
 ******************************************************************************
 *  @brief      Schaltet Ausgabe in den Fehlermodus bis zum naechsten CLEAR
 *  @param      code => Codenummer
 *  @return     void
 ******************************************************************************
*/
void printError(int code);

#endif /* RPN_OUTPUT_H */
// EOF
