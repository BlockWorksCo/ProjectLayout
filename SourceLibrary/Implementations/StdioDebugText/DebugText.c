


#include "DebugText.h"
#include <stdio.h>






void DebugTextOutput(const char* text)
{
    fprintf(stderr, "%s",text);
    fflush(stderr);
}




void DebugPrintf(const char* format, ...)
{
    static char     output[256];
    
    DebugTextOutput( &output[0] );
}





