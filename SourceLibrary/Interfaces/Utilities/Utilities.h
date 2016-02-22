//
// Copyright (C) BlockWorks Consulting Ltd - All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
// Written by Steve Tickle <Steve@BlockWorks.co>, September 2014.
//






#ifndef __UTILITIES_H__
#define __UTILITIES_H__

#include "Common.h"
#include "DebugText.h"



//#define offsetof(st, m)         ((size_t)(&((st *)0)->m))

#define NUMBER_OF_ELEMENTS(a)   (sizeof(a)/sizeof(a[0]))

#define PRIVATE                 static


#define DPRINTF(format, ...)    DebugPrintf(format, ##__VA_ARGS__)
#define TRACE                   DebugPrintf("<%s:%d>\n",__FILE__,__LINE__)
#define DBG                     DebugPrintf("%s:%d\n",__FILE__,__LINE__)

void PANIC();

uint32_t CurrentTimestamp_ms();



#endif

