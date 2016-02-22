//
// Copyright (C) BlockWorks Consulting Ltd - All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
// Written by Steve Tickle <Steve@BlockWorks.co>, September 2014.
//




#ifndef __PERSISTENTSTORAGE_H__
#define __PERSISTENTSTORAGE_H__

#include "Common.h"
#include "EventQueue.h"



#define BLOCK_SIZE          (1024)
#define NUMBER_OF_BLOCKS    (128)



void WriteBlock( uint32_t address, uint8_t* data, uint32_t numberOfBytes, Handler completionHandler );
void ReadBlock( uint32_t address, uint8_t* data, uint32_t numberOfBytes, Handler completionHandler );
void EraseBlock( uint32_t address, Handler completionHandler );
void EraseDevice( Handler completionHandler );

#endif



