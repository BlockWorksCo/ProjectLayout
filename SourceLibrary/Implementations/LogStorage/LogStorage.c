//
// Copyright (C) BlockWorks Consulting Ltd - All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
// Written by Steve Tickle <Steve@BlockWorks.co>, September 2014.
//


#include "LogStorage.h"
#include "FileStorage.h"

#define LOG_ENTRY_SIZE      (128)
#define LOG_FILE_NUMBER     (1)

uint32_t    lastEntry   = 0xffffffff;


//
// FindLastEntry state machine.
//
uint32_t    FindLastEntryReadAddress       = 0;
Handler     FindLastEntryCompletionEvent   = 0;
uint8_t     FindLastEntryLogEntry          = {0};

void FindLastEntryReadComplete()
{
    FindLastEntryReadAddress    += LOG_ENTRY_SIZE;
    ReadFileBlock( LOG_FILE_NUMBER, FindLastEntryReadAddress, &FindLastEntryLogEntry, LOG_ENTRY_SIZE, FindLastEntryReadComplete );
}

uint32_t FindLastEntry( Handler completionHandler )
{
    FindLastEntryCompletionEvent    = completionHandler;
    if(lastEntry == 0xffffffff)
    {
        FindLastEntryReadAddress    = 0;
        ReadFileBlock( LOG_FILE_NUMBER, FindLastEntryReadAddress, &FindLastEntryLogEntry, LOG_ENTRY_SIZE, FindLastEntryReadComplete );
    }
    else
    {
        Call( completionHandler );
    }

    return lastEntry;
}


//
// WriteLog state machine.
//
uint8_t*    WriteLogLogEntry            = 0;
Handler     WriteLogCompletionHandler   = 0;

void WriteLogLastEntryAvailable()
{
    uint32_t    address     = lastEntry;
    WriteFileBlock( LOG_FILE_NUMBER, address, WriteLogLogEntry, LOG_ENTRY_SIZE, WriteLogCompletionHandler );
}

void WriteLog( uint8_t* data, Handler completionHandler )
{
    WriteLogLogEntry    = data;
    WriteLogCompletionHandler   = completionHandler;
    FindLastEntry( WriteLogLastEntryAvailable );
}


//
// ReadLog state machine.
//
uint8_t*    ReadLogLogEntry             = 0;
Handler     ReadLogCompletionHandler    = 0;

void ReadLogLastEntryAvailable()
{
    uint32_t    address     = lastEntry+1;
    ReadFileBlock( LOG_FILE_NUMBER, address, ReadLogLogEntry, LOG_ENTRY_SIZE, ReadLogCompletionHandler );
}

void ReadLog( uint8_t* data, Handler completionHandler )
{
    ReadLogLogEntry             = data;
    ReadLogCompletionHandler    = completionHandler;
    FindLastEntry( ReadLogLastEntryAvailable );
}
