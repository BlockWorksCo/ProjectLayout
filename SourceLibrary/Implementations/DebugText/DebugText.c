


#include "DebugText.h"






void DebugTextOutput(const char* text)
{

}




void DebugPrintf(const char* format, ...)
{
    static char     output[256];
    
    DebugTextOutput( &output[0] );
}





