#include "interrupts.h"
#include "stm32f429xx.h"

void initInterrupts(void) {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

    SYSCFG->EXTICR[0] &= ~(SYSCFG_EXTICR1_EXTI1 + SYSCFG_EXTICR1_EXTI0);
    SYSCFG->EXTICR[0] |= (SYSCFG_EXTICR1_EXTI1_PG + SYSCFG_EXTICR1_EXTI0_PG);
    
    EXTI->RTSR |= (EXTI_RTSR_TR1 + EXTI_RTSR_TR0);
    EXTI->FTSR |= (EXTI_FTSR_TR1 + EXTI_FTSR_TR0);
    EXTI->IMR  |= (EXTI_IMR_MR1 + EXTI_IMR_MR0);

    NVIC_SetPriority(EXTI1_IRQn, 0);
    NVIC_SetPriority(EXTI0_IRQn, 0);
    NVIC_EnableIRQ(EXTI1_IRQn);
    NVIC_EnableIRQ(EXTI0_IRQn);
}

void EXTI1_IRQHandler(void) {
    EXTI->PR = EXTI_PR_PR1;

}

void EXTI0_IRQHandler(void) {
    EXTI->PR = EXTI_PR_PR0;

}

// EOF
