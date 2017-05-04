/*
 * state_machine.h
 *
 *  Created on: May 4, 2017
 *      Author: jonathanwingfield
 */

#ifndef SOURCES_STATE_MACHINE_H_
#define SOURCES_STATE_MACHINE_H_

#include "definitions.h"
#include "control.h"
#include "uart.h"
#include "definitions.h"
#include "led.h"
#include "pwm.h"
#include "timer.h"
#include "data.h"
#include <stdlib.h>

#pragma pack(1)
typedef enum commands_t {
	GET_TIMESTAMP = 0x00,
	// Perform software reset
	RESET         = 0x01,
	// Control red led brightness
	RED_CONTROL   = 0x02,
	// Control green led brightness
	GREEN_CONTROL = 0x03,
	// Control blue led brightness
	BLUE_CONTROL  = 0x04,
}cmds;

#pragma pack(1)
typedef struct{
	cmds command;
	uint8_t length; // length of entire struct in bytes
	uint8_t data[MAX_DATA_SIZE];
	uint8_t checksum; // XOR checksum
} command_t;

typedef enum{
	read_state,
	decode_state,
	execute_state
}current_state_t;

typedef int32_t (*state_machine_t)(command_t*);
typedef void (*callback_function_t)(command_t*);

/* send_message(message * m)
 * 	Will send the message data in m. First it will generate the checksum then it will
 * 	send the data starting with the command, then the length, then the data, then the
 * 	checksum.
 *
 * INPUTS:
 * 	- message * m: message type pointer containing the command, data, and length of data parameters.
 *
 * OUTPUTS:
 *  - 0 for success
 *  - -1 for error (NULL pointer, checksum failure, uart failure)
 */
int32_t send_command(command_t* cmd);


int32_t read_command(command_t* cmd);

/* int32_t decode_message(command_t * cmd)
 * 	Validates message as being correct after it is read in in S1 (read_message)
 *
 * INPUTS:
 *  - commant_t * cmd: reference to command object
 *
 * OUTPUTS:
 *  -  -1 if command is invalid (failed checksum, bad pointer, bad payload size)
 *  -  0 if command is valid and able to be executed
 */
int32_t decode_command(command_t* cmd);


int32_t execute_command(command_t* cmd);


#endif /* SOURCES_STATE_MACHINE_H_ */
