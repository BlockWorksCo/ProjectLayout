



#include "Assertions.h"
#include "ErrorHandling.h"


//
//
//
void AssertThat( bool condition, const char* message )
{
    if( condition == false )
    {
        PANIC();
    }
}



