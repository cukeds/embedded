#include "bsp.h"

// Function to enable TIM4 interrupt
void BSP_START_PRESENCE_COUNTER(void) {
    // Enable the TIM4 update interrupt
    TIM4->DIER |= TIM_DIER_UIE;

    // Enable the TIM4 IRQ in the NVIC
    NVIC_EnableIRQ(TIM4_IRQn);
}

// Function to disable TIM4 interrupt
void BSP_STOP_PRESENCE_COUNTER(void) {
    // Disable the TIM4 update interrupt
    TIM4->DIER &= ~TIM_DIER_UIE;

    // Disable the TIM4 IRQ in the NVIC
    NVIC_DisableIRQ(TIM4_IRQn);
}
