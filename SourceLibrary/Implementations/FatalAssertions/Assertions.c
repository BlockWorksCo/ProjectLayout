



#include "Assertions.h"
#include "ErrorHandling.h"


//
//
//
void AssertThat( bool condition )
{
    if( condition == false )
    {
        PANIC();
    }
}



