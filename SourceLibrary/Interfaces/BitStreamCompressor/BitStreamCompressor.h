//
// Copyright (C) BlockWorks Consulting Ltd - All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
// Written by Steve Tickle <Steve@BlockWorks.co>, September 2014.
//



#ifndef __BITSTREAMCOMPRESSOR_H__
#define __BITSTREAMCOMPRESSOR_H__


#include "Common.h"


#define MAX_BITSTREAM_DATA_SIZE                     (128)

//
//
//
typedef uint32_t    Timestamp;

//
//
//
typedef enum
{
    Uncompressed,
    InterEdgeOffsetCompressed,

} BitStreamPacketType;


//
// Definition of the temporary working data/context.
//
typedef struct
{
    Timestamp       timestamps[128];
    uint32_t        numberOfTimestamps;

} WorkingData;


//
//
//
typedef struct
{
    BitStreamPacketType     type;
    Timestamp               startTime;    
    bool                    initialState;
    Timestamp               minimumInterEdgeDuration;
    uint8_t                 numberOfBitsPerCompressedElement;
    uint32_t                numberOfCompressedElements;
    uint8_t                 compressedData[MAX_BITSTREAM_DATA_SIZE];

} BitStreamPacket;


//
//
//
void CompressedBitStreamInitialise( BitStreamPacket* packet, Timestamp now, bool currentState, WorkingData* workingData );
bool CompressedBitStreamAddEdge( BitStreamPacket* packet, uint32_t timestamp, WorkingData* workingData  );



#endif




