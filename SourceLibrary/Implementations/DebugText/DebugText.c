


#include "DebugText.h"






void DebugTextOutput(const char* text)
{

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



