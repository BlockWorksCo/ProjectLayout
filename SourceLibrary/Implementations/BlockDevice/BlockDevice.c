//
// Copyright (C) BlockWorks Consulting Ltd - All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
// Written by Steve Tickle <Steve@BlockWorks.co>, September 2014.
//




#include "BlockDevice.h"



uint8_t             blockDeviceData[1024*16];


//
//
//
void WriteToBlockDeviceRegion( uint32_t transactionID, uint32_t offset, uint8_t* data, uint32_t numberOfBytes )
{
    memcpy( &blockDeviceData[offset], data, numberOfBytes );
}


//
//
//
void ReadFromBlockDeviceRegion( uint32_t transactionID, uint32_t offset, uint8_t* data, uint32_t numberOfBytes )
{
    memcpy( data, &blockDeviceData[offset], numberOfBytes );
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

}



