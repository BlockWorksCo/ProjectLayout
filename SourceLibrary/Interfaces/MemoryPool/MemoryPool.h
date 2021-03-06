//
// Copyright (C) BlockWorks Consulting Ltd - All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
// Written by Steve Tickle <Steve@BlockWorks.co>, September 2014.
//



#ifndef __MEMORYPOOL_H__
#define __MEMORYPOOL_H__



#define MEMORYPOOL(name, size, numberOfElements)                \
typedef struct                                                  \
{                                                               \
    uint32_t    bottomCanary;                                   \
    uint8_t     data[size];                                     \
    uint32_t    topCanary;                                      \
    bool        allocated;                                      \
} PoolElement_##name;                                           \
PoolElement_##name  pool##name[numberOfElements];               \
void* AllocateFromPool_##name()                                 \
{                                                               \
    for(uint32_t i = 0; i<numberOfElements; i++)                \
    {                                                           \
        if(pool##name[i].allocated == false)                    \
        {                                                       \
            pool##name[i].bottomCanary     = 0x0123abcd;        \
            pool##name[i].bottomCanary     = 0xabcd0123;        \
            pool##name[i].allocated     = true;                 \
            return (void*)&pool##name[i].data;                  \
        }                                                       \
    }                                                           \
}                                                               \
void ReleaseToPool_##name( PoolElement_##name* element )        \
{                                                               \
    element->allocated  = false;                                \
}                                                               \


#endif

