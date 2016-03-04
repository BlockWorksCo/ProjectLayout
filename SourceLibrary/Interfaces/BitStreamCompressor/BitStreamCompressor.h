

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
//
//
typedef struct
{
    BitStreamPacketType     type;
    Timestamp               startTime;    
    bool                    initialState;
    Timestamp               minimumInterEdgeDuration;
    uint8_t                 numberOfBitsPerCompressedElement;
    uint8_t                 compressedData[MAX_BITSTREAM_DATA_SIZE];

} BitStream;


//
//
//
void CompressedBitStreamInitialise();
void CompressedBitStreamAddEdge( uint32_t timestamp );



#endif




