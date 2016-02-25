//
// Copyright (C) BlockWorks Consulting Ltd - All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
// Written by Steve Tickle <Steve@BlockWorks.co>, September 2014.
//



#ifndef __SAFETY_H__
#define __SAFETY_H__



#include "Common.h"
#include "ErrorHandling.h"


#define PANIC_IF_ADDRESS_IS_NOT_READABLE( address )         if(IsPointerReadable() == false) PAINC()
#define PANIC_IF_ADDRESS_IS_NOT_WRITABLE( address )         if(IsPointerWritable() == false) PAINC()
#define PANIC_IF_ADDRESS_IS_NOT_EXECUTABLE( address )       if(IsPointerExecutable() == false) PAINC()


bool IsPointerReadable( void* pointer );
bool IsPointerWritable( void* pointer );
bool IsPointerExecutable( void* pointer );


#endif