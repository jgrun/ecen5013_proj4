/*
 * commands.h
 *
 *  Created on: Apr 30, 2017
 *      Author: jacob
 */

#ifndef __COMMANDS_H__
#define __COMMANDS_H__
#include "state_machine.h"
#include "definitions.h"
#include "control.h"
#include "led.h"
#include "pwm.h"


void get_timestamp(command_t* cmd);

void reset_software(command_t* cmd);

void set_red(command_t* cmd);

void set_green(command_t* cmd);

void set_blue(command_t* cmd);

#endif
