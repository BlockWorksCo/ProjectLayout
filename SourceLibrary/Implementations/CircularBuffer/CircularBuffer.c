//
// Copyright (C) BlockWorks Consulting Ltd - All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
// Written by Steve Tickle <Steve@BlockWorks.co>, September 2014.
//





#include "CircularBuffer.h"
#include "DebugText.h"



//
//
//
void CircularBufferShow( CircularBuffer* circularBuffer )
{
    DebugPrintf("first = %d\n", circularBuffer->first);
    DebugPrintf("last = %d\n", circularBuffer->last);
    DebugPrintf("elementSize = %d\n", circularBuffer->elementSize);
    DebugPrintf("numberOfElements = %d\n", circularBuffer->numberOfElements);
    DebugPrintf("elements = %p\n", circularBuffer->elements);
}


//
//
//
void CircularBufferInitialise( CircularBuffer* circularBuffer, uint32_t _elementSize, void* _elements, uint32_t _numberOfElements )
{
    circularBuffer->first               = 0;
    circularBuffer->last                = 0;
    circularBuffer->elementSize         = _elementSize;
    circularBuffer->elements            = _elements;
    circularBuffer->numberOfElements    = _numberOfElements;
}


//
//
//
void CircularBufferPut( CircularBuffer* circularBuffer, void* element )
{
    uint32_t    newLast     = (circularBuffer->last + 1) % circularBuffer->numberOfElements;

    //
    // Busy wait so we don't overwrite data.
    //
    while(circularBuffer->first == newLast)
    {
    }

    CircularBufferShow( circularBuffer );

    //
    // Copy data into the buffer.
    //
    uint32_t    offset      = circularBuffer->elementSize * newLast;
    uint8_t*    elements    = (uint8_t*)circularBuffer->elements;
    //memcpy( (void*)&elements[offset], element , circularBuffer->elementSize );

    //
    // Move the indices around.
    //
    circularBuffer->last   = newLast;
}


//
//
//
void CircularBufferGet( CircularBuffer* circularBuffer, void* element )
{
    //
    // Busy wait while no data in buffer.
    //
    while(circularBuffer->first == circularBuffer->last)
    {
    }

    //
    // Copy data out of the buffer.
    //
    uint32_t    offset      = circularBuffer->elementSize * circularBuffer->first;
    uint8_t*    elements    = (uint8_t*)circularBuffer->elements;
    memcpy( element,  (void*)&elements[offset] , circularBuffer->elementSize );

    //
    // Move the indices around.
    //
    circularBuffer->first   = (circularBuffer->first+1) % circularBuffer->numberOfElements;
}



