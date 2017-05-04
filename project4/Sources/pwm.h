/*
 * timer.h
 *
 *  Created on: May 3, 2017
 *      Author: jonathanwingfield
 */

#ifndef SOURCES_PWM_H_
#define SOURCES_PWM_H_
#include "MKL25Z4.h"
#include "led.h"

typedef enum {
	TPM_CH0,
	TPM_CH1,
	TPM_CH2,
	TPM_CH3,
	TPM_CH4,
	TPM_CH5,
}tpm0_channel_t;

void pwm_init(void);
void pwm_set_duty_cycle(tpm0_channel_t channel, uint32_t duty_cycle);



#endif /* SOURCES_PWM_H_ */
