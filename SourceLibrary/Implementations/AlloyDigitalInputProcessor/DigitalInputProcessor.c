//
// Copyright (C) BlockWorks Consulting Ltd - All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
// Written by Steve Tickle <Steve@BlockWorks.co>, November 2015.
//


#include "DigitalInputProcessor.h"
#include "HighResolutionTimestamp.h"
#include "Common.h"


//
//
//
typedef struct
{
    uint32_t    inputs;
    uint32_t    timestamp;

} InputQueueElement;

uint32_t GetInputs();
void InputQueueAdd( InputQueueElement* element );


//
//
//
void ProcessDigitalInputs()
{
    //
    // Sample *all* digital input lines.
    //
    uint32_t            timestamp           = GetHighResolutionTimestamp();
    uint32_t            rawInputs           = GetInputs();
    static uint32_t     previousRawInputs   = 0x00000000;

    //
    // Delta detection.
    //
    if( rawInputs != previousRawInputs )
    {
        //
        // If we have a change, add it to the queue.
        //
        InputQueueElement   element     =
        {
            .inputs     = rawInputs,
            .timestamp  = timestamp,
        };
        InputQueueAdd( &element );
    }

    //
    // Store the current values as the previous values for the next iteration.
    //
}


