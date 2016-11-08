//
// Copyright (C) BlockWorks Consulting Ltd - All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
// Written by Steve Tickle <Steve@BlockWorks.co>, September 2014.
//


#include "UARTReceiver.h"
#include "ErrorHandling.h"


PRIVATE uint32_t    sampleNumber    = 0;



void ResetUARTReceiver()
{
    sampleNumber    = 0;
}


void UARTReceiveHandler()
{
    bool    sample  = GET_RX_STATE();



    sampleNumber++;
}



uint8_t GetUARTReceivedByte()
{
    return 0;
}



