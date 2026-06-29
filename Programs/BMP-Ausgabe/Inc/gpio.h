#ifndef _GPIO_H
#define _GPIO_H

#include "stm32f429xx.h"
#define  INPUT  GPIOF
#define  S0     0

/**
 *  @brief  Lese einen GPIO Pin aus
 *  @param  *GPIOx  Welche GPIO Schnittstelle
 *  @param  pin     Welcher Pin
 *  @retval NOK wenn invalider Pin
 */
int readGPIOpin(GPIO_TypeDef *GPIOx, int pin);

/**
 *  @brief  Warte auf einen kompletten Knopfdruck (push + release)
            Geht in endlose Fehlerschleife wenn invalider Pin
 *  @param  button  Pin des gewuenschten Knopfes
 *  @retval None
 */
void waitForButton(int button);

#endif /* _GPIO_H */
// EOF
