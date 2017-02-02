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
    uint32_t            reserved1;
    uint32_t            reserved2;
    uint32_t            reserved3;
    volatile uint32_t    first;
    uint32_t            reserved4;
    uint32_t            reserved5;
    uint32_t            reserved6;
    uint32_t            reserved7;
    uint32_t            reserved8;
    uint32_t            reserved9;
    volatile uint32_t    last;
    uint32_t            reserved10;
    uint32_t            reserved11;
    uint32_t            reserved12;
    uint32_t            reserved13;
    volatile uint32_t    elementSize;
    volatile void*       readerElements;
    volatile void*       writerElements;
    volatile uint32_t    numberOfElements;
    volatile uint32_t    numberOfReaders;
    volatile uint32_t    numberOfWriters;

} CircularBuffer;


void CircularBufferInitialiseAsReader( CircularBuffer* circularBuffer, uint32_t _elementSize, void* _elements, uint32_t _numberOfElements );
void CircularBufferInitialiseAsWriter( CircularBuffer* circularBuffer, uint32_t _elementSize, void* _elements, uint32_t _numberOfElements );

void CircularBufferPut( CircularBuffer* circularBuffer, void* element );
void CircularBufferGet( CircularBuffer* circularBuffer, void* element );
void CircularBufferShow( CircularBuffer* circularBuffer );


#endif


