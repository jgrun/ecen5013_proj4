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
#include "led.h"
#include "pwm.h"
#include "uart.h"
#include "memory.h"
#include "data.h"
#include "timer.h"
#include "state_machine.h"
state_machine_t state_machine[] = {read_command,
								   decode_command,
								   execute_command};

current_state_t current_state = read_state;

int main(void) {

	command_t cmd;
	uint32_t t, i;
	led_init();
	pwm_init();
	uart_init();
	systick_init();
	__enable_irq();
	while(1) {
		switch(current_state){
		case read_state:
			if(state_machine[read_state](&cmd) == 0)
				current_state = decode_state;
			break;
		case decode_state:
			if(state_machine[decode_state](&cmd) == 0)
				current_state = execute_state;
			else
				current_state = read_state;
			break;
		case execute_state:
			state_machine[execute_state](&cmd);
			current_state = read_state;
			break;
		}
	}

}
