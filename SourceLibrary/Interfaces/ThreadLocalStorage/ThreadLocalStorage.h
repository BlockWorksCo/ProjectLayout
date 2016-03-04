


#ifndef __THREADLOCALSTORAGE_H__
#define __THREADLOCALSTORAGE_H__

#include "Common.h"
#include "Alloy.h"  // TODO: Remove me.

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

