



#include "Assertions.h"
#include "DebugText.h"


//
//
//
void AssertThat( bool condition )
{
    if( condition == false )
    {
        DebugPrintf("\n*** ASSERTION FAILURE ***\n");
    }
}



