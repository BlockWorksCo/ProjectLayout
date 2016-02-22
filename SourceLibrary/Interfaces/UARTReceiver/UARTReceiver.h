//
// Copyright (C) BlockWorks Consulting Ltd - All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
// Written by Steve Tickle <Steve@BlockWorks.co>, September 2014.
//


#ifndef __UARTRECEIVER_H__
#define __UARTRECEIVER_H__



#include "Common.h"
#include "EventQueue.h"


void uartRxISR();
uint8_t UARTReceiveByte();

#endif




