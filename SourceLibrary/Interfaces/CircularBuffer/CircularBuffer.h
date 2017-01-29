//
// Copyright (C) BlockWorks Consulting Ltd - All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
// Written by Steve Tickle <Steve@BlockWorks.co>, September 2014.
//




#ifndef __CIRCULARBUFFER_H__
#define __CIRCULARBUFFER_H__



#include "Common.h"


typedef struct
{
    volatile uint32_t    first;
    volatile uint32_t    last;
    volatile uint32_t    elementSize;
    volatile void*       elements;
    volatile uint32_t    numberOfElements;

} CircularBuffer;


void CircularBufferInitialise( CircularBuffer* circularBuffer, uint32_t _elementSize, void* _elements, uint32_t _numberOfElements );
void CircularBufferPut( CircularBuffer* circularBuffer, void* element );
void CircularBufferGet( CircularBuffer* circularBuffer, void* element );
void CircularBufferShow( CircularBuffer* circularBuffer );


#endif


