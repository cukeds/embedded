#include "bsp.h"

static volatile uint32_t cooldown_counter = 0;


// Starts the cooldown timer
void BSP_StartCardCooldown(void) {
    cooldown_counter = CARD_COOLDOWN * 1000; // Convert seconds to milliseconds
}

inline void BSP_Countdown(void){
	cooldown_counter--;
}

inline uint32_t BSP_GetCounter(){
	return cooldown_counter;
}
