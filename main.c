/*
 * main.c
 *
 * Description:
 *  An example project for running the CMSIS-RTOS2 on an STM32F107-based board (Cortex-M3)
 *  Based on the Blinky example from CMSIS RTOS2 folder.
 *  Toggles PORTE pins 14 and 15.
 *
 * Setup steps:
 * Get CMSIS-5 library with git submodule init
 *  and git submodule update
 *
 * Author: Furkan Cayci
 *
 * Project Setup:
 *   EasyMX Pro V7 board
 *   Cortex-M3 arch
 *   STM32F107 chip
 */

/*************************************************
* Definitions
*************************************************/
#include <stdio.h>
#include "stm32f107xx.h"
#include "ARMCM3.h"
#include "cmsis_os2.h"

void set_system_clock_to_72Mhz(void);
int main(void);

osThreadId_t tid_blink14; // Thread id of thread: blink14
osThreadId_t tid_blink15; // Thread id of thread: blink15
osThreadId_t tid_clock;   // Thread id of thread: clock

osMutexId_t phases_mut_id;

void set_system_clock_to_72Mhz(void)
{
	// Necessary wait states for Flash for high speeds
	FLASH->ACR = 0x12;
	// Enable HSE
	RCC->CR |= (1 << 16);
	// Wait untill HSE settles down
	while (!(RCC->CR & (1 << 17)));
	// Set PREDIV2 division factor to 5
	RCC->CFGR2 |= (0b0100 << 4);
	// Set PLL2 multiplication factor to 8
	RCC->CFGR2 |= (0b0110 << 8);
	// Enable PLL2
	RCC->CR |= (1 << 26);
	// Wait untill PLL2 settles down
	while (!(RCC->CR & (1 << 27)));
	// Set PLL2 as PREDIV1 clock source
	RCC->CFGR2 |= (1 << 16);
	// Set PREDIV1 division factor to 5
	RCC->CFGR2 |= (0b0100 << 0);
	// Select Prediv1 as PLL source
	RCC->CFGR |= (1 << 16);
	// Set PLL1 multiplication factor to 9
	RCC->CFGR |= (0b0111 << 18);
	// Set APB1 to 36MHz
	RCC->CFGR |= 1 << 10;
	// Enable PLL
	RCC->CR |= (1 << 24);
	// Wait untill PLL settles down
	while (!(RCC->CR & (1 << 25)));
	// Finally, choose PLL as the system clock
	RCC->CFGR |= (0b10 << 0);
}

/*----------------------------------------------------------------------------
 *      Function 'signal_func' called from multiple threads
 *---------------------------------------------------------------------------*/
void signal_func (osThreadId_t tid)  {
  osThreadFlagsSet(tid_clock, 0x0100);      /* set signal to clock thread    */
  osDelay(500);                             /* delay 500ms                   */
  osThreadFlagsSet(tid_clock, 0x0100);      /* set signal to clock thread    */
  osDelay(500);                             /* delay 500ms                   */
  osThreadFlagsSet(tid, 0x0001);            /* set signal to thread 'thread' */
  osDelay(500);                             /* delay 500ms                   */
}

/*----------------------------------------------------------------------------
 *      Thread 1 Blink LED PE14
 *---------------------------------------------------------------------------*/
void blink14 (void *argument) {
  for (;;) {
    osThreadFlagsWait(0x0001, osFlagsWaitAny ,osWaitForever);    /* wait for an event flag 0x0001 */
    GPIOE->ODR |= (1 << 14);
    signal_func(tid_blink15);                                     /* call common signal function   */
	GPIOE->ODR &= ~(1 << 14);
  }
}

/*----------------------------------------------------------------------------
 *      Thread 2 Blink LED PE15
 *---------------------------------------------------------------------------*/
void blink15 (void *argument) {
  for (;;) {
    osThreadFlagsWait(0x0001, osFlagsWaitAny, osWaitForever);    /* wait for an event flag 0x0001 */
    GPIOE->ODR |= (1 << 15);
    signal_func(tid_blink14);                /* call common signal function   */
    GPIOE->ODR &= ~(1 << 15);
  }
}

/*----------------------------------------------------------------------------
 *      Thread 3 'clock': Signal Clock
 *---------------------------------------------------------------------------*/
void clock (void *argument) {
  for (;;) {
    osThreadFlagsWait(0x0100, osFlagsWaitAny, osWaitForever);    /* wait for an event flag 0x0100 */
    osDelay(80);                            /* delay  80ms                   */
  }
}

/*----------------------------------------------------------------------------
 *      Main: Initialize and start RTX Kernel
 *---------------------------------------------------------------------------*/
void app_main (void *argument) {

	tid_blink14 = osThreadNew(blink14, NULL, NULL);
	tid_blink15 = osThreadNew(blink15, NULL, NULL);
	tid_clock  = osThreadNew(clock,  NULL, NULL);

	osThreadFlagsSet(tid_blink14, 0x0001);          /* set signal to blink14 thread   */

	osDelay(osWaitForever);
	while(1);
}

void _start(void)
{
	main();
}

/*************************************************
* Main code starts from here
*************************************************/
int main(void)
{
	// Update system core clock to 72 Mhz
	SystemCoreClockUpdate();
	set_system_clock_to_72Mhz();

	// Generate interrupt each 10 ms
	SysTick_Config(SystemCoreClock/100);

	// Enable GPIOE clock. Bit 6 in RCC APB2ENR register
	RCC->APB2ENR |= (1 << 6);

	// Make PE14 & PE15 output
	GPIOE->CRH &= 0x00000000;
	GPIOE->CRH |= 0x22222222;
	GPIOE->ODR = 0;

	// Initialize CMSIS-RTOS
	osKernelInitialize();

	// Create application main thread
	osThreadNew(app_main, NULL, NULL);

	if (osKernelGetState() == osKernelReady) {
		// Start thread execution
		osKernelStart();
	}

	while(1){
	};

	return 0;
}
