#ifndef STACK_H
#define STACK_H

/**
 ******************************************************************************
 *  @brief      Packt ein Element auf den Stack.
 *  @param      value => Integer für den Stack
 *  @return     int => Statuscode der Funktion
 ******************************************************************************
*/
int stackPush(int value);

/**
 ******************************************************************************
 *  @brief      Entfernt das oberste Element auf den Stack.
 *  @param      *value => Integer Adresse in die der Wert geschrieben wird.
 *  @return     int => Statuscode der Funktion
 ******************************************************************************
*/
int stackPop(int *value);

/**
 ******************************************************************************
 *  @brief      Liest ein Element im Stack an gewünschter Tiefe
 *  @param      *value => Integer Adresse in die der Wert geschrieben wird.
 *              depth => Bestimmt wie tief im Stack gesucht wird.
 *  @return     int => Statuscode der Funktion
 ******************************************************************************
*/
int stackPeek(int *value, int depth);

/**
 ******************************************************************************
 *  @brief      Setzt den Stack zurück
 *  @return     void
 ******************************************************************************
*/
void clearStack(void);

#endif /* STACK_H */
// EOF
