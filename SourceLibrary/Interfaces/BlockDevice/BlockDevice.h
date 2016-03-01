//
// Copyright (C) BlockWorks Consulting Ltd - All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
// Written by Steve Tickle <Steve@BlockWorks.co>, September 2014.
//



#ifndef __BLOCKDEVICE_H__
#define __BLOCKDEVICE_H__



#include "Common.h"


//
//
//
typedef enum
{
    DoSomething,
    
} TransactionType;


//
//
//
typedef enum
{
    EntireDevice,

} BlockDeviceRegion;


//
//
//
void WriteToBlockDeviceRegion( uint32_t transactionID, uint32_t offset, uint8_t* data, uint32_t numberOfBytes );
void ReadFromBlockDeviceRegion( uint32_t transactionID, uint32_t offset, uint8_t* data, uint32_t numberOfBytes );

uint32_t StartTransaction( TransactionType type );
void EndTransaction( uint32_t transactionID );

#endif

