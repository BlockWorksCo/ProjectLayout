

#ifndef __BITARRAY_H__
#define __BITARRAY_H__

#include "Common.h"



void BitArraySet( uint8_t* data, uint8_t elementWidth, uint32_t index, uint32_t value );
void BitArrayGet( uint8_t* data, uint8_t elementWidth, uint32_t index, uint32_t* value );


#endif


