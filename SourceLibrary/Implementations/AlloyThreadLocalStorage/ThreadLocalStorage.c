


#include "ThreadLocalStorage.h"
#include "BoardSupport.h"


extern GlobalData              globals[NUMBER_OF_CORES];



//
//
//
//GlobalData              globals[NUMBER_OF_CORES];
//CoreServicesBridge*     bridge                      = (CoreServicesBridge*)BRIDGE_BASE;




//
//
//
GlobalData* Globals()
{
    uint32_t    coreID              = CoreNumber();

    return &globals[coreID];
}

