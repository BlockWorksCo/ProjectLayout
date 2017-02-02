//
// Copyright (C) BlockWorks Consulting Ltd - All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
// Written by Steve Tickle <Steve@BlockWorks.co>, September 2014.
//





#include "CircularBuffer.h"
#include "DebugText.h"


#define ISB	__asm__ volatile ("mcr     p15, 0, %0, c7, c5, 4" : : "r" (0))
#define DSB	__asm__ volatile ("mcr     p15, 0, %0, c7, c10, 4" : : "r" (0))
#define DMB	__asm__ volatile ("mcr     p15, 0, %0, c7, c10, 5" : : "r" (0))

//
//
//
void CircularBufferShow( CircularBuffer* circularBuffer )
{
    DebugPrintf("first = %d\n", circularBuffer->first);
    DebugPrintf("last = %d\n", circularBuffer->last);
    DebugPrintf("elementSize = %d\n", circularBuffer->elementSize);
    DebugPrintf("numberOfElements = %d\n", circularBuffer->numberOfElements);
    DebugPrintf("readerElements = %p\n", circularBuffer->readerElements);
    DebugPrintf("writerElements = %p\n", circularBuffer->writerElements);
}


//
//
//
void CircularBufferInitialiseAsReader( CircularBuffer* circularBuffer, uint32_t _elementSize, void* _elements, uint32_t _numberOfElements )
{
    circularBuffer->first               = 0;
    circularBuffer->last                = 0;
    circularBuffer->elementSize         = _elementSize;
    circularBuffer->readerElements      = _elements;
    circularBuffer->numberOfElements    = _numberOfElements;

    memset( (void*)circularBuffer->readerElements, 0xff, circularBuffer->elementSize*circularBuffer->numberOfElements );

    circularBuffer->numberOfReaders++;

    //CircularBufferShow( circularBuffer );
}


//
//
//
void CircularBufferInitialiseAsWriter( CircularBuffer* circularBuffer, uint32_t _elementSize, void* _elements, uint32_t _numberOfElements )
{
    circularBuffer->first               = 0;
    circularBuffer->last                = 0;
    circularBuffer->elementSize         = _elementSize;
    circularBuffer->writerElements      = _elements;
    circularBuffer->numberOfElements    = _numberOfElements;

    memset( (void*)circularBuffer->writerElements, 0xff, circularBuffer->elementSize*circularBuffer->numberOfElements );

    circularBuffer->numberOfWriters++;

    //CircularBufferShow( circularBuffer );
}


//
//
//
void CircularBufferPut( CircularBuffer* circularBuffer, void* element )
{
    volatile uint32_t    newLast     = (circularBuffer->last + 1) % circularBuffer->numberOfElements;

    //
    // Busy wait so we don't overwrite data.
    //
    DSB;
    DMB;
    while(circularBuffer->first == newLast)
    {
    }
    DSB;
    DMB;

    //
    // Copy data into the buffer.
    //
    uint32_t    offset      = circularBuffer->elementSize * circularBuffer->last;
    uint8_t*    elements    = (uint8_t*)circularBuffer->writerElements;
    memcpy( (void*)&elements[offset] , element , circularBuffer->elementSize );

    //
    // Move the indices around.
    //
    circularBuffer->last   = newLast;
    DSB;
    DMB;
}


//
//
//
void CircularBufferGet( CircularBuffer* circularBuffer, void* element )
{
    volatile uint32_t    newFirst    = (circularBuffer->first+1) % circularBuffer->numberOfElements;

    //
    // Busy wait while no data in buffer.
    //
    DMB;
    DSB;
    while(circularBuffer->first == circularBuffer->last)
    {
    }
    DMB;
    DSB;

    //CircularBufferShow( circularBuffer );

    //
    // Copy data out of the buffer.
    //
    uint32_t    offset      = circularBuffer->elementSize * circularBuffer->first;
    uint8_t*    elements    = (uint8_t*)circularBuffer->readerElements;
    memcpy( element,  (void*)&elements[offset] , circularBuffer->elementSize );

    //
    // Move the indices around.
    //
    circularBuffer->first   = newFirst;
    DMB;
    DSB;
}



