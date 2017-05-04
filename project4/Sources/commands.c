/*
 * commands.c
 *
 *  Created on: Apr 30, 2017
 *      Author: jacob
 */

#include "commands.h"



void get_timestamp(command_t* cmd) {
	int8_t timebuf[8];
	uart_send_byte_n(my_itoa(timebuf, systick_get_time_ms(), 10), 6);
}

void reset_software(command_t* cmd) {
	NVIC_SystemReset();
}

// These will need some PWM stuff to actually do things
void set_red(command_t* cmd) {
	pwm_set_duty_cycle(LED_RED_TPM_CH, cmd->data[0]);
}

void set_green(command_t* cmd) {
	pwm_set_duty_cycle(LED_GREEN_TPM_CH, cmd->data[0]);
}

void set_blue(command_t* cmd) {
	pwm_set_duty_cycle(LED_BLUE_TPM_CH, cmd->data[0]);
}
