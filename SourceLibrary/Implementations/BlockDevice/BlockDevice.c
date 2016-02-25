//
// Copyright (C) BlockWorks Consulting Ltd - All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
// Written by Steve Tickle <Steve@BlockWorks.co>, September 2014.
//




#include "BlockDevice.h"
#include "Utilities.h"



#define BLOCK_SIZE          (256)
#define BLOCKS_IN_CACHE     (4)

typedef struct
{
    uint8_t     data[BLOCK_SIZE];
    uint32_t    transactionID;
    uint32_t    offset;

} BlockCacheElement;



uint8_t             blockDeviceData[1024*16];
BlockCacheElement   blockCache[BLOCKS_IN_CACHE]     =
{
    {.offset    = 0xffffffff},
    {.offset    = 0xffffffff},
    {.offset    = 0xffffffff},
    {.offset    = 0xffffffff},
};




//
//
//
uint32_t CacheBlockForOffset( uint32_t offset )
{
    uint32_t    blockOffset     = offset / BLOCK_SIZE;
    uint32_t    cacheIndex      = BLOCKS_IN_CACHE;

    for(uint32_t i=0; i<NUMBER_OF_ELEMENTS(blockCache); i++)
    {
        if( blockCache[i].offset == blockOffset )
        {
            cacheIndex  = i;
            break;
        }
    }

    return cacheIndex;
}

//
//
//

uint32_t AddToCache( uint32_t transactionID, uint32_t offset, uint8_t* data)
{
    uint32_t    blockOffset     = offset / BLOCK_SIZE;
    uint32_t    cacheIndex      = BLOCKS_IN_CACHE;

    for(uint32_t i=0; i<NUMBER_OF_ELEMENTS(blockCache); i++)
    {
        if( blockCache[i].offset == 0xffffffff )
        {
            blockCache[i].offset            = blockOffset;
            blockCache[i].transactionID     = transactionID;
            memcpy( &blockCache[i].data[0], data, BLOCK_SIZE );

            cacheIndex  = i;
            break;
        }
    }

    return cacheIndex;    
}


//
//
//
void FlushCache( uint32_t transactionID )
{
    for(uint32_t i=0; i<NUMBER_OF_ELEMENTS(blockCache); i++)
    {
        if( blockCache[i].transactionID == transactionID )
        {
            //
            // Write to the device.
            //
            memcpy( &blockDeviceData[blockCache[i].offset], &blockCache[i].data[0], BLOCK_SIZE );

            blockCache[i].offset    = 0xffffffff;
            break;
        }
    }
}



//
//
//
void WriteToBlockDeviceRegion( uint32_t transactionID, uint32_t offset, uint8_t* data, uint32_t numberOfBytes )
{
    uint32_t    cacheIndex  = CacheBlockForOffset(offset);
    if(cacheIndex != BLOCKS_IN_CACHE)
    {
        //
        // Write to the cache only.
        //
        memcpy( &blockCache[cacheIndex].data[0], data, numberOfBytes );

    }
    else
    {
        //
        // Write thru to the device.
        //
        memcpy( &blockDeviceData[offset], data, numberOfBytes );

        //
        // Add it to the cache if we can.
        //
        AddToCache( transactionID, offset, data );
    }

}


//
//
//
void ReadFromBlockDeviceRegion( uint32_t transactionID, uint32_t offset, uint8_t* data, uint32_t numberOfBytes )
{
    uint32_t    cacheIndex  = CacheBlockForOffset(offset);
    if(cacheIndex != BLOCKS_IN_CACHE)
    {
        //
        // Read from the cache only.
        //
        memcpy( data, &blockCache[cacheIndex].data[0], numberOfBytes );
    }
    else
    {
        //
        // Read from the device.
        //
        memcpy( data, &blockDeviceData[offset], numberOfBytes );

        //
        // Add it to the cache if we can.
        //
        AddToCache( transactionID, offset, data );
    }
}






//
//
//
uint32_t StartTransaction( TransactionType type )
{
    static uint32_t     transactionIDCounter     = 0;

    transactionIDCounter++;

    return transactionIDCounter;
}


//
//
//
void EndTransaction( uint32_t transactionID )
{
    FlushCache( transactionID );
}



