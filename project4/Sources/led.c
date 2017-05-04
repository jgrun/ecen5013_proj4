/*
 * led.c
 *
 *  Created on: May 3, 2017
 *      Author: jonathanwingfield
 */
#include "led.h"

void led_init(void){
	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK|SIM_SCGC5_PORTD_MASK;
	// enable clock for portb and portd gpio pins (tied to leds)

	PORTB_PCR18 = PORT_PCR_MUX(1);// Set PB.18 to output
	PORTB_PCR19 = PORT_PCR_MUX(1); // set PB.19 to output
	PORTD_PCR1 = PORT_PCR_MUX(1);
	GPIOB_PDDR |= (1<<18)|(1<<19);
	GPIOB_PDOR |= (1<<18)|(1<<19);
	GPIOD_PDDR |= (1<<1);
	GPIOD_PDOR |= (1<<1);
}


