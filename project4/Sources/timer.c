/*
 * timer.c
 *
 *  Created on: Apr 1, 2017
 *      Author: jonathanwingfield
 */
#include "timer.h"

static volatile systime_t sys_time = 0; // can count without ovflw for ~ 27.8 thousand yrs
// holds time in 0.75 second granularity
// sys_time + SYSTICK->CVR gives system time with 47.6 ns resolution

void systick_init(void){
	sys_time = 0;
	SYSTICK->SYST_CVR = 0x0;
	//clear systick timer
	SYSTICK->SYST_CSR = (SYST_CSR_CLKSOURCE|SYST_CSR_TICKINT|SYST_CSR_ENABLE);
	// sets to freq of core clock and enables interrupts and timer
	SYSTICK->SYST_RVR = SYST_RVR_RELOAD_MAX;
	// set reload to be maximum value
	NVIC_EnableIRQ(SysTick_IRQn);
}

volatile systime_t systick_get_ticks(void){
	return sys_time + (SYSTICK->SYST_RVR - SYSTICK->SYST_CVR);
}

volatile uint32_t systick_get_time_ms(void){
	volatile uint32_t t = systick_get_ticks();
	volatile uint32_t t_ms = TICKS_TO_mSEC(t);
	return t_ms;
}

volatile uint32_t systick_get_time_us(void){
	return TICKS_TO_uSEC(systick_get_ticks());
}

volatile systime_t systick_get_ticks_since(systime_t previous_time){
	return systick_get_ticks() - previous_time;
}

volatile uint32_t systick_get_time_since_ms(systime_t previous_time){
	return systick_get_time_ms() - previous_time;
}

volatile uint32_t systick_get_time_since_us(systime_t previous_time){
	return systick_get_time_us() - previous_time;
}

void delay_ms(volatile uint32_t num_ms){

	volatile uint32_t start = systick_get_time_ms();
	while(systick_get_time_since_ms(start) < num_ms);
}

//uint32_t systick_get_time_since_us(systime_t previous_time){
//	return TICKS_TO_uSEC(systick_get_ticks()) - previous_time;
//}

extern void SysTick_Handler(void){ // interrupts every 0.750 seconds
	sys_time += (SYST_RVR_RELOAD_MAX + 1);
	// update system time with number of ticks to have occurred
}

void stall(uint32_t t) {
	systime_t start = systick_get_ticks(); // Get base ticks
	while(systick_get_time_since_ms(start) <= t); // Wait until t milliseconds have passed
}

