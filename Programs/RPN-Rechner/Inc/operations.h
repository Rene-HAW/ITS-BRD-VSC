#ifndef RPN_OPERATIONS_H
#define RPN_OPERATIONS_H

/**
 *
 */
int rpn_enterNumber(int num);

/*
 ****************************************************************************************
 *  @brief      Nimmt die zwei obersten Werte vom Stack
 *              und wendet die Operation des gegeben Tokens auf diese an
 *
 *  @param      token => Der Token Character
 *
 *  @return     int => Statuscode der Funktion
 ****************************************************************************************/
int rpn_binaryOperations(char token);

/*
 ****************************************************************************************
 *  @brief      Dupliziert den obersten Wert auf dem Stack
 *
 *  @return     int => Statuscode der Funktion
 ****************************************************************************************/
int rpn_duplicate(void);

/*
 ****************************************************************************************
 *  @brief      Gibt das obersten oder alle Elemente im Stack
 *              auf den Bildschirm aus.
 *
 *  @param      token => PRT oder PRT_ALL Token
 *
 *  @return     void
 ****************************************************************************************/
void rpn_printOperations(char token);

/**
 *
 */
void rpn_clearMemory(void);

#endif /* RPN_OPERATIONS_H */
// EOF
