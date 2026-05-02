/*
 * Bare Metal OS(Task scheduler)
 *
 *  Created on: May 2, 2026
 *      Author: 2k18h
 */

#include <stdint.h>
#include <stdio.h>
#include "BMOS.h"

uint32_t volatile* const pICSR = (uint32_t volatile* const)0xE000ED04; // Interrupt Control Reg
TCB_t tcbs[TASKSMAXCOUNT];
uint32_t gCurrentTick = 0;
uint32_t gTasks_Count = 0;
uint8_t gCurrentRunningTask = 1;

void delay(uint32_t delayMs){
	__asm volatile("CPSID i"); // dissable Interrupts

	tcbs[gCurrentRunningTask].BLOCK_COUNT = gCurrentTick + delayMs;
	tcbs[gCurrentRunningTask].ACTIVE_STATE = BLOCKED_STATE;

	__asm volatile("CPSIE i"); // enable Interrupts
	pendPendSV();
}

void pendPendSV(void){
	*pICSR |= (1<<28);
}
void en_sysFaults(void){
	uint32_t volatile* pSHCRS = (uint32_t volatile*)0xE000ED24;
	*pSHCRS |=(7U << 16);
}
void en_SysTick(uint32_t timHZ){
	uint32_t clockSpeed = CLOCKSPEED;
	SysTick_t volatile* pSysTick = (SysTick_t volatile*)0xE000E010;
	pSysTick->CVR = 0;
	pSysTick->RVR |= (clockSpeed / timHZ) - 1; // Set Tick
	__asm volatile("CPSID i"); // dissable interrupts before enabling clock
	pSysTick->CSR |= 7U; //Enable SysTick

}
void init_task(void (*pFuncAddress)(void)){

	tcbs[gTasks_Count].taskPointer = pFuncAddress;
	//tcbs[5].taskPointer = task5;


	tcbs[gTasks_Count].ACTIVE_STATE = READY_STATE;
	tcbs[gTasks_Count].BLOCK_COUNT = 0;


	if(gTasks_Count == 0){
		tcbs[0].PSP = SRAMEND;
	}
	else{
		tcbs[gTasks_Count].PSP = SRAMEND - IDLETASKSIZE - (gTasks_Count - 1) * TASKSTACKSIZE;
	}
	 // Init PSP
	uint32_t volatile *pPSP = (uint32_t volatile *)tcbs[gTasks_Count].PSP;
	pPSP--;
	*pPSP = XPSR_INIT_VALUE; // T Bit enable
	pPSP--;
	*pPSP = (uint32_t)tcbs[gTasks_Count].taskPointer; // PC points to its own func
	pPSP--;
	*pPSP = LR_RET_TO_THREAD_PSP; // LR init Return to Thread mode

	for(uint32_t j = 0; j < 13; j++){ // Init Regs of Task with 0
		pPSP--;
		*pPSP = 0;
	}
	tcbs[gTasks_Count].PSP = (uint32_t)pPSP; // Set PSP to new PSP after initialization
	gTasks_Count++;

}
void find_freeTask(void){
	for(uint32_t i = 0; i < gTasks_Count; i++){
		gCurrentRunningTask++;
		gCurrentRunningTask %= gTasks_Count;
		if( (tcbs[gCurrentRunningTask].ACTIVE_STATE == READY_STATE || ((int32_t)(gCurrentTick - tcbs[gCurrentRunningTask].BLOCK_COUNT) >= 0)) && gCurrentRunningTask != 0){
			tcbs[gCurrentRunningTask].ACTIVE_STATE = READY_STATE;
			return;
		}
	}
	gCurrentRunningTask = 0;
	return;
}
__attribute__((naked)) void initSchedule(uint32_t pSchedule_Stack){
	__asm volatile("MSR MSP,R0"); //Initialization of MSP on the new STACK frame
	__asm volatile("BX LR");
}
void start_os(void){
	__asm volatile("CPSIE i"); // enabling interrupts
	__asm volatile("SVC #0x05");
	while(1);
}
uint32_t getCurrTask_PSP(void){
	return tcbs[gCurrentRunningTask].PSP;
}
uint32_t getFirstPSP(void){
	return tcbs[1].PSP;
}
void SysTick_Handler(void){
	gCurrentTick++;
	pendPendSV();
}

void saveCurrPSP(uint32_t PSP){
	tcbs[gCurrentRunningTask].PSP = PSP;
}

__attribute__((naked)) void PendSV_Handler(void){
	__asm volatile("MRS R0,PSP");
	__asm volatile("STMFD R0!, {R4-R11}");
	__asm volatile("PUSH {R3,LR}"); // Push R3 to align Stack Pointer
	__asm volatile("BL saveCurrPSP");
	__asm volatile("BL find_freeTask");
	__asm volatile("BL getCurrTask_PSP");
	__asm volatile("POP {R3,LR}");
	__asm volatile("LDMFD R0!,{R4-R11}");
	__asm volatile("MSR PSP, R0");
	__asm volatile("BX LR");
}
void HardFault_Handler(void){
	printf("HardFault error!\n");
}
void BusFault_Handler(void){
	printf("BusFault error!\n");
}
void MemManage_Handler(void){
	printf("MemManage error!\n");
}
void UsageFault_Handler(void){
	printf("UsageFault error!\n");
}
__attribute__((naked)) void SVC_Handler(void){

	__asm volatile("BL getFirstPSP");
	__asm volatile("LDMIA R0!, {R4-R11}");
	__asm volatile("MSR PSP, R0");    // Setting the PSP value
	__asm volatile("MOV R0, #0x02");  // Enabling PSP
	__asm volatile("MSR CONTROL, R0");
	__asm volatile("ISB"); // Synch Barrier
	__asm volatile("LDR LR, =0xFFFFFFFD");
	__asm volatile("BX LR");		  // Return
}



