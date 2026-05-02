/*
 * led.h
 *
 *  Created on: May 1, 2026
 *      Author: 2k18h
 */

#ifndef LED_H_
#define LED_H_

#define YELLOW_LED  10U
#define RED_LED     8U
#define GREEN_LED   6U
#define BLUE_LED    5U

#define RCC_AHB1ENR     (*((volatile uint32_t *)0x40023830))
#define GPIOC_MODER     (*((volatile uint32_t *)0x40020800))
#define GPIOC_BSRR      (*((volatile uint32_t *)0x40020818))

void initLEDs(void);
void turnOnLED(uint8_t LED);
void turnOffLED(uint8_t LED);


#endif /* LED_H_ */
