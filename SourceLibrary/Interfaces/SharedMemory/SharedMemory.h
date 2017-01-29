


#ifndef __SHAREDMEMORY_H__
#define __SHAREDMEMORY_H__


#include "Common.h"




void* SharedMemoryMasterInitialise(uint32_t identifier);
void* SharedMemorySlaveInitialise(uint32_t identifier);


#endif


