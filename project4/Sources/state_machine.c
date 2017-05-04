/*
 * state_machine.c
 *
 *  Created on: May 4, 2017
 *      Author: jonathanwingfield
 */
#include "state_machine.h"

/* uint8_t get_message_checksum(command_t* cmd)
 *  returns 8 bit checksum for message m
 *  checksum calculated as byte wise xor of command
 */
static uint8_t get_command_checksum(command_t* cmd){

	if(cmd == NULL) return -1;
	uint8_t* ite = (uint8_t*)cmd;
	uint8_t checksum = 0;
	uint8_t i = cmd->length - 1;
	while(i--){
		checksum ^= *ite++;
	}
	return checksum;
}

/* uint8_t is_valid_checksum(commant_t * cmd)
 * 	Indicates if received checksum is valid given command_t item.
 *
 * INPUTS:
 * 	- command_t * cmd: reference to a command object
 *
 * OUTPUTS:
 * 	- boolean that is true if checksum is valid and false otherwise
 */
static uint8_t is_valid_checksum(command_t* cmd) {
	return (cmd && (get_command_checksum(cmd) == cmd->checksum));
}

int32_t send_command(command_t* cmd) {

	if(cmd == NULL) return -1;
	if(cmd->checksum= get_command_checksum(cmd) == -1) return -1;
	uart_send_byte_n((uint8_t*)cmd, cmd->length);
	return 0;
}

int32_t read_command(command_t* cmd){

	if(cmd == NULL) return -1;

	uart_receive_byte_n((uint8_t*)cmd, 2); // receive cmd and length
	if(cmd->length > MAX_DATA_SIZE + 3){
		return -1;
	}
	uart_receive_byte_n(cmd->data, cmd->length - 3);
	uart_receive_byte(&(cmd->checksum));
	return 0;
}

int32_t decode_command(command_t* cmd) {

	if(cmd == NULL) return -1;
	if(cmd->command > 4 || cmd->command < 0) return -1; // handle better than this, but ignore invalid commands
	if(!is_valid_checksum(cmd)) return -1;
	return 0;
}

int32_t execute_command(command_t* cmd){

	int8_t timebuf[8];
	if(cmd == NULL) return -1;
	switch(cmd->command){
	case GET_TIMESTAMP:
		my_itoa(timebuf, systick_get_time_ms(), 10);
		uart_send_byte_n(timebuf, 6);
		break;
	case RESET:
		NVIC_SystemReset();
		break;
	case RED_CONTROL:
		pwm_set_duty_cycle(LED_RED_TPM_CH, cmd->data[0]);
		break;
	case GREEN_CONTROL:
		pwm_set_duty_cycle(LED_GREEN_TPM_CH, cmd->data[0]);
		break;
	case BLUE_CONTROL:
		pwm_set_duty_cycle(LED_BLUE_TPM_CH, cmd->data[0]);
		break;
	}
	return 0;
}

