//
// Copyright (C) BlockWorks Consulting Ltd - All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
// Written by Steve Tickle <Steve@BlockWorks.co>, September 2014.
//






#ifndef __UTILITIES_H__
#define __UTILITIES_H__

#include "Platform.h"


#define NUMBER_OF_ELEMENTS(a)   (sizeof(a)/sizeof(a[0]))
#define TRACE                   printf("<%s:%d>\n",__FILE__,__LINE__)

#define PRIVATE                 static

#define DPRINTF(format, ...)    printf(format, ##__VA_ARGS__)

#define DBG                     printf("%s:%d\n",__FILE__,__LINE__)

void PANIC();

uint32_t CurrentTimestamp_ms();



#endif

