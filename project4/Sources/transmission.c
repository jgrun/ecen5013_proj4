/*
 * transmission.c
 *
 *  Created on: Apr 30, 2017
 *      Author: jacob
 */

#include "transmission.h"

void send_message(message * m) {
	uint8_t length = m->length; // Store length
	uint64_t bits = (uint64_t)(length - 1) * 8;
	uint8_t check;
	uint64_t j;
	for(j = 0; j < bits; j++) {
		check ^= ((*(uint8_t *) (m + (j/8)) >> j) & 1); // Bitwise XOR the message to generate checksum
	}
	m->checksum = check;
	uint8_t i;
	for(i = 0; i < length; i++) {
	//	uart_send(*(uint8_t *)(m + i)); // transmit m byte by byte
	}
}

uint8_t valid_message(message * m) {
	uint64_t bits = (uint64_t)(m->length - 1) * 8;
	uint64_t j;
	uint8_t check;
	for(j = 0; j < bits; j++) {
		check ^= ((*(uint8_t *) (m + (j/8)) >> j) & 1); // Bitwise XOR the message to generate checksum
	}
	if(check == m->checksum) return 1;
	return 0;
}

void decode_message(message * m, uint8_t * data, uint8_t length) {
	uint8_t i = 0;
	m->command = *(data);
	m->length = *(data + 1);
	uint8_t lenth = m->length - 3;
	for(i = 0; i < lenth; i++) {
		*(m->data + i) = *(data + 2 + i);
	}
	m->checksum = *(data + m->length - 1);
}

void (* execute_command[])(uint8_t value) = {
	get_timestamp,
	reset_software,
	set_red,
	set_green,
	set_blue
};

