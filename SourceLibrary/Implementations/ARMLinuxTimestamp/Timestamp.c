


#include "Timestamp.h"


void TimestampInitialise()
{

}



Timestamp GetTimestamp()
{
    uint32_t r = 0;
    __asm volatile("mrc p15, 0, %0, c9, c13, 0" : "=r"(r) );

    return r;
}



