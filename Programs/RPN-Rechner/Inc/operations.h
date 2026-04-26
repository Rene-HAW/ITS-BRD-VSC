#ifndef OPERATIONS_H
#define OPERATIONS_H

/*
 ****************************************************************************************
 *  @brief      Nimmt die zwei obersten Werte vom Stack
 *              und wendet die Operation des gegeben Tokens auf diese an
 *
 *  @param      token => Der Token Character
 *
 *  @return     int => Statuscode der Funktion
 ****************************************************************************************/
int calculate(char token);

/*
 ****************************************************************************************
 *  @brief      Dupliziert den obersten Wert auf dem Stack
 *
 *  @return     int => Statuscode der Funktion
 ****************************************************************************************/
int duplicate(void);

/*
 ****************************************************************************************
 *  @brief      Gibt den obersten oder alle Elemente im Stack
 *              auf den Bildschirm aus.
 *
 *  @param      token => PRT oder PRT_ALL Token
 *
 *  @return     void
 ****************************************************************************************/
void printOps(char token);

#endif /* OPERATIONS_H */
// EOF
