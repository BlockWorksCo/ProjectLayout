//
// Copyright (C) BlockWorks Consulting Ltd - All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
// Written by Steve Tickle <Steve@BlockWorks.co>, September 2014.
//




#ifndef __FILESTORAGE_H__
#define __FILESTORAGE_H__


#include "Common.h"
#include "EventQueue.h"

void WriteFileBlock( uint8_t fileNumber, uint32_t address, uint8_t* data, uint32_t numberOfBytes, Handler completionHandler );
void ReadFileBlock( uint8_t fileNumber, uint32_t address, uint8_t* data, uint32_t numberOfBytes, Handler completionHandler );
void EraseFileBlock( uint8_t fileNumber, uint32_t address, Handler completionHandler );

#endif



