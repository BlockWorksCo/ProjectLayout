//
// Copyright (C) BlockWorks Consulting Ltd - All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
// Written by Steve Tickle <Steve@BlockWorks.co>, September 2014.
//



#include "FileStorage.h"
#include "PersistentStorage.h"

uint32_t fileMap[]  =
{
    0,
    1,
    10,
    30,
    40,
};

void WriteFileBlock( uint8_t fileNumber, uint32_t address, uint8_t* data, uint32_t numberOfBytes, Handler completionHandler )
{
    WriteBlock( (fileMap[fileNumber]*BLOCK_SIZE)+address, data, numberOfBytes, completionHandler );
}

void ReadFileBlock( uint8_t fileNumber, uint32_t address, uint8_t* data, uint32_t numberOfBytes, Handler completionHandler )
{
    ReadBlock( (fileMap[fileNumber]*BLOCK_SIZE)+address, data, numberOfBytes, completionHandler );
}

void EraseFileBlock( uint8_t fileNumber, uint32_t address, Handler completionHandler )
{
    EraseBlock( (fileMap[fileNumber]*BLOCK_SIZE)+address, completionHandler );
}


