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
	// send RTC/Systick time stamp to host
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
}state_t;

typedef int32_t (*state_machine_t)(command_t*);
typedef void (*callback_function_t)(command_t*);

/* send_message(command_t* cmd)
 * 	Will send the data contained in the the paramter. First it will generate the checksum then it will
 * 	send the data starting with the command, then the length, then the data, then the
 * 	checksum.
 *
 * INPUT:
 * 	> command_t* cmd: reference to command object containing data to send
 *
 * OUTPUT:
 *  > 0 for success
 *  > -1 for error (NULL pointer, checksum failure, uart failure)
 *
 */
int32_t send_command(command_t* cmd);

/* int32_t read_command(command_t* cmd)
 *	Reads command from UART connection and writes data into cmd
 *
 *	INPUT:
 *	> command_t* cmd: reference to command object which will be filled
 *		with received command data
 *	OUTPUT:
 *	>  0 for success
 *	> -1 for error
 *
 */
int32_t read_command(command_t* cmd);

/* int32_t decode_command(command_t * cmd)
 * 	Validates command object by verifying checksum is correct and command is valid
 *
 * INPUT:
 *  > command_t * cmd: reference to command object to be verified
 *
 * OUTPUT:
 *  >  -1 if command is invalid (failed checksum, NULL pointer, invalid command)
 *  >   0 if command is valid and able to be executed
 *
 */
int32_t decode_command(command_t* cmd);

/* int32_t execute_command(command_t* cmd)
 * 	executes appropriate callback function for command object
 *
 * INPUT:
 * > command_t* cmd: reference to command object whose callback is to be ran
 *
 * OUTPUT:
 * > 0
 *
 */
int32_t execute_command(command_t* cmd);


#endif /* SOURCES_STATE_MACHINE_H_ */
