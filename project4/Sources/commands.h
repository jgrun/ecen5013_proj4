/*
 * commands.h
 *
 *  Created on: Apr 30, 2017
 *      Author: jacob
 */

#ifndef __COMMANDS_H__
#define __COMMANDS_H__

#include "definitions.h"
#include "control.h"

#define RED_LED 1 << 18
#define GREEN_LED 1 << 19
#define BLUE_LED 1 << 1

void get_timestamp(uint8_t value);

void reset_software(uint8_t value);

void set_red(uint8_t value);

void set_green(uint8_t value);

void set_blue(uint8_t value);

void set_rgb(uint8_t red, uint8_t green, uint8_t blue);

void set_rgb_hex(uint32_t rgb);

#endif
