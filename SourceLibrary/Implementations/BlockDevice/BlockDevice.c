//
// Copyright (C) BlockWorks Consulting Ltd - All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
// Written by Steve Tickle <Steve@BlockWorks.co>, September 2014.
//




#include "BlockDevice.h"
#include "Utilities.h"
#include "ErrorHandling.h"




uint8_t             blockDeviceData[1024*16];





//
// Initialise the BlockDevice driver.
//
void BlockDeviceInitialise()
{
    memset( &blockDeviceData[0], 0xff, sizeof(blockDeviceData) );
}



//
//
//
void WriteToBlockDeviceRegion( uint32_t offset, uint8_t* data, uint32_t numberOfBytes )
{
    if( offset >= sizeof(blockDeviceData) )
    {
        PANIC();
    }

    if( offset+numberOfBytes >= sizeof(blockDeviceData) )
    {
        PANIC();
    }

    //
    // ...otherwise write thru to the device.
    //
    memcpy( &blockDeviceData[offset], data, numberOfBytes );
}


//
//
//
void ReadFromBlockDeviceRegion( uint32_t offset, uint8_t* data, uint32_t numberOfBytes )
{
    if( offset >= sizeof(blockDeviceData) )
    {
        PANIC();
    }

    if( offset+numberOfBytes >= sizeof(blockDeviceData) )
    {
        PANIC();
    }

    //
    // Read from the device.
    //
    memcpy( data, &blockDeviceData[offset], numberOfBytes );
}

