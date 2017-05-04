/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "MKL25Z4.h"
#include "definitions.h"
#include "control.h"
#include "commands.h"
#include "transmission.h"


// red PTB18
// green PTB19
// blue PTD1

extern uint8_t red_pw;
extern uint8_t green_pw;
extern uint8_t blue_pw;

// Holds count from timer
uint8_t count;

int main(void) {

	message m;
	uint8_t data[MAX_DATA_SIZE];
	int i = 0;
	for(i; i < 16; i++) {
		data[i] = i;
	}
	data[1] = 16;
	decode_message(&m, data, 16);
	while(1) {
		toggle_leds();
	}

}

void toggle_leds() {
	if(count >= red_pw) (led_on[RED])();
	else (led_off[RED])();
	if(count >= green_pw) (led_on[GREEN])();
	else (led_off[GREEN])();
	if(count >= blue_pw) (led_on[BLUE])();
	else (led_off[BLUE])();
}

void red_on() {
	return;
}

void blue_on() {
	return;
}

void green_on() {
	return;
}

void red_off() {
	return;
}

void blue_off() {
	return;
}

void green_off() {
	return;
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
