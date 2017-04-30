/*
 * control.h
 *
 *  Created on: Apr 30, 2017
 *      Author: jacob
 */

#ifndef SOURCES_CONTROL_H_
#define SOURCES_CONTROL_H_

#include "definitions.h"

/* Only LED brightness needs to be controlled. If brightness is set to 0,
 * then the LED is off.
 */
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

typedef struct message_t {
	cmds command;
	uint8_t length; // length of entire struct in bytes
	uint8_t data[MAX_DATA_SIZE];
	uint8_t checksum; // XOR checksum
} message;


#endif /* SOURCES_CONTROL_H_ */
