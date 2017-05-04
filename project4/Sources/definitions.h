/*
 * definitions.h
 *
 *  Created on: Apr 30, 2017
 *      Author: jacob
 */

#ifndef SOURCES_DEFINITIONS_H_
#define SOURCES_DEFINITIONS_H_

#include <stdint.h>

// Define the maximum size for message data
#define MAX_DATA_SIZE 14

#define RED 0
#define GREEN 1
#define BLUE 2

void toggle_leds();

void red_on();
void blue_on();
void green_on();

void (* led_on[])() = {
		red_on,
		green_on,
		blue_on
};

void red_off();
void blue_off();
void green_off();

void (* led_off[])() = {
		red_off,
		green_off,
		blue_off
};

#endif /* SOURCES_DEFINITIONS_H_ */
