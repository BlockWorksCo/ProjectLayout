


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





