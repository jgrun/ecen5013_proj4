/*
 * uart.c
 *
 *  Created on: Feb 28, 2017
 *      Author: jacob
 */

#include "uart.h"

CircBuf TXBuf, RXBuf;

int32_t uart_init(void) {

	SIM_SOPT2 |= SIM_SOPT2_PLLFLLSEL(0);
	SIM_SOPT2 |= SIM_SOPT2_UART0SRC(1);
	SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;

	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;
	PORTA_PCR1 = PORT_PCR_MUX(2);
	PORTA_PCR2 = PORT_PCR_MUX(2);

	UART0_C2  = 0x00;
	UART0_C1  = 0x00;
	UART0_C3  = 0x00;
	UART0_C4  = 0x00;
	UART0_BDH = 0x00;
	UART0_BDL = 0x16;

    #ifdef __UART_INTERRUPTS
	if(UARTBufferInit(&TXBuf, DEFAULT_UARTBUF_SIZE) != 0)
		return -1;
	if(UARTBufferInit(&RXBuf, DEFAULT_UARTBUF_SIZE) != 0)
		return -1;
	UART0_C2 = UART0_C2_RIE_MASK;
	NVIC_EnableIRQ(UART0_IRQn);
    #endif

	UART0_C2 |= UART_C2_RE_MASK | UART0_C2_TE_MASK;
	return 0;
}


int32_t uart_send_byte(uint8_t data) {

    #ifdef __UART_INTERRUPTS
	while(UARTBufferFull(&TXBuf));
	if(UARTBufferAdd(&TXBuf, data) != 0) return -1;
	UART0_C2 |= UART0_C2_TIE_MASK;
	NVIC_EnableIRQ(UART0_IRQn);
	return 0;
    #endif

    #ifndef __UART_INTERRUPTS
	while(!(UART0_S1 & UART_S1_TDRE_MASK)); // wait for transmit buffer to empty
	UART0_D = data;
	return 0;
    #endif

}

int32_t uart_send_byte_n(uint8_t* data, uint32_t length) {

	uint32_t i;

	#ifdef __UART_INTERRUPTS
	for(i = 0; i < length; ++i){
		if(UARTBufferAdd(&TXBuf, *(data+i)) != 0)
			return -1;
	}
	if(length) UART0_C2 |= UART0_C2_TIE_MASK;
	#endif

	    #ifndef __UART_INTERRUPTS
	for(i = 0; i < length; ++i){
		if(uart_send_byte(data[i]) == -1)
			return -1;
	}
	    #endif
	return 0;

}

int32_t uart_receive_byte(uint8_t* buffer) {

	if(buffer == NULL) return 0;

    #ifdef __UART_INTERRUPTS
	while(UARTBufferEmpty(&RXBuf)); // wait for receive buffer to be full
	UARTBufferRemove(&RXBuf, buffer);
    #endif
    #ifndef __UART_INTERRUPTS
	while(!(UART0_S1 & UART_S1_RDRF_MASK)); // wait for receive buffer to be full
	*buffer = UART0_D;
    #endif
	return 0;
}

int32_t uart_receive_byte_n(uint8_t* buffer, uint32_t length) {

	uint32_t i;
	if(buffer == NULL) return -1;

	for(i = 0; i < length; ++i){
		uart_receive_byte(buffer + i);
	}
	return 0;
}

extern void UART0_IRQHandler(void){

	uint8_t data = 0;

	if(UART0_S1 & UART_S1_TDRE_MASK){
		if(UARTBufferCount(&TXBuf) >= 1){
			UARTBufferRemove(&TXBuf, &data);
			UART0_D = data;
		}
		else UART0_C2 &= ~UART0_C2_TIE_MASK;
	}
	if(UART0_S1 & UART_S1_RDRF_MASK){
		if(!UARTBufferFull(&RXBuf)){
			data = UART0_D;
			UARTBufferAdd(&RXBuf, data);
		}
	}
}
