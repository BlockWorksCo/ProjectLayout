//
// Copyright (C) BlockWorks Consulting Ltd - All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
// Written by Steve Tickle <Steve@BlockWorks.co>, September 2014.
//






#ifndef __EVENTQUEUE_H__
#define __EVENTQUEUE_H__


typedef void (*Handler)();


void Call( Handler handler );
void CallFromInterrupt( Handler handler );

void DispatchHandlers();

#endif

