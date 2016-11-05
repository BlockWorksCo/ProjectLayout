//
// Copyright (C) BlockWorks Consulting Ltd - All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
// Written by Steve Tickle <Steve@BlockWorks.co>, September 2014.
//



#include "DebugText.h"
#include "BoardSupport.h"
#include "Alloy.h"





//
//
//
void DebugTextOutput(const char* text)
{
    uint32_t    coreID  = CoreNumber();

    SystemCall  systemCall  = 
    {
        .type           = 0x00000001,
        .payload        = (uint32_t)text,
        .processedFlag  = false,
    };

    bridge->coreMessages[0][coreID].type    = 123;
    bridge->coreMessages[0][coreID].payload = (uint32_t)&systemCall;
    FlushCache();
    TriggerMailboxInterrupt(0);            

    while( systemCall.processedFlag == false );    
}




void DebugPrintf(const char* format, ...)
{
    static char     output[256];
    
    DebugTextOutput( &output[0] );
}






void DebugHexDumpBytes( const uint8_t* data, uint32_t numberOfBytes )
{

}

void DebugHexDumpWords( const uint8_t* data, uint32_t numberOfBytes )
{

}

