/*
 * transmission.h
 *
 *  Created on: Apr 30, 2017
 *      Author: jacob
 */

#ifndef SOURCES_TRANSMISSION_H_
#define SOURCES_TRANSMISSION_H_

#include "definitions.h"
#include "control.h"
#include "commands.h"

// externed from commands.h
extern void get_timestamp(uint8_t value);
extern void reset_software(uint8_t value);
extern void set_red(uint8_t value);
extern void set_green(uint8_t value);
extern void set_blue(uint8_t value);

/* send_message(message * m)
 * 	Will send the message data in m. First it will generate the checksum then it will
 * 	send the data starting with the command, then the length, then the data, then the
 * 	checksum.
 *
 * INPUTS:
 * 	- message * m: message type pointer containing the command, data, and length of data parameters.
 *
 * OUTPUTS:
 *  - nothing yet
 */
void send_message(message * m);

/* validate_message(message * m)
 * 	Will validate checksum from message.
 *
 * INPUTS:
 * 	- message * m: message type pointer that is received and needs to be validated
 *
 * OUTPUTS:
 * 	- boolean that is true if checksum is valid and false otherwise
 */
uint8_t valid_message(message * m);

/* decode_message(message * m, uint8_t * data, uint8_t length)
 * 	Takes in received data and stores it in appropriate bins in m
 *
 * INPUTS:
 *  - message * m: message type pointer to empty message
 *  - uint8_t * data: pointer to raw data from uart transmission
 *  - uint8_t length: length of raw data from uart transmission
 *
 * OUTPUTS:
 *  - none
 */
void decode_message(message * m, uint8_t * data, uint8_t length);

/* (* execute_command)(uint8_t value)
 * 	Takes in a command of type cmds as the dereferencer then executes the command
 *
 * INPUTS:
 * 	- uint8_t value: the brightness value for an LED or an unused value for timestamp and reset
 *
 * OUTPUTS:
 * 	- none
 */

#endif /* SOURCES_TRANSMISSION_H_ */
