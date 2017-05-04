/*
 * state_machine.c
 *
 *  Created on: May 4, 2017
 *      Author: jonathanwingfield
 */
#include "state_machine.h"

extern void get_timestamp(command_t* cmd);
extern void reset_software(command_t* cmd);
extern void set_red(command_t* cmd);
extern void set_green(command_t* cmd);
extern void set_blue(command_t* cmd);

static callback_function_t callback_function[]= {get_timestamp,
												 reset_software,
												 set_red,
												 set_green,
												 set_blue};

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
	if(cmd->checksum = get_command_checksum(cmd) == -1) return -1;
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
	callback_function[cmd->command](cmd);
	return 0;
}

