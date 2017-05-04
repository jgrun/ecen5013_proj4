#include "memory.h"

int32_t my_memmove(uint8_t* src, uint8_t* dst, uint32_t length)
{

	uint32_t i;
	if( !src || !dst ) return -1;

	if(src > dst)
	{
		for(i = 0; i < length; ++i)
			*(dst + i) = *(src + i);
	}
	else if(src < dst)
	{
		for(i = length; i > 0; --i)
			*(dst + i - 1) =  *(src + i - 1);
	}
	return 0;

}
int32_t my_memset(uint8_t* src, uint32_t length, uint8_t value)
{
	uint32_t i;
	if( !src ) return -1;

	for(i = 0; i < length; ++i)
		*(src + i) = value;

	return 0;
}

int32_t my_memzero(uint8_t* src, uint32_t length)
{
	uint32_t i;
	if( !src ) return -1;

	for(i = 0; i < length; ++i)
		*(src + i) = 0;

	return 0;
}

int32_t my_reverse(uint8_t* src, uint32_t length)
{
	if( !src ) return -1;
    uint32_t i;
	uint8_t temp;

	for(i = 0; i < length >> 1; ++i)
	{
		temp = src[i];
		*(src + i)= *(src + length - 1 - i);
		*(src + length -1 - i) = temp;
	}
	return 0;
}
