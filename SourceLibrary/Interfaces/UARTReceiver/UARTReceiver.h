//
// Copyright (C) BlockWorks Consulting Ltd - All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
// Written by Steve Tickle <Steve@BlockWorks.co>, September 2014.
//


#ifndef __UARTRECEIVER_H__
#define __UARTRECEIVER_H__



#include "Common.h"


bool GET_RX_STATE();

void ResetUARTReceiver();
void UARTReceiveHandler();
uint8_t GetUARTReceivedByte();

#endif




