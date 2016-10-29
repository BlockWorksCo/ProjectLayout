



#include "Assertions.h"
#include "DebugText.h"


//
//
//
void AssertThat( bool condition, const char* message  )
{
    if( condition == false )
    {
        DebugPrintf("\n*** ASSERTION FAILURE: %s ***\n", message );
    }
}



