/*
 * led.h
 *
 *  Created on: May 3, 2017
 *      Author: jonathanwingfield
 */

#ifndef SOURCES_LED_H_
#define SOURCES_LED_H_

#include "MKL25Z4.h"

#define RED 0
#define GREEN 1
#define BLUE 2

#define RED_LED 1 << 18
#define GREEN_LED 1 << 19
#define BLUE_LED 1 << 1

#define LED_RED_TPM_CH   TPM_CH0
#define LED_GREEN_TPM_CH TPM_CH1
#define LED_BLUE_TPM_CH  TPM_CH2

void led_init(void);

__attribute__((always_inline))
inline void led_red_clear(void){
	GPIOB_PSOR |= (1<<18);
}

__attribute__((always_inline))
inline void led_green_clear(void){
	GPIOB_PSOR |= (1<<19);
}

__attribute__((always_inline))
inline void led_blue_clear(void){
	GPIOD_PSOR |= (1<<1);
}

__attribute__((always_inline))
inline void led_red_set(void){
	GPIOB_PCOR |= (1<<18);
}

__attribute__((always_inline))
inline void led_green_set(void){
	GPIOB_PCOR |= (1<<19);
}

__attribute__((always_inline))
inline void led_blue_set(void){
	GPIOD_PCOR |= (1<<1);
}

__attribute__((always_inline))
inline void led_red_toggle(void){
	GPIOB_PTOR |= (1<<18);
}

__attribute__((always_inline))
inline void led_green_toggle(void){
	GPIOB_PTOR |= (1<<19);
}

__attribute__((always_inline))
inline void led_blue_toggle(void){
	GPIOD_PTOR |= (1<<1);
}

#endif /* SOURCES_LED_H_ */
