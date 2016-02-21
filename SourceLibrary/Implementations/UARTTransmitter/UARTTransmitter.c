//
// Copyright (C) BlockWorks Consulting Ltd - All Rights Reserved.
// Unauthorized copying of this file, via any medium is strictly prohibited.
// Proprietary and confidential.
// Written by Steve Tickle <Steve@BlockWorks.co>, September 2014.
//


#ifndef __UARTTRANSMITTER_H__
#define __UARTTRANSMITTER_H__



#include "UARTTransmitter.h"
#include "Utilities.h"


PRIVATE uint8_t     byteToTransmit;
PRIVATE uint8_t     bitNumber;
PRIVATE uint8_t     state;


bool    txState = false;

void SET_TX()
{
    txState  = true;
}

void CLEAR_TX()
{
    txState = false;
}




void uartISR()
{
    if( state == 0 )
    {
        //
        // Start bit.
        //
        CLEAR_TX();
    }
    else if( (state>=1) && (state<9) )
    {
        uint8_t     bitNumber = state-1;

        //
        // data bits
        //
        if( (byteToTransmit&(1<<bitNumber)) != 0)
        {
            SET_TX();
        }
        else
        {
            CLEAR_TX();
        }
    }
    else if( state == 9 )
    {
        //
        // Stop bit.
        //
        SET_TX();
    }

    state++;
}

void UARTTransmitByte( uint8_t byte )
{
    state           = 0;
    bitNumber       = 0;
    byteToTransmit  = byte;


}

#endif




