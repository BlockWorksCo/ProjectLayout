//
// Copyright (C) BlockWorks Consulting Ltd - All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
// Written by Steve Tickle <Steve@BlockWorks.co>, September 2014.
//






#ifndef __BLOCKEDEVENTS_H__
#define __BLOCKEDEVENTS_H__

#include "Platform.h"
#include "EventQueue.h"


void CallWhenUnblocked( Handler handler, bool* blockingFlag );
void CheckBlockedEventHandlers();

#endif

