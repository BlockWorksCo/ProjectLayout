//
// Copyright (C) BlockWorks Consulting Ltd - All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
// Written by Steve Tickle <Steve@BlockWorks.co>, September 2014.
//



#ifndef __THREADLOCALSTORAGE_H__
#define __THREADLOCALSTORAGE_H__

#include "Common.h"
#include "Alloy.h"

//
//
//
typedef struct
{
    CoreMessage             message;
    uint32_t                numberOfMessagesAvailable;
    
} GlobalData;


GlobalData* Globals();


#endif
