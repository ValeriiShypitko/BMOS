
#include <stdint.h>
#include "led.h"

void initLEDs(void){
	RCC_AHB1ENR |= (1U << 2); // Turn On RCC for GPIO port C
	GPIOC_MODER &= ~((3U << 10) | (3U << 12) | (3U << 16) | (3U << 20));//Сlear GPIOC pinmodes to OUTPUT
	GPIOC_MODER |= ((1U << 10) | (1U << 12) | (1U << 16) | (1U << 20));//Set GPIOC pinmodes to OUTPUT
}

void turnOnLED(uint8_t LED){
	GPIOC_BSRR = (1U << LED); // Turn on the LED
}
void turnOffLED(uint8_t LED){
	GPIOC_BSRR = (1U << (LED + 16)); // Turn off the LED
}
