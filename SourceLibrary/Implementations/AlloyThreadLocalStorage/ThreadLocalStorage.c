


#include "ThreadLocalStorage.h"
#include "Alloy.h"


extern GlobalData              globals[NUMBER_OF_CORES];
uint32_t MPIDR();

//
//
//
GlobalData* Globals()
{
    uint32_t    coreID              = MPIDR();

    return &globals[coreID];
}



