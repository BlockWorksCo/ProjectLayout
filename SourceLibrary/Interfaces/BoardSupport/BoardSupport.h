//
// Copyright (C) BlockWorks Consulting Ltd - All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
// Written by Steve Tickle <Steve@BlockWorks.co>, September 2014.
//



#ifndef __BOARDSUPPORT_H__
#define __BOARDSUPPORT_H__



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


extern CoreServicesBridge*     bridge;



uint32_t CoreNumber();
void BoardSupportInitialise();
void EnableInterrupts();
void TriggerMailboxInterrupt(uint32_t toID);

void FlushCache();

#endif


