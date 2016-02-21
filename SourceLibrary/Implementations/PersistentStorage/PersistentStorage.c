//
// Copyright (C) BlockWorks Consulting Ltd - All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
// Written by Steve Tickle <Steve@BlockWorks.co>, September 2014.
//




#include <string.h>
#include "PersistentStorage.h"




uint8_t     simulatedFLASH[BLOCK_SIZE*NUMBER_OF_BLOCKS];

void WriteBlock( uint32_t address, uint8_t* data, uint32_t numberOfBytes, Handler completionHandler )
{
    memcpy( &simulatedFLASH[address], data, numberOfBytes );

    Call( completionHandler );
}

void ReadBlock( uint32_t address, uint8_t* data, uint32_t numberOfBytes, Handler completionHandler )
{
    memcpy( data, &simulatedFLASH[address], numberOfBytes );    
    
    Call( completionHandler );
}

void EraseBlock( uint32_t address, Handler completionHandler )
{
    uint32_t    blockNumber     = address / BLOCK_SIZE;
    memset( &simulatedFLASH[blockNumber*BLOCK_SIZE], 0xff, BLOCK_SIZE );
    
    Call( completionHandler );
}

void EraseDevice( Handler completionHandler )
{
    memset( &simulatedFLASH[0], 0xff, sizeof(simulatedFLASH) );
    
    Call( completionHandler );
}
