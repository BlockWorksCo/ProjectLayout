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
    bool        discardable;

} BlockCacheElement;



uint8_t             blockDeviceData[1024*16];
BlockCacheElement   blockCache[BLOCKS_IN_CACHE]     =
{
    {.offset    = 0xffffffff, .discardable  = true},
    {.offset    = 0xffffffff, .discardable  = true},
    {.offset    = 0xffffffff, .discardable  = true},
    {.offset    = 0xffffffff, .discardable  = true},
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
// Search for a cache entry that is either unused or discardable and add the specified data
// in its place.
//
uint32_t AddToCache( uint32_t transactionID, uint32_t offset, uint8_t* data)
{
    uint32_t    blockOffset     = offset / BLOCK_SIZE;
    uint32_t    cacheIndex      = BLOCKS_IN_CACHE;


    for(uint32_t i=0; i<NUMBER_OF_ELEMENTS(blockCache); i++)
    {
        if( (blockCache[i].offset == 0xffffffff) || (blockCache[i].discardable == true) )
        {
            blockCache[i].offset            = blockOffset;
            blockCache[i].transactionID     = transactionID;
            blockCache[i].discardable       = true;
            memcpy( &blockCache[i].data[0], data, BLOCK_SIZE );

            cacheIndex  = i;
            break;
        }
    }

    return cacheIndex;    
}

#if 0
//
// Write all cache entries for the specified transaction that are *not* discardable to the device.
//
void FlushCache( uint32_t transactionID )
{
    for(uint32_t i=0; i<NUMBER_OF_ELEMENTS(blockCache); i++)
    {
        if( (blockCache[i].transactionID == transactionID) && (blockCache[i].discardable == false) )
        {
            //
            // Write to the device.
            //
            memcpy( &blockDeviceData[blockCache[i].offset], &blockCache[i].data[0], BLOCK_SIZE );

            blockCache[i].offset        = 0xffffffff;
            blockCache[i].discardable   = true;
            break;
        }
    }
}


#endif


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

        //
        // This cache entry is now not discardable as it needs syncing to FLASH.
        //
        blockCache[cacheIndex].discardable  = false;
    }
    else
    {
        //
        // Add it to the cache if we can...
        //
        cacheIndex     = AddToCache( transactionID, offset, data );
        if(cacheIndex != BLOCKS_IN_CACHE)
        {
            //
            // ...otherwise write thru to the device.
            //
            memcpy( &blockDeviceData[offset], data, numberOfBytes );
        }
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
        // Add it to the cache if we can, but mark it as discardable as this is not a dirty entry.
        //
        cacheIndex  = AddToCache( transactionID, offset, data );
        blockCache[cacheIndex].discardable  = true;
    }
}

