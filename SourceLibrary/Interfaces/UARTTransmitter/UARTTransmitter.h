//
// Copyright (C) BlockWorks Consulting Ltd - All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
// Written by Steve Tickle <Steve@BlockWorks.co>, September 2014.
//


#ifndef __UARTTRANSMITTER_H__
#define __UARTTRANSMITTER_H__



#include "Platform.h"
#include "EventQueue.h"


void uartISR();
void UARTTransmitByte( uint8_t byte );

#endif




