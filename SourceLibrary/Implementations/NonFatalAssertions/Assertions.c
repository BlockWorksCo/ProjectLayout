



#include "Assertions.h"
#include "DebugText.h"
#include <stdio.h>


//
//
//
void AssertThat( bool condition, const char* message, ...  )
{
    if( condition == false )
    {
        static char     output[256];
        va_list         list;

        va_start( list, message );     
        vsnprintf( &output[0], sizeof(output), message, list );
        va_end(list);

        DebugTextOutput( "\n*** ASSERTION FAILURE: " );
        DebugTextOutput( &output[0] );
        DebugTextOutput( " ***\n" );
    }
}



