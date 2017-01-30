



#include "Common.h"
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "SharedMemory.h"
#include "ErrorHandling.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>


const int       SIZE = 1024*1024;


//
//
//
volatile void* SharedMemoryMasterInitialise(uint32_t identifier)
{
    const char*     name = "shm-example";
    int             shm_fd;	
    void*           sharedMemoryBase    = NULL;

    shm_fd = shm_open(name, O_CREAT|O_RDWR, 0666);
    if (shm_fd == -1) 
    {
        PANIC("shm_open failed.");
    }

    ftruncate(shm_fd, SIZE);

    sharedMemoryBase = mmap(0, SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (sharedMemoryBase == MAP_FAILED) 
    {
        PANIC("mmap failed.");
    }

    //DebugPrintf("mapped range = %p to %p\n", sharedMemoryBase, sharedMemoryBase+SIZE);

    //
    //
    //
    memset( sharedMemoryBase, 0xff, SIZE );

    return sharedMemoryBase;
}



//
//
//
volatile void* SharedMemorySlaveInitialise(uint32_t identifier)
{
    const char* name = "shm-example";
    int         shm_fd;
    void*       sharedMemoryBase    = NULL;

    shm_fd = shm_open(name, O_RDWR, 0666);
    if (shm_fd == -1) 
    {
        PANIC();
    }

    sharedMemoryBase = mmap(0, SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (sharedMemoryBase == MAP_FAILED) 
    {
        PANIC();
    }

    //DebugPrintf("mapped range = %p to %p\n", sharedMemoryBase, sharedMemoryBase+SIZE);

    return sharedMemoryBase;
}


