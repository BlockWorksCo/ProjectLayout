


#ifndef __SHAREDMEMORY_H__
#define __SHAREDMEMORY_H__


#include "Common.h"




volatile void* SharedMemoryMasterInitialise(uint32_t identifier);
volatile void* SharedMemorySlaveInitialise(uint32_t identifier);


#endif


