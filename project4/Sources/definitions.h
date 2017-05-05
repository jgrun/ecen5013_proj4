/*
 * definitions.h
 *
 *  Created on: Apr 30, 2017
 *      Author: jacob
 */

#ifndef SOURCES_DEFINITIONS_H_
#define SOURCES_DEFINITIONS_H_

// Define the maximum size for message data
#define MAX_DATA_SIZE 14
// enable UART for interrupt based mode instead of polling based
#define __UART_INTERRUPTS
// maximum number of characters uart buffer can hold
#define DEFAULT_UARTBUF_SIZE 64

#endif /* SOURCES_DEFINITIONS_H_ */
