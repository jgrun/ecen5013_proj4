/*
 * commands.c
 *
 *  Created on: Apr 30, 2017
 *      Author: jacob
 */

#include "commands.h"

uint8_t red_pw = 255;
uint8_t green_pw = 255;
uint8_t blue_pw = 255;

void get_timestamp(uint8_t value) {

}

void reset_software(uint8_t value) {

}

// These will need some PWM stuff to actually do things
void set_red(uint8_t value) {
	red_pw = value;
}

void set_green(uint8_t value) {
	green_pw = value;
}

void set_blue(uint8_t value) {
	blue_pw = value;
}

void set_rgb(uint8_t red, uint8_t green, uint8_t blue) {
	set_red(red);
	set_green(green);
	set_blue(blue);
}

void set_rgb_hex(uint32_t rgb) {
	uint8_t red = (uint8_t)(rgb & 0x00ff0000) >> 16;
	uint8_t green = (uint8_t)(rgb & 0x0000ff00) >> 8;
	uint8_t blue = (uint8_t)(rgb & 0xff);
	set_rgb(red, green, blue);
}


