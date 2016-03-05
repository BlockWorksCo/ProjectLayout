//
// Copyright (C) BlockWorks Consulting Ltd - All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
// Written by Steve Tickle <Steve@BlockWorks.co>, September 2014.
//


#include "BitStreamCompressor.h"
#include "Utilities.h"
#include "BitArray.h"


//
//
//
void CompressedBitStreamInitialise( BitStreamPacket* packet, Timestamp now, bool currentState, WorkingData* workingData )
{
    packet->type                                = InterEdgeOffsetCompressed;
    packet->startTime                           = now;
    packet->initialState                        = currentState;
    packet->minimumInterEdgeDuration            = 0;
    packet->numberOfBitsPerCompressedElement    = 32;
    packet->numberOfCompressedElements          = 0;

    workingData->numberOfTimestamps             = 0;
}


//
//
//
bool CompressedBitStreamAddEdge( BitStreamPacket* packet, uint32_t timestamp, WorkingData* workingData  )
{
    bool    packetIsComplete    = false;

    workingData->timestamps[workingData->numberOfTimestamps]   = timestamp;
    workingData->numberOfTimestamps++;
    if(workingData->numberOfTimestamps >= NUMBER_OF_ELEMENTS(workingData->timestamps) )
    {
        //
        // Find the minimum & maximum.
        //
        uint32_t    minimumDelta    = 0xffffffff;
        uint32_t    maximumDelta    = 0;
        for(uint32_t i=0; i<NUMBER_OF_ELEMENTS(workingData->timestamps); i++ )
        {
            uint32_t    timestampDelta;
            if(i == 0)
            {
                timestampDelta  = workingData->timestamps[i] - packet->startTime;
            }
            else
            {
                timestampDelta  = workingData->timestamps[i] - workingData->timestamps[i-1];
            }

            if(timestampDelta >= maximumDelta)
            {
                maximumDelta    = timestampDelta;
            }

            if(timestampDelta <= minimumDelta)
            {
                minimumDelta    = timestampDelta;
            }
        }

        //
        // Find the minimum number of bits to encode the range.
        //
        uint32_t    numberOfLeadingZeros            = __builtin_clz( minimumDelta );
        uint32_t    minimumNumberOfBitsForRange     = 32 - numberOfLeadingZeros;

        //
        // Encode the timestamps into the minimum number of bits into the packet data.
        //
        uint32_t    elementIndex    = 0;
        for(uint32_t i=0; i<NUMBER_OF_ELEMENTS(workingData->timestamps); i++ )
        {
            uint32_t    timestampDelta;
            if(i == 0)
            {
                timestampDelta  = workingData->timestamps[i] - packet->startTime;
            }
            else
            {
                timestampDelta  = workingData->timestamps[i] - workingData->timestamps[i-1];
            }



            elementIndex++;
        }

        packetIsComplete    = true;
    }

    return packetIsComplete;
}



