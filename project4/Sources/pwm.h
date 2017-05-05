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

/* void pwm_init(void)
 * 	Initializes MKL25Z's TPM0 module channels 0-2 for software capture mode
 */
void pwm_init(void);

/*
 * void pwm_set_duty_cycle(tpm0_channel_t channel, uint32_t duty_cycle)
 * 	sets duty cycle of a TPM0 channel specified by argument
 *
 * INPUTS
 * 	> tpm0_channel_t channel: argument specifies specific channel of TPM0
 * 	> uint32_t duty cycle: argument specifies duty cycle to set channel to
 * 		values should range from 0-100, those greater than 100 will create a 100% duty cycle
 *
 */
void pwm_set_duty_cycle(tpm0_channel_t channel, uint32_t duty_cycle);



#endif /* SOURCES_PWM_H_ */
