


#include "DebugText.h"
#include <stdio.h>
#include <stdarg.h>





void DebugTextOutput(const char* text)
{
    fprintf(stderr, "%s",text);
    fflush(stderr);
}




void DebugPrintf(const char* format, ...)
{
    static char     output[256];
    va_list         list;

    va_start( list, format );     
    vsnprintf( &output[0], sizeof(output), format, list );
    va_end(list);

    DebugTextOutput( &output[0] );
}


char NibbleToHex( uint8_t nibble )
{
    if(nibble<10)
    {
        return '0'+nibble;
    }
    else
    {
        return 'A'+(nibble-10);
    }
}

void DebugHexDumpBytes( const uint8_t* data, uint32_t numberOfBytes )
{
    for(uint32_t i=0; i<numberOfBytes; i++)
    {
        char    text[4]     = {0};
        text[0]     = NibbleToHex( (data[i] & 0x0f)>>4 );
        text[1]     = NibbleToHex( data[i] & 0x0f );
        text[2]     = ' ';
        text[3]     = 0;
        DebugTextOutput( &text[0] );
    }
    DebugTextOutput( "\n" );
}

void DebugHexDumpWords( const uint8_t* data, uint32_t numberOfBytes )
{

}



