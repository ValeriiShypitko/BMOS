#include <stdint.h>
#include <stdio.h>
#include "BMOS.h"
#include "led.h"




int main(void){
	en_sysFaults();// Enable BusFault,UsageFault, MemManageFault
	initLEDs(); // GPIOC 10,8,6,5 setting
	initSchedule(SCHEDULE_START); // Initialize MSP stack frame
	// Task initialization in PSP stack frame
	init_task(idle_task);
	init_task(task1);
	init_task(task2);
	init_task(task3);
	en_SysTick(1000); // Enabling System Clock
	start_os();
}




void idle_task(void){
	while(1);
}
void task1(void){
	while(1){
		turnOnLED(YELLOW_LED);
		delay(1000);
		turnOffLED(YELLOW_LED);
		delay(1000);
	}
}
void task2(void){
	while(1){
		turnOnLED(RED_LED);
		delay(1000);
		turnOffLED(RED_LED);
		delay(1000);
	}
}
void task3(void){
	while(1){
		turnOnLED(GREEN_LED);
		delay(500);
		turnOffLED(GREEN_LED);
		delay(500);
	}
}
void task4(void){
	while(1){
		turnOnLED(BLUE_LED);
		delay(400);
		turnOffLED(BLUE_LED);
		delay(400);
	}
}


