#include "uartbuf.h"

int32_t UARTBufferInit(CircBuf* CB, uint32_t size){

	if(!CB) return -1;
	if(size == 0) return -1;
	CB->buffer = (uint8_t*)malloc(sizeof(uint8_t) * size);
	if(!(CB->buffer)) return -1;
	CB->head = CB->buffer;
	CB->tail = CB->buffer;
	CB->length = size;
	CB->count = 0;
	return 0;
}

int32_t UARTBufferAdd(CircBuf* CB, uint8_t item){

	uint8_t* temp_ptr;

	if(!CB || !CB->buffer || CB->count == CB->length) return -1;

	if(CB->count > 0)
		CB->head = ((uint8_t*)CB->head < (uint8_t*)CB->buffer + CB->length - 1 ? ((uint8_t*)CB->head) + 1 : CB->buffer);

	temp_ptr = (uint8_t*)CB->head;
	*temp_ptr = item;
	(CB->count)++;
	return 0;
}


int32_t UARTBufferRemove(CircBuf* CB, uint8_t* item){

	if(!CB || !CB->buffer || !CB->count) return -1;

	if(CB->count == 1){ // return to empty state
		if(item) *item = *((uint8_t*)CB->tail);
		CB->tail = CB->buffer;
		CB->head = CB->buffer;
		CB->count = 0;
		return 0;
	}

	if(item) *item = *((uint8_t*)CB->tail);
	CB->tail = (((uint8_t*)CB->tail) < ((uint8_t*)CB->buffer) + CB->length - 1 ? ((uint8_t*)CB->tail) + 1 : CB->buffer);
	(CB->count)--;
	return 0;
}

int32_t UARTBufferFull(CircBuf* CB){
	return (CB->count == CB->length);
}

int32_t UARTBufferEmpty(CircBuf* CB){
	return (CB->count == 0);
}

uint32_t UARTBufferCount(CircBuf* CB){
	return CB->count;
}

int32_t UARTBufferPeek(CircBuf* CB, uint8_t* item_n, uint32_t n){
// returns nth oldest item
	if(!CB || !item_n || !CB->buffer || n > CB->count || n < 1) return -1;
	*item_n = (((uint8_t*)CB->tail) + n - 1 > ((uint8_t*)CB->buffer) + (CB->length - 1) ?
			*((uint8_t*)(CB->tail - CB->length + n - 1)) : *(((uint8_t*)CB->tail) + n - 1));
	return 0;
}

int32_t UARTBufferDestroy(CircBuf* CB){

	if(!CB || !(CB->buffer)) return -1;
	free(CB->buffer);
	CB->length = 0;
	CB->count = 0;
	CB->head = NULL;
	CB->tail = NULL;
	CB->buffer = NULL;
	return 0;
}
