#include "test.h"
#include "init.h"
#include "lcd.h"
#include "LCD_GUI.h"
#include "stm32f429xx.h"

volatile int counter = 0;

void EXTI1_IRQHandler(void) {
    EXTI->PR = EXTI_PR_PR1;
    counter++;
}

static void initInterrupt(void) {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOFEN;
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

    SYSCFG->EXTICR[0] &= ~SYSCFG_EXTICR1_EXTI1;
    SYSCFG->EXTICR[0] |=  SYSCFG_EXTICR1_EXTI1_PF;
    
    EXTI->RTSR |= EXTI_RTSR_TR1;
    EXTI->IMR  |= EXTI_IMR_MR1;

    NVIC_SetPriority(EXTI1_IRQn, 0);
    NVIC_EnableIRQ(EXTI1_IRQn);
}

void main_test(void) {
    initITSboard();
    GUI_init(DEFAULT_BRIGHTNESS);
    initInterrupt();
    int current, last = 0;

    while (1) {
        current = counter;
        if (current != last) {
            lcdGotoXY(1,1);
            lcdPrintInt(current);
            last = current;
        }
    }
}
