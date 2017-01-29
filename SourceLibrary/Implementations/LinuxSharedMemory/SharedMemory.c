



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





void* SharedMemoryMasterInitialise(uint32_t identifier)
{
    const char*     name = "shm-example";
    const int       SIZE = 4096;
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

    return sharedMemoryBase;
}




void* SharedMemorySlaveInitialise(uint32_t identifier)
{
    const char* name = "shm-example";
    const int   SIZE = 4096;		
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

    return sharedMemoryBase;
}


