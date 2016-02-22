//
// Copyright (C) BlockWorks Consulting Ltd - All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
// Written by Steve Tickle <Steve@BlockWorks.co>, September 2014.
//






#ifndef __TIMEDEVENTS_H__
#define __TIMEDEVENTS_H__


#include "Common.h"
#include "EventQueue.h"


void CallEvery_ms( Handler handler, uint32_t interval );
void CallAfter_ms( Handler handler, uint32_t interval );
void CheckTimedEventHandlers();


#endif

