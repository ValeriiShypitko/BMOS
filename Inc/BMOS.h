/*
 * BMOS.h
 *
 *  Created on: May 2, 2026
 *      Author: 2k18h
 */

#ifndef BMOS_H_
#define BMOS_H_

// Macros ///
#define SRAMSTART 				(0x20000000U)
#define SRAMEND 				(0x20020000U)


#define TASKSTACKSIZE 			(1024U)
#define IDLETASKSIZE 			(128U)
#define SCHEDULE_START			(SRAMEND - IDLETASKSIZE -  (TASKSMAXCOUNT * TASKSTACKSIZE))

#define TASKSMAXCOUNT 			(5U) // Changeble 5 by default
#define READY_STATE 			(1U)
#define BLOCKED_STATE 			(0U)

#define XPSR_INIT_VALUE 		(0x01000000)// T Bit Enable
#define LR_RET_TO_THREAD_PSP	(0xFFFFFFFD)
#define CLOCKSPEED 				(16000000U);


// Footprints
void start_os(void);
void en_sysFaults(void);
void en_SysTick(uint32_t timHZ);
void init_task(void (*pFuncAddress)(void));
__attribute__((naked)) void initSchedule(uint32_t pSchedule_Stack);
__attribute__((naked)) void switch_SP_to_PSP();
uint32_t find_and_get_freeTask(void);
uint32_t getFirstPSP(void);
void delay(uint32_t delayMs);
void pendPendSV(void);
void idle_task(void);
void task1(void);
void task2(void);
void task3(void);
void task4(void);
void task5(void);

//Structs
typedef struct{
	uint32_t PSP;
	uint32_t ACTIVE_STATE;
	uint32_t BLOCK_COUNT;
	void(*taskPointer)(void);
}TCB_t; // Task Control Block
typedef struct{
	uint32_t CSR;
	uint32_t RVR;
	uint32_t CVR;
	uint32_t CALIB;
}SysTick_t;



#endif /* BMOS_H_ */
